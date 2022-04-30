/***************************************************************************
 *   Copyright (C) 2006 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


/*
 * Include the standard headers for cout to write
 * some output to the console.
 */
#include <iostream>

/*
 * Now include all podofo header files, to have access
 * to all functions of podofo and so that you do not have
 * to care about the order of includes.
 *
 * You should always use podofo.h and not try to include
 * the required headers on your own.
 */
#include <podofo/podofo.h>

/*
 * All podofo classes are member of the PoDoFo namespace.
 */
using namespace PoDoFo;


void deembed( const char* openFilename ,const char* saveFilename) 
{
    /* pdzFilename es el archivo que se va a abrir*/
    PdfMemDocument document( openFilename );
    /*
     * This pointer will hold the page object later. 
     * PdfSimpleWriter can write several PdfPage's to a PDF file.
     */
    PdfPage* pPage;

    for (auto i:document.GetObjects()){
        std::cout<<i<<"\n";
    };
    

    document.Write(saveFilename);
}

int main( int argc, char* argv[] )
{
    
    try {
        /*
         * Call the drawing routing which will create a PDF file
         * with the filename of the output file as argument.
         */
         deembed("/home/yomismo/Projects/PDFU-CPP/tests/testpdf/test_deembedded.pdf","/home/yomismo/Projects/PDFU-CPP/tests/testpdf/unembedded.pdf");
    } catch( const PdfError & eCode ) {
        /*
         * We have to check if an error has occurred.
         * If yes, we return and print an error message
         * to the commandline.
         */
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }
}
