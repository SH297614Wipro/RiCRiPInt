/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : modelinfo.h
 *   VERSION         : $Revision$
 *   AUTHOR          : Satoshi MIYAZAKI
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 04 Feb 2000: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_MODELINFO_H_
#define	_GPS_MODELINFO_H_

/*
 * gpsGetModelinfo()
 */
/* INPUT VALUE */
#define	MAX_KEY_LEN		(32)
#define	MAX_CATEGORY_LEN	MAX_KEY_LEN
#define	MAX_VALUE_LEN		MAX_KEY_LEN

#define	PATH_RESIDENT_ROM	(0)
#define	PATH_OPTION_DIMM1	(1)
#define	MAX_PATH_NUM		(1)	/* changed 2 -> 1 */

#define	CATEGORY_NOT_DEFINED	""

/* RETURN VALUE */
#define	SERCH_OK			(0)
#define	SERCH_KEY_NOT_FOUND		(-1)
#define	SERCH_CATEGORY_NOT_FOUND	(-2)
#define	SERCH_BUFFER_OVER		(-3)
#define	SERCH_ILLEGAL_PARAM		(-4)
#define	SERCH_INIT_ERROR		(-5)

extern int gpsGetModelInfo(gwmsg_client_t *client, char path, char num, const unsigned char *key, const unsigned char *category, unsigned char value_len, unsigned char *value);

#endif /* !_GPS_MODELINFO_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */
