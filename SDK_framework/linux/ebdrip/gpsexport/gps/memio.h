/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : memio.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 10 Apr 2000: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_MEMIO_H_
#define _GPS_MEMIO_H_

extern void	gpsMemIoInit(gwmsg_client_t *client);
extern caddr_t	gpsWkMalloc(gwmsg_client_t *client, long size);
extern int	gpsGetFontInfo(gwmsg_client_t* client, int font, gps_fontinfo_t *fontinfo);

#endif /* !_GPS_MEMIO_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */
