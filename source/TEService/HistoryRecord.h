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
 * @file  HistroyRecord.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief Histroy Record Class
 * @details 
 * @author zwx283069
 * @version 1.0
 * @date 2015-11-23   
 * @history  v1.1 2015-11-23 Init TE Desktop SDK Interface
****************************************************/
#ifndef HISTROY_RECORD_H
#define HISTROY_RECORD_H

#include "stdafx.h"
/***************************************************
 * @class CHistroyRecord
 * @brief Histroy Record
 * @details 
***************************************************/
const int Recentcalllnum = 1500; /* 最大记录1500条 */

/* 用来记录Record里的信息 */
typedef struct stPersonInfo 
{
	long itemID; 
	std::string cvsID;
	long long recordID;
	int		nUserId;
	tstring strAcc;
	tstring strName;
	tstring strPhone;
	tstring strMessage;
	tstring strTime;
	tstring strDuration;
	int		nPersonStatus;
	int		nPhoneStatus;
	tstring strPersonIcon;
	int nCalltype;

	stPersonInfo()
	{
		itemID = 0;
		cvsID = "";
		recordID = 0;
		nUserId = 0;
		strAcc = _TEXT("");
		strName = _TEXT("");
		strPhone = _TEXT("");
		strMessage = _TEXT("");
		strTime = _TEXT("");
		strDuration = _TEXT("");
		nPersonStatus = 0;
		nPhoneStatus = 0;
		strPersonIcon = _TEXT("");
		nCalltype = 0;
	}

	stPersonInfo& operator =(const stPersonInfo& stInfo)
	{
		if (this != &stInfo)
		{
			itemID = stInfo.itemID;
			cvsID = stInfo.cvsID;
			recordID =  stInfo.recordID;
			nUserId = stInfo.nUserId;
			strAcc = stInfo.strAcc;
			strName = stInfo.strName;
			strPhone = stInfo.strPhone;
			strMessage = stInfo.strMessage;
			strTime = stInfo.strTime;
			strDuration = stInfo.strDuration;
			nPersonStatus = stInfo.nPersonStatus;
			nPhoneStatus = stInfo.nPhoneStatus;
			strPersonIcon = stInfo.strPersonIcon;
			nCalltype = stInfo.nCalltype;
		}
		return *this;
	}
}stPersonInfo;


class CHistroyRecord
{
public:
	static inline CHistroyRecord& Instance()
	{
		static CHistroyRecord inst;
		return inst;
	}
	virtual BOOL OnInitDialog();
public:
    CHistroyRecord(void);
    ~CHistroyRecord(void);

	std::map<long,stPersonInfo> m_CurShowHistoryRecordList;//和当前列表中显示的成员保持一致
	std::map<long, stPersonInfo> m_MapHistoryRecordList;
	long m_RecordId ;  /* 初始选择中ItemID为0 */
	bool m_bIsSearchIng;//当前显示的内容是否是搜索的结果。
	int m_nCallType;//用于保存呼叫类型
	void LoadLangRes();
	void  InitRecentCallList();
	std::string GetCallTime(uc::model::historydata::Date date, uc::model::historydata::Time times);
	std::string GetDuration(int duration);
	std::string ParsePhoneNo(const std::string& uri);
	int GetCallType(int duration, const std::string &body, BOOL bRead , BOOL bSend);
	int OnRMenuClearOneRecord(long RcdId);
	LRESULT OnHistoryRecordSearch(WPARAM wParam,LPARAM lParam);
	int OnRMenuClearAllRecord();
	int InsertResultIntoCurRecordList(std::string key,TE_S_PERSONS_INFO* historyInfo);
	bool RecordCompareKey(stPersonInfo &personInfo,std::string key);
	int GetAllHistoryCallRecords(TE_S_PERSONS_INFO* historyCallRecords);
};
#endif //HISTROY_RECORD_H