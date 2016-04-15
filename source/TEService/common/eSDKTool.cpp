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
 * @file  eSDKTool.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief eSDK common tool
 * @details common function
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 eSDK common tool
****************************************************/

#include "stdafx.h"
#include "objbase.h"
#include "eSDKTool.h"
#include <io.h>


eSDKTool::eSDKTool(void)
{
}

eSDKTool::~eSDKTool(void)
{
}

void eSDKTool::getCurrentPath(std::string& strPath)
{
	HMODULE hModule = GetModuleHandle(L"TEService.dll");
	char path[MAX_PATH+1] = {0};
	::GetModuleFileNameA(hModule, path, MAX_PATH);
	std::string strModulePath = path;
	unsigned int loc = strModulePath.find_last_of("\\");
	if( loc != string::npos )
	{
		strPath = strModulePath.substr(0,loc);
	}
}

void eSDKTool::GetStartTime(uc::model::historydata::Date& startdate,uc::model::historydata::Time& starttime,unsigned int duration)
{
	_tzset();
	CTime times =  CTime::GetCurrentTime();
	times -= (long long)duration;
	startdate.year = times.GetYear();
	startdate.month = times.GetMonth();
	startdate.day = times.GetDay();
	starttime.hour = times.GetHour();
	starttime.minute = times.GetMinute();
	starttime.second = times.GetSecond();
}
bool eSDKTool::IsValidUri(const std::string& uri)
{
	size_t nSip = uri.find("sip:");
	if (nSip != 0) //必须以sip:开头
	{
		return false;
	}
	return true;
}
bool eSDKTool::IsVirtualUri(const std::string& uri)
{
	//模拟的没有绑定任何号码的用户uri
	if (0 == uri.find("sip:index"))
	{
		return true;
	}
	return false;
}
std::string eSDKTool::GetNoFromUri(const std::string & uri)
{
	size_t nSip = uri.find("sip:");

	if (nSip != 0) //必须以sip:开头
	{
		return "";
	}

	if (IsVirtualUri(uri))
	{
		return "";
	}

	size_t nAt = uri.find('@');
	if (std::string::npos == nAt) //必须含有@字符
	{
		return "";
	}
	//取sip:与@之间的字符串，注意要除去长度为4的"sip:"
	std::string strNum = uri.substr(/*nSip +*/ 4, (nAt /*- nSip*/) - 4); //程序执行到此行时，nSip==0

	if (strNum.find('+') != std::string::npos)
	{
		strNum = strNum.substr(1);
	}

	return strNum;
}

std::string eSDKTool::MergeString(const std::vector<std::string>& strList)
{
	unsigned int iSize = strList.size();
	std::string outStr("");
	if(iSize == 0)
	{
		return outStr;
	}
	if(iSize == 1)
	{
		outStr.append(strList.at(0));
		return outStr;
	}
	for(unsigned int i=0;i<(iSize-1);++i)
	{
		outStr.append(strList.at(i));
		outStr.append(",");
	}
	outStr.append(strList.at(iSize-1));
	return outStr;
}
void eSDKTool::SplitString(const std::string& inputstr,std::vector<std::string>& stroutputList)
{
	stroutputList.clear();

	std::string instr = inputstr;
	int pos = -1;
	do{
		pos = (int)instr.find(',');
		stroutputList.push_back(instr.substr(0,(unsigned int)pos));
		instr = instr.substr((unsigned int)(pos+1));
	}while(-1 != pos && instr!="");
	return;
}
void eSDKTool::GetIPPort(const std::string& serverURL,std::string& ip,int& port)
{
	ip.clear();
	std::string instr = serverURL;
	string::size_type pos = instr.find(':');
	if( pos != string::npos )
	{
		ip = instr.substr(0,pos);
		std::string outPort = instr.substr(pos+1);
		port =  atoi(outPort.c_str());
	}
	else
	{
		ip = "";
		port = 0;
	}


	return;
}
std::string eSDKTool::CreateGuidStr()
{
	GUID guid;
	(void)::CoCreateGuid(&guid);

	char buf[64];
	(void)::sprintf_s(buf,sizeof(buf), 
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", 
		(unsigned int)guid.Data1, guid.Data2, guid.Data3, 
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], 
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	return buf;
}

std::string eSDKTool::unicode_w_2_utf8(const std::wstring & uni_str)
{
	if (uni_str.empty())
	{
		return std::string();
	}
	std::string strOut(ctk::to_utf8str(uni_str.c_str()));

	return strOut;
}

//UTF8转化为unicode
CString eSDKTool::utf8_2_unicode(const std::string& utf_str)
{
	CString szResult(_T(""));
	std::wstring strOut = L"";
	ctk::utf8ToWstring(utf_str,strOut);

	szResult = strOut.c_str();

	return  szResult;
}


ctk::String eSDKTool::unicode_2_utf8(const CString& uni_str)
{
	ctk::String strRes = "";

	strRes = ctk::to_utf8str(uni_str.GetString());

	return strRes;
}
//UTF8转化为unicode
std::wstring eSDKTool::utf82unicode(const std::string& str)
{
	int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pUnicode =  new  wchar_t[nLen+1];  
	memset(pUnicode,0,(nLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,0,str.c_str(),-1,(LPWSTR)pUnicode,nLen );  
	std::wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	std::wstring cstr = rt.c_str();
	delete[]  pUnicode; 
	return cstr;
}

std::wstring eSDKTool::CstringToWstring(CString m_ContactName)
{
	CStringW ContactName;
	std::wstring cstrName;
	ContactName = m_ContactName;
	cstrName = ContactName;
	return cstrName;
}

std::wstring eSDKTool::utf8_2_unicode_w(const std::string & utf_str)
{
	if (utf_str.empty())
	{
		return std::wstring();
	}
	std::wstring strOut;
	ctk::utf8ToWstring(utf_str, strOut);

	return strOut;
}


std::string eSDKTool::utf8str2unicodestr(const std::string& utf_str)
{
	std::wstring strOut = utf82unicode(utf_str);

	int len= WideCharToMultiByte(CP_ACP,0,strOut.c_str(),(int)wcslen(strOut.c_str()),NULL,0,NULL,NULL); 
	char* pChar=new char[(unsigned int)len+1]; 
	WideCharToMultiByte(CP_ACP,0,strOut.c_str(),(int)wcslen(strOut.c_str()),pChar,len,NULL,NULL); 
	pChar[len]='\0';

	std::string str(pChar);
	delete[] pChar;
	return  str;
}

std::string eSDKTool::WSToString(const std::wstring& ws)
{	
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::string eSDKTool::unicode2utf8(const std::wstring & wstr)
{
	char* pElementText;
	int   iTextLen = WideCharToMultiByte(CP_UTF8,0,wstr.c_str(),-1,NULL,0,NULL,NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char)*(iTextLen+1));
	::WideCharToMultiByte(CP_UTF8,0,wstr.c_str(),-1,pElementText,iTextLen,NULL,NULL);
	std::string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

std::string eSDKTool::Unicode2Utf8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}

	std::vector<char> resultstring(utf8size);

	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);

	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}

	return std::string(&resultstring[0]);
}

void eSDKTool::GetNumStringFromCmd(const std::string& _spker, std::string& _spkeNum0, std::string& _spkeNum1)
{
	std::string spker = _spker;
	std::string::size_type pos = spker.find("#");
	if ( pos != std::string::npos )
	{
		_spkeNum0 = spker.substr(0,pos);
		spker = spker.substr(pos+1);
		pos = spker.find("#");
		if ( pos != std::string::npos )
		{
			_spkeNum1 = spker.substr(0,pos);       
		}
	}
	else if ( !spker.empty() )
	{
		_spkeNum0 = spker;
	}
	else
	{
	}
}

bool eSDKTool::CheckString(const std::string strNum1,const std::string& strNum2,std::string& strNum3)
{
	if(strNum1.empty() || strNum2.empty())
	{
		return false;
	}

	std::string substr = strNum2.substr(0,strNum1.length());
	if(substr != strNum1)
	{
		return false;
	}
	else
	{
		strNum3 = strNum2.substr(strNum1.length());
		return true;
	}
}
void eSDKTool::UTCTime2LocalTime(const std::string& _utcdate, const std::string& _utctime, std::string& localdate_, std::string& localtime_)
{
	int year;
	int month;
	int day;
	(void)::sscanf_s(_utcdate.c_str(), "%d-%d-%d", &year, &month, &day);

	int hour;
	int minute;
	int second;
	(void)::sscanf_s(_utctime.c_str(), "%d:%d:%d", &hour, &minute, &second);

	SYSTEMTIME sysTimeUTC;
	memset(&sysTimeUTC, 0, sizeof(SYSTEMTIME));  
	sysTimeUTC.wYear = (WORD)year;
	sysTimeUTC.wMonth = (WORD)month;
	sysTimeUTC.wDay = (WORD)day;
	sysTimeUTC.wHour = (WORD)hour;
	sysTimeUTC.wMinute = (WORD)minute;
	sysTimeUTC.wSecond = (WORD)second;

	SYSTEMTIME sysTimeLocal;
	memset(&sysTimeLocal, 0, sizeof(SYSTEMTIME));

	TIME_ZONE_INFORMATION *lpTimeZone = new TIME_ZONE_INFORMATION;
	(void)GetTimeZoneInformation(lpTimeZone);

	(void)SystemTimeToTzSpecificLocalTime(lpTimeZone,&sysTimeUTC,&sysTimeLocal);//UTC转本地时间

	delete lpTimeZone;

	char strlocaldate_[16];
	(void)::sprintf_s(strlocaldate_, 16, "%04d-%02d-%02d", sysTimeLocal.wYear, sysTimeLocal.wMonth, sysTimeLocal.wDay);
	localdate_ = strlocaldate_;

	char strlocaltime_[16];
	(void)::sprintf_s(strlocaltime_, 16, "%02d:%02d:%02d", sysTimeLocal.wHour, sysTimeLocal.wMinute, sysTimeLocal.wSecond);
	localtime_ = strlocaltime_;

}

int eSDKTool::MakeDir(const std::string &path)
{
	std::wstring wpath = utf82unicode(path);

	return ::_wmkdir(wpath.c_str());
}

bool eSDKTool::RenameFile(const std::string &filepath, const std::string &newfilepath)
{
	return TRUE == ::MoveFileW(
		utf82unicode(filepath).c_str(), utf82unicode(newfilepath).c_str());
}

void eSDKTool::GetFilesInDir(const std::string& _dirPath,std::list<std::string>& _lstFiles)
{
	_finddata_t fileData;
	std::string searchKey = _dirPath + "*";
	intptr_t hFindFile = ::_findfirst(searchKey.c_str(),&fileData);
	if(hFindFile != -1)
	{
		std::string fileName = fileData.name ;
		if(fileName != "." && fileName != "..")
		{
			_lstFiles.push_back(fileName);
		}
		while(::_findnext(hFindFile,&fileData) == 0)
		{
			fileName = fileData.name ;
			if(fileName != "." && fileName != "..")
			{
				_lstFiles.push_back(fileName);
			}
		}
		(void)::_findclose(hFindFile);
	}
}

bool eSDKTool::Access(const std::string &path, int mode)
{
	std::wstring wpath = utf82unicode(path);
	return Access(wpath, mode);

}
bool eSDKTool::Access(const std::wstring &path, int mode)
{

	return (0 == _waccess(path.c_str(), mode));

}

//static 
std::wstring eSDKTool::s_modulePathW;

//static
std::string eSDKTool::s_modulePath;

std::string eSDKTool::GetProgramDir()
{
	(void)GetProgramDirW();

	return s_modulePath;
}
 CString eSDKTool::GetProgramDir1()
{
	static CString modulePath;
	static CString s_moduleDir;

	if (s_moduleDir.IsEmpty())
	{
		if (modulePath.IsEmpty())
		{
			TCHAR szPath[_MAX_PATH];
			//ASSERT(::GetModuleFileName(NULL, szPath, _MAX_PATH) > 0);
			::GetModuleFileName(NULL, szPath, _MAX_PATH);

			modulePath = szPath;
		}

		int leftmostBackslash = modulePath.ReverseFind(L'\\');
		s_moduleDir = modulePath.Left(leftmostBackslash + 1);
	}

	return s_moduleDir;
}

//static
std::wstring eSDKTool::GetProgramDirW()
{

	if (s_modulePathW.empty())
	{
		HMODULE hModule = GetModuleHandle(L"UCService.dll");
		WCHAR szPath[_MAX_PATH + 1] = {0};
		(void)::GetModuleFileNameW(hModule, szPath, _MAX_PATH);

		s_modulePathW = szPath;
		size_t rightmostBackslash = s_modulePathW.rfind(L'\\');
		s_modulePathW = s_modulePathW.substr(0, rightmostBackslash + 1);

		s_modulePath = unicode2utf8(s_modulePathW);
	}

	return s_modulePathW;
}

//static
bool eSDKTool::DeleteFile(const std::string &filepath)
{

	return TRUE == ::DeleteFileW(utf82unicode(filepath).c_str());

}

std::string eSDKTool::num2str(int i)
{
	char str[STRING_LENGTH]= {0};
	sprintf_s(str,STRING_LENGTH-1,"%d",i);
	return std::string(str);
}
#if 0
int eSDKTool::str2num(const std::string& str)
{	
	return atoi(str.c_str());
}
#endif
long long eSDKTool::GetCurUTCTime()
{
	CTime cur = CTime::GetCurrentTime();
	return cur.GetTime()*1000;
}

bool eSDKTool::GetBestHostip(std::string& ip, const std::string& serverip)
{
	DWORD destAddr = inet_addr(serverip.c_str());

	MIB_IPFORWARDROW bestRoute;
	memset(&bestRoute, 0, sizeof(bestRoute));
	if (NO_ERROR != GetBestRoute((DWORD)destAddr, 0, &bestRoute))
	{
		return false;
	}

	MIB_IPADDRTABLE buf;
	PMIB_IPADDRTABLE pIPAddrTable = (MIB_IPADDRTABLE*)&buf;
	if ( !pIPAddrTable )
	{
		return false;
	}

	// Make an initial call to GetIpAddrTable to get the
	// necessary size into the dwSize variable
	DWORD dwSize = 0;
	if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER)
	{
		if ( !pIPAddrTable )
		{
			return false;
		}
	}

	char* strTable = new char[dwSize];
	pIPAddrTable = (MIB_IPADDRTABLE*)strTable;

	// Make a second call to GetIpAddrTable to get the
	// actual data we want
	if ( (GetIpAddrTable( pIPAddrTable, &dwSize, 0 )) != NO_ERROR ) 
	{ 
		return false;
	}

	bool ret = false;
	for (DWORD i=0; i<pIPAddrTable->dwNumEntries; ++i)
	{
		const MIB_IPADDRROW& entry = pIPAddrTable->table[i];
		if (entry.dwIndex == bestRoute.dwForwardIfIndex)
		{
			bool found = false;
			if (0 == bestRoute.dwForwardNextHop)
				found = (entry.dwAddr&bestRoute.dwForwardMask) == (bestRoute.dwForwardDest&bestRoute.dwForwardMask);
			else
				found = (entry.dwAddr&entry.dwMask) == (bestRoute.dwForwardNextHop&entry.dwMask);
			if (found)
			{
				char * ipaddr = NULL;
				const unsigned IPLENGTH = 20;//ip 字符串长度
				char addr[IPLENGTH]={0};
				in_addr inaddr;
				inaddr.s_addr=entry.dwAddr;
				ipaddr = inet_ntoa(inaddr);
				strcpy_s(addr,IPLENGTH,ipaddr);  
				if (strcmp(addr,"0.0.0.0") !=0  && strcmp(addr,"127.0.0.1") !=0)
				{
					ip = addr;
					ret = true;
				}
			}
		}
	}

	delete[] strTable;
	return ret;
}


// 过滤sip号码头 "SIP::"
std::string eSDKTool::ParsePhoneNo(const std::string& uri)
{
	//从uri解析号码，若非uri返回号码
	std::string::size_type pos1 = uri.find("sip:");

	if(pos1!= std::string::npos)
	{
		//去除@tedesktop和 sip:
		std::string::size_type pos2 = uri.rfind("@tedesktop");
		std::string strDomainUri = "";
		if(pos2 != std::string::npos)
		{
			strDomainUri = uri.substr(pos1+4, pos2-pos1-4);
		}
		else
		{
			strDomainUri = uri.substr(pos1+4);
		}

		std::string::size_type pos3 = strDomainUri.find("@");
		//如果还能找到@，判断@后面是ip还是域名，是IP的去除后返回
		if(pos3 != std::string::npos)
		{
			if (IsValidIP_V4(strDomainUri.substr(pos3 + 1)))
			{
				return strDomainUri.substr(0 ,pos3);
			}
			else 
			{
				return strDomainUri;
			}
		}
		else
		{
			return strDomainUri;
		}
	}
	else
	{
		return uri;
	}
}

// 检查Email格式是否正确
BOOL eSDKTool::IsValidEmailFormat(const std::string &strEmail)	  
{
	// 导入文件邮箱可以为空
	if (strEmail.empty())
	{
		return TRUE;
	}

	// 长度至少5 不超过 100
	const wstring tstrEmail = eSDKTool::utf8_2_unicode_w(strEmail);
	const ctk::size_type minEmailLen = 5;
	if( ((strEmail.length() < minEmailLen)) || (tstrEmail.size() > 100))
	{
		return FALSE;
	}

	char ch = strEmail[0];

	// 第一个字符必须是26个大、小写字母或者数字
	if( !(((ch >= 'a') && (ch <= 'z'))
		|| ((ch >= 'A') && (ch <= 'Z'))
		|| ((ch >= '0') && (ch <= '9'))) )
	{
		return FALSE;
	}

	int atCount = 0;
	int dotCount = 0;
	for(ctk::size_type i = 1; i < strEmail.length(); ++i) //0已经判断过了，从1开始
	{
		ch = strEmail[i];
		if(!eSDKTool::IsValidEmailChar(ch))
		{
			return FALSE;
		}

		if('@' == ch)
		{
			++atCount;
		}
		else if( (atCount > 0) && (ch == '.') )//@符号后的"."号
		{
			++dotCount;
		}
	}

	// 结尾不得是字符“@”或者“.”
	if( '.' == ch || '@' == ch )
	{
		return FALSE;
	}

	// 条件判断含义：必须包含一个并且只有 1 个符号“@”，同时@后必须包含至少一个至多 3 个符号“.”
	if( (atCount != 1) || (dotCount < 1) || (dotCount > 3) )
	{
		return FALSE;
	}
	// 不允许出现“@.”或者“.@”
	const ctk::size_type x = strEmail.find("@.");
	const ctk::size_type y = strEmail.find(".@");
	if( x != std::string::npos || y != std::string::npos )
	{
		return FALSE;
	}

	return TRUE;
}

// 检查油箱字符是否符合规范
BOOL eSDKTool::IsValidEmailChar(const char ch)
{
	// 邮箱合法字符包括：26个大/小写字母、数字或'-'、'_'、'@'
	if( (ch >= 'a') && (ch <= 'z')
		|| (ch >= 'A') && (ch <= 'Z')
		|| (ch >= '0') && (ch <= '9')
		|| ( ch == '-' || ch == '_' || ch == '.' || ch == '@' ))
	{
		return true;
	}

	return false;
}


bool eSDKTool::IsValidIP_V4(const std::string &ip)
{
	//IPV4最大长度：255.255.255.255，即15个字符
	if (/*ip.empty() || */ip.size() > 15)
	{
		return false;
	}

	unsigned int pointNum = 0;          //'.'的个数
	const unsigned int maxPointNum = 3; //'.'的最大数量为3个

	string::size_type start = 0;

	for (unsigned int i = 0; i <= maxPointNum; ++i)
	{
		string tmpBuf = "";
		string::size_type loc = ip.find(".", start);
		if (loc != string::npos && i < maxPointNum)
		{
			tmpBuf = ip.substr(start, loc - start);
			start = loc + 1;
			++pointNum;
		}

		if (loc == string::npos || i >= maxPointNum)
		{
			tmpBuf = ip.substr(start);
		}

		for(unsigned int j = 0; j < tmpBuf.size(); ++j)
		{
			if ( ((tmpBuf.size() > 1) && ((tmpBuf.at(0) > '9') || (tmpBuf.at(0) < '1'))) //第一个数字范围1～9
				|| ((tmpBuf.at(j) > '9') || (tmpBuf.at(j) < '0')) ) //数字范围0～9
			{
				return false;
			}
		}

		int num = atoi(tmpBuf.c_str());
		if ( (num > 255)//地址每个子段不会超过255
			|| (num < 0)//地址每个子段不会小于0
			|| ((num == 0) && (tmpBuf != "0")) ) //tmpBuf == ""时转换得到的数字为0
		{
			return false;
		}
	}

	if (pointNum != maxPointNum)
	{
		return false;
	}

	return true;
}

bool eSDKTool::IsEmptyUri(const std::string& uri)
{
	string::size_type nSip = uri.find("sip:@");
	if (string::npos == nSip) 
	{
		return false;
	}
	return true;
}
#if 0
// 判断是否合法URI，有sip:
bool eSDKTool::IsValidUri(const std::string& uri)
{
	size_t nSip = uri.find("sip:");
	if (nSip != 0) 
	{
		return false;
	}
	return true;
}

std::string eSDKTool::GetNoFromUri(const std::string & uri)
{
	//从uri解析号码，若非uri返回号码
	std::string::size_type pos1 = uri.find("sip:");

	if(pos1!= std::string::npos)
	{
		//对于"号码@ip地址"的场景之前不兼容
		std::string::size_type pos2 = uri.rfind("@");
		//std::string::size_type pos2 = uri.find("@");
		if(pos2 != std::string::npos)
		{
			if(4 == pos2)
			{
				return "";
			}
			else
			{
				return uri.substr(pos1+4, pos2-pos1-4);
			}
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
#endif