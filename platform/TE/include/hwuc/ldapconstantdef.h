#ifndef __LDAP_CONSTANT_DEF__H_
#define __LDAP_CONSTANT_DEF__H_



#define LDAP_STR_OR_HEAD        "(|"
#define LDAP_STR_OR_END         ")"
#define LDAP_STR_WILDCARD       "*)"
#define LDAP_STR_START          "*"

#define LDAP_FILTER_MAX_KEYWORDS_NUMBER      3
#define LDAP_STR_AND_HEAD        "(&"
#define LDAP_STR_AND_END        ")"

#define LDAP_TYPE_STR_LDAP       "ldap"
#define LDAP_TYPE_STR_LDAPS      "ldaps"

#define LDAP_STR_BLANK          " "

#define MAX_LDAPA_SEARCH_SN_NUM      18
#define MAX_LDAPA_SEARCH_SIZELIMIT   50

#define LDAP_DEFAULT_PORT       389
#define LDAPS_DEFAULT_PORT      636

#define CONTACT_TYPE_H320                2
#define CONTACT_TYPE_H323                3
#define CONTACT_TYPE_SIP                 6
#define CONTACT_TYPE_SIP_H323            7

#define CROSS_LINE                       "-"
#define PLUS_SIGN                        "+"
#define SPECIAL_SPLIT_ENTRYUUID          "$$"

#define SIP_ENTRYUUID                     "sip"
#define H323_ENTRYUUID                    "h323"
#define H320_ENTRYUUID                    "h320"

#define ISDN_MARK_NAME                    "ISDN"




/* ldap ����filter */
// base information
#define LDAP_FILTER_STR_CN                         "(cn="
#define LDAP_FILTER_STR_DISPLAYNAME                "(displayName="
#define LDAP_FILTER_STR_MAIL                       "(email="
#define LDAP_FILTER_STR_TELEPHONENUMBER            "(telephoneNumber="
#define LDAP_FILTER_STR_MOBILE                     "(mobile="
#define LDAP_FILTER_STR_POSTALADDRESS              "(postalAddress="
// #define LDAP_FILTER_STR_ORGANIZATIONUNITNAME       "(organizationalUnitName="


// h323Identity
// #define LDAP_STR_H323IDENTITY_H323ID "(h323Identityh323-ID=" // ���ն˲�֧�ִ˲�ѯ ��ʹ�鵽Ҳ�޷�����
#define LDAP_FILTER_STR_H323IDENTITY_DIALEDDIGITS         "(h323IdentitydialedDigits="

// h320Identity
#define LDAP_FILTER_STR_H320IDENTITY_SN                    "(h320IdentitySN="


// SIPIdentity
#define LDAP_FILTER_STR_SIPIDENTITY_SIPURL                 "(SIPIdentitySIPURI="
#define LDAP_FILTER_STR_SIPIDENTITY_ADDRESS                "(SIPIdentityAddress="

// h323IdentityTP
#define LDAP_FILRER_STR_TPH323IDENTITY_DIALEDDIGITSM        "(TPh323IdentitydialedDigitsM="  
#define LDAP_FILTER_STR_H323IDENTITY_TRANSPORTIDM			"(TPh323IdentitytransportIDM="

// SIPIdentityTP
#define LDAP_FILTER_STR_SIPIDENTITY_SIPURIM                 "(TPSIPIdentitySIPURIM="
#define LDAP_FILTER_STR_SIPIDENTITY_AddressM                "(TPSIPIdentityAddressM="



// SIPIdentityCT
#define LDAP_FILTER_STR_SIPIDENTITYCT_DIALEDDIGITS         "(CTSIPIdentitydialedDigits="

// SIPIdentityVCC
#define LDAP_FILTER_STR_SIPIDENTITYVCC_NUMBER              "(VCCIdentityNumber="

// LyncUC
#define LDAP_FILTER_STR_LYNCUC_RTCSIP_LINE                 "(msRTCSIP-Line="
#define LDAP_FILTER_STR_LYNCUC_RTCSIP_PRIMARYUSERADDRESS   "(msRTCSIP-PrimaryUserAddress="


// DN ���ڸ��� ������DN��ѯ
#define LDAP_FILTER_STR_DN                                  "(EntryUuid="





/* ldap Attribute ����ƥ���ѯ��� */
#define LDAP_ATTRIBUTE_STR_CN                              "cn"                            // �᳡����
#define LDAP_ATTRIBUTE_STR_DISPLAYNAME                     "displayName"                   // �᳡����
#define LDAP_ATTRIBUTE_STR_MAIL                            "mail"						   // email
#define LDAP_ATTRIBUTE_STR_TELEPHONENUMBER                 "telephoneNumber"               // �칫����
#define LDAP_ATTRIBUTE_STR_MOBILE                          "mobile"                        // �ƶ����� 
#define LDAP_ATTRIBUTE_STR_POSTTALADDRESS                  "postalAddress"                 // ��ַ

#define LDAP_ATTRIBUTE_STR_DN							   "EntryUuid"                 // DN �᳡GUID "distinguishedName"
// #define LDAP_ATTRIBUTE_STR_ORGANIZATIONUNITNAME            "organizationalUnitName"                 // ����

#define LDAP_ATTRIBUTE_STR_H323IDENTITY_DIALEDDIGITSM      "TPh323IdentitydialedDigitsM"  // H.323��ָ���Ĳ��ź���-����
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_TRANSPORTIDM       "TPh323IdentitytransportIDM"   // H.323��ָ���ĵ�ַ-����
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_DIALEDDIGITS       "h323IdentitydialedDigits"     // H.323��ָ���Ĳ��ź���
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_URLID              "h323IdentityURL-ID"           // H.323��ָ����URL-ID�ı���
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_TRANSPORTID        "h323IdentitytransportID"      // H.323��ָ���ĵ�ַ


#define LDAP_ATTRIBUTE_STR_H320IDENTITY_SN                  "h320IdentitySN"               // �ն˵�ַ�û���
#define LDAP_ATTRIBUTE_STR_H320IdentityCC                   "h320IdentityCC"			   // H320������
#define LDAP_ATTRIBUTE_STR_H320IdentityNDC                  "h320IdentityNDC"              // h320����������


#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_SIPURIM              "TPSIPIdentitySIPURIM"   // SIPURI -����
#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_AddressM             "TPSIPIdentityAddressM"  // ��ַ������-����
#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_SIPURL               "SIPIdentitySIPURI"      // sipЭ������Դ��ͳһ��Դ��ʶ����������ͨ�������û����ơ����������Ե�������ĸ�ʽ���֡�
#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_ADDRESS              "SIPIdentityAddress"     // �û�����ĵ�ַ��������

#define LDAP_ATTRIBUTE_STR_SIPIDENTITYCT_DIALEDDIGITS       "CTSIPIdentitydialedDigits"      // CT���ź���

#define LDAP_ATTRIBUTE_STR_SIPIDENTITYVCC_NUMBER            "VCCIdentityNumber"              // VCCIdentityNumber

#define LDAP_ATTRIBUTE_STR_LYNCUC_RTCSIP_LINE                "msRTCSIP-Line"                    // Lync UC SIP���� E164
#define LDAP_ATTRIBUTE_STR_LYNCUC_RTCSIP_PRIMARYUSERADDRESS  "msRTCSIP-PrimaryUserAddress"      // Lync UC SIPURI


/* �������������б���Э���д��������Ժ���Ҫ��ȡ���������ԣ�
������ĩβ���Ӽ��ɣ���������е����Բ���Ҫ������ֱ������
*/
typedef enum _tagLDAPA_ATTR_E
{
	LDAPA_ATTR_E_CN = 0,
	LDAPA_ATTR_E_DISPLAYNAME,
	LDAPA_ATTR_E_MAIL,                 
	LDAPA_ATTR_E_TELEPHONENUMBER,    
	LDAPA_ATTR_E_MOBILE,
	LDAPA_ATTR_E_POSTTALADDRESS,
	LDAPA_ATTR_E_DN,  
	// LDAPA_ATTR_E_ORGANIZATIONUNITNAME,   /*0-7Ϊ�����ͻ᳡������*/

	LDAPA_ATTR_E_H323IDENTITY_DIALEDDIGITSM,
	LDAPA_ATTR_E_H323IDENTITY_TRANSPORTIDM,
	LDAPA_ATTR_E_H323IDENTITY_DIALEDDIGITS,
	LDAPA_ATTR_E_H323IDENTITY_URLID,
	LDAPA_ATTR_E_H323IDENTITY_TRANSPORTID,   /*8-12ΪH323�᳡������*/

	LDAPA_ATTR_E_H320IDENTITY_SN,       /*13ΪH320�᳡������*/
	LDAPA_ATTR_E_H320IdentityCC,
	LDAPA_ATTR_E_H320IdentityNDC,

	LDAPA_ATTR_E_SIPIDENTITY_SIPURIM,
	LDAPA_ATTR_E_SIPIDENTITY_AddressM,
	LDAPA_ATTR_E_SIPIDENTITY_SIPURL,    /*14-16ΪSIP�᳡������*/
	LDAPA_ATTR_E_SIPIDENTITY_ADDRESS,


	LDAPA_ATTR_E_SIPIDENTITYCT_DIALEDDIGITS,  /*17ΪSIPCT�᳡������*/

	LDAPA_ATTR_E_SIPIDENTITYVCC_NUMBER,     /*18ΪSIPVCC�᳡������*/

	LDAPA_ATTR_E_LYNCUC_RTCSIP_LINE,
	LDAPA_ATTR_E_LYNCUC_RTCSIP_PRIMARYUSERADDRESS,  /*19-20ΪLyncUC�᳡������*/

	LDAPA_ATTR_BUTT,
}LDAPA_ATTR_E;




/* ldap����������� */
typedef enum _tagLDAPC_RESULT_TYPE_E
{
	LDAPC_RESULT_SIPIDENTITY,      /*SIP���� */
	LDAPC_RESULT_H323IDENTITY,     /*H323����*/
	LDAPC_RESULT_H320IDENTITY,     /*H320����*/
	LDAPC_RESULT_SIPIDENTITYCT,    /*SIPIdentityCT����*/
	LDAPC_RESULT_SIPIdentityVCC,   /*SIPIdentityVCC����*/
	LDAPC_RESULT_LYNCUC,           /*LyncUC����*/
	LDAPC_RESULT_BUTT = 0xFF,      /*�Ƿ�����*/
}LDAPC_RESULT_TYPE_E;


/* ldap������� */
typedef struct _tagLDAPC_SEARCH_RESULT_D 
{
	/*std::string cn;
	std::string displayName;
	std::string mail;
	std::string telephoneNumber;
	std::string mobile;
 // std::string homePhone;  // ������homePhone
	std::string postalAddress;
	std::string organizationalUnitName;
	std::string entryUUID;

	std::string TPh323IdentitydialedDigitsM;
    std::string TPh323IdentitytransportIDM;
	std::string h323IdentitydialedDigits;
	std::string h323IdentityURLID;
	std::string h323IdentitytransportID;

	std::string h320IdentitySN;

	std::string TPSIPIdentitySIPURIM;
	std::string TPSIPIdentityAddressM;
	std::string SIPIdentitySIPURI;
  
	std::string CTSIPIdentitydialedDigits;

	std::string VCCIdentityNumber;

	std::string LyncUCmsRTCSIPLine;
	std::string LyncmsRTCSIPPrimaryUserAddress;*/

	std::string attributes[LDAPA_ATTR_BUTT];
	LDAPC_RESULT_TYPE_E eType;

	_tagLDAPC_SEARCH_RESULT_D()
	{
		for (int i = 0; i < LDAPA_ATTR_BUTT; i++)
		{
			attributes[i] = "";
		}

		eType = LDAPC_RESULT_BUTT;
	}

}LDAPC_SEARCH_RESULT_D;



/* ldap����filter��ƥ��ģʽ */
typedef enum _tagLDAPC_FILTER_MODE_E
{
	LDAPC_FILTER_MODE_FUZZY,     /* ģ��ƥ�� */
	LDAPC_FILTER_MODE_PRECISE,   /* ��ȷƥ�� */
	LDAPC_FILTER_MODE_BUTT
}LDAPC_FILTER_MODE_E;


/* ldap ����filter */
typedef struct _tagLDAPC_FILTER_S
{
	std::string szLdapEntryFilter;
	LDAPC_FILTER_MODE_E enMode;
}LDAPC_FILTER_S;


/* ldap ���� Attribute */
typedef struct _tagLDAPC_ATTRIBUTE_S
{
	LDAPA_ATTR_E enMode;
	std::string szLdapEntryAttribute;
}LDAPC_ATTRIBUTE_S;

typedef struct _tagLDAPC_TYPE_S
{
	LDAPA_ATTR_E enMode;
	LDAPC_RESULT_TYPE_E eType;
}LDAPC_TYPE_S;


typedef struct _tagLDAP_ESPACE_S 
{
	std::string sourceStr;
	std::string espaceStr;
}LDAP_ESPACE_S;



/*  ���ģ��Ķ���
typedef enum tagCCSiteCallTerminalType
{
	CC_isdnVideo,                                         // ISDN��Ѷ�ն�
	CC_v35,                                               // V.35�ն�
	CC_e1,                                                // E1�ն�
	CC_h323,                                              // IP�ն�
	CC_phone,                                             // Phone�ն�
	CC_4e1,                                               // 4E1�ն�
	CC_sip,                                               // SIP�ն�

	CC_invalidTerminalType = 0xFF,                      // ������Ч��ֵ
} 
*/

typedef enum _tagTECONTACT_TYPE_E
{
	CONTACT_H320_TYPE = CONTACT_TYPE_H320,         // ��ӦCC_e1
	CONTACT_H323_TYPE = CONTACT_TYPE_H323,         // ��ӦCC_h323
	CONTACT_SIP_TYPE  = CONTACT_TYPE_SIP,         // ��ӦCC_sip
	CONTACT_SIP_H323_TYPE = CONTACT_TYPE_SIP_H323,     // SIP H323ͬ��
	CONTACT_TYPE_BUTT = 0xFF,     // �쳣����
}TECONTACT_TYPE_E;


// ͬ�ŵ����
typedef enum _tagTESAMEACCOUNT_TYPE_E
{
	sip = 1,
	h323,
	h323_sip,
	h320,
	h320_sip,
	h320_h323,
	h320_h323_sip,
}TESAMEACCOUNT_TYPE_E;






/* AES ciphersuites from RFC3268 */
#define     TUP_LDAPS_E_TLS11_CK_RSA_WITH_AES_128_SHA           0x0300002F  /*TLS_RSA_WITH_AES_128_CBC_SHA     */
#define     TUP_LDAPS_E_TLS11_CK_DHE_DSS_WITH_AES_128_SHA       0x03000032  /*TLS_DHE_DSS_WITH_AES_128_CBC_SHA */
#define     TUP_LDAPS_E_TLS11_CK_DHE_RSA_WITH_AES_128_SHA       0x03000033  /*TLS_DHE_RSA_WITH_AES_128_CBC_SHA */
#define     TUP_LDAPS_E_TLS11_CK_ADH_WITH_AES_128_SHA           0x03000034  /*TLS_DH_anon_WITH_AES_128_CBC_SHA */

#define     TUP_LDAPS_E_TLS11_CK_RSA_WITH_AES_256_SHA           0x03000035  /*TLS_RSA_WITH_AES_256_CBC_SHA    */
#define     TUP_LDAPS_E_TLS11_CK_DHE_DSS_WITH_AES_256_SHA       0x03000038  /*TLS_DHE_DSS_WITH_AES_256_CBC_SHA*/
#define     TUP_LDAPS_E_TLS11_CK_DHE_RSA_WITH_AES_256_SHA       0x03000039  /*TLS_DHE_RSA_WITH_AES_256_CBC_SHA*/
#define     TUP_LDAPS_E_TLS11_CK_ADH_WITH_AES_256_SHA           0x0300003A  /*TLS_DH_anon_WITH_AES_256_CBC_SHA*/




#endif