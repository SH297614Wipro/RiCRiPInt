/************************************************************************
 * ファイル名   : gps_rmtprn.h
 * 機能概要     : GPS - リモート印刷管理
 * 著作者       : Copyright (C) RICOH CO., LTD. 1999,2000
 * 設計者       : Masaki Tsusaka
 * 変更履歴     : 2000.04.17 1st created.
 ************************************************************************/

#ifndef _GPS_RMTPRN_H_INCLUDED_
#define _GPS_RMTPRN_H_INCLUDED_

/*  gpsRmtprnTxStart() の戻り値 */
#define  GPS_RMTPRN_TS_SUCCESS		(0)	/* 成功 */
#define  GPS_RMTPRN_TS_ERROR		(-1)	/* 予定外のエラー */
#define  GPS_RMTPRN_TS_ERROR_RTY	(-2)	/* 今すぐ受け付けられないので、所定のwait後リトライ */

/*  リモートプリント送信パラメータ構造体 */
typedef struct gps_rmtprn_param {
    char	telno[256];	/* 電話番号 (文字列形式) */
    char	line[32];	/* 回線種別 (文字列形式) */
    char	ver[16];	/* RPCSバージョン (文字列形式) */
    char	limit[16];	/* 送信データの上限 (文字列形式) */
} gps_rmtprn_param_t;

/*  リモートプリント送信処理 開始要求 */
int	gpsRmtprnTxStart(gwmsg_client_t *client, int ujobid, gps_rmtprn_param_t *rprm);

#endif /* _GPS_RMTPRN_H_INCLUDED_ */
