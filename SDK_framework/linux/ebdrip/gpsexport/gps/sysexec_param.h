/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : sys_exec_param.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 12 Mar 2000: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_SYSEXEC_PARAM_H_
#define _GPS_SYSEXEC_PARAM_H_

#define SYSEXECSTRSIZE  (16)

typedef union gps_sysexec_member
{
    char            cVal;
    unsigned char   ucVal;
    short           sVal;
    unsigned short  usVal;
    long            lVal;
    unsigned long   ulVal;
    int             nVal;
    unsigned int    unVal;
    char            strVal[SYSEXECSTRSIZE];

} GPS_SYSEXEC_MEMBER, *PGPS_SYSEXEC_MEMBER;

typedef struct gps_sysexec_param {
	int	key;
    GPS_SYSEXEC_MEMBER member;
} gps_sysexec_param_t;
#endif /* !_GPS_SYSEXEC_PARAM_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */
