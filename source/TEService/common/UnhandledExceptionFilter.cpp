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
 * @file  UnhandledExceptionFilter.cpp
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief handle exception tool
 * @details handle exception function
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK 
****************************************************/
#include "stdafx.h"
#include "minidmp.h"
#include "Log.h"
#include "eSDKTool.h"

LONG WINAPI GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	//得到当前时间
	WARN_LOG("dump happped");
	SYSTEMTIME st;
	::GetLocalTime(&st);
	std::string strPath;
	eSDKTool::getCurrentPath(strPath);
	const int PATH_LENGTH = 2048;
	char szFileName[PATH_LENGTH]={0};
	(void)sprintf_s(szFileName,(PATH_LENGTH-1),"%s\\core-%04d%02d%02d-%02d%02d-%02d-%02d.dmp",strPath.c_str(), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	CreateMiniDump(pExceptionInfo, szFileName);
	//std::cerr << "unknown error：" << (*pExceptionInfo->ExceptionRecord) << std::endl;
	exit((int)(pExceptionInfo->ExceptionRecord->ExceptionCode));
}

