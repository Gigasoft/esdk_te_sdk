/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_CONSOLE_H_
#define _Z_CTK_LOG_CONSOLE_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"

#define CTK_OUT(x) do { std::ostringstream oss; oss << x; ctk::console::print(oss.str()); } while(0)
#define CTK_OUTL(x) CTK_OUT(x << std::endl)

namespace ctk
{
    class CTK_API console
    {
    public:
        CTK_STATIC_FUN void create();
        CTK_STATIC_FUN void destroy();

        CTK_STATIC_FUN void open();
        CTK_STATIC_FUN void close();

        CTK_STATIC_FUN void flush();

        CTK_STATIC_FUN void print(rcstr _msg);
        CTK_STATIC_FUN void println(rcstr _msg);
        CTK_STATIC_FUN void print(pcstr _msg, size_type _len=npos);
        CTK_STATIC_FUN void println(pcstr _msg, size_type _len=npos);

        CTK_STATIC_FUN void readline(String& _cmd, pcstr _prompt=">");

        CTK_STATIC_FUN void print(rcwstr _msg);
        CTK_STATIC_FUN void println(rcwstr _msg);
        CTK_STATIC_FUN void print(pcwstr _msg, size_type _len=npos);
        CTK_STATIC_FUN void println(pcwstr _msg, size_type _len=npos);

        CTK_STATIC_FUN void readline(Wstring& _cmd, pcwstr _prompt=L">");
    };

}

#endif//_Z_CTK_LOG_CONSOLE_H_

