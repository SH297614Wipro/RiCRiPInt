/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : modelinfo_key.h
 *   VERSION         : $Revision$
 *   AUTHOR          : Nobuhiro SHINDOH
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 02 Mar 2000: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_MODELINFO_KEY_H_
#define	_GPS_MODELINFO_KEY_H_

/*
 *	CATEGORY
 */
#define	GPS_MINFO_CATEGORY_PRINTER	"PRINTER"
#define	GPS_MINFO_CATEGORY_HDD		"HDD"

/*
 *	common
 */
#define	GPS_MINFO_KEY_VERSION		"version"

/*
 *	PRINTER
 */
#define	GPS_MINFO_KEY_VOID_PDL		"void_pdl"
#define	GPS_MINFO_KEY_WORK_MAP		"workmap"
#define	GPS_MINFO_KEY_NVSYSCLR		"nvsysclr"
#define GPS_MINFO_KEY_INITIAL_BITSW	"ibitsw"
#define GPS_MINFO_KEY_DISP_LINES	"disp_lines"
#define GPS_MINFO_KEY_DISP_COLUMNS	"disp_columns"
#define GPS_MINFO_KEY_RPCS_LANG_VER	"remote_version"
#define	GPS_MINFO_KEY_SORT_RAMSIZE	"sort_ramsize"
#define	GPS_MINFO_KEY_PREMAP_RSVSIZE	"premap_rsvsize"


/*
 *	HDD category
 */
#define	GPS_MINFO_KEY_HDD_CATEGORY	"hdd_category"
#define	GPS_MINFO_KEY_HDD_CATEGORY_LEN	7
#define	GPS_MINFO_KEY_HDD_ID		"hdd_id"
#define	GPS_MINFO_KEY_HDD_PATH		"hdd_path"
#define	GPS_MINFO_KEY_HDD_STANDARD	"hdd_standard"
#define	GPS_MINFO_KEY_HDD_MAP		"hddmap"
#define	GPS_MINFO_KEY_SD_MAP		"sdmap"
#define	GPS_MINFO_KEY_SD_SIZE		"sd_size"

/*
 *	PDL
 */
#define	GPS_MINFO_KEY_PDL_CATEGORY	"pdl_category"
#define	GPS_MINFO_KEY_PDL_CATEGORY_LEN	7
#define	GPS_MINFO_KEY_SHORTNAME		"sname"
#define	GPS_MINFO_KEY_INTERP_ID		"interp_id"
#define	GPS_MINFO_KEY_PDL_ID		"pdl_id"
#define	GPS_MINFO_KEY_EXEC_DIR		"exec_dir"
#define	GPS_MINFO_KEY_EXEC_PATH		"exec_path"
#define	GPS_MINFO_KEY_DISP_FEEDTRAY	"disp_feedtray"
#define	GPS_MINFO_KEY_DISP_MSIS		"disp_msis"
#define	GPS_MINFO_KEY_DISP_FONT		"disp_font"
#define	GPS_MINFO_KEY_DISP_FORM		"disp_form"
#define	GPS_MINFO_KEY_CSIG_CONTROL	"csig_control"
#define	GPS_MINFO_KEY_LONGNAME		"lname"			/* used MIB */
#define	GPS_MINFO_KEY_LANGFAMILY	"LangFamily"		/* used MIB */
#define	GPS_MINFO_KEY_LANGLEVEL		"LangLevel"		/* used MIB */
#define	GPS_MINFO_KEY_TWOWAY		"TwoWay"		/* used MIB */
#define	GPS_MINFO_KEY_PDL2_CATEGORY	"pdl2_category"		/* used MIB */
#define GPS_MINFO_KEY_XPDL_MENU_NAME1   "xpdl_menu_name1"
#define GPS_MINFO_KEY_XPDL_MENU_NAME2   "xpdl_menu_name2"
#define GPS_MINFO_KEY_XPDL_MENU_NAME3   "xpdl_menu_name3"
#define GPS_MINFO_KEY_XPDL_MENU_NAME4   "xpdl_menu_name4"
#define GPS_MINFO_KEY_XPDL_MENU_NAME5   "xpdl_menu_name5"
#define GPS_MINFO_KEY_XPDL_MENU_NAME6   "xpdl_menu_name6"
#define GPS_MINFO_KEY_XPDL_MENU_NAME7   "xpdl_menu_name7"
#define GPS_MINFO_KEY_XPDL_MENU_NAME8   "xpdl_menu_name8"
#define GPS_MINFO_KEY_XPDL_MENU_NAME9   "xpdl_menu_name9"
#define	GPS_MINFO_KEY_CENTRO_TWOWAY	"centro_twoway"
#define GPS_MINFO_KEY_MEDIA_TYPE	"media_type"
#define	GPS_MINFO_KEY_FEED_CONTROL	"feed_control"
#define GPS_MINFO_KEY_MIXEDROT		"MixedRot"
#define GPS_MINFO_KEY_ENDIAN		"Endian"
#define GPS_MINFO_KEY_INTERRUPT		"interrupt"

/*
 *	OFONT	(Outline KANJI Font)
 */
#define	GPS_MINFO_KEY_OFONT_CATEGORY	"ofont_category"
#define	GPS_MINFO_KEY_OFONT_ENAME	"ofont_ename"
#define	GPS_MINFO_KEY_OFONT_JNAME	"ofont_jname"

/*
 *	CPF	(Color ProFile)
 */
#define	GPS_MINFO_KEY_CPF_CATEGORY	"cpf_category"
#define	GPS_MINFO_KEY_CPF_FILE		"cpf_file"
#define	GPS_MINFO_KEY_CPF_MEDIA		"cpf_media"
#define	GPS_MINFO_KEY_CPF_PATH		"cpf_path"

#endif /* !_GPS_MODELINFO_KEY_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */
