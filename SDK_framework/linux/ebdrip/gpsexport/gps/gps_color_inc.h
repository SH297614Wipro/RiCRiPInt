/*
 * GPS COLOR LIBRARY TYPE DEFINITION.
 * Copyright (c) Ricoh Company, Ltd.
 * ALL Rights Reserved.
 *
 * $Id: gps_color_inc.h,v 1.8 2000/12/05 13:35:00 MrX Exp MrX $
 * $Date: 2000/12/05 13:35:00 $
 * $Author: MrX $
 *
 * ガンマ・ディザデータの型定義
 *
 */

#ifndef	__INC_GPS_COLOR_DEF__	/* { */
#define	__INC_GPS_COLOR_DEF__

/*
 * 【１】
 * 標準型宣言
 */

#define	ulong	unsigned long
#define	ushort	unsigned short
#define	uchar	unsigned char



#include "gps_color_mtype.h"

/*
 * 【２】
 * 共有メモリの定義
 */

/**** ガンマデータ構造体の定義 ****/
typedef	struct {
	long	gam;		/* ガンマデータへのオフセット */
	ulong	gamsz;		/* ガンマデータのサイズ */
} gps_clr_gam_t;

/**** ディザデータ構造体の定義 ****/
typedef	struct {
	long	dit;		/* ディザデータへのオフセット */
	ushort	ditsz;		/* ディザデータのサイズ */
	ushort	xsz;		/* ディザマトリックスのＸサイズ */
	ushort	ysz;		/* ディザマトリックスのＹサイズ */
	ushort	thrshpln;	/* ディザの閾値プレーン数 */
} gps_clr_dit_t;

/*** 色毎データ構造体の定義 ***/
typedef	struct {
	long	gam;		/* ガンマ構造体へのオフセット */
	long	dit;		/* ディザ構造体へのオフセット */
} gps_clr_plane_t;

/** モード毎データ構造体の定義 **/
typedef	struct {
	/* 各色データ構造体へのオフセット */
	gps_clr_plane_t	color[GPS_CLR_PLANE];
} gps_clr_data_t;

/* 共有メモリヘッダの定義 */
typedef	struct {
	int				size;		/* このメモリの大きさ */
	ulong			stat;		/* ステータス */
	ushort			dmode;		/* 描画モード数 */
	ushort			numcolor;	/* 色数 (==GPS_CLR_PLANE) */
	ulong			off;		/* データポインタへのオフセット */
	gps_clr_data_t	data;		/* モード毎データの配列 */
/*
   data[dmode]は以下のようなメモリイメージになる
	long	gam;		ID=0,color=0のガンマ構造体へのオフセット【２】を参照
	long	dit;		ID=0,color=0のディザ構造体へのオフセット【３】を参照
	long	gam;		ID=0,color=1のガンマ構造体へのオフセット
	long	dit;		ID=0,color=1のディザ構造体へのオフセット
	…	…		…
	long	gam;		ID=1,color=0のガンマ構造体へのオフセット
	long	dit;		ID=1,color=0のディザ構造体へのオフセット
	…	…		…
	long	gam;		ID=dmode-1,color=numcolor-1のガンマ構造体へのオフセット
	long	dit;		ID=dmode-1,color=numcolor-1のディザ構造体へのオフセット
*
   IDとはgpsColor_getID()で得たカラーモードID
   colorとは、Jupiterでは
	#define GPS_CLR_K 0
	#define GPS_CLR_C 1
	#define GPS_CLR_M 2
	#define GPS_CLR_Y 3
	#define GPS_CLR_PLANE 4   　となる
*/
} gps_clr_shdm_t;

/* statのbit定義 */
#define	GAMM_UPDREQ	0		/* gamma変更要求 */
#define	TLIM_UPDREQ	1		/* 総量規制値変更要求 */


/*
 * 【３】
 * 引数の型定義
 */
/* 量子化bit定義 */
#define	GPS_COLOR_QUANT_BIT1	1	/* 1bit */
#define	GPS_COLOR_QUANT_BIT2	2	/* 2bit */
#define	GPS_COLOR_QUANT_BIT4	4	/* 4bit */
#define	GPS_COLOR_QUANT_BIT8	8	/* 8bit */

/* ディザ・γの描画モード定義 */
#define	PHOTO_DRAWMODE		0
#define	TEXT_DRAWMODE		1
#define	GRAP_DRAWMODE		2
#define	THIN_DRAWMODE		3
#define	PHOTO2_DRAWMODE		4

/* gps_color_file.h に移動したが、互換性のためこちらにも入れた */
#ifndef	SPCL_DRAWMODE_BIT
#define	SPCL_DRAWMODE_MSK			0xFFFF		/* mask for file id (same mode, maybe) */
#define	SPCL_DRAWMODE_BIT			16			/* flag of no gamma calc */
#define	NOREARRANGE_DRAWMODE_BIT	17			/* flag to has no rearrange data */
#define	SPCL_DRAWMODE	(1<<SPCL_DRAWMODE_BIT)	/* mask for no gammma calc */
#define	NOREARRANGE_DRAWMODE	(1<<NOREARRANGE_DRAWMODE_BIT)
												/* mask for no rearrage data */
#endif

/* 総量規制のモード定義 */
#define	TLIMIT_PHOTOMODE	0
#define	TLIMIT_TEXTMODE		1

/* ガンマファイルデータ取り出し用構造体の定義 */
typedef	struct {
	uchar	fname[64];				/* ガンマデータファイルのfilename */
	int		off[GPS_CLR_PLANE];		/* 色別offset値 */
}	gps_clr_gmfile_t;

/* ガンマ計算用構造体の定義 */
	/* ユーザー・サービスガンマデータのサイズ */
#define	GPS_COLOR_UGAMSZALL	(GPS_CLR_GAMUMODE)
#define	GPS_COLOR_SGAMSZ1M	(GPS_CLR_GAMSPNTS)
typedef	struct {
	uchar	ug[GPS_COLOR_UGAMSZALL];	/* ユーザーガンマデータ */
	uchar	sg[GPS_COLOR_SGAMSZ1M];		/* サービスガンマデータ */
}	gps_clr_calcgam_t;

/* 描画モードパラメータ構造体の定義 */
typedef	struct {
	int		whatis;					/* bit 0:SPモードで指定されている */
									/* UPモードガンマ対象 */
	ushort	hdpi;					/* for horizontal resolution (ex. 1200) */
	ushort	vdpi;					/* for vertical resolution (ex. 600) */
	ushort	mode;					/* for id:D draw mode (ex.Photo/Text) */
	uchar	bit;					/* for N bit (ex.1,2,4) */
	uchar	id;						/* id for liblary */
} gps_color_drawparam_t;
/* whatisのbit定義 */
#define	SPmode_set		0			/* On:SPモードで指定されている */
#define	effectUPgamma	1			/* On:UPモードガンマ対象 */
/* whatisをチェックする　（引数はgps_color_idsrch_t*）*/
#define	check_spmodeDID(x)		((x)->whatis & (1<<SPmode_set))
#define	check_effectUPrDID(x)	((x)->whatis & (1<<effectUPgamma))

/*
 * 【２Ａ】
 * カラーテスト印刷用共有メモリの定義
 */
/* カラーテスト印刷用共有メモリヘッダの定義 */
typedef	struct {
	int				size;		/* このメモリの大きさ */
	int				ext;		/* 拡張用 */
	int				data;		/* size分のデータ領域 */
} gps_clr_shdm2_t;


/*
 * 【３Ａ】
 * カラーテスト印刷用の定義
 */
#define	GPS_COLOR_SHRDWKSZ	GPS_CLR_PIXEL_OUT


#endif	/* } __INC_GPS_COLOR_DEF__ */
