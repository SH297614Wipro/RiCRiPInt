/************************************************************************
 * ファイル名   : replot.h
 * 機能概要     : GPS - 印刷ページ管理 - GL用リプロット機能
 * 著作者       : Copyright (C) RICOH CO., LTD. 2000.
 * 設計者       : T.Kitazawa
 * 変更履歴     : 2000-06-15 開始
 *                2000-06-19 Version 1.28.k1
 ************************************************************************/
/*      */
#ifndef _REPLOT_H
#define _REPLOT_H
#ifdef  __cplusplus
extern "C" {
#endif  /* !__cplusplus */
/*      */
/************************************************************************
 *      Public Function
 ************************************************************************/
/*      */
extern int      gpsFrameReplot( gwmsg_client_t *client, int plotid, int paper_count );
/*      */
#ifdef  __cplusplus
}
#endif  /* !__cplusplus */
#endif  /* !_REPLOT_H */
/* EOF  */
