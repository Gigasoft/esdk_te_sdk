/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_STREAM_H_
#define _Z_CTK_XML_STREAM_H_

#include "ctk/xml/XMLInStream.h"
#include "ctk/xml/XMLOutStream.h"

namespace ctk {
namespace xml {

    class CTK_API XMLStream : public XMLInStream, public XMLOutStream
    {
    public:
        //{{{ output stream
        XMLStream();
        XMLStream(rcistr _name);
        XMLStream(out_t, rcistr _name);
        XMLStream(out_t, rcistr _nodeName, XMLOutStream& _parent);
        XMLStream(out_t, XMLNode& _node);
        //}}}
        //{{{ input stream
        XMLStream(std::ifstream& _ifs);
        XMLStream(in_t, rcistr _xml);
        XMLStream(in_t, rcistr _nodeName, const XMLInStream& _parent);
        XMLStream(in_t, const XMLNode& _node);
        //}}}
        ~XMLStream();

        template<class T>
        bool attribute(rcistr _attrName, T& _attrValue)
        {
            if (isInputting())
                return XMLInStream::attribute(_attrName, _attrValue);

            XMLOutStream::attribute(_attrName, _attrValue);
            return true;
        }

        template<class T>
        bool attribute(rcistr _attrName, T& _attrValue) const
        {
            return XMLInStream::attribute(_attrName, _attrValue);
        }

        // 如果节点名已经存在，则覆盖，否该新建。
        template<class T>
        void element(rcistr _childName, T& _childValue)
        {
            if (isInputting())
                XMLInStream::element(_childName, _childValue);
            else
                XMLOutStream::element(_childName, _childValue);
        }

        template<class T>
        void element(rcistr _childName, T& _childValue) const
        {
            XMLInStream::element(_childName, _childValue);
        }

        // T is a container, such as vector<>
        template<class T>
        void element(rcistr _childName, T& _childValue, pcstr _elemName)
        {
            element(_childName, _childValue, (istr)_elemName);
        }

        // T is a container, such as vector<>
        template<class T>
        void element(rcistr _childName, T& _childValue, istr _elemName)
        {
            if (isInputting())
                XMLInStream::element(_childName, _childValue);
            else
                XMLOutStream::element(_childName, _childValue, _elemName);
        }

        template<class T, class Fn>
        void element(rcistr _childName, T& _childValue, Fn _fn)
        {
            if (isInputting())
                XMLInStream::element(_childName, _childValue, _fn);
            else
                XMLOutStream::element(_childName, _childValue, _fn);
        }

        template<class T>
        void element(rcistr _childName, T& _childValue, pcstr _elemName) const
        {
            element(_childName, _childValue, (istr)_elemName);
        }

        template<class T>
        void element(rcistr _childName, T& _childValue, istr _elemName) const
        {
            XMLInStream::element(_childName, _childValue);
        }

        template<class T, class Fn>
        void element(rcistr _childName, T& _childValue, Fn _fn) const
        {
            XMLInStream::element(_childName, _childValue, _fn);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value)
        {
            if (isInputting())
            {
                // 输入时可以分别检查属性和子节点。
                XMLInStream::operator()(_name, _value);
            }
            else
            {
                // 输出只能输出到子节点。
                // 如果要输出到属性就要用attribute函数。
                XMLOutStream::operator()(_name, _value);
            }
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value) const
        {
            XMLInStream::operator()(_name, _value);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::pcstr _elemName)
        {
            operator()(_name, _value, (ctk::istr)_elemName);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::istr _elemName)
        {
            if (isInputting())
            {
                XMLInStream::operator()(_name, _value);
            }
            else
            {
                XMLOutStream::operator()(_name, _value, _elemName);
            }
        }

        template<class T, class Fn>
        void operator()(ctk::rcistr _name, T& _value, Fn _fn)
        {
            if (isInputting())
            {
                XMLInStream::operator()(_name, _value, _fn);
            }
            else
            {
                XMLOutStream::operator()(_name, _value, _fn);
            }
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::pcstr _elemName) const
        {
            operator()(_name, _value, (ctk::istr)_elemName);
        }

        template<class T>
        void operator()(ctk::rcistr _name, T& _value, ctk::istr _elemName) const
        {
            XMLInStream::operator()(_name, _value);
        }

        template<class T, class Fn>
        void operator()(ctk::rcistr _name, T& _value, Fn _fn) const
        {
            XMLInStream::operator()(_name, _value, _fn);
        }

        // attribute accessor

        XMLAttr& attr( rcistr _name )
        {
            if (isInputting())
            {
                return const_cast<XMLAttr&>(XMLInStream::attr(_name));
            }
            else
            {
                return XMLOutStream::attr(_name);
            }
        }

        XMLAttr& operator()( rcistr _name )
        {
            return attr(_name);
        }

        const XMLAttr& attr( rcistr _name ) const
        {
            return XMLInStream::attr(_name);
        }

        const XMLAttr& operator()( rcistr _name ) const
        {
            return attr(_name);
        }

        // element accessor

        XMLNode& child( rcistr _name )
        {
            if (isInputting())
            {
                return const_cast<XMLNode&>(XMLInStream::child(_name));
            }
            else
            {
                return XMLOutStream::child(_name);
            }
        }

        XMLNode& operator[]( rcistr _name )
        {
            return child(_name);
        }

        const XMLNode& child( rcistr _name ) const
        {
            return XMLInStream::child(_name);
        }

        const XMLNode& operator[]( rcistr _name ) const
        {
            return child(_name);
        }

    };

    typedef XMLStream xstream;

} // end of namespace xml
} // end of namespace ctk

#endif // _Z_CTK_XML_STREAM_H_

