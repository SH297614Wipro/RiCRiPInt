/******************************************************
 * $Id$
 *
 * Copyright (C) 2001 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : info.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 05 Feb 2001: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_RGATE_H_
#define	_GPS_RGATE_H_
#include	"penv_var.h"

#define	GPS_RGATE_LOG_FILENAME	"Sys/RICOH_LOG_FILE"

/*
 *	gps_rgateparam_var_t flags
 */
#define	GPS_RGATEPARAM_USERID			(1 << 0)
#define	GPS_RGATEPARAM_DATE			(1 << 1)
#define	GPS_RGATEPARAM_TIME			(1 << 2)
#define	GPS_RGATEPARAM_GROUPID			(1 << 3)
#define	GPS_RGATEPARAM_HOSTNAME			(1 << 4)
#define	GPS_RGATEPARAM_COMMENT			(1 << 5)
#define	GPS_RGATEPARAM_LIMITPAGES		(1 << 6)
#define	GPS_RGATEPARAM_INFO			(1 << 7)

/*
 *	MAX length
 */
#define	GPS_MAX_RGATEPARAM_USERID_LEN		32
#define	GPS_MAX_RGATEPARAM_DATE_LEN		12
#define	GPS_MAX_RGATEPARAM_TIME_LEN		12
#define	GPS_MAX_RGATEPARAM_GROUPID_LEN		12
#define	GPS_MAX_RGATEPARAM_HOSTNAME_LEN		32
#define	GPS_MAX_RGATEPARAM_COMMENT_LEN		32
#define	GPS_MAX_RGATEPARAM_INFO_LEN		78
#define	GPS_MAX_RGATEPARAM_PRINTERNAME_LEN	32

typedef struct gps_rgateparam_var {
	unsigned long	flag;
	union {
		unsigned char	userid[GPS_MAX_RGATEPARAM_USERID_LEN + 1];
		unsigned char	date[GPS_MAX_RGATEPARAM_DATE_LEN + 1];
		unsigned char	time[GPS_MAX_RGATEPARAM_TIME_LEN + 1];
		unsigned char	groupid[GPS_MAX_RGATEPARAM_GROUPID_LEN + 1];
		unsigned char	hostname[GPS_MAX_RGATEPARAM_HOSTNAME_LEN + 1];
		unsigned char	comment[GPS_MAX_RGATEPARAM_COMMENT_LEN + 1];
		unsigned int	limitpages;
		unsigned char	info[GPS_MAX_RGATEPARAM_INFO_LEN + 1];
	} rp;
} gps_rgateparam_var_t;

typedef struct gps_rgateparam {
	unsigned char	userid[GPS_MAX_RGATEPARAM_USERID_LEN];
	unsigned char	groupid[GPS_MAX_RGATEPARAM_GROUPID_LEN];
	unsigned char	date[GPS_MAX_RGATEPARAM_DATE_LEN];
	unsigned char	time[GPS_MAX_RGATEPARAM_TIME_LEN];
	unsigned char	hostname[GPS_MAX_RGATEPARAM_HOSTNAME_LEN];
	unsigned char	printername[GPS_MAX_RGATEPARAM_PRINTERNAME_LEN];
	unsigned char	comment[GPS_MAX_RGATEPARAM_COMMENT_LEN];
	unsigned char	duplex;
	unsigned char	mono_color;
	unsigned char	info[GPS_MAX_RGATEPARAM_INFO_LEN];
	unsigned int	pagesize;
	unsigned int	limitpages;
	unsigned int	pages;
} gps_rgateparam_t;
#endif /* !_GPS_RGATE_H_ */
/*
 * Copyright (c) 2001 Ricoh Company, Ltd.  All Rights Reserved.
 */
