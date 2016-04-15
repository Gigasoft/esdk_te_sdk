/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0


Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/
/****************************************************   
 * @file  HistroyRecord.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Histroy Record Class
 * @details 
 * @author zwx283069
 * @version 1.0
 * @date 2015-11-23
 * @history  v1.1 2015-11-23 Init TE Desktop SDK Interface
****************************************************/
#include "stdafx.h"
#include "HistoryRecord.h"
#include "LangResManager.h"
#include "Log.h"

CHistroyRecord::CHistroyRecord(void)
{
	m_RecordId = 0;
	m_bIsSearchIng = false;
	m_nCallType = -1;
}

CHistroyRecord::~CHistroyRecord(void)
{
   
}

BOOL CHistroyRecord::OnInitDialog()
{

	LoadLangRes();

	return TRUE;
}

void CHistroyRecord::LoadLangRes() //加载语言资源
{

	std::wstring str = _T("");
	str = LANG(HISTORYRECORD_RADIOBOX_CALL);

	str = LANG(HISTORYRECORD_RADIOBOX_NOANSWER);
}

int CHistroyRecord::OnRMenuClearOneRecord(long RcdId)
{
	DEBUG_TRACE("rcdId:%ld",RcdId);
	uc::model::historydata::Record record;
	uc::model::historydata::HistoryManager *pHistoryManager = uc::model::historydata::HistoryManager::Instance();
	bool bRetRcd = pHistoryManager->GetRecordByRecordId(record, RcdId);
	if (!bRetRcd)
	{
		ERROR_LOG( "GetRecordByRecordId failed !!");
		return TE_SDK_GetCallRecordsFailed;
	}
	int nRet = pHistoryManager->RemoveRecordsByRecordId(RcdId);
	if (nRet < 0)
	{
		ERROR_LOG("RemoveRecordsByRecordId fail !!");
		return TE_SDK_RemoveRecordsByRecordIdFailed;
	}
	else
	{
		INFO_LOG( " You have delete a history record!,%s",UCCLIENT()->Self->selfInfo.ucAcc_.c_str());
	}

	//删除map里的record
	std::map<long, stPersonInfo>::iterator itor = m_MapHistoryRecordList.begin();
	for (; itor != m_MapHistoryRecordList.end(); itor++)
	{
		if ((*itor).second.recordID == RcdId)
		{
			(void)m_MapHistoryRecordList.erase(itor);
			break;
		}
	}

	//删除show里的record
	std::map<long, stPersonInfo>::iterator itorShow = m_CurShowHistoryRecordList.begin();
	for (; itorShow != m_CurShowHistoryRecordList.end(); itorShow++)
	{
		if ((*itorShow).second.recordID == RcdId)
		{
			(void)m_CurShowHistoryRecordList.erase(itorShow);
			break;
		}
	}

	//RefreshHistoryList();
	return TE_SDK_Success;
}

void CHistroyRecord::InitRecentCallList()
{
	DEBUG_TRACE("");
	//此函数只用于初始化列表，刷新列表走UpdateHistoryRecordList.
	//刷新列表
	if(!m_CurShowHistoryRecordList.empty())
	{
		m_CurShowHistoryRecordList.clear();//清空当前用于显示的列表
	}
	if(!m_MapHistoryRecordList.empty())
	{
		m_MapHistoryRecordList.clear(); //清空数据
	}
	
	uc::model::historydata::HistoryManager *pHistoryManager = uc::model::historydata::HistoryManager::Instance();
	std::vector<uc::model::historydata::Record>  recordlist;
	int nRet = pHistoryManager->GetRecentPeerCallRecords(recordlist, Recentcalllnum);
	if (nRet < 0)
	{
		ERROR_LOG( "GetRecentPeerCallRecords failed !!");
	}
	std::vector<uc::model::historydata::Record>::reverse_iterator itor = recordlist.rbegin();

	m_RecordId = 0; //此函数只用于初始化列表，刷新列表走UpdateHistoryRecordList.
	for(;itor != recordlist.rend(); ++itor)
	{
		stPersonInfo stInfo;
		//hwsecure
		hw::memset_s((void*)&stInfo,sizeof(stInfo),0,sizeof(stInfo));
		stInfo.recordID = (*itor).recordId;

		//uc::model::historydata::Conversation cov;
		uc::model::historydata::Record record;

		//GetRecentCallRecords中返回的record中cvsId为默认值，导致GetConversationByConversationId无法取得conversation中的数据
		//因此使用GetRecordAndConversationByRecordId函数获取conversation中的数据。
		//pHistoryManager->GetRecordAndConversationByRecordId(record, cov, (*itor).recordId);
		bool bRet = pHistoryManager->GetRecordByRecordId(record, (*itor).recordId);
		if (!bRet)
		{
			ERROR_LOG( "GetRecordByRecordId failed !!");
		}
		stInfo.cvsID = record.cvsId;
		if(stInfo.cvsID.empty())
		{
			stInfo.cvsID = record.peerId;
		}
		stInfo.strTime = eSDKTool::utf8_2_unicode(GetCallTime((*itor).date, (*itor).time));
		stInfo.nCalltype = GetCallType((*itor).duration,(*itor).body, (*itor).read,(*itor).sent);

		stInfo.strDuration = eSDKTool::utf8_2_unicode(GetDuration((*itor).duration));

		std::string strPhone = ParsePhoneNo(record.peerId);
		stInfo.strPhone = eSDKTool::utf8_2_unicode(record.peerId);

		uc::model::Contact contact;

		if(UCCLIENT()->ContactManager->HasContactByAccount(strPhone))
		{
			(void)UCCLIENT()->ContactManager->GetContactByAccount(strPhone, contact);
		}
		else if(UCCLIENT()->ContactManager->HasNetContactByAcc(strPhone))
		{
			(void)UCCLIENT()->ContactManager->GetNetContactByAcc(strPhone, contact);
		}


		if(contact.name_.empty())
		{
			stInfo.strName = eSDKTool::utf8_2_unicode(strPhone);
		}
		else
		{
			stInfo.strName = eSDKTool::utf8_2_unicode(contact.name_);
		}

		if(stInfo.strName.empty()||contact.uri_ == UCCLIENT()->Self->selfInfo.uri_)
		{
			stInfo.strName = stInfo.strPhone;
		}

		if (!contact.ucAcc_.empty())
		{
			if(contact.uri_ == UCCLIENT()->Self->selfInfo.uri_)
			{
				stInfo.strAcc = stInfo.strPhone;
			}
			else
			{
				stInfo.strAcc =  eSDKTool::utf8_2_unicode(contact.ucAcc_);
			}
		}
		else
		{
			stInfo.strAcc = stInfo.strPhone;
		}
		stInfo.nPersonStatus = UCCLIENT()->ContactSubManager->GetContactStatus(record.peerId, contact.gender_);

		stInfo.itemID = m_RecordId;

		(void)m_MapHistoryRecordList.insert(std::map<long, stPersonInfo>::value_type(stInfo.itemID,stInfo));
		(void)m_CurShowHistoryRecordList.insert(std::map<long, stPersonInfo>::value_type(stInfo.itemID,stInfo));

		++m_RecordId;
	}
}

std::string CHistroyRecord::GetCallTime(uc::model::historydata::Date date, uc::model::historydata::Time times)
{
	DEBUG_TRACE("");
	int year = CTime::GetCurrentTime().GetYear();
	int month = CTime::GetCurrentTime().GetMonth();
	int day =  CTime::GetCurrentTime().GetDay();

	if(date.year == year && date.month == month && date.day == day)
	{
		return times.ToString();
	}
	else
	{
		return date.ToString();
	}
}

//用来将duration的时间换算成00:00:00格式
std::string CHistroyRecord::GetDuration(int duration)
{
	DEBUG_TRACE("duration:%d",duration);
	int hour = 0;
	int minute = 0;
	int second = 0;
	string str;

	if (duration > 0)
	{
		second = duration % 60;  //一分钟60秒
		duration = duration / 60;
	}

	if (duration > 0)
	{
		minute = duration % 60;  //一小时60分钟
		duration = duration / 60;
	}

	if (duration > 0)
	{
		hour = duration % 100;  //最大现实99小时
	}

	if (hour < 10)
	{
		str = "0";
	}
	str = str + eSDKTool::num2str(hour) + ":";

	if (minute < 10)
	{
		str = str + "0";
	}
	str = str + eSDKTool::num2str(minute) + ":";

	if (second < 10)
	{
		str = str + "0";
	}
	str = str + eSDKTool::num2str(second);

	return str;
}

std::string CHistroyRecord::ParsePhoneNo(const std::string& uri)
{
	DEBUG_TRACE("uri:%s",uri.c_str());
	//从uri解析号码，若非uri返回号码
	std::string::size_type pos1 = uri.find("sip:");

	if(pos1!= std::string::npos)
	{
		std::string::size_type pos2 = uri.find("@");
		if(pos2 != std::string::npos)
		{
			return uri.substr(pos1+4, pos2-pos1-4);
		}
		else
		{
			return uri.substr(pos1+4);
		}
	}
	else
	{
		return uri;
	}
}

/** 根据send和duration判断通话类型
*
*  @param[in] 
*
*  @return 
*  @retval :: 
*
*  @History:added by l00220604 2013/06/25
*/
int CHistroyRecord::GetCallType(int duration, const std::string &body, BOOL bRead , BOOL bSend)
{
	char strParameter[TE_D_MAXLOGLENGTH] = {0};
	sprintf_s(strParameter,sizeof(strParameter),"duration:%d,body:%s",duration,body.c_str());
	DEBUG_TRACE("get call type:%s",strParameter);
	//通过通话时长
	if(bSend)
	{
		if(body == "ACB")
		{
			return CALL_TYPE_ACB; //ACB回呼
		}
		else
		{
			return CALL_TYPE_DIAL; //已拨
		}
	}
	else
	{
		if(bRead && duration >= 0)
		{
			return CALL_TYPE_ANSWER; //已接
		}
		else
		{
			return CALL_TYPE_NOANSWER; //未接
		}
	}
}

int CHistroyRecord::OnRMenuClearAllRecord()
{
	DEBUG_TRACE("");
	/* begin:modified by l00220604 2013/09/25 Reason: annotate for DTS2013091805944 */
	//根据类型提示
	InitRecentCallList();
	uc::model::historydata::HistoryManager *pHistoryManager = uc::model::historydata::HistoryManager::Instance();

	if ((m_nCallType == -1) && (!m_bIsSearchIng))  //如果是全部，则直接全部清空即可
	{
		(void)pHistoryManager->RemoveHistoryCallRecords();
		if(!m_MapHistoryRecordList.empty())
		{
			m_MapHistoryRecordList.clear();
		}
		if(!m_CurShowHistoryRecordList.empty())
		{
			m_CurShowHistoryRecordList.clear();
		}
	} 
	else
	{
		//遍历删除当前显示列表
		std::map<long,stPersonInfo>::iterator itor = m_CurShowHistoryRecordList.begin();
		while (itor != m_CurShowHistoryRecordList.end())
		{
			int nRet = pHistoryManager->RemoveRecordsByRecordId((*itor).second.recordID);
			if (nRet < 0)
			{
				ERROR_LOG( "RemoveRecordsByRecordId fail !!");
				return TE_SDK_RemoveRecordsByRecordIdFailed;
			}
			itor++;
		}

		if(!m_CurShowHistoryRecordList.empty())
		{
			m_CurShowHistoryRecordList.clear(); //当前需要显示tab肯定为空
		}
	}
	/* end:modified by l00220604 2013/09/25 Reason: annotate for DTS2013091805944 */

	INFO_LOG( " You have clear all current history records,%s",UCCLIENT()->Self->selfInfo.ucAcc_.c_str());
	return TE_SDK_Success;
}

LRESULT CHistroyRecord::OnHistoryRecordSearch(WPARAM wParam,LPARAM lParam)
{
	DEBUG_TRACE("");
	tstring* pstrKey = (tstring*)wParam;
	if (pstrKey->empty())
	{
		m_bIsSearchIng = FALSE;
	}
	else
	{
		m_bIsSearchIng = TRUE;
	}
	
	//InsertResultIntoCurRecordList(*pstrKey);

	// 编辑变化为主动刷新
	//RefreshHistoryList(TRUE);

	SAFE_DELETE(pstrKey);
	return 1L;//lint !e438
}

int CHistroyRecord::InsertResultIntoCurRecordList(std::string key,TE_S_PERSONS_INFO* historyInfo)
{
	DEBUG_TRACE("");
	historyInfo->historyRecords = NULL;
	historyInfo->num = -1;
	stPersonInfo personInfo;
	int i=0;
	std::string str;
	std::wstring wcvsId;
	std::wstring str1;
	CHistroyRecord::Instance().InitRecentCallList();
	if(!m_CurShowHistoryRecordList.empty())
	{
		m_CurShowHistoryRecordList.clear();
	}
	if (key.empty())
	{
		std::map<long,stPersonInfo>::iterator itor = m_MapHistoryRecordList.begin();
		while (itor != m_MapHistoryRecordList.end())
		{
			if (((*itor).second.nCalltype == m_nCallType) || m_nCallType == -1)
			{
				personInfo = (*itor).second;
				(void)m_CurShowHistoryRecordList.insert(std::map<long, stPersonInfo>::value_type((*itor).first,personInfo));
			}
			++itor;
		}
	}
	else//搜索
	{
		std::map<long,stPersonInfo>::reverse_iterator itor = m_MapHistoryRecordList.rbegin();
		while(itor != m_MapHistoryRecordList.rend())
		{
			personInfo = (*itor).second;
			bool bIsResult = RecordCompareKey(personInfo,key);

			/* begin:modified by l00220604 2013/09/24 Reason: annotate for DTS2013091702566 */
			//屏蔽掉筛选同一号码的记录
			//bool bIsExist = FALSE;
			std::map<long,stPersonInfo>::iterator curItor = m_CurShowHistoryRecordList.begin();
			if (bIsResult)//如果该条记录匹配关键字，则先比对先前的记录。保证同一个号码只显示一次。
			{
				if (personInfo.nCalltype == m_nCallType || m_nCallType == -1)
				{
					(void)m_CurShowHistoryRecordList.insert(std::map<long, stPersonInfo>::value_type((*itor).first,personInfo));
				}
			}
			itor++;
			/* end:modified by l00220604 2013/09/24 Reason: annotate for DTS2013091702566 */
		}
	}
	historyInfo->historyRecords = (TE_S_PERSON_INFO*)malloc(sizeof(TE_S_PERSON_INFO)*m_CurShowHistoryRecordList.size());
	if(NULL == historyInfo->historyRecords)
	{
		return TE_SDK_NullPtr;
	}
	std::map<long, stPersonInfo>::const_iterator itr=m_CurShowHistoryRecordList.begin();
	for(;itr!=m_CurShowHistoryRecordList.end();itr++)
	{
		historyInfo->historyRecords[i].itemID = itr->second.itemID;
		str =  itr->second.cvsID;
		wcvsId = eSDKTool::utf82unicode(str);
		strncpy(historyInfo->historyRecords[i].cvsID, eSDKTool::WSToString(wcvsId).c_str(),TE_D_ID_LEN);
		historyInfo->historyRecords[i].recordID =  itr->second.recordID;
		historyInfo->historyRecords[i].nUserId =  itr->second.nUserId ;
		str1 =  itr->second.strAcc;
		strncpy(historyInfo->historyRecords[i].strAcc, eSDKTool::WSToString(str1).c_str(),TE_D_NUMBER_LEN);
		str1 =  itr->second.strName;
		strncpy(historyInfo->historyRecords[i].strName, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);
		str1 =  itr->second.strPhone;
		strncpy(historyInfo->historyRecords[i].strPhone, eSDKTool::WSToString(str1).c_str(),TE_D_PHONE_LEN);
		str1 =  itr->second.strMessage;
		strncpy(historyInfo->historyRecords[i].strMessage, eSDKTool::WSToString(str1).c_str(),TE_D_DESCRIPTION_LEN);
		str1 =  itr->second.strTime;
		strncpy(historyInfo->historyRecords[i].strTime, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);
		str1 =  itr->second.strDuration;
		strncpy(historyInfo->historyRecords[i].strDuration, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);
		historyInfo->historyRecords[i].nPersonStatus =  itr->second.nPersonStatus ;
		historyInfo->historyRecords[i].nPhoneStatus =  itr->second.nPhoneStatus ;
		str1 =  itr->second.strPersonIcon;
		strncpy(historyInfo->historyRecords[i].strPersonIcon, eSDKTool::WSToString(str1).c_str(),TE_D_NAME_LEN);
		historyInfo->historyRecords[i].nCalltype =  itr->second.nCalltype ;
		i++;
	}
	historyInfo->num = i;
	return TE_SDK_Success;
}

bool CHistroyRecord::RecordCompareKey(stPersonInfo &personInfo,std::string key)
{
	DEBUG_TRACE("");
	uc::model::Contact contact;
	std::string strAcc = eSDKTool::unicode2utf8(personInfo.strAcc);
	CString cstrKey = key.c_str();
	//std::string strKey = eSDKTool::unicode_2_utf8(cstrKey.MakeLower());
	std::string strKey = eSDKTool::unicode_2_utf8(key.c_str());
	tstring wkey=eSDKTool::utf8_2_unicode_w(strKey);
	if (UCCLIENT()->ContactManager->GetContactByAccount(strAcc, contact))
	{
		if (contact.ucAcc_.find(strKey.c_str()) != std::string::npos)
		{
			return TRUE;
		}
		else if(contact.name_.find(strKey.c_str()) != std::string::npos)
		{
			return TRUE;
		}
		else if(contact.qpinyin_.find(strKey.c_str()) != std::string::npos)
		{
			return TRUE;
		}
		else if(contact.spinyin_.find(strKey.c_str()) != std::string::npos)
		{
			return TRUE;
		}
	}
	else // 找不到联系人
	{
		if (personInfo.strAcc.find(wkey) != std::string::npos)
		{
			return TRUE;
		}
		else if (personInfo.strName.find(wkey) != std::string::npos)
		{
			return TRUE;
		}
		else if (personInfo.strPhone.find(wkey) != std::string::npos)
		{
			return TRUE;
		}
	}

	return FALSE;
}


int CHistroyRecord::GetAllHistoryCallRecords(TE_S_PERSONS_INFO* historyCallRecords)
{
	DEBUG_TRACE("");
	if(!historyCallRecords)
	{
		return TE_SDK_NullPtr;
	}
	historyCallRecords->historyRecords = NULL;
	uc::model::historydata::HistoryManager *pHistoryManager = uc::model::historydata::HistoryManager::Instance();
	std::vector<uc::model::historydata::Record>  recordlist;
	std::wstring wpeerId;
	int i=0;
	int nRet = pHistoryManager->GetRecentPeerCallRecords(recordlist, Recentcalllnum);
	if (nRet < 0)
	{
		ERROR_LOG( "GetRecentPeerCallRecords failed !!");
		return TE_SDK_GetCallRecordsFailed;
	}
	std::vector<uc::model::historydata::Record>::reverse_iterator itor = recordlist.rbegin();

	//	m_RecordId = 0; //此函数只用于初始化列表，刷新列表走UpdateHistoryRecordList.
	historyCallRecords->historyRecords =(TE_S_PERSON_INFO*)malloc(sizeof(TE_S_PERSON_INFO)*recordlist.size());
	if( NULL == historyCallRecords->historyRecords)
	{
		return TE_SDK_NullPtr;
	}
	for(;itor != recordlist.rend(); ++itor)
	{
		stPersonInfo stInfo;
		//hwsecure
		hw::memset_s((void*)&stInfo,sizeof(stInfo),0,sizeof(stInfo));
		stInfo.recordID = (*itor).recordId;

		//uc::model::historydata::Conversation cov;
		uc::model::historydata::Record record;

		//GetRecentCallRecords中返回的record中cvsId为默认值，导致GetConversationByConversationId无法取得conversation中的数据
		//因此使用GetRecordAndConversationByRecordId函数获取conversation中的数据。
		//bool bRet = pHistoryManager->GetRecordAndConversationByRecordId(record, cov, (*itor).recordId);
		bool bRetRcd = pHistoryManager->GetRecordByRecordId(record, (*itor).recordId);
		if (!bRetRcd)
		{
			ERROR_LOG( "GetRecordByRecordId fail !!");
			return TE_SDK_GetCallRecordsFailed;
		}
		stInfo.cvsID = record.cvsId;
		if(stInfo.cvsID.empty())
		{
			stInfo.cvsID = record.peerId;
		}
		stInfo.strTime =eSDKTool::utf8_2_unicode(GetCallTime((*itor).date, (*itor).time));
		stInfo.nCalltype = GetCallType((*itor).duration,(*itor).body, (*itor).read,(*itor).sent);

		stInfo.strDuration = eSDKTool::utf8_2_unicode(GetDuration((*itor).duration));

		std::string strPhone = ParsePhoneNo(record.peerId);
		stInfo.strPhone = eSDKTool::utf8_2_unicode(strPhone);

		uc::model::UCClient *pClient = uc::model::UCClient::GetClient();
		uc::model::Contact contact;

		if(UCCLIENT()->ContactManager->HasContactByAccount(strPhone))
		{
			(void)UCCLIENT()->ContactManager->GetContactByAccount(strPhone, contact);
		}
		else if(UCCLIENT()->ContactManager->HasNetContactByAcc(strPhone))
		{
			(void)UCCLIENT()->ContactManager->GetNetContactByAcc(strPhone, contact);
		}
		//(void)stInfo.strPersonIcon.append(PathService::GetHeadImagePathByContactW(contact));

		if(contact.name_.empty())
		{
			stInfo.strName = eSDKTool::utf8_2_unicode(strPhone);
		}
		else
		{
			stInfo.strName = eSDKTool::utf8_2_unicode(contact.name_);
		}

		if(stInfo.strName.empty()||contact.uri_ == pClient->Self->selfInfo.uri_)
		{
			stInfo.strName = stInfo.strPhone;
		}

		if (!contact.ucAcc_.empty())
		{
			if(contact.uri_ == pClient->Self->selfInfo.uri_)
			{
				stInfo.strAcc = stInfo.strPhone;
			}
			else
			{
				stInfo.strAcc =  eSDKTool::utf8_2_unicode(contact.ucAcc_);
			}
		}
		else
		{
			stInfo.strAcc = stInfo.strPhone;
		}
		stInfo.nPersonStatus = pClient->ContactSubManager->GetContactStatus(record.peerId, contact.gender_);

	//	stInfo.itemID = m_RecentCallId;
		wpeerId = eSDKTool::utf82unicode(itor->peerId);
		strncpy(historyCallRecords->historyRecords[i].strName , eSDKTool::WSToString(wpeerId).c_str(),TE_D_NAME_LEN);
		strncpy(historyCallRecords->historyRecords[i].strTime ,eSDKTool::WSToString(stInfo.strTime).c_str(),TE_D_NAME_LEN);
		strncpy(historyCallRecords->historyRecords[i].strDuration,eSDKTool::WSToString(stInfo.strDuration).c_str(),TE_D_NAME_LEN);
		historyCallRecords->historyRecords[i].nPersonStatus = stInfo.nPersonStatus;
		strncpy(historyCallRecords->historyRecords[i].strPhone,eSDKTool::WSToString(stInfo.strPhone).c_str(),TE_D_PHONE_LEN);
		historyCallRecords->historyRecords[i].recordID = stInfo.recordID;
		historyCallRecords->historyRecords[i].nCalltype = stInfo.nCalltype;
		wpeerId = eSDKTool::utf82unicode(stInfo.cvsID);
		strncpy(historyCallRecords->historyRecords[i].cvsID,eSDKTool::WSToString(wpeerId).c_str(),TE_D_ID_LEN);
		strncpy(historyCallRecords->historyRecords[i].strAcc,eSDKTool::WSToString(stInfo.strAcc).c_str(),TE_D_NUMBER_LEN);
		i++;
	}
	historyCallRecords->num = nRet;
	return TE_SDK_Success;
}

