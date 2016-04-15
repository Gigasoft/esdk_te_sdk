/*******************************************************************************
* Author: Lianyang Gong                                                        *
*   Date: 2011-03-17                                                           *
*******************************************************************************/
#if !defined(_BASE64_BY_GONGLIANYANG_)
#define _BASE64_BY_GONGLIANYANG_

#ifdef __cplusplus
extern "C" {
#endif

int BASE64_Encode_GLY(
    char         * pszBase64, // 输出参数，保存 Base64 编码结果
    unsigned int * puiLen,    // *puiLen，输入输出参数，输入：缓存 pszBase64 的
                              //   大小，输出：字符串的大小，包括结束符
    const char   * pszData,   // 输入参数：数据
    unsigned int   uiDataLen  // 输入参数：数据的长度
                              //   为 0 时，当 pszData 为字符串，自动取该字符串的长度
    ); // 0：成功，其它：失败

int BASE64_Decode_GLY(
    char         * pszData,    // 输出参数，保存 Base64 解码结果
    unsigned int * puiLen,     // *puiLen，输入输出参数，输入：缓存 pszData 的大小，
                               //   输出：Base64 解码结果的大小
    const char   * pszBase64,  // 输入参数：Base64 编码的字符串
    unsigned int   uiBase64Len // 输入参数：Base64 编码的字符串的长度
                               //   为 0 时，自动取 Base64 编码的字符串的长度
    ); // 0：成功，其它：失败

#ifdef __cplusplus
}
#endif

#endif // !defined(_BASE64_BY_GONGLIANYANG_)