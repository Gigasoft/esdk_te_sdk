/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_MACROS_H_
#define _Z_CTK_LOG_MACROS_H_

#include "ctk/ctk_config.h"

#include "ctk/log/log_factory.h"

#include "ctk/base/user_log_macros.h"

// define self logger
#define CTK_LOGGER()                    CTK_USER_LOGGER(ctk::LOGGER_ID)

//////////////////////////////////////////////////////////////////////////////


// should #include "ctk/log/log_tracer.h" before use these macros
#define CTK_TRACE()                     CTK_USER_TRACE(CTK_LOGGER())
#define CTK_TRACE1(info)                CTK_USER_TRACE1(CTK_LOGGER(), info)

//////////////////////////////////////////////////////////////////////////////

// 断言日志
// should #include "ctk/base/assert.h" before use following macros
#define CTK_ASSERT(cond)                CTK_USER_ASSERT(CTK_LOGGER(), cond)
#define CTK_ASSERT_ACT(cond, action)    CTK_USER_ASSERT_ACT(CTK_LOGGER(), cond, action)
#define CTK_ASSERT_RET(cond, val)       CTK_USER_ASSERT_RET(CTK_LOGGER(), cond, val)
#define CTK_ENSURE(cond)                CTK_USER_ENSURE(CTK_LOGGER(), cond)
#define CTK_ENSURE_MSG(cond, msg)       CTK_USER_ENSURE_MSG(CTK_LOGGER(), cond, msg)
#define CTK_ENSURE_RET(cond, val)       CTK_USER_ENSURE_RET(CTK_LOGGER(), cond, val)

//////////////////////////////////////////////////////////////////////////////

// should #include "ctk/log/log_debug.h" before use these macros

// 信息日志
#define CTK_INFO_LOG(x)                 CTK_USER_INFO_LOG(CTK_LOGGER(), x)
#define CTK_NOTICE_LOG(x)               CTK_USER_NOTICE_LOG(CTK_LOGGER(), x)

// 错误日志
#define CTK_WARN_LOG(x)                 CTK_USER_WARN_LOG(CTK_LOGGER(), x)
#define CTK_ERROR_LOG(x)                CTK_USER_ERROR_LOG(CTK_LOGGER(), x)
#define CTK_EXCPT_LOG(ex)               CTK_USER_EXCPT_LOG(CTK_LOGGER(), ex)

// 异常日志
#define CTK_THROW_MSG_RET(ex, msg, ret)     CTK_USER_THROW_MSG_RET(CTK_LOGGER(), ex, msg, ret)
#define CTK_THROW(ex)                       CTK_USER_THROW(CTK_LOGGER(), ex)
#define CTK_THROW_RET(ex, ret)              CTK_USER_THROW_RET(CTK_LOGGER(), ex, ret)

#define CTK_ASSERT_NOTNULL(ptr)         CTK_USER_ASSERT_NOTNULL(CTK_LOGGER(), ptr)

namespace ctk
{
    // default log filename will be $(CWD)/log/$(LOGGER_ID).default.log
    const std::string LOGGER_ID("CTK");
}

#endif//_Z_CTK_LOG_MACROS_H_

