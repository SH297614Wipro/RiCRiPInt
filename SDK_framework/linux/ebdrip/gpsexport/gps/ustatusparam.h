/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : ustatusparam.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 18 Oct 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_USTATUSPARAM_H_
#define	_GPS_USTATUSPARAM_H_

#define GPS_USTATUS_OFF     (0)
#define GPS_USTATUS_ON      (1)
#define GPS_USTATUS_VERBOSE (2)

typedef struct gps_ustatusparam {
#define	GPS_USTATUS_DEVICE		(1 << 0)
#define	GPS_USTATUS_JOB			(1 << 1)
#define	GPS_USTATUS_PAGE		(1 << 2)
#define	GPS_USTATUS_TIMED		(1 << 3)
	unsigned long		flag;
	unsigned char		device;		/* 0->OFF 1->ON 2->VERBOSE */
	unsigned char		job;		/* 0->OFF 1->ON */
	unsigned char		page;		/* 0->OFF 1->ON */
	unsigned short		timed;		/* 0(OFF), 5-300 (sec) */
} gps_ustatusparam_t;

#endif /* !_GPS_USTATUSPARAM_H_ */
/*
 * Copyright (c) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 */
