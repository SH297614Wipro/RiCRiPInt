/*
 * GPS COLOR LIBRARY TYPE DEFINITION.
 * Copyright (c) Ricoh Company, Ltd.
 * ALL Rights Reserved.
 *
 * $Id: gps_color_mtype.h,v 1.4 2000/04/05 01:42:05 MrX Exp MrX $
 * $Date: 2000/04/05 01:42:05 $
 * $Author: MrX $
 *
 * ガンマ・ディザデータの型定義
 *
 */

#ifndef	__INC_GPS_COLOR_MTYPE__	/* { */
#define	__INC_GPS_COLOR_MTYPE__

/*
 * 色，ビット数の指定
 */
/* 転写色数の定義 */
#define	GPS_CLR_PLANE		4		/* 4 plane for Jupiter */

/* 色番号の定義 */
#define	GPS_CLR_K			0
#define	GPS_CLR_C			1
#define	GPS_CLR_M			2
#define	GPS_CLR_Y			3

/* １描画ピクセルの型定義 */
typedef	unsigned char	gps_clr_pixel_t;		/* 8bit for Jupiter */
#define	GPS_CLR_PIXEL_LVL	8					/* 8bit for Jupiter */
#define	GPS_CLR_PIXEL_OUT	(1<<GPS_CLR_PIXEL_LVL)		/* 8bit for Jupiter */

/* 描画モード数の定義 */
#define	GPS_CLR_DMODE		6		/*    3(1200x1200,1200x600,600x600)
										* 1(1bit)
								 		* 2(photo/text) = 6 for jupiter */

/* ランクヘッド最大値の定義 */
#define	GPS_MAX_HEADRANK	9


/* リアレンジマトリックスデータIDの型定義 */
typedef	unsigned short	gps_color_rid_t;	/* same type in gps_page_mode_t */

/* ガンマ調整の定数の定義 */
#define	GPS_CLR_GAMUMODE	2			/* mode = highlight/midle */
#define	GPS_CLR_GAMSPNTS	15			/* point = 0-14 */



#endif	/* } __INC_GPS_COLOR_MTYPE__	 */
