/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_THREAD_UTIL_H_
#define _Z_CTK_THREAD_UTIL_H_

#include "ctk/ctk_config.h"

namespace ctk
{
    template<class T>
    inline
    bool
    stopThread(ctk::Handle<T>& _thr, ctk::Time _waitTime)
    {
        bool stopped = true;
        ctk::Handle<T> tmp = _thr;
        if (tmp)
        {
            stopped = tmp->stop(_waitTime);
            tmp = 0;
        }
        _thr = 0;
        return stopped;
    }

    template<class T>
    inline
    bool
    stopThread(ctk::Handle<T>& _thr)
    {
        bool stopped = true;
        ctk::Handle<T> tmp = _thr;
        if (tmp)
        {
            tmp->stop();
            tmp = 0;
        }
        _thr = 0;
        return stopped;
    }
} // end of namespace ctk

#endif //_Z_CTK_THREAD_UTIL_H_

