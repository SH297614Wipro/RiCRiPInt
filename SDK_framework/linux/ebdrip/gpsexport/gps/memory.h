/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : memory.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 8 Nov 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_MEMORY_H_
#define	_GPS_MEMORY_H_

/*
 *	Font
 */
#define	GPS_FONT_SUMMARY	0	/* for summary */
#define	GPS_FONT_COMMON		1	/* for emulation */
#define	GPS_FONT_PCL		2	/* for PCL */
#define	GPS_FONT_PS		3	/* for PS */
#define	GPS_FONT_PSDOM		4	/* for PSDOM */
#define	GPS_FONT_PSDOMOPT	5	/* for PSDOM option*/
#define	GPS_FONT_RPGLEXP	6	/* for RPGL(EXP) */
#define	GPS_FONT_MAX		7

typedef struct gps_fontinfo {
	unsigned char	*addr;
	unsigned long	size;
	unsigned long	offset;
} gps_fontinfo_t;

/*
 *	NVRAM
 */
#define	GPS_NVFILE_NAME_LEN	4

/*
 *	HDD
 */
#define	GPS_HDD_DOWNLOAD		0
#define	GPS_HDD_SPOOL			1	/* 2001/06/20 */
#define	GPS_RAM_DOWNLOAD		2	/* 2003/02/18 */
#define	GPS_RAM_SPOOL			3	/* 2003/02/18 */
#define	GPS_HDD_TMP				4	/* 2003/11/20 */
#define	GPS_SD_DOWNLOAD			5	/* 2004/10/19 */
#define	GPS_HDD_IPDS_DOWNLOAD	6	/* IPDSêÍóp 2006/04/28 */
#define	GPS_SD_IPDS_DOWMLOAD	7	/* IPDSêÍóp 2006/04/28 */
#define	GPS_SD_PICTBRIDGE		8	/* 2006/06/13 */
#define	GPS_HDD_DATA			9

#define	GPS_MAX_HDD_PATH_LEN	64

typedef struct gps_hddinfo {
	char	path[GPS_MAX_HDD_PATH_LEN];
} gps_hddinfo_t;

#endif /* !_GPS_MEMORY_H_ */
/*
 * Copyright (c) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 */
