/**
 * @file di_getinfo.h
 * @brief di_getinfoモジュールのI/F
 *
 * @author kumagai
 * @date 2005-09-15
 * $Revision: 1.3 $
 *
 * Copyright (c) 2002-2007 by RICOH CO., LTD.
 */

#ifndef __DI_GETINFO_H__
#define __DI_GETINFO_H__

/* 内部関数の戻り値は,GPSの関数の戻り値にあわせる */
#define	DI_GET_OK	0
#define	DI_GET_NG	-1

#ifdef USE_SET_CATEGORY
#define	DI_SET_OK	0
#define	DI_SET_NG	-1
#endif /* USE_SET_CATEGORY */

#include "device.h"

/** \defgroup GetinfoInterface Infomation I/F
 * \{
 */

/**
 * \brief 解像度・ディザの種類数とモード・プレーン数を取得
 *
 * \param devinfo    DI構造体
 * \param alloc_func 領域確保用コールバック関数
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_render_info_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

/**
 * \brief ディザを取得
 *
 * \param devinfo    DI構造体
 * \param alloc_func 領域確保用コールバック関数
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_dither_info_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

/**
 * \brief γを取得
 *
 * \param devinfo    DI構造体
 * \param alloc_func 領域確保用コールバック関数
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_gamma_info_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

/**
 * \brief BG/UCRパラメータを取得
 *
 * \param devinfo DI構造体
 * \param alloc_func 領域確保用コールバック関数
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
#ifndef USE_IMAQ
int get_bgucr_param_di_(di_devinfo_t *devinfo);
#else /* USE_IMAQ */
int get_bgucr_param_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);
#endif /* USE_IMAQ */

/**
 * \brief ソフトトナーセーブのサポート有無を取得
 *
 * \param devinfo DI構造体
 *
 * \param  0 成功
 * \param -1 失敗
 */
int get_support_softtsave_di_(di_devinfo_t *devinfo);

/**
 * \brief ソフトトナーセーブの割合を取得
 *
 * \param devinfo DI構造体
 *
 * \param  0 成功
 * \param -1 失敗
 */
int get_tonersave_ratio_di_(di_devinfo_t *devinfo);

/**
 * \brief 拡張ソフトトナーセーブの対応情報を取得
 *
 * \param devinfo DI構造体
 *
 * \param  0 成功
 * \param -1 失敗
 */
int get_support_extend_softtsave_di_(di_devinfo_t *devinfo);

/**
 * \brief 総量規制のサポート有無を取得
 *
 * \param devinfo DI構造体
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_support_tlimit_di_(di_devinfo_t *devinfo);

/**
 * \brief 総量規制値を取得
 *
 * \param devinfo DI構造体
 * \param alloc_func 領域確保用コールバック関数
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_tlimit_di_( di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

#ifdef USE_IMAQ
/**
 * \brief 適量データを取得
 *
 * \param devinfo DI構造体
 * \param alloc_func 領域確保用コールバック関数
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_drop_di_( di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func );

/**
 * \brief 両面γ割合を取得
 *
 * \param devinfo DI構造体
 * \param alloc_func 領域確保用コールバック関数
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_dupgam_di_( di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func );

/**
 * \brief 適量サポート情報を取得
 *
 * \param devinfo DI構造体
 *
 * \retval  0 成功
 * \retval -1 失敗
 */
int get_support_drop_di_(di_devinfo_t *devinfo);
#endif /* USE_IMAQ */

/*
 * Get min and max band height
 */
int get_minbandheight_di_(di_devinfo_t *devinfo);
int get_maxbandheight_di_(di_devinfo_t *devinfo);
int get_bandsize_di_(di_devinfo_t *devinfo);

/** \} */ /* end of group(Interface) */

#ifdef USE_SET_CATEGORY
int set_category_di_( char *category );
#endif /* USE_SET_CATEGORY */

#endif	/* __DI_GETINFO_H__ */

/*
 *
 *	COPYRIGHT (C) 2002-2007 RICOH COMPANY LTD.
 *	All rights reserved.
 *
 */
