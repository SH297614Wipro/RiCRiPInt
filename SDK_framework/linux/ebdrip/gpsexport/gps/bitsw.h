/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : bitsw.h
 *   VERSION         : $Revision$
 *   AUTHOR          : Satoshi MIYAZAKI
 *-----------------------------------------------------
 *       HISTORY
 *	 miyazaki - 19 Apr 2000: Created.
 *	 $Log$
 *	
 ******************************************************/
#ifndef _GPS_BITSW_H_
#define	_GPS_BITSW_H_

#define	BIT_SW_001	0
#define	BIT_SW_002	1
#define	BIT_SW_003	2
#define	BIT_SW_004	3
#define	BIT_SW_005	4
#define	BIT_SW_006	5
#define	BIT_SW_007	6
#define	BIT_SW_008	7
#define	BIT_SW_009	8
#define	BIT_SW_010	9
#define	BIT_SW_011	10
#define	BIT_SW_012	11
#define	BIT_SW_013	12
#define	BIT_SW_014	13
#define	BIT_SW_015	14
#define	BIT_SW_016	15
#define BIT_SW_NUM	16

/*
 * NAD, Russian 等のプリンタのビットスイッチとはビットの順番が逆なので
 * 注意が必要。
 * 設計者にはこちらの方が直感的にコーディングできるようになっている。
 * 番号の定義も従来の１～Ｇではなく、ＳＰ番号に即した００１～０１６
 * に変更した
 *
 * 例えば「ビットスイッチ３－７」と仕様書やマニュアルに書いてある場合、
 * その値を見るには
 *
 *  u_char val;
 *  val = (u_char)gpsGetBitSw(BIT_SW_003);
 *  if (val & (1<<7))    // BitSW 3-7 が真なら
 *  {
 *    .
 *    .
 *    .
 *  }
 *
 * の様に単純に７ビットシフトで調べる事が出来る。
 */

#endif /* !_GPS_BITSW_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */

