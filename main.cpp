#include <iostream>
#include <podofo/podofo.h>

using namespace PoDoFo;

void deembed( const char* openFilename ,const char* saveFilename) {
    /* pdzFilename es el archivo que se va a abrir*/
    PdfMemDocument document( openFilename );
    // Hay que hacer un loop que pase por todas las páginas del documento
    PdfPage* page = document.GetPage(1);
    PdfDictionary resource = page->GetResources()->GetDictionary();
    
    for (auto& k : resource.GetKeys()) {
    if (k.first.GetName() == "XObject") {
      if (k.second->IsDictionary()) {
        auto targetDict = k.second->GetDictionary();
        for (auto& r : k.second->GetDictionary().GetKeys()) {
          std::cout << r.first.GetEscapedName() << "\n";
        //Hay que poner un if que chekee que r.first empiece por "EmbeddedPdfPage"
        //r.second es el objeto a partir del que creamos las páginas nuevas.
          }
        }
    }
    }

    document.Write(saveFilename);

}

int main( int argc, char* argv[] ) {
    try {
         deembed("/home/yomismo/Projects/PDFU-CPP/tests/testpdf/test.pdf","/home/yomismo/Projects/PDFU-CPP/tests/testpdf/unembedded.pdf");
    } catch( const PdfError & eCode ) {
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }
}
