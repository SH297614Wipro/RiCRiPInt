/**
 * @file di_getinfo.h
 * @brief di_getinfo���W���[����I/F
 *
 * @author kumagai
 * @date 2005-09-15
 * $Revision: 1.3 $
 *
 * Copyright (c) 2002-2007 by RICOH CO., LTD.
 */

#ifndef __DI_GETINFO_H__
#define __DI_GETINFO_H__

/* �����֐��̖߂�l��,GPS�̊֐��̖߂�l�ɂ��킹�� */
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
 * \brief �𑜓x�E�f�B�U�̎�ސ��ƃ��[�h�E�v���[�������擾
 *
 * \param devinfo    DI�\����
 * \param alloc_func �̈�m�ۗp�R�[���o�b�N�֐�
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
int get_render_info_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

/**
 * \brief �f�B�U���擾
 *
 * \param devinfo    DI�\����
 * \param alloc_func �̈�m�ۗp�R�[���o�b�N�֐�
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
int get_dither_info_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

/**
 * \brief �����擾
 *
 * \param devinfo    DI�\����
 * \param alloc_func �̈�m�ۗp�R�[���o�b�N�֐�
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
int get_gamma_info_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

/**
 * \brief BG/UCR�p�����[�^���擾
 *
 * \param devinfo DI�\����
 * \param alloc_func �̈�m�ۗp�R�[���o�b�N�֐�
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
#ifndef USE_IMAQ
int get_bgucr_param_di_(di_devinfo_t *devinfo);
#else /* USE_IMAQ */
int get_bgucr_param_di_(di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);
#endif /* USE_IMAQ */

/**
 * \brief �\�t�g�g�i�[�Z�[�u�̃T�|�[�g�L�����擾
 *
 * \param devinfo DI�\����
 *
 * \param  0 ����
 * \param -1 ���s
 */
int get_support_softtsave_di_(di_devinfo_t *devinfo);

/**
 * \brief �\�t�g�g�i�[�Z�[�u�̊������擾
 *
 * \param devinfo DI�\����
 *
 * \param  0 ����
 * \param -1 ���s
 */
int get_tonersave_ratio_di_(di_devinfo_t *devinfo);

/**
 * \brief �g���\�t�g�g�i�[�Z�[�u�̑Ή������擾
 *
 * \param devinfo DI�\����
 *
 * \param  0 ����
 * \param -1 ���s
 */
int get_support_extend_softtsave_di_(di_devinfo_t *devinfo);

/**
 * \brief ���ʋK���̃T�|�[�g�L�����擾
 *
 * \param devinfo DI�\����
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
int get_support_tlimit_di_(di_devinfo_t *devinfo);

/**
 * \brief ���ʋK���l���擾
 *
 * \param devinfo DI�\����
 * \param alloc_func �̈�m�ۗp�R�[���o�b�N�֐�
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
int get_tlimit_di_( di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func);

#ifdef USE_IMAQ
/**
 * \brief �K�ʃf�[�^���擾
 *
 * \param devinfo DI�\����
 * \param alloc_func �̈�m�ۗp�R�[���o�b�N�֐�
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
int get_drop_di_( di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func );

/**
 * \brief ���ʃ��������擾
 *
 * \param devinfo DI�\����
 * \param alloc_func �̈�m�ۗp�R�[���o�b�N�֐�
 *
 * \retval  0 ����
 * \retval -1 ���s
 */
int get_dupgam_di_( di_devinfo_t *devinfo, DI_CALLBACK_MEMALLOC alloc_func );

/**
 * \brief �K�ʃT�|�[�g�����擾
 *
 * \param devinfo DI�\����
 *
 * \retval  0 ����
 * \retval -1 ���s
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
