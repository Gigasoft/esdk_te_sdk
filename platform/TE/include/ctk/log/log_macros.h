/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_BASE_MACROS_H_
#define _Z_CTK_LOG_BASE_MACROS_H_

#include "ctk/ctk_config.h"

#define CTK_DUMP_MAX_SIZE ctk::size_type(256)

// 用于辅助日志记载

#define CTK_DUMP(_os_, _type_) \
            std::ostringstream __oss__; \
            __oss__ << _type_; \
            ctk::dumper::_Entry __dump_entry__(_os_, __oss__.str())

#define DUMP_ONE(_os_, _name_, _var_, _sep_) \
            do { \
                _os_ << ctk::indent; \
                _os_ << ctk::namestring(_name_, _sep_); \
                _os_ << _var_;\
                _os_ << ctk::endline;\
            } while (0)

#define DUMP_VAL(_os_, _val_) \
            do { \
                _os_ << ctk::indent; \
                _os_ << _val_;\
                _os_ << ctk::endline;\
            } while (0)


#define DUMP_VAR(_os_, _var_)            DUMP_ONE(_os_, #_var_, _var_, 0)

#define DUMP_NVL(_os_, _name_, _val_)    DUMP_ONE(_os_, #_name_, _val_, 0)

#define DUMP_BUF(_os_, _var_, _maxsize_) DUMP_ONE(_os_, #_var_, ctk::istr(_var_, _maxsize_), 0)

#define DUMP_PTR(_os_, _ptr_) do { if (_ptr_) DUMP_NVL(_os_, _ptr_, *_ptr_); else DUMP_NVL(_os_, _ptr_, ctk::rawstring("null")); } while(0)

//////////////////////////////////////////////////////////////////////////////

#define CTK_COMPILE_TIME __DATE__ " " __TIME__

#define COUTL(x)    CTK_OUT(x<<std::endl)

#define OSOUT(os, x)    do { os << x; } while(0)
#define OSOUTL(os, x)   OSOUT(os, x << std::endl)

#ifndef CTK_MAX_DEBUG_LINE_LEN
#define CTK_MAX_DEBUG_LINE_LEN 118
#endif

namespace ctk {

    typedef ctk::dumper& (*__dumper_fn)(ctk::dumper&);
    inline ctk::dumper& operator<<(ctk::dumper& _os, __dumper_fn _fn)
    {
        return _fn(_os);
    }

    CTK_API ctk::dumper& indent(ctk::dumper& _os);
    CTK_API ctk::dumper& endline(ctk::dumper& _os);
    CTK_API ctk::dumper& nl(ctk::dumper& _os);

}

#endif//_Z_CTK_LOG_BASE_MACROS_H_

