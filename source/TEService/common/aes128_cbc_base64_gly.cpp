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
#include "aes128_cbc_base64_gly.h"
#include "base64_gly.h"
#include "aes128_cbc_gly.h"

#if defined (AES_BLOCK_SIZE)
#undef AES_BLOCK_SIZE
#endif

#define AES_BLOCK_SIZE      16

int AES128_CBC_BASE64_Encode_GLY(
    char         * pszHex,    // ���������16 ���Ʊ��������
    unsigned int * puiLen,    // *puiLen������������������룺���� pszHex ��
                              //   ��С�������16 ���Ʊ�������ĵĳ��ȣ�����������
    const char   * pszPlain,  // �������������
    unsigned int   uiDataLen, // ������������ĵĳ���
                              //   Ϊ 0 ʱ���� pszData Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    const char   * pszKey,    // �����������Կ
    unsigned int   uiKeyLen,  // �����������Կ�ĳ���
                              //   Ϊ 0 ʱ���� pszKey Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    const char   * pszIV,     // �����������ʼ����
    unsigned int   uiIVLen    // �����������ʼ�����ĳ���
                              //   Ϊ 0 ʱ���� pszIV Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    ) // 0���ɹ���������ʧ��
{
    char       * l_pszCipher = NULL;
    unsigned int l_uiLen;
    int          l_iResult;

    if (   (pszHex   == NULL)
        || (puiLen   == NULL)
        || (*puiLen  == 0   )
        || (pszPlain == NULL)
        || (pszKey   == NULL)
        )
    {
        return -9999;
    }

    if (uiDataLen == 0)
    {
        uiDataLen = (unsigned int)strlen(pszPlain);
    }

    if (uiKeyLen == 0)
    {
        uiKeyLen = (unsigned int)strlen(pszKey);
    }

    if (   (uiDataLen == 0)
        || (uiKeyLen  == 0)
        )
    {
        return -9998;
    }

    l_uiLen = ((uiDataLen / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;

    if (*puiLen < (((l_uiLen / 3) + (((l_uiLen % 3) == 0) ? 0 : 1)) * 4 + 1))
    {
        return -9997;
    }

    l_pszCipher = (char *)malloc(l_uiLen);

    if (l_pszCipher == NULL)
    {
        return -9996;
    }

    l_iResult = AES128_CBC_Encode_GLY(
        l_pszCipher,
        &l_uiLen,
        pszPlain,
        uiDataLen,
        pszKey,
        uiKeyLen,
        pszIV,
        uiIVLen
        );

    if (l_iResult == 0)
    {
        l_iResult = BASE64_Encode_GLY(pszHex, puiLen, l_pszCipher, l_uiLen);
    }

    free(l_pszCipher);

    return l_iResult;
}

int AES128_CBC_BASE64_Decode_GLY(
    char         * pszPlain, // �������������
    unsigned int * puiLen,   // *puiLen������������������룺���� pszPlain ��
                             //   ��С����������ĵĳ���
    const char   * pszHex,   // ���������16 ���Ʊ��������
    unsigned int   uiHexLen, // ���������16 ���Ʊ�������ĵĳ��ȣ�������������
                             //   Ϊ 0 ʱ���� pszHex Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    const char   * pszKey,   // �����������Կ
    unsigned int   uiKeyLen, // �����������Կ�ĳ���
                             //   Ϊ 0 ʱ���� pszKey Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    const char   * pszIV,     // �����������ʼ����
    unsigned int   uiIVLen    // �����������ʼ�����ĳ���
                              //   Ϊ 0 ʱ���� pszIV Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    ) // 0���ɹ���������ʧ��
{
    char       * l_pszData;
    unsigned int l_uiLen;
    int          l_iResult;

    if (   (pszPlain == NULL)
        || (puiLen   == NULL)
        || (*puiLen  == 0   )
        || (pszHex   == NULL)
        || (pszKey   == NULL)
        )
    {
        return -9999;
    }

    if (uiHexLen == 0)
    {
        uiHexLen = (unsigned int)strlen(pszHex);
    }

    if (uiKeyLen == 0)
    {
        uiKeyLen = (unsigned int)strlen(pszKey);
    }

    if (   (uiHexLen == 0)
        || (uiKeyLen == 0)
        )
    {
        return -9998;
    }

    if ((uiHexLen % 4) != 0)
    {
        return -9997;
    }

    l_uiLen = (uiHexLen * 3) / 4;

    l_pszData = (char *)malloc(l_uiLen);

    if (l_pszData == NULL)
    {
        return -9996;
    }

    l_iResult = BASE64_Decode_GLY(l_pszData, &l_uiLen, pszHex, uiHexLen);

    if (l_iResult == 0)
    {
        l_iResult = AES128_CBC_Decode_GLY(
            pszPlain,
            puiLen,
            l_pszData,
            l_uiLen,
            pszKey,
            uiKeyLen,
            pszIV,
            uiIVLen
            );
    }

    free(l_pszData);

    return l_iResult;
}
