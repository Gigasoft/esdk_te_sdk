/******************************************************************************
*    �ļ����� :    PthreadMutex.h
*    ��    �� :    w00221920
*    �ļ����� :    hwuc�ڲ��߳��� ͷ�ļ�
*    ����ʱ�� :    2014-12-25
*    �޶���ʷ :    2014-12-25    1.0.0
******************************************************************************/

#pragma once

#if defined WIN32
#define TE_MUTEX_T HANDLE
typedef void* TE_Pthread_T;
#else //not windows��for MAC
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
 * �� �� ��  : TE_MutexCreate
 * ��������  : ����mutex
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : TE_MUTEX_T
 * ����˵��  : 
 * 
 * �޸���ʷ      :
 *  1.��    ��   : 2014-12-25
 *    ��    ��   : w00221920
 *    �޸�����   : �����ɺ���
 ******************************************************************************/
TE_MUTEX_T TE_MutexCreate();

/******************************************************************************
 * �� �� ��  : TE_MutexFree
 * ��������  : �ͷ�mutex
 * �������  : mutex  
 * �������  : ��
 * �� �� ֵ  : ��
 * ����˵��  : 
 * 
 * �޸���ʷ      :
 *  1.��    ��   : 2014-12-25
 *    ��    ��   : w00221920
 *    �޸�����   : �����ɺ���
 ******************************************************************************/
void TE_MutexFree(TE_MUTEX_T MutexHandle);

/******************************************************************************
 * �� �� ��  : TE_MutexLock
 * ��������  : lock mutex
 * �������  : mutex  
 * �������  : ��
 * �� �� ֵ  : 0 �ɹ�;else ������
 * ����˵��  : 
 * 
 * �޸���ʷ      :
 *  1.��    ��   : 2014-12-25
 *    ��    ��   : w00221920
 *    �޸�����   : �����ɺ���
 ******************************************************************************/
int TE_MutexLock(TE_MUTEX_T MutexHandle);

/******************************************************************************
 * �� �� ��  : TE_MutexUnlock
 * ��������  : unlock mutex
 * �������  : mutex  
 * �������  : ��
 * �� �� ֵ  : 0 �ɹ�;else ������
 * ����˵��  : 
 * 
 * �޸���ʷ      :
 *  1.��    ��   : 2014-12-25
 *    ��    ��   : w00221920
 *    �޸�����   : �����ɺ���
 ******************************************************************************/
int TE_MutexUnlock(TE_MUTEX_T MutexHandle);


//ʵ���߳����� w00221920  2014-12-25
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
 * �� �� ��  : TE_PthreadCreate
 * ��������  : �����߳�
 * �������  : TE_PthreadFun PthreadStartFun, void *arg  
 * �������  : TE_Pthread_T *PthreaHandle
 * �� �� ֵ  : 0 �ɹ�;else ������
 * ����˵��  : 
 * 
 * �޸���ʷ      :
 *  1.��    ��   : 2014-12-26
 *    ��    ��   : w00221920
 *    �޸�����   : �����ɺ���
 ******************************************************************************/
int TE_PthreadCreate(TE_Pthread_T *PthreaHandle, TE_PthreadFun PthreadStartFun, void *arg);

/******************************************************************************
 * �� �� ��  : TE_PthreadCreate
 * ��������  : �����߳�
 * �������  : TE_Pthread_T PthreaHandle 
 * �������  : void **thread_return
 * �� �� ֵ  : 0 �ɹ�;else ������
 * ����˵��  : 
 * 
 * �޸���ʷ      :
 *  1.��    ��   : 2014-12-26
 *    ��    ��   : w00221920
 *    �޸�����   : �����ɺ���
 ******************************************************************************/
int TE_PthreadJoin(TE_Pthread_T PthreaHandle, void **thread_return);


