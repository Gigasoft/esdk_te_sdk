/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_MLCHECK_H_
#define _Z_CTK_MLCHECK_H_
// Mem Leak Check

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_current.h"
#include "ctk/base/assert.h"

//#define CTK_MLC_DEFAULT_NO_CHECK

#define CTK_MLCHECKER() (*ctk::MemLeakChecker::instance())

#define CTK_DELETE_MLC(p)   ctk::destroy(p, CTK_CURRENT)

#ifndef CDECL
#ifdef WIN32
#define CDECL __cdecl
#else
#define CDECL
#endif
#endif

CTK_API void * CDECL operator new(size_t _size, CTK_CURRENT_ARGS);
CTK_API void   CDECL operator delete(void* _p,  CTK_CURRENT_ARGS);
inline void * CDECL operator new[](size_t _size, CTK_CURRENT_ARGS)
{ return ::operator new(_size, CTK_CURRENT_VARS); }
inline void   CDECL operator delete[](void* _p,  CTK_CURRENT_ARGS)
{ ::operator delete(_p, CTK_CURRENT_VARS); }

#define ctk_return_new0(T, CTK_CURRENT_VARS) \
                T* allocatedMemory = new(CTK_CURRENT_VARS) T; \
                /*CTK_ASSERT_CURR(allocatedMemory != 0, CTK_CURRENT_VARS);*/ \
                return allocatedMemory
#define ctk_return_new(T, args, CTK_CURRENT_VARS) \
                T* allocatedMemory = new(CTK_CURRENT_VARS) T args; \
                /*CTK_ASSERT_CURR(allocatedMemory != 0, CTK_CURRENT_VARS);*/ \
                return allocatedMemory

namespace ctk
{
    class CTK_API Mutex;

    class CTK_API MemLeakChecker
    {
    public:
        typedef MemLeakChecker _Self;

        typedef void* _Key;
        typedef Current _Value;
        typedef std::map<_Key, _Value> _Ptrs;

        typedef Mutex _Mutex;

    public:
        CTK_STATIC_FUN MemLeakChecker*& instance();
        CTK_STATIC_FUN void destroy();

        void push(void* _p, CTK_CURRENT_ARGS);
        bool pop(void* _p, CTK_CURRENT_ARGS_DEFAULT);

        std::ostream& dump(std::ostream& _os) const;
        ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        MemLeakChecker();
        ~MemLeakChecker();

        CTK_STATIC_FUN _Mutex& mtxInstance();

        void start();
        void stop();

        void dumpOn();
        void dumpOff();

    private:
        _Ptrs ptrs_;
        bool inUsing_;
        bool dumping_;
    };
    inline std::ostream& operator<<(std::ostream& _os, const MemLeakChecker& _v)
    {
        return _v.dump(_os);
    }

    template<class T>
    T* allocate_push_maybe(T* _p, CTK_CURRENT_ARGS)
    {
#ifndef CTK_MLC_DEFAULT_NO_CHECK
        if (_p) CTK_MLCHECKER().push(_p, CTK_CURRENT_VARS);
#endif
        return _p;
    }

    template<class T>
    void destroy_pop_maybe(T* _p, CTK_CURRENT_ARGS_DEFAULT)
    {
#ifndef CTK_MLC_DEFAULT_NO_CHECK
        if (_p) CTK_MLCHECKER().pop(_p, CTK_CURRENT_VARS);
#endif
    }

    template<class T>
    void destroy_pop(T* _p, CTK_CURRENT_ARGS_DEFAULT)
    {
        if (_p) CTK_MLCHECKER().pop(_p, CTK_CURRENT_VARS);
    }

    template<class T>
    T* allocate_no_mlc(CTK_CURRENT_ARGS)
    {
        ctk_return_new0(T, CTK_CURRENT_VARS);
    }

    template<class T, class _P1>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1)
    {
        ctk_return_new(T, (_p1), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2)
    {
        ctk_return_new(T, (_p1, _p2), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3)
    {
        ctk_return_new(T, (_p1, _p2, _p3), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4)
    {
        ctk_return_new(T, (_p1, _p2, _p3, _p4), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5)
    {
        ctk_return_new(T, (_p1, _p2, _p3, _p4, _p5), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6)
    {
        ctk_return_new(T, (_p1, _p2, _p3, _p4, _p5, _p6), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6, class _P7>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6, const _P7& _p7)
    {
        ctk_return_new(T, (_p1, _p2, _p3, _p4, _p5, _p6, _p7), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6, class _P7, class _P8>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6, const _P7& _p7, const _P8& _p8)
    {
        ctk_return_new(T, (_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6, class _P7, class _P8, class _P9>
    T* allocate_no_mlc(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6, const _P7& _p7, const _P8& _p8, const _P9& _p9)
    {
        ctk_return_new(T, (_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9), CTK_CURRENT_VARS);
    }

    template<class T>
    T* allocate_a_no_mlc(CTK_CURRENT_ARGS, size_type _sz)
    {
        ctk_return_new(T, [_sz], CTK_CURRENT_VARS);
    }

    template<class T>
    void destroy_no_mlc(T*& _p, CTK_CURRENT_ARGS_DEFAULT)
    {
        CTK_DELETE(_p);
    }

    template<class T>
    void destroy_a_no_mlc(T*& _p, CTK_CURRENT_ARGS_DEFAULT)
    {
        CTK_DELETE_A(_p);
    }

    template<class T>
    T* allocate(CTK_CURRENT_ARGS)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS), CTK_CURRENT_VARS);
    }

    template<class T, class _P1>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2, _p3), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2, _p3, _p4), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2, _p3, _p4, _p5), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2, _p3, _p4, _p5, _p6), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6, class _P7>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6, const _P7& _p7)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2, _p3, _p4, _p5, _p6, _p7), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6, class _P7, class _P8>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6, const _P7& _p7, const _P8& _p8)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8), CTK_CURRENT_VARS);
    }

    template<class T, class _P1, class _P2, class _P3, class _P4, class _P5, class _P6, class _P7, class _P8, class _P9>
    T* allocate(CTK_CURRENT_ARGS, const _P1& _p1, const _P2& _p2, const _P3& _p3, const _P4& _p4, const _P5& _p5, const _P6& _p6, const _P7& _p7, const _P8& _p8, const _P9& _p9)
    {
        return allocate_push_maybe(allocate_no_mlc<T>(CTK_CURRENT_VARS, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9), CTK_CURRENT_VARS);
    }

    template<class T>
    T* allocate_a(CTK_CURRENT_ARGS, size_type _sz)
    {
        return allocate_push_maybe(allocate_a_no_mlc<T>(CTK_CURRENT_VARS, _sz), CTK_CURRENT_VARS);
    }

    template<class T>
    void destroy(T*& _p, CTK_CURRENT_ARGS_DEFAULT)
    {
        destroy_pop_maybe(_p, CTK_CURRENT_VARS);
        destroy_no_mlc(_p, CTK_CURRENT_VARS);
    }

    template<class T>
    void destroy_a(T*& _p, CTK_CURRENT_ARGS_DEFAULT)
    {
        destroy_pop_maybe(_p, CTK_CURRENT_VARS);
        destroy_a_no_mlc(_p, CTK_CURRENT_VARS);
    }
} // namespace ctk

#endif //_Z_CTK_MLCHECK_H_

