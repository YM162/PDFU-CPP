#include <iostream>
#include <string>
#include <podofo/podofo.h>
#include <cstdlib>

using namespace PoDoFo;

void deembed( const char* openFilename ,const char* saveFilename) {
    /* pdzFilename es el archivo que se va a abrir*/
    PdfMemDocument document( openFilename );
    // Hay que hacer un loop que pase por todas las páginas del documento
    PdfPage* page = document.GetPage(1);
    PdfPage* newpage;
    PdfDictionary resource = page->GetResources()->GetDictionary();
    
    auto objvec = document.GetObjects();
    
    
              
    //PdfPainter painter;
    //painter.SetPage(newpage);
    newpage =document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );
    
    for (auto& k : resource.GetKeys()) {
    if (k.first.GetName() == "XObject") {
      if (k.second->IsDictionary()) {
        auto targetDict = k.second->GetDictionary();
        for (auto& r : k.second->GetDictionary().GetKeys()) {
          if (r.first.GetEscapedName().find("EmbeddedPdfPage",0)==0){
            if (r.second->IsReference()){
              auto target = document.GetObjects().GetObject(r.second->GetReference());
             
              //Del targetDict sacaremos las keys para introducirlas en la pagina
              //BBox que se convertirá en MediaBox
              //Resources que también será Resources
              //Lenght y Filter también salen de aquí
              auto targetDict = target->GetDictionary();
              auto targetstream = target->GetStream();
              auto contents = new PdfContents(newpage);
              
              //A pageDictionary metemos BBox como MediaBox y Resources
              auto pageDictionary = newpage->GetObject()->GetDictionary();
              auto bbox = targetDict.GetKey("BBox");
              auto resources = targetDict.GetKey("Resources");
              pageDictionary.AddKey("MediaBox",bbox);
              //PUEDE QUE ESTÉ AQUÍ EL ERROR, NO SE SI LOS ESTOY METIENDO BIEN!!!!!
              //pageDictionary.AddKey("Resources",resources);
              auto newresources = newpage->GetResources();
              std::cout << "Newresources: "<< newresources->GetDataTypeString() << std::endl;
              
              auto resources_keys = resources->GetDictionary().GetKeys();
              
              newresources->GetDictionary().RemoveKey("ProcSet");
              
              for (TCIKeyMap key = resources_keys.begin();key!=resources_keys.end();++key)
              {
                std::cout << key->first.GetEscapedName() << ": ";
                std::cout << key->second->GetDataTypeString() << std::endl;
                //newresources->GetDictionary().AddKey(key->first.GetEscapedName(),key->second);
              }
              newresources->GetDictionary().AddKey("ExtGState",resources->GetDictionary().GetKey("ExtGState"));
              newresources->GetDictionary().AddKey("Font",resources->GetDictionary().GetKey("Font"));
              auto fontobj = resources->GetDictionary().GetKey("Font");
              newresources->GetDictionary().AddKey("ProcSet",resources->GetDictionary().GetKey("ProcSet"));
              newresources->GetDictionary().AddKey("XObject",resources->GetDictionary().GetKey("XObject"));
              
              auto r10 = document.GetObjects().GetObject(fontobj->GetDictionary().GetKey("R10")->GetReference());
              auto r8 = document.GetObjects().GetObject(fontobj->GetDictionary().GetKey("R8")->GetReference());
              fontobj->GetDictionary().AddKey("R10",r10);
              fontobj->GetDictionary().AddKey("R8",r8);

              //gcont es el diccionario donde meteremos las keys Lenght y Filter
              auto gcont = contents->GetContents();
              auto length = targetDict.GetKey("Length");
              std::cout << "Lenght: " << length->GetNumber() << std::endl;
              auto filter = targetDict.GetKey("Filter");
              gcont->GetDictionary().AddKey("Length",length);
              gcont->GetDictionary().AddKey("Filter",filter);

              //A gstream metemos targetstream
              
            char* buffer = (char*)malloc(100000);
              pdf_long len = 100000;
              targetstream->GetFilteredCopy(&buffer,&len);
              //std::cout << buffer << std::endl;




              auto gstream = gcont->GetStream();
              //Con este bloque añadimos lo que queramos a gstream
              auto filters = PdfFilterFactory::CreateFilterList(filter);
              gstream->BeginAppend(filters);
              gstream->Append(buffer,len);
              gstream->EndAppend();
              
              //Ver la longitud del stream. Debugging.
              std::cout << gcont->GetStream()->GetLength() << std::endl;
              //auto pagecontent = newdoc.GetObjects()->GetObject(pageDictionary.GetKey(PdfName::KeyContents)->GetReference());

              //Con este bloque podemos ver los nombres de las keys de un diccionario
              auto content_keys = r8->GetDictionary().GetKeys();
              for (TCIKeyMap key = content_keys.begin();key!=content_keys.end();++key)
              {std::cout << key->first.GetEscapedName() << ": ";
               std::cout << key->second->GetDataTypeString() << std::endl;}
              

              //painter.DrawXObject(0,0,&a,10,10);
              
            }
            }
            
        //Hay que poner un if que chekee que r.first empiece por "EmbeddedPdfPage"
        //r.second es el objeto a partir del que creamos las páginas nuevas.
          }
        }
    }
    }
    //painter.FinishPage();
 
    document.Write("/home/yomismo/Projects/PDFU-CPP/tests/testpdf/write.pdf");


}

int main( int argc, char* argv[] ) {
    try {
         deembed("/home/yomismo/Projects/PDFU-CPP/tests/testpdf/test.pdf","/home/yomismo/Projects/PDFU-CPP/tests/testpdf/unembedded.pdf");
    } catch( const PdfError & eCode ) {
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }
}
