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
 * @file  minidmp.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief mini dump tool
 * @details dump function
 * @author p00327183
 * @version 1.0
 * @date 2015-07-08    
 * @history  v1.1 2015-07-08 Init TE Desktop SDK 
****************************************************/

#ifndef _MINIDUMP_H_
#define _MINIDUMP_H_
#include <windows.h>
#include <imagehlp.h>
#include <stdlib.h>
#include <string>
#pragma comment(lib, "dbghelp.lib")

BOOL IsDataSectionNeeded(const WCHAR* pModuleName);
BOOL CALLBACK MiniDumpCallback(PVOID, const PMINIDUMP_CALLBACK_INPUT pInput, PMINIDUMP_CALLBACK_OUTPUT pOutput);
void CreateMiniDump(EXCEPTION_POINTERS* pep, std::string strFileName);

#endif

