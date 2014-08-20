#ifndef __DI_PAPERDEF_H__
#define __DI_PAPERDEF_H__

/* 用紙サイズ・コードの定義 */

#define	DI_CODE_Y		0
#define	DI_CODE_T		128

enum	di_p_sz	{
	/* 横サイズ */
	DI_CODE_NO_PAPER = 0,
	DI_CODE_A0,		DI_CODE_A1,		DI_CODE_A2,		DI_CODE_A3,
	DI_CODE_A4,		DI_CODE_A5,		DI_CODE_A6,		DI_CODE_A7,
	DI_CODE_B0,		DI_CODE_B1,		DI_CODE_B2,		DI_CODE_B3,
	DI_CODE_B4,		DI_CODE_B5,		DI_CODE_B6,		DI_CODE_B7,
	DI_CODE_WMAIL,		DI_CODE_MAIL,		DI_CODE_LINE1,		DI_CODE_LINE2,
	DI_CODE_LIB6,		DI_CODE_LIB8,		DI_CODE_210x170,	DI_CODE_210x182,
	DI_CODE_267x388,	DI_CODE_SRA3,
	DI_CODE_SRA4,

	DI_CODE_FREEmm = 31,
	DI_CODE_11x17,
	DI_CODE_11x14,		DI_CODE_10x15,		DI_CODE_10x14,		DI_CODE_8Hx14,
	DI_CODE_8Hx13,		DI_CODE_8Hx11,		DI_CODE_8Qx14,		DI_CODE_8Qx13,
	DI_CODE_8x13,		DI_CODE_8x10H,		DI_CODE_8x10,		DI_CODE_5Hx8H,
	DI_CODE_7Qx10H,	DI_CODE_17x22,

	DI_CODE_12x18 = 47,
	DI_CODE_12x14H,
	DI_CODE_11x15,		DI_CODE_9Hx11,		 DI_CODE_8Hx12,	DI_CODE_13x19,
	DI_CODE_13x19Q,	DI_CODE_13x18,

	DI_CODE_36x48 = 55,
	DI_CODE_24x36,		DI_CODE_18x24,		DI_CODE_9x12,

	DI_CODE_34x44 = 60,
	DI_CODE_22x34,		DI_CODE_30x42,		DI_CODE_21x30,

	DI_CODE_8KAI = 66,
	DI_CODE_16KAI,

	DI_CODE_12_6x18_5 = 70,
	DI_CODE_12_6x19_2,

	DI_CODE_NO_10 = 80,
	DI_CODE_NO_7,

	DI_CODE_C5 = 83,
	DI_CODE_C6,		DI_CODE_DL,

	DI_CODE_841mmRoll = 97,
	DI_CODE_594mmRoll,	DI_CODE_420mmRoll,	DI_CODE_297mmRoll,	DI_CODE_210mmRoll,
	DI_CODE_660mmRoll,	DI_CODE_440mmRoll,	DI_CODE_880mmRoll,	DI_CODE_800mmRoll,

	DI_CODE_728mmRoll,	DI_CODE_515mmRoll,	DI_CODE_364mmRoll,	DI_CODE_257mmRoll,
	DI_CODE_182mmRoll,	DI_CODE_625mmRoll,

	DI_CODE_YOH_ENV_0 = 112,
	DI_CODE_YOH_ENV_2, DI_CODE_YOH_ENV_4, DI_CODE_JAPANESE_ENV_3, DI_CODE_JAPANESE_ENV_4,
	DI_CODE_KAKU_ENV_2 = 119,

	DI_CODE_226x310 = 121,
	DI_CODE_310x432,

	/* 縦サイズ */
	DI_CODE_NO_SIZE = 128,
	DI_CODE_A0T,		DI_CODE_A1T,		DI_CODE_A2T,		DI_CODE_A3T,
	DI_CODE_A4T,		DI_CODE_A5T,		DI_CODE_A6T,		DI_CODE_A7T,
	DI_CODE_B0T,		DI_CODE_B1T,		DI_CODE_B2T,		DI_CODE_B3T,
	DI_CODE_B4T,		DI_CODE_B5T,		DI_CODE_B6T,		DI_CODE_B7T,
	DI_CODE_WMAILT,	DI_CODE_MAILT,		DI_CODE_LINE1T,	DI_CODE_LINE2T,
	DI_CODE_LIB6T,		DI_CODE_LIB8T,		DI_CODE_210x170T,	DI_CODE_210x182T,
	DI_CODE_267x388T,	DI_CODE_SRA3T,
	DI_CODE_SRA4T,

	DI_CODE_FREEmmT = 159,
	DI_CODE_11x17T,
	DI_CODE_11x14T,	DI_CODE_10x15T,	DI_CODE_10x14T,	DI_CODE_8Hx14T,
	DI_CODE_8Hx13T,	DI_CODE_8Hx11T,	DI_CODE_8Qx14T,	DI_CODE_8Qx13T,
	DI_CODE_8x13T,		DI_CODE_8x10HT,	DI_CODE_8x10T,		DI_CODE_5Hx8HT,
	DI_CODE_7Qx10HT,	DI_CODE_17x22T,

	DI_CODE_12x18T = 175,
	DI_CODE_12x14HT,
	DI_CODE_11x15T,	DI_CODE_9Hx11T,	 DI_CODE_8Hx12T,	DI_CODE_13x19T,
	DI_CODE_13x19QT,	DI_CODE_13x18T,

	DI_CODE_36x48T = 183,
	DI_CODE_24x36T,	DI_CODE_18x24T,	DI_CODE_9x12T,

	DI_CODE_34x44T = 188,
	DI_CODE_22x34T,	DI_CODE_30x42T,	DI_CODE_21x30T,

	DI_CODE_8KAIT = 194,
	DI_CODE_16KAIT,

	DI_CODE_12_6x18_5T = 198,
	DI_CODE_12_6x19_2T,

	DI_CODE_NO_10T = 208,
	DI_CODE_NO_7T,

	DI_CODE_C5T = 211,
	DI_CODE_C6T,		DI_CODE_DL_T,

	DI_CODE_36inchRoll = 225,
	DI_CODE_24inchRoll,	DI_CODE_18inchRoll,	DI_CODE_12inchRoll,	DI_CODE_9inchRoll,
	DI_CODE_30inchRoll,	DI_CODE_707mmRoll,

	DI_CODE_490mmRoll = 232,
	DI_CODE_680mmRoll,		DI_CODE_34inchRoll,	DI_CODE_22inchRoll,	DI_CODE_17inchRoll,
	DI_CODE_11inchRoll,	DI_CODE_8HinchRoll,	DI_CODE_620mmRoll,

	DI_CODE_YOH_ENV_0T = 240,
	DI_CODE_YOH_ENV_2T, DI_CODE_YOH_ENV_4T, DI_CODE_JAPANESE_ENV_3T, DI_CODE_JAPANESE_ENV_4T,
	DI_CODE_KAKU_ENV_2T = 247,

	DI_CODE_226x310T = 249,
	DI_CODE_310x432T,
};

/* 一般名称でのサイズ・コード定義 */
#define	DI_CODE_ANSIC		DI_CODE_17x22
#define	DI_CODE_ANSICT		DI_CODE_17x22T

#define	DI_CODE_DLT		DI_CODE_11x17
#define	DI_CODE_DLTT		DI_CODE_11x17T

#define	DI_CODE_LG			DI_CODE_8Hx14
#define	DI_CODE_LGT		DI_CODE_8Hx14T

#define	DI_CODE_LT			DI_CODE_8Hx11
#define	DI_CODE_LTT		DI_CODE_8Hx11T

#define DI_CODE_HLT		DI_CODE_5Hx8H
#define DI_CODE_HLTT		DI_CODE_5Hx8HT

#define	DI_CODE_F			DI_CODE_8x13
#define	DI_CODE_FT			DI_CODE_8x13T
#define	DI_CODE_GL			DI_CODE_8x13
#define	DI_CODE_GLT		DI_CODE_8x13T

#define	DI_CODE_Foolscap	DI_CODE_8Hx13
#define	DI_CODE_FoolscapT	DI_CODE_8Hx13T
#define	DI_CODE_F4			DI_CODE_8Hx13
#define	DI_CODE_F4T		DI_CODE_8Hx13T

#define	DI_CODE_Folio		DI_CODE_8Qx13
#define	DI_CODE_FolioT		DI_CODE_8Qx13T

#define	DI_CODE_GT			DI_CODE_8x10H
#define	DI_CODE_GTT		DI_CODE_8x10HT

#define	DI_CODE_UK			DI_CODE_8x10
#define	DI_CODE_UKT		DI_CODE_8x10T

#define	DI_CODE_Exective	DI_CODE_7Qx10H
#define	DI_CODE_ExectiveT	DI_CODE_7Qx10HT

/* */
#define	DI_CODE_13x19_2	DI_CODE_13x19Q
#define	DI_CODE_13x19_2T	DI_CODE_13x19QT


/* Original size only */
#define	DI_CODE_435x310	0xFF
#define	DI_CODE_300x250	0xFF
#define	DI_CODE_11x14CFF	0xFF


/*      */

#endif /* !__DI_PAPERDEF_H__ */
