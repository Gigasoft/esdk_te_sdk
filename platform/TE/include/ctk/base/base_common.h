/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_COMMON_H_
#define _Z_CTK_BASE_COMMON_H_

#include "ctk/ctk_config.h"

#include <utility>

namespace ctk
{

    class CTK_API dumper;

    using std::swap;

    template<class T>
    struct MemberTypeBase
    {
        typedef T type;
    };
    template<class T>
    struct MemberType : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<T&> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<const T> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<const T&> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<volatile T> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<volatile T&> : public MemberTypeBase<T>
    {
    };

} // namespace ctk

#endif //_Z_CTK_BASE_COMMON_H_

