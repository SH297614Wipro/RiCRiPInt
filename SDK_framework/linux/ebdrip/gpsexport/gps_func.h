/* -*- tab-width: 4; c-basic-offset: 4; -*- *** vi:ts=4:sw=4
 ***********************************************************
 *	$Id$
 *
 *	Copyright (C) 2001 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *	FILE NAME	: gps_func.h
 *	VERSION		: $Revision$
 *	AUTHOR		: Satoshi MIYAZAKI
 *----------------------------------------------------------
 *	HISTORY
 *	miyazaki - 22 Jun 2001: Created.
 *	$Log$
 *
 ***********************************************************/
#ifndef _GPS_FUNC_H_
#define	_GPS_FUNC_H_

/*
 *
 */
extern void gpsApiInit(gwmsg_client_t *client);

/*
 * Function Returns
 */
#define	GPS_FUNC_SUPPORT	(1)
#define	GPS_FUNC_NOT_SUPPORT	(0)

/**********************************************************
 * Function
 * 環境変数にセットするビットが 31 まで増えたら次の環境変
 * 数を用意する事
 * 使用変数: gps_function_support_info
 **********************************************************/

/**********************************************************
 * id	: 2500
 * 名称	: gpsGetHddInfo2()
 * date	: 2001/06/22
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_GET_HDD_INFO2 を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_GET_HDD_INFO2	(1<<0)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_hddinfo2 {
	char	stat;						/* status        */
	char	path[GPS_MAX_HDD_PATH_LEN];	/* path          */
	long	f_bsize;					/* block size    */
	long	f_blocks;					/* total blocks  */
	long	f_bfree;					/* free blocks   */
	long	reserve;					/* reserve       */
} gps_hddinfo2_t;

/* gps_hddinfo2: stat */
#define	GPS_HDDSTAT_UNKNOWN	0
#define	GPS_HDDSTAT_NONE	1
#define	GPS_HDDSTAT_READY	2

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetHddInfo2( gwmsg_client_t* client, int hdd, int *status, gps_hddinfo2_t *hddinfo2 );


/**********************************************************
 * id	: 2501
 * 名称	: gpsPlotSetShift()
 * date	: 2001/06/22
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_SET_SHIFT を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PLOT_SET_SHIFT	(1<<1)

/*
 * 追加される API のプロトタイプ
 */
extern int gpsPlotSetShift( gwmsg_client_t* client, int plotid, int shiftoff );


/**********************************************************
 * id	: 2502
 * 名称	: gpsGetPrmInfo()
 * date	: 2001/06/30
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_GET_PRMINFP を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_GET_PRM_INFO		(1<<2)

/* gpsGetPrmInfo(): f_id */
/* GWID_GpsEv_GetPrmInfo_Res: f_id */
#define	GPS_PRMINFO_GET_JOBSPOOL	0
#define	GPS_PRMINFO_GET_TOTALCOUNT	1
#define GPS_PRMINFO_GET_MAXIMGSIZE	2
#define GPS_PRMINFO_GET_NUMFLASHMEM	3
#define GPS_PRMINFO_GET_MAXPAPERSIZE	4
#define GPS_PRMINFO_GET_XPDL_ELANG	5
#define GPS_PRMINFO_GET_COLOR_MODEL	6
#define GPS_PRMINFO_GET_PAGEEXIST	7
#define GPS_PRMINFO_GET_TESTPRINT_LOCK	8
#define GPS_PRMINFO_GET_MACHINE_PPM	9
#define GPS_PRMINFO_GET_FIRMPROHIBIT	10
#define GPS_PRMINFO_GET_CARTRIDGEINFO	11
#define GPS_PRMINFO_GET_CARTRIDGECOUNT	12
#define GPS_PRMINFO_GET_MICRINFO		13


/* gpsGetPrmInfo(): status */
/* GWID_GpsEv_GetPrmInfo_Res: status */
#define GPS_PRMINFO_SUCCESS			0
#define GPS_PRMINFO_FAILED			1
#define GPS_PRMINFO_QUEUE			2
#define GPS_PRMINFO_CHECKING        3

/* gpsGetPrmInfo: GPS_PRMINFO_GET_COLOR_MODEL: long data */
#define	GPS_CM_BW_MACHINE		0	/* Black and White */
#define	GPS_CM_FULL_COLOR_MACHINE	1	/* Full Color */
#define	GPS_CM_TWIN_COLOR_MACHINE	2	/* Twin Color */

/* gpsGetPrmInfo: GPS_PRMINFO_GET_MICRINFO: long data */
enum {
	GPS_SYS_MODEL_STANDARD,			/* 0:RICOH標準モデル */
	GPS_SYS_MODEL_MICR_SECURE_PCL,	/* 1:Secure PCL MICRモデル */
	GPS_SYS_MODEL_MICR_IPDS			/* 2:IPDS MICRモデル */
};

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetPrmInfo( gwmsg_client_t* client, int f_id, int* status, int size, void* data);


/**********************************************************
 * id	: 2503
 * 名称	: gpsPlotSetPageParam2()
 * date	: 2001/07/26
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_SET_PAGE_PARAM2 を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PLOT_SET_PAGE_PARAM2	(1<<3)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_pageparam2 {
	unsigned long	flag;					/* 設定するパラメータ */
#define	GPS_PARAM2_SHIFT					(1<<0)	/* パラメータ shift が有効 */
#define	GPS_PARAM2_BACKCOVER				(1<<1)	/* パラメータ backcover が有効 */
#define	GPS_PARAM2_BACKCOVERPRINT			(1<<2)	/* パラメータ backcoverprint が有効 */
#define	GPS_PARAM2_BACKCOVERTRAY			(1<<3)	/* パラメータ backcovertray が有効 */
#define	GPS_PARAM2_PARTITION				(1<<4)	/* パラメータ partition が有効 */
#define	GPS_PARAM2_PARTITIONCYCLE			(1<<5)	/* パラメータ partitioncycle が有効 */
#define	GPS_PARAM2_STAMP					(1<<6)	/* パラメータ stamp が有効 */
#define	GPS_PARAM2_Z_FOLD					(1<<7)	/* パラメータ z_fold が有効 */
#define	GPS_PARAM2_DUPLEXMODE				(1<<8)	/* パラメータ duplexmode が有効 */
#define	GPS_PARAM2_W_FOLD					(1<<9)	/* パラメータ w_fold が有効 */
#define	GPS_PARAM2_W_PUNCH					(1<<10)	/* パラメータ w_punch が有効 */
#define	GPS_PARAM2_W_EDGEFOLD				(1<<11)	/* パラメータ w_edgefold が有効 */
#define	GPS_PARAM2_ZIG_WIDTH				(1<<12)	/* パラメータ zig_width が有効 */
#define GPS_PARAM2_RING_BIND				(1<<13)	/* パラメータ ring_bind が有効 */
#define GPS_PARAM2_PERF_BIND				(1<<14)	/* パラメータ perf_bind が有効 */
#define GPS_PARAM2_PERF_TRIM				(1<<15)	/* パラメータ perf_trim が有効 */
#define GPS_PARAM2_PERF_PAPERCODE			(1<<16)	/* パラメータ perf_paper_code が有効 */
#define GPS_PARAM2_PERF_PAPERWIDTH			(1<<17)	/* パラメータ perf_paper_width が有効 */
#define GPS_PARAM2_PERF_PAPERLENGTH			(1<<18)	/* パラメータ perf_paper_length が有効 */
#define GPS_PARAM2_PERF_INPUTTRAY			(1<<19)	/* パラメータ perf_input_tray が有効 */
#define GPS_PARAM2_PERF_COVERTRAY			(1<<20)	/* パラメータ perf_cover_tray が有効 */
#define GPS_PARAM2_PERF_IMAGEVERT			(1<<21)	/* パラメータ perf_image_vert が有効 */
#define GPS_PARAM2_PERF_IMAGEHORI			(1<<22)	/* パラメータ perf_image_hori が有効 */
#define GPS_PARAM2_PERF_FINALPAPERCODE		(1<<23)	/* パラメータ perf_final_paper_code が有効 */
#define GPS_PARAM2_PERF_FINALPAPERWIDTH		(1<<24)	/* パラメータ perf_final_paper_width が有効 */
#define GPS_PARAM2_PERF_FINALPAPERLENGTH	(1<<25)	/* パラメータ perf_final_paper_length が有効 */
#define GPS_PARAM2_PERF_FINALPAPPERVERT		(1<<26)	/* パラメータ perf_final_paper_vert が有効 */
#define GPS_PARAM2_PERF_CUTPAPERTOP			(1<<27)	/* パラメータ perf_cut_paper_top が有効 */
#define GPS_PARAM2_PERF_CUTPAPERBOTTOM		(1<<28)	/* パラメータ perf_cut_paper_bottom が有効 */
#define GPS_PARAM2_PERF_CUTPAPERSIDE		(1<<29)	/* パラメータ perf_cut_paper_side が有効 */
#define	GPS_PARAM2_W_MACHINESTAMP			(1<<30)	/* パラメータ w_machinestamp が有効 */

	unsigned char	shift:1;		/* 部間でシフトをする／しない（ジョブ間は gps_pageparam_tの shiftoff）*/
	unsigned char	stamp:1;		/* 本体スタンプを使用する */
#define	GPS_STAMP_OFF		(0)		/* 使用しない */
#define	GPS_STAMP_ON		(1)		/* 使用する */

	unsigned char	duplexmode:1;	/* ドライバーから両面指定 */
#define	GPS_DUPLEXMODE_OFF	(0)		/* 両面指定なし */
#define	GPS_DUPLEXMODE_ON	(1)		/* 両面指定あり */

	unsigned char	w_punch:1;		/* 折り機パンチ */
#define	GPS_W_PUNCH_OFF			(0)		/* 折り機パンチなし */
#define	GPS_W_PUNCH_ON			(1)		/* 折り機パンチあり */

	unsigned char	w_edgefold:1;	/* 耳折り */
#define	GPS_W_EDGEFOLD_OFF		(0)		/* 耳折りなし */
#define	GPS_W_EDGEFOLD_ON		(1)		/* 耳折りあり */

	unsigned char	w_machinestamp:1;	/* メカスタンプ */
#define	GPS_W_MACHINE_STAMP_OFF	(0)		/* 使用しない */	
#define	GPS_W_MACHINE_STAMP_ON	(1)		/* 使用する */

	unsigned char	res1:2;

	unsigned char	backcover;		/* 裏表紙モード */
#define	GPS_COVER_BACK		(0x02)	/* 裏表紙あり */

	unsigned char	backcoverprint;	/* 裏表紙画像印刷面 */
/*		GPS_COVER_BACK		(0x02)	   裏表紙印刷あり */
#define	GPS_COVER_BACK_R	(0x22)	/* 裏表紙反転（内側に）印刷 */

	unsigned char	backcovertray;	/* 裏表紙トレイ */

	unsigned char	partition;		/* 仕切紙モード */
#define	GPS_PARTITION_OFF	(0)		/* 仕切紙なし */
#define	GPS_PARTITION_SORT	(1)		/* 部単位 */
#define	GPS_PARTITION_JOB	(2)		/* ジョブ単位 */

	unsigned short	partitioncycle;	/* 仕切紙の部数指定（部単位の場合のみ有効） */

	unsigned char	z_fold;			/* Ｚ折り */
#define	GPS_Z_FOLD_OFF		(0)		/* Ｚ折りなし */
#define	GPS_Z_FOLD_RIGHT	(1)		/* 右折り */
#define	GPS_Z_FOLD_BOTTOM	(2)		/* 下折り */
#define	GPS_Z_FOLD_LEFT		(3)		/* 左折り */

	unsigned char	w_fold;			/* 広幅折り */
#define	GPS_W_FOLD_OFF			GPS_Z_FOLD_OFF		/* 折りなし */
#define	GPS_W_FOLD_ZIGZAG		(1)		/* ジャバラ折り */
#define	GPS_W_FOLD_ZIGZAGFILE	(2)		/* ジャバラファイル折り */
#define	GPS_W_FOLD_BASIC		(3)		/* 基本折り */
#define	GPS_W_FOLD_BAG			(4)		/* 袋折り */
#define	GPS_W_FOLD_FILE			(5)		/* ファイル折り */
#define	GPS_W_FOLD_CUSTOM1		(6)		/* 特殊折り１ */
#define	GPS_W_FOLD_CUSTOM2		(7)		/* 特殊折り２ */
#define	GPS_W_FOLD_PROGRAM1		(8)		/* プログラム折り１ */
#define	GPS_W_FOLD_PROGRAM2		(9)		/* プログラム折り２ */
#define	GPS_W_FOLD_PROGRAM3		(10)	/* プログラム折り３ */
#define	GPS_W_FOLD_PROGRAM4		(11)	/* プログラム折り４ */
#define	GPS_W_FOLD_ZIGZAGCUSTOM1	(12)	/* 長尺特殊折り１ */
#define	GPS_W_FOLD_ZIGZAGCUSTOM2	(13)	/* 長尺特殊折り２ */
	unsigned long	zigzag_width;	/* ジャバラ折りの折り幅 */

	unsigned char	ring_bind;			/* リング製本(モード設定 | 綴じ位置) */
#define	GPS_RING_BIND_OFF		(0)		/* しない */
#define	GPS_RING_BIND_LEFT		(1)		/* 左綴じ */
#define	GPS_RING_BIND_TOP		(2)		/* 上綴じ */
#define	GPS_RING_BIND_RIGHT		(3)		/* 右綴じ */
#define	GPS_RING_MODE_OFF		(0x00)	/* モードOFF */
#define	GPS_RING_MODE_PUNCH		(0x10)	/* パンチのみモード */
#define	GPS_RING_MODE_RING		(0x20)	/* リング製本モード */
#define	GPS_RING_BIND_MASK		(0x0F)	/* 綴じ位置指定ビット */
#define	GPS_RING_MODE_MASK		(0xF0)	/* モード指定ビット */

	unsigned char	perf_bind;			/* くるみ製本(綴じ位置) */
#define GPS_PERF_BIND_OFF		(0) 	/* しない */
#define GPS_PERF_BIND_LEFT		(1) 	/* 左綴じ */
#define GPS_PERF_BIND_TOP		(2) 	/* 上綴じ */
#define GPS_PERF_BIND_RIGHT 	(3) 	/* 右綴じ */

	unsigned char	perf_trim;			/* くるみ製本(仕上がりサイズ指定方法 | 裁断設定) */
#define GPS_PERF_TRIM_NONE		(0)		/* 裁断なし */
#define GPS_PERF_TRIM_SINGLE	(1)		/* 小口カット */
#define GPS_PERF_TRIM_TRIPLE	(2)		/* 三辺カット */
#define GPS_PERF_MODE_OFF		(0x00)	/* 指定なし */
#define GPS_PERF_MODE_FINALSIZE	(0x10)	/* 仕上がりサイズ指定 */
#define GPS_PERF_MODE_CUTSIZE	(0x20)	/* カット量指定 */
#define	GPS_PERF_TRIM_MASK		(0x0F)	/* 裁断方法指定ビット */
#define	GPS_PERF_MODE_MASK		(0xF0)	/* 仕上がりサイズ方法指定ビット */

	unsigned char	perf_paper_code;	/* くるみ製本 中紙サイズコード(paper.h 参照) */
	unsigned long	perf_paper_width;	/* くるみ製本 フリーサイズ時の中紙幅   (0.1mm単位) */
	unsigned long	perf_paper_length;	/* くるみ製本 フリーサイズ時の中紙高さ (0.1mm単位) */

	unsigned char	perf_input_tray;	/* くるみ製本 中紙給紙トレイ */

	unsigned char	perf_cover_tray;	/* くるみ製本 表紙トレイ */

	long			perf_image_vert;	/* くるみ製本 作像天地位置調整 (0.1mm単位) */
	long			perf_image_hori;	/* くるみ製本 作像小口位置調整 (0.1mm単位) */

	unsigned char	perf_final_paper_code;		/* 仕上がりサイズ指定時 製本サイズコード(paper.h 参照) */
	long			perf_final_paper_width; 	/* 仕上がりサイズ指定時 フリーサイズ時の製本幅   (0.1mm単位) */
	long			perf_final_paper_length;	/* 仕上がりサイズ指定時 フリーサイズ時の製本高さ (0.1mm単位) */
	long			perf_final_paper_vert;		/* 仕上がりサイズ指定時 仕上がりサイズ位置調整 (0.1mm単位) */

	unsigned long	perf_cut_paper_top; 		/* カット量指定時 天方向   (0.1mm単位) */
	unsigned long	perf_cut_paper_bottom;		/* カット量指定時 地方向   (0.1mm単位) */
	unsigned long	perf_cut_paper_side;		/* カット量指定時 小口方向 (0.1mm単位) */

	/* 追加項目の領域確保 */
	unsigned char	res2[4];
} gps_pageparam2_t, *gps_pageparam2_p;

/*
 * 追加される API のプロトタイプ
 */
extern int gpsPlotSetPageParam2( gwmsg_client_t* client, int plotid, const gps_pageparam2_t *ppageparam2, int *result, unsigned long *flag );


/**********************************************************
 * id	: 2504
 * 名称	: gpsFrameLoadEnv()
 * date	: 2001/07/26
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FRAME_LOAD_ENV を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FRAME_LOAD_ENV	(1<<4)

/*
 * 追加される API のプロトタイプ
 */
extern int gpsFrameLoadEnv( gwmsg_client_t* client, int frameid );


/**********************************************************
 * id	: 2505
 * 名称	: gpsPlotChkDirection()
 * date	: 2001/07/26
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_CHK_DIRECTION を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PLOT_CHK_DIRECTION	(1<<5)

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsPlotChkDirection( gwmsg_client_t* client, int plotid, const gps_chkdirprm_t *condition, int *direction, int *slantdirection );


/**********************************************************
 * id	: 2506
 * 名称	: gpsFrameGetMultiBandShm()
 * date	: 2001/08/31
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FRAME_MULTIBAND を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FRAME_MULTIBAND	(1<<6)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_bandtable
{
	int				band_id;			/* バンドID */
	int				plane_id;			/* プレーンID */
	long			band_xdot;			/* バンド幅 */
	long			band_ydot;			/* バンド高さ */
	int				band_draw;			/* 描画結果 */
	int				band_skip;			/* 間引き */
	unsigned char	band_stat;			/* テーブル内のバンド使用状態 */
	void			*band_addr;

} gps_bandtable_t, *gps_bandtable_p;

/* gps_bandtable: band_stat */
#define GPS_BAND_GET	(1 << 0)
#define GPS_BAND_OPEN	(1 << 1)
#define GPS_BAND_CLOSE	(1 << 2)

/*
 * 追加される API のプロトタイプ
 */
extern int gpsFrameGetMultiBandShm( gwmsg_client_t* client, long *offset, int *num );


/**********************************************************
 * id	: 2507
 * 名称	: gpsFrameGetMultiBand()
 * date	: 2001/08/31
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FRAME_MULTIBAND を定義する事
 **********************************************************/
/*
 * 追加される API のプロトタイプ
 */
extern int gpsFrameGetMultiBand( gwmsg_client_t* client, int frameid, int bandid, int *result );


/**********************************************************
 * id	: 2508
 * 名称	: gpsFrameFlushMultiBand()
 * date	: 2001/08/31
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FRAME_MULTIBAND を定義する事
 **********************************************************/
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsFrameFlushMultiBand( gwmsg_client_t* client, int frameid, int bandid, int *result );


/**********************************************************
 * id	: 2509
 * 名称	: gpsFrameChapterSet()
 * date	: 2001/07/26
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FRAME_CHAPTER_SET を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FRAME_CHAPTER_SET	(1<<7)

/*
 * 追加される API のプロトタイプ
 */
extern int gpsFrameChapterSet( gwmsg_client_t* client, int frameid, unsigned char mode, unsigned char paper_type );


/**********************************************************
 * id	: 2510
 * 名称	: gpsGetFontInfoWffn()
 * date	: 2001/12/04 (Tsusaka)
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h, gps_api 等に
 * GPS_SUPPORT_FONTINFO_WFFN を定義する事
 * (備考)
 * このI/Fは、GPSライブラリ内部でのみ使用される関数だが
 * サポート可否のチェックをする必要があるため、ここに
 * 追加する。(Tsusaka)
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FONTINFO_WFFN	(1<<8)

/*
 * API 追加に伴って追加される型定義
 */
#define	GPS_FONT_MEDIA_MEMORY	0	/* font media type is memory (eg. mask ROM) */
#define	GPS_FONT_MEDIA_FILE		1	/* font media type is file (eg. SD card) */
#define	GPS_MAX_FONT_PATH_LEN	92

typedef struct gps_fontinfo_wffn {
	int				media;	/* font media type */
	char			font_fname[GPS_MAX_FONT_PATH_LEN];	/* font file path */
	unsigned long	faddr;	/* offset address from start of file, or memory address */
	unsigned long	size;	/* font data size (not file size) */
	unsigned long	offset; /* offset address from offset to font contents */
} gps_fontinfo_wffn_t;	/* this structure size must not be excess 112(=(128-16)) bytes. */

/*
 * 追加される API のプロトタイプ
 */
/* int	gpsGetFontInfoWffn( gwmsg_client_t* client, int font, gps_fontinfo_wffn_t *fontinfo_wffn ); */


/**********************************************************
 * id	: 2511
 * 名称	: gpsPlotChangeBinding()
 * date	: 2001/12/12
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_CHANGE_BINDING を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PLOT_CHANGE_BINDING	(1<<9)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsPlotChangeBinding( gwmsg_client_t* client, int plotid, unsigned char binding, int *result );


/**********************************************************
 * id	: 2512
 * 名称	: gpsGetFlashMemInfo()
 * date	: 2002/01/10
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_GET_FLASH_MEM_INFO を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_GET_FLASH_MEM_INFO	(1<<10)

/*
 * API 追加に伴って追加される型定義
 */
#define	GPS_MAX_FM_PATH_LEN	64

typedef struct gps_flashmem_info {
	unsigned long	attr;				/* attribute */
	unsigned long	media;				/* kind of media */
	char		path[GPS_MAX_FM_PATH_LEN];	/* directory path */
	char		reserved[16];			/* reserved */
} gps_flashmem_info_t, *gps_flashmem_info_p;

/* gps_flashmem_info: attr */
#define	GPS_FLASHMEM_ATTR_RW	(1 << 0)	/* READ/WRITE
							(READONLY if not set) */

/* gps_flashmem_info: media */
#define	GPS_FLASHMEM_MEDIA_UNKNOWN	0		/* unknown media */
#define	GPS_FLASHMEM_MEDIA_ROM		1		/* ROM DIMM */
#define	GPS_FLASHMEM_MEDIA_SDCARD	2		/* SD Card */

/* gpsGetFlashMemInfo(): status */
#define	GPS_GETFMINFO_SUCCESS		0
#define	GPS_GETFMINFO_FAILED		1

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsGetFlashMemInfo(gwmsg_client_t* client, int fm_id, int *status, gps_flashmem_info_t *info);

/**********************************************************
 * id	: 2513
 * 名称	: gpsXpdlMenuEntryDone()
 * date	: 2002/01/16
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_XPDL_MENU_ENTRY を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_XPDL_MENU_ENTRY_DONE	(1<<11)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsXpdlMenuEntryDone( gwmsg_client_t* client );

/**********************************************************
 * id	: 2514
 * 名称	: gpsReqEventNotify()
 * date	: 2002/01/23
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_REQ_EVENT_NOTIFY を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_REQ_EVENT_NOTIFY	(1<<12)

/*
 * API 追加に伴って追加される型定義
 */
/* req */
#define	GPS_REQEVENT_ON		1
#define	GPS_REQEVENT_OFF	0

/* ev */
#define	GPS_REQEVENT_PAGEEXIT			(1 << 0)
#define	GPS_REQEVENT_XPDL_TESTPRN_DONE	(1 << 1)
#define	GPS_REQEVENT_XPDL_UJOB_END	(1 << 2)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsReqEventNotify(gwmsg_client_t* client, int req, unsigned long ev, unsigned long *res);


/**********************************************************
 * id	: 2515
 * 名称	: gpsFramePrintInfo()
 * date	: 2002/01/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FRAME_PRINT_INFO を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FRAME_PRINT_INFO	(1<<13)

/*
 * API 追加に伴って追加される型定義
 */
enum OBJECT_TYPE
{
	OBJECT_TYPE_CHAR,		/* 文字 */
	OBJECT_TYPE_IMAGE,		/* イメージ */
	OBJECT_TYPE_GRAPHIC,	/* グラフィック*/
	OBJECT_TYPE_LINE,		/* 線 */
	OBJECT_TYPE_NUM
};

typedef struct gps_pageinfo2 {
	unsigned long		flag;				/* 設定するパラメータ */
#define	GPS_INFO2_BYPASS_DIR		(1<<0)	/* パラメータ bypass_dir が有効 */
#define	GPS_INFO2_PWIDTH			(1<<1)	/* パラメータ paper_width が有効 */
#define	GPS_INFO2_PLENGTH			(1<<2)	/* パラメータ paper_length が有効 */
#define	GPS_INFO2_FWIDTH			(1<<3)	/* パラメータ frame_width が有効 */
#define	GPS_INFO2_FLENGTH			(1<<4)	/* パラメータ frame_length が有効 */
#define	GPS_INFO2_BAND				(1<<5)	/* パラメータ band_length が有効 */
#define	GPS_INFO2_PRINT_MODE		(1<<6)	/* パラメータ print_mode が有効 */
#define	GPS_INFO2_PAGE_SHIFT		(1<<7)	/* パラメータ page_shift が有効 */
#define	GPS_INFO2_PRINT_FACE		(1<<8)	/* パラメータ print_face が有効 */
#define	GPS_INFO2_DUMMY_PAGE		(1<<9)	/* パラメータ dummy_page が有効 */
/* COSMOS用ここから */
#define GPS_INFO2_DITHER_MODE		(1<<10)	/* パラメータ dither_mode が有効 */
#define GPS_INFO2_COLOR_MATCH		(1<<11)	/* パラメータ color_match が有効 */
#define GPS_INFO2_ORIENT			(1<<12)	/* パラメータ orientation が有効 */
#define GPS_INFO2_GRAY_PRINT		(1<<13)	/* パラメータ gray_print が有効 */
#define GPS_INFO2_RGB_COLOR			(1<<14)	/* パラメータ rgb_color_mode が有効 */
/* ここまで */
#define GPS_INFO2_ECO_COLOR			(1<<15)	/* パラメータ eco_color が有効 */
#define GPS_INFO2_FUSER_CTL			(1<<16)	/* パラメータ fuser_ctl が有効 */

	unsigned char		bypass_dir:2;		/* 用紙方向*/
#define	GPS_BYPASS_DIR_NONE			(0)
#define	GPS_BYPASS_DIR_LEF			(1)
#define	GPS_BYPASS_DIR_SEF			(2)

	unsigned char		page_shift:1;		/* ページ単位のシフト操作 */
#define	GPS_PAGE_SHIFT_NONE			(0)		/* シフトしない */
#define	GPS_PAGE_SHIFT_ON			(1)		/* シフトする */

	unsigned char	res1:5;

	unsigned char		print_mode;			/* 印刷モード */
#define GPS_PRINT_MODE_NONE			(0)		/* 指定しない */
#define GPS_PRINT_MODE_HIGH			(1)		/* 高速 */
#define GPS_PRINT_MODE_NORMAL		(2)		/* 標準 */
#define GPS_PRINT_MODE_QUALITY		(3)		/* 高画質 */
	unsigned char		print_face;			/* 両面印刷面 */

	unsigned char	res2[1];

	unsigned long		paper_width;		/* フリーサイズ時の用紙幅   (0.1mm単位) */
	unsigned long		paper_length;		/* フリーサイズ時の用紙長　 (0.1mm単位) */
	unsigned long		frame_width;		/* フレームの幅   (ドット単位) */
	unsigned long		frame_length;		/* フレームの長　 (ドット単位) */
	unsigned long		band_length;		/* バンドの長　   (ドット単位) */

	unsigned char		dummy_page;		/* ダミーページ */

#define GPS_DUMMY_PAGE_OFF			(0)	/* not a dummy page */
#define GPS_DUMMY_PAGE_BLANK			(1)	/* dummy blank page */

/* COSMOS用ここから */
	unsigned char		dither_mode[OBJECT_TYPE_NUM];		/* ディザデータ[COSMOS] */
		#define GPS_DITHER_AUTO		(0)	/* 自動 */
		#define GPS_DITHER_MODE1		(1)	/* 写真用 */
		#define GPS_DITHER_MODE2		(2)	/* 文字用 */

	unsigned char		color_match[OBJECT_TYPE_NUM];		/* カラーマッチングデータ[COSMOS] */
		#define GPS_COLOR_MATCH_OFF		(0)	/* しない */
		#define GPS_COLOR_MATCH_MODE1	(1)	/* あざやか優先 */
		#define GPS_COLOR_MATCH_MODE2	(2)	/* 階調優先 */
		#define GPS_COLOR_MATCH_MODE3	(3)	/* 文字優先 */

	unsigned char		orientation;					/* 原稿方向[COSMOS] */
		#define GPS_ORIENT_PORTRAIT		(0)	/* ポートレート */
		#define GPS_ORIENT_LANDSCAPE	(1)	/* ランドスケープ */

	unsigned char		gray_print[OBJECT_TYPE_NUM];		/* グレー印刷方式[COSMOS] */
		#define GPS_GRAY_PRINT_MODE1	(0)	/* なし(CMYK) */
		#define GPS_GRAY_PRINT_MODE2	(1)	/* 黒１色 */
		#define GPS_GRAY_PRINT_MODE3	(2)	/* グレー画素のみ黒１色 */

	unsigned char		rgb_color_mode;				/* RGBカラーモード[COSMOS] */
		#define GPS_RGB_MODE_COLOR		(0)	/* カラー */
		#define GPS_RGB_MODE_MONO		(1)	/* モノクロ */
/* ここまで */

	unsigned char		eco_color;		/* Economy Color Mode */
		#define GPS_ECO_COLOR_NONE		(0)	/* エコノミーカラーモード指定なし */
		#define GPS_ECO_COLOR_PRT		(1)	/* エコノミーカラーモード指定あり */

	unsigned char		fuser_ctl;		/* 定着温度下げ情報 */	
		#define GPS_FUSER_CTL_STD		(0)	/* 基準画像処理(温度を下げない) */
		#define GPS_FUSER_CTL_LEVEL1	(1)	/* 画像処理レベル１ */
		#define GPS_FUSER_CTL_LEVEL2	(3)	/* 画像処理レベル２ */

	/* 追加項目の領域確保 */
	unsigned char	res3[19];
} gps_pageinfo2_t, *gps_pageinfo2_p;

/*
 * 追加される API のプロトタイプ
 */
extern int gpsFramePrintInfo( gwmsg_client_t* client, int frameid, const gps_pageinfo2_t *ppageinfo2, unsigned long *flag );


/**********************************************************
 * id	: 2516
 * 名称	: gpsGetTrayInfoShm()
 * date	: 2002/02/04
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_GET_TRAY_INFO_SHM を定義する事
 * このI/Fは、GPSライブラリ内部でのみ使用される関数
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_GET_TRAY_INFO_SHM	(1<<14)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_trayinfo_shm_header {
#define	GPS_TRAYINFO_SHM_STAT_LOCKED		(0x80000000L)
#define	GPS_TRAYINFO_SHM_STAT_COUNT_MASK	(0x0000ffffL)
	unsigned long	stat;
} gps_trayinfo_shm_header_t;

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetTrayInfoShm( gwmsg_client_t* client, int *ret_code, int num, long *offset, int *ret_num, int notify );

/**********************************************************
 * id	: 2517
 * 名称	: gpsGetBinInfoShm()
 * date	: 2002/02/04
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_GET_BIN_INFO_SHM を定義する事
 * このI/Fは、GPSライブラリ内部でのみ使用される関数
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_GET_BIN_INFO_SHM	(1<<15)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_bininfo_shm_header {
#define	GPS_BININFO_SHM_STAT_LOCKED		(0x80000000L)
#define	GPS_BININFO_SHM_STAT_COUNT_MASK		(0x0000ffffL)
	unsigned long	stat;
} gps_bininfo_shm_header_t;

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetBinInfoShm( gwmsg_client_t* client, int *ret_code, int num, long *offset, int *ret_num, int notify );

/**********************************************************
 * id	: 2518
 * 名称	: gpsInterpNotifyExt()
 * date	: 2002/02/11
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_INTERP_NOTIFY_EXT を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_INTERP_NOTIFY_EXT	(1<<16)

typedef union gps_interp_notify_ext {
	struct	ext_testprint {
		int		interp_id;				/* interp id          */
		int		mode;					/* type of test print */
		char	res[24];
	} testprint;
	struct	ext_alert {
		int		interp_id;	/* interp id */
		int		pdl_id;		/* pdl id */
		int		mode;		/* GPS_INTERPEXT_ALERT_ON/OFF */
#define	GPS_INTERPEXT_ALERT_ON		0
#define	GPS_INTERPEXT_ALERT_OFF		1
		int		error;		/* error code */
		char		res[16];
	} alert;
	struct	ext_errorlog {
		int		interp_id;	/* interp id */
		int		pdl_id;		/* pdl id */
		int		error;		/* error code */
		char		res[20];
	} errorlog;
	struct	ext_resetkey {
		int		interp_id;	/* interp id */
		int		pdl_id;		/* pdl id */
		char		res[24];
	} resetkey;
	struct	ext_pdlerror {
		int		interp_id;	/* interp id */
		int		pdl_id;		/* pdl id */
		int		errid;		/* error id (1-9999) */
		char		res[20];
	} pdlerror;
} gps_interp_notify_ext_t;

/* status */
#define	GPS_INTERPEXT_NOSUPPORT		0
#define	GPS_INTERPEXT_SUPPORT		1

/* ext_id */
#define GPS_INTERPEXT_TESTPRINT		0
#define GPS_INTERPEXT_ALERT		1
#define GPS_INTERPEXT_ERRORLOG		2
#define GPS_INTERPEXT_RESETKEY		3
#define GPS_INTERPEXT_PDLERROR		4
/*
 * 追加される API のプロトタイプ
 */

extern int	gpsInterpNotifyExt( gwmsg_client_t* client , int ext_id, int *status, gps_interp_notify_ext_t interp_ext);

/**********************************************************
 * id	: 2519
 * 名称	: gpsColor_getProfile()
 * date	: 2002/02/11
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_COLOR_GET_PROFILE を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_COLOR_GET_PROFILE	(1<<17)

#define	GPS_MAX_CPF_PATH_LEN		96
#define	GPS_MAX_CPF_ATTR_LEN		27

#define	GPS_CPF_MEDIA_RESIDENT		0	/* RESIDENT ROM */
#define	GPS_CPF_MEDIA_ROM		1	/* OPTION ROM DIMM */
#define	GPS_CPF_MEDIA_SDCARD		2	/* OPTION SD CARD */
#define	GPS_CPF_MEDIA_HDD		3	/* OPTION HDD */

typedef struct gps_color_profile_info {
	unsigned long		key;
	unsigned char		media;
	unsigned char		attr[GPS_MAX_CPF_ATTR_LEN];
	char			path[GPS_MAX_CPF_PATH_LEN];
} gps_color_profile_info_t;

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsColor_getProfile( gwmsg_client_t* client , void **addr, long *num );

/**********************************************************
 * id	: 2520
 * 名称	: gpsUjobCancel()
 * date	: 2002/04/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_UJOB_CANCEL を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_UJOB_CANCEL		(1<<18)

/* gpsUjobCancel(): status */
#define	GPS_UJOBCANCEL_SUCCESS		0
#define	GPS_UJOBCANCEL_FAILED		1

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsUjobCancel( gwmsg_client_t* client, int ujobid, int *status);

/**********************************************************
 * id	: 2521
 * 名称	: gpsPenvDataAllocShm()
 * date	: 2002/04/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PENV_DATA_ALLOC_SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PENV_DATA_ALLOC_SHM		(1<<19)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsPenvDataAllocShm( gwmsg_client_t* client, int penv, long *offset, long size, int *result );

/**********************************************************
 * id	: 2522
 * 名称	: gpsPenvDataFreeShm()
 * date	: 2002/04/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PENV_DATA_FREE_SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PENV_DATA_FREE_SHM		(1<<20)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsPenvDataFreeShm( gwmsg_client_t* client, int penv, long offset, int *result );

/**********************************************************
 * id	: 2523
 * 名称	: gpsPenvSetDataShm()
 * date	: 2002/04/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PENV_SET_DATA_SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PENV_SET_DATA_SHM		(1<<21)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsPenvSetDataShm( gwmsg_client_t* client, int penv, long var, long offset, long val_size, int *result );

/**********************************************************
 * id	: 2524
 * 名称	: gpsPenvGetDataShm()
 * date	: 2002/04/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PENV_GET_DATA_SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PENV_GET_DATA_SHM		(1<<22)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsPenvGetDataShm( gwmsg_client_t* client, int penv, long var, long *offset, long in_size, long *out_size, int *result );

/**********************************************************
 * id	: 2525
 * 名称	: gpsGetPaperWidLen()
 * date	: 2002/04/21
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_GET_PAPER_WID_LEN を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_GET_PAPER_WID_LEN		(1<<23)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsGetPaperWidLen( gwmsg_client_t* client, u_char psize, u_short *pwidth, u_short *plength );

/**********************************************************
 * id	: 2526
 * 名称	: gpsAuthReq()
 * date	: 2003/12/04
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_AUTH_REQ を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_AUTH_REQ		(1<<24)

/* gpsAuthReq(): status */
#define	GPS_AUTH_SUCCESS	(0)	/* 成功   */
#define	GPS_AUTH_FAILED		(-1)	/* 失敗   */
#define	GPS_AUTH_BUSY		(-2)	/* ビジー */

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsAuthReq( gwmsg_client_t* client, int ujobid, int *status );

/**********************************************************
 * id	: 2527
 * 名称	: gpsColor_getPrmVal
 * date	: 2004/04/14
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_COLOR_GET_PRM_VAL を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_COLOR_GET_PRM_VAL		(1<<25)

/* PrmID */
/* GPS_COLOR_xx：SP1-108-xx(拡張トナーセーブ)設定値取得要求 */
#define GPS_COLOR_01		(1)
#define GPS_COLOR_02		(2)
#define GPS_COLOR_03		(3)
#define GPS_COLOR_04		(4)
#define GPS_COLOR_05		(5)
#define GPS_COLOR_06		(6)
#define GPS_COLOR_07		(7)
#define GPS_COLOR_08		(8)
#define GPS_COLOR_09		(9)
#define GPS_COLOR_10		(10)

/* 09A(Zeus-P1～)から追加 */
/* GPS_ECOCOLOR_xx：SP1-109-xx(エコノミーカラーモード)設定値取得要求 */
#define GPS_ECOCOLOR_01		(21)
#define GPS_ECOCOLOR_02		(22)
#define GPS_ECOCOLOR_03		(23)
#define GPS_ECOCOLOR_04		(24)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsColor_getPrmVal( gwmsg_client_t* client, int param, u_long *val, int *result );

/**********************************************************
 * id	: 2528
 * 名称	: gpsInterpReqEventNotify
 * date	: 2004/04/14
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_INTERP_REQ_EVENT_NOTIFY を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_INTERP_REQ_EVENT_NOTIFY	(1<<26)

/* req */
#define	GPS_INTERP_REQ_EVENT_FEED2	1

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsInterpReqEventNotify( gwmsg_client_t* client, int req, int *result );

/**********************************************************
 * id	: 2529
 * 名称	: gpsTrayRequest2()
 * date	: 2004/04/25
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_TRAY_REQUEST2 を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_TRAY_REQUEST2		(1<<27)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_trayrequestEx
{
	unsigned long		flag;		/* 設定するパラメータ */
#define GPS_TRAYREQFLAG_ALL			(0xFFFFFFFF)	/* すべて */
#define GPS_TRAYREQFLAG_PWIDTH		(1<<0)			/* 用紙幅 */
#define GPS_TRAYREQFLAG_PLENGTH		(1<<1)			/* 用紙長 */
#define GPS_TRAYREQFLAG_MODE		(1<<2)			/* 検索モード */
	unsigned long		pwidth;		/* フリーサイズ時の用紙幅   (0.1mm単位) */
	unsigned long		plength;	/* フリーサイズ時の用紙長さ (0.1mm単位) */
	unsigned char		mode:1;		/* 検索指定 */
#define	GPS_REQ_MODE1				(0)				/* 用紙幅、長さが一致した場合のみ */
#define	GPS_REQ_MODE2				(1)				/* 大きいサイズがある場合でもOK */
	unsigned char		res1:7;		/* リザーブ */
	unsigned char		res2[31];	/* リザーブ */

} gps_trayrequestEx_t, *gps_trayrequestEx_p;

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsTrayRequest2( gwmsg_client_t* client, int plotid, int psize, int nodir, int ptype, int tray, const gps_trayrequestEx_t *pTrayReq, int *result );

/**********************************************************
 * id	: 2530
 * 名称	: gpsFrameCreateEx()
 * date	: 2004/04/25
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FRAME_CREATE_Ex を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FRAME_CREATE_EX		(1<<28)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_pagemode2
{
	unsigned long		flag;			/* 設定するパラメータ */
#define GPS_PAGEMODEFLAG_FWIDTH			(1<<0)		/* フレーム幅 */
#define GPS_PAGEMODEFLAG_FLENGTH		(1<<1)		/* フレーム長 */
#define GPS_PAGEMODEFLAG_BAND			(1<<2)		/* バンド長 */
	unsigned long		frame_width;	/* フレームの幅   (ドット単位) */
	unsigned long		frame_length;	/* フレームの長　 (ドット単位) */
	unsigned long		band_length;	/* バンドの高さ   (ドット単位) */
	unsigned char		res[32];		/* リザーブ */
} gps_pagemode2_t, *gps_pagemode2_p;


/*
 * 追加される API のプロトタイプ
 */

extern int	gpsFrameCreateEx( gwmsg_client_t* client, int plotid, const gps_pagemode2_t *ppagemode2, const gps_pageinfo2_t *ppageinfo2, int *result );

/**********************************************************
 * id	: 2531
 * 名称	: gpsReplotInfoEx()
 * date	: 2004/04/25
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_REPLOT_INFO_EX を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_REPLOT_INFO_EX		(1<<29)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsReplotInfoEx( gwmsg_client_t* client, int plotid, gps_pagemode2_t *ppagemode2, gps_pageinfo2_t *ppageinfo2, int *result );

/**********************************************************
 * id	: 2532
 * 名称	: gpsPlotChkDirection2()
 * date	: 2004/04/25
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_CHK_DIR2 を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_PLOT_CHK_DIR2	(1<<30)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_chkdirprmEx_tag
{
	unsigned long	flag;			/* 設定するパラメータ */
#define GPS_CHKDIR2_ALL				(0xFFFFFFFF)	/* すべて */
#define GPS_CHKDIR2_PWIDTH			(1<<0)			/* 用紙幅 */
#define GPS_CHKDIR2_PLENGTH			(1<<1)			/* 用紙長 */
	unsigned long	ulwidth;		/* 用紙幅(0.1mm単位) */
	unsigned long	ullength;		/* 用紙長(0.1mm単位) */
	unsigned char	res[32];		/* リザーブ */
	
} gps_chkdirprmEx_t, *gps_chkdirprmEx_p;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsPlotChkDirection2( gwmsg_client_t* client, int plotid, const gps_chkdirprm_t *condition, const gps_chkdirprmEx_t *condEx, int *direction, int *slantdirection );

/**********************************************************
 * id	: 2533
 * 名称	: gpsFormGetImageInfo()
 * date	: 2004/06/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FORM_OVERLAY を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FORM_OVERLAY	(1<<31)

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsFormGetImageInfo(gwmsg_client_t* client, int plotid, int formno, int *result);

/**********************************************************
 * id	: 2534
 * 名称	: gpsFormOpen()
 * date	: 2004/06/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FORM_OVERLAY を定義する事
 **********************************************************/
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsFormOpen(gwmsg_client_t* client, int plotid, int formno, int *result);

/**********************************************************
 * id	: 2535
 * 名称	: gpsFormClose()
 * date	: 2004/06/01
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_FORM_OVERLAY を定義する事
 **********************************************************/
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsFormClose(gwmsg_client_t* client, int formno, int frameid, int *result);


/**********************************************************
 * id	: 1543
 * 名称	: gpsFrameFlushBand()
 * date	: 2002/09/10
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_BAND_DRAW_CONTINUE を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FRAME_FLUSH_BAND	(1<<19)

/*
 * 追加される API のプロトタイプ
 */

extern int	gpsFrameFlushBand( gwmsg_client_t* client, int frameid, int bandid, int planeid, int drawn );

/**********************************************************
 * id	: 2580
 * 名称	: GWID_GpsEv_GetPrm_Info_Res
 * date	: 2001/06/30
 **********************************************************/

/**********************************************************
 * id	: 2581
 * 名称	: GWID_GpsEv_Notify_PageExit
 * date	: 2002/01/23
 **********************************************************/
/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_event_pageexit {
	int		ujobid;
	int		kind;
	long		pageno;
	unsigned short	outbin;
	unsigned char	printcount;
	unsigned char	face;
	long		repeat_count;
	long		repeat_max;
	unsigned char	dummy_page;
	char		reserved[31];
} gps_event_pageexit_t, *gps_event_pageexit_p;

/**********************************************************
 * id	: 2582
 * 名称	: GWID_GpsEv_Xpdl_Notify
 * date	: 2002/01/25
 **********************************************************/
/*
 * API 追加に伴って追加される型定義
 */

typedef union _xpdl_notify_data {
	struct xpdl_ujobend {			/* GPS_XPDL_NOTIFY_UJOB_END */
		int			ujobid;
		char			reserved[56];
	} ujobend;
	struct xpdl_menu_entry {			/* GPS_XPDL_NOTIFY_MENU_ENTRY */
		int				pdl_id;
		char			reserved[56];
	} menu_entry;
	unsigned char			uc[60];
	unsigned short			us[30];
	unsigned long			ul[15];
} _xpdl_notify_data_t;

typedef struct gps_event_xpdl_notify {
	int						info_id;
	_xpdl_notify_data_t		data;
} gps_event_xpdl_notify_t, *gps_event_xpdl_notify_p;

/* info_id */
#define	GPS_XPDL_NOTIFY_TESTPRN_DONE	(0)
#define	GPS_XPDL_NOTIFY_UJOB_END	(1)
#define	GPS_XPDL_NOTIFY_MENU_ENTRY		(2)
#define	GPS_XPDL_NOTIFY_SETTING_CHANGE		(3)

/**********************************************************
 * id	: 2583
 * 名称	: GWID_GpsEv_Auth_Res
 * date	: 2003/12/04
 **********************************************************/
/*
 * API 追加に伴って追加される型定義
 */

/* limitrole */
#define	GPS_AUTH_LIMIT_ADMINMACHINE	(1 << 0)	/* 機器管理者機能 	*/
#define	GPS_AUTH_LIMIT_ADMINUSER	(1 << 1)	/* ユーザー管理者機能 */
#define	GPS_AUTH_LIMIT_ADMINDOCUMENT	(1 << 2)	/* 文書管理者機能 	*/
#define	GPS_AUTH_LIMIT_ADMINNETWORK	(1 << 3)	/* ネットワーク管理者機能 */
#define	GPS_AUTH_LIMIT_CERUSER		(1 << 4)	/* 認証ユーザ機能 	*/
#define	GPS_AUTH_LIMIT_SUPERVISOR      	(1 << 5)	/* スーパーバイザー機能 */
#define	GPS_AUTH_LIMIT_SERVICE		(1 << 6)	/* サービス機能 	*/

/* result */
#define	GPS_AUTH_RES_OK			(0)
#define	GPS_AUTH_RES_NG			(1)
#define	GPS_AUTH_RES_BUSY		(2)
#define	GPS_AUTH_RES_CANCEL		(3)
#define	GPS_AUTH_RES_TIMEOUT		(4)


#endif

/**********************************************************
 * id	: 2584
 * 名称	: GWID_GpsEv_Notify_Feed2
 * date	: 2004/04/14
 **********************************************************/


/**********************************************************
 * id	: 2585
 * 名称	: GWID_GpsPage_TrayRequest2_Res
 * date	: 2004/04/25
 **********************************************************/

/**********************************************************
 * id	: 2586
 * 名称	: GWID_GpsPage_FormGetImageInfo_Res
 * date	: 2004/06/01
 **********************************************************/

/**********************************************************
 * id	: 2587
 * 名称	: GWID_GpsPage_FormOpen_Res
 * date	: 2004/06/01
 **********************************************************/


/*
 * Copyright (c) 2001 Ricoh Company, Ltd.  All Rights Reserved.
 */

