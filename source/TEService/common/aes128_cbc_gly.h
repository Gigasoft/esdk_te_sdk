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
* ============================================================================ *
* CBC 模式需要提供初始向量 IV，加密和解密必须采用相同的初始向量                *
* 可以简单认为初始向量就是一个干扰项，用来增强安全性的                         *
* 从安全角度考虑，每次调用加密函数时都需要变换初始向量                         *
* 安全性要求不是很严格时，初始向量可以明文传送到解密端                         *
* 初始向量的长度一般为加密块的大小（AES 算法加密块的大小为 16 字节）           *
*******************************************************************************/
#if !defined(_AES128_CBC_BY_GONGLIANYANG_)
#define _AES128_CBC_BY_GONGLIANYANG_

#ifdef __cplusplus
extern "C" {
#endif

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
    ); // 0：成功，其它：失败

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
    ); // 0：成功，其它：失败

#ifdef __cplusplus
}
#endif

#endif // !defined(_AES128_CBC_BY_GONGLIANYANG_)