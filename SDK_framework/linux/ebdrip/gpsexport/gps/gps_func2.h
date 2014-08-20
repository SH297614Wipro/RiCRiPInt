/* -*- tab-width: 4; c-basic-offset: 4; -*- *** vi:ts=4:sw=4
 ***********************************************************
 *	$Id$
 *
 *	Copyright (C) 2005 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *	FILE NAME	: gps_func2.h
 *	VERSION		: $Revision$
 *	AUTHOR		: Satoshi MIYAZAKI
 *----------------------------------------------------------
 *	HISTORY
 *	12 Jan 2005: Created.
 *	$Log$
 *
 ***********************************************************/
#ifndef _GPS_FUNC2_H_
#define	_GPS_FUNC2_H_


/**********************************************************
 * Function
 * 環境変数にセットするビットが 31 まで増えたら次の環境変
 * 数を用意する事
 * 使用変数: gps_function_support_info2
 **********************************************************/

/**********************************************************
 * id	: 2536
 * 名称	: gpsColor_getID2()
 * date	: 2005/01/12
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_COLOR_GET_ID2 を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define	GPS_COLOR_GET_ID2	(1<<0)

/* prt */
#define	NONE_PRINTMODE		0	/* 指定なし */
#define	HIGH_PRINTMODE		1	/* 高速 */
#define	NORMAL_PRINTMODE	2	/* 標準 */
#define	QUALITY_PRINTMODE	3	/* 高画質 */

/*
 * 追加される API のプロトタイプ
 */
extern int gpsColor_getID2(gwmsg_client_t *client, int hdpi, int vdpi, int bit, int draw, unsigned char prt, unsigned char paper, int *modeID);

/**********************************************************
 * id	: 2537
 * 名称	: gpsColor_getGoff2()
 * date	: 
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_COLOR_GET_ID2 を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 * GPS_COLOR_GET_ID2 を使用
 */

/*
 * 追加される API のプロトタイプ
 */
#ifdef	__INC_GPS_NEW_COLOR_DEF__
extern int	gpsColor_getGoff2( gwmsg_client_t* client, int modeID, gps_nclr_gmfile_t *gmfile );
#endif

/**********************************************************
 * id	: 2538
 * 名称	: gpsColor_get_drawparam2()
 * date	: 
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_COLOR_GET_ID2 を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 * GPS_COLOR_GET_ID2 を使用
 */

/*
 * 追加される API のプロトタイプ
 */
#ifdef	__INC_GPS_NEW_COLOR_DEF__
extern int	gpsColor_get_drawparam2( gwmsg_client_t* client, int modeID, gps_nclr_drawparam_t *param );
#endif

/**********************************************************
 * id	: 2539
 * 名称	: gpsInterpPauseAns()
 * date	: 
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define	GPS_INTERP_PAUSE_ANS	(1<<1)

/* result */
#define GPS_INTERP_PAUSE_OK		(0)
#define GPS_INTERP_PAUSE_NG		(-1)

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsInterpPauseAns( gwmsg_client_t* client, int ujobid, int result, ulong param );

/**********************************************************
 * id	: 2540
 * 名称	: gpsInterpResumeAns()
 * date	: 
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 * GPS_INTERP_PAUSE_ANS を使用
 */

/* result */
#define GPS_INTERP_RESUME_OK	(0)

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsInterpResumeAns( gwmsg_client_t* client, int ujobid, int result, ulong param );

/*********************************************************************
 * id		: 2541
 * 名称		: gpsDispSetFreeMsg()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/

/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
#define	GPS_FUNC_IPDS	(1<<2)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_freemsg
{
	unsigned char	charset;		/* charset */
#define GPS_MAX_FREEMSG			(80)
	unsigned char	str[GPS_MAX_FREEMSG];	/* 文字列 */
} gps_freemsg_t;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsDispSetFreeMsg( gwmsg_client_t* client, const gps_freemsg_t *freemsg );


/*********************************************************************
 * id		: 2542
 * 名称		: gpsInterpFinishProcData2()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsInterpFinishProcData2( gwmsg_client_t* client, int njobid );


/*********************************************************************
 * id		: 2543
 * 名称		: gpsInterpJobResumeAns(()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)

/* result */
#define GPS_SYS_SUCCESS		(0)
#define GPS_SYS_FAILURE		(-1)

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsInterpJobResumeAns( gwmsg_client_t* client, int result );

/*********************************************************************
 * id		: 2544
 * 名称		: gpsInterpJobEndAns(()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsInterpJobEndAns( gwmsg_client_t* client, int result );

/*********************************************************************
 * id		: 2545
 * 名称		: gpsInterpSessionCloseAns()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsInterpSessionCloseAns( gwmsg_client_t* client, int njobid, int result );

/*********************************************************************
 * id		: 2546
 * 名称		: gpsGetFormTrayInfo()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_formtray_info
{
	int	result;
	gps_penv_varinfo_t	varinfo;	/* Value Information */
} gps_formtray_info_t;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetFormTrayInfo( gwmsg_client_t* client, int formid, long penvid, gps_formtray_info_t *formtrayinfo );


/*********************************************************************
 * id		: 2547
 * 名称		: gpsGetFormTrayList()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_formtray_list
{
#define GPS_FORMTRAY_MAX		(20)
	int	formid[GPS_FORMTRAY_MAX];
} gps_formtray_list_t;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetFormTrayList( gwmsg_client_t* client, gps_formtray_list_t *formtraylist );

/*********************************************************************
 * id		: 2548
 * 名称		: gpsGetFormTrayList()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsPlotChangeFormTray( gwmsg_client_t* client, int plotid, int formid, int *result );

/*********************************************************************
 * id		: 2549
 * 名称		: gpsGetFormTrayInfoStr()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_formtray_info_str
{
	int	result;
#define GPS_MAX_FORMNAME		(20)
	char	name[GPS_MAX_FORMNAME+1]; /* FORM名 */
} gps_formtray_info_str_t;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetFormTrayInfoStr( gwmsg_client_t* client, int formid, gps_formtray_info_str_t *formtrayinfostr );

/*********************************************************************
 * id		: 2550
 * 名称		: gpsGetFormTrayInfoAttr()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_formtray_info_attr
{
	int	result;
	unsigned long attr;	/* attr */
} gps_formtray_info_attr_t;
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetFormTrayInfoAttr( gwmsg_client_t* client, int formid, gps_formtray_info_attr_t *formtrayinfoattr );

/*********************************************************************
 * id		: 2551
 * 名称		: gpsInterpFinishFontreset()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsInterpFinishFontreset( gwmsg_client_t* client );

/*********************************************************************
 * id		: 2552
 * 名称		: gpsUjobCancel2()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsUjobCancel2( gwmsg_client_t* client, int njobid );

/*********************************************************************
 * id		: 2553
 * 名称		: gpsGetStapleOkSize()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
/* Staple Position */
#define		GPS_SYS_STAPLE_NONE		(0) /* No Staple */
#define		GPS_SYS_STAPLE_TOP_POS		(1) /* Top */
#define		GPS_SYS_STAPLE_BOTTOM_POS	(2) /* Bottom */
#define		GPS_SYS_STAPLE_BOTH_POS		(3) /* Both */
#define		GPS_SYS_STAPLE_SADDLE_POS	(4) /* Saddle */

extern u_char	gpsGetStapleOkSize( gwmsg_client_t* client, u_char p_size, u_short p_width, u_short p_length, u_char position );

/*********************************************************************
 * id		: 2554
 * 名称		: gpsGetPunchOkSize()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
/* Punch Position Bit */
#define		GPS_SYS_BIT_PUNCHHOLE_NONE	(0x00) /* Punch Disable */
#define		GPS_SYS_BIT_PUNCHHOLE2		(0x01) /* 2-Hole Punch */
#define		GPS_SYS_BIT_PUNCHHOLE3		(0x02) /* 3-Hole Punch */
#define		GPS_SYS_BIT_PUNCHHOLE4_EU	(0x04) /* 4-Hole(EU) Punch */
#define		GPS_SYS_BIT_PUNCHHOLE4_NE	(0x08) /* 4-Hole(NE) Punch */
#define		GPS_SYS_BIT_PUNCHHOLE2_NA	(0x10) /* 4-Hole(NA) Punch */

extern u_char	gpsGetPunchOkSize( gwmsg_client_t* client, u_char p_size, u_short p_width, u_short p_length );

/*********************************************************************
 * id		: 2555
 * 名称		: gpsGetStapleMax()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
/* Punch Position */
#define		GPS_SYS_PUNCH_NONE		(0) /* None */
#define		GPS_SYS_PUNCH_2			(1) /* 2-Hole */
#define		GPS_SYS_PUNCH_3			(2) /* 3-Hole */
#define		GPS_SYS_PUNCH_4_EU		(3) /* 4-Hole (EU) */
#define		GPS_SYS_PUNCH_4_NE		(4) /* 4-Hole (NE) */
#define		GPS_SYS_PUNCH_2_NA		(5) /* 2-Hole (NA) */

#define		GPS_SYS_PUNCH_OFF		(0)
#define		GPS_SYS_PUNCH_ON		(1)

extern u_char	gpsGetStapleMax( gwmsg_client_t* client, u_char p_size, u_char p_kind, u_short p_width, u_short p_length, u_char punch, u_char position );

/*********************************************************************
 * id		: 2556
 * 名称		: gpsGetStaplePos()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
/* Staple Position Bit Deatil */
#define		GPS_SYS_BIT_STAPLE_OFF		(0)
#define		GPS_SYS_BIT_STAPLE_LEFTTOPSLANT	(1 << 0)
#define		GPS_SYS_BIT_STAPLE_RIGHTTOPSLANT (1 << 1)
#define		GPS_SYS_BIT_STAPLE_LEFT2	(1 << 2)
#define		GPS_SYS_BIT_STAPLE_TOP2		(1 << 3)
#define		GPS_SYS_BIT_STAPLE_RIGHT2	(1 << 4)
#define		GPS_SYS_BIT_STAPLE_LEFTTOP	(1 << 5)
#define		GPS_SYS_BIT_STAPLE_RIGHTTOP	(1 << 6)
#define		GPS_SYS_BIT_STAPLE_BOOKLET	(1 << 7)

extern u_long	gpsGetStaplePos( gwmsg_client_t* client );

/*********************************************************************
 * id		: 2557
 * 名称		: gpsGetPunchPos()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
/* Punch Position Bit Detail */
#define		GPS_SYS_BIT_PUNCH_OFF		(0)
#define		GPS_SYS_BIT_PUNCH_LEFT2		(1 << 0)
#define		GPS_SYS_BIT_PUNCH_TOP2		(1 << 1)
#define		GPS_SYS_BIT_PUNCH_RIGHT2	(1 << 2)
#define		GPS_SYS_BIT_PUNCH_LEFT3		(1 << 3)
#define		GPS_SYS_BIT_PUNCH_TOP3		(1 << 4)
#define		GPS_SYS_BIT_PUNCH_RIGHT3	(1 << 5)
#define		GPS_SYS_BIT_PUNCH_LEFT4		(1 << 6)
#define		GPS_SYS_BIT_PUNCH_TOP4		(1 << 7)
#define		GPS_SYS_BIT_PUNCH_RIGHT4	(1 << 8)

extern u_long	gpsGetPunchPos( gwmsg_client_t* client );

/*********************************************************************
 * id		: 2558
 * 名称		: gpsGetPaperExitOkSize()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
/* face */
#define		GPS_SYS_FACE_UP			(0)
#define		GPS_SYS_FACE_DOWN		(1)
#define		GPS_SYS_FACE_NONE		(0xff)
/* tray */
#define		GPS_SYS_TRAY_NONE		(0xff)
/* EXit Tray Position Bit */
#define		GPS_SYS_BIT_EXIT_NONE		(0x0000) /* :Output Disable */
#define		GPS_SYS_BIT_EXIT_NORMAL		(0x0001) /* :Normal Output Tray */
#define		GPS_SYS_BIT_EXIT_SHIFT		(0x0002) /* :Shift Tray */
#define		GPS_SYS_BIT_EXIT_PROOF		(0x0004) /*: Proof Tray */
#define		GPS_SYS_BIT_EXIT_MAIL_BOX	(0x0008) /* :Mail Box */
#define		GPS_SYS_BIT_EXIT_BIN1		(0x0010) /* :1Bin Tray */
#define		GPS_SYS_BIT_EXIT_SADDLE		(0x0020) /* :Saddle Tray */
#define		GPS_SYS_BIT_EXIT_SHIFT_1	GPS_SYS_BIT_EXIT_SHIFT /* :Shift Tray1 */
#define		GPS_SYS_BIT_EXIT_FU			(0x0040) /* :Fu Exit Tray */
#define		GPS_SYS_BIT_EXIT_SHIFT_2	(0x0080) /* :Shift Tray2 */

extern u_long	gpsGetPaperExitOkSize( gwmsg_client_t* client, u_char p_size, u_short p_width, u_short p_length, u_char face, u_char trayno );

/*********************************************************************
 * id		: 2559
 * 名称		: gpsGetPunchOkKind()
 * Date		: 2007/03/29
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern u_char	gpsGetPunchOkKind( gwmsg_client_t* client, u_char p_kind );

/*********************************************************************
 * id		: 2560
 * 名称		: gpsGetTrayInfo2()
 * Date		: 2007/03/29
 * ---------------------------------------
 *********************************************************************/
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetTrayInfo2(gwmsg_client_t* client, int num, gps_trayinfo_t *trayinfo, long *trayinfo_size, int notify);

/**********************************************************
 * id		: 2561
 * 名称		: gpsPlotPrepare()
 * date		: 2007/07/05
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_PREPARE を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define	GPS_PLOT_PREPARE	(1<<3)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_plotprepareparam {
	unsigned short	resolution_x;		/* X方向解像度 (25.4mmあたりのドット数) */
	unsigned short	resolution_y;		/* Y方向解像度 (25.4mmあたりのドット数) */
	unsigned char		depth;		/* 量子化数(階調) */
	unsigned char		paper_type;	/* 紙種 */
	unsigned char		color_count;	/* 色数 */
	unsigned char		reserved[25];
} gps_plotprepareparam_t;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsPlotPrepare( gwmsg_client_t* client, int ujobid, gps_plotprepareparam_t *param );

/*********************************************************************
 * id		: 2562
 * 名称		: gpsGetStapleOkKind()
 * Date		: 2007/11/02
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern u_char	gpsGetStapleOkKind( gwmsg_client_t* client, u_char p_kind , u_char position );

/*********************************************************************
 * id		: 2563
 * 名称		: gpsGetPaperExitOkKind()
 * Date		: 2007/11/02
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_IPDS を定義する事
 *********************************************************************/
/*
 * 環境変数 gps_function_support_info にセットされるビット
 */
//#define	GPS_FUNC_IPDS	(1<<2)
/*
 * 追加される API のプロトタイプ
 */
extern u_long	gpsGetPaperExitOkKind( gwmsg_client_t* client, u_char p_kind, u_char face, u_char trayno );

/**********************************************************
 * id		: 2564
 * 名称		: gpsPlotGetShmInfo()
 * date		: 2008/03/21
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_SETPARAM_SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define	GPS_PLOT_SETPARAM_SHM	(1<<4)

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsPlotGetShmInfo( gwmsg_client_t* client, long *offset, long *size, int *result );

/**********************************************************
 * id		: 2565
 * 名称		: gpsPlotSetPageParam_Shm()
 * date		: 2008/03/21
 * ---------------------------------------
 * サポートする GPS は config_XXXX.h 等に
 * GPS_SUPPORT_PLOT_SETPARAM_SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
//#define	GPS_PLOT_SETPARAM_SHM	(1<<4)

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsPlotSetPageParam_Shm( gwmsg_client_t* client, int plotid, int *result );

/**********************************************************
 * id		: 2566
 * 名称		: gpsChkDuplexOk()
 * date		: 2008/08/06
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_CHK_DUPLEX_OK を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_CHK_DUPLEX_OK					(1<<5)

/*
 * フラグの定義
 */
#define  GPS_DUPLEX_CHK_SIZE				(1 << 0)      /*用紙サイズが両面可能かチェック*/
#define  GPS_DUPLEX_CHK_KIND				(1 << 1)      /*用紙種類が両面可能かチェック*/

/*
 * リターン値の定義
 */
#define  GPS_DUPLEX_CHK_NG					0             /*両面通紙不可能*/
#define  GPS_DUPLEX_CHK_OK					1             /*両面通紙可能*/

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_chkduplexok_tag {
	unsigned long flag;					/* 設定するパラメータ */
	unsigned long pwidth;				/* フリーサイズ時の用紙幅   (0.1mm単位) */
	unsigned long plength;				/* フリーサイズ時の用紙高さ (0.1mm単位) */
	unsigned char psize;
	unsigned char pkind;
	unsigned char reserved[18];			/* リザーブ (機能追加用) */
} gps_chkduplexok_t, *gps_chkduplexok_p;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsChkDuplexOk( gwmsg_client_t* client, gps_chkduplexok_t *pchkduplexok, int *result );

/**********************************************************
 * id		: 2567
 * 名称		: gpsChkExtPortOk()
 * date		: 2008/11/28
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_CHK_PORT_OK を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_CHK_PORT_OK					(1<<6)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsChkExtPortOk( gwmsg_client_t* client, int *result );

/**********************************************************
 * id		: 2568
 * 名称		: gpsGetPrtStatus2Shm()
 * date		: 2009/01/20
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_PRTSTATUS2SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_PRTSTATUS2SHM					(1<<7)
/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetPrtStatus2Shm( gwmsg_client_t* client, long *offset, int notify, int *result );

/**********************************************************
 * id		: 2569
 * 名称		: gpsGetTrayInfoTrayBusyShm()
 * date		: 2009/12/20
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_TRAYINFOBUSYSHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_TRAY_INFO_BUSY_SHM					(1<<8)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_trayinfobusy_shm_header {
#define	GPS_TRAYINFO_SHM_STAT_LOCKED		(0x80000000L)
#define	GPS_TRAYINFO_SHM_STAT_COUNT_MASK	(0x0000ffffL)
	unsigned long	stat;
} gps_trayinfobusy_shm_header_t;

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetTrayInfoBusyShm( gwmsg_client_t* client, int *ret_code, int num, long *offset, int *ret_num, int notify);

/**********************************************************
 * id		: 2570
 * 名称		: gpsGetPdlPrintCondition()
 * date		: 2010/09/30
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_PDLPRINTCONDITION を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_PDL_PRINT_CONDITION			(1<<9)

/*
 * API 追加に伴って追加される型定義
 */
/* printcond.hにて定義 */

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetPdlPrintCondition(gwmsg_client_t* client, int ujobid, int *status, gps_pdl_printcondition_t *cond, gps_pdl_media_printcondition_t *media);

/**********************************************************
 * id		: 2571
 * 名称		: gpsGetPdfParam()
 * date		: 2010/09/30
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_PDFPARAM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_PDF_PARAM						(1<<10)

/*
 * API 追加に伴って追加される型定義
 */
/* printcond.hにて定義 */

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetPdfParam(gwmsg_client_t* client, int ujobid, int *status, gps_pdf_param_t *param);

/**********************************************************
 * id		: 2572
 * 名称		: gpsSetPdlPrintInfo()
 * date		: 2010/11/16
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_SET_PDL_PRINT_INFO を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_SET_PDL_PRINT_INFO					(1<<11)

/*
 * API 追加に伴って追加される型定義
 */
typedef struct gps_pdl_printinfo {
	/* 印刷条件変更の初期値を設定するパラメータ */
	unsigned long	flag;					/* 設定するパラメータ */
		#define	GPS_PDL_PRTINFO_NUP					(1<<0)	/* パラメータ nup が有効 */
		#define	GPS_PDL_PRTINFO_UPSIDEDOWN			(1<<1)	/* パラメータ upsidedown が有効 */

	struct {
		unsigned char	layout;					/* 集約 */
			#define	GPS_NUP_LAYOUT_OFF				(0)		/* 集約無し */
			#define	GPS_NUP_LAYOUT_2IN1				(1)		/* 2in1 */
			#define	GPS_NUP_LAYOUT_4IN1				(2)		/* 4in1 */
			#define	GPS_NUP_LAYOUT_6IN1				(3)		/* 6in1 */
			#define	GPS_NUP_LAYOUT_8IN1				(4)		/* 8in1 */
			#define	GPS_NUP_LAYOUT_9IN1				(5)		/* 9in1 */
			#define	GPS_NUP_LAYOUT_16IN1			(6)		/* 16in1 */

		unsigned char	option;					/* 集約パラメータ */
			#define	GPS_NUP_OPTION_RIGHT_THEN_DOWN	(0)		/* 2in1以外:左上→右上→左下→右下 2in1:左から右へ */
			#define	GPS_NUP_OPTION_LEFT_THEN_DOWN	(1)		/* 2in1以外:右上→左上→右下→左下 2in1:右から左へ */
			#define	GPS_NUP_OPTION_DOWN_THEN_RIGHT	(2)		/* 2in1以外:左上→左下→右上→右下 2in1:未使用 */
			#define	GPS_NUP_OPTION_DOWN_THEN_LEFT	(3)		/* 2in1以外:右上→右下→左上→左下 2in1:未使用 */

		unsigned char	line;					/* 集約仕切り線 */
			#define	GPS_NUP_LINE_OFF				(0)		/* 集約仕切り線無し */
			#define	GPS_NUP_LINE_ON					(1)		/* 集約仕切り線有り */

		unsigned char	reserve;				/* 機能追加用 */

	} nup;

	unsigned char		upsidedown;				/* 180度回転 */
			#define	GPS_UPSIDEDOWN_OFF				(0)		/* 180度回転していない */
			#define	GPS_UPSIDEDOWN_ON				(1)		/* 180度回転している */

	unsigned char		reserve1[3];			/* 機能追加用 */

	unsigned long		reserve2[4];			/* 機能追加用 */


	/* ドライバで指定された印刷条件を設定するパラメータ */
	unsigned long		driver_flag;			/* 設定するパラメータ */
			/* ( 1 << "driver_prtcondの配列番号" )で設定する印刷条件を指定する */

	unsigned char		driver_prtcond[32];		/* ドライバで指定された印刷条件 */
			#define	GPS_D_PRTCOND_OFF				(0)		/* ドライバで指定していない */
			#define	GPS_D_PRTCOND_ON				(1)		/* ドライバで指定している */

			/* driver_prtcondの配列番号 */
			#define	GPS_PDL_PRTINFO_D_PRTCOND_WEEKLY			(0)		/* 週刊誌綴じ */
			#define	GPS_PDL_PRTINFO_D_PRTCOND_OUTPUT_REVERSE	(1)		/* 逆順印刷 */
			#define	GPS_PDL_PRTINFO_D_PRTCOND_USED_PROFILE		(2)		/* プロファイル処理を施した印刷 */
			#define	GPS_PDL_PRTINFO_D_PRTCOND_TAB				(3)		/* タブ紙（インデックス紙） */
			#define	GPS_PDL_PRTINFO_D_PRTCOND_PRINTER_MARKING	(4)	/* 地紋印刷 */
			#define	GPS_PDL_PRTINFO_D_PRTCOND_TWIN_COLOR		(5)	/* ２色プリント */

} gps_pdl_printinfo_t, *gps_pdl_printinfo_p;

/*
 * 追加される API のプロトタイプ
 */
extern int gpsSetPdlPrintInfo( gwmsg_client_t* client, int plotid, gps_pdl_printinfo_t *prtinfo );

/**********************************************************
 * id		: 2573
 * 名称		: gpsGetUcpParamShm()
 * date		: 2011/01/11
 * ---------------------------------------
 * サポートする GPS は config_mach.h 等に
 * GPS_SUPPORT_UCP を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_UCP_PARAM_SHM				(1<<12)

/*
 * API 追加に伴って追加される型定義
 */
/* info.hにて定義 */

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetUcpParamShm( gwmsg_client_t* client, int ujobid, long *offset, int *result );

/**********************************************************
 * id		: 2574
 * 名称		: gpsGetUcpData()
 * date		: 2011/01/11
 * ---------------------------------------
 * サポートする GPS は config_mach.h 等に
 * GPS_SUPPORT_UCP を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_UCP_DATA					(1<<13)

/*
 * API 追加に伴って追加される型定義
 */

enum
{
	STRING_DOT_DENSITY1,		/* 文字ドットパターンの地紋濃度1のパターンデータ */
	STRING_DOT_DENSITY2,		/* 文字ドットパターンの地紋濃度2のパターンデータ */
	STRING_DOT_DENSITY3,		/* 文字ドットパターンの地紋濃度3のパターンデータ */
	STRING_DOT_DENSITY4,		/* 文字ドットパターンの地紋濃度4のパターンデータ */
	STRING_DOT_DENSITY5,		/* 文字ドットパターンの地紋濃度5のパターンデータ */
	BACKGROUND_DOT_DENSITY1,	/* 背景ドットパターンの地紋濃度1のパターンデータ */
	BACKGROUND_DOT_DENSITY2,	/* 背景ドットパターンの地紋濃度2のパターンデータ */
	BACKGROUND_DOT_DENSITY3,	/* 背景ドットパターンの地紋濃度3のパターンデータ */
	BACKGROUND_DOT_DENSITY4,	/* 背景ドットパターンの地紋濃度4のパターンデータ */
	BACKGROUND_DOT_DENSITY5,	/* 背景ドットパターンの地紋濃度5のパターンデータ */
	MASKTYPE_AMIME,				/* 背景地紋マスクパターンの網目のパターンデータ */
	MASKTYPE_HIGAKI,			/* 背景地紋マスクパターンの桧垣のパターンデータ */
	MASKTYPE_KIKKOU,			/* 背景地紋マスクパターンの亀甲のパターンデータ */
	MASKTYPE_KOUSHI1,			/* 背景地紋マスクパターンの格子1のパターンデータ */
	MASKTYPE_KOUSHI2,			/* 背景地紋マスクパターンの格子2のパターンデータ */
	MASKTYPE_MATSUKAWABISHI,	/* 背景地紋マスクパターンの松皮菱のパターンデータ */
	MASKTYPE_SEIGAIHA,			/* 背景地紋マスクパターンの青海波のパターンデータ */
	MASKTYPE_SHIPPOU,			/* 背景地紋マスクパターンの七宝のパターンデータ */
	MASKTYPE_SYOKKOU,			/* 背景地紋マスクパターンの蜀江のパターンデータ */
	MASKTYPE_UROKO,				/* 背景地紋マスクパターンの鱗のパターンデータ */
	EFFECTCOPYGUARD_BACKGROUND,	/* 不正コピーガードの背景ドットパターンデータ */
	EFFECTCOPYGUARD_STRING,		/* 不正コピーガードの文字列ドットパターンデータ */
};

#define	GPS_UCP_DATA_RES_200x200	(1)	/* 解像度200x200 */
#define	GPS_UCP_DATA_RES_300x300	(2)	/* 解像度300x300 */
#define	GPS_UCP_DATA_RES_400x400	(3)	/* 解像度400x400 */
#define	GPS_UCP_DATA_RES_600x600	(4)	/* 解像度600x600 */
#define	GPS_UCP_DATA_RES_600x1200	(5)	/* 解像度600x1200 */
#define	GPS_UCP_DATA_RES_1200x600	(6)	/* 解像度1200x600 */
#define	GPS_UCP_DATA_RES_1200x1200	(7)	/* 解像度1200x1200 */

#define	GPS_UCP_DATA_DEPTH_1BIT		(1)	/* 1bit */
#define	GPS_UCP_DATA_DEPTH_2BIT		(2)	/* 2bit */
#define	GPS_UCP_DATA_DEPTH_4BIT		(4)	/* 4bit */

typedef	struct {
	unsigned char	width;		/* 地紋データの幅 */
	unsigned char	length;		/* 地紋データの高さ */
	long			offset;		/* 共有メモリ上の地紋データポインタへのオフセット */
}gps_ucp_data_t;

typedef	struct {
	unsigned char	kind;		/* 地紋パターンの種類 */
	unsigned char	resolution;	/* 地紋パターンの解像度 */
	unsigned char	depth;		/* 地紋パターンのbitの深さ */
}gps_ucp_info_t;

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetUcpData(gwmsg_client_t *client, gps_ucp_info_t ucpinfo, gps_ucp_data_t *ucpdata, int *result)	;

/**********************************************************
 * id	: 2575
 * 名称	: gpsGetCipherSeed()
 * date	: 2011/02/28
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_CIPHER_SEED				(1<<14)

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetCipherSeed( gwmsg_client_t* client, int size, u_char *seed, long *seed_size ) ;

/**********************************************************
 * id		: 2576
 * 名称		: gpsGetPdlPrintConditionShm()
 * date		: 2010/09/30
 * ---------------------------------------
 * サポートする GPS は gps_api.h 等に
 * GPS_SUPPORT_PDLPRINTCONDITION_SHM を定義する事
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_PDL_PRINT_CONDITION_SHM			(1<<15)

/*
 * API 追加に伴って追加される型定義
 */
/* printcond.hにて定義 */

/*
 * 追加される API のプロトタイプ
 */
extern int	gpsGetPdlPrintConditionShm(gwmsg_client_t* client, int ujobid, int *status, unsigned long *offset);

/**********************************************************
 * id		: 2577
 * 名称		: gpsGetHeadRiseMode()
 * date		: 2012/01/30
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_HEAD_RISE_MODE			(1<<16)
/*
 * 追加される API のプロトタイプ
 */

typedef struct {		/* OUT */
	int	bypass;	/* 手差しトレイ */
	int	tray1;		/* トレイ1 */
	int	tray2;		/* トレイ2 */
			#define GPS_HEADRISE_OFF (0) /* ヘッド上昇モードOFF */
			#define GPS_HEADRISE_ON  (1) /* ヘッド上昇モードON */
} gps_headrise_mode_t;

extern int	gpsGetHeadRiseMode(gwmsg_client_t* client, gps_headrise_mode_t *mode, int *result);

/**********************************************************
 * id	: 2579
 * 名称	: GWID_GpsEv_TrayInfoBusy
 * date	: 
 **********************************************************/

/**********************************************************
 * id	: 2588
 * 名称	: GWID_GpsEv_Interp_Pause_Req
 * date	: 
 **********************************************************/

/**********************************************************
 * id	: 2589
 * 名称	: GWID_GpsEv_Interp_Resume_Req
 * date	: 
 **********************************************************/

/**********************************************************
 * id	: 2590
 * 名称	: GWID_GpsEv_Notify_CaptureMode
 * date	: 2007/03/29
 **********************************************************/
/* mode */
#define GPS_SYS_CAPTURE_OFF				(0)
#define GPS_SYS_CAPTURE_ON				(1)

/**********************************************************
 * id	: 2591
 * 名称	: GWID_GpsEv_Notify_EngineState
 * date	: 2007/03/29
 **********************************************************/
/* mode */
#define GPS_SYS_ENGINE_START				(0)
#define GPS_SYS_ENGINE_PRESTOP				(1)
#define GPS_SYS_ENGINE_STOP				(2)

/**********************************************************
 * id	: 2592
 * 名称	: GWID_GpsEv_Req_JobEnd
 * date	: 2007/03/29
 **********************************************************/
/* reason */
#define GPS_REQ_JOBEND_REASON_SETTING			(0)
#define GPS_REQ_JOBEND_REASON_PDLCHANGE			(1)
#define GPS_REQ_JOBEND_REASON_POWERMODE			(2)

/**********************************************************
 * id	: 2593
 * 名称	: GWID_GpsEv_Req_JobResume
 * date	: 2007/03/29
 **********************************************************/

/**********************************************************
 * id	: 2594
 * 名称	: GWID_GpsEv_Req_SessionClose
 * date	: 2007/03/29
 **********************************************************/
/* reason */
#define GPS_REQ_SESSIONCLOSE_REASON_REBOOT		(0)
#define GPS_REQ_SESSIONCLOSE_REASON_PDLCHANGE		(1)
#define GPS_REQ_SESSIONCLOSE_REASON_IPDSTESTPRINT	(2)
#define GPS_REQ_SESSIONCLOSE_REASON_IPDSFONTRESET	(3)

/**********************************************************
 * id	: 2595
 * 名称	: GWID_GpsEv_Req_Proc_Data2
 * date	: 2007/03/29
 **********************************************************/

/**********************************************************
 * id	: 2596
 * 名称	: GWID_GpsEv_Notify_PurgedPages
 * date	: 2007/03/29
 **********************************************************/

/**********************************************************
 * id	: 2597
 * 名称	: GWID_GpsEv_Notify_StapleComplete
 * date	: 2007/03/29
 **********************************************************/

/**********************************************************
 * id	: 2598
 * 名称	: GWID_GpsEv_Req_Fontreset
 * date	: 2007/03/29
 **********************************************************/

/**********************************************************
 * id	: 2599
 * 名称	: GWID_GpsEv_TrayInfo2
 * date	: 2007/03/29
 **********************************************************/

/**********************************************************
 * id	: 2600
 * 名称	: gpsGetPrtTotalCounterReq()
 * date	: 2012/08/21
 **********************************************************/
/*
 * 環境変数 gps_function_support_info2 にセットされるビット
 */
#define  GPS_GET_PRT_TOTAL_COUNTER		(1<<17)

/*
 * 追加される API のプロトタイプ
 */
extern int gpsGetPrtTotalCounterReq(gwmsg_client_t* client);

/**********************************************************
 * id	: 2601
 * 名称	: GWID_GpsEv_GetPrtTotalCounter_Res
 * date	: 2012/08/21
 **********************************************************/

#endif	/* _GPS_FUNC2_H_ */
/*
 * Copyright (c) 2005 Ricoh Company, Ltd.  All Rights Reserved.
 */

