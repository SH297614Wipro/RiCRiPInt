/***** -*- C -*- **************************************
 * $Id: gwipc.h,v 1.2 2007/01/09 03:17:48 senda Exp $
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *   ORDER           : inter process communication routines
 *		       for GW architecture
 *   PROGRAM NAME    : libgwipc
 *   FILE NAME       : gwipc.h
 *   VERSION         : $Revision: 1.2 $
 *   DESIGNER        : S.Senda
 *   AUTHOR          : $Author: senda $
 *-----------------------------------------------------
 *       HISTORY
 *	 senda -  4 Feb 1999: Created.
 *	 $Log: gwipc.h,v $
 *	 Revision 1.2  2007/01/09 03:17:48  senda
 *	 add remain_timer.
 *	
 *	 Revision 1.1  2006/03/09 05:38:49  senda
 *	 first comit to LPUX2.0
 *	
 *	 Revision 1.1.1.1  2001/09/30 04:00:19  hyuki
 *	 imported from mips version GWIPC_20010919
 *	
 *	 Revision 1.21  2000/06/13 05:45:28  senda
 *	 gwipc_destroy_timer() added.
 *	
 *	 Revision 1.20  2000/06/13 05:07:58  senda
 *	 gwipc_close_client() added.
 *	
 *	 Revision 1.19  2000/06/13 04:35:45  senda
 *	 ending functions added for memory leak checking.
 *	
 *	 Revision 1.18  2000/01/22 09:57:21  senda
 *	 STATISTICS/ITRON_DUMP feature.
 *	
 *	 Revision 1.17  2000/01/05 09:13:44  senda
 *	 use -Wall to compile.
 *	
 *	 Revision 1.16  1999/12/08 03:26:17  senda
 *	 init_client  char * -> const char *
 *	
 *	 Revision 1.15  1999/11/10 02:24:55  senda
 *	 gwipcgen: use gwipc_funcall and gwipc_funcall_oneway for ipc function call.
 *	
 *	 Revision 1.14  1999/11/09 11:35:11  senda
 *	 bugfix: ERR_RETQUEUE if no process switch is occured between call_func and wait_fret
 *	
 *	 Revision 1.13  1999/11/04 04:21:43  senda
 *	 message size limit restriction added.
 *	
 *	 Revision 1.12  1999/09/09 11:26:25  senda
 *	 logging support
 *	
 ******************************************************/

#ifndef __GWIPC_H__
#define __GWIPC_H__

/* --------------------------------------------------------------------
 * message structure
 */
typedef struct _gwmsg {
    unsigned short	type;		/* message type			   */
    unsigned short	length;		/* message length (include header) */
    pid_t		pid;		/* message origin (pid)		   */
    char		message[0];	/* message content                 */
} gwmsg_t;

typedef struct _gwfunc {
    unsigned short	type;		/* message type			   */
    unsigned short	length;		/* message length (include header) */
    pid_t		pid;		/* message origin (pid)		   */
    unsigned long	fid;		/* function id			   */
    char		message[0];	/* message content                 */
} gwfunc_t;

#define	GWMSG_FUNCTION	0x8000		/* 関数用msgのIDを示すbit	   */
#define	GWMSG_RETURN	0xc000		/* 関数戻り値用msgのIDを示すbit	   */

#define GWIPC_SELF_CID	(-1)		/* selfメッセージのcid		   */

#define	GWIPC_MSG_SIZE_MAX	128	/* 最大msgサイズ		   */

/* --------------------------------------------------------------------
 * 共通ハンドラ定義
 */
typedef int (*gwerr_handler_t)(void *, gwmsg_t *, int errid);
typedef int (*gwmsg_handler_t)(void *, gwmsg_t *);

/* --------------------------------------------------------------------
 * server side defs
 */
struct _gwmsg_server;
typedef struct _gwmsg_server * gwmsg_server_p;

typedef long gwmsg_client_id_t;
typedef int (*gwmsg_srv_handler_t)(void *, gwmsg_t *, gwmsg_client_id_t);

#define GWS_SELF_POST	0x8000

/* --------------------------------------------------------------------
 * client side defs
 */
struct _gwmsg_client;
typedef struct _gwmsg_client * gwmsg_client_p;

/* --------------------------------------------------------------------
 * GWIPC function decls (to path -Wunused)
 */
/** functions for server **/
static __inline int
gwipc_init_server(gwmsg_server_p st, const char *procname,
		  gwerr_handler_t error_handler)
__attribute__ ((unused));

static __inline int
gwipc_close_server(gwmsg_server_p st)
__attribute__ ((unused));

static __inline int
gwipc_set_server_handler(gwmsg_server_p st, long id, gwmsg_srv_handler_t h)
__attribute__ ((unused));

static __inline void
gwipc_set_default_server_handler(gwmsg_server_p st, gwmsg_srv_handler_t h)
__attribute__ ((unused));

static __inline void
gwipc_set_logging_server_handler(gwmsg_server_p st, gwmsg_srv_handler_t h)
__attribute__ ((unused));

static __inline int
gwipc_dispatch(gwmsg_server_p st)
__attribute__ ((unused));

static __inline void
gwipc_run_server(gwmsg_server_p st, pthread_attr_t* attr)
__attribute__ ((unused));

static __inline void
gwipc_end_server(gwmsg_server_p st)
__attribute__ ((unused));

static __inline gwmsg_t*
gwipc_svmsg_alloc(gwmsg_server_p c, long msgid, size_t size)
__attribute__ ((unused));

static __inline void
gwipc_svmsg_free( gwmsg_server_p c, gwmsg_t* msg )
__attribute__ ((unused));

static __inline void
gwipc_svmsg_send( gwmsg_server_p c, gwmsg_t* msg, gwmsg_client_id_t cid )
__attribute__ ((unused));

/** functions for skelton (server). **/
static __inline gwfunc_t *
gwipc_fret_alloc( gwmsg_server_p st, long id, size_t sz )
__attribute__ ((unused));

static __inline void
gwipc_ret_func( gwmsg_server_p st,
		gwfunc_t* fc, gwfunc_t* fr, gwmsg_client_id_t cid )
__attribute__ ((unused));

/** functions for client **/
static __inline int
gwipc_init_client(gwmsg_client_p c, const char * procname, gwerr_handler_t h)
__attribute__ ((unused));

static __inline int
gwipc_end_client(gwmsg_client_p c)
__attribute__ ((unused));

static __inline int
gwipc_close_client(gwmsg_client_p c)
__attribute__ ((unused));

static __inline int
gwipc_set_client_handler(gwmsg_client_p c, long id, gwmsg_handler_t h)
__attribute__ ((unused));

static __inline void
gwipc_set_default_client_handler(gwmsg_client_p c, gwmsg_handler_t h)
__attribute__ ((unused));

static __inline void
gwipc_set_logging_client_handler(gwmsg_client_p c, gwmsg_handler_t h)
__attribute__ ((unused));

static __inline void
gwipc_run_client(gwmsg_client_p c, pthread_attr_t* attr)
__attribute__ ((unused));

static __inline gwmsg_t*
gwipc_msg_alloc(gwmsg_client_p c, long msgid, size_t size)
__attribute__ ((unused));

static __inline void
gwipc_msg_free( gwmsg_client_p c, gwmsg_t* msg )
__attribute__ ((unused));

static __inline void
gwipc_msg_send( gwmsg_client_p c, gwmsg_t* msg )
__attribute__ ((unused));

/** functions for stub (client). don't call from application directly. **/
static __inline gwfunc_t*
gwipc_get_fc( gwmsg_client_p c, long msg_id, size_t size )
__attribute__ ((unused));

static __inline void
gwipc_call_func( gwmsg_client_p c, gwfunc_t* fc )
__attribute__ ((unused));

static __inline gwfunc_t*
gwipc_wait_fret( gwmsg_client_p c, long fid )
__attribute__ ((unused));

static __inline gwfunc_t*
gwipc_funcall( gwmsg_client_p c, gwfunc_t* fc )
__attribute__ ((unused));

static __inline void
gwipc_funcall_oneway( gwmsg_client_p c, gwfunc_t* fc )
__attribute__ ((unused));

static __inline void
gwipc_free_fr( gwmsg_client_p c, gwfunc_t* fr )
__attribute__ ((unused));


#ifdef GWIPC_USE_SOCKET
/* --------------------------------------------------------------------
 * functions for server
 */
static __inline int
gwipc_init_server(gwmsg_server_p st, const char *procname,
		  gwerr_handler_t error_handler)
{
    int	gwipc_init_server_sock(gwmsg_server_p, const char *,
			       gwerr_handler_t);
    return gwipc_init_server_sock( st, procname, error_handler );
}

static __inline int
gwipc_close_server(gwmsg_server_p st)
{
    int gwipc_close_server_sock(gwmsg_server_p st);
    
    return gwipc_close_server_sock(st);
}

static __inline int
gwipc_set_server_handler(gwmsg_server_p st, long id, gwmsg_srv_handler_t h)
{
    int gwipc_set_server_handler_sock(gwmsg_server_p, long,
				      gwmsg_srv_handler_t);
    return gwipc_set_server_handler_sock( st, id, h );
}

static __inline void
gwipc_set_default_server_handler(gwmsg_server_p st, gwmsg_srv_handler_t h)
{
    void gwipc_set_default_server_handler_sock(gwmsg_server_p,
					       gwmsg_srv_handler_t);
    gwipc_set_default_server_handler_sock( st, h );
}

static __inline void
gwipc_set_logging_server_handler(gwmsg_server_p st, gwmsg_srv_handler_t h)
{
    void gwipc_set_logging_server_handler_sock(gwmsg_server_p,
					       gwmsg_srv_handler_t);
    gwipc_set_logging_server_handler_sock( st, h );
}

static __inline int
gwipc_dispatch(gwmsg_server_p st)
{
    int	gwipc_dispatch_sock(gwmsg_server_p st);
    return gwipc_dispatch_sock(st);
}

static __inline void
gwipc_run_server(gwmsg_server_p st, pthread_attr_t* attr)
{
    void	gwipc_run_server_sock(gwmsg_server_p st, pthread_attr_t* attr);
    gwipc_run_server_sock(st, attr);
}

static __inline void
gwipc_end_server(gwmsg_server_p st)
{
    void	gwipc_end_server_sock(gwmsg_server_p st);
    gwipc_end_server_sock(st);
}

static __inline gwmsg_t*
gwipc_svmsg_alloc(gwmsg_server_p c, long msgid, size_t size)
{
    gwmsg_t* gwipc_svmsg_alloc_sock(gwmsg_server_p, long, size_t);
    return gwipc_svmsg_alloc_sock(c, msgid, size);
}

static __inline void
gwipc_svmsg_free( gwmsg_server_p c, gwmsg_t* msg )
{
    void gwipc_svmsg_free_sock( gwmsg_server_p, gwmsg_t* );
    gwipc_svmsg_free_sock( c, msg );
    return;
}

static __inline void
gwipc_svmsg_send( gwmsg_server_p c, gwmsg_t* msg, gwmsg_client_id_t cid )
{
    void gwipc_svmsg_send_sock( gwmsg_server_p, gwmsg_t*, gwmsg_client_id_t );
    gwipc_svmsg_send_sock( c, msg, cid );
}

/* 
 * functions for skelton (server).
 */
static __inline gwfunc_t *
gwipc_fret_alloc( gwmsg_server_p st, long id, size_t sz )
{
    gwfunc_t * gwipc_fret_alloc_sock( gwmsg_server_p st, long id, size_t sz );
    return gwipc_fret_alloc_sock( st, id, sz );
}

static __inline void
gwipc_ret_func( gwmsg_server_p st,
		gwfunc_t* fc, gwfunc_t* fr, gwmsg_client_id_t cid )
{
    void gwipc_ret_func_sock( gwmsg_server_p st,
			      gwfunc_t* fc, gwfunc_t* fr,
			      gwmsg_client_id_t cid );
    gwipc_ret_func_sock( st, fc, fr, cid );
}

/*
 * functions for client
 */
static __inline int
gwipc_init_client(gwmsg_client_p c, const char * procname, gwerr_handler_t h)
{
    int gwipc_init_client_sock(gwmsg_client_p, const char *, gwerr_handler_t);
    
    return gwipc_init_client_sock(c, procname, h);
}

static __inline int
gwipc_end_client(gwmsg_client_p c)
{
    int gwipc_end_client_sock(gwmsg_client_p);
    
    return gwipc_end_client_sock(c);
}

static __inline int
gwipc_close_client(gwmsg_client_p c)
{
    int	gwipc_close_client_sock(gwmsg_client_p c);

    return gwipc_close_client_sock(c);
}

static __inline int
gwipc_set_client_handler(gwmsg_client_p c, long id, gwmsg_handler_t h)
{
    int gwipc_set_client_handler_sock(gwmsg_client_p, long, gwmsg_handler_t);
    return gwipc_set_client_handler_sock( c, id, h );
}

static __inline void
gwipc_set_default_client_handler(gwmsg_client_p c, gwmsg_handler_t h)
{
    void gwipc_set_default_client_handler_sock(gwmsg_client_p,gwmsg_handler_t);
    gwipc_set_default_client_handler_sock( c, h );
}

static __inline void
gwipc_set_logging_client_handler(gwmsg_client_p c, gwmsg_handler_t h)
{
    void gwipc_set_logging_client_handler_sock(gwmsg_client_p,gwmsg_handler_t);
    gwipc_set_logging_client_handler_sock( c, h );
}

static __inline void
gwipc_run_client(gwmsg_client_p c, pthread_attr_t* attr)
{    
    void	gwipc_run_client_sock(gwmsg_client_p c, pthread_attr_t* attr);
    gwipc_run_client_sock(c, attr);
}

static __inline gwmsg_t*
gwipc_msg_alloc(gwmsg_client_p c, long msgid, size_t size)
{
    gwmsg_t* gwipc_msg_alloc_sock(gwmsg_client_p, long, size_t);
    return gwipc_msg_alloc_sock(c, msgid, size);
}

static __inline void
gwipc_msg_free( gwmsg_client_p c, gwmsg_t* msg )
{
    void gwipc_msg_free_sock( gwmsg_client_p, gwmsg_t* );
    gwipc_msg_free_sock( c, msg );
    return;
}

static __inline void
gwipc_msg_send( gwmsg_client_p c, gwmsg_t* msg )
{
    void gwipc_msg_send_sock( gwmsg_client_p c, gwmsg_t* msg );
    gwipc_msg_send_sock( c, msg );
}

/* 
 * functions for stub (client). don't call from application directly.
 */
static __inline gwfunc_t*
gwipc_get_fc( gwmsg_client_p c, long msg_id, size_t size )
{
    gwfunc_t* gwipc_get_fc_sock( gwmsg_client_p, long, size_t);
    return gwipc_get_fc_sock( c, msg_id, size );
}
static __inline void
gwipc_call_func( gwmsg_client_p c, gwfunc_t* fc )
{
    void gwipc_call_func_sock( gwmsg_client_p, gwfunc_t* );
    gwipc_call_func_sock( c, fc );
    return;
}
static __inline gwfunc_t*
gwipc_wait_fret( gwmsg_client_p c, long fid )
{
    gwfunc_t*	gwipc_wait_fret_sock( gwmsg_client_p, long fid );
    return gwipc_wait_fret_sock( c, fid );
}
static __inline gwfunc_t*
gwipc_funcall( gwmsg_client_p c, gwfunc_t* fc )
{
    gwfunc_t* gwipc_funcall_sock( gwmsg_client_p, gwfunc_t* );
    return gwipc_funcall_sock( c, fc );
}
static __inline void
gwipc_funcall_oneway( gwmsg_client_p c, gwfunc_t* fc )
{
    void gwipc_funcall_oneway_sock( gwmsg_client_p, gwfunc_t* );
    gwipc_funcall_oneway_sock( c, fc );
    return;
}
static __inline void
gwipc_free_fr( gwmsg_client_p c, gwfunc_t* fr )
{
    void gwipc_msg_free_sock( gwmsg_client_p, gwmsg_t* );
    gwipc_msg_free_sock( c, (gwmsg_t*) fr );
    return;
}

#else /* !GWIPC_USE_SOCKET */
/* --------------------------------------------------------------------
 * functions for server (EVENT VERSION)
 */
static __inline int
gwipc_init_server(gwmsg_server_p st, int id,
		  gwerr_handler_t error_handler)
{
    int	gwipc_init_server_ef(gwmsg_server_p, int,
			       gwerr_handler_t);
    return gwipc_init_server_ef( st, id, error_handler );
}

static __inline int
gwipc_close_server(gwmsg_server_p st)
{
    int gwipc_close_server_ef(gwmsg_server_p st);
    
    return gwipc_close_server_ef(st);
}

static __inline int
gwipc_set_server_handler(gwmsg_server_p st, long id, gwmsg_srv_handler_t h)
{
    int gwipc_set_server_handler_ef(gwmsg_server_p, long,
				      gwmsg_srv_handler_t);
    return gwipc_set_server_handler_ef( st, id, h );
}

static __inline void
gwipc_set_default_server_handler(gwmsg_server_p st, gwmsg_srv_handler_t h)
{
    void gwipc_set_default_server_handler_ef(gwmsg_server_p,
					       gwmsg_srv_handler_t);
    gwipc_set_default_server_handler_ef( st, h );
}

static __inline void
gwipc_set_logging_server_handler(gwmsg_server_p st, gwmsg_srv_handler_t h)
{
    void gwipc_set_logging_server_handler_ef(gwmsg_server_p,
					       gwmsg_srv_handler_t);
    gwipc_set_logging_server_handler_ef( st, h );
}

static __inline int
gwipc_dispatch(gwmsg_server_p st)
{
    int	gwipc_dispatch_ef(gwmsg_server_p st);
    return gwipc_dispatch_ef(st);
}

static __inline void
gwipc_run_server(gwmsg_server_p st, pthread_attr_t* attr)
{
    void	gwipc_run_server_ef(gwmsg_server_p st, pthread_attr_t* attr);
    gwipc_run_server_ef(st, attr);
}

static __inline void
gwipc_end_server(gwmsg_server_p st)
{
    void	gwipc_end_server_ef(gwmsg_server_p st);
    gwipc_end_server_ef(st);
}

static __inline gwmsg_t*
gwipc_svmsg_alloc(gwmsg_server_p c, long msgid, size_t size)
{
    gwmsg_t* gwipc_svmsg_alloc_ef(gwmsg_server_p, long, size_t);
    return gwipc_svmsg_alloc_ef(c, msgid, size);
}

static __inline void
gwipc_svmsg_free( gwmsg_server_p c, gwmsg_t* msg )
{
    void gwipc_svmsg_free_ef( gwmsg_server_p, gwmsg_t* );
    gwipc_svmsg_free_ef( c, msg );
    return;
}

static __inline void
gwipc_svmsg_send( gwmsg_server_p c, gwmsg_t* msg, gwmsg_client_id_t cid )
{
    void gwipc_svmsg_send_ef( gwmsg_server_p, gwmsg_t*, gwmsg_client_id_t );
    gwipc_svmsg_send_ef( c, msg, cid );
}

/* 
 * functions for skelton (server).
 */
static __inline gwfunc_t *
gwipc_fret_alloc( gwmsg_server_p st, long id, size_t sz )
{
    gwfunc_t * gwipc_fret_alloc_ef( gwmsg_server_p st, long id, size_t sz );
    return gwipc_fret_alloc_ef( st, id, sz );
}

static __inline void
gwipc_ret_func( gwmsg_server_p st,
		gwfunc_t* fc, gwfunc_t* fr, gwmsg_client_id_t cid )
{
    void gwipc_ret_func_ef( gwmsg_server_p st,
			      gwfunc_t* fc, gwfunc_t* fr,
			      gwmsg_client_id_t cid );
    gwipc_ret_func_ef( st, fc, fr, cid );
}

/*
 * functions for client
 */
static __inline int
gwipc_init_client(gwmsg_client_p c, long id, gwerr_handler_t h)
{
    int gwipc_init_client_ef(gwmsg_client_p, long id, gwerr_handler_t);
    
    return gwipc_init_client_ef(c, id, h);
}

static __inline int
gwipc_end_client(gwmsg_client_p c)
{
    int gwipc_end_client_ef(gwmsg_client_p);
    
    return gwipc_end_client_ef(c);
}

static __inline int
gwipc_close_client(gwmsg_client_p c)
{
    int	gwipc_close_client_ef(gwmsg_client_p c);

    return gwipc_close_client_ef(c);
}

static __inline int
gwipc_set_client_handler(gwmsg_client_p c, long id, gwmsg_handler_t h)
{
    int gwipc_set_client_handler_ef(gwmsg_client_p, long, gwmsg_handler_t);
    return gwipc_set_client_handler_ef( c, id, h );
}

static __inline void
gwipc_set_default_client_handler(gwmsg_client_p c, gwmsg_handler_t h)
{
    void gwipc_set_default_client_handler_ef(gwmsg_client_p,gwmsg_handler_t);
    gwipc_set_default_client_handler_ef( c, h );
}

static __inline void
gwipc_set_logging_client_handler(gwmsg_client_p c, gwmsg_handler_t h)
{
    void gwipc_set_logging_client_handler_ef(gwmsg_client_p,gwmsg_handler_t);
    gwipc_set_logging_client_handler_ef( c, h );
}

static __inline void
gwipc_run_client(gwmsg_client_p c, pthread_attr_t* attr)
{    
    void	gwipc_run_client_ef(gwmsg_client_p c, pthread_attr_t* attr);
    gwipc_run_client_ef(c, attr);
}

static __inline gwmsg_t*
gwipc_msg_alloc(gwmsg_client_p c, long msgid, size_t size)
{
    gwmsg_t* gwipc_msg_alloc_ef(gwmsg_client_p, long, size_t);
    return gwipc_msg_alloc_ef(c, msgid, size);
}

static __inline void
gwipc_msg_free( gwmsg_client_p c, gwmsg_t* msg )
{
    void gwipc_msg_free_ef( gwmsg_client_p, gwmsg_t* );
    gwipc_msg_free_ef( c, msg );
    return;
}

static __inline void
gwipc_msg_send( gwmsg_client_p c, gwmsg_t* msg )
{
    void gwipc_msg_send_ef( gwmsg_client_p c, gwmsg_t* msg );
    gwipc_msg_send_ef( c, msg );
}

/* 
 * functions for stub (client). don't call from application directly.
 */
static __inline gwfunc_t*
gwipc_get_fc( gwmsg_client_p c, long msg_id, size_t size )
{
    gwfunc_t* gwipc_get_fc_ef( gwmsg_client_p, long, size_t);
    return gwipc_get_fc_ef( c, msg_id, size );
}
static __inline void
gwipc_call_func( gwmsg_client_p c, gwfunc_t* fc )
{
    void gwipc_call_func_ef( gwmsg_client_p, gwfunc_t* );
    gwipc_call_func_ef( c, fc );
    return;
}
static __inline gwfunc_t*
gwipc_wait_fret( gwmsg_client_p c, long fid )
{
    gwfunc_t*	gwipc_wait_fret_ef( gwmsg_client_p, long fid );
    return gwipc_wait_fret_ef( c, fid );
}
static __inline gwfunc_t*
gwipc_funcall( gwmsg_client_p c, gwfunc_t* fc )
{
    gwfunc_t* gwipc_funcall_ef( gwmsg_client_p, gwfunc_t* );
    return gwipc_funcall_ef( c, fc );
}
static __inline void
gwipc_funcall_oneway( gwmsg_client_p c, gwfunc_t* fc )
{
    void gwipc_funcall_oneway_ef( gwmsg_client_p, gwfunc_t* );
    gwipc_funcall_oneway_ef( c, fc );
    return;
}
static __inline void
gwipc_free_fr( gwmsg_client_p c, gwfunc_t* fr )
{
    void gwipc_msg_free_ef( gwmsg_client_p, gwmsg_t* );
    gwipc_msg_free_ef( c, (gwmsg_t*) fr );
    return;
}

#endif /* GWIPC_USE_SOCKET */

/* -------------------------------------------------------------------- */
/*
 * server message queue
 *	サーバ用メッセージqueueルーチン
 */
typedef void *	gwipc_svmqueue_t; /* handle for svmqueue */

gwipc_svmqueue_t
gwipc_svmqueue_init( size_t queue_length );
void
gwipc_svmqueue_send( gwipc_svmqueue_t q,
		     gwmsg_t* m, gwmsg_client_id_t cid );
void
gwipc_svmqueue_receive( gwipc_svmqueue_t q,
			gwmsg_t** m, gwmsg_client_id_t *cid );
void
gwipc_svmqueue_destroy( gwipc_svmqueue_t q );

/*
 * timer routine
 */
typedef void * gwipc_timer_t;		/* handler for timer */
typedef unsigned long gwipc_timer_id_t;	/* handle for 1 timer entry */

gwipc_timer_t
gwipc_run_timer(gwerr_handler_t err_handler, pthread_attr_t* attr);

gwipc_timer_id_t
gwipc_set_timer( gwipc_timer_t* tt,
		 u_int seconds,
		 u_int mseconds,
		 void	(*func)(gwipc_timer_id_t, void *),
		 void	*arg );

int
gwipc_unset_timer( gwipc_timer_t* tt, gwipc_timer_id_t id );

int
gwipc_get_remain_timer( gwipc_timer_t* tt, gwipc_timer_id_t id, u_int *sec, u_int *msec);

void
gwipc_destroy_timer(gwipc_timer_t* tt);

/*
 * for debugging	統計情報/itronダンプ機能があるときのみ有効
 */
void	gwipc_debug_print( int sig );


#endif /* __GWIPC_H__ */
/*
 * Local Variables:
 * c-basic-offset: 4
 * End:
 */
