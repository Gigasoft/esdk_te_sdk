/******************************************************************************
* Huawei Enterprise Communication API
* contactsubscription.h
* Author :  Huawei
* Description :  ContactSubscription related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/
#pragma  once

namespace uc
{
	namespace model
	{

		/**
		* \brief ContactSubscription
		* \note The ContactSubscription class manager all contacts subscription
		* \author  y00135380
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API ContactSubscription
		{
		public:
			virtual ~ContactSubscription() {}

			/**
			* \brief Init contact presence subscription
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true:  success ; false: failed
			*/
			virtual bool Init() = 0;
			virtual bool Uninit() = 0;

			/**
			* \brief get the specified contact status
			* \param[in]  contact uri
			* \param[out] ContactAvailability description
			* \param[out] contact device type
			* \return  ContactAvailability and
			*/
			virtual ContactAvailability GetContactStatus(const std::string& _uri, const std::string &_protocolType) = 0;
			virtual ContactAvailability GetContactStatus(const std::string& _uri, std::string& _desc,const std::string &_protocolType) = 0;
			virtual std::string GetContactDevice(const std::string& _uri) = 0;

			virtual void ClearSubList() = 0;

			virtual bool SubSCUserStatus(const bool _bFresh) = 0;
			virtual bool UnSubSCUserStatus(const std::string& _id) = 0;

		public:
			/**
			* \brief Contact state changed Signal
			*        UI need to implement has_slots<> and connect to the signal.
			*        Like this:  void OnAvailabilityChanged(uc::model::UCClient::ContactAvailability _state,
			*                          std::string _desc, uc::model::Contact _contact);
			*/
			sigslot::te_signal3<uc::model::ContactAvailability, std::string, uc::model::Contact&> UserAvailabilityChanged_;
			sigslot::te_signal1<std::string> SCStatusNotify_;
            
		};

	}
}
