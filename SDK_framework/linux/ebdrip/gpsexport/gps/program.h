/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : program.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 18 Oct 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_PROGRAM_H_
#define	_GPS_PROGRAM_H_

/*
 * Misc Definition
 */
#define	GPS_PROG_NAME_LEN	3

/*
 *	Program Table
 */
typedef struct gps_progtable {
	char		name[GPS_PROG_NAME_LEN];
	unsigned char	fileno;
} gps_progtable_t, *gps_prograble_p;

/*
 *	Program Requests
 */
#define	GPS_PROG_ENTRY		0		/* program entry */
#define	GPS_PROG_DELETE		1		/* program delete */

/*
 * Functions
 */
int gpsProgGetNum(gwmsg_client_t *client);
int gpsProgGetTable(gwmsg_client_t *client, int num, gps_progtable_t **progtable, long *progtable_size);
int gpsProgEntry(gwmsg_client_t *client, int prog_no, char *name, long name_len, int fileno);
int gpsProgDelete(gwmsg_client_t *client, int prog_no);
int gpsProgNvWrite(gwmsg_client_t *client, char *name, int name_size, int fileno, char *data, int data_size);
int gpsProgNvRead(gwmsg_client_t *client, char *name, int name_size, int fileno, char *data, long *data_size, long size);
int gpsProgNvDelete(gwmsg_client_t *client, char *name, int name_size, int fileno);

#endif /* !_GPS_PROGRAM_H_ */
/*
 * Copyright (c) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 */

