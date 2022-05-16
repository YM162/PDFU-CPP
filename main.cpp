#include <iostream>
#include <string>
#include <podofo/podofo.h>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace PoDoFo;

int cleanpage(PdfPage* page,PdfMemDocument* document){
//Cleans the page and adds it to the end of the document.
  PdfDictionary resource = page->GetResources()->GetDictionary();
  
  for (auto& resourcekeys : resource.GetKeys()) {
    if (resourcekeys.first.GetName() == "XObject") {
      if (resourcekeys.second->IsDictionary()) {
        PdfDictionary targetDict = resourcekeys.second->GetDictionary();
        for (auto& r : resourcekeys.second->GetDictionary().GetKeys()) {
          if (r.first.GetEscapedName().find("EmbeddedPdfPage",0)==0){
            if (r.second->IsReference()){
              
              //Si tenemos una embeddedpdfpage, creamos la página nueva para añadir
              PdfObject* target = document->GetObjects().GetObject(r.second->GetReference());
              PdfPage* newpage = document->CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );
  
              PdfDictionary targetDict = target->GetDictionary();
              //A pageDictionary metemos BBox como MediaBox y Resources
              
              newpage->GetObject()->GetDictionary().AddKey("MediaBox",targetDict.GetKey("BBox"));

              PdfObject* resources = targetDict.GetKey("Resources");
              PdfObject* newresources = newpage->GetResources();

              auto resource_keys = resources->GetDictionary().GetKeys();
              for (TCIKeyMap key = resource_keys.begin();key!=resource_keys.end();++key)
              {
                newresources->GetDictionary().AddKey(key->first.GetEscapedName(),resources->GetDictionary().GetKey(key->first.GetEscapedName()));
              }

              //gcont es el diccionario donde meteremos las keys Lenght y Filter
              PdfContents* contents = new PdfContents(newpage);
              PdfObject* gcont = contents->GetContents();
              PdfObject* length = targetDict.GetKey("Length");
              PdfObject* filter = targetDict.GetKey("Filter");
              gcont->GetDictionary().AddKey("Length",length);
              gcont->GetDictionary().AddKey("Filter",filter);
              //std::cout << "Stream length: " << length->GetNumber() << std::endl;
              
              //Copiamos el stream a un buffer, habrá que optimizar el número
              int buffersize = 20000;
              pdf_long len = buffersize;
              char* buffer = (char*)malloc(buffersize);
              target->GetStream()->GetFilteredCopy(&buffer,&len);
              
              //Añadimos el buffer a gstream
              PdfStream* gstream = gcont->GetStream();
              TVecFilters filters = PdfFilterFactory::CreateFilterList(filter);
              gstream->BeginAppend(filters);
              gstream->Append(buffer,len);
              gstream->EndAppend();
              
              return 1;
              }}}}}}
              return 0;
}

int deembed( const char* openFilename ,const char* saveFilename) {
    /* pdzFilename es el archivo que se va a abrir*/
    PdfMemDocument document( openFilename );
    
    int total_pages = document.GetPageCount();
    int newpage_number = 0;
    for (int i;i<total_pages;i++){
      newpage_number = newpage_number + cleanpage(document.GetPage(i),&document);
    }
    if (newpage_number==0){
      return 1;
    }
    document.DeletePages(0,total_pages);
    auto start = std::chrono::high_resolution_clock::now();
    
    document.Write( saveFilename );

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    double display= (double)duration.count()/(double)1000;
    std::cout << "Time used writing: " << display << " ms" << std::endl;
    
    return 0;

}

int main( int argc, char* argv[] ) {
    auto start = std::chrono::high_resolution_clock::now();
    std::cout<<argc<<std::endl;
    if (argc!=2){std::cout<<"Use 1 argument for pdf path."<<std::endl;return 1;};

    std::string load = argv[1];
    std::string save = load.substr(0, load.size()-4) + "write.pdf";

    try {
         if (deembed(load.c_str(),save.c_str())==0){
           std::cout << "Limpiado correctamente" << std::endl;
         }else{
           std::cout << "No se han encontrado páginas insertadas" << std::endl;
         };
    } catch( const PdfError & eCode ) {
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    double display= (double)duration.count()/(double)1000;
    std::cout << "Time used total: " << display << " ms" << std::endl;
    
}