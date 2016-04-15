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
/*******************************************************************************
* Author: Lianyang Gong                                                        *
*   Date: 2011-03-17                                                           *
*******************************************************************************/
#include "stdafx.h"
#include "base64_gly.h"

static char ReturnToData(char cChar);

int BASE64_Encode_GLY(
    char         * pszBase64, // 输出参数，保存 Base64 编码结果
    unsigned int * puiLen,    // *puiLen，输入输出参数，输入：缓存 pszBase64 的
                              //   大小，输出：字符串的大小，包括结束符
    const char   * pszData,   // 输入参数：数据
    unsigned int   uiDataLen  // 输入参数：数据的长度
                              //   为 0 时，当 pszData 为字符串，自动取该字符串的长度
    ) // 0：成功，其它：失败
{
    int           l_iFlag;
    unsigned int  l_iGroup;
    unsigned int  ii;
    unsigned int  jj;
    unsigned int  kk;
    unsigned char l_uszTmp[3];
    char          l_szEncoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    if (   (pszBase64 == NULL)
        || (puiLen    == NULL)
        || (*puiLen   == 0   )
        || (pszData   == NULL)
        )
    {
        return -1;
    }

    if (uiDataLen == 0)
    {
        uiDataLen = (unsigned int)strlen(pszData);
    }

    if (uiDataLen == 0)
    {
        return -2;
    }

    l_iGroup = uiDataLen / 3;

    ii = l_iGroup;

    l_iFlag = uiDataLen % 3;

    if (l_iFlag != 0)
    {
        ii++;
    }

    ii *= 4;
    ii++; // 需要包括字符串结束符

    if (*puiLen < ii)
    {
        return -3;
    }

    *puiLen = ii;

    pszBase64[ii - 1] = (char)0x00;

    for (ii = 0, jj = 0, kk = 0; ii < l_iGroup; ii++)
    {
        l_uszTmp[0] = pszData[kk++];
        l_uszTmp[1] = pszData[kk++];
        l_uszTmp[2] = pszData[kk++];

        pszBase64[jj++] = l_szEncoding[  l_uszTmp[0] >> 2];
        pszBase64[jj++] = l_szEncoding[((l_uszTmp[0] & 0x03) << 4) | (l_uszTmp[1] >> 4)];
        pszBase64[jj++] = l_szEncoding[((l_uszTmp[1] & 0x0F) << 2) | (l_uszTmp[2] >> 6)];
        pszBase64[jj++] = l_szEncoding[  l_uszTmp[2] & 0x3F];
    }

    if (l_iFlag != 0)
    {
        l_uszTmp[0] = pszData[kk++];

        pszBase64[jj ++ ] = l_szEncoding[l_uszTmp[0] >> 2];
        pszBase64[jj + 1] = '=';
        pszBase64[jj + 2] = '=';

        if ((uiDataLen % 3) == 1)
        {
            pszBase64[jj] = l_szEncoding[(l_uszTmp[0] & 0x03) << 4];
        }
        else // if ((uiDataLen % 3) == 2)
        {
            l_uszTmp[1] = pszData[kk];

            pszBase64[jj++] = l_szEncoding[((l_uszTmp[0] & 0x03) << 4) | (l_uszTmp[1] >> 4)];
            pszBase64[jj  ] = l_szEncoding[ (l_uszTmp[1] & 0x0F) << 2];
        }
    }

    return 0;
}

int BASE64_Decode_GLY(
    char         * pszData,    // 输出参数，保存 Base64 解码结果
    unsigned int * puiLen,     // *puiLen，输入输出参数，输入：缓存 pszData 的大小，
                               //   输出：Base64 解码结果的大小
    const char   * pszBase64,  // 输入参数：Base64 编码的字符串
    unsigned int   uiBase64Len // 输入参数：Base64 编码的字符串的长度
                               //   为 0 时，自动取 Base64 编码的字符串的长度
    ) // 0：成功，其它：失败
{
    int           l_iFlag;
    unsigned int  l_iGroup;
    unsigned int  ii;
    unsigned int  jj;
    unsigned int  kk;
    unsigned char l_uszTmp[4];

    if (   (pszData   == NULL)
        || (puiLen    == NULL)
        || (*puiLen   == 0   )
        || (pszBase64 == NULL)
        )
    {
        return -1;
    }

    if (uiBase64Len == 0)
    {
        uiBase64Len = (unsigned int)strlen(pszBase64);
    }

    if (uiBase64Len == 0)
    {
        return -2;
    }

    if ((uiBase64Len % 4) != 0)
    {
        return -3;
    }

    l_iGroup = uiBase64Len / 4;
    ii       = l_iGroup * 3;

    l_iFlag = 0;

    if (pszBase64[uiBase64Len - 1] == '=')
    {
        uiBase64Len--;
                 ii--;
           l_iGroup--;
            l_iFlag++;

        if (pszBase64[uiBase64Len - 1] == '=')
        {
            uiBase64Len--;
                     ii--;
        }
    }

    if (*puiLen < ii)
    {
        return -4;
    }

    *puiLen = ii;

    for (ii = 0; ii < uiBase64Len; ii++)
    {
        if (!( (pszBase64[ii] == '+')
            || (('/' <= pszBase64[ii]) && (pszBase64[ii] <= '9'))
            || (('A' <= pszBase64[ii]) && (pszBase64[ii] <= 'Z'))
            || (('a' <= pszBase64[ii]) && (pszBase64[ii] <= 'z'))
            ))
        {
            return -5;
        }
    }

    for (ii = 0, jj = 0, kk = 0; ii < l_iGroup; ii++)
    {
        l_uszTmp[0] = (unsigned char)ReturnToData(pszBase64[kk++]);
        l_uszTmp[1] = (unsigned char)ReturnToData(pszBase64[kk++]);
        l_uszTmp[2] = (unsigned char)ReturnToData(pszBase64[kk++]);
        l_uszTmp[3] = (unsigned char)ReturnToData(pszBase64[kk++]);

        pszData[jj++] = (l_uszTmp[0] << 2) | (l_uszTmp[1] >> 4);
        pszData[jj++] = (l_uszTmp[1] << 4) | (l_uszTmp[2] >> 2);
        pszData[jj++] = (l_uszTmp[2] << 6) | (l_uszTmp[3] & 0x3F);
    }

    if (l_iFlag != 0)
    {
        l_uszTmp[0] = (unsigned char)ReturnToData(pszBase64[kk++]);
        l_uszTmp[1] = (unsigned char)ReturnToData(pszBase64[kk++]);

        pszData[jj++] = (l_uszTmp[0] << 2) | (l_uszTmp[1] >> 4);

        if ((uiBase64Len % 4) == 3)
        {
            l_uszTmp[2]  = (unsigned char)ReturnToData(pszBase64[kk]);

            pszData[jj] = (l_uszTmp[1] << 4) | (l_uszTmp[2] >> 2);
        }
    }

    return 0;
}

static char ReturnToData(char cChar) // cChar 的合法性由 decode 中的代码保证了
{
    if (('A' <= cChar) && (cChar <= 'Z'))
    {
        cChar -= 'A';
    }
    else if (('a' <= cChar) && (cChar <= 'z'))
    {
        cChar -= 'a';
        cChar += 26;
    }
    else if (('0' <= cChar) && (cChar <= '9'))
    {
        cChar -= '0';
        cChar += 52;
    }
    else if (cChar == '+')
    {
        cChar = 62;
    }
    else // if (cChar == '/')
    {
        cChar = 63;
    }

    return cChar;
}
