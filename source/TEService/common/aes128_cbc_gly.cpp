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
    char         * pszCipher, // ������������ģ����룩
    unsigned int * puiLen,    // *puiLen������������������룺���� pszCipher ��
                              //   ��С����������ĵĳ���
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
    char         * pszPlain,  // �������������
    unsigned int * puiLen,    // *puiLen������������������룺���� pszPlain ��
                              //   ��С����������ĵĳ���
    const char   * pszCipher, // �������������
    unsigned int   uiDataLen, // ������������ĵĳ���
                              //   Ϊ 0 ʱ���� pszCipher Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    const char   * pszKey,    // �����������Կ
    unsigned int   uiKeyLen,  // �����������Կ�ĳ���
                              //   Ϊ 0 ʱ���� pszKey Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    const char   * pszIV,     // �����������ʼ����
    unsigned int   uiIVLen    // �����������ʼ�����ĳ���
                              //   Ϊ 0 ʱ���� pszIV Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    ) // 0���ɹ���������ʧ��
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

    l_uiLen = uiDataLen; // ����Ҫ������һ������CRYPT_decrypt �ڲ���Ҫ����֪Ϊʲô

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
