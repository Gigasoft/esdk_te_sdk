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
// LangResManager.cpp 
//
#include "stdafx.h"
//#include "CommonMacros.h"
#include "LangResManager.h"
#include "Log.h"
#include "eSDKTool.h"
//#include "FilePathUtil.h"
/*lint -save -e10 -e40 -e49 -e59 -e63 -e64 -e78 -e129 -e534*/
LangResManager::LangResManager()
{
    m_programDir = eSDKTool::GetProgramDir1();
    m_languageTxt = m_programDir + _T("language.txt");
}

std::wstring LangResManager::ReadLangCode()
{
    std::wifstream infile(m_languageTxt.GetString());

    std::wstring langCode;
    if (infile)
    {
        infile >> langCode;
    }
    return langCode;
}

void LangResManager::WriteLangCode(const std::wstring & lang)
{
    std::wofstream outfile(
        m_languageTxt.GetString(), ios::out | ios_base::trunc);

    if (outfile)
    {
        outfile << lang;
    }
}

bool LangResManager::ReloadLangRes()
{
   /* DEBUG_LOG("%s",m_langCode);*/

    CString searchDir = m_programDir + _T("language\\");
    searchDir.Append( m_langCode.c_str() );
    searchDir.Append( _T("\\*.elp") );
	if(!m_langMap.empty())
	{
		m_langMap.clear();
	}

    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(searchDir, &fd);

    if ( hFind == INVALID_HANDLE_VALUE )
    {
        return false;
    }
    do
    {
        CString folderName = fd.cFileName;
        if ( folderName != _T(".") && folderName != _T("..") )
        {
            CString path = m_programDir + _T("language\\");
            path.Append( m_langCode.c_str() );
            path.Append( _T("\\") );
            path.Append(folderName);

            // 打开语言文件，以二进制方式读取
        //    INFO_PARAM1(path);
            std::ifstream infs( path, ios::binary );
            if (!infs.is_open())
            {
                WARN_LOG("can not open file : " );
                continue;
            }

            // 获取filebuf对象的指针，调用filebuf对象方法获取文件大小
            filebuf * pbuf = infs.rdbuf();
            long sz = pbuf->pubseekoff(0, ios::end, ios::in);
            pbuf->pubseekpos(0, ios::in);

            // 分配内存空间，读取文件内容到缓存中
            char * buffer(new char[sz + 2]);
            pbuf->_Sgetn_s(buffer, sz, sz);
            buffer[sz] = buffer[sz + 1] = 0;

            // 内容已读出，可以关闭语言文件
            infs.close();

            // 将缓存中的数据拷贝包装在wstringstream里，释放缓存
            std::wistringstream wistrstr((wchar_t *)buffer);
            delete [] buffer;

            // 解析文件内容
            std::wstring line;
            while ( getline(wistrstr, line) )
            {
                eSDKTool::trim(line);

                if (line.empty())
                {
                    continue;
                }
                std::wstring::size_type pos = line.find( L'=' );
                if ( pos == std::wstring::npos ) 
                {
                    continue;
                }
                std::wstring key  = line.substr(0, pos);
                std::wstring val = line.substr(pos + 1);
                eSDKTool::trim(key);
                eSDKTool::trim(val);

                if (key.empty()) { // 空key忽略
                    WARN_LOG( "empty key in line " );
                    continue;
                }

                if (val.empty()) // 空val
                {
                    WARN_LOG( "empty val in line " );
                }
                if (m_langMap.end() != m_langMap.find(key)) // 重复的key
                {
                    WARN_LOG("reduplicated language key : " );
                }
                m_langMap.insert(
                    LANG_MAP::value_type(key, val)
                    );
            }
        }

    } while ( ::FindNextFile(hFind, &fd) );

    (void)::FindClose(hFind);

    return true;
}

std::wstring LangResManager::GetValue(const std::wstring & key)
{
    std::wstring strRet;

    LANG_MAP::iterator pos = m_langMap.find(key);
    if ( pos != m_langMap.end() )
    {
        strRet = pos->second;
    }
    else
    {
        WARN_LOG( "empty language string : ");
    }

    return strRet;
}
/*lint -restore*/