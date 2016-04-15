/******************************************************************************
* Huawei Enterprise Communication API
* ldapmgr.h
* Author :  Huawei
* Description :  Group related API
* Create Time:  2015-06-03 10:27:00
* Copyright (c) 2015 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2015-06-03 1.00  First version
******************************************************************************/

#pragma  once
#include "ldapconstantdef.h"

namespace uc {
	namespace model {

		class UCClient;

		class APPCLASSLAYER_API LdapUiObserver
		{
		public:
			virtual bool OnLdapNotification(void* _item) = 0;
		};


		// 搜索条件
		struct LDAP_D_Search_Condition
		{
			std::string keywords; // 搜索关键字
			std::string sortAttribute; // 排序属性
			bool bPageSize; //  是否分页  若不支持分页下面两个参数全部传递0
			unsigned int ulCookieLen; // 若分页 0标识首页查询  其他情况 标识pcPageCookie长度 
			char *pcPageCookie; // 非文本，需要memcpy_s，上次分页查询由服务器返回

			LDAP_D_Search_Condition():keywords("")
				,sortAttribute("")
				,bPageSize(false)
				,ulCookieLen(0)
				,pcPageCookie(NULL)
			{
				
			}
		};

		// 搜索结果上抛
		struct LDAP_D_Search_Result
		{
			bool bSucess; // 是否成功
			unsigned int	ulCode; // 返回码
			unsigned int ulSeqNo; // 搜索序号的返回
			unsigned int ulCookieLen; // 本次搜索的cookie长度
			char *pcPageCookie; // cookie内容

			LDAP_D_Search_Result():bSucess(false)
				,ulCode(0)
				,ulSeqNo(0)
				,ulCookieLen(0)
				,pcPageCookie(NULL)
			{
				
			}

			~LDAP_D_Search_Result()
			{
				bSucess = false;
				ulCode = 0;
				ulSeqNo = 0;
				ulCookieLen = 0;
				if (pcPageCookie != NULL)
				{
					free(pcPageCookie);
					pcPageCookie = NULL;
				}
			}

			LDAP_D_Search_Result(LDAP_D_Search_Result& right)
			{
				bSucess = right.bSucess;
				ulCode = right.ulCode;
				ulSeqNo = right.ulSeqNo;
				ulCookieLen = right.ulCookieLen;
				if (right.ulCookieLen > 0)
				{
					pcPageCookie = (char *)malloc(right.ulCookieLen);
					hw::memset_s(pcPageCookie, ulCookieLen, 0, right.ulCookieLen);
					hw::memcpy_s(pcPageCookie, ulCookieLen, right.pcPageCookie, right.ulCookieLen);
				}
				else
				{
					pcPageCookie = NULL;
				}
			}
		};

		/**
		* \brief LdapMgr
		* \note The Conference class maintains all Conference(including Conference create and control)
		* \author  h00212443
		* \version 1.0.0  initial version
		*/
		class APPCLASSLAYER_API LdapMgr
		{
		public:
			LdapMgr(uc::model::UCClient* _cli = NULL)
				: client(_cli), observer(NULL)
			{
			}

			virtual ~LdapMgr()
			{

			}

			/**
			* \brief init ldap manager
			* \param[in]  N/A
			* \param[out] N/A
			* \return  true: success; false: failed
			*/
			virtual bool Init() = 0;

			virtual bool UnInit() = 0;

			virtual bool HandleLdapNotify(void* _item) = 0;


			/**
			*  进行搜索
			* \param[in]  searchCondition 搜索条件  
			* \param[out] ulSeqNo 出参 返回当前搜索序号
			* \return  调用接口是否成功 true: success; false: failed 
			*/
			virtual bool Search(LDAP_D_Search_Condition& searchCondition, unsigned int *ulSeqNo) = 0;


			/**
			*  进行批量更新
			* \param[in]  dnVector 批量更新
			* \param[out] seqNoVector 出参 返回当前搜索序号
			* \return  调用接口是否成功 true: success; false: failed 
			*/
			virtual bool BatchUpdate(std::vector<std::string> dnVector, std::vector<unsigned int> *seqNoVector) = 0;

			/**
			* \brief disconnect with UI observer
			* \param[in]  N/A
			* \param[out] N/A
			* \return  total trans count
			*/
			virtual void DisconObserver() = 0;

			virtual void AddOneContactToLdapCache(LDAPC_SEARCH_RESULT_D *pstContact, unsigned int ulSeqNo) = 0;

			virtual void SearchComplete(LDAP_D_Search_Result& searchResult) = 0;

			/**
			*  清除内存数据
			* \param[in]  ulSeqNo 搜索次数 根据信号槽emit上去 获取完数据之后 再将获取完的数据清除掉 
			* \return  NA
			*/
			virtual void CleanLdapCache(unsigned int ulSeqNo) = 0;

			virtual void SetOfflineMark(bool offline) = 0;

			/**
			*  获取搜索结果
			* \param[in]  ulSeqNo 搜索次数 根据信号槽emit上去 再传递下来  
			* \param[out] 出参 返回搜索结果的引用
			* \return  true: success; false: failed
			*/
			virtual bool GetSearchResult(unsigned int ulSeqNo, std::vector<Contact>& searchResult) = 0;

			virtual void GetBatchUpdateResult(std::vector<Contact> &batchUpdateReult) = 0;
		public:
			uc::model::UCClient* client;   //!< uc client instance
			LdapUiObserver* observer;  //!< ui observer for handling notification

			//  搜索完成的信号槽 第一个参数 代表是否搜索成功 第二个在失败的时候关注 为错误码 第三个为搜索序号 用于获取搜索结果以及释放内存
			sigslot::te_signal1<LDAP_D_Search_Result*> ldapSearchResultSignal;
		};

	}
}
