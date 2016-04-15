/*******************************************************************************
*                                                                              *
*                Copyright 2003, Huawei Technologies Co. Ltd.                  *
*                            ALL RIGHTS RESERVED                               *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*                              sec_sys.h                                    *
*                                                                              *
*  Project Code: SeCert                                                        *
*   Module Name: Common Module                                                 *
*   @brief: Contains structures and functions required in two or more     *
*   modules. The list of items in this file are:							   *
*		-SEC_REPORT_ERROR-   To log errors if _SEC_DEBUG_MODE is set		   *
*		-Memory Macros-    To allocate,free,set,copy,compare memory blocks	   *
*       -SEC_fprintf-      To print to a file                                  *
*       -SEC_CertType_E-   enumeration to hold Certificate type: used in	   *
*							PKCS12,SCEPTo print to a file					   *
*       -SEC_getPubKey-      functions to convert SubjPubKeyInfo to SEC_PKEY   *
*		-SEC_createSubjPubKeyInfo								and viceversa  *
*       -SEC_GenTimeToDateTime-      To convert GeneralizedTime to Dtae Time   *
*       -SEC_DateTimeToGenTime-      and viceversa							   *
*******************************************************************************/
#ifndef  _SEC_SYS_H_
#define  _SEC_SYS_H_

//Added for DLL Build - Start
#ifdef __CRYPTO_DLL
#define CRYPTOLINKDLL __declspec(dllimport)
#else 
#define CRYPTOLINKDLL
#endif


#ifdef __PSE_DLL
#define PSELINKDLL __declspec(dllimport)
#define _PSE_INTERNAL_USE_DLL
#else
#define PSELINKDLL
#endif

#ifdef __SSL_DLL
#define SSLLINKDLL __declspec(dllimport)
#define _SSL_INTERNAL_USE_DLL
#else
#define SSLLINKDLL
#endif

//Added for DLL Build - End

#ifdef SEC_DOPRA
	#include <sec_sys_dopra.h>
#else
	#include <stdio.h>
	#include <stdlib.h>
	#include <malloc.h>
	#include <string.h>
#endif

#ifdef	 __cplusplus
extern	"C"{
#endif

#ifndef SEC_DOPRA

#define SEC_SUCCESS            0

typedef void                   SEC_VOID;

typedef unsigned char          SEC_UINT8;

typedef signed char            SEC_INT8;

typedef char                   SEC_CHAR;           

typedef unsigned char          SEC_UCHAR;


typedef unsigned short         SEC_UINT16;

typedef signed   short         SEC_INT16;

typedef signed   short         SEC_WCHAR;          

#if defined(__LP64__)

typedef unsigned int           SEC_UINT32;

typedef signed   int           SEC_INT32;

typedef unsigned int           SEC_BOOL;

#else

typedef unsigned long          SEC_UINT32;

typedef signed   long          SEC_INT32;

typedef unsigned long          SEC_BOOL;

#endif

typedef int                    SEC_INT;

typedef unsigned int           SEC_UINT;

typedef FILE                   SEC_FILE_F;


#endif

#ifndef	SEC_DOPRA_HAS_DATETIME

#endif	/* SEC_DOPRA_HAS_DATETIME */

/* the enum to hold all the common IDs corresponding to the OIDs (in the algtable) */
typedef enum
{
	CID_UNKNOWN,

	/* Algorithm Ids from crypto*/

	CID_RC4,

	CID_DES_ECB,
	CID_DES_CBC,
	CID_DES_OFB,
	CID_DES_CFB,

	/* Algorithm Ids for SSX31B HW support */
	CID_SCB2_128_ECB,
	CID_SCB2_128_CBC,

	CID_SCB2_256_ECB,
	CID_SCB2_256_CBC,

	CID_DES_EDE_ECB,
	CID_DES_EDE_CBC,
	CID_DES_EDE_OFB,
	CID_DES_EDE_CFB,

	CID_DES_EDE3_ECB,
	CID_DES_EDE3_CBC,
	CID_DES_EDE3_OFB,
	CID_DES_EDE3_CFB,

	CID_AES128_ECB,
	CID_AES128_CBC,
	CID_AES128_OFB,
	CID_AES128_CFB,

	CID_AES192_ECB,
	CID_AES192_CBC,
	CID_AES192_OFB,
	CID_AES192_CFB,

	CID_AES256_ECB,
	CID_AES256_CBC,
	CID_AES256_OFB,
	CID_AES256_CFB,

	CID_RSA,
	CID_DSA,
	CID_ECDSA,
	CID_DH,
    CID_ECDH,

	CID_MD5,
	CID_SHA1,
	CID_SHA224,
	CID_SHA256,
	CID_SHA384,
	CID_SHA512,

	CID_HMAC_MD5,
	CID_HMAC_SHA1,
	CID_HMAC_SHA224,
	CID_HMAC_SHA256,
	CID_HMAC_SHA384,
	CID_HMAC_SHA512,

	CID_MD5WITHRSA,
	CID_SHA1WITHRSA,
	CID_SHA1WITHRSAOLD,
	CID_DSAWITHSHA1,
	CID_DSAWITHSHA1_2,
	CID_ECDSAWITHSHA1,
	CID_SHA256WITHRSAENCRYPTION,
	CID_SHA384WITHRSAENCRYPTION,
	CID_SHA512WITHRSAENCRYPTION,
	
	/*RFC 3279 */

	CID_KEYEXCHANGEALGORITHM,
	CID_PKCS1,
	CID_ANSI_X9_62,
	CID_ECSIGTYPE,
	CID_FIELDTYPE,
	CID_PRIME_FIELD,
	CID_CHARACTERISTIC_TWO_FIELD,
	CID_CHARACTERISTIC_TWO_BASIS,
	CID_GNBASIS,
	CID_TPBASIS,
	CID_PPBASIS,
	CID_PUBLICKEYTYPE,
	CID_ELLIPTICCURVE,
	CID_C_TWOCURVE,
	CID_C2PNB163V1,
	CID_C2PNB163V2,
	CID_C2PNB163V3,
	CID_C2PNB176W1,
	CID_C2TNB191V1,
	CID_C2TNB191V2,
	CID_C2TNB191V3,
	CID_C2ONB191V4,
	CID_C2ONB191V5,
	CID_C2PNB208W1,
	CID_C2TNB239V1,
	CID_C2TNB239V2,
	CID_C2TNB239V3,
	CID_C2ONB239V4,
	CID_C2ONB239V5,
	CID_C2PNB272W1,
	CID_C2PNB304W1,
	CID_C2TNB359V1,
	CID_C2PNB368W1,
	CID_C2TNB431R1,
	CID_PRIMECURVE,
	CID_PRIME192V1,
	CID_PRIME192V2,
	CID_PRIME192V3,
	CID_PRIME239V1,
	CID_PRIME239V2,
	CID_PRIME239V3,
	CID_PRIME256V1,


	/* SCEP */

	CID_VERISIGN,
	CID_PKI,
	CID_ATTRIBUTES,
	CID_MESSAGETYPE,
	CID_PKISTATUS,
	CID_FAILINFO,
	CID_SENDERNONCE,
	CID_RECIPIENTNONCE,
	CID_TRANSID,
	CID_EXTENSIONREQ,



	/* PKCS 5 */

	CID_RSADSI,
	CID_PKCS,
	CID_PKCS5,
	CID_PBKDF2,
	CID_PBE_MD2WITHDESCBC,
	CID_PBE_MD2WITHRC2CBC,
	CID_PBE_MD5WITHDESCBC,
	CID_PBE_MD5WITHRC2CBC,
	CID_PBE_SHA1WITHDESCBC,
	CID_PBE_SHA1WITHRC2CBC,
	CID_PBES2,
	CID_PBMAC1,
	CID_DIGESTALGORITHM,
	CID_ENCRYPTIONALGORITHM,
	CID_RC2CBC,
	CID_RC5_CBC_PAD,
	CID_RSAES_OAEP,/* from pkcs1 */



	/* OCSP */

	CID_PKIX_OCSP_BASIC,
	CID_PKIX_OCSP_NONCE,
	CID_PKIX_OCSP_CRL,
	CID_PKIX_OCSP_RESPONSE,
	CID_PKIX_OCSP_NOCHECK,
	CID_PKIX_OCSP_ARCHIVE_CUTOFF,
	CID_PKIX_OCSP_SERVICE_LOCATOR,

	/* PKCS 10 */

	CID_CHALLENGE_PWD_ATTR,
	CID_EXTENSIONREQUEST,

	/* FROM PKIXEXPLICIT */

	CID_PKIX,
	CID_PE,
	CID_QT,
	CID_KP,
	CID_AD,
	CID_QT_CPS,
	CID_QT_UNOTICE,
	CID_AD_OCSP,
	CID_AD_CAISSUERS,
	CID_AD_TIMESTAMPING,
	CID_AD_CAREPOSITORY,
	CID_AT,
	CID_AT_NAME,
	CID_AT_SURNAME,
	CID_AT_GIVENNAME,
	CID_AT_INITIALS,
	CID_AT_GENERATIONQUALIFIER,
	CID_AT_COMMONNAME,
	CID_AT_LOCALITYNAME,
	CID_AT_STATEORPROVINCENAME,
	CID_AT_ORGANIZATIONNAME,
	CID_AT_ORGANIZATIONALUNITNAME,
	CID_AT_TITLE,
	CID_AT_DNQUALIFIER,
	CID_AT_COUNTRYNAME,
	CID_AT_SERIALNUMBER,
	CID_AT_PSEUDONYM,
	CID_DOMAINCOMPONENT,
	CID_EMAILADDRESS,

	/* PKIXIMPLICIT */

	CID_CE,
	CID_CE_AUTHORITYKEYIDENTIFIER,
	CID_CE_SUBJECTKEYIDENTIFIER,
	CID_CE_KEYUSAGE,
	CID_CE_PRIVATEKEYUSAGEPERIOD,
	CID_CE_CERTIFICATEPOLICIES,
	CID_ANYPOLICY,
	CID_CE_POLICYMAPPINGS,
	CID_CE_SUBJECTALTNAME,
	CID_CE_ISSUERALTNAME,
	CID_CE_SUBJECTDIRECTORYATTRIBUTES,
	CID_CE_BASICCONSTRAINTS,
	CID_CE_NAMECONSTRAINTS,
	CID_CE_POLICYCONSTRAINTS,
	CID_CE_CRLDISTRIBUTIONPOINTS,
	CID_CE_EXTKEYUSAGE,
	CID_ANYEXTENDEDKEYUSAGE,
	CID_KP_SERVERAUTH,
	CID_KP_CLIENTAUTH,
	CID_KP_CODESIGNING,
	CID_KP_EMAILPROTECTION,
	CID_KP_TIMESTAMPING,
	CID_KP_OCSPSIGNING,
	CID_CE_INHIBITANYPOLICY,
	CID_CE_FRESHESTCRL,
	CID_PE_AUTHORITYINFOACCESS,
	CID_PE_SUBJECTINFOACCESS,
	CID_CE_CRLNUMBER,
	CID_CE_ISSUINGDISTRIBUTIONPOINT,
	CID_CE_DELTACRLINDICATOR,
	CID_CE_CRLREASONS,
	CID_CE_CERTIFICATEISSUER,
	CID_CE_HOLDINSTRUCTIONCODE,
	CID_HOLDINSTRUCTION,
	CID_HOLDINSTRUCTION_NONE,
	CID_HOLDINSTRUCTION_CALLISSUER,
	CID_HOLDINSTRUCTION_REJECT,
	CID_CE_INVALIDITYDATE,
	CID_PDA_DATEOFBIRTH,
	CID_PDA_PLACEOFBIRTH,
	CID_PDA_GENDER,
	CID_PDA_COUNTRYOFCITIZENSHIP,
	CID_PDA_COUNTRYOFRESIDENCE,
	CID_PDA,
	CID_ON_PERMANENTIDENTIFIER,
	CID_ON,
    CID_CE_DOMAININFO,

	/* CMP */

	CID_PASSWORDBASEDMAC,
	CID_DHBASEDMAC,
	CID_IT,
	CID_CAPROTENCCERT,
	CID_SIGNKEYPAIRTYPES,
	CID_ENCKEYPAIRTYPES,
	CID_PREFERREDSYMMALG,
	CID_CAKEYUPDATEINFO,
	CID_CURRENTCRL,


	/*CRMF*/

	CID_PKIP,
	CID_REGCTRL,
	CID_REGCTRL_REGTOKEN,
	CID_REGCTRL_AUTHENTICATOR,
	CID_REGCTRL_PKIPUBLICATIONINFO,
	CID_REGCTRL_PKIARCHIVEOPTIONS,
	CID_REGCTRL_OLDCERTID,
	CID_REGCTRL_PROTOCOLENCRKEY,
	CID_REGINFO,
	CID_REGINFO_UTF8PAIRS,
	CID_REGINFO_CERTREQ,

	/* PKCS12 */

	CID_PKCS12,
	CID_PKCS12PBEIDS,
	CID_PBE_SHAWITH128BITRC4,
	CID_PBE_SHAWITH40BITRC4,
	CID_PBE_SHAWITH3KEY_TRIPLE_DESCBC,
	CID_PBE_SHAWITH2KEY_TRIPLE_DESCBC,
	CID_PBE_SHAWITH128BIT_RC2CBC,
	CID_PBE_SHAWITH40BIT_RC2CBC,
	CID_BAGTYPES,
	CID_KEYBAG,
	CID_PKCS8SHROUDEDKEYBAG,
	CID_CERTBAG,
	CID_CRLBAG,
	CID_SECRETBAG,
	CID_SAFECONTENTSBAG,
	CID_X509CERTIFICATE,
	CID_SDSICERTIFICATE,
	CID_FRIENDLYNAME,
	CID_LOCALKEYID,

	/* auth_frame*/

	CID_CERTIFICATEREVOCATIONLIST,


	/*PKCS7 & 9*/

	CID_PKCS7,
	CID_PKCS7_SIMPLEDATA,
	CID_PKCS7_SIGNEDDATA,
	CID_PKCS7_ENVELOPEDDATA,
	CID_PKCS7_SIGNED_ENVELOPEDDATA,
	CID_PKCS7_DIGESTEDDATA,
	CID_PKCS7_ENCRYPTEDDATA,


	CID_PKCS9,
	CID_PKCS9_AT_CONTENTTYPE,
	CID_PKCS9_AT_MESSAGEDIGEST,
	CID_PKCS9_AT_SIGNINGTIME,
	CID_PKCS9_AT_COUNTERSIGNATURE,
	CID_PKCS9_AT_RANDOMNONCE,
	CID_PKCS9_AT_SEQUENCENUMBER,


}SEC_CID_E;
	
#ifdef	__cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _SEC_SEC_H */

