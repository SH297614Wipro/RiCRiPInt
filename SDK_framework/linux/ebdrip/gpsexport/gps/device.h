/**
 * @file device.h
 * @brief DI‚ÌŒöŠJƒtƒ@ƒCƒ‹
 *
 * @author kumagai
 * @date 2005-09-13
 * $Revision: 1.4 $
 *
 * Copyright (c) 2001-2007 by RICOH CO., LTD.
 */

/** \mainpage DI Library “à•”�ÝŒvŽd—l�‘
 *
 * –{Žd—l�‘‚Í�ADI�iDevice Infomation) Library ‚Ì“à•”Žd—l‚ð‹L�q‚µ‚½‚à‚Ì‚Å‚·�B
 *
 * DI‚Í�AƒvƒŠƒ“ƒ^�[ƒAƒvƒŠ�iˆÈ‰ºƒAƒvƒŠ�j‚ª“®�ì‚·‚é‚½‚ß‚É•K—v‚È�î•ñ‚Ì’ñ‹Ÿ‚ð
 * �s‚¤ƒ‰ƒCƒuƒ‰ƒŠ‚Å‚·�B
 * ƒAƒvƒŠ‚Å‚Í�AƒvƒŠƒ“ƒ^�[‚Ì‚n‚r‚â‹@Ží‚ÉˆË‘¶‚µ‚½�î•ñ‚ª•K—v‚Å‚·‚ª�A‚»‚Ì‚æ‚¤
 * ‚È•Ï“®ƒpƒ‰ƒ��[ƒ^‚ðDI‚©‚çŽæ“¾‚·‚é‚±‚Æ‚É‚æ‚è�Aƒp�[ƒX•”�AƒŒƒ“ƒ_ƒŠƒ“ƒO•”‚Æ
 * ‚¢‚Á‚½�ˆ—�•”•ª‚Ì”Ä—p�«‚ð�‚‚ß‚Ü‚·�B
 *
 * \date 2005/09
 * \author M.Kumagai
 */

#ifndef	__DEVICE_H__
#define	__DEVICE_H__

#define DI_MAX_TRAY_NUM	8

/*
 * di_select_ideviceŠÖ�”‚ÌI/O’è‹`
 */
#define DI_HOST_IO         0
#define DI_MEMORY_IO       1
#define DI_FILE_IO         2

/*
 * ƒVƒXƒeƒ€‚©‚ç—ˆ‚éƒCƒxƒ“ƒg’l
 */
#define	DI_REQ_PROCESS	0x01	/* ’Ê�í�ˆ—� */
#define	DI_REQ_CANCEL	0x02	/* ƒpƒlƒ‹‚©‚ç‚ÌƒWƒ‡ƒuƒŠƒZƒbƒg */
#define	DI_REQ_EXIT		0x04	/* �I—¹—v‹� */
#define	DI_REQ_PAUSE    0x08	/* Š„‚è�ž‚Ý‚É‚æ‚éˆêŽž’âŽ~—v‹� */
#define	DI_REQ_RESUME   0x10	/* �ˆ—��ÄŠJ—v‹� */
#define	DI_REQ_PROGENTRY	0x20	/* ƒvƒ�ƒOƒ‰ƒ€“o˜^—v‹��iMSISŒnPDL�ê—p�j */
#define	DI_REQ_PROGDELETE	0x40	/* ƒvƒ�ƒOƒ‰ƒ€�í�œ—v‹��iMSISŒnPDL�ê—p�j */
#define	DI_REQ_TERM		0x80	/* ƒvƒŠƒ“ƒ^ƒAƒvƒŠ�I—¹—v‹��iMSISŒnPDL�ê—p�j */
#define	DI_REQ_INTRAY		0x100	/* ‹‹Ž†ƒgƒŒƒC�î•ñŠm”F—v‹��iMSISŒnPDL�ê—p */

/*
 * ƒVƒXƒeƒ€‚Ö‚Ì’Ê’mƒ�ƒbƒZ�[ƒW
 */
#define DI_NOTIFYMSG_JOBEND		0x01	/* ƒWƒ‡ƒu‚Ì�I—¹ */
#define DI_NOTIFYMSG_STATE		0x02	/* �ó‘Ô‚Ì’Ê’m */
#define DI_NOTIFYMSG_STRING		0x03	/* •¶Žš—ñ‚É‚æ‚é�ó‘Ô‚Ì’Ê’m */
#define DI_NOTIFYMSG_ERRFORCE		0x11	/* ƒGƒ‰�[‚Ì‹­�§’Ê’m */
#define DI_NOTIFYMSG_START		0x12	/* –¾Ž¦“I‚È‹N“®’Ê’m */
#define DI_NOTIFYMSG_FINISH_FONTCOUNT	0x13	/* ƒtƒHƒ“ƒgƒJƒEƒ“ƒg‚Ì�I—¹’Ê’m */
#define DI_NOTIFYMSG_PAUSE		0x14	/* ˆêŽž’âŽ~—v‹�‚É‘Î‚·‚é‰ž“š�iŠ®—¹�A‚à‚µ‚­‚ÍˆêŽž’âŽ~‚Å‚«‚È‚¢�j’Ê’m */
#define DI_NOTIFYMSG_RESUME		0x15	/* �ˆ—��ÄŠJ’Ê’m */
#define DI_NOTIFYMSG_ERR		0x16    /* ƒGƒ‰�[‚Ì’Ê’m */
#define DI_NOTIFYMSG_WARNNING		0x17	/* ƒ��[ƒjƒ“ƒOƒŒƒxƒ‹‚ÌƒGƒ‰�[‚Ì’Ê’m */
#define DI_NOTIFYMSG_CLEAR_WARNNING	0x18	/* ƒ��[ƒjƒ“ƒOƒŒƒxƒ‹‚ÌƒGƒ‰�[‚ÌƒNƒŠƒA‚Ì’Ê’m */
#define DI_NOTIFYMSG_ALERT		0x19	/* ƒIƒyƒŒ�[ƒ^ƒR�[ƒ‹ƒŒƒxƒ‹‚ÌƒGƒ‰�[‚Ì’Ê’m */
#define DI_NOTIFYMSG_CLEAR_ALERT	0x1A	/* ƒIƒyƒŒ�[ƒ^ƒR�[ƒ‹ƒŒƒxƒ‹‚ÌƒGƒ‰�[‚ÌƒNƒŠƒA‚Ì’Ê’m */

/*
 *ˆêŽŸ’âŽ~—v‹�‚É‘Î‚·‚é‰ž“š‚Ìˆø�”
 */
#define DI_INTERP_PAUSE_OK	0	/* ˆêŽž’âŽ~‚µ‚½Žž */
#define DI_INTERP_PAUSE_NG	-1	/* ˆêŽž’âŽ~‚Å‚«‚È‚¢ */

/*
 * ƒCƒ“ƒ^ƒvƒŠƒ^‚Ì�ó‘Ô
 */
#define DI_INTERP_STATE_IDLE       0   /* idle */
#define DI_INTERP_STATE_PROCESSING 1   /* processing */
#define DI_INTERP_STATE_WAITING    2   /* waiting data */
#define DI_INTERP_STATE_FLUSHING   3   /* flushing data */

/*
 * ƒR�[ƒ‹ƒoƒbƒNŠÖ�”‚ÌŽw’è
 */
/* di_singetc “Ç‚Ý�ž‚ÝŽ¸”s‚ÌŽž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_READERR_SINGETC		0x01
/* di_singet “Ç‚Ý�ž‚ÝŽ¸”s‚ÌŽž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_READERR_SINGET		0x02
/* di_singetc ƒTƒCƒYŽw’è•s�³Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_SIZEERR_SINGET		0x03
/* ƒVƒXƒeƒ€‚©‚çƒf�[ƒ^�ˆ—�‚ÌŠJŽn—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_PROCDATA		0x11
/* ƒVƒXƒeƒ€‚©‚çƒCƒ“ƒ^ƒvƒŠƒ^�I—¹—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_EXIT			0x12
/* ƒVƒXƒeƒ€‚©‚çƒf�[ƒ^�ˆ—�‚Ì’†Ž~—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_CANCEL			0x13
/* ƒVƒXƒeƒ€‚©‚çƒIƒ“ƒ‰ƒCƒ“—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_ONLINE			0x14
/* ƒVƒXƒeƒ€‚©‚çƒIƒtƒ‰ƒCƒ“—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_OFFLINE			0x15
/* ƒVƒXƒeƒ€‚©‚çƒeƒXƒgƒvƒŠƒ“ƒg—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_TESTPRINT		0x16
/* ƒVƒXƒeƒ€‚©‚ç‹‹Ž†ƒgƒŒƒC‚Ì•Ï�X’Ê’m‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_TRAYINFO		0x17
/* ƒVƒXƒeƒ€‚©‚ç”rŽ†ƒrƒ“‚Ì•Ï�X’Ê’m‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_BININFO			0x18
/* ƒVƒXƒeƒ€‚©‚ç‹­�§”rŽ†—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_EXITPAPER		0x19
/* ƒVƒXƒeƒ€‚©‚çƒtƒHƒ“ƒg�”‚ÌƒJƒEƒ“ƒg—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_FONTCOUNT		0x1A
/* ƒVƒXƒeƒ€‚©‚çƒvƒŠƒ“ƒ^ƒXƒe�[ƒ^ƒX�î•ñ‚Ì•Ï�X’Ê’m‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_PRTSTATUS		0x1B
/* ƒVƒXƒeƒ€‚©‚çƒKƒ“ƒ}�ÄŒvŽZ‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_GAM				0x1C
/* ƒVƒXƒeƒ€‚©‚çƒf�[ƒ^�ˆ—�‚ÌˆêŽž’âŽ~—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_PAUSE				0x1D
/* ƒVƒXƒeƒ€‚©‚çƒf�[ƒ^�ˆ—�‚Ì�ˆ—��ÄŠJ—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_RESUME				0x1E
/* ƒVƒXƒeƒ€‚©‚çƒ�ƒjƒ…�[ƒAƒCƒeƒ€‚Ì“o˜^—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_MENU_INIT			0x20
/* ƒVƒXƒeƒ€‚©‚çƒ�ƒjƒ…�[‰æ–Ê‚Ì�I—¹—v‹�‚ª‚«‚½Žž‚ÉƒR�[ƒ‹‚·‚éŠÖ�” */
#define DI_CALLBACK_REQ_MENU_EXIT			0x21
#define DI_CALLBACK_REQ_TRAY			0x26

/*
 * ‰ð‘œ“x
 */
#define DI_RESO_200x200x1	(1 << 0)
#define DI_RESO_300x300x1	(1 << 1)
#define DI_RESO_400x400x1	(1 << 2)
#define DI_RESO_600x600x1	(1 << 3)
#define DI_RESO_1200x1200x1	(1 << 4)
#define DI_RESO_1200x600x1	(1 << 5)
#define DI_RESO_600x600x2	(1 << 6)
#define DI_RESO_600x600x4	(1 << 7)
#define DI_RESO_1200x1200x2	(1 << 8)
#define DI_RESO_600x1200x1	(1 << 9)

/*
 * di_getinfo( )‚ÌƒGƒ‰�[‚ÌŽí—Þ
 */
#define DI_GI_ERR_CONDITION  	(1 << 0)
#define DI_GI_ERR_DITHER     	(1 << 1)
#define DI_GI_ERR_GAMMA      	(1 << 2)
#define DI_GI_ERR_FONT       	(1 << 3)
#define DI_GI_ERR_PROF       	(1 << 4)
#define DI_GI_ERR_RESO       	(1 << 5)
#define DI_GI_ERR_NDIT       	(1 << 6)
#define DI_GI_ERR_NPLANE     	(1 << 7)
#define DI_GI_ERR_BGUCR      	(1 << 8)
#define DI_GI_ERR_TSAVE      	(1 << 9)
#define DI_GI_ERR_TSAVE_R    	(1 << 10)
#define DI_GI_ERR_TLIMIT     	(1 << 11)
#define DI_GI_ERR_TLIMIT_R   	(1 << 12)
#define DI_GI_ERR_SHDM       	(1 << 13)
#define DI_GI_ERR_SYSH       	(1 << 14)
#define DI_GI_ERR_EXTENDTSAVE   (1 << 15)
#define DI_GI_ERR_DROP      	(1 << 16)
#define DI_GI_ERR_DUPGAM    	(1 << 17)
#define DI_GI_ERR_SUPPORT_DROP  (1 << 18)
#define DI_GI_ERR_CMYMEDIA	(1 << 19)
#define DI_GI_ERR_GCR		(1 << 20)
#define DI_GI_ERR_MINBH		(1 << 21)
#define DI_GI_ERR_MAXBH		(1 << 22)
#define DI_GI_ERR_BANDSIZE	(1 << 23)

/*
 * operation value of di_setrenderinfo
 */
#define DI_SRI_DITHER	0
#define DI_SRI_GAMMA	1
#define DI_SRI_BGUCR	2
#define DI_SRI_TLIMIT	3

/*
 * di_get_appinfo( )‚Ì•Ô‚è’l
 */
#define DI_PINI_OK                  0
#define DI_PINI_KEY_NOT_FOUND      -1
#define DI_PINI_CATEGORY_NOT_FOUND -2
#define DI_PINI_TOOLONG_VALUE      -3
#define DI_PINI_ILLEGAL_ARG        -4
#define DI_PINI_FAILURE            -5
#define DI_PINI_ERROR              -6

/*
 * di_get_appinfo( )‚Ì’l‚ðŠi”[‚·‚é”z—ñ‚Ì�Å‘å’·
 */
#define DI_MAX_VALUE_LEN 32

/*
 * di_get/set_envalue( )‚Ì•Ô‚è’l
 */
#define DI_ENV_ASSIGN          1
#define DI_ENV_DEFAULT         0
#define DI_ENV_ERROR          -1
#define DI_ENV_NOEXIST_TABLE  -2
#define DI_ENV_NOEXIST_VALUE  -3
#define DI_ENV_READONLY       -4
#define DI_ENV_ILLEGAL_VALUE  -5
#define DI_ENV_TABLE_BUSY     -6
/*
 * di_get_envdata( )‚Ì•Ô‚è’l
 * ‚·‚®�ã‚àdi_get_envdata( )‚ÅŽg—p‚µ‚Ä‚¢‚é
 */
#define DI_ENV_TOOLONG_VALUE  -4

/*
 * di_soutput‚ÅŽw’è‚·‚é�‘‚«�ž‚Ý•û–@
 */
#define DI_HOST_BLOCK		0x00
#define DI_HOST_NONBLOCK	0x01

/*
 * ƒfƒBƒXƒN‚ÌŽí—Þ
 */
#define DI_HDD_DOWNLOAD 0
#define DI_HDD_SPOOL    1
#define DI_RAM_DOWNLOAD 2
#define DI_RAM_SPOOL    3
#define DI_HDD_TMP      4
#define DI_SD_DOWNLOAD  5
#define DI_HDD_IPDS_DOWNLOAD	6
#define DI_SD_IPDS_DOWNLOAD	7
#define DI_SD_PICTBRIDGE	8

/*
 * ƒXƒgƒŒ�[ƒW‚ÌŽí—Þ
 */
#define DI_STORAGE_NVRAM 0 /* NVRAM */

/*
 * ‹@”\�î•ñ
 */
#define DI_SYS_FUNC_DUPLEX             (1 << 0)        /* duplex */
#define DI_SYS_FUNC_STAPLE             (1 << 1)        /* staple */
#define DI_SYS_FUNC_PUNCH              (1 << 2)        /* punch */
#define DI_SYS_FUNC_SORT               (1 << 3)        /* sorting */
#define DI_SYS_FUNC_HDD_FS             (1 << 4)        /* HDD for FileSystem */
#define DI_SYS_FUNC_SHIFT              (1 << 5)        /* shift */
#define DI_SYS_FUNC_FINISHER           (1 << 6)        /* Finisher */
#define DI_SYS_FUNC_MAILBOX            (1 << 7)        /* Mail Box */
#define DI_SYS_FUNC_COLOR              (1 << 8)        /* Color (CMYK) */
#define DI_SYS_FUNC_HDD                (1 << 9)        /* HDD */
#define DI_SYS_FUNC_PROOFPRINT         (1 << 10)       /* proof print */
#define DI_SYS_FUNC_SEQUREPRINT        (1 << 11)       /* sequre print */
#define DI_SYS_FUNC_LOCALSTORAGE       (1 << 12)       /* local storage */
#define DI_SYS_FUNC_NETWORK            (1 << 13)       /* network */
#define DI_SYS_FUNC_REMOTEPRINT        (1 << 14)       /* remote print */
#define DI_SYS_FUNC_IEEE1394           (1 << 15)       /* IEEE1394 */
#define DI_SYS_FUNC_MF_MODEL           (1 << 16)       /* MF (not P) Model */
#define DI_SYS_FUNC_LARGEPRINTOUT      (1 << 17)       /* large printout */
#define DI_SYS_FUNC_IEEE802_11b        (1 << 18)       /* IEEE802.11b */
#define DI_SYS_FUNC_USB                (1 << 19)       /* USB */
#define DI_SYS_FUNC_CENTRO             (1 << 20)       /* CENTRO */
#define DI_SYS_FUNC_BLUETOOTH          (1 << 21)       /* Bluetooth */
#define DI_SYS_FUNC_GWMAC              (1 << 22)       /* GWMAC */
#define DI_SYS_FUNC_GIGAETHER          (1 << 23)       /* Gigabit Ethernet */
#define DI_SYS_FUNC_FOLD               (1 << 24)       /* Z�Ü‚è */

/*
 * ƒpƒ“ƒ`�î•ñ
 */
#define DI_SYS_PUNCH_HOLE_JP2          (1 << 0)        /* 2 JP */
#define DI_SYS_PUNCH_HOLE_US2          (1 << 1)        /* 2 US */ 
#define DI_SYS_PUNCH_HOLE_US3          (1 << 2)        /* 3 US */ 
#define DI_SYS_PUNCH_HOLE_EU4          (1 << 3)        /* 4 EU */
#define DI_SYS_PUNCH_HOLE_NEU4         (1 << 4)        /* 4 Northern EU */

/*
 * ƒ`ƒƒƒlƒ‹”Ô�†
 */
#define DI_CHANNEL_LPD                 1               /* LPD */
#define DI_CHANNEL_FTP                 2               /* FTP */
#define DI_CHANNEL_RSH                 3               /* RSH */
#define DI_CHANNEL_DIPRINT             4               /* Direct Print */
#define DI_CHANNEL_IPP                 7               /* IPP */
#define DI_CHANNEL_FAX                 11              /* FAX */
#define DI_CHANNEL_CENTRO              12              /* centronics */
#define DI_CHANNEL_PSERVER             13              /* NetWare(PSERVER) */
#define DI_CHANNEL_NPRINTER            14              /* NetWare(NPRINTER) */
#define DI_CHANNEL_SMB                 15              /* SMB */
#define DI_CHANNEL_PAP                 16              /* AppleTalk PAP */
#define DI_CHANNEL_USB                 21              /* USB */
#define DI_CHANNEL_BT                  22              /* BLUETOOTH */

/*
 * PDL ID
 */
#define DI_PDL_AUTO            -1
#define DI_PDL_RPCS            0
#define DI_PDL_RPDL            1
#define DI_PDL_R98             2
#define DI_PDL_R16             3
#define DI_PDL_R55             4
#define DI_PDL_RPGL            5
#define DI_PDL_HPGL2           6
#define DI_PDL_RTIFF           7
#define DI_PDL_POSTSCRIPT      8
#define DI_PDL_PCL             9
#define DI_PDL_PCLXL           10
#define DI_PDL_TIFF            11
#define DI_PDL_PDF             12
#define DI_PDL_BMLINKS         13
#define	DI_PDL_PICTBRIDGE      14
#define	DI_PDL_XPS             16
#define	DI_PDL_MP_TIFF         30
#define	DI_PDL_MP_JPEG         31

#define DI_NOTIFY_CHANGE_OFF    0       /* not notify if changed */
#define DI_NOTIFY_CHANGE_ON     1       /* notify if changed */

#define DI_DISKSTAT_UNKNOWN		0		/* •s’è�icheck’†�j */
#define DI_DISKSTAT_NONE		1		/* ƒfƒBƒXƒN–³‚µ */
#define DI_DISKSTAT_READY		2		/* Ready */

#define DI_DEVICETYPE_FILE 0x01
#define DI_STRING_LEN_MAX  112
#define   DI_SET_MODIFY           1
#define   DI_RESET_MODIFY         2
#define   DI_SET_DISP             3
#define   DI_HALF_DISP            4
#define   DI_RESET_DISP           5
#define   DI_SET_ACT              6
#define   DI_RESET_ACT            7

#define DI_LANG_JAPANESE		0		/* “ú–{Œê */
#define DI_LANG_ENGLISH			1		/* ‰pŒê */
#define DI_LANG_FRENCH			2		/* ƒtƒ‰ƒ“ƒXŒê */
#define DI_LANG_GERMAN			3		/* ƒhƒCƒcŒê */
#define DI_LANG_ITALIAN			4		/* ƒCƒ^ƒŠƒAŒê */
#define DI_LANG_SPANISH			5		/* ƒXƒyƒCƒ“Œê */
#define DI_LANG_DUTCH			6		/* ƒIƒ‰ƒ“ƒ_Œê */
#define DI_LANG_SWEDISH			7		/* ƒXƒEƒF�[ƒfƒ“Œê */
#define DI_LANG_NORWEGIAN		8		/* ƒmƒ‹ƒEƒF�[Œê */
#define DI_LANG_DANISH			9		/* ƒfƒ“ƒ}�[ƒNŒê */
#define DI_LANG_FINNISH			10		/* ƒtƒBƒ“ƒ‰ƒ“ƒhŒê */
#define DI_LANG_PORTUGUESE		11		/* ƒ|ƒ‹ƒgƒKƒ‹Œê */
#define DI_LANG_CZECH			12		/* ƒ`ƒFƒRŒê */
#define DI_LANG_POLISH			13		/* ƒ|�[ƒ‰ƒ“ƒhŒê */
#define DI_LANG_HUNGARIAN		14		/* ƒnƒ“ƒKƒŠ�[Œê */
#define DI_LANG_CHINESE			15		/* ’†�‘Œê */
#define DI_LANG_TAIWANESE		16		/* ‘ä˜pŒê */
#define DI_LANG_RUSSIAN			17		/* ƒ�ƒVƒAŒê */
#define DI_LANG_HEBREW			18		/* ƒwƒuƒ‰ƒCŒê */
#define DI_LANG_ARABIC			19		/* ƒAƒ‰ƒrƒAŒê */


#define DI_MENU_TYPE_TRAY     5    /* ƒgƒŒƒC�Ý’èƒ�ƒjƒ…�[ */
#define DI_MENU_TYPE_EMUSET   8    /* ƒGƒ~ƒ…ƒŒ�[ƒVƒ‡ƒ“ˆó�ü�ðŒ�ƒ�ƒjƒ…�[ */
#define DI_MENU_TYPE_PRN_NUM  9    /* ƒGƒ~ƒ…ƒŒ�[ƒVƒ‡ƒ“ˆó�ü•”�”ƒ�ƒjƒ…�[ */
#define DI_MENU_TYPE_PCL     15    /* PCLˆó�ü�ðŒ�ƒjƒ…�[ */

#define   DI_ITEM_TYPE_START        0  /* ƒ‹�[ƒg�\‘¢‘ÌƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_MENU         1  /* ƒ�ƒjƒ…�[Œ^‰æ–Ê—pƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_EXECUTING    3  /* ŽÀ�sŒ^‰æ–Ê—pƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq  */
#define   DI_ITEM_TYPE_SELECT       2  /* ‘I‘ðŽˆŒ^‰æ–Ê—pƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_INTEGER      5  /* �®�”’lŒ^‰æ–Ê—pƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_FLOAT        6  /* �¬�”’lŒ^‰æ–Ê—pƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_PRN_NUM      8  /* ˆó�ü•”�”‰æ–Ê—pƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_PTIME       14  /* —pŽ†•Ï”{—¦ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_ANY         15  /* ”CˆÓƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_FLOAT_EXT   16  /* �¬�”’lŒ…Šg’£“Á‰»Œ^ƒAƒCƒeƒ€ƒ^ƒCƒvŽ¯•ÊŽq */
#define   DI_ITEM_TYPE_PTIME_FLT   20  /* �¬�”Œ^—pŽ†•Ï”{—¦ƒ^ƒCƒvŽ¯•ÊŽq */


#define DI_INTERP_TESTPRINT_SUMMARY			-1	/* ƒCƒ“ƒ^ƒvƒŠƒ^ƒTƒ}ƒŠ�[(ˆó�ü�ðŒ�)ˆó�ü */
#define DI_INTERP_TESTPRINT_FONTSET				1	/* ƒtƒHƒ“ƒgƒZƒbƒgˆó�ü */
#define DI_INTERP_TESTPRINT_FONTALL				2	/* ‘S•¶Žšˆó�ü */
#define DI_INTERP_TESTPRINT_PROGRAM				3	/* ƒvƒ�ƒOƒ‰ƒ€ˆê——ˆó�ü */
#define DI_INTERP_TESTPRINT_FORMLIST			4	/* “o˜^ƒtƒH�[ƒ€ˆê——ˆó�ü */
#define DI_INTERP_TESTPRINT_PSINFO				5	/* PostScript info list */
#define DI_INTERP_TESTPRINT_COLORSAMPLE			6	/* ƒJƒ‰�[ƒTƒ“ƒvƒ‹ˆó�ü */
#define DI_INTERP_TESTPRINT_COLORMATCHING		7	/* �F‚¸‚ê•â�³ */
#define DI_INTERP_TESTPRINT_COLORTEST			8	/* ƒJƒ‰�[ƒeƒXƒg */
#define DI_INTERP_TESTPRINT_GAMMA_USER1			9	/* ŠK’²•â�³‚P */
#define DI_INTERP_TESTPRINT_GAMMA_USER2			10	/* ŠK’²•â�³‚Q */
#define DI_INTERP_TESTPRINT_COLORSHIFT_SET		11	/* ’è’…‘¬“x•â�³�Ý’è—p */
#define DI_INTERP_TESTPRINT_COLORSHIFT_CHECK	12	/* ’è’…‘¬“x•â�³Šm”F—p */
#define DI_INTERP_TESTPRINT_PDFINFO				13	/* PDF info list */
#define DI_INTERP_TESTPRINT_MICR				20	/* MICR testsheet */

#define	DI_BIT_SW_001	0
#define	DI_BIT_SW_002	1
#define	DI_BIT_SW_003	2
#define	DI_BIT_SW_004	3
#define	DI_BIT_SW_005	4
#define	DI_BIT_SW_006	5
#define	DI_BIT_SW_007	6
#define	DI_BIT_SW_008	7
#define	DI_BIT_SW_009	8
#define	DI_BIT_SW_010	9
#define	DI_BIT_SW_011	10
#define	DI_BIT_SW_012	11
#define	DI_BIT_SW_013	12
#define	DI_BIT_SW_014	13
#define	DI_BIT_SW_015	14
#define	DI_BIT_SW_016	15
#define DI_BIT_SW_NUM	16

/*
 *    request reqson
 */
#define       DI_REQ_PROC_REASON_ENTERLANGUAGE        0       /* PJL ENTER LANGUAGE=XXX */
#define       DI_REQ_PROC_REASON_FILETYPE             1       /* filetype=XXX */
#define       DI_REQ_PROC_REASON_AUTOSENSE            2       /* auto sense */
#define       DI_REQ_PROC_REASON_NOSENSE              3       /* no sense */
#define       DI_REQ_PROC_REASON_EMCHGCMD             4       /* EM CHANGE COMMAND */
#define       DI_REQ_PROC_REASON_PANEL                5       /* panel */

/*
 *	parmanent font
 */
#define DI_DOWNLOADINFO_CREATE		0
#define DI_DOWNLOADINFO_OPEN		1
#define DI_DOWNLOADINFO_DIR		2
#define DI_DOWNLOADINFO_FILE		3

#define DI_PATHMAX	336

#define PERMFONTFILEEXTENSION	".fnt"

/*
*	return of di_get_printcondition()
*/
#define DI_PCND_OK_ALL			3
#define DI_PCND_OK_MEDIA		2
#define DI_PCND_OK_COND			1
#define DI_PCND_OK_NONE			0
#define DI_PCND_NG_ERROR		-1
#define DI_PCND_NG_NOTSUPPORT	-2
/*
*	return of di_get_printconditionShm()
*/
#define DI_PCND_SHM_OK			0
#define DI_PCND_SHM_NG			-1
/*
*	status of di_get_printconditionShm()
*/
#define DI_PCND_SHM_STATUS_COND		0
#define DI_PCND_SHM_STATUS_NONE		-1

/*
*	memory required for zlib
*/
#define DI_ZLIB_MEMORY	(64 * 1024)		/* 64KB */

/*
 *  MICR model type
*/
enum {
	DI_SYS_MODEL_STANDARD,			/* RICOH standard model */
	DI_SYS_MODEL_MICR_SECURE_PCL,	/* Secure PCL MICR model */
	DI_SYS_MODEL_MICR_IPDS,			/* IPDS MICR model */
};

/* memory Šm•ÛŠÖ�”‚ÌŒ^ */
typedef char* (*DI_CALLBACK_MEMALLOC)( unsigned long );
/* memory ‰ð•úŠÖ�”‚ÌŒ^ */
typedef void (*DI_CALLBACK_MEMFREE)( char * );
/* ƒR�[ƒ‹ƒoƒbƒNŠÖ�”‚ÌŒ^ */
typedef void (*DI_CALLBACK_FUNC)( void );

/* ƒfƒBƒU�î•ñ�\‘¢‘Ì */
typedef struct di_ditinfo {
	unsigned char	*dit_ptr;		/* ƒfƒBƒU‚Ì�æ“ªƒAƒhƒŒƒX */
	unsigned char	x_size;			/* •� */
	unsigned char	y_size;			/* �‚‚³ */
	unsigned char	dit_order;		/* ƒfƒBƒU‚ÌƒI�[ƒ_’lŽg—pON/OFF */
									/* [0: Žg—p‚µ‚È‚¢, 0x40: Žg—p‚·‚é] */
	unsigned short	rearrange;		/* ƒŠƒAƒŒƒ“ƒWƒ}ƒgƒŠƒbƒNƒXƒpƒ^�[ƒ“ ID */
									/* gps_pagemode_t ŽQ�Æ */
	unsigned char	e_flag_max;		/* engine flag for color level: 255 */
	unsigned char	e_flag_mid;		/* engine flag for color level: 1 to 254 */
} dit_info_t, di_ditinfo_t;

/* ‰ð‘œ“x�\‘¢‘Ì */
typedef struct di_resoinfo {
	unsigned int	x;	/* Žå‘–�¸•ûŒü‰ð‘œ“x */
	unsigned int	y;	/* •›‘–�¸•ûŒü‰ð‘œ“x */
} reso_info_t, di_resoinfo_t;

/* ‰ð‘œ“x�\‘¢‘Ì(ƒrƒbƒg‚Æ‚Ì‘g�‡‚¹) */
typedef struct di_resolutioninfo {
	unsigned int	x;		/* Žå‘–�¸•ûŒü‰ð‘œ“x */
	unsigned int	y;		/* •›‘–�¸•ûŒü‰ð‘œ“x */
	unsigned char	bit;		/* ƒrƒbƒg�” */
	unsigned char   paper;		/* Ž†Ží */
	unsigned char	dit_mode;	/* ƒfƒBƒUƒ‚�[ƒh */
	unsigned char   prt_mode;	/* ƒvƒŠƒ“ƒ^ƒhƒ‰ƒCƒo‚Å‚Ìƒ‚�[ƒh */
} resolution_info_t, di_resolutioninfo_t;

/* ‘�—Ê‹K�§’l�î•ñ�\‘¢‘Ì */
typedef struct di_tlimitinfo {
	di_resolutioninfo_t	reso;	/* ‰ð‘œ“x�Ball 0‚È‚ç‰ð‘œ“x‚ÌŽw’è‚È‚µ */
	int					text;	/* •¶ŽšƒIƒuƒWƒFƒNƒg‚Ì‘�—Ê‹K�§’l */
	int					line;	/* �ü‰æƒIƒuƒWƒFƒNƒg‚Ì‘�—Ê‹K�§’l */
	int					phot;	/* ŽÊ�^ƒIƒuƒWƒFƒNƒg‚Ì‘�—Ê‹K�§’l */
	int					fill;	/* “h‚è‚Â‚Ô‚µƒIƒuƒWƒFƒNƒg‚Ì‘�—Ê‹K�§’l */
} tlimit_info_t, di_tlimitinfo_t;

/* ƒgƒŒƒC�î•ñ */
typedef struct di_onetrayinfo {
	unsigned short	id;				/* tray ID */
	unsigned char	p_size;			/* —pŽ†ƒTƒCƒY(di_paperdef.hŽQ�Æ) */
#define DI_PAPER_AUTO          (0x00)          /* Ž†ŽíŽw’è‚È‚µ */
#define DI_PAPER_NORMAL        (0x01)          /* •�’ÊŽ† */
#define DI_PAPER_RECYCLE       (0x02)          /* �Ä�¶Ž† */
#define DI_PAPER_SPECIAL       (0x03)          /* “ÁŽêŽ† */
#define DI_PAPER_TRACING       (0x04)          /* ƒgƒŒ�[ƒVƒ“ƒOŽ† */
#define DI_PAPER_OHP           (0x05)          /* OHP */
#define DI_PAPER_LABEL         (0x06)          /* ƒ‰ƒxƒ‹Ž† */
#define DI_PAPER_BOND          (0x07)          /* ƒ{ƒ“ƒhŽ† */
#define DI_PAPER_CARDSTOCK     (0x08)          /* ƒJ�[ƒhƒXƒgƒbƒN */
#define DI_PAPER_CARDBOARD     (0x09)          /* ŒúŽ† */
#define DI_PAPER_PREPRINT      (0x0A)          /* ˆó�ü�Ï‚ÝŽ† */
#define DI_PAPER_LETTER_HEAD   (0x0B)          /* ƒŒƒ^�[ƒwƒbƒhŽ† */
#define DI_PAPER_LTHEAD        (0x0B)          /* ”pŽ~—\’è */
#define DI_PAPER_PUNCH         (0x0C)          /* ƒpƒ“ƒ`�Ï‚ÝŽ† */
#define DI_PAPER_PREPUNCH      (0x0C)          /* ”pŽ~—\’è */
#define DI_PAPER_TAB           (0x0D)          /* ƒ^ƒuŽ† */
#define DI_PAPER_COLOR         (0x0E)          /* �FŽ† */
#define DI_PAPER_NORMAL2ND     (0x0F)          /* •�’ÊŽ†(— –Ê) */
#define DI_PAPER_CARDBOARD2ND  (0x10)          /* ŒúŽ†(— –Ê) */
#define DI_PAPER_THIN          (0x11)          /* ”–Ž† */
#define DI_PAPER_GLOSSY        (0x12)          /* Œõ‘òŽ† */
#define DI_PAPER_USED          (0x13)          /* — Ž†�iŽg—p�Ï‚Ý�j */
#define DI_PAPER_POSTCARD      (0x14)          /* ƒnƒKƒL */
#define DI_PAPER_POSTCARD2ND   (0x15)          /* ƒnƒKƒL(— –Ê) */
#define DI_PAPER_CARDBOARD2    (0x16)          /* ŒúŽ†‚Q */
#define DI_PAPER_FILM          (0x17)          /* ƒtƒBƒ‹ƒ€Ž†�i�}–ÊƒRƒs�[—p�j */
#define DI_PAPER_INKPOST       (0x18)          /* ƒCƒ“ƒNƒWƒFƒbƒg—p‚Í‚ª‚« */
#define DI_PAPER_HG_NORMAL     (0x19)          /* HG•�’ÊŽ† */
#define DI_PAPER_ENVELOPE      (0x1A)          /* ••“› */
#define DI_PAPER_CARDBOARD3    (0x1B)          /* ŒúŽ†‚R */
#define DI_PAPER_SPECIAL2      (0x1C)          /* “ÁŽêŽ†‚Q */
#define DI_PAPER_SPECIAL3      (0x1D)          /* “ÁŽêŽ†‚R */
#define DI_PAPER_MIDDLETHICK   (0x1E)          /* ’†ŒúŒû */
#define DI_PAPER_COATED        (0x1F)          /* ƒR�[ƒgŽ† */
#define DI_PAPER_CARDBOARD2REV (0x20)          /* ŒúŽ†‚Q(— –Ê) */
#define DI_PAPER_CARDBOARD3REV (0x21)          /* ŒúŽ†‚R(— –Ê) */
#define DI_PAPER_NORMAL2       (0x22)          /* •�’ÊŽ†‚Q */
#define DI_PAPER_THICKGLOSSY   (0x23)          /* ŒúŽèŒõ‘òŽ† */
#define DI_PAPER_SPECIAL4      (0x24)          /* “ÁŽêŽ†‚S */
#define DI_PAPER_SPECIAL5      (0x25)          /* “ÁŽêŽ†‚T */
#define DI_PAPER_SPECIAL6      (0x26)          /* “ÁŽêŽ†‚U */
#define DI_PAPER_USER_DEF1     (0x30)          /* ƒ†�[ƒUŽw’è‚P */
#define DI_PAPER_USER_DEF2     (0x31)          /* ƒ†�[ƒUŽw’è‚Q */
#define DI_PAPER_USER_DEF3     (0x32)          /* ƒ†�[ƒUŽw’è‚R */
#define DI_PAPER_USER_DEF4     (0x33)          /* ƒ†�[ƒUŽw’è‚S */
#define DI_PAPER_USER_DEF5     (0x34)          /* ƒ†�[ƒUŽw’è‚T */
#define DI_PAPER_USER_DEF6     (0x35)          /* ƒ†�[ƒUŽw’è‚U */
#define DI_PAPER_USER_DEF7     (0x36)          /* ƒ†�[ƒUŽw’è‚V */
#define DI_PAPER_USER_DEF8     (0x37)          /* ƒ†�[ƒUŽw’è‚W */
#define DI_PAPER_USER_DEF0     (0x38)          /* ƒ†�[ƒUŽw’è‚O�i–¢“o˜^ƒJƒXƒ^ƒ€Ž†Ží�j */
#define DI_PAPER_COLOR1        (0x40)          /* �FŽ†‚P           */
#define DI_PAPER_COLOR2        (0x41)          /* �FŽ†‚Q           */
#define DI_PAPER_COLOR_WHITE   (0x50)          /* Žg—p•s‰Â(•W�€) */
#define DI_PAPER_COLOR_YELLOW  (0x51)          /* ‰© */
#define DI_PAPER_COLOR_GREEN   (0x52)          /* —Î */
#define DI_PAPER_COLOR_BLUE    (0x53)          /* �Â */
#define DI_PAPER_COLOR_PURPLE  (0x54)          /* Ž‡ */
#define DI_PAPER_COLOR_IVORY   (0x55)          /* ƒAƒCƒ{ƒŠ�[ */
#define DI_PAPER_COLOR_ORANGE  (0x56)          /* žò */
#define DI_PAPER_COLOR_PINK    (0x57)          /* “� */
#define DI_PAPER_COLOR_RED     (0x58)          /* �Ô */
#define DI_PAPER_COLOR_GRAY    (0x59)          /* ŠD */
#define DI_PAPER_GLOSSY_COATED		(0x60)	/* glossy coated */
#define DI_PAPER_THICK_GLOSSY_COATED	(0x61)	/* thick glossy coated */
#define DI_PAPER_MAT_COATED		(0x62)	/* matt coated */
#define DI_PAPER_THICK_MAT_COATED	(0x63)	/* thick matt coated */
#define DI_PAPER_WATER_PROOF		(0x64)	/* waterproof */
#define DI_PAPER_CARDBOARD4		(0x65)	/* cardboard 4 */
#define DI_PAPER_CARDBOARD4REV		(0x66)	/* cardboard 4 (reverse) */
#define DI_PAPER_COATED_HIGH_GLOSSY	(0x67)	/* high glossy coated */
#define DI_PAPER_SEMIGLOSSY		(0x68)
#define DI_PAPER_INKJETPLAIN	(0x69)
#define DI_PAPER_MATFILM		(0x6C)
#define DI_PAPER_CADCOATED		(0x6D)
#define DI_PAPER_NONE          (0x80)          /* ƒgƒŒƒC‚É�Ý’è‚³‚ê‚Ä‚¢‚éŽ†Ží(“Á’èPDL‚©‚ÂƒgƒŒƒCŽw’èŽž‚Ì‚ÝŽg—p‰Â) */
#define DI_PAPER_USER_DEF9			(0x81)	/* ƒ†�[ƒUŽw’è‚X(IMSS) */
#define DI_PAPER_USER_DEF10			(0x82)	/* ƒ†�[ƒUŽw’è‚P‚O(IMSS) */
#define DI_PAPER_USER_DEF11			(0x83)	/* ƒ†�[ƒUŽw’è‚P‚P(IMSS) */
#define DI_PAPER_USER_DEF12			(0x84)	/* ƒ†�[ƒUŽw’è‚P‚Q(IMSS) */
#define DI_PAPER_USER_DEF13			(0x85)	/* ƒ†�[ƒUŽw’è‚P‚R(IMSS) */
#define DI_PAPER_USER_DEF14			(0x86)	/* ƒ†�[ƒUŽw’è‚P‚S(IMSS) */
#define DI_PAPER_USER_DEF15			(0x87)	/* ƒ†�[ƒUŽw’è‚P‚T(IMSS) */
#define DI_PAPER_USER_DEF16			(0x88)	/* ƒ†�[ƒUŽw’è‚P‚U(IMSS) */
#define DI_PAPER_USER_DEF17			(0x89)	/* ƒ†�[ƒUŽw’è‚P‚V(IMSS) */
#define DI_PAPER_USER_DEF18			(0x8A)	/* ƒ†�[ƒUŽw’è‚P‚W(IMSS) */
#define DI_PAPER_USER_DEF19			(0x8B)	/* ƒ†�[ƒUŽw’è‚P‚X(IMSS) */
#define DI_PAPER_USER_DEF20			(0x8C)	/* ƒ†�[ƒUŽw’è‚Q‚O(IMSS) */
#define DI_PAPER_USER_DEF21			(0x8D)	/* ƒ†�[ƒUŽw’è‚Q‚P(IMSS) */
#define DI_PAPER_USER_DEF22			(0x8E)	/* ƒ†�[ƒUŽw’è‚Q‚Q(IMSS) */
#define DI_PAPER_USER_DEF23			(0x8F)	/* ƒ†�[ƒUŽw’è‚Q‚R(IMSS) */
#define DI_PAPER_USER_DEF24			(0x90)	/* ƒ†�[ƒUŽw’è‚Q‚S(IMSS) */
#define DI_PAPER_USER_DEF25			(0x91)	/* ƒ†�[ƒUŽw’è‚Q‚T(IMSS) */
#define DI_PAPER_USER_DEF26			(0x92)	/* ƒ†�[ƒUŽw’è‚Q‚U(IMSS) */
#define DI_PAPER_USER_DEF27			(0x93)	/* ƒ†�[ƒUŽw’è‚Q‚V(IMSS) */
#define DI_PAPER_USER_DEF28			(0x94)	/* ƒ†�[ƒUŽw’è‚Q‚W(IMSS) */
#define DI_PAPER_USER_DEF29			(0x95)	/* ƒ†�[ƒUŽw’è‚Q‚X(IMSS) */
#define DI_PAPER_USER_DEF30			(0x96)	/* ƒ†�[ƒUŽw’è‚R‚O(IMSS) */
#define DI_PAPER_USER_DEF31			(0x97)	/* ƒ†�[ƒUŽw’è‚R‚P(IMSS) */
#define DI_PAPER_USER_DEF32			(0x98)	/* ƒ†�[ƒUŽw’è‚R‚Q(IMSS) */
#define DI_PAPER_USER_DEF33			(0x99)	/* ƒ†�[ƒUŽw’è‚R‚R(IMSS) */
#define DI_PAPER_USER_DEF34			(0x9A)	/* ƒ†�[ƒUŽw’è‚R‚S(IMSS) */
#define DI_PAPER_USER_DEF35			(0x9B)	/* ƒ†�[ƒUŽw’è‚R‚T(IMSS) */
#define DI_PAPER_USER_DEF36			(0x9C)	/* ƒ†�[ƒUŽw’è‚R‚U(IMSS) */
#define DI_PAPER_USER_DEF37			(0x9D)	/* ƒ†�[ƒUŽw’è‚R‚V(IMSS) */
#define DI_PAPER_USER_DEF38			(0x9E)	/* ƒ†�[ƒUŽw’è‚R‚W(IMSS) */
#define DI_PAPER_USER_DEF39			(0x9F)	/* ƒ†�[ƒUŽw’è‚R‚X(IMSS) */
#define DI_PAPER_USER_DEF40			(0xA0)	/* ƒ†�[ƒUŽw’è‚S‚O(IMSS) */
#define DI_PAPER_USER_DEF41			(0xA1)	/* ƒ†�[ƒUŽw’è‚S‚P(IMSS) */
#define DI_PAPER_USER_DEF42			(0xA2)	/* ƒ†�[ƒUŽw’è‚S‚Q(IMSS) */
#define DI_PAPER_USER_DEF43			(0xA3)	/* ƒ†�[ƒUŽw’è‚S‚R(IMSS) */
#define DI_PAPER_USER_DEF44			(0xA4)	/* ƒ†�[ƒUŽw’è‚S‚S(IMSS) */
#define DI_PAPER_USER_DEF45			(0xA5)	/* ƒ†�[ƒUŽw’è‚S‚T(IMSS) */
#define DI_PAPER_USER_DEF46			(0xA6)	/* ƒ†�[ƒUŽw’è‚S‚U(IMSS) */
#define DI_PAPER_USER_DEF47			(0xA7)	/* ƒ†�[ƒUŽw’è‚S‚V(IMSS) */
#define DI_PAPER_USER_DEF48			(0xA8)	/* ƒ†�[ƒUŽw’è‚S‚W(IMSS) */
#define DI_PAPER_USER_DEF49			(0xA9)	/* ƒ†�[ƒUŽw’è‚S‚X(IMSS) */
#define DI_PAPER_USER_DEF50			(0xAA)	/* ƒ†�[ƒUŽw’è‚T‚O(IMSS) */
#define DI_PAPER_USER_DEF51			(0xAB)	/* ƒ†�[ƒUŽw’è‚T‚P(IMSS) */
#define DI_PAPER_USER_DEF52			(0xAC)	/* ƒ†�[ƒUŽw’è‚T‚Q(IMSS) */
#define DI_PAPER_USER_DEF53			(0xAD)	/* ƒ†�[ƒUŽw’è‚T‚R(IMSS) */
#define DI_PAPER_USER_DEF54			(0xAE)	/* ƒ†�[ƒUŽw’è‚T‚S(IMSS) */
#define DI_PAPER_USER_DEF55			(0xAF)	/* ƒ†�[ƒUŽw’è‚T‚T(IMSS) */
#define DI_PAPER_USER_DEF56			(0xB0)	/* ƒ†�[ƒUŽw’è‚T‚U(IMSS) */
#define DI_PAPER_USER_DEF57			(0xB1)	/* ƒ†�[ƒUŽw’è‚T‚V(IMSS) */
#define DI_PAPER_USER_DEF58			(0xB2)	/* ƒ†�[ƒUŽw’è‚T‚W(IMSS) */
#define DI_PAPER_USER_DEF59			(0xB3)	/* ƒ†�[ƒUŽw’è‚T‚X(IMSS) */
#define DI_PAPER_USER_DEF60			(0xB4)	/* ƒ†�[ƒUŽw’è‚U‚O(IMSS) */
#define DI_PAPER_USER_DEF61			(0xB5)	/* ƒ†�[ƒUŽw’è‚U‚P(IMSS) */
#define DI_PAPER_USER_DEF62			(0xB6)	/* ƒ†�[ƒUŽw’è‚U‚Q(IMSS) */
#define DI_PAPER_USER_DEF63			(0xB7)	/* ƒ†�[ƒUŽw’è‚U‚R(IMSS) */
#define DI_PAPER_USER_DEF64			(0xB8)	/* ƒ†�[ƒUŽw’è‚U‚S(IMSS) */
#define DI_PAPER_USER_DEF65			(0xB9)	/* ƒ†�[ƒUŽw’è‚U‚T(IMSS) */
#define DI_PAPER_USER_DEF66			(0xBA)	/* ƒ†�[ƒUŽw’è‚U‚U(IMSS) */
#define DI_PAPER_USER_DEF67			(0xBB)	/* ƒ†�[ƒUŽw’è‚U‚V(IMSS) */
#define DI_PAPER_USER_DEF68			(0xBC)	/* ƒ†�[ƒUŽw’è‚U‚W(IMSS) */
#define DI_PAPER_USER_DEF69			(0xBD)	/* ƒ†�[ƒUŽw’è‚U‚X(IMSS) */
#define DI_PAPER_USER_DEF70			(0xBE)	/* ƒ†�[ƒUŽw’è‚V‚O(IMSS) */
#define DI_PAPER_USER_DEF71			(0xBF)	/* ƒ†�[ƒUŽw’è‚V‚P(IMSS) */
#define DI_PAPER_USER_DEF72			(0xC0)	/* ƒ†�[ƒUŽw’è‚V‚Q(IMSS) */
#define DI_PAPER_USER_DEF73			(0xC1)	/* ƒ†�[ƒUŽw’è‚V‚R(IMSS) */
#define DI_PAPER_USER_DEF74			(0xC2)	/* ƒ†�[ƒUŽw’è‚V‚S(IMSS) */
#define DI_PAPER_USER_DEF75			(0xC3)	/* ƒ†�[ƒUŽw’è‚V‚T(IMSS) */
#define DI_PAPER_USER_DEF76			(0xC4)	/* ƒ†�[ƒUŽw’è‚V‚U(IMSS) */
#define DI_PAPER_USER_DEF77			(0xC5)	/* ƒ†�[ƒUŽw’è‚V‚V(IMSS) */
#define DI_PAPER_USER_DEF78			(0xC6)	/* ƒ†�[ƒUŽw’è‚V‚W(IMSS) */
#define DI_PAPER_USER_DEF79			(0xC7)	/* ƒ†�[ƒUŽw’è‚V‚X(IMSS) */
#define DI_PAPER_USER_DEF80			(0xC8)	/* ƒ†�[ƒUŽw’è‚W‚O(IMSS) */
#define DI_PAPER_USER_DEF81			(0xC9)	/* ƒ†�[ƒUŽw’è‚W‚P(IMSS) */
#define DI_PAPER_USER_DEF82			(0xCA)	/* ƒ†�[ƒUŽw’è‚W‚Q(IMSS) */
#define DI_PAPER_USER_DEF83			(0xCB)	/* ƒ†�[ƒUŽw’è‚W‚R(IMSS) */
#define DI_PAPER_USER_DEF84			(0xCC)	/* ƒ†�[ƒUŽw’è‚W‚S(IMSS) */
#define DI_PAPER_USER_DEF85			(0xCD)	/* ƒ†�[ƒUŽw’è‚W‚T(IMSS) */
#define DI_PAPER_USER_DEF86			(0xCE)	/* ƒ†�[ƒUŽw’è‚W‚U(IMSS) */
#define DI_PAPER_USER_DEF87			(0xCF)	/* ƒ†�[ƒUŽw’è‚W‚V(IMSS) */
#define DI_PAPER_USER_DEF88			(0xD0)	/* ƒ†�[ƒUŽw’è‚W‚W(IMSS) */
#define DI_PAPER_USER_DEF89			(0xD1)	/* ƒ†�[ƒUŽw’è‚W‚X(IMSS) */
#define DI_PAPER_USER_DEF90			(0xD2)	/* ƒ†�[ƒUŽw’è‚X‚O(IMSS) */
#define DI_PAPER_USER_DEF91			(0xD3)	/* ƒ†�[ƒUŽw’è‚X‚P(IMSS) */
#define DI_PAPER_USER_DEF92			(0xD4)	/* ƒ†�[ƒUŽw’è‚X‚Q(IMSS) */
#define DI_PAPER_USER_DEF93			(0xD5)	/* ƒ†�[ƒUŽw’è‚X‚R(IMSS) */
#define DI_PAPER_USER_DEF94			(0xD6)	/* ƒ†�[ƒUŽw’è‚X‚S(IMSS) */
#define DI_PAPER_USER_DEF95			(0xD7)	/* ƒ†�[ƒUŽw’è‚X‚T(IMSS) */
#define DI_PAPER_USER_DEF96			(0xD8)	/* ƒ†�[ƒUŽw’è‚X‚U(IMSS) */
#define DI_PAPER_USER_DEF97			(0xD9)	/* ƒ†�[ƒUŽw’è‚X‚V(IMSS) */
#define DI_PAPER_USER_DEF98			(0xDA)	/* ƒ†�[ƒUŽw’è‚X‚W(IMSS) */
#define DI_PAPER_USER_DEF99			(0xDB)	/* ƒ†�[ƒUŽw’è‚X‚X(IMSS) */
#define DI_PAPER_USER_DEF100		(0xDC)	/* ƒ†�[ƒUŽw’è‚P‚O‚O(IMSS) */

	unsigned char	p_kind;			/* Ž†Ží’è‹`(‚·‚®�ã‚Ìdefine) */
#define DI_TRAY_MANUAL          (1 << 0)    /* (attr) manual */
#define DI_TRAY_TANDEM          (1 << 1)    /* (attr) tandem */
#define DI_TRAY_NODUPLEX        (1 << 2)    /* (attr) noduplex */
#define DI_TRAY_LOCKED          (1 << 3)    /* (attr) tray locked */
#define DI_TRAY_SIZE_SENSE      (1 << 4)    /* (attr) sense paper size */
#define DI_TRAY_NODUPLEX_PAPER  (1 << 5)    /* (attr) noduplex paper(size | type) */
#define DI_TRAY_FRONTCOVERPRINT (1 << 6)    /* (attr) frontcoverprint */
#define DI_TRAY_SLIPSHEET       (1 << 7)    /* (attr) slipsheet */
#define DI_TRAY_INNERLCT        (1 << 8)    /* (attr) INNER LCT */
#define DI_TRAY_CHAPTERSHEET1   (1 << 9)    /* (attr) chaptersheet1 */
#define DI_TRAY_CHAPTERSHEET2   (1 << 10)   /* (attr) chaptersheet2 */
#define DI_TRAY_CHAPTERSHEET3   (1 << 11)   /* (attr) chaptersheet3 */
#define DI_TRAY_CHAPTERSHEET4   (1 << 12)   /* (attr) chaptersheet4 */
#define DI_TRAY_CHAPTERSHEET5   (1 << 13)   /* (attr) chaptersheet5 */
#define DI_TRAY_CHAPTERSHEET6   (1 << 14)   /* (attr) chaptersheet6 */
#define DI_TRAY_CHAPTERSHEET7   (1 << 15)   /* (attr) chaptersheet7 */
#define DI_TRAY_BACKCOVERPRINT  (1 << 16)   /* (attr) backcoverprint */
#define DI_TRAY_PARTITION       (1 << 17)   /* (attr) partition */
#define DI_TRAY_TANDEM_SEPARATE (1 << 18)   /* (attr) tandem(separate) */
#define DI_TRAY_ROLL            (1 << 19)   /* (attr) roll tray */
#define DI_TRAY_MSIZESENSE_VALID	(1 << 20)	/* (attr) Žè�·‚µŽ©“®ƒTƒCƒYŒŸ’m—LŒø */
#define DI_TRAY_SINGLE_PAPER    (1 << 21)   /* (attr) ˆê–‡ƒgƒŒƒC */
#define DI_TRAY_CHAPTERSHEET8   (1 << 22)   /* (attr) chaptersheet8 */
#define DI_TRAY_CHAPTERSHEET9   (1 << 23)   /* (attr) chaptersheet9 */
#define DI_TRAY_SMALLSIZE_TYPE  (1 << 24)   /* (attr) �¬ƒTƒCƒYƒgƒŒƒC�Ý’è‚ªON */
	unsigned long	attr;			/* ƒgƒŒƒCŽí—Þ(‚·‚®�ã‚Ìdefine) */
#define DI_TRAY_PAPEREND       (1 << 0)
#define DI_TRAY_BUSY           (1 << 1)
#define DI_TRAY_SETFAIL        (1 << 2)
#define DI_TRAY_ERROR          (1 << 3)
#define DI_TRAY_COPEN          (1 << 4)
#define DI_TRAY_MAN_PAPEREXIST (1 << 5)
#define DI_TRAY_MAN_OPEN       (1 << 6)
#define DI_TRAY_MAN_SIZE       (1 << 7)
#define DI_TRAY_TAN_MISSSET    (1 << 8)
#define DI_TRAY_TAN_BUSY       (1 << 9)
#define DI_TRAY_UNLOAD         (1 << 10)
#define DI_TRAY_TAN_PAPEREXIST (1 << 11)
#define DI_TRAY_TAN_INVALID    (1 << 12)
#define DI_TRAY_DOOR_OPEN      (1 << 13)
	unsigned long	status;			/* ƒXƒe�[ƒ^ƒX(‚·‚®�ã‚Ìdefine) */
	unsigned long	p_length;		/* —pŽ†�‚‚³(0.1mm’PˆÊ) */
	unsigned long	p_width;		/* —pŽ†•�(0.1mm’PˆÊ) */
} tray_info_t, di_onetrayinfo_t;

typedef struct di_trayinfo {
	long				tray_num;					/* ƒgƒŒƒC�” */
	di_onetrayinfo_t	trayinfo[DI_MAX_TRAY_NUM];	/* ŠeƒgƒŒƒC‚Ì�î•ñ */
} di_trayinfo_t;

typedef struct di_optinfo {
#define DI_OPT_EXT_EXTLCT              (1 << 31)       /* ext. LCT */
#define DI_OPT_EXT_TRAY2               (1 << 30)       /* Tray2 */
#define DI_OPT_EXT_TRAY3               (1 << 29)       /* Tray3 */
#define DI_OPT_EXT_BANK                (1 << 28)       /* BANK */
#define DI_OPT_EXT_TANDEM              (1 << 27)       /* TANDEM */
#define DI_OPT_EXT_TRAYMAN             (1 << 26)       /* MANUAL TRAY */
#define DI_OPT_EXT_INLCT               (1 << 25)       /* INNER LCT */
#define DI_OPT_EXT_TRAY4               (1 << 24)       /* Tray4 */
#define DI_OPT_EXT_TRAY5               (1 << 23)       /* Tray5 */
#define DI_OPT_EXT_INSERTER            (1 << 22)       /* INSERTER */
#define DI_OPT_EXT_TRAY7               (1 << 21)       /* Tray7 */
#define DI_OPT_EXT_ROLL_FEEDER         (1 << 20)       /* Roll Unit */
#define DI_OPT_EXT_INSERTER2           (1 << 19)       /* INSERTER2(2’i) */
#define DI_OPT_EXT_LARGELCT            (1 << 18)       /* Large Size LCT */
#define DI_OPT_EXT_ROLL_FEEDER2        (1 << 17)       /* Roll Unit2 */
	unsigned long	tray;		/* ‹‹Ž†ŒnƒIƒvƒVƒ‡ƒ“‹@Šíƒtƒ‰ƒO */
#define DI_OPT_EXT_1BIN                (1 << 31)       /* 1BIN */
#define DI_OPT_EXT_EXTTRAY             (1 << 30)       /* ext. tray */
#define DI_OPT_EXT_INSHIFT             (1 << 29)       /* INNER SHIFT */
#define DI_OPT_EXT_SUPERIOR            (1 << 28)       /* SUPERIOR */
	unsigned long	bin;		/* ”rŽ†ŒnƒIƒvƒVƒ‡ƒ“‹@Šíƒtƒ‰ƒO */
#define DI_OPT_EXT_DUPLEX              (1)
	unsigned long	duplex;		/* —¼–Êƒ†ƒjƒbƒgƒIƒvƒVƒ‡ƒ“‹@Šíƒtƒ‰ƒO */
#define DI_OPT_EXT_FIN_YUKON           (1)
#define DI_OPT_EXT_FIN_LAWRENCE        (2)
#define DI_OPT_EXT_FIN_SADDLE          (3)             /* TONEGAWA */
#define DI_OPT_EXT_FIN_SHINKAWA        (4)
#define DI_OPT_EXT_FIN_FUJIGAWA        (5)
#define DI_OPT_EXT_FIN_KING            (6)
#define DI_OPT_EXT_FIN_BRAZOS_NON      (7)
#define DI_OPT_EXT_FIN_BRAZOS_PRF      (8)
#define DI_OPT_EXT_FIN_VICTORIA_B      (9)
#define DI_OPT_EXT_FIN_ZAIRE_SDL       (10)
#define DI_OPT_EXT_FIN_ZAIRE_NON       (11)
#define DI_OPT_EXT_FIN_TONEGAWA_C      (12)
#define DI_OPT_EXT_FIN_PLOKMATIC       (13)    /* VICTORIA-B+PLOKMATIC */
#define DI_OPT_EXT_FIN_KINUGAWA        (14)
#define DI_OPT_EXT_FIN_HUDOSON         (15)    /* GAIA_P1—pFIN –{‘Ì”rŽ†‚ð‚Â‚Ô‚µ‚ÄƒXƒe�[ƒvƒ‹‚Ì‚Ý‰Â”\ */
#define DI_OPT_EXT_FIN_EUPHRATES_SDL   (16)
#define DI_OPT_EXT_FIN_EUPHRATES_NON   (17)
#define DI_OPT_EXT_FIN_TIGRIS          (18)
#define DI_OPT_EXT_FIN_KANOGAWA        (19)
#define DI_OPT_EXT_FIN_ATLANTIC_A      (20)    /* ƒWƒƒƒoƒ‰‹@ */
#define DI_OPT_EXT_FIN_ATLANTIC_B      (21)    /* ƒtƒHƒ‹ƒ_�[‹@�iƒWƒƒƒoƒ‰‹@�{ƒNƒ�ƒXƒ†ƒjƒbƒg�j */
#define	DI_OPT_EXT_FIN_ELBE            (23)	/* ELBE */
#define	DI_OPT_EXT_FIN_SAKAWAGAWA	(24)
#define DI_OPT_EXT_FIN_COLUMBIA        (25)    /* COLUMBIA */
#define DI_OPT_EXT_FIN_SHINJIKO        (26)    /* COLUMBIA+SHINJIKO */
#define DI_OPT_EXT_FIN_EUPHRATES_1BIT  (27)    /* EUPHRATES-D(1 hole) */
#define DI_OPT_EXT_FIN_EUPHRATES_2BIT  (28)    /* EUPHRATES-D(2 holes) */
#define DI_OPT_EXT_FIN_RUBICON         (29)    /* RUBICON */
#define DI_OPT_EXT_FIN_AMUR_SDL        (30)    /* AMUR(saddle stitch) */
#define DI_OPT_EXT_FIN_AMUR_NON        (31)    /* AMUR */
#define DI_OPT_EXT_FIN_VOLGA_SDL       (32)    /* VOLGA(saddle stitch) */
#define DI_OPT_EXT_FIN_VOLGA_NON       (33)    /* VOLGA */
#define DI_OPT_EXT_FIN_COLUMBIA_SDL    (34)    /* COLUMBIA(saddle stitch) */
#define DI_OPT_EXT_FIN_UYUNI           (35)    /* UYUNI(�j–³‚µ’Ô‚¶) */
	unsigned long	fin;		/* ƒtƒBƒjƒbƒVƒƒŒnƒIƒvƒVƒ‡ƒ“‹@Šíƒtƒ‰ƒO */
#define DI_OPT_EXT_MB_9BIN             (1)             /* MB 9BIN */
#define DI_OPT_EXT_MB_9BIN_P           (2)             /* MB_P 9BIN+proof */
#define DI_OPT_EXT_MB_SAXBY            (3)             /* SAXBY */
#define DI_OPT_EXT_MB_POTOMAC          (4)             /* POTOMAC */
#define DI_OPT_EXT_MB_JACK             (5)             /* JACK */
#define DI_OPT_EXT_MB_ONTARIO          (6)             /* ONTARIO */
	unsigned long	mbox;		/* ƒ��[ƒ‹ƒ{ƒbƒNƒXŒnƒIƒvƒVƒ‡ƒ“‹@Šíƒtƒ‰ƒO */
#define DI_OPT_EXT_DEVELOPMENT_R       (1 << 31)       /* RED DEVELOPMENT */
#define DI_OPT_EXT_ZFOLD_UNIT          (1 << 30)       /* ZFOLD UNIT */
	unsigned long	misc;		/* �ã‹LˆÈŠO‚ÌƒIƒvƒVƒ‡ƒ“‹@Šíƒtƒ‰ƒO */
#define DI_OPT_EXT_CF_UNIT             (1 << 31)       /* CF UNIT */
#define DI_OPT_EXT_ADF                 (1 << 30)       /* ADF */
#define DI_OPT_EXT_GBC_PUNCH           (1 << 29)       /* GBCƒpƒ“ƒ`ƒ†ƒjƒbƒg */
#define DI_OPT_EXT_KARUN_SDL           (1 << 28)       /* ’†’Ô‚¶ƒ†ƒjƒbƒg(KARUN) */
	unsigned long	non_prt;	/* ƒvƒŠƒ“ƒ^‚ÉŠÖ˜A‚µ‚È‚¢ƒIƒvƒVƒ‡ƒ“‹@Šíƒtƒ‰ƒO */
} di_optinfo_t;

typedef struct di_ethertalk_info {
/* length */
#define	DI_MAX_ATINFO_OBJECT_NAME_LEN	32
#define	DI_MAX_ATINFO_TYPE_NAME_LEN		32
#define	DI_MAX_ATINFO_ZONE_NAME_LEN		32
#define	DI_MAX_ATINFO_MACADDR_LEN		6

#define	DI_ATINFO_FLAG_OBJECT_NAME		(1 << 0)
#define	DI_ATINFO_FLAG_TYPE_NAME		(1 << 1)
#define	DI_ATINFO_FLAG_ZONE_NAME		(1 << 2)
#define	DI_ATINFO_FLAG_MACADDR			(1 << 3)
	unsigned long		flag;								/* ƒtƒ‰ƒO */
	unsigned char		object_name[DI_MAX_ATINFO_OBJECT_NAME_LEN + 1];		/* NULLƒ^�[ƒ~ƒl�[ƒg (R/W) */
	unsigned char		type_name[DI_MAX_ATINFO_TYPE_NAME_LEN + 1];		/* NULLƒ^�[ƒ~ƒl�[ƒg (ReadOnly)*/
	unsigned char		zone_name[DI_MAX_ATINFO_ZONE_NAME_LEN + 1];		/* NULLƒ^�[ƒ~ƒl�[ƒg (R/W)*/
	unsigned char		macaddr[DI_MAX_ATINFO_MACADDR_LEN];			/* (ReadOnly) */
} di_ethertalk_info_t;

typedef struct di_ujob_info {

/*
 *	flag
 */
#define	DI_UPARAM_DATE					(1 << 0)
#define	DI_UPARAM_TIME					(1 << 1)
#define	DI_UPARAM_TRACKID				(1 << 2)
#define	DI_UPARAM_USERCODE				(1 << 3)
#define	DI_UPARAM_USERID				(1 << 4)
#define	DI_UPARAM_JOBID					(1 << 5)
#define	DI_UPARAM_JOBPASSWORD			(1 << 6)
#define	DI_UPARAM_DISPCHARSET			(1 << 7)
#define	DI_UPARAM_HOSTCHARSET			(1 << 8)
#define	DI_UPARAM_HOSTLOGINNAME			(1 << 9)
#define	DI_UPARAM_HOSTNAME				(1 << 10)
#define	DI_UPARAM_HOSTPORTNAME			(1 << 11)
#define	DI_UPARAM_HOSTPRINTERNAME		(1 << 12)
#define	DI_UPARAM_PROOFJOB				(1 << 13)
#define	DI_UPARAM_SECUREJOB				(1 << 14)
#define	DI_UPARAM_JOBNAME				(1 << 15)
#define	DI_UPARAM_OWNERID				(1 << 16)
#define	DI_UPARAM_PRINTINFO				(1 << 17)
#define	DI_UPARAM_AUTHUSERNAME			(1 << 18)
#define	DI_UPARAM_AUTHPASSWORD			(1 << 19)
#define	DI_UPARAM_AUTHENCRYPTMETHOD		(1 << 20)
#define	DI_UPARAM_AUTHENCRYPTSETTING	(1 << 21)
#define	DI_UPARAM_JOBPASSWORD_EXT		(1 << 22)
#define	DI_UPARAM_PAUSEDJOB			(1 << 23)
#define	DI_UPARAM_FORMJOB			(1 << 24)
#define	DI_UPARAM_AUTHUSERNAMECHARSET	(1 << 25)
#define	DI_UPARAM_AUTHPASSWORDCHARSET	(1 << 26)
#define	DI_UPARAM_NDISPCHARSET		(1 << 27)
#define	DI_UPARAM_NHOSTCHARSET		(1 << 28)
#define	DI_UPARAM_BILLINGCODE		(1 << 29)
#define	DI_UPARAM_PRINTAPPOINTEDTIME	(1 << 30)
#define	DI_UPARAM_EXT2					(1 << 31)
/*
 *	flag2
 */
#define	DI_UPARAM_DRIVERKINDINFO		(1 << 0)
#define	DI_UPARAM_FOLDERNUMBER			(1 << 1)
#define	DI_UPARAM_FOLDERPASSWORD		(1 << 2)
#define	DI_UPARAM_EXT3					(1 << 31)
/*
 *	max length
 */
#define	DI_MAX_UPARAM_DATE_LEN				10
#define	DI_MAX_UPARAM_TIME_LEN				8
#define	DI_MAX_UPARAM_TRACKID_LEN			20
#define	DI_MAX_UPARAM_USERCODE_LEN			8
#define	DI_MAX_UPARAM_USERID_LEN			8
#define	DI_MAX_UPARAM_JOBID_LEN				20
#define	DI_MAX_UPARAM_JOBPASSWORD_LEN		4
#define	DI_MAX_UPARAM_DISPCHARSET_LEN		63
#define	DI_MAX_UPARAM_HOSTCHARSET_LEN		63
#define	DI_MAX_UPARAM_HOSTLOGINNAME_LEN		20
#define	DI_MAX_UPARAM_HOSTNAME_LEN			63
#define	DI_MAX_UPARAM_HOSTPORTNAME_LEN		64
#define	DI_MAX_UPARAM_HOSTPRINTERNAME_LEN	64
#define	DI_MAX_UPARAM_JOBNAME_LEN			232
#define	DI_MAX_UPARAM_OWNERID_LEN			20
#define	DI_MAX_UPARAM_PRINTINFO_LEN			230
#define	DI_MAX_UPARAM_AUTHUSERNAME_LEN		217
#define	DI_MAX_UPARAM_AUTHPASSWORD_LEN		217
#define	DI_MAX_UPARAM_JOBPASSWORD_EXT_LEN	8
#define	DI_MAX_UPARAM_BILLINGCODE_LEN		32
#define	DI_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN	5
#define	DI_MAX_UPARAM_FOLDERPASSWORD_LEN	8
/*
 *	driver kind info
 */
#define	DI_UPARAM_DRIVERKINDINFO_INBOX			(1)
#define	DI_UPARAM_DRIVERKINDINFO_PCL6			(2)
#define	DI_UPARAM_DRIVERKINDINFO_PCL6UD			(3)
#define	DI_UPARAM_DRIVERKINDINFO_PCL6UDGENERIC	(4)
#define	DI_UPARAM_DRIVERKINDINFO_PS				(5)
#define	DI_UPARAM_DRIVERKINDINFO_PSUD			(6)
#define	DI_UPARAM_DRIVERKINDINFO_PSUDGENERIC	(7)
#define	DI_UPARAM_DRIVERKINDINFO_RPCSBASIC		(8)
#define	DI_UPARAM_DRIVERKINDINFO_RPCSXPS		(9)
#define	DI_UPARAM_DRIVERKINDINFO_RPCS			(10)


	unsigned long	flag;
	union {
		unsigned char	date[DI_MAX_UPARAM_DATE_LEN + 1];
		unsigned char	time[DI_MAX_UPARAM_TIME_LEN + 1];
		unsigned char	trackid[DI_MAX_UPARAM_TRACKID_LEN + 1];
		unsigned char	usercode[DI_MAX_UPARAM_USERCODE_LEN + 1];
		unsigned char	billingcode[DI_MAX_UPARAM_BILLINGCODE_LEN + 2];
		unsigned char	userid[DI_MAX_UPARAM_USERID_LEN + 1];
		unsigned char	jobid[DI_MAX_UPARAM_JOBID_LEN + 1];
		unsigned char	jobpassword[DI_MAX_UPARAM_JOBPASSWORD_LEN + 1];
		unsigned char	dispcharset[DI_MAX_UPARAM_DISPCHARSET_LEN + 1];
		unsigned char	hostcharset[DI_MAX_UPARAM_HOSTCHARSET_LEN + 1];
		unsigned char	hostloginname[DI_MAX_UPARAM_HOSTLOGINNAME_LEN + 1];
		unsigned char	hostname[DI_MAX_UPARAM_HOSTNAME_LEN + 1];
		unsigned char	hostportname[DI_MAX_UPARAM_HOSTPORTNAME_LEN + 1];
		unsigned char	hostprintername[DI_MAX_UPARAM_HOSTPRINTERNAME_LEN + 1];
		unsigned char	jobname[DI_MAX_UPARAM_JOBNAME_LEN + 1];
		unsigned char	ownerid[DI_MAX_UPARAM_OWNERID_LEN + 1];
		unsigned char	printinfo[DI_MAX_UPARAM_PRINTINFO_LEN + 1];
		unsigned char	authusername[DI_MAX_UPARAM_AUTHUSERNAME_LEN + 1];
		unsigned char	authpassword[DI_MAX_UPARAM_AUTHPASSWORD_LEN + 1];
		int		authencryptmethod;
		int		authencryptsetting;
		unsigned char	jobpassword_ext[DI_MAX_UPARAM_JOBPASSWORD_EXT_LEN + 1];
		short			authusernamecharset;
		short			authpasswordcharset;
		short			ndispcharset;
		short			nhostcharset;
		unsigned char	printappointedtime[DI_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN + 1];
		int				driverkindinfo;
		unsigned short	foldernumber;
		unsigned char	folderpassword[DI_MAX_UPARAM_FOLDERPASSWORD_LEN + 1];
		unsigned char	dummy[240];
	} up;
	unsigned long	flag2;
} di_ujob_info_t;


typedef struct di_status {

#define	DI_ST_CODE_MAX		32

	unsigned char		cur_interpreter;			/* “®�ì’†‚ÌƒCƒ“ƒ^ƒvƒŠƒ^ID */
	int					state;						/* state */
	int					st_code_num;				/* st_code[]‚Å—LŒø‚È�” */
	unsigned long		st_code[DI_ST_CODE_MAX];	/* status code list */
#define	DI_SYS_FUNC_DUPLEX			(1 << 0)		/* duplex */
#define	DI_SYS_FUNC_STAPLE			(1 << 1)		/* staple */
#define	DI_SYS_FUNC_PUNCH			(1 << 2)		/* punch */
#define	DI_SYS_FUNC_SORT			(1 << 3)		/* sorting */
#define	DI_SYS_FUNC_HDD_FS			(1 << 4)		/* HDD for FileSystem */
#define	DI_SYS_FUNC_SHIFT			(1 << 5)		/* shift */
#define	DI_SYS_FUNC_FINISHER		(1 << 6)		/* Finisher */
#define	DI_SYS_FUNC_MAILBOX			(1 << 7)		/* Mail Box */
#define	DI_SYS_FUNC_COLOR			(1 << 8)		/* Color (CMYK) */
#define	DI_SYS_FUNC_HDD				(1 << 9)		/* HDD */
#define	DI_SYS_FUNC_PROOFPRINT		(1 << 10)	/* proof print */
#define	DI_SYS_FUNC_SEQUREPRINT		(1 << 11)	/* sequre print */
#define	DI_SYS_FUNC_LOCALSTORAGE	(1 << 12)	/* local storage */
#define	DI_SYS_FUNC_NETWORK			(1 << 13)	/* network */
#define	DI_SYS_FUNC_REMOTEPRINT		(1 << 14)	/* remote print */
#define	DI_SYS_FUNC_IEEE1394		(1 << 15)	/* IEEE1394 */
#define	DI_SYS_FUNC_IEEE802_11b		(1 << 18)	/* IEEE802.11b */
#define	DI_SYS_FUNC_USB				(1 << 19)	/* USB */
#define	DI_SYS_FUNC_BLUETOOTH		(1 << 21)	/* Bluetooth */
	unsigned long		function_disable;	/* ‹@”\Žg—p•s‰Â(SC) */
#define	DI_STATE_OFFLINE			(1 << 0)		/* ST_OFFLINE */
#define	DI_STATE_HEXDUMP			(1 << 1)		/* ST_HEXDUMP */
#define	DI_STATE_WARMING_UP			(1 << 2)		/* ST_WARMING_UP */
#define	DI_STATE_ENERGY_SAVE		(1 << 3)		/* ST_ENERGY_SAVE */
#define	DI_STATE_PRINTING			(1 << 4)		/* ST_PROCESSIG (ˆó�ü’†) */
#define	DI_STATE_PROCESSING			(1 << 5)		/* ST_PROCESSING�iƒf�[ƒ^�ˆ—�’†�j */
#define	DI_STATE_PREHEAT			(1 << 6)		/* ST_PREHEAT */
#define	DI_STATE_WAITING			(1 << 7)		/* ST_WAITING */
#define	DI_STATE_JOB_RESETTING		(1 << 8)		/* ST_JOB_RESETTING */
#define	DI_STATE_INT_REQ			(1 << 9)		/* Š„�ž‚ÝƒRƒs�[�iˆó�ü’âŽ~�j—v‹� */
#define	DI_STATE_INT_PAUSE			(1 << 10)	/* Š„�ž‚ÝƒRƒs�[’† */
#define	DI_STATE_CALIBRATING		(1 << 11)	/* calibrating */ 
#define	DI_STATE_SUPPLYING_TONER	(1 << 12)	/* supplying toner */
#define	DI_STATE_INIT_DEVELOPER		(1 << 13)	/* initial developer */
#define	DI_STATE_COOLING_DOWN		(1 << 14)	/* cooling down */
#define	DI_STATE_CARDSAVE			(1 << 31)	/* ƒJ�[ƒhƒZ�[ƒu */
	unsigned long		state_detail;		/* �ó‘Ô‚Ì�Ú�×‚ðƒrƒbƒg‚Å‚ ‚ç‚í‚· */
	/* st_code[]‚ÌŒx��ˆµ‚¢‚ÌƒGƒ‰�[ƒR�[ƒh‚Ì�” */
	int			st_code_num_warning;
	/* st_code[]‚ÌƒIƒyƒŒ�[ƒ^ƒR�[ƒ‹ˆµ‚¢‚ÌƒGƒ‰�[ƒR�[ƒh‚Ì�” */
	int			st_code_num_error;
} di_status_t;


typedef struct di_diskinfo {

#define DI_MAX_HDD_PATH_LEN 64

	char	stat;						/* status              */
	char	path[DI_MAX_HDD_PATH_LEN];	/* path                */
	long	f_bsize;					/* block size (bytes)  */
	long	f_blocks;					/* total blocks        */
	long	f_bfree;					/* free blocks         */
	long	reserve;					/* reserve             */
} di_diskinfo_t;

typedef struct di_res_reqpaper{
	unsigned short	type;		/* GWID_GpsPage_TrayRequest_Res */
	unsigned short	length;
	int				pid;
	int				result;		/* Œ‹‰Ê */
#define	DI_TRAY_FOUND	(0)		/* �ðŒ�‚É�‡‚¤ƒgƒŒƒC‚ª�oŒ»‚µ‚½ */
#define	DI_TRAY_ERRSKIP	(1)		/* ƒGƒ‰�[ƒXƒLƒbƒv‚µ‚Ä‚­‚¾‚³‚¢ */
#define	DI_TRAY_CANCEL	(2)		/* ƒLƒƒƒ“ƒZƒ‹‚ªŽwŽ¦‚³‚ê‚½ */
#define	DI_TRAY_FORCE	(3)		/* ‹­�§ˆó�ü‚ªŽwŽ¦‚³‚ê‚½ */
#define	DI_TRAY_ANOTHER	(4)		/* —pŽ†ƒTƒCƒY‚ª—ÞŽ—‚µ‚½ƒgƒŒƒC‘¶�Ý */
	int			tray_id;		/* ƒgƒŒƒCID */
	int			paper_code;		/* —pŽ†ƒTƒCƒYƒR�[ƒh */
	int			paper_width;	/* —pŽ†•�   (0.1mm’PˆÊ) */
	int			paper_length;	/* —pŽ†�‚‚³ (0.1mm’PˆÊ) */
} di_res_reqpaper_t;

typedef struct di_envinfo {
	long           id; /* variable ID */
#define DI_PENV_VARFLAG_READONLY (1 << 0) /* PJL READ ONLY */
	unsigned long  flag; /* variable flag */
	long           init_val; /* initial value */
	long           def_val; /* default value */
	long           cur_val; /* current value */
	unsigned char  val_denom; /* value denominaator (use if type is FLOAT) */
#define DI_PENV_VALTYPE_ENUM    0 /* ENUMERATE */
#define DI_PENV_VALTYPE_INT     1 /* INTEGER(range) */
#define DI_PENV_VALTYPE_FLOAT   2 /* FLOAT(range) */
#define DI_PENV_VALTYPE_NETADDR 3 /* Network address */
	unsigned char  val_type; /* value type */
	long           val_num; /* number of value list */
} di_envinfo_t;

typedef struct di_flashmem_info {
#define DI_FLASHMEM_ATTR_RW (1 << 0) /* Read/Write‰Â”\ */
	unsigned long attr;          /* attribute */
#define DI_FLASHMEM_MEDIA_UNKNOWN 0 /* •s–¾ */
#define DI_FLASHMEM_MEDIA_ROM     1 /* ROM DIMM / SD Card */
	unsigned long media;         /* kind of media */
#define DI_MAX_FM_PATH_LEN 64
	char path[DI_MAX_FM_PATH_LEN];  /* directory path */
} di_flashmem_info_t;


typedef  struct {
	unsigned short idPanel;   /* ƒAƒCƒeƒ€Ž©�g‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idDown;    /* ‰ºŠK‘w‚Ìƒpƒlƒ‹‚h‚c */
	/* ƒgƒ‰ƒbƒv—pŠÖ�”ƒ|ƒCƒ“ƒ^ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
#define   FILENAME_LEN         14
	unsigned char  filename[FILENAME_LEN];   /* ƒtƒ@ƒCƒ‹ƒl�[ƒ€ */
	unsigned char  panel_lock_stat; /* ƒpƒlƒ‹ƒ�ƒbƒN�ó‘Ô�î•ñ */
	unsigned char  ucReserved[3];   /* –¢Žg—p */
	unsigned char  reserve_cid[4];  /* ƒNƒ‰ƒCƒAƒ“ƒg‚h‚c—p—\–ñ—Ìˆæ */
	unsigned char  ucItem;          /* ƒAƒCƒeƒ€ƒ^ƒCƒv  */
	unsigned char  ucMenu;          /* ƒ�ƒjƒ…�[ƒ^ƒCƒv  */
} di_menu_type_t;


typedef  struct {
	unsigned short idPanel;    /* ƒAƒCƒeƒ€Ž©�g‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idNext;     /* “¯ŠK‘w‚ÌŽŸ‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idPrev;     /* “¯ŠK‘w‚Ì‘O‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idDown;     /* ‰ºŠK‘w‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idBack;     /* ŒÄ�o‚µŒ³ �ãˆÊŠK‘w‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short str1_id;    /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ‚h‚c */
	unsigned short str1_mod;   /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ�C�ü�î•ñ */
	unsigned short str2_id;    /* �€–Ú•”�i‚Q�s–Ú�j‚Ì•¶Žš—ñ‚h‚c */
    /* ƒgƒ‰ƒbƒv—pŠÖ�”ƒ|ƒCƒ“ƒ^ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  disp_flg;   /* •\Ž¦�^”¼‹P“x�^”ñ•\Ž¦‚Ìƒtƒ‰ƒO */
        unsigned char  ucReserved[5];   /* –¢Žg—p */
        unsigned char  reserve_cid[4];  /* ƒNƒ‰ƒCƒAƒ“ƒg‚h‚c•Û‘¶—p—\–ñ—Ìˆæ */
        unsigned char  ucItem;          /* ƒAƒCƒeƒ€ƒ^ƒCƒv */
        unsigned char  ucMenu;          /* ƒ�ƒjƒ…�[ƒ^ƒCƒv */
} di_item_type_menu_t;

typedef  struct {
	unsigned short idPanel;  /* ƒAƒCƒeƒ€Ž©�g‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idNext;   /* “¯ŠK‘w‚ÌŽŸ‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idPrev;   /* “¯ŠK‘w‚Ì‘O‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idDown;   /* ‰ºŠK‘w‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idBack;   /* ŒÄ�o‚µŒ³ �ãˆÊŠK‘w‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short str1_id;  /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ‚h‚c */
	unsigned short str1_mod; /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ�C�ü�î•ñ */
	unsigned short str2_id;  /* �€–Ú•”�i‚Q�s–Ú�j‚Ì•¶Žš—ñ‚h‚c */
	/* ƒgƒ‰ƒbƒv—pŠÖ�”ƒ|ƒCƒ“ƒ^ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned char  up_num;   /* ŽÀ�sŒã‚É‘JˆÚ‚·‚é�ã‚Ö‚ÌŠK‘w�” */
	unsigned char  disp_flg; /* •\Ž¦�^”¼‹P“x�^”ñ•\Ž¦‚Ìƒtƒ‰ƒO */
	unsigned char  fselect;  /* ‘I‘ð�^”ñ‘I‘ð‚Ìƒtƒ‰ƒO */
	unsigned char  disp_fselect; /* ‘I‘ðƒtƒ‰ƒO‚Ì•\Ž¦�^”ñ•\Ž¦‚Ìƒtƒ‰ƒO */
	unsigned char  ucReserved[2]; /* –¢Žg—p */
	unsigned char  reserve_cid[4]; /* ƒNƒ‰ƒCƒAƒ“ƒg‚h‚c•Û‘¶—p—\–ñ—Ìˆæ */
	unsigned char  ucItem;         /* ƒAƒCƒeƒ€ƒ^ƒCƒv */
	unsigned char  ucMenu;         /* ƒ�ƒjƒ…�[ƒ^ƒCƒv */
} di_item_type_select_t;

typedef  struct {
	unsigned short idPanel;  /* ƒAƒCƒeƒ€Ž©�g‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short idBack;   /* ŒÄ�o‚µŒ³ �ãˆÊŠK‘w‚Ìƒpƒlƒ‹‚h‚c */
	unsigned short str1_id;  /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ‚h‚c */
	unsigned short str1_mod; /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ�C�ü�î•ñ */
	short          sMax;     /* �Å‘å’l */
	short          sMin;     /* �Å�¬’l */
	unsigned short step;     /* •Ï‰»•� */
	short          value;    /* �Ý’è’l */
	/* ƒgƒ‰ƒbƒv—pŠÖ�”ƒ|ƒCƒ“ƒ^ */
	void (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;         /* ’PˆÊ•¶Žš—ñ‚h‚c */
	unsigned char  up_num;         /* ŽÀ�sŒã‚É‘JˆÚ‚·‚é�ã‚Ö‚ÌŠK‘w�” */
	unsigned char  fig_num;        /* •\Ž¦Œ…�” */
	unsigned char  ucReserved[2];  /* –¢Žg—p */
	unsigned char  reserve_cid[4]; /* ƒNƒ‰ƒCƒAƒ“ƒg‚h‚c•Û‘¶—p—\–ñ—Ìˆæ */
	unsigned char  ucItem;         /* ƒAƒCƒeƒ€ƒ^ƒCƒv */
	unsigned char  ucMenu;         /* ƒ�ƒjƒ…�[ƒ^ƒCƒv */
} di_item_type_integer_t;

typedef  struct {
	unsigned short idPanel;    /* ƒAƒCƒeƒ€Ž©�g‚Ìƒpƒlƒ‹‚h‚c             */
	unsigned short idBack;     /* ŒÄ�o‚µŒ³ �ãˆÊŠK‘w‚Ìƒpƒlƒ‹‚h‚c        */
	unsigned short str1_id;    /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ‚h‚c     */
	unsigned short str1_mod;   /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ�C�ü�î•ñ */
	short          sMax;       /* �Å‘å’l                               */
	short          sMin;       /* �Å�¬’l                               */
	unsigned short step;       /* •Ï‰»•�                               */
	short          value;      /* �Ý’è’l                               */
	/* ƒgƒ‰ƒbƒv—pŠÖ�”ƒ|ƒCƒ“ƒ^               */
	void           (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;     /* ’PˆÊ•¶Žš—ñ‚h‚c                       */
	unsigned char  up_num;     /* ŽÀ�sŒã‚É‘JˆÚ‚·‚é�ã‚Ö‚ÌŠK‘w�”         */
	unsigned char  fig_num;    /* •\Ž¦Œ…�”                             */
	unsigned char  ucMulti;    /* Žw�”’l                               */
	unsigned char  ucReserved; /* –¢Žg—p                               */
	unsigned char  reserve_cid[4]; /* ƒNƒ‰ƒCƒAƒ“ƒg‚h‚c•Û‘¶—p—\–ñ—Ìˆæ       */
	unsigned char  ucItem;     /* ƒAƒCƒeƒ€ƒ^ƒCƒv                       */
	unsigned char  ucMenu;     /* ƒ�ƒjƒ…�[ƒ^ƒCƒv                       */
} di_item_type_float_t;

typedef  struct {
	unsigned short idPanel; /* ƒAƒCƒeƒ€Ž©�g‚Ìƒpƒlƒ‹‚h‚c             */
	unsigned short idBack;  /* ŒÄ�o‚µŒ³ �ãˆÊŠK‘w‚Ìƒpƒlƒ‹‚h‚c        */
	unsigned short str1_id; /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ‚h‚c     */
	short          sMin;    /* �Å�¬’l                               */
	int            sMax;    /* �Å‘å’l                               */
	int            value;   /* �Ý’è’l                               */
	/* ƒgƒ‰ƒbƒv—pŠÖ�”ƒ|ƒCƒ“ƒ^               */
	void           (*fchecker)(unsigned short, unsigned char, unsigned char);
	unsigned short msr_id;  /* ’PˆÊ•¶Žš—ñ‚h‚c                       */
	unsigned char  str1_mod; /* ƒ^ƒCƒgƒ‹•”�i‚P�s–Ú�j‚Ì•¶Žš—ñ�C�ü�î•ñ */
	unsigned char  step;     /* •Ï‰»•�                               */
	unsigned char  fig_num;  /* •\Ž¦Œ…�”                             */
	unsigned char  ucMulti;  /* Žw�”’l                               */
	unsigned char  reserve_cid[4]; /* ƒNƒ‰ƒCƒAƒ“ƒg‚h‚c•Û‘¶—p—\–ñ—Ìˆæ       */
	unsigned char  ucItem;   /* ƒAƒCƒeƒ€ƒ^ƒCƒv                       */
	unsigned char  ucMenu;   /* ƒ�ƒjƒ…�[ƒ^ƒCƒv                       */
} di_item_type_floatext_t;

typedef  struct di_fontinfo {
	unsigned char *addr;  /* ƒAƒhƒŒƒX */
	unsigned long size;   /* ƒTƒCƒY */
	unsigned long offset; /* ƒIƒtƒZƒbƒg */
} di_fontinfo_t;

typedef  struct di_pdlinfo {
#define DI_INTERP_LEN_SHORTNAME 3
#define DI_MINFO_KEY_PDL_CATEGORY_LEN 7
	int interp_id; /* ƒCƒ“ƒ^ƒvƒŠƒ^ID */
	/* ƒVƒ‡�[ƒgƒl�[ƒ€(’è‹`‚³‚ê‚Ä‚¢‚È‚¢�ê�‡‚ÍNULL) */
	char shortname[DI_INTERP_LEN_SHORTNAME + 1];
	char path; /* printer.ini path ID  */
	/* printer.ini ƒtƒ@ƒCƒ‹‚ÌƒJƒeƒSƒŠ–¼ */
	char category[DI_MINFO_KEY_PDL_CATEGORY_LEN + 1];
} di_pdlinfo_t;

/**
 * �»•i�î•ñ�\‘¢‘Ì
 */
typedef struct di_initinfo {
#define	DI_MACHINECODE_ADONIS_C2		0x00
#define	DI_MACHINECODE_KIR_P			0x10
#define	DI_MACHINECODE_KIR_P2			0x13
#define	DI_MACHINECODE_KIR_P3			0x15
#define	DI_MACHINECODE_JUPITER_P		0x20
#define	DI_MACHINECODE_URANOS_P			0x30
#define	DI_MACHINECODE_RUSSIAN_C2		0x40
#define DI_MACHINECODE_ADONIS_P3		0x50
#define DI_MACHINECODE_URANOS_C			0x60
#define DI_MACHINECODE_ARES_P			0x70
#define DI_MACHINECODE_KAISER3			0x80
#define DI_MACHINECODE_JUPITER_P2		0x90
#define DI_MACHINECODE_JUPITER_P2Y		0x93		/* –ò‘Ü */
#define DI_MACHINECODE_JUPITER_P2M		0xa0
#define DI_MACHINECODE_JUPITER_P2K		0xb0
#define	DI_MACHINECODE_URANOS_P2		0xc0
#define DI_MACHINECODE_JUPITER_C0		0xe0
#define	DI_MACHINECODE_CASSIS_P1_DOM	0xf0		/* DOM */

#define	DI_MACHINECODE_MARTINI_C1		0x00080000
#define	DI_MACHINECODE_BELLINI_C2		0x00090000
#define	DI_MACHINECODE_ADONIS_C3		0x000A0000
#define	DI_MACHINECODE_RUSSIAN_C3		0x000B0000
#define	DI_MACHINECODE_SEADRAGON_C1		0x000C0000
#define	DI_MACHINECODE_JUPITER_C1		0x000D0000
#define	DI_MACHINECODE_KIR_P3_EXP		0x00010000	/* EXP */
#define	DI_MACHINECODE_KIR_C2			0x00120000
#define	DI_MACHINECODE_CASSIS_P1_EXP	0x00130000	/* EXP */
#define	DI_MACHINECODE_PLUTO_P1			0x00140000
#define DI_MACHINECODE_VENUS_C1			0x00150000
#define DI_MACHINECODE_URANOS_C2		0x00160000
#define	DI_MACHINECODE_JUPITER_P3		0x00170000
#define DI_MACHINECODE_GAIA_P1			0x00180000
#define DI_MACHINECODE_MARTINI_C2		0x00190000
#define DI_MACHINECODE_STELLA_C2		0x001A0000
#define DI_MACHINECODE_DOLPHIN_C2		0x001B0000	/* DOLPHIN-C2 group */
#define DI_MACHINECODE_JUPITER_C2		0x001C0000	/* JUPITER_C2 group */
#define	DI_MACHINECODE_CASSIS_P2		0x001D0000	/* CASSIS-P2 group */
#define	DI_MACHINECODE_MARTINI_P1		0x001E0000	/* MARTINI-P1 group */
#define	DI_MACHINECODE_ADONIS_C4		0x001F0000	/* ADONIS-C4 group */
#define	DI_MACHINECODE_RUSSIAN_C4		0x00200000	/* RUSSIAN-C4 group */
#define	DI_MACHINECODE_KIR_P4			0x00210000	/* KIR-P4 group */
#define	DI_MACHINECODE_JUPITER_P4		0x00220000	/* JUPITER-P4 group */
#define DI_MACHINECODE_PEGASUS_C1		0x00230000	/* PegasusC1 group */
#define DI_MACHINECODE_APOLLON_C1		0x00240000	/* ApollonC1 group */
#define DI_MACHINECODE_ATHENA_C1		0x00250000	/* AthenaC1 group */
#define DI_MACHINECODE_BELLINI_C3		0x00260000	/* BELLINI-C3 group */
#define DI_MACHINECODE_MARTINI_C3		0x00270000	/* MARTINI-C3 group */
#define DI_MACHINECODE_ARES_P2			0x00280000	/* ARES-P2 group */
#define DI_MACHINECODE_GAIA_P2			0x00290000	/* Gaia-P2 group */
#define DI_MACHINECODE_APOLLON_P1		0x002A0000	/* Apollon-P1 group */
#define DI_MACHINECODE_ADONIS_P4		0x002B0000	/* Adonis-P4 group */
#define	DI_MACHINECODE_MARTINI_P2		0x002C0000	/* MARTINI-P2 group */
#define	DI_MACHINECODE_KIR_C3			0x002D0000	/* KIR-C3 group */
#define	DI_MACHINECODE_NEPTUNE_C2		0x002E0000	/* NEPTUNE-C2 group */
#define	DI_MACHINECODE_SEADRAGON_C2		0x002F0000	/* SEADRAGON_C2 group */
#define	DI_MACHINECODE_ADONIS_C4_5		0x00300000	/* ADONIS-C4.5 group */
#define	DI_MACHINECODE_RUSSIAN_C4_5		0x00310000	/* RUSSIAN-C4.5 group */
#define DI_MACHINECODE_STELLA_C3		0x00320000	/* STELLA-C3 group */
#define DI_MACHINECODE_KRISS_P1			0x00330000	/* Kriss-P1 group */
#define DI_MACHINECODE_LUNA_P1			0x00340000	/* Luna-P1 group */
#define DI_MACHINECODE_SINCERE_P1		0x00350000	/* Sincere-P1 group */
#define DI_MACHINECODE_PARISIAN_C1		0x00360000	/* Parisian-C1 group */
#define DI_MACHINECODE_VENUS_C2			0x00370000	/* Venus-C2 group */
#define DI_MACHINECODE_ALEX_C1			0x003A0000	/* Alex-C1 group */
#define DI_MACHINECODE_RUSSIAN_C5		0x003B0000	/* Russian-C5 group */
#define DI_MACHINECODE_NEPTUNE_P1		0x003C0000	/* Neptune-P1 group */
#define DI_MACHINECODE_ATHENA_C2		0x003D0000	/* Athena-C2 group */
#define DI_MACHINECODE_ALEX_P1			0x003E0000	/* Alex-P1 group */
#define DI_MACHINECODE_APOLLON_C2		0x003F0000	/* Apollon-C2 group */
#define DI_MACHINECODE_PEGASUS_C2		0x00400000	/* Pegasus-C2 group */
#define DI_MACHINECODE_BELUGA_C1		0x00410000	/* Beluga-C1 group */
#define DI_MACHINECODE_DIANA_C1			0x00420000	/* Diana-C1 group */
#define DI_MACHINECODE_GAIA_P3			0x00430000	/* Gaia-P3 group */
#define DI_MACHINECODE_APOLLON_P2		0x00440000	/* Apollon-P2 group */
#define DI_MACHINECODE_SINCERE_P2		0x00450000	/* Sincere-P2 group */
#define DI_MACHINECODE_BELLINI_C4		0x00460000	/* Bellini-C4 group */
#define DI_MACHINECODE_MARTINI_C4		0x00470000	/* Martini-C4 group */
#define DI_MACHINECODE_LUNA_P2			0x00480000	/* Luna-P2 group */
#define DI_MACHINECODE_DIANA_C1L		0x00490000	/* Diana-C1L group */
	/**
	 * \brief ‹@ŽíƒR�[ƒh
	 * ’l‚ÍˆÈ‰º
	 * \li DI_MACHINECODE_ADONIS_C2
	 */
	unsigned long	machinecode;	/**< ‹@ŽíƒR�[ƒh */
	unsigned char	*model;			/* ƒ‚ƒfƒ‹–¼�B"IPSiO CX8200"“™ */
	unsigned char	*maker;			/* ƒ��[ƒJ�[ */
	unsigned char	*machine_number;/* ‹@”Ô */
	di_optinfo_t	option;			/* ƒIƒvƒVƒ‡ƒ“‹@Ší */
	unsigned long	function;		/* ‹@”\�î•ñ(DI_SYS_FUNC_xx) */
	unsigned char	disp_lines;		/* •\Ž¦‰æ–Ê‚Ìƒ‰ƒCƒ“�” */
	unsigned char	disp_columns;	/* •\Ž¦‰æ–Ê‚Ì‚Pƒ‰ƒCƒ“‚Ì•¶Žš�” */
	unsigned char	punch_hole;		/* ƒpƒ“ƒ`‰Â”\‚ÈŒŠ‚Ì�î•ñ(DI_SYS_PUNCH_HOLE_xx) */
	unsigned long	total_ram_size;	/* ƒvƒŠƒ“ƒ^‚É“‹�Ú‚³‚ê‚Ä‚¢‚éRAM—e—Ê(Byte) */
#define DI_DEST_DOM		0	/* DOM */
#define DI_DEST_NA		1	/* NA */
#define DI_DEST_EU		2	/* EU */
	unsigned char	destination;	/* ŽdŒü‚¯’nƒR�[ƒh(‚·‚®�ã‚Ìdefine) */
	unsigned long	memory_size;	/* ƒCƒ“ƒ^ƒvƒŠƒ^‚ªŽg—p‚Å‚«‚é */
					/* ƒ�ƒ‚ƒŠƒTƒCƒY(Byte) */
	unsigned char	*ver_printer;			/* ƒvƒŠƒ“ƒ^‚Ìƒo�[ƒWƒ‡ƒ“ */
} di_initinfo_t;

/* BG/UCRƒe�[ƒuƒ‹�î•ñ�\‘¢‘Ì */
typedef struct di_bgucrinfo {
	unsigned char	*bg;	/* BGƒe�[ƒuƒ‹ */
	unsigned char	*ucr;	/* UCRƒe�[ƒuƒ‹ */
	unsigned char	*bg_hgr;	/* BGƒe�[ƒuƒ‹(�‚–n—p) */
	unsigned char	*ucr_hgr;	/* UCRƒe�[ƒuƒ‹(�‚–n—p) */
	unsigned char	*bg_compbk;	/* for composite black */
	unsigned char	*ucr_compbk;
} di_bgucrinfo_t;

/* ‰ð‘œ“x�\‘¢‘Ì(ƒrƒbƒg‚Æ‚Ì‘g�‡‚¹) */
typedef struct di_resolution_info
{
	unsigned int x;		/* Žå‘–�¸•ûŒü‰ð‘œ“x */
	unsigned int y;		/* •›‘–�¸•ûŒü‰ð‘œ“x */
	unsigned char bit;	/* ƒrƒbƒg�” */

	unsigned char pkgroup;      /* Ž†ŽíƒOƒ‹�[ƒv */
	unsigned char dit_mode;     /* ƒfƒBƒUƒ‚�[ƒh */
	unsigned char prtmode;       /* ˆó�üƒ‚�[ƒh(�‚‘¬/•W�€/�‚�¸�×) */

} di_resolution_info_t;

/* ‘�—Ê‹K�§’l�î•ñ�\‘¢‘Ì */
typedef struct di_tlimit_info
{
	di_resolution_info_t reso;	/* ‰ð‘œ“x&�[‚³ */
	int text;	/* •¶ŽšƒIƒuƒWƒFƒNƒg */
	int line;	/* �ü‰æƒIƒuƒWƒFƒNƒg */
	int phot;	/* ŽÊ�^ƒIƒuƒWƒFƒNƒg */
	int fill;	/* “h‚è‚Â‚Ô‚µƒIƒuƒWƒFƒNƒg */
} di_tlimit_info_t;


/* structure of information of GCR table */
typedef struct di_gcrinfo {
	unsigned long	flag;
	short			*CB_bg;
	short			*CB_ucr;
	short			*CG_bg;
	short			*CG_ucr;
	short			*YG_bg;
	short			*YG_ucr;
	short			*MB_bg;
	short			*MB_ucr;
	short			*MR_bg;
	short			*MR_ucr;
	short			*YR_bg;
	short			*YR_ucr;
} di_gcrinfo_t;

/* “K—Êƒe�[ƒuƒ‹�î•ñ�\‘¢‘Ì */
typedef struct di_dropinfo {
	unsigned char	*lit;	/* “K—Êƒf�[ƒ^ */
	unsigned char	*inv;	/* ‹t•ÏŠ·ƒe�[ƒuƒ‹ */
} di_dropinfo_t;

/* —¼–ÊƒÁŠ„�‡�î•ñ�\‘¢‘Ì */
typedef struct di_dupgaminfo {
	unsigned char	*gam_front;	/* •\–ÊŠ„�‡[ŽÊ�^,•¶Žš,“h‚è,�ü‰æ] */
	unsigned char	*gam_back;	/* — –ÊŠ„�‡[ŽÊ�^,•¶Žš,“h‚è,�ü‰æ] */
} di_dupgaminfo_t;


/* ‹@Ží�î•ñ�\‘¢‘Ì */
typedef struct di_devinfo {
	/*
	 * ƒfƒBƒU�î•ñ
	 * ŽÀ�Û‚Ì�”‚Í
	 *  ƒTƒ|�[ƒgƒrƒbƒg�” x ‰ð‘œ“xŽí—Þ�” x ƒfƒBƒUŽí—Þ�” x ƒTƒ|�[ƒg�Å‘åƒvƒŒ�[ƒ“�”
	 * ‚Æ‚È‚é�BŠe’l‚Í‹@Ží”\—Í�î•ñ�B
	 * ”z’u�‡‚Í
	 *  for ƒrƒbƒg�”(’l �¬ -> ‘å)
	 *    for ‰ð‘œ“x�”(Žå‘–�¸+•›‘–�¸ �¬ -> ‘å)
	 *      for ƒfƒBƒU�”(photo -> text -> cad -> graphics)
	 *        for ƒvƒŒ�[ƒ“�”(K -> C -> M -> Y)
	 *          dither_info
	 * ‚Æ‚È‚é
	 */
	di_ditinfo_t	*dither_info;
	di_ditinfo_t	*dither_info_mono;

	/*
	 * ƒKƒ“ƒ}�î•ñ
	 * �”,”z’u�‡‚Í dither_info ‚Æ“¯—l
	 */
	unsigned char	**gamma_info;
	unsigned char	**gamma_info_mono;

	/*
	 * ƒfƒoƒCƒXƒtƒHƒ“ƒg�î•ñ
	 */
	/*
	 * ƒtƒHƒ“ƒg‚Ì�æ“ªƒAƒhƒŒƒX
	 */
	unsigned char	*font_address;
	/*
	 * ƒtƒHƒ“ƒgƒTƒCƒY
	 */
	unsigned long	font_size;
	/* ƒtƒHƒ“ƒgŽí—Þ */
#define DI_FONT_RPCS		0	/* RPCS DOM—p */
#define DI_FONT_RPCS_EXP	1	/* RPCS EXP—p */
#define DI_FONT_PS			2	/* PS ‰¢•¶ */
#define DI_FONT_PSDOM		3	/* PS “ú–{Œê */
#define DI_FONT_PCL			4	/* PCL—p */
	unsigned char	font_type;

	/*
	 * CMM‚ÅŽg—p‚·‚éƒvƒ�ƒtƒ@ƒCƒ‹�î•ñ
	 */
	void	*profaddress;
	long	profnumber;

	/*
	 * ‹@Ží”\—Í�î•ñ
	 */
	unsigned int		resonum;	/* ƒTƒ|�[ƒg‰ð‘œ“x&ƒrƒbƒg‘g‚Ý�‡‚í‚¹Ží—Þ�” */
	di_resolutioninfo_t	*reso_set;	/* ‰ð‘œ“x&ƒrƒbƒg‘g�‡‚¹ */
						/* reso•ª‚ ‚é(=reso_set[resonum]) */
	int		ndit;		/* ƒfƒBƒUŽí—Þ�” */
	int		nplane;		/* ƒTƒ|�[ƒg�Å‘åƒvƒŒ�[ƒ“�” */
	float	bg_startp;	/* BG ‚ªŽn‚Ü‚éŠJŽnƒŒƒxƒ‹ */
	float	bg_slant;	/* BG ’¼�üŒù”z */
	float	ucr_startp;	/* UCR ‚ªŽn‚Ü‚éŠJŽnƒŒƒxƒ‹ */
	float	ucr_slant;	/* UCR ’¼�üŒù”z */
	int		soft_tsave;	/* ƒ\ƒtƒgƒgƒi�[ƒZ�[ƒu‚ÌƒTƒ|�[ƒg */
				/* [1:‚ ‚è, 0:‚È‚µ] */
	float	tsave_ratio;	/* ƒ\ƒtƒgƒgƒi�[ƒZ�[ƒuŠ„�‡(0.0 - 1.0) */
	int		extend_soft_tsave;	/* Šg’£ƒ\ƒtƒgƒgƒi�[ƒZ�[ƒu‚Ì‘Î‰ž */
					/* [1:‚ ‚è, 0:‚È‚µ] */
	int		toner_limit;	/* ‘�—Ê‹K�§‚ÌƒTƒ|�[ƒg */
				/* [1:‚ ‚è, 0:‚È‚µ] */
	unsigned int	tlimit_num;	/* ‹@Ží‚ªƒTƒ|�[ƒg‚µ‚Ä‚¢‚é‘�—Ê‹K�§’l‚ÌŽí—Þ�” */
	di_tlimitinfo_t	*tlimit_val;/* ‘�—Ê‹K�§’l‚ÌƒoƒŠƒG�[ƒVƒ‡ƒ“ */
				/* tlimit_num ŒÂ‚ ‚é */
				/* ˆê”Ô�Å�‰‚ªƒfƒtƒHƒ‹ƒg’l */
				/* ‚»‚êˆÈŠO‚Í“ÁŽêƒ‚�[ƒh‚Ì’l */
				/* ƒTƒ|�[ƒg‚µ‚Ä‚¢‚È‚¯‚ê‚ÎNULL */

	/*
	 * ƒVƒXƒeƒ€�î•ñ
	 */
	char	*shdm_addr;	/* ƒVƒFƒA�[ƒhƒ�ƒ‚ƒŠ‚Ì�æ“ªƒAƒhƒŒƒX */
	long	sys_handle;	/* ƒVƒXƒeƒ€ƒnƒ“ƒhƒ‹ */

	/*
	 * Šg’£�î•ñ
	 */
#define DI_NOTSUPPORT_EXT_DEVINFO_PARAM	0 /* ‚±‚êˆÈ�~‚Ìƒ�ƒ“ƒo‚ª–³Œø */
#define DI_SUPPORT_EXT_DEVINFO_PARAM	1 /* ‚±‚êˆÈ�~‚Ìƒ�ƒ“ƒo‚ª—LŒø */
	unsigned long	flag;		/* ŠeŽíƒtƒ‰ƒO */
				/* 1bit–Ú -- Šg’£�î•ñ‚Ì—LŒø/–³Œø */

	di_bgucrinfo_t	**bgucr_info;	/* BG/UCR(ƒe�[ƒuƒ‹) */

	di_gcrinfo_t	*gcr_info;	/* WiShGCR */

	di_gcrinfo_t	*gcrhgr_info;	/* WiShGCR(�‚–n—p) */

	di_dropinfo_t	**drop_info;	/* “K—Êƒe�[ƒuƒ‹ */

	di_dupgaminfo_t	**dupgam_info;	/* —¼–ÊƒÁŠ„�‡ */

	int	support_drop;	/* “K—Ê‚ÌƒTƒ|�[ƒg */
				/* [1:‚ ‚è, 0:‚È‚µ] */
	int		cmy_media_num;	/* CMYˆó�ü‚ð‚·‚éŽ†Ží‚Ì�” */
	unsigned char	*cmy_media;	/* CMYˆó�ü‚ð‚·‚éŽ†Ží‚Ì”z—ñ */
	int		minbandheight;
	int		maxbandheight;
	int		bandsize;
} dev_info_t, di_devinfo_t;

/*
 * ˆÈ�~‚Ídi_init()‚Åƒ†�[ƒU‚ªDI‚É“n‚·ƒpƒ‰ƒ��[ƒ^
 */

/* ”ñ“¯Šú‚ÉDI“à•”‚Å�X�V‚³‚ê‚éƒpƒ‰ƒ��[ƒ^ */
typedef struct di_async_para {
	/*
	 * ƒWƒ‡ƒuƒŠƒZƒbƒg�î•ñ
	 * ƒVƒXƒeƒ€‚©‚çƒWƒ‡ƒuƒŠƒZƒbƒg—v‹�‚ª‚ ‚Á‚½�ê�‡‚É�X�V‚³‚ê‚é
	 * [0: ƒŠƒZƒbƒg‚³‚ê‚Ä‚¢‚È‚¢, ”ñ0: ƒŠƒZƒbƒg‚³‚ê‚½]
	 */
	int	jobreset;
	/*
	 * Ž©Œ¾ŒêŠO‚©‚Ç‚¤‚©
	 * Œ¾Œê‚Ì‹«ŠE‚Å�X�V‚³‚ê‚é
	 * [0: Œ¾Œê“à, ”ñ0: Œ¾ŒêŠO]
	 */
	int	not_joblang;
	/*
	 * ƒWƒ‡ƒuID
	 * ƒVƒXƒeƒ€‚©‚çˆó�ü—v‹�‚ª‚ ‚Á‚½�ê�‡‚É�X�V‚³‚ê‚é
	 */
	int	job_id;
	/*
	 * ƒeƒXƒgƒvƒŠƒ“ƒg‚ª—v‹�‚³‚ê‚½‚© [0: ‚³‚ê‚Ä‚¢‚È‚¢, ”ñ0: ‚³‚ê‚½]
	 * ƒeƒXƒgƒvƒŠƒ“ƒg—v‹�‚ª‚ ‚Á‚½�ê�‡‚É�X�V‚³‚ê‚é�B
	 * di_notify_msg(DI_NOTIFYMSG_JOBEND)‚ÅƒNƒŠƒA(=0)‚³‚ê‚é�B
	 * ƒeƒXƒgƒvƒŠƒ“ƒg‹@”\‚ðƒTƒ|�[ƒg‚µ‚Ä‚¢‚éŠÂ‹«‚Ì‚Ý•K—v�B
	 */
	int	testprint;
	/*
	 * ƒlƒbƒgƒWƒ‡ƒuID
	 * ƒVƒXƒeƒ€‚©‚çˆó�ü—v‹�‚ª‚ ‚Á‚½�ê�‡‚É�X�V‚³‚ê‚é
	 */
	int	njob_id;
	/*
	 * ƒ`ƒƒƒlƒ‹”Ô�†
	 * ƒVƒXƒeƒ€‚©‚çˆó�ü—v‹�‚ª‚ ‚Á‚½Žž‚É�X�V‚³‚ê‚é
	 * ’l‚Í DI_CHANNEL_xxx
	 */
	int	host_channel;
	/*
	 * PDL ID
	 * ƒVƒXƒeƒ€‚©‚çˆó�ü—v‹�‚ª‚ ‚Á‚½Žž‚É�X�V‚³‚ê‚é
	 * ’l‚Í DI_PDL_xxx
	 */
	int	pdl_id;
	/*
	 * ƒvƒ�ƒZƒXID
	 * ƒVƒXƒeƒ€‚©‚çˆó�ü—v‹�‚ª‚ ‚Á‚½Žž‚É�X�V‚³‚ê‚é
	 */
	long	pid;
	/*
	 * ƒvƒ�ƒOƒ‰ƒ€”Ô�†
	 * ƒVƒXƒeƒ€‚©‚çƒvƒ�ƒOƒ‰ƒ€“o˜^/�í�œ—v‹�‚ª‚ ‚Á‚½Žž‚É�X�V‚³‚ê‚é�iMSISŒnPDL�ê—p�j
	 * ’l‚ÌƒNƒŠƒA‚Íƒ†�[ƒU‚ª–¾Ž¦“I‚É�s‚Á‚Ä‚­‚¾‚³‚¢
	 */
	int	pno;
	/*
	 * ƒVƒXƒeƒ€‚©‚çƒvƒ‰ƒCƒ€ƒŠƒZƒbƒg—v‹�‚ª‚ ‚Á‚½Žž‚É”ñ‚O‚É�X�V‚³‚ê‚é�iMSISŒnPDL�ê—p�j
	 * ’l‚ÌƒNƒŠƒA‚Íƒ†�[ƒU‚ª–¾Ž¦“I‚É�s‚Á‚Ä‚­‚¾‚³‚¢
	 */
	int	prime_reset;
	/*
	 * ƒ†�[ƒUƒXƒCƒbƒ`”Ô�†
	 * ƒVƒXƒeƒ€‚©‚çˆó�ü—v‹�‚ª‚ ‚Á‚½Žž‚É�X�V‚³‚ê‚é�iMSISŒnPDL�ê—p�j
	 */
	int		uswitch;
	/*
	 * ƒf�[ƒ^�ˆ—�ŠJŽn—�—R
	 * ƒVƒXƒeƒ€‚©‚çˆó�ü—v‹�‚ª‚ ‚Á‚½Žž‚É�X�V‚³‚ê‚é�iMSISŒnPDL�ê—p�j
	 */
	int		reason;
} async_para_t, di_async_para_t;

typedef struct di_setinfo {
	/*
	 * ”ñ“¯Šú‚É•Ï‰»‚·‚éƒpƒ‰ƒ��[ƒ^
	 * Œ»�óGPS�ã‚Ì“®�ì‚Å‚Ì‚Ý—LŒø
	 */
	di_async_para_t	*async;
	/*
	 * DI‚ªƒXƒgƒŠ�[ƒ€‚©‚ç“Ç‚Ý�ž‚ñ‚¾ƒoƒCƒg�”�B
	 * di_singet(c) or di_sinseek ‚ðƒR�[ƒ‹‚·‚é‚½‚Ñ‚ÉŽ©“®“I‚É�X�V‚³‚ê‚é�B
	 * DEBUG‚ðdefine‚µ‚ÄƒRƒ“ƒpƒCƒ‹‚µ‚½�ê�‡‚Ì‚Ý—LŒø
	 */
	int	cmd_offset;
	/*
	 * ƒCƒ“ƒ^ƒvƒŠƒ^ID(’l‚ÍˆÈ‰º‚Ìdefine)
	 */
#define DI_INTERP_RPCS			0x0000	/* RPCS */
#define DI_INTERP_XHTML			0x0010	/* XHTML */
#define DI_INTERP_EXIF			0x0100	/* EXIF */
#define DI_INTERP_BMLINKS		0x0101	/* BMLinkS */
#define DI_INTERP_PS			0x1000	/* PS */
#define DI_INTERP_PCL			0x1001	/* PCL */

#define DI_INTERP_RPDL			0x10000	/* RPDL */
#define DI_INTERP_R98			0x10001	/* R98 */
#define DI_INTERP_R16			0x10010	/* R16 */
#define DI_INTERP_R55			0x10011	/* R55 */
#define DI_INTERP_RPGL2			0x10100	/* RPGL2 */
#define DI_INTERP_RTIFF			0x10101	/* RTIFF */
#define DI_INTERP_RPGL2c		0x10110	/* RPGL2c */
#define DI_INTERP_PICTBRIDGE	0x0110	/* PictBridge */
#define DI_INTERP_XPS			0x0111	/* XPS */
#define DI_INTERP_MP_TIFF		0x11000	/* MediaPrintTIFF */
#define DI_INTERP_MP_JPEG		0x11001	/* MediaPrintJPEG */
	 int	interp_id;
	/*
	 * ƒVƒXƒeƒ€�‰Šú‰»‚Ì‚½‚ß‚ÌƒIƒvƒVƒ‡ƒ“ƒpƒ‰ƒ��[ƒ^(-1‚Å–¢Žg—p)
	 * interp_id ‚É‚æ‚Á‚ÄˆÓ–¡‚ª•Ï‰»‚·‚é
	 * DI_INTERP_RPCS	‹N“®—�—R’Ê’m
	 * ‚»‚Ì‘¼			–¢Žg—p
	 */
	long	option;
} di_setinfo_t;

/* ƒ†�[ƒU�[ƒWƒ‡ƒu•Ï�”�\‘¢‘Ì */
typedef struct ujobparam_var {
	unsigned long	flag;
/* di_ujob_info_t‚Éƒ}ƒNƒ�’è‹`‚ª‚ ‚é */
} ujobparam_var_t;

typedef struct di_onebininfo {
	unsigned short	id;		/* ”rŽ†ƒrƒ“‚ÌID */
#define DI_BIN_STAPLER            (1 << 0)        /* ƒXƒe�[ƒvƒ‹‰Â */
#define DI_BIN_PUNCH              (1 << 1)        /* ƒpƒ“ƒ`‰Â */
#define DI_BIN_SHIFT              (1 << 2)        /* ƒVƒtƒg”rŽ†‰Â */
#define DI_BIN_PAPER_SENSE        (1 << 3)        /* sense paper exist */
#define DI_BIN_FULL_SENSE         (1 << 4)        /* sense paper full */
#define DI_BIN_NODUPLEX           (1 << 5)        /* noduplex */
#define DI_BIN_SADDLE             (1 << 6)        /* saddle */
#define DI_BIN_FOLD               (1 << 7)        /* �Ü‚è‹@”\ */
	unsigned long	attr;	/* ”rŽ†ƒrƒ“‚ÌŽí—Þ */
#define DI_BIN_FULL               (1 << 0)        /* –ž”t */
#define DI_BIN_ERROR              (1 << 1)        /* ŒÌ�á�ó‘Ô */
#define DI_BIN_STOPEXIT           (1 << 2)        /* ”rŽ†—}�§ */
#define DI_BIN_SADDLE_DISABLE     (1 << 3)        /* ’†’Ô‚¶”rŽ†‹ÖŽ~ */
#define DI_BIN_NORMAL_DISABLE     (1 << 4)        /* ’†’Ô‚¶ˆÈŠO‚Ì”rŽ†‹ÖŽ~ */
	unsigned long	status;	/* ƒXƒe�[ƒ^ƒX */
} di_onebininfo_t;

#define DI_MAX_BIN_NUM 32

typedef struct di_bininfo {
	long			bin_num;					/* ”rŽ†ƒrƒ“‚Ì�” */
	di_onebininfo_t	bininfo[DI_MAX_BIN_NUM];	/* Šeƒrƒ“‚Ì�î•ñ */
} di_bininfo_t;

typedef struct di_filectrl {
	int	ope;
	char	Fontfilename[DI_PATHMAX];
	char	Tempfilename[DI_PATHMAX];
	int	fd;
} di_filectrl_t;

typedef struct di_rotenvinfo {
#define	DI_CHKDIR_STAPLE     (1<<0)	    /* stapleƒpƒ‰ƒ��[ƒ^Žw’è */
#define DI_CHKDIR_PUNCH      (1<<1)	    /* punchƒpƒ‰ƒ��[ƒ^Žw’è */
#define DI_CHKDIR_BINDING    (1<<2)	    /* bindingƒpƒ‰ƒ��[ƒ^Žw’è */
#define DI_CHKDIR_RESOLUTION (1<<3)	    /* reso_x‚Æreso_yƒpƒ‰ƒ��[ƒ^Žw’è */
#define DI_CHKDIR_DEPTH      (1<<5)	    /* depthƒpƒ‰ƒ��[ƒ^Žw’è */
	unsigned long		flag;			/* �Ý’è‚·‚éƒpƒ‰ƒ��[ƒ^ */
	int					psize;			/* —pŽ†ƒTƒCƒY�i•K�{�j */
	unsigned long		pwidth;			/* —pŽ†•��i0.1mm’PˆÊ�j */
	unsigned long		plength;		/* —pŽ†’·�i0.1mm’PˆÊ�j */
#define DI_ORIENTATION_PORTRAIT  (1<<0)	/* Portrait */
#define DI_ORIENTATION_LANDSCAPE (1<<1)	/* Landscape */
	unsigned char		orientation;	/* ƒIƒŠƒGƒ“ƒe�[ƒVƒ‡ƒ“ */
#define DI_STAPLE_OFF              (0)  /* ‚È‚µ */
#define DI_STAPLE_LEFT_TOP_HORIZ   (1)  /* Žg—p‚Í�„�§‚µ‚È‚¢ */
#define DI_STAPLE_LEFT_TOP_VERT    (2)  /* Žg—p‚Í�„�§‚µ‚È‚¢ */
#define DI_STAPLE_LEFT_TOP_SLANT   (3)  /* �¶�ãŽÎ‚ß */
#define DI_STAPLE_RIGHT_TOP_HORIZ  (5)  /* Žg—p‚Í�„�§‚µ‚È‚¢ */
#define DI_STAPLE_RIGHT_TOP_VERT   (6)  /* Žg—p‚Í�„�§‚µ‚È‚¢ */
#define DI_STAPLE_RIGHT_TOP_SLANT  (7)  /* ‰E�ãŽÎ‚ß */
#define DI_STAPLE_DOUBLE_LEFT      (9)  /* �¶‘¤‚QŒÂ�Š */
#define DI_STAPLE_DOUBLE_TOP       (10) /* �ã‘¤‚QŒÂ�Š */
#define DI_STAPLE_DOUBLE_RIGHT     (11) /* ‰E‘¤‚QŒÂ�Š */
#define DI_STAPLE_BOOKLET          (12) /* �^’†‚QŒÂ�Š */
#define DI_STAPLE_LEFT_TOP         (16) /* �¶�ã */
#define DI_STAPLE_RIGHT_TOP        (17) /* ‰E�ã */
	unsigned char		staple;			/* ƒXƒe�[ƒvƒ‹ */
#define DI_PUNCH_OFF   (0)              /* ‚È‚µ */
#define DI_PUNCH_LEFT  (1)              /* �¶•Ó */
#define DI_PUNCH_TOP   (2)              /* �ã•Ó */
#define DI_PUNCH_RIGHT (3)              /* ‰E•Ó */
#define DI_PUNCH_JP2   (0x00)           /* �ãˆÊ‚Ìƒpƒ“ƒ`Ží—Þ‚ÌŽw’è‚Í‚ ‚Á‚Ä‚à‚È‚­‚Ä‚à—Ç‚¢ */
#define DI_PUNCH_US2   (0x10)
#define DI_PUNCH_US3   (0x20)
#define DI_PUNCH_EU4   (0x30)
#define DI_PUNCH_NEU4  (0x40)
	unsigned char		punch;			/* ƒpƒ“ƒ` */
#define DI_BIND_LEFT      (0)           /* �¶’Ô‚¶ */
#define DI_BIND_TOP       (1)           /* �ã’Ô‚¶ */
#define DI_BIND_RIGHT     (2)           /* ‰E’Ô‚¶ */
#define DI_BIND_BOTTOM    (3)           /* ‰º’Ô‚¶(–¢Žg—p) */
#define DI_BIND_LEFTRIGHT (4)           /* �¶‰E’Ô‚¶(RTIFF) */
#define DI_BIND_TOPBOTTOM (5)           /* �ã‰º’Ô‚¶(RTIFF) */
#define DI_BIND_OFF       (0xF)         /* Žw’è‚È‚µ(gpsPlotChkDirection()—p) */
	unsigned char		binding;		/* ‚Æ‚¶•ûŒü */
	unsigned short		reso_x;			/* X•ûŒü‚Ì‰ð‘œ“x */
	unsigned short		reso_y;			/* Y•ûŒü‚Ì‰ð‘œ“x */
#define DI_DEPTH_2        (1)           /* ‚Q’l(1bit) */
#define DI_DEPTH_4        (2)           /* ‚S’l(2bit) */
unsigned char		depth;			    /* ŠK’² */
} di_rotenvinfo_t;

typedef struct di_imgrotinfo {
#define DI_ROT_0B    (1<<0) /* ‚O“x */
#define DI_ROT_90B   (1<<1) /* ‚X‚O“x */
#define DI_ROT_180B  (1<<2) /* ‚P‚W‚O“x */
#define DI_ROT_270B  (1<<3) /* ‚Q‚V‚O“x */
#define DI_ROT_ALL   (DI_ROT_0B|DI_ROT_90B|DI_ROT_180B|DI_ROT_270B) /* ‰ñ“]�ˆ—�•s•K—v */
#define DI_ROT_NG    (0x80) /* ‰ñ“]�ˆ—�•s‰Â */
#define DI_ROT_ERROR (0)    /* ƒGƒ‰�[ (’ÊŽ†•s‰Â‚È‚Ç) */

	int direction;	    	/* ‰æ‘œ•ûŒü */
#define DI_ROT_0B    (1<<0)	/* ‚O“x */
#define DI_ROT_90B   (1<<1)	/* ‚X‚O“x */
#define DI_ROT_180B  (1<<2)	/* ‚P‚W‚O“x */
#define DI_ROT_270B  (1<<3)	/* ‚Q‚V‚O“x */
#define DI_ROT_ERROR (0)	/* ŽÎ‚ßƒXƒe�[ƒvƒ‹�o—ˆ‚È‚¢�A–”‚Íƒpƒ‰ƒ��[ƒ^–³Œø�iƒXƒe�[ƒvƒ‹Žw’è‚µ‚Ä‚¢‚È‚¢�ê�‡‚È‚Ç�j */
	int slantdirection;		/* ŽÎ‚ßƒXƒe�[ƒvƒ‹‚ª‚Å‚«‚é‰æ‘œ•ûŒü */
} di_imgrotinfo_t;

/* ƒJƒ‰�[ƒvƒ�ƒtƒ@ƒCƒ‹�î•ñ */
/* GPS‚Ì�\‘¢‘Ì gps_color_profile_info‚Æ“¯‚¶Œ^ */
#define	DI_MAX_CPF_PATH_LEN		96
#define	DI_MAX_CPF_ATTR_LEN		27

typedef struct di_color_profile_info {
	unsigned long		key;	/* profile ID */
	unsigned char		media;	/* profile in media */
	unsigned char		attr[DI_MAX_CPF_ATTR_LEN];	/* ‘®�« */
	char			path[DI_MAX_CPF_PATH_LEN];	/* ƒpƒX–¼ */
} di_color_profile_info_t;

/* ƒvƒ�ƒOƒ‰ƒ€ƒe�[ƒuƒ‹ */
typedef struct di_progtable {
	unsigned char eml_name[3];	/* ƒGƒ~ƒ…ƒŒ�[ƒVƒ‡ƒ“–¼ */
	unsigned char file_no;	/*ƒGƒ~ƒ…ƒŒ�[ƒVƒ‡ƒ“’PˆÊ‚ÅŠÇ—�‚³‚ê‚Ä‚¢‚éƒvƒ�ƒOƒ‰ƒ€”Ô�†�BNVRAMƒtƒ@ƒCƒ‹‚Ìƒtƒ@ƒCƒ‹”Ô�†‚É‘Î‰ž‚·‚é�B */
} di_progtable_t;

#define	DI_AUTH_LIMIT_ADMINMACHINE	(1 << 0)		/* ‹@ŠíŠÇ—�ŽÒ‹@”\ 	*/
#define	DI_AUTH_LIMIT_ADMINUSER		(1 << 1)		/* ƒ†�[ƒU�[ŠÇ—�ŽÒ‹@”\ */
#define	DI_AUTH_LIMIT_ADMINDOCUMENT	(1 << 2)		/* •¶�‘ŠÇ—�ŽÒ‹@”\ 	*/
#define	DI_AUTH_LIMIT_ADMINNETWORK	(1 << 3)		/* ƒlƒbƒgƒ��[ƒNŠÇ—�ŽÒ‹@”\ */
#define	DI_AUTH_LIMIT_CERUSER		(1 << 4)		/* ”F�Øƒ†�[ƒU‹@”\ 	*/
#define	DI_AUTH_LIMIT_SUPERVISOR      	(1 << 5)		/* ƒX�[ƒp�[ƒoƒCƒU�[‹@”\ */
#define	DI_AUTH_LIMIT_SERVICE		(1 << 6)		/* ƒT�[ƒrƒX‹@”\ 	*/
#define DI_ALL_FUNCTION_LIMIT		0xffffffff		/* ‘S‹@”\�§ŒÀ */

/*
	NVRAM FILE ACCESS
*/
#define DI_AUTHORIZED		 0
#define DI_AUTH_LIMITED		-1
#define DI_AUTH_NOT_NOTIFY	-2

/* flag to check paper size and kind for di_query_duplex() */
#define DI_DUPLEX_CHK_SIZE	(1 << 0)
#define DI_DUPLEX_CHK_KIND	(1 << 1)

typedef struct di_chkduplexok {
	unsigned long	flag;		/* check flag */
	unsigned long	pwidth;		/* the width of free size paper (0.1mm) */
	unsigned long	plength;	/* the height of free size paper (0.1mm) */
	unsigned char	psize;		/* size of paper */
	unsigned char	pkind;		/* kind of paper */
	unsigned char	reserved[18];	/* reserved parameter for new function */
} di_chkduplexok_t;

typedef struct di_trayrequest {
	unsigned long		flag;
#define DI_TRAYREQFLAG_ALL			(0xFFFFFFFF)
#define DI_TRAYREQFLAG_PWIDTH		(1<<0)
#define DI_TRAYREQFLAG_PLENGTH		(1<<1)
#define DI_TRAYREQFLAG_MODE			(1<<2)
	unsigned long		pwidth;
	unsigned long		plength;
	unsigned char		mode:1;
#define	DI_REQ_MODE1				(0)
#define	DI_REQ_MODE2				(1)
	unsigned char		res1:7;
	unsigned char		res2[31];

} di_trayrequest_t; 

typedef struct di_res_reqtray {
	int result;
	int tray_id;
	int paper_code;
	unsigned long paper_width;
	unsigned long paper_length;
} di_res_reqtray_t;

typedef struct di_printcondition {
	unsigned int job_type;
#define DI_PCND_SDK_THUMBNAILJOB	4
#define DI_PCND_SDK_PRINTJOB		3
#define DI_PCND_THUMBNAILJOB		2
#define DI_PCND_MEDIAPRINTJOB		1
#define DI_PCND_PRINTJOB			0
	unsigned long chg_paper_kind;
#define DI_PCND_CHG_PAPERKIND_EXIST	(1 << 0)
	unsigned int paper_kind;
	unsigned long duplex;
#define DI_PCND_DUPLEX_OFF		(1 << 0)
#define DI_PCND_DUPLEX_LEFT		(1 << 1)
#define DI_PCND_DUPLEX_TOP		(1 << 3)
	unsigned long tonersave_color;
#define DI_PCND_TONERSAVE_COLOR_OFF		(1 << 0)
#define DI_PCND_TONERSAVE_COLOR_ON		(1 << 1)
	unsigned long nup;
#define DI_PCND_NUP_OFF			(1 << 0)
#define DI_PCND_NUP_2IN1		(1 << 1)
#define DI_PCND_NUP_4IN1		(1 << 2)
#define DI_PCND_NUP_6IN1		(1 << 3)
#define DI_PCND_NUP_8IN1		(1 << 4)
#define DI_PCND_NUP_9IN1		(1 << 5)
#define DI_PCND_NUP_16IN1		(1 << 6)
	unsigned long nup_option;
#define DI_PCND_NUPPAGEORDER_RIGHTTHENDOWN		(1 << 0)
#define DI_PCND_NUPPAGEORDER_LEFTTHENDOWN		(1 << 1)
#define DI_PCND_NUPPAGEORDER_DOWNTHENRIGHT		(1 << 2)
#define DI_PCND_NUPPAGEORDER_DOWNTHENLEFT		(1 << 3)
	unsigned long nup_border;
#define DI_PCND_NUPBORDER_OFF	(1 << 0)
#define DI_PCND_NUPBORDER_ON	(1 << 1)
	unsigned long colormode;
#define DI_PCND_COLORMODE_MONO	(1 << 0)
#define DI_PCND_COLORMODE_COLOR	(1 << 1)
	unsigned long inputtray;
#define DI_PCND_INPUTTRAY_AUTO	(1 << 0)
#define DI_PCND_INPUTTRAY_1		(1 << 1)
#define DI_PCND_INPUTTRAY_2		(1 << 2)
#define DI_PCND_INPUTTRAY_3		(1 << 3)
#define DI_PCND_INPUTTRAY_4		(1 << 4)
#define DI_PCND_INPUTTRAY_5		(1 << 5)
#define DI_PCND_INPUTTRAY_6		(1 << 6)
#define DI_PCND_INPUTTRAY_7		(1 << 7)
#define DI_PCND_INPUTTRAY_LCT	(1 << 30)
#define DI_PCND_INPUTTRAY_MAN	(1 << 31)
	unsigned long staple;
#define DI_PCND_STAPLE_OFF				(1 << 0)
#define DI_PCND_STAPLE_LEFTTOP			(1 << 1)
#define DI_PCND_STAPLE_RIGHTTOP			(1 << 2)
#define DI_PCND_STAPLE_LEFTTOPSLANT		(1 << 3)
#define DI_PCND_STAPLE_RIGHTTOPSLANT	(1 << 4)
#define DI_PCND_STAPLE_LEFT2			(1 << 5)
#define DI_PCND_STAPLE_TOP2				(1 << 6)
#define DI_PCND_STAPLE_RIGHT2			(1 << 7)
#define DI_PCND_STAPLE_BOOKLET			(1 << 8)
	unsigned long punch;
#define DI_PCND_PUNCH_OFF			(1 << 0)
#define DI_PCND_PUNCH_LEFT2			(1 << 1)
#define DI_PCND_PUNCH_TOP2			(1 << 2)
#define DI_PCND_PUNCH_RIGHT2		(1 << 3)
#define DI_PCND_PUNCH_LEFT3			(1 << 4)
#define DI_PCND_PUNCH_TOP3			(1 << 5)
#define DI_PCND_PUNCH_RIGHT3		(1 << 6)
#define DI_PCND_PUNCH_LEFT4			(1 << 7)
#define DI_PCND_PUNCH_TOP4			(1 << 8)
#define DI_PCND_PUNCH_RIGHT4		(1 << 9)
#define DI_PCND_PUNCH_LEFTGBC		(1 << 10)
#define DI_PCND_PUNCH_TOPGBC		(1 << 11)
#define DI_PCND_PUNCH_RIGHTGBC		(1 << 12)
#define DI_PCND_PUNCH_LEFTTOP		(1 << 13)
} di_printcondition_t;

typedef struct di_printcondition2 {
#define DI_PDF_PASSWORD_LEN			36
	unsigned char pdfpassword[DI_PDF_PASSWORD_LEN];
	unsigned long reserve[16];
} di_printcondition2_t;

typedef struct di_media_printcondition {
	unsigned long bind;
#define DI_PCND_MEDIA_BIND_OFF				(1 << 0)
#define DI_PCND_MEDIA_BIND_MAGAZIGE_LEFT	(1 << 1)
#define DI_PCND_MEDIA_BIND_MAGAZIGE_RIGHT	(1 << 2)
	struct {
			unsigned long magnification;
#define DI_PCND_MEDIA_MAG_OFF		(1 << 0)
#define DI_PCND_MEDIA_MAG_ON		(1 << 1)
			unsigned int size_code;
			unsigned long paper_width;
			unsigned long paper_length;
	} paper_size;
	struct {
			unsigned long tiff;
#define DI_PCND_MEDIA_RESOL_TIFF_200		(1 << 0)
#define DI_PCND_MEDIA_RESOL_TIFF_300		(1 << 1)
#define DI_PCND_MEDIA_RESOL_TIFF_400		(1 << 2)
#define DI_PCND_MEDIA_RESOL_TIFF_600		(1 << 3)
			unsigned long pdf;
#define DI_PCND_MEDIA_RESOL_PDF_600_FAST	(1 << 0)
#define DI_PCND_MEDIA_RESOL_PDF_600_STD		(1 << 1)
#define DI_PCND_MEDIA_RESOL_PDF_600_HIGH	(1 << 2)
#define DI_PCND_MEDIA_RESOL_PDF_1200		(1 << 3)
#define DI_PCND_MEDIA_RESOL_PDF_300			(1 << 4)
#define DI_PCND_MEDIA_RESOL_PDF_1200_2		(1 << 5)
	} resolution;
	unsigned long printquality;
#define DI_PCND_MEDIA_PRTQUAL_NORMAL		(1 << 0)
#define DI_PCND_MEDIA_PRTQUAL_DRAFT			(1 << 1)
#define DI_PCND_MEDIA_PRTQUAL_FINE			(1 << 2)
	unsigned long reserve1;
	unsigned long reserve2;
	unsigned long reserve3;
} di_media_printcondition_t;

typedef struct di_sdk_printcondition {
#define DI_PDL_PAGES_LEN		229
	unsigned char printpages[DI_PDL_PAGES_LEN];
	unsigned long forced_duplex;
#define DI_PCND_SDK_FORCEDDUPLEX_LEFT		(1 << 1)
#define DI_PCND_SDK_FORCEDDUPLEX_TOP		(1 << 3)
	unsigned long duplex;
#define DI_PCND_SDK_DUPLEX_OFF			(1 << 0)
#define DI_PCND_SDK_DUPLEX_LEFT			(1 << 1)
#define DI_PCND_SDK_DUPLEX_TOP			(1 << 3)
	unsigned long forced_colormode;
	unsigned long colormode;
#define DI_PCND_SDK_COLORMODE_MONO		(1 << 0)
#define DI_PCND_SDK_COLORMODE_COLOR		(1 << 1)
	unsigned long tonersave_color;
#define DI_PCND_SDK_TONERSAVE_OFF		(1 << 0)
#define DI_PCND_SDK_TONERSAVE_ON		(1 << 1)
	unsigned long tonersave_mono;
#define DI_PCND_SDK_TONERSAVE_MONO_OFF	(1 << 0)
#define DI_PCND_SDK_TONERSAVE_MONO_ON	(1 << 1)
	unsigned int print_num;
	unsigned int chg_paper_kind;
#define DI_PCND_SDK_CHG_PAPERKIND_EXIST	(1 << 0)
	unsigned int paper_kind;
	unsigned long nup;
#define DI_PCND_SDK_NUP_OFF				(1 << 0)
#define DI_PCND_SDK_NUP_2IN1			(1 << 1)
#define DI_PCND_SDK_NUP_4IN1			(1 << 2)
#define DI_PCND_SDK_NUP_6IN1			(1 << 3)
#define DI_PCND_SDK_NUP_8IN1			(1 << 4)
#define DI_PCND_SDK_NUP_9IN1			(1 << 5)
#define DI_PCND_SDK_NUP_16IN1			(1 << 6)
	unsigned long nup_option;
#define DI_PCND_SDK_NUPOPT_PAGEORDER_RIGHT_THEN_DOWN	(1 << 0)
#define DI_PCND_SDK_NUPOPT_PAGEORDER_LEFT_THEN_DOWN		(1 << 1)
#define DI_PCND_SDK_NUPOPT_PAGEORDER_DOWN_THEN_RIGHT	(1 << 2)
#define DI_PCND_SDK_NUPOPT_PAGEORDER_DOWN_THEN_LEFT		(1 << 3)
	unsigned long nup_border;
#define DI_PCND_SDK_NUP_BORDER_OFF		(1 << 0)
#define DI_PCND_SDK_NUP_BORDER_ON		(1 << 1)
#define DI_SDK_PDF_PASSWORD_LEN			(36)
	unsigned char pdfpassword[DI_SDK_PDF_PASSWORD_LEN];
	unsigned long inputtray;
#define DI_PCND_SDK_INPUTTRAY_AUTO		(1 << 0)
#define DI_PCND_SDK_INPUTTRAY_1			(1 << 1)
#define DI_PCND_SDK_INPUTTRAY_2			(1 << 2)
#define DI_PCND_SDK_INPUTTRAY_3			(1 << 3)
#define DI_PCND_SDK_INPUTTRAY_4			(1 << 4)
#define DI_PCND_SDK_INPUTTRAY_5			(1 << 5)
#define DI_PCND_SDK_INPUTTRAY_6			(1 << 6)
#define DI_PCND_SDK_INPUTTRAY_7			(1 << 7)
#define DI_PCND_SDK_INPUTTRAY_LCT		(1 << 30)
#define DI_PCND_SDK_INPUTTRAY_MAN		(1 << 31)
	 unsigned long sort;
#define DI_PCND_SDK_SORT_NORMAL			(1 << 0)
#define DI_PCND_SDK_SORT_ROTATE			(1 << 1)
#define DI_PCND_SDK_SORT_SHIFT			(1 << 2)
	unsigned long stack;
#define DI_PCND_SDK_STACK				(1 << 0)
	unsigned long staple;
#define DI_PCND_SDK_STAPLE_OFF				(1 << 0)
#define DI_PCND_SDK_STAPLE_LEFTTOP			(1 << 1)
#define DI_PCND_SDK_STAPLE_RIGHTTOP			(1 << 2)
#define DI_PCND_SDK_STAPLE_LEFTTOPSLANT		(1 << 3)
#define DI_PCND_SDK_STAPLE_RIGHTTOPSLANT	(1 << 4)
#define DI_PCND_SDK_STAPLE_LEFT2			(1 << 5)
#define DI_PCND_SDK_STAPLE_TOP2				(1 << 6)
#define DI_PCND_SDK_STAPLE_RIGHT2			(1 << 7)
#define DI_PCND_SDK_STAPLE_BOOKLET			(1 << 8)
	unsigned long punch;
#define DI_PCND_SDK_PUNCH_OFF			(1 << 0)
#define DI_PCND_SDK_PUNCH_LEFT2			(1 << 1)
#define DI_PCND_SDK_PUNCH_TOP2			(1 << 2)
#define DI_PCND_SDK_PUNCH_RIGHT2		(1 << 3)
#define DI_PCND_SDK_PUNCH_LEFT3			(1 << 4)
#define DI_PCND_SDK_PUNCH_TOP3			(1 << 5)
#define DI_PCND_SDK_PUNCH_RIGHT3		(1 << 6)
#define DI_PCND_SDK_PUNCH_LEFT4			(1 << 7)
#define DI_PCND_SDK_PUNCH_TOP4			(1 << 8)
#define DI_PCND_SDK_PUNCH_RIGHT4		(1 << 9)
#define DI_PCND_SDK_PUNCH_LEFTGBC		(1 << 10)
#define DI_PCND_SDK_PUNCH_TOPGBC		(1 << 11)
#define DI_PCND_SDK_PUNCH_RIGHTGBC		(1 << 12)
#define DI_PCND_SDK_PUNCH_LEFTTOP		(1 << 13)
	unsigned long bind;
#define DI_PCND_SDK_BIND_OFF			(1 << 0)
#define DI_PCND_SDK_BIND_MAGAZINE_LEFT	(1 << 1)
#define DI_PCND_SDK_BIND_MAGAZINE_RIGHT	(1 << 2)
	struct {
		unsigned long magnification;
#define DI_PCND_SDK_MAG_OFF				(1 << 0)
#define DI_PCND_SDK_MAG_ON				(1 << 1)
		unsigned int  size_code;
		unsigned long paper_width;
		unsigned long paper_length;
	} paper_size;
	struct {
		unsigned long pdf;
#define DI_PCND_SDK_RESOL_PDF_600_FAST	(1 << 0)
#define DI_PCND_SDK_RESOL_PDF_600_STD	(1 << 1)
#define DI_PCND_SDK_RESOL_PDF_600_HIGH	(1 << 2)
#define DI_PCND_SDK_RESOL_PDF_1200		(1 << 3)
#define DI_PCND_SDK_RESOL_PDF_300		(1 << 4)
#define DI_PCND_SDK_RESOL_PDF_1200_2	(1 << 5)
	} resolution;
	unsigned long reserve[13];
} di_sdk_printcondition_t;

typedef struct di_sys2_printcondition {
	unsigned long inputtray;
#define DI_PCND_SYS2_INPUTTRAY_AUTO	(1 << 0)
#define DI_PCND_SYS2_INPUTTRAY_1	(1 << 1)
#define DI_PCND_SYS2_INPUTTRAY_2	(1 << 2)
#define DI_PCND_SYS2_INPUTTRAY_3	(1 << 3)
#define DI_PCND_SYS2_INPUTTRAY_4	(1 << 4)
#define DI_PCND_SYS2_INPUTTRAY_5	(1 << 5)
#define DI_PCND_SYS2_INPUTTRAY_6	(1 << 6)
#define DI_PCND_SYS2_INPUTTRAY_7	(1 << 7)
#define DI_PCND_SYS2_INPUTTRAY_LCT	(1 << 30)
#define DI_PCND_SYS2_INPUTTRAY_MAN	(1 << 31)
	unsigned long duplex;
#define DI_PCND_SYS2_DUPLEX_OFF		(1 << 0)
#define DI_PCND_SYS2_DUPLEX_LEFT	(1 << 1)
#define DI_PCND_SYS2_DUPLEX_TOP		(1 << 3)
	unsigned long sort;
#define DI_PCND_SYS2_SORT_NORMAL	(1 << 0)
#define DI_PCND_SYS2_SORT_ROTATE	(1 << 1)
#define DI_PCND_SYS2_SORT_SHIFT		(1 << 2)
	unsigned long stack;
#define DI_PCND_SYS2_STACK			(1 << 0)
	unsigned long staple;
#define DI_PCND_SYS2_STAPLE_OFF				(1 << 0)
#define DI_PCND_SYS2_STAPLE_LEFTTOP			(1 << 1)
#define DI_PCND_SYS2_STAPLE_RIGHTTOP		(1 << 2)
#define DI_PCND_SYS2_STAPLE_LEFTTOPSLANT	(1 << 3)
#define DI_PCND_SYS2_STAPLE_RIGHTTOPSLANT	(1 << 4)
#define DI_PCND_SYS2_STAPLE_LEFT2			(1 << 5)
#define DI_PCND_SYS2_STAPLE_TOP2			(1 << 6)
#define DI_PCND_SYS2_STAPLE_RIGHT2			(1 << 7)
#define DI_PCND_SYS2_STAPLE_BOOKLET			(1 << 8)
	unsigned long punch;
#define DI_PCND_SYS2_PUNCH_OFF		(1 << 0)
#define DI_PCND_SYS2_PUNCH_LEFT2	(1 << 1)
#define DI_PCND_SYS2_PUNCH_TOP2		(1 << 2)
#define DI_PCND_SYS2_PUNCH_RIGHT2	(1 << 3)
#define DI_PCND_SYS2_PUNCH_LEFT3	(1 << 4)
#define DI_PCND_SYS2_PUNCH_TOP3		(1 << 5)
#define DI_PCND_SYS2_PUNCH_RIGHT3	(1 << 6)
#define DI_PCND_SYS2_PUNCH_LEFT4	(1 << 7)
#define DI_PCND_SYS2_PUNCH_TOP4		(1 << 8)
#define DI_PCND_SYS2_PUNCH_RIGHT4	(1 << 9)
#define DI_PCND_SYS2_PUNCH_LEFTGBC	(1 << 10)
#define DI_PCND_SYS2_PUNCH_TOPGBC	(1 << 11)
#define DI_PCND_SYS2_PUNCH_RIGHTGBC	(1 << 12)
#define DI_PCND_SYS2_PUNCH_LEFTTOP	(1 << 13)
	unsigned int qty;
	unsigned long tonersave_mono;
#define DI_PCND_SYS2_TONERSAVE_MONO_OFF		(1 << 0)
#define DI_PCND_SYS2_TONERSAVE_MONO_ON		(1 << 1)
	unsigned long upsidedown;
#define DI_PCND_SYS2_UPSIDEDOWN_OFF	(1 << 0)
#define DI_PCND_SYS2_UPSIDEDOWN_ON	(1 << 1)
	unsigned long reserve1;
	unsigned long mode;
#define DI_PCND_SYS2_MODE_FORCERIP	(1 << 0)
} di_sys2_printcondition_t;

typedef struct di_printconditionShm {
	unsigned int job_type;
	unsigned long change;
#define DI_PCND_CHG_PDL			(1 << 0)
#define DI_PCND_CHG_PDL2		(1 << 1)
#define DI_PCND_CHG_MEDIA		(1 << 2)
#define DI_PCND_CHG_SDK			(1 << 3)
#define DI_PCND_CHG_SYS			(1 << 4)
	di_printcondition_t	pdl;
	di_printcondition2_t pdl2;
	di_media_printcondition_t media;
	di_sdk_printcondition_t sdk;
	di_sys2_printcondition_t sys;
} di_printconditionShm_t;

typedef struct {
	unsigned long support_flag;
	unsigned long forced_flag;
#define DI_PARAM_PRINTERMARKINGTYPE			(1 << 0)
#define DI_PARAM_UCPMASKTYPE				(1 << 1)
#define DI_PARAM_UCPPATTERNCOLOR			(1 << 2)
#define DI_PARAM_UCPPATTERNDENSITY			(1 << 3)
#define DI_PARAM_UCPEFFECTCOPYGUARD			(1 << 4)
#define DI_PARAM_UCPUCPEFFECTCOPYINHIBITION	(1 << 5)
#define DI_PARAM_UCPSTRPOSITION				(1 << 6)
#define DI_PARAM_UCPSTRREPEATPRINT			(1 << 7)
#define DI_PARAM_UCPFONTNUMBER				(1 << 8)
#define DI_PARAM_UCPFONTSIZE				(1 << 9)
#define DI_PARAM_UCPLINESPACE				(1 << 10)
#define DI_PARAM_UCPSTRANGLE				(1 << 11)
#define DI_PARAM_UCPSTRING					(1 << 12)
#define DI_PARAM_UCPFONTTYPE				(1 << 13)
#define DI_PARAM_UCPFONTNUMBER2				(1 << 14)
#define DI_PARAM_UCPPATTERNCOLOR2			(1 << 15)
	unsigned char printermarkingtype;
	unsigned char ucpmasktype;
	unsigned char ucppatterncolor;
	unsigned char ucppatterndensity;
	unsigned char ucpeffectcopyguard;
	unsigned char ucpeffectcopyinhibition;
	unsigned char ucpstrposition;
	unsigned char ucpstrrepeatprint;
	unsigned char ucpfontnumber;
	unsigned char ucpstring_charcode;
	unsigned char ucpstring_default_charcode;
#define DI_UCP_CHAR_CODE_NONE		0	
#define DI_UCP_CHAR_CODE_SJIS		1
#define DI_UCP_CHAR_CODE_EUSTD		2
#define DI_UCP_CHAR_CODE_CE			3
#define DI_UCP_CHAR_CODE_GREEK		4
#define DI_UCP_CHAR_CODE_CYR		5
#define DI_UCP_CHAR_CODE_TUR		6
#define DI_UCP_CHAR_CODE_BALTIC		7
#define DI_UCP_CHAR_CODE_GB			8
#define DI_UCP_CHAR_CODE_BIG		9
#define DI_UCP_CHAR_CODE_HEBREW		10
#define DI_UCP_CHAR_CODE_ARABIC		11
#define DI_UCP_CHAR_CODE_THAI		12
#define DI_UCP_CHAR_CODE_KS			13
	unsigned short ucpfontsize;
	unsigned short ucplinespace;
	unsigned short ucpstrangle;
#define DI_MAX_UCPSTRING_LEN				64
	unsigned char ucpstring[DI_MAX_UCPSTRING_LEN + 1];
	unsigned char ucpstring_default[DI_MAX_UCPSTRING_LEN + 1];
#define DI_MAX_UCPFONTTYPE_LEN				210
	unsigned char ucpfonttype[DI_MAX_UCPFONTTYPE_LEN + 1];
	unsigned char ucpfontnumber2;
	unsigned char ucppatterncolor2;
} di_ucp_param_t;

enum {
	DI_STRING_DOT_DENSITY1,
	DI_STRING_DOT_DENSITY2,
	DI_STRING_DOT_DENSITY3,
	DI_STRING_DOT_DENSITY4,
	DI_STRING_DOT_DENSITY5,
	DI_BACKGROUND_DOT_DENSITY1,
	DI_BACKGROUND_DOT_DENSITY2,
	DI_BACKGROUND_DOT_DENSITY3,
	DI_BACKGROUND_DOT_DENSITY4,
	DI_BACKGROUND_DOT_DENSITY5,
	DI_MASKTYPE_AMIME,
	DI_MASKTYPE_HIGAKI,
	DI_MASKTYPE_KIKKOU,
	DI_MASKTYPE_KOUSHI1,
	DI_MASKTYPE_KOUSHI2,
	DI_MASKTYPE_MATSUKAWABISHI,
	DI_MASKTYPE_SEIGAIHA,
	DI_MASKTYPE_SHIPPOU,
	DI_MASKTYPE_SYOKKOU,
	DI_MASKTYPE_UROKO,
	DI_EFFECTCOPYGUARD_BACKGROUND,
	DI_EFFECTCOPYGUARD_STRING
};

typedef struct {
	unsigned char kind;
	unsigned char resolution;
#define DI_UCP_DATA_RES_200x200		(1)
#define DI_UCP_DATA_RES_300x300		(2)
#define DI_UCP_DATA_RES_400x400		(3)
#define DI_UCP_DATA_RES_600x600		(4)
#define DI_UCP_DATA_RES_600x1200	(5)
#define DI_UCP_DATA_RES_1200x600	(6)
#define DI_UCP_DATA_RES_1200x1200	(7)
	unsigned char depth;
#define DI_UCP_DATA_DEPTH_1BIT		(1)
#define DI_UCP_DATA_DEPTH_2BIT		(2)
#define DI_UCP_DATA_DEPTH_4BIT		(4)
} di_ucp_info_t;

typedef struct {
	unsigned char width;
	unsigned char length;
	long offset;
} di_ucp_data_t;

typedef struct {
	unsigned long flag;
#define DI_PINFO_NUP 		(1 << 0)
#define DI_PINFO_UPSIDEDOWN (1 << 1)
	struct {
			unsigned char layout;
#define DI_PINFO_NUPLAYOUT_OFF		0
#define DI_PINFO_NUPLAYOUT_2in1		1
#define DI_PINFO_NUPLAYOUT_4in1		2
#define DI_PINFO_NUPLAYOUT_6in1		3
#define DI_PINFO_NUPLAYOUT_8in1		4
#define DI_PINFO_NUPLAYOUT_9in1		5
#define DI_PINFO_NUPLAYOUT_16in1	6
			unsigned char option;
#define DI_PINFO_NUPOPTION_RIGHTTHENDOWN	0
#define DI_PINFO_NUPOPTION_LEFTTHENDOWN		1
#define DI_PINFO_NUPOPTION_DOWNTHENRIGHT	2
#define DI_PINFO_NUPOPTION_DOWNTHENLEFT		3
			unsigned char line;
#define DI_PINFO_NUPLINE_OFF	0
#define DI_PINFO_NUPLINE_ON		1
			unsigned char reserve;
	} nup;
	unsigned char upsidedown;
#define DI_PINFO_UPSIDEDOWN_OFF 0
#define DI_PINFO_UPSIDEDOWN_ON 	1
	unsigned char reserve1[3];
	unsigned long reserve2[4];
	unsigned long driver_flag;
#define DI_PINFO_D_WEEKLY			0
#define DI_PINFO_D_OUTPUT_REVERSE	1
#define DI_PINFO_D_USED_PROFILE		2
#define DI_PINFO_D_TAB				3
#define DI_PINFO_D_PRINTER_MARKING		4
#define DI_PINFO_D_TWIN_COLOR			5
	unsigned char driver_prtcond[32];
#define DI_PINFO_D_OFF	0
#define DI_PINFO_D_ON	1
} di_printinfo_t;

#include "di_paperdef.h"
#include "di_envdef.h"
#include "di_errorcode.h"

#ifndef DEFINE_DI_TYPE

#ifndef EXPORT
#ifndef DI_PACKDLL
#define EXPORT
#else
#define EXPORT  __declspec(dllexport)
#endif
#endif

/** \defgroup PublicInterface DI I/F
 * \{
 */

/**
 * \brief DI I/F‚Ì�‰Šú‰»�A‹y‚Ñ�»•i�î•ñ‚ÌŽæ“¾‚ð�s‚È‚¤�B
 *
 * \param initinfo DI‚ª’l‚ðƒZƒbƒg‚·‚é�\‘¢‘Ì�B
 * \param setinfo  DI‚É“n‚·ŠeŽíƒpƒ‰ƒ��[ƒ^�BŒ»�óGPS‚Ì‚Ý‚Å—LŒø�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO Ž¸”s
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚È‚¢�B
 * \pre ˆø�” *initinfo ‚ÉƒAƒNƒZƒX‰Â”\�B
 * \pre ˆø�” *setinfo ‚ÉƒAƒNƒZƒX‰Â”\�B
 * \pre ˆø�” setinfo->interp_id ‚ªˆÈ‰º‚Ì‚¢‚¸‚ê‚©�B
 *  \li DI_ITNERP_RPCS
 *  \li DI_INTERP_XHTML
 *  \li DI_INTERP_EXIF
 *  \li DI_INTERP_BMLINKS
 *  \li DI_INTERP_PS
 *  \li DI_INTERP_PCL
 * \pre ˆø�” setinfo->async ‚ªƒAƒNƒZƒX‰Â”\(GPS“®�ì‚Ì‚Ý)�B
 *
 * \post di_term() ‚ªƒR�[ƒ‹‚³‚ê‚é‚Ü‚Å di_init() ‚ÍŽg—p•s‰Â”\�B
 * \post di_term() ‚ªƒR�[ƒ‹‚³‚ê‚é‚Ü‚Ådi_init()‚ð�œ‚­‘S‚Ä‚Ì‚c‚h‚ÌƒCƒ“ƒ^�[
 * ƒtƒF�[ƒX‚ªŽg—p‰Â”\�B
 * \post di_term()‚ªƒR�[ƒ‹‚³‚ê‚é‚Ü‚Åsetinfo->async‚ÌŠeƒpƒ‰ƒ��[ƒ^‚ª”ñ“¯Šú
 * ‚É�X�V‚³‚ê‚é(GPS“®�ì‚Ì‚Ý)�B
 * \post ƒpƒlƒ‹‚É‚c‚h‚ðŽg—p‚µ‚Ä‚¢‚éƒvƒŠƒ“ƒ^ƒAƒvƒŠ–¼•\Ž¦(GPS“®�ì‚Ì‚Ý)�B
 * \post ˆø�” *initinfo “à‚Ìƒ�ƒ“ƒo‚ª“K�Ø‚È’l‚É�X�V‚³‚ê‚é�B
 */
extern EXPORT int di_init( di_initinfo_t *initinfo, di_setinfo_t *setinfo );

/**
 * \brief DI‚ªƒZƒbƒg‚µ‚½ƒpƒ‰ƒ��[ƒ^‚ðƒNƒŠƒA‚·‚é�B
 *
 *  \param devinfo   �î•ñ‚ªŠi”[‚³‚ê‚Ä‚¢‚é�\‘¢‘Ì�B
 *  \param free_func –{ŠÖ�”“à‚Åƒ�ƒ‚ƒŠ‚ð‰ð•ú‚·‚é‚½‚ß‚ÌƒR�[ƒ‹ƒoƒbƒNŠÖ�”�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO Ž¸”s
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *devinfo ‚ÉƒAƒNƒZƒX‰Â”\�B
 * \pre free_func ‚ÉƒR�[ƒ‹‰Â”\�B
 *
 * \post di_getinfo()‚ÅŠm•Û‚µ‚½ƒ�ƒ‚ƒŠ‚Í�Afree_func‚ðŽg—p‚µ‚Ä‰ð•ú‚³‚ê‚é�B
 * \post *devinfo‚Ìƒpƒ‰ƒ��[ƒ^‚Íƒ[ƒ�ƒNƒŠƒA‚³‚ê‚é�B
 */
extern EXPORT int di_clear( di_devinfo_t *devinfo, DI_CALLBACK_MEMFREE free_func );

/**
 * \brief DI I/F‚Ì�I—¹�ˆ—�‚ð�s‚È‚¤�B
 *
 * \post di_init(),di_term()‚ð�œ‚­‘S‚Ä‚Ì‚c‚h‚ÌƒCƒ“ƒ^�[ƒtƒF�[ƒX‚ªŽg—p•s‰Â�B
 * \post ƒvƒŠƒ“ƒ^‚n‚r‚ª�A‚c‚h‚ðŽg—p‚µ‚Ä‚¢‚éƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚Ì�I—¹‚ð”FŽ¯�B
 */
extern EXPORT void di_term();

/**
 * \brief ƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚Ì‹N“®‚©‚ç�I—¹‚Ü‚Å•Ï‰»‚µ‚È‚¢‹@ŽíˆË‘¶�î•ñ‚ÌŽæ“¾‚ð
 *�s‚È‚¤�B
 *
 *  \param devinfo �î•ñ‚ðŠi”[‚·‚é�\‘¢‘Ì�B
 *  \param alloc_func –{ŠÖ�”“à‚Åƒ�ƒ‚ƒŠ‚ðŠm•Û‚·‚é‚½‚ß‚ÌƒR�[ƒ‹ƒoƒbƒNŠÖ�”�B
 *	\param dither_gamma_file ƒfƒBƒU¥ƒKƒ“ƒ}ƒtƒ@ƒCƒ‹‚Ìƒtƒ@ƒCƒ‹–¼�iƒtƒ‹ƒpƒX
 *Žw’è�j�B
 *
 * \return •Ô‚è’l‚ª‚OˆÈŠO‚Ì�ê�‡‚Í�AˆÈ‰º‚Ìƒrƒbƒgƒtƒ‰ƒO‚ÌOn‚ÌˆÓ–¡‚Æ‚È‚é�B
 *•¡�”‚Ìƒtƒ‰ƒO‚ªOn‚Æ‚È‚é�ê�‡‚à‚ ‚é�B
 *
 * \retval 0     �³�í�I—¹
 * \retval DI_GI_ERR_CONDITION  Ž–‘O�ðŒ�‚ð–ž‚½‚µ‚Ä‚¢‚È‚¢
 * \retval DI_GI_ERR_DITHER     dither_info Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_GAMMA      gamma_info Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_FONT       font_address & font_size Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_PROF       profaddress & profnumber Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_RESO       resonum & reso_set Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_NDIT       ndit Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_NPLANE     nplane Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_BGUCR      bg_(startp/slant) & ucr_(startp/slant)
 *Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_TSAVE      soft_tsave Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_TSAVE_R    tsave_ratio Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_TLIMIT     toner_limit Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_TLIMIT_R   tlimit_num & tlimit_val Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_SHDM       shdm_addr Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_SYSH       sys_handle Žæ“¾Ž¸”s
 * \retval DI_GI_ERR_EXTENDTSAVE      extend_soft_tsave Žæ“¾Ž¸”s
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *devinfo‚ªƒAƒNƒZƒX‰Â”\�B
 * \pre alloc_func( size )‚ðƒR�[ƒ‹‚·‚é‚Æ�Asize ‚¾‚¯Šm•Û‚µ‚½ƒ�ƒ‚ƒŠ‚Ì�æ“ª
 *ƒAƒhƒŒƒX‚Ì’l‚ª•Ô‚Á‚Ä‚­‚é�B
 * \pre dither_gamma_file ‚Æ‚¢‚¤ƒtƒ@ƒCƒ‹‚ª‘¶�Ý‚·‚é�A‚à‚µ‚­‚Í
 *dither_gamma_file‚ªNULL�B
 * \pre alloc_func‚ÅŽæ“¾‚·‚éƒ�ƒ‚ƒŠƒTƒCƒY‚Í�AGPSŠÂ‹«‚Å–ñ300Byte�AGPSˆÈŠO
 *‚ÌŠÂ‹«‚Å–ñ65KByte ‚Æ‚È‚é�B
 *
 * \post *devinfo“à‚Ìƒ�ƒ“ƒo‚ª“K�Ø‚È’l‚É�X�V‚³‚ê‚é�B
 */
extern EXPORT int di_getinfo(di_devinfo_t *devinfo,
							 DI_CALLBACK_MEMALLOC alloc_func,
							 char *dither_gamma_file);

/**
 * \brief ƒvƒŠƒ“ƒ^‚n‚r‚©‚çƒCƒxƒ“ƒg—v‹�‚ðŽæ“¾‚·‚é�B
 *
 * �I—¹—v‹�ˆÈŠO‚Ì—v‹�‚Ì�ê�‡,ƒCƒ“ƒ^ƒvƒŠƒ^‚Íƒf�[ƒ^�ˆ—�‰Â”\�ó‘Ô‚Æ‚È‚é�B
 *
 * \retval DI_REQ_PROCESS    ’Ê�í�ˆ—�—v‹�
 * \retval DI_REQ_CANCEL     ’Ê�í�ˆ—��{ƒWƒ‡ƒuƒLƒƒƒ“ƒZƒ‹—v‹�
 * \retval DI_REQ_EXIT       �I—¹—v‹�
 * \retval -1                ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é
 *
 * \post •Ô‚è’l‚ÉƒVƒXƒeƒ€‚©‚ç‚Ì—v‹�‚ªŠi”[‚³‚ê‚é�B
 * \post •Ô‚è’l‚ªDI_REQ_PROCESS,DI_REQ_CANCEL‚Ì�ê�‡‚É‚Í�AƒvƒŠƒ“ƒ^‚n‚r
 *‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚ªƒf�[ƒ^�ˆ—��ó‘Ô‚É‚È‚Á‚½‚Æ”»’f‚·‚é�B
 * \post •Ô‚è’l‚ªDI_REQ_EXIT‚Ì�ê�‡‚É‚Í�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚ª
 *ƒAƒCƒhƒ‹�ó‘Ô‚É‚È‚Á‚½‚Æ”»’f‚·‚é�B
 */
extern EXPORT int di_get_request();

/**
 * \brief ƒgƒŒƒC�î•ñ‚ÌŽæ“¾‚ð�s‚¤�B
 *
 * \param trayinfo ƒgƒŒƒC�î•ñ‚ðŠi”[‚·‚é�\‘¢‘Ì
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[�AƒgƒŒƒC�î•ñŽæ“¾Ž¸”s
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *trayinfo‚ªƒAƒNƒZƒX‰Â”\�B
 *
 * \post *trayinfo“à‚Ìƒ�ƒ“ƒo‚ª“K�Ø‚È’l‚É�X�V‚³‚ê‚é�B
 */
extern EXPORT int di_get_trayinfo(di_trayinfo_t *trayinfo );

/**
 * \brief ƒAƒvƒŠŒÅ—L�î•ñ‚©‚çŽw’èƒJƒeƒSƒŠ‚ÌƒL�[‚Ì’l‚ðŽæ“¾‚·‚é�B
 *
 * \param key      ŒŸ�õƒL�[(•¶Žš—ñ)
 * \param category ŒŸ�õƒJƒeƒSƒŠ(•¶Žš—ñ)
 * \param value    ŒŸ�õŒ‹‰Ê(•¶Žš—ñ)‚ðŠi”[‚·‚é—Ìˆæ
 *
 * \retval  DI_PINI_OK                 ŒŸ�õ�¬Œ÷
 * \retval  DI_PINI_KEY_NOT_FOUND      ŠY“–‚·‚ékey‚ªŒ©‚Â‚©‚ç‚È‚©‚Á‚½
 * \retval  DI_PINI_CATEGORY_NOT_FOUND ŠY“–‚·‚écategory‚ªŒ©‚Â‚©‚ç‚È‚©
 *‚Á‚½
 * \retval  DI_PINI_ERROR              ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre key‚Ì•¶Žš�”‚ªƒ^�[ƒ~ƒl�[ƒg‚ðŠÜ‚ß1•¶ŽšˆÈ�ã32•¶ŽšˆÈ“à
 * \pre category‚Ì•¶Žš�”‚ªƒ^�[ƒ~ƒl�[ƒg‚ðŠÜ‚ß1•¶ŽšˆÈ�ã32•¶ŽšˆÈ“à
 * \pre value[0]�`value[DI_MAX_VALUE_LEN-1]‚Ü‚ÅƒAƒNƒZƒX‰Â”\
 *
 * \post ŒŸ�õ‚µ‚½•¶Žš—ñ‚ªvalue‚É�‘‚«�ž‚Ü‚ê‚é�B•¶Žš—ñ‚ªDI_MAX_VALUE_LEN
 *‚æ‚è’·‚¢�ê�‡‚Í�ADI_MAX_VALUE_LEN-1‚Ü‚Å‚Ì•¶Žš—ñ‚ðŽæ“¾‚µ‚Ä�A
 *value[DI_MAX_VALUE_LEN-1]‚É�I’[•¶Žš‚ð’Ç‰Á‚·‚é�B
 */
extern EXPORT int di_get_appinfo(char *key, char *category, char value[]);

/**
 * \brief ŠÂ‹«•Ï�”‚Ì’l‚ðŽæ“¾‚·‚é�B
 *
 * \param table_name ŠÂ‹«•Ï�”ƒe�[ƒuƒ‹–¼
 * \param id         ŠÂ‹«•Ï�”ID
 * \param val        “¾‚ç‚ê‚½ŠÂ‹«•Ï�”‚Ì’l
 *
 * \retval  1 �³�í�I—¹�iŠÂ‹«•Ï�”‚ª–¾Ž¦“I‚ÉŽw’è‚³‚ê‚Ä‚¢‚é�j
 * \retval  0 �³�í�I—¹�iŠÂ‹«•Ï�”‚ª–¾Ž¦“I‚ÉŽw’è‚³‚ê‚Ä‚È‚¢‚½‚ß�AƒfƒtƒHƒ‹
 *ƒg’lƒZƒbƒg)
 * \retval -1 ƒGƒ‰�[�idi_init()‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚È‚¢�j
 * \retval -2 ƒGƒ‰�[�itable_name‚ª‘¶�Ý‚µ‚È‚¢�j
 * \retval -3 ƒGƒ‰�[�iŽw’è‚µ‚½ŠÂ‹«•Ï�”‚ª‚È‚¢�j
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre table_name‚Æ‚¢‚¤ƒe�[ƒuƒ‹‚ª‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�Atable_name‚É‘¶�Ý‚·‚é�B
 * \pre *val‚ªƒAƒNƒZƒX‰Â”\�B
 *
 * \post *val‚ÉŽw’è‚µ‚½ŠÂ‹«•Ï�”‚Ì’l‚ªŠi”[‚³‚ê‚é�B
 */
extern EXPORT int di_get_envvalue( char *table_name, long id, long *val );

/**
 * \brief ŠÂ‹«•Ï�”‚Ì’l‚ðƒZƒbƒg‚·‚é�B
 *
 * \param table_name ŠÂ‹«•Ï�”ƒe�[ƒuƒ‹–¼
 * \param id         ŠÂ‹«•Ï�”ID
 * \param val        ƒZƒbƒg‚·‚éŠÂ‹«•Ï�”‚Ì’l
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[�idi_init()‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚È‚¢�j
 * \retval -2 ƒGƒ‰�[�itable_name‚ª‘¶�Ý‚µ‚È‚¢�j
 * \retval -3 ƒGƒ‰�[�i Žw’è‚µ‚½ŠÂ‹«•Ï�”‚ª‚È‚¢�j
 * \retval -4 ƒGƒ‰�[�iƒŠ�[ƒhƒIƒ“ƒŠ�[‚ÌŠÂ‹«•Ï�”�j
 * \retval -5 ƒGƒ‰�[�i val ‚ª�Ý’è•s‰Â”\‚È’l�j
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre table_name‚Æ‚¢‚¤ƒe�[ƒuƒ‹‚ª‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�A�Ý’è‰Â”\‚È•Ï�”‚Æ‚µ‚Ätable_name‚É‘¶�Ý‚·‚é�B
 *
 * \post di_set_envvalue( table_name, id, k )‚Æ‚¢‚¤Œ`Ž®‚Å–{ŠÖ�”‚ðƒR�[
 *ƒ‹‚µ‚½�ê�‡�Adi_get_envvalue( table_name, id, &val )‚Æ‚·‚é‚Æval ‚É k
 * ‚ªƒZƒbƒg‚³‚ê‚é�B
 */
extern EXPORT int di_set_envvalue( char *table_name, long id, long val );

/**
 * \brief DI‚Ì“Á’è‚Ìƒ^ƒCƒ~ƒ“ƒO‚ÅƒR�[ƒ‹‚·‚éŠÖ�”‚ðŽw’è‚·‚é�B
 *
 * \param type ˆø�” func ‚ÅŽw’è‚³‚ê‚½ƒR�[ƒ‹ƒoƒbƒNŠÖ�”‚ðƒR�[ƒ‹‚·‚éƒ^ƒCƒ~ƒ“ƒO�B
 *Še’l‚É‘Î‚·‚éƒ^ƒCƒ~ƒ“ƒO‚ÍˆÈ‰º‚Ì‚Æ‚¨‚è�B
 *  <table>
 *   <tr>
 *    <td>DI_CALLBACK_READERR_SINGETC</td>
 *    <td>di_singetc() “à‚Å“Ç‚Ý�ž‚Ý‚ªŽ¸”s‚µ‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_READERR_SINGET</td>
 *    <td>di_singet( )“à‚Å“Ç‚Ý�ž‚Ý‚ªŽ¸”s‚µ‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_SIZEERR_SINGET</td>
 *    <td>di_singet( )‚Ìˆø�”‚Å�AƒTƒCƒYŽw’è‚ª•s�³‚¾‚Á‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_PROCDATA</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒf�[ƒ^�ˆ—�‚ÌŠJŽn—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_EXIT</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒCƒ“ƒ^ƒvƒŠƒ^�I—¹—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_CANCEL</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒf�[ƒ^�ˆ—�‚Ì’†Ž~—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_ONLINE</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒIƒ“ƒ‰ƒCƒ“—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_OFFLINE</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒIƒtƒ‰ƒCƒ“—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_TESTPRINT</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒeƒXƒgƒvƒŠƒ“ƒg—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_TRAYINFO</td>
 *    <td>ƒVƒXƒeƒ€‚©‚ç‹‹Ž†ƒgƒŒƒC‚Ì•Ï�X’Ê’m‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_BININFO</td>
 *    <td>ƒVƒXƒeƒ€‚©‚ç”rŽ†ƒrƒ“‚Ì•Ï�X’Ê’m‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_EXITPAPER</td>
 *    <td>ƒVƒXƒeƒ€‚©‚ç‹­�§”rŽ†—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_FONTCOUNT</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒtƒHƒ“ƒg�”‚ÌƒJƒEƒ“ƒg—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_PRTSTATUS</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒvƒŠƒ“ƒ^ƒXƒe�[ƒ^ƒX�î•ñ‚Ì•Ï�X’Ê’m‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *   <tr>
 *    <td>DI_CALLBACK_REQ_GAM</td>
 *    <td>ƒVƒXƒeƒ€‚©‚çƒKƒ“ƒ}‚Ì�ÄŒvŽZ—v‹�‚ª‚«‚½�ê�‡</td>
 *   </tr>
 *  </table>
 * \param func Žw’è‚·‚éƒR�[ƒ‹ƒoƒbƒNŠÖ�”
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre type ‚ªˆø�”‚Ì�à–¾‚É‚ ‚é’l‚Ì‚¢‚¸‚ê‚©
 * \pre func ‚ªƒR�[ƒ‹‰Â”\
 *
 * \post type ‚É‚æ‚èŽw’è‚³‚ê‚½ƒ^ƒCƒ~ƒ“ƒO‚Å func ‚ðƒR�[ƒ‹‚·‚é�B
 */
extern EXPORT int di_set_callbackfunc( int type, DI_CALLBACK_FUNC func );

/**
 * \brief ƒvƒŠƒ“ƒ^‚n‚r‚ªŠÇ—�‚µ‚Ä‚¢‚éƒ�ƒ‚ƒŠ‚ÌŠm•Û‚ð�s‚¤�B
 *
 * \param size Šm•Û‚·‚éƒ�ƒ‚ƒŠƒTƒCƒY(Byte)
 *
 * \retval Šm•Û‚µ‚½ƒ�ƒ‚ƒŠ‚Ì�æ“ªƒAƒhƒŒƒX Šm•Û�¬Œ÷
 * \retval NULL ƒGƒ‰�[�Aƒ�ƒ‚ƒŠŠm•ÛŽ¸”s
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre di_memory_alloc()‚ª‚P“x‚àƒR�[ƒ‹‚³‚ê‚Ä‚¢‚È‚¢(GPS“®�ì‚Ì‚Ý)
 *
 * \post •Ô‚è’l‚ÌƒAƒhƒŒƒX‚©‚çsizeƒoƒCƒg‚ªƒAƒNƒZƒX‰Â”\
 */
extern EXPORT char *di_memory_alloc(unsigned long size);

/**
 * \brief di_memory_alloc() ‚ÅŠm•Û‚µ‚½ƒ�ƒ‚ƒŠ‚Ì‰ð•ú‚ð�s‚¤�B
 *
 * \param ptr ‰ð•ú‚·‚éƒ�ƒ‚ƒŠ‚Ì�æ“ªƒAƒhƒŒƒX
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ptr‚ªdi_memory_alloc()‚ÅŠm•Û‚µ‚½ƒ�ƒ‚ƒŠ‚Ì�æ“ªƒAƒhƒŒƒX�A‚à‚µ‚­‚Í‚O
 *
 * \post ‰ð•ú‚µ‚½ƒ�ƒ‚ƒŠ‚Í�AƒvƒŠƒ“ƒ^‚n‚r‚ª—˜—p‰Â”\
 */
extern EXPORT int di_memory_free(char *ptr);

/**
 * \brief “ü—ÍƒzƒXƒgƒoƒbƒtƒ@‚ðƒI�[ƒvƒ“‚·‚é�B
 * ƒf�[ƒ^“Ç‚Ý�ž‚Ý‘O‚É•K‚¸–{ŠÖ�”‚ðƒR�[ƒ‹‚·‚é‚±‚Æ
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒVƒXƒeƒ€‚©‚ç’Ê�í�ˆ—�—v‹�‚ª—ˆ‚Ä‚¢‚é
 *(di_get_request(),di_trans_process()ŽQ�Æ)
 *
 * \post di_close_host()�A‚à‚µ‚­‚Í di_trans_process() ‚ðƒR�[ƒ‹‚·‚é‚Ü‚Å
 *ˆÈ‰º‚Ì I/F ‚ªŽg—p‰Â”\
 *  \li di_singetc()
 *  \li di_singet()
 *  \li di_sinpeekc()
 *  \li di_sinpeek()
 *  \li di_reset_sinpeek()
 *  \li di_sinseek()
 */
extern EXPORT int di_open_host();

/**
 * \brief di_open_host()‚É‚æ‚èƒI�[ƒvƒ“‚³‚ê‚½ ƒzƒXƒgƒoƒbƒtƒ@‚ðƒNƒ��[ƒY
 *‚·‚é�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 *
 * \post di_open_host() ‚ðƒR�[ƒ‹‚·‚é‚Ü‚ÅˆÈ‰º‚ÌI/F‚ªŽg—p•s‰Â”\�B
 *  \li di_singetc()
 *  \li di_singet()
 *  \li di_sinpeekc()
 *  \li di_sinpeek()
 *  \li di_reset_sinpeek()
 *  \li di_sinseek()
 */
extern EXPORT int di_close_host();

/**
 * \brief “ü—ÍƒXƒgƒŠ�[ƒ€‚©‚ç‚PƒoƒCƒg‚Ì“Ç‚Ý�ž‚Þ�B
 *
 * \param dat “Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^‚Ì’l
 *
 * \retval 0     “Ç‚Ý�ž‚Ý�¬Œ÷
 * \retval 0ˆÈŠO ƒGƒ‰�[�A“Ç‚Ý�ž‚ÝŽ¸”s�AEOF
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_host() ŽQ�Æ�j
 * \pre *dat ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *dat‚É“ü—ÍƒXƒgƒŠ�[ƒ€‚Ì�æ“ª‚PƒoƒCƒg‚ªŠi”[‚³‚ê‚é�B
 * \post ƒŠ�[ƒhƒ|ƒCƒ“ƒ^�Aƒs�[ƒNƒ|ƒCƒ“ƒ^‚ªŽŸ‚Ì“Ç‚Ý�ž‚ÝˆÊ’u‚ÉˆÚ“®‚·‚é
 */
extern EXPORT int di_singetc( unsigned char *dat );

/**
 * \brief “ü—ÍƒXƒgƒŠ�[ƒ€‚©‚ç•¡�”ƒoƒCƒg“Ç‚Ý�ž‚Þ�B
 *
 * \param buf “Ç‚Ý�ž‚Ý�æƒoƒbƒtƒ@
 * \param len “Ç‚Ý�ž‚ÞƒTƒCƒY(Byte)
 *
 * \retval >0 “Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^‚ÌƒoƒCƒg�”
 * \retval 0  EOF
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre “ü—ÍƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_host() ŽQ�Æ�j
 * \pre len ‚ª0ˆÈ�ã
 * \pre len ‚ª1ˆÈ�ã‚Ì�ê�‡‚É buf[0]�`buf[len-1] ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post buf‚É“ü—ÍƒXƒgƒŠ�[ƒ€‚Ì�æ“ªlenƒoƒCƒg‚ªŠi”[‚³‚ê‚é�B
 * \post ƒŠ�[ƒhƒ|ƒCƒ“ƒ^�Aƒs�[ƒNƒ|ƒCƒ“ƒ^‚ªŽŸ‚Ì“Ç‚Ý�ž‚ÝˆÊ’u‚ÉˆÚ“®‚·‚é�B
 */
extern EXPORT int di_singet( unsigned char *buf, long len );

/**
 * \brief “ü—ÍƒXƒgƒŠ�[ƒ€‚©‚ç‚PƒoƒCƒg“Ç‚Ý�ž‚Þ�B
 *
 * “Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^“à—e‚Í”jŠü‚µ‚È‚¢‚½‚ß�Adi_reset_sinpeek() ‚É‚æ‚è�Ä“Ç
 *‚Ý�ž‚Ý‰Â”\�B
 *
 * \param dat “Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^‚Ì’l
 *
 * \retval 0     “Ç‚Ý�ž‚Ý�¬Œ÷
 * \retval 0ˆÈŠO ƒGƒ‰�[�AEOF�A“Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^‚ªƒzƒXƒgƒoƒbƒtƒ@‚ÌƒTƒCƒY
 *‚ð’´‚¦‚½�ê�‡
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_host() ŽQ�Æ�j
 * \pre *dat ‚ªƒAƒNƒZƒX‰Â”\
 * \pre “ü—ÍƒXƒgƒŠ�[ƒ€‚ª hostI/O�i di_select_idevice()ŽQ�Æ�j
 * \pre di_reset_sinpeek() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 *
 * \post *dat‚É“ü—ÍƒXƒgƒŠ�[ƒ€‚Ì�æ“ª‚PƒoƒCƒg‚ªŠi”[‚³‚ê‚é�B
 * \post ƒs�[ƒNƒ|ƒCƒ“ƒ^‚ª‚PƒoƒCƒg‚¸‚ê‚é�B
 */
extern EXPORT int di_sinpeekc( unsigned char *dat );

/**
 * \brief “ü—ÍƒXƒgƒŠ�[ƒ€‚©‚ç•¡�”ƒoƒCƒg“Ç‚Ý�ž‚Þ�B
 *
 * “Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^“à—e‚Í”jŠü‚µ‚È‚¢‚½‚ß�Adi_reset_sinpeek() ‚É‚æ‚è�Ä“Ç
 *‚Ý�ž‚Ý‰Â”\�B
 *
 * \param buf “Ç‚Ý�ž‚Ý�æƒoƒbƒtƒ@
 * \param len “Ç‚Ý�ž‚ÞƒTƒCƒY(Byte)
 *
 * \retval >0 “Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^‚ÌƒoƒCƒg�”
 * \retval 0  EOF�Aƒs�[ƒN‚Å“Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^‚ªƒzƒXƒgƒoƒbƒtƒ@‚ÌƒTƒCƒY‚ð
 *’´‚¦‚½�ê�‡
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_host() ŽQ�Æ�j
 * \pre len ‚ª0ˆÈ�ã
 * \pre len ‚ª1ˆÈ�ã‚Ì�ê�‡‚É buf[0]�`buf[len-1] ‚ªƒAƒNƒZƒX‰Â”\
 * \pre “ü—ÍƒXƒgƒŠ�[ƒ€‚ª hostI/O�i di_select_idevice()ŽQ�Æ�j
 * \pre di_reset_sinpeek() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚Ä�A‚©‚Â‚»‚ÌŒã‚É
 * di_singetc() , di_singet() , di_sinseek() ‚Ì‚¢‚¸‚ê‚àƒR�[ƒ‹‚³‚ê‚Ä‚¢
 *‚È‚¢�B
 *
 * \post buf‚É“ü—ÍƒXƒgƒŠ�[ƒ€‚Ì�æ“ªlenƒoƒCƒg‚ªŠi”[‚³‚ê‚é�B
 * \post ƒs�[ƒNƒ|ƒCƒ“ƒ^‚ª‚PƒoƒCƒg‚¸‚ê‚é�B
 */
extern EXPORT int di_sinpeek( unsigned char *buf, long len );

/**
 * \brief ƒzƒXƒgƒoƒbƒtƒ@‚Ì“Ç‚Ý�ž‚ÝˆÊ’u‚ð�A—LŒøƒf�[ƒ^‚Ì�æ“ª‚ÉˆÚ“®‚·‚é�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_host() ŽQ�Æ�j
 * \pre “ü—ÍƒXƒgƒŠ�[ƒ€‚ª hostI/O�i di_select_idevice()ŽQ�Æ�j
 *
 * \post ƒs�[ƒNƒ|ƒCƒ“ƒ^‚ªƒŠ�[ƒhƒ|ƒCƒ“ƒ^‚ÌˆÊ’u‚ÉˆÚ“®‚·‚é�B
 */
extern EXPORT int di_reset_sinpeek();

/**
 * \brief ƒzƒXƒgƒoƒbƒtƒ@‚É‘Î‚µ‚Ä�AŽw’è‚µ‚½ƒoƒCƒg�”‚¾‚¯“Ç‚ÝŽÌ‚Ä‚é�B
 *
 * \param len “Ç‚Ý�ž‚ÞƒTƒCƒY(Byte)
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_host() ŽQ�Æ�j
 * \pre “ü—ÍƒXƒgƒŠ�[ƒ€‚ª hostI/O�i di_select_idevice()ŽQ�Æ�j
 *
 * \post ƒŠ�[ƒhƒ|ƒCƒ“ƒ^‚Æƒs�[ƒNƒ|ƒCƒ“ƒ^‚ªƒŠ�[ƒhƒ|ƒCƒ“ƒ^‚ÌˆÊ’u‚ÉˆÚ“®‚·‚é�B
 */
extern EXPORT int di_sinseek( long len );

/**
 * \brief “ü—ÍƒXƒgƒŠ�[ƒ€‚ð•Ï�X‚·‚é�B
 *
 * ƒfƒtƒHƒ‹ƒg‚Í DI_HOST_IO
 *
 * \param mode ˆÈ‰º‚ÌŽw’è“ü—ÍƒXƒgƒŠ�[ƒ€
 *   \li DI_HOST_IO   host I/O
 *   \li DI_MEMORY_IO memory buffer I/O
 *   \li DI_FILE_IO   file I/O
 * \param opt mode‚É‚æ‚è“à—e‚ª•Ï‰»‚·‚é
 *  <table>
 *   <tr>
 *    <td><center>mode</center></td><td><center>“à—e</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_HOST_IO</td>
 *    <td>Žg—p‚µ‚È‚¢</td>
 *   </tr>
 *   <tr>
 *    <td>DI_MEMORY_IO</td>
 *    <td>
 *      ƒ�ƒ‚ƒŠ‚©‚ç“Ç‚Ý�ž‚ÞƒR�[ƒ‹ƒoƒbƒNŠÖ�”<br>
 *      Œ^:typedef int (*CALLBACK_MEMREAD)( unsigned char **, int * );<br>
 *      ‘æ‚Pˆø�”: “Ç‚Ý�ž‚Ý�æƒAƒhƒŒƒX<br>
 *      ‘æ‚Qˆø�”: “Ç‚Ý�ž‚ÞƒTƒCƒY<br>
 *    </td>
 *   </tr>
 *   <tr>
 *    <td>DI_FILE_IO</td>
 *    <td>ƒtƒ@ƒCƒ‹ƒ|ƒCƒ“ƒ^(Œ^‚ÍFILE *)</td>
 *   </tr>
 *  </table>
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre mode ‚ªˆø�”‚Ì�à–¾‚É‚ ‚é’l‚Ì‚¢‚¸‚ê‚©
 * \pre opt ‚ª—LŒøƒpƒ‰ƒ��[ƒ^�iˆø�”‚Ì�à–¾ŽQ�Æ�j
 *
 * \post di_singetc() , di_singet() ‚Ì“Ç‚Ý�ž‚Ý�æ‚ª mode ‚É•Ï�X‚³‚ê‚é�B
 */
extern EXPORT int di_select_idevice( int mode, void *opt );

/**
 * \brief �§Œä‚ð‘¼ƒvƒ�ƒZƒX‚ÖˆÚ�s‚·‚é
 *
 * –{ŠÖ�”�I—¹Œã‚ÍI/O‚ª�Ø‚è—£‚³‚ê‚½�ó‘Ô‚Æ‚È‚é‚½‚ß,
 *�Ä“xƒoƒbƒtƒ@‚©‚ç‚Ì“Ç‚Ý�ž‚Ý‚ð�s‚È‚¤�ê�‡‚Ídi_open_host()‚ðƒR�[ƒ‹‚·‚é
 *‚±‚Æ�B
 *
 * \return �Ä“x�§Œä‚ªˆÚ�s‚µ‚Ä‚«‚½Žž‚ÌƒVƒXƒeƒ€‚©‚ç‚Ì—v‹�
 * \retval DI_REQ_EXIT    �I—¹—v‹�
 * \retval DI_REQ_PROCESS ’Ê�í�ˆ—�—v‹�
 * \retval DI_REQ_CANCEL  ƒWƒ‡ƒuƒLƒƒƒ“ƒZƒ‹—v‹�
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 *
 * \post •Ô‚è’l‚ÉƒVƒXƒeƒ€‚©‚ç‚Ì—v‹�‚ªŠi”[‚³‚ê‚é�B
 * \post ƒzƒXƒgƒoƒbƒtƒ@‚ªƒNƒ��[ƒY�ó‘Ô‚Æ‚È‚é�B
 */
extern EXPORT int di_trans_process();

/**
 * \brief ƒvƒŠƒ“ƒ^OS‚Öƒ�ƒbƒZ�[ƒW‚ð’Ê’m‚·‚é�B
 *
 * \param msg ’Ê’m‚·‚éƒ�ƒbƒZ�[ƒW
 *  \li DI_NOTIFYMSG_JOBEND    ƒWƒ‡ƒu‚Ì�I—¹
 *  \li DI_NOTIFYMSG_STATE     �ó‘Ô‚Ì’Ê’m
 *  \li DI_NOTIFYMSG_STRING    •¶Žš—ñ‚É‚æ‚é�ó‘Ô‚Ì’Ê’m
 *  \li DI_NOTIFYMSG_ERRFORCE  ƒGƒ‰�[‚Ì‹­�§’Ê’m
 *  \li DI_NOTIFYMSG_START     –¾Ž¦“I‚È‹N“®’Ê’m�Bdi_init() ‚ÅŽw’è‚·‚é
 *ƒCƒ“ƒ^ƒvƒŠƒ^ ID ‚ª[ DI_INTERP_PS , DI_INTERP_PCL ] ‚Ì�ê�‡‚É•K—v�B
 *  \li DI_NOTIFYMSG_FONTCOUNT ƒtƒHƒ“ƒgƒJƒEƒ“ƒg‚Ì�I—¹’Ê’m
 *  \li DI_NOTIFYMSG_PAUSE ˆêŽž’âŽ~—v‹�‚É‘Î‚·‚é‰ž“š�iŠ®—¹�A‚à‚µ‚­‚ÍˆêŽž’âŽ~‚Å‚«‚È‚¢�j’Ê’m
 *  \li DI_NOTIFYMSG_RESUME �ˆ—��ÄŠJ’Ê’m
 * \param opt msg‚É‚æ‚è“à—e‚ª•Ï‰»‚·‚é�B
 *  <table>
 *   <tr>
 *    <td><center>msg</center></td><td><center>“à—e</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_JOBEND</td>
 *    <td>Žg—p‚µ‚È‚¢</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_STATE</td>
 *    <td>’Ê’m‚·‚é�ó‘Ô<br>
 *        DI_INTERP_STATE_IDLE       �iƒf�[ƒ^‘Ò‚¿’†�j<br>
 *        DI_INTERP_STATE_PROCESSING �iƒf�[ƒ^�ˆ—�’†�j<br>
 *        DI_INTERP_STATE_WAITING    �iƒf�[ƒ^�ˆ—�’†‚©‚Âƒf�[ƒ^‘Ò‚¿�j<br>
 *        DI_INTERP_STATE_FLUSHING   �iƒf�[ƒ^ƒLƒƒƒ“ƒZƒ‹’†�j<br>
 *    </td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_STRING</td>
 *    <td>•¶Žš—ñ‚Ì�æ“ªƒAƒhƒŒƒX</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_ERRFORCE</td>
 *    <td>ƒGƒ‰�[ƒR�[ƒh(�Ú�×‚ÍGPSŽd—l�‘)</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_START</td>
 *    <td>ƒCƒ“ƒ^ƒvƒŠƒ^ID�B di_setinfo_t ŽQ�Æ</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_FONTCOUNT</td>
 *    <td>Žg—p‚µ‚È‚¢</td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_PAUSE</td>
 *    <td>’Ê’m‚·‚é�ó‘Ô<br>
 *        DI_INTERP_PAUSE_OK	�iˆêŽž’âŽ~‚µ‚½Žž�j<br>
 *        DI_INTERP_PAUSE_NG	�iˆêŽž’âŽ~‚Å‚«‚È‚¢�j<br>
 *    </td>
 *   </tr>
 *   <tr>
 *    <td>DI_NOTIFYMSG_RESUME</td>
 *    <td>Žg—p‚µ‚È‚¢</td>
 *   </tr>
 *  </table>
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre msg ‚ªˆø�”‚Ì�à–¾‚É‚ ‚é’l‚Ì‚¢‚¸‚ê‚©
 *
 * \post msg ‚ª DI_NOTIFYMSG_JOBEND ‚È‚ç�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ
 *‚ªƒAƒCƒhƒ‹�ó‘Ô‚É‚È‚Á‚½‚Æ”»’f‚·‚é�B
 * \post msg ‚ª DI_NOTIFYMSG_STATE ‚È‚ç�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚ª
 *opt‚Ì�ó‘Ô‚Æ”»’f‚·‚é�B
 * \post msg ‚ª DI_NOTIFYMSG_ERRFORCE ‚È‚ç�Aƒpƒlƒ‹‚Ö‚ÌƒGƒ‰�[•\Ž¦‚ÆƒGƒ‰
 *�[ƒ�ƒMƒ“ƒO”½‰f‚ð�s‚¤�B
 * \post msg ‚ª DI_NOTIFYMSG_STRING ‚È‚ç�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ
 *‚ª•¶Žš—ñŽw’è‚Ì�ó‘Ô‚É‚È‚Á‚½‚Æ”»’f‚·‚é�B
 * \post msg ‚ª DI_NOTIFYMSG_START ‚È‚ç�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚ª
 *‹N“®‚³‚ê‚½‚Æ”»’f‚·‚é�B
 * \post msg ‚ª DI_NOTIFYMSG_FINISH_FONTCOUNT ‚È‚ç�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒtƒH
 *ƒ“ƒgƒJƒEƒ“ƒg‚ª�I—¹‚³‚ê‚½‚Æ”»’f‚·‚é�B
 * \post msg ‚ª DI_NOTIFYMSG_PAUSE ‚È‚ç�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚ª
 *opt‚Ì�ó‘Ô‚Æ”»’f‚·‚é�B
 * \post msg ‚ª DI_NOTIFYMSG_RESUME ‚È‚ç�AƒvƒŠƒ“ƒ^‚n‚r‚ÍƒvƒŠƒ“ƒ^ƒAƒvƒŠ‚ª
 *�ˆ—��ÄŠJ‚³‚ê‚½‚Æ”»’f‚·‚é�B
 */
extern EXPORT int di_notify_msg( int msg, long opt );

/**
 * \brief Žw’è‚µ‚½—pŽ†ƒTƒCƒY‚ðƒvƒŠƒ“ƒ^‚ªƒTƒ|�[ƒg‚µ‚Ä‚¢‚é‚©–â‚¢�‡‚í‚¹‚é�B
 *
 * \param paper_id —pŽ†ƒTƒCƒYID(GPS’è‹`)
 *
 * \retval  1 ƒTƒ|�[ƒg‚³‚ê‚Ä‚¢‚é
 * \retval  0 ƒTƒ|�[ƒg‚³‚ê‚Ä‚¢‚È‚¢
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 *
 * \post •Ô‚è’l‚ª‚P‚È‚ç�A‚»‚Ì—pŽ†ƒTƒCƒY‚Å�o—Í‰Â”\
 */
extern EXPORT int di_query_supportpaper( int paper_id );

/**
 * \brief ƒWƒ‡ƒu‚É�Ý’è‚³‚ê‚Ä‚¢‚éƒIƒvƒVƒ‡ƒ“•¶Žš—ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param str ƒIƒvƒVƒ‡ƒ“•¶Žš—ñ‚Ì�æ“ªƒAƒhƒŒƒX
 *
 * \retval  0 �¬Œ÷
 * \retval -1 Ž¸”s(Žw’è‚³‚ê‚½ƒIƒvƒVƒ‡ƒ“•¶Žš—ñ‚ð“r’†‚Ü‚Å‚µ‚©Žæ“¾‚Å‚«‚È
 *‚©‚Á‚½)�Bstr‚É‚Í“r’†‚Ü‚Å‚Ì•¶Žš—ñ‚ÌƒAƒhƒŒƒX‚ð•Ô‚·
 * \retval -2 Ž¸”s�AƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *str ‚ªƒAƒNƒZƒX‰Â”\�B
 * \pre ƒvƒŠƒ“ƒ^OS‚æ‚è’Ê�í�ˆ—�—v‹�‚ª—ˆ‚Ä‚¢‚é�B
 *
 * \post *str‚ÉƒIƒvƒVƒ‡ƒ“•¶Žš—ñ‚Ì�æ“ªƒAƒhƒŒƒX‚ªŠi”[‚³‚ê‚é�B
 */
extern EXPORT int di_get_optstr( char **str );

/**
 * \brief ƒGƒ‰�[ƒvƒŠƒ“ƒg—p‚Ìƒoƒbƒtƒ@‚ÌƒAƒhƒŒƒXŽæ“¾
 *
 * \param buffer �¡‚Ü‚Å‚Ìƒoƒbƒtƒ@‚Ì�æ“ªƒAƒhƒŒƒX
 * \param size   Žæ“¾‚µ‚½ƒoƒbƒtƒ@‚ÌƒTƒCƒY
 *
 * \retval Žæ“¾‚µ‚½ƒoƒbƒtƒ@‚Ì�æ“ªƒAƒhƒŒƒX �³�í�I—¹
 * \retval NULL  ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *buffer ‚ªƒAƒNƒZƒX‰Â”\�B
 * \pre *size ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post •Ô‚è’l‚ÉŽæ“¾‚µ‚½ƒoƒbƒtƒ@‚Ì�æ“ªƒAƒhƒŒƒX‚ª•Ô‚Á‚Ä‚­‚é�B
 */
extern EXPORT char *di_get_epbuffer( char *buffer, int *size );

/**
 * \brief Žw’è‚µ‚½—pŽ†‚ÌƒTƒCƒY‚ðŽæ“¾‚·‚é
 *
 * \param code   —pŽ†ƒR�[ƒh
 * \param width  —pŽ†•��i0.1mm’PˆÊ�j
 * \param length —pŽ†’·‚³�i0.1mm’PˆÊ�j
 *
 * \retval  1 ƒTƒ|�[ƒg‚µ‚Ä‚¢‚é
 * \retval  0 ƒTƒ|�[ƒg‚µ‚Ä‚¢‚È‚¢
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 *
 * \post *width ‚ª—pŽ†ƒR�[ƒh code ‚Ì—pŽ†•�‚Æ‚È‚é
 * \post *length ‚ª—pŽ†ƒR�[ƒh code ‚Ì—pŽ†’·‚³‚Æ‚È‚é
 */
extern EXPORT int di_get_papersize( unsigned char code,
									unsigned int *width,
									unsigned int *length );

/**
 * \brief �o—ÍƒzƒXƒgƒoƒbƒtƒ@‚ðƒI�[ƒvƒ“‚·‚é�B
 *
 * ƒf�[ƒ^�‘‚«�ž‚Ý‘O‚É•K‚¸–{ŠÖ�”‚ðƒR�[ƒ‹‚·‚é‚±‚Æ
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒVƒXƒeƒ€‚©‚ç’Ê�í�ˆ—�—v‹�‚ª—ˆ‚Ä‚¢‚é�i di_get_request() �A
 * di_trans_process() ŽQ�Æ�j
 *
 * \post di_close_ohost() �A‚à‚µ‚­‚Í di_trans_process() ‚ðƒR�[ƒ‹‚·‚é‚Ü
 *‚ÅˆÈ‰º‚ÌI/F‚ªŽg—p‰Â”\�B
 *  \li di_soutputc()
 *  \li di_soutput()
 *  \li di_soutflush()
 */
extern EXPORT int di_open_ohost();

/**
 * \brief di_open_ohost() ‚É‚æ‚èƒI�[ƒvƒ“‚³‚ê‚½ƒzƒXƒgƒoƒbƒtƒ@‚ðƒNƒ��[ƒY
 *‚·‚é�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 *
 * \post di_open_ohost() ‚ðƒR�[ƒ‹‚·‚é‚Ü‚ÅˆÈ‰º‚ÌI/F‚ªŽg—p•s‰Â”\�B
 *  \li di_soutputc()
 *  \li di_soutput()
 *  \li di_soutflush()
 */
extern EXPORT int di_close_ohost();

/**
 * \brief �o—ÍƒXƒgƒŠ�[ƒ€‚Ö‚PƒoƒCƒg�‘‚«�ž‚Þ�B
 *
 * ‘—�Mƒoƒbƒtƒ@‚É�‘‚«�ž‚Ý—Ìˆæ‚ª‚È‚¢�ê�‡‚É‚Í�A‘—�Mƒf�[ƒ^‚ð�‘‚«�ž‚Þ—Ìˆæ
 *‚ª‚Å‚«‚é‚Ü‚Åƒuƒ�ƒbƒN‚·‚é�B
 *
 * \param dat �‘‚«�ž‚Þƒf�[ƒ^‚Ì’l
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[�A�‘‚«�ž‚ÝŽ¸”s
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre �o—ÍƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_ohost() ŽQ�Æ�j
 *
 * \post ‘—�Mƒoƒbƒtƒ@‚É dat ‚ª�‘‚«�ž‚Ü‚ê‚é�B
 */
extern EXPORT int di_soutputc( unsigned char dat );

/**
 * \brief �o—ÍƒXƒgƒŠ�[ƒ€‚Ö•¡�”ƒoƒCƒg�‘‚«�ž‚Þ�B
 *
 * \param buf �‘‚«�ž‚Þƒf�[ƒ^
 * \param len “Ç‚Ý�ž‚ÞƒTƒCƒY(Byte)
 * \param flag �‘‚«�ž‚Ý•û–@
 *  <table>
 *   <tr>
 *    <td><center>’l</center></td><td><center>“à—e</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_HOST_BLOCK</td>
 *    <td>ƒmƒ“ƒuƒ�ƒbƒNŽw’è‚È‚µ�B‘—�Mƒoƒbƒtƒ@‚É�‘‚«�ž‚Ý—Ìˆæ‚ª‚È‚¢�ê�‡‚É
 *        ‚Í�A‘—�Mƒf�[ƒ^‚ð�‘‚«�ž‚Þ—Ìˆæ‚ª‚Å‚«‚é‚Ü‚Åƒuƒ�ƒbƒN‚·‚é�B</td>
 *   </tr>
 *   <tr>
 *    <td>DI_HOST_NONBLOCK</td>
 *    <td> ƒmƒ“ƒuƒ�ƒbƒNŽw’è‚ ‚è�B‘—�Mƒoƒbƒtƒ@‚Ìƒuƒ�ƒbƒN‚Í‚µ‚È‚¢�iƒoƒb
 *        ƒtƒ@‚ªˆì‚ê‚é‚Ü‚Å�‘‚«�ž‚Ý�A�‘‚«�ž‚ß‚½ƒoƒCƒg�”‚ð–ß‚è’l‚Æ‚µ‚Ä•Ô
 *        ‚·�j�B</td>
 *   </tr>
 *  </table>
 *
 * \retval >=0 �‘‚«�ž‚ñ‚¾ƒf�[ƒ^‚ÌƒoƒCƒg�”
 * \retval  -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre �o—ÍƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_ohost() ŽQ�Æ�j
 * \pre len ‚ª0ˆÈ�ã
 * \pre len ‚ª1ˆÈ�ã‚Ì�ê�‡‚É buf[0]�`buf[len-1] ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post buf ‚Ì“à—e‚ª�o—ÍƒXƒgƒŠ�[ƒ€‚É�‘‚«�ž‚Ü‚ê‚é
 */
extern EXPORT int di_soutput( unsigned char *buf, long len, int flag );

/**
 * \brief ‘—�Mƒoƒbƒtƒ@’†‚É�‘‚«�ž‚Ü‚ê‚½‚ª�A‚Ü‚¾‘—�M‚³‚ê‚Ä‚¢‚È‚¢ƒf�[ƒ^‚ð
 *ƒzƒXƒg‚É‘—�M‚·‚é�B
 *
 * di_soutputc() ‚ ‚é‚¢‚Í di_soutput() ‚É‚Äˆê‹æ�Ø‚è‚Ì‘—�Mƒf�[ƒ^‚ð‘—�M
 *ƒoƒbƒtƒ@‚É�‘‚«�ž‚ñ‚¾Œã�A•K‚¸�A‚±‚ÌŠÖ�”‚ðŒÄ‚Ô‚±‚Æ�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒVƒXƒeƒ€‚©‚ç’Ê�í�ˆ—�—v‹�‚ª—ˆ‚Ä‚¢‚é�i di_get_request() ,
 * di_trans_process() ŽQ�Æ�j
 *
 * \post ‘—�Mƒoƒbƒtƒ@‚Ìƒf�[ƒ^‚ª‘S‚Ä‘—�M‚³‚ê‚é�B
 */
extern EXPORT int di_soutflush();

/**
 * \brief “ü—ÍƒXƒgƒŠ�[ƒ€‚Ì—LŒøƒoƒCƒg�”‚ðŽæ“¾‚·‚é�B
 *
 * \param len “ü—ÍƒXƒgƒŠ�[ƒ€ƒoƒbƒtƒ@’†‚Ì—LŒø‚Èƒf�[ƒ^‚ÌƒoƒCƒg�”
 *
 * \retval  1 �³�í�I—¹(EOF‚ªƒoƒbƒtƒ@‚ÉŠÜ‚Ü‚ê‚Ä‚¢‚é)
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre �o—ÍƒzƒXƒg‚ªƒI�[ƒvƒ“‚³‚ê‚Ä‚¢‚é�i di_open_ohost() ŽQ�Æ�j
 * \pre *len ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *len‚É“ü—ÍƒXƒgƒŠ�[ƒ€‚Ì—LŒøƒoƒCƒg�”‚ªŠi”[‚³‚ê‚é�B
 */
extern EXPORT int di_sinavail( long *len );

/**
 * \brief Œ»�ÝŽw’è‚³‚ê‚Ä‚¢‚é—D�æ‹‹Ž†ƒgƒŒƒC�î•ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param tray_id —D�æ‹‹Ž†ƒgƒŒƒC�î•ñ‚ÉŽw’è‚³‚ê‚Ä‚¢‚éƒgƒŒƒCID�B
 * di_onetrayinfo_t ŽQ�Æ�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *tray_id ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post —D�æƒgƒŒƒC‚Ì ID ‚ª *tray_id ‚ÉŠi”[‚³‚ê‚é�B
 */
extern EXPORT int di_get_deftray( int *tray_id );

/**
 * \brief Œ»�ÝŽw’è‚³‚ê‚Ä‚¢‚é—D�æ”rŽ†ƒrƒ“�î•ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param bin_id —D�æ”rŽ†ƒrƒ“�î•ñ‚ÉŽw’è‚³‚ê‚Ä‚¢‚éƒrƒ“ID�B
 * di_onebininfo_t ŽQ�Æ�B
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *bin_id ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post —D�æ”rŽ†ƒrƒ“‚ÌID‚ª*bin_id‚ÉŠi”[‚³‚ê‚é
 */
extern EXPORT int di_get_defbin( int *bin_id );

/**
 * \brief ”rŽ†ƒrƒ“�î•ñ‚ÌŽæ“¾‚ð�s‚¤�B
 *
 * \param bininfo ”rŽ†ƒrƒ“�î•ñ
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *bininfo ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *bininfo ‚Ì’l‚Æ”rŽ†ƒrƒ“‚Ì�î•ñ‚ªˆê’v‚·‚é�B
 */
extern EXPORT int di_get_bininfo( di_bininfo_t *bininfo );

/**
 * \brief ƒvƒŠƒ“ƒ^‚ÌƒXƒe�[ƒ^ƒX�î•ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param status ƒXƒe�[ƒ^ƒX�î•ñ
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *status ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *status ‚Ì’l‚ÆƒvƒŠƒ“ƒ^‚ÌƒXƒe�[ƒ^ƒX�î•ñ‚ªˆê’v‚·‚é�B
 */
extern EXPORT int di_get_status( di_status_t *status );

/**
 * \brief ƒg�[ƒ^ƒ‹ƒJƒEƒ“ƒ^�[‚Ì’l‚ðŽæ“¾‚·‚é�B
 *
 * \param cnt ƒg�[ƒ^ƒ‹ƒJƒEƒ“ƒ^�[‚Ì’l
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *tray_id ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post cnt ‚Ì’l‚Æƒg�[ƒ^ƒ‹ƒJƒEƒ“ƒ^�[‚Ì’l‚ªˆê’v‚·‚é�B
 */
extern EXPORT int di_get_totalcounter( long *cnt );

/**
 * \brief EhterTalk ƒpƒ‰ƒ��[ƒ^‚ðŽæ“¾‚·‚é�B
 *
 * \param info EtherTalk ƒpƒ‰ƒ��[ƒ^
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post info ‚Ì’l‚ÆEtherTalkƒpƒ‰ƒ��[ƒ^‚Ì’l‚ªˆê’v‚·‚é�B
 */
extern EXPORT int di_get_ethertalkinfo( di_ethertalk_info_t *info );

/**
 * \brief EhterTalk ƒpƒ‰ƒ��[ƒ^‚ð�Ý’è‚·‚é�B
 *
 * \param info EtherTalk ƒpƒ‰ƒ��[ƒ^
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post di_get_ethertalkinfo() ‚ÅŽæ“¾‚µ‚½Ethertalkƒpƒ‰ƒ��[ƒ^‚ª *info ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_set_ethertalkinfo( di_ethertalk_info_t *info );

/**
 * \brief ƒ†�[ƒU�[ƒWƒ‡ƒu�î•ñ‚ð�Ý’è‚·‚é�B
 *
 * \param job_id ƒ†�[ƒU�[ƒWƒ‡ƒuID
 * \param info   ƒ†�[ƒU�[ƒWƒ‡ƒu�î•ñ
 *
 * \retval 0     �³�í�I—¹
 * \retval -1    ƒGƒ‰�[
 * \retval -2    Žw’è‚µ‚½ƒpƒ‰ƒ��[ƒ^‚ðƒTƒ|�[ƒg‚µ‚Ä‚¢‚È‚¢
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒVƒXƒeƒ€‚©‚ç’Ê�í�ˆ—�—v‹�‚ª—ˆ‚Ä‚¢‚é
 * ( di_get_request() , di_trans_process )ŽQ�Æ
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post ƒ†�[ƒU�[ƒWƒ‡ƒu�î•ñ‚ªƒVƒXƒeƒ€‚É�Ý’è‚³‚ê‚Ä‚¢‚é�B
 */
extern EXPORT int di_set_ujobinfo( int job_id, di_ujob_info_t *info );

/**
 * \brief ƒ†�[ƒU�[ƒWƒ‡ƒu�î•ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param job_id ƒ†�[ƒU�[ƒWƒ‡ƒuID
 * \param info   ƒ†�[ƒU�[ƒWƒ‡ƒu�î•ñ
 *
 * \retval 0     �³�í�I—¹
 * \retval -1    ƒGƒ‰�[
 * \retval -2    Žw’è‚µ‚½ƒpƒ‰ƒ��[ƒ^‚ðƒTƒ|�[ƒg‚µ‚Ä‚¢‚È‚¢
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre ƒVƒXƒeƒ€‚©‚ç’Ê�í�ˆ—�—v‹�‚ª—ˆ‚Ä‚¢‚é
 * ( di_get_request() , di_trans_process )ŽQ�Æ
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *info‚Ì‹¤—p‘Ìup‚ÉŒ»�Ý�Ý’è‚³‚ê‚Ä‚¢‚é’l‚ª“ü‚é�B
 * \post �Ý’è‚³‚ê‚Ä‚¢‚È‚¢�ê�‡‚É‚Íinfo->flag‚É‚ÄŽw’è‚³‚ê‚½ƒtƒ‰ƒO‚ªƒŠƒZƒbƒg‚³‚ê‚é�B
 */
extern EXPORT int di_get_ujobinfo( int job_id, di_ujob_info_t *info );

/**
 * \brief ƒrƒbƒgƒXƒCƒbƒ`‚Ì’l‚ðŽæ“¾‚·‚é�B
 *
 * \param no  ƒrƒbƒgƒXƒCƒbƒ`‚Ì”Ô�†
 * \param val ƒrƒbƒgƒXƒCƒbƒ`‚Ì’l
 *
 * \retval 0     �³�í�I—¹
 * \retval 0ˆÈŠO ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *val ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post no”Ô–Ú‚ÌƒrƒbƒgƒXƒCƒbƒ`‚Ì’l‚ª *val ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_bitswinfo( int no, int *val );

/**
 * ŠeŽíƒfƒBƒXƒN�î•ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param type ƒfƒBƒXƒN‚ÌŽí—Þ
 *  <table>
 *   <tr>
 *    <td><center>’l</center></td><td><center>“à—e</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_HDD_DOWNLOAD</td>
 *    <td>ƒtƒ@ƒCƒ‹ƒ_ƒEƒ“ƒ��[ƒh—pƒn�[ƒhƒfƒBƒXƒN</td>
 *   </tr>
 *   <tr>
 *    <td>DI_HDD_SPOOL</td>
 *    <td>ƒXƒv�[ƒ‹—pƒn�[ƒhƒfƒBƒXƒN</td>
 *   </tr>
 *   <tr>
 *    <td>DI_RAM_DOWNLOAD</td>
 *    <td>ƒtƒ@ƒCƒ‹ƒ_ƒEƒ“ƒ��[ƒh—pRAMƒfƒBƒXƒN</td>
 *   </tr>
 *   <tr>
 *    <td>DI_RAM_SPOOL</td>
 *    <td>ƒXƒv�[ƒ‹—pRAMƒfƒBƒXƒN</td>
 *   </tr>
 *  </table>
 * \param info ƒfƒBƒXƒN‚Ì�î•ñ
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 type‚ÌƒfƒBƒXƒN‚ª“‹�Ú‚³‚ê‚Ä‚¢‚È‚¢
 * \retval -3 Žó•t‹‘”Û�iŒÄ‚Ñ�o‚µ‚Ì“ñ�d‰»‚ª”­�¶‚µ‚½�ê�‡�j
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre type ‚ªˆø�”‚Ì�à–¾‚É‚ ‚é’l‚Ì‚¢‚¸‚ê‚©
 * \pre *val ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post type ‚ÅŽw’è‚³‚ê‚½ƒfƒBƒXƒN�î•ñ’l‚ª *info ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_diskinfo( int type, di_diskinfo_t *info );

/**
 * \brief ƒXƒgƒŒ�[ƒWƒfƒoƒCƒX‚Öƒtƒ@ƒCƒ‹‚ð•Û‘¶‚·‚é�B
 *
 * \param type ƒXƒgƒŒ�[ƒW‚ÌŽí—Þ
 *  <table>
 *   <tr>
 *    <td><center>’l</center></td><td><center>“à—e</center></td>
 *   </tr>
 *   <tr>
 *    <td>DI_STORAGE_NVRAM</td>
 *    <td>NVRAM</td>
 *   </tr>
 *  </table>
 * \param fname ‚S•¶Žš‚Ìƒtƒ@ƒCƒ‹–¼
 * \param data  �‘‚«�ž‚Þƒf�[ƒ^”z—ñ‚Ì�æ“ªƒAƒhƒŒƒX
 * \param size  data‚Ì”z—ñ‚Ì’·‚³
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 —e—Ê•s‘«‚É‚æ‚éŽ¸”s
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre type ‚ªˆø�”‚Ì�à–¾‚É‚ ‚é’l‚Ì‚¢‚¸‚ê‚©
 * \pre *fname ‚ÅŽw’è‚·‚éƒtƒ@ƒCƒ‹–¼‚ª‚S•¶Žš
 * \pre data[0]�`data[size-1] ‚Ü‚Å‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post ƒXƒgƒŒ�[ƒW‚É fname ‚Æ‚¢‚¤ƒtƒ@ƒCƒ‹‚Å data ‚Ì“à—e‚ª size •ª�‘‚«
 *�ž‚Ü‚ê‚é�B
 */
extern EXPORT int di_write_storage( int type, char *fname,
									unsigned char *data, long size );

/**
 * \brief ƒXƒgƒŒ�[ƒWƒfƒoƒCƒX‚É�‘‚«�ž‚Ü‚ê‚Ä‚¢‚éƒtƒ@ƒCƒ‹‚©‚çƒf�[ƒ^‚ð“Ç‚Ý
 *�ž‚Þ�B
 *
 * \param type    ƒXƒgƒŒ�[ƒW‚ÌŽí—Þ(“à—e‚Í di_write_storage() ‚Æ“¯‚¶)
 * \param fname   ‚S•¶Žš‚Ìƒtƒ@ƒCƒ‹–¼
 * \param data    “Ç‚Ý�ž‚ñ‚¾ƒf�[ƒ^‚ðŠi”[‚·‚é”z—ñ‚Ì�æ“ªƒAƒhƒŒƒX
 * \param size    data‚Ì”z—ñ‚Ì’·‚³
 * \param data_size ŽÀ�Û‚É“Ç‚ñ‚¾ƒf�[ƒ^‚ÌƒTƒCƒY
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 fname ‚Æ‚¢‚¤ƒtƒ@ƒCƒ‹‚ª‘¶�Ý‚µ‚È‚¢
 * \retval -3 data[size]‚æ‚è‘å‚«‚¢ƒtƒ@ƒCƒ‹‚¾‚Á‚½‚Ì‚Å�ÅŒã‚Ü‚Å“Ç‚Ý�ž‚ß‚È
 *‚©‚Á‚½�B‚±‚Ì�ê�‡‚Å‚àsize•ª‚¾‚¯‚Ídata[]‚É“Ç‚Ý�ž‚Ü‚ê�A*data_size‚ÉƒRƒs
 *�[‚µ‚½ƒf�[ƒ^‚ÌƒoƒCƒg�”(=size)‚ª•Ô‚é�B
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre type ‚ªˆø�”‚Ì�à–¾‚É‚ ‚é’l‚Ì‚¢‚¸‚ê‚©
 * \pre *fname ‚ÅŽw’è‚·‚éƒtƒ@ƒCƒ‹–¼‚ª‚S•¶Žš
 * \pre data[0]�`data[size-1] ‚Ü‚Å‚ªƒAƒNƒZƒX‰Â”\
 * \pre *data_size ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post ƒXƒgƒŒ�[ƒW‚É‚ ‚é fname ‚Æ‚¢‚¤ƒtƒ@ƒCƒ‹‚©‚ç size •ª‚Ìƒf�[ƒ^‚ª
 *data‚É“Ç‚Ý�ž‚Ü‚ê‚é�B
 */
extern EXPORT int di_read_storage( int type, char *fname, unsigned char *data,
								   long size, long *data_size );

/**
 * \brief ƒXƒgƒŒ�[ƒWƒfƒoƒCƒX‚É�‘‚«�ž‚Ü‚ê‚Ä‚¢‚éƒtƒ@ƒCƒ‹‚ð�í�œ‚·‚é�B
 *
 * \param type  ƒXƒgƒŒ�[ƒW‚ÌŽí—Þ(“à—e‚Í di_write_storage() ‚Æ“¯‚¶)
 * \param fname ‚S•¶Žš‚Ìƒtƒ@ƒCƒ‹–¼
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre type ‚ªˆø�”‚Ì�à–¾‚É‚ ‚é’l‚Ì‚¢‚¸‚ê‚©
 * \pre *fname ‚ÅŽw’è‚·‚éƒtƒ@ƒCƒ‹–¼‚ª‚S•¶Žš
 *
 * \post ƒXƒgƒŒ�[ƒW‚É fname ‚Æ‚¢‚¤ƒtƒ@ƒCƒ‹‚ª‘¶�Ý‚µ‚È‚¢�B
 */
extern EXPORT int di_delete_storage( int type, char *fname );

/**
 * \brief �ðŒ�‚É�‡’v‚·‚éŽw’è—pŽ†‚ð—v‹�‚·‚é
 *
 * \param plotid  ƒvƒ�ƒbƒ^ID
 * \param psize   —pŽ†ƒTƒCƒYID
 * \param nodir   —pŽ†•ûŒü
 *  <table>
 *   <tr>
 *    <td><center>’l</center></td><td><center>“à—e</center></td>
 *   </tr>
 *   <tr>
 *    <td>0</td>
 *    <td>—pŽ†ƒTƒCƒY‚ÅŽw’è‚µ‚½•ûŒü‚Ì‚Ý�B</td>
 *   </tr>
 *   <tr>
 *    <td>1</td>
 *    <td>—pŽ†ƒTƒCƒY‚ªˆÙ‚È‚é•ûŒü‚Å‚à‚n‚j�B</td>
 *   </tr>
 *  </table>
 * \param ptype   Ž†Ží
 * \param trayid  ƒgƒŒƒCID
 * \param req     —v‹�Œ‹‰Ê
 *
 * \retval  4 ƒTƒuƒy�[ƒp�[ƒTƒCƒY‚ª—LŒø‚Ì‚Æ‚«�A—v‹�—pŽ†ƒTƒCƒY‚Æ—ÞŽ—‚µ‚½
 *ƒTƒCƒY‚Ì—pŽ†‚ª�oŒ»‚µ‚½
 * \retval  3 ƒGƒ‰�[‰æ–Ê‚É‚¨‚¯‚éƒ†�[ƒU�[‚Ì‘€�ì‚É‚æ‚è�A‹­�§ˆó�ü‚ª‘I‘ð‚³
 *‚ê‚½
 * \retval  2 ƒGƒ‰�[‰æ–Ê‚É‚¨‚¯‚éƒ†�[ƒU�[‚Ì‘€�ì‚É‚æ‚è�AƒWƒ‡ƒuƒLƒƒƒ“ƒZƒ‹
 *‚ª‘I‘ð‚³‚ê‚½
 * \retval  1 ƒGƒ‰�[ƒXƒLƒbƒv‚ª”­�¶‚µ‚½
 * \retval  0 �ðŒ�‚Éˆê’v‚·‚é—pŽ†‚ª�oŒ»‚µ‚½
 * \retval -1 ƒGƒ‰�[
 * \retval -2 ƒrƒW�[�iƒI�[ƒvƒ“�Ï‚Ýƒy�[ƒW‚Ìˆó�ü‚ª�I—¹‚µ‚Ä‚¢‚È‚¢�j
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *req ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post —v‹�Œ‹‰Ê‚ª *req ‚ÉŠi”[‚³‚ê‚é
 */
extern EXPORT int di_request_paper(int plotid, int psize, int nodir, int ptype,
								   int trayid, di_res_reqpaper_t *req);

/**
 * \brief ŠÂ‹«•Ï�”‚ÌƒfƒtƒHƒ‹ƒg’l‚ðŽæ“¾‚·‚é�B
 *
 * \param table_name  ŠÂ‹«•Ï�”ƒe�[ƒuƒ‹–¼
 * \param id          ŠÂ‹«•Ï�”ID
 * \param val         “¾‚ç‚ê‚½ŠÂ‹«•Ï�”‚Ì’l
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 table_name‚ª‘¶�Ý‚µ‚È‚¢
 * \retval -3 Žw’è‚µ‚½ŠÂ‹«•Ï�”‚ª‚È‚¢
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre table_name ‚Æ‚¢‚¤ƒe�[ƒuƒ‹‚ª‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�Atable_name ‚É‘¶�Ý‚·‚é�B
 * \pre *val ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *val ‚ªŠÂ‹«•Ï�” id ‚ÌƒfƒtƒHƒ‹ƒg’l‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_defenvvalue(char *table_name, long id, long *val);

/**
 * \brief ŠÂ‹«•Ï�”‚ÌƒfƒtƒHƒ‹ƒg’l‚ÌƒZƒbƒg
 *
 * \param table_name  ŠÂ‹«•Ï�”ƒe�[ƒuƒ‹–¼
 * \param id          ŠÂ‹«•Ï�”ID
 * \param  val        ƒZƒbƒg‚·‚éŠÂ‹«•Ï�”‚Ì’l
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 table_name‚ª‘¶�Ý‚µ‚È‚¢
 * \retval -3 Žw’è‚µ‚½ŠÂ‹«•Ï�”‚ª‚È‚¢
 * \retval -4 ƒŠ�[ƒhƒIƒ“ƒŠ�[‚ÌŠÂ‹«•Ï�”
 * \retval -5 val‚ª�Ý’è•s‰Â”\‚È’l
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre table_name ‚Æ‚¢‚¤ƒe�[ƒuƒ‹‚ª‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�Atable_name ‚É‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�Atable_name ‚É�Ý’è‰Â”\‚Å‚ ‚é�B
 *
 * \post val ‚ªŠÂ‹«•Ï�” id ‚ÌƒfƒtƒHƒ‹ƒg’l‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_set_defenvvalue(char *table_name, long id, long val);

/**
 * \brief ŠÂ‹«•Ï�”�î•ñ‚ÌŽæ“¾
 *
 * \param table_name  ŠÂ‹«•Ï�”ƒe�[ƒuƒ‹–¼
 * \param id          ŠÂ‹«•Ï�”ID
 * \param info        ŠÂ‹«•Ï�”‚Ì�î•ñ
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 table_name‚ª‘¶�Ý‚µ‚È‚¢
 * \retval -3 Žw’è‚µ‚½ŠÂ‹«•Ï�”‚ª‚È‚¢
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre table_name ‚Æ‚¢‚¤ƒe�[ƒuƒ‹‚ª‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�Atable_name ‚É‘¶�Ý‚·‚é�B
 * \pre *table_name ‚ªƒAƒNƒZƒX‰Â”\
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *info ‚ªŠÂ‹«•Ï�”�î•ñ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_envvalinfo(char *table_name, long id,
									di_envinfo_t *info);

/**
 * \brief ŠÂ‹«•Ï�”‚Ì’lƒŠƒXƒg‚ÌŽæ“¾
 *
 * \param table_name  ŠÂ‹«•Ï�”ƒe�[ƒuƒ‹–¼
 * \param id          ŠÂ‹«•Ï�”ID
 * \param start       Žæ“¾‚µ‚½‚¢ŠÂ‹«•Ï�”‚Ì’l‚ÌƒŠƒXƒg’†‚Ì�æ“ª”Ô�†
 * \param end         Žæ“¾‚µ‚½‚¢ŠÂ‹«•Ï�”‚Ì’l‚ÌƒŠƒXƒg’†‚Ì�I—¹”Ô�†
 * \param list        ’l‚ÌƒŠƒXƒg‚ð“ü‚ê‚é”z—ñ‚Ìƒ|ƒCƒ“ƒ^
 * \param list_num    list‚É“ü—Í‚µ‚½—LŒø‚È•Ï�”ƒŠƒXƒg‚Ì�€–Ú�”
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 table_name‚ª‘¶�Ý‚µ‚È‚¢
 * \retval -3 Žw’è‚µ‚½ŠÂ‹«•Ï�”‚ª‚È‚¢
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre table_name ‚Æ‚¢‚¤ƒe�[ƒuƒ‹‚ª‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�Atable_name ‚É‘¶�Ý‚·‚é�B
 * \pre *table_name ‚ªƒAƒNƒZƒX‰Â”\
 * \pre list[0]�`list[end-start]  ‚ªƒAƒNƒZƒX‰Â”\
 * \pre *list_num ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post list[0]�`list[list_num-1] ‚ªŠÂ‹«•Ï�”id‚Ì’l‚ÌƒŠƒXƒg‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_envvallist(char *table_name, long id,
									unsigned long start, unsigned long end,
									long *list, long *list_num);

/**
 * \brief ƒpƒlƒ‹•\Ž¦Œ¾Œê‚ðŽæ“¾‚·‚é�B
 *
 * \param language   ƒpƒlƒ‹•\Ž¦Œ¾Œê
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *table_name ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *language ‚ªƒpƒlƒ‹•\Ž¦Œ¾Œê‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_panellang(unsigned char *language);

/**
 * \brief “‹�Ú‚³‚ê‚Ä‚¢‚éƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ‚ÌŠeŽí�î•ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param id         ƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ‚Ì”Ô�†
 * \param info       id”Ô–Ú‚Ìƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ‚Ì�î•ñ
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\
 * \pre id ‚ª 1�`n ‚Ì”ÍˆÍ“à�Bn ‚Í di_get_flashmemnum() ‚ÅŽæ“¾‚³‚ê‚é
 *ƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ‚Ì�”�B
 *
 * \post *info ‚ª id ”Ô–Ú‚Ìƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ�î•ñ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_flashmeminfo(int id, di_flashmem_info_t *info);

/**
 * \brief “‹�Ú‚³‚ê‚Ä‚¢‚éƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ‚Ì�”‚ðŽæ“¾‚·‚é�B
 *
 * \param num     ƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ‚Ì�”
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *num ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *num ‚ª“‹�Ú‚³‚ê‚Ä‚¢‚éƒtƒ‰ƒbƒVƒ…ƒ�ƒ‚ƒŠ‚Ì�”‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_flashmemnum(long *num);

/**
 * \brief ’ÊŽ†‰Â”\‚È�Å‘å—pŽ†ƒTƒCƒY‚ðŽæ“¾‚·‚é�B
 *
 * \param x     Žå‘–�¸•ûŒü(’PˆÊ : 1/10mm)
 * \param y     •›‘–�¸•ûŒü(’PˆÊ : 1/10mm)
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *x ‚ªƒAƒNƒZƒX‰Â”\
 * \pre *y ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *x ‚ªŽå‘–�¸•ûŒü‚Ì’ÊŽ†‰Â”\�Å‘åƒTƒCƒY‚Æ“™‚µ‚­‚È‚é�B
 * \post *y ‚ª•›‘–�¸•ûŒü‚Ì’ÊŽ†‰Â”\�Å‘åƒTƒCƒY‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_maxpapersize(long *x, long *y);

/**
 * \brief ƒGƒ“ƒWƒ“‚Å�ì‘œ‰Â”\‚È�Å‘åƒTƒCƒY‚ðŽæ“¾‚·‚é�B
 *
 * \param x     Žå‘–�¸•ûŒü(’PˆÊ : 1/10mm)
 * \param y     •›‘–�¸•ûŒü(’PˆÊ : 1/10mm)
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *x ‚ªƒAƒNƒZƒX‰Â”\
 * \pre *y ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *x ‚ªŽå‘–�¸•ûŒü‚Ì�ì‘œ‰Â”\�Å‘åƒTƒCƒY‚Æ“™‚µ‚­‚È‚é�B
 * \post *y ‚ª•›‘–�¸•ûŒü‚Ì�ì‘œ‰Â”\�Å‘åƒTƒCƒY‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_maximagesize(long *x, long *y);

/**
 * \brief ƒ�ƒjƒ…�[ƒAƒCƒeƒ€�î•ñ‚ÌŽæ“¾
 *
 * \param panel_id  ƒ�ƒjƒ…�[ƒAƒCƒeƒ€‚Ìƒpƒlƒ‹ID
 * \param itemtype  ƒ�ƒjƒ…�[ƒAƒCƒeƒ€‚ÌƒAƒCƒeƒ€ƒ^ƒCƒv
 * \param menutype  ƒ�ƒjƒ…�[ƒAƒCƒeƒ€‚Ìƒ�ƒjƒ…�[ƒ^ƒCƒv
 * \param buf       ƒ�ƒjƒ…�[ƒAƒCƒeƒ€‚Ì�î•ñ‚ðŠi”[‚·‚éƒoƒbƒtƒ@
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre buf[0]�`buf[31] ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post buf ‚ªƒ�ƒjƒ…�[ƒAƒCƒeƒ€‚Ì�î•ñ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_menuitem(unsigned long panel_id,
								  unsigned long itemtype,
								  unsigned long menutype,
								  unsigned char *buf);

/**
 * \brief Žw’è‚·‚éƒfƒoƒCƒX‚©‚ç•¶Žš—ñ‚ðŽæ“¾‚·‚é�B
 *
 * \param type    ƒfƒoƒCƒXŽí—Þ
 * \param device  ƒfƒoƒCƒX‚Ì�Ú�×
 * \param id      •¶Žš—ñID
 * \param buf     •¶Žš—ñ‚ðŠi”[‚·‚éƒoƒbƒtƒ@
 * \param size    �I’[•¶Žš‚ðŠÜ‚ñ‚¾•¶Žš—ñ‚Ì’·‚³
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre buf[0]�`buf[size-1] ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post buf ‚ªŽw’è‚³‚ê‚½ƒfƒoƒCƒX‚Ì•¶Žš—ñ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_string(int type, long device, unsigned long id,
								unsigned char *buf, unsigned long size);
								
/**
 * \brief ƒtƒHƒ“ƒg‚Ì�î•ñ‚ðŽæ“¾‚·‚é�B
 *
 * ƒtƒHƒ“ƒg‚ÌŠî–{�î•ñ‚Í di_getinfo() ‚ÅŽæ“¾‚Å‚«‚é‚ª�A�Ú�×�î•ñ‚ðŽæ“¾‚·
 *‚é�ê�‡�A‚à‚µ‚­‚Í di_getinfo() ‚ÅŽæ“¾‚Å‚«‚éƒtƒHƒ“ƒgˆÈŠO‚ÌŽí—Þ‚ÌƒtƒHƒ“
 *ƒg�î•ñ‚ðŽæ“¾‚·‚é�ê�‡‚É–{ŠÖ�”‚ðŽg—p‚·‚é�B
 *
 * \param type  ƒtƒHƒ“ƒg‚ÌŽí—Þ
 * \param info  ƒtƒHƒ“ƒg‚Ì�î•ñ
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\
 *
 * \post *info ‚ª type ‚ÌƒtƒHƒ“ƒg�î•ñ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_fontinfo(int type, di_fontinfo_t *info);

/**
 * \brief “‹�ÚPDL�î•ñ‚ðŽæ“¾‚·‚é
 *
 * \param pdl_id  PDL ID
 * \param info    PDL�î•ñ
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 Žw’èPDL‚ª“‹�Ú‚³‚ê‚Ä‚¢‚È‚¢
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre pdl_id ‚ª—LŒøID
 *
 * \post *info ‚ª pdl_id ‚Ì PDL �î•ñ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_pdlinfo(int pdl_id, di_pdlinfo_t *info);

/**
 * \brief ƒ†�[ƒU�[ƒWƒ‡ƒu•Ï�”‚Ì’l‚ðŽæ“¾‚·‚é�B
 *
 * \param ujobparam ƒ†�[ƒU�[ƒWƒ‡ƒu�î•ñ
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒWƒ‡ƒuID‚ª–³Œø
 * \retval -2 ƒTƒ|�[ƒg‚µ‚Ä‚¢‚È‚¢ƒpƒ‰ƒ��[ƒ^‚ðŽw’è‚µ‚½
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre *ujobparam ‚ªƒAƒNƒZƒX‰Â”\�B
 *
 * \post *ujobparam ‚ªƒ†�[ƒU�[ƒWƒ‡ƒu•Ï�”‚Ì’l‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_ujobparamvar( ujobparam_var_t *ujobparam );

/**
 * \brief conversion of the paper output bin number to id 
 *
 * \parameter bin_index: the number of the paper output bin
 *  
 * \retval >=0: id of paper output bin
 * \retval -1 : failure
 *
 * \pre di_init() has been called
 *
 * \post return the id of the paper output bin
 */
extern EXPORT int di_convert_binid(int bin_index);

extern EXPORT int di_open_downloadinfo(int ope, int mediatype, char *pdlname, char *filename,
					unsigned long *filesize, unsigned long *hfctrl);
extern EXPORT int di_close_downloadinfo(unsigned long hfctrl);
extern EXPORT int di_read_downloadinfo(unsigned long hfctrl, void *pbuf, long readsize, long *nsize);
extern EXPORT int di_write_downloadinfo(unsigned long hfctrl, void *pbuf, long writesize, long *nsize);
extern EXPORT int di_delete_downloadinfo(int ope, int mediatype, char *pdlname, char *dirname);
extern EXPORT void di_check_interrupt();

extern EXPORT void di_set_ujobid(int ujobid);


/**
 * \brief Žw’è‚³‚ê‚½—pŽ†“™‚Ì�î•ñ‚ðŒ³‚É�A•K—v‚È‰æ‘œ‰ñ“]•ûŒü‚Ì�î•ñ‚ðŽæ“¾
 *‚·‚é�B
 *
 * \param plotid ƒvƒ�ƒbƒ^ID
 * \param info   ‰æ‘œ‰ñ“]•ûŒü‚Ì”»’è‚ð�s‚¤‚½‚ß‚Ì�î•ñ
 * \param result ‰æ‘œ‰ñ“]•ûŒü‚Ì”»’èŒ‹‰Ê
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 * \retval -2 ŠÖ�”‚ªƒTƒ|�[ƒg‚³‚ê‚Ä‚¢‚È‚¢
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre plotid ‚ª—LŒø ID�B
 * \pre *info ‚ªƒAƒNƒZƒX‰Â”\�B
 * \pre *result ‚ªƒAƒNƒZƒX‰Â”\�B
 *
 * \post *result ‚ª‰æ‘œ‰ñ“]•ûŒü‚Ì�î•ñ‚Æ“™‚µ‚­‚È‚é�B
 */
extern EXPORT int di_get_imgrotinfo( int plotid, di_rotenvinfo_t *info, di_imgrotinfo_t *result );

/**
 * \brief ƒKƒ“ƒ}�ÄŒvŽZ‚ð�s‚¤�B
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 *
 * \post ƒVƒXƒeƒ€“à‚ÌƒKƒ“ƒ}‚ª�ÄŒvŽZ‚³‚ê‚é�B
 */
extern EXPORT int di_update_gamma();

/**
 * \brief ŠÂ‹«•Ï�”‚Ì’l(ƒoƒCƒg—ñ)‚ðŽæ“¾‚·‚é�B
 *
 * \param table_name ŠÂ‹«•Ï�”ƒe�[ƒuƒ‹–¼
 * \param id         ŠÂ‹«•Ï�”ID
 * \param val        “¾‚ç‚ê‚½ŠÂ‹«•Ï�”‚Ì’l
 * \param in_size    ƒoƒCƒg—ñval‚ÌƒoƒCƒg�”�BŠÂ‹«•Ï�”‚ª•¶Žš—ñ‚Ì�ê�‡‚É‚Í�ANULLƒ^�[ƒ~ƒl�[ƒg‚ª“ü‚é‚¾‚¯‚Ì�”‚ðŽw’è‚·‚é‚±‚Æ�B
 * \param out_size   ƒoƒCƒg—ñ‚Ì—LŒø‚ÈƒoƒCƒg�”�BŠÂ‹«•Ï�”‚ª•¶Žš—ñ‚Ì�ê�‡‚É‚Í�ANULLƒ^�[ƒ~ƒl�[ƒg‚ðŠÜ‚Þ’·‚³‚ð•Ô‚·�B
 *
 * \retval  1 �³�í�I—¹�iŠÂ‹«•Ï�”‚ª–¾Ž¦“I‚ÉŽw’è‚³‚ê‚Ä‚¢‚é�j
 * \retval  0 �³�í�I—¹�iŠÂ‹«•Ï�”‚ª–¾Ž¦“I‚ÉŽw’è‚³‚ê‚Ä‚È‚¢‚½‚ß�AƒfƒtƒHƒ‹
 *ƒg’lƒZƒbƒg)
 * \retval -1 ƒGƒ‰�[�idi_init()‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚È‚¢�AŠÖ�”‚ðƒTƒ|�[ƒg‚µ‚Ä‚¢‚È‚¢�j
 * \retval -2 ƒGƒ‰�[�itable_name‚ª‘¶�Ý‚µ‚È‚¢�j
 * \retval -3 ƒGƒ‰�[�iŽw’è‚µ‚½ŠÂ‹«•Ï�”‚ª‚È‚¢�j
 * \retval -4 ƒGƒ‰�[�iin_size‚ª�¬‚³‚·‚¬‚é�j
 *
 * \pre di_init() ‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é�B
 * \pre table_name‚Æ‚¢‚¤ƒe�[ƒuƒ‹‚ª‘¶�Ý‚·‚é�B
 * \pre ŠÂ‹«•Ï�” id ‚ª�Atable_name‚É‘¶�Ý‚·‚é�B
 * \pre val[0]-val[in_size-1]‚ªƒAƒNƒZƒX‰Â”\�B
 * \pre *out_size‚ªƒAƒNƒZƒX‰Â”\�B
 *
 * \post val[0]-val[out_size-1]‚ÉŽw’è‚µ‚½ŠÂ‹«•Ï�”‚Ì’l‚ªŠi”[‚³‚ê‚é�B
 */
extern EXPORT int di_get_envdata( char *table_name, long id, void *val, unsigned long in_size, unsigned long *out_size );

/**
 * \brief ƒpƒlƒ‹‚ÉƒGƒ~ƒ…ƒŒ�[ƒVƒ‡ƒ“–¼‚ð•\Ž¦‚·‚é�B
 *
 * \retval  0 �³�í�I—¹
 * \retval -1 ƒGƒ‰�[
 *
 * \pre di_init()‚ªƒR�[ƒ‹‚³‚ê‚Ä‚¢‚é
 * \pre str‚ªNULL‚Å‚È‚¢
 * \pre str‚ªNULLƒ^�[ƒ~ƒl�[ƒg‚ðŠÜ‚ß‚Ä�A8ƒoƒCƒgˆÈ“à‚Å‚ ‚é
 *
 * \post ƒpƒlƒ‹‚Éstr‚ÅŽw’è‚µ‚½ƒGƒ~ƒ…ƒŒ�[ƒVƒ‡ƒ“–¼‚ª•\Ž¦‚³‚ê‚é(GPS“®�ì‚Ì‚Ý)
 */
extern EXPORT int di_disp_setemulation( char *str );

extern EXPORT int di_disp_setcurrentintray( unsigned short tray_id );
extern EXPORT int di_disp_setcurrentintray2( unsigned short tray_id,
						unsigned short cut_orient_id );
extern EXPORT int di_disp_setdialogueid( char *filename, unsigned short str1_id, unsigned char str1_size,
 unsigned short str2_id, unsigned char str2_size, unsigned char time );
extern EXPORT int di_disp_clrdialogue( void );
extern EXPORT int di_disp_setprognum( unsigned short prog_id );
extern EXPORT int di_disp_menucheckfinish( void );
extern EXPORT int di_disp_addmenuitem( unsigned char *buf );

/* ƒvƒ�ƒOƒ‰ƒ€“o˜^ */
extern EXPORT struct di_progtable * di_get_programinfo ( unsigned int prog_no );
extern EXPORT int di_register_program( int prog_no, di_progtable_t *psw );
extern EXPORT int di_delete_program(int prog_no );
extern EXPORT int di_get_programnum( void );
extern EXPORT int di_write_program( char *name, int fileno, char *data, int data_size );
extern EXPORT int di_read_program( char *name, int fileno, char *data, int data_size );
extern EXPORT int di_finish_program( void );
extern EXPORT int di_write_storage_auth( int type, char *fname, unsigned char *data, long size, unsigned long auth );
extern EXPORT int di_register_program_auth( int prog_no, di_progtable_t *psw, unsigned long auth );
extern EXPORT int di_delete_program_auth( int prog_no, unsigned long auth );
extern EXPORT int di_write_program_auth( char *name, int fileno, char *data, int data_size, unsigned long auth );

/* USE_SET_CATEGORY */
extern EXPORT int di_set_category( char *category );

/* USE_CHANGE_EML */
extern EXPORT int di_change_eml( char *eml_name, int uswitch );

extern EXPORT int di_query_duplex( di_chkduplexok_t *pchkduplex );
extern EXPORT int di_set_ethertalkinfo_auth( di_ethertalk_info_t *info, unsigned long auth );

extern EXPORT int di_open_envtable( char *table_name );
extern EXPORT int di_close_envtable( int penv );
extern EXPORT int di_get_envvalue_direct( int penv, long id, long *val );
extern EXPORT int di_get_defenvvalue_direct( int penv, long id, long *val );
extern EXPORT int di_get_envdata_direct( int penv, long id, void *val,
							unsigned long in_size, unsigned long *out_size );
extern EXPORT int di_request_tray( int plotid, int psize, int nodir, int ptype,
									int trayid, di_trayrequest_t *trayreq, 
									int *result );
extern EXPORT int di_get_micrinfo( long *micrinfo );
extern EXPORT int di_get_printcondition( di_printcondition_t *cond,
										 di_media_printcondition_t *media );
extern EXPORT int di_get_printconditionShm( di_printconditionShm_t *condShm,
											int *status );
extern EXPORT int di_get_trayinfo2( di_trayinfo_t *trayinfo );
extern EXPORT int di_get_ucpdata(di_ucp_info_t ucpinfo,
								di_ucp_data_t *ucpdata,
								int *result);
extern EXPORT int di_get_ucpparam(di_ucp_param_t *ucpparam, int *result);
extern EXPORT int di_set_printinfo(int plotid, di_printinfo_t *prtinfo);

extern EXPORT int di_zinit( di_initinfo_t *initinfo, di_setinfo_t *setinfo );
extern EXPORT int di_zopen_host(void);
extern EXPORT int di_zclose_host(void);
extern EXPORT int di_ztrans_process(void);
extern EXPORT int di_zselect_idevice(int mode, void *opt);
extern EXPORT int di_zinit_memory(unsigned char *mem_zlib_addr);

/** \} */ /* end of group(Interface) */

#else	/* DEFINE_DI_TYPE */

typedef int (*DI_PROC_INIT)( di_initinfo_t *, di_setinfo * );
typedef int (*DI_PROC_CLEAR)( di_devinfo_t *, DI_CALLBACK_MEMFREE );
typedef void (*DI_PROC_TERM)();
typedef int (*DI_PROC_GETINFO)( di_devinfo_t *, DI_CALLBACK_MEMALLOC, char * );
typedef int (*DI_PROC_GET_REQUEST)();
typedef int (*DI_PROC_GET_TRAYINFO)( di_trayinfo_t * );
typedef int (*DI_PROC_GET_ENVVALUE)( char *, long, long * );
typedef int (*DI_PROC_SET_ENVVALUE)( char *, long, long );
typedef int (*DI_PROC_SET_CALLBACKFUNC)( int, DI_CALLBACK_FUNC );
typedef char* (*DI_PROC_MEMORY_ALLOC)( unsigned long );
typedef void (*DI_PROC_MEMORY_FREE)( char * );
typedef void (*DI_PROC_OPEN_HOST)();
typedef void (*DI_PROC_CLOSE_HOST)();
typedef int (*DI_PROC_IGETCH)( unsigned char *);
typedef int (*DI_PROC_IGETS)( unsigned char *, long );
typedef int (*DI_PROC_IPEEKCH)( unsigned char *);
typedef int (*DI_PROC_IPEEKS)( unsigned char *, long );
typedef void (*DI_PROC_RESET_IPEEK)();
typedef int (*DI_PROC_ISEEK)( long );
typedef int (*DI_PROC_SELECT_IDEVICE)( int, void * );
typedef int (*DI_PROC_TRANS_PROCESS)();
typedef int (*DI_PROC_NOTIFY_MSG)(int, long);
typedef int (*DI_PROC_QUERY_SUPPORTPAPER)( int );
typedef int (*DI_PROC_GET_OPTSTR)( char ** );
typedef int (*DI_PROC_GET_PAPERSIZE)( unsigned char, unsigned int, unsigned int );
typedef int (*DI_PROC_OPEN_HOSTS)();
typedef int (*DI_PROC_CLOSE_HOSTS)();
typedef int (*DI_PROC_SOUTPUTC)( unsigned char );
typedef int (*DI_PROC_SOUTPUT)( unsigned char *, long, int );
typedef int (*DI_PROC_SOUTFLUSH)();
typedef int (*DI_PROC_SINAVAIL)( long * );
typedef int (*DI_PROC_GET_DEFTRAY)( int * );
typedef int (*DI_PROC_GET_DEFBIN)( int * );
typedef int (*DI_PROC_GET_BININFO)( di_bininfo_t * );
typedef int (*DI_PROC_GET_STATUS)( di_status_t * );
typedef int (*DI_PROC_GET_TOTALCOUNTER)( long * );
typedef int (*DI_PROC_GET_ETHERTALKINFO)( di_ehtertalk_info_t * );
typedef int (*DI_PROC_SET_ETHERTALKINFO)( di_ehtertalk_info_t * );
typedef int (*DI_PROC_SET_UJOBINFO)( int, di_ujob_info_t * );
typedef int (*DI_PROC_GET_UJOBINFO)( int, di_ujob_info_t * );
typedef int (*DI_PROC_GET_BITSWINFO)( int, int * );
typedef int (*DI_PROC_GET_DISKINFO)( int, di_diskinfo_t * );
typedef int (*DI_PROC_WRITE_STORAGE)( int, char *, unsigned char *, long );
typedef int (*DI_PROC_READ_STORAGE)( int, char *, unsigned char *, long, long * );
typedef int (*DI_PROC_DELETE_STORAGE)( int, char * );
typedef int (*DI_PROC_REQUEST_PAPER)( int, int, int, int, int, di_res_reqpaper_t * );
typedef int (*DI_PROC_GET_DEFENVVALUE)( char *, long, long * );
typedef int (*DI_PROC_SET_DEFENVVALUE)( char *, long, long );
typedef int (*DI_PROC_GET_ENVVALINFO)( char *, long, di_envinfo_t *o );
typedef int (*DI_PROC_GET_ENVVALLIST)( char *, long, unsigned long, unsigned long, long *, long * );
typedef int (*DI_PROC_GET_PANELLANG)( unsigned char * );
typedef int (*DI_PROC_GET_FLASHMEMINFO)( int, di_flashmem_info_t * );
typedef int (*DI_PROC_GET_FLASHMEMNUM)( long * );
typedef int (*DI_PROC_GET_MAXPAPERSIZE)( long *, long * );
typedef int (*DI_PROC_GET_MAXIMAGESIZE)( long *, long * );
typedef int (*DI_PROC_GET_MENUITEM)( unsigned long, unsigned long, unsigned long, unsigned char * );
typedef int (*DI_PROC_GET_STRING)( int, long, unsigned long, unsigned char, unsigned long * );
typedef int (*DI_PROC_GET_FONTINFO)( int, di_fontinfo_t * );
typedef int (*DI_PROC_GET_PDLINFO)( int, di_pdlinfo_t * );
typedef int (*DI_PROC_GET_UJOBPARAMVAR)( ujobparam_var_t *);
typedef int (*DI_PROC_OPEN_DOWNLOADINFO)(int, int, char *, char *, unsigned long *, unsigned long *);
typedef int (*DI_PROC_CLOSE_DOWNLOADINFO)(unsigned long);
typedef int (*DI_PROC_READ_DOWNLOADINFO)(unsigned long, void *, long, long *);
typedef int (*DI_PROC_WRITE_DOWNLOADINFO)(unsigned long, void *, long, long *); 
typedef int (*DI_PROC_DELETE_DOWNLOADINFO)(int, int, char *, char *);
typedef int (*DI_PROC_GET_IMGROTINFO)( int , di_rotenvinfo_t *, di_imgrotinfo_t * );
typedef int (*DI_PROC_UPDATE_GAMMA)();
typedef int (*DI_PROC_GET_ENVDATA)( char *, long, void *, unsigned long, unsigned long * );
typedef int (*DI_PROC_DISP_SETEMULATION)( char * );
typedef void (*DI_PROC_CHECK_INTERRUPT)();
typedef int (*DI_PROC_DISP_SETCURRENTINTRAY)( unsigned short );
typedef int (*DI_PROC_DISP_SETDIALOGUEID)( char *, unsigned short, unsigned char, unsigned short, unsigned char, unsigned char );
typedef int (*DI_PROC_DISP_CLRDIALOGUE)();
typedef int (*DI_PROC_DISP_SETPROGNUM)( unsigned short );
typedef int (*DI_PROC_DISP_MENUCHECKFINISH)();
typedef int (*DI_PROC_DISP_ADDMENUITEM)( unsigned char * );
typedef int (*DI_PROC_CONVERT_BINID)( int );

typedef struct di_progtable* (*DI_GET_PROGRAMINFO)( unsigned int );
typedef int (*DI_REGISTER_PROGMRAM)( int, di_progtable_t * );
typedef int (*DI_DELETE_PROGRAM)( int );
typedef int (*DI_GET_PROGRAMNUM)( void );
typedef int (*DI_WRITE_PROGRAM)( char *, int, char *, int );
typedef int (*DI_READ_PROGRAM)( char *, int, char *, int );
typedef int (*DI_FINISH_PROGRAM)( void );
typedef int (*DI_WRITE_STORAGE_AUTH)( int, char *, unsigned char *, long, unsigned long );
typedef int (*DI_REGISTER_PROGRAM_AUTH)( int, di_progtable_t *, unsigned long );
typedef int (*DI_DELETE_PROGRAM_AUTH)( int, unsigned long );
typedef int (*DI_WRITE_PROGRAM_AUTH)( char *, int, char *, int, unsigned long );

typedef int (*DI_SET_CATEGORY)( char * );

typedef int (*DI_CHANGE_EML)( char *, int );

typedef int (*DI_QUERY_DUPLEX)( di_chkduplexok_t * );
typedef int (*DI_SET_ETHERTALKINFO_AUTH)( di_ehtertalk_info_t *, unsigned long );

typedef int (*DI_OPEN_ENVTABLE)( char * );
typedef int (*DI_CLOSE_ENVTABLE)( int );
typedef int (*DI_GET_ENVVALUE_DIRECT)( int, long, long * );
typedef int (*DI_GET_DEFENVVALUE_DIRECT)( int, long, long * );
typedef int (*DI_REQUEST_TRAY)( int, int, int, int, int, di_trayrequest_t *, int *);
typedef int (*DI_GET_MICRINFO)( long * );
typedef int (*DI_GET_PRINTCONDITION)( di_printcondition_t *,
									  di_media_printcondition_t * );
typedef int (*DI_GET_PRINTCONDITIONSHM)( di_printconditionShm_t *, int * );
typedef int (*DI_GET_TRAYINFO2)( di_trayinfo_t * );
typedef int (*DI_GET_UCPDATA)(di_ucp_info_t ucpinfo,
								di_ucp_data_t *ucpdata
								int *result);
typedef int (*DI_GET_UCPPARAM)(di_ucp_param_t *ucpparam,
											int *result);
typedef int (*DI_SET_PRINTINFO)(int, di_printinfo_t *);

typedef int (*DI_ZINIT)( di_initinfo_t *, di_setinfo_t * );
typedef int (*DI_ZOPEN_HOST)( void );
typedef int (*DI_ZCLOSE_HOST)( void );
typedef int (*DI_ZTRANS_PROCESS)( void );
typedef int (*DI_ZSELECT_IDEVICE)( int, void * );
typedef int (*DI_ZINIT_MEMORY)( unsigned char * );

#endif	/* DEFINE_DI_TYPE */

#endif	/* __DEVICE_H__ */

/*
 *
 *	COPYRIGHT (C) 2001-2007 RICOH COMPANY LTD.
 *	All rights reserved.
 *
 */
