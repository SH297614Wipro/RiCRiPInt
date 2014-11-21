/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : infoio.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 14 Mar 2000: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_INFOIO_H_
#define _GPS_INFOIO_H_

extern void	gpsInfoIoInit(gwmsg_client_t *client);
extern int	gpsGetSysInfo(gwmsg_client_t* client, gps_sysinfo_t *sysinfo );
extern long	gpsGetTotalCounter(gwmsg_client_t *client);
extern int	gpsGetTrayInfo(gwmsg_client_t* client, int num, gps_trayinfo_t *trayinfo, long *trayinfo_size, int notify);
extern int	gpsGetBinInfo(gwmsg_client_t* client, int num, gps_bininfo_t *bininfo, long *bininfo_size, int notify);
extern int	gpsGetPrtStatus2(gwmsg_client_t* client, gps_prtstatus2_t *prtstatus, int notify, int *result);
extern int	gpsGetTrayInfoBusy(gwmsg_client_t* client, int num, gps_trayinfo_t *trayinfo, long *trayinfo_num, int notify, int *result);
extern int	gpsGetUcpParam( gwmsg_client_t* client, int ujobid, gps_ucp_param_t *ucpparam, int *result);
extern int	gpsGetPrtTotalCounter(gwmsg_client_t *client, gps_prtcnt_t *prtcnt, int *result);


#endif /* !_GPS_INFOIO_H_*/
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */
