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
typedef short MT_NUMBER_TYPE;
namespace uc {
	namespace model {

		class UCClient;

		/**
		* \brief Hall
		* \note The Hall class is the detailed hall information class
		* \author  c00292094
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API Hall
		{
		public:
			Hall():
			 index_(0),name_(""),number_("")
			,T_(0),M_(0),isBroadcast_(false)
			,isChairMan_(false),isJoined_(false)
			,isMute_(false),isWatching_(false)
			{
				/*index_ = 0;
				name_ = "";
				number_ = "";
				T_ = 0;
				M_ = 0;
				isBroadcast_ = false;
				isChairMan_ = false;
				isJoined_ = false;
				isMute_ = false;
				isWatching_ = false;*/
			}

		public:
			unsigned int index_;                    //序号
			std::string name_;				//会场名
			std::string number_;			//号码
			MT_NUMBER_TYPE T_;				//会场T号
			MT_NUMBER_TYPE M_;				//会场M号
			bool isBroadcast_;				//是否在广播中
			bool isMute_;					//是否闭音状态
			bool isChairMan_;				//是否是主席
			bool isJoined_;					//是否入会
			bool isWatching_;

		public:
			bool operator < (const Hall& hall) const
			{
				bool result = false;
				if (isJoined_ && !hall.isJoined_)
				{
					result = true;
				}
				else if (!isJoined_ && hall.isJoined_)
				{
					result = false;
				}
				else
				{
					result = name_ < hall.name_;
				}
				return result;
			}

			bool operator > (const Hall& hall) const
			{
				bool result = false;
				if (isJoined_ && !hall.isJoined_)
				{
					result = false;
				}
				else if (!isJoined_ && hall.isJoined_)
				{
					result = true;
				}
				else
				{
					result = name_ > hall.name_;
				}
				return result;
			}
		};

		namespace conference {

			
			class APPCLASSLAYER_API ConferenceUiObserver
			{
			public:
				virtual bool OnConfNotification(void* _item) = 0;
			};

			/**
			* \brief ConferenceMgr
			* \note The Conference class maintains all Conference(including Conference create and control)
			* \author  c00292094
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API ConferenceMgr
			{
			public:
				ConferenceMgr(uc::model::UCClient* _cli = NULL)
					: client(_cli), observer(NULL)
				{
				}

				virtual ~ConferenceMgr()
				{

				}

				/**
				* \brief supplied to UI for notification handling
				* \param[in]  msg item
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool HandleConferenceNotify(void* _item) = 0;

				/**
				* \brief init conference manager
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool Init() = 0;

				/**
				* \brief Set/Get Language code
				* \param[in] _langcode
				* \param[out] N/A
				* \return  language code
				*/
				virtual void SetLangCode(const std::string _langCode) = 0; 
				virtual std::string GetLangCode() = 0;

				/**
				* \brief apply chairman
				* \param[in]  _password
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool ConfApplyChairman(const std::string& _password) = 0;

				/**
				* \brief release chairman
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool ConfReleaseChairman() = 0;

				/**
				* \brief extend conference time
				* \param[in]  _time
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool ConfExtend(const unsigned short& _time) = 0;

				/**
				* \brief end conference
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool ConfEnd() = 0;

				/**
				* \brief end conference
				* \param[in]  _contacts
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool ConfCreate(std::vector<uc::model::Contact>& _contacts) = 0;

				virtual bool ConfMutehall(const uc::model::Hall& _hall) = 0;

				virtual bool ConfUnMuteHall(const uc::model::Hall& _hall) = 0;

				virtual bool ConfAddThisHall(std::vector<uc::model::Contact>& _contacts) = 0;

				virtual bool ConfDeleteHall(const uc::model::Hall& _hall) = 0;
                
                virtual bool ConfCallOutHall(const uc::model::Hall& _hall) = 0;
                
				virtual bool ConfHangUpHall(const uc::model::Hall& _hall) = 0;

				virtual bool ConfBroadCastHall(const uc::model::Hall& _hall) = 0;

				virtual bool ConfUnBroadCastHall(const uc::model::Hall& _hall) = 0;

				virtual bool ConfWatchHall(const uc::model::Hall& _hall) = 0;

				virtual bool GetConfAttendeeList(std::vector<uc::model::Hall>& _confHallList) = 0;

				virtual bool IsLocalChairMan() = 0;

				virtual bool HasBroadCastHall() = 0;
				
				virtual bool IsInConference() = 0;

				virtual unsigned int GetLocalHall(uc::model::Hall& _hall) = 0;

				virtual bool ConferenceClose(unsigned int _callId) = 0;

				/**
				* \brief disconnect with UI observer
				* \param[in]  N/A
				* \param[out] N/A
				* \return  total trans count
				*/
				virtual void DisconObserver() = 0;
			public:
				uc::model::UCClient* client;   //!< uc client instance

				ConferenceUiObserver* observer;  //!< ui observer for handling notification
		
				/**
				* \brief 申请主席的结果上报        
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this:  void OnConfApplyChairManNotifySigRes(std::string _reason, bool _result) 
				*/
				sigslot::te_signal1<int> ApplyChairmanSignal;
				sigslot::te_signal1<bool> ReleaseChairmanSignal;
				sigslot::te_signal1<bool> ExtendTimeSignal;
				sigslot::te_signal0<> NeedEnterPassWordSignal;

				/**
				* \brief 创建会议的结果上报        
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this: void OnConfCreateStateChangeSigRes(std::string _result, string _reason);
				*/
				sigslot::te_signal2<std::string, int> ConfCreateStateSignal;

				/**
				* \brief 会议会控功能可用上报     
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this: void OnConfCtrlEnableSigRes(bool _reason);
				*/
				sigslot::te_signal2<short,short> ConfCtrlEnableSignal;

				/**
				* \brief 与会者列表上报     
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this: void OnConfAttendeeListRefreshSigRes(std::vector<uc::model::Hall>);
				*/
				sigslot::te_signal1< std::vector<uc::model::Hall> > ConfCtrlAttendeeListRefreshSignal;

				/**
				* \brief 会议剩余时间上报    
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this: void ConfCtrlTimeRemnantSigRes(short time);
				*/
				sigslot::te_signal1<short> ConfCtrlTimeRemnantSignal;

				/**
				* \brief 会议广播会场上报 
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this: void ConfBroadCastIndSigRes(short M, short T);
				*/
				sigslot::te_signal2<short, short> ConfBroadCastIndSignal;
                
                sigslot::te_signal1<int> ConfBroadCastResultSignal;
				sigslot::te_signal1<int> ConfWatchResultSignal;

				/**
				* \brief 会议发言指示上报 
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this: void ConfFloorAttendeeIndSigRes(std::map<uc::model::Hall, short>);
				*/
				sigslot::te_signal1< uc::model::Hall > ConfFloorAttendeeIndSignal;

				/**
				* \brief 会议主席指示上报
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this: void ConfChairmanIndSigRes(short M, short T);
				*/
				sigslot::te_signal1<bool> ConfChairmanIndSignal;

				/**
				* \brief 会控添加会场的结果上报        
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this:  void OnConfAddHallResultSigRes(std::string _reason, bool _result) 
				*/
				sigslot::te_signal2<short, bool> ConfAddHallResultSignal;

				/**
				* \brief 会控本地闭音状态上报        
				*        UI need to implement has_slots<> and connect to the signal.
				*        Like this:  void OnConfMuteStatusSigRes(bool isMute) 
				*/
				sigslot::te_signal1<bool> ConfLocalMuteStatusSignal;
			};

		}
	}
}
