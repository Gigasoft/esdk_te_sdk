/*******************************************************************************
*                                                                              *
*                Copyright 2003, Huawei Technologies Co. Ltd.                  *
*                            ALL RIGHTS RESERVED                               *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*                              sec_crypto.h                                    *
*                                                                              *
*  Project Code: SeCert                                                        *
*   Module Name: Crypto Module                                                 *
*  Date Created: 2005-07-13                                                    *
*        Author: Jimmy Bahuleyan, Sanjay Vasudevan                             *
*   Descrption: Contains various crypto interface functions		               *
*------------------------------------------------------------------------------*
*  Modification History                                                        *
*  DATE        NAME             DESCRIPTION                                    *
*  --------------------------------------------------------------------------  *
*  2006-07-31   Siva Kumar.K    Added a new interface and ID's to enable       *
*                               SSX31B HW support                              *
*  2006-08-09   Satish          Added new Algorithm ID's for SCB2              *
*******************************************************************************/

#ifndef _CRYPT_H
#define _CRYPT_H

#ifdef __cplusplus
extern  "C" {
#endif


#include "sec_sys.h"


#define ALGID_UNKNOWN   0

/* The following Symmetric Block algorithms belong to the four modes
	ECB - Electronic Code Book
	CBC - Cipher Block Chaining
	OFB - Output FeedBack
	CFB - Cipher FeedBack
*/

#define ALGID_DES_ECB					CID_DES_ECB		/* identifies DES algorithm in ECB mode */
#define ALGID_DES_CBC					CID_DES_CBC		/* identifies DES algorithm in CBC mode */
#define ALGID_DES_OFB					CID_DES_OFB		/* identifies DES algorithm in OFB mode */
#define ALGID_DES_CFB					CID_DES_CFB		/* identifies DES algorithm in CFB mode */

/* ID's for supporting SSX31B HW */
#define ALGID_SCB2_128_ECB				CID_SCB2_128_ECB    /* identifies SCB2-128 algorithm in ECB mode */
#define ALGID_SCB2_128_CBC				CID_SCB2_128_CBC    /* identifies SCB2-128 algorithm in CBC mode */
#define ALGID_SCB2_256_ECB				CID_SCB2_256_ECB	/* identifies SCB2-256 algorithm in ECB mode */
#define ALGID_SCB2_256_CBC				CID_SCB2_256_CBC	/* identifies SCB2-256 algorithm in CBC mode */

#define ALGID_DES_EDE_ECB				CID_DES_EDE_ECB	/* identifies 2 key triple DES algorithm in ECB mode */
#define ALGID_DES_EDE_CBC				CID_DES_EDE_CBC	/* identifies 2 key triple DES algorithm in CBC mode */
#define ALGID_DES_EDE_OFB				CID_DES_EDE_OFB	/* identifies 2 key triple DES algorithm in OFB mode */
#define ALGID_DES_EDE_CFB				CID_DES_EDE_CFB	/* identifies 2 key triple DES algorithm in CFB mode */

#define ALGID_DES_EDE3_ECB				CID_DES_EDE3_ECB/* identifies 3 key triple DES algorithm in ECB mode */
#define ALGID_DES_EDE3_CBC				CID_DES_EDE3_CBC/* identifies 3 key triple DES algorithm in CBC mode */
#define ALGID_DES_EDE3_OFB				CID_DES_EDE3_OFB/* identifies 3 key triple DES algorithm in OFB mode */
#define ALGID_DES_EDE3_CFB				CID_DES_EDE3_CFB/* identifies 3 key triple DES algorithm in CFB mode */

#define ALGID_AES128_ECB				CID_AES128_ECB	/* identifies AES-128 algorithm in ECB mode */
#define ALGID_AES128_CBC				CID_AES128_CBC	/* identifies AES-128 algorithm in CBC mode */
#define ALGID_AES128_OFB				CID_AES128_OFB	/* identifies AES-128 algorithm in OFB mode */
#define ALGID_AES128_CFB				CID_AES128_CFB	/* identifies AES-128 algorithm in CFB mode */

#define ALGID_AES192_ECB				CID_AES192_ECB	/* identifies AES-192 algorithm in ECB mode */
#define ALGID_AES192_CBC				CID_AES192_CBC	/* identifies AES-192 algorithm in CBC mode */
#define ALGID_AES192_OFB				CID_AES192_OFB	/* identifies AES-192 algorithm in OFB mode */
#define ALGID_AES192_CFB				CID_AES192_CFB	/* identifies AES-192 algorithm in CFB mode */

#define ALGID_AES256_ECB				CID_AES256_ECB	/* identifies AES-256 algorithm in ECB mode */
#define ALGID_AES256_CBC				CID_AES256_CBC	/* identifies AES-256 algorithm in CBC mode */
#define ALGID_AES256_OFB				CID_AES256_OFB	/* identifies AES-256 algorithm in OFB mode */
#define ALGID_AES256_CFB				CID_AES256_CFB	/* identifies AES-256 algorithm in CFB mode */

#define ALGID_RC4						CID_RC4			/* identifies the RC4 algorithm */

#define ALGID_RSA						CID_RSA			/* identifies the RSA algorithm */
#define ALGID_DSA						CID_DSA			/* identifies the DSA algorithm */
#define ALGID_ECDSA						CID_ECDSA		/* identifies the ECDSA algorithm */
#define ALGID_DH						CID_DH			/* identifies the Diffie-Hellman algorithm */
#define	ALGID_ECDH						CID_ECDH		/* identifies the EC Diffie-Hellman algorithm */

#define ALGID_MD5						CID_MD5			/* identifies the MD5 hash algorithm */
#define ALGID_SHA1						CID_SHA1		/* identifies the SHA1 hash algorithm */
#define ALGID_SHA224					CID_SHA224		/* identifies the SHA224 hash algorithm */
#define ALGID_SHA256					CID_SHA256		/* identifies the SHA256 hash algorithm */
#define ALGID_SHA384					CID_SHA384		/* identifies the SHA384 hash algorithm */
#define ALGID_SHA512					CID_SHA512		/* identifies the SHA512 hash algorithm */

#define ALGID_HMAC_MD5					CID_HMAC_MD5	/* identifies hmac with MD5 */
#define ALGID_HMAC_SHA1					CID_HMAC_SHA1	/* identifies hmac with SHA1 */
#define ALGID_HMAC_SHA224				CID_HMAC_SHA224	/* identifies hmac with SHA224 */
#define ALGID_HMAC_SHA256				CID_HMAC_SHA256	/* identifies hmac with SHA256 */
#define ALGID_HMAC_SHA384				CID_HMAC_SHA384	/* identifies hmac with SHA384 */
#define ALGID_HMAC_SHA512				CID_HMAC_SHA512	/* identifies hmac with SHA512 */


#define ALGID_MD5WITHRSA				CID_MD5WITHRSA	/* identifies signature using MD5 and RSA */
#define ALGID_SHA1WITHRSA				CID_SHA1WITHRSA	/* identifies signature using SHA1 and RSA */
#define ALGID_SHA1WITHRSAOLD			CID_SHA1WITHRSAOLD	/* identifies signature using SHA1 and RSA (coresponds to old Oid)*/
#define ALGID_DSA_WITH_SHA1				CID_DSAWITHSHA1	/* identifies signature using SHA1 and DSA */
#define ALGID_DSAWITHSHA1_2				CID_DSAWITHSHA1_2	/* identifies signature using SHA1 and DSA */
#define ALGID_ECDSA_WITH_SHA1			CID_ECDSAWITHSHA1	/* identifies signature using SHA1 and ECDSA */
#define ALGID_SHA256WITHRSAENCRYPTION	CID_SHA256WITHRSAENCRYPTION	/* identifies signature using SHA256 and RSA */
#define ALGID_SHA384WITHRSAENCRYPTION	CID_SHA384WITHRSAENCRYPTION	/* identifies signature using SHA384 and RSA */
#define ALGID_SHA512WITHRSAENCRYPTION	CID_SHA512WITHRSAENCRYPTION	/* identifies signature using SHA512 and RSA */



/*! Mask out the pad info to get alg_id */
#define	CRYPT_MASK_PAD(x)		((SEC_UINT32)((x) & 0xFFFF))



/*! Macro to mask out the pad info to get alg_id */
#define	CRYPT_MASK_PAD(x)		((SEC_UINT32)((x) & 0xFFFF))

/*! Macros to get & set the pad mode of a symmetric algorithm */
/* the parameter 'a' must be an l-value */
#define	CRYPT_SET_PAD_MODE(a,m)	((a) |= (((SEC_UINT32)(m))<<16))
#define	CRYPT_RESET_PAD_MODE(a)	((a) &= 0x0000ffff)
#define	CRYPT_GET_PAD_MODE(a)	(((SEC_UINT32)(a)) >> 16)


/*! Specifies the result of a comparison operation */
#define	SEC_CRYPT_MATCH		0UL	/* compared values match when comparison function returns SEC_CRYPT_MATCH */
#define	SEC_CRYPT_NO_MATCH	1UL /* compared values do not match when comparison function returns SEC_CRYPT_MATCH */

/*! The maximum size of a digest */
#define MAX_DIGEST_SIZE		64UL	/*! Maximum possible size of a digest, same as size of SHA512 digest */
/*! The maximum size of a symmetric alg key */
#define MAX_KEY_LENGTH		32UL
/*! The maximum size of a symmetric alg block */
#define MAX_BLOCK_LENGTH	16UL
/*! The maximum size of a symmetric alg IV */
#define MAX_IV_LENGTH		MAX_BLOCK_LENGTH

/*! Operating modes for symmetric algorithm */
#define	SYMALG_STREAM_CIPHER	0x0UL
#define	SYMALG_ECB_MODE		0x1UL
#define	SYMALG_CBC_MODE		0x2UL
#define	SYMALG_CFB_MODE		0x3UL
#define	SYMALG_OFB_MODE		0x4UL
#define INVALID_SYMALG_MODE		0x5UL

/*! algorithm type */



/*! Block cipher padding types */
/*! add a 1 followed by 0  or many 0 */
#define BLOCK_PADDING_ONEZERO	0x0L
/*!  add n to construct a whole block */
#define BLOCK_PADDING_NORMAL	0x1L
/*! no padding */
#define	BLOCK_PADDING_NONE		0x2L

/*! RSA padding type */
/*! default type of padding mode */
#define	RSA_DEFAULT_PADDING		0x0L
/*! no padding */
#define RSA_NO_PADDING			0x1L
/*! pad with random bytes containing no 0 */
#define RSA_PKCS1_PADDING		0x2L
/*! pad with random bytes containing no 0 and 8 LSB of pad set to 3 - TLSv1 */
#define RSA_SSLV23_PADDING		0x4L
/*! OAEP padding as in PKCS1 */
#define RSA_PKCS1_OAEP_PADDING	0x8L


/*!
 * The below GROUPID macros identify CURVEs defined by X9.62 standard Appendix J
 * optimal basis is not supported
 *
 * The macros should be used as arguments to the CRYPT_createECParamsById function
 */
#define       GROUPID_X9_62_C2PNB163V1		1
#define       GROUPID_X9_62_C2PNB163V2		2
#define       GROUPID_X9_62_C2PNB163V3		3
#define		  GROUPID_X9_62_C2PNB176W1		4
#define       GROUPID_X9_62_C2TNB191V1		5
#define       GROUPID_X9_62_C2TNB191V2		6
#define       GROUPID_X9_62_C2TNB191V3		7
#define       GROUPID_X9_62_C2ONB191V4		0
#define       GROUPID_X9_62_C2ONB191V5		0

#define       GROUPID_X9_62_C2PNB208W1		8
#define       GROUPID_X9_62_C2TNB239V1		9
#define       GROUPID_X9_62_C2TNB239V2		10
#define       GROUPID_X9_62_C2TNB239V3		11
#define       GROUPID_X9_62_C2ONB239V4		0
#define       GROUPID_X9_62_C2ONB239V5		0

#define       GROUPID_X9_62_C2PNB272W1		12
#define       GROUPID_X9_62_C2PNB304W1		13
#define       GROUPID_X9_62_C2TNB359V1		14
#define       GROUPID_X9_62_C2PNB368W1		15
#define       GROUPID_X9_62_C2TNB431R1		16

#define       GROUPID_X9_62_PRIME192V1		17
#define       GROUPID_X9_62_PRIME192V2		18
#define       GROUPID_X9_62_PRIME192V3		19
#define       GROUPID_X9_62_PRIME239V1		20
#define       GROUPID_X9_62_PRIME239V2		21
#define       GROUPID_X9_62_PRIME239V3		22
#define       GROUPID_X9_62_PRIME256V1		23

/*******************************************************************************
*    Func Name:  CRYPT_encrypt		  									       *
********************************************************************************/

/**  @brief  This encrypts plaintext to get ciphertext using symmetric encryption.
*   	 @param[in]:ulAlgId, The algorithm Id
*@param	pucKey	The key value to be used
*@param	ulKeyLen	The length of the key
*@param	pucIV	InitializationVector(CBC,CFB,OFB algorithm modes)
*@param	ulIVLen	Length of IV. pass 0 if no IV
*@param	pucPlainText	Plaintext to be encrypted
*@param	ulPlainLen	Length of plaintext
*   	@param[out]:pucCipherText	Encrypted ciphertext
*@param	pulCLen	Length of encrypted ciphertext
*   	@return \n  SEC_UINT32, the return code. The possible values are:
*				 @li SEC_ERR_MALLOC_FAIL	:Memory allocation failure
*				 @li SEC_ERR_INVALID_ALGID  : Invalid Algorithm Id
	*				 @li SEC_CRYPT_ERR_UNDEFINED_PADDING : Invalid Padding Mode. Padding mode
	*													set on Algorithm is not defined
*				 @li SEC_ERR_INVALID_KEY_LEN : Invalid Keylength for alg.
*			     @li SEC_ERR_INVALID_IV_LEN : Invalid IVlength for alg
*                @li SEC_ERR_INVALID_DATA_LEN, Invalid plaintext length given for encryption
*												and padding_mode = BLOCK_PADDING_NONE.
*												(plaintext length was not integral no. of blocks)
*                @li SEC_SUCCESS : Successful return
*                @li SEC_ERR_INITLIB       : if the Library is not initialized
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_encrypt (
	SEC_UINT32 ulAlgId,
	SEC_UCHAR * pucKey,
	SEC_UINT32 ulKeyLen,
	SEC_UCHAR * pucIV,
 	SEC_UINT32 ulIVLen,
	SEC_UCHAR * pucPlainText,
	SEC_UINT32 ulPlainLen,
	SEC_UCHAR * pucCipherText,
	SEC_UINT32 * pulCLen);

/**  @brief  This function decrypts ciphertext to get plaintext using symmetric decryption.
*   	 @param[in]:ulAlgId	The algorithm Id
*@param	pucKey	The key value to be used
*@param	ulKeyLen	The length of the key
*@param	pucIV	InitializationVector(CBC	FB,OFB modes)
*@param	 pucCipherText	 to be decrypted ciphertext
*@param	ulCLen	Length of  ciphertext
*@param	ulIVLen	Length of IV. pass 0 if no IV
*   	@param[out]:pucPlainText	decrypted Plaintext
*@param	pulPLen	Length of plaintext
*   	@return \n  SEC_UINT32, the return code. The possible values are:
*				 @li SEC_ERR_MALLOC_FAIL	:Memory allocation failure
*				 @li SEC_ERR_INVALID_ALGID  : Invalid Algorithm Id
*				 @li SEC_CRYPT_ERR_UNDEFINED_PADDING : Invalid Padding Mode. Padding mode
*													set on Algorithm is not defined
*				 @li SEC_CRYPT_ERR_INVALID_PADDING : The pad bits are incorrect.  When after
*												decrypting the padding bits dont match the pad mode.
*												It can be due to incorrect Key or IV as that will produce
*												junk plaintext with random padding bits, which dont
*												match the padding mode.
*				 @li SEC_ERR_INVALID_KEY_LEN : Invalid Keylength for alg
*			     @li SEC_ERR_INVALID_IV_LEN : Invalid IVlength for alg
*                @li SEC_ERR_INVALID_DATA_LEN, Invalid ciphertext length given for decryption in update.
*												(ciphertext length was not integral no. of blocks)
*                @li SEC_SUCCESS : Successful return
*                @li SEC_ERR_INITLIB       : if the Library is not initialized
*/

CRYPTOLINKDLL SEC_UINT32 CRYPT_decrypt (
	SEC_UINT32 ulAlgId,
	const SEC_UCHAR * pucKey,
	SEC_UINT32 ulKeyLen,
	const SEC_UCHAR * pucIV,
	SEC_UINT32 ulIVLen,
	SEC_UCHAR * pucCipherText,
	SEC_UINT32 ulCLen,
	SEC_UCHAR * pucPlainText,
	SEC_UINT32 * pulPLen);

#ifdef __cplusplus
}
#endif

#endif /* _CRYPT_H */


