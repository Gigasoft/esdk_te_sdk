/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_3DES_H_
#define _Z_CTK_UTIL_3DES_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"

#include "hwsecure/securec.h"
#if !defined(DES3_ED_FLAG)
#define DES3_ED_FLAG
#define des3_encrypt 0
#define des3_decrypt 1
#endif

namespace ctk {

//////////////////////////////////////////////////////////////////////////
/* 3DES Class. */
class des3 
{
public:
    CTK_API static bool encode(rcistr _in, Bytes& _out, rcistr _key);
    CTK_API static bool decode(rcistr _in, Bytes& _out, rcistr _key);
	des3()
	{
		hw::memset_s(key,  8,    0, 8);
		hw::memset_s(m,    8,    0, 8);
		hw::memset_s(c,    8,    0, 8);
		hw::memset_s(k,    16*8, 0, 16*8);
		hw::memset_s(s_in, 8,    0, 8);
		hw::memset_s(pc,   64,   0, 64);
		ed_flag   =  0 ;
		hw::memset_s(x, 2, 0, 2);
	}
	~des3()
	{
	}
private:
    bool HW_DES3_Encrypt(uchar edFlag, rcistr _in, Bytes& _out, const uchar* pKey /*[8]*/);
    bool HW_DES3_Encrypt(
        uchar edFlag, //EDFlag是加\脱密标志,0表示加密，1表示脱密
        uchar* databuf/*[8]*/, //DataBuf将被处理的明文或密文的缓冲区,并兼作输出缓冲区
        const uchar* keybuf/*[8]*/ //8byte的密钥缓冲区
    );
    inline void HW_Pro_Key(void);
    inline void HW_First_p(void);
    inline void HW_Expand_X(void);
    inline void HW_Fction(void);
    inline void HW_MakeKey(bool bFirstFlag);
    static const ulong ulSp0[64],ulSp1[64],ulSp2[64],ulSp3[64],ulSp4[64],ulSp5[64],ulSp6[64],ulSp7[64];
    static const uchar pc0[64],pc0_v[64],pc1[56],pc2[48],rotate[16],bytebit[8];
    static const ulong bigbyte[24],bigbyte1[32];
    uchar key[8],m[8],c[8],k[16][8],s_in[8],pc[64];
    uchar ed_flag;
    ulong x[2];
};

} // namespace ctk

#endif //_Z_CTK_UTIL_3DES_H_

