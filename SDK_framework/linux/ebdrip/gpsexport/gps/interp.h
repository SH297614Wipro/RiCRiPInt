/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : interp.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 18 Oct 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_INTERP_H_
#define	_GPS_INTERP_H_

#include	"errorcode.h"
#include	"modelinfo_key.h"

#define	GPS_INTERP_RPCS			0
#define	GPS_INTERP_RPDL			1
#define	GPS_INTERP_R98			2
#define	GPS_INTERP_R16			3
#define	GPS_INTERP_R55			4
#define	GPS_INTERP_RPGL2		5
#define	GPS_INTERP_RTIFF		6
#define	GPS_INTERP_RPGL2c		7
#define	GPS_INTERP_PS3			8
#define	GPS_INTERP_PCL5e		9
#define	GPS_INTERP_PCL5c		10
#if 0 /* PDFはPS3と一体となったため削除。ただしID=11は予約 */
#define	GPS_INTERP_PDF			11
#endif /* 0 */
#define	GPS_INTERP_BMLINKS		12
#define	GPS_INTERP_PICTBRIDGE		13
#define	GPS_INTERP_IPDS			14
#define	GPS_INTERP_XPS			15

/* メディアプリント向けインタープリタ(30～39予約済) */
#define	GPS_INTERP_MP_GROUP		30
#define	GPS_INTERP_MP_TIFF		30
#define	GPS_INTERP_MP_JPEG		31

/* RICOH以外が実装するインタープリタで使用するID */
#define GPS_INTERP_RGROUP		40	/* R_GROUP用開始位置 */
#define GPS_INTERP_OTHERS		70	/* 第３者用開始位置  */

#define GPS_INTERP_RG_SR_KS		40	/* SHINDO RICOH KS/KSSM */
#define GPS_INTERP_RG_FNP		41	/* FNP(富士通OEM) */
#define GPS_INTERP_PAGES		42	/* PAGES */


#define	GPS_PDL_AUTO			-1
#define	GPS_PDL_RPCS			0
#define	GPS_PDL_RPDL			1
#define	GPS_PDL_R98			2
#define	GPS_PDL_R16			3
#define	GPS_PDL_R55			4
#define	GPS_PDL_RPGL			5
#define	GPS_PDL_HPGL2			6
#define	GPS_PDL_RTIFF			7
#define	GPS_PDL_POSTSCRIPT		8
#define	GPS_PDL_PCL			9
#define	GPS_PDL_PCLXL			10
#define	GPS_PDL_TIFF			11
#define	GPS_PDL_PDF			12
#define	GPS_PDL_BMLINKS			13
#define	GPS_PDL_PICTBRIDGE		14
#define	GPS_PDL_IPDS			15
#define	GPS_PDL_XPS				16

/* メディアプリント向けPDL(30～39予約済) */
#define	GPS_PDL_MP_GROUP		30
#define	GPS_PDL_MP_TIFF			30
#define	GPS_PDL_MP_JPEG			31

#define	GPS_PDL_PROGRAM			100
#define	GPS_PDL_PROGRAM_ID(n)		(100 + (n))

/* RICOH以外が実装するPDLで使用するID  GPS_PDL_RGROUP～GPS_PDL_PROGRAM-1 */
#define GPS_PDL_RGROUP			40	/* R_GROUP用開始位置 */
#define GPS_PDL_OTHERS			70	/* 第３者用開始位置  */

#define GPS_PDL_RG_KSKSSM		40	/* SHINDO RICOH KS/KSSM */
#define GPS_PDL_RG_KS			41	/* SHINDO RICOH KS      */
#define GPS_PDL_RG_KSSM			42	/* SHINDO RICOH KSSM    */
#define GPS_PDL_RG_KSP			43	/* SHINDO RICOH KSP     */

#define GPS_PDL_RG_FNP			45	/* FNP(富士通OEM) */
#define GPS_PDL_PAGES			46	/* PAGES */

/*
 *	request reqson
 */
#define	GPS_REQ_PROC_REASON_ENTERLANGUAGE	0	/* PJL ENTER LANGUAGE=XXX */
#define	GPS_REQ_PROC_REASON_FILETYPE		1	/* filetype=XXX */
#define	GPS_REQ_PROC_REASON_AUTOSENSE		2	/* auto sense */
#define	GPS_REQ_PROC_REASON_NOSENSE		3	/* no sense */
#define	GPS_REQ_PROC_REASON_EMCHGCMD		4	/* EM CHANGE COMMAND */
#define	GPS_REQ_PROC_REASON_PANEL		5	/* panel */
#define	GPS_REQ_PROC_REASON_IPDSTESTPRINT	6	/* IPDS Font List */
#define	GPS_REQ_PROC_REASON_IPDSFONTRESET	7	/* IPDS Fonr Reset */
/*
 *	Interpreter length definitio
 */
#define	GPS_INTERP_LEN_SHORTNAME	3	/* short name (byte) */

/*
 *	Interpreter Process Finish status
 */
#define	GPS_INTERP_FIN_NORMAL		0	/* normal end */
#define	GPS_INTERP_FIN_ERROR		1	/* error and data flushed */
#define	GPS_INTERP_FIN_CANCEL		2	/* cancelled */

/*
 *	Interpreter Status
 */
#define	GPS_INTERP_STATE_IDLE		0	/* idle */
#define	GPS_INTERP_STATE_PROCESSING	1	/* processing */
#define	GPS_INTERP_STATE_WAITING	2	/* waiting data */
#define	GPS_INTERP_STATE_FLUSHING	3	/* flushing data */

/*
 *	Interpreter test print request
 */
#define	GPS_INTERP_TESTPRINT_SUMMARY		0		/* summary */
#define	GPS_INTERP_TESTPRINT_FONTSET		1		/* fontset */
#define	GPS_INTERP_TESTPRINT_FONTALL		2		/* font all */
#define	GPS_INTERP_TESTPRINT_PROGRAM		3		/* program */
#define	GPS_INTERP_TESTPRINT_FORMLIST		4		/* formlist */
#define	GPS_INTERP_TESTPRINT_PSINFO		5		/* PostScript info list */
#define GPS_INTERP_TESTPRINT_COLORSAMPLE	6
#define GPS_INTERP_TESTPRINT_COLORMATCHING	7
#define GPS_INTERP_TESTPRINT_COLORTEST		8
#define GPS_INTERP_TESTPRINT_GAMMA_USER1	9
#define GPS_INTERP_TESTPRINT_GAMMA_USER2	10
#define GPS_INTERP_TESTPRINT_COLORSHIFT_SET	11
#define GPS_INTERP_TESTPRINT_COLORSHIFT_CHECK	12
#define GPS_INTERP_TESTPRINT_PDFINFO		13	/* PDF info list */
#define GPS_INTERP_TESTPRINT_MICR			20	/* MICR testsheet */
#define GPS_INTERP_TESTPRINT_GAMMA_SP(n)	(100+(n))

/*
 *	Interpreter EXT PDL
 */
#define	GPS_XPDL_ENTERLANG_LEN		16


/*
 *	PDL info structure
 */
typedef struct gps_pdl_info {
	char	pdl_id;
	char	interp_id;
	char	shortname[GPS_INTERP_LEN_SHORTNAME + 1];
	char	path;
	char	category[GPS_MINFO_KEY_PDL_CATEGORY_LEN + 1];
} gps_pdl_info_t;

/*
 *	XPDL enterlang table(PJLでのみ使用)
 */
typedef struct gps_xpdl_enterlang {
	char	pdl_id;	
	char	interp_id;
	char	enter_lang[GPS_XPDL_ENTERLANG_LEN + 1];
	char	reserve[13];
} gps_xpdl_enterlang_t;


#endif /* !_GPS_INTERP_H_ */
/*
 * Copyright (c) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 */
