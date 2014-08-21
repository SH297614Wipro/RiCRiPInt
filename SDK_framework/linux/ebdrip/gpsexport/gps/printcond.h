/******************************************************
 * $Id$
 *
 * Copyright (C) 2010 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : printcond.h
 *   VERSION         : $Revision$
 *   AUTHOR          : Yusuke Nomura
 *-----------------------------------------------------
 *   HISTORY
 *	 30 Sep 2010: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_PRINTCOND_H_
#define	_GPS_PRINTCOND_H_


#include "sdkprintcond.h" /* 印刷条件(SDK) 12A～ */

/* PDL印刷条件取得結果 12A以降未使用 */
#define GPS_PDLPRTCOND_OK_ALL     (3) /* 成功(*cond、*media共に印刷条件変更有り) */
#define GPS_PDLPRTCOND_OK_MEDIA   (2) /* 成功(*mediaのみ印刷条件変更有り) */
#define GPS_PDLPRTCOND_OK_COND    (1) /* 成功(*cond のみ印刷条件変更有り) */
#define GPS_PDLPRTCOND_OK_NONE    (0) /* 成功(*cond、*media共に印刷条件変更無し) */
#define GPS_PDLPRTCOND_NG_IDERR  (-1) /* ujobidに指定したユーザージョブＩＤが不正 */
#define GPS_PDLPRTCOND_NG_PRMERR (-2) /* パラメータエラー */

/* PDF専用パラメータ取得結果 12A以降未使用 */
#define GPS_PDFPRM_OK         (0) /* 成功 */
#define GPS_PDFPRM_NG_IDERR  (-1) /* ujobidに指定したユーザージョブＩＤが不正 */
#define GPS_PDFPRM_NG_PRMERR (-2) /* パラメータエラー */

#define GPS_PDF_PASSWORD_LEN (36)

/*
 * 印刷条件(PDL)
 */

/* ジョブタイプ設定値 */
#define GPS_PCND_PDL_JOBTYPE_PRINT			(0)	/* プリンタジョブ */
#define GPS_PCND_PDL_JOBTYPE_MEDIA			(1)	/* メディアプリントジョブ */
#define GPS_PCND_PDL_JOBTYPE_THUMBNAIL		(2)	/* プレビュージョブ(12A～) */
#define GPS_PCND_PDL_JOBTYPE_SDK_PRINT		(3)	/* SDKプリントジョブ(12A～) */
#define GPS_PCND_PDL_JOBTYPE_SDK_THUMBNAIL	(4)	/* SDKプレビュージョブ(12A～) */

/* 用紙種類変更有無設定値 */
#define GPS_PCND_PDL_CHG_PAPERKIND_EXIST (1<<0) /* 変更有り */

/* 両面印刷設定値 */
#define GPS_PCND_PDL_DUPLEX_OFF   (1<<0) /* 片面 */
#define GPS_PCND_PDL_DUPLEX_LEFT  (1<<1) /* 両面左開き */
#define GPS_PCND_PDL_DUPLEX_TOP   (1<<3) /* 両面上開き */

/* トナーセーブ(カラー)設定値 */
#define GPS_PCND_PDL_TONERSAVE_COLOR_OFF (1<<0) /* OFF */
#define GPS_PCND_PDL_TONERSAVE_COLOR_ON  (1<<1) /* ON */

/* 集約設定値 */
#define GPS_PCND_PDL_NUP_OFF   (1<<0) /* 集約無し */
#define GPS_PCND_PDL_NUP_2IN1  (1<<1) /* 2in1 */
#define GPS_PCND_PDL_NUP_4IN1  (1<<2) /* 4in1 */
#define GPS_PCND_PDL_NUP_6IN1  (1<<3) /* 6in1 */
#define GPS_PCND_PDL_NUP_8IN1  (1<<4) /* 8in1 */ /* 予約(将来のため) */
#define GPS_PCND_PDL_NUP_9IN1  (1<<5) /* 9in1 */
#define GPS_PCND_PDL_NUP_16IN1 (1<<6) /* 16in1 */

/* 集約パラメータ設定値 */
#define GPS_PCND_PDL_NUPOPT_PAGEORDER_RIGHT_THEN_DOWN (1<<0) /* 2in1以外:左上→右上→左下→右下 2in1:左から右へ */
#define GPS_PCND_PDL_NUPOPT_PAGEORDER_LEFT_THEN_DOWN  (1<<1) /* 2in1以外:右上→左上→右下→左下 2in1:右から左へ */
#define GPS_PCND_PDL_NUPOPT_PAGEORDER_DOWN_THEN_RIGHT (1<<2) /* 2in1以外:左上→左下→右上→右下 2in1:未使用 */
#define GPS_PCND_PDL_NUPOPT_PAGEORDER_DOWN_THEN_LEFT  (1<<3) /* 2in1以外:右上→右下→左上→左下 2in1:未使用 */

/* 集約仕切り線 */
#define GPS_PCND_PDL_NUP_BORDER_OFF (1<<0) /* 無し */
#define GPS_PCND_PDL_NUP_BORDER_ON  (1<<1) /* 有り */

/* カラー/白黒設定値 */
#define GPS_PCND_PDL_COLORMODE_MONO  (1<<0) /* 白黒 */
#define GPS_PCND_PDL_COLORMODE_COLOR (1<<1) /* カラー */

/* 給紙トレイ選択設定値 12A以降未使用 */
#define GPS_PCND_PDL_INPUTTRAY_AUTO (1<<0)  /* 自動トレイ */
#define GPS_PCND_PDL_INPUTTRAY_1    (1<<1)  /* トレイ1 */
#define GPS_PCND_PDL_INPUTTRAY_2    (1<<2)  /* トレイ2 */
#define GPS_PCND_PDL_INPUTTRAY_3    (1<<3)  /* トレイ3 */
#define GPS_PCND_PDL_INPUTTRAY_4    (1<<4)  /* トレイ4 */
#define GPS_PCND_PDL_INPUTTRAY_5    (1<<5)  /* トレイ5 */
#define GPS_PCND_PDL_INPUTTRAY_6    (1<<6)  /* トレイ6 */
#define GPS_PCND_PDL_INPUTTRAY_7    (1<<7)  /* トレイ7 */
#define GPS_PCND_PDL_INPUTTRAY_LCT  (1<<30) /* 大量給紙トレイ */
#define GPS_PCND_PDL_INPUTTRAY_MAN  (1<<31) /* 手差しトレイ */

/* ステープル設定値 12A以降未使用 */
#define GPS_PCND_PDL_STAPLE_OFF           (1<<0) /* ステープル無し */
#define GPS_PCND_PDL_STAPLE_LEFTTOP       (1<<1) /* 左上 */
#define GPS_PCND_PDL_STAPLE_RIGHTTOP      (1<<2) /* 右上 */
#define GPS_PCND_PDL_STAPLE_LEFTTOPSLANT  (1<<3) /* 左上斜め */
#define GPS_PCND_PDL_STAPLE_RIGHTTOPSLANT (1<<4) /* 右上斜め */
#define GPS_PCND_PDL_STAPLE_LEFT2         (1<<5) /* 左2つ */
#define GPS_PCND_PDL_STAPLE_TOP2          (1<<6) /* 上2つ */
#define GPS_PCND_PDL_STAPLE_RIGHT2        (1<<7) /* 右2つ */
#define GPS_PCND_PDL_STAPLE_BOOKLET       (1<<8) /* 中綴じ */

/* パンチ設定値 12A以降未使用 */
#define GPS_PCND_PDL_PUNCH_OFF      (1<<0)  /* パンチ無し */
#define GPS_PCND_PDL_PUNCH_LEFT2    (1<<1)  /* 左2つ */
#define GPS_PCND_PDL_PUNCH_TOP2     (1<<2)  /* 上2つ */
#define GPS_PCND_PDL_PUNCH_RIGHT2   (1<<3)  /* 右2つ */
#define GPS_PCND_PDL_PUNCH_LEFT3    (1<<4)  /* 左3つ */
#define GPS_PCND_PDL_PUNCH_TOP3     (1<<5)  /* 上3つ */
#define GPS_PCND_PDL_PUNCH_RIGHT3   (1<<6)  /* 右3つ */
#define GPS_PCND_PDL_PUNCH_LEFT4    (1<<7)  /* 左4つ */
#define GPS_PCND_PDL_PUNCH_TOP4     (1<<8)  /* 上4つ */
#define GPS_PCND_PDL_PUNCH_RIGHT4   (1<<9)  /* 右4つ */
#define GPS_PCND_PDL_PUNCH_LEFTGBC  (1<<10) /* GBC左 */
#define GPS_PCND_PDL_PUNCH_TOPGBC   (1<<11) /* GBC上 */
#define GPS_PCND_PDL_PUNCH_RIGHTGBC (1<<12) /* GBC右 */
#define GPS_PCND_PDL_PUNCH_LEFTTOP  (1<<13) /* 左上1つ */

typedef struct gps_pdl_printcondition {
	unsigned int  job_type;        /* ジョブタイプ */
	unsigned long chg_paper_kind;  /* 用紙種類変更有無 */
	unsigned int  paper_kind;      /* 用紙種類 */
	unsigned long duplex;          /* 両面印刷 */
	unsigned long tonersave_color; /* トナーセーブ(カラー) */
	unsigned long nup;             /* 集約 */
	unsigned long nup_option;      /* 集約パラメータ */
	unsigned long nup_border;      /* 集約仕切り線 */
	unsigned long colormode;       /* カラー/白黒 */
	unsigned long inputtray;       /* 給紙トレイ選択 */
	unsigned long staple;          /* ステープル */
	unsigned long punch;           /* パンチ */
} gps_pdl_printcondition_t;


/*
 * 印刷条件(PDL2) 12A～
 */

typedef struct gps_pdl_printcondition2{
	unsigned char pdfpassword[GPS_PDF_PASSWORD_LEN]; /* PDFパスワード文字列 */
	unsigned long reserve[16];                       /* 予約(拡張用) */
} gps_pdl_printcondition2_t;


/*
 * メディアプリント専用印刷条件(PDL)
 */

/* 製本設定値 */
#define GPS_PCND_MEDIA_BIND_OFF            (1<<0) /* 製本無し */
#define GPS_PCND_MEDIA_BIND_MAGAZINE_LEFT  (1<<1) /* 週刊誌(左へ開く) */
#define GPS_PCND_MEDIA_BIND_MAGAZINE_RIGHT (1<<2) /* 週刊誌(右へ開く) */

/* 用紙サイズ指定(用紙サイズ変倍)設定値 */
#define GPS_PCND_MEDIA_MAG_OFF (1<<0) /* OFF */
#define GPS_PCND_MEDIA_MAG_ON  (1<<1) /* ON */

/* 解像度(TIFF用)設定値 */
#define GPS_PCND_MEDIA_RESOL_TIFF_200 (1<<0) /* 200dpi */
#define GPS_PCND_MEDIA_RESOL_TIFF_300 (1<<1) /* 300dpi */
#define GPS_PCND_MEDIA_RESOL_TIFF_400 (1<<2) /* 400dpi */
#define GPS_PCND_MEDIA_RESOL_TIFF_600 (1<<3) /* 600dpi */

/* 解像度(PDF用)設定値 */
#define GPS_PCND_MEDIA_RESOL_PDF_600_FAST (1<<0) /* 600dpi(2階調) */
#define GPS_PCND_MEDIA_RESOL_PDF_600_STD  (1<<1) /* 600dpi(標準) */
#define GPS_PCND_MEDIA_RESOL_PDF_600_HIGH (1<<2) /* 600dpi(高画質) */
#define GPS_PCND_MEDIA_RESOL_PDF_1200     (1<<3) /* 1200dpi */
#define GPS_PCND_MEDIA_RESOL_PDF_300      (1<<4) /* 300dpi */
#define GPS_PCND_MEDIA_RESOL_PDF_1200_2   (1<<5) /* 1200dpi 2bit */

/* 印刷品質(JPEG用)設定値 */
#define GPS_PCND_MEDIA_PRTQUAL_NORMAL (1<<0) /* ノーマル */
#define GPS_PCND_MEDIA_PRTQUAL_DRAFT  (1<<1) /* ドラフト */
#define GPS_PCND_MEDIA_PRTQUAL_FINE   (1<<2) /* ファイン */

typedef struct gps_pdl_media_printcondition {
	unsigned long bind;          /* 製本 */
	struct {                     /* 用紙サイズ指定 */
		unsigned long magnification; /* 用紙サイズ変倍 */
		unsigned int  size_code;     /* 紙サイズコード */
		unsigned long paper_width;   /* フリーサイズ時の用紙幅  (0.1mm単位) */
		unsigned long paper_length;  /* フリーサイズ時の用紙高さ(0.1mm単位) */
	} paper_size;
	struct {                     /* 解像度 */
		unsigned long tiff;          /* TIFF用 */
		unsigned long pdf;           /* PDF用 */
	} resolution;
	unsigned long printquality;  /* 印刷品質(JPEG用) */
	unsigned long reserve1;      /* 予約1 */
	unsigned long reserve2;      /* 予約2 */
	unsigned long reserve3;      /* 予約3 */
} gps_pdl_media_printcondition_t;


/*
 * 印刷条件(SYS) 12A～
 */

/* 給紙トレイ選択設定値 */
#define GPS_PCND_SYS2_INPUTTRAY_AUTO (1<<0)  /* 自動トレイ */
#define GPS_PCND_SYS2_INPUTTRAY_1    (1<<1)  /* トレイ1 */
#define GPS_PCND_SYS2_INPUTTRAY_2    (1<<2)  /* トレイ2 */
#define GPS_PCND_SYS2_INPUTTRAY_3    (1<<3)  /* トレイ3 */
#define GPS_PCND_SYS2_INPUTTRAY_4    (1<<4)  /* トレイ4 */
#define GPS_PCND_SYS2_INPUTTRAY_5    (1<<5)  /* トレイ5 */
#define GPS_PCND_SYS2_INPUTTRAY_6    (1<<6)  /* トレイ6 */
#define GPS_PCND_SYS2_INPUTTRAY_7    (1<<7)  /* トレイ7 */
#define GPS_PCND_SYS2_INPUTTRAY_LCT  (1<<30) /* 大量給紙トレイ */
#define GPS_PCND_SYS2_INPUTTRAY_MAN  (1<<31) /* 手差しトレイ */

/* 両面印刷設定値 */
#define GPS_PCND_SYS2_DUPLEX_OFF   (1<<0) /* 片面 */
#define GPS_PCND_SYS2_DUPLEX_LEFT  (1<<1) /* 両面左開き */
#define GPS_PCND_SYS2_DUPLEX_TOP   (1<<3) /* 両面上開き */

/* ソート設定値 */
#define GPS_PCND_SYS2_SORT_NORMAL (1<<0) /* ソート */
#define GPS_PCND_SYS2_SORT_ROTATE (1<<1) /* 回転ソート */
#define GPS_PCND_SYS2_SORT_SHIFT  (1<<2) /* シフトソート */

/* スタック設定値 */
#define GPS_PCND_SYS2_STACK (1<<0) /* スタック */

/* ステープル設定値 */
#define GPS_PCND_SYS2_STAPLE_OFF           (1<<0) /* ステープル無し */
#define GPS_PCND_SYS2_STAPLE_LEFTTOP       (1<<1) /* 左上 */
#define GPS_PCND_SYS2_STAPLE_RIGHTTOP      (1<<2) /* 右上 */
#define GPS_PCND_SYS2_STAPLE_LEFTTOPSLANT  (1<<3) /* 左上斜め */
#define GPS_PCND_SYS2_STAPLE_RIGHTTOPSLANT (1<<4) /* 右上斜め */
#define GPS_PCND_SYS2_STAPLE_LEFT2         (1<<5) /* 左2つ */
#define GPS_PCND_SYS2_STAPLE_TOP2          (1<<6) /* 上2つ */
#define GPS_PCND_SYS2_STAPLE_RIGHT2        (1<<7) /* 右2つ */
#define GPS_PCND_SYS2_STAPLE_BOOKLET       (1<<8) /* 中綴じ */

/* パンチ設定値 */
#define GPS_PCND_SYS2_PUNCH_OFF      (1<<0)  /* パンチ無し */
#define GPS_PCND_SYS2_PUNCH_LEFT2    (1<<1)  /* 左2つ */
#define GPS_PCND_SYS2_PUNCH_TOP2     (1<<2)  /* 上2つ */
#define GPS_PCND_SYS2_PUNCH_RIGHT2   (1<<3)  /* 右2つ */
#define GPS_PCND_SYS2_PUNCH_LEFT3    (1<<4)  /* 左3つ */
#define GPS_PCND_SYS2_PUNCH_TOP3     (1<<5)  /* 上3つ */
#define GPS_PCND_SYS2_PUNCH_RIGHT3   (1<<6)  /* 右3つ */
#define GPS_PCND_SYS2_PUNCH_LEFT4    (1<<7)  /* 左4つ */
#define GPS_PCND_SYS2_PUNCH_TOP4     (1<<8)  /* 上4つ */
#define GPS_PCND_SYS2_PUNCH_RIGHT4   (1<<9)  /* 右4つ */
#define GPS_PCND_SYS2_PUNCH_LEFTGBC  (1<<10) /* GBC左 */
#define GPS_PCND_SYS2_PUNCH_TOPGBC   (1<<11) /* GBC上 */
#define GPS_PCND_SYS2_PUNCH_RIGHTGBC (1<<12) /* GBC右 */
#define GPS_PCND_SYS2_PUNCH_LEFTTOP  (1<<13) /* 左上1つ */

/* トナーセーブ(モノクロ)設定値 */
#define GPS_PCND_SYS2_TONERSAVE_MONO_OFF (1<<0) /* OFF */
#define GPS_PCND_SYS2_TONERSAVE_MONO_ON  (1<<1) /* ON */

/* 180度回転設定値 */
#define GPS_PCND_SYS2_UPSIDEDOWN_OFF (1<<0) /* OFF */
#define GPS_PCND_SYS2_UPSIDEDOWN_ON  (1<<1) /* ON */

/* モード */
#define GPS_PCND_SYS2_MODE_FORCERIP  (1<<0)  /* 強制RIP */

typedef struct gps_sys2_printcondition {
	unsigned long inputtray;      /* 給紙トレイ選択 */
	unsigned long duplex;         /* 両面印刷 */
	unsigned long sort;           /* ソート */
	unsigned long stack;          /* スタック */
	unsigned long staple;         /* ステープル */
	unsigned long punch;          /* パンチ */
	unsigned int  qty;            /* 出力部数 */
	unsigned long tonersave_mono; /* トナーセーブ(モノクロ) */
	unsigned long upsidedown;     /* 180度回転 */
	unsigned long reserve1;       /* 予約1 */
	unsigned long mode;           /* モード */
} gps_sys2_printcondition_t;


/*
 * 印刷条件構造体(共有メモリ版) 12A～
 */

/* 印刷条件変更の有無(change) */
#define GPS_PCND_CHG_PDL   (1<<0) /* bit0: 印刷条件(PDL) */
#define GPS_PCND_CHG_PDL2  (1<<1) /* bit1: 印刷条件２(PDL) */
#define GPS_PCND_CHG_MEDIA (1<<2) /* bit2: メディアプリント印刷条件(PDL) */
#define GPS_PCND_CHG_SDK   (1<<3) /* bit3: ＳＤＫアプリプリント印刷条件(PDL) */
#define GPS_PCND_CHG_SYS   (1<<4) /* bit4: 印刷条件(システム) */

typedef struct gps_printconditionShm {
	unsigned int                   job_type; /* ジョブタイプ設定値 */
	unsigned long                  change;   /* 印刷条件変更の有無 */
	gps_pdl_printcondition_t       pdl;      /* 印刷条件(PDL)格納領域 */
	gps_pdl_printcondition2_t      pdl2;     /* 印刷条件２(PDL)格納領域 */
	gps_pdl_media_printcondition_t media;    /* メディアプリント専用印刷条件(PDL)格納領域 */
	gps_pdl_sdk_printcondition_t   sdk;      /* SDKアプリプリント専用印刷条件(PDL)格納領域  ※CPS側管理構造体 */
	gps_sys2_printcondition_t      sys;      /* 印刷条件(システム)格納領域 ※将来用に追加 */
} gps_printconditionShm_t;


/*
 * PDF専用パラメータ 12A以降未使用
 */

#define GPS_PDF_PRINTPAGES_LEN 12

typedef struct {
	unsigned char pdfpassword[GPS_PDF_PASSWORD_LEN];  /* PDFパスワード文字列 */
	unsigned char printpages[GPS_PDF_PRINTPAGES_LEN]; /* 論理ページ指定(生成対象ページ) */
} gps_pdf_param_t;

#endif /* !_GPS_PRINTCOND_H_ */
/*
 * Copyright (c) 2010 Ricoh Company, Ltd.  All Rights Reserved.
 */
