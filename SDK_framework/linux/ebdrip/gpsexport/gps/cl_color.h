////////////////////////////////////////////////////////////////////////////////
// File Name            : cl_color.h
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CL_COLOR_H_
#define _CL_COLOR_H_

#ifdef __cplusplus
#include "pager.h"
#endif
#include "gps/device.h"

// color mode.
#define	PAGE_COLOR_K	0x00		// mono print mode.
#define	PAGE_COLOR_CMYK	0x80		// CMYK color print mode.
#define	PAGE_COLOR_RK	0x40		// RK color print mode.
#define	PAGE_COLOR_CMY	0x20		// CMY color print mode.
#define	PAGE_COLOR_MASK	0xFC		// color mode mask.
#define	PAGE_COLOR_XRGB	0x10	// XRGB color print mode.
#define	PAGE_COLOR_XG	0x08	//XG color print mode.
#define	PAGE_COLOR_RK2	0x04		// RK2 color print mode.

#define	SET_DIT_IMAG(ditmod)	((ditmod & DIT_MASK) << 6)
#define	SET_DIT_GRAP(ditmod)	((ditmod & DIT_MASK) << 4)
#define	SET_DIT_TEXT(ditmod)	((ditmod & DIT_MASK) << 2)
#define	SET_DIT_LINE(ditmod)	((ditmod & DIT_MASK) << 0)


#define NUM_CMMOBJECT	4
#define	CMM_CMYK	(0x80000000)
#define FULLX86		0x00ffffff

/* FROM PRGrawphicsDrawinfo.h*/
#define	DIT_PHOT		0	/* ï¾…ï½½ï¾ƒç’°çœŸï¾†æ–­ï¾†é�”ï¾†æ—¦ */
#define	DIT_TEXT		1	/* çª¶ï½¢ï¾‚ï½¶ï¾…ï½½ï¾…ï½¡ï¾†æ–­ï¾†é�”ï¾†æ—¦ */
#define	DIT_GRAP		2	/* ï¾†ä¸¹ï¾†å�œï¿½ï¾†ç¨šï¾†é�”ï¾†é�›ï¾†èª°ï¾†æ¹›ï¾†æ–­ï¾†é�”ï¾†æ—¦ */
#define	DIT_CAD			3	/* CADï¾†æ–­ï¾†é�”ï¾†æ—¦ */
#define	DIT_MAX			4	/* ï¾†æ–­ï¾†é�”ï¾†æ—¦ï¾…ï½½ï¾ƒï½­çª¶æ°¾æ¥ªçµ¶ï¿½ */
#define	DIT_MASK		0x03

/* GRAY MODE æŒ‡å®šã�®ã�Ÿã‚�ã�«ã‚«ãƒ©ãƒ¼ã�¨ãƒ¢ãƒŽã‚’åˆ†ã�‘ã‚‹å¿…è¦�ã�Œæœ‰ã‚‹ */
#define PR_OBJ_IMAG_COLOR			4
#define PR_OBJ_IMAG_MONO			5
#define PR_OBJ_MASK_1ST			0x07

#define GAMMA_THROUGH  //bala todo

/*
 * æ��ç”»ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆã�®ç¨®é¡ž
 * ã�“ã�®ç¨®é¡žã�«ã‚ˆã�£ã�¦ãƒ‡ã‚£ã‚¶ã‚„ K ç”Ÿæˆ�è¦�å‰‡ã‚’åˆ‡æ›¿ã�ˆã‚‹
 */
#define OBJ_IMAG	0	/* ã‚¤ãƒ¡ãƒ¼ã‚¸ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define OBJ_GRAP	1	/* ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯(å¡—ã‚Š)ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define OBJ_TEXT		2	/* æ–‡å­—ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define OBJ_LINE		3	/* ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯(ç·š)ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define OBJ_MAX		4	/* ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç¨®é¡žæ•° */
#define OBJ_MASK	0x03	/* OBJ_{IMAG,GRAP,TEXT,LINE} ç”¨ãƒžã‚¹ã‚¯ */
/* GRAY MODE æŒ‡å®šã�®ã�Ÿã‚�ã�«ã‚«ãƒ©ãƒ¼ã�¨ãƒ¢ãƒŽã‚’åˆ†ã�‘ã‚‹å¿…è¦�ã�Œæœ‰ã‚‹ */
#define OBJ_IMAG_COLOR			4
#define OBJ_IMAG_MONO			5
#define OBJ_MASK_1ST			0x07

#define	COLOR_BGMODE		0x08	// BG mode (0:FG,1:BG)
#define	COLOR_2NDFGBG		0x10	// 2nd FG/BG (0:OFF,1:ON)
#define	COLOR_2NDBGMODE		0x20	// 2nd BG mode (0:FG,1:BG)
#define	COLOR_2NDMASK		0x30	/* 2nd ãƒ¢ãƒ¼ãƒ‰æŒ‡å®šã�®ãƒžã‚¹ã‚¯       */
#define	COLOR_GRADATION		0x40	/* ã‚°ãƒ©ãƒ‡ãƒ¼ã‚·ãƒ§ãƒ³æ��ç”»æŒ‡å®š       */
#define	COLOR_SCANRULE		0x80	/* ã‚¹ã‚­ãƒ£ãƒ³ãƒ©ã‚¤ãƒ³å¤‰æ�›è¦�å‰‡       */

/*
 * ƒIƒuƒWƒFƒNƒgŽí—Þ–ˆ‚ÌƒOƒŒƒCˆó�üŽí—Þƒ‚�[ƒh
 * 	Še•`‰æƒIƒuƒWƒFƒNƒg (ƒCƒ��[ƒW�A•¶Žš�AƒOƒ‰ƒtƒBƒbƒN(�ü�A“h‚è)) ‚É�A
 * 	‚»‚ê‚¼‚ê‚Ç‚ÌƒOƒŒƒCˆó�ü•ûŽ® (G2K,CMYK,K2K) ‚Ì‚Ç‚ê‚ðŽg‚¤‚©‚ðŽ¦‚·ƒ‚�[ƒh
 * 	gmod ‚Í pagestart ‚Ì 'g' ƒIƒvƒVƒ‡ƒ“‚ÅŽw’è‚³‚ê‚é vec_gray ‚ðŽg‚¤�B
 *
 * gmod: IIGGTTLL
 *	II:	ƒCƒ��[ƒWƒIƒuƒWƒFƒNƒg—pƒOƒŒƒCˆó�ü•ûŽ®
 *	GG:	ƒOƒ‰ƒtƒBƒbƒN(“h‚è)ƒIƒuƒWƒFƒNƒg—pƒOƒŒƒCˆó�ü•ûŽ®
 *	TT:	•¶ŽšƒIƒuƒWƒFƒNƒg—pƒOƒŒƒCˆó�ü•ûŽ®
 *	LL:	�ü‰æƒIƒuƒWƒFƒNƒg—pƒOƒŒƒCˆó�ü•ûŽ®
 */
#define	GRAY_IMAG_MODE(gmod)	((gmod >> 24) & GRAY_MASK)
#define	GRAY_GRAP_MODE(gmod)	((gmod >> 16) & GRAY_MASK)
#define	GRAY_TEXT_MODE(gmod)	((gmod >> 8)  & GRAY_MASK)
#define	GRAY_LINE_MODE(gmod)	((gmod >> 0)  & GRAY_MASK)

/*
 * ã‚°ãƒ¬ã‚¤å�°åˆ·æ–¹å¼�
 *	GRAY_G2K (æ—§ GRAY_K1)
 *		ã‚°ãƒ¬ã‚¤ (R=G=B)ã�«ã�®ã�¿é»’å¤‰æ�› (K=1.0-R) ã‚’è¡Œã�ªã�†ã€‚
 *		ã��ã‚Œä»¥å¤–ã�¯ BG/UCR ã‚’æŽ›ã�‘ã‚‹ã€‚
 *		æ–‡æ›¸/è¡¨ã�§æ–‡å­—ã‚„ç½«ç·šã�®é»’ãƒˆãƒŠãƒ¼ã�«ã‚ˆã‚‹å�°åˆ·ã‚’ä¿�è¨¼ã�™ã‚‹ã€‚
 *
 *	GRAY_CMYK
 *		æ–‡å­—, ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯, ã‚¤ãƒ¡ãƒ¼ã‚¸ã�§ BG/UCR ã‚’æŽ›ã�‘ã‚‹ã€‚
 *		CMY ã‚°ãƒ©ãƒ‡ãƒ¼ã‚·ãƒ§ãƒ³ã�®éšŽèª¿é€£ç¶šæ€§ã�Œç¶­æŒ�ã�§ã��ã‚‹ã€‚
 *
 *	GRAY_K2K (æ—§ GRAY_TEXTK1)
 *		é»’ (R=G=B=0) ã�®ã�¿é»’å¤‰æ�› (K=1.0) ã‚’è¡Œã�ªã�†ã€‚
 *		ã��ã‚Œä»¥å¤–ã�¯ BG/UCR ã‚’æŽ›ã�‘ã‚‹ã€‚
 *		DTP MODE ã�ªã�©ã€�ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯ã�«ã‚ˆã‚‹ã‚°ãƒ¬ã‚¤ã�®
 *		ã‚°ãƒ©ãƒ‡ãƒ¼ã‚·ãƒ§ãƒ³ã�«ã�¯CMYã‚’ã€�æ–‡å­—ã�ªã�©ã�®ç´”é»’ã�«ã�¯
 *		é»’ï¼‘è‰²ã�§å�°åˆ·ã�™ã‚‹å ´å�ˆã�«ä½¿ç”¨ã�™ã‚‹ã€‚
 *
 *	GRAY_CMY
 *		BG/UCRã‚’ã�›ã�šå�˜ç´”ã�«RGBã�‹ã‚‰CMYã�«å¤‰æ�›ã�™ã‚‹ã€‚
 *
 *	GRAY_PIXELK
 *		ã‚«ãƒ©ãƒ¼ã‚¤ãƒ¡ãƒ¼ã‚¸ã�§ã‚‚ã‚°ãƒ¬ã‚¤ï¼ˆRï¼�Gï¼�Bï¼‰ã�§ã�‚ã‚Œã�°é»’å¤‰æ�›ã�™ã‚‹
 *             ï¼ˆæœ¬å½“ã�®GRAY_G2Kï¼‰
 *              ItBOXã�®2è‰²ï¼ˆM+K, C+Kï¼‰å¯¾å¿œã�§å¿…è¦�ã�¨ã�ªã�£ã�Ÿã€‚
 *
 *	GRAY_MAYBEK
 *		ç”»ç´ å±¥æ­´ã‚’è¦‹ã�¦GRAY->Kå¤‰æ�›ã‚’è¡Œã�ªã�†ã€‚ å�˜ç´”ã�«GRAY_G2Kã�§
 *	        ã�¯æ–‡å­—ã�ªã�©ã‚‚ã�™ã�¹ã�¦CMYKã�§æ��ç”»ã�—ã�¦ã�—ã�¾ã�†ã€‚
 *              ä¸€æ–¹ã€�GRAY_PIXELKã�§ã�¯ã‚«ãƒ©ãƒ¼ã‚¤ãƒ¡ãƒ¼ã‚¸ã�§éšŽèª¿æ€§ã�Œç¶­æŒ�ã�§ã��
 *              ã�ªã�„å ´å�ˆã�Œã�‚ã‚‹ã€‚ ç”»ç´ å�‚ç…§ç¯„å›²ã�¯8ç”»ç´ ã€‚
 *              BMLinkSå¯¾å¿œï¼ˆStretchBltã�®ã�¿ã�§é€�ã�£ã�¦ã��ã‚‹ï¼‰ã�§å¿…è¦�ã�¨ã�ªã�£ã�Ÿã€‚
 *
 *	GRAY_ABOUTK
 *		ã‚¢ãƒ—ãƒªã�ŒRâ‰’Gâ‰’Bã�§æ��ç”»ã�—ã�¦ã��ã‚‹ã�Ÿã‚�ã€�ä¸€éƒ¨ã� ã�‘4Cã�§æ��ç”»ã�•
 *	        ã‚Œã‚‹ã�¨ã�„ã�†ä»•æ§˜ã�Œã�‚ã‚Šã€�ã�“ã‚Œã‚’å›žé�¿ã�™ã‚‹ã�Ÿã‚�ã�®æ‰‹æ®µã€‚
 *	        ã�Ÿã� ã�—ã€�ãƒ‰ãƒ©ã‚¤ãƒ�å�´ã�§ã‚‚å¯¾å¿œã�§ã��ã‚‹ã�Ÿã‚�ã€�wantãƒ¬ãƒ™ãƒ«ã€‚
 *	        è¿‘ä¼¼è‰²ç¯„å›²ã�¯1
 */
#define GRAY_G2K			0	/* ã‚°ãƒ¬ã‚¤ã�®ã�¿é»’å¤‰æ�›orBG/UCR */
#define GRAY_CMYK			1	/* å¸¸ã�«BG/UCR */
#define GRAY_K2K			2	/* é»’ã�®ã�¿é»’å¤‰æ�›orBG/UCR */
#define GRAY_CMY			3	/* BG/UCRã�—ã�ªã�„(RGB->CMYã�®ã�¿) */
#define GRAY_PIXELK  		4	/* ã‚«ãƒ©ãƒ¼ã‚¤ãƒ¡ãƒ¼ã‚¸ã�§ã‚‚ã‚°ãƒ¬ã‚¤ã�®ã�¿
				   é»’å¤‰æ�›orBG/UCRï¼ˆæœ¬å½“ã�®G2Kï¼‰ */
#define GRAY_MAYBEK  		5	/* ç”»ç´ å±¥æ­´ã‚’è¦‹ã�¦GRAY->Kå¤‰æ�›ã‚’è¡Œã�ªã�† */
#define GRAY_ABOUTK   		6	/* Râ‰’Gâ‰’Bã�§GRAY->Kå¤‰æ�›ã‚’è¡Œã�ªã�† */
#define GRAY_IMAGEK			7	/* ã‚¤ãƒ¡ãƒ¼ã‚¸ã�§ã‚‚K2Kã‚’è¡Œã�ªã�†      */
#define GRAY_COMPBK			8	/* Gray change to composite k */
#define GRAY_HGRG2K			10	/* ã‚°ãƒ¬ã‚¤ã�®ã�¿é»’å¤‰æ�›orBG/UCR(é«˜å¢¨ç”¨) */
#define GRAY_HGRCMYK		11	/* å¸¸ã�«BG/UCR(é«˜å¢¨ç”¨) */

#define GRAY_MASK			0xff

#define	SET_GRAY_IMAG(gmod)	((gmod & GRAY_MASK) << 24)
#define	SET_GRAY_GRAP(gmod)	((gmod & GRAY_MASK) << 16)
#define	SET_GRAY_TEXT(gmod)	((gmod & GRAY_MASK) << 8)
#define	SET_GRAY_LINE(gmod)	((gmod & GRAY_MASK) << 0)

/*
 * ç¬¬2FG/BGç”¨ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç¨®é¡ž
 *	æ��ç”»ç¨®é¡žã�Œ PR_DRAWALTFILL ã�‹ PR_DRAWWINDFILL ã�®å ´å�ˆã�«ã€�
 *	DRAW æ��ç”»å±žæ€§ã�Œ PR_ATTR_DRAW_DEFAULT ä»¥å¤–ã� ã�£ã�Ÿå ´å�ˆã�«ä½¿ç”¨ã€‚
 */
#define	OBJ_DEF_2ND		0x00	/* ç¬¬1FG/BGã�¨å�Œã�˜å±žæ€§ */
#define	OBJ_IMAG_2ND	0x10	/* ã‚¤ãƒ¡ãƒ¼ã‚¸ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define	OBJ_GRAP_2ND	0x20	/* ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯(å¡—ã‚Š)ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define	OBJ_TEXT_2ND	0x30	/* æ–‡å­—ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define	OBJ_LINE_2ND	0x40	/* ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯(ç·š)ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ */
#define	OBJ_MASK_2ND	0x70    /* OBJ_{IMAG,GRAP,TEXT,LINE}_2ND ç”¨ãƒžã‚¹ã‚¯ */
/* GRAY MODE æŒ‡å®šã�®ã�Ÿã‚�ã�«ã‚«ãƒ©ãƒ¼ã�¨ãƒ¢ãƒŽã‚’åˆ†ã�‘ã‚‹å¿…è¦�ã�Œæœ‰ã‚‹ */
#define OBJ_IMAG_COLOR_2ND	0x50
#define OBJ_IMAG_MONO_2ND		0x60


/* FROM PRGrawphicsDrawinfo.h*/

/*
 * ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç¨®é¡žæ¯Žã�®ãƒ‡ã‚£ã‚¶ç¨®é¡žãƒ¢ãƒ¼ãƒ‰
 * 	å�„æ��ç”»ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆ (ã‚¤ãƒ¡ãƒ¼ã‚¸ã€�æ–‡å­—ã€�ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯(ç·šã€�å¡—ã‚Š)) ã�«ã€�
 * 	ã��ã‚Œã�žã‚Œã�©ã�®ãƒ‡ã‚£ã‚¶ (å†™çœŸã€�æ–‡å­—ã€�CADã€�OPTION) ã�®ã�©ã‚Œã‚’ä½¿ã�†ã�‹ã‚’ç¤ºã�™ãƒ¢ãƒ¼ãƒ‰
 * 	ditmod ã�¯8bitã�§æŒ‡å®šã�•ã‚Œã€�pagestart ã�® 'd' ã‚ªãƒ—ã‚·ãƒ§ãƒ³ã‚„
 *	setcolor ã�§æŒ‡å®šã�•ã‚Œã‚‹ã€‚
 *
 * ditmod: IIGGTTLL
 *	II:	ã‚¤ãƒ¡ãƒ¼ã‚¸ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç”¨ãƒ‡ã‚£ã‚¶ç¨®é¡ž
 *	GG:	ã‚°ãƒ©ãƒ•ã‚£ãƒƒã‚¯(å¡—ã‚Š)ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç”¨ãƒ‡ã‚£ã‚¶ç¨®é¡ž
 *	TT:	æ–‡å­—ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç”¨ãƒ‡ã‚£ã‚¶ç¨®é¡ž
 *	LL:	ç·šç”»ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆç”¨ãƒ‡ã‚£ã‚¶ç¨®é¡ž
 */
#define	DIT_IMAG_MODE(ditmod)	((ditmod >> 6) & DIT_MASK)
#define	DIT_GRAP_MODE(ditmod)	((ditmod >> 4) & DIT_MASK)
#define	DIT_TEXT_MODE(ditmod)	((ditmod >> 2) & DIT_MASK)
#define	DIT_LINE_MODE(ditmod)	((ditmod >> 0) & DIT_MASK)

#define	COLOR_GRAY			0	// GRAY mode.
#define	COLOR_RGB			1	// RGB mode.
#define	COLOR_CMYK			2	// CMYK mode.
#define	COLOR_MASK			0x03
#define	COLOR_MANUAL_DITHER	0x04	// manual dither mode
#define	COLOR_BGMODE		0x08	// BG mode (0:FG,1:BG)
#define	COLOR_2NDFGBG		0x10	// 2nd FG/BG (0:OFF,1:ON)
#define	COLOR_2NDBGMODE		0x20	// 2nd BG mode (0:FG,1:BG)
#define	COLOR_2NDMASK		0x30	/* 2nd ãƒ¢ãƒ¼ãƒ‰æŒ‡å®šã�®ãƒžã‚¹ã‚¯       */
#define	COLOR_GRADATION		0x40	/* ã‚°ãƒ©ãƒ‡ãƒ¼ã‚·ãƒ§ãƒ³æ��ç”»æŒ‡å®š       */
#define	COLOR_SCANRULE		0x80	/* ã‚¹ã‚­ãƒ£ãƒ³ãƒ©ã‚¤ãƒ³å¤‰æ�›è¦�å‰‡       */

/* FROM PRSpool.h*/
#define FUSER_CTL_AREA_OVER		0x01	/* use FuserCtlTbl index of over area limit */
/* FROM PRSpool.h*/

/*#ifndef TRUE
#define	TRUE	(1)		// Function TRUE  value
#endif
#ifndef	FALSE
#define	FALSE	(0)		// Function FALSE value
#endif*/
#ifndef NULL
#define	NULL	0		// Null character value
#endif
#define	ICL_WR		306
#define	ICL_WG		601
#define	IC_WB		117
#define	IC_WBIAS	1024

#define MAX_4C_TONER_LIMIT_RATIO 400
#define	calc_tlimit(val)	(val * 255 / 100)
#define REN_DIT_MAX 4
#define REN_OBJ_MAX 4


#define CR_OBJ_IMAG	0
#define CR_OBJ_GRAP	1
#define CR_OBJ_TEXT	2
#define	CR_OBJ_LINE	3
#define	CR_OBJ_MASK	0x03	// OBJ_{IMAG,GRAP,TEXT,LINE}

#define CR_GRAY_G2K	0
#define CR_GRAY_CMYK 1
#define CR_GRAY_K2K	2
#define CR_GRAY_CMY	3
#define	CR_GRAY_PIXELK	4
#define	CR_GRAY_MAYBEK	5
#define	CR_GRAY_ABOUTK	6
#define	CR_GRAY_IMAGEK	7
#define	CR_GRAY_COMPBK	8
#define CR_GRAY_HGRG2K	10
#define CR_GRAY_HGRCMYK 11

#define CR_GRAY_MASK	0xff
#define CR_GRAY_ABOUTRANGE      1
#define CR_GRAYABS(x)           ((x) < 0 ? -(x) : (x))
#define CR_MAYBE_RANGE  8

#define CR_JUDGE_GRAY_AFTER_CMM_ON	0	/* CMMï¾‚å�¤ï½£ï¾‚ã�¥å€‹ã‚°ï¾‚Î´å€‹ã‚¤ï¾‚æ�¿ï½»ï¾‚æ´¥ï½¨ï¾‚æ¸‰æŒ‰çŒŸæ•–ã�¥ï½°ï¾‚è¡Œï¾‚ã�¥æŒ‰ã‚„ã�Žï¾‚ï¼ˆï¾‚ãƒ‡ï¾‚ãƒ•ï¾‚ã‚©ï¾‚Î´ä»°ãƒˆï¾‚ï¼‰ */
#define CR_JUDGE_GRAY_AFTER_CMM_OFF	1	/* CMMï¾‚å�¤ï½£ï¾‚ã�¥å€‹ã‚°ï¾‚Î´å€‹ã‚¤ï¾‚æ�¿ï½»ï¾‚æ´¥ï½¨ï¾‚æ¸‰æŒ‰çŒŸæ•–ã�¥ï½°ï¾‚è¡Œï¾‚ã�¥æŒ‰ã�¥ï½­ï¾‚ã�¥æŒ‰ã�¤ï½¢ */

#define	CR_STRBLT_BPP_MASK	0x00000007	// BPP Mask
#define	CR_STRBLT_1BPP		0x00000000	// 1BPP
#define	CR_STRBLT_4BPP		0x00000001	// 4BPP 
#define	CR_STRBLT_8BPP		0x00000002	// 8BPP 
#define	CR_STRBLT_24BPP		0x00000003	// 24BPP 
#define	CR_STRBLT_32BPP		0x00000004	// 32BPP 

#define	CR_STRBLT_COLOR_MASK	0x00000038
#define	CR_STRBLT_MONO		0x00000000
#define	CR_STRBLT_RGB		0x00000008
#define	CR_STRBLT_KCMY		0x00000010
#define	CR_STRBLT_INDEX_MASK	0x000000c0	// Index Table
#define	CR_STRBLT_INDEX_OFF	0x00000000	// Index Table
#define CR_STRBLT_REVERSE	0x00000800	// on:Bit reverse    
#define CR_STRBLT_RGB_ORDER	0x00000200	// on:R,G,B  off:B,G,R 
#define	CR_STRBLT_INDEX_ON	0x00000040	// Index Table
#define	CR_STRBLT_THROUGH	0x00040000
#define	CR_STRBLT_SRCNOT	0x00200000
#define	CR_ATTR_TEXT		0x04000000
#define	CR_ATTR_MASK		0x07000000

#define	CR_GRAYP_G2K		0x0400
#define	CR_GRAYP_CMYK		0x0800
#define	CR_GRAYP_K2K		0x0C00
#define	CR_GRAYP_CMY		0x1000
#define	CR_GRAYP_PIXELK		0x1400
#define	CR_GRAYP_MAYBEK		0x1800
#define	CR_GRAYP_ABOUTK		0x1C00
#define	CR_GRAYP_IMAGEK		0x2000
#define	CR_GRAYP_HGRG2K		0x2C00
#define	CR_GRAYP_HGRCMYK	0x3000
#define	CR_GRAYP_MASK		0x3C00

#define	CR_OUTPUT_SPACE_MASK	0x70
#define	CR_OUTPUT_SPACE_MONO	0x10
#define	CR_OUTPUT_SPACE_RGB	0x20
#define	CR_OUTPUT_SPACE_CMY	0x30
#define	CR_OUTPUT_SPACE_CMYK	0x40
#define	CR_OUTPUT_SPACE_RK	0x50
#define	CR_OUTPUT_SPACE_XRGB	0x60
#define	CR_OUTPUT_SPACE_RK2	0x70

#define	CR_INPUT_ORDER_MASK	0x08
#define	CR_INPUT_ORDER_NORMAL	0x08
#define	CR_INPUT_ORDER_REVERSE	0x00

#define	CR_INPUT_SPACE_MASK	0x03
#define	CR_INPUT_SPACE_RGB	0x02
#define	CR_INPUT_SPACE_CMYK	0x01
#define	CR_INPUT_SPACE_GRAY	0x00

/* Check CMM */
#ifdef __cplusplus

// Index Table
#define	PALSZ_1		2	// 1bit pallete size.   
#define	PALSZ_4		16	// 4bit pallete size.   
#define	PALSZ_8		256	// 8bit pallete size.   
#define	PALSZ_24	0	// 24bit color pallete size.    
#define	PALSZ_1C	6	// 1bit color pallete size.     
#define	PALSZ_4C	48	// 4bit color pallete size.     
#define	PALSZ_8C	768	// 8bit color pallete size.     
#define	PALSZ_MX	1024	// 8bit CMYK color pallete size. 

#define	CR_COLORTREATMENT_OFF	0x80000000

#define	CR_DIT_MASK		0x300000
#define	CR_DIT_PHOT		0x000000
#define	CR_DIT_TEXT		0x100000
#define	CR_DIT_GRAP		0x200000
#define	CR_DIT_CAD		0x300000

#define CR_JUDGE_GRAY_MASK	0x80000
#define CR_JUDGE_GRAY_ON	0x80000
#define CR_JUDGE_GRAY_OFF	0x00000

#define	CR_UGAMMA_MASK		0x40000
#define	CR_UGAMMA_ON		0x40000
#define	CR_UGAMMA_OFF		0x00000

#define CR_CMM_MASK		0x20000
#define CR_CMM_ON		0x20000
#define CR_CMM_OFF		0x00000
#define	CR_TONERLIMIT_MASK	0x10000
#define	CR_TONERLIMIT_ON	0x10000
#define	CR_TONERLIMIT_OFF	0x00000

#define	CR_GAMMA_MASK		0x8000
#define	CR_GAMMA_ON		0x8000
#define	CR_GAMMA_OFF		0x0000

#define	CR_GRAYP_G2K		0x0400
#define	CR_GRAYP_CMYK		0x0800
#define	CR_GRAYP_K2K		0x0C00
#define	CR_GRAYP_CMY		0x1000
#define	CR_GRAYP_PIXELK		0x1400
#define	CR_GRAYP_MAYBEK		0x1800
#define	CR_GRAYP_ABOUTK		0x1C00
#define	CR_GRAYP_IMAGEK		0x2000
#define	CR_GRAYP_HGRG2K		0x2C00
#define	CR_GRAYP_HGRCMYK	0x3000
#define	CR_GRAYP_MASK		0x3C00

#define	CR_OUTPUT_ORDER_MASK	0x100
#define	CR_OUTPUT_ORDER_NORMAL	0x100
#define	CR_OUTPUT_ORDER_REVERSE	0x000

#define	CR_OUTPUT_SPACE_MASK	0x70
#define	CR_OUTPUT_SPACE_MONO	0x10
#define	CR_OUTPUT_SPACE_RGB	0x20
#define	CR_OUTPUT_SPACE_CMY	0x30
#define	CR_OUTPUT_SPACE_CMYK	0x40
#define	CR_OUTPUT_SPACE_RK	0x50
#define	CR_OUTPUT_SPACE_XRGB	0x60
#define	CR_OUTPUT_SPACE_RK2	0x70

#define	CR_INPUT_ORDER_MASK	0x08
#define	CR_INPUT_ORDER_NORMAL	0x08
#define	CR_INPUT_ORDER_REVERSE	0x00

#define	CR_INPUT_SPACE_MASK	0x03
#define	CR_INPUT_SPACE_RGB	0x02
#define	CR_INPUT_SPACE_CMYK	0x01
#define	CR_INPUT_SPACE_GRAY	0x00

#define CR_BGUCR_NORMAL		0
#define CR_BGUCR_COMPBK		1
#define CR_BGUCR_TABLE_NORMAL	0x01
#define CR_BGUCR_TABLE_COMPBK	0x02

#ifdef PR_XPS_SUPPORT
#define XPS_ATTR_PHOTO 0x0
#define XPS_ATTR_TEXT 0x40
#define XPS_ATTR_FILL 0x80
#define XPS_ATTR_LINE 0xC0
#define XPS_ATTR_MASK 0xC0

#endif

#ifdef SUPPORT_CUTTING_RGBVALUE
#define DEFAULT_RGB_RATIO 100
#define DEFAULT_TONERLIMIT_RATIO 100

#define CR_GRAP_SRCNOT_OFF 0x00
#define CR_GRAP_SRCNOT_ON 0x01
#endif

#define	CR_NUM_FOR_NONREPEAT_URF 257
#endif

#ifdef __cplusplus
#ifndef __ARM
extern "C"
{
	void abort();
}
#endif /* __ARM */
#endif

#ifdef __cplusplus
extern "C" {
#endif

void* getColorData( unsigned long pCmm, 
                    di_dropinfo_t* pDropInfo, 
                    di_tlimitinfo_t  *limit,
                    di_bgucrinfo_t* bgi_ptr,
                    di_gcrinfo_t* wishgcr, 
                    di_gcrinfo_t* gcrhgr_ptr, 
                    unsigned long cmmProfile );
void setRGB( void* pCPRColor, unsigned long ulFlag,
			 int nGrayMode, unsigned char **ppucGamma, int nObjMode,
			 int ucSpoolColor, unsigned char* pucPtr, int nOutputChannels);
int
SetcolorGG(unsigned long ulVectorGray,unsigned long ulGrayJudgeMode, unsigned char ucColorMode,
	int	toner_limit, unsigned char ucDither, di_tlimitinfo_t usLimit,
	unsigned long ulFlag,void* pCPRColor,
	unsigned char* pucPtr,
	unsigned char* pucoutPtr,
	int nObjMode,
	int nObjectType,
	unsigned char **ppucSrcGam,
	di_tlimitinfo_t  *tlimit);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// WiShGCR of BG and UCR parameters
typedef struct gcr_bgucr
{
	short* bg;
	short* ucr;
	gcr_bgucr()
	{
		bg = NULL;
		ucr = NULL;
	};
} gcr_bgucr_t;

// WiShGCR structure
typedef struct cr_gcrinfo
{
	gcr_bgucr_t CB;
	gcr_bgucr_t CG;
	gcr_bgucr_t YG;
	gcr_bgucr_t MB;
	gcr_bgucr_t MR;
	gcr_bgucr_t YR;
} cr_gcrinfo_t;

typedef struct clr_tlimit
{
	unsigned short text;
	unsigned short line;
	unsigned short phot;
	unsigned short fill;
	clr_tlimit()
	{
		text = 0;
		line = 0;
		phot = 0;
		fill = 0;
	}
} clr_tlimit_t;

#define	CR_CACHE_SIZE		2

typedef struct clr_cache
{
	unsigned long ulRGB;
	unsigned char ucK;
	unsigned char ucC;
	unsigned char ucM;
	unsigned char ucY;
} clr_cache_t;

#define	toner_limit_text	(limit->text)
#define	toner_limit_line	(limit->line)
#define	toner_limit_phot	(limit->phot)
#define	toner_limit_fill	(limit->fill)

#define	calc_tlimit(val)	(val * 255 / 100)

#define	SIZEOF_LUT	256
#define	MAX_LUT		255

// ROP
#define	CR_ROPEE	0x01

class CPRColor;

// type definition of function pointer
typedef void (*GCR_Method_pfT) (CPRColor*, int, int, int, unsigned
	char[]);

typedef void (*GCR_LIMIT_Method_pfT) (CPRColor*,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	int,
	unsigned char**);

typedef void (*LIMIT_Method_pfT) (CPRColor*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	int,
	int,
	unsigned char**);
typedef void (*TRANS_FN_TYPE) (CPRColor*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	int,
	int,
	clr_tlimit_t*,
	unsigned char**);

typedef void (* TRANS_FN_TYPE_1) (CPRColor*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	int,
	unsigned char**);
#ifdef PR_XPS_SUPPORT
typedef void (*CONVN_FN_TYPE)(CPRColor *, unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned long *,
	unsigned long *,
	int,
	unsigned char **,
	clr_tlimit_t *);
#endif
class CPRColor
{
public:
	CPRColor();

    /* CMM Instance received from CMM_init() */
	long m_lIsCmm;
	unsigned long m_ulCmmProfiles[NUM_CMMOBJECT];
    unsigned long m_ulCurId;
#ifdef SUPPORT_DYNAMIC_PROFILEOPEN
	unsigned long m_ulCurProfileGroup;
#endif
#ifdef SUPPORT_COMPOSITEBLACK
	unsigned long m_ulCmmProfilesCompbk[NUM_CMMOBJECT];
#ifdef SUPPORT_DYNAMIC_PROFILEOPEN
	unsigned long m_ulCurProfileGroupCompbk;
#endif
#endif

	/* CMM Instance */
	unsigned char m_ucBgLut[SIZEOF_LUT];	// BG look-up table
	unsigned char m_ucUcrLut[SIZEOF_LUT];	// UCR look-up table
	struct cr_gcrinfo m_sGcrInfo;		// WiShGCR parameters
	unsigned char m_ucBgHgrLut[SIZEOF_LUT];		// BG look-up table (HGR)
	unsigned char m_ucUcrHgrLut[SIZEOF_LUT];	// UCR look-up table (HGR)
	struct cr_gcrinfo m_sGcrHgrInfo;		// WiShGCR parameters (HGR)
#ifdef PR_SUPPORT_FUSER_CTL
	/*
	 * fuser temperature controlling table of current page
	 *	for (area) (photo dither -> text dither)
	 *		for (dither kind) (photo->text->graphics->cad)
	 *			for (plane) (K->C->M->Y)
	 *				for (color level)
	 */
	unsigned char m_ucFuserCtlTbl[2][DIT_MAX][4][256];
#endif /* PR_SUPPORT_FUSER_CTL */

	struct clr_tlimit m_sPqLimit;
	unsigned char* m_pucPqTbl;
	unsigned char* m_pucRPqTbl;

	struct clr_tlimit m_sPqLimitPhot;
	unsigned char* m_pucPqTblPhot;
	unsigned char* m_pucRPqTblPhot;

	struct clr_tlimit m_sPqLimitText;
	unsigned char* m_pucPqTblText;
	unsigned char* m_pucRPqTblText;

	struct clr_tlimit m_sPqLimitGrap;
	unsigned char* m_pucPqTblGrap;
	unsigned char* m_pucRPqTblGrap;

	struct clr_tlimit pqlimit_ed;
	unsigned char *pqtbl_ed;
	unsigned char *rpqtbl_ed;
#ifdef SUPPORT_CUTTING_RGBVALUE
	unsigned char m_ucRgbRatio[4];
	unsigned char m_ucRatioColorTbl[OBJ_MAX][256];
#ifdef SUPPORT_COMPOSITEBLACK
	unsigned char m_ucRgbRatioCompbk[4];
	unsigned char m_ucRatioColorTblCompbk[OBJ_MAX][256];
#endif
#endif
#ifdef SUPPORT_CUTTING_TONERLIMIT
	unsigned char m_ucTonerLimitRatio[4];
#endif
#ifdef SUPPORT_COMPOSITEBLACK
	unsigned char m_ucBgLutCompbk[SIZEOF_LUT];
	unsigned char m_ucUcrLutCompbk[SIZEOF_LUT];
	unsigned long m_ulBgucrTblFlag;	/*
					 * bgucr flag for
					 * which data had set
					 * 0x01:normal, 0x02:compbk, 0x03:both
					 */
	GCR_Method_pfT		m_pFuncGcrCompbk;	/* pointer of compbk function */
	GCR_LIMIT_Method_pfT	m_pFuncGcrLimitCompbk;
	unsigned char m_ucRenderingIsmono;
#endif
	struct CPRCmm* m_psCmmColor;
	unsigned long m_ulGrayCount;
	unsigned short m_usGrayHistory;
	unsigned long m_ulClrUsedPlane;	// KKCCMMYY
	int m_nIsPqtc;	//pqtc flag for current resolution and depth
	int m_nDevPqtc;	//pqtc flag for the printer model
	int m_nIsGcr;		// GCR presence flag
	GCR_Method_pfT m_pFuncGcr;
	GCR_Method_pfT m_pFuncGcrHgr;
	GCR_LIMIT_Method_pfT m_pFuncGcrLimit;
	GCR_LIMIT_Method_pfT m_pFuncGcrHgrLimit;
	LIMIT_Method_pfT m_pFuncLimit;
	
	int m_nRenderNColor;	// Number of Render color (equals prh->m_objRender.m_nNColor)
	unsigned char m_ucIsGrayJudge;	//ï¾‚å€‹ï½»ï¾‚å‚¬æ•–ã�¥å€‹æ��ï¾‚å˜‰ï½¦ï¾‚ã‚³ï¾‚ãƒžï¾‚Î´ç�£ãƒ‰ï¾‚ã�¥å�¯ã�¥ã�¤ã�¤ï½¢ï¾‚ã�¥ï¿½ã�¥é�´MMï¾‚å�¤ï½£ï¾‚ã�¥å€‹ã‚°ï¾‚Î´å€‹ã‚¤ï¾‚æ�¿ï½»ï¾‚æ´¥ï½¨ï¾‚ã�¥å€‹æœ‰ï¾‚é³´ï½³ï¾‚ã�¥ï½°ï¾‚é™›å´¢å •ï½¶
	clr_cache_t m_sCache[CR_CACHE_SIZE];

public:
#ifdef PR_XPS_SUPPORT
	int DoColorProcessing(CPRPageRenderer *prh);
	int SetPixelAttribute(prh_t* prh, unsigned char *pcATBuf, int&
		rnGrayMode, int& rnObjMode);
	void ApplyBgucrsGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);

	CONVN_FN_TYPE SetClrPrcsFn(uchar* pucPixAttr, int nGrayMode);
	void ApplyBgucrImageKsGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);

	void
	ApplyBgucrKeepgraysGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);
	void ApplyBgucrMaybeKeepgraysGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);
#endif
#ifdef PR_SUPPORT_FUSER_CTL
	///////////////////////////////////////////////////////////////////////////////
	//Function      :GetFuserCtlKCMY 
	//Description   :Get the Fuser temperature information for KCMY
	//Arguments     :
	//              :unsigned char ucK:[IN]
	//              :unsigned char ucC:[IN]
	//              :unsigned char ucM:[IN]
	//              :unsigned char ucY:[IN]
	//              :unsigned char *pucTbl:[IN]
	//Return value  :unsigned char
	///////////////////////////////////////////////////////////////////////////////
	inline unsigned char GetFuserCtlKCMY(unsigned char ucK, unsigned char ucC,
		unsigned char ucM, unsigned char ucY, unsigned char *pucTbl)
	{
		return (*(pucTbl + ucK) &
				*(pucTbl + 256 + ucC) &
				*(pucTbl + 256 * 2 + ucM) &
				*(pucTbl + 256 * 3 + ucY));
	}
	///////////////////////////////////////////////////////////////////////////////
	//Function      :GetFuserCtlK
	//Description   :Get the Fuser temperature information for K
	//Arguments     :
	//              :unsigned char ucK:[IN]
	//              :unsigned char *pucTbl:[IN]
	//Return value  :unsigned char
	///////////////////////////////////////////////////////////////////////////////
	inline unsigned char GetFuserCtlK(unsigned char ucK, unsigned char *pucTbl)
	{
		return (*(pucTbl + ucK));
	}
	///////////////////////////////////////////////////////////////////////////////
	//Function      :GetFuserCtlKC
	//Description   :Get the Fuser temperature information for KC
	//Arguments     :
	//              :unsigned char ucK:[IN]
	//              :unsigned char ucC:[IN]
	//              :unsigned char *pucTbl:[IN]
	//Return value  :unsigned char
	///////////////////////////////////////////////////////////////////////////////
	inline unsigned char GetFuserCtlKC(unsigned char ucK, unsigned char ucC,
		unsigned char *pucTbl)
	{
		return (*(pucTbl + ucK) &
				*(pucTbl + 256 + ucC));
	}
	int MakePaletteColor(unsigned long,
		unsigned char *,
		unsigned char *,
		unsigned char,
		int,
		int,
		unsigned long,
		clr_tlimit_t *,
		TRANS_FN_TYPE,
		unsigned char **,
		unsigned char *);
	int MakePaletteMono (unsigned long,
		unsigned char *,
		unsigned char *,
		unsigned char,
		int,
		unsigned long,
		TRANS_FN_TYPE_1,
		unsigned char **,
		unsigned char *);
#else
	int MakePaletteColor(unsigned long,
		unsigned char *,
		unsigned char *,
		int,
		int,
		clr_tlimit_t *,
		TRANS_FN_TYPE,
		unsigned char **);
	int MakePaletteMono (unsigned long,
		unsigned char *,
		unsigned char *,
		int,
		TRANS_FN_TYPE_1,
		unsigned char **);
#endif /* PR_SUPPORT_FUSER_CTL */
	TRANS_FN_TYPE SetTransrgb (unsigned long, int);
	TRANS_FN_TYPE SetTransrgbRK2 (unsigned long, int);
	TRANS_FN_TYPE_1 SetTransgray (unsigned long, int);
	TRANS_FN_TYPE SetTransrgbBrush (int);
	TRANS_FN_TYPE_1 SetTransgrayBrush (void);
	void ApplyRgb2Cmy(unsigned char[], unsigned char[]);
#ifdef SUPPORT_CUTTING_RGBVALUE
	void ApplyBgucr(unsigned char[], unsigned char[], int, unsigned long);
	void ApplyBgucrHgr(unsigned char[], unsigned char[], int, unsigned long);
	void ApplyBgucrKeepgray(unsigned char[], unsigned char[],
							int, unsigned long);
	void ApplyBgucrHgrKeepgray(unsigned char[], unsigned char[],
							int, unsigned long);
#else
	void ApplyBgucr(unsigned char[], unsigned char[]);
	void ApplyBgucrHgr(unsigned char[], unsigned char[]);
	void ApplyBgucrKeepgray(unsigned char[], unsigned char[]);
	void ApplyBgucrHgrKeepgray(unsigned char[], unsigned char[]);
#endif
	void ApplyBgucrKeepblack(unsigned char[], unsigned char[]);
#ifdef SUPPORT_COMPOSITEBLACK
	void ApplyBgucrCompbk(unsigned char[], unsigned char[], int, unsigned long);
#endif
	void ApplyBgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrsHgrGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyTwinColorRK2BgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrsGammasURF (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrsHgrGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotTwinColorRK2BgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrHgrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrHgrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrAboutKeepgray(unsigned char rgb[], unsigned char
		kcmy[]);
	void ApplyBgucrMaybeKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrAboutKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrImageKsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrImageKsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
#ifdef SUPPORT_COMPOSITEBLACK
	void ApplyBgucrCompbksGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrCompbksGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
#endif
	void ApplyRgb2CmyGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	///////////////////////////////////////////////////////////////////////////////
	//Function      :ApplyUserGammas 
	//Description   :Apply the user gamma 
	//Arguments     :
	//              :unsigned char* pucUserGamma:[IN]
	//              :int size:[IN]
	//              :unsigned char *pucValue:[IN/OUT]
	//Return value  :void
	///////////////////////////////////////////////////////////////////////////////
	void
	ApplyUserGammas(unsigned char* pucUserGamma,
		int nSize,
		unsigned char* pucValue)
	{
		if (pucUserGamma == (unsigned char*)0)
		{
			return;
		}
		for(int i=0; i<nSize; i++)
		{
			pucValue[i] = pucUserGamma[ pucValue[i] ];
		}
	}
	inline void DoGammaK(unsigned char *in_k,
		unsigned char *out_k,
		unsigned char **gamma)
	{;
		/* CMMassert (in_k && out_k);*/
		*out_k = *in_k;
	#ifdef GAMMA_THROUGH
		return;
	#endif
		ApplyUserGammas(*(gamma+m_nRenderNColor), 1, out_k);
		*out_k = (*gamma)[*out_k];
	}
	//private:
	void GammaSNoTonerLimit (unsigned char **ppucGamma,
		int nSize,
		unsigned char *pucK,
		unsigned char *pucC,
		unsigned char *pucM,
		unsigned char *pucY);
	void DoGamma(unsigned char[], int, int, clr_tlimit_t*, unsigned
		char**);
	void DoGammaRK2(unsigned char[], int, int, clr_tlimit_t*, unsigned
		char**);
	void PreDoGammaRK2(unsigned char[], int, int, clr_tlimit_t*, unsigned
		char**);
	void DoGammaS (int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma,
		int size,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y);
	void DoTonerLimits(int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma,
		int size,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y);
	int SetTonerLimitInColor (int obj_kind, clr_tlimit_t * limit);
	void UpdateLut(unsigned char *, unsigned char *,
					unsigned char *, unsigned char *);
#ifdef SUPPORT_COMPOSITEBLACK
	void UpdateLutExt(unsigned char *, unsigned char *, int);
#endif
	void MakeLut (float, float, float, float);
	/* CMMvoid GetDeviceColor (ginf_t *,
		unsigned char **,
		unsigned char *,
		unsigned char *);*/

	void TransURF2Cmyk (const unsigned char *pucSrcPtr,
		unsigned char *ptr,
		const unsigned long ulWidth,
		const unsigned long ulHeight,
		const unsigned long ulImgSize,
		unsigned char nTLimit,
		clr_tlimit_t * pVal,
		unsigned char **ppucGamma);
	void TransURFDirect (
		unsigned long ulFlag,
		unsigned long ulWidth,
		unsigned long ulHeight,
		unsigned long ulImgSize,
		unsigned char *pucSrcptr,
		unsigned char *ptr,
		unsigned char *pucIndexTable,
		unsigned char nTLimit,
		clr_tlimit_t * pVal,
		unsigned char **ppucGamma);

	void TransrgbDirect (
		unsigned long,
		int,
		unsigned char *,
		unsigned char *,
		unsigned char,
		clr_tlimit_t *,
		TRANS_FN_TYPE,
		unsigned char **gamma,
		int,
		int);
	void ApplySrcnotRgb2CmyGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	inline void GammaK(unsigned char* Blk,
		unsigned char* Cyan,
		unsigned char* Mag,
		unsigned char* Yel,
		unsigned char** Gam,
		unsigned char& KPlane)
	{
		unsigned char ucK = ~*Yel;
		ApplyUserGammas(*(Gam+m_nRenderNColor), 1, &ucK);
		*Blk = (*Gam)[ucK];
		*Cyan = 0;
		*Mag = 0;
		*Yel = 0;
		KPlane |= *Blk;
	}
	inline void GammaKcmy(unsigned char* Blk,
		unsigned char* Cyan,
		unsigned char* Mag,
		unsigned char* Yel,
		unsigned char** Gam,
		unsigned char& KPlane)
	{
		unsigned char ucK = *Yel;
		ApplyUserGammas(*(Gam+m_nRenderNColor), 1, &ucK);
		*Blk = (*Gam)[ucK];
		*Cyan = 0;
		*Mag = 0;
		*Yel = 0;
		KPlane |= *Blk;
	}
	void ApplyTwinColor (
		unsigned char rgb[],
		unsigned char kcmy[])
	{
		unsigned char R, G, B;

		R = rgb[0];
		G = rgb[1];
		B = rgb[2];

		if (R == G && G == B)
		{
			kcmy[0] = ~R;
			kcmy[1] = 0;
			kcmy[2] = kcmy[3] = 0;
			return;
		}

		kcmy[0] = 0;
		kcmy[1] = R;
		kcmy[2] = 0;
		kcmy[3] = 0;
	}
	void
	ApplyCmyk2Gray (unsigned char kcmy[])
	{
		unsigned int g;

		g = kcmy[0] + (kcmy[1] * ICL_WR + kcmy[2] * ICL_WG + kcmy[3] *
			IC_WB) / IC_WBIAS;
		if (g > 255)
			g = 255;
		kcmy[0] = g;
		kcmy[1] = 0;
		kcmy[2] = 0;
		kcmy[3] = 0;
	}
	/* CMM void SetColorGinfColorMask(prh_t *prh, int obj_mode, uchar *fgp,
		uchar *bgp,
		uchar **gamma, ginf_t * ginf, int orig_obj_mode, clr_tlimit_t
		*limit);
	void SetcolorGinfIsColor(prh_t *prh, int obj_mode, uchar *fgp,
		uchar *bgp, uchar **gamma,
		int orig_obj_mode, clr_tlimit_t *limit, ginf_t * ginf);
	int SetcolorGinfColorGradation(prh_t *prh, ginf_t *ginf,
		clr_tlimit_t *limit, int obj_mode);
	int SetcolorGinfForDespool(prh_t *prh, ginf_t *ginf,
		clr_tlimit_t *limit, int obj_mode);*/

	void SetColorGinfColorMask(unsigned long ulVectorGray,unsigned long ulGrayJudgeMode,
		unsigned char ucColorMode, int	toner_limit, unsigned long ulFlag,
		int nObjMode, unsigned char *pucFGPointer, unsigned char *pucBGPointer,
		unsigned char **ppucGamma, int nOrigObjMode, clr_tlimit_t *pLimit);
	void SetcolorGinfIsColor(unsigned long ulVectorGray,unsigned long ulGrayJudgeMode,
		unsigned char ucColorMode, int toner_limit, unsigned long ulFlag,int nObjMode,unsigned char *pucFGPointer, unsigned char *pucBGPointer, unsigned char **ppucGamma,
		int nOrigObjMode, clr_tlimit_t *pLimit);
	void SetIsGrayJudge (unsigned long ulGrayJudgeMode, int nObjMode);

	void SetTransgcr(void);
	// CMMvoid SetIsGrayJudge(prh_t *prh, int obj_mode);
#ifdef SUPPORT_CUTTING_RGBVALUE
	void CPRColor::SetRgbRatioAndTable(unsigned char ucMode,
		unsigned char ucPhot,
		unsigned char ucFill,
		unsigned char ucText,
		unsigned char ucLine);
#endif /* SUPPORT_CUTTING_RGBVALUE */
#ifdef SUPPORT_COMPOSITEBLACK
	int CheckCompbk(void);
#endif
#ifdef PR3_SUPPORT_GIPA1
	int GetGrayMode(unsigned long ulColorFlag);
#endif
	/* CMMbool IsUseColorBrush(CPRPageRenderer * prh,
		int nObjectType,
		CPRPrintElement * pobjPrintElement,
		int &nBrushUsedPlane);*/
};

#ifdef SUPPORT_CUTTING_RGBVALUE
#define ApplyRgbRatioRgb(pobjColor, pucR, pucG, pucB, nSize, \
		nObjKind, ulSrcNot) \
{ \
	int nRatio = (pobjColor)->m_ucRgbRatio[(nObjKind)]; \
	unsigned char *pucTbl; \
	unsigned char *pucTempR, *pucTempG, *pucTempB; \
	int nCnt; \
	pucTbl = &((pobjColor)->m_ucRatioColorTbl[(nObjKind)][0]); \
	pucTempR = (pucR); \
	pucTempG = (pucG); \
	pucTempB = (pucB); \
	if (nRatio != 100) { \
		if ((ulSrcNot)) { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = 255 - *(pucTbl + 255 - *pucTempR); \
				*pucTempG = 255 - *(pucTbl + 255 - *pucTempG); \
				*pucTempB = 255 - *(pucTbl + 255 - *pucTempB); \
			} \
		} else { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = *(pucTbl + *pucTempR); \
				*pucTempG = *(pucTbl + *pucTempG); \
				*pucTempB = *(pucTbl + *pucTempB); \
			} \
		} \
	} \
}

#define ApplyRgbRatioGray(pobjColor, pucK, nSize, nObjKind, ulSrcNot) \
{ \
	int nRatio = (pobjColor)->m_ucRgbRatio[(nObjKind)]; \
	unsigned char *pucTbl; \
	unsigned char *pucTempK; \
	int nCnt; \
	pucTbl = &((pobjColor)->m_ucRatioColorTbl[(nObjKind)][0]); \
	pucTempK = (pucK); \
	if (nRatio != 100) { \
		if ((ulSrcNot)) { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, pucTempK++) { \
				*pucTempK = *(pucTbl + *pucTempK); \
			} \
		} else { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, pucTempK++) { \
				*pucTempK = 255 - *(pucTbl + 255 - *pucTempK); \
			} \
		} \
	} \
}

#ifdef SUPPORT_COMPOSITEBLACK
#define ApplyRgbRatioRgbCompbk(pobjColor, pucR, pucG, pucB, nSize, \
		nObjKind, ulSrcNot) \
{ \
	int nRatio = (pobjColor)->m_ucRgbRatioCompbk[(nObjKind)]; \
	unsigned char *pucTbl; \
	unsigned char *pucTempR, *pucTempG, *pucTempB; \
	int nCnt; \
	pucTbl = &((pobjColor)->m_ucRatioColorTblCompbk[(nObjKind)][0]); \
	pucTempR = (pucR); \
	pucTempG = (pucG); \
	pucTempB = (pucB); \
	if (nRatio != 100) { \
		if ((ulSrcNot)) { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = 255 - *(pucTbl + 255 - *pucTempR); \
				*pucTempG = 255 - *(pucTbl + 255 - *pucTempG); \
				*pucTempB = 255 - *(pucTbl + 255 - *pucTempB); \
			} \
		} else { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = *(pucTbl + *pucTempR); \
				*pucTempG = *(pucTbl + *pucTempG); \
				*pucTempB = *(pucTbl + *pucTempB); \
			} \
		} \
	} \
}
#endif
#endif /* SUPPORT_CUTTING_RGBVALUE */
extern void MakeLut (CPRColor*,
	float,
	float,
	float,
	float);
#ifdef SUPPORT_CUTTING_RGBVALUE
extern void ApplyRgb2Gray (CPRColor *, unsigned char[], int, unsigned long);
#else
extern void ApplyRgb2Gray (unsigned char[]);
#endif

extern void ApplyTwinColorGammas (CPRColor*,
	unsigned char[],
	unsigned char[],
	unsigned char[],
	unsigned char[],
	unsigned char[],
	int,
	unsigned char **);
//extern void ApplyCmyk2Gray (unsigned char[]);

#ifdef	PR_HAVE_XRGB_DRAW
extern void SetXRGBbyPixel(CPRColor*, int, unsigned char *, unsigned
	char *);
extern void SetRGBXbyPlaner(CPRColor*, unsigned char *,
	unsigned char *, unsigned char *, unsigned char *,
	int, int, clr_tlimit_t *, unsigned char **);
#endif

/* CMM
int
PrRgb2Cmyk (prh_t * prh,
	uchar obj,
	uchar r,	// IN
	uchar g,	// IN
	uchar b,	// IN
	uchar * c,	// OUT
	uchar * m,	// OUT
	uchar * y,	// OUT
	uchar * k);	// OUT

int
PrRgb2CmykPixels (prh_t * prh,
	uchar obj,
	uchar * pucRgb,		// IN
	uchar * pucCmyk,	// OUT
	ulong ulSize);

int
PrRgb2K (prh_t * prh,
	uchar obj,
	uchar r,	// IN
	uchar g,	// IN
	uchar b,	// IN
	uchar * k);	// OUT

int
PrRgb2KPixels (prh_t * prh,
	uchar obj,
	uchar * pucRgb,		// IN
	uchar * pucK,		// OUT
	ulong ulSize);
CMM*/
/* CMM
#if defined(PR_SUPPORT_FUSER_CTL) || defined(USE_SINGLE_ROP66_PARTIAL_DETECTION)
int SetcolorGinf (CPRPageRenderer * prh,
	ginf_t * ginf,
	int obj_mode,
	int obj_type,
	long lSx,
	long lEx,
	long lSy,
	long lEy,
	uchar ucCoordFlag,
	CPRPrintElement * pobjPrintElement = NULL);
#else
int SetcolorGinf (CPRPageRenderer * prh,
	ginf_t * ginf,
	int obj_mode,
	int obj_type,
	CPRPrintElement * pobjPrintElement = NULL);
#endif
CMM*/
#ifdef PR_XPS_SUPPORT
static void TransrgbBgucrPhotXPS(CPRColor* color, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrTextXPS(CPRColor *color, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void
TransrgbBgucrImageKPhotXPS(CPRColor *color, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);

static void TransrgbBgucrImageKTextXPS(CPRColor *color, unsigned char
	*pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrKeepgrayTextXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrKeepgrayPhotXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrMaykeepgrayTextXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrMaykeepgrayTextXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
#endif // __cplusplus
#endif // PR_XPS_SUPPORT
#endif // _CL_COLOR_H_


