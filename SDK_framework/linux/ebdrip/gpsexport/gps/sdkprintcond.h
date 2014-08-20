/*
 * sdkprintcond.h
 *
 *  Created on: 2011/08/11
 */

#ifndef SDKPRINTCOND_H_
#define SDKPRINTCOND_H_


/*
 * SDKアプリプリント専用印刷条件(PDL)
 */

#define GPS_SDK_PAGES_LEN								(229) /* 論理ページ指定最大文字列長 */
#define GPS_SDK_PDF_PASSWORD_LEN						(36) /* PDFパスワード最大文字列長 */

#define GPS_PCND_SDK_FORCEDDUPLEX_LEFT					(1<<1) /* 強制両面設定：左開き */
#define GPS_PCND_SDK_FORCEDDUPLEX_TOP					(1<<3) /* 強制両面設定：上開き */

#define GPS_PCND_SDK_DUPLEX_OFF							(1<<0) /* 片面 */
#define GPS_PCND_SDK_DUPLEX_LEFT						(1<<1) /* 両面左開き */
#define GPS_PCND_SDK_DUPLEX_TOP							(1<<3) /* 両面上開き */

#define GPS_PCND_SDK_COLORMODE_MONO						(1<<0) /* 白黒 */
#define GPS_PCND_SDK_COLORMODE_COLOR					(1<<1) /* カラー */

#define GPS_PCND_SDK_TONERSAVE_OFF						(1<<0) /* (カラー機用)OFF */
#define GPS_PCND_SDK_TONERSAVE_ON						(1<<1) /* (カラー機用)ON */

#define GPS_PCND_SDK_TONERSAVE_MONO_OFF					(1<<0) /* OFF */
#define GPS_PCND_SDK_TONERSAVE_MONO_ON					(1<<1) /* ON */

#define GPS_PCND_SDK_CHG_PAPERKIND_EXIST				(1<<0) /* 変更有り */

#define GPS_PCND_SDK_NUP_OFF							(1<<0) /* 集約無し */
#define GPS_PCND_SDK_NUP_2IN1							(1<<1) /* 2in1 */
#define GPS_PCND_SDK_NUP_4IN1							(1<<2) /* 4in1 */
#define GPS_PCND_SDK_NUP_6IN1							(1<<3) /* 6in1 */
#define GPS_PCND_SDK_NUP_8IN1							(1<<4) /* 8in1 */
#define GPS_PCND_SDK_NUP_9IN1							(1<<5) /* 9in1 */
#define GPS_PCND_SDK_NUP_16IN1							(1<<6) /* 16in1 */

#define GPS_PCND_SDK_NUPOPT_PAGEORDER_RIGHT_THEN_DOWN	(1<<0) /* 集約方向 2in1以外:左上→右上→左下→右下 2in1:左から右へ */
#define GPS_PCND_SDK_NUPOPT_PAGEORDER_LEFT_THEN_DOWN	(1<<1) /* 集約方向 2in1以外:右上→左上→右下→左下 2in1:右から左へ */
#define GPS_PCND_SDK_NUPOPT_PAGEORDER_DOWN_THEN_RIGHT	(1<<2) /* 集約方向 2in1以外:左上→左下→右上→右下 2in1:未使用 */
#define GPS_PCND_SDK_NUPOPT_PAGEORDER_DOWN_THEN_LEFT	(1<<3) /* 集約方向 2in1以外:右上→右下→左上→左下 2in1:未使用 */

#define GPS_PCND_SDK_NUP_BORDER_OFF						(1<<0) /* 無し */
#define GPS_PCND_SDK_NUP_BORDER_ON						(1<<1) /* 有り */

#define GPS_PCND_SDK_INPUTTRAY_AUTO						(1<<0) /* 自動トレイ */
#define GPS_PCND_SDK_INPUTTRAY_1						(1<<1) /* トレイ1 */
#define GPS_PCND_SDK_INPUTTRAY_2						(1<<2) /* トレイ2 */
#define GPS_PCND_SDK_INPUTTRAY_3						(1<<3) /* トレイ3 */
#define GPS_PCND_SDK_INPUTTRAY_4						(1<<4) /* トレイ4 */
#define GPS_PCND_SDK_INPUTTRAY_5						(1<<5) /* トレイ5 */
#define GPS_PCND_SDK_INPUTTRAY_6						(1<<6) /* トレイ6 */
#define GPS_PCND_SDK_INPUTTRAY_7						(1<<7) /* トレイ7 */
#define GPS_PCND_SDK_INPUTTRAY_LCT						(1<<30) /* 大量給紙トレイ */
#define GPS_PCND_SDK_INPUTTRAY_MAN						(1<<31) /* 手差しトレイ */

#define GPS_PCND_SDK_SORT_NORMAL						(1<<0) /* ソート */
#define GPS_PCND_SDK_SORT_ROTATE						(1<<1) /* 回転ソート */
#define GPS_PCND_SDK_SORT_SHIFT							(1<<2) /* シフトソート */

#define GPS_PCND_SDK_STACK								(1<<0) /* スタック */

#define GPS_PCND_SDK_STAPLE_OFF							(1<<0) /* ステープル無し */
#define GPS_PCND_SDK_STAPLE_LEFTTOP						(1<<1) /* 左上 */
#define GPS_PCND_SDK_STAPLE_RIGHTTOP					(1<<2) /* 右上 */
#define GPS_PCND_SDK_STAPLE_LEFTTOPSLANT				(1<<3) /* 左上斜め */
#define GPS_PCND_SDK_STAPLE_RIGHTTOPSLANT				(1<<4) /* 右上斜め */
#define GPS_PCND_SDK_STAPLE_LEFT2						(1<<5) /* 左2つ */
#define GPS_PCND_SDK_STAPLE_TOP2						(1<<6) /* 上2つ */
#define GPS_PCND_SDK_STAPLE_RIGHT2						(1<<7) /* 右2つ */
#define GPS_PCND_SDK_STAPLE_BOOKLET						(1<<8) /* 中綴じ */

#define GPS_PCND_SDK_PUNCH_OFF							(1<<0) /* パンチ無し */
#define GPS_PCND_SDK_PUNCH_LEFT2						(1<<1) /* 左2つ */
#define GPS_PCND_SDK_PUNCH_TOP2							(1<<2) /* 上2つ */
#define GPS_PCND_SDK_PUNCH_RIGHT2						(1<<3) /* 右2つ */
#define GPS_PCND_SDK_PUNCH_LEFT3						(1<<4) /* 左3つ */
#define GPS_PCND_SDK_PUNCH_TOP3							(1<<5) /* 上3つ */
#define GPS_PCND_SDK_PUNCH_RIGHT3						(1<<6) /* 右3つ */
#define GPS_PCND_SDK_PUNCH_LEFT4						(1<<7) /* 左4つ */
#define GPS_PCND_SDK_PUNCH_TOP4							(1<<8) /* 上4つ */
#define GPS_PCND_SDK_PUNCH_RIGHT4						(1<<9) /* 右4つ */
#define GPS_PCND_SDK_PUNCH_LEFTGBC						(1<<10) /* GBC左 */
#define GPS_PCND_SDK_PUNCH_TOPGBC						(1<<11) /* GBC上 */
#define GPS_PCND_SDK_PUNCH_RIGHTGBC						(1<<12) /* GBC右 */
#define GPS_PCND_SDK_PUNCH_LEFTTOP						(1<<13) /* 左上1つ */

#define GPS_PCND_SDK_BIND_OFF							(1<<0) /* 製本無し */
#define GPS_PCND_SDK_BIND_MAGAZINE_LEFT					(1<<1) /* 週刊誌(左へ開く) */
#define GPS_PCND_SDK_BIND_MAGAZINE_RIGHT				(1<<2) /* 週刊誌(右へ開く) */

#define GPS_PCND_SDK_MAG_OFF							(1<<0) /* OFF */
#define GPS_PCND_SDK_MAG_ON								(1<<1) /* ON */

#define GPS_PCND_SDK_RESOL_PDF_600_FAST					(1<<0) /* 600dpi(2階調) */
#define GPS_PCND_SDK_RESOL_PDF_600_STD					(1<<1) /* 600dpi(標準) */
#define GPS_PCND_SDK_RESOL_PDF_600_HIGH					(1<<2) /* 600dpi(高画質) */
#define GPS_PCND_SDK_RESOL_PDF_1200						(1<<3) /* 1200dpi */
#define GPS_PCND_SDK_RESOL_PDF_300						(1<<4) /* 300dpi */
#define GPS_PCND_SDK_RESOL_PDF_1200_2					(1<<5) /* 1200dpi(2bit) */

typedef struct gps_pdl_skd_printcondition{

	unsigned char printpages[GPS_SDK_PAGES_LEN];	/* 論理ページ指定(生成対象ページ)  要NULLターミネート */

	/* 強制両面 */
	unsigned long forced_duplex;

	/* 両面 */ /* PDF用 */
	unsigned long duplex;

	/* 強制モノクロ */
	unsigned long forced_colormode;

	/* カラーモード */ /* PDF用 */
	unsigned long colormode;

	/* トナーセーブ(カラー機) */
	unsigned long tonersave_color;

	/* トナーセーブ(モノクロ機) */
	unsigned long tonersave_mono;

	/* 部数 */
	unsigned int print_num;

	/* 用紙種類変更有無 */ /* PDF用 */
	unsigned long chg_paper_kind;

	/* 用紙種類 */ /* PDF用 */
	unsigned int  paper_kind;

	/* 集約 */ /* PDF用 */
	unsigned long nup;

	/* 集約パラメータ */ /* PDF用 */
	unsigned long nup_option;

	/* 集約仕切り線 */ /* PDF用 */
	unsigned long nup_border;

	/* PDFパスワード文字列 要NULLターミネート */ /* PDF用 */
	unsigned char pdfpassword[GPS_SDK_PDF_PASSWORD_LEN];

	/* 給紙トレイ選択 */ /* PDF用 */
	unsigned long inputtray;

	/* ソート */ /* PDF用 */
	unsigned long sort;

	/* スタック */ /* PDF用 */
	unsigned long stack;

	/* ステープル */ /* PDF用 */
	unsigned long staple;

	/* パンチ */ /* PDF用 */
	unsigned long punch;

	/* 製本 */ /* PDF用 */
	unsigned long bind;

	/* 用紙サイズ指定 */ /* PDF用 */
	struct {

		/* 用紙サイズ変倍 */
		unsigned long magnification;

		/* 紙サイズコード */
		unsigned int  size_code;

		/* フリーサイズ時の用紙幅  (0.1mm単位) */
		unsigned long paper_width;

		/* フリーサイズ時の用紙高さ(0.1mm単位) */
		unsigned long paper_length;

	} paper_size;
	
	/* 解像度 */
	struct {

		/* PDF用 */
		unsigned long pdf;

	} resolution;

	unsigned long reserve[13];					/* 予約 */

} gps_pdl_sdk_printcondition_t;


#endif /* SDKPRINTCOND_H_ */
