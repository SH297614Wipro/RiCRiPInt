/************************************************************************
 * ファイル名   : pageio.h
 * 機能概要     : GPS - 印刷ページ管理 - クライアント用ライブラリ
 * 著作者       : Copyright (C) RICOH CO., LTD. 1999, 2000.
 * 設計者       : T.Kitazawa
 * 変更履歴     : 1999-11-05 開始
 *                2000-07-05 Version 1.30
 ************************************************************************/
/*      */
#ifndef _PAGEIO_H
#define _PAGEIO_H
#ifdef  __cplusplus
extern "C" {
#endif  /* !__cplusplus */
/*      */
/************************************************************************
 *      Public Function
 ************************************************************************/
/*      */
extern void     gpsPageInit(              gwmsg_client_t *client );
extern int      gpsJupiterFrameCreateRes( gwmsg_client_t *client, int plotid, gps_pagemode_p ppagemode, gps_pageinfo_t *ppageinfo, int force,     gwmsg_GpsPage_FrameCreate_Res_t    *pFCR );
extern int      gpsFrameCreateInfoRes(    gwmsg_client_t *client, int plotid, gps_pagemode_p ppagemode, gps_pageinfo_t *ppageinfo, int force,     gwmsg_GpsPage_FrameCreate_Res_t    *pFCR );
extern int      gpsFrameCreateRes(        gwmsg_client_t *client, int plotid, gps_pagemode_p ppagemode,                                           gwmsg_GpsPage_FrameCreate_Res_t    *pFCR );
extern int      gpsFrameOpenRes(          gwmsg_client_t *client, int plotid,                                                                     gwmsg_GpsPage_FrameOpen_Res_t      *pFOR );
extern int      gpsFrameGetBandRes(       gwmsg_client_t *client, int frameid, int bandid, int planeid,                                           gwmsg_GpsPage_FrameGetBand_Res_t   *pFGBR );
extern int      gpsFrameFlushBandRes(     gwmsg_client_t *client, int frameid, int bandid, int planeid, int drawn, int flush,                     gwmsg_GpsPage_FrameFlushBand_Res_t *pFFBR );
extern int      gpsFrameFlushSoon(        gwmsg_client_t *client,                                                                                 gwmsg_GpsPage_FrameFlushBand_Res_t *pFFBR );
extern int      gpsReplotOpenRes(         gwmsg_client_t *client, int plotid,                                                                     gwmsg_GpsPage_FrameOpen_Res_t      *pFOR );
extern int      gpsReplotGetBandRes(      gwmsg_client_t *client, int frameid, int bandid, int planeid,                                           gwmsg_GpsPage_FrameGetBand_Res_t   *pFGBR );
extern int      gpsReplotFlushBandRes(    gwmsg_client_t *client, int frameid, int bandid, int planeid, int drawn, int flush,                     gwmsg_GpsPage_FrameFlushBand_Res_t *pFFBR );
extern int      gpsTrayRequestRes(        gwmsg_client_t *client, int plotid, int psize,                          int nodir, int ptype, int tray, gwmsg_GpsPage_TrayRequest_Res_t    *pTRR );
extern int      gpsPaperRequestRes(       gwmsg_client_t *client, int plotid, int psize, int pwidth, int plength, int nodir, int ptype, int tray, gwmsg_GpsPage_PaperRequest_Res_t   *pPRR );
extern int      gpsFormGetImageInfoRes(   gwmsg_client_t *client, int plotid, int formno, int *result,                                  gwmsg_GpsPage_FormGetImageInfo_Res_t *pFGIIR);
extern int      gpsFormOpenRes(           gwmsg_client_t *client, int plotid, int formno, int *result,                                  gwmsg_GpsPage_FormOpen_Res_t       *pFOOR);
extern int      gpsFormOpenBandRes(       gwmsg_client_t *client, int frameid, int bandid, int planeid, int *result,                              gwmsg_GpsPage_FrameGetBand_Res_t   *pFGBR);
extern int      gpsFormCloseBandRes(      gwmsg_client_t *client, int frameid, int bandid, int planeid, int *result,                              gwmsg_GpsPage_FrameFlushBand_Res_t *pFFBR);
extern int      gpsFrameGetBandRes2(      gwmsg_client_t *client, int frameid, int bandid, int planeid,                                           gwmsg_GpsPage_FrameGetBand_Res_t   *pFGBR );
extern int      gpsFrameFlushBandRes2(    gwmsg_client_t *client, int frameid, int bandid, int planeid, int drawn, int flush,                     gwmsg_GpsPage_FrameFlushBand_Res_t *pFFBR );
extern int      gpsPlotSetPageParamShm(   gwmsg_client_t* client, int plotid, gps_pageparam_shm_t *ppageparam_shm, int *result);
/*      */
#define         GPS_FLUSH_SOON  (0)
#define         GPS_FLUSH_LATER (1)
/*      */
#ifdef  __cplusplus
}
#endif  /* !__cplusplus */
#endif  /* !_PAGEIO_H */
/* EOF  */
