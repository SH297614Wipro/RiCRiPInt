/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : jobio.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 5 Nov 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_JOBIO_H_
#define	_GPS_JOBIO_H_
extern int	gpsUjobSetParamVar(gwmsg_client_t *client, int ujobid,
					gps_ujobparam_var_t *ujobparam_var);
extern int	gpsUjobGetParamVar(gwmsg_client_t *client, int ujobid,
					gps_ujobparam_var_t *ujobparam_var);
#endif /* !_GPS_JOBIO_H_ */
/*
 * Copyright (c) 1998 Ricoh Company, Ltd.  All Rights Reserved.
 */
