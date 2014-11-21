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

#ifndef	__INC_GPS_NEW_COLOR_DEF__	/* { */
#define	__INC_GPS_NEW_COLOR_DEF__

/*
 * 共有メモリの定義
 */

/**** ガンマデータ構造体の定義 ****/
typedef	struct {
	long	gam[GPS_MAX_HEADRANK];		/* 往路ガンマデータへのオフセット */
	long 	gam2[GPS_MAX_HEADRANK];		/* 復路ガンマデータへのオフセット */
} gps_nclr_gam_t;

/**** ディザデータ構造体の定義 ****/
typedef	struct {
	long	dit;			/* ディザデータへのオフセット */
	ushort	ditsz;			/* ディザデータのサイズ */
	ushort	xsz;			/* ディザマトリックスのＸサイズ */
	ushort	ysz;			/* ディザマトリックスのＹサイズ */
	ushort	thrshpln;		/* ディザの閾値プレーン数（出力レベルの数） */
	uchar	e_flag_max;		/* 定着温度制御用フラグ(上位4bit) */
	uchar	e_flag_mid;		/* 定着温度制御用フラグ(下位4bit) */
} gps_nclr_dit_t;

/**** 誤差拡散データ構造体の定義 ****/
typedef struct
{
	ulong	size;			/* ガンマデータのサイズ */
	ushort	plane;			/* プレーン数 */
	ushort	mask_x;			/* マスクテーブルＸサイズ */
	ushort	mask_y;			/* マスクテーブルＹサイズ */
	long	thrdata;		/* 閾値データへのオフセット */
	long	mask;			/* マスクテーブルへのオフセット*/
}
gps_nclr_ed_t;

/*** 色毎データ構造体の定義 ***/
typedef	struct {
	long	gam;			/* ガンマデータ構造体へのオフセット */
	long	dit;			/* ディザデータ構造体へのオフセット */
	long	ed;				/* 誤差拡散ヘッダー構造体へのオフセット */
	long	ed_gam;			/* 誤差拡散ガンマデータ構造体へのオフセット */
} gps_nclr_plane_t;

/*** 適量テーブルデータ構造体の定義 ***/
typedef struct
{
	ulong	size;		/* データサイズ */ 
	long	lit;		/* 適量テーブルデータへのオフセット */
	long	inv;		/* 逆変換テーブルデータへのオフセット */
}
gps_nclr_drop_t;

/*** BG/UCRデータ構造体の定義 ***/
typedef struct
{
	ulong	size;		/* データサイズ */
	long	bg;			/* BGデータへのオフセット */
	long	ucr;		/* UCRデータへのオフセット */
}
gps_nclr_bgucr_t;

/*** 総量規制データ構造体の定義 ***/
typedef struct
{
	ulong	size;		/* データサイズ */
	long	limit;		/* 総量規制データへのオフセット */
}
gps_nclr_limit_t;

/*** 両面ガンマ割合データ構造体の定義 ***/	
typedef struct
{
	ulong	size;		/* データサイズ */
	long	gam_front;	/* 両面ガンマ割合へのオフセット（表面）*/
	long	gam_back;	/* 両面ガンマ割合へのオフセット（裏面）*/
}
gps_nclr_dupgam_t;

/* WiShGCRフォーマット (07A) */
typedef struct
{
	ulong	size;		/* 本構造体のサイズ */
	long	CB_bg_wish;	/* CBのBGテーブルへのオフセット */
	long	CB_ucr_wish;	/* CBのUCRテーブルへのオフセット */
	long	CG_bg_wish;	/* CGのBGテーブルへのオフセット */
	long	CG_ucr_wish;	/* CGのUCRテーブルへのオフセット */
	long	YG_bg_wish;	/* YGのBGテーブルへのオフセット */
	long	YG_ucr_wish;	/* YGのUCRテーブルへのオフセット */
	long	MB_bg_wish;	/* MBのBGテーブルへのオフセット */
	long	MB_ucr_wish;	/* MBのUCRテーブルへのオフセット */
	long	MR_bg_wish;	/* MBのBGテーブルへのオフセット */
	long	MR_ucr_wish;	/* MBのUCRテーブルへのオフセット */
	long	YR_bg_wish;	/* YRのBGテーブルへのオフセット */
	long	YR_ucr_wish;	/* YRのUCRテーブルへのオフセット */
}
gps_nclr_wishgcr_t;


/** モード毎データ構造体の定義 **/
typedef struct
{
	/* 各色データ */
	gps_nclr_plane_t	color[GPS_CLR_PLANE];
	/* 適量データ */
	gps_nclr_drop_t	drop;
	/* 総量規制データ */
	gps_nclr_limit_t	limit;
	/* 誤差拡散用適量データ */
	gps_nclr_drop_t	ed_drop;
	/* 誤差拡散用総量規制データ */
	gps_nclr_limit_t	ed_limit;
	/* BG/UCRデータ */
	gps_nclr_bgucr_t	bgucr;
	/* 両面ガンマ割合データ */	
	gps_nclr_dupgam_t	dupgam;
	/* WishGCRデータ*/
	gps_nclr_wishgcr_t	wishgcr;
} 
gps_nclr_data_t;

/* 共有メモリヘッダの定義 */
typedef	struct {
	int				size;		/* このメモリの大きさ */
	ulong			stat;		/* ステータス */
	ushort			dmode;		/* 描画モード数 */
	ushort			numcolor;	/* 色数 (==GPS_CLR_PLANE) */
	ulong			off;		/* データポインタへのオフセット */
	gps_nclr_data_t	data;		/* モード毎データの配列 */
/*
   data[dmode]は以下のようなメモリイメージになる。但し、データが存在しない場合には、各オフセット値は０とする。
	long	gam;		ID=0,color=0のガンマデータ構造体へのオフセット
	long	dit;		ID=0,color=0のディザデータ構造体へのオフセット
	long	ed;			ID=0,color=0の誤差拡散データ構造体へのオフセット
	long	ed_gam;		ID=0,color=0の誤差拡散データ構造体へのオフセット	
	…	…		…
	long	gam;		ID=0,color=3のガンマデータ構造体へのオフセット
	long	dit;		ID=0,color=3のディザデータ構造体へのオフセット
	long	ed;			ID=0,color=3の誤差拡散データ構造体へのオフセット
	long	ed_gam;		ID=0,color=3の誤差拡散データ構造体へのオフセット
	long	drop;	  	ID=0の適量テーブルデータ構造体へのオフセット
	long	limit;		ID=0の総量規制テーブルデータ構造体へのオフセット
	long	ed_drop;	ID=0の誤差拡散適量テーブルデータ構造体へのオフセット
	long	ed_limit;	ID=0の誤差拡散総量規制テーブルデータ構造体へのオフセット
	long	bgucr;		ID=0のBGUCRテーブルデータ構造体へのオフセット
	long	dupgam;		ID=0の両面ガンマ割合データ構造体へのオフセット
	…	…		…
	long	gam;		ID=1,color=0のガンマデータ構造体へのオフセット
	long	dit;		ID=1,color=0のディザデータ構造体へのオフセット
	long	ed;			ID=1,color=0の誤差拡散データ構造体へのオフセット
	long	ed_gam;		ID=1,color=0の誤差拡散データ構造体へのオフセット
	…	…		…
	long	gam;		ID=1,color=3のガンマデータ構造体へのオフセット
	long	dit;		ID=1,color=3のディザデータ構造体へのオフセット
	long	ed;			ID=1,color=3の誤差拡散データ構造体へのオフセット
	long	ed_gam;		ID=1,color=3の誤差拡散データ構造体へのオフセット
	long	drop;	  	ID=1の適量テーブルデータ構造体へのオフセット
	long	limit;		ID=1の総量規制テーブルデータ構造体へのオフセット
	long	ed_drop;	ID=1の誤差拡散適量テーブルデータ構造体へのオフセット
	long	ed_limit;	ID=1の誤差拡散総量規制テーブルデータ構造体へのオフセット	
	long	bgucr;		ID=1のBGUCRテーブルデータ構造体へのオフセット
	long	dupgam;	ID=1の両面ガンマ割合データ構造体へのオフセット	
	…	…		…
	long	gam;		ID=dmode-1,color=numcolor-1のガンマデータ構造体へのオフセット
	long	dit;		ID=dmode-1,color=numcolor-1のディザデータ構造体へのオフセット
	long	ed;		ID=dmode-1,color=numcolor-1の誤差拡散データ構造体へのオフセット
	long	ed_gam;	ID=dmode-1,color=numcolor-1の誤差拡散データ構造体へのオフセット
	…	…		…
*
   IDとはgpsColor_getID()で得たカラーモードID
   colorとは、Jupiterでは
	#define GPS_CLR_K 0
	#define GPS_CLR_C 1
	#define GPS_CLR_M 2
	#define GPS_CLR_Y 3
	#define GPS_CLR_PLANE 4   　となる
*/
} gps_nclr_shdm_t;

/* ガンマファイルデータ取り出し用構造体の定義 */
typedef	struct {
	uchar	fname[64];				/* ガンマデータファイルのfilename */
	int		off[GPS_CLR_PLANE];		/* 色別offset値 */
}	gps_nclr_gmfile_t;

/* 描画モードパラメータ構造体の定義 */
typedef	struct {
	int		whatis;					/* bit 0:SPモードで指定されている */
									/* UPモードガンマ対象 */
	ushort	hdpi;					/* for horizontal resolution (ex. 1200) */
	ushort	vdpi;					/* for vertical resolution (ex. 600) */
	ushort	mode;					/* for id:D draw mode (ex.Photo/Text) */
	uchar	bit;					/* for N bit (ex.1,2,4) */
	uchar	id;						/* id for liblary */
	uchar	prt;					/* for print mode */
	uchar	paper;					/* for paper type */
} gps_nclr_drawparam_t;

#endif	/* } __INC_GPS_NEW_COLOR_DEF__ */
