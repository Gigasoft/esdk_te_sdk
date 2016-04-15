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
/********************************************************************
created:	2012/09/30
filename: 	LangResManager.h
file path:	WinGUI\src\CommLib
author:		xkf78311

purpose:	������֧��
*********************************************************************/
#pragma once
#include <map>
#include <string>
#include "ctk/util/singleton_T.h"
#include "ctk/ctk_config.h"

//���嵥ʵ��
#ifndef DECL_SINGLETON
#define DECL_SINGLETON(cls) \
  public: \
  static cls * Instance() {return ctk::Singleton_T<cls>::instance(CTK_CURRENT);} \
  static void Destroy() {ctk::Singleton_T<cls>::destroy();}
#endif

class  LangResManager
{
public:
  typedef std::map<std::wstring, std::wstring> LANG_MAP;

  LangResManager();

  DECL_SINGLETON(LangResManager);

public:
  // ���ļ���������
  std::wstring ReadLangCode();
  // д�����뵽�ļ�
  void WriteLangCode(const std::wstring & lang);

  // ���ʵ�ǰ���õ�������
  void SetLangCode(const std::wstring & lang)
  { m_langCode = lang; }
  std::wstring GetLangCode() const
  { return m_langCode; }

public:
  // ����������Դ
  bool ReloadLangRes();

  // ��ȡ��ֵ
  std::wstring GetValue(const std::wstring & key);

private:
  // ����Ŀ¼
  CString m_programDir;
  // �������ļ�
  CString m_languageTxt;

  // ���Դ��룺����"2052", Ӣ��"1033"
  std::wstring m_langCode;

  // ��ǰ���Ե�(key, value)����
  LANG_MAP m_langMap;

};

#define LANGRESMGR() (LangResManager::Instance())
#define LANG(key) (LANGRESMGR()->GetValue(L#key))
