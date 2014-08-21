/***** -*- C -*- **************************************
 * $Id: hashmacro.h,v 1.1 2006/03/09 05:38:49 senda Exp $
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *   ORDER           : gwipc hash table manip macro
 *   PROGRAM NAME    : libgwipc
 *   FILE NAME       : hashmacro.h
 *   VERSION         : $Revision: 1.1 $
 *   DESIGNER        : SENDA Shigeya
 *   AUTHOR          : SENDA Shigeya
 *-----------------------------------------------------
 *       HISTORY
 *	 senda - 14 May 1999: Created.
 *	 $Log: hashmacro.h,v $
 *	 Revision 1.1  2006/03/09 05:38:49  senda
 *	 first comit to LPUX2.0
 *	
 *	 Revision 1.1.1.1  2001/09/30 04:00:19  hyuki
 *	 imported from mips version GWIPC_20010919
 *	
 *	 Revision 1.8  2000/06/14 10:37:59  senda
 *	 bugfix : delq replace error.
 *	
 *	 Revision 1.7  2000/06/14 05:33:09  senda
 *	 keep same NM##hash_tbl_t size.
 *	
 *	 Revision 1.6  2000/06/13 04:35:47  senda
 *	 ending functions added for memory leak checking.
 *	
 *	 Revision 1.5  2000/01/22 09:57:22  senda
 *	 STATISTICS/ITRON_DUMP feature.
 *	
 *	 Revision 1.4  1999/08/19 09:32:30  senda
 *	 gwipc_timer.c : fix unlock miss
 *	 hashmacro.h   : fix NULL setting of queue next member
 *	
 *	 Revision 1.3  1999/08/18 01:17:59  senda
 *	 hashmacro : fixed un-initialized next member on malloced queue element
 *	 *.h : fix compile problems
 *	
 *	 Revision 1.2  1999/08/17 06:05:02  senda
 *	 use malloc if delq is exhausted.
 *	
 *	 Revision 1.1.1.1  1999/06/10 11:01:34  senda
 *	 GWIPC
 *	
 ******************************************************/

#ifndef __HASHMACRO_H__
#define __HASHMACRO_H__

/*
 *  hash tableのテーブル定義、ルーチンを自動生成するマクロ。
 *	key   : id
 *	value : void pointer
 *
 *	マクロ:
 *		MakeHashDefs( PREFIX, TSIZE, ESIZE );
 *		- PREFIX : 定義につける名前の先頭辞
 *		- TSIZE  : hashテーブルサイズ。
 *		- ESIZE  : 登録する要素の最大数。
 *			   この実装では要素を固定領域で管理している。
 *			   この要素数メモリ領域をあらかじめ消費する。
 *
 *	定義される関数:
 *
 *	void NM##hash_tbl_init( NM##hash_tbl_p tblp );
 *	  - テーブルの初期化。hash_tbl_tは使用者が変数構造体を確保する。
 *
 *      int  NM##hash_tbl_register( NM##hash_tbl_p tblp,
 *		       long hash_key, long id, void *value );
 *        - テーブルへの登録。hash_keyはhash関数をユーザが外部で与えて
 *          その値をいれる。idが同一の物が既に登録済の場合、valueが更新される。
 *
 *	void* NM##hash_tbl_find( NM##hash_tbl_p tblp, long hash_key, long id );
 *        - 検索。hash_key, idに該当する要素のvalueを返却する。
 *          nullは検索した結果がなかったことを示す。
 *
 *	void NM##hash_tbl_iter( NM##hash_tbl_p tblp,
 *				void (*printval)(long id, void *val) );
 *	  - 登録内容の全件探索。登録要素すべてに対し、関数引数の
 *	    printval(id, val)が呼び出される。
 *
 *	使用法:
 *		MakeHashDefs( TEST_, 128, 64 ); // TEST_xxxが定義される。
 *		long hash_func(long id) {....}
 *			// 戻り値は 0以上、TSIZE-1以下であること
 *		....
 *		TEST_hash_tbl_t tbl; 		// 変数宣言
 *		....
 *		TEST_hash_tbl_init( &tbl );	// 初期化
 *		....
 *		TEST_hash_tbl_register(&tbl, hash_func(id), id, value);
 *		....
 *		value = TEST_hash_tbl_find(&tbl, hash_func(id), id);
 */

#define MakeHashDefs( NM, TSIZE, ESIZE )                             \
       								     \
typedef struct NM##_hash_e {					     \
    struct NM##_hash_e *	next;				     \
    long			id;				     \
    void *			value;				     \
} NM##hash_elm_t;						     \
								     \
typedef NM##hash_elm_t *  NM##hash_elm_p;			     \
								     \
typedef struct NM##_hash_tbl {					     \
    NM##hash_elm_p		delq;				     \
    NM##hash_elm_p		tbl[ TSIZE ];			     \
    NM##hash_elm_t		elm[ ESIZE ];			     \
} NM##hash_tbl_t;						     \
								     \
typedef NM##hash_tbl_t *  NM##hash_tbl_p;			     \
								     \
/*								     \
 * hashテーブル初期化						     \
 */								     \
static __inline void						     \
NM##hash_tbl_init( NM##hash_tbl_p tblp )			     \
{								     \
    int i;							     \
    NM##hash_elm_p * ip;					     \
    								     \
    for( i=0; i < TSIZE; i++ ) {				     \
	tblp->tbl[i] = 0;					     \
    }								     \
    ip = &(tblp->delq);						     \
    for( i=1; i < ESIZE; i++ ) { /* 最初の要素はリンク用 */	     \
	*ip = &(tblp->elm[i]);					     \
	ip = &(tblp->elm[i].next);				     \
    }								     \
    *ip = NULL;							     \
    tblp->elm->next = 0;					     \
    return;							     \
}								     \
								     \
/*								     \
 * hashの空要素の補充 (delq == 0を仮定)				     \
 */								     \
static __inline void						     \
NM##hash_new_delq( NM##hash_tbl_p tblp )			     \
{								     \
    int i;							     \
    NM##hash_elm_p e;						     \
    NM##hash_elm_p * ip;					     \
								     \
    e = (NM##hash_elm_p) calloc( ESIZE, sizeof(*e) );		     \
    if( e == 0 ) return;					     \
    ip = &(tblp->delq);						     \
    for( i=1; i < ESIZE; i++ ) {				     \
	*ip = &(e[i]);						     \
	ip = &(e[i].next);					     \
    }								     \
    *ip = NULL;							     \
    /* 最初の要素はcallocエリアのリンク保持 */			     \
    e->next = tblp->elm->next;					     \
    tblp->elm->next = e;					     \
    return;							     \
}								     \
								     \
/*								     \
 * hash登録							     \
 *	id重複は許さない。					     \
 *	この関数の外でhash関数によりhash_keyを求めること。	     \
 */								     \
static __inline int						     \
NM##hash_tbl_register( NM##hash_tbl_p tblp,			     \
		       long hash_key, long id, void *value )	     \
{								     \
    NM##hash_elm_p e;						     \
    NM##hash_elm_p *ip;						     \
    								     \
    ip = &(tblp->tbl[hash_key]);				     \
    while( (*ip) != NULL ) {					     \
	if( (*ip)->id == id ) {					     \
	    (*ip)->value = value;	/* 更新 */		     \
	    return 2;						     \
	}							     \
	ip = &((*ip)->next);	/* つぎのhashの空きをチェック */     \
    }								     \
    e = tblp->delq;						     \
    if( e == 0 ) {						     \
	NM##hash_new_delq(tblp);				     \
	e = tblp->delq;						     \
	if( e == 0 ) return 0;				             \
    }								     \
    tblp->delq = e->next;	/* 削除queueから１つとってくる */    \
								     \
    e->id = id;							     \
    e->value = value;						     \
    e->next = NULL;						     \
    *ip = e;							     \
    return 1;							     \
}								     \
								     \
/*								     \
 * hash検索							     \
 */								     \
static __inline void *						     \
NM##hash_tbl_find( NM##hash_tbl_p tblp, long hash_key, long id )     \
{								     \
    NM##hash_elm_p p;						     \
								     \
    p = tblp->tbl[hash_key];					     \
    while( p != NULL ) {					     \
	if( p->id == id ) {					     \
	    return p->value;					     \
	}							     \
	p = p->next;	/* つぎのhashの空きをチェック */	     \
    }								     \
    return 0;							     \
}								     \
								     \
/*								     \
 * hashの全件探索						     \
 */								     \
static __inline void						     \
NM##hash_tbl_iter( NM##hash_tbl_p tblp,				     \
		    void (*printval)(long id, void *val) )	     \
{								     \
    int i;							     \
    NM##hash_elm_p	ip;					     \
								     \
    for( i=0; i<TSIZE; i++ ) {					     \
	ip = tblp->tbl[i];					     \
	if( ip != 0 ) {						     \
	    for(; ip != 0; ip = ip->next) {			     \
		printval( ip->id, ip->value );			     \
	    }							     \
	}							     \
    }								     \
    return;							     \
}								     \
								     \
/*								     \
 * hashテーブルの破壊	(callocエリアの解放)			     \
 */								     \
static __inline void						     \
NM##hash_tbl_destroy( NM##hash_tbl_p tblp )			     \
{								     \
    register NM##hash_elm_p e = tblp->elm->next;		     \
    while(e) {							     \
	register NM##hash_elm_p f = e;				     \
	e = e->next;						     \
	free(f);						     \
    }								     \
    return;							     \
}								     \

/*
 * hash削除などはとりあえず必要ないので作ってない。
 */

#endif /* __HASHMACRO_H__ */
/*
 * Local Variables:
 * c-basic-offset: 4
 * End:
 */
