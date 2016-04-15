/******************************************************************************
*    文件名称 :    PthreadMutex.h
*    作    者 :    w00221920
*    文件描述 :    hwuc内部线程锁 头文件
*    创建时间 :    2014-12-25
*    修订历史 :    2014-12-25    1.0.0
******************************************************************************/

#pragma once

#if defined WIN32
#define TE_MUTEX_T HANDLE
typedef void* TE_Pthread_T;
#else //not windows，for MAC
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
typedef  pthread_mutex_t *TE_MUTEX_T;
typedef  pthread_t TE_Pthread_T;
#endif

typedef void  TE_Pthread_ID;
typedef void* (*TE_PthreadFun)(void *); 


/******************************************************************************
 * 函 数 名  : TE_MutexCreate
 * 功能描述  : 创建mutex
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : TE_MUTEX_T
 * 其它说明  : 
 * 
 * 修改历史      :
 *  1.日    期   : 2014-12-25
 *    作    者   : w00221920
 *    修改内容   : 新生成函数
 ******************************************************************************/
TE_MUTEX_T TE_MutexCreate();

/******************************************************************************
 * 函 数 名  : TE_MutexFree
 * 功能描述  : 释放mutex
 * 输入参数  : mutex  
 * 输出参数  : 无
 * 返 回 值  : 无
 * 其它说明  : 
 * 
 * 修改历史      :
 *  1.日    期   : 2014-12-25
 *    作    者   : w00221920
 *    修改内容   : 新生成函数
 ******************************************************************************/
void TE_MutexFree(TE_MUTEX_T MutexHandle);

/******************************************************************************
 * 函 数 名  : TE_MutexLock
 * 功能描述  : lock mutex
 * 输入参数  : mutex  
 * 输出参数  : 无
 * 返 回 值  : 0 成功;else 错误码
 * 其它说明  : 
 * 
 * 修改历史      :
 *  1.日    期   : 2014-12-25
 *    作    者   : w00221920
 *    修改内容   : 新生成函数
 ******************************************************************************/
int TE_MutexLock(TE_MUTEX_T MutexHandle);

/******************************************************************************
 * 函 数 名  : TE_MutexUnlock
 * 功能描述  : unlock mutex
 * 输入参数  : mutex  
 * 输出参数  : 无
 * 返 回 值  : 0 成功;else 错误码
 * 其它说明  : 
 * 
 * 修改历史      :
 *  1.日    期   : 2014-12-25
 *    作    者   : w00221920
 *    修改内容   : 新生成函数
 ******************************************************************************/
int TE_MutexUnlock(TE_MUTEX_T MutexHandle);


//实现线程锁类 w00221920  2014-12-25
class CTEMutexLock
{
public:
	CTEMutexLock(TE_MUTEX_T MutexHandle)
	{
		m_MutexLockHandle = MutexHandle;
		TE_MutexLock(m_MutexLockHandle);
	}

	~CTEMutexLock()
	{
		TE_MutexUnlock(m_MutexLockHandle);
	}

private:
	TE_MUTEX_T m_MutexLockHandle;
};


/******************************************************************************
 * 函 数 名  : TE_PthreadCreate
 * 功能描述  : 创建线程
 * 输入参数  : TE_PthreadFun PthreadStartFun, void *arg  
 * 输出参数  : TE_Pthread_T *PthreaHandle
 * 返 回 值  : 0 成功;else 错误码
 * 其它说明  : 
 * 
 * 修改历史      :
 *  1.日    期   : 2014-12-26
 *    作    者   : w00221920
 *    修改内容   : 新生成函数
 ******************************************************************************/
int TE_PthreadCreate(TE_Pthread_T *PthreaHandle, TE_PthreadFun PthreadStartFun, void *arg);

/******************************************************************************
 * 函 数 名  : TE_PthreadCreate
 * 功能描述  : 创建线程
 * 输入参数  : TE_Pthread_T PthreaHandle 
 * 输出参数  : void **thread_return
 * 返 回 值  : 0 成功;else 错误码
 * 其它说明  : 
 * 
 * 修改历史      :
 *  1.日    期   : 2014-12-26
 *    作    者   : w00221920
 *    修改内容   : 新生成函数
 ******************************************************************************/
int TE_PthreadJoin(TE_Pthread_T PthreaHandle, void **thread_return);


