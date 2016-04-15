/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_FUNC_H_
#define _Z_CTK_BASE_FUNC_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include <typeinfo>

namespace ctk
{
    template <typename _T1, typename _T2>
    inline _T1
    Min(_T1 v1, _T2 v2)
    {
        return v1 < v2 ? v1 : (_T1)v2; 
    }

    template <typename _T1, typename _T2>
    inline _T1
    Max(_T1 v1, _T2 v2)
    {
        return v1 > v2 ? v1 : (_T1)v2; 
    }

    CTK_API pcstr SafeStr(pcstr v);
    
    CTK_API pcustr SafeStr(pcustr v);

} // namespace ctk

#endif //_Z_CTK_BASE_FUNC_H_

