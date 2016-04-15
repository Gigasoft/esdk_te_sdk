/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

#ifndef _Z_CTK_CTK_H_
#define _Z_CTK_CTK_H_

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4996) // This function or variable may be unsafe.
#pragma warning(disable:4512) // assignment operator could not be generated.
#pragma warning(disable:4251) // class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4127) // conditional expression is constant
#endif

#ifdef  TE_SDK_STATIC_LIB
#ifndef _CTK_USE_STATIC_LIB
#define _CTK_USE_STATIC_LIB
#endif
#endif

#include "ctk/ctk_config.h"

#include "ctk/base.h"
#include "ctk/base/base_type_stl.h"

#include "ctk/cfg/config_file.h"
#include "ctk/log.h"
#include "ctk/log/log_stl.h"

#include "ctk/mt.h"
#include "ctk/mt/stl.h"

#include "ctk/pml.h"
#include "ctk/pml/ntv_stl.h"

#include "ctk/strings.h"

#include "ctk/util.h"
#include "ctk/util/singleton_T.h"

#include "ctk/xml/XML.h"

#ifdef WIN32
#pragma warning(pop)
#endif

#endif//_Z_CTK_CTK_H_
