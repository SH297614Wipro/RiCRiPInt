/************************************************************************
 * ファイル名   : bandcache.h
 * 機能概要     : GPS - 印刷ページ管理 - バンドメモリーキャッシュ機能
 * 著作者       : Copyright (C) RICOH CO., LTD. 2000.
 * 設計者       : T.Kitazawa
 * 変更履歴     : 2000-08-26 開始
 *                2000-08-26 Version 1.44 std / 2.08 kipw
 ************************************************************************/
/*      */
#ifndef _BANDCACHE_H
#define _BANDCACHE_H
#ifdef  __cplusplus
extern "C" {
#endif  /* !__cplusplus */
/*      */
/************************************************************************
 *      Public Function
 ************************************************************************/
/*      */
extern int      gpsFrameOpenBandCache(  gwmsg_client_t *client, int frameid, int bandid, int planeid,                       gwmsg_GpsPage_FrameGetBand_Res_t   *pFGBR );
extern int      gpsFrameCloseBandCache( gwmsg_client_t *client, int frameid, int bandid, int planeid, int drawn, int flush, gwmsg_GpsPage_FrameFlushBand_Res_t *pFFBR );
extern int      gpsFrameFlushBandCache( gwmsg_client_t *client,                                                             gwmsg_GpsPage_FrameFlushBand_Res_t *pFFBR );
/*      */
#ifdef  __cplusplus
}
#endif  /* !__cplusplus */
#endif  /* _BANDCACHE_H */
/* EOF  */
