/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Parenthesis Markup Language

#ifndef _Z_PML_PML_STREAM_H_
#define _Z_PML_PML_STREAM_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv_unit.h"

#define PML_IO_NV(io, n, v) io  | ctk::pml::name_value(n , v)

#define PML_IO_ONE(io, field) PML_IO_NV(io, #field, field##_)


namespace ctk {
namespace pml {

    struct from_file { };

    struct name_id
    {
        virtual const pcstr str() const = 0; 

        operator istr() const { return str(); }
    };

    class CTK_API stream
    {
        enum eDir
        {
            eiOutput = 0,
            eiInput = 1,
            eiUndefined = -1
        };

    public:
        stream();
        stream(const ntv::Unit& _u);
        stream(rcistr _pml_str, bool _isList=false);
        stream(rciwstr _pml_str, bool _isList=false);
        stream(rcistr _pml_file, from_file _dummy, bool _isList=false);

        void from(rcistr _pml_str, bool _isList=false);
        void from(rciwstr _pml_str, bool _isList=false);
        void from(rcistr _pml_file, from_file _dummy, bool _isList=false);
        void combine(const stream& _from);

        void setAsInputStream() const;
        void setAsOutputStream(bool _allNesessary=false) const;

        bool isOutputStream() const { return direction_==eiOutput; }
        bool isInputStream() const { return direction_==eiInput; }

        String str(ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL) const;
        void toString(String& _s, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL) const;

        String toPml(bool _formatted=false) const;

        bool has(rcistr _name) const;
        bool isEmptyChild(rcistr _name) const;

        stream& name(rcistr _name) { unit_.name(_name); return *this; }
        stream& type(rcistr _type) { unit_.type(_type); return *this; }
        stream& value(rcistr _type) { unit_.setValue(_type); return *this; }
        rcstr name() const { return unit_.name(); }
        rcstr type() const { return unit_.type(); }

        stream& clear() { unit_.clear(); return *this; }

        ntv::Unit& unit();
        const ntv::Unit& unit() const;

        ntv::Unit& operator[](rcistr _name);
        const ntv::Unit& operator[](rcistr _name) const;

        ntv::Unit& operator[](const name_id& _name);
        const ntv::Unit& operator[](const name_id& _name) const;

        template<class T>
        void read(rcistr _name, T& _value, const T& _default)
        {
            if (has(_name))
                (*this)[_name] >> _value;
            else
                _value = _default;
        }

        template<class T>
        void write(rcistr _name, const T& _value)
        {
            (*this)[_name] << _value;
        }

        template<class T>
        void codec(rcistr _name, T& _value, bool _shouldEncode = true)
        {
            if (direction_ == eiInput)
            {
                (*this)[_name] >> _value;
            }
            else if (direction_ == eiOutput)
            {
                if (allNesessary_ || _shouldEncode)
                {
                    (*this)[_name].allNesessary(allNesessary()) << _value;
                }
            }
            else
            {
            }
        }

        bool allNesessary() const
        {
            return allNesessary_;
        }

        void allNesessary(bool _v)
        {
            allNesessary_ = _v;
        }

        ctk::dumper& dump(ctk::dumper& _d) const;

    private:
        ntv::Unit unit_;
        mutable eDir direction_;
        mutable Boolean allNesessary_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const stream& _v);
    CTK_API ctk::String& operator<<(ctk::String& _os, const stream& _v);
    CTK_API ntv::Unit& operator<<(ntv::Unit& _os, const stream& _v);
    CTK_API const ntv::Unit& operator>>(const ntv::Unit& _is, stream& _v);

    template<class T>
    struct Field__
    {
        istr name_;
        istr type_;
        T& val_;

        Field__(rcistr _name, T& _val)
            : name_(_name), val_(_val)
        {
        }

        Field__(rcistr _name, const T& _val)
            : name_(_name), val_(const_cast<T&>(_val))
        {
        }

        Field__(rcistr _name, rcistr _type, T& _val)
            : name_(_name), type_(_type), val_(_val)
        {
        }

        Field__(rcistr _name, rcistr _type, const T& _val)
            : name_(_name), type_(_type), val_(const_cast<T&>(_val))
        {
        }

        pml::stream& set(pml::stream& _os) const
        {
            ctk::pml::ntv::Unit* p = ctk::allocate<ctk::pml::ntv::Unit>(CTK_CURRENT);
            (*p) << val_;
            if (!type_.empty()) p->type(type_);
            p->name(name_);
            _os.unit().addChild(p);
            return _os;
        }

        bool get(const pml::stream& _is)
        {
            const ntv::Unit* pU = _is.unit().at(name_);
            if (pU)
            {
                (*pU) >> val_;
                return true;
            }
            return false;
        }

    };

    template<class T> inline Field__<T>
        name_value(rcistr _name, const T& _val)
    {
        return Field__<T>(_name, _val);
    }
    template<class T> inline Field__<T>
        name_value(rcistr _name, T& _val)
    {
        return Field__<T>(_name, _val);
    }

    template<class T> inline stream&
        operator<<(stream& _os, Field__<T> _field)
    {
        return _field.set(_os);
    }
    template<class T> inline bool
        operator>>(const stream& _is, Field__<T> _field)
    {
        return _field.get(_is);
    }

    template<class T> inline stream&
        operator|(stream& _os, Field__<T> _field)
    {
        if (_os.isInputStream())
            _os >> _field;
        else
            _os << _field;
        return _os;
    }

    template<class T> inline void 
        operator<<(stream& _mps, const T& _v)
    {
        _mps.unit().allNesessary(_mps.allNesessary()) << _v;
    }

    template<class T> inline void 
        operator>>(const stream& _mps, T& _v)
    {
        _mps.unit() >> _v;
    }

    template<class T> inline void 
        operator+=(stream& _mps, const T& _v)
    {
        _mps.unit() += _v;
    }

} // end of namespace pml
} // end of namespace ctk

#endif // !defined(_Z_PML_PML_STREAM_H_)

