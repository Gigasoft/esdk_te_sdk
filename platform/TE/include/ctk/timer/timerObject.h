/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2006-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TIMER_OBJECT_H_
#define _Z_CTK_TIMER_OBJECT_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_time.h"

namespace ctk {

    struct CTK_API OnTimerResult
    {
        ctk::Time interval_;
        ctk::uint32 times_;

        OnTimerResult(ctk::Time _interval=ctk::Time(), ctk::uint32 _times=1)
            : interval_(_interval), times_(_times)
        {
        }
    };
} // end of namespace ctk

#endif // _Z_CTK_TIMER_OBJECT_H_

