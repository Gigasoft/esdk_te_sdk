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
#include "aes128_cbc_gly.h"
#include "hwsecure/securec.h"
#include "sec_crypto.h"

#if defined (AES_BLOCK_SIZE)
#undef AES_BLOCK_SIZE
#endif
#if defined (AES_128_KEY_SIZE)
#undef AES_128_KEY_SIZE
#endif

#define AES_BLOCK_SIZE      16
#define AES_128_KEY_SIZE    16

int AES128_CBC_Encode_GLY(
    char         * pszCipher, // 输出参数，密文（乱码）
    unsigned int * puiLen,    // *puiLen，输入输出参数，输入：缓存 pszCipher 的
                              //   大小，输出：密文的长度
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
    char       l_szIV[AES_BLOCK_SIZE];
    unsigned int l_uiAlgID;
    char       l_szKey[AES_128_KEY_SIZE];

    if (   (pszCipher == NULL)
        || (puiLen    == NULL)
        || (*puiLen   == 0   )
        || (pszPlain  == NULL)
        || (pszKey    == NULL)
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

    if (*puiLen < (((uiDataLen / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE))
    {
        return -9997;
    }

    //memset(l_szKey, 0, AES_128_KEY_SIZE);
	//hwsecure
	hw::memset_s(l_szKey, AES_128_KEY_SIZE, 0, AES_128_KEY_SIZE);
	hw::memcpy_s(
        l_szKey,sizeof(l_szKey),
        pszKey,
        (uiKeyLen < AES_128_KEY_SIZE) ? uiKeyLen : AES_128_KEY_SIZE
        );

    //memset(l_szIV, 0, AES_BLOCK_SIZE);
	//hwsecure
	hw::memset_s(l_szIV, AES_BLOCK_SIZE, 0, AES_BLOCK_SIZE);

    if (pszIV != NULL)
    {
        if (uiIVLen == 0)
        {
            uiIVLen = (unsigned int)strlen(pszIV);
        }

		hw::memcpy_s(l_szIV, sizeof(l_szIV), pszIV, (uiIVLen < AES_BLOCK_SIZE) ? uiIVLen : AES_BLOCK_SIZE);
    }

    l_uiAlgID = ALGID_AES128_CBC;

    CRYPT_SET_PAD_MODE(l_uiAlgID, BLOCK_PADDING_NORMAL);

    return (int)CRYPT_encrypt(
        (SEC_UINT32  )l_uiAlgID,
        (SEC_UCHAR  *)l_szKey,
        (SEC_UINT32  )AES_128_KEY_SIZE,
        (SEC_UCHAR  *)l_szIV,
        (SEC_UINT32  )AES_BLOCK_SIZE,
        (SEC_UCHAR  *)pszPlain,
        (SEC_UINT32  )uiDataLen,
        (SEC_UCHAR  *)pszCipher,
        (SEC_UINT32 *)puiLen
        );
}

int AES128_CBC_Decode_GLY(
    char         * pszPlain,  // 输出参数，明文
    unsigned int * puiLen,    // *puiLen，输入输出参数，输入：缓存 pszPlain 的
                              //   大小，输出：明文的长度
    const char   * pszCipher, // 输入参数：密文
    unsigned int   uiDataLen, // 输入参数：密文的长度
                              //   为 0 时，当 pszCipher 为字符串，自动取该字符串的长度
    const char   * pszKey,    // 输入参数：密钥
    unsigned int   uiKeyLen,  // 输入参数：密钥的长度
                              //   为 0 时，当 pszKey 为字符串，自动取该字符串的长度
    const char   * pszIV,     // 输入参数：初始向量
    unsigned int   uiIVLen    // 输入参数：初始向量的长度
                              //   为 0 时，当 pszIV 为字符串，自动取该字符串的长度
    ) // 0：成功，其它：失败
{
    char       * l_pszData = NULL;
    char         l_szIV[AES_BLOCK_SIZE];
    unsigned int l_uiLen;
    int          l_iResult;
    SEC_UINT32   l_uiAlgID;
    char         l_szKey[AES_128_KEY_SIZE];

    if (   (pszPlain  == NULL)
        || (puiLen    == NULL)
        || (*puiLen   == 0   )
        || (pszCipher == NULL)
        || (pszKey    == NULL)
        )
    {
        return -9999;
    }

    if (uiDataLen == 0)
    {
        uiDataLen = (unsigned int)strlen(pszCipher);
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

    if ((uiDataLen % AES_BLOCK_SIZE) != 0)
    {
        return -9997;
    }

    l_uiLen = uiDataLen; // 至少要和明文一样长，CRYPT_decrypt 内部需要，不知为什么

    l_pszData = (char *)malloc(l_uiLen + 1);

    if (l_pszData == NULL)
    {
        return -9996;
    }

    //memset(l_szKey, 0, AES_128_KEY_SIZE);
	//hwsecure
	hw::memset_s(l_szKey, AES_128_KEY_SIZE, 0, AES_128_KEY_SIZE);
	hw::memcpy_s(
        l_szKey,sizeof(l_szKey),
        pszKey,
        (uiKeyLen < AES_128_KEY_SIZE) ? uiKeyLen : AES_128_KEY_SIZE
        );

    //memset(l_szIV, 0, AES_BLOCK_SIZE);
	//hwsecure
	hw::memset_s(l_szIV, AES_BLOCK_SIZE, 0, AES_BLOCK_SIZE);

    if (pszIV != NULL)
    {
        if (uiIVLen == 0)
        {
            uiIVLen = (unsigned int)strlen(pszIV);
        }

		hw::memcpy_s(l_szIV, sizeof(l_szIV),pszIV, (uiIVLen < AES_BLOCK_SIZE) ? uiIVLen : AES_BLOCK_SIZE);
    }

    l_uiAlgID = ALGID_AES128_CBC;

    CRYPT_SET_PAD_MODE(l_uiAlgID, BLOCK_PADDING_NORMAL);

    l_iResult = (int)CRYPT_decrypt(
        (SEC_UINT32       )l_uiAlgID,
        (const SEC_UCHAR *)l_szKey,
        (SEC_UINT32       )AES_128_KEY_SIZE,
        (const SEC_UCHAR *)l_szIV,
        (SEC_UINT32       )AES_BLOCK_SIZE,
        (SEC_UCHAR       *)pszCipher,
        (SEC_UINT32       )uiDataLen,
        (SEC_UCHAR       *)l_pszData,
        (SEC_UINT32      *)&l_uiLen
        );

    if (*puiLen < l_uiLen)
    {
        l_iResult = -9995;
    }

    if (l_iResult == SEC_SUCCESS) // 0
    {
        *puiLen = l_uiLen;
		hw::memcpy_s(pszPlain,l_uiLen, l_pszData, l_uiLen);
    }

    free(l_pszData);

    return l_iResult;
}
