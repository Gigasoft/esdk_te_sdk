/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_STL_H_
#define _Z_CTK_LOG_STL_H_

#include "ctk/base/base_type_stl.h"
#include "ctk/base/base_type_pointer.h"
#include "ctk/base/base_type_array.h"

#include "ctk/string/string_charray.h"
#include "ctk/string/string_formatter.h"

#include "ctk/log/log_dumper.h"
#include "ctk/log/log_macros.h"

#include "ctk/mt/handle.h"

namespace ctk
{
    template<class T>
    inline ctk::dumper& operator<<(ctk::dumper& os, const T& v)
    {
        return v.dump(os);
    }

    // ¶ÔSTLÀàÐÍÀ©³ä
    template<class T1, class T2>
    dumper& operator<<(dumper& _d, const std::pair<T1, T2>& _v)
    {
        String s;
        s << _v.first;
        return _d << ctk::rawstring(s.data()) << ctk::rawstring(" : ") << _v.second;
    }

    // T is iterator
    template<class T>
    dumper& output_(dumper& _os, std::pair<T, T> itRange)
    {
        for (T it=itRange.first; it!=itRange.second; ++it)
        {
            DUMP_VAL(_os, *it);
        }
        return _os;
    }

    // T is iterator
    template<class T>
    dumper& output_array_(dumper& _os, std::pair<T, T> itRange)
    {
        ctk::size_type idx = 0;
        for (T it=itRange.first; it!=itRange.second; ++it, ++idx)
        {
            ctk::String name;
            name << "[" << idx << "]";
            DUMP_ONE(_os, name, *it, " ");
        }
        return _os;
    }

    // T is container
    template<class T>
    dumper& output(dumper& _os, const T& _v)
    {
        return output_(_os, std::make_pair(_v.begin(), _v.end()));
    }
    template<class T>
    dumper& output_array(dumper& _os, const T& _v)
    {
        return output_array_(_os, std::make_pair(_v.begin(), _v.end()));
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::vector<T>& _v)
    {
        CTK_DUMP(_d, "ctk::vector");
        return output_array(_d, _v);
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::stack<T>& _v)
    {
        CTK_DUMP(_d, "ctk::stack");
        return output(_d, _v._Get_c());
    }

    template<class T>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::list<T>& _v)
    {
        CTK_DUMP(_d, "ctk::list");
        return output(_d, _v);
    }

    template<class _K, class _V>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::map<_K,_V>& _v)
    {
        CTK_DUMP(_d, "ctk::map");
        return output(_d, _v);
    }

    template<class _K, class _V>
    ctk::dumper& operator<<(ctk::dumper& _d, const ctk::multimap<_K,_V>& _v)
    {
        CTK_DUMP(_d, "ctk::multimap");
        return output(_d, _v);
    }
} // end of namespace ctk

namespace std
{
    inline std::ostream& operator<<(std::ostream& _os, const std::ostringstream& _v)
    {
        return _os << _v.str();
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::vector<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::deque<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::queue<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::stack<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& _os, const ctk::list<T>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class K, class V>
    std::ostream& operator<<(std::ostream& _os, const ctk::map<K, V>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

    template<class K, class V>
    std::ostream& operator<<(std::ostream& _os, const ctk::multimap<K, V>& _v)
    {
        ctk::dumper d(_os);
        d << _v;
        return _os;
    }

} // end of namespace std


#endif//_Z_CTK_LOG_STL_H_

