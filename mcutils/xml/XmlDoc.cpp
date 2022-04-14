/****************************************************************************//*
 * Copyright (C) 2022 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <mcutils/xml/XmlDoc.h>

#include <cstring>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

XmlDoc::XmlDoc( const char *fileName )
    : _doc  ( nullptr )
    , _open ( false )
    , _root ( nullptr )
{
    openFile( fileName );
}

////////////////////////////////////////////////////////////////////////////////

XmlDoc::~XmlDoc()
{
    closeFile();
}

////////////////////////////////////////////////////////////////////////////////

void XmlDoc::openFile( const char *fileName )
{
    closeFile();

    if ( std::strlen( fileName ) > 0 )
    {
        _doc = xmlParseFile( fileName );

        if ( _doc == nullptr )
        {
            xmlFreeDoc( _doc );
            return;
        }

        xmlNodePtr root = xmlDocGetRootElement( _doc );

        if ( root == nullptr )
        {
            xmlFreeDoc( _doc );
            return;
        }

        _root = new XmlNode( root, fileName );

        _open = true;
    }
}

////////////////////////////////////////////////////////////////////////////////

void XmlDoc::closeFile()
{
    _open = false;

    if ( _root ) delete _root;
    if ( _doc  ) xmlFreeDoc( _doc );

    _root = nullptr;
    _doc  = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
