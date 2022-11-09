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
#ifndef MCUTILS_XML_XMLDOC_H_
#define MCUTILS_XML_XMLDOC_H_

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <libxml/tree.h>

#include <mcutils/defs.h>

#include <mcutils/xml/XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief XML Document class.
 */
class MCUTILSAPI XmlDoc
{
public:

    /** @brief Constrcutor. */
    XmlDoc( const char *fileName = "" );

    /** @brief Destructor. */
    ~XmlDoc();

    /**
     * @brief Gets XML document root node.
     * @return XML document root node
     */
    inline XmlNode getRootNode()
    {
        return XmlNode( *_root );
    }

    /**
     * @brief Checks if XML document is open.
     * @return returns true if XML document is open
     */
    inline bool isOpen() const
    {
        return _open;
    }

    /** @brief Open file for reading. */
    void openFile( const char *fileName );

    /** @brief Closes file. */
    void closeFile();

private:

    xmlDocPtr _doc;     ///< XML document pointer
    bool _open;         ///< specifies if document is open
    XmlNode *_root;     ///< XML document root node
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // MCUTILS_XML_XMLDOC_H_
