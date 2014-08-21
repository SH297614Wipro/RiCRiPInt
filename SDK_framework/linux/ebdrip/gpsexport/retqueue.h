/***** -*- C -*- **************************************
 * $Id: retqueue.h,v 1.1 2006/03/09 05:38:49 senda Exp $
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *   ORDER           : 
 *   PROGRAM NAME    : 
 *   FILE NAME       : retqueue.h
 *   VERSION         : $Revision: 1.1 $
 *   DESIGNER        : SENDA Shigeya
 *   AUTHOR          : SENDA Shigeya
 *-----------------------------------------------------
 *       HISTORY
 *	 senda - 11 May 1999: Created.
 *	 $Log: retqueue.h,v $
 *	 Revision 1.1  2006/03/09 05:38:49  senda
 *	 first comit to LPUX2.0
 *	
 *	 Revision 1.3  2003/04/14 04:04:35  senda
 *	 bugfix: mutex range miss.
 *	
 *	 Revision 1.2  2002/12/09 04:40:50  senda
 *	 cast warning on g++
 *	
 *	 Revision 1.1.1.1  2001/09/30 04:00:19  hyuki
 *	 imported from mips version GWIPC_20010919
 *	
 *	 Revision 1.8  2001/09/19 00:38:43  senda
 *	 add thread locking at funcall if retqueue is full.
 *	
 *	 Revision 1.7  2000/06/27 08:41:46  senda
 *	 bugfix: retqueue_init() initialize head to 0.
 *	
 ******************************************************/

#ifndef __RETQUEUE_H__
#define __RETQUEUE_H__

#define	RETQUEUESIZE	8

typedef struct _rq_elm {
    struct _rq_elm *	next;
    pthread_cond_t	cond;	/* 待ち合わせ場所 */
    long		fid;	/* 待っているfuncのfid */
    void *		data;
} rq_elm_t;

typedef rq_elm_t * rq_elm_p;

typedef struct _retqueue {
    pthread_mutex_t	mutex;	/* queueの排他制御 */
    rq_elm_p		head;
    rq_elm_p		delq;
#if defined(USE_NEWVAR)
    rq_elm_p		ehead;
    size_t		esize;
#endif
} retqueue_t;

#if !defined(USE_NO_WAIT)
/*
 * 2001/08/24  :  Adonis-P3 商品テストで発覚(障害対応)
 *
 * 関数まち行列: retqueueあふれをエラーとしないで、呼び出しthreadをウエイト
 * させるように変更する。
 *
 * へッダの定義を変えないで条件変数を確保する苦肉の手段をとっている。
 * client構造体上で、retqueue_tと要素の領域が並んでいる事実を利用して、
 * elmの最初の要素をqueueの空待ちの条件変数として転用する。
 */
typedef struct _retqueue_ex {
    retqueue_t		retqueue;
    rq_elm_t		elm[RETQUEUESIZE];
} retqueue_ex_t;

static __inline rq_elm_p
get_ret_elm(retqueue_t *q)
{
    retqueue_ex_t *qq = (retqueue_ex_t *)q;
    return &(qq->elm[0]);	/* 最初のelmをdelq待ちに転用する */
}
#endif

/** avoid warning (-Wunused) ***/
static __inline void 
retqueue_init( retqueue_t * q, rq_elm_p e, size_t sz )
__attribute__ ((unused));
static __inline void 
retqueue_destroy( retqueue_t * q )
__attribute__ ((unused));
static __inline rq_elm_p
retqueue_getnew( retqueue_t * q )
__attribute__ ((unused));
static __inline void
retqueue_delete( retqueue_t * q, rq_elm_p e )
__attribute__ ((unused));
static __inline void *
retqueue_wait( retqueue_t * q, long fid )
__attribute__ ((unused));
static __inline rq_elm_p
retqueue_pre_wait( retqueue_t * q, long fid )
__attribute__ ((unused));
static __inline void
retqueue_unwait( retqueue_t * q, rq_elm_p e )
__attribute__ ((unused));
static __inline void *
retqueue_real_wait( retqueue_t * q, rq_elm_p e, long fid )
__attribute__ ((unused));
static __inline rq_elm_p
retqueue_search( retqueue_t * q, long fid )
__attribute__ ((unused));
static __inline int
retqueue_signal( retqueue_t * q, long fid, void *data )
__attribute__ ((unused));

static __inline void 
retqueue_init( retqueue_t * q, rq_elm_p e, size_t sz )
{
    unsigned int		i;
    rq_elm_p *	ip = &(q->delq);

#if defined(USE_NEWVAR)
    q->ehead = e;
    q->esize = sz;
#endif
    q->head = 0;

    for( i = 0; i < sz; i++ ) {	/* 削除queueに登録 */
	*ip = &(e[i]);
	pthread_cond_init(&(e[i].cond), NULL);
	ip = &(e[i].next);
    }
    *ip = 0;
    
#if !defined(USE_NO_WAIT)
    q->delq = q->delq->next;	/* 一つ分確保。つまり、delqから取り除いておく。 */
    get_ret_elm(q)->fid = 0;	/* retqueue待ち個数に転用する。 */
#endif
    pthread_mutex_init( &q->mutex, NULL );
    return;
}

static __inline void 
retqueue_destroy( retqueue_t * q )
{
#if defined(USE_NEWVAR)    
    unsigned int		i;
#endif
    rq_elm_p	e;

    pthread_mutex_lock(&q->mutex);
#if !defined(USE_NO_WAIT)
    e = q->delq; q->delq = get_ret_elm(q); q->delq->next = e;	/* 確保分返す */
#endif
#if defined(USE_NEWVAR)
    e = q->ehead;
    for( i = 0; i < q->esize; i++ ) {
	pthread_cond_destroy( &(e[i].cond) );
    }
#else
    for( e = q->head; e; e = e->next ) {
	e->data = 0;	/* 戻値０ */
	pthread_cond_signal( &e->cond );
	pthread_cond_destroy( &e->cond );
    }
    for( e = q->delq; e; e = e->next ) {
	pthread_cond_destroy( &e->cond );
    }
#endif
    pthread_mutex_unlock(&q->mutex);
    pthread_mutex_destroy( &q->mutex );
    return;
}

static __inline rq_elm_p
retqueue_getnew( retqueue_t * q )
{    
    rq_elm_p ret, tmp;
    if( q->delq == 0 ) return 0;

/*    pthread_mutex_lock(&q->mutex); */

    ret = q->delq;
    q->delq = ret->next;
    tmp = q->head;
    q->head = ret;
    ret->next = tmp;	/* 削除queueから１つとってきてheadのリストに追加 */

/*    pthread_mutex_unlock(&q->mutex); */

    return ret;
}

static __inline void
retqueue_delete( retqueue_t * q, rq_elm_p e )
{			
    rq_elm_p	tmp;
    rq_elm_p*	ip;	/* ipはq->headかリンクリスト中のnextのアドレス */
    

/*    pthread_mutex_lock(&q->mutex); */

    for( ip = &(q->head); ip != NULL && *ip != e; ip = &((*ip)->next) );

    if( ip == 0 || e == 0 ) return;
    *ip = e->next;
    tmp = q->delq;
    q->delq = e;	/* eの指す要素を削除し削除queueに入れる */
    e->next = tmp;

#if !defined(USE_NO_WAIT)
    if( get_ret_elm(q)->fid > 0 ) {
	get_ret_elm(q)->fid--;
	pthread_cond_signal( &(get_ret_elm(q)->cond) );
    }
#endif

/*    pthread_mutex_unlock(&q->mutex); */

    return;
}

static __inline void *
retqueue_wait( retqueue_t * q, long fid )
{
    void *	ret = 0;
    rq_elm_p	e;
    
    if( q->delq == 0 ) return 0;

    pthread_mutex_lock(&q->mutex);

    e = retqueue_getnew( q );	/* 待ち合わせ場所確保 */
    if( e == 0 ) {
	pthread_mutex_unlock(&q->mutex);
	return 0;
    }
    e->fid  = fid;
    e->data = 0;
    while( e->data == 0 ) {
	int err;
	err = pthread_cond_wait( &e->cond, &q->mutex );
	if( err ) {
	    retqueue_delete( q, e );	/* 待ち合わせ場所削除 */
	    pthread_mutex_unlock(&q->mutex);
	    return 0;
	}
    }
    ret = e->data;
    retqueue_delete( q, e );	/* 待ち合わせ場所削除 */
    
    pthread_mutex_unlock(&q->mutex);

    return ret;
}

/*
 * retqueue_waitを登録と待ち合わせに分けたバージョン
 *   ex)
 *	rq_elm_p e = retqueue_pre_wait(q, fid);
 *	* 何か動作 ....
 *	* error時 --- retqueue_unwait();
 *	ret = retqueue_real_wait(q, e, fid);
 *
 */
static __inline rq_elm_p
retqueue_pre_wait( retqueue_t * q, long fid )
{
    rq_elm_p	e;
    
#if defined(USE_NO_WAIT)
    if( q->delq == 0 ) return 0;

    pthread_mutex_lock(&q->mutex);

    e = retqueue_getnew( q );	/* 待ち合わせ場所確保 */
    if( e == 0 ) {
	pthread_mutex_unlock(&q->mutex);
	return 0;
    }
#else
    pthread_mutex_lock(&q->mutex);

    while( (e = retqueue_getnew( q )) == 0 ) {    /* 待ち合わせ場所確保 */
	register int err;
	get_ret_elm(q)->fid++;
	err = pthread_cond_wait( &(get_ret_elm(q)->cond), &q->mutex );
	if( err ) {
	    pthread_mutex_unlock(&q->mutex);
	    return 0;
	}
    }
#endif
    e->fid  = fid;
    e->data = 0;

    return e;
}

static __inline void
retqueue_unwait( retqueue_t * q, rq_elm_p e )	/* 待たないで解除のみ */
{
    retqueue_delete( q, e );	/* 待ち合わせ場所削除 */
    pthread_mutex_unlock(&q->mutex);
    return;
}

static __inline void *
retqueue_real_wait( retqueue_t * q, rq_elm_p e, long fid )
{
    void *	ret = 0;
    int		err;
    
    while( e->data == 0 ) {
	err = pthread_cond_wait( &e->cond, &q->mutex );
	if( err ) {
	    retqueue_unwait( q, e );
	    return 0;
	}
    }
    ret = e->data;
    retqueue_unwait( q, e );
    return ret;
}

static __inline rq_elm_p
retqueue_search( retqueue_t * q, long fid )
{
    rq_elm_p e = q->head; 	/* 注意！ この関数はmutexがlockされていることが前提 */
    for( ; e != 0 ; e = e->next )
	if( e->fid == fid ) break;
    return e;
}

static __inline int
retqueue_signal( retqueue_t * q, long fid, void *data )
{
    int ret = 0;
    rq_elm_p e;

    pthread_mutex_lock(&q->mutex);

    for( e = q->head; e != 0 ; e = e->next )
	if( e->fid == fid ) break;
    if( e != 0 ) {
	ret = 1;	/* シグナルできた */
	e->data = data;	/* たしかにsignalであることをwaiterに知らせる */
	pthread_cond_signal( &e->cond );
    } else {
	ret = 0;
    }
    pthread_mutex_unlock(&q->mutex);

    return ret;
}

#endif /* __RETQUEUE_H__ */
/* 
 * Local Variables: 
 * c-basic-offset: 4
 * End:
 */
