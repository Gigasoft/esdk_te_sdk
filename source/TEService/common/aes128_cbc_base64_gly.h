/*******************************************************************************
* Author: Lianyang Gong                                                        *
*   Date: 2011-03-17                                                           *
* ============================================================================ *
* 为了保证能和 Java 代码保持一致，本封装仅支持 PKCS5Padding                    *
* 因此加解密接口中不体现数据块补齐模式                                         *
* ============================================================================ *
* 从安全性考虑，本封装仅支持 ECB 和 CBC 模式                                   *
* ============================================================================ *
* 密文的长度 x 与明文的长度 y 的关系如下，申请内存时需注意                     *
* x = ((y / 16) + 1) * 16                                                      *
* 16 进制编码后的长度 z（包括字符串结束符）与密文长度 x 的关系如下，           *
* z = (((x / 3) + (((x % 3) == 0) ? 0 : 1)) * 4                                *
*******************************************************************************/
#if !defined(_AES128_CBC_BASE64_BY_GONGLIANYANG_)
#define _AES128_CBC_BASE64_BY_GONGLIANYANG_

#ifdef __cplusplus
extern "C" {
#endif

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
    ); // 0：成功，其它：失败

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
    const char   * pszIV,    // 输入参数：初始向量
    unsigned int   uiIVLen   // 输入参数：初始向量的长度
                             //   为 0 时，当 pszIV 为字符串，自动取该字符串的长度
    ); // 0：成功，其它：失败

#ifdef __cplusplus
}
#endif

#endif // !defined(_AES128_CBC_BASE64_BY_GONGLIANYANG_)