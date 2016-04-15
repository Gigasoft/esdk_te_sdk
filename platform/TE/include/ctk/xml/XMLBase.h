/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_BASE_H_
#define _Z_CTK_XML_BASE_H_

#include <ctk/ctk_config.h>
#include <ctk/base.h>
#include <ctk/util.h>
 
namespace ctk {
namespace xml {

    class XMLAttr;
    class XMLNode;
    class XMLParser;

    class CTK_API XMLRuntimeException : public std::exception
    {
    public:
        XMLRuntimeException(rcistr _msg);
        XMLRuntimeException(rcistr _msg, rcistr _file, size_t _line);
        virtual ~XMLRuntimeException() CTK_NOTHROW;

        virtual const char *what() const CTK_NOTHROW
        {
            return "XMLRuntimeException";
        }

    public:
        String message_;
        String fileName_;
        size_t lineNumber_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const XMLRuntimeException& _e);

    struct CTK_API XMLParserCallback
    {
        virtual ~XMLParserCallback()
        {
        }

        virtual void onNodeBegin (XMLParser* _parser, XMLNode* _found )
        {
        }

        virtual void onNodeEnd   (XMLParser* _parser, XMLNode* _found )
        {
        }

        virtual void onCDATAFound(XMLParser* _parser, XMLNode* _found )
        {
        }

        virtual void onAttrFound (XMLParser* _parser, XMLAttr* _found )
        {
        }

    };

} // end of namespace xml
} // end of namespace ctk

#endif // _Z_CTK_XML_BASE_H_

