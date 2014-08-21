/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : info.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 18 Oct 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_INFO_H_
#define	_GPS_INFO_H_

/*
 *	notify flag
 */
#define	GPS_NOTIFY_CHANGE_OFF	0	/* not notify if changed */
#define	GPS_NOTIFY_CHANGE_ON	1	/* notify if changed */

/*
 *	destination definision
 */
#define	GPS_SYS_DEST_DOM	0
#define	GPS_SYS_DEST_NA		1
#define	GPS_SYS_DEST_EU		2

/*
 *	option definition
 */
#define	GPS_SYS_OPTION(n)		(1 << (n))
#define	GPS_SYS_OPTION_DUPLEX		GPS_SYS_OPTION(0)	/* DUPLEX */
#define	GPS_SYS_OPTION_EXTLCT		GPS_SYS_OPTION(1)	/* ext. LCT */
#define	GPS_SYS_OPTION_1BIN		GPS_SYS_OPTION(2)	/* 1BIN shift */
#define	GPS_SYS_OPTION_EXTTRAY		GPS_SYS_OPTION(3)	/* ext. tray */
#define	GPS_SYS_OPTION_FIN_YUKON	GPS_SYS_OPTION(4)	/* FIN1000 */
#define	GPS_SYS_OPTION_FIN_LAWRENCE	GPS_SYS_OPTION(5)	/* FIN2250 */
#define	GPS_SYS_OPTION_FIN_SADDLE	GPS_SYS_OPTION(6)	/* Booklet */
#define	GPS_SYS_OPTION_MB_9BIN		GPS_SYS_OPTION(7)	/* 9BIN MBOX */
#define	GPS_SYS_OPTION_MB_SAXBY		GPS_SYS_OPTION(8)	/* Kir 4BIN */
#define	GPS_SYS_OPTION_MB_POTOMAC	GPS_SYS_OPTION(9)	/* Jup 4BIN */
#define	GPS_SYS_OPTION_TRAY2		GPS_SYS_OPTION(10)	/* Tray2 */
#define	GPS_SYS_OPTION_TRAY3		GPS_SYS_OPTION(11)	/* Tray3 */
#define	GPS_SYS_OPTION_BANK		GPS_SYS_OPTION(12)	/* BANK */
#define	GPS_SYS_OPTION_TANDEM		GPS_SYS_OPTION(13)	/* TANDEM */
#define	GPS_SYS_OPTION_FIN_FUJIGAWA	GPS_SYS_OPTION(14)	/* FUJIGAWA */
#define	GPS_SYS_OPTION_FIN_KING		GPS_SYS_OPTION(15)	/* KING */
#define	GPS_SYS_OPTION_FIN_SHINKAWA	GPS_SYS_OPTION(16)	/* UraP 1BIN SHIFT FIN */
#define	GPS_SYS_OPTION_TRAYMAN		GPS_SYS_OPTION(17)	/* MANUAL TRAY */
#define	GPS_SYS_OPTION_INLCT		GPS_SYS_OPTION(18)	/* INNER LCT */
#define	GPS_SYS_OPTION_FIN_BRAZOS_NON	GPS_SYS_OPTION(19)	/* BRAZOS-P */
#define	GPS_SYS_OPTION_FIN_BRAZOS_PRF	GPS_SYS_OPTION(20)	/* BRAZOS */
#define	GPS_SYS_OPTION_INSHIFT		GPS_SYS_OPTION(21)	/* INNER SHIFT */
#define	GPS_SYS_OPTION_CF_UNIT		GPS_SYS_OPTION(22)	/* CF UNIT */
#define	GPS_SYS_OPTION_ADF		GPS_SYS_OPTION(23)	/* ADF */
#define	GPS_SYS_OPTION_INSERTER		GPS_SYS_OPTION(24)	/* INSERTER */
#define	GPS_SYS_OPTION_SUPERIOR		GPS_SYS_OPTION(25)	/* SUPERIOR */
#define	GPS_SYS_OPTION_FIN_VICTORIA_B	GPS_SYS_OPTION(26)	/* VICTORIA */
#define	GPS_SYS_OPTION_FIN_ZAIRE_NON	GPS_SYS_OPTION(27)	/* ZAIRE */
#define	GPS_SYS_OPTION_FIN_ZAIRE_SDL	GPS_SYS_OPTION(28)	/* ZAIRE */
#define	GPS_SYS_OPTION_MB_ONTARIO	GPS_SYS_OPTION(29)	/* ONTARIO */
#define	GPS_SYS_OPTION_TRAY4		GPS_SYS_OPTION(30)	/* Tray4 */
#define	GPS_SYS_OPTION_TRAY5		GPS_SYS_OPTION(31)	/* Tray5 */

/*
 *	function definition
 */
#define	GPS_SYS_FUNC_DUPLEX		(1 << 0)	/* duplex */
#define	GPS_SYS_FUNC_STAPLE		(1 << 1)	/* staple */
#define	GPS_SYS_FUNC_PUNCH		(1 << 2)	/* punch */
#define	GPS_SYS_FUNC_SORT		(1 << 3)	/* sorting */
#define	GPS_SYS_FUNC_HDD_FS		(1 << 4)	/* HDD for FileSystem */
#define	GPS_SYS_FUNC_SHIFT		(1 << 5)	/* shift */
#define	GPS_SYS_FUNC_FINISHER		(1 << 6)	/* Finisher */
#define	GPS_SYS_FUNC_MAILBOX		(1 << 7)	/* Mail Box */
#define	GPS_SYS_FUNC_COLOR		(1 << 8)	/* Color (CMYK) */
#define	GPS_SYS_FUNC_HDD		(1 << 9)	/* HDD */
#define	GPS_SYS_FUNC_PROOFPRINT		(1 << 10)	/* proof print */
#define	GPS_SYS_FUNC_SEQUREPRINT	(1 << 11)	/* sequre print */
#define	GPS_SYS_FUNC_LOCALSTORAGE	(1 << 12)	/* local storage */
#define	GPS_SYS_FUNC_NETWORK		(1 << 13)	/* network */
#define	GPS_SYS_FUNC_REMOTEPRINT	(1 << 14)	/* remote print */
#define	GPS_SYS_FUNC_IEEE1394		(1 << 15)	/* IEEE1394 */
#define	GPS_SYS_FUNC_MF_MODEL		(1 << 16)	/* MF (not P) Model */
#define	GPS_SYS_FUNC_LARGEPRINTOUT	(1 << 17)	/* large printout */
#define	GPS_SYS_FUNC_IEEE802_11b	(1 << 18)	/* IEEE802.11b */
#define	GPS_SYS_FUNC_USB		(1 << 19)	/* USB */
#define GPS_SYS_FUNC_CENTRO		(1 << 20)	/* CENTRO */
#define	GPS_SYS_FUNC_BLUETOOTH		(1 << 21)	/* Bluetooth */
#define	GPS_SYS_FUNC_GWMAC		(1 << 22)	/* GWMAC */
#define	GPS_SYS_FUNC_GIGAETHER		(1 << 23)	/* Gigabit Ethernet */
#define	GPS_SYS_FUNC_FOLD		(1 << 24)	/* Z折り */
#define	GPS_SYS_FUNC_USBHOST		(1 << 25)	/* USBホスト */
#define	GPS_SYS_FUNC_PAUSEDPRINT	(1 << 26)	/* paused print(保留印刷) */
#define	GPS_SYS_FUNC_SAVEDDOCUMENT	(1 << 27)	/* saved document(保存文書) */
#define	GPS_SYS_FUNC_IMAGEOVERLAY	(1 << 28)	/* image overlay(イメージオーバーレイ) */
#define	GPS_SYS_FUNC_INTERRUPT		(1 << 29)	/* interrupt(割込み印刷) */
#define	GPS_SYS_FUNC_BIND		(1 << 30)	/* リング・くるみ製本（綴じる）*/
#define	GPS_SYS_FUNC_STAPLE2		(1 << 31)	/* staple2 */


/*
 *	resolution definition
 */
#define	GPS_SYS_RES_200x200		(1 << 0)
#define	GPS_SYS_RES_300x300		(1 << 1)
#define	GPS_SYS_RES_400x400		(1 << 2)
#define	GPS_SYS_RES_600x600		(1 << 3)
#define	GPS_SYS_RES_1200x1200		(1 << 4)
#define	GPS_SYS_RES_1200x600		(1 << 5)
#define	GPS_SYS_RES_600x600x2		(1 << 6)
#define	GPS_SYS_RES_600x600x4		(1 << 7)
#define	GPS_SYS_RES_1200x1200x2		(1 << 8)
#define	GPS_SYS_RES_600x1200		(1 << 9)
#define	GPS_SYS_RES_600x600x8		(1 << 10)

/*
 *	punch unit(not support)
 */
#define	GPS_SYS_PUNCH_UNIT_NONE		0
#define	GPS_SYS_PUNCH_UNIT_2		1	/* 2 */
#define	GPS_SYS_PUNCH_UNIT_3		2	/* 3 */
#define	GPS_SYS_PUNCH_UNIT_4_EU		3	/* 4 EU */
#define	GPS_SYS_PUNCH_UNIT_4_NE		4	/* 4 Northern EU */
#define	GPS_SYS_PUNCH_UNIT_2_NA		5	/* 2 NA */

/*
 *	punch hole
 */
#define	GPS_SYS_PUNCH_HOLE_JP2		(1 << 0)	/* 2 JP */
#define	GPS_SYS_PUNCH_HOLE_US2		(1 << 1)	/* 2 US */ 
#define	GPS_SYS_PUNCH_HOLE_US3		(1 << 2)	/* 3 US */ 
#define	GPS_SYS_PUNCH_HOLE_EU4		(1 << 3)	/* 4 EU */
#define	GPS_SYS_PUNCH_HOLE_NEU4		(1 << 4)	/* 4 Northern EU */
#define	GPS_SYS_PUNCH_HOLE_JP1		(1 << 5)	/* 1 JP */
#define	GPS_SYS_PUNCH_HOLE_MULTI	(1 << 6)	/* GBCパンチ */
#define GPS_SYS_PUNCH_HOLE_RING		(1 << 7)	/* RING PUNCH (21穴）*/
#define GPS_SYS_PUNCH_HOLE_RING2	(1 << 8)	/* RING PUNCH (46穴）*/

/*
 *	System info
 */
#define	GPS_SYS_LEN_MACHINE_NUMBER	11
#define	GPS_SYS_LEN_MODEL		50
#define	GPS_SYS_LEN_MAKER		20
#define	GPS_SYS_LEN_VERSION		12

/* 
 *	struct gps_option_ext
 */
/* gps_option_ext:flag */
#define	GPS_OPT_EXT_FLAG_VALID		(1 << 31)	/* set if this gps_option_ext structure is available */
#define	GPS_OPT_EXT_FLAG_TRAY		(1 << 30)	/* exist input tray option(s) */
#define	GPS_OPT_EXT_FLAG_BIN		(1 << 29)	/* exist output bin option(s) */
#define	GPS_OPT_EXT_FLAG_DUPLEX		(1 << 28)	/* exist optional duplex unit */
#define	GPS_OPT_EXT_FLAG_FIN		(1 << 27)	/* exist finisher */
#define	GPS_OPT_EXT_FLAG_MBOX		(1 << 26)	/* exist mail box */
#define	GPS_OPT_EXT_FLAG_MISC_PRT	(1 << 25)	/* exist other printer option(s) */
#define	GPS_OPT_EXT_FLAG_MISC_NON_PRT	(1 << 24)	/* exist other non-printer option(s) */
#define	GPS_OPT_EXT_FLAG_SUB_FIN	(1 << 23)	/* exist sub finisher */

/* gps_option_ext:tray */
#define	GPS_OPT_EXT_EXTLCT		(1 << 31)	/* ext. LCT */
#define	GPS_OPT_EXT_TRAY2		(1 << 30)	/* Tray2 */
#define	GPS_OPT_EXT_TRAY3		(1 << 29)	/* Tray3 */
#define	GPS_OPT_EXT_BANK		(1 << 28)	/* BANK */
#define	GPS_OPT_EXT_TANDEM		(1 << 27)	/* TANDEM */
#define	GPS_OPT_EXT_TRAYMAN		(1 << 26)	/* MANUAL TRAY */
#define	GPS_OPT_EXT_INLCT		(1 << 25)	/* INNER LCT */
#define	GPS_OPT_EXT_TRAY4		(1 << 24)	/* Tray4 */
#define	GPS_OPT_EXT_TRAY5		(1 << 23)	/* Tray5 */
#define	GPS_OPT_EXT_INSERTER		(1 << 22)	/* INSERTER */
#define	GPS_OPT_EXT_TRAY7		(1 << 21)	/* Tray7 */
#define	GPS_OPT_EXT_ROLL_FEEDER		(1 << 20)	/* Roll Unit */
#define	GPS_OPT_EXT_INSERTER2		(1 << 19)	/* INSERTER2(2段) */
#define	GPS_OPT_EXT_LARGELCT		(1 << 18)	/* Large Size LCT */
#define	GPS_OPT_EXT_ROLL_FEEDER2	(1 << 17)	/* Roll Unit2 */
#define	GPS_OPT_EXT_PERFECTBIND_INSERTER2	(1 << 16)	/* くるみ製本機インサーター */
#define	GPS_OPT_EXT_SMALLSIZE_TRAY	(1 << 15)	/* 小サイズトレイ */

/* gps_option_ext:bin */
#define	GPS_OPT_EXT_1BIN		(1 << 31)	/* 1BIN */
#define	GPS_OPT_EXT_EXTTRAY		(1 << 30)	/* ext. tray */
#define	GPS_OPT_EXT_INSHIFT		(1 << 29)	/* INNER SHIFT */
#define	GPS_OPT_EXT_SUPERIOR		(1 << 28)	/* SUPERIOR */

/* gps_option_ext:fin */
#define	GPS_OPT_EXT_FIN_YUKON		(1)
#define	GPS_OPT_EXT_FIN_LAWRENCE	(2)
#define	GPS_OPT_EXT_FIN_SADDLE		(3)		/* TONEGAWA */
#define	GPS_OPT_EXT_FIN_SHINKAWA	(4)
#define	GPS_OPT_EXT_FIN_FUJIGAWA	(5)
#define	GPS_OPT_EXT_FIN_KING		(6)
#define	GPS_OPT_EXT_FIN_BRAZOS_NON	(7)
#define	GPS_OPT_EXT_FIN_BRAZOS_PRF	(8)
#define	GPS_OPT_EXT_FIN_VICTORIA_B	(9)
#define	GPS_OPT_EXT_FIN_ZAIRE_SDL	(10)
#define	GPS_OPT_EXT_FIN_ZAIRE_NON	(11)
#define	GPS_OPT_EXT_FIN_TONEGAWA_C	(12)
#define	GPS_OPT_EXT_FIN_PLOKMATIC	(13)	/* VICTORIA-B+PLOKMATIC */
#define	GPS_OPT_EXT_FIN_KINUGAWA	(14)
#define	GPS_OPT_EXT_FIN_HUDOSON		(15)	/* GAIA_P1用FIN 本体排紙をつぶしてステープルのみ可能 */
#define	GPS_OPT_EXT_FIN_EUPHRATES_SDL	(16)
#define	GPS_OPT_EXT_FIN_EUPHRATES_NON	(17)
#define	GPS_OPT_EXT_FIN_TIGRIS		(18)
#define	GPS_OPT_EXT_FIN_KANOGAWA	(19)
#define	GPS_OPT_EXT_FIN_ATLANTIC_A	(20)	/* ATLANTIC ジャバラ機 */
#define	GPS_OPT_EXT_FIN_ATLANTIC_B	(21)	/* ATLANTIC フォルダー機（ジャバラ機＋クロスユニット） */
#define	GPS_OPT_EXT_FIN_ELBE		(23)	/* ELBE */
#define	GPS_OPT_EXT_FIN_SAKAWAGAWA	(24)
#define	GPS_OPT_EXT_FIN_COLUMBIA	(25)	/* COLUMBIA(中綴じ無し) */
#define	GPS_OPT_EXT_FIN_SHINJIKO	(26)	/* COLUMBIA+SHINJIKO(トリマー) */ 
#define	GPS_OPT_EXT_FIN_EUPHRATES_1BIT	(27)	/* EUPHRATES-D(1穴) */
#define	GPS_OPT_EXT_FIN_EUPHRATES_2BIT	(28)	/* EUPHRATES-D(2穴) */
#define	GPS_OPT_EXT_FIN_RUBICON		(29)	/* RUBICON */
#define GPS_OPT_EXT_FIN_AMUR_SDL	(30)	/* AMUR(中綴じ有り) */
#define GPS_OPT_EXT_FIN_AMUR_NON	(31)	/* AMUR(中綴じ無し) */
#define GPS_OPT_EXT_FIN_VOLGA_SDL	(32)	/* VOLGA(中綴じ有り) */
#define GPS_OPT_EXT_FIN_VOLGA_NON	(33)	/* VOLGA(中綴じ無し) */
#define GPS_OPT_EXT_FIN_COLUMBIA_SDL	(34)	/* COLUMBIA(中綴じ有り) */

/* gps_option_ext:mbox */
#define	GPS_OPT_EXT_MB_9BIN		(1)		/* MB 9BIN */
#define	GPS_OPT_EXT_MB_9BIN_P		(2)		/* MB_P 9BIN+proof */
#define	GPS_OPT_EXT_MB_SAXBY		(3)		/* SAXBY */
#define	GPS_OPT_EXT_MB_POTOMAC		(4)		/* POTOMAC */
#define	GPS_OPT_EXT_MB_JACK		(5)		/* JACK */
#define	GPS_OPT_EXT_MB_ONTARIO		(6)		/* ONTARIO */

/* gps_option_ext:misc_prt */
#define	GPS_OPT_EXT_DEVELOPMENT_R      	(1 << 31)	/* RED DEVELOPMENT */
#define	GPS_OPT_EXT_ZFOLD_UNIT      	(1 << 30)	/* ZFOLD UNIT */
#define GPS_OPT_EXT_GBC_PUNCH		(1 << 29)	/* GBCパンチユニット */
#define GPS_OPT_EXT_KARUN_SDL		(1 << 28)	/* 中綴じユニット(KARUN) */
#define GPS_OPT_EXT_MACHINE_STAMP	(1 << 27)	/* メカスタンプ */
#define GPS_OPT_EXT_DECURLER_UNIT	(1 << 26)	/* デカーラ・パージユニット */
							/* ※ MACHINE COMPO上、デカーラユニットおよびパージユニットは別でセットされるが、プリンタではまとめて管理（仮） */
#define GPS_OPT_EXT_COOLING_UNIT	(1 << 25)	/* 用紙冷却搬送ユニット */

/* gps_option_ext:misc_non_prt */
#define	GPS_OPT_EXT_CF_UNIT		(1 << 31)	/* CF UNIT */
#define	GPS_OPT_EXT_ADF			(1 << 30)	/* ADF */

/* gps_option_ext:sub_fin */
#define	GPS_OPT_EXT_SUBFIN_ISHIKARI	(1 << 31)	/* リング製本 */
#define	GPS_OPT_EXT_SUBFIN_TENRYU	(1 << 30)	/* くるみ製本 */
#define GPS_OPT_EXT_SUBFIN_DONAU	(1 << 29)	/* DONAU(多機能折り機) */
#define GPS_OPT_EXT_SUBFIN_LOIRE	(1 << 28)	/* LOIRE(スタッカ) */
#define GPS_OPT_EXT_SUBFIN_LOIRE2	(1 << 27)	/* LOIRE2(スタッカ) */

/* gps_option_ext:opt_tray_sub */
#define	GPS_OPT_EXT_TRAYSUB_KAUAI	(1)		/* KAUAI */
#define	GPS_OPT_EXT_TRAYSUB_SANDY_C	(2)		/* SANDY-C */
#define GPS_OPT_EXT_TRAYSUB_CATALINA_B	(3)	/* CATALINA-B */
#define GPS_OPT_EXT_TRAYSUB_EASTER_B	(4)	/* EASTER-B */
#define GPS_OPT_EXT_TRAYSUB_PHUKET	(5)	/* PHUKET */
#define GPS_OPT_EXT_TRAYSUB_TIMOR	(6)	/* TIMOR */
#define GPS_OPT_EXT_TRAYSUB_DALL	(7)	/* DALL */
#define GPS_OPT_EXT_TRAYSUB_CRETE	(8)	/* CRETE */

typedef struct gps_option_ext {
	unsigned long	flag;		/* valid flag (bit assign) */
	unsigned long	tray;		/* input tray option(s) (bit assign) */
	unsigned long	bin;		/* output bin option(s) (bit assign) */
	unsigned short	fin;		/* finisher (value) */
	unsigned short	mbox;		/* mali box (value) */
	unsigned long	misc_prt;	/* printer option(s) (bit assign) */
	unsigned long	misc_non_prt;	/* non-printer option(s) (bit assign) */
	unsigned long	sub_fin;	/* sub finisher (bit assign)*/
	unsigned char	opt_tray_sub[8];/* option tray information(connected tray name) */
	unsigned char	reserved[20];
} gps_option_ext_t, *gps_option_ext_p;

typedef struct gps_sysinfo {
#define	GPS_MACHINECODE_ADONIS_C2	0x00
#define	GPS_MACHINECODE_KIR_P		0x10
#define	GPS_MACHINECODE_KIR_P2		0x13
#define	GPS_MACHINECODE_KIR_P3		0x15
#define	GPS_MACHINECODE_JUPITER_P	0x20
#define	GPS_MACHINECODE_URANOS_P	0x30
#define	GPS_MACHINECODE_RUSSIAN_C2	0x40
#define GPS_MACHINECODE_ADONIS_P3	0x50
#define GPS_MACHINECODE_URANOS_C	0x60
#define GPS_MACHINECODE_ARES_P		0x70
#define GPS_MACHINECODE_KAISER3		0x80
#define GPS_MACHINECODE_JUPITER_P2	0x90
#define GPS_MACHINECODE_JUPITER_P2Y	0x93		/* 薬袋 */
#define GPS_MACHINECODE_JUPITER_P2M	0xa0
#define GPS_MACHINECODE_JUPITER_P2K	0xb0
#define	GPS_MACHINECODE_URANOS_P2	0xc0
#define GPS_MACHINECODE_JUPITER_C0	0xe0
#define	GPS_MACHINECODE_CASSIS_P1_DOM	0xf0		/* DOM */

#define	GPS_MACHINECODE_MARTINI_C1	0x00080000
#define	GPS_MACHINECODE_BELLINI_C2	0x00090000
#define	GPS_MACHINECODE_ADONIS_C3	0x000A0000
#define	GPS_MACHINECODE_RUSSIAN_C3	0x000B0000
#define	GPS_MACHINECODE_SEADRAGON_C1	0x000C0000
#define	GPS_MACHINECODE_JUPITER_C1	0x000D0000
#define	GPS_MACHINECODE_KIR_P3_EXP	0x00010000	/* EXP */
#define	GPS_MACHINECODE_KIR_C2		0x00120000
#define	GPS_MACHINECODE_CASSIS_P1_EXP	0x00130000	/* EXP */
#define	GPS_MACHINECODE_PLUTO_P1	0x00140000
#define GPS_MACHINECODE_VENUS_C1	0x00150000
#define GPS_MACHINECODE_URANOS_C2	0x00160000
#define	GPS_MACHINECODE_JUPITER_P3	0x00170000
#define GPS_MACHINECODE_GAIA_P1		0x00180000
#define GPS_MACHINECODE_MARTINI_C2	0x00190000
#define GPS_MACHINECODE_STELLA_C2	0x001A0000
#define GPS_MACHINECODE_DOLPHIN_C2	0x001B0000	/* DOLPHIN-C2 group */
#define GPS_MACHINECODE_JUPITER_C2	0x001C0000	/* JUPITER_C2 group */
#define	GPS_MACHINECODE_CASSIS_P2	0x001D0000	/* CASSIS-P2 group */
#define	GPS_MACHINECODE_MARTINI_P1	0x001E0000	/* MARTINI-P1 group */
#define	GPS_MACHINECODE_ADONIS_C4	0x001F0000	/* ADONIS-C4 group */
#define	GPS_MACHINECODE_RUSSIAN_C4	0x00200000	/* RUSSIAN-C4 group */
#define	GPS_MACHINECODE_KIR_P4		0x00210000	/* KIR-P4 group */
#define	GPS_MACHINECODE_JUPITER_P4	0x00220000	/* JUPITER-P4 group */
#define GPS_MACHINECODE_PEGASUS_C1	0x00230000	/* PegasusC1 group */
#define GPS_MACHINECODE_APOLLON_C1	0x00240000	/* ApollonC1 group */
#define GPS_MACHINECODE_ATHENA_C1	0x00250000	/* AthenaC1 group */
#define GPS_MACHINECODE_BELLINI_C3	0x00260000	/* BELLINI-C3 group */
#define GPS_MACHINECODE_MARTINI_C3	0x00270000	/* MARTINI-C3 group */
#define GPS_MACHINECODE_ARES_P2		0x00280000	/* ARES-P2 group */
#define GPS_MACHINECODE_GAIA_P2		0x00290000	/* Gaia-P2 group */
#define GPS_MACHINECODE_APOLLON_P1	0x002A0000	/* Apollon-P1 group */
#define GPS_MACHINECODE_ADONIS_P4	0x002B0000	/* Adonis-P4 group */
#define	GPS_MACHINECODE_MARTINI_P2	0x002C0000	/* MARTINI-P2 group */
#define	GPS_MACHINECODE_KIR_C3		0x002D0000	/* KIR-C3 group */
#define	GPS_MACHINECODE_NEPTUNE_C2	0x002E0000	/* NEPTUNE-C2 group */
#define	GPS_MACHINECODE_SEADRAGON_C2	0x002F0000	/* SEADRAGON_C2 group */
#define	GPS_MACHINECODE_ADONIS_C4_5	0x00300000	/* ADONIS-C4.5 group */
#define	GPS_MACHINECODE_RUSSIAN_C4_5	0x00310000	/* RUSSIAN-C4.5 group */
#define GPS_MACHINECODE_STELLA_C3	0x00320000	/* STELLA-C3 group */
#define GPS_MACHINECODE_KRISS_P1	0x00330000	/* Kriss-P1 group */
#define GPS_MACHINECODE_LUNA_P1		0x00340000	/* Luna-P1 group */
#define GPS_MACHINECODE_SINCERE_P1	0x00350000	/* Sincere-P1 group */
#define GPS_MACHINECODE_PARISIAN_C1	0x00360000	/* Parisian-C1 group */
#define GPS_MACHINECODE_VENUS_C2	0x00370000	/* Venus-C2 group */
#define GPS_MACHINECODE_ALEX_C1		0x003A0000	/* Alex-C1 group */
#define GPS_MACHINECODE_RUSSIAN_C5	0x003B0000	/* Russian-C5 group */
#define GPS_MACHINECODE_NEPTUNE_P1	0x003C0000	/* Neptune-P1 group */
#define GPS_MACHINECODE_ATHENA_C2	0x003D0000	/* Athena-C2 group */
#define GPS_MACHINECODE_ALEX_P1		0x003E0000	/* Alex-P1 group */
#define GPS_MACHINECODE_APOLLON_C2	0x003F0000	/* Apollon-C2 group */
#define GPS_MACHINECODE_PEGASUS_C2	0x00400000	/* Pegasus-C2 group */
#define GPS_MACHINECODE_BELUGA_C1	0x00410000	/* Beluga-C1 group */
#define GPS_MACHINECODE_DIANA_C1	0x00420000	/* Diana-C1 group */
#define GPS_MACHINECODE_GAIA_P3		0x00430000	/* Gaia-P3 group */
#define GPS_MACHINECODE_APOLLON_P2	0x00440000	/* Apollon-P2 group */
#define GPS_MACHINECODE_SINCERE_P2	0x00450000	/* Sincere-P2 group */
#define GPS_MACHINECODE_BELLINI_C4	0x00460000	/* Bellini-C4 group */
#define GPS_MACHINECODE_MARTINI_C4	0x00470000	/* Martini-C4 group */
#define GPS_MACHINECODE_LUNA_P2		0x00480000	/* Luna-P2 group */
#define GPS_MACHINECODE_DIANA_C1L	0x00490000	/* Diana-C1L group */
#define GPS_MACHINECODE_STELLA_C4	0x004B0000	/* STELLA-C4 group */
#define GPS_MACHINECODE_SHINKA_P1	0x004C0000	/* Shinka-P1 group */
#define GPS_MACHINECODE_KRISS_P2	0x004D0000	/* Kriss-P2 group */
#define GPS_MACHINECODE_VENUS_C3	0x004F0000	/* Venus-C3 group */
#define GPS_MACHINECODE_ZEUS_P1		0x00500000	/* Zeus-P1 group */
#define GPS_MACHINECODE_MARTINI_P3	0x00510000	/* Martini-P3 group */
#define GPS_MACHINECODE_NEPTUNE_C3	0x00520000	/* Neptune-C3 group */
#define GPS_MACHINECODE_MIDAS_P2	0x00550000	/* Midas-P2 group */
#define GPS_MACHINECODE_APOLLON_C2_5	0x00580000	/* Apollon-C2.5 group */
#define GPS_MACHINECODE_ATHENA_C2_5	0x00590000	/* Athena-C2.5 group */
#define GPS_MACHINECODE_DIANA_C1_5	0x005A0000	/* Diana-C1.5 group */
#define GPS_MACHINECODE_ZEUS_C1		0x005B0000	/* Zeus-C1 group */
#define GPS_MACHINECODE_SHINKA_MF1	0x005C0000	/* Shinka-MF1 group */
#define GPS_MACHINECODE_SINCERE_P3	0x005D0000	/* Sincere-P3 group */
#define GPS_MACHINECODE_STELLA_C4_5	0x005E0000	/* STELLA-C4.5 group */
#define GPS_MACHINECODE_ORVAL_C1	0x005F0000	/* Orval-C1 group */
#define GPS_MACHINECODE_LUCINA_P1	0x00600000	/* Lucina-P1 group */
#define GPS_MACHINECODE_ALEX_C2		0x00610000	/* Alex-C2 group */
#define GPS_MACHINECODE_GRIFFIN_C1	0x00620000	/* Griffin-C1 group */
#define GPS_MACHINECODE_MARTINI_C5	0x00630000	/* Martini-C5 group */
#define GPS_MACHINECODE_MOCHA_C1	0x00640000	/* Mocha-C1 group */
#define GPS_MACHINECODE_APOLLON_C3	0x00650000	/* Apollon-C3 group */
#define GPS_MACHINECODE_ATHENA_C3	0x00660000	/* Athena-C3 group */
#define GPS_MACHINECODE_STELLA_C5	0x00670000	/* Stella-C5 group */
#define GPS_MACHINECODE_SEADRAGON_C3	0x00680000	/* SeaDragon-C3 group */
#define GPS_MACHINECODE_METIS_C1	0x00690000	/* Metis-C1 group */
#define GPS_MACHINECODE_CHARIS_C1	0x006A0000	/* Charis-C1 group */
#define GPS_MACHINECODE_APOLLON_P3	0x006B0000	/* Apollon-P3 group */
#define GPS_MACHINECODE_ALEX_P2		0x006C0000	/* Alex-P2 group */
#define GPS_MACHINECODE_TITAN_P1	0x006D0000	/* Titan-P1 group */
#define GPS_MACHINECODE_KIR_C4		0x006E0000	/* Kir-C4 group */
#define GPS_MACHINECODE_BARON_C1	0x006F0000	/* Baron-C1 group */
#define GPS_MACHINECODE_GIMLET_MF1	0x00700000	/* Gimlet-MF1 group */
#define GPS_MACHINECODE_GIMLET_P1	0x00710000	/* Gimlet-P1 group */
#define GPS_MACHINECODE_ORVAL_C2	0x00720000	/* Orval-C2 group */
#define GPS_MACHINECODE_MARTINI_P5	0x00730000	/* Martini-P5 group */

	unsigned char		machinecode;
	unsigned char		model[GPS_SYS_LEN_MODEL];
	unsigned char		maker[GPS_SYS_LEN_MAKER];
	unsigned char		reserved[10];
	char			ver_printer[GPS_SYS_LEN_VERSION];
	char			ver_engine[GPS_SYS_LEN_VERSION];
	char			ver_lcdc[GPS_SYS_LEN_VERSION];
	unsigned long		option;
	unsigned long		function;
	unsigned char		destination;
	unsigned char		num_tray;
	unsigned char		num_bin;
	unsigned char		disp_lines;
	unsigned char		disp_columns;
	unsigned char		punch_unit;		/* not support */
	unsigned short		punch_hole;
	unsigned long		total_ram_size;
	unsigned long		resolution;
	unsigned char		machine_number[GPS_SYS_LEN_MACHINE_NUMBER + 1];
							/* NULL terminate */
	unsigned long		modelcode;
	gps_option_ext_t	option_ext;

#define GPS_MODELTYPE_A			0x00000001		/* type A */
#define GPS_MODELTYPE_B			0x00000002		/* type B */
#define GPS_MODELTYPE_C			0x00000003		/* type C */
#define GPS_MODELTYPE_D			0x00000004		/* type D */
#define GPS_MODELTYPE_E			0x00000005		/* type E */
#define GPS_MODELTYPE_F			0x00000006		/* type F */
#define GPS_MODELTYPE_G			0x00000007		/* type G */
#define GPS_MODELTYPE_H			0x00000008		/* type H */
#define GPS_MODELTYPE_I			0x00000009		/* type I */
#define GPS_MODELTYPE_J			0x0000000a		/* type J */
#define GPS_MODELTYPE_K			0x0000000b		/* type K */
#define GPS_MODELTYPE_L			0x0000000c		/* type L */
#define GPS_MODELTYPE_X			0x00000018		/* type X */
#define GPS_MODELTYPE_Y			0x00000019		/* type Y */
#define GPS_MODELTYPE_Z			0x0000001a		/* type Z */
#define GPS_MODELTYPE_C_DPX		GPS_MODELTYPE_D	/* type C(duplex) */
#define GPS_MODELTYPE_F_DPX		GPS_MODELTYPE_G	/* type C(duplex) */
#define GPS_MODELTYPE_C_1PASS	GPS_MODELTYPE_E	/* type C(1pass duplex) */
#define GPS_MODELTYPE_D_1PASS	GPS_MODELTYPE_F	/* type D(1pass duplex) */
#define GPS_MODELTYPE_A_PRO		GPS_MODELTYPE_C	/* type A(Pro) */
#define GPS_MODELTYPE_B_PRO		GPS_MODELTYPE_D	/* type B(Pro) */
	unsigned long		model_type;		/* エンジン モデル種別 */
	unsigned long		reserved2;		/* リザーブ２ */
} gps_sysinfo_t, *gps_sysinfo_p;

/*
 *	Printer info
 */
#define	GPS_LANG_JAPANESE		0
#define	GPS_LANG_ENGLISH		1
#define	GPS_LANG_FRENCH			2
#define	GPS_LANG_GERMAN			3
#define	GPS_LANG_ITALIAN		4
#define	GPS_LANG_SPANISH		5
#define	GPS_LANG_DUTCH			6
#define	GPS_LANG_SWEDISH		7
#define	GPS_LANG_NORWEGIAN		8
#define	GPS_LANG_DANISH			9
#define	GPS_LANG_FINNISH		10
#define	GPS_LANG_PORTUGUESE		11
#define	GPS_LANG_CZECH			12
#define	GPS_LANG_POLISH			13
#define	GPS_LANG_HUNGARIAN		14
#define	GPS_LANG_CHINESE		15
#define	GPS_LANG_TAIWANESE		16
#define	GPS_LANG_RUSSIAN		17
#define	GPS_LANG_HEBREW			18
#define	GPS_LANG_ARABIC			19
#define	GPS_LANG_AMERICAN		20
#define	GPS_LANG_CATALAN		21
#define	GPS_LANG_TURKISH		22
#define	GPS_LANG_GREEK			23
#define	GPS_LANG_BRAZILIAN		24

typedef struct gps_prtinfo {
	unsigned char		default_tray;
	unsigned short		default_bin;
	unsigned char		default_pdl;
	unsigned char		language;
} gps_prtinfo_t, *gps_prtinfo_p;

/*
 *	Tray info
 */
typedef struct gps_trayinfo {
	unsigned short		id;
	unsigned char		remain;
#define	GPS_TRAY_MANUAL			(1 << 0)	/* (attr) manual */
#define	GPS_TRAY_TANDEM			(1 << 1)	/* (attr) tandem */
#define	GPS_TRAY_NODUPLEX		(1 << 2)	/* (attr) noduplex */
#define	GPS_TRAY_LOCKED			(1 << 3)	/* (attr) tray locked */
#define	GPS_TRAY_SIZE_SENSE		(1 << 4)	/* (attr) sense paper size */
#define	GPS_TRAY_NODUPLEX_PAPER		(1 << 5)	/* (attr) noduplex paper(size | type) */
#define	GPS_TRAY_FRONTCOVERPRINT	(1 << 6)	/* (attr) frontcoverprint */
#define	GPS_TRAY_SLIPSHEET		(1 << 7)	/* (attr) slipsheet */
#define	GPS_TRAY_INNERLCT		(1 << 8)	/* (attr) INNER LCT */
#define	GPS_TRAY_CHAPTERSHEET1		(1 << 9)	/* (attr) chaptersheet1 */
#define	GPS_TRAY_CHAPTERSHEET2		(1 << 10)	/* (attr) chaptersheet2 */
#define	GPS_TRAY_CHAPTERSHEET3		(1 << 11)	/* (attr) chaptersheet3 */
#define	GPS_TRAY_CHAPTERSHEET4		(1 << 12)	/* (attr) chaptersheet4 */
#define	GPS_TRAY_CHAPTERSHEET5		(1 << 13)	/* (attr) chaptersheet5 */
#define	GPS_TRAY_CHAPTERSHEET6		(1 << 14)	/* (attr) chaptersheet6 */
#define	GPS_TRAY_CHAPTERSHEET7		(1 << 15)	/* (attr) chaptersheet7 */
#define	GPS_TRAY_BACKCOVERPRINT		(1 << 16)	/* (attr) backcoverprint */
#define	GPS_TRAY_PARTITION		(1 << 17)	/* (attr) partition */
#define	GPS_TRAY_TANDEM_SEPARATE 	(1 << 18)	/* (attr) tandem(separate) */
#define	GPS_TRAY_ROLL       		(1 << 19)	/* (attr) roll tray */
#define GPS_TRAY_MSIZESENSE_VALID 	(1 << 20)	/* (attr) 手差し自動サイズ検知有効 */
#define GPS_TRAY_SINGLE_PAPER 		(1 << 21)  	/* (attr) 一枚トレイ */
#define	GPS_TRAY_CHAPTERSHEET8		(1 << 22)	/* (attr) chaptersheet8 */
#define	GPS_TRAY_CHAPTERSHEET9		(1 << 23)	/* (attr) chaptersheet9 */
#define GPS_TRAY_SMALLSIZE_TYPE		(1 << 24)  	/* (attr) 小サイズトレイ設定がON */
	unsigned long		attr;
#define	GPS_TRAY_PAPEREND		(1 << 0)
#define	GPS_TRAY_BUSY			(1 << 1)
#define	GPS_TRAY_SETFAIL		(1 << 2)
#define	GPS_TRAY_ERROR			(1 << 3)
#define	GPS_TRAY_COPEN			(1 << 4)
#define	GPS_TRAY_MAN_PAPEREXIST		(1 << 5)
#define	GPS_TRAY_MAN_OPEN		(1 << 6)
#define	GPS_TRAY_MAN_SIZE		(1 << 7)
#define	GPS_TRAY_TAN_MISSSET		(1 << 8)
#define	GPS_TRAY_TAN_BUSY		(1 << 9)
#define	GPS_TRAY_UNLOAD			(1 << 10)
#define	GPS_TRAY_TAN_PAPEREXIST		(1 << 11)
#define	GPS_TRAY_TAN_INVALID		(1 << 12)
#define	GPS_TRAY_DOOR_OPEN		(1 << 13)
#define	GPS_TRAY_SIZEDETECT_ERR		(1 << 14)
	unsigned long		status;
	unsigned char		p_size;
	unsigned char		p_kind;
	unsigned char		p_color;
	unsigned short		p_length;		/* (0.1mm) */
	unsigned short		p_width;		/* (0.1mm) */
} gps_trayinfo_t, *gps_trayinfo_p;

/*
 *	Bin info
 */
typedef struct gps_bininfo {
	unsigned short		id;
	unsigned char		exist;
#define	GPS_BIN_STAPLER			(1 << 0)
#define	GPS_BIN_PUNCH			(1 << 1)
#define	GPS_BIN_SHIFT			(1 << 2)
#define	GPS_BIN_PAPER_SENSE		(1 << 3)	/* sense paper exist */
#define	GPS_BIN_FULL_SENSE		(1 << 4)	/* sense paper full */
#define	GPS_BIN_NODUPLEX		(1 << 5)	/* noduplex */
#define	GPS_BIN_SADDLE			(1 << 6)	/* saddle */
#define	GPS_BIN_FOLD			(1 << 7)	/* 折り機能 */
#define GPS_BIN_BINDPERFECT		(1 << 8)	/* くるみ機能 */
#define GPS_BIN_BINDRING		(1 << 9)	/* リング綴じ機能 */
#define GPS_BIN_RINGPUNCH		(1 << 10)	/* リングパンチ機能 */
#define GPS_BIN_MULTIFOLD		(1 << 11)	/* 多機能折り機能 */
#define GPS_BIN_FOLD_FIN_HALF	(1 << 12)	/* フィニッシャ中折り機能 */
	unsigned long		attr;
#define	GPS_BIN_FULL			(1 << 0)	/* 満杯 */
#define	GPS_BIN_ERROR			(1 << 1)	/* 故障状態 */
#define GPS_BIN_STOPEXIT       		(1 << 2)	/* 排紙抑制 */
#define GPS_BIN_SADDLE_DISABLE 		(1 << 3)	/* 中綴じ排紙禁止 */
#define GPS_BIN_NORMAL_DISABLE 		(1 << 4)	/* 中綴じ以外の排紙禁止 */
#define GPS_BIN_UNLOAD			(1 << 5)	/* スタッカ未セット */
#define	GPS_BIN_CARRIERUNLOAD		(1 << 6)	/* スタッカー台車未セット */
#define	GPS_BIN_COPEN			(1 << 7)	/* スタッカーカバーオープン */
	unsigned long		status;
} gps_bininfo_t, *gps_bininfo_p;

/*
 *	Printer Status
 */
#define	GPS_STCODE_MAX		32

typedef struct gps_prtstatus {
	unsigned char		cur_interpreter;
	int			state;
	int			st_code_num;
	unsigned short		st_code[GPS_STCODE_MAX];
	unsigned long		pjam_place;
	unsigned long		copen;
	unsigned long		function_disable;
#define	GPS_STATE_OFFLINE	(1 << 0)	/* offline */
#define	GPS_STATE_HEXDUMP	(1 << 1)	/* hexdump mode */
#define	GPS_STATE_WARMING_UP	(1 << 2)	/* warming up */
#define	GPS_STATE_ENERGY_SAVE	(1 << 3)	/* energy save mode */
#define	GPS_STATE_PRINTING	(1 << 4)        /* printing */
#define	GPS_STATE_PROCESSING	(1 << 5)        /* data processing */
#define	GPS_STATE_PREHEAT	(1 << 6)	/* preheat mode */
#define	GPS_STATE_WAITING	(1 << 7)	/* wating data */
#define	GPS_STATE_JOB_RESETTING	(1 << 8)	/* job resetting */
#define	GPS_STATE_INT_REQ	(1 << 9)	/* 割込み（コピー）要求 */
#define	GPS_STATE_INT_PAUSE	(1 << 10)	/* 割込み（コピー）中 */
#define	GPS_STATE_CALIBRATING	(1 << 11)	/* calibrating */ 
#define	GPS_STATE_SUPPLYING_TONER	(1 << 12)	/* supplying toner */
#define	GPS_STATE_INIT_DEVELOPER	(1 << 13)	/* initial developer */
#define	GPS_STATE_COOLING_DOWN	(1 << 14)	/* cooling down */
#define	GPS_STATE_UPDATING_REMOTECERT	(1 << 15)	/* updating remote cert */
#define	GPS_STATE_DRYING	(1 << 16)	/* 乾燥停止中 */
#define	GPS_STATE_PAUSE		(1 << 17)	/* 一次停止中 */
#define	GPS_STATE_SUSPEND	(1 << 18)	/* 停止再開 停止中 */

#define	GPS_STATE_HPPSTOP	(1 << 20)	/* HPP用 停止状態 */

#define	GPS_STATE_PANEL_LOG	(1 << 30)	/* D_LOG ON */
#define	GPS_STATE_CARDSAVE	(1 << 31)	/* cardsave mode */
	unsigned long		state_detail;
	int			st_code_num_warning;
	int			st_code_num_error;
	unsigned char		op_panel;	/* state for operation panel (from scs) */
	unsigned char		plt_eng_stat;	/* state for engine (from scs) */
} gps_prtstatus_t, *gps_prtstatus_p;

/*
 *	Printer Status2
 */
typedef struct gps_prtstatus2 {
	unsigned char		cur_interpreter;
	int			state;
	int			st_code_num;
	unsigned long		st_code[GPS_STCODE_MAX];
	unsigned long		pjam_place;
	unsigned long		copen;
	unsigned long		function_disable;
	unsigned long		state_detail; /* gps_prtstatus_t */
	int			st_code_num_warning;
	int			st_code_num_error;
	unsigned char		op_panel;	/* state for operation panel (from scs) */
	unsigned char		plt_eng_stat;	/* state for engine (from scs) */
} gps_prtstatus2_t, *gps_prtstatus2_p;

/*
 *	Paper Info
 */
typedef struct gps_paperinfo {
	unsigned char		id;
	unsigned long		input_enable_tray;
	unsigned long		output_enable_bin;
} gps_paperinfo_t, *gps_paperinfo_p;

/*
 *	Controller Error
 */
typedef struct gps_ctl_error {
	char		interp_id;
	unsigned short	error_id;
} gps_ctl_error_t;

/*
 *	info table ID
 */
#define	GPS_INFO_TABLE_ID_RPCS		1
#define	GPS_INFO_TABLE_ID_PCL		2

/*
 *	AppleTalk Info
 */
#define	GPS_ATINFO_FLAG_OBJECT_NAME		(1 << 0)
#define	GPS_ATINFO_FLAG_TYPE_NAME		(1 << 1)
#define	GPS_ATINFO_FLAG_ZONE_NAME		(1 << 2)
#define	GPS_ATINFO_FLAG_MACADDR			(1 << 3)
#define	GPS_MAX_ATINFO_OBJECT_NAME_LEN		32
#define	GPS_MAX_ATINFO_TYPE_NAME_LEN		32
#define	GPS_MAX_ATINFO_ZONE_NAME_LEN		32
#define	GPS_MAX_ATINFO_MACADDR_LEN		6

typedef struct gps_appletalk_info {
	unsigned long	flag;
	unsigned char	object_name[GPS_MAX_ATINFO_OBJECT_NAME_LEN + 1];
	unsigned char	type_name[GPS_MAX_ATINFO_TYPE_NAME_LEN + 1];
	unsigned char	zone_name[GPS_MAX_ATINFO_ZONE_NAME_LEN + 1];
	unsigned char	macaddr[GPS_MAX_ATINFO_MACADDR_LEN];
} gps_appletalk_info_t;

/*
 *	Centro Signal
 */
#define	GPS_CSIG_FAULT		0x01
#define	GPS_CSIG_SELECT		0x02
#define	GPS_CSIG_PE		0x04
#define	GPS_CSIG_BUSY		0x08

/*
 *	TONER CARTRIDGE INFO(PJLでのみ使用)
 */
typedef struct gps_cartridge_info
{
	char	type;		/* カートリッジ情報 */
/*
			0 : NORMALカートリッジ
			1 : MICRカートリッジ
 */
	char	status;		/* カートリッジステータス */

#define GPS_CARTRIDGE_STAT_UNKNOWN	(0)
#define GPS_CARTRIDGE_STAT_OK		(1)
#define GPS_CARTRIDGE_STAT_LOW		(2)
#define GPS_CARTRIDGE_STAT_EMPTY	(3)

	char	remain;		/* カートリッジトナー残量 */
	char	reserve[5];	/* Reserve */

#define  GPS_CARTRIDGE_ID_MAX_LEN	(16)

	char	id[GPS_CARTRIDGE_ID_MAX_LEN + 1];	/* カートリッジシリアル番号(ASCII) */
} gps_cartridge_info_t;


/* 地紋印刷条件パラメータ */
#define GPS_PARAM_PRINTERMARKINGTYPE		(1<<0)
#define GPS_PARAM_UCPMASKTYPE				(1<<1)
#define GPS_PARAM_UCPPATTERNCOLOR			(1<<2)
#define GPS_PARAM_UCPPATTERNDENSITY			(1<<3)
#define GPS_PARAM_UCPEFFECTCOPYGUARD		(1<<4)
#define GPS_PARAM_UCPEFFECTCOPYINHIBITION	(1<<5)
#define GPS_PARAM_UCPSTRPOSITION			(1<<6)
#define GPS_PARAM_UCPSTRREPEATPRINT			(1<<7)
#define GPS_PARAM_UCPFONTNUMBER				(1<<8)
#define GPS_PARAM_UCPFONTSIZE				(1<<9)
#define GPS_PARAM_UCPLINESPACE				(1<<10)
#define GPS_PARAM_UCPSTRANGLE				(1<<11)
#define GPS_PARAM_UCPSTRING					(1<<12)
#define GPS_PARAM_UCPFONTTYPE				(1<<13)

#define GPS_MAX_UCPSTRING_LEN				(64)
#define GPS_MAX_UCPFONTTYPE_LEN				(210)

/* 地紋抑止文字列・代替文字列エンコード */
#define	GPS_CHAR_CODE_NONE		0  /* 文字コードなし */
#define	GPS_CHAR_CODE_SJIS		1  /* Shift_JIS */
#define	GPS_CHAR_CODE_EUSTD		2  /* 欧州スタンダード (WinLatin1) */
#define	GPS_CHAR_CODE_CE		3  /* 中央ヨーロッパ (WinLatin2) */
#define	GPS_CHAR_CODE_GREEK		4  /* ギリシャ語系 (WinGreek) */
#define	GPS_CHAR_CODE_CYR		5  /* キリル語系 (WinCyrillic) */
#define	GPS_CHAR_CODE_TUR		6  /* トルコ語系 (WinTurkish) */
#define	GPS_CHAR_CODE_BALTIC	7  /* バルト語系 (WinBaltic) */
#define	GPS_CHAR_CODE_GB		8  /* 簡体字系 (GB2312) */
#define	GPS_CHAR_CODE_BIG		9  /* 繁体字系 (Big5) */
#define	GPS_CHAR_CODE_HEBREW	10 /* ヘブライ語 (WinHebrew?) */
#define	GPS_CHAR_CODE_ARABIC	11 /* アラビア語 (WinArabic?) */
#define	GPS_CHAR_CODE_THAI		12 /* タイ語 (DosThai?) */
#define	GPS_CHAR_CODE_KS		13 /* 韓国語（KS C 5601-1992) */


typedef struct gps_ucp_param {
	unsigned long	support_flag;
	unsigned long	forced_flag;
	unsigned char	printermarkingtype;
	unsigned char	ucpmasktype;
	unsigned char	ucppatterncolor;
	unsigned char	ucppatterndensity;
	unsigned char	ucpeffectcopyguard;
	unsigned char	ucpeffectcopyinhibition;
	unsigned char	ucpstrposition;
	unsigned char	ucpstrrepeatprint;
	unsigned char	ucpfontnumber;
	unsigned char	ucpstring_charcode;
	unsigned char	ucpstring_default_charcode;
	unsigned short	ucpfontsize;
	unsigned short	ucplinespace;
	unsigned short	ucpstrangle;
	unsigned char	ucpstring[GPS_MAX_UCPSTRING_LEN + 1];
	unsigned char	ucpstring_default[GPS_MAX_UCPSTRING_LEN + 1];
	unsigned char	ucpfonttype[GPS_MAX_UCPFONTTYPE_LEN + 1];
} gps_ucp_param_t;


/*
 * CipherSeed
 */
#define GPS_SCRTY_LEN_CIPHER_SEED (32)

/*
 * Printer Total Counter
 */
typedef	struct {
	long	blackcnt;		/* プリンタアプリのブラックカウンタ */
	long	fullcolorcnt;	/* プリンタアプリのフルカラーカウンタ */
} gps_prtcnt_t;


#endif /* !_GPS_INFO_H_ */
/*
 * Copyright (c) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 */
