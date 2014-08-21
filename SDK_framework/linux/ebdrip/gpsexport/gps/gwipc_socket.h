/***** -*- C -*- **************************************
 * $Id: gwipc_socket.h,v 1.1 2006/03/09 05:38:49 senda Exp $
 *
 * Copyright(C) 1999 RICOH CO.LTD
 *   ORDER           : gwipc socket version
 *   PROGRAM NAME    : libgwipc
 *   FILE NAME       : gwipc_socket.h
 *   VERSION         : $Revision: 1.1 $
 *   DESIGNER        : SENDA Shigeya
 *   AUTHOR          : $Author: senda $
 *-----------------------------------------------------
 *       HISTORY
 *	 senda - 16 May 1999: Created.
 *	 $Log: gwipc_socket.h,v $
 *	 Revision 1.1  2006/03/09 05:38:49  senda
 *	 first comit to LPUX2.0
 *	
 *	 Revision 1.1.1.1  2001/09/30 04:00:19  hyuki
 *	 imported from mips version GWIPC_20010919
 *	
 *	 Revision 1.5  1999/09/14 06:13:56  senda
 *	 try to open socket in /udom/XXX before /tmp/XXX
 *	
 *	 Revision 1.4  1999/09/09 11:26:26  senda
 *	 logging support
 *	
 *	 Revision 1.3  1999/08/18 01:17:59  senda
 *	 hashmacro : fixed un-initialized next member on malloced queue element
 *	 *.h : fix compile problems
 *	
 *	 Revision 1.2  1999/08/09 02:06:56  senda
 *	 table size increased for FCS (over 64 functions)
 *	
 *	 Revision 1.1.1.1  1999/06/10 11:01:34  senda
 *	 GWIPC
 *	
 ******************************************************/

#ifndef __GWIPC_SOCKET_H__
#define __GWIPC_SOCKET_H__

#ifdef GWIPC_USE_SOCKET

#include <stdlib.h>
#include "hashmacro.h"
#include "retqueue.h"

#define GWS_SELF_POST	0x8000


#define	GWMSG_HASH_SIZE		64
#define	MAX_GWMSG_HANDLER	64

MakeHashDefs(gwf_, GWMSG_HASH_SIZE, MAX_GWMSG_HANDLER);

/*
 * server side handler (socket version)
 */
#define GWS_SOCKN	16

struct _gwmsg_server {
    gwerr_handler_t	error_handler;
    gwmsg_srv_handler_t	default_handler;
    gwmsg_srv_handler_t	logging_handler;
    int			type;		/* server type			*/
    char		procname[16];	/* process(server) name		*/
    /*-- private --*/
    gwf_hash_tbl_t	hash;		/* hash table for message func	*/
    /*-- thread --*/
    pthread_t		dispatcher;	/* client_dispatcher thread	*/
    /*-- socket specific --*/
    int			sockfd;		/* socket fd			*/
    int			fds[GWS_SOCKN];	/* accepted socket fd		*/
    int			fdbit;		/* active fd in fds		*/
    int			pfd[2];		/* socket pair fd		*/
};
typedef struct _gwmsg_server gwmsg_server_t;

/*
 * client side handler (socket version)
 */
#define	RETQUEUESIZE 8

struct _gwmsg_client {
    gwerr_handler_t	error_handler;
    gwmsg_handler_t	default_handler;
    gwmsg_handler_t	logging_handler;
    long		fid;
    /*-- private --*/
    retqueue_t		retqueue;
    rq_elm_t		elm[ RETQUEUESIZE ];
    gwf_hash_tbl_t	hash;
    /*-- socket --*/
    int			fd;		/* socket fd */
    /*-- thread --*/
    pthread_t		dispatcher;	/* client_dispatcher thread */
};
typedef struct _gwmsg_client gwmsg_client_t;


/* lpuxÇÃnfsÇ»Çµé¿ã@Ç≈Ç‚ÇÈèÍçá /udom Ç…ïœÇ¶ÇÈÅB*/
#if defined(mips) && defined(__NetBSD__)
#  define PATH_UNIXDOMAIN "/udom/"
#  define PATH_UNIXDOMAIN2 "/tmp/"
#else
#  define PATH_UNIXDOMAIN "/udom/"
#  define PATH_UNIXDOMAIN2 "/tmp/"
#endif

#endif

#endif /* __GWIPC_SOCKET_H__ */
/*
 * Local Variables:
 * c-basic-offset: 4
 * End:
 */
