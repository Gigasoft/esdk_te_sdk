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
 * @file  eSDKTool.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief eSDK common tool
 * @details common function
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 eSDK common tool
****************************************************/
#ifndef _ESDKTOOL_H
#define _ESDKTOOL_H

#include <string>
#include <vector>
#include <list>
#include <iosfwd>

#ifdef WIN32
#include <tchar.h>
#include <time.h>
#include <atltime.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Iphlpapi.h>
#endif
#include "ctk/ctk.h"
#include "hwuc/HWUC.h"
#include "history/history.h"
#include "stdafx.h"

const int STRING_LENGTH = 100;//���ж����ַ����̶�����
const int IM_LENGTH = 1024*10;//��ʱ��Ϣ��󳤶�

//#include "UCHistoryMgr.h"

using namespace std;
//#include "Log.h"

#define USER_AGENT				"Huawei SoftCoPCA"

#define SAFE_DELETE(pPoint) 	if(NULL != pPoint)\
{\
	delete pPoint;\
	pPoint = NULL;\
}

#define SAFE_DELETE_ARRAY(pPoint) 	if(NULL != pPoint)\
{\
	delete[] pPoint;\
	pPoint = NULL;\
}

#define CHECK_POINTER(pPoint) if(NULL == pPoint)\
{\
	return;\
}

#define CHECK_POINTER_RETURN(pPoint,ret) if(NULL == pPoint)\
{\
	return ret;\
}

#if 0
namespace esdkTools
{
	//�ַ���ת��Ϊ�����ڶ�������ָ�����ƣ�Ĭ��ʮ���ƣ�
	//ʹ��ʱָ��ģ��������ͣ�ת��ʧ���׳�runtime_error�쳣
	template<class T> inline T str2num(
		const std::string & str, std::ios_base &(*f)(std::ios_base&) = std::dec) 
	{ 
		T num;

		std::istringstream iss(str);
		if ((iss >> f >> num).fail()) 
			throw std::runtime_error("invalid conversion : str = " + str);

		return num;
	}

	//����ת��Ϊ�ַ������ڶ�������ָ�����ƣ�Ĭ��ʮ���ƣ�
	//ʹ��ʱ���Բ�ָ��ģ��������ͣ�ת��ʧ���׳�runtime_error�쳣
	template<class T> inline std::string num2str(
		const T & num, std::ios_base &(*f)(std::ios_base&) = std::dec)
	{
		std::ostringstream oss;
		if ((oss << f << num).fail())
			throw std::runtime_error("invalid conversion : num = " + num);

		return oss.str();
	}
}
#endif

//������
/***************************************************
 * @class eSDKTool
 * @brief provide eSDK common tool function 
 * @details 
***************************************************/
class eSDKTool
{
private:
	eSDKTool(void);
	~eSDKTool(void);
public:
	static void GetStartTime(uc::model::historydata::Date& startdate,uc::model::historydata::Time& starttime,unsigned int duration);
	static void getCurrentPath(std::string& cstrPath);//��ȡ��ǰ�����ִ��·��	
	static bool IsValidUri(const std::string& uri);//�ж��Ƿ�����Чuri
	static bool IsVirtualUri(const std::string& uri);//�ж��Ƿ���ģ���uri��û�а��κκ���	
	static std::string GetNoFromUri(const std::string & uri);//��uri����ȡ����
	static std::string MergeString(const std::vector<std::string>& strList);// ��','Ϊ����ϲ��ַ����б�
	static void SplitString(const std::string& inputstr,std::vector<std::string>& stroutputList);//���ն��ŷֽ��ַ���
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);//���롰10.10.10.10:10������������10.10.10.10����10
	static std::string CreateGuidStr();

	static std::wstring utf82unicode(const std::string& utf_str);
	static std::string unicode2utf8(const std::wstring & uni_str);
	static std::string Unicode2Utf8(const std::wstring& widestring);
	static std::string utf8str2unicodestr(const std::string& utf_str);
	static std::string WSToString(const std::wstring& ws);

	static std::string unicode_w_2_utf8(const std::wstring & uni_str);
	static CString utf8_2_unicode(const std::string& utf_str);
	static ctk::String unicode_2_utf8(const CString& uni_str);
	static std::wstring CstringToWstring(CString m_ContactName);
	static std::wstring utf8_2_unicode_w(const std::string & utf_str);

	static void GetNumStringFromCmd(const std::string& _spker, std::string& _spkeNum0, std::string& _spkeNum1);
	static bool CheckString(const std::string strNum1,const std::string& strNum2,std::string& strNum3);//�鿴strNum2��ǰ��ļ����ַ����ǲ���strNum1�����򷵻�true

	static void UTCTime2LocalTime(const std::string& _utcdate, const std::string& _utctime, std::string& localdate_, std::string& localtime_);
	static int MakeDir(const std::string &path);
	static bool RenameFile(const std::string &filepath, const std::string &newfilepath);
	static void GetFilesInDir(const std::string& _dirPath,std::list<std::string>& _lstFiles);

	static bool Access(const std::string & path, int mode);
	static bool Access(const std::wstring & path, int mode);
	static bool Exists(const std::string & path)
	{ return Access(path, 0); }
	static bool Exists(const std::wstring & path)
	{ return Access(path, 0); }
	static std::string GetProgramDir();
	static CString GetProgramDir1();
	static std::wstring GetProgramDirW();

	static bool DeleteFile(const std::string & filepath);

	static std::string num2str(int);
	//static int str2num(const std::string& str);
	template<class T> inline static T str2num(
		const std::string & str, const T & def = T(), 
		std::ios_base &(*f)(std::ios_base&) = std::dec) 
	{ 
		T num = def; 

		std::istringstream iss(str); 
		if ((iss >> f >> num).fail()) 
		{
			//throw std::runtime_error("invalid conversion : str = " + str);
		}
		return num; 
	} 
	template <class T> inline static 
		std::basic_string<T> & trim(std::basic_string<T> & s) 
	{
		if (s.empty())
			return s;

		std::basic_string<T>::iterator c;

		// Erase whitespace before the string
		for (c = s.begin(); c != s.end() && iswspace(*c++););
		s.erase(s.begin(), --c);

		// Erase whitespace after the string
		for (c = s.end(); c != s.begin() && iswspace(*--c););
		if (s.end() != c)
		{
			s.erase(++c, s.end());
		}

		return s;
	}
	static BOOL IsValidEmailFormat(const std::string &strEmail);	
	static BOOL IsValidEmailChar(const char ch);
	static long long GetCurUTCTime();

	static bool GetBestHostip(std::string& ip, const std::string& serverip);
	static std::string eSDKTool::ParsePhoneNo(const std::string& uri);
	static bool IsValidIP_V4(const std::string &ip);
	static bool IsEmptyUri(const std::string& uri);
//	static bool IsValidUri(const std::string& uri);
//	static std::string GetNoFromUri(const std::string & uri);

private:
	static std::wstring s_modulePathW;
	static std::string s_modulePath;
};

#endif


