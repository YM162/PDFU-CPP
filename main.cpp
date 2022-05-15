#include <iostream>
#include <string>
#include <podofo/podofo.h>
#include <cstdlib>

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

              newresources->GetDictionary().AddKey("ExtGState",resources->GetDictionary().GetKey("ExtGState"));
              newresources->GetDictionary().AddKey("Font",resources->GetDictionary().GetKey("Font"));
              newresources->GetDictionary().AddKey("ProcSet",resources->GetDictionary().GetKey("ProcSet"));
              newresources->GetDictionary().AddKey("XObject",resources->GetDictionary().GetKey("XObject"));
              

              //gcont es el diccionario donde meteremos las keys Lenght y Filter
              PdfContents* contents = new PdfContents(newpage);
              PdfObject* gcont = contents->GetContents();
              PdfObject* length = targetDict.GetKey("Length");
              PdfObject* filter = targetDict.GetKey("Filter");
              gcont->GetDictionary().AddKey("Length",length);
              gcont->GetDictionary().AddKey("Filter",filter);
              std::cout << "Stream length: " << length->GetNumber() << std::endl;
              
              //Copiamos el stream a un buffer, habrá que optimizar el número
              int buffersize = 1000000;
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
    for (int i=0;i<total_pages;i++){
      newpage_number = newpage_number + cleanpage(document.GetPage(i),&document);
    }
    std::cout << "New pages: " << newpage_number << std::endl;
    if (newpage_number==0){
      return 1;
    }
    document.DeletePages(0,total_pages);
    document.Write( saveFilename );
    return 0;

}

int main( int argc, char* argv[] ) {
    try {
         if (deembed("/home/yomismo/Projects/PDFU-CPP/tests/testpdf/test.pdf","/home/yomismo/Projects/PDFU-CPP/tests/testpdf/write.pdf")==0){
           std::cout << "Limpiado correctamente" << std::endl;
         }else{
           std::cout << "No se han encontrado páginas insertadas" << std::endl;
         };
    } catch( const PdfError & eCode ) {
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }
}
