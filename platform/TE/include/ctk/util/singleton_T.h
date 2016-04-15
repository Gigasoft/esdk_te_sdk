/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_SINGLETON_T_H_
#define _Z_CTK_SINGLETON_T_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_system.h"
#include "ctk/base/mlcheck.h"

#include "ctk/mt/mutex.h"

namespace ctk
{
    template<class T>
        class Singleton_T
        {
        public:
            typedef Mutex _Mutex;

            CTK_STATIC_FUN T*& instance(CTK_CURRENT_ARGS)
            {
                if (!ptr())
                {
                    _Mutex::Lock __lck(mtx());
                    if (!ptr())
                    {
                        ptr() = ctk::allocate<T>(CTK_CURRENT_VARS);
                    }
                }
                return ptr();
            }

            CTK_STATIC_FUN void destroy()
            {
                _Mutex::Lock __lck(mtx());
                CTK_DELETE_MLC(ptr());
            }

        private:
            CTK_STATIC_FUN _Mutex& mtx()
            {
                CTK_STATIC_VAR _Mutex g__mtx;
                return g__mtx;
            }

            CTK_STATIC_FUN T*& ptr()
            {
                CTK_STATIC_VAR T* g__inst = 0;
                return g__inst;
            }

        private:
            Singleton_T();
            Singleton_T(const Singleton_T&);
            Singleton_T& operator=(const Singleton_T&);
        };

} // end of namespace ctk

#endif //_Z_CTK_SINGLETON_T_H_

