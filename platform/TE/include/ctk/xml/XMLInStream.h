/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_IN_STREAM_H_
#define _Z_CTK_XML_IN_STREAM_H_

#include "ctk/xml/XMLStreamBase.h"

#include "ctk/xml/XMLParser.h"

#define CTK_XML_DECODE(xis, field)                 xis(CTK_NV_VAR(field))
#define CTK_XML_DECODE_FN(xis, field, fn)          xis(CTK_NV_VAR(field), fn)

#define CTK_XML_DECODE_NV(xis, name, var)          xis(name, var)
#define CTK_XML_DECODE_NV_FN(xis, name, var, fn)   xis(name, var, fn)

namespace ctk {
namespace xml {

    template<class T> struct Decoder;

    class CTK_API XMLInStream : virtual public XMLStreamBase
    {
    public:
        XMLInStream();
        XMLInStream(rcistr _xml);
        XMLInStream(std::ifstream& _ifs);
        XMLInStream(rcistr _nodeName, const XMLInStream& _parent);
        XMLInStream(const XMLNode& _node);
        ~XMLInStream();

        void parse(rcistr _xml);
        void parse(std::ifstream& _ifs);

        rcstr type() const;

        const XMLAttr& operator()( rcistr _name ) const;
        const XMLAttr& attr( rcistr _name ) const;

        const XMLNode& operator[]( rcistr _name ) const ;
        const XMLNode& child( rcistr _name ) const ;

        void operator>>(bool& _value) const;
        void operator>>(char& _value) const;
        void operator>>(uchar& _value) const;
        void operator>>(int16& _value) const;
        void operator>>(uint16& _value) const;
        void operator>>(int32& _value) const;
        void operator>>(uint32& _value) const;
#if defined(_CTK_INT32_IS_LONG)
        void operator>>(int& _value) const;
        void operator>>(uint& _value) const;
#endif
        void operator>>(int64& _value) const;
        void operator>>(uint64& _value) const;
        void operator>>(float& _value) const;
        void operator>>(double& _value) const;

        void operator>>(volatile bool& _value) const;
        void operator>>(volatile char& _value) const;
        void operator>>(volatile uchar& _value) const;
        void operator>>(volatile int16& _value) const;
        void operator>>(volatile uint16& _value) const;
        void operator>>(volatile int32& _value) const;
        void operator>>(volatile uint32& _value) const;
#if defined(_CTK_INT32_IS_LONG)
        void operator>>(volatile int& _value) const;
        void operator>>(volatile uint& _value) const;
#endif
        void operator>>(volatile int64& _value) const;
        void operator>>(volatile uint64& _value) const;
        void operator>>(volatile float& _value) const;
        void operator>>(volatile double& _value) const;
        
        void operator>>(Int1& _value) const;
        void operator>>(Int16& _value) const;
        void operator>>(Int32& _value) const;
        void operator>>(Int64& _value) const;
        void operator>>(Uint8& _value) const;
        void operator>>(Uint16& _value) const;
        void operator>>(Uint32& _value) const;
        void operator>>(Wchar& _value) const;
        void operator>>(string& _value) const;
        void operator>>(String& _value) const;
        void operator>>(Wstring& _value) const;
        void operator>>(Bytes& _value) const;
        void operator>>(Time& _value) const;

        // 基本类型使用istream输入取值。
        template<class T>
        void operator>>(T& _v) const
        {
            _v.decodeXml(*this);
        }

        template<class T>
        bool attribute(rcistr _attrName, T& _attrValue) const
        {
            return attr(_attrName) >> _attrValue;
        }

        template<class T>
        bool element(rcistr _childName, T& _childValue) const
        {
            return child(_childName) >> _childValue;
        }

        // 建议只在容器元素为简单类型或其它非自定义类型再用函数子。
        // 对于自定义类型，可以在其中加入编解码函数，然后就支持<<和>>了。
        // 下面的例子假设对于
        // <userlist>
        //   <user uri="..."/>
        //   <user uri="..."/>
        // </userlist>
        // 解码。
        //ctk::vector<ctk::String> userlist;
        //struct FnUserXmlIn
        //{
        //    void operator()(const ctk::xml::XMLInStream& xis, ctk::String& _uri)
        //    {
        //        xis("uri") >> _uri; // 等价于 xis.attribute("uri", uri_);
        //    }
        //};
        //xisSome.element("userlist", userlist, FnUserXmlIn());
        //或：xisSome("userlist", userlist, FnUserXmlIn());

        template<class T, class _Fn>
        bool element(rcistr _childName, T& _childValue, _Fn _fn) const
        {
            const ctk::xml::XMLNode& node = child(_childName);
            if (node.isNull())
                return false;
            XMLInStream xis(node);
            xis.iterate(_childValue, _fn);
            return true;
        }

        // _childValue是一个容器，其内包括一个定义容器元素类型的value_type（标准的std和ctk容器都有）。
        // 对ctk::set或ctk::map这样的容器，可以用input函数（指定插入器类型为ctk::random_inserter）。
        template<class T, class _Fn>
        void iterate(T& _childValue, _Fn _fn) const
        {
            for (size_type i=0; i<numofChildren(); ++i)
            {
                typename T::value_type tmp;
                XMLInStream xis(childAt(i));
                _fn(xis, tmp);
                *std::back_inserter(_childValue) = tmp;
            }
        }

        template<class _Inserter>
        void input(_Inserter _inserter) const
        {
            input(_inserter, Decoder<typename _Inserter::container_type::value_type>());
        }

        template<class _Inserter, class _Fn>
        void input(_Inserter _inserter, _Fn _fn) const
        {
            for (size_type i=0; i<numofChildren(); ++i)
            {
                typename _Inserter::container_type::value_type tmp;
                XMLInStream xis(childAt(i));
                _fn(xis, tmp);
                *_inserter = tmp;
            }
        }

        template<class T>
        bool operator()(ctk::rcistr _name, T& _value) const
        {
            if (element(_name, _value))
                return true;

            if (attribute(_name, _value))
                return true;
            
            return false;
        }

        template<class T, class _Fn>
        bool operator()(ctk::rcistr _name, T& _value, _Fn _fn) const
        {
            if (element(_name, _value, _fn))
                return true;

            if (attribute(_name, _value))
                return true;
            
            return false;
        }

    };

    // 结合XMLInStream的[]使用
    template<class T>
    bool operator>>(const XMLNode& _n, T& _v)
    {
        if (_n.isNull())
            return false;

        XMLInStream xis(_n);
        xis >> _v;
        return true;
    }

    template<class T>
    bool operator>>(const XMLAttr& _n, T& _v)
    {
        if (_n.isNull())
            return false;

        XMLNode node(_n.value(), cdata_t());
        XMLInStream xis(node);
        xis >> _v;
        return true;
    }

    // 缺省的解码函数子
    template<class T>
    struct Decoder
    {
        void operator()(const XMLInStream& _xis, T& _v)
        {
            _xis >> _v;
        }
    };

    // 自定义类型（结构）需要重载:
    //     void operator>>(const XMLInStream& _xis, UserDefinedClass& _v);
    // 建议在UserDefinedClass中定义decodeXml函数:
    //     void decodeXml(const XMLInStream& _xis);
    // 供operator>>调用。
    // 或从XMLCodecBase派生，参见XMLCodec.h。
} // end of namespace xml
} // end of namespace ctk

#endif // _Z_CTK_XML_IN_STREAM_H_

