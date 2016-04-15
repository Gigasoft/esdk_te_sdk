/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_USER_LOG_MACROS_H_
#define _Z_CTK_BASE_USER_LOG_MACROS_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/traceentry.h"

#define CTK_USER_LOGGER(x)      ctk::logger_factory::instance(x)

#define CTK_LOG_AND_OUTPUT(l,s) do { std::ostringstream __oss__; __oss__ << s; l.writeAndPrint(__oss__.str()); } while(0)

#define CTK_USER_LOGL2(l, x)    CTK_LOG_AND_OUTPUT(l, x << std::endl)

#define CTK_VAR(v) #v << '(' << v << ')'

// ��������ջ
#define CTK_USER_TRACE(_log_)           ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, ctk::TraceEntry::LOG_NONE)

#define CTK_USER_TRACE1(_log_, _x_)     std::ostringstream __trace_info__; if (_log_.traceOn()) __trace_info__ << _x_; \
                                        ctk::TraceEntry __trace_entry__(_log_, CTK_CURRENT, \
											 !_log_.traceOn() ? ctk::TraceEntry::LOG_NONE : ctk::TraceEntry::LOG_ALL, \
											 __trace_info__.str().c_str())

//////////////////////////////////////////////////////////////////////////////
//
//              ������־��
//
//////////////////////////////////////////////////////////////////////////////

// CTK_USER_ASSERT(_log_, cond)
// CTK_USER_ASSERT_ACT(_log_, cond, action)
// CTK_USER_ASSERT_RET(_log_, cond, val)
// CTK_USER_ENSURE(_log_, cond)
// CTK_USER_ENSURE_ACT(_log_, cond, action)
// CTK_USER_ENSURE_RET(_log_, cond, val)

///////////////////////////////////////////////////////////////////////////////

#ifdef _CTK_ASSERT_ABORT_ON
#define CTK_ASSERT__(x) assert(x)
#else
#define CTK_ASSERT__(x)
#endif

#define CTK_USER_ASSERT_FAIL__(_log_, cond, act) ctk::assertFailure(_log_, cond, CTK_CURRENT, act)
#define CTK_USER_ENSURE_FAIL__(_log_, cond, act) ctk::ensureFailure(_log_, cond, CTK_CURRENT, act)

#ifdef _CTK_ASSERT_ON

// ���԰汾������Ϊfalseʱ���˳�����(core dump)
#define CTK_USER_ASSERT(_log_, cond) do { \
            if (!(cond)) CTK_USER_ASSERT_FAIL__(_log_, #cond, ""); \
        } while(0)

// ���Բ�����ʱ�����԰��˳���������ִ��action
#define CTK_USER_ASSERT_ACT(_log_, cond, action) do { \
            if (!(cond)) CTK_USER_ASSERT_FAIL__(_log_, #cond, #action); \
            if (!(cond)) { action; } \
        } while(0)

// ���Բ�����ʱ�����԰��˳��������淵��һ��ֵ
#define CTK_USER_ASSERT_RET(_log_, cond, val) do { \
            if (!(cond)) CTK_USER_ASSERT_FAIL__(_log_, #cond, "return " #val); \
            if (!(cond)) { return(val); } \
        } while(0)

// �û����ݴ�����������Ϊfalseʱ���Լ������У�ֻ�������ʾ����
#define CTK_USER_ENSURE(_log_, cond) do { \
            if (!(cond)) CTK_USER_ENSURE_FAIL__(_log_, #cond, ""); \
        } while(0)

#define CTK_USER_ENSURE_MSG(_log_, cond, msg) do { \
            std::ostringstream oss_; oss_ << #cond << ", " << msg; \
            if (!(cond)) CTK_USER_ENSURE_FAIL__(_log_, oss_.str().c_str(), ""); \
        } while(0)

// ����Ϊfalseʱ����
#define CTK_USER_ENSURE_RET(_log_, cond, val) do { \
            if (!(cond)) CTK_USER_ENSURE_FAIL__(_log_, #cond, "return " #val); \
            if (!(cond)) { return(val); } \
        } while(0)

#else

#define CTK_USER_ASSERT(_log_, cond) do; while(0)
#define CTK_USER_ASSERT_ACT(_log_, cond, action) do { if (!(cond)) { action; } } while(0)
#define CTK_USER_ASSERT_RET(_log_, cond, val) do { if (!(cond)) { return val; } } while(0)
#define CTK_USER_ENSURE(_log_, cond) do ; while(0)
#define CTK_USER_ENSURE_MSG(_log_, cond, msg) do ; while(0)
#define CTK_USER_ENSURE_RET(_log_, cond, val) do { if (!(cond)) { return val; } } while(0)

#endif

///////////////////////////////////////////////////////////////////////////////

#define CTK_USER_INFO_LOG_X__(l, t, on, x) do { \
            if (on) { \
                std::ostringstream _oss_; _oss_ << x; \
                ctk::writeInfoLog(l, CTK_CURRENT, _oss_.str().c_str(), t); \
            } \
        } while(0)
#define CTK_USER_INFO_LOG(l, x)         CTK_USER_INFO_LOG_X__(l, ctk::log::TYPE_INFO,   l.infoOn(),   x)

#define CTK_USER_NOTICE_LOG(l, x)       CTK_USER_INFO_LOG_X__(l, ctk::log::TYPE_NOTICE, true,         x)

///////////////////////////////////////////////////////////////////////////////

#define CTK_USER_ERROR_LOG_X(_log_, type, x) do { \
            std::ostringstream oss_info; oss_info << x; \
            ctk::writeErrorLog(_log_, CTK_CURRENT, oss_info.str().c_str(), type); \
        } while(0)
#define CTK_USER_WARN_LOG(_log_, x)     CTK_USER_ERROR_LOG_X(_log_, ctk::log::TYPE_WARN, x)
#define CTK_USER_ERROR_LOG(_log_, x)    CTK_USER_ERROR_LOG_X(_log_, ctk::log::TYPE_ERROR, x)
#define CTK_USER_FATAL_LOG(_log_, x)    CTK_USER_ERROR_LOG_X(_log_, ctk::log::TYPE_FATAL, x)

///////////////////////////////////////////////////////////////////////////////

#define CTK_USER_EXCPT_LOG(_log_, ex) do { \
            std::ostringstream oss_info; oss_info << ex; \
            ctk::writeExcptLog(_log_, CTK_CURRENT, oss_info.str().c_str()); \
        } while(0)

///////////////////////////////////////////////////////////////////////////////

#define CTK_THROW_ANYWAY(ex) throw ex(CTK_CURRENT, #ex)

#define CTK_RETHROW throw
#ifdef _DEBUG
#define CTK_RETHROW_AT_DEBUG throw
#else
#define CTK_RETHROW_AT_DEBUG
#endif

#if defined(_CTK_THROW_REALLY) && _CTK_THROW_REALLY
#define CTK_USER_THROW__(_log_, ex, msg) do { \
            ctk::String __s__; __s__ << #ex << ": " << msg; \
            ctk::exceptionThrown(_log_, CTK_CURRENT, __s__.c_str()); \
            throw ex(CTK_CURRENT, __s__.c_str()); \
        } while(0)

#define CTK_USER_THROW_MSG(_log_, ex, msg)              CTK_USER_THROW__(_log_, ex, msg)
#define CTK_USER_THROW_MSG_RET(_log_, ex, msg, ret)     CTK_USER_THROW_MSG(_log_, ex, msg)
#else
#define CTK_USER_THROW_ACT__(_log_, ex, msg, act) do { \
            CTK_USER_INFO_LOG(_log_, "Following exception will be thrown in real world."); \
            ctk::String __s__; __s__ << #ex << ": " << msg; \
            ctk::exceptionThrown(_log_, CTK_CURRENT, __s__.c_str()); \
            act; \
        } while(0)
#define CTK_USER_THROW_MSG(_log_, ex, msg)              CTK_USER_THROW_ACT__(_log_, ex, msg, )
#define CTK_USER_THROW_MSG_RET(_log_, ex, msg, ret)     CTK_USER_THROW_ACT__(_log_, ex, msg, return ret)
#endif
#define CTK_USER_THROW(_log_, ex)                       CTK_USER_THROW_MSG(_log_, ex, #ex)
#define CTK_USER_THROW_RET(_log_, ex, ret)              CTK_USER_THROW_MSG_RET(_log_, ex, #ex, ret)

#define CTK_USER_ASSERT_THROW_MSG(_log_, cond, ex, msg) CTK_USER_ASSERT_ACT(_log_, cond, CTK_USER_THROW_MSG(_log_, ex, msg))
#define CTK_USER_ASSERT_THROW(_log_, cond, ex)          CTK_USER_ASSERT_THROW_MSG(_log_, cond, ex, #ex)
#define CTK_USER_ASSERT_NOTNULL(_log_, ptr)             CTK_USER_ASSERT_THROW(_log_, ptr!=0, ctk::NullPointerException)

namespace ctk
{
    namespace log {
        
        const pcstr TYPE_INFO = "INFO";
        const pcstr TYPE_NOTICE = "NOTICE";

        const pcstr TYPE_WARN = "<WARNING>";
        const pcstr TYPE_ERROR = "<ERROR>";
        const pcstr TYPE_FATAL = "<FATALERROR>";

    }
}

#endif // _Z_CTK_BASE_USER_LOG_MACROS_H_
