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
    char         * pszBase64, // ������������� Base64 ������
    unsigned int * puiLen,    // *puiLen������������������룺���� pszBase64 ��
                              //   ��С��������ַ����Ĵ�С������������
    const char   * pszData,   // �������������
    unsigned int   uiDataLen  // ������������ݵĳ���
                              //   Ϊ 0 ʱ���� pszData Ϊ�ַ������Զ�ȡ���ַ����ĳ���
    ); // 0���ɹ���������ʧ��

int BASE64_Decode_GLY(
    char         * pszData,    // ������������� Base64 ������
    unsigned int * puiLen,     // *puiLen������������������룺���� pszData �Ĵ�С��
                               //   �����Base64 �������Ĵ�С
    const char   * pszBase64,  // ���������Base64 ������ַ���
    unsigned int   uiBase64Len // ���������Base64 ������ַ����ĳ���
                               //   Ϊ 0 ʱ���Զ�ȡ Base64 ������ַ����ĳ���
    ); // 0���ɹ���������ʧ��

#ifdef __cplusplus
}
#endif

#endif // !defined(_BASE64_BY_GONGLIANYANG_)