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




/* ldap 搜索filter */
// base information
#define LDAP_FILTER_STR_CN                         "(cn="
#define LDAP_FILTER_STR_DISPLAYNAME                "(displayName="
#define LDAP_FILTER_STR_MAIL                       "(email="
#define LDAP_FILTER_STR_TELEPHONENUMBER            "(telephoneNumber="
#define LDAP_FILTER_STR_MOBILE                     "(mobile="
#define LDAP_FILTER_STR_POSTALADDRESS              "(postalAddress="
// #define LDAP_FILTER_STR_ORGANIZATIONUNITNAME       "(organizationalUnitName="


// h323Identity
// #define LDAP_STR_H323IDENTITY_H323ID "(h323Identityh323-ID=" // 软终端不支持此查询 即使查到也无法呼出
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


// DN 用于更新 即根据DN查询
#define LDAP_FILTER_STR_DN                                  "(EntryUuid="





/* ldap Attribute 用于匹配查询结果 */
#define LDAP_ATTRIBUTE_STR_CN                              "cn"                            // 会场名称
#define LDAP_ATTRIBUTE_STR_DISPLAYNAME                     "displayName"                   // 会场名称
#define LDAP_ATTRIBUTE_STR_MAIL                            "mail"						   // email
#define LDAP_ATTRIBUTE_STR_TELEPHONENUMBER                 "telephoneNumber"               // 办公号码
#define LDAP_ATTRIBUTE_STR_MOBILE                          "mobile"                        // 移动号码 
#define LDAP_ATTRIBUTE_STR_POSTTALADDRESS                  "postalAddress"                 // 地址

#define LDAP_ATTRIBUTE_STR_DN							   "EntryUuid"                 // DN 会场GUID "distinguishedName"
// #define LDAP_ATTRIBUTE_STR_ORGANIZATIONUNITNAME            "organizationalUnitName"                 // 部门

#define LDAP_ATTRIBUTE_STR_H323IDENTITY_DIALEDDIGITSM      "TPh323IdentitydialedDigitsM"  // H.323中指定的拨号号码-中屏
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_TRANSPORTIDM       "TPh323IdentitytransportIDM"   // H.323中指定的地址-中屏
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_DIALEDDIGITS       "h323IdentitydialedDigits"     // H.323中指定的拨号号码
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_URLID              "h323IdentityURL-ID"           // H.323中指定的URL-ID的别名
#define LDAP_ATTRIBUTE_STR_H323IDENTITY_TRANSPORTID        "h323IdentitytransportID"      // H.323中指定的地址


#define LDAP_ATTRIBUTE_STR_H320IDENTITY_SN                  "h320IdentitySN"               // 终端地址用户号
#define LDAP_ATTRIBUTE_STR_H320IdentityCC                   "h320IdentityCC"			   // H320国家码
#define LDAP_ATTRIBUTE_STR_H320IdentityNDC                  "h320IdentityNDC"              // h320国内区域码


#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_SIPURIM              "TPSIPIdentitySIPURIM"   // SIPURI -中屏
#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_AddressM             "TPSIPIdentityAddressM"  // 地址或域名-中屏
#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_SIPURL               "SIPIdentitySIPURI"      // sip协议中资源的统一资源标识符，该属性通常包含用户名称、主机名，以电子邮箱的格式出现。
#define LDAP_ATTRIBUTE_STR_SIPIDENTITY_ADDRESS              "SIPIdentityAddress"     // 用户代理的地址或者域名

#define LDAP_ATTRIBUTE_STR_SIPIDENTITYCT_DIALEDDIGITS       "CTSIPIdentitydialedDigits"      // CT拨号号码

#define LDAP_ATTRIBUTE_STR_SIPIDENTITYVCC_NUMBER            "VCCIdentityNumber"              // VCCIdentityNumber

#define LDAP_ATTRIBUTE_STR_LYNCUC_RTCSIP_LINE                "msRTCSIP-Line"                    // Lync UC SIP号码 E164
#define LDAP_ATTRIBUTE_STR_LYNCUC_RTCSIP_PRIMARYUSERADDRESS  "msRTCSIP-PrimaryUserAddress"      // Lync UC SIPURI


/* 本地搜索属性列表，在协议层写死，如果以后需要获取其他的属性，
在数组末尾增加即可，如果后续有的属性不需要，可以直接屏蔽
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
	// LDAPA_ATTR_E_ORGANIZATIONUNITNAME,   /*0-7为各类型会场的属性*/

	LDAPA_ATTR_E_H323IDENTITY_DIALEDDIGITSM,
	LDAPA_ATTR_E_H323IDENTITY_TRANSPORTIDM,
	LDAPA_ATTR_E_H323IDENTITY_DIALEDDIGITS,
	LDAPA_ATTR_E_H323IDENTITY_URLID,
	LDAPA_ATTR_E_H323IDENTITY_TRANSPORTID,   /*8-12为H323会场的属性*/

	LDAPA_ATTR_E_H320IDENTITY_SN,       /*13为H320会场的属性*/
	LDAPA_ATTR_E_H320IdentityCC,
	LDAPA_ATTR_E_H320IdentityNDC,

	LDAPA_ATTR_E_SIPIDENTITY_SIPURIM,
	LDAPA_ATTR_E_SIPIDENTITY_AddressM,
	LDAPA_ATTR_E_SIPIDENTITY_SIPURL,    /*14-16为SIP会场的属性*/
	LDAPA_ATTR_E_SIPIDENTITY_ADDRESS,


	LDAPA_ATTR_E_SIPIDENTITYCT_DIALEDDIGITS,  /*17为SIPCT会场的属性*/

	LDAPA_ATTR_E_SIPIDENTITYVCC_NUMBER,     /*18为SIPVCC会场的属性*/

	LDAPA_ATTR_E_LYNCUC_RTCSIP_LINE,
	LDAPA_ATTR_E_LYNCUC_RTCSIP_PRIMARYUSERADDRESS,  /*19-20为LyncUC会场的属性*/

	LDAPA_ATTR_BUTT,
}LDAPA_ATTR_E;




/* ldap搜索结果类型 */
typedef enum _tagLDAPC_RESULT_TYPE_E
{
	LDAPC_RESULT_SIPIDENTITY,      /*SIP类型 */
	LDAPC_RESULT_H323IDENTITY,     /*H323类型*/
	LDAPC_RESULT_H320IDENTITY,     /*H320类型*/
	LDAPC_RESULT_SIPIDENTITYCT,    /*SIPIdentityCT类型*/
	LDAPC_RESULT_SIPIdentityVCC,   /*SIPIdentityVCC类型*/
	LDAPC_RESULT_LYNCUC,           /*LyncUC类型*/
	LDAPC_RESULT_BUTT = 0xFF,      /*非法类型*/
}LDAPC_RESULT_TYPE_E;


/* ldap搜索结果 */
typedef struct _tagLDAPC_SEARCH_RESULT_D 
{
	/*std::string cn;
	std::string displayName;
	std::string mail;
	std::string telephoneNumber;
	std::string mobile;
 // std::string homePhone;  // 不查找homePhone
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



/* ldap搜索filter的匹配模式 */
typedef enum _tagLDAPC_FILTER_MODE_E
{
	LDAPC_FILTER_MODE_FUZZY,     /* 模糊匹配 */
	LDAPC_FILTER_MODE_PRECISE,   /* 精确匹配 */
	LDAPC_FILTER_MODE_BUTT
}LDAPC_FILTER_MODE_E;


/* ldap 搜索filter */
typedef struct _tagLDAPC_FILTER_S
{
	std::string szLdapEntryFilter;
	LDAPC_FILTER_MODE_E enMode;
}LDAPC_FILTER_S;


/* ldap 搜索 Attribute */
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



/*  会控模块的定义
typedef enum tagCCSiteCallTerminalType
{
	CC_isdnVideo,                                         // ISDN视讯终端
	CC_v35,                                               // V.35终端
	CC_e1,                                                // E1终端
	CC_h323,                                              // IP终端
	CC_phone,                                             // Phone终端
	CC_4e1,                                               // 4E1终端
	CC_sip,                                               // SIP终端

	CC_invalidTerminalType = 0xFF,                      // 代表无效的值
} 
*/

typedef enum _tagTECONTACT_TYPE_E
{
	CONTACT_H320_TYPE = CONTACT_TYPE_H320,         // 对应CC_e1
	CONTACT_H323_TYPE = CONTACT_TYPE_H323,         // 对应CC_h323
	CONTACT_SIP_TYPE  = CONTACT_TYPE_SIP,         // 对应CC_sip
	CONTACT_SIP_H323_TYPE = CONTACT_TYPE_SIP_H323,     // SIP H323同号
	CONTACT_TYPE_BUTT = 0xFF,     // 异常类型
}TECONTACT_TYPE_E;


// 同号的情况
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