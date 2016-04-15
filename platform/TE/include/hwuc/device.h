/******************************************************************************
* Huawei Enterprise Communication API
* device.h
* Author :  Huawei
* Description :  Device and DeviceMgr related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/

#pragma  once

#ifndef WIN32
typedef unsigned int UINT;
#endif
namespace uc {
	namespace model {
		namespace device {

			/**
			* \brief PreviewWndParam
			* \note The PreviewWndParam class is video drawing window param.
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			struct APPCLASSLAYER_API PreviewWndParam
			{
			public:
				unsigned long wndhandle;   /*!< video window handle*/
				unsigned long wndleft;     /*!< left coordinate*/
				unsigned long wndwidth;    /*!< window width*/
				unsigned long wndtop;      /*!< top coordinate*/
				unsigned long wndheight;   /*!< window height*/
			};

			/**
			* \brief Device
			* \note The Device class is the basis class of all audio/video devices.
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API Device
			{
			public:
				Device():
					/* Begin:modify by hKF68714 2014/03/21,reason:TQE for TP V100R001C01*/
					  index(0)
					  ,iscertified(false)
					  ,isactive(false)
					  ,type(false)
					  ,name("")
					  /* End:modify by hKF68714 2014/03/21,reason:TQE for TP V100R001C01*/
				  {

				  }
				/**
				* \brief get Speaker device level
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual int GetGain() = 0;
				virtual bool SetGain(int _gain) = 0;

				virtual int GetLevel() = 0;
				/**
				* \brief Mute device
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual bool Mute() = 0;

				/**
				* \brief UnMute device
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual bool UnMute() = 0;

				/**
				* \brief Set device volume
				* \param[in]  volume level
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual bool SetVolume(int _vol) = 0;

				/**
				* \brief Get device volume
				* \param[in]  N/A
				* \param[out] N/A
				* \return  volume level
				*/ 
				virtual int GetVolume() = 0;

			public:
				std::string name;   /*!< device name*/
				int index;          /*!< device no*/
				bool iscertified;   /*!< if device is verified by Huawei Corp.*/
				bool isactive;      /*!< if device is active*/

				bool type;          /*!< 设备类型*/

			};

			/**
			* \brief MicDev
			* \note The MicDev class is microphone device.
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API MicDev: public Device
			{
			public:
				/**
				* \brief Begin microphone device test
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool BeginMicTest() = 0;

				/**
				* \brief End microphone device test
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true: success; false: failed
				*/
				virtual bool EndMicTest() = 0;

			};

			/**
			* \brief SpeakerDev
			* \note The SpeakerDev class is speaker device.
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API SpeakerDev: public Device
			{
			public:
				/**
				* \brief Begin to play a audio file
				* \param[in]  filename
				* \param[in]  true: loop; false: just once
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual int BeginPlayFile(const std::string& _file, bool _loop) = 0;

				/**
				* \brief Stop current file playing
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual bool StopPlayFile(int handle) = 0;	
				
				int m_handle;
			};

			/**
			* \brief VideoDev
			* \note The VideoDev class is video device.
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API VideoDev: public Device
			{
			public:
				/**
				* \brief Begin video preview
				* \param[in]  video preview window
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual bool BeginPreview(PreviewWndParam _param, int _index) = 0;

				/**
				* \brief End video preview
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual bool EndPreview() = 0;
			};

			/**
			* \brief DeviceMgr
			* \note The DeviceMgr class managers Audio and Video devices
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API DeviceMgr
			{
			public:
				DeviceMgr()
					: activemicdev(NULL)
					, activespkerdev(NULL)
					, activevideodev(NULL)
				{
				}
				
				//Begin Modify By hKF68714 2013/08/05 Reason:TQE eSpace for TP V100R001C01	
				virtual ~DeviceMgr()
				{

				}
				//End Modify By hKF68714 2013/08/05 Reason:TQE eSpace for TP V100R001C01	

				/**
				* \brief Init device list
				* \param[in]  N/A
				* \param[out] N/A
				* \return  true:  success ; false: failed 
				*/ 
				virtual bool Init() = 0;
				virtual bool Uninit() = 0;

				virtual bool SetAudioCaptureDev(const UINT _index) = 0;

				virtual bool SetAudioPlayDev(const UINT _index) = 0;

				virtual bool SetVideoCaptureDev(const UINT _index) = 0;
                
#ifdef __APPLE__
				  virtual bool performanceForCPU() = 0;
#endif
              

			public:
				uc::model::device::MicDev* activemicdev;    //!< current active microphone device
				uc::model::device::SpeakerDev* activespkerdev;  //!< current active speaker device
				uc::model::device::VideoDev* activevideodev;    //!< current active video device

				std::vector<uc::model::device::MicDev*> micdevlist;  //!< microphone device list
				std::vector<uc::model::device::SpeakerDev*> speakerdevlist;  //!< speaker device list
				std::vector<uc::model::device::VideoDev*> videodevlist;  //!< video device list

			};

		}
	}
}
