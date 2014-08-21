/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : nvram.h
 *   VERSION         : $Revision$
 *   AUTHOR          : Satoshi MIYAZAKI
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 06 Mar 2000: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_NVRAM_H_
#define	_GPS_NVRAM_H_

extern	int gpsNvWrite(gwmsg_client_t *client, char *fname, long fname_size, char *data, long data_size);
extern	int gpsNvRead(gwmsg_client_t *client, char *fname, long fname_size, char *data, long *data_size, long size);
extern	void gpsNvDelete(gwmsg_client_t *client, char *fname, long fname_size);
extern	int gpsNvFileCheck(gwmsg_client_t *client, char *fname, long fname_size);


#endif /* !_GPS_NVRAM_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */

