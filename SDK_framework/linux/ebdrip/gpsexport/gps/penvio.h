/******************************************************
 * $Id$
 *
 * Copyright (C) 2001 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : penvio.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 11 Jum 2001: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_PENVIO_H_
#define _GPS_PENVIO_H_

extern int	gpsPenvGetVarList( gwmsg_client_t* client, int penv, long start, long num, long *var, long *var_size );
extern int	gpsPenvGetValueList( gwmsg_client_t* client, int penv, long var, long start, long num, long *value, long *value_size );
extern int	gpsPenvSetData(gwmsg_client_t* client, int penv, long var, void *val, long val_size, int *result);
extern int	gpsPenvGetData(gwmsg_client_t* client, int penv, long var, void *val, long in_size, long *out_size, int *result);

#endif /* !_GPS_PENVIO_H_ */
/*
 * Copyright (c) 2001 Ricoh Company, Ltd.  All Rights Reserved.
 */
