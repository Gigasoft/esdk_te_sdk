/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_VERSION_STR_H_
#define _Z_CTK_VERSION_STR_H_

#include "ctk/ctk_version.h"

#define CTK_VERSION_MINI_PATCH  00
#define CTK_VERSION_DATE_TIME   "20111201"

#define CTK_MINI_PATCH_STR     _CTK_STRINGIZE(CTK_VERSION_MINI_PATCH)"["CTK_VERSION_DATE_TIME"]"

#ifdef _DEBUG
#define CTK_DEBUG_STR           "(debug) "
#else
#define CTK_DEBUG_STR           ""
#endif

#define CTK_VERSION_STR        CTK_DEBUG_STR""_CTK_LIB_VERSION_STR"-"CTK_MINI_PATCH_STR 

#define CTK_COPYRIGHT           "CTK(Common Tool Kit) version " CTK_VERSION_STR "\n" \
                                "Author: luyunhai 117629(3664)/huawei\n" \
                                "Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.\n" \
                                "All rights reserved."

#define CTK_FULL_VERSION        CTK_MERGE(CTK_VERSION, CTK_VERSION_MINI_PATCH)

#define CTK_FULL_NAMESPACE(x)   CTK_MERGE(x##_, CTK_FULL_VERSION)

namespace CTK_FULL_NAMESPACE(ctk)
{
}

#endif //_Z_CTK_VERSION_STR_H_

