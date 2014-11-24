/*
 * config.h
 *
 *	$Author: tomson $
 *	$Date: 2009/03/27 05:40:50 $
 *	$Revision: 1.30 $
 *
 *      COPYRIGHT (C) 1997,2002 RICOH COMPANY LTD.
 *      All rights reserved.
 *
 */
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "assert.h"
//#define GE2_OPTIMIZING_BEZIER
#ifdef TARGET_IRIPS

#define	DR_TARGET_IRIPS		/* LibDRAW�Ƃ̑g����            */

#define DR_TUNING_COLORBRUSH	/* �J���[�u���V�̍�����(COLOR �� HATCH��) */

#define PR2_SUPPORT_SIGNED_BRUSHORG	/* �u���V���_�� signed �Ή� */
#define PR2_SUPPORT_ROP88EE_PLURAL_IMAGES	/* ROP88EE�����C���[�W�Ή� */
#define PR2_SUPPORT_ROP66EE88_PLURAL_IMAGES	/* ROP66EE88EE88�����C���[�W�Ή� */
#define PR2_TUNING_DIRECT_INDEX_DRAW	/* INDEX �C���[�W���ڕ`�� */
#define PR2_TUNING_CONV_INDEX_BITBLT	/* Bitblt�ϊ� */
#define PR2_TUNING_CP_INDEX_TO_BITBLT/* Bitblt�ϊ� */
#define PR_HAVE_FAST_TRANSGRAY		/* �O���[�ϊ������̍����� */
#define PR_HAVE_DYNAMIC_MEMORY		/* ���I�ȃX�v�[���������Ǘ������ւ̑Ή� */
#define	PR2_SUPPORT_SAVE_CLIP_LIST	/* CLIP SAVE/RESTORE�Ή� */
#define PR2_SUPPORT_SET_PAGEPARAM_PAGEEND	/* gpsPlotSetPageParam�Ăшʒu�ύX */
#endif /* TARGET_IRIPS */

/*
 * �@�틤�ʋ@�\�̒�`
 */
//#define	USE_CMOST		/* ��𑜓xImage�̃W���M�[�␳�@�\	*/

#define	PR_TEST_WORDALIGN(x)	(((unsigned long)x) & 0x03UL)

/*
 *	followings are value of attribute bit of XRGB.
 */
#define	XRGB_ATTR_WHITE	0x00		/* attribute of white pixel.			*/
#define	XRGB_ATTR_IMAGE	0x40		/* attribute of image.					*/
#define	XRGB_ATTR_K1	0x80		/* attribute of K.						*/
#define	XRGB_ATTR_OTHER	0xc0		/* attribute of except image drawing.	*/

#define PR2_SUPPORT_CALC_CHECKSUM	/* checksum�@�\�̑Ή� */
#define PR_OBJECTMEMORY_OVERRUN_SOLUTION	/* object memory�Ή� */
#define MM_SUPPORT_ALIGNSIZE		/* libmm��alignment size�Ή��iPR2_SUPPORT_EXTENSION_INIT���K�v�j */
#define PR2_SUPPORT_EXTENSION_INIT	/* �@�\�I���\��PageRenderer������I/F(pr_init_ext())�̑Ή� */
//#define	PR_RENDERER_PARAM_CMD		/* �掿�݌v�p�����[�^�𓮓I�ɐ؂�ւ���RPCS�̊g���Ή� */
#ifdef TARGET_12A
#define TARGET_09A
#define PR_SUPPORT_FUSER_CTL2		/* New TEC Function  for AtApC3 and Later */
#endif

#ifdef TARGET_GJ
#define SUPPORT_SWITCH_BANDFLUSHMODE	/* Switch band flush mode
						   and notice it to gps */
#define SUPPORT_CUTTING_RGBVALUE	/* Correspondence for RGB ratio */
#define SUPPORT_CUTTING_TONERLIMIT	/* Correspondence for Tonerlimit ratio */
#define SUPPORT_SKIPPING_CALCTLIMIT	/* Tonerlimit is not calculated
					   (refer as not ratio but value) */
#define SUPPORT_LIMITING_K		/* Correspondence limiting k */
#define SUPPORT_COMPOSITEBLACK	/* Correspondence compositeblack draw */
#define SUPPORT_DYNAMIC_PROFILEOPEN /* Dynamic open and close profile */
#define SUPPORT_PAGE_PREFEED	/* Correspondence GPS prefeed */
#define DISABLE_DRAWFRAMELINE	/* Disable draw frame line */
#define SUPPORT_EXT_PRINTPARAM	/* Correspondence ext print param */
#endif /* TARGET_GJ */
#ifdef TARGET_KIBO
#define SUPPORT_SWITCH_BANDFLUSHMODE	/* Switch band flush mode*/
#define SUPPORT_PAGE_PREFEED	/* Correspondence GPS prefeed */
#define SUPPORT_DYNAMIC_PROFILEOPEN /* Dynamic open and close profile */
#define DISABLE_DRAWFRAMELINE	/* Disable draw frame line */
#endif /* TARGET_KIBO */

#ifdef TARGET_09A
#define TARGET_08A
#define PR_SUPPORT_FUSER_CTL	/* TEC�l���P�i�蒅���x�ጸ�j�̑Ή� */
#endif /* TARGET_09A */

#ifdef TARGET_08A
#define PR_LENGTHWISE_SCALING_UP	/* Luna 600x1200�Ή� */
#define PR2_SUPPORT_PRECEDINGINFO	/* pr_setprecedinginfo() �Ή� */
#endif /* TARGET_08A */

#if 0
/* Venus-C1�t�@���N�V�����e�X�g��QNo.00067���������邽�ߖ����Ƃ��� */
/* �P��ROP 0x66�Ή� */
#define USE_SINGLE_ROP66_DETECTION
#define USE_SINGLE_ROP66_DETECTION_WHITE
#endif /* 0 */

#define MAX_BAND_H	2048	/* �ő�o���h��		*/
#define MIN_BAND_H	256		/* �ŏ��o���h��		*/

/*
 * �@�\�}�N���Z�b�g
 */
#define PERMANENTSIZE   (1024 * 520)
#define ALLOCHEADSIZE   (1024 * 80)

#ifdef UNIX
#define	mprintf			printf
#endif

#if defined(UNIX) || defined(_WINDOWS)
#define NOTUSE_GPSLINK
#endif

#if defined(DEBUG) || defined(UNIX)
extern int dlevel;
extern int RET;
#endif


/*
 *  X86�Ή��֘A
 */
#ifdef X86
#define DSWAP(dat) ((((dat)>>8)&0xff) | (((dat)<<8)&0xff00))
#define LSWAP(dat) ((((dat)>>24)&0xff) | (((dat)>>8)&0xff00) |\
                    (((dat)<<8)&0xff0000) | (((dat)<<24)&0xff000000))
#else  /*  !X86  */
#define DSWAP(dat) (dat)
#define LSWAP(dat) (dat)
#endif  /*  !X86  */

#ifdef X86
	//  Little Endian Shifting Macros.
#define LSM8(x,n)	( (((x) << (n)) & LSM8Mask[(n)]) | (((x) >> (16 - (n)) \
                    & LSM8Mask[8+(n)])) )
#define PIX_LSHIFT(x,n)	( LSM8(((x) >> ((n) & ~7)),(n) & 7) )
#define RSM8(x,n)	( (((x) >> (n)) & RSM8Mask[(n)]) | (((x) << (16 - (n)) \
                    & RSM8Mask[8+(n)])) )
#define PIX_RSHIFT(x,n)	( RSM8(((x) << ((n) & ~7)),(n) & 7) )

#define PIX_LMASK(n)	LMask[n]
#define PIX_RMASK(n)	RMask[n]

//  Look-up Tables
static const unsigned LSM8Mask[16] = {
	0xFFFFFFFF, 0xFEFEFEFE, 0xFCFCFCFC, 0xF8F8F8F8,
	0xF0F0F0F0, 0xE0E0E0E0, 0xC0C0C0C0, 0x80808080,
	0x00000000, 0x01010101, 0x03030303, 0x07070707,
	0x0F0F0F0F, 0x1F1F1F1F, 0x3F3F3F3F, 0x7F7F7F7F,
};
static const unsigned RSM8Mask[16] = {
	0xFFFFFFFF, 0x7F7F7F7F, 0x3F3F3F3F, 0x1F1F1F1F,
	0x0F0F0F0F, 0x07070707, 0x03030303, 0x01010101,
	0x00000000, 0x80808080, 0xC0C0C0C0, 0xE0E0E0E0,
	0xF0F0F0F0, 0xF8F8F8F8, 0xFCFCFCFC, 0xFEFEFEFE,
};
static const unsigned LMask[32] = {
	0xFFFFFFFF, 0xFFFFFF7F, 0xFFFFFF3F, 0xFFFFFF1F,
	0xFFFFFF0F, 0xFFFFFF07, 0xFFFFFF03, 0xFFFFFF01,
	0xFFFFFF00, 0xFFFF7F00, 0xFFFF3F00, 0xFFFF1F00,
	0xFFFF0F00, 0xFFFF0700, 0xFFFF0300, 0xFFFF0100,
	0xFFFF0000, 0xFF7F0000, 0xFF3F0000, 0xFF1F0000,
	0xFF0F0000, 0xFF070000, 0xFF030000, 0xFF010000,
	0xFF000000, 0x7F000000, 0x3F000000, 0x1F000000,
	0x0F000000, 0x07000000, 0x03000000, 0x01000000,
};
static const unsigned RMask[32] = {
	0x00000080, 0x000000C0, 0x000000E0, 0x000000F0,
	0x000000F8, 0x000000FC, 0x000000FE, 0x000000FF,
	0x000080FF, 0x0000C0FF, 0x0000E0FF, 0x0000F0FF,
	0x0000F8FF, 0x0000FCFF, 0x0000FEFF, 0x0000FFFF,
	0x0080FFFF, 0x00C0FFFF, 0x00E0FFFF, 0x00F0FFFF,
	0x00F8FFFF, 0x00FCFFFF, 0x00FEFFFF, 0x00FFFFFF,
	0x80FFFFFF, 0xC0FFFFFF, 0xE0FFFFFF, 0xF0FFFFFF,
	0xF8FFFFFF, 0xFCFFFFFF, 0xFEFFFFFF, 0xFFFFFFFF,
};
#else
	//  Big Endian Shifting Macros.
#define PIX_LSHIFT(x,n)	( (x) << (n) )
#define PIX_RSHIFT(x,n)	( (x) >> (n) )

#define PIX_LMASK(n)	(((1 << (31-(n))) - 1) | (1 << (31-(n))))
#define PIX_RMASK(n)	(((1 << (31-(n))) - 1) ^ 0xFFFFFFFF)
#endif /* X86 */

/*
 * ����SWAP
 */
#define FLSWAP(dat) ((((dat)>>24)&0xff) | (((dat)>>8)&0xff00) |\
                    (((dat)<<8)&0xff0000) | (((dat)<<24)&0xff000000))

/*
 * �������֐��֘A
 */
#ifdef _WINDOWS
#define USE_MEMCPY		/* Windows �ɂ� bcopy() ���Ȃ� */
#define USE_MEMCMP		/* Windows �ɂ� bcmp() ���Ȃ� */
#define USE_MEMSET		/* Windows �ɂ� bzero() ���Ȃ� */
#define USE_MEMMOVE
#endif

#ifdef USE_BCMP			/* memcmp() �̑���� bcmp() ���g�� */
#define	memcmp(dst, src, len)	bcmp(src, dst, len)
#endif
#ifdef USE_MEMCPY		/* bcopy() �̑���� memcpy() ���g�� */
#define bcopy(src, dst, len)	memcpy(dst, src, len)   
#endif
#ifdef USE_MEMCMP		/* bcmp() �̑���� memcmp() ���g�� */
#define bcmp(src, dst, len)	memcmp(dst, src, len)   
#endif
#ifdef USE_MEMSET		/* bzero() �̑���� memset() ���g�� */
#define bzero(ptr, len)		memset(ptr, 0, len)
#endif
#ifndef USE_MEMMOVE		/* overlap �������֐��ő�p���� */
#define	memmove(dst, src, len)	bcopy(src, dst, len)
#endif

#ifdef __ARM
namespace {
	extern "C" void *memcpy(void *, const void *, size_t);
	extern "C" void *memset(void *, int, size_t);
	extern "C" int memcmp(const void *, const void *, size_t);
	extern "C" int strcmp(const char *, const char *);
}
#else
extern "C" void *memcpy(void *, const void *, size_t);
extern "C" void *memset(void *, int, size_t);
#endif
extern "C" void bzero(void *, size_t);

#ifdef PR_XPS_SUPPORT
#define PR_ENABLE_BLENDING_FALSE 0
#define PR_ENABLE_BLENDING_TRUE 1
#define PR_BLEND_SPACE_SRGB 1
#define PR_BLEND_SPACE_GRAY 0
#define PR_BLEND_MODE_XPS 1
#define PR_SET_ALPHA_UINT8 1
#endif

#endif /* _CONFIG_H_ */

/*
 *      COPYRIGHT (C) 1997,2002 RICOH COMPANY LTD.
 *      All rights reserved.
 */
