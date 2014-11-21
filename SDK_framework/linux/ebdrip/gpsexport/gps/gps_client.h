/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : gps_client.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 18 Oct 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_CLIENT_H_
#define _GPS_CLIENT_H_

#include	<pthread.h>
#include	"gwipc.h"
#ifdef GWIPC_USE_SOCKET
#include	"gwipc_socket.h"
#else /*  GWIPC_USE_SOCKET */
#include	"gwipc_event.h"
#endif /*  GWIPC_USE_SOCKET */

extern int	gpsOpen(gwmsg_client_t *client, gwmsg_handler_t handler, pthread_attr_t *attr, void **shm_addr);

extern void	gpsClose(gwmsg_client_t *client, void *shm_addr);

#endif /* !_GPS_CLIENT_H_ */
/*
 * Copyright (c) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 */
