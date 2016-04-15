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
    char         * pszBase64, // ������������� Base64 ������
    unsigned int * puiLen,    // *puiLen������������������룺���� pszBase64 ��
                              //   ��С��������ַ����Ĵ�С������������
    const char   * pszData,   // �������������
    unsigned int   uiDataLen  // ������������ݵĳ���
                              //   Ϊ 0 ʱ���� pszData Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    ) // 0���ɹ���������ʧ��
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
    ii++; // ��Ҫ�����ַ���������

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
    char         * pszData,    // ������������� Base64 ������
    unsigned int * puiLen,     // *puiLen������������������룺���� pszData �Ĵ�С��
                               //   �����Base64 �������Ĵ�С
    const char   * pszBase64,  // ���������Base64 ������ַ���
    unsigned int   uiBase64Len // ���������Base64 ������ַ����ĳ���
                               //   Ϊ 0 ʱ���Զ�ȡ Base64 ������ַ����ĳ���
    ) // 0���ɹ���������ʧ��
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

static char ReturnToData(char cChar) // cChar �ĺϷ����� decode �еĴ��뱣֤��
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
