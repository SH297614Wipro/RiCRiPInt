/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : host.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 18 Oct 1999: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_HOST_H_
#define	_GPS_HOST_H_

#include	"gwipc.h"
#ifdef GWIPC_USE_SOCKET
#include	"gwipc_socket.h"
#else /* !GWIPC_USE_SOCKET */
#include	"gwipc_event.h"
#endif /* !GWIPC_USE_SOCKET */

#define	GPS_NEW_HOST

/*
 *	GPS Host buffer interface structure
 */
typedef struct gps_hostdesc {
	int			host_id;		/* GPS set */
#define	GPS_HOST_DIR_RECV		0
#define	GPS_HOST_DIR_SEND		1
	unsigned char		host_dir;		/* GPS set */
	long			host_period;		/* GPS set */
	int			HostBuf_shmid;		/* GPS set */
	long			HostBuf_offset;		/* GPS set */
	int			buf_shmid;		/* GPS set */
	long			buf_offset;		/* GPS set */
} gps_hostdesc_t;

typedef struct gps_hostctl {
	unsigned long		size;		/* size(byte) of *buf */
	volatile unsigned char	eof;		/* EOF flag */
	volatile unsigned char	intr;
	unsigned short		reserved;
	volatile unsigned long	in;		/* size(byte) of input data */
	volatile unsigned long	out;		/* size(byte) of read data */
	unsigned char		*buf;		/* buffer body */
} gps_hostctl_t;

#ifdef __cplusplus
#define	ARG_GPS_SIN_AVAIL	struct gps_hostbuf *
#define	ARG_GPS_SIN_GETC	struct gps_hostbuf *
#define	ARG_GPS_SIN_READ	struct gps_hostbuf *, unsigned char *, long, int
#define	ARG_GPS_SIN_PEEK	struct gps_hostbuf *, unsigned char *, long, int
#define	ARG_GPS_SIN_PEEKC	struct gps_hostbuf *
#define	ARG_GPS_SIN_SEEK	struct gps_hostbuf *, long
#define	ARG_GPS_SIN_AVAILEOF	struct gps_hostbuf *, long *
#else
#define	ARG_GPS_SIN_AVAIL
#define	ARG_GPS_SIN_GETC
#define	ARG_GPS_SIN_READ
#define	ARG_GPS_SIN_PEEK
#define	ARG_GPS_SIN_PEEKC
#define	ARG_GPS_SIN_SEEK
#define	ARG_GPS_SIN_AVAILEOF
#endif

typedef struct gps_hostbuf {
	gps_hostdesc_t		_hostdesc;		/* GPS set */
	gwmsg_client_t		*client;		/* LIB use */
	long			host_size;		/* LIB use */
	unsigned long		host_mode;		/* LIB use */
	unsigned char		*host_start;		/* LIB use */
	unsigned char		*host_end;		/* LIB use */
	unsigned char		*host_head;		/* LIB use */
	unsigned char		*host_cur;		/* LIB use */
	long			host_cnt;		/* LIB use */
	unsigned long		host_in;		/* LIB use */
	unsigned long		host_out;		/* LIB use */
	int			host_ctl_a;		/* LIB use */
	int			host_ctl_eof;		/* LIB use */
	unsigned char		*host_peek_head;	/* LIB use */
	unsigned char		*host_peek_cur;		/* LIB use */
	unsigned long		host_peek_cnt;		/* LIB use */
	unsigned long		host_peek_out;		/* LIB use */
	unsigned int		host_peek_reset;	/* LIB use */
	int			host_peek_ctl_a;	/* LIB use */
	int			host_peek_ctl_eof;	/* LIB use */
	long			(*gpsSinAvail)(ARG_GPS_SIN_AVAIL);
							/* LIB use */
	int			(*gpsSinGetc)(ARG_GPS_SIN_GETC);
							/* LIB use */
	long			(*gpsSinRead)(ARG_GPS_SIN_READ);
							/* LIB use */
	long			(*gpsSinPeek)(ARG_GPS_SIN_PEEK);
					      		/* LIB use */
	int			(*gpsSinPeekc)(ARG_GPS_SIN_PEEKC);
							/* LIB use */
	int			(*gpsSinSeek)(ARG_GPS_SIN_SEEK);
							/* LIB use */
	int			(*gpsSinAvailEof)(ARG_GPS_SIN_AVAILEOF);
							/* LIB use */
	gps_hostctl_t		*_HostBuf;		/* LIB use */
	pthread_mutex_t		mutex_HostWait;	/* mutex for waiting */
	pthread_cond_t		cond_HostWait;	/* condition for waiting */
	char			event_HostWait;/* event value for waiting */
} gps_hostbuf_t, *gps_hostbuf_p;

#define	_host_id		_hostdesc.host_id
#define	_host_dir		_hostdesc.host_dir
#define	_host_period		_hostdesc.host_period
#define	_host_eof		_HostBuf->eof
#define	_host_intr		_HostBuf->intr
#define	_host_in		_HostBuf->in
#define	_host_out		_HostBuf->out
#define	_host_buf		_HostBuf->buf

/*
 *	standard input functions.
 */
#define	GPS_HOST_NONBLOCK	0x0001

#define	GPS_HOST_CONTROL_GET	0		/* gpsSinControl() */
#define	GPS_HOST_CONTROL_SET	1		/* gpsSinControl() */

#define	GPS_HOST_MODE_STANDARD	0x00000000	/* gpsSinControl() */
#define	GPS_HOST_MODE_BCP	0x00000001	/* gpsSinControl() */
#define	GPS_HOST_MODE_NORMAL	0x00000002	/* gpsSinControl() */
#define	GPS_HOST_MODE_PROT_MASK	0x0000000f	/* gpsSinControl() */

extern gps_hostbuf_p	gpsSinOpen(gwmsg_client_t *client, int hostid);
extern int		gpsSinClose(gps_hostbuf_p hostbuf);
extern int		gpsSinControl(gps_hostbuf_p hb,
					int action, unsigned long *mode);
extern void		gpsSinPeekReset(gps_hostbuf_p hostbuf);

static __inline long
gpsSinAvail(gps_hostbuf_p hb)
{
	return (*hb->gpsSinAvail)(hb);
}

static __inline int
gpsSinGetc(gps_hostbuf_p hb)
{
	return (*hb->gpsSinGetc)(hb);
}

static __inline long
gpsSinRead(gps_hostbuf_p hb, unsigned char *buf, long len, int flag)
{
	return (*hb->gpsSinRead)(hb, buf, len, flag);
}

static __inline int
gpsSinPeekc(gps_hostbuf_p hb)
{
	return (*hb->gpsSinPeekc)(hb);
}

static __inline long
gpsSinPeek(gps_hostbuf_p hb, unsigned char *buf, long len, int flag)
{
	return (*hb->gpsSinPeek)(hb, buf, len, flag);
}

static __inline int
gpsSinSeek(gps_hostbuf_p hb, long len)
{
	return (*hb->gpsSinSeek)(hb, len);
}

static __inline int
gpsSinAvailEof(gps_hostbuf_p hb, long *len)
{
	return (*hb->gpsSinAvailEof)(hb, len);
}

/*
 *	standard output functions.
 */
extern gps_hostbuf_p	gpsSoutOpen(gwmsg_client_t *client, int hostid);
extern int		gpsSoutPutc(gps_hostbuf_p hostbuf, int c);
extern long		gpsSoutWrite(gps_hostbuf_p hostbuf,
				unsigned char *buf, long len, int flag);
extern int		gpsSoutFlush(gps_hostbuf_p hostbuf);
extern int		gpsSoutClose(gps_hostbuf_p hostbuf);

#endif /* !_GPS_HOST_H_ */
/*
 * Copyright (c) 1998 Ricoh Company, Ltd.  All Rights Reserved.
 */
