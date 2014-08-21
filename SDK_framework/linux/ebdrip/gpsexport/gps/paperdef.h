/************************************************************************
 * ファイル名   : paperdef.h
 * 機能概要     : GPS - 用紙情報
 * 著作者       : Copyright (C) RICOH CO., LTD. 1999, 2000.
 * 設計者       : T.Kitazawa
 * 変更履歴     : 1999-11-04 開始
 *                2000-04-25 Version 1.22
 ************************************************************************/
/*      */
#ifndef _PAPERDEF_H
#define _PAPERDEF_H
#ifdef  __cplusplus
extern "C" {
#endif  /* !__cplusplus */
/*      */
/************************************************************************
 *      #include "paper.h"
 ************************************************************************/
/*      */
/********************************************************************
 *
 *		
 *	【ファイル名】	paper.h
 *
 * 	【機種名】		Adonis-C2、Kir
 *
 *	【目的】		転写紙、原稿に関する定義
 *
 *	【参照ファイル】なし
 *
 *	【履歴】		作成`92年11月07日 （ASAP-G：田川）
 *					修正`93年 4月17日 （206G　：田川）
 *					修正'93年 7月19日 （206G　：本橋）
 *					修正`93年 7月29日 （206G　：田川）
 *						A:Ｆサイズ関係追加
 *					修正`96年10月16日 （MF2G　：田川）
 *						A:Exectiveサイズ追加
 *
 ********************************************************************/

/* 用紙サイズ・コードの定義 */

#define	GPS_CODE_Y		0
#define	GPS_CODE_T		128

enum	gps_p_sz	{
	/* 横サイズ */
	GPS_CODE_NO_PAPER = 0,
	GPS_CODE_A0,		GPS_CODE_A1,		GPS_CODE_A2,		GPS_CODE_A3,
	GPS_CODE_A4,		GPS_CODE_A5,		GPS_CODE_A6,		GPS_CODE_A7,
	GPS_CODE_B0,		GPS_CODE_B1,		GPS_CODE_B2,		GPS_CODE_B3,
	GPS_CODE_B4,		GPS_CODE_B5,		GPS_CODE_B6,		GPS_CODE_B7,
	GPS_CODE_WMAIL,		GPS_CODE_MAIL,		GPS_CODE_LINE1,		GPS_CODE_LINE2,
	GPS_CODE_LIB6,		GPS_CODE_LIB8,		GPS_CODE_210x170,	GPS_CODE_210x182,
	GPS_CODE_267x388,	GPS_CODE_SRA3,
	GPS_CODE_SRA4,

	GPS_CODE_FREEmm = 31,
	GPS_CODE_11x17,
	GPS_CODE_11x14,		GPS_CODE_10x15,		GPS_CODE_10x14,		GPS_CODE_8Hx14,
	GPS_CODE_8Hx13,		GPS_CODE_8Hx11,		GPS_CODE_8Qx14,		GPS_CODE_8Qx13,
	GPS_CODE_8x13,		GPS_CODE_8x10H,		GPS_CODE_8x10,		GPS_CODE_5Hx8H,
	GPS_CODE_7Qx10H,	GPS_CODE_17x22,

	GPS_CODE_12x18 = 47,
	GPS_CODE_12x14H,
	GPS_CODE_11x15,		GPS_CODE_9Hx11,		 GPS_CODE_8Hx12,	GPS_CODE_13x19,
	GPS_CODE_13x19Q,	GPS_CODE_13x18,

	GPS_CODE_36x48 = 55,
	GPS_CODE_24x36,		GPS_CODE_18x24,		GPS_CODE_9x12,

	GPS_CODE_34x44 = 60,
	GPS_CODE_22x34,		GPS_CODE_30x42,		GPS_CODE_21x30,

	GPS_CODE_8KAI = 66,
	GPS_CODE_16KAI,

	GPS_CODE_12_6x18_5 = 70,
	GPS_CODE_12_6x19_2,

	GPS_CODE_NO_10 = 80,
	GPS_CODE_NO_7,

	GPS_CODE_C5 = 83,
	GPS_CODE_C6,		GPS_CODE_DL,

	GPS_CODE_841mmRoll = 97,
	GPS_CODE_594mmRoll,	GPS_CODE_420mmRoll,	GPS_CODE_297mmRoll,	GPS_CODE_210mmRoll,
	GPS_CODE_660mmRoll,	GPS_CODE_440mmRoll,	GPS_CODE_880mmRoll,	GPS_CODE_800mmRoll,

	GPS_CODE_728mmRoll,	GPS_CODE_515mmRoll,	GPS_CODE_364mmRoll,	GPS_CODE_257mmRoll,
	GPS_CODE_182mmRoll,	GPS_CODE_625mmRoll,

	GPS_CODE_YOH_ENV_0 = 112,
	GPS_CODE_YOH_ENV_2, GPS_CODE_YOH_ENV_4, GPS_CODE_JAPANESE_ENV_3, GPS_CODE_JAPANESE_ENV_4,
	GPS_CODE_KAKU_ENV_2 = 119,

	GPS_CODE_226x310 = 121,
	GPS_CODE_310x432,

	/* 縦サイズ */
	GPS_CODE_NO_SIZE = 128,
	GPS_CODE_A0T,		GPS_CODE_A1T,		GPS_CODE_A2T,		GPS_CODE_A3T,
	GPS_CODE_A4T,		GPS_CODE_A5T,		GPS_CODE_A6T,		GPS_CODE_A7T,
	GPS_CODE_B0T,		GPS_CODE_B1T,		GPS_CODE_B2T,		GPS_CODE_B3T,
	GPS_CODE_B4T,		GPS_CODE_B5T,		GPS_CODE_B6T,		GPS_CODE_B7T,
	GPS_CODE_WMAILT,	GPS_CODE_MAILT,		GPS_CODE_LINE1T,	GPS_CODE_LINE2T,
	GPS_CODE_LIB6T,		GPS_CODE_LIB8T,		GPS_CODE_210x170T,	GPS_CODE_210x182T,
	GPS_CODE_267x388T,	GPS_CODE_SRA3T,
	GPS_CODE_SRA4T,

	GPS_CODE_FREEmmT = 159,
	GPS_CODE_11x17T,
	GPS_CODE_11x14T,	GPS_CODE_10x15T,	GPS_CODE_10x14T,	GPS_CODE_8Hx14T,
	GPS_CODE_8Hx13T,	GPS_CODE_8Hx11T,	GPS_CODE_8Qx14T,	GPS_CODE_8Qx13T,
	GPS_CODE_8x13T,		GPS_CODE_8x10HT,	GPS_CODE_8x10T,		GPS_CODE_5Hx8HT,
	GPS_CODE_7Qx10HT,	GPS_CODE_17x22T,

	GPS_CODE_12x18T = 175,
	GPS_CODE_12x14HT,
	GPS_CODE_11x15T,	GPS_CODE_9Hx11T,	 GPS_CODE_8Hx12T,	GPS_CODE_13x19T,
	GPS_CODE_13x19QT,	GPS_CODE_13x18T,

	GPS_CODE_36x48T = 183,
	GPS_CODE_24x36T,	GPS_CODE_18x24T,	GPS_CODE_9x12T,

	GPS_CODE_34x44T = 188,
	GPS_CODE_22x34T,	GPS_CODE_30x42T,	GPS_CODE_21x30T,

	GPS_CODE_8KAIT = 194,
	GPS_CODE_16KAIT,

	GPS_CODE_12_6x18_5T = 198,
	GPS_CODE_12_6x19_2T,

	GPS_CODE_NO_10T = 208,
	GPS_CODE_NO_7T,

	GPS_CODE_C5T = 211,
	GPS_CODE_C6T,		GPS_CODE_DL_T,

	GPS_CODE_36inchRoll = 225,
	GPS_CODE_24inchRoll,	GPS_CODE_18inchRoll,	GPS_CODE_12inchRoll,	GPS_CODE_9inchRoll,
	GPS_CODE_30inchRoll,	GPS_CODE_707mmRoll,

	GPS_CODE_490mmRoll = 232,
	GPS_CODE_680mmRoll,		GPS_CODE_34inchRoll,	GPS_CODE_22inchRoll,	GPS_CODE_17inchRoll,
	GPS_CODE_11inchRoll,	GPS_CODE_8HinchRoll,	GPS_CODE_620mmRoll,

	GPS_CODE_YOH_ENV_0T = 240,
	GPS_CODE_YOH_ENV_2T, GPS_CODE_YOH_ENV_4T, GPS_CODE_JAPANESE_ENV_3T, GPS_CODE_JAPANESE_ENV_4T,
	GPS_CODE_KAKU_ENV_2T = 247,

	GPS_CODE_226x310T = 249,
	GPS_CODE_310x432T,
};

/* 一般名称でのサイズ・コード定義 */
#define	GPS_CODE_ANSIC		GPS_CODE_17x22
#define	GPS_CODE_ANSICT		GPS_CODE_17x22T

#define	GPS_CODE_DLT		GPS_CODE_11x17
#define	GPS_CODE_DLTT		GPS_CODE_11x17T

#define	GPS_CODE_LG			GPS_CODE_8Hx14
#define	GPS_CODE_LGT		GPS_CODE_8Hx14T

#define	GPS_CODE_LT			GPS_CODE_8Hx11
#define	GPS_CODE_LTT		GPS_CODE_8Hx11T

#define GPS_CODE_HLT		GPS_CODE_5Hx8H
#define GPS_CODE_HLTT		GPS_CODE_5Hx8HT

#define	GPS_CODE_F			GPS_CODE_8x13
#define	GPS_CODE_FT			GPS_CODE_8x13T
#define	GPS_CODE_GL			GPS_CODE_8x13
#define	GPS_CODE_GLT		GPS_CODE_8x13T

#define	GPS_CODE_Foolscap	GPS_CODE_8Hx13
#define	GPS_CODE_FoolscapT	GPS_CODE_8Hx13T
#define	GPS_CODE_F4			GPS_CODE_8Hx13
#define	GPS_CODE_F4T		GPS_CODE_8Hx13T

#define	GPS_CODE_Folio		GPS_CODE_8Qx13
#define	GPS_CODE_FolioT		GPS_CODE_8Qx13T

#define	GPS_CODE_GT			GPS_CODE_8x10H
#define	GPS_CODE_GTT		GPS_CODE_8x10HT

#define	GPS_CODE_UK			GPS_CODE_8x10
#define	GPS_CODE_UKT		GPS_CODE_8x10T

#define	GPS_CODE_Exective	GPS_CODE_7Qx10H
#define	GPS_CODE_ExectiveT	GPS_CODE_7Qx10HT

/* */
#define	GPS_CODE_13x19_2	GPS_CODE_13x19Q
#define	GPS_CODE_13x19_2T	GPS_CODE_13x19QT


/* Original size only */
#define	GPS_CODE_435x310	0xFF
#define	GPS_CODE_300x250	0xFF
#define	GPS_CODE_11x14CFF	0xFF


/*      */
#ifdef  __cplusplus
}
#endif  /* !__cplusplus */
#endif  /* !_PAPERDEF_H */
/* EOF  */
