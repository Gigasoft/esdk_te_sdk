/******************************************************************************
*    �ļ����� :    login.h
*    ��    �� :    h00191107
*    �ļ����� :    ��½ ͷ�ļ�
*    ����ʱ�� :    2014-12-25
*    �޶���ʷ :    2014-12-25    1.0.0
******************************************************************************/

#pragma once
#ifdef __APPLE__
#include <SystemConfiguration/SystemConfiguration.h>
#endif

namespace ecs
{
	namespace framework
	{
		struct MsgItem;
	}
}

typedef unsigned int Uint32;

namespace uc {
	namespace model {
		namespace login {

	//����仯��⴦��
	class NetStateMonitor : public ctk::ThreadOwner
	{
	public:
	NetStateMonitor();
	~NetStateMonitor();

	bool start();
	void stop();

	bool onThreadBirth();
	void onThreadWork();
	void onThreadStop();
	void onThreadDeath();

	void setLoacalIp(const std::string& _local)
	{
		if (!_local.empty())
		{
			localIp_ = _local;
		}
	}

	bool isThreadStarted() const
	{
		return NULL != netMonthread_.get();
	}

	virtual void onThreadExit(ctk::Thread* /*_thr*/) {}

protected:
	void onIPAddrChange();

private:
	typedef ctk::OwnedThread<NetStateMonitor> _Thread;
	typedef ctk::Handle<_Thread> _ThreadPtr;
	_ThreadPtr netMonthread_;

	std::string localIp_;

#ifdef WIN32
	HANDLE  hAddrMon_;
	OVERLAPPED  overlapped_;
#endif
        
#ifdef __APPLE__
    SCDynamicStoreRef  systemDynamicStore_;
    CFRunLoopSourceRef storeRLSource_;
public:
    void onMacIPChanged();
#endif
};

            
class APPCLASSLAYER_API CLogin : ctk::noncopyable
{
public:
	CLogin(uc::model::UCClient *client);
	virtual ~CLogin();

private:
	uc::model::UCClient* client_;
	NetStateMonitor monitor_;    /*!< ������ģ��*/
	bool bCancelLogin_;  /*!< ������ȡ����¼*/

	PasswordWrapper mAccount;// ���ܵ��û��� 
	PasswordWrapper mPassWord;//  ���ܵ�����
    bool GetSystemConfigFromIniFile() const;
    void initUserProfile() const;
    void ConvertAccount(const ctk::String &srcAccount, ctk::String &dstAccount) const;

	void supportH264HP(std::string server);
	bool supportSessionTimerConfig(std::string server);

	bool startRegister( std::string userName, std::string strPassword );

public:
	bool login();
    bool logout(bool bCancelLogin);

    bool changeRegisterPassword(const ctk::String &oldPassword,
                                const ctk::String &newPassword,
                                const ctk::String &server);

	void sipRegisterResult(void *pBody, ecs::framework::MsgItem& item);
    void authorizeFailed(ecs::framework::MsgItem& item);
	void getLicenseTypeResult(Uint32  ulParam1, Uint32 ulParam2, ecs::framework::MsgItem& item);
	void applyLicenseResult(Uint32 ulParam1, ecs::framework::MsgItem& item);
	void loginApplyLicense();
};
		} // name space login
	} // name space model
} // name space uc
