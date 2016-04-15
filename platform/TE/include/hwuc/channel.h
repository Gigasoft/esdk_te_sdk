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
		namespace conversation {

			class Session;

			namespace avchannel {


//定义不同平台的窗口句柄
#ifdef WIN32
typedef  HWND  WINDOW_HAND;
#else
typedef  void* WINDOW_HAND;
#endif

				// ! An enum
				/** \brief  audio/video media stream direction
				*/
				enum MediaStreamDirection
				{
					InvalidMediaDir = 0,
					MediaSend,
					MediaReceive,
					MediaSendReceive,
				};

				// ! An enum
				/** \brief  audio/video channel state
				*/
				enum ChannelState
				{
					ChannelConnecting,   /*!<  channel is establishing*/
					ChannelReceive,      /*!<  channel direction is receive only*/
					ChannelSend,         /*!<  channel direction is send only*/
					ChannelSendReceive,  /*!<  channel direction is send/receive*/
					ChannelInActive,     /*!<  channel is inactive*/

					ChannelReceiving,       /*data channel is waiting for receiving*/
					VideoDecodeSucess,      /*Video First Frame Decord Sucess */
				};

				enum DataChannelEvent
				{
					DataSending,
					DataRecving,
					DataStoped,
					DataStartFailure,
					DataDecodeSucess,
				};

				enum VideoType
				{
					RemoteVideo = 0,
					LocalVideo  = 1,
					RemoteData  = 2
				};


				/**
				* \brief Channel
				* \note The Channel class controls media stream.
				* \author  y00135380
				* \version 1.0.0  initial version
				*/
				class APPCLASSLAYER_API Channel
				{
				public:

					Channel(ChannelState state = ChannelInActive);

					Channel(ChannelState state,uc::model::conversation::Session* ownsession );

					/**
					* \brief Resume channel
					*        It's used for Resume a holded channel
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Start() = 0;

					/**
					* \brief Hold channel
					*        It's used for hold an established channel
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Stop() = 0;


					virtual ChannelState GetChannelState() const;
					virtual void SetChannelState(const ChannelState enChannelState);

					virtual uc::model::conversation::Session* GetChannelSession();
					virtual void SetChannelSession(Session* const pSession);

                private:
                    
					ChannelState state_;  /*!< Current channel state*/
                    
					uc::model::conversation::Session* session_;  /*!< Session that this channel belongs to*/

				public:

					/**
					* \brief Occurs when the channel state changes
					*        UI need to implement has_slots<> and connect to the signal.
					*        Like this:  void OnChannelStateChanged(uc::model::conversation::avchannel::ChannelState _state, uc::model::conversation::Session* _pSess); 
					*/
					sigslot::te_signal2<ChannelState, uc::model::conversation::Session*> ChannelStateChanged;  
				};

				/**
				* \brief Audio Channel
				* \note The Channel class controls audio media stream.
				* \author  y00135380
				* \version 1.0.0  initial version
				*/
				class APPCLASSLAYER_API AudioChannel: public Channel
				{
				public:

					/**
					* \brief See the reference of Channel
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Start();

					/**
					* \brief See the reference of Channel
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Stop();

                    /**
					* \brief Send DTMF event
					* \param[in]  _tones dtmf event string
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					bool SendDTMF(const std::string& _tones);
				};

				/**
				* \brief VideoWindow
				* \note The Channel class controls media channel.
				* \author  y00135380
				* \version 1.0.0  initial version
				*/
				struct APPCLASSLAYER_API VideoWindow
				{
				public:
					VideoWindow()
						: wnd_(NULL)
						//, height_(0)
						//, width_(0)
					{

					}
                    
					WINDOW_HAND wnd_;   //!< render window
					//int height_; //!< render window height  目前没有用处
					//int width_;  //!< render window width   目前没有用处
				};

				/**
				* \brief Video Channel
				* \note The Channel class controls video media stream.
				* \author  y00135380
				* \version 1.0.0  initial version
				*/
				class APPCLASSLAYER_API VideoChannel: public Channel
				{
				public:
                    
                    VideoChannel() {iVideoClosedReason = 0;}

					/**
					* \brief See the reference of Channel
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Start();

					/**
					* \brief See the reference of Channel
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Stop();

					/**
					* \brief Change video channel's VideoWindow parameter
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Update();
#ifdef __APPLE__

					virtual bool PauseRender();
					virtual bool ResumeRender();
#endif // __APPLE__
					virtual bool Cancel();

					bool SwitchRemoteOrLocalVideoDisplayType(bool bRemoteVideo, bool bIsOriginalProportionDisplayType);
                    
                    
                    //设置远端主流接收窗口的句柄
                    void setVideoRemoteWnd(WINDOW_HAND Handle) {remotewnd_.wnd_ = Handle;}

                    //获取远端主流接收窗口的句柄
                    WINDOW_HAND getVideoRemoteWnd() {return remotewnd_.wnd_;}
                    

                    //设置本地主流接收窗口的句柄
                    void setVideoLocalWnd(WINDOW_HAND Handle) {localwnd_.wnd_ = Handle;}

                    //获取本地主流接收窗口的句柄
                    WINDOW_HAND getVideoLocalWnd() {return localwnd_.wnd_;}

                private:
                    VideoWindow remotewnd_;  //!< remote video render window                
                    VideoWindow localwnd_;   //!< local video render window

				public:
					int iVideoClosedReason;  //视频转音频的原因 0-正常操作 1-带宽过低
				};

				class APPCLASSLAYER_API DataChannel: public Channel
				{
				public:
					/**
					* \brief See the reference of Channel
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Start();

					bool StartRecv();

					virtual bool Stop();

					/**
					* \brief Change data channel's VideoWindow parameter
					* \param[in]  N/A
					* \param[out] N/A
					* \return  true: success; false: failed
					*/ 
					virtual bool Update();

					bool SwitchRemoteDataDisplayType(bool bIsOriginalProportionDisplayType, bool bTrueOriginalDisplayType);

                    //设置辅流接收窗口的句柄
                    void setDataRemoteWnd(WINDOW_HAND Handle) {remotewnd_.wnd_ = Handle;}
                    
                    WINDOW_HAND getDataRemoteWnd() { return remotewnd_.wnd_; }
                    
                    //设置被共享的桌面、或者程序的句柄
                    void setDataCaptureWnd(WINDOW_HAND Handle) {capturewnd_.wnd_ = Handle;}

                    private:
                        VideoWindow remotewnd_;  //!< remote data render window
                        
                        VideoWindow capturewnd_;

                    public:
                        
                    #ifdef __APPLE__
                    unsigned int captureWndId_;
                    #endif

					sigslot::te_signal3<DataChannelEvent, uc::model::conversation::Session*, int> ChannelEventChanged;
				};
			}
		}
	}
}
