/******************************************************************************
* Huawei Enterprise Communication API
* group.h
* Author :  Huawei
* Description :  Group related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/

#pragma  once
namespace uc {
	namespace model {

		class UCClient;

		namespace conversation {

			/**
			* \brief ConversationUiObserver
			* \note The ConversationUiObserver class is the interface exposed to UI
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API ConversationUiObserver
			{
			public:
				virtual bool OnConvNotification(void* _item) = 0;
			};

			/**
			* \brief ConversationMgr
			* \note The ConversationMgr class maintains all conversation(including outgoing and incoming)
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API ConversationMgr
			{
			public:
				ConversationMgr(uc::model::UCClient* _cli = NULL)
					: client(_cli), observer(NULL)
				{
				}

				virtual ~ConversationMgr()
				{

				}

				/**
				* \brief supplied to UI for notification handling
				* \param[in]  msg item
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool HandleConversationNotify(void* _item) = 0;

				/**
				* \brief init conversation manager
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool Init() = 0;

				/**
				* \brief create a new conversation
				* \param[in]  N/A
				* \param[out] N/A
				* \return  conversation: if success, generate an identifier for new conversation
				*/
				virtual Conversation* AddConversation() = 0;

				/**
				* \brief remove an exist conversation
				* \param[in]  _sess: Conversation need to be deleted 
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool RemoveConversation(const std::string& _identifier) = 0;

				/**
				* \brief get an exist conversation
				* \param[in]  Conversation identifier 
				* \param[out] N/A
				* \return  true: conversation pointer; false: NULL
				*/
				virtual Conversation* GetConversation(const std::string& _identifier) = 0;

				/**
				* \brief get an exist conversation has specified contact
				* \param[in]  _contact 
				* \param[out] N/A
				* \return  true: conversation pointer; false: NULL
				* modify by hKF68714 change param tpye from const uc::model::Contact to const uc::model::Contact&
				*/
				virtual Conversation* GetConversationByContact(const uc::model::Contact& _contact) = 0;

				/**
				* \brief Get count of exist conversation with AVSession
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true or false
				*/
				virtual int GetAVSessionConvCount() = 0;

				/**
				* \brief Check if exist conversation with AVSession and AVSession is conference
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true or false
				*/
				virtual bool HasConfAVSessionConv() = 0;

				/**
				* \brief Check if exist conversation with AVSession and AVSession is connecting
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true or false
				*/
				virtual bool HasConnectingAVSession() = 0;

				/**
				* \brief get now AVSession Call id if exist
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true or false
				*/
				virtual unsigned int GetNowAVSessionCallID() = 0;
				/**
				* \brief disconnect with UI observer
				* \param[in]  N/A
				* \param[out] N/A
				* \return  total trans count
				*/
				virtual void DisconObserver() = 0;
			public:
				uc::model::UCClient* client;   //!< uc client instance

				ConversationUiObserver* observer;  //!< ui observer for handling notification

				/**
				* \brief new audio/video session has been added signal.
				*        incoming audio/video call for UE
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this:  void OnAvSessAdded(uc::model::conversation::Conversation* _con); 
				*/
				sigslot::te_signal2<Conversation*, sAudioVideoParam> AVSessAdded;

				/**
				* \brief AV session receive ring notification
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this:  void OnAVSessionRinged(uc::model::conversation::Conversation* _con); 
				*/
				sigslot::te_signal1<Conversation*> AVSessionRinged;

				/**
				* \brief AV session receive closed notification
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this:  void OnAVSessionClosed(uc::model::conversation::Conversation* _con, std:;string _reason); 
				*/
				sigslot::te_signal3<Conversation*, std::string, std::string> AVSessionClosed;

				/**
				* \brief AV session receive connected notification
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this:  void OnAVSessionConnected(uc::model::conversation::Conversation* _con); 
				*/
				sigslot::te_signal2<Conversation*, int> AVSessionConnected;

				/*begin:modified by Z220718 2013/06/20 Reason:新增的呼叫类上报事件 annotate for eSpace for TP*/
				sigslot::te_signal2<Conversation*, std::string> AVSessionRefered;//呼叫转移
				sigslot::te_signal2<std::string, bool> AVSessionRecord;//开始、停止，bool中 true是开始；false是停止
				sigslot::te_signal3<std::string, int, bool> AVSessionBFCPModified;//辅流BFCP重能力协商结果  
				/*begin:modified by Z220718 2013/06/20 Reason:新增的呼叫类上报事件 annotate for eSpace for TP*/

				sigslot::te_signal2<std::string, bool> AVSessionCameraOper;

				sigslot::te_signal2<Conversation*, bool> AVSessionBeHold;//呼叫被保持
			};

		}
	}
}
