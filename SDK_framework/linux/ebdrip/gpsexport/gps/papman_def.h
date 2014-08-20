/**********************************************************************************
* GW PRINTER APPLICATION PANEL MANAGER HEADER FILE FOR PANEL-CLIENT
* Author:	Koji Dan			  Date: 2000/07/04
* Copyright:	Copyright (C) 2000, 2001 RICOH COMPANY, LTD.
* Function:	Defined the information table
* -------------------------------------------------------------------------------
* (Revision History)
*  ver0.10:(1999/10/25)  initial release
*  ver1.00:(2000/07/04)  クライアント用に切り離し
**********************************************************************************/
#ifndef __GPS_PM_INFORMATION_H_
#define	__GPS_PM_INFORMATION_H_
/*
 *  papman_def.hのバージョン
 */
#define   PAPMAN_DEF_H_20001026 1

/* =================================================================================== *
 *      一般マクロ定義
 * =================================================================================== */
/*       */
#define   I_AM_GPS             123
/*       */
#define   GLOBAL               /**/
#define   PM_SUCCESS           0
#define   PM_FAILURE           (-1)
#define   MENU_GETITEM_FAIL    0xff

/*       */
#define   FILENAME_LEN         14
/*
 * STRING_CODE_MAX(= 160)なのだが、GWIPCの最大許容(= 128)の兼ね合いから
 *     unsigned short	type;    ( ← 2 byte )
 *     unsigned short	length;  ( ← 2 byte )
 *     pid_t		pid;     ( ← 4 byte )
 *     余裕分                    ( ← 8 byte )
 *  以上を差し引いて, 128 - (2+2+4+8) = 112 byte とする。
 */
#define   PM_STRING_LEN_MAX   112   /* GWIPCの制約にあわせる（NULLターミネート含む）*/
#define   STRING_LEN          112   /* GWIPCの制約にあわせる（NULLターミネート含む）*/
#define   STRING_LEN_P         17   /* CHARパネル機の最大数:NULLターミネート含む */
#define   DBG_MAX_NUM         (32)  /* ８行×４段落 */
#define   SELECT_ITEMS_NUM     16
#define   PM_ITEM_SIZE         32

/* =================================================================================== *
 *      トレイ情報・紙情報・キー情報・言語情報・ＬＥＤ情報
 * =================================================================================== */
/*
 *  キーコードＩＤ
 */
enum {
  PM_KEY_NONE = 0xFFFD,             /* no key event */
  PM_KEY_C_0 = 0x40,                /* Number key (0) （Ｃモデルのみに適用） */
  PM_KEY_C_1,                       /* Number key (1) （Ｃモデルのみに適用） */
  PM_KEY_C_2,                       /* Number key (2) （Ｃモデルのみに適用） */
  PM_KEY_C_3,                       /* Number key (3) （Ｃモデルのみに適用） */
  PM_KEY_C_4,                       /* Number key (4) （Ｃモデルのみに適用） */
  PM_KEY_C_5,                       /* Number key (5) （Ｃモデルのみに適用） */
  PM_KEY_C_6,                       /* Number key (6) （Ｃモデルのみに適用） */
  PM_KEY_C_7,                       /* Number key (7) （Ｃモデルのみに適用） */
  PM_KEY_C_8,                       /* Number key (8) （Ｃモデルのみに適用） */
  PM_KEY_C_9,                       /* Number key (9) （Ｃモデルのみに適用） */
  PM_KEY_C_PERIOD,                  /* Number key(.／*)（Ｃモデルのみに適用）*/
  PM_KEY_C_SHARP,                   /* Number key (#) （Ｃモデルのみに適用） */
  PM_KEY_C_CLEAR,                   /* Number key(clr)（Ｃモデルのみに適用） */
  PM_KEY_P_UP = 0x80,               /* UP arrow key   （Ｐモデルのみに適用）*/
  PM_KEY_P_DOWN,                    /* DOWN arrow key （Ｐモデルのみに適用）*/
  PM_KEY_P_MENU,                    /* MENU key       （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_ESC,                     /* ESCAPE key     （Ｐモデルのみに適用）*/
  PM_KEY_P_EXEC,                    /* EXECUTE key    （Ｐモデルのみに適用）*/
  PM_KEY_P_EXIT_PAPER,              /* EXIT PAPER key （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_RESET,                   /* RESET key      （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_ONLINE,                  /* ON/OFF LINE key（Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_MENU_UNLOCK,             /* Menu Lock key  （Ｐモデルのみに適用）*/
  PM_KEY_P_MENU_SPECIAL,            /* Menu spcl  key （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_MENU_SPECIAL2,           /* Menu spcl2 key （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_MENU_SPECIAL3,           /* Menu spcl3 key （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_MENU_SPECIAL4,           /* Menu spcl4 key （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_MENU_SPECIAL5,           /* Menu spcl5 key （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_SPECIAL,                   /* Special key    （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_SPECIAL2,                  /* Special key2   （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_SPECIAL3,                  /* Special key3   （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_SPECIAL4,                  /* Special key4   （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_SPECIAL5,                  /* Special key5   （Ｃモデル／Ｐモデルともに適用）*/
  PM_KEY_P_STOP,                    /* STOP key       （Ｐモデルに適用されるかは未定）*/
  PM_KEY_P_STOP_INVALID             /* STOP key       （Ｐモデルに適用されるかは未定）ストップキー受付不可の状態でのストップキー押下通知 */
};

/* =================================================================================== *
 *      PDL用キーダイアログ 定義
 * =================================================================================== */
/*       */
#define	 PM_KDLGPDL_MAX_LINE   6    /* 最大表示行数。偶数で指定すること。*/
#define	 PM_KDLGPDL_MAX_BTN    2    /* 最大表示ボタン数                  */

/* =================================================================================== *
 *       PDL用キーダイアログ 構造体
 * =================================================================================== */
typedef struct {
	unsigned short		exist;		/* ボタン表示 SET_DISP:表示  RESET_DISP:非表示 */
	unsigned short		id;		/* ボタンに表示する文字列の文字列ＩＤ 但し（0xFFF0～0xFFFF）は使用禁止*/
	unsigned int		code;		/* ボタン項目の返信コード */
}Btn_Info_t;

typedef struct {
	char 			*filename;			/* 取出す文字列のある文字列ファイル名。 */
	void			(*pfunc);			/* ハンドリングする関数のポインタ */
	unsigned short		str_id[PM_KDLGPDL_MAX_LINE];	/* 表示する文字列の文字列ＩＤ */
	Btn_Info_t		btninfo[PM_KDLGPDL_MAX_BTN];	/* ボタン情報。ポップアップ画面に表示されるボタンを左から順に数えた値 - 1 を添字とする。*/
	unsigned char		time;				/* ダイアログを表示する時間（秒）。*/
}Key_Dialogue_PDL_t;


/* =================================================================================== *
 *        MENU DEFINITION
 * =================================================================================== */
/* ------------------------------------------------ *
 *    メニューアイテム設定用 マクロ定義
 * ------------------------------------------------ */
#define   PM_MENU_NONE         0xFFFF
#define   PM_MSR_NONE          0xFFFE
#define   SET_MODIFY           1
#define   RESET_MODIFY         2
#define   SET_DISP             3
#define   HALF_DISP            4
#define   RESET_DISP           5
#define   SET_ACT              6
#define   RESET_ACT            7

/* ------------------------------------------------ *
 *    通知メニューイベント マクロ定義
 * ------------------------------------------------ */
#define   PM_MENU_INIT0       0
#define   PM_MENU_INIT        1
#define   PM_MENU_COMPLETE0   2
#define   PM_MENU_COMPLETE1   3
#define   PM_MENU_END         4
#define   PM_MENU_EXIT0       7
#define   PM_MENU_EXIT        5
#define   PM_MENU_FIN         6
#define   PM_MENU_INIT2       7

/* ---------------------------------------------------
 *   MENU TYPE DEFINITION
 *   注意:既定義の番号は変更しないこと。
 * ------------------------------------------------- */
#define MENU_TYPE_TRAY     5                /* (05) トレイ設定メニュー               : ＜P専用＞    */
#define MENU_TYPE_EMUSET   8                /* (08) エミュレーション印刷条件メニュー : ＜P／C共用＞ */
#define MENU_TYPE_PRN_NUM  9                /* (09) エミュレーション印刷部数メニュー : ＜P／C共用＞ */
#define MENU_TYPE_PCL     15                /* (15) PCL印刷条件ニュー                : ＜P／C共用＞ */
//
// GPS用 XPDLメニュータイプ定義
#define MENU_TYPE_XPDL1   91                /* (91) 拡張PDL設定メニュー              : ＜P／C共用＞ */
#define MENU_TYPE_XPDL2   92                /* (92) 拡張PDL設定メニュー              : ＜P／C共用＞ */
#define MENU_TYPE_XPDL3   93                /* (93) 拡張PDL設定メニュー              : ＜P／C共用＞ */
#define MENU_TYPE_XPDL4   94                /* (94) 拡張PDL設定メニュー              : ＜P／C共用＞ */
#define MENU_TYPE_XPDL5   95                /* (95) 拡張PDL設定メニュー              : ＜P／C共用＞ */
//
// nGPS用 XPDLメニュータイプ定義
// 1PDLのメニュータイプ最大許容数 → ５個
// R_GROUP用PDL        最大許容数 → ２０個 (interp.hには３０個まで領域確保）
// OTHERS 用PDL        最大許容数 → ２０個 (interp.hには３０個まで領域確保）
// 
#include "interp.h"
#ifndef GPS_PDL_RGROUP
#define GPS_PDL_RGROUP 40
#endif
#ifndef GPS_PDL_OTHERS
#define GPS_PDL_OTHERS 70
#endif
//  (51)～(150)
#define MENU_TYPE_XPDL1_RGRP(n)   (51+((n-GPS_PDL_RGROUP)*5))      /* R_GROUP用拡張PDL設定メニュー : ＜P／C共用＞ */
#define MENU_TYPE_XPDL2_RGRP(n)   (52+((n-GPS_PDL_RGROUP)*5))      /* R_GROUP用拡張PDL設定メニュー : ＜P／C共用＞ */
#define MENU_TYPE_XPDL3_RGRP(n)   (53+((n-GPS_PDL_RGROUP)*5))      /* R_GROUP用拡張PDL設定メニュー : ＜P／C共用＞ */
#define MENU_TYPE_XPDL4_RGRP(n)   (54+((n-GPS_PDL_RGROUP)*5))      /* R_GROUP用拡張PDL設定メニュー : ＜P／C共用＞ */
#define MENU_TYPE_XPDL5_RGRP(n)   (55+((n-GPS_PDL_RGROUP)*5))      /* R_GROUP用拡張PDL設定メニュー : ＜P／C共用＞ */
// (151)～(250)
#define MENU_TYPE_XPDL1_OTHR(n)   (151+((n-GPS_PDL_OTHERS)*5))     /* 第３者用拡張PDL設定メニュー  : ＜P／C共用＞ */
#define MENU_TYPE_XPDL2_OTHR(n)   (152+((n-GPS_PDL_OTHERS)*5))     /* 第３者用拡張PDL設定メニュー  : ＜P／C共用＞ */
#define MENU_TYPE_XPDL3_OTHR(n)   (153+((n-GPS_PDL_OTHERS)*5))     /* 第３者用拡張PDL設定メニュー  : ＜P／C共用＞ */
#define MENU_TYPE_XPDL4_OTHR(n)   (154+((n-GPS_PDL_OTHERS)*5))     /* 第３者用拡張PDL設定メニュー  : ＜P／C共用＞ */
#define MENU_TYPE_XPDL5_OTHR(n)   (155+((n-GPS_PDL_OTHERS)*5))     /* 第３者用拡張PDL設定メニュー  : ＜P／C共用＞ */

/* ---------------------------------------------------
 *   ITEM TYPE DEFINITION
 *   注意:既定義の番号は変更しないこと。
 * ------------------------------------------------- */
#define   ITEM_TYPE_START        0          /* (00) ルート構造体アイテムタイプ識別子                 */
#define   ITEM_TYPE_MENU         1          /* (01) メニュー型画面用アイテムタイプ識別子             */
#define   ITEM_TYPE_EXECUTING    3          /* (03) 実行型画面用アイテムタイプ識別子                 */
#define   ITEM_TYPE_SELECT       2          /* (02) 選択肢型画面用アイテムタイプ識別子               */
#define   ITEM_TYPE_INTEGER      5          /* (05) 整数値型画面用アイテムタイプ識別子               */
#define   ITEM_TYPE_FLOAT        6          /* (06) 小数値型画面用アイテムタイプ識別子               */
#define   ITEM_TYPE_PRN_NUM      8          /* (08) 印刷部数画面用アイテムタイプ識別子               */
#define   ITEM_TYPE_PTIME       14          /* (14) 用紙変倍率タイプ識別子                           */
#define   ITEM_TYPE_ANY         15          /* (15) 任意アイテムタイプ識別子                         */
#define   ITEM_TYPE_FLOAT_EXT   16          /* (16) 小数値桁拡張特化型アイテムタイプ識別子           */
#define   ITEM_TYPE_PTIME_FLT   20          /* (20) 小数型用紙変倍率タイプ識別子                     */


/* =================================================================================== *
 *       メニューアイテム構造体
 * =================================================================================== */
/* ---------------------------------------------------
 *   ITEM_TYPE_START : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		                      /* アイテム自身のパネルＩＤ 	*/
        unsigned short idDown;		                      /* 下階層のパネルＩＤ 		*/
					                      /* トラップ用関数ポインタ 	*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
        unsigned char  filename[FILENAME_LEN];                /* ファイルネーム 		*/
	unsigned char  panel_lock_stat;        		      /* パネルロック状態情報 		*/       
	unsigned char  ucReserved[3];                         /* 未使用 			*/
        unsigned char  reserve_cid[4];                        /* クライアントＩＤ用予約領域 	*/
	unsigned char  ucItem;           		      /* アイテムタイプ 		*/
        unsigned char  ucMenu;                                /* メニュータイプ        		*/
} Menu_Type_t;

/* ---------------------------------------------------
 *   ITEM_TYPE_MENU : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		      	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idNext;		       	/* 同階層の次のパネルＩＤ 		*/
	unsigned short idPrev;		       	/* 同階層の前のパネルＩＤ 		*/
	unsigned short idDown;		       	/* 下階層のパネルＩＤ 			*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	unsigned short str1_id;		       	/* タイトル部（１行目）の文字列ＩＤ 	*/
	unsigned short str1_mod;	       	/* タイトル部（１行目）の文字列修飾情報	*/
	unsigned short str2_id;		       	/* 項目部（２行目）の文字列ＩＤ 	*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  disp_flg;	       	/* 表示／半輝度／非表示のフラグ 	*/
	unsigned char  ucReserved[5];          	/* 未使用 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_Menu_t;

/* ---------------------------------------------------
 *   ITEM_TYPE_SELECT : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		       	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idNext;		       	/* 同階層の次のパネルＩＤ 		*/
	unsigned short idPrev;		       	/* 同階層の前のパネルＩＤ 		*/
	unsigned short idDown;		       	/* 下階層のパネルＩＤ 			*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	unsigned short str1_id;		       	/* タイトル部（１行目）の文字列ＩＤ 	*/
	unsigned short str1_mod;	       	/* タイトル部（１行目）の文字列修飾情報 */
	unsigned short str2_id;		       	/* 項目部（２行目）の文字列ＩＤ 	*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  up_num;         	       	/* 実行後に遷移する上への階層数 	*/
	unsigned char  disp_flg;	       	/* 表示／半輝度／非表示のフラグ 	*/
	unsigned char  fselect;		       	/* 選択／非選択のフラグ 		*/
	unsigned char  disp_fselect;		/* 選択フラグの表示／非表示のフラグ	*/
	unsigned char  ucReserved[2];          	/* 未使用 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_Select_t;

/* ---------------------------------------------------
 *   ITEM_TYPE_INTEGER : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		       	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	unsigned short str1_id;		       	/* タイトル部（１行目）の文字列ＩＤ 	*/
	unsigned short str1_mod;	       	/* タイトル部（１行目）の文字列修飾情報	*/
	short          sMax;		       	/* 最大値 				*/
	short          sMin;		       	/* 最小値 				*/
	unsigned short step;		       	/* 変化幅 				*/
	short          value;		       	/* 設定値 				*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;		       	/* 単位文字列ＩＤ 	                */
	unsigned char  up_num;         	       	/* 実行後に遷移する上への階層数 	*/
	unsigned char  fig_num;		       	/* 表示桁数      	                */
	unsigned char  ucReserved[2];          	/* 未使用 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_Integer_t;

/* ---------------------------------------------------
 *   ITEM_TYPE_FLOAT : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		       	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	unsigned short str1_id;		       	/* タイトル部（１行目）の文字列ＩＤ 	*/
	unsigned short str1_mod;	       	/* タイトル部（１行目）の文字列修飾情報	*/
	short          sMax;		       	/* 最大値 				*/
	short          sMin;		       	/* 最小値 				*/
	unsigned short step;		       	/* 変化幅 				*/
	short          value;		       	/* 設定値 				*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;		       	/* 単位文字列ＩＤ 	                */
	unsigned char  up_num;         	       	/* 実行後に遷移する上への階層数 	*/
	unsigned char  fig_num;		       	/* 表示桁数      	                */
	unsigned char  ucMulti; 	       	/* 指数値 				*/
        unsigned char  ucReserved;          	/* 未使用 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_Float_t;

/* ---------------------------------------------------
 *   ITEM_TYPE_PRN_NUM : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		       	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	short          sMax;		       	/* 最大値				*/
	short          sMin;		       	/* 最小値 				*/
	unsigned short step;		       	/* 変化幅 				*/
	short          value;		       	/* 設定値 				*/
	unsigned short usReserved[2];          	/* 未使用 				*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  ucReserved[6];          	/* 未使用 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_PrnNum_t;

/* ---------------------------------------------------
 *   ITEM_TYPE_PTIME : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		       	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	unsigned short str1_id;		       	/* タイトル部（１行目）の文字列ＩＤ 	*/
	unsigned short str1_mod;	       	/* タイトル部（１行目）の文字列修飾情報	*/
	short          sMax;		       	/* 最大値 				*/
	short          sMin;		       	/* 最小値 				*/
	unsigned short step;		       	/* 変化幅 				*/
	short          value;		       	/* 設定値 				*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;		       	/* 単位文字列ＩＤ 	                */
	unsigned char  up_num;         	       	/* 実行後に遷移する上への階層数 	*/
	unsigned char  fig_num;		       	/* 表示桁数      	                */
	unsigned char  ucReserved[2];          	/* 未使用 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_Ptime_t;

/* ---------------------------------------------------
 *   ITEM_TYPE_FLOAT_EXT : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		       	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	unsigned short str1_id;		       	/* タイトル部（１行目）の文字列ＩＤ 	*/
	short          sMin;		       	/* 最小値 				*/
	int            sMax;		       	/* 最大値 				*/
	int            value;		       	/* 設定値 				*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;		       	/* 単位文字列ＩＤ 	                */
	unsigned char  str1_mod;	       	/* タイトル部（１行目）の文字列修飾情報	*/
	unsigned char  step;		       	/* 変化幅 				*/
	unsigned char  fig_num;		       	/* 表示桁数      	                */
	unsigned char  ucMulti; 	       	/* 指数値 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_FloatExt_t;


/* ---------------------------------------------------
 *   ITEM_TYPE_EXECUTING : (32byte) ＜P／C共用＞
 * ------------------------------------------------- */
typedef  struct {
	unsigned short idPanel;		       	/* アイテム自身のパネルＩＤ 		*/
	unsigned short idBack;		       	/* 呼出し元 上位階層のパネルＩＤ	*/
	unsigned short str1_id;		       	/* タイトル部（１行目）の文字列ＩＤ 	*/
	unsigned short str1_mod;	       	/* タイトル部（１行目）の文字列修飾情報	*/
	unsigned short str2_id;		       	/* 項目部（２行目）の文字列ＩＤ 	*/
	unsigned short usReserved[3];          	/* 未使用 				*/
					   	/* トラップ用関数ポインタ 		*/
	void	       (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  up_num;         	       	/* 実行後に遷移する上への階層数 	*/
        unsigned char  confirm;                 /* 確認画面フラグ                       */
	unsigned char  ucReserved[4];          	/* 未使用 				*/
        unsigned char  reserve_cid[4];         	/* クライアントＩＤ保存用予約領域 	*/
	unsigned char  ucItem;		       	/* アイテムタイプ 			*/
        unsigned char  ucMenu;                 	/* メニュータイプ        		*/
} Item_Type_Executing_t;

#endif  /* ! __GPS_PM_INFORMATION_H_ */

/*- EOF -*/
