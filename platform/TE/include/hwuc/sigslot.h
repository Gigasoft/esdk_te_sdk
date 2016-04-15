

#include <set>
#include <list>

#if defined WIN32
    #define _SIGSLOT_HAS_WIN32_THREADS
    #include <windows.h>
#else
    #define _SIGSLOT_HAS_POSIX_THREADS
    #include <pthread.h>
#endif

//定义线程锁
#define TE_DEFAULT_THREAD_MUTEX  te_multi_thread_mutex

namespace sigslot 
{

#define TE_IS_SIGLOT_CONNECTED(pclass)  \
    bool isconnected(has_slots<mt_policy>* pclass) \
    { \
        lock_block<mt_policy> lock(this); \
        typename te_connections_list::iterator it = m_connected_slots.begin(); \
        typename te_connections_list::iterator itEnd = m_connected_slots.end(); \
        while(it != itEnd) \
        { \
            if((*it)->getdest() == pclass) \
            { \
                return true; \
            } \
            ++it; \
        } \
        return false; \
    }\

#define TE_DISCONNECT_ALL()  \
    void disconnect_all()  \
    { \
        lock_block<mt_policy> lock(this); \
        typename te_connections_list::const_iterator it = m_connected_slots.begin(); \
        typename te_connections_list::const_iterator itEnd = m_connected_slots.end(); \
        while(it != itEnd) \
        { \
		    has_slots<mt_policy>* pDest = (*it)->getdest();    \
			if (pDest != NULL) pDest->signal_disconnect(this); \
            delete *it; \
            ++it; \
        } \
        m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end()); \
    } \

#define  TE_DISCONNECT_ONE(pclass)  \
    void disconnect(has_slots<mt_policy>* pclass) \
    { \
        lock_block<mt_policy> lock(this); \
        typename te_connections_list::iterator it = m_connected_slots.begin(); \
        typename te_connections_list::iterator itEnd = m_connected_slots.end(); \
        while(it != itEnd) \
        { \
            if((*it)->getdest() == pclass) \
            { \
                delete *it; \
                m_connected_slots.erase(it); \
                pclass->signal_disconnect(this); \
                return; \
            } \
            ++it; \
        } \
    } \

#define TE_SIGSLOT_DISCONNECT(pslot)  \
    void slot_disconnect(has_slots<mt_policy>* pslot) \
    { \
        lock_block<mt_policy> lock(this); \
        typename te_connections_list::iterator it = m_connected_slots.begin(); \
        typename te_connections_list::iterator itEnd = m_connected_slots.end(); \
        while(it != itEnd) \
        { \
            typename te_connections_list::iterator itNext = it; \
            ++itNext; \
            if((*it)->getdest() == pslot) \
            { \
                m_connected_slots.erase(it); \
            } \
            it = itNext; \
        } \
    } \

#define TE_SIGSLOT_DUPLICATE(oldtarget, newtarget) \
    void slot_duplicate(const has_slots<mt_policy>* oldtarget, has_slots<mt_policy>* newtarget) \
    { \
        lock_block<mt_policy> lock(this); \
        typename te_connections_list::iterator it = m_connected_slots.begin(); \
        typename te_connections_list::iterator itEnd = m_connected_slots.end(); \
        while(it != itEnd) \
        { \
            if((*it)->getdest() == oldtarget) \
            { \
                m_connected_slots.push_back((*it)->duplicate(newtarget)); \
            } \
            ++it; \
        } \
    } \

//定义win32情况下的线程锁
#ifdef _SIGSLOT_HAS_WIN32_THREADS

	class te_multi_thread_mutex
	{
	public:
		te_multi_thread_mutex()
		{
			InitializeCriticalSection(&m_CriticalSection);
		}

		te_multi_thread_mutex(const te_multi_thread_mutex&)
		{
			InitializeCriticalSection(&m_CriticalSection);
		}

		virtual ~te_multi_thread_mutex()
		{
			DeleteCriticalSection(&m_CriticalSection);
		}

		virtual void lock()
		{
			EnterCriticalSection(&m_CriticalSection);
		}

		virtual void unlock()
		{
			LeaveCriticalSection(&m_CriticalSection);
		}

	private:
		CRITICAL_SECTION m_CriticalSection;
	};
#endif


//定义POSIX情况下的线程锁
#ifdef _SIGSLOT_HAS_POSIX_THREADS

	class te_multi_thread_mutex
	{
	public:
		te_multi_thread_mutex()
		{
			pthread_mutex_init(&m_mutex, NULL);
		}

		te_multi_thread_mutex(const te_multi_thread_mutex&)
		{
			pthread_mutex_init(&m_mutex, NULL);
		}

		virtual ~te_multi_thread_mutex()
		{
			pthread_mutex_destroy(&m_mutex);
		}

		virtual void lock()
		{
			pthread_mutex_lock(&m_mutex);
		}

		virtual void unlock()
		{
			pthread_mutex_unlock(&m_mutex);
		}

	private:
		pthread_mutex_t m_mutex;
	};
#endif 


//添加一个slots到m_connected_slots  w00221920  2015-02-04
#define TE_SIGNAL_BASE_ADD_CONNECTED_SIGSLOT \
{ \
    lock_block<mt_policy> lock(this); \
    typename te_connections_list::const_iterator it = s.m_connected_slots.begin();  \
    typename te_connections_list::const_iterator itEnd = s.m_connected_slots.end(); \
    while(it != itEnd) \
    { \
        (*it)->getdest()->signal_connect(this); \
        m_connected_slots.push_back((*it)->clone()); \
        ++it; \
    } \
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class mt_policy>
	class lock_block
	{
	public:
		mt_policy *m_mutex;

		lock_block(mt_policy *mtx) : m_mutex(mtx)
		{
			if(m_mutex)
            {
                m_mutex->lock();
            }         
		}

		~lock_block()
		{
			if(m_mutex)
			m_mutex->unlock();
		}
	};

	template<class mt_policy>
	class has_slots;

	template<class mt_policy>
	class te_connection_base0
	{
	public:
		virtual has_slots<mt_policy>* getdest() const = 0;
		virtual void emit() = 0;
		virtual te_connection_base0* clone() = 0;
		virtual te_connection_base0* duplicate(has_slots<mt_policy>* pnewdest) = 0;
		virtual ~te_connection_base0()
		{
			;
		}
	};

	template<class arg1_type, class mt_policy>
	class te_connection_base1
	{
	public:
		virtual has_slots<mt_policy>* getdest() const = 0;
		virtual void emit(arg1_type) = 0;
		virtual te_connection_base1<arg1_type, mt_policy>* clone() = 0;
		virtual te_connection_base1<arg1_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest) = 0;
		virtual ~te_connection_base1()
		{
			;
		}
	};

	template<class arg1_type, class arg2_type, class mt_policy>
	class te_connection_base2
	{
	public:
		virtual has_slots<mt_policy>* getdest() const = 0;
		virtual void emit(arg1_type, arg2_type) = 0;
		virtual te_connection_base2<arg1_type, arg2_type, mt_policy>* clone() = 0;
		virtual te_connection_base2<arg1_type, arg2_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest) = 0;
		virtual ~te_connection_base2()
		{
			;
		}
	};

	template<class arg1_type, class arg2_type, class arg3_type, class mt_policy>
	class te_connection_base3
	{
	public:
		virtual has_slots<mt_policy>* getdest() const = 0;
		virtual void emit(arg1_type, arg2_type, arg3_type) = 0;
		virtual te_connection_base3<arg1_type, arg2_type, arg3_type, mt_policy>* clone() = 0;
		virtual te_connection_base3<arg1_type, arg2_type, arg3_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest) = 0;
		virtual ~te_connection_base3()
		{
			;
		}
	};

	template<class arg1_type, class arg2_type, class arg3_type, class arg4_type, class mt_policy>
	class te_connection_base4
	{
	public:
		virtual has_slots<mt_policy>* getdest() const = 0;
		virtual void emit(arg1_type, arg2_type, arg3_type, arg4_type) = 0;
		virtual te_connection_base4<arg1_type, arg2_type, arg3_type, arg4_type, mt_policy>* clone() = 0;
		virtual te_connection_base4<arg1_type, arg2_type, arg3_type, arg4_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest) = 0;
	};

	template<class mt_policy>
	class _signal_base : public mt_policy
	{
	public:
		virtual void slot_disconnect(has_slots<mt_policy>* pslot) = 0;
		virtual void slot_duplicate(const has_slots<mt_policy>* poldslot, has_slots<mt_policy>* pnewslot) = 0;
	};

	template<class mt_policy = TE_DEFAULT_THREAD_MUTEX>
	class has_slots : public mt_policy 
	{
	private:
		typedef std::set<_signal_base<te_multi_thread_mutex> *> sender_set;
		typedef sender_set::const_iterator const_iterator;

	public:
		has_slots()
		{
			;
		}

		has_slots(const has_slots& hs) : mt_policy(hs)
		{
			lock_block<mt_policy> lock(this);
			const_iterator it = hs.m_senders.begin();
			const_iterator itEnd = hs.m_senders.end();

			while(it != itEnd)
			{
				(*it)->slot_duplicate(&hs, this);
				m_senders.insert(*it);
				++it;
			}
		} 

		void signal_connect(_signal_base<mt_policy>* sender)
		{
			lock_block<mt_policy> lock(this);
			m_senders.insert(sender);
		}

		void signal_disconnect(_signal_base<mt_policy>* sender)
		{
			lock_block<mt_policy> lock(this);
			m_senders.erase(sender);
		}

		virtual ~has_slots()
		{
			disconnect_all();
		}

		void disconnect_all()
		{
			lock_block<mt_policy> lock(this);
			const_iterator it = m_senders.begin();
			const_iterator itEnd = m_senders.end();

			while(it != itEnd)
			{
				(*it)->slot_disconnect(this);
				++it;
			}

			m_senders.erase(m_senders.begin(), m_senders.end());
		}

	private:
		sender_set m_senders;
	};

	template<class mt_policy>
	class te_signal_base0 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<te_connection_base0<mt_policy> *> te_connections_list;

		te_signal_base0()
		{
			;
		}

		te_signal_base0(const te_signal_base0& s) : _signal_base<mt_policy>(s)
		{
            TE_SIGNAL_BASE_ADD_CONNECTED_SIGSLOT
		}

		~te_signal_base0()
		{
			disconnect_all();
		}

    TE_DISCONNECT_ALL()
    TE_DISCONNECT_ONE(pclass)   
    TE_IS_SIGLOT_CONNECTED(pclass)
    TE_SIGSLOT_DISCONNECT(pslot)
    TE_SIGSLOT_DUPLICATE(oldtarget, newtarget)

	protected:
		te_connections_list m_connected_slots;   
	};

	template<class arg1_type, class mt_policy>
	class te_signal_base1 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<te_connection_base1<arg1_type, mt_policy> *> te_connections_list;

		te_signal_base1()
		{
			;
		}

		te_signal_base1(const te_signal_base1<arg1_type, mt_policy>& s) : _signal_base<mt_policy>(s)
		{
            TE_SIGNAL_BASE_ADD_CONNECTED_SIGSLOT
		}

		~te_signal_base1()
		{
			disconnect_all();
		}

    TE_DISCONNECT_ALL()
    TE_DISCONNECT_ONE(pclass)   
    TE_IS_SIGLOT_CONNECTED(pclass)
    TE_SIGSLOT_DISCONNECT(pslot)
    TE_SIGSLOT_DUPLICATE(oldtarget, newtarget)

	protected:
		te_connections_list m_connected_slots;   
	};

	template<class arg1_type, class arg2_type, class mt_policy>
	class te_signal_base2 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<te_connection_base2<arg1_type, arg2_type, mt_policy> *> te_connections_list;

		te_signal_base2()
		{
			;
		}

		te_signal_base2(const te_signal_base2<arg1_type, arg2_type, mt_policy>& s) : _signal_base<mt_policy>(s)
		{
            TE_SIGNAL_BASE_ADD_CONNECTED_SIGSLOT
		}

		~te_signal_base2()
		{
			disconnect_all();
		}

    TE_DISCONNECT_ALL()
    TE_DISCONNECT_ONE(pclass)   
    TE_IS_SIGLOT_CONNECTED(pclass)
    TE_SIGSLOT_DISCONNECT(pslot)
    TE_SIGSLOT_DUPLICATE(oldtarget, newtarget)

	protected:
		te_connections_list m_connected_slots;   
	};

	template<class arg1_type, class arg2_type, class arg3_type, class mt_policy>
	class te_signal_base3 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<te_connection_base3<arg1_type, arg2_type, arg3_type, mt_policy> *> te_connections_list;

		te_signal_base3()
		{
			;
		}

		te_signal_base3(const te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>& s) : _signal_base<mt_policy>(s)
		{
            TE_SIGNAL_BASE_ADD_CONNECTED_SIGSLOT
		}

		~te_signal_base3()
		{
			disconnect_all();
		}

    TE_DISCONNECT_ALL()
    TE_DISCONNECT_ONE(pclass)   
    TE_IS_SIGLOT_CONNECTED(pclass)
    TE_SIGSLOT_DISCONNECT(pslot)
    TE_SIGSLOT_DUPLICATE(oldtarget, newtarget)

	protected:
		te_connections_list m_connected_slots;   
	};

	template<class arg1_type, class arg2_type, class arg3_type, class arg4_type, class mt_policy>
	class te_signal_base4 : public _signal_base<mt_policy>
	{
	public:
		typedef std::list<te_connection_base4<arg1_type, arg2_type, arg3_type, arg4_type, mt_policy> *> te_connections_list;

		te_signal_base4()
		{
			;
		}

		te_signal_base4(const te_signal_base4<arg1_type, arg2_type, arg3_type, arg4_type, mt_policy>& s) : _signal_base<mt_policy>(s)
		{
            TE_SIGNAL_BASE_ADD_CONNECTED_SIGSLOT
		}

		~te_signal_base4()
		{
			disconnect_all();
		}

    TE_DISCONNECT_ALL()
    TE_DISCONNECT_ONE(pclass)   
    TE_IS_SIGLOT_CONNECTED(pclass)
    TE_SIGSLOT_DISCONNECT(pslot)
    TE_SIGSLOT_DUPLICATE(oldtarget, newtarget)

	protected:
		te_connections_list m_connected_slots;   
	};

	template<class dest_type, class mt_policy>
	class te_connection0 : public te_connection_base0<mt_policy>
	{
	public:
		te_connection0()
		{
			m_pobject = NULL;
			m_pmemfun = NULL;
		}

		te_connection0(dest_type* pobject, void (dest_type::*pmemfun)())
		{
			m_pobject = pobject;
			m_pmemfun = pmemfun;
		}

		virtual te_connection_base0<mt_policy>* clone()
		{
			return new te_connection0<dest_type, mt_policy>(*this);
		}

		virtual te_connection_base0<mt_policy>* duplicate(has_slots<mt_policy>* pnewdest)
		{
			return new te_connection0<dest_type, mt_policy>((dest_type *)pnewdest, m_pmemfun);
		}

		virtual void emit()
		{
			(m_pobject->*m_pmemfun)();
		}

		virtual has_slots<mt_policy>* getdest() const
		{
			return m_pobject;
		}

	private:
		dest_type* m_pobject;
		void (dest_type::* m_pmemfun)();
	};

	template<class dest_type, class arg1_type, class mt_policy>
	class te_connection1 : public te_connection_base1<arg1_type, mt_policy>
	{
	public:
		te_connection1()
		{
			m_pobject = NULL;
			m_pmemfun = NULL;
		}

		te_connection1(dest_type* pobject, void (dest_type::*pmemfun)(arg1_type))
		{
			m_pobject = pobject;
			m_pmemfun = pmemfun;
		}

		virtual te_connection_base1<arg1_type, mt_policy>* clone()
		{
			return new te_connection1<dest_type, arg1_type, mt_policy>(*this);
		}

		virtual te_connection_base1<arg1_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest)
		{
			return new te_connection1<dest_type, arg1_type, mt_policy>((dest_type *)pnewdest, m_pmemfun);
		}

		virtual void emit(arg1_type a1)
		{
			(m_pobject->*m_pmemfun)(a1);
		}

		virtual has_slots<mt_policy>* getdest() const
		{
			return m_pobject;
		}

	private:
		dest_type* m_pobject;
		void (dest_type::* m_pmemfun)(arg1_type);
	};

	template<class dest_type, class arg1_type, class arg2_type, class mt_policy>
	class te_connection2 : public te_connection_base2<arg1_type, arg2_type, mt_policy>
	{
	public:
		te_connection2()
		{
			m_pobject = NULL;
			m_pmemfun = NULL;
		}

		te_connection2(dest_type* pobject, void (dest_type::*pmemfun)(arg1_type, arg2_type))
		{
			m_pobject = pobject;
			m_pmemfun = pmemfun;
		}

		virtual te_connection_base2<arg1_type, arg2_type, mt_policy>* clone()
		{
			return new te_connection2<dest_type, arg1_type, arg2_type, mt_policy>(*this);
		}

		virtual te_connection_base2<arg1_type, arg2_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest)
		{
			return new te_connection2<dest_type, arg1_type, arg2_type, mt_policy>((dest_type *)pnewdest, m_pmemfun);
		}

		virtual void emit(arg1_type a1, arg2_type a2)
		{
			(m_pobject->*m_pmemfun)(a1, a2);
		}

		virtual has_slots<mt_policy>* getdest() const
		{
			return m_pobject;
		}

	private:
		dest_type* m_pobject;
		void (dest_type::* m_pmemfun)(arg1_type, arg2_type);
	};

	template<class dest_type, class arg1_type, class arg2_type, class arg3_type, class mt_policy>
	class te_connection3 : public te_connection_base3<arg1_type, arg2_type, arg3_type, mt_policy>
	{
	public:
		te_connection3()
		{
			m_pobject = NULL;
			m_pmemfun = NULL;
		}

		te_connection3(dest_type* pobject, void (dest_type::*pmemfun)(arg1_type, arg2_type, arg3_type))
		{
			m_pobject = pobject;
			m_pmemfun = pmemfun;
		}

		virtual te_connection_base3<arg1_type, arg2_type, arg3_type, mt_policy>* clone()
		{
			return new te_connection3<dest_type, arg1_type, arg2_type, arg3_type, mt_policy>(*this);
		}

		virtual te_connection_base3<arg1_type, arg2_type, arg3_type, mt_policy>* duplicate(has_slots<mt_policy>* pnewdest)
		{
			return new te_connection3<dest_type, arg1_type, arg2_type, arg3_type, mt_policy>((dest_type *)pnewdest, m_pmemfun);
		}

		virtual void emit(arg1_type arg1, arg2_type arg2, arg3_type arg3)
		{
			(m_pobject->*m_pmemfun)(arg1, arg2, arg3);
		}

		virtual has_slots<mt_policy>* getdest() const
		{
			return m_pobject;
		}

	private:
		dest_type* m_pobject;
		void (dest_type::* m_pmemfun)(arg1_type, arg2_type, arg3_type);
	};

	template<class mt_policy = TE_DEFAULT_THREAD_MUTEX>
	class te_signal0 : public te_signal_base0<mt_policy>
	{
	public:
		te_signal0()
		{
			;
		}

		te_signal0(const te_signal0<mt_policy>& s) : te_signal_base0<mt_policy>(s)
		{
			;
		}

		template<class desttype>
			void connect(desttype* pclass, void (desttype::*pmemfun)())
		{
			lock_block<mt_policy> lock(this);
			te_connection0<desttype, mt_policy>* conn = new te_connection0<desttype, mt_policy>(pclass, pmemfun);
            te_signal_base0<mt_policy>::m_connected_slots.push_back(conn);
			pclass->signal_connect(this);
		}

		void emit()
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base0<mt_policy>::te_connections_list::const_iterator  it = te_signal_base0<mt_policy>::m_connected_slots.begin();
			typename te_signal_base0<mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base0<mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit();
                ++it;
			}
		}

		void operator()()
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base0<mt_policy>::te_connections_list::const_iterator  it = te_signal_base0<mt_policy>::m_connected_slots.begin();
			typename te_signal_base0<mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base0<mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit();
                ++it;
			}
		}
	};

	template<class arg1_type, class mt_policy = TE_DEFAULT_THREAD_MUTEX>
	class te_signal1 : public te_signal_base1<arg1_type, mt_policy>
	{
	public:
		te_signal1()
		{
			;
		}

		te_signal1(const te_signal1<arg1_type, mt_policy>& s)
			: te_signal_base1<arg1_type, mt_policy>(s)
		{
			;
		}

		template<class desttype>
			void connect(desttype* pclass, void (desttype::*pmemfun)(arg1_type))
		{
			lock_block<mt_policy> lock(this);
			te_connection1<desttype, arg1_type, mt_policy>* conn = new te_connection1<desttype, arg1_type, mt_policy>(pclass, pmemfun);
			te_signal_base1<arg1_type, mt_policy>::m_connected_slots.push_back(conn);
			pclass->signal_connect(this);
		}

		void emit(arg1_type a1)
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base1<arg1_type, mt_policy>::te_connections_list::const_iterator  it = te_signal_base1<arg1_type, mt_policy>::m_connected_slots.begin();
			typename te_signal_base1<arg1_type, mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base1<arg1_type, mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit(a1);
                ++it;
			}
		}

		void operator()(arg1_type a1)
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base1<arg1_type, mt_policy>::te_connections_list::const_iterator  it = te_signal_base1<arg1_type, mt_policy>::m_connected_slots.begin();
			typename te_signal_base1<arg1_type, mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base1<arg1_type, mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit(a1);
                ++it;
			}
		}
	};

	template<class arg1_type, class arg2_type, class mt_policy = TE_DEFAULT_THREAD_MUTEX>
	class te_signal2 : public te_signal_base2<arg1_type, arg2_type, mt_policy>
	{
	public:
		te_signal2()
		{
			;
		}

		te_signal2(const te_signal2<arg1_type, arg2_type, mt_policy>& s)
			: te_signal_base2<arg1_type, arg2_type, mt_policy>(s)
		{
			;
		}

		template<class desttype>
		void connect(desttype* pclass, void (desttype::*pmemfun)(arg1_type, arg2_type))
		{
			lock_block<mt_policy> lock(this);
			te_connection2<desttype, arg1_type, arg2_type, mt_policy>* conn = new te_connection2<desttype, arg1_type, arg2_type, mt_policy>(pclass, pmemfun);
			te_signal_base2<arg1_type, arg2_type, mt_policy>::m_connected_slots.push_back(conn);
			pclass->signal_connect(this);
		}

		void emit(arg1_type a1, arg2_type a2)
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base2<arg1_type, arg2_type, mt_policy>::te_connections_list::const_iterator  it = te_signal_base2<arg1_type, arg2_type, mt_policy>::m_connected_slots.begin();
			typename te_signal_base2<arg1_type, arg2_type, mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base2<arg1_type, arg2_type, mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit(a1, a2);
                ++it;
			}
		}

		void operator()(arg1_type a1, arg2_type a2)
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base2<arg1_type, arg2_type, mt_policy>::te_connections_list::const_iterator  it = te_signal_base2<arg1_type, arg2_type, mt_policy>::m_connected_slots.begin();
			typename te_signal_base2<arg1_type, arg2_type, mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base2<arg1_type, arg2_type, mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit(a1, a2);
                ++it;
			}
		}
	};

	template<class arg1_type, class arg2_type, class arg3_type, class mt_policy = TE_DEFAULT_THREAD_MUTEX>
	class te_signal3 : public te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>
	{
	public:
		te_signal3()
		{
			;
		}

		te_signal3(const te_signal3<arg1_type, arg2_type, arg3_type, mt_policy>& s)
			: te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>(s)
		{
			;
		}

		template<class desttype> 
        void connect(desttype* pclass, void (desttype::*pmemfun)(arg1_type, arg2_type, arg3_type))
		{
			lock_block<mt_policy> lock(this);
			te_connection3<desttype, arg1_type, arg2_type, arg3_type, mt_policy>* conn = new te_connection3<desttype, arg1_type, arg2_type, arg3_type, mt_policy>(pclass, pmemfun);
			te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::m_connected_slots.push_back(conn);
			pclass->signal_connect(this);
		}

		void emit(arg1_type a1, arg2_type a2, arg3_type a3)
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::te_connections_list::const_iterator  it = te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::m_connected_slots.begin();
			typename te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit(a1, a2, a3);
                ++it;
			}
		}

		void operator()(arg1_type a1, arg2_type a2, arg3_type a3)
		{
			lock_block<mt_policy> lock(this);
			typename te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::te_connections_list::const_iterator  it = te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::m_connected_slots.begin();
			typename te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::te_connections_list::const_iterator itEnd = te_signal_base3<arg1_type, arg2_type, arg3_type, mt_policy>::m_connected_slots.end();

			while(it != itEnd)
			{
				(*it)->emit(a1, a2, a3);
                ++it;
			}
		}
	};
};

