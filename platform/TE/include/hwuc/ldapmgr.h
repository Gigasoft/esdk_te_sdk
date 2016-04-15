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


		// ��������
		struct LDAP_D_Search_Condition
		{
			std::string keywords; // �����ؼ���
			std::string sortAttribute; // ��������
			bool bPageSize; //  �Ƿ��ҳ  ����֧�ַ�ҳ������������ȫ������0
			unsigned int ulCookieLen; // ����ҳ 0��ʶ��ҳ��ѯ  ������� ��ʶpcPageCookie���� 
			char *pcPageCookie; // ���ı�����Ҫmemcpy_s���ϴη�ҳ��ѯ�ɷ���������

			LDAP_D_Search_Condition():keywords("")
				,sortAttribute("")
				,bPageSize(false)
				,ulCookieLen(0)
				,pcPageCookie(NULL)
			{
				
			}
		};

		// �����������
		struct LDAP_D_Search_Result
		{
			bool bSucess; // �Ƿ�ɹ�
			unsigned int	ulCode; // ������
			unsigned int ulSeqNo; // ������ŵķ���
			unsigned int ulCookieLen; // ����������cookie����
			char *pcPageCookie; // cookie����

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
			*  ��������
			* \param[in]  searchCondition ��������  
			* \param[out] ulSeqNo ���� ���ص�ǰ�������
			* \return  ���ýӿ��Ƿ�ɹ� true: success; false: failed 
			*/
			virtual bool Search(LDAP_D_Search_Condition& searchCondition, unsigned int *ulSeqNo) = 0;


			/**
			*  ������������
			* \param[in]  dnVector ��������
			* \param[out] seqNoVector ���� ���ص�ǰ�������
			* \return  ���ýӿ��Ƿ�ɹ� true: success; false: failed 
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
			*  ����ڴ�����
			* \param[in]  ulSeqNo �������� �����źŲ�emit��ȥ ��ȡ������֮�� �ٽ���ȡ������������ 
			* \return  NA
			*/
			virtual void CleanLdapCache(unsigned int ulSeqNo) = 0;

			virtual void SetOfflineMark(bool offline) = 0;

			/**
			*  ��ȡ�������
			* \param[in]  ulSeqNo �������� �����źŲ�emit��ȥ �ٴ�������  
			* \param[out] ���� �����������������
			* \return  true: success; false: failed
			*/
			virtual bool GetSearchResult(unsigned int ulSeqNo, std::vector<Contact>& searchResult) = 0;

			virtual void GetBatchUpdateResult(std::vector<Contact> &batchUpdateReult) = 0;
		public:
			uc::model::UCClient* client;   //!< uc client instance
			LdapUiObserver* observer;  //!< ui observer for handling notification

			//  ������ɵ��źŲ� ��һ������ �����Ƿ������ɹ� �ڶ�����ʧ�ܵ�ʱ���ע Ϊ������ ������Ϊ������� ���ڻ�ȡ��������Լ��ͷ��ڴ�
			sigslot::te_signal1<LDAP_D_Search_Result*> ldapSearchResultSignal;
		};

	}
}
