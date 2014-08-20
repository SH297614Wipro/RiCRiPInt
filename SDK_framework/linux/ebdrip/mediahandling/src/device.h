/**
 * @file device.h
 * @brief DIの公開ファイル
 *
 * @author kumagai
 * @date 2005-09-13
 * $Revision: 1.4 $
 *
 * Copyright (c) 2001-2007 by RICOH CO., LTD.
 */

/** \mainpage DI Library 内部設計仕様書
 *
 * 本仕様書は、DI（Device Infomation) Library の内部仕様を記述したものです。
 *
 * DIは、プリンターアプリ（以下アプリ）が動作するために必要な情報の提供を
 * 行うライブラリです。
 * アプリでは、プリンターのＯＳや機種に依存した情報が必要ですが、そのよう
 * な変動パラメータをDIから取得することにより、パース部、レンダリング部と
 * いった処理部分の汎用性を高めます。
 *
 * \date 2005/09
 * \author M.Kumagai
 */

#ifndef	__DEVICE_H__
#define	__DEVICE_H__

#define DI_MAX_TRAY_NUM	8

/*
 * di_select_idevice関数のI/O定義
 */
#define DI_HOST_IO         0
#define DI_MEMORY_IO       1
#define DI_FILE_IO         2

/*
 * システムから来るイベント値
 */
#define	DI_REQ_PROCESS	0x01	/* 通常処理 */
#define	DI_REQ_CANCEL	0x02	/* パネルからのジョブリセット */
#define	DI_REQ_EXIT		0x04	/* 終了要求 */
#define	DI_REQ_PAUSE    0x08	/* 割り込みによる一時停止要求 */
#define	DI_REQ_RESUME   0x10	/* 処理再開要求 */
#define	DI_REQ_PROGENTRY	0x20	/* プログラム登録要求（MSIS系PDL専用） */
#define	DI_REQ_PROGDELETE	0x40	/* プログラム削除要求（MSIS系PDL専用） */
#define	DI_REQ_TERM		0x80	/* プリンタアプリ終了要求（MSIS系PDL専用） */
#define	DI_REQ_INTRAY		0x100	/* 給紙トレイ情報確認要求（MSIS系PDL専用 */

/*
 * システムへの通知メッセージ
 */
#define DI_NOTIFYMSG_JOBEND		0x01	/* ジョブの終了 */
#define DI_NOTIFYMSG_STATE		0x02	/* 状態の通知 */
#define DI_NOTIFYMSG_STRING		0x03	/* 文字列による状態の通知 */
#define DI_NOTIFYMSG_ERRFORCE		0x11	/* エラーの強制通知 */
#define DI_NOTIFYMSG_START		0x12	/* 明示的な起動通知 */
#define DI_NOTIFYMSG_FINISH_FONTCOUNT	0x13	/* フォントカウントの終了通知 */
#define DI_NOTIFYMSG_PAUSE		0x14	/* 一時停止要求に対する応答（完了、もしくは一時停止できない）通知 */
#define DI_NOTIFYMSG_RESUME		0x15	/* 処理再開通知 */
#define DI_NOTIFYMSG_ERR		0x16    /* エラーの通知 */
#define DI_NOTIFYMSG_WARNNING		0x17	/* ワーニングレベルのエラーの通知 */
#define DI_NOTIFYMSG_CLEAR_WARNNING	0x18	/* ワーニングレベルのエラーのクリアの通知 */
#define DI_NOTIFYMSG_ALERT		0x19	/* オペレータコールレベルのエラーの通知 */
#define DI_NOTIFYMSG_CLEAR_ALERT	0x1A	/* オペレータコールレベルのエラーのクリアの通知 */

/*
 *一次停止要求に対する応答の引数
 */
#define DI_INTERP_PAUSE_OK	0	/* 一時停止した時 */
#define DI_INTERP_PAUSE_NG	-1	/* 一時停止できない */

/*
 * インタプリタの状態
 */
#define DI_INTERP_STATE_IDLE       0   /* idle */
#define DI_INTERP_STATE_PROCESSING 1   /* processing */
#define DI_INTERP_STATE_WAITING    2   /* waiting data */
#define DI_INTERP_STATE_FLUSHING   3   /* flushing data */

/*
 * コールバック関数の指定
 */
/* di_singetc 読み込み失敗の時にコールする関数 */
#define DI_CALLBACK_READERR_SINGETC		0x01
/* di_singet 読み込み失敗の時にコールする関数 */
#define DI_CALLBACK_READERR_SINGET		0x02
/* di_singetc サイズ指定不正時にコールする関数 */
#define DI_CALLBACK_SIZEERR_SINGET		0x03
/* システムからデータ処理の開始要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_PROCDATA		0x11
/* システムからインタプリタ終了要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_EXIT			0x12
/* システムからデータ処理の中止要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_CANCEL			0x13
/* システムからオンライン要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_ONLINE			0x14
/* システムからオフライン要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_OFFLINE			0x15
/* システムからテストプリント要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_TESTPRINT		0x16
/* システムから給紙トレイの変更通知がきた時にコールする関数 */
#define DI_CALLBACK_REQ_TRAYINFO		0x17
/* システムから排紙ビンの変更通知がきた時にコールする関数 */
#define DI_CALLBACK_REQ_BININFO			0x18
/* システムから強制排紙要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_EXITPAPER		0x19
/* システムからフォント数のカウント要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_FONTCOUNT		0x1A
/* システムからプリンタステータス情報の変更通知がきた時にコールする関数 */
#define DI_CALLBACK_REQ_PRTSTATUS		0x1B
/* システムからガンマ再計算がきた時にコールする関数 */
#define DI_CALLBACK_REQ_GAM				0x1C
/* システムからデータ処理の一時停止要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_PAUSE				0x1D
/* システムからデータ処理の処理再開要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_RESUME				0x1E
/* システムからメニューアイテムの登録要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_MENU_INIT			0x20
/* システムからメニュー画面の終了要求がきた時にコールする関数 */
#define DI_CALLBACK_REQ_MENU_EXIT			0x21
#define DI_CALLBACK_REQ_TRAY			0x26

/*
 * 解像度
 */
#define DI_RESO_200x200x1	(1 << 0)
#define DI_RESO_300x300x1	(1 << 1)
#define DI_RESO_400x400x1	(1 << 2)
#define DI_RESO_600x600x1	(1 << 3)
#define DI_RESO_1200x1200x1	(1 << 4)
#define DI_RESO_1200x600x1	(1 << 5)
#define DI_RESO_600x600x2	(1 << 6)
#define DI_RESO_600x600x4	(1 << 7)
#define DI_RESO_1200x1200x2	(1 << 8)
#define DI_RESO_600x1200x1	(1 << 9)

/*
 * di_getinfo( )のエラーの種類
 */
#define DI_GI_ERR_CONDITION  	(1 << 0)
#define DI_GI_ERR_DITHER     	(1 << 1)
#define DI_GI_ERR_GAMMA      	(1 << 2)
#define DI_GI_ERR_FONT       	(1 << 3)
#define DI_GI_ERR_PROF       	(1 << 4)
#define DI_GI_ERR_RESO       	(1 << 5)
#define DI_GI_ERR_NDIT       	(1 << 6)
#define DI_GI_ERR_NPLANE     	(1 << 7)
#define DI_GI_ERR_BGUCR      	(1 << 8)
#define DI_GI_ERR_TSAVE      	(1 << 9)
#define DI_GI_ERR_TSAVE_R    	(1 << 10)
#define DI_GI_ERR_TLIMIT     	(1 << 11)
#define DI_GI_ERR_TLIMIT_R   	(1 << 12)
#define DI_GI_ERR_SHDM       	(1 << 13)
#define DI_GI_ERR_SYSH       	(1 << 14)
#define DI_GI_ERR_EXTENDTSAVE   (1 << 15)
#define DI_GI_ERR_DROP      	(1 << 16)
#define DI_GI_ERR_DUPGAM    	(1 << 17)
#define DI_GI_ERR_SUPPORT_DROP  (1 << 18)
#define DI_GI_ERR_CMYMEDIA	(1 << 19)
#define DI_GI_ERR_GCR		(1 << 20)
#define DI_GI_ERR_MINBH		(1 << 21)
#define DI_GI_ERR_MAXBH		(1 << 22)
#define DI_GI_ERR_BANDSIZE	(1 << 23)

/*
 * operation value of di_setrenderinfo
 */
#define DI_SRI_DITHER	0
#define DI_SRI_GAMMA	1
#define DI_SRI_BGUCR	2
#define DI_SRI_TLIMIT	3

/*
 * di_get_appinfo( )の返り値
 */
#define DI_PINI_OK                  0
#define DI_PINI_KEY_NOT_FOUND      -1
#define DI_PINI_CATEGORY_NOT_FOUND -2
#define DI_PINI_TOOLONG_VALUE      -3
#define DI_PINI_ILLEGAL_ARG        -4
#define DI_PINI_FAILURE            -5
#define DI_PINI_ERROR              -6

/*
 * di_get_appinfo( )の値を格納する配列の最大長
 */
#define DI_MAX_VALUE_LEN 32

/*
 * di_get/set_envalue( )の返り値
 */
#define DI_ENV_ASSIGN          1
#define DI_ENV_DEFAULT         0
#define DI_ENV_ERROR          -1
#define DI_ENV_NOEXIST_TABLE  -2
#define DI_ENV_NOEXIST_VALUE  -3
#define DI_ENV_READONLY       -4
#define DI_ENV_ILLEGAL_VALUE  -5
#define DI_ENV_TABLE_BUSY     -6
/*
 * di_get_envdata( )の返り値
 * すぐ上もdi_get_envdata( )で使用している
 */
#define DI_ENV_TOOLONG_VALUE  -4

/*
 * di_soutputで指定する書き込み方法
 */
#define DI_HOST_BLOCK		0x00
#define DI_HOST_NONBLOCK	0x01

/*
 * ディスクの種類
 */
#define DI_HDD_DOWNLOAD 0
#define DI_HDD_SPOOL    1
#define DI_RAM_DOWNLOAD 2
#define DI_RAM_SPOOL    3
#define DI_HDD_TMP      4
#define DI_SD_DOWNLOAD  5
#define DI_HDD_IPDS_DOWNLOAD	6
#define DI_SD_IPDS_DOWNLOAD	7
#define DI_SD_PICTBRIDGE	8

/*
 * ストレージの種類
 */
#define DI_STORAGE_NVRAM 0 /* NVRAM */

/*
 * 機能情報
 */
#define DI_SYS_FUNC_DUPLEX             (1 << 0)        /* duplex */
#define DI_SYS_FUNC_STAPLE             (1 << 1)        /* staple */
#define DI_SYS_FUNC_PUNCH              (1 << 2)        /* punch */
#define DI_SYS_FUNC_SORT               (1 << 3)        /* sorting */
#define DI_SYS_FUNC_HDD_FS             (1 << 4)        /* HDD for FileSystem */
#define DI_SYS_FUNC_SHIFT              (1 << 5)        /* shift */
#define DI_SYS_FUNC_FINISHER           (1 << 6)        /* Finisher */
#define DI_SYS_FUNC_MAILBOX            (1 << 7)        /* Mail Box */
#define DI_SYS_FUNC_COLOR              (1 << 8)        /* Color (CMYK) */
#define DI_SYS_FUNC_HDD                (1 << 9)        /* HDD */
#define DI_SYS_FUNC_PROOFPRINT         (1 << 10)       /* proof print */
#define DI_SYS_FUNC_SEQUREPRINT        (1 << 11)       /* sequre print */
#define DI_SYS_FUNC_LOCALSTORAGE       (1 << 12)       /* local storage */
#define DI_SYS_FUNC_NETWORK            (1 << 13)       /* network */
#define DI_SYS_FUNC_REMOTEPRINT        (1 << 14)       /* remote print */
#define DI_SYS_FUNC_IEEE1394           (1 << 15)       /* IEEE1394 */
#define DI_SYS_FUNC_MF_MODEL           (1 << 16)       /* MF (not P) Model */
#define DI_SYS_FUNC_LARGEPRINTOUT      (1 << 17)       /* large printout */
#define DI_SYS_FUNC_IEEE802_11b        (1 << 18)       /* IEEE802.11b */
#define DI_SYS_FUNC_USB                (1 << 19)       /* USB */
#define DI_SYS_FUNC_CENTRO             (1 << 20)       /* CENTRO */
#define DI_SYS_FUNC_BLUETOOTH          (1 << 21)       /* Bluetooth */
#define DI_SYS_FUNC_GWMAC              (1 << 22)       /* GWMAC */
#define DI_SYS_FUNC_GIGAETHER          (1 << 23)       /* Gigabit Ethernet */
#define DI_SYS_FUNC_FOLD               (1 << 24)       /* Z折り */

/*
 * パンチ情報
 */
#define DI_SYS_PUNCH_HOLE_JP2          (1 << 0)        /* 2 JP */
#define DI_SYS_PUNCH_HOLE_US2          (1 << 1)        /* 2 US */ 
#define DI_SYS_PUNCH_HOLE_US3          (1 << 2)        /* 3 US */ 
#define DI_SYS_PUNCH_HOLE_EU4          (1 << 3)        /* 4 EU */
#define DI_SYS_PUNCH_HOLE_NEU4         (1 << 4)        /* 4 Northern EU */

/*
 * チャネル番号
 */
#define DI_CHANNEL_LPD                 1               /* LPD */
#define DI_CHANNEL_FTP                 2               /* FTP */
#define DI_CHANNEL_RSH                 3               /* RSH */
#define DI_CHANNEL_DIPRINT             4               /* Direct Print */
#define DI_CHANNEL_IPP                 7               /* IPP */
#define DI_CHANNEL_FAX                 11              /* FAX */
#define DI_CHANNEL_CENTRO              12              /* centronics */
#define DI_CHANNEL_PSERVER             13              /* NetWare(PSERVER) */
#define DI_CHANNEL_NPRINTER            14              /* NetWare(NPRINTER) */
#define DI_CHANNEL_SMB                 15              /* SMB */
#define DI_CHANNEL_PAP                 16              /* AppleTalk PAP */
#define DI_CHANNEL_USB                 21              /* USB */
#define DI_CHANNEL_BT                  22              /* BLUETOOTH */

/*
 * PDL ID
 */
#define DI_PDL_AUTO            -1
#define DI_PDL_RPCS            0
#define DI_PDL_RPDL            1
#define DI_PDL_R98             2
#define DI_PDL_R16             3
#define DI_PDL_R55             4
#define DI_PDL_RPGL            5
#define DI_PDL_HPGL2           6
#define DI_PDL_RTIFF           7
#define DI_PDL_POSTSCRIPT      8
#define DI_PDL_PCL             9
#define DI_PDL_PCLXL           10
#define DI_PDL_TIFF            11
#define DI_PDL_PDF             12
#define DI_PDL_BMLINKS         13
#define	DI_PDL_PICTBRIDGE      14
#define	DI_PDL_XPS             16
#define	DI_PDL_MP_TIFF         30
#define	DI_PDL_MP_JPEG         31

#define DI_NOTIFY_CHANGE_OFF    0       /* not notify if changed */
#define DI_NOTIFY_CHANGE_ON     1       /* notify if changed */

#define DI_DISKSTAT_UNKNOWN		0		/* 不定（check中） */
#define DI_DISKSTAT_NONE		1		/* ディスク無し */
#define DI_DISKSTAT_READY		2		/* Ready */

#define DI_DEVICETYPE_FILE 0x01
#define DI_STRING_LEN_MAX  112
#define   DI_SET_MODIFY           1
#define   DI_RESET_MODIFY         2
#define   DI_SET_DISP             3
#define   DI_HALF_DISP            4
#define   DI_RESET_DISP           5
#define   DI_SET_ACT              6
#define   DI_RESET_ACT            7

#define DI_LANG_JAPANESE		0		/* 日本語 */
#define DI_LANG_ENGLISH			1		/* 英語 */
#define DI_LANG_FRENCH			2		/* フランス語 */
#define DI_LANG_GERMAN			3		/* ドイツ語 */
#define DI_LANG_ITALIAN			4		/* イタリア語 */
#define DI_LANG_SPANISH			5		/* スペイン語 */
#define DI_LANG_DUTCH			6		/* オランダ語 */
#define DI_LANG_SWEDISH			7		/* スウェーデン語 */
#define DI_LANG_NORWEGIAN		8		/* ノルウェー語 */
#define DI_LANG_DANISH			9		/* デンマーク語 */
#define DI_LANG_FINNISH			10		/* フィンランド語 */
#define DI_LANG_PORTUGUESE		11		/* ポルトガル語 */
#define DI_LANG_CZECH			12		/* チェコ語 */
#define DI_LANG_POLISH			13		/* ポーランド語 */
#define DI_LANG_HUNGARIAN		14		/* ハンガリー語 */
#define DI_LANG_CHINESE			15		/* 中国語 */
#define DI_LANG_TAIWANESE		16		/* 台湾語 */
#define DI_LANG_RUSSIAN			17		/* ロシア語 */
#define DI_LANG_HEBREW			18		/* ヘブライ語 */
#define DI_LANG_ARABIC			19		/* アラビア語 */


#define DI_MENU_TYPE_TRAY     5    /* トレイ設定メニュー */
#define DI_MENU_TYPE_EMUSET   8    /* エミュレーション印刷条件メニュー */
#define DI_MENU_TYPE_PRN_NUM  9    /* エミュレーション印刷部数メニュー */
#define DI_MENU_TYPE_PCL     15    /* PCL印刷条件ニュー */

#define   DI_ITEM_TYPE_START        0  /* ルート構造体アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_MENU         1  /* メニュー型画面用アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_EXECUTING    3  /* 実行型画面用アイテムタイプ識別子  */
#define   DI_ITEM_TYPE_SELECT       2  /* 選択肢型画面用アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_INTEGER      5  /* 整数値型画面用アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_FLOAT        6  /* 小数値型画面用アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_PRN_NUM      8  /* 印刷部数画面用アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_PTIME       14  /* 用紙変倍率タイプ識別子 */
#define   DI_ITEM_TYPE_ANY         15  /* 任意アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_FLOAT_EXT   16  /* 小数値桁拡張特化型アイテムタイプ識別子 */
#define   DI_ITEM_TYPE_PTIME_FLT   20  /* 小数型用紙変倍率タイプ識別子 */


#define DI_INTERP_TESTPRINT_SUMMARY			-1	/* インタプリタサマリー(印刷条件)印刷 */
#define DI_INTERP_TESTPRINT_FONTSET				1	/* フォントセット印刷 */
#define DI_INTERP_TESTPRINT_FONTALL				2	/* 全文字印刷 */
#define DI_INTERP_TESTPRINT_PROGRAM				3	/* プログラム一覧印刷 */
#define DI_INTERP_TESTPRINT_FORMLIST			4	/* 登録フォーム一覧印刷 */
#define DI_INTERP_TESTPRINT_PSINFO				5	/* PostScript info list */
#define DI_INTERP_TESTPRINT_COLORSAMPLE			6	/* カラーサンプル印刷 */
#define DI_INTERP_TESTPRINT_COLORMATCHING		7	/* 色ずれ補正 */
#define DI_INTERP_TESTPRINT_COLORTEST			8	/* カラーテスト */
#define DI_INTERP_TESTPRINT_GAMMA_USER1			9	/* 階調補正１ */
#define DI_INTERP_TESTPRINT_GAMMA_USER2			10	/* 階調補正２ */
#define DI_INTERP_TESTPRINT_COLORSHIFT_SET		11	/* 定着速度補正設定用 */
#define DI_INTERP_TESTPRINT_COLORSHIFT_CHECK	12	/* 定着速度補正確認用 */
#define DI_INTERP_TESTPRINT_PDFINFO				13	/* PDF info list */
#define DI_INTERP_TESTPRINT_MICR				20	/* MICR testsheet */
#define DI_INTERP_TESTPRINT_SUMMARY_TEXT		21
#define DI_INTERP_TESTPRINT_FONTSET_DOWNLOAD_PCL	22
#define DI_INTERP_TESTPRINT_FONTSET_DOWNLOAD_PS 	23
#define DI_INTERP_TESTPRINT_FONTSET_DOWNLOAD_PDF	24
#define DI_INTERP_LEN_TESTPRINT_PATH				80

#define	DI_BIT_SW_001	0
#define	DI_BIT_SW_002	1
#define	DI_BIT_SW_003	2
#define	DI_BIT_SW_004	3
#define	DI_BIT_SW_005	4
#define	DI_BIT_SW_006	5
#define	DI_BIT_SW_007	6
#define	DI_BIT_SW_008	7
#define	DI_BIT_SW_009	8
#define	DI_BIT_SW_010	9
#define	DI_BIT_SW_011	10
#define	DI_BIT_SW_012	11
#define	DI_BIT_SW_013	12
#define	DI_BIT_SW_014	13
#define	DI_BIT_SW_015	14
#define	DI_BIT_SW_016	15
#define DI_BIT_SW_NUM	16

/*
 *    request reqson
 */
#define       DI_REQ_PROC_REASON_ENTERLANGUAGE        0       /* PJL ENTER LANGUAGE=XXX */
#define       DI_REQ_PROC_REASON_FILETYPE             1       /* filetype=XXX */
#define       DI_REQ_PROC_REASON_AUTOSENSE            2       /* auto sense */
#define       DI_REQ_PROC_REASON_NOSENSE              3       /* no sense */
#define       DI_REQ_PROC_REASON_EMCHGCMD             4       /* EM CHANGE COMMAND */
#define       DI_REQ_PROC_REASON_PANEL                5       /* panel */

/*
 *	parmanent font
 */
#define DI_DOWNLOADINFO_CREATE		0
#define DI_DOWNLOADINFO_OPEN		1
#define DI_DOWNLOADINFO_DIR		2
#define DI_DOWNLOADINFO_FILE		3

#define DI_PATHMAX	336

#define PERMFONTFILEEXTENSION	".fnt"

/*
*	return of di_get_printcondition()
*/
#define DI_PCND_OK_ALL			3
#define DI_PCND_OK_MEDIA		2
#define DI_PCND_OK_COND			1
#define DI_PCND_OK_NONE			0
#define DI_PCND_NG_ERROR		-1
#define DI_PCND_NG_NOTSUPPORT	-2
/*
*	return of di_get_printconditionShm()
*/
#define DI_PCND_SHM_OK			0
#define DI_PCND_SHM_NG			-1
/*
*	status of di_get_printconditionShm()
*/
#define DI_PCND_SHM_STATUS_COND		0
#define DI_PCND_SHM_STATUS_NONE		-1

/*
*	memory required for zlib
*/
#define DI_ZLIB_MEMORY	(64 * 1024)		/* 64KB */

/*
 *  MICR model type
*/
enum {
	DI_SYS_MODEL_STANDARD,			/* RICOH standard model */
	DI_SYS_MODEL_MICR_SECURE_PCL,	/* Secure PCL MICR model */
	DI_SYS_MODEL_MICR_IPDS,			/* IPDS MICR model */
};

/* memory 確保関数の型 */
typedef char* (*DI_CALLBACK_MEMALLOC)( unsigned long );
/* memory 解放関数の型 */
typedef void (*DI_CALLBACK_MEMFREE)( char * );
/* コールバック関数の型 */
typedef void (*DI_CALLBACK_FUNC)( void );

/* ディザ情報構造体 */
typedef struct di_ditinfo {
	unsigned char	*dit_ptr;		/* ディザの先頭アドレス */
	unsigned char	x_size;			/* 幅 */
	unsigned char	y_size;			/* 高さ */
	unsigned char	dit_order;		/* ディザのオーダ値使用ON/OFF */
									/* [0: 使用しない, 0x40: 使用する] */
	unsigned short	rearrange;		/* リアレンジマトリックスパターン ID */
									/* gps_pagemode_t 参照 */
	unsigned char	e_flag_max;		/* engine flag for color level: 255 */
	unsigned char	e_flag_mid;		/* engine flag for color level: 1 to 254 */
} dit_info_t, di_ditinfo_t;

/* 解像度構造体 */
typedef struct di_resoinfo {
	unsigned int	x;	/* 主走査方向解像度 */
	unsigned int	y;	/* 副走査方向解像度 */
} reso_info_t, di_resoinfo_t;

/* 解像度構造体(ビットとの組合せ) */
typedef struct di_resolutioninfo {
	unsigned int	x;		/* 主走査方向解像度 */
	unsigned int	y;		/* 副走査方向解像度 */
	unsigned char	bit;		/* ビット数 */
	unsigned char   paper;		/* 紙種 */
	unsigned char	dit_mode;	/* ディザモード */
	unsigned char   prt_mode;	/* プリンタドライバでのモード */
} resolution_info_t, di_resolutioninfo_t;

/* 総量規制値情報構造体 */
typedef struct di_tlimitinfo {
	di_resolutioninfo_t	reso;	/* 解像度。all 0なら解像度の指定なし */
	int					text;	/* 文字オブジェクトの総量規制値 */
	int					line;	/* 線画オブジェクトの総量規制値 */
	int					phot;	/* 写真オブジェクトの総量規制値 */
	int					fill;	/* 塗りつぶしオブジェクトの総量規制値 */
} tlimit_info_t, di_tlimitinfo_t;

/* トレイ情報 */
typedef struct di_onetrayinfo {
	unsigned short	id;				/* tray ID */
	unsigned char	p_size;			/* 用紙サイズ(di_paperdef.h参照) */
#define DI_PAPER_AUTO          (0x00)          /* 紙種指定なし */
#define DI_PAPER_NORMAL        (0x01)          /* 普通紙 */
#define DI_PAPER_RECYCLE       (0x02)          /* 再生紙 */
#define DI_PAPER_SPECIAL       (0x03)          /* 特殊紙 */
#define DI_PAPER_TRACING       (0x04)          /* トレーシング紙 */
#define DI_PAPER_OHP           (0x05)          /* OHP */
#define DI_PAPER_LABEL         (0x06)          /* ラベル紙 */
#define DI_PAPER_BOND          (0x07)          /* ボンド紙 */
#define DI_PAPER_CARDSTOCK     (0x08)          /* カードストック */
#define DI_PAPER_CARDBOARD     (0x09)          /* 厚紙 */
#define DI_PAPER_PREPRINT      (0x0A)          /* 印刷済み紙 */
#define DI_PAPER_LETTER_HEAD   (0x0B)          /* レターヘッド紙 */
#define DI_PAPER_LTHEAD        (0x0B)          /* 廃止予定 */
#define DI_PAPER_PUNCH         (0x0C)          /* パンチ済み紙 */
#define DI_PAPER_PREPUNCH      (0x0C)          /* 廃止予定 */
#define DI_PAPER_TAB           (0x0D)          /* タブ紙 */
#define DI_PAPER_COLOR         (0x0E)          /* 色紙 */
#define DI_PAPER_NORMAL2ND     (0x0F)          /* 普通紙(裏面) */
#define DI_PAPER_CARDBOARD2ND  (0x10)          /* 厚紙(裏面) */
#define DI_PAPER_THIN          (0x11)          /* 薄紙 */
#define DI_PAPER_GLOSSY        (0x12)          /* 光沢紙 */
#define DI_PAPER_USED          (0x13)          /* 裏紙（使用済み） */
#define DI_PAPER_POSTCARD      (0x14)          /* ハガキ */
#define DI_PAPER_POSTCARD2ND   (0x15)          /* ハガキ(裏面) */
#define DI_PAPER_CARDBOARD2    (0x16)          /* 厚紙２ */
#define DI_PAPER_FILM          (0x17)          /* フィルム紙（図面コピー用） */
#define DI_PAPER_INKPOST       (0x18)          /* インクジェット用はがき */
#define DI_PAPER_HG_NORMAL     (0x19)          /* HG普通紙 */
#define DI_PAPER_ENVELOPE      (0x1A)          /* 封筒 */
#define DI_PAPER_CARDBOARD3    (0x1B)          /* 厚紙３ */
#define DI_PAPER_SPECIAL2      (0x1C)          /* 特殊紙２ */
#define DI_PAPER_SPECIAL3      (0x1D)          /* 特殊紙３ */
#define DI_PAPER_MIDDLETHICK   (0x1E)          /* 中厚口 */
#define DI_PAPER_COATED        (0x1F)          /* コート紙 */
#define DI_PAPER_CARDBOARD2REV (0x20)          /* 厚紙２(裏面) */
#define DI_PAPER_CARDBOARD3REV (0x21)          /* 厚紙３(裏面) */
#define DI_PAPER_NORMAL2       (0x22)          /* 普通紙２ */
#define DI_PAPER_THICKGLOSSY   (0x23)          /* 厚手光沢紙 */
#define DI_PAPER_SPECIAL4      (0x24)          /* 特殊紙４ */
#define DI_PAPER_SPECIAL5      (0x25)          /* 特殊紙５ */
#define DI_PAPER_SPECIAL6      (0x26)          /* 特殊紙６ */
#define DI_PAPER_USER_DEF1     (0x30)          /* ユーザ指定１ */
#define DI_PAPER_USER_DEF2     (0x31)          /* ユーザ指定２ */
#define DI_PAPER_USER_DEF3     (0x32)          /* ユーザ指定３ */
#define DI_PAPER_USER_DEF4     (0x33)          /* ユーザ指定４ */
#define DI_PAPER_USER_DEF5     (0x34)          /* ユーザ指定５ */
#define DI_PAPER_USER_DEF6     (0x35)          /* ユーザ指定６ */
#define DI_PAPER_USER_DEF7     (0x36)          /* ユーザ指定７ */
#define DI_PAPER_USER_DEF8     (0x37)          /* ユーザ指定８ */
#define DI_PAPER_USER_DEF0     (0x38)          /* ユーザ指定０（未登録カスタム紙種） */
#define DI_PAPER_COLOR1        (0x40)          /* 色紙１           */
#define DI_PAPER_COLOR2        (0x41)          /* 色紙２           */
#define DI_PAPER_COLOR_WHITE   (0x50)          /* 使用不可(標準) */
#define DI_PAPER_COLOR_YELLOW  (0x51)          /* 黄 */
#define DI_PAPER_COLOR_GREEN   (0x52)          /* 緑 */
#define DI_PAPER_COLOR_BLUE    (0x53)          /* 青 */
#define DI_PAPER_COLOR_PURPLE  (0x54)          /* 紫 */
#define DI_PAPER_COLOR_IVORY   (0x55)          /* アイボリー */
#define DI_PAPER_COLOR_ORANGE  (0x56)          /* 橙 */
#define DI_PAPER_COLOR_PINK    (0x57)          /* 桃 */
#define DI_PAPER_COLOR_RED     (0x58)          /* 赤 */
#define DI_PAPER_COLOR_GRAY    (0x59)          /* 灰 */
#define DI_PAPER_GLOSSY_COATED		(0x60)	/* glossy coated */
#define DI_PAPER_THICK_GLOSSY_COATED	(0x61)	/* thick glossy coated */
#define DI_PAPER_MAT_COATED		(0x62)	/* matt coated */
#define DI_PAPER_THICK_MAT_COATED	(0x63)	/* thick matt coated */
#define DI_PAPER_WATER_PROOF		(0x64)	/* waterproof */
#define DI_PAPER_CARDBOARD4		(0x65)	/* cardboard 4 */
#define DI_PAPER_CARDBOARD4REV		(0x66)	/* cardboard 4 (reverse) */
#define DI_PAPER_COATED_HIGH_GLOSSY	(0x67)	/* high glossy coated */
#define DI_PAPER_SEMIGLOSSY		(0x68)
#define DI_PAPER_INKJETPLAIN	(0x69)
#define DI_PAPER_MATFILM		(0x6C)
#define DI_PAPER_CADCOATED		(0x6D)
#define DI_PAPER_NONE          (0x80)          /* トレイに設定されている紙種(特定PDLかつトレイ指定時のみ使用可) */
#define DI_PAPER_USER_DEF9			(0x81)	/* ユーザ指定９(IMSS) */
#define DI_PAPER_USER_DEF10			(0x82)	/* ユーザ指定１０(IMSS) */
#define DI_PAPER_USER_DEF11			(0x83)	/* ユーザ指定１１(IMSS) */
#define DI_PAPER_USER_DEF12			(0x84)	/* ユーザ指定１２(IMSS) */
#define DI_PAPER_USER_DEF13			(0x85)	/* ユーザ指定１３(IMSS) */
#define DI_PAPER_USER_DEF14			(0x86)	/* ユーザ指定１４(IMSS) */
#define DI_PAPER_USER_DEF15			(0x87)	/* ユーザ指定１５(IMSS) */
#define DI_PAPER_USER_DEF16			(0x88)	/* ユーザ指定１６(IMSS) */
#define DI_PAPER_USER_DEF17			(0x89)	/* ユーザ指定１７(IMSS) */
#define DI_PAPER_USER_DEF18			(0x8A)	/* ユーザ指定１８(IMSS) */
#define DI_PAPER_USER_DEF19			(0x8B)	/* ユーザ指定１９(IMSS) */
#define DI_PAPER_USER_DEF20			(0x8C)	/* ユーザ指定２０(IMSS) */
#define DI_PAPER_USER_DEF21			(0x8D)	/* ユーザ指定２１(IMSS) */
#define DI_PAPER_USER_DEF22			(0x8E)	/* ユーザ指定２２(IMSS) */
#define DI_PAPER_USER_DEF23			(0x8F)	/* ユーザ指定２３(IMSS) */
#define DI_PAPER_USER_DEF24			(0x90)	/* ユーザ指定２４(IMSS) */
#define DI_PAPER_USER_DEF25			(0x91)	/* ユーザ指定２５(IMSS) */
#define DI_PAPER_USER_DEF26			(0x92)	/* ユーザ指定２６(IMSS) */
#define DI_PAPER_USER_DEF27			(0x93)	/* ユーザ指定２７(IMSS) */
#define DI_PAPER_USER_DEF28			(0x94)	/* ユーザ指定２８(IMSS) */
#define DI_PAPER_USER_DEF29			(0x95)	/* ユーザ指定２９(IMSS) */
#define DI_PAPER_USER_DEF30			(0x96)	/* ユーザ指定３０(IMSS) */
#define DI_PAPER_USER_DEF31			(0x97)	/* ユーザ指定３１(IMSS) */
#define DI_PAPER_USER_DEF32			(0x98)	/* ユーザ指定３２(IMSS) */
#define DI_PAPER_USER_DEF33			(0x99)	/* ユーザ指定３３(IMSS) */
#define DI_PAPER_USER_DEF34			(0x9A)	/* ユーザ指定３４(IMSS) */
#define DI_PAPER_USER_DEF35			(0x9B)	/* ユーザ指定３５(IMSS) */
#define DI_PAPER_USER_DEF36			(0x9C)	/* ユーザ指定３６(IMSS) */
#define DI_PAPER_USER_DEF37			(0x9D)	/* ユーザ指定３７(IMSS) */
#define DI_PAPER_USER_DEF38			(0x9E)	/* ユーザ指定３８(IMSS) */
#define DI_PAPER_USER_DEF39			(0x9F)	/* ユーザ指定３９(IMSS) */
#define DI_PAPER_USER_DEF40			(0xA0)	/* ユーザ指定４０(IMSS) */
#define DI_PAPER_USER_DEF41			(0xA1)	/* ユーザ指定４１(IMSS) */
#define DI_PAPER_USER_DEF42			(0xA2)	/* ユーザ指定４２(IMSS) */
#define DI_PAPER_USER_DEF43			(0xA3)	/* ユーザ指定４３(IMSS) */
#define DI_PAPER_USER_DEF44			(0xA4)	/* ユーザ指定４４(IMSS) */
#define DI_PAPER_USER_DEF45			(0xA5)	/* ユーザ指定４５(IMSS) */
#define DI_PAPER_USER_DEF46			(0xA6)	/* ユーザ指定４６(IMSS) */
#define DI_PAPER_USER_DEF47			(0xA7)	/* ユーザ指定４７(IMSS) */
#define DI_PAPER_USER_DEF48			(0xA8)	/* ユーザ指定４８(IMSS) */
#define DI_PAPER_USER_DEF49			(0xA9)	/* ユーザ指定４９(IMSS) */
#define DI_PAPER_USER_DEF50			(0xAA)	/* ユーザ指定５０(IMSS) */
#define DI_PAPER_USER_DEF51			(0xAB)	/* ユーザ指定５１(IMSS) */
#define DI_PAPER_USER_DEF52			(0xAC)	/* ユーザ指定５２(IMSS) */
#define DI_PAPER_USER_DEF53			(0xAD)	/* ユーザ指定５３(IMSS) */
#define DI_PAPER_USER_DEF54			(0xAE)	/* ユーザ指定５４(IMSS) */
#define DI_PAPER_USER_DEF55			(0xAF)	/* ユーザ指定５５(IMSS) */
#define DI_PAPER_USER_DEF56			(0xB0)	/* ユーザ指定５６(IMSS) */
#define DI_PAPER_USER_DEF57			(0xB1)	/* ユーザ指定５７(IMSS) */
#define DI_PAPER_USER_DEF58			(0xB2)	/* ユーザ指定５８(IMSS) */
#define DI_PAPER_USER_DEF59			(0xB3)	/* ユーザ指定５９(IMSS) */
#define DI_PAPER_USER_DEF60			(0xB4)	/* ユーザ指定６０(IMSS) */
#define DI_PAPER_USER_DEF61			(0xB5)	/* ユーザ指定６１(IMSS) */
#define DI_PAPER_USER_DEF62			(0xB6)	/* ユーザ指定６２(IMSS) */
#define DI_PAPER_USER_DEF63			(0xB7)	/* ユーザ指定６３(IMSS) */
#define DI_PAPER_USER_DEF64			(0xB8)	/* ユーザ指定６４(IMSS) */
#define DI_PAPER_USER_DEF65			(0xB9)	/* ユーザ指定６５(IMSS) */
#define DI_PAPER_USER_DEF66			(0xBA)	/* ユーザ指定６６(IMSS) */
#define DI_PAPER_USER_DEF67			(0xBB)	/* ユーザ指定６７(IMSS) */
#define DI_PAPER_USER_DEF68			(0xBC)	/* ユーザ指定６８(IMSS) */
#define DI_PAPER_USER_DEF69			(0xBD)	/* ユーザ指定６９(IMSS) */
#define DI_PAPER_USER_DEF70			(0xBE)	/* ユーザ指定７０(IMSS) */
#define DI_PAPER_USER_DEF71			(0xBF)	/* ユーザ指定７１(IMSS) */
#define DI_PAPER_USER_DEF72			(0xC0)	/* ユーザ指定７２(IMSS) */
#define DI_PAPER_USER_DEF73			(0xC1)	/* ユーザ指定７３(IMSS) */
#define DI_PAPER_USER_DEF74			(0xC2)	/* ユーザ指定７４(IMSS) */
#define DI_PAPER_USER_DEF75			(0xC3)	/* ユーザ指定７５(IMSS) */
#define DI_PAPER_USER_DEF76			(0xC4)	/* ユーザ指定７６(IMSS) */
#define DI_PAPER_USER_DEF77			(0xC5)	/* ユーザ指定７７(IMSS) */
#define DI_PAPER_USER_DEF78			(0xC6)	/* ユーザ指定７８(IMSS) */
#define DI_PAPER_USER_DEF79			(0xC7)	/* ユーザ指定７９(IMSS) */
#define DI_PAPER_USER_DEF80			(0xC8)	/* ユーザ指定８０(IMSS) */
#define DI_PAPER_USER_DEF81			(0xC9)	/* ユーザ指定８１(IMSS) */
#define DI_PAPER_USER_DEF82			(0xCA)	/* ユーザ指定８２(IMSS) */
#define DI_PAPER_USER_DEF83			(0xCB)	/* ユーザ指定８３(IMSS) */
#define DI_PAPER_USER_DEF84			(0xCC)	/* ユーザ指定８４(IMSS) */
#define DI_PAPER_USER_DEF85			(0xCD)	/* ユーザ指定８５(IMSS) */
#define DI_PAPER_USER_DEF86			(0xCE)	/* ユーザ指定８６(IMSS) */
#define DI_PAPER_USER_DEF87			(0xCF)	/* ユーザ指定８７(IMSS) */
#define DI_PAPER_USER_DEF88			(0xD0)	/* ユーザ指定８８(IMSS) */
#define DI_PAPER_USER_DEF89			(0xD1)	/* ユーザ指定８９(IMSS) */
#define DI_PAPER_USER_DEF90			(0xD2)	/* ユーザ指定９０(IMSS) */
#define DI_PAPER_USER_DEF91			(0xD3)	/* ユーザ指定９１(IMSS) */
#define DI_PAPER_USER_DEF92			(0xD4)	/* ユーザ指定９２(IMSS) */
#define DI_PAPER_USER_DEF93			(0xD5)	/* ユーザ指定９３(IMSS) */
#define DI_PAPER_USER_DEF94			(0xD6)	/* ユーザ指定９４(IMSS) */
#define DI_PAPER_USER_DEF95			(0xD7)	/* ユーザ指定９５(IMSS) */
#define DI_PAPER_USER_DEF96			(0xD8)	/* ユーザ指定９６(IMSS) */
#define DI_PAPER_USER_DEF97			(0xD9)	/* ユーザ指定９７(IMSS) */
#define DI_PAPER_USER_DEF98			(0xDA)	/* ユーザ指定９８(IMSS) */
#define DI_PAPER_USER_DEF99			(0xDB)	/* ユーザ指定９９(IMSS) */
#define DI_PAPER_USER_DEF100		(0xDC)	/* ユーザ指定１００(IMSS) */

	unsigned char	p_kind;			/* 紙種定義(すぐ上のdefine) */
#define DI_TRAY_MANUAL          (1 << 0)    /* (attr) manual */
#define DI_TRAY_TANDEM          (1 << 1)    /* (attr) tandem */
#define DI_TRAY_NODUPLEX        (1 << 2)    /* (attr) noduplex */
#define DI_TRAY_LOCKED          (1 << 3)    /* (attr) tray locked */
#define DI_TRAY_SIZE_SENSE      (1 << 4)    /* (attr) sense paper size */
#define DI_TRAY_NODUPLEX_PAPER  (1 << 5)    /* (attr) noduplex paper(size | type) */
#define DI_TRAY_FRONTCOVERPRINT (1 << 6)    /* (attr) frontcoverprint */
#define DI_TRAY_SLIPSHEET       (1 << 7)    /* (attr) slipsheet */
#define DI_TRAY_INNERLCT        (1 << 8)    /* (attr) INNER LCT */
#define DI_TRAY_CHAPTERSHEET1   (1 << 9)    /* (attr) chaptersheet1 */
#define DI_TRAY_CHAPTERSHEET2   (1 << 10)   /* (attr) chaptersheet2 */
#define DI_TRAY_CHAPTERSHEET3   (1 << 11)   /* (attr) chaptersheet3 */
#define DI_TRAY_CHAPTERSHEET4   (1 << 12)   /* (attr) chaptersheet4 */
#define DI_TRAY_CHAPTERSHEET5   (1 << 13)   /* (attr) chaptersheet5 */
#define DI_TRAY_CHAPTERSHEET6   (1 << 14)   /* (attr) chaptersheet6 */
#define DI_TRAY_CHAPTERSHEET7   (1 << 15)   /* (attr) chaptersheet7 */
#define DI_TRAY_BACKCOVERPRINT  (1 << 16)   /* (attr) backcoverprint */
#define DI_TRAY_PARTITION       (1 << 17)   /* (attr) partition */
#define DI_TRAY_TANDEM_SEPARATE (1 << 18)   /* (attr) tandem(separate) */
#define DI_TRAY_ROLL            (1 << 19)   /* (attr) roll tray */
#define DI_TRAY_MSIZESENSE_VALID	(1 << 20)	/* (attr) 手差し自動サイズ検知有効 */
#define DI_TRAY_SINGLE_PAPER    (1 << 21)   /* (attr) 一枚トレイ */
#define DI_TRAY_CHAPTERSHEET8   (1 << 22)   /* (attr) chaptersheet8 */
#define DI_TRAY_CHAPTERSHEET9   (1 << 23)   /* (attr) chaptersheet9 */
#define DI_TRAY_SMALLSIZE_TYPE  (1 << 24)   /* (attr) 小サイズトレイ設定がON */
	unsigned long	attr;			/* トレイ種類(すぐ上のdefine) */
#define DI_TRAY_PAPEREND       (1 << 0)
#define DI_TRAY_BUSY           (1 << 1)
#define DI_TRAY_SETFAIL        (1 << 2)
#define DI_TRAY_ERROR          (1 << 3)
#define DI_TRAY_COPEN          (1 << 4)
#define DI_TRAY_MAN_PAPEREXIST (1 << 5)
#define DI_TRAY_MAN_OPEN       (1 << 6)
#define DI_TRAY_MAN_SIZE       (1 << 7)
#define DI_TRAY_TAN_MISSSET    (1 << 8)
#define DI_TRAY_TAN_BUSY       (1 << 9)
#define DI_TRAY_UNLOAD         (1 << 10)
#define DI_TRAY_TAN_PAPEREXIST (1 << 11)
#define DI_TRAY_TAN_INVALID    (1 << 12)
#define DI_TRAY_DOOR_OPEN      (1 << 13)
	unsigned long	status;			/* ステータス(すぐ上のdefine) */
	unsigned long	p_length;		/* 用紙高さ(0.1mm単位) */
	unsigned long	p_width;		/* 用紙幅(0.1mm単位) */
} tray_info_t, di_onetrayinfo_t;

typedef struct di_trayinfo {
	long				tray_num;					/* トレイ数 */
	di_onetrayinfo_t	trayinfo[DI_MAX_TRAY_NUM];	/* 各トレイの情報 */
} di_trayinfo_t;

typedef struct di_optinfo {
#define DI_OPT_EXT_EXTLCT              (1 << 31)       /* ext. LCT */
#define DI_OPT_EXT_TRAY2               (1 << 30)       /* Tray2 */
#define DI_OPT_EXT_TRAY3               (1 << 29)       /* Tray3 */
#define DI_OPT_EXT_BANK                (1 << 28)       /* BANK */
#define DI_OPT_EXT_TANDEM              (1 << 27)       /* TANDEM */
#define DI_OPT_EXT_TRAYMAN             (1 << 26)       /* MANUAL TRAY */
#define DI_OPT_EXT_INLCT               (1 << 25)       /* INNER LCT */
#define DI_OPT_EXT_TRAY4               (1 << 24)       /* Tray4 */
#define DI_OPT_EXT_TRAY5               (1 << 23)       /* Tray5 */
#define DI_OPT_EXT_INSERTER            (1 << 22)       /* INSERTER */
#define DI_OPT_EXT_TRAY7               (1 << 21)       /* Tray7 */
#define DI_OPT_EXT_ROLL_FEEDER         (1 << 20)       /* Roll Unit */
#define DI_OPT_EXT_INSERTER2           (1 << 19)       /* INSERTER2(2段) */
#define DI_OPT_EXT_LARGELCT            (1 << 18)       /* Large Size LCT */
#define DI_OPT_EXT_ROLL_FEEDER2        (1 << 17)       /* Roll Unit2 */
	unsigned long	tray;		/* 給紙系オプション機器フラグ */
#define DI_OPT_EXT_1BIN                (1 << 31)       /* 1BIN */
#define DI_OPT_EXT_EXTTRAY             (1 << 30)       /* ext. tray */
#define DI_OPT_EXT_INSHIFT             (1 << 29)       /* INNER SHIFT */
#define DI_OPT_EXT_SUPERIOR            (1 << 28)       /* SUPERIOR */
	unsigned long	bin;		/* 排紙系オプション機器フラグ */
#define DI_OPT_EXT_DUPLEX              (1)
	unsigned long	duplex;		/* 両面ユニットオプション機器フラグ */
#define DI_OPT_EXT_FIN_YUKON           (1)
#define DI_OPT_EXT_FIN_LAWRENCE        (2)
#define DI_OPT_EXT_FIN_SADDLE          (3)             /* TONEGAWA */
#define DI_OPT_EXT_FIN_SHINKAWA        (4)
#define DI_OPT_EXT_FIN_FUJIGAWA        (5)
#define DI_OPT_EXT_FIN_KING            (6)
#define DI_OPT_EXT_FIN_BRAZOS_NON      (7)
#define DI_OPT_EXT_FIN_BRAZOS_PRF      (8)
#define DI_OPT_EXT_FIN_VICTORIA_B      (9)
#define DI_OPT_EXT_FIN_ZAIRE_SDL       (10)
#define DI_OPT_EXT_FIN_ZAIRE_NON       (11)
#define DI_OPT_EXT_FIN_TONEGAWA_C      (12)
#define DI_OPT_EXT_FIN_PLOKMATIC       (13)    /* VICTORIA-B+PLOKMATIC */
#define DI_OPT_EXT_FIN_KINUGAWA        (14)
#define DI_OPT_EXT_FIN_HUDOSON         (15)    /* GAIA_P1用FIN 本体排紙をつぶしてステープルのみ可能 */
#define DI_OPT_EXT_FIN_EUPHRATES_SDL   (16)
#define DI_OPT_EXT_FIN_EUPHRATES_NON   (17)
#define DI_OPT_EXT_FIN_TIGRIS          (18)
#define DI_OPT_EXT_FIN_KANOGAWA        (19)
#define DI_OPT_EXT_FIN_ATLANTIC_A      (20)    /* ジャバラ機 */
#define DI_OPT_EXT_FIN_ATLANTIC_B      (21)    /* フォルダー機（ジャバラ機＋クロスユニット） */
#define	DI_OPT_EXT_FIN_ELBE            (23)	/* ELBE */
#define	DI_OPT_EXT_FIN_SAKAWAGAWA	(24)
#define DI_OPT_EXT_FIN_COLUMBIA        (25)    /* COLUMBIA */
#define DI_OPT_EXT_FIN_SHINJIKO        (26)    /* COLUMBIA+SHINJIKO */
#define DI_OPT_EXT_FIN_EUPHRATES_1BIT  (27)    /* EUPHRATES-D(1 hole) */
#define DI_OPT_EXT_FIN_EUPHRATES_2BIT  (28)    /* EUPHRATES-D(2 holes) */
#define DI_OPT_EXT_FIN_RUBICON         (29)    /* RUBICON */
#define DI_OPT_EXT_FIN_AMUR_SDL        (30)    /* AMUR(saddle stitch) */
#define DI_OPT_EXT_FIN_AMUR_NON        (31)    /* AMUR */
#define DI_OPT_EXT_FIN_VOLGA_SDL       (32)    /* VOLGA(saddle stitch) */
#define DI_OPT_EXT_FIN_VOLGA_NON       (33)    /* VOLGA */
#define DI_OPT_EXT_FIN_COLUMBIA_SDL    (34)    /* COLUMBIA(saddle stitch) */
#define DI_OPT_EXT_FIN_UYUNI           (35)    /* UYUNI(針無し綴じ) */
	unsigned long	fin;		/* フィニッシャ系オプション機器フラグ */
#define DI_OPT_EXT_MB_9BIN             (1)             /* MB 9BIN */
#define DI_OPT_EXT_MB_9BIN_P           (2)             /* MB_P 9BIN+proof */
#define DI_OPT_EXT_MB_SAXBY            (3)             /* SAXBY */
#define DI_OPT_EXT_MB_POTOMAC          (4)             /* POTOMAC */
#define DI_OPT_EXT_MB_JACK             (5)             /* JACK */
#define DI_OPT_EXT_MB_ONTARIO          (6)             /* ONTARIO */
	unsigned long	mbox;		/* メールボックス系オプション機器フラグ */
#define DI_OPT_EXT_DEVELOPMENT_R       (1 << 31)       /* RED DEVELOPMENT */
#define DI_OPT_EXT_ZFOLD_UNIT          (1 << 30)       /* ZFOLD UNIT */
	unsigned long	misc;		/* 上記以外のオプション機器フラグ */
#define DI_OPT_EXT_CF_UNIT             (1 << 31)       /* CF UNIT */
#define DI_OPT_EXT_ADF                 (1 << 30)       /* ADF */
#define DI_OPT_EXT_GBC_PUNCH           (1 << 29)       /* GBCパンチユニット */
#define DI_OPT_EXT_KARUN_SDL           (1 << 28)       /* 中綴じユニット(KARUN) */
	unsigned long	non_prt;	/* プリンタに関連しないオプション機器フラグ */
} di_optinfo_t;

typedef struct di_ethertalk_info {
/* length */
#define	DI_MAX_ATINFO_OBJECT_NAME_LEN	32
#define	DI_MAX_ATINFO_TYPE_NAME_LEN		32
#define	DI_MAX_ATINFO_ZONE_NAME_LEN		32
#define	DI_MAX_ATINFO_MACADDR_LEN		6

#define	DI_ATINFO_FLAG_OBJECT_NAME		(1 << 0)
#define	DI_ATINFO_FLAG_TYPE_NAME		(1 << 1)
#define	DI_ATINFO_FLAG_ZONE_NAME		(1 << 2)
#define	DI_ATINFO_FLAG_MACADDR			(1 << 3)
	unsigned long		flag;								/* フラグ */
	unsigned char		object_name[DI_MAX_ATINFO_OBJECT_NAME_LEN + 1];		/* NULLターミネート (R/W) */
	unsigned char		type_name[DI_MAX_ATINFO_TYPE_NAME_LEN + 1];		/* NULLターミネート (ReadOnly)*/
	unsigned char		zone_name[DI_MAX_ATINFO_ZONE_NAME_LEN + 1];		/* NULLターミネート (R/W)*/
	unsigned char		macaddr[DI_MAX_ATINFO_MACADDR_LEN];			/* (ReadOnly) */
} di_ethertalk_info_t;

typedef struct di_ujob_info {

/*
 *	flag
 */
#define	DI_UPARAM_DATE					(1 << 0)
#define	DI_UPARAM_TIME					(1 << 1)
#define	DI_UPARAM_TRACKID				(1 << 2)
#define	DI_UPARAM_USERCODE				(1 << 3)
#define	DI_UPARAM_USERID				(1 << 4)
#define	DI_UPARAM_JOBID					(1 << 5)
#define	DI_UPARAM_JOBPASSWORD			(1 << 6)
#define	DI_UPARAM_DISPCHARSET			(1 << 7)
#define	DI_UPARAM_HOSTCHARSET			(1 << 8)
#define	DI_UPARAM_HOSTLOGINNAME			(1 << 9)
#define	DI_UPARAM_HOSTNAME				(1 << 10)
#define	DI_UPARAM_HOSTPORTNAME			(1 << 11)
#define	DI_UPARAM_HOSTPRINTERNAME		(1 << 12)
#define	DI_UPARAM_PROOFJOB				(1 << 13)
#define	DI_UPARAM_SECUREJOB				(1 << 14)
#define	DI_UPARAM_JOBNAME				(1 << 15)
#define	DI_UPARAM_OWNERID				(1 << 16)
#define	DI_UPARAM_PRINTINFO				(1 << 17)
#define	DI_UPARAM_AUTHUSERNAME			(1 << 18)
#define	DI_UPARAM_AUTHPASSWORD			(1 << 19)
#define	DI_UPARAM_AUTHENCRYPTMETHOD		(1 << 20)
#define	DI_UPARAM_AUTHENCRYPTSETTING	(1 << 21)
#define	DI_UPARAM_JOBPASSWORD_EXT		(1 << 22)
#define	DI_UPARAM_PAUSEDJOB			(1 << 23)
#define	DI_UPARAM_FORMJOB			(1 << 24)
#define	DI_UPARAM_AUTHUSERNAMECHARSET	(1 << 25)
#define	DI_UPARAM_AUTHPASSWORDCHARSET	(1 << 26)
#define	DI_UPARAM_NDISPCHARSET		(1 << 27)
#define	DI_UPARAM_NHOSTCHARSET		(1 << 28)
#define	DI_UPARAM_BILLINGCODE		(1 << 29)
#define	DI_UPARAM_PRINTAPPOINTEDTIME	(1 << 30)
#define	DI_UPARAM_EXT2					(1 << 31)
/*
 *	flag2
 */
#define	DI_UPARAM_DRIVERKINDINFO		(1 << 0)
#define	DI_UPARAM_FOLDERNUMBER			(1 << 1)
#define	DI_UPARAM_FOLDERPASSWORD		(1 << 2)
#define	DI_UPARAM_EXT3					(1 << 31)
/*
 *	max length
 */
#define	DI_MAX_UPARAM_DATE_LEN				10
#define	DI_MAX_UPARAM_TIME_LEN				8
#define	DI_MAX_UPARAM_TRACKID_LEN			20
#define	DI_MAX_UPARAM_USERCODE_LEN			8
#define	DI_MAX_UPARAM_USERID_LEN			8
#define	DI_MAX_UPARAM_JOBID_LEN				20
#define	DI_MAX_UPARAM_JOBPASSWORD_LEN		4
#define	DI_MAX_UPARAM_DISPCHARSET_LEN		63
#define	DI_MAX_UPARAM_HOSTCHARSET_LEN		63
#define	DI_MAX_UPARAM_HOSTLOGINNAME_LEN		20
#define	DI_MAX_UPARAM_HOSTNAME_LEN			63
#define	DI_MAX_UPARAM_HOSTPORTNAME_LEN		64
#define	DI_MAX_UPARAM_HOSTPRINTERNAME_LEN	64
#define	DI_MAX_UPARAM_JOBNAME_LEN			232
#define	DI_MAX_UPARAM_OWNERID_LEN			20
#define	DI_MAX_UPARAM_PRINTINFO_LEN			230
#define	DI_MAX_UPARAM_AUTHUSERNAME_LEN		217
#define	DI_MAX_UPARAM_AUTHPASSWORD_LEN		217
#define	DI_MAX_UPARAM_JOBPASSWORD_EXT_LEN	8
#define	DI_MAX_UPARAM_BILLINGCODE_LEN		32
#define	DI_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN	5
#define	DI_MAX_UPARAM_FOLDERPASSWORD_LEN	8
/*
 *	driver kind info
 */
#define	DI_UPARAM_DRIVERKINDINFO_INBOX			(1)
#define	DI_UPARAM_DRIVERKINDINFO_PCL6			(2)
#define	DI_UPARAM_DRIVERKINDINFO_PCL6UD			(3)
#define	DI_UPARAM_DRIVERKINDINFO_PCL6UDGENERIC	(4)
#define	DI_UPARAM_DRIVERKINDINFO_PS				(5)
#define	DI_UPARAM_DRIVERKINDINFO_PSUD			(6)
#define	DI_UPARAM_DRIVERKINDINFO_PSUDGENERIC	(7)
#define	DI_UPARAM_DRIVERKINDINFO_RPCSBASIC		(8)
#define	DI_UPARAM_DRIVERKINDINFO_RPCSXPS		(9)
#define	DI_UPARAM_DRIVERKINDINFO_RPCS			(10)


	unsigned long	flag;
	union {
		unsigned char	date[DI_MAX_UPARAM_DATE_LEN + 1];
		unsigned char	time[DI_MAX_UPARAM_TIME_LEN + 1];
		unsigned char	trackid[DI_MAX_UPARAM_TRACKID_LEN + 1];
		unsigned char	usercode[DI_MAX_UPARAM_USERCODE_LEN + 1];
		unsigned char	billingcode[DI_MAX_UPARAM_BILLINGCODE_LEN + 2];
		unsigned char	userid[DI_MAX_UPARAM_USERID_LEN + 1];
		unsigned char	jobid[DI_MAX_UPARAM_JOBID_LEN + 1];
		unsigned char	jobpassword[DI_MAX_UPARAM_JOBPASSWORD_LEN + 1];
		unsigned char	dispcharset[DI_MAX_UPARAM_DISPCHARSET_LEN + 1];
		unsigned char	hostcharset[DI_MAX_UPARAM_HOSTCHARSET_LEN + 1];
		unsigned char	hostloginname[DI_MAX_UPARAM_HOSTLOGINNAME_LEN + 1];
		unsigned char	hostname[DI_MAX_UPARAM_HOSTNAME_LEN + 1];
		unsigned char	hostportname[DI_MAX_UPARAM_HOSTPORTNAME_LEN + 1];
		unsigned char	hostprintername[DI_MAX_UPARAM_HOSTPRINTERNAME_LEN + 1];
		unsigned char	jobname[DI_MAX_UPARAM_JOBNAME_LEN + 1];
		unsigned char	ownerid[DI_MAX_UPARAM_OWNERID_LEN + 1];
		unsigned char	printinfo[DI_MAX_UPARAM_PRINTINFO_LEN + 1];
		unsigned char	authusername[DI_MAX_UPARAM_AUTHUSERNAME_LEN + 1];
		unsigned char	authpassword[DI_MAX_UPARAM_AUTHPASSWORD_LEN + 1];
		int		authencryptmethod;
		int		authencryptsetting;
		unsigned char	jobpassword_ext[DI_MAX_UPARAM_JOBPASSWORD_EXT_LEN + 1];
		short			authusernamecharset;
		short			authpasswordcharset;
		short			ndispcharset;
		short			nhostcharset;
		unsigned char	printappointedtime[DI_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN + 1];
		int				driverkindinfo;
		unsigned short	foldernumber;
		unsigned char	folderpassword[DI_MAX_UPARAM_FOLDERPASSWORD_LEN + 1];
		unsigned char	dummy[240];
	} up;
	unsigned long	flag2;
} di_ujob_info_t;


typedef struct di_status {

#define	DI_ST_CODE_MAX		32

	unsigned char		cur_interpreter;			/* 動作中のインタプリタID */
	int					state;						/* state */
	int					st_code_num;				/* st_code[]で有効な数 */
	unsigned long		st_code[DI_ST_CODE_MAX];	/* status code list */
#define	DI_SYS_FUNC_DUPLEX			(1 << 0)		/* duplex */
#define	DI_SYS_FUNC_STAPLE			(1 << 1)		/* staple */
#define	DI_SYS_FUNC_PUNCH			(1 << 2)		/* punch */
#define	DI_SYS_FUNC_SORT			(1 << 3)		/* sorting */
#define	DI_SYS_FUNC_HDD_FS			(1 << 4)		/* HDD for FileSystem */
#define	DI_SYS_FUNC_SHIFT			(1 << 5)		/* shift */
#define	DI_SYS_FUNC_FINISHER		(1 << 6)		/* Finisher */
#define	DI_SYS_FUNC_MAILBOX			(1 << 7)		/* Mail Box */
#define	DI_SYS_FUNC_COLOR			(1 << 8)		/* Color (CMYK) */
#define	DI_SYS_FUNC_HDD				(1 << 9)		/* HDD */
#define	DI_SYS_FUNC_PROOFPRINT		(1 << 10)	/* proof print */
#define	DI_SYS_FUNC_SEQUREPRINT		(1 << 11)	/* sequre print */
#define	DI_SYS_FUNC_LOCALSTORAGE	(1 << 12)	/* local storage */
#define	DI_SYS_FUNC_NETWORK			(1 << 13)	/* network */
#define	DI_SYS_FUNC_REMOTEPRINT		(1 << 14)	/* remote print */
#define	DI_SYS_FUNC_IEEE1394		(1 << 15)	/* IEEE1394 */
#define	DI_SYS_FUNC_IEEE802_11b		(1 << 18)	/* IEEE802.11b */
#define	DI_SYS_FUNC_USB				(1 << 19)	/* USB */
#define	DI_SYS_FUNC_BLUETOOTH		(1 << 21)	/* Bluetooth */
	unsigned long		function_disable;	/* 機能使用不可(SC) */
#define	DI_STATE_OFFLINE			(1 << 0)		/* ST_OFFLINE */
#define	DI_STATE_HEXDUMP			(1 << 1)		/* ST_HEXDUMP */
#define	DI_STATE_WARMING_UP			(1 << 2)		/* ST_WARMING_UP */
#define	DI_STATE_ENERGY_SAVE		(1 << 3)		/* ST_ENERGY_SAVE */
#define	DI_STATE_PRINTING			(1 << 4)		/* ST_PROCESSIG (印刷中) */
#define	DI_STATE_PROCESSING			(1 << 5)		/* ST_PROCESSING（データ処理中） */
#define	DI_STATE_PREHEAT			(1 << 6)		/* ST_PREHEAT */
#define	DI_STATE_WAITING			(1 << 7)		/* ST_WAITING */
#define	DI_STATE_JOB_RESETTING		(1 << 8)		/* ST_JOB_RESETTING */
#define	DI_STATE_INT_REQ			(1 << 9)		/* 割込みコピー（印刷停止）要求 */
#define	DI_STATE_INT_PAUSE			(1 << 10)	/* 割込みコピー中 */
#define	DI_STATE_CALIBRATING		(1 << 11)	/* calibrating */ 
#define	DI_STATE_SUPPLYING_TONER	(1 << 12)	/* supplying toner */
#define	DI_STATE_INIT_DEVELOPER		(1 << 13)	/* initial developer */
#define	DI_STATE_COOLING_DOWN		(1 << 14)	/* cooling down */
#define	DI_STATE_CARDSAVE			(1 << 31)	/* カードセーブ */
	unsigned long		state_detail;		/* 状態の詳細をビットであらわす */
	/* st_code[]の警告扱いのエラーコードの数 */
	int			st_code_num_warning;
	/* st_code[]のオペレータコール扱いのエラーコードの数 */
	int			st_code_num_error;
} di_status_t;


typedef struct di_diskinfo {

#define DI_MAX_HDD_PATH_LEN 64

	char	stat;						/* status              */
	char	path[DI_MAX_HDD_PATH_LEN];	/* path                */
	long	f_bsize;					/* block size (bytes)  */
	long	f_blocks;					/* total blocks        */
	long	f_bfree;					/* free blocks         */
	long	reserve;					/* reserve             */
} di_diskinfo_t;

typedef struct di_res_reqpaper{
	unsigned short	type;		/* GWID_GpsPage_TrayRequest_Res */
	unsigned short	length;
	int				pid;
	int				result;		/* 結果 */
#define	DI_TRAY_FOUND	(0)		/* 条件に合うトレイが出現した */
#define	DI_TRAY_ERRSKIP	(1)		/* エラースキップしてください */
#define	DI_TRAY_CANCEL	(2)		/* キャンセルが指示された */
#define	DI_TRAY_FORCE	(3)		/* 強制印刷が指示された */
#define	DI_TRAY_ANOTHER	(4)		/* 用紙サイズが類似したトレイ存在 */
	int			tray_id;		/* トレイID */
	int			paper_code;		/* 用紙サイズコード */
	int			paper_width;	/* 用紙幅   (0.1mm単位) */
	int			paper_length;	/* 用紙高さ (0.1mm単位) */
} di_res_reqpaper_t;

typedef struct di_envinfo {
	long           id; /* variable ID */
#define DI_PENV_VARFLAG_READONLY (1 << 0) /* PJL READ ONLY */
	unsigned long  flag; /* variable flag */
	long           init_val; /* initial value */
	long           def_val; /* default value */
	long           cur_val; /* current value */
	unsigned char  val_denom; /* value denominaator (use if type is FLOAT) */
#define DI_PENV_VALTYPE_ENUM    0 /* ENUMERATE */
#define DI_PENV_VALTYPE_INT     1 /* INTEGER(range) */
#define DI_PENV_VALTYPE_FLOAT   2 /* FLOAT(range) */
#define DI_PENV_VALTYPE_NETADDR 3 /* Network address */
	unsigned char  val_type; /* value type */
	long           val_num; /* number of value list */
} di_envinfo_t;

typedef struct di_flashmem_info {
#define DI_FLASHMEM_ATTR_RW (1 << 0) /* Read/Write可能 */
	unsigned long attr;          /* attribute */
#define DI_FLASHMEM_MEDIA_UNKNOWN 0 /* 不明 */
#define DI_FLASHMEM_MEDIA_ROM     1 /* ROM DIMM / SD Card */
	unsigned long media;         /* kind of media */
#define DI_MAX_FM_PATH_LEN 64
	char path[DI_MAX_FM_PATH_LEN];  /* directory path */
} di_flashmem_info_t;


typedef  struct {
	unsigned short idPanel;   /* アイテム自身のパネルＩＤ */
	unsigned short idDown;    /* 下階層のパネルＩＤ */
	/* トラップ用関数ポインタ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
#define   FILENAME_LEN         14
	unsigned char  filename[FILENAME_LEN];   /* ファイルネーム */
	unsigned char  panel_lock_stat; /* パネルロック状態情報 */       
	unsigned char  ucReserved[3];   /* 未使用 */
	unsigned char  reserve_cid[4];  /* クライアントＩＤ用予約領域 */
	unsigned char  ucItem;          /* アイテムタイプ  */
	unsigned char  ucMenu;          /* メニュータイプ  */
} di_menu_type_t;


typedef  struct {
	unsigned short idPanel;    /* アイテム自身のパネルＩＤ */
	unsigned short idNext;     /* 同階層の次のパネルＩＤ */
	unsigned short idPrev;     /* 同階層の前のパネルＩＤ */
	unsigned short idDown;     /* 下階層のパネルＩＤ */
	unsigned short idBack;     /* 呼出し元 上位階層のパネルＩＤ */
	unsigned short str1_id;    /* タイトル部（１行目）の文字列ＩＤ */
	unsigned short str1_mod;   /* タイトル部（１行目）の文字列修飾情報 */
	unsigned short str2_id;    /* 項目部（２行目）の文字列ＩＤ */
    /* トラップ用関数ポインタ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  disp_flg;   /* 表示／半輝度／非表示のフラグ */
        unsigned char  ucReserved[5];   /* 未使用 */
        unsigned char  reserve_cid[4];  /* クライアントＩＤ保存用予約領域 */
        unsigned char  ucItem;          /* アイテムタイプ */
        unsigned char  ucMenu;          /* メニュータイプ */
} di_item_type_menu_t;

typedef  struct {
	unsigned short idPanel;  /* アイテム自身のパネルＩＤ */
	unsigned short idNext;   /* 同階層の次のパネルＩＤ */
	unsigned short idPrev;   /* 同階層の前のパネルＩＤ */
	unsigned short idDown;   /* 下階層のパネルＩＤ */
	unsigned short idBack;   /* 呼出し元 上位階層のパネルＩＤ */
	unsigned short str1_id;  /* タイトル部（１行目）の文字列ＩＤ */
	unsigned short str1_mod; /* タイトル部（１行目）の文字列修飾情報 */
	unsigned short str2_id;  /* 項目部（２行目）の文字列ＩＤ */
	/* トラップ用関数ポインタ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  up_num;   /* 実行後に遷移する上への階層数 */
	unsigned char  disp_flg; /* 表示／半輝度／非表示のフラグ */
	unsigned char  fselect;  /* 選択／非選択のフラグ */
	unsigned char  disp_fselect; /* 選択フラグの表示／非表示のフラグ */
	unsigned char  ucReserved[2]; /* 未使用 */
	unsigned char  reserve_cid[4]; /* クライアントＩＤ保存用予約領域 */
	unsigned char  ucItem;         /* アイテムタイプ */
	unsigned char  ucMenu;         /* メニュータイプ */
} di_item_type_select_t;

typedef  struct {
	unsigned short idPanel;  /* アイテム自身のパネルＩＤ */
	unsigned short idBack;   /* 呼出し元 上位階層のパネルＩＤ */
	unsigned short str1_id;  /* タイトル部（１行目）の文字列ＩＤ */
	unsigned short str1_mod; /* タイトル部（１行目）の文字列修飾情報 */
	short          sMax;     /* 最大値 */
	short          sMin;     /* 最小値 */
	unsigned short step;     /* 変化幅 */
	short          value;    /* 設定値 */
	/* トラップ用関数ポインタ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;         /* 単位文字列ＩＤ */
	unsigned char  up_num;         /* 実行後に遷移する上への階層数 */
	unsigned char  fig_num;        /* 表示桁数 */
	unsigned char  ucReserved[2];  /* 未使用 */
	unsigned char  reserve_cid[4]; /* クライアントＩＤ保存用予約領域 */
	unsigned char  ucItem;         /* アイテムタイプ */
	unsigned char  ucMenu;         /* メニュータイプ */
} di_item_type_integer_t;

typedef  struct {
	unsigned short idPanel;    /* アイテム自身のパネルＩＤ             */
	unsigned short idBack;     /* 呼出し元 上位階層のパネルＩＤ        */
	unsigned short str1_id;    /* タイトル部（１行目）の文字列ＩＤ     */
	unsigned short str1_mod;   /* タイトル部（１行目）の文字列修飾情報 */
	short          sMax;       /* 最大値                               */
	short          sMin;       /* 最小値                               */
	unsigned short step;       /* 変化幅                               */
	short          value;      /* 設定値                               */
	/* トラップ用関数ポインタ               */
	void           (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;     /* 単位文字列ＩＤ                       */
	unsigned char  up_num;     /* 実行後に遷移する上への階層数         */
	unsigned char  fig_num;    /* 表示桁数                             */
	unsigned char  ucMulti;    /* 指数値                               */
	unsigned char  ucReserved; /* 未使用                               */
	unsigned char  reserve_cid[4]; /* クライアントＩＤ保存用予約領域       */
	unsigned char  ucItem;     /* アイテムタイプ                       */
	unsigned char  ucMenu;     /* メニュータイプ                       */
} di_item_type_float_t;

typedef  struct {
	unsigned short idPanel; /* アイテム自身のパネルＩＤ             */
	unsigned short idBack;  /* 呼出し元 上位階層のパネルＩＤ        */
	unsigned short str1_id; /* タイトル部（１行目）の文字列ＩＤ     */
	short          sMin;    /* 最小値                               */
	int            sMax;    /* 最大値                               */
	int            value;   /* 設定値                               */
	/* トラップ用関数ポインタ               */
	void           (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;  /* 単位文字列ＩＤ                       */
	unsigned char  str1_mod; /* タイトル部（１行目）の文字列修飾情報 */
	unsigned char  step;     /* 変化幅                               */
	unsigned char  fig_num;  /* 表示桁数                             */
	unsigned char  ucMulti;  /* 指数値                               */
	unsigned char  reserve_cid[4]; /* クライアントＩＤ保存用予約領域       */
	unsigned char  ucItem;   /* アイテムタイプ                       */
	unsigned char  ucMenu;   /* メニュータイプ                       */
} di_item_type_floatext_t;

typedef  struct di_fontinfo {
	unsigned char *addr;  /* アドレス */
	unsigned long size;   /* サイズ */
	unsigned long offset; /* オフセット */
} di_fontinfo_t;

typedef  struct di_pdlinfo {
#define DI_INTERP_LEN_SHORTNAME 3
#define DI_MINFO_KEY_PDL_CATEGORY_LEN 7
	int interp_id; /* インタプリタID */
	/* ショートネーム(定義されていない場合はNULL) */
	char shortname[DI_INTERP_LEN_SHORTNAME + 1];
	char path; /* printer.ini path ID  */
	/* printer.ini ファイルのカテゴリ名 */
	char category[DI_MINFO_KEY_PDL_CATEGORY_LEN + 1];
} di_pdlinfo_t;

/**
 * 製品情報構造体
 */
typedef struct di_initinfo {
#define	DI_MACHINECODE_ADONIS_C2		0x00
#define	DI_MACHINECODE_KIR_P			0x10
#define	DI_MACHINECODE_KIR_P2			0x13
#define	DI_MACHINECODE_KIR_P3			0x15
#define	DI_MACHINECODE_JUPITER_P		0x20
#define	DI_MACHINECODE_URANOS_P			0x30
#define	DI_MACHINECODE_RUSSIAN_C2		0x40
#define DI_MACHINECODE_ADONIS_P3		0x50
#define DI_MACHINECODE_URANOS_C			0x60
#define DI_MACHINECODE_ARES_P			0x70
#define DI_MACHINECODE_KAISER3			0x80
#define DI_MACHINECODE_JUPITER_P2		0x90
#define DI_MACHINECODE_JUPITER_P2Y		0x93		/* 薬袋 */
#define DI_MACHINECODE_JUPITER_P2M		0xa0
#define DI_MACHINECODE_JUPITER_P2K		0xb0
#define	DI_MACHINECODE_URANOS_P2		0xc0
#define DI_MACHINECODE_JUPITER_C0		0xe0
#define	DI_MACHINECODE_CASSIS_P1_DOM	0xf0		/* DOM */

#define	DI_MACHINECODE_MARTINI_C1		0x00080000
#define	DI_MACHINECODE_BELLINI_C2		0x00090000
#define	DI_MACHINECODE_ADONIS_C3		0x000A0000
#define	DI_MACHINECODE_RUSSIAN_C3		0x000B0000
#define	DI_MACHINECODE_SEADRAGON_C1		0x000C0000
#define	DI_MACHINECODE_JUPITER_C1		0x000D0000
#define	DI_MACHINECODE_KIR_P3_EXP		0x00010000	/* EXP */
#define	DI_MACHINECODE_KIR_C2			0x00120000
#define	DI_MACHINECODE_CASSIS_P1_EXP	0x00130000	/* EXP */
#define	DI_MACHINECODE_PLUTO_P1			0x00140000
#define DI_MACHINECODE_VENUS_C1			0x00150000
#define DI_MACHINECODE_URANOS_C2		0x00160000
#define	DI_MACHINECODE_JUPITER_P3		0x00170000
#define DI_MACHINECODE_GAIA_P1			0x00180000
#define DI_MACHINECODE_MARTINI_C2		0x00190000
#define DI_MACHINECODE_STELLA_C2		0x001A0000
#define DI_MACHINECODE_DOLPHIN_C2		0x001B0000	/* DOLPHIN-C2 group */
#define DI_MACHINECODE_JUPITER_C2		0x001C0000	/* JUPITER_C2 group */
#define	DI_MACHINECODE_CASSIS_P2		0x001D0000	/* CASSIS-P2 group */
#define	DI_MACHINECODE_MARTINI_P1		0x001E0000	/* MARTINI-P1 group */
#define	DI_MACHINECODE_ADONIS_C4		0x001F0000	/* ADONIS-C4 group */
#define	DI_MACHINECODE_RUSSIAN_C4		0x00200000	/* RUSSIAN-C4 group */
#define	DI_MACHINECODE_KIR_P4			0x00210000	/* KIR-P4 group */
#define	DI_MACHINECODE_JUPITER_P4		0x00220000	/* JUPITER-P4 group */
#define DI_MACHINECODE_PEGASUS_C1		0x00230000	/* PegasusC1 group */
#define DI_MACHINECODE_APOLLON_C1		0x00240000	/* ApollonC1 group */
#define DI_MACHINECODE_ATHENA_C1		0x00250000	/* AthenaC1 group */
#define DI_MACHINECODE_BELLINI_C3		0x00260000	/* BELLINI-C3 group */
#define DI_MACHINECODE_MARTINI_C3		0x00270000	/* MARTINI-C3 group */
#define DI_MACHINECODE_ARES_P2			0x00280000	/* ARES-P2 group */
#define DI_MACHINECODE_GAIA_P2			0x00290000	/* Gaia-P2 group */
#define DI_MACHINECODE_APOLLON_P1		0x002A0000	/* Apollon-P1 group */
#define DI_MACHINECODE_ADONIS_P4		0x002B0000	/* Adonis-P4 group */
#define	DI_MACHINECODE_MARTINI_P2		0x002C0000	/* MARTINI-P2 group */
#define	DI_MACHINECODE_KIR_C3			0x002D0000	/* KIR-C3 group */
#define	DI_MACHINECODE_NEPTUNE_C2		0x002E0000	/* NEPTUNE-C2 group */
#define	DI_MACHINECODE_SEADRAGON_C2		0x002F0000	/* SEADRAGON_C2 group */
#define	DI_MACHINECODE_ADONIS_C4_5		0x00300000	/* ADONIS-C4.5 group */
#define	DI_MACHINECODE_RUSSIAN_C4_5		0x00310000	/* RUSSIAN-C4.5 group */
#define DI_MACHINECODE_STELLA_C3		0x00320000	/* STELLA-C3 group */
#define DI_MACHINECODE_KRISS_P1			0x00330000	/* Kriss-P1 group */
#define DI_MACHINECODE_LUNA_P1			0x00340000	/* Luna-P1 group */
#define DI_MACHINECODE_SINCERE_P1		0x00350000	/* Sincere-P1 group */
#define DI_MACHINECODE_PARISIAN_C1		0x00360000	/* Parisian-C1 group */
#define DI_MACHINECODE_VENUS_C2			0x00370000	/* Venus-C2 group */
#define DI_MACHINECODE_ALEX_C1			0x003A0000	/* Alex-C1 group */
#define DI_MACHINECODE_RUSSIAN_C5		0x003B0000	/* Russian-C5 group */
#define DI_MACHINECODE_NEPTUNE_P1		0x003C0000	/* Neptune-P1 group */
#define DI_MACHINECODE_ATHENA_C2		0x003D0000	/* Athena-C2 group */
#define DI_MACHINECODE_ALEX_P1			0x003E0000	/* Alex-P1 group */
#define DI_MACHINECODE_APOLLON_C2		0x003F0000	/* Apollon-C2 group */
#define DI_MACHINECODE_PEGASUS_C2		0x00400000	/* Pegasus-C2 group */
#define DI_MACHINECODE_BELUGA_C1		0x00410000	/* Beluga-C1 group */
#define DI_MACHINECODE_DIANA_C1			0x00420000	/* Diana-C1 group */
#define DI_MACHINECODE_GAIA_P3			0x00430000	/* Gaia-P3 group */
#define DI_MACHINECODE_APOLLON_P2		0x00440000	/* Apollon-P2 group */
#define DI_MACHINECODE_SINCERE_P2		0x00450000	/* Sincere-P2 group */
#define DI_MACHINECODE_BELLINI_C4		0x00460000	/* Bellini-C4 group */
#define DI_MACHINECODE_MARTINI_C4		0x00470000	/* Martini-C4 group */
#define DI_MACHINECODE_LUNA_P2			0x00480000	/* Luna-P2 group */
#define DI_MACHINECODE_DIANA_C1L		0x00490000	/* Diana-C1L group */
	/**
	 * \brief 機種コード
	 * 値は以下
	 * \li DI_MACHINECODE_ADONIS_C2
	 */
	unsigned long	machinecode;	/**< 機種コード */
	unsigned char	*model;			/* モデル名。"IPSiO CX8200"等 */
	unsigned char	*maker;			/* メーカー */
	unsigned char	*machine_number;/* 機番 */
	di_optinfo_t	option;			/* オプション機器 */
	unsigned long	function;		/* 機能情報(DI_SYS_FUNC_xx) */
	unsigned char	disp_lines;		/* 表示画面のライン数 */
	unsigned char	disp_columns;	/* 表示画面の１ラインの文字数 */
	unsigned char	punch_hole;		/* パンチ可能な穴の情報(DI_SYS_PUNCH_HOLE_xx) */
	unsigned long	total_ram_size;	/* プリンタに搭載されているRAM容量(Byte) */
#define DI_DEST_DOM		0	/* DOM */
#define DI_DEST_NA		1	/* NA */
#define DI_DEST_EU		2	/* EU */
	unsigned char	destination;	/* 仕向け地コード(すぐ上のdefine) */
	unsigned long	memory_size;	/* インタプリタが使用できる */
					/* メモリサイズ(Byte) */
	unsigned char	*ver_printer;			/* プリンタのバージョン */
} di_initinfo_t;

/* BG/UCRテーブル情報構造体 */
typedef struct di_bgucrinfo {
	unsigned char	*bg;	/* BGテーブル */
	unsigned char	*ucr;	/* UCRテーブル */
	unsigned char	*bg_hgr;	/* BGテーブル(高墨用) */
	unsigned char	*ucr_hgr;	/* UCRテーブル(高墨用) */
	unsigned char	*bg_compbk;	/* for composite black */
	unsigned char	*ucr_compbk;
} di_bgucrinfo_t;

/* structure of information of GCR table */
typedef struct di_gcrinfo {
	unsigned long	flag;
	short			*CB_bg;
	short			*CB_ucr;
	short			*CG_bg;
	short			*CG_ucr;
	short			*YG_bg;
	short			*YG_ucr;
	short			*MB_bg;
	short			*MB_ucr;
	short			*MR_bg;
	short			*MR_ucr;
	short			*YR_bg;
	short			*YR_ucr;
} di_gcrinfo_t;

/* 適量テーブル情報構造体 */
typedef struct di_dropinfo {
	unsigned char	*lit;	/* 適量データ */
	unsigned char	*inv;	/* 逆変換テーブル */
} di_dropinfo_t;

/* 両面γ割合情報構造体 */
typedef struct di_dupgaminfo {
	unsigned char	*gam_front;	/* 表面割合[写真,文字,塗り,線画] */
	unsigned char	*gam_back;	/* 裏面割合[写真,文字,塗り,線画] */
} di_dupgaminfo_t;


/* 機種情報構造体 */
typedef struct di_devinfo {
	/*
	 * ディザ情報
	 * 実際の数は
	 *  サポートビット数 x 解像度種類数 x ディザ種類数 x サポート最大プレーン数
	 * となる。各値は機種能力情報。
	 * 配置順は
	 *  for ビット数(値 小 -> 大)
	 *    for 解像度数(主走査+副走査 小 -> 大)
	 *      for ディザ数(photo -> text -> cad -> graphics)
	 *        for プレーン数(K -> C -> M -> Y)
	 *          dither_info
	 * となる
	 */
	di_ditinfo_t	*dither_info;
	di_ditinfo_t	*dither_info_mono;

	/*
	 * ガンマ情報
	 * 数,配置順は dither_info と同様
	 */
	unsigned char	**gamma_info;
	unsigned char	**gamma_info_mono;

	/*
	 * デバイスフォント情報
	 */
	/*
	 * フォントの先頭アドレス
	 */
	unsigned char	*font_address;
	/*
	 * フォントサイズ
	 */
	unsigned long	font_size;
	/* フォント種類 */
#define DI_FONT_RPCS		0	/* RPCS DOM用 */
#define DI_FONT_RPCS_EXP	1	/* RPCS EXP用 */
#define DI_FONT_PS			2	/* PS 欧文 */
#define DI_FONT_PSDOM		3	/* PS 日本語 */
#define DI_FONT_PCL			4	/* PCL用 */
	unsigned char	font_type;

	/*
	 * CMMで使用するプロファイル情報
	 */
	void	*profaddress;
	long	profnumber;

	/*
	 * 機種能力情報
	 */
	unsigned int		resonum;	/* サポート解像度&ビット組み合わせ種類数 */
	di_resolutioninfo_t	*reso_set;	/* 解像度&ビット組合せ */
						/* reso分ある(=reso_set[resonum]) */
	int		ndit;		/* ディザ種類数 */
	int		nplane;		/* サポート最大プレーン数 */
	float	bg_startp;	/* BG が始まる開始レベル */
	float	bg_slant;	/* BG 直線勾配 */
	float	ucr_startp;	/* UCR が始まる開始レベル */
	float	ucr_slant;	/* UCR 直線勾配 */
	int		soft_tsave;	/* ソフトトナーセーブのサポート */
				/* [1:あり, 0:なし] */
	float	tsave_ratio;	/* ソフトトナーセーブ割合(0.0 - 1.0) */
	int		extend_soft_tsave;	/* 拡張ソフトトナーセーブの対応 */
					/* [1:あり, 0:なし] */
	int		toner_limit;	/* 総量規制のサポート */
				/* [1:あり, 0:なし] */
	unsigned int	tlimit_num;	/* 機種がサポートしている総量規制値の種類数 */
	di_tlimitinfo_t	*tlimit_val;/* 総量規制値のバリエーション */
				/* tlimit_num 個ある */
				/* 一番最初がデフォルト値 */
				/* それ以外は特殊モードの値 */
				/* サポートしていなければNULL */

	/*
	 * システム情報
	 */
	char	*shdm_addr;	/* シェアードメモリの先頭アドレス */
	long	sys_handle;	/* システムハンドル */

	/*
	 * 拡張情報
	 */
#define DI_NOTSUPPORT_EXT_DEVINFO_PARAM	0 /* これ以降のメンバが無効 */
#define DI_SUPPORT_EXT_DEVINFO_PARAM	1 /* これ以降のメンバが有効 */
	unsigned long	flag;		/* 各種フラグ */
				/* 1bit目 -- 拡張情報の有効/無効 */

	di_bgucrinfo_t	**bgucr_info;	/* BG/UCR(テーブル) */

	di_gcrinfo_t	*gcr_info;	/* WiShGCR */

	di_gcrinfo_t	*gcrhgr_info;	/* WiShGCR(高墨用) */

	di_dropinfo_t	**drop_info;	/* 適量テーブル */

	di_dupgaminfo_t	**dupgam_info;	/* 両面γ割合 */

	int	support_drop;	/* 適量のサポート */
				/* [1:あり, 0:なし] */
	int		cmy_media_num;	/* CMY印刷をする紙種の数 */
	unsigned char	*cmy_media;	/* CMY印刷をする紙種の配列 */
	int		minbandheight;
	int		maxbandheight;
	int		bandsize;
} dev_info_t, di_devinfo_t;

/*
 * 以降はdi_init()でユーザがDIに渡すパラメータ
 */

/* 非同期にDI内部で更新されるパラメータ */
typedef struct di_async_para {
	/*
	 * ジョブリセット情報
	 * システムからジョブリセット要求があった場合に更新される
	 * [0: リセットされていない, 非0: リセットされた]
	 */
	int	jobreset;
	/*
	 * 自言語外かどうか
	 * 言語の境界で更新される
	 * [0: 言語内, 非0: 言語外]
	 */
	int	not_joblang;
	/*
	 * ジョブID
	 * システムから印刷要求があった場合に更新される
	 */
	int	job_id;
	/*
	 * テストプリントが要求されたか [0: されていない, 非0: された]
	 * テストプリント要求があった場合に更新される。
	 * di_notify_msg(DI_NOTIFYMSG_JOBEND)でクリア(=0)される。
	 * テストプリント機能をサポートしている環境のみ必要。
	 */
	int	testprint;
	/*
	 * ネットジョブID
	 * システムから印刷要求があった場合に更新される
	 */
	int	njob_id;
	/*
	 * チャネル番号
	 * システムから印刷要求があった時に更新される
	 * 値は DI_CHANNEL_xxx
	 */
	int	host_channel;
	/*
	 * PDL ID
	 * システムから印刷要求があった時に更新される
	 * 値は DI_PDL_xxx
	 */
	int	pdl_id;
	/*
	 * プロセスID
	 * システムから印刷要求があった時に更新される
	 */
	long	pid;
	/*
	 * プログラム番号 
	 * システムからプログラム登録/削除要求があった時に更新される（MSIS系PDL専用）
	 * 値のクリアはユーザが明示的に行ってください
	 */
	int	pno;
	/*
	 * システムからプライムリセット要求があった時に非０に更新される（MSIS系PDL専用）
	 * 値のクリアはユーザが明示的に行ってください
	 */
	int	prime_reset;
	/*
	 * ユーザスイッチ番号
	 * システムから印刷要求があった時に更新される（MSIS系PDL専用）
	 */
	int		uswitch;
	/*
	 * データ処理開始理由
	 * システムから印刷要求があった時に更新される（MSIS系PDL専用）
	 */
	int		reason;
	unsigned char	filepath[DI_INTERP_LEN_TESTPRINT_PATH];
} async_para_t, di_async_para_t;

typedef struct di_setinfo {
	/*
	 * 非同期に変化するパラメータ
	 * 現状GPS上の動作でのみ有効
	 */
	di_async_para_t	*async;
	/*
	 * DIがストリームから読み込んだバイト数。
	 * di_singet(c) or di_sinseek をコールするたびに自動的に更新される。
	 * DEBUGをdefineしてコンパイルした場合のみ有効
	 */
	int	cmd_offset;
	/*
	 * インタプリタID(値は以下のdefine)
	 */
#define DI_INTERP_RPCS			0x0000	/* RPCS */
#define DI_INTERP_XHTML			0x0010	/* XHTML */
#define DI_INTERP_EXIF			0x0100	/* EXIF */
#define DI_INTERP_BMLINKS		0x0101	/* BMLinkS */
#define DI_INTERP_PS			0x1000	/* PS */
#define DI_INTERP_PCL			0x1001	/* PCL */

#define DI_INTERP_RPDL			0x10000	/* RPDL */
#define DI_INTERP_R98			0x10001	/* R98 */
#define DI_INTERP_R16			0x10010	/* R16 */
#define DI_INTERP_R55			0x10011	/* R55 */
#define DI_INTERP_RPGL2			0x10100	/* RPGL2 */
#define DI_INTERP_RTIFF			0x10101	/* RTIFF */
#define DI_INTERP_RPGL2c		0x10110	/* RPGL2c */
#define DI_INTERP_PICTBRIDGE	0x0110	/* PictBridge */
#define DI_INTERP_XPS			0x0111	/* XPS */
#define DI_INTERP_MP_TIFF		0x11000	/* MediaPrintTIFF */
#define DI_INTERP_MP_JPEG		0x11001	/* MediaPrintJPEG */
	 int	interp_id;
	/*
	 * システム初期化のためのオプションパラメータ(-1で未使用)
	 * interp_id によって意味が変化する
	 * DI_INTERP_RPCS	起動理由通知
	 * その他			未使用
	 */
	long	option;
} di_setinfo_t;

/* ユーザージョブ変数構造体 */
typedef struct ujobparam_var {
	unsigned long	flag;
/* di_ujob_info_tにマクロ定義がある */
} ujobparam_var_t;

typedef struct di_onebininfo {
	unsigned short	id;		/* 排紙ビンのID */
#define DI_BIN_STAPLER            (1 << 0)        /* ステープル可 */
#define DI_BIN_PUNCH              (1 << 1)        /* パンチ可 */
#define DI_BIN_SHIFT              (1 << 2)        /* シフト排紙可 */
#define DI_BIN_PAPER_SENSE        (1 << 3)        /* sense paper exist */
#define DI_BIN_FULL_SENSE         (1 << 4)        /* sense paper full */
#define DI_BIN_NODUPLEX           (1 << 5)        /* noduplex */
#define DI_BIN_SADDLE             (1 << 6)        /* saddle */
#define DI_BIN_FOLD               (1 << 7)        /* 折り機能 */
	unsigned long	attr;	/* 排紙ビンの種類 */
#define DI_BIN_FULL               (1 << 0)        /* 満杯 */
#define DI_BIN_ERROR              (1 << 1)        /* 故障状態 */
#define DI_BIN_STOPEXIT           (1 << 2)        /* 排紙抑制 */
#define DI_BIN_SADDLE_DISABLE     (1 << 3)        /* 中綴じ排紙禁止 */
#define DI_BIN_NORMAL_DISABLE     (1 << 4)        /* 中綴じ以外の排紙禁止 */
	unsigned long	status;	/* ステータス */
} di_onebininfo_t;

#define DI_MAX_BIN_NUM 32

typedef struct di_bininfo {
	long			bin_num;					/* 排紙ビンの数 */
	di_onebininfo_t	bininfo[DI_MAX_BIN_NUM];	/* 各ビンの情報 */
} di_bininfo_t;

typedef struct di_filectrl {
	int	ope;
	char	Fontfilename[DI_PATHMAX];
	char	Tempfilename[DI_PATHMAX];
	int	fd;
} di_filectrl_t;

typedef struct di_rotenvinfo {
#define	DI_CHKDIR_STAPLE     (1<<0)	    /* stapleパラメータ指定 */
#define DI_CHKDIR_PUNCH      (1<<1)	    /* punchパラメータ指定 */
#define DI_CHKDIR_BINDING    (1<<2)	    /* bindingパラメータ指定 */
#define DI_CHKDIR_RESOLUTION (1<<3)	    /* reso_xとreso_yパラメータ指定 */
#define DI_CHKDIR_DEPTH      (1<<5)	    /* depthパラメータ指定 */
	unsigned long		flag;			/* 設定するパラメータ */
	int					psize;			/* 用紙サイズ（必須） */
	unsigned long		pwidth;			/* 用紙幅（0.1mm単位） */
	unsigned long		plength;		/* 用紙長（0.1mm単位） */
#define DI_ORIENTATION_PORTRAIT  (1<<0)	/* Portrait */
#define DI_ORIENTATION_LANDSCAPE (1<<1)	/* Landscape */
	unsigned char		orientation;	/* オリエンテーション */
#define DI_STAPLE_OFF              (0)  /* なし */
#define DI_STAPLE_LEFT_TOP_HORIZ   (1)  /* 使用は推奨しない */
#define DI_STAPLE_LEFT_TOP_VERT    (2)  /* 使用は推奨しない */
#define DI_STAPLE_LEFT_TOP_SLANT   (3)  /* 左上斜め */
#define DI_STAPLE_RIGHT_TOP_HORIZ  (5)  /* 使用は推奨しない */
#define DI_STAPLE_RIGHT_TOP_VERT   (6)  /* 使用は推奨しない */
#define DI_STAPLE_RIGHT_TOP_SLANT  (7)  /* 右上斜め */
#define DI_STAPLE_DOUBLE_LEFT      (9)  /* 左側２個所 */
#define DI_STAPLE_DOUBLE_TOP       (10) /* 上側２個所 */
#define DI_STAPLE_DOUBLE_RIGHT     (11) /* 右側２個所 */
#define DI_STAPLE_BOOKLET          (12) /* 真中２個所 */
#define DI_STAPLE_LEFT_TOP         (16) /* 左上 */
#define DI_STAPLE_RIGHT_TOP        (17) /* 右上 */
	unsigned char		staple;			/* ステープル */
#define DI_PUNCH_OFF   (0)              /* なし */
#define DI_PUNCH_LEFT  (1)              /* 左辺 */
#define DI_PUNCH_TOP   (2)              /* 上辺 */
#define DI_PUNCH_RIGHT (3)              /* 右辺 */
#define DI_PUNCH_JP2   (0x00)           /* 上位のパンチ種類の指定はあってもなくても良い */
#define DI_PUNCH_US2   (0x10)
#define DI_PUNCH_US3   (0x20)
#define DI_PUNCH_EU4   (0x30)
#define DI_PUNCH_NEU4  (0x40)
	unsigned char		punch;			/* パンチ */
#define DI_BIND_LEFT      (0)           /* 左綴じ */
#define DI_BIND_TOP       (1)           /* 上綴じ */
#define DI_BIND_RIGHT     (2)           /* 右綴じ */
#define DI_BIND_BOTTOM    (3)           /* 下綴じ(未使用) */
#define DI_BIND_LEFTRIGHT (4)           /* 左右綴じ(RTIFF) */
#define DI_BIND_TOPBOTTOM (5)           /* 上下綴じ(RTIFF) */
#define DI_BIND_OFF       (0xF)         /* 指定なし(gpsPlotChkDirection()用) */
	unsigned char		binding;		/* とじ方向 */
	unsigned short		reso_x;			/* X方向の解像度 */
	unsigned short		reso_y;			/* Y方向の解像度 */
#define DI_DEPTH_2        (1)           /* ２値(1bit) */
#define DI_DEPTH_4        (2)           /* ４値(2bit) */
unsigned char		depth;			    /* 階調 */
} di_rotenvinfo_t;

typedef struct di_imgrotinfo {
#define DI_ROT_0B    (1<<0) /* ０度 */
#define DI_ROT_90B   (1<<1) /* ９０度 */
#define DI_ROT_180B  (1<<2) /* １８０度 */
#define DI_ROT_270B  (1<<3) /* ２７０度 */
#define DI_ROT_ALL   (DI_ROT_0B|DI_ROT_90B|DI_ROT_180B|DI_ROT_270B) /* 回転処理不必要 */
#define DI_ROT_NG    (0x80) /* 回転処理不可 */
#define DI_ROT_ERROR (0)    /* エラー (通紙不可など) */

	int direction;	    	/* 画像方向 */
#define DI_ROT_0B    (1<<0)	/* ０度 */
#define DI_ROT_90B   (1<<1)	/* ９０度 */
#define DI_ROT_180B  (1<<2)	/* １８０度 */
#define DI_ROT_270B  (1<<3)	/* ２７０度 */
#define DI_ROT_ERROR (0)	/* 斜めステープル出来ない、又はパラメータ無効（ステープル指定していない場合など） */
	int slantdirection;		/* 斜めステープルができる画像方向 */
} di_imgrotinfo_t;

/* カラープロファイル情報 */
/* GPSの構造体 gps_color_profile_infoと同じ型 */
#define	DI_MAX_CPF_PATH_LEN		96
#define	DI_MAX_CPF_ATTR_LEN		27

typedef struct di_color_profile_info {
	unsigned long		key;	/* profile ID */
	unsigned char		media;	/* profile in media */
	unsigned char		attr[DI_MAX_CPF_ATTR_LEN];	/* 属性 */
	char			path[DI_MAX_CPF_PATH_LEN];	/* パス名 */
} di_color_profile_info_t;

/* プログラムテーブル */
typedef struct di_progtable {
	unsigned char eml_name[3];	/* エミュレーション名 */
	unsigned char file_no;	/*エミュレーション単位で管理されているプログラム番号。NVRAMファイルのファイル番号に対応する。 */
} di_progtable_t;

#define	DI_AUTH_LIMIT_ADMINMACHINE	(1 << 0)		/* 機器管理者機能 	*/
#define	DI_AUTH_LIMIT_ADMINUSER		(1 << 1)		/* ユーザー管理者機能 */
#define	DI_AUTH_LIMIT_ADMINDOCUMENT	(1 << 2)		/* 文書管理者機能 	*/
#define	DI_AUTH_LIMIT_ADMINNETWORK	(1 << 3)		/* ネットワーク管理者機能 */
#define	DI_AUTH_LIMIT_CERUSER		(1 << 4)		/* 認証ユーザ機能 	*/
#define	DI_AUTH_LIMIT_SUPERVISOR      	(1 << 5)		/* スーパーバイザー機能 */
#define	DI_AUTH_LIMIT_SERVICE		(1 << 6)		/* サービス機能 	*/
#define DI_ALL_FUNCTION_LIMIT		0xffffffff		/* 全機能制限 */

/*
	NVRAM FILE ACCESS
*/
#define DI_AUTHORIZED		 0
#define DI_AUTH_LIMITED		-1
#define DI_AUTH_NOT_NOTIFY	-2

/* flag to check paper size and kind for di_query_duplex() */
#define DI_DUPLEX_CHK_SIZE	(1 << 0)
#define DI_DUPLEX_CHK_KIND	(1 << 1)

typedef struct di_chkduplexok {
	unsigned long	flag;		/* check flag */
	unsigned long	pwidth;		/* the width of free size paper (0.1mm) */
	unsigned long	plength;	/* the height of free size paper (0.1mm) */
	unsigned char	psize;		/* size of paper */
	unsigned char	pkind;		/* kind of paper */
	unsigned char	reserved[18];	/* reserved parameter for new function */
} di_chkduplexok_t;

typedef struct di_trayrequest {
	unsigned long		flag;
#define DI_TRAYREQFLAG_ALL			(0xFFFFFFFF)
#define DI_TRAYREQFLAG_PWIDTH		(1<<0)
#define DI_TRAYREQFLAG_PLENGTH		(1<<1)
#define DI_TRAYREQFLAG_MODE			(1<<2)
	unsigned long		pwidth;
	unsigned long		plength;
	unsigned char		mode:1;
#define	DI_REQ_MODE1				(0)
#define	DI_REQ_MODE2				(1)
	unsigned char		res1:7;
	unsigned char		res2[31];

} di_trayrequest_t; 

typedef struct di_res_reqtray {
	int result;
	int tray_id;
	int paper_code;
	unsigned long paper_width;
	unsigned long paper_length;
} di_res_reqtray_t;

typedef struct di_printcondition {
	unsigned int job_type;
#define DI_PCND_SDK_THUMBNAILJOB	4
#define DI_PCND_SDK_PRINTJOB		3
#define DI_PCND_THUMBNAILJOB		2
#define DI_PCND_MEDIAPRINTJOB		1
#define DI_PCND_PRINTJOB			0
	unsigned long chg_paper_kind;
#define DI_PCND_CHG_PAPERKIND_EXIST	(1 << 0)
	unsigned int paper_kind;
	unsigned long duplex;
#define DI_PCND_DUPLEX_OFF		(1 << 0)
#define DI_PCND_DUPLEX_LEFT		(1 << 1)
#define DI_PCND_DUPLEX_TOP		(1 << 3)
	unsigned long tonersave_color;
#define DI_PCND_TONERSAVE_COLOR_OFF		(1 << 0)
#define DI_PCND_TONERSAVE_COLOR_ON		(1 << 1)
	unsigned long nup;
#define DI_PCND_NUP_OFF			(1 << 0)
#define DI_PCND_NUP_2IN1		(1 << 1)
#define DI_PCND_NUP_4IN1		(1 << 2)
#define DI_PCND_NUP_6IN1		(1 << 3)
#define DI_PCND_NUP_8IN1		(1 << 4)
#define DI_PCND_NUP_9IN1		(1 << 5)
#define DI_PCND_NUP_16IN1		(1 << 6)
	unsigned long nup_option;
#define DI_PCND_NUPPAGEORDER_RIGHTTHENDOWN		(1 << 0)
#define DI_PCND_NUPPAGEORDER_LEFTTHENDOWN		(1 << 1)
#define DI_PCND_NUPPAGEORDER_DOWNTHENRIGHT		(1 << 2)
#define DI_PCND_NUPPAGEORDER_DOWNTHENLEFT		(1 << 3)
	unsigned long nup_border;
#define DI_PCND_NUPBORDER_OFF	(1 << 0)
#define DI_PCND_NUPBORDER_ON	(1 << 1)
	unsigned long colormode;
#define DI_PCND_COLORMODE_MONO	(1 << 0)
#define DI_PCND_COLORMODE_COLOR	(1 << 1)
	unsigned long inputtray;
#define DI_PCND_INPUTTRAY_AUTO	(1 << 0)
#define DI_PCND_INPUTTRAY_1		(1 << 1)
#define DI_PCND_INPUTTRAY_2		(1 << 2)
#define DI_PCND_INPUTTRAY_3		(1 << 3)
#define DI_PCND_INPUTTRAY_4		(1 << 4)
#define DI_PCND_INPUTTRAY_5		(1 << 5)
#define DI_PCND_INPUTTRAY_6		(1 << 6)
#define DI_PCND_INPUTTRAY_7		(1 << 7)
#define DI_PCND_INPUTTRAY_LCT	(1 << 30)
#define DI_PCND_INPUTTRAY_MAN	(1 << 31)
	unsigned long staple;
#define DI_PCND_STAPLE_OFF				(1 << 0)
#define DI_PCND_STAPLE_LEFTTOP			(1 << 1)
#define DI_PCND_STAPLE_RIGHTTOP			(1 << 2)
#define DI_PCND_STAPLE_LEFTTOPSLANT		(1 << 3)
#define DI_PCND_STAPLE_RIGHTTOPSLANT	(1 << 4)
#define DI_PCND_STAPLE_LEFT2			(1 << 5)
#define DI_PCND_STAPLE_TOP2				(1 << 6)
#define DI_PCND_STAPLE_RIGHT2			(1 << 7)
#define DI_PCND_STAPLE_BOOKLET			(1 << 8)
	unsigned long punch;
#define DI_PCND_PUNCH_OFF			(1 << 0)
#define DI_PCND_PUNCH_LEFT2			(1 << 1)
#define DI_PCND_PUNCH_TOP2			(1 << 2)
#define DI_PCND_PUNCH_RIGHT2		(1 << 3)
#define DI_PCND_PUNCH_LEFT3			(1 << 4)
#define DI_PCND_PUNCH_TOP3			(1 << 5)
#define DI_PCND_PUNCH_RIGHT3		(1 << 6)
#define DI_PCND_PUNCH_LEFT4			(1 << 7)
#define DI_PCND_PUNCH_TOP4			(1 << 8)
#define DI_PCND_PUNCH_RIGHT4		(1 << 9)
#define DI_PCND_PUNCH_LEFTGBC		(1 << 10)
#define DI_PCND_PUNCH_TOPGBC		(1 << 11)
#define DI_PCND_PUNCH_RIGHTGBC		(1 << 12)
#define DI_PCND_PUNCH_LEFTTOP		(1 << 13)
} di_printcondition_t;

typedef struct di_printcondition2 {
#define DI_PDF_PASSWORD_LEN			36
	unsigned char pdfpassword[DI_PDF_PASSWORD_LEN];
	unsigned long reserve[16];
} di_printcondition2_t;

typedef struct di_media_printcondition {
	unsigned long bind;
#define DI_PCND_MEDIA_BIND_OFF				(1 << 0)
#define DI_PCND_MEDIA_BIND_MAGAZIGE_LEFT	(1 << 1)
#define DI_PCND_MEDIA_BIND_MAGAZIGE_RIGHT	(1 << 2)
	struct {
			unsigned long magnification;
#define DI_PCND_MEDIA_MAG_OFF		(1 << 0)
#define DI_PCND_MEDIA_MAG_ON		(1 << 1)
			unsigned int size_code;
			unsigned long paper_width;
			unsigned long paper_length;
	} paper_size;
	struct {
			unsigned long tiff;
#define DI_PCND_MEDIA_RESOL_TIFF_200		(1 << 0)
#define DI_PCND_MEDIA_RESOL_TIFF_300		(1 << 1)
#define DI_PCND_MEDIA_RESOL_TIFF_400		(1 << 2)
#define DI_PCND_MEDIA_RESOL_TIFF_600		(1 << 3)
			unsigned long pdf;
#define DI_PCND_MEDIA_RESOL_PDF_600_FAST	(1 << 0)
#define DI_PCND_MEDIA_RESOL_PDF_600_STD		(1 << 1)
#define DI_PCND_MEDIA_RESOL_PDF_600_HIGH	(1 << 2)
#define DI_PCND_MEDIA_RESOL_PDF_1200		(1 << 3)
#define DI_PCND_MEDIA_RESOL_PDF_300			(1 << 4)
#define DI_PCND_MEDIA_RESOL_PDF_1200_2		(1 << 5)
	} resolution;
	unsigned long printquality;
#define DI_PCND_MEDIA_PRTQUAL_NORMAL		(1 << 0)
#define DI_PCND_MEDIA_PRTQUAL_DRAFT			(1 << 1)
#define DI_PCND_MEDIA_PRTQUAL_FINE			(1 << 2)
	unsigned long reserve1;
	unsigned long reserve2;
	unsigned long reserve3;
} di_media_printcondition_t;

typedef struct di_sdk_printcondition {
#define DI_PDL_PAGES_LEN		229
	unsigned char printpages[DI_PDL_PAGES_LEN];
	unsigned long forced_duplex;
#define DI_PCND_SDK_FORCEDDUPLEX_LEFT		(1 << 1)
#define DI_PCND_SDK_FORCEDDUPLEX_TOP		(1 << 3)
	unsigned long duplex;
#define DI_PCND_SDK_DUPLEX_OFF			(1 << 0)
#define DI_PCND_SDK_DUPLEX_LEFT			(1 << 1)
#define DI_PCND_SDK_DUPLEX_TOP			(1 << 3)
	unsigned long forced_colormode;
	unsigned long colormode;
#define DI_PCND_SDK_COLORMODE_MONO		(1 << 0)
#define DI_PCND_SDK_COLORMODE_COLOR		(1 << 1)
	unsigned long tonersave_color;
#define DI_PCND_SDK_TONERSAVE_OFF		(1 << 0)
#define DI_PCND_SDK_TONERSAVE_ON		(1 << 1)
	unsigned long tonersave_mono;
#define DI_PCND_SDK_TONERSAVE_MONO_OFF	(1 << 0)
#define DI_PCND_SDK_TONERSAVE_MONO_ON	(1 << 1)
	unsigned int print_num;
	unsigned int chg_paper_kind;
#define DI_PCND_SDK_CHG_PAPERKIND_EXIST	(1 << 0)
	unsigned int paper_kind;
	unsigned long nup;
#define DI_PCND_SDK_NUP_OFF				(1 << 0)
#define DI_PCND_SDK_NUP_2IN1			(1 << 1)
#define DI_PCND_SDK_NUP_4IN1			(1 << 2)
#define DI_PCND_SDK_NUP_6IN1			(1 << 3)
#define DI_PCND_SDK_NUP_8IN1			(1 << 4)
#define DI_PCND_SDK_NUP_9IN1			(1 << 5)
#define DI_PCND_SDK_NUP_16IN1			(1 << 6)
	unsigned long nup_option;
#define DI_PCND_SDK_NUPOPT_PAGEORDER_RIGHT_THEN_DOWN	(1 << 0)
#define DI_PCND_SDK_NUPOPT_PAGEORDER_LEFT_THEN_DOWN		(1 << 1)
#define DI_PCND_SDK_NUPOPT_PAGEORDER_DOWN_THEN_RIGHT	(1 << 2)
#define DI_PCND_SDK_NUPOPT_PAGEORDER_DOWN_THEN_LEFT		(1 << 3)
	unsigned long nup_border;
#define DI_PCND_SDK_NUP_BORDER_OFF		(1 << 0)
#define DI_PCND_SDK_NUP_BORDER_ON		(1 << 1)
#define DI_SDK_PDF_PASSWORD_LEN			(36)
	unsigned char pdfpassword[DI_SDK_PDF_PASSWORD_LEN];
	unsigned long inputtray;
#define DI_PCND_SDK_INPUTTRAY_AUTO		(1 << 0)
#define DI_PCND_SDK_INPUTTRAY_1			(1 << 1)
#define DI_PCND_SDK_INPUTTRAY_2			(1 << 2)
#define DI_PCND_SDK_INPUTTRAY_3			(1 << 3)
#define DI_PCND_SDK_INPUTTRAY_4			(1 << 4)
#define DI_PCND_SDK_INPUTTRAY_5			(1 << 5)
#define DI_PCND_SDK_INPUTTRAY_6			(1 << 6)
#define DI_PCND_SDK_INPUTTRAY_7			(1 << 7)
#define DI_PCND_SDK_INPUTTRAY_LCT		(1 << 30)
#define DI_PCND_SDK_INPUTTRAY_MAN		(1 << 31)
	 unsigned long sort;
#define DI_PCND_SDK_SORT_NORMAL			(1 << 0)
#define DI_PCND_SDK_SORT_ROTATE			(1 << 1)
#define DI_PCND_SDK_SORT_SHIFT			(1 << 2)
	unsigned long stack;
#define DI_PCND_SDK_STACK				(1 << 0)
	unsigned long staple;
#define DI_PCND_SDK_STAPLE_OFF				(1 << 0)
#define DI_PCND_SDK_STAPLE_LEFTTOP			(1 << 1)
#define DI_PCND_SDK_STAPLE_RIGHTTOP			(1 << 2)
#define DI_PCND_SDK_STAPLE_LEFTTOPSLANT		(1 << 3)
#define DI_PCND_SDK_STAPLE_RIGHTTOPSLANT	(1 << 4)
#define DI_PCND_SDK_STAPLE_LEFT2			(1 << 5)
#define DI_PCND_SDK_STAPLE_TOP2				(1 << 6)
#define DI_PCND_SDK_STAPLE_RIGHT2			(1 << 7)
#define DI_PCND_SDK_STAPLE_BOOKLET			(1 << 8)
	unsigned long punch;
#define DI_PCND_SDK_PUNCH_OFF			(1 << 0)
#define DI_PCND_SDK_PUNCH_LEFT2			(1 << 1)
#define DI_PCND_SDK_PUNCH_TOP2			(1 << 2)
#define DI_PCND_SDK_PUNCH_RIGHT2		(1 << 3)
#define DI_PCND_SDK_PUNCH_LEFT3			(1 << 4)
#define DI_PCND_SDK_PUNCH_TOP3			(1 << 5)
#define DI_PCND_SDK_PUNCH_RIGHT3		(1 << 6)
#define DI_PCND_SDK_PUNCH_LEFT4			(1 << 7)
#define DI_PCND_SDK_PUNCH_TOP4			(1 << 8)
#define DI_PCND_SDK_PUNCH_RIGHT4		(1 << 9)
#define DI_PCND_SDK_PUNCH_LEFTGBC		(1 << 10)
#define DI_PCND_SDK_PUNCH_TOPGBC		(1 << 11)
#define DI_PCND_SDK_PUNCH_RIGHTGBC		(1 << 12)
#define DI_PCND_SDK_PUNCH_LEFTTOP		(1 << 13)
	unsigned long bind;
#define DI_PCND_SDK_BIND_OFF			(1 << 0)
#define DI_PCND_SDK_BIND_MAGAZINE_LEFT	(1 << 1)
#define DI_PCND_SDK_BIND_MAGAZINE_RIGHT	(1 << 2)
	struct {
		unsigned long magnification;
#define DI_PCND_SDK_MAG_OFF				(1 << 0)
#define DI_PCND_SDK_MAG_ON				(1 << 1)
		unsigned int  size_code;
		unsigned long paper_width;
		unsigned long paper_length;
	} paper_size;
	struct {
		unsigned long pdf;
#define DI_PCND_SDK_RESOL_PDF_600_FAST	(1 << 0)
#define DI_PCND_SDK_RESOL_PDF_600_STD	(1 << 1)
#define DI_PCND_SDK_RESOL_PDF_600_HIGH	(1 << 2)
#define DI_PCND_SDK_RESOL_PDF_1200		(1 << 3)
#define DI_PCND_SDK_RESOL_PDF_300		(1 << 4)
#define DI_PCND_SDK_RESOL_PDF_1200_2	(1 << 5)
	} resolution;
	unsigned long reserve[13];
} di_sdk_printcondition_t;

typedef struct di_sys2_printcondition {
	unsigned long inputtray;
#define DI_PCND_SYS2_INPUTTRAY_AUTO	(1 << 0)
#define DI_PCND_SYS2_INPUTTRAY_1	(1 << 1)
#define DI_PCND_SYS2_INPUTTRAY_2	(1 << 2)
#define DI_PCND_SYS2_INPUTTRAY_3	(1 << 3)
#define DI_PCND_SYS2_INPUTTRAY_4	(1 << 4)
#define DI_PCND_SYS2_INPUTTRAY_5	(1 << 5)
#define DI_PCND_SYS2_INPUTTRAY_6	(1 << 6)
#define DI_PCND_SYS2_INPUTTRAY_7	(1 << 7)
#define DI_PCND_SYS2_INPUTTRAY_LCT	(1 << 30)
#define DI_PCND_SYS2_INPUTTRAY_MAN	(1 << 31)
	unsigned long duplex;
#define DI_PCND_SYS2_DUPLEX_OFF		(1 << 0)
#define DI_PCND_SYS2_DUPLEX_LEFT	(1 << 1)
#define DI_PCND_SYS2_DUPLEX_TOP		(1 << 3)
	unsigned long sort;
#define DI_PCND_SYS2_SORT_NORMAL	(1 << 0)
#define DI_PCND_SYS2_SORT_ROTATE	(1 << 1)
#define DI_PCND_SYS2_SORT_SHIFT		(1 << 2)
	unsigned long stack;
#define DI_PCND_SYS2_STACK			(1 << 0)
	unsigned long staple;
#define DI_PCND_SYS2_STAPLE_OFF				(1 << 0)
#define DI_PCND_SYS2_STAPLE_LEFTTOP			(1 << 1)
#define DI_PCND_SYS2_STAPLE_RIGHTTOP		(1 << 2)
#define DI_PCND_SYS2_STAPLE_LEFTTOPSLANT	(1 << 3)
#define DI_PCND_SYS2_STAPLE_RIGHTTOPSLANT	(1 << 4)
#define DI_PCND_SYS2_STAPLE_LEFT2			(1 << 5)
#define DI_PCND_SYS2_STAPLE_TOP2			(1 << 6)
#define DI_PCND_SYS2_STAPLE_RIGHT2			(1 << 7)
#define DI_PCND_SYS2_STAPLE_BOOKLET			(1 << 8)
	unsigned long punch;
#define DI_PCND_SYS2_PUNCH_OFF		(1 << 0)
#define DI_PCND_SYS2_PUNCH_LEFT2	(1 << 1)
#define DI_PCND_SYS2_PUNCH_TOP2		(1 << 2)
#define DI_PCND_SYS2_PUNCH_RIGHT2	(1 << 3)
#define DI_PCND_SYS2_PUNCH_LEFT3	(1 << 4)
#define DI_PCND_SYS2_PUNCH_TOP3		(1 << 5)
#define DI_PCND_SYS2_PUNCH_RIGHT3	(1 << 6)
#define DI_PCND_SYS2_PUNCH_LEFT4	(1 << 7)
#define DI_PCND_SYS2_PUNCH_TOP4		(1 << 8)
#define DI_PCND_SYS2_PUNCH_RIGHT4	(1 << 9)
#define DI_PCND_SYS2_PUNCH_LEFTGBC	(1 << 10)
#define DI_PCND_SYS2_PUNCH_TOPGBC	(1 << 11)
#define DI_PCND_SYS2_PUNCH_RIGHTGBC	(1 << 12)
#define DI_PCND_SYS2_PUNCH_LEFTTOP	(1 << 13)
	unsigned int qty;
	unsigned long tonersave_mono;
#define DI_PCND_SYS2_TONERSAVE_MONO_OFF		(1 << 0)
#define DI_PCND_SYS2_TONERSAVE_MONO_ON		(1 << 1)
	unsigned long upsidedown;
#define DI_PCND_SYS2_UPSIDEDOWN_OFF	(1 << 0)
#define DI_PCND_SYS2_UPSIDEDOWN_ON	(1 << 1)
	unsigned long reserve1;
	unsigned long mode;
#define DI_PCND_SYS2_MODE_FORCERIP	(1 << 0)
} di_sys2_printcondition_t;

typedef struct di_printconditionShm {
	unsigned int job_type;
	unsigned long change;
#define DI_PCND_CHG_PDL			(1 << 0)
#define DI_PCND_CHG_PDL2		(1 << 1)
#define DI_PCND_CHG_MEDIA		(1 << 2)
#define DI_PCND_CHG_SDK			(1 << 3)
#define DI_PCND_CHG_SYS			(1 << 4)
	di_printcondition_t	pdl;
	di_printcondition2_t pdl2;
	di_media_printcondition_t media;
	di_sdk_printcondition_t sdk;
	di_sys2_printcondition_t sys;
} di_printconditionShm_t;

typedef struct {
	unsigned long support_flag;
	unsigned long forced_flag;
#define DI_PARAM_PRINTERMARKINGTYPE			(1 << 0)
#define DI_PARAM_UCPMASKTYPE				(1 << 1)
#define DI_PARAM_UCPPATTERNCOLOR			(1 << 2)
#define DI_PARAM_UCPPATTERNDENSITY			(1 << 3)
#define DI_PARAM_UCPEFFECTCOPYGUARD			(1 << 4)
#define DI_PARAM_UCPUCPEFFECTCOPYINHIBITION	(1 << 5)
#define DI_PARAM_UCPSTRPOSITION				(1 << 6)
#define DI_PARAM_UCPSTRREPEATPRINT			(1 << 7)
#define DI_PARAM_UCPFONTNUMBER				(1 << 8)
#define DI_PARAM_UCPFONTSIZE				(1 << 9)
#define DI_PARAM_UCPLINESPACE				(1 << 10)
#define DI_PARAM_UCPSTRANGLE				(1 << 11)
#define DI_PARAM_UCPSTRING					(1 << 12)
#define DI_PARAM_UCPFONTTYPE				(1 << 13)
#define DI_PARAM_UCPFONTNUMBER2				(1 << 14)
#define DI_PARAM_UCPPATTERNCOLOR2			(1 << 15)
	unsigned char printermarkingtype;
	unsigned char ucpmasktype;
	unsigned char ucppatterncolor;
	unsigned char ucppatterndensity;
	unsigned char ucpeffectcopyguard;
	unsigned char ucpeffectcopyinhibition;
	unsigned char ucpstrposition;
	unsigned char ucpstrrepeatprint;
	unsigned char ucpfontnumber;
	unsigned char ucpstring_charcode;
	unsigned char ucpstring_default_charcode;
#define DI_UCP_CHAR_CODE_NONE		0	
#define DI_UCP_CHAR_CODE_SJIS		1
#define DI_UCP_CHAR_CODE_EUSTD		2
#define DI_UCP_CHAR_CODE_CE			3
#define DI_UCP_CHAR_CODE_GREEK		4
#define DI_UCP_CHAR_CODE_CYR		5
#define DI_UCP_CHAR_CODE_TUR		6
#define DI_UCP_CHAR_CODE_BALTIC		7
#define DI_UCP_CHAR_CODE_GB			8
#define DI_UCP_CHAR_CODE_BIG		9
#define DI_UCP_CHAR_CODE_HEBREW		10
#define DI_UCP_CHAR_CODE_ARABIC		11
#define DI_UCP_CHAR_CODE_THAI		12
#define DI_UCP_CHAR_CODE_KS			13
	unsigned short ucpfontsize;
	unsigned short ucplinespace;
	unsigned short ucpstrangle;
#define DI_MAX_UCPSTRING_LEN				64
	unsigned char ucpstring[DI_MAX_UCPSTRING_LEN + 1];
	unsigned char ucpstring_default[DI_MAX_UCPSTRING_LEN + 1];
#define DI_MAX_UCPFONTTYPE_LEN				210
	unsigned char ucpfonttype[DI_MAX_UCPFONTTYPE_LEN + 1];
	unsigned char ucpfontnumber2;
	unsigned char ucppatterncolor2;
} di_ucp_param_t;

enum {
	DI_STRING_DOT_DENSITY1,
	DI_STRING_DOT_DENSITY2,
	DI_STRING_DOT_DENSITY3,
	DI_STRING_DOT_DENSITY4,
	DI_STRING_DOT_DENSITY5,
	DI_BACKGROUND_DOT_DENSITY1,
	DI_BACKGROUND_DOT_DENSITY2,
	DI_BACKGROUND_DOT_DENSITY3,
	DI_BACKGROUND_DOT_DENSITY4,
	DI_BACKGROUND_DOT_DENSITY5,
	DI_MASKTYPE_AMIME,
	DI_MASKTYPE_HIGAKI,
	DI_MASKTYPE_KIKKOU,
	DI_MASKTYPE_KOUSHI1,
	DI_MASKTYPE_KOUSHI2,
	DI_MASKTYPE_MATSUKAWABISHI,
	DI_MASKTYPE_SEIGAIHA,
	DI_MASKTYPE_SHIPPOU,
	DI_MASKTYPE_SYOKKOU,
	DI_MASKTYPE_UROKO,
	DI_EFFECTCOPYGUARD_BACKGROUND,
	DI_EFFECTCOPYGUARD_STRING
};

typedef struct {
	unsigned char kind;
	unsigned char resolution;
#define DI_UCP_DATA_RES_200x200		(1)
#define DI_UCP_DATA_RES_300x300		(2)
#define DI_UCP_DATA_RES_400x400		(3)
#define DI_UCP_DATA_RES_600x600		(4)
#define DI_UCP_DATA_RES_600x1200	(5)
#define DI_UCP_DATA_RES_1200x600	(6)
#define DI_UCP_DATA_RES_1200x1200	(7)
	unsigned char depth;
#define DI_UCP_DATA_DEPTH_1BIT		(1)
#define DI_UCP_DATA_DEPTH_2BIT		(2)
#define DI_UCP_DATA_DEPTH_4BIT		(4)
} di_ucp_info_t;

typedef struct {
	unsigned char width;
	unsigned char length;
	long offset;
} di_ucp_data_t;

typedef struct {
	unsigned long flag;
#define DI_PINFO_NUP 		(1 << 0)
#define DI_PINFO_UPSIDEDOWN (1 << 1)
	struct {
			unsigned char layout;
#define DI_PINFO_NUPLAYOUT_OFF		0
#define DI_PINFO_NUPLAYOUT_2in1		1
#define DI_PINFO_NUPLAYOUT_4in1		2
#define DI_PINFO_NUPLAYOUT_6in1		3
#define DI_PINFO_NUPLAYOUT_8in1		4
#define DI_PINFO_NUPLAYOUT_9in1		5
#define DI_PINFO_NUPLAYOUT_16in1	6
			unsigned char option;
#define DI_PINFO_NUPOPTION_RIGHTTHENDOWN	0
#define DI_PINFO_NUPOPTION_LEFTTHENDOWN		1
#define DI_PINFO_NUPOPTION_DOWNTHENRIGHT	2
#define DI_PINFO_NUPOPTION_DOWNTHENLEFT		3
			unsigned char line;
#define DI_PINFO_NUPLINE_OFF	0
#define DI_PINFO_NUPLINE_ON		1
			unsigned char reserve;
	} nup;
	unsigned char upsidedown;
#define DI_PINFO_UPSIDEDOWN_OFF 0
#define DI_PINFO_UPSIDEDOWN_ON 	1
	unsigned char reserve1[3];
	unsigned long reserve2[4];
	unsigned long driver_flag;
#define DI_PINFO_D_WEEKLY			0
#define DI_PINFO_D_OUTPUT_REVERSE	1
#define DI_PINFO_D_USED_PROFILE		2
#define DI_PINFO_D_TAB				3
#define DI_PINFO_D_PRINTER_MARKING		4
#define DI_PINFO_D_TWIN_COLOR			5
	unsigned char driver_prtcond[32];
#define DI_PINFO_D_OFF	0
#define DI_PINFO_D_ON	1
} di_printinfo_t;

#include "di_paperdef.h"
#include "di_envdef.h"
#include "di_errorcode.h"

#ifndef DEFINE_DI_TYPE

#ifndef EXPORT
#ifndef DI_PACKDLL
#define EXPORT
#else
#define EXPORT  __declspec(dllexport)
#endif
#endif

/** \defgroup PublicInterface DI I/F
 * \{
 */

/**
 * \brief DI I/Fの初期化、及び製品情報の取得を行なう。
 *
 * \param initinfo DIが値をセットする構造体。
 * \param setinfo  DIに渡す各種パラメータ。現状GPSのみで有効。
 *
 * \retval 0     正常終了
 * \retval 0以外 失敗
 *
 * \pre di_init() がコールされていない。
 * \pre 引数 *initinfo にアクセス可能。
 * \pre 引数 *setinfo にアクセス可能。
 * \pre 引数 setinfo->interp_id が以下のいずれか。
 *  \li DI_ITNERP_RPCS
 *  \li DI_INTERP_XHTML
 *  \li DI_INTERP_EXIF
 *  \li DI_INTERP_BMLINKS
 *  \li DI_INTERP_PS
 *  \li DI_INTERP_PCL
 * \pre 引数 setinfo->async がアクセス可能(GPS動作のみ)。
 *
 * \post di_term() がコールされるまで di_init() は使用不可能。
 * \post di_term() がコールされるまでdi_init()を除く全てのＤＩのインター
 * フェースが使用可能。
 * \post di_term()がコールされるまでsetinfo->asyncの各パラメータが非同期
 * に更新される(GPS動作のみ)。
 * \post パネルにＤＩを使用しているプリンタアプリ名表示(GPS動作のみ)。
 * \post 引数 *initinfo 内のメンバが適切な値に更新される。
 */
extern EXPORT int di_init( di_initinfo_t *initinfo, di_setinfo_t *setinfo );

/**
 * \brief DIがセットしたパラメータをクリアする。
 *
 *  \param devinfo   情報が格納されている構造体。
 *  \param free_func 本関数内でメモリを解放するためのコールバック関数。
 *
 * \retval 0     正常終了
 * \retval 0以外 失敗
 *
 * \pre di_init() がコールされている。
 * \pre *devinfo にアクセス可能。
 * \pre free_func にコール可能。
 *
 * \post di_getinfo()で確保したメモリは、free_funcを使用して解放される。
 * \post *devinfoのパラメータはゼロクリアされる。
 */
extern EXPORT int di_clear( di_devinfo_t *devinfo, DI_CALLBACK_MEMFREE free_func );

/**
 * \brief DI I/Fの終了処理を行なう。
 *
 * \post di_init(),di_term()を除く全てのＤＩのインターフェースが使用不可。
 * \post プリンタＯＳが、ＤＩを使用しているプリンタアプリの終了を認識。
 */
extern EXPORT void di_term();

/**
 * \brief プリンタアプリの起動から終了まで変化しない機種依存情報の取得を
 *行なう。
 *
 *  \param devinfo 情報を格納する構造体。
 *  \param alloc_func 本関数内でメモリを確保するためのコールバック関数。
 *	\param dither_gamma_file ディザ･ガンマファイルのファイル名（フルパス
 *指定）。
 *
 * \return 返り値が０以外の場合は、以下のビットフラグのOnの意味となる。
 *複数のフラグがOnとなる場合もある。
 *
 * \retval 0     正常終了
 * \retval DI_GI_ERR_CONDITION  事前条件を満たしていない
 * \retval DI_GI_ERR_DITHER     dither_info 取得失敗
 * \retval DI_GI_ERR_GAMMA      gamma_info 取得失敗
 * \retval DI_GI_ERR_FONT       font_address & font_size 取得失敗
 * \retval DI_GI_ERR_PROF       profaddress & profnumber 取得失敗
 * \retval DI_GI_ERR_RESO       resonum & reso_set 取得失敗
 * \retval DI_GI_ERR_NDIT       ndit 取得失敗
 * \retval DI_GI_ERR_NPLANE     nplane 取得失敗
 * \retval DI_GI_ERR_BGUCR      bg_(startp/slant) & ucr_(startp/slant)
 *取得失敗
 * \retval DI_GI_ERR_TSAVE      soft_tsave 取得失敗
 * \retval DI_GI_ERR_TSAVE_R    tsave_ratio 取得失敗
 * \retval DI_GI_ERR_TLIMIT     toner_limit 取得失敗
 * \retval DI_GI_ERR_TLIMIT_R   tlimit_num & tlimit_val 取得失敗
 * \retval DI_GI_ERR_SHDM       shdm_addr 取得失敗
 * \retval DI_GI_ERR_SYSH       sys_handle 取得失敗
 * \retval DI_GI_ERR_EXTENDTSAVE      extend_soft_tsave 取得失敗
 *
 * \pre di_init() がコールされている。
 * \pre *devinfoがアクセス可能。
 * \pre alloc_func( size )をコールすると、size だけ確保したメモリの先頭
 *アドレスの値が返ってくる。
 * \pre dither_gamma_file というファイルが存在する、もしくは
 *dither_gamma_fileがNULL。
 * \pre alloc_funcで取得するメモリサイズは、GPS環境で約300Byte、GPS以外
 *の環境で約65KByte となる。
 *
 * \post *devinfo内のメンバが適切な値に更新される。
 */
extern EXPORT int di_getinfo(di_devinfo_t *devinfo,
							 DI_CALLBACK_MEMALLOC alloc_func,
							 char *dither_gamma_file);

/**
 * \brief プリンタＯＳからイベント要求を取得する。
 *
 * 終了要求以外の要求の場合,インタプリタはデータ処理可能状態となる。
 *
 * \retval DI_REQ_PROCESS    通常処理要求
 * \retval DI_REQ_CANCEL     通常処理＋ジョブキャンセル要求
 * \retval DI_REQ_EXIT       終了要求
 * \retval -1                エラー
 *
 * \pre di_init() がコールされている
 *
 * \post 返り値にシステムからの要求が格納される。
 * \post 返り値がDI_REQ_PROCESS,DI_REQ_CANCELの場合には、プリンタＯＳ
 *はプリンタアプリがデータ処理状態になったと判断する。
 * \post 返り値がDI_REQ_EXITの場合には、プリンタＯＳはプリンタアプリが
 *アイドル状態になったと判断する。
 */
extern EXPORT int di_get_request();

/**
 * \brief トレイ情報の取得を行う。
 *
 * \param trayinfo トレイ情報を格納する構造体
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー、トレイ情報取得失敗
 *
 * \pre di_init() がコールされている。
 * \pre *trayinfoがアクセス可能。
 *
 * \post *trayinfo内のメンバが適切な値に更新される。
 */
extern EXPORT int di_get_trayinfo(di_trayinfo_t *trayinfo );

/**
 * \brief アプリ固有情報から指定カテゴリのキーの値を取得する。
 *
 * \param key      検索キー(文字列)
 * \param category 検索カテゴリ(文字列)
 * \param value    検索結果(文字列)を格納する領域
 *
 * \retval  DI_PINI_OK                 検索成功
 * \retval  DI_PINI_KEY_NOT_FOUND      該当するkeyが見つからなかった
 * \retval  DI_PINI_CATEGORY_NOT_FOUND 該当するcategoryが見つからなか
 *った
 * \retval  DI_PINI_ERROR              エラー
 *
 * \pre di_init() がコールされている。
 * \pre keyの文字数がターミネートを含め1文字以上32文字以内
 * \pre categoryの文字数がターミネートを含め1文字以上32文字以内
 * \pre value[0]～value[DI_MAX_VALUE_LEN-1]までアクセス可能
 *
 * \post 検索した文字列がvalueに書き込まれる。文字列がDI_MAX_VALUE_LEN
 *より長い場合は、DI_MAX_VALUE_LEN-1までの文字列を取得して、
 *value[DI_MAX_VALUE_LEN-1]に終端文字を追加する。
 */
extern EXPORT int di_get_appinfo(char *key, char *category, char value[]);

/**
 * \brief 環境変数の値を取得する。
 *
 * \param table_name 環境変数テーブル名
 * \param id         環境変数ID
 * \param val        得られた環境変数の値
 *
 * \retval  1 正常終了（環境変数が明示的に指定されている）
 * \retval  0 正常終了（環境変数が明示的に指定されてないため、デフォル
 *ト値セット)
 * \retval -1 エラー（di_init()がコールされていない）
 * \retval -2 エラー（table_nameが存在しない）
 * \retval -3 エラー（指定した環境変数がない）
 *
 * \pre di_init() がコールされている。
 * \pre table_nameというテーブルが存在する。
 * \pre 環境変数 id が、table_nameに存在する。
 * \pre *valがアクセス可能。
 *
 * \post *valに指定した環境変数の値が格納される。
 */
extern EXPORT int di_get_envvalue( char *table_name, long id, long *val );

/**
 * \brief 環境変数の値をセットする。
 *
 * \param table_name 環境変数テーブル名
 * \param id         環境変数ID
 * \param val        セットする環境変数の値
 *
 * \retval  0 正常終了
 * \retval -1 エラー（di_init()がコールされていない）
 * \retval -2 エラー（table_nameが存在しない）
 * \retval -3 エラー（ 指定した環境変数がない）
 * \retval -4 エラー（リードオンリーの環境変数）
 * \retval -5 エラー（ val が設定不可能な値）
 *
 * \pre di_init() がコールされている。
 * \pre table_nameというテーブルが存在する。
 * \pre 環境変数 id が、設定可能な変数としてtable_nameに存在する。
 *
 * \post di_set_envvalue( table_name, id, k )という形式で本関数をコー
 *ルした場合、di_get_envvalue( table_name, id, &val )とするとval に k
 * がセットされる。
 */
extern EXPORT int di_set_envvalue( char *table_name, long id, long val );

/**
 * \brief DIの特定のタイミングでコールする関数を指定する。
 *
 * \param type 引数 func で指定されたコールバック関数をコールするタイミング。
 *各値に対するタイミングは以下のとおり。
 *  <table>
 *   <tr>
 *    <td>DI_CALLBACK_READERR_SINGETC</td>
 *    <td>di_singetc() 内で読み込みが失敗した場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_READERR_SINGET</td>
 *    <td>di_singet( )内で読み込みが失敗した場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_SIZEERR_SINGET</td>
 *    <td>di_singet( )の引数で、サイズ指定が不正だった場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_PROCDATA</td>
 *    <td>システムからデータ処理の開始要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_EXIT</td>
 *    <td>システムからインタプリタ終了要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_CANCEL</td>
 *    <td>システムからデータ処理の中止要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_ONLINE</td>
 *    <td>システムからオンライン要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_OFFLINE</td>
 *    <td>システムからオフライン要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_TESTPRINT</td>
 *    <td>システムからテストプリント要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_TRAYINFO</td>
 *    <td>システムから給紙トレイの変更通知がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_BININFO</td>
 *    <td>システムから排紙ビンの変更通知がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_EXITPAPER</td>
 *    <td>システムから強制排紙要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_FONTCOUNT</td>
 *    <td>システムからフォント数のカウント要求がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_PRTSTATUS</td>
 *    <td>システムからプリンタステータス情報の変更通知がきた場合</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_GAM</td>
 *    <td>システムからガンマの再計算要求がきた場合</td>
 *   </tr>
 *  </table>
 * \param func 指定するコールバック関数
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre type が引数の説明にある値のいずれか
 * \pre func がコール可能
 *
 * \post type により指定されたタイミングで func をコールする。
 */
extern EXPORT int di_set_callbackfunc( int type, DI_CALLBACK_FUNC func );

/**
 * \brief プリンタＯＳが管理しているメモリの確保を行う。
 *
 * \param size 確保するメモリサイズ(Byte)
 *
 * \retval 確保したメモリの先頭アドレス 確保成功
 * \retval NULL エラー、メモリ確保失敗
 *
 * \pre di_init() がコールされている。
 * \pre di_memory_alloc()が１度もコールされていない(GPS動作のみ)
 *
 * \post 返り値のアドレスからsizeバイトがアクセス可能
 */
extern EXPORT char *di_memory_alloc(unsigned long size);

/**
 * \brief di_memory_alloc() で確保したメモリの解放を行う。
 *
 * \param ptr 解放するメモリの先頭アドレス
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre ptrがdi_memory_alloc()で確保したメモリの先頭アドレス、もしくは０
 *
 * \post 解放したメモリは、プリンタＯＳが利用可能
 */
extern EXPORT int di_memory_free(char *ptr);

/**
 * \brief 入力ホストバッファをオープンする。
 * データ読み込み前に必ず本関数をコールすること
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre システムから通常処理要求が来ている
 *(di_get_request(),di_trans_process()参照)
 *
 * \post di_close_host()、もしくは di_trans_process() をコールするまで
 *以下の I/F が使用可能
 *  \li di_singetc()
 *  \li di_singet()
 *  \li di_sinpeekc()
 *  \li di_sinpeek()
 *  \li di_reset_sinpeek()
 *  \li di_sinseek()
 */
extern EXPORT int di_open_host();

/**
 * \brief di_open_host()によりオープンされた ホストバッファをクローズ
 *する。
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 *
 * \post di_open_host() をコールするまで以下のI/Fが使用不可能。
 *  \li di_singetc()
 *  \li di_singet()
 *  \li di_sinpeekc()
 *  \li di_sinpeek()
 *  \li di_reset_sinpeek()
 *  \li di_sinseek()
 */
extern EXPORT int di_close_host();

/**
 * \brief 入力ストリームから１バイトの読み込む。
 *
 * \param dat 読み込んだデータの値
 *
 * \retval 0     読み込み成功
 * \retval 0以外 エラー、読み込み失敗、EOF
 *
 * \pre di_init() がコールされている。
 * \pre ホストがオープンされている（ di_open_host() 参照）
 * \pre *dat がアクセス可能
 *
 * \post *datに入力ストリームの先頭１バイトが格納される。
 * \post リードポインタ、ピークポインタが次の読み込み位置に移動する
 */
extern EXPORT int di_singetc( unsigned char *dat );

/**
 * \brief 入力ストリームから複数バイト読み込む。
 *
 * \param buf 読み込み先バッファ
 * \param len 読み込むサイズ(Byte)
 *
 * \retval >0 読み込んだデータのバイト数
 * \retval 0  EOF
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre 入力ホストがオープンされている（ di_open_host() 参照）
 * \pre len が0以上
 * \pre len が1以上の場合に buf[0]～buf[len-1] がアクセス可能
 *
 * \post bufに入力ストリームの先頭lenバイトが格納される。
 * \post リードポインタ、ピークポインタが次の読み込み位置に移動する。
 */
extern EXPORT int di_singet( unsigned char *buf, long len );

/**
 * \brief 入力ストリームから１バイト読み込む。
 *
 * 読み込んだデータ内容は破棄しないため、di_reset_sinpeek() により再読
 *み込み可能。
 *
 * \param dat 読み込んだデータの値
 *
 * \retval 0     読み込み成功
 * \retval 0以外 エラー、EOF、読み込んだデータがホストバッファのサイズ
 *を超えた場合
 *
 * \pre di_init() がコールされている。
 * \pre ホストがオープンされている（ di_open_host() 参照）
 * \pre *dat がアクセス可能
 * \pre 入力ストリームが hostI/O（ di_select_idevice()参照）
 * \pre di_reset_sinpeek() がコールされている。
 *
 * \post *datに入力ストリームの先頭１バイトが格納される。
 * \post ピークポインタが１バイトずれる。
 */
extern EXPORT int di_sinpeekc( unsigned char *dat );

/**
 * \brief 入力ストリームから複数バイト読み込む。
 *
 * 読み込んだデータ内容は破棄しないため、di_reset_sinpeek() により再読
 *み込み可能。
 *
 * \param buf 読み込み先バッファ
 * \param len 読み込むサイズ(Byte)
 *
 * \retval >0 読み込んだデータのバイト数
 * \retval 0  EOF、ピークで読み込んだデータがホストバッファのサイズを
 *超えた場合
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre ホストがオープンされている（ di_open_host() 参照）
 * \pre len が0以上
 * \pre len が1以上の場合に buf[0]～buf[len-1] がアクセス可能
 * \pre 入力ストリームが hostI/O（ di_select_idevice()参照）
 * \pre di_reset_sinpeek() がコールされていて、かつその後に
 * di_singetc() , di_singet() , di_sinseek() のいずれもコールされてい
 *ない。
 *
 * \post bufに入力ストリームの先頭lenバイトが格納される。
 * \post ピークポインタが１バイトずれる。
 */
extern EXPORT int di_sinpeek( unsigned char *buf, long len );

/**
 * \brief ホストバッファの読み込み位置を、有効データの先頭に移動する。
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre ホストがオープンされている（ di_open_host() 参照）
 * \pre 入力ストリームが hostI/O（ di_select_idevice()参照）
 *
 * \post ピークポインタがリードポインタの位置に移動する。
 */
extern EXPORT int di_reset_sinpeek();

/**
 * \brief ホストバッファに対して、指定したバイト数だけ読み捨てる。
 *
 * \param len 読み込むサイズ(Byte)
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre ホストがオープンされている（ di_open_host() 参照）
 * \pre 入力ストリームが hostI/O（ di_select_idevice()参照）
 *
 * \post リードポインタとピークポインタがリードポインタの位置に移動する。
 */
extern EXPORT int di_sinseek( long len );

/**
 * \brief 入力ストリームを変更する。
 *
 * デフォルトは DI_HOST_IO
 *
 * \param mode 以下の指定入力ストリーム
 *   \li DI_HOST_IO   host I/O
 *   \li DI_MEMORY_IO memory buffer I/O
 *   \li DI_FILE_IO   file I/O
 * \param opt modeにより内容が変化する
 *  <table>
 *   <tr>
 *    <td><center>mode</center></td><td><center>内容</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_HOST_IO</td>
 *    <td>使用しない</td>
 *   </tr>
 *   <tr>
 *    <td>DI_MEMORY_IO</td>
 *    <td>
 *      メモリから読み込むコールバック関数<br>
 *      型:typedef int (*CALLBACK_MEMREAD)( unsigned char **, int * );<br>
 *      第１引数: 読み込み先アドレス<br>
 *      第２引数: 読み込むサイズ<br>
 *    </td>
 *   </tr>
 *   <tr>
 *    <td>DI_FILE_IO</td>
 *    <td>ファイルポインタ(型はFILE *)</td>
 *   </tr>
 *  </table>
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre mode が引数の説明にある値のいずれか
 * \pre opt が有効パラメータ（引数の説明参照）
 *
 * \post di_singetc() , di_singet() の読み込み先が mode に変更される。
 */
extern EXPORT int di_select_idevice( int mode, void *opt );

/**
 * \brief 制御を他プロセスへ移行する
 *
 * 本関数終了後はI/Oが切り離された状態となるため,
 *再度バッファからの読み込みを行なう場合はdi_open_host()をコールする
 *こと。
 *
 * \return 再度制御が移行してきた時のシステムからの要求
 * \retval DI_REQ_EXIT    終了要求
 * \retval DI_REQ_PROCESS 通常処理要求
 * \retval DI_REQ_CANCEL  ジョブキャンセル要求
 *
 * \pre di_init() がコールされている。
 *
 * \post 返り値にシステムからの要求が格納される。
 * \post ホストバッファがクローズ状態となる。
 */
extern EXPORT int di_trans_process();

/**
 * \brief プリンタOSへメッセージを通知する。
 *
 * \param msg 通知するメッセージ
 *  \li DI_NOTIFYMSG_JOBEND    ジョブの終了
 *  \li DI_NOTIFYMSG_STATE     状態の通知
 *  \li DI_NOTIFYMSG_STRING    文字列による状態の通知
 *  \li DI_NOTIFYMSG_ERRFORCE  エラーの強制通知
 *  \li DI_NOTIFYMSG_START     明示的な起動通知。di_init() で指定する
 *インタプリタ ID が[ DI_INTERP_PS , DI_INTERP_PCL ] の場合に必要。
 *  \li DI_NOTIFYMSG_FONTCOUNT フォントカウントの終了通知
 *  \li DI_NOTIFYMSG_PAUSE 一時停止要求に対する応答（完了、もしくは一時停止できない）通知
 *  \li DI_NOTIFYMSG_RESUME 処理再開通知
 * \param opt msgにより内容が変化する。
 *  <table>
 *   <tr>
 *    <td><center>msg</center></td><td><center>内容</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_JOBEND</td>
 *    <td>使用しない</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_STATE</td>
 *    <td>通知する状態<br>
 *        DI_INTERP_STATE_IDLE       （データ待ち中）<br>
 *        DI_INTERP_STATE_PROCESSING （データ処理中）<br>
 *        DI_INTERP_STATE_WAITING    （データ処理中かつデータ待ち）<br>
 *        DI_INTERP_STATE_FLUSHING   （データキャンセル中）<br>
 *    </td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_STRING</td>
 *    <td>文字列の先頭アドレス</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_ERRFORCE</td>
 *    <td>エラーコード(詳細はGPS仕様書)</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_START</td>
 *    <td>インタプリタID。 di_setinfo_t 参照</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_FONTCOUNT</td>
 *    <td>使用しない</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_PAUSE</td>
 *    <td>通知する状態<br>
 *        DI_INTERP_PAUSE_OK	（一時停止した時）<br>
 *        DI_INTERP_PAUSE_NG	（一時停止できない）<br>
 *    </td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_RESUME</td>
 *    <td>使用しない</td>
 *   </tr>
 *  </table>
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre msg が引数の説明にある値のいずれか
 *
 * \post msg が DI_NOTIFYMSG_JOBEND なら、プリンタＯＳはプリンタアプリ
 *がアイドル状態になったと判断する。
 * \post msg が DI_NOTIFYMSG_STATE なら、プリンタＯＳはプリンタアプリが
 *optの状態と判断する。
 * \post msg が DI_NOTIFYMSG_ERRFORCE なら、パネルへのエラー表示とエラ
 *ーロギング反映を行う。
 * \post msg が DI_NOTIFYMSG_STRING なら、プリンタＯＳはプリンタアプリ
 *が文字列指定の状態になったと判断する。
 * \post msg が DI_NOTIFYMSG_START なら、プリンタＯＳはプリンタアプリが
 *起動されたと判断する。
 * \post msg が DI_NOTIFYMSG_FINISH_FONTCOUNT なら、プリンタＯＳはフォ
 *ントカウントが終了されたと判断する。
 * \post msg が DI_NOTIFYMSG_PAUSE なら、プリンタＯＳはプリンタアプリが
 *optの状態と判断する。
 * \post msg が DI_NOTIFYMSG_RESUME なら、プリンタＯＳはプリンタアプリが
 *処理再開されたと判断する。
 */
extern EXPORT int di_notify_msg( int msg, long opt );

/**
 * \brief 指定した用紙サイズをプリンタがサポートしているか問い合わせる。
 *
 * \param paper_id 用紙サイズID(GPS定義)
 *
 * \retval  1 サポートされている
 * \retval  0 サポートされていない
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 *
 * \post 返り値が１なら、その用紙サイズで出力可能
 */
extern EXPORT int di_query_supportpaper( int paper_id );

/**
 * \brief ジョブに設定されているオプション文字列を取得する。
 *
 * \param str オプション文字列の先頭アドレス
 *
 * \retval  0 成功
 * \retval -1 失敗(指定されたオプション文字列を途中までしか取得できな
 *かった)。strには途中までの文字列のアドレスを返す
 * \retval -2 失敗、エラー
 *
 * \pre di_init() がコールされている。
 * \pre *str がアクセス可能。
 * \pre プリンタOSより通常処理要求が来ている。
 *
 * \post *strにオプション文字列の先頭アドレスが格納される。
 */
extern EXPORT int di_get_optstr( char **str );

/**
 * \brief エラープリント用のバッファのアドレス取得
 *
 * \param buffer 今までのバッファの先頭アドレス
 * \param size   取得したバッファのサイズ
 *
 * \retval 取得したバッファの先頭アドレス 正常終了
 * \retval NULL  エラー
 *
 * \pre di_init() がコールされている。
 * \pre *buffer がアクセス可能。
 * \pre *size がアクセス可能
 *
 * \post 返り値に取得したバッファの先頭アドレスが返ってくる。
 */
extern EXPORT char *di_get_epbuffer( char *buffer, int *size );

/**
 * \brief 指定した用紙のサイズを取得する
 *
 * \param code   用紙コード
 * \param width  用紙幅（0.1mm単位）
 * \param length 用紙長さ（0.1mm単位）
 *
 * \retval  1 サポートしている
 * \retval  0 サポートしていない
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 *
 * \post *width が用紙コード code の用紙幅となる
 * \post *length が用紙コード code の用紙長さとなる
 */
extern EXPORT int di_get_papersize( unsigned char code,
									unsigned int *width,
									unsigned int *length );

/**
 * \brief 出力ホストバッファをオープンする。
 *
 * データ書き込み前に必ず本関数をコールすること
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre システムから通常処理要求が来ている（ di_get_request() 、
 * di_trans_process() 参照）
 *
 * \post di_close_ohost() 、もしくは di_trans_process() をコールするま
 *で以下のI/Fが使用可能。
 *  \li di_soutputc()
 *  \li di_soutput()
 *  \li di_soutflush()
 */
extern EXPORT int di_open_ohost();

/**
 * \brief di_open_ohost() によりオープンされたホストバッファをクローズ
 *する。
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 *
 * \post di_open_ohost() をコールするまで以下のI/Fが使用不可能。
 *  \li di_soutputc()
 *  \li di_soutput()
 *  \li di_soutflush()
 */
extern EXPORT int di_close_ohost();

/**
 * \brief 出力ストリームへ１バイト書き込む。
 *
 * 送信バッファに書き込み領域がない場合には、送信データを書き込む領域
 *ができるまでブロックする。
 *
 * \param dat 書き込むデータの値
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー、書き込み失敗
 *
 * \pre di_init() がコールされている。
 * \pre 出力ホストがオープンされている（ di_open_ohost() 参照）
 *
 * \post 送信バッファに dat が書き込まれる。
 */
extern EXPORT int di_soutputc( unsigned char dat );

/**
 * \brief 出力ストリームへ複数バイト書き込む。
 *
 * \param buf 書き込むデータ
 * \param len 読み込むサイズ(Byte)
 * \param flag 書き込み方法
 *  <table>
 *   <tr>
 *    <td><center>値</center></td><td><center>内容</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_HOST_BLOCK</td>
 *    <td>ノンブロック指定なし。送信バッファに書き込み領域がない場合に
 *        は、送信データを書き込む領域ができるまでブロックする。</td>
 *   </tr>
 *   <tr>
 *    <td>DI_HOST_NONBLOCK</td>
 *    <td> ノンブロック指定あり。送信バッファのブロックはしない（バッ
 *        ファが溢れるまで書き込み、書き込めたバイト数を戻り値として返
 *        す）。</td>
 *   </tr>
 *  </table>
 *
 * \retval >=0 書き込んだデータのバイト数
 * \retval  -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre 出力ホストがオープンされている（ di_open_ohost() 参照）
 * \pre len が0以上
 * \pre len が1以上の場合に buf[0]～buf[len-1] がアクセス可能
 *
 * \post buf の内容が出力ストリームに書き込まれる
 */
extern EXPORT int di_soutput( unsigned char *buf, long len, int flag );

/**
 * \brief 送信バッファ中に書き込まれたが、まだ送信されていないデータを
 *ホストに送信する。
 *
 * di_soutputc() あるいは di_soutput() にて一区切りの送信データを送信
 *バッファに書き込んだ後、必ず、この関数を呼ぶこと。
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre システムから通常処理要求が来ている（ di_get_request() ,
 * di_trans_process() 参照）
 *
 * \post 送信バッファのデータが全て送信される。
 */
extern EXPORT int di_soutflush();

/**
 * \brief 入力ストリームの有効バイト数を取得する。
 *
 * \param len 入力ストリームバッファ中の有効なデータのバイト数
 *
 * \retval  1 正常終了(EOFがバッファに含まれている)
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre 出力ホストがオープンされている（ di_open_ohost() 参照）
 * \pre *len がアクセス可能
 *
 * \post *lenに入力ストリームの有効バイト数が格納される。
 */
extern EXPORT int di_sinavail( long *len );

/**
 * \brief 現在指定されている優先給紙トレイ情報を取得する。
 *
 * \param tray_id 優先給紙トレイ情報に指定されているトレイID。
 * di_onetrayinfo_t 参照。
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *tray_id がアクセス可能
 *
 * \post 優先トレイの ID が *tray_id に格納される。
 */
extern EXPORT int di_get_deftray( int *tray_id );

/**
 * \brief 現在指定されている優先排紙ビン情報を取得する。
 *
 * \param bin_id 優先排紙ビン情報に指定されているビンID。
 * di_onebininfo_t 参照。
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *bin_id がアクセス可能
 *
 * \post 優先排紙ビンのIDが*bin_idに格納される
 */
extern EXPORT int di_get_defbin( int *bin_id );

/**
 * \brief 排紙ビン情報の取得を行う。
 *
 * \param bininfo 排紙ビン情報
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *bininfo がアクセス可能
 *
 * \post *bininfo の値と排紙ビンの情報が一致する。
 */
extern EXPORT int di_get_bininfo( di_bininfo_t *bininfo );

/**
 * \brief プリンタのステータス情報を取得する。
 *
 * \param status ステータス情報
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *status がアクセス可能
 *
 * \post *status の値とプリンタのステータス情報が一致する。
 */
extern EXPORT int di_get_status( di_status_t *status );

/**
 * \brief トータルカウンターの値を取得する。
 *
 * \param cnt トータルカウンターの値
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *tray_id がアクセス可能
 *
 * \post cnt の値とトータルカウンターの値が一致する。
 */
extern EXPORT int di_get_totalcounter( long *cnt );

/**
 * \brief EhterTalk パラメータを取得する。
 *
 * \param info EtherTalk パラメータ
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *info がアクセス可能
 *
 * \post info の値とEtherTalkパラメータの値が一致する。
 */
extern EXPORT int di_get_ethertalkinfo( di_ethertalk_info_t *info );

/**
 * \brief EhterTalk パラメータを設定する。
 *
 * \param info EtherTalk パラメータ
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *info がアクセス可能
 *
 * \post di_get_ethertalkinfo() で取得したEthertalkパラメータが *info と等しくなる。
 */
extern EXPORT int di_set_ethertalkinfo( di_ethertalk_info_t *info );

/**
 * \brief ユーザージョブ情報を設定する。
 *
 * \param job_id ユーザージョブID
 * \param info   ユーザージョブ情報
 *
 * \retval 0     正常終了
 * \retval -1    エラー
 * \retval -2    指定したパラメータをサポートしていない
 *
 * \pre di_init() がコールされている。
 * \pre システムから通常処理要求が来ている
 * ( di_get_request() , di_trans_process )参照
 * \pre *info がアクセス可能
 *
 * \post ユーザージョブ情報がシステムに設定されている。
 */
extern EXPORT int di_set_ujobinfo( int job_id, di_ujob_info_t *info );

/**
 * \brief ユーザージョブ情報を取得する。
 *
 * \param job_id ユーザージョブID
 * \param info   ユーザージョブ情報
 *
 * \retval 0     正常終了
 * \retval -1    エラー
 * \retval -2    指定したパラメータをサポートしていない
 *
 * \pre di_init() がコールされている。
 * \pre システムから通常処理要求が来ている
 * ( di_get_request() , di_trans_process )参照
 * \pre *info がアクセス可能
 *
 * \post *infoの共用体upに現在設定されている値が入る。
 * \post 設定されていない場合にはinfo->flagにて指定されたフラグがリセットされる。
 */
extern EXPORT int di_get_ujobinfo( int job_id, di_ujob_info_t *info );

/**
 * \brief ビットスイッチの値を取得する。
 *
 * \param no  ビットスイッチの番号
 * \param val ビットスイッチの値
 *
 * \retval 0     正常終了
 * \retval 0以外 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *val がアクセス可能
 *
 * \post no番目のビットスイッチの値が *val と等しくなる。
 */
extern EXPORT int di_get_bitswinfo( int no, int *val );

/**
 * 各種ディスク情報を取得する。
 *
 * \param type ディスクの種類
 *  <table>
 *   <tr>
 *    <td><center>値</center></td><td><center>内容</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_HDD_DOWNLOAD</td>
 *    <td>ファイルダウンロード用ハードディスク</td>
 *   </tr>
 *   <tr>
 *    <td>DI_HDD_SPOOL</td>
 *    <td>スプール用ハードディスク</td>
 *   </tr>
 *   <tr>
 *    <td>DI_RAM_DOWNLOAD</td>
 *    <td>ファイルダウンロード用RAMディスク</td>
 *   </tr>
 *   <tr>
 *    <td>DI_RAM_SPOOL</td>
 *    <td>スプール用RAMディスク</td>
 *   </tr>
 *  </table>
 * \param info ディスクの情報
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 typeのディスクが搭載されていない
 * \retval -3 受付拒否（呼び出しの二重化が発生した場合）
 *
 * \pre di_init() がコールされている。
 * \pre type が引数の説明にある値のいずれか
 * \pre *val がアクセス可能
 *
 * \post type で指定されたディスク情報値が *info と等しくなる。
 */
extern EXPORT int di_get_diskinfo( int type, di_diskinfo_t *info );

/**
 * \brief ストレージデバイスへファイルを保存する。
 *
 * \param type ストレージの種類
 *  <table>
 *   <tr>
 *    <td><center>値</center></td><td><center>内容</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_STORAGE_NVRAM</td>
 *    <td>NVRAM</td>
 *   </tr>
 *  </table>
 * \param fname ４文字のファイル名
 * \param data  書き込むデータ配列の先頭アドレス
 * \param size  dataの配列の長さ
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 容量不足による失敗
 *
 * \pre di_init() がコールされている。
 * \pre type が引数の説明にある値のいずれか
 * \pre *fname で指定するファイル名が４文字
 * \pre data[0]～data[size-1] までがアクセス可能
 *
 * \post ストレージに fname というファイルで data の内容が size 分書き
 *込まれる。
 */
extern EXPORT int di_write_storage( int type, char *fname,
									unsigned char *data, long size );

/**
 * \brief ストレージデバイスに書き込まれているファイルからデータを読み
 *込む。
 *
 * \param type    ストレージの種類(内容は di_write_storage() と同じ)
 * \param fname   ４文字のファイル名
 * \param data    読み込んだデータを格納する配列の先頭アドレス
 * \param size    dataの配列の長さ
 * \param data_size 実際に読んだデータのサイズ
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 fname というファイルが存在しない
 * \retval -3 data[size]より大きいファイルだったので最後まで読み込めな
 *かった。この場合でもsize分だけはdata[]に読み込まれ、*data_sizeにコピ
 *ーしたデータのバイト数(=size)が返る。
 *
 * \pre di_init() がコールされている。
 * \pre type が引数の説明にある値のいずれか
 * \pre *fname で指定するファイル名が４文字
 * \pre data[0]～data[size-1] までがアクセス可能
 * \pre *data_size がアクセス可能
 *
 * \post ストレージにある fname というファイルから size 分のデータが
 *dataに読み込まれる。
 */
extern EXPORT int di_read_storage( int type, char *fname, unsigned char *data,
								   long size, long *data_size );

/**
 * \brief ストレージデバイスに書き込まれているファイルを削除する。
 *
 * \param type  ストレージの種類(内容は di_write_storage() と同じ)
 * \param fname ４文字のファイル名
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre type が引数の説明にある値のいずれか
 * \pre *fname で指定するファイル名が４文字
 *
 * \post ストレージに fname というファイルが存在しない。
 */
extern EXPORT int di_delete_storage( int type, char *fname );

/**
 * \brief 条件に合致する指定用紙を要求する
 *
 * \param plotid  プロッタID
 * \param psize   用紙サイズID
 * \param nodir   用紙方向
 *  <table>
 *   <tr>
 *    <td><center>値</center></td><td><center>内容</center></td>
 *   </tr>
 *   <tr>
 *    <td>0</td>
 *    <td>用紙サイズで指定した方向のみ。</td>
 *   </tr>
 *   <tr>
 *    <td>1</td>
 *    <td>用紙サイズが異なる方向でもＯＫ。</td>
 *   </tr>
 *  </table>
 * \param ptype   紙種
 * \param trayid  トレイID
 * \param req     要求結果
 *
 * \retval  4 サブペーパーサイズが有効のとき、要求用紙サイズと類似した
 *サイズの用紙が出現した
 * \retval  3 エラー画面におけるユーザーの操作により、強制印刷が選択さ
 *れた
 * \retval  2 エラー画面におけるユーザーの操作により、ジョブキャンセル
 *が選択された
 * \retval  1 エラースキップが発生した
 * \retval  0 条件に一致する用紙が出現した
 * \retval -1 エラー
 * \retval -2 ビジー（オープン済みページの印刷が終了していない）
 *
 * \pre di_init() がコールされている。
 * \pre *req がアクセス可能
 *
 * \post 要求結果が *req に格納される
 */
extern EXPORT int di_request_paper(int plotid, int psize, int nodir, int ptype,
								   int trayid, di_res_reqpaper_t *req);

/**
 * \brief 環境変数のデフォルト値を取得する。
 *
 * \param table_name  環境変数テーブル名
 * \param id          環境変数ID
 * \param val         得られた環境変数の値
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 table_nameが存在しない
 * \retval -3 指定した環境変数がない
 *
 * \pre di_init() がコールされている。
 * \pre table_name というテーブルが存在する。
 * \pre 環境変数 id が、table_name に存在する。
 * \pre *val がアクセス可能
 *
 * \post *val が環境変数 id のデフォルト値と等しくなる。
 */
extern EXPORT int di_get_defenvvalue(char *table_name, long id, long *val);

/**
 * \brief 環境変数のデフォルト値のセット
 *
 * \param table_name  環境変数テーブル名
 * \param id          環境変数ID
 * \param  val        セットする環境変数の値
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 table_nameが存在しない
 * \retval -3 指定した環境変数がない
 * \retval -4 リードオンリーの環境変数
 * \retval -5 valが設定不可能な値
 *
 * \pre di_init() がコールされている。
 * \pre table_name というテーブルが存在する。
 * \pre 環境変数 id が、table_name に存在する。
 * \pre 環境変数 id が、table_name に設定可能である。
 *
 * \post val が環境変数 id のデフォルト値と等しくなる。
 */
extern EXPORT int di_set_defenvvalue(char *table_name, long id, long val);

/**
 * \brief 環境変数情報の取得
 *
 * \param table_name  環境変数テーブル名
 * \param id          環境変数ID
 * \param info        環境変数の情報
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 table_nameが存在しない
 * \retval -3 指定した環境変数がない
 *
 * \pre di_init() がコールされている。
 * \pre table_name というテーブルが存在する。
 * \pre 環境変数 id が、table_name に存在する。
 * \pre *table_name がアクセス可能
 * \pre *info がアクセス可能
 *
 * \post *info が環境変数情報と等しくなる。
 */
extern EXPORT int di_get_envvalinfo(char *table_name, long id,
									di_envinfo_t *info);

/**
 * \brief 環境変数の値リストの取得
 *
 * \param table_name  環境変数テーブル名
 * \param id          環境変数ID
 * \param start       取得したい環境変数の値のリスト中の先頭番号
 * \param end         取得したい環境変数の値のリスト中の終了番号
 * \param list        値のリストを入れる配列のポインタ
 * \param list_num    listに入力した有効な変数リストの項目数
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 table_nameが存在しない
 * \retval -3 指定した環境変数がない
 *
 * \pre di_init() がコールされている。
 * \pre table_name というテーブルが存在する。
 * \pre 環境変数 id が、table_name に存在する。
 * \pre *table_name がアクセス可能
 * \pre list[0]～list[end-start]  がアクセス可能
 * \pre *list_num がアクセス可能
 *
 * \post list[0]～list[list_num-1] が環境変数idの値のリストと等しくなる。
 */
extern EXPORT int di_get_envvallist(char *table_name, long id,
									unsigned long start, unsigned long end,
									long *list, long *list_num);

/**
 * \brief パネル表示言語を取得する。
 *
 * \param language   パネル表示言語
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *table_name がアクセス可能
 *
 * \post *language がパネル表示言語と等しくなる。
 */
extern EXPORT int di_get_panellang(unsigned char *language);

/**
 * \brief 搭載されているフラッシュメモリの各種情報を取得する。
 *
 * \param id         フラッシュメモリの番号
 * \param info       id番目のフラッシュメモリの情報
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *info がアクセス可能
 * \pre id が 1～n の範囲内。n は di_get_flashmemnum() で取得される
 *フラッシュメモリの数。
 *
 * \post *info が id 番目のフラッシュメモリ情報と等しくなる。
 */
extern EXPORT int di_get_flashmeminfo(int id, di_flashmem_info_t *info);

/**
 * \brief 搭載されているフラッシュメモリの数を取得する。
 *
 * \param num     フラッシュメモリの数
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *num がアクセス可能
 *
 * \post *num が搭載されているフラッシュメモリの数と等しくなる。
 */
extern EXPORT int di_get_flashmemnum(long *num);

/**
 * \brief 通紙可能な最大用紙サイズを取得する。
 *
 * \param x     主走査方向(単位 : 1/10mm)
 * \param y     副走査方向(単位 : 1/10mm)
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *x がアクセス可能
 * \pre *y がアクセス可能
 *
 * \post *x が主走査方向の通紙可能最大サイズと等しくなる。
 * \post *y が副走査方向の通紙可能最大サイズと等しくなる。
 */
extern EXPORT int di_get_maxpapersize(long *x, long *y);

/**
 * \brief エンジンで作像可能な最大サイズを取得する。
 *
 * \param x     主走査方向(単位 : 1/10mm)
 * \param y     副走査方向(単位 : 1/10mm)
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *x がアクセス可能
 * \pre *y がアクセス可能
 *
 * \post *x が主走査方向の作像可能最大サイズと等しくなる。
 * \post *y が副走査方向の作像可能最大サイズと等しくなる。
 */
extern EXPORT int di_get_maximagesize(long *x, long *y);

/**
 * \brief メニューアイテム情報の取得
 *
 * \param panel_id  メニューアイテムのパネルID
 * \param itemtype  メニューアイテムのアイテムタイプ
 * \param menutype  メニューアイテムのメニュータイプ
 * \param buf       メニューアイテムの情報を格納するバッファ
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre buf[0]～buf[31] がアクセス可能
 *
 * \post buf がメニューアイテムの情報と等しくなる。
 */
extern EXPORT int di_get_menuitem(unsigned long panel_id,
								  unsigned long itemtype,
								  unsigned long menutype,
								  unsigned char *buf);

/**
 * \brief 指定するデバイスから文字列を取得する。
 *
 * \param type    デバイス種類
 * \param device  デバイスの詳細
 * \param id      文字列ID
 * \param buf     文字列を格納するバッファ
 * \param size    終端文字を含んだ文字列の長さ
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre buf[0]～buf[size-1] がアクセス可能
 *
 * \post buf が指定されたデバイスの文字列と等しくなる。
 */
extern EXPORT int di_get_string(int type, long device, unsigned long id,
								unsigned char *buf, unsigned long size);
								
/**
 * \brief フォントの情報を取得する。
 *
 * フォントの基本情報は di_getinfo() で取得できるが、詳細情報を取得す
 *る場合、もしくは di_getinfo() で取得できるフォント以外の種類のフォン
 *ト情報を取得する場合に本関数を使用する。
 *
 * \param type  フォントの種類
 * \param info  フォントの情報
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 * \pre *info がアクセス可能
 *
 * \post *info が type のフォント情報と等しくなる。
 */
extern EXPORT int di_get_fontinfo(int type, di_fontinfo_t *info);

/**
 * \brief 搭載PDL情報を取得する
 *
 * \param pdl_id  PDL ID
 * \param info    PDL情報
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 指定PDLが搭載されていない
 *
 * \pre di_init() がコールされている。
 * \pre pdl_id が有効ID
 *
 * \post *info が pdl_id の PDL 情報と等しくなる。
 */
extern EXPORT int di_get_pdlinfo(int pdl_id, di_pdlinfo_t *info);

/**
 * \brief ユーザージョブ変数の値を取得する。
 *
 * \param ujobparam ユーザージョブ情報
 *
 * \retval  0 正常終了
 * \retval -1 ジョブIDが無効
 * \retval -2 サポートしていないパラメータを指定した
 *
 * \pre di_init() がコールされている。
 * \pre *ujobparam がアクセス可能。
 *
 * \post *ujobparam がユーザージョブ変数の値と等しくなる。
 */
extern EXPORT int di_get_ujobparamvar( ujobparam_var_t *ujobparam );

/**
 * \brief conversion of the paper output bin number to id 
 *
 * \parameter bin_index: the number of the paper output bin
 *  
 * \retval >=0: id of paper output bin
 * \retval -1 : failure
 *
 * \pre di_init() has been called
 *
 * \post return the id of the paper output bin
 */
extern EXPORT int di_convert_binid(int bin_index);

extern EXPORT int di_open_downloadinfo(int ope, int mediatype, char *pdlname, char *filename,
					unsigned long *filesize, unsigned long *hfctrl);
extern EXPORT int di_close_downloadinfo(unsigned long hfctrl);
extern EXPORT int di_read_downloadinfo(unsigned long hfctrl, void *pbuf, long readsize, long *nsize);
extern EXPORT int di_write_downloadinfo(unsigned long hfctrl, void *pbuf, long writesize, long *nsize);
extern EXPORT int di_delete_downloadinfo(int ope, int mediatype, char *pdlname, char *dirname);
extern EXPORT void di_check_interrupt();

extern EXPORT void di_set_ujobid(int ujobid);


/**
 * \brief 指定された用紙等の情報を元に、必要な画像回転方向の情報を取得
 *する。
 *
 * \param plotid プロッタID
 * \param info   画像回転方向の判定を行うための情報
 * \param result 画像回転方向の判定結果
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 * \retval -2 関数がサポートされていない
 *
 * \pre di_init() がコールされている。
 * \pre plotid が有効 ID。
 * \pre *info がアクセス可能。
 * \pre *result がアクセス可能。
 *
 * \post *result が画像回転方向の情報と等しくなる。
 */
extern EXPORT int di_get_imgrotinfo( int plotid, di_rotenvinfo_t *info, di_imgrotinfo_t *result );

/**
 * \brief ガンマ再計算を行う。
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init() がコールされている。
 *
 * \post システム内のガンマが再計算される。
 */
extern EXPORT int di_update_gamma();

/**
 * \brief 環境変数の値(バイト列)を取得する。
 *
 * \param table_name 環境変数テーブル名
 * \param id         環境変数ID
 * \param val        得られた環境変数の値
 * \param in_size    バイト列valのバイト数。環境変数が文字列の場合には、NULLターミネートが入るだけの数を指定すること。
 * \param out_size   バイト列の有効なバイト数。環境変数が文字列の場合には、NULLターミネートを含む長さを返す。
 *
 * \retval  1 正常終了（環境変数が明示的に指定されている）
 * \retval  0 正常終了（環境変数が明示的に指定されてないため、デフォル
 *ト値セット)
 * \retval -1 エラー（di_init()がコールされていない、関数をサポートしていない）
 * \retval -2 エラー（table_nameが存在しない）
 * \retval -3 エラー（指定した環境変数がない）
 * \retval -4 エラー（in_sizeが小さすぎる）
 *
 * \pre di_init() がコールされている。
 * \pre table_nameというテーブルが存在する。
 * \pre 環境変数 id が、table_nameに存在する。
 * \pre val[0]-val[in_size-1]がアクセス可能。
 * \pre *out_sizeがアクセス可能。
 *
 * \post val[0]-val[out_size-1]に指定した環境変数の値が格納される。
 */
extern EXPORT int di_get_envdata( char *table_name, long id, void *val, unsigned long in_size, unsigned long *out_size );

/**
 * \brief パネルにエミュレーション名を表示する。
 *
 * \retval  0 正常終了
 * \retval -1 エラー
 *
 * \pre di_init()がコールされている
 * \pre strがNULLでない
 * \pre strがNULLターミネートを含めて、8バイト以内である
 *
 * \post パネルにstrで指定したエミュレーション名が表示される(GPS動作のみ)
 */
extern EXPORT int di_disp_setemulation( char *str );

extern EXPORT int di_disp_setcurrentintray( unsigned short tray_id );
extern EXPORT int di_disp_setcurrentintray2( unsigned short tray_id,
						unsigned short cut_orient_id );
extern EXPORT int di_disp_setdialogueid( char *filename, unsigned short str1_id, unsigned char str1_size,
 unsigned short str2_id, unsigned char str2_size, unsigned char time );
extern EXPORT int di_disp_clrdialogue( void );
extern EXPORT int di_disp_setprognum( unsigned short prog_id );
extern EXPORT int di_disp_menucheckfinish( void );
extern EXPORT int di_disp_addmenuitem( unsigned char *buf );

/* プログラム登録 */
extern EXPORT struct di_progtable * di_get_programinfo ( unsigned int prog_no );
extern EXPORT int di_register_program( int prog_no, di_progtable_t *psw );
extern EXPORT int di_delete_program(int prog_no );
extern EXPORT int di_get_programnum( void );
extern EXPORT int di_write_program( char *name, int fileno, char *data, int data_size );
extern EXPORT int di_read_program( char *name, int fileno, char *data, int data_size );
extern EXPORT int di_finish_program( void );
extern EXPORT int di_write_storage_auth( int type, char *fname, unsigned char *data, long size, unsigned long auth );
extern EXPORT int di_register_program_auth( int prog_no, di_progtable_t *psw, unsigned long auth );
extern EXPORT int di_delete_program_auth( int prog_no, unsigned long auth );
extern EXPORT int di_write_program_auth( char *name, int fileno, char *data, int data_size, unsigned long auth );

/* USE_SET_CATEGORY */
extern EXPORT int di_set_category( char *category );

/* USE_CHANGE_EML */
extern EXPORT int di_change_eml( char *eml_name, int uswitch );

extern EXPORT int di_query_duplex( di_chkduplexok_t *pchkduplex );
extern EXPORT int di_set_ethertalkinfo_auth( di_ethertalk_info_t *info, unsigned long auth );

extern EXPORT int di_open_envtable( char *table_name );
extern EXPORT int di_close_envtable( int penv );
extern EXPORT int di_get_envvalue_direct( int penv, long id, long *val );
extern EXPORT int di_get_defenvvalue_direct( int penv, long id, long *val );
extern EXPORT int di_get_envdata_direct( int penv, long id, void *val,
							unsigned long in_size, unsigned long *out_size );
extern EXPORT int di_request_tray( int plotid, int psize, int nodir, int ptype,
									int trayid, di_trayrequest_t *trayreq, 
									int *result );
extern EXPORT int di_get_micrinfo( long *micrinfo );
extern EXPORT int di_get_printcondition( di_printcondition_t *cond,
										 di_media_printcondition_t *media );
extern EXPORT int di_get_printconditionShm( di_printconditionShm_t *condShm,
											int *status );
extern EXPORT int di_get_trayinfo2( di_trayinfo_t *trayinfo );
extern EXPORT int di_get_ucpdata(di_ucp_info_t ucpinfo,
								di_ucp_data_t *ucpdata,
								int *result);
extern EXPORT int di_get_ucpparam(di_ucp_param_t *ucpparam, int *result);
extern EXPORT int di_set_printinfo(int plotid, di_printinfo_t *prtinfo);

extern EXPORT int di_zinit( di_initinfo_t *initinfo, di_setinfo_t *setinfo );
extern EXPORT int di_zopen_host(void);
extern EXPORT int di_zclose_host(void);
extern EXPORT int di_ztrans_process(void);
extern EXPORT int di_zselect_idevice(int mode, void *opt);
extern EXPORT int di_zinit_memory(unsigned char *mem_zlib_addr);

/** \} */ /* end of group(Interface) */

#else	/* DEFINE_DI_TYPE */

typedef int (*DI_PROC_INIT)( di_initinfo_t *, di_setinfo * );
typedef int (*DI_PROC_CLEAR)( di_devinfo_t *, DI_CALLBACK_MEMFREE );
typedef void (*DI_PROC_TERM)();
typedef int (*DI_PROC_GETINFO)( di_devinfo_t *, DI_CALLBACK_MEMALLOC, char * );
typedef int (*DI_PROC_GET_REQUEST)();
typedef int (*DI_PROC_GET_TRAYINFO)( di_trayinfo_t * );
typedef int (*DI_PROC_GET_ENVVALUE)( char *, long, long * );
typedef int (*DI_PROC_SET_ENVVALUE)( char *, long, long );
typedef int (*DI_PROC_SET_CALLBACKFUNC)( int, DI_CALLBACK_FUNC );
typedef char* (*DI_PROC_MEMORY_ALLOC)( unsigned long );
typedef void (*DI_PROC_MEMORY_FREE)( char * );
typedef void (*DI_PROC_OPEN_HOST)();
typedef void (*DI_PROC_CLOSE_HOST)();
typedef int (*DI_PROC_IGETCH)( unsigned char *);
typedef int (*DI_PROC_IGETS)( unsigned char *, long );
typedef int (*DI_PROC_IPEEKCH)( unsigned char *);
typedef int (*DI_PROC_IPEEKS)( unsigned char *, long );
typedef void (*DI_PROC_RESET_IPEEK)();
typedef int (*DI_PROC_ISEEK)( long );
typedef int (*DI_PROC_SELECT_IDEVICE)( int, void * );
typedef int (*DI_PROC_TRANS_PROCESS)();
typedef int (*DI_PROC_NOTIFY_MSG)(int, long);
typedef int (*DI_PROC_QUERY_SUPPORTPAPER)( int );
typedef int (*DI_PROC_GET_OPTSTR)( char ** );
typedef int (*DI_PROC_GET_PAPERSIZE)( unsigned char, unsigned int, unsigned int );
typedef int (*DI_PROC_OPEN_HOSTS)();
typedef int (*DI_PROC_CLOSE_HOSTS)();
typedef int (*DI_PROC_SOUTPUTC)( unsigned char );
typedef int (*DI_PROC_SOUTPUT)( unsigned char *, long, int );
typedef int (*DI_PROC_SOUTFLUSH)();
typedef int (*DI_PROC_SINAVAIL)( long * );
typedef int (*DI_PROC_GET_DEFTRAY)( int * );
typedef int (*DI_PROC_GET_DEFBIN)( int * );
typedef int (*DI_PROC_GET_BININFO)( di_bininfo_t * );
typedef int (*DI_PROC_GET_STATUS)( di_status_t * );
typedef int (*DI_PROC_GET_TOTALCOUNTER)( long * );
typedef int (*DI_PROC_GET_ETHERTALKINFO)( di_ehtertalk_info_t * );
typedef int (*DI_PROC_SET_ETHERTALKINFO)( di_ehtertalk_info_t * );
typedef int (*DI_PROC_SET_UJOBINFO)( int, di_ujob_info_t * );
typedef int (*DI_PROC_GET_UJOBINFO)( int, di_ujob_info_t * );
typedef int (*DI_PROC_GET_BITSWINFO)( int, int * );
typedef int (*DI_PROC_GET_DISKINFO)( int, di_diskinfo_t * );
typedef int (*DI_PROC_WRITE_STORAGE)( int, char *, unsigned char *, long );
typedef int (*DI_PROC_READ_STORAGE)( int, char *, unsigned char *, long, long * );
typedef int (*DI_PROC_DELETE_STORAGE)( int, char * );
typedef int (*DI_PROC_REQUEST_PAPER)( int, int, int, int, int, di_res_reqpaper_t * );
typedef int (*DI_PROC_GET_DEFENVVALUE)( char *, long, long * );
typedef int (*DI_PROC_SET_DEFENVVALUE)( char *, long, long );
typedef int (*DI_PROC_GET_ENVVALINFO)( char *, long, di_envinfo_t *o );
typedef int (*DI_PROC_GET_ENVVALLIST)( char *, long, unsigned long, unsigned long, long *, long * );
typedef int (*DI_PROC_GET_PANELLANG)( unsigned char * );
typedef int (*DI_PROC_GET_FLASHMEMINFO)( int, di_flashmem_info_t * );
typedef int (*DI_PROC_GET_FLASHMEMNUM)( long * );
typedef int (*DI_PROC_GET_MAXPAPERSIZE)( long *, long * );
typedef int (*DI_PROC_GET_MAXIMAGESIZE)( long *, long * );
typedef int (*DI_PROC_GET_MENUITEM)( unsigned long, unsigned long, unsigned long, unsigned char * );
typedef int (*DI_PROC_GET_STRING)( int, long, unsigned long, unsigned char, unsigned long * );
typedef int (*DI_PROC_GET_FONTINFO)( int, di_fontinfo_t * );
typedef int (*DI_PROC_GET_PDLINFO)( int, di_pdlinfo_t * );
typedef int (*DI_PROC_GET_UJOBPARAMVAR)( ujobparam_var_t *);
typedef int (*DI_PROC_OPEN_DOWNLOADINFO)(int, int, char *, char *, unsigned long *, unsigned long *);
typedef int (*DI_PROC_CLOSE_DOWNLOADINFO)(unsigned long);
typedef int (*DI_PROC_READ_DOWNLOADINFO)(unsigned long, void *, long, long *);
typedef int (*DI_PROC_WRITE_DOWNLOADINFO)(unsigned long, void *, long, long *); 
typedef int (*DI_PROC_DELETE_DOWNLOADINFO)(int, int, char *, char *);
typedef int (*DI_PROC_GET_IMGROTINFO)( int , di_rotenvinfo_t *, di_imgrotinfo_t * );
typedef int (*DI_PROC_UPDATE_GAMMA)();
typedef int (*DI_PROC_GET_ENVDATA)( char *, long, void *, unsigned long, unsigned long * );
typedef int (*DI_PROC_DISP_SETEMULATION)( char * );
typedef void (*DI_PROC_CHECK_INTERRUPT)();
typedef int (*DI_PROC_DISP_SETCURRENTINTRAY)( unsigned short );
typedef int (*DI_PROC_DISP_SETDIALOGUEID)( char *, unsigned short, unsigned char, unsigned short, unsigned char, unsigned char );
typedef int (*DI_PROC_DISP_CLRDIALOGUE)();
typedef int (*DI_PROC_DISP_SETPROGNUM)( unsigned short );
typedef int (*DI_PROC_DISP_MENUCHECKFINISH)();
typedef int (*DI_PROC_DISP_ADDMENUITEM)( unsigned char * );
typedef int (*DI_PROC_CONVERT_BINID)( int );

typedef struct di_progtable* (*DI_GET_PROGRAMINFO)( unsigned int );
typedef int (*DI_REGISTER_PROGMRAM)( int, di_progtable_t * );
typedef int (*DI_DELETE_PROGRAM)( int );
typedef int (*DI_GET_PROGRAMNUM)( void );
typedef int (*DI_WRITE_PROGRAM)( char *, int, char *, int );
typedef int (*DI_READ_PROGRAM)( char *, int, char *, int );
typedef int (*DI_FINISH_PROGRAM)( void );
typedef int (*DI_WRITE_STORAGE_AUTH)( int, char *, unsigned char *, long, unsigned long );
typedef int (*DI_REGISTER_PROGRAM_AUTH)( int, di_progtable_t *, unsigned long );
typedef int (*DI_DELETE_PROGRAM_AUTH)( int, unsigned long );
typedef int (*DI_WRITE_PROGRAM_AUTH)( char *, int, char *, int, unsigned long );

typedef int (*DI_SET_CATEGORY)( char * );

typedef int (*DI_CHANGE_EML)( char *, int );

typedef int (*DI_QUERY_DUPLEX)( di_chkduplexok_t * );
typedef int (*DI_SET_ETHERTALKINFO_AUTH)( di_ehtertalk_info_t *, unsigned long );

typedef int (*DI_OPEN_ENVTABLE)( char * );
typedef int (*DI_CLOSE_ENVTABLE)( int );
typedef int (*DI_GET_ENVVALUE_DIRECT)( int, long, long * );
typedef int (*DI_GET_DEFENVVALUE_DIRECT)( int, long, long * );
typedef int (*DI_REQUEST_TRAY)( int, int, int, int, int, di_trayrequest_t *, int *);
typedef int (*DI_GET_MICRINFO)( long * );
typedef int (*DI_GET_PRINTCONDITION)( di_printcondition_t *,
									  di_media_printcondition_t * );
typedef int (*DI_GET_PRINTCONDITIONSHM)( di_printconditionShm_t *, int * );
typedef int (*DI_GET_TRAYINFO2)( di_trayinfo_t * );
typedef int (*DI_GET_UCPDATA)(di_ucp_info_t ucpinfo,
								di_ucp_data_t *ucpdata
								int *result);
typedef int (*DI_GET_UCPPARAM)(di_ucp_param_t *ucpparam,
											int *result);
typedef int (*DI_SET_PRINTINFO)(int, di_printinfo_t *);

typedef int (*DI_ZINIT)( di_initinfo_t *, di_setinfo_t * );
typedef int (*DI_ZOPEN_HOST)( void );
typedef int (*DI_ZCLOSE_HOST)( void );
typedef int (*DI_ZTRANS_PROCESS)( void );
typedef int (*DI_ZSELECT_IDEVICE)( int, void * );
typedef int (*DI_ZINIT_MEMORY)( unsigned char * );

#endif	/* DEFINE_DI_TYPE */

#endif	/* __DEVICE_H__ */

/*
 *
 *	COPYRIGHT (C) 2001-2007 RICOH COMPANY LTD.
 *	All rights reserved.
 *
 */
