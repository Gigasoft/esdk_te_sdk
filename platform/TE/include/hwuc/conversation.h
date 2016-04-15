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

namespace uc
{
    namespace model
    {
        namespace conversation
        {

            class Conversation;

            // ! An enum
            /** \brief  Conversation state enum
            */
            enum APPCLASSLAYER_API ConversationState
            {
                ConvInactive,       /*!<  conversation is inactive */
                ConvActive,         /*!<  conversation is active*/
                ConvParked,         /*!<  conversation is been parked*/
                ConvTerminated,     /*!<  conversation is been terminated*/
                ConvInvalidState,
            };

            // ! An enum
            /** \brief  Conversation property enum
            */
            enum APPCLASSLAYER_API ConversationProperty
            {
                ConvIdentifier,     /*!< conversation ID*/
                ConvSubject,        /*!< conversation subject*/

                ConvConfIdentifier, /*< audio conference identifier*/

                ConvTempGroupUri,   /*< if have, conversation combined tempgroup uri*/
                ConvHistoryGroupUri, /*< if have, conversation is a history temp group*/
            };

            // ! An enum
            /** \brief  Session property enum
            */
            enum APPCLASSLAYER_API SessionState
            {
                SessionDisconnected,   /*!<  session disconnected*/
                SessionConnecting,     /*!<  session is connecting*/
                SessionConnected,      /*!<  session connected*/
                SessionOnHold,         /*!<  session is on hold*/
                SessionBeHeld,         /*!<  session is on behold*/
                SessionTransfering,    /*!<  session is transfering*/
            };

            // ! An enum
            /** \brief  Business session property enum
            */
            enum APPCLASSLAYER_API SessionProperty
            {
                AVSessionIdentifier,             /*!< call session identifier*/
            };

            // ! An enum
            /** \brief  enum which device to join the session
            */
            enum APPCLASSLAYER_API SessionConnType
            {
                SessionConnUri,     /*!< default value, connect soft client*/

                UnknownConnType,
            };

            // ! An enum
            /** \brief  define media session type
            */
            enum APPCLASSLAYER_API MediaSessionType
            {
                MEDIA_SESSION_NONE  = 0,
                MEDIA_SESSION_AUDIO = 1,
                MEDIA_SESSION_VIDEO = 2,
                MEDIA_SESSION_BFCP  = 4,
            };

            typedef APPCLASSLAYER_API struct
            {
                std::string caller_;
                std::string callername_;
                int callalertinfo_;
                std::string lineindex_;
                bool isvideo_;
                bool callmode_;

            } sAudioVideoParam, *PAudioVideoParam;

            /**
            * \brief Business Session class
            * \note The session class is the basis of all business flow.
            * \author  y00135380
            * \version 1.0.0  initial version
            */
            class APPCLASSLAYER_API Session
            {
            public:
                Session(Conversation* pConv)
                    : pConv_(pConv)
                {
                    state_ = SessionDisconnected;
                    mediasessiontype_ = 0;
					type_ = AudioVideo;
                }
                virtual ~Session();
                virtual bool Accept() = 0;
                virtual bool Reject() = 0;
                virtual bool Connect() = 0;
                virtual bool Disconnect() = 0;
                
                virtual bool ReferConnect() = 0;
                
            public:
                Conversation* pConv_;  //!< conversation this session belongs to

                uc::model::SessionType type_;  //!< business session type
                SessionState state_;   //!< business session state
                int mediasessiontype_;	//!<the current avsession's media sesstion type
                typedef std::map<SessionProperty, std::string> SessionProperties_;
                SessionProperties_ propmap_;  //!< properties of this conversation
            };

            /**
            * \brief Conversation class
            * \note This class is the session container of user business action.
            * \author  y00135380
            * \version 1.0.0  initial version
            */
            class APPCLASSLAYER_API Conversation
            {
            public:
                Conversation()
                    : state_(ConvInactive), sessiontype_(0)
                {
                }

                ~Conversation();

                /**
                * \brief Add Business to this conversation
                * \param[in]  SessionType
                * \param[out] N/A
                * \return  new business session
                */
                Session* AddSession(uc::model::SessionType _type);

                /**
                * \brief Get related business session
                * \param[in]  SessionType
                * \param[out] N/A
                * \return  exist business session
                */
                Session* GetSession(uc::model::SessionType _type);

                /**
                * \brief Remove specified type session
                * \param[in]  SessionType
                * \param[out] N/A
                * \return  true: success; false: faield
                */
                bool RemoveSession(uc::model::SessionType _type);

                /**
                * \brief check if have specified type session
                * \param[in]  SessionType
                * \param[out] N/A
                * \return  true: success; false: faield
                */
                bool HasSession(uc::model::SessionType _type);

                /**
                * \brief Judge if this contact has been added
                * \param[in]  Contact
                * \param[out] N/A
                * \return  true: success; false: failed
                */
                bool HasParticipant(const uc::model::Contact& _contact);

                /**
                * \brief Add Participant to this conversation
                * \param[in]  Contact can be a phone number or a real contact
                * \param[out] N/A
                * \return  true: success; false: failed
                */
                bool AddParticipant(const uc::model::Contact& _contact);

                bool RemoveParticipant(const uc::model::Contact& _contact);

				bool UpdateParticipant(const uc::model::Contact& _contact);

                /**
                * \brief End this conversation.All sessions will be auto ended.
                * \param[in]  N/A
                * \param[out] N/A
                * \return  true: success; false: failed
                */
                bool End();

            public:
                typedef std::map<uc::model::SessionType, Session*> SessMap_;
                SessMap_ sessions_;  //!< current business sessions for this conversation

                typedef std::map<std::string, Participant*> MemList_;
                MemList_ members_;  //!< participant list of this conversation(including all business session attender)

                typedef std::map<ConversationProperty, std::string> ConvProperties_;
                ConvProperties_ propmap_;  //!< properties of this conversation

                ConversationState state_;  //!< current conversation state

                /*begin:modified by Z220718 2013/06/20 Reason:辅流 annotate for eSpace for TP*/
                unsigned int sessiontype_;//会话类型，最后一位表示有音频，倒数第二位为有视频，倒数第三位为有辅流
                /*end:modified by Z220718 2013/06/20 Reason:辅流 annotate for eSpace for TP*/

            };

            /**
            * \brief AVSession class handles audio or audio conference call
            * \note This class is basic class of audio/video session.
            * \author  y00135380
            * \version 1.0.0  initial version
            */
            class APPCLASSLAYER_API AVSession: public Session
            {
            public:
                AVSession(Conversation* pConv)
                    : Session(pConv)
                {
                    type_ = uc::model::AudioVideo;
                    state_ = SessionDisconnected;
                }

                virtual ~AVSession();

                /**
                * \brief hold audio/video call
                * \param[in]  N/A
                * \param[out] N/A
                * \return  true:  success ; false: Otherwise
                */
                virtual bool Hold() = 0;

                /**
                * \brief resume audio/video call
                * \param[in]  N/A
                * \param[out] N/A
                * \return  true:  success ; false: Otherwise
                */
                virtual bool Resume() = 0;

                /**
                * \brief Get current audio call/conf mos value
                * \param[in]  N/A
                * \param[out] N/A
                * \return  current audio mos value
                */
                virtual int GetRealTimeAudioMos() = 0;

                virtual int GetRecvDataScreenSize(unsigned int &ulDataWidth, unsigned int &ulDataHeight) = 0;

                virtual void SetRecvDataScreenSize(unsigned int ulDataWidth, unsigned int ulDataHeight) = 0;

                virtual void SetAudioNetQuality(unsigned int ulNetLevel) = 0;
                
                virtual void SetVideoNetQuality(unsigned int ulNetLevel) = 0;
                /**
                * \brief close local video
                * \param[in]  N/A
                * \param[out] N/A
                * \return  current audio mos value
                */
                virtual bool CloseLocalVideo() = 0;

                /**
                * \brief open local video
                * \param[in]  N/A
                * \param[out] N/A
                * \return  current audio mos value
                */
                virtual bool  OpenLocalvideo() = 0;
                
                /**
                 * \brief mute speaker
                 * \param[in]  N/A
                 * \param[out] N/A
                 * \return  the result of mute
                 */
                virtual bool  MuteSpeaker() = 0;
                
                /**
                 * \brief unmute speaker
                 * \param[in]  N/A
                 * \param[out] N/A
                 * \return  the result of unmute
                 */
                virtual bool  UnMuteSpeaker() = 0;
                
                /**
                 * \brief mute micphone
                 * \param[in]  N/A
                 * \param[out] N/A
                 * \return  the result of mute
                 */
                virtual bool  MuteMic() = 0;
                
                /**
                 * \brief unmute micphone
                 * \param[in]  N/A
                 * \param[out] N/A
                 * \return  the result of unmuteCloseLocalVideo
                 */
                virtual bool  UnMuteMic() = 0;

                virtual std::string GetMediaInfo() = 0;

            public:
                avchannel::AudioChannel audiochannel_;  //!< audio stream channel
                avchannel::VideoChannel videochannel_;  //!< video stream channel
                avchannel::DataChannel   datachannel_;//!< data stream channel

                sigslot::te_signal1<AVSession*> StreamConnected_;
                sigslot::te_signal1<AVSession*> StreamHolded_;
            };
        }
    }
}
