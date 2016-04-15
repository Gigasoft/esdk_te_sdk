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
    char         * pszHex,    // 输出参数，16 进制编码的密文
    unsigned int * puiLen,    // *puiLen，输入输出参数，输入：缓存 pszHex 的
                              //   大小，输出：16 进制编码的密文的长度，包括结束符
    const char   * pszPlain,  // 输入参数：明文
    unsigned int   uiDataLen, // 输入参数：明文的长度
                              //   为 0 时，当 pszData 为字符串，自动取该字符串的长度
    const char   * pszKey,    // 输入参数：密钥
    unsigned int   uiKeyLen,  // 输入参数：密钥的长度
                              //   为 0 时，当 pszKey 为字符串，自动取该字符串的长度
    const char   * pszIV,     // 输入参数：初始向量
    unsigned int   uiIVLen    // 输入参数：初始向量的长度
                              //   为 0 时，当 pszIV 为字符串，自动取该字符串的长度
    ) // 0：成功，其它：失败
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
    char         * pszPlain, // 输出参数，明文
    unsigned int * puiLen,   // *puiLen，输入输出参数，输入：缓存 pszPlain 的
                             //   大小，输出：明文的长度
    const char   * pszHex,   // 输入参数：16 进制编码的密文
    unsigned int   uiHexLen, // 输入参数：16 进制编码的密文的长度，不包括结束符
                             //   为 0 时，当 pszHex 为字符串，自动取该字符串的长度
    const char   * pszKey,   // 输入参数：密钥
    unsigned int   uiKeyLen, // 输入参数：密钥的长度
                             //   为 0 时，当 pszKey 为字符串，自动取该字符串的长度
    const char   * pszIV,     // 输入参数：初始向量
    unsigned int   uiIVLen    // 输入参数：初始向量的长度
                              //   为 0 时，当 pszIV 为字符串，自动取该字符串的长度
    ) // 0：成功，其它：失败
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
