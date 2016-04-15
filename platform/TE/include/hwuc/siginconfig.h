/******************************************************************************
* Huawei Enterprise Communication API
* siginconfig.h
* Author :  Huawei
* Description :  SignInConfig related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once

#ifdef WIN32
#include "hwsecure/securec.h"
#endif

namespace uc {
	namespace model {

		/**
		* \brief PasswordWrapper
		* \note The PasswordWrapper class is the password stored in ram with certain encrypt algorithm.
		* \author  k00191387
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API PasswordWrapper
		{
		public:
			PasswordWrapper();
			~PasswordWrapper();
			PasswordWrapper(const PasswordWrapper &p);
			PasswordWrapper(const std::string &p);
			PasswordWrapper &operator=(const std::string &p);
			PasswordWrapper &operator=(const PasswordWrapper &p);
			operator std::string () const;
			std::string encryptText() const;
			void setEncryptText(const std::string &text);
		private:
			int ToPwd(const std::string text, std::string &out) const ;
			int GetPwd(const std::string text, std::string &res) const ;

			std::string m_pwdEncryptText;
		};
		/**
		* \brief SignInConfig
		* \note The SignInConfig class is the signin configuration collection manager class.
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		struct APPCLASSLAYER_API SignInConfig
		{
		public:
			std::string account;  /*!< SignIn account*/
			uc::model::PasswordWrapper pwd;              /*!< SignIn password*/
			std::string strSipRegisterMode;
			std::string lang;     /*!< Current using language*/

			bool savepwd;   /*!< Whether saving password*/
			bool autosign;  /*!< Whether auto sign in next time*/

			ContactAvailability initStatus; /*! Sign in initial status*/

			std::string licenseServerIp; /*! Sign in licenseServerIp*/

            void SetInternalUrl(std::string strUrl) { internalurl = strUrl; }
            std::string GetInternalUrl() { return internalurl; }

			void SetSipDomain(std::string domain){sipDomain = domain;}
			std::string GetSipDomain(){return sipDomain;}

			void SetUserName(std::string name){userName = name;}
			std::string GetUserName(){return userName;}

			void SetSipUri(std::string uri){sipUri = uri;}
			std::string GetSipUri(){return sipUri;}

            void SetBeAnonymityLogin(bool bAnonymityLogin) { bIsAnonymityLogin = bAnonymityLogin; }
            bool GetBeAnonymityLogin() { return bIsAnonymityLogin; }

            void SetClientVersion(std::string strVer) { ver = strVer; }
            std::string GetClientVersion() { return ver; }
			
			bool getADCertification(){return mIsADCertification;}
			void setADCertification(bool result){mIsADCertification = result;}
			void SetLicenseServer(std::string serverIp){ licenseServerIp = serverIp;}
			std::string GetLicenseServer(){return licenseServerIp;}

			SignInConfig()
			{
#ifdef WIN32
				hw::memset_s(this, sizeof(SignInConfig), 0, sizeof(SignInConfig));
#endif
			}
            
        private:                            
			std::string internalurl;  /*!< Internal server address*/
			std::string sipDomain; /*!< Sip域（可选） */
			std::string userName;
			std::string sipUri;
            bool bIsAnonymityLogin;            
			std::string ver;      /*!< Current client version*/

			//AD认证结果
			bool mIsADCertification;
		};


	}//namespace model
}//namespace uc
