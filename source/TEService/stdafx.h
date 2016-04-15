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

// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include "ctk/ctk.h"
#include "hwuc/HWUC.h"
#include "history/history.h"
#include "tup/call_def.h"
using namespace uc::model; 
using namespace uc::model::historydata;
using namespace sigslot;
using namespace uc::model::conversation;
using namespace uc::model::conference;
#include <windows.h>
#include "TESDK.h"
#include "eSDKTool.h"
#include "UnhandledExceptionFilter.h"




//ҵ��궨��

#ifndef UCCLIENT
#define UCCLIENT() (uc::model::UCClient::GetClient())
#endif

#ifndef UCSELF
#define UCSELF() (UCCLIENT()->Self)
#endif

#ifndef UCSELFSTATUS
#define UCSELFSTATUS() (UCSELF()->selfStatus)
#endif

#ifndef UCSELFDESC
#define UCSELFDESC() (UCSELF()->selfStatusDesc)
#endif

#ifndef UCSELFINFO
#define UCSELFINFO() (UCCLIENT()->Self->selfInfo)
#endif

#ifndef USERCONFIG
#define USERCONFIG() (UCSELF()->simplecfg_)
#endif

#ifndef SYSCONFIG
#define SYSCONFIG() (UCCLIENT()->SysConfig)
#endif

#ifndef SIGNINCONFIG
#define SIGNINCONFIG() (UCCLIENT()->SignConfig)
#endif

#ifndef CONTACTMGR
#define CONTACTMGR() (UCCLIENT()->ContactManager)
#endif

#ifndef CONTACTSUBMGR
#define CONTACTSUBMGR() (UCCLIENT()->ContactSubManager)
#endif

#ifndef ENTADDRMGR
#define ENTADDRMGR() (UCCLIENT()->EntAddrbookManager_)
#endif

#ifndef FAVMGR
#define FAVMGR() (UCCLIENT()->FavouriteManager)
#endif

#ifndef DEVICEMGR
#define DEVICEMGR() (UCCLIENT()->DeviceManager)
#endif

#ifndef CONVMGR
#define CONVMGR() (UCCLIENT()->ConvManager)
#endif

#ifndef PERM
#define PERM(t) (UCSELF()->HasPermission(t))
#endif

#ifndef FEAT
#define FEAT(t) (UCSELF()->HasFeatrueFlag(t)) 
#endif


#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

#import "../../../platform/TE/import/Excel/MSO.DLL" rename("RGB", "RGBXL") rename("SearchPath", "SearchPathXL")
#import "../../../platform/TE/import/Excel/VBE6EXT.OLB"
#import "../../../platform/TE/import/Excel/EXCEL.EXE" rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") \
	rename("CopyFile", "CopyFileXL") rename("ReplaceText", "ReplaceTextXL") \
	rename("DocumentProperties", "DocumentPropertiesXL") exclude("IFont","IPicture")


#import "../../../platform/TE/import/Excel/MSOUTL.OLB" no_namespace  exclude("_IRecipientControl", "_DRecipientControl")\
	rename("CopyFile", "CopyFileOL")   rename("Folder", "FolderOL") exclude("_OlkTextBox","_OlkLabel","_OlkCommandButton","_OlkCheckBox","_OlkOptionButton","_OlkComboBox","_OlkListBox","_OlkDateControl","_OlkTimeControl" ,"_OlkFrameHeader")