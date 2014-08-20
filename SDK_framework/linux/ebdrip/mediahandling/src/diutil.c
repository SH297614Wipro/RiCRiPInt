#include "device.h"
#if 0
#include "mhwrapper.h"
#endif
#include "pageprint.h"
#include "omstub.h"

#define	PR_PRINT_MODE_MASK			(0x0F)
#define GPS_CHKDIR_RESOLUTION	(1<<3)
#define NOT_CHANGE 0
#define _enum_None 0

di_devinfo_t diDevInfo;
long CustomSizeWidth;
long CustomSizeLength;
gps_chkdirprm_t condition;

int PrintSysCheckQualityMode (int *om_media, OMenum *om_qmode)
{
	di_resolutioninfo_t * reso;
	Uint16 xres, yres;
    Uint8 bit;
	/*HDW_MEDIA media;
	HDW_QUALITY qmode, def_qmode;*/
	/*Uint8 num;
	Uint8 agree;
	Uint8 ret = NOT_CHANGE;*/
    int qmode, def_qmode, media;
    int num;
	int agree;
	int ret = NOT_CHANGE;
	xres = OMGetCurrentInt(XRESOLUTION, OMSYSTEM);
	yres = OMGetCurrentInt(YRESOLUTION, OMSYSTEM);
	bit = OMGetCurrentInt(OMBITSPERPIXEL, OMSYSTEM);
	/* Convert to the draw resolution */
	PrintSysChangeResolution(&xres, &yres, &bit);
/*
	media = mnOMtoHdwMediaType(*om_media);
	qmode = mnOMtoHdwQualityMode(*om_qmode);
*/
	/* Combination check of resolution and paper kind */
	agree = 0;
	for (reso = diDevInfo.reso_set, num = 0;
	     num < diDevInfo.resonum;
	     reso += diDevInfo.ndit, num += diDevInfo.ndit) {
		if (xres == reso->x && yres == reso->y && bit == reso->bit &&
		    media == reso->paper) {
			agree = 1;
			break ;
		}
	}

	/* no combination of resolution and paper kind */
	if (agree == 0) {
		reso = diDevInfo.reso_set;
		num = 0;

		/* paper kind is changed to default paper kind */
		media = reso->paper;
		/**om_media = mnHdwMediaTypeOM(media);*/
		ret |= CHANGE_MEDIATYPE;

		while ((num < diDevInfo.resonum) && (media == reso->paper)) {
			if (xres == reso->x && yres == reso->y && bit == reso->bit) {
				break;
			}
			reso += diDevInfo.ndit;
			num += diDevInfo.ndit;
		}
	/*	ASSERT((num < diDevInfo.resonum) && (media == reso->paper));*/
	}

	/* set the min quality mode to default quality mode */
#ifdef INK_VOLUME_FEATURE
	def_qmode = (reso->prt_mode & PR_PRINT_MODE_MASK);
#else
	def_qmode = reso->prt_mode;
#endif

	/* Combination check of resolution, paper kind and quality mode */
	agree = 0;
	for (;
	     (num < diDevInfo.resonum) && (media == reso->paper);
	     reso += diDevInfo.ndit, num += diDevInfo.ndit) {
		if (xres == reso->x && yres == reso->y && bit == reso->bit &&
		    media == reso->paper) {
#ifdef INK_VOLUME_FEATURE
			if (qmode == (reso->prt_mode & PR_PRINT_MODE_MASK)) {
#else
			if (qmode == reso->prt_mode) {
#endif
				agree = 1;
				break;
			}
#ifdef INK_VOLUME_FEATURE
			else if ((reso->prt_mode & PR_PRINT_MODE_MASK) ==
					(diDevInfo.reso_set->prt_mode & PR_PRINT_MODE_MASK)) {
#else
			else if (reso->prt_mode == diDevInfo.reso_set->prt_mode) {
#endif
				/* set the Default prt_mode to default quality mode */
#ifdef INK_VOLUME_FEATURE
				def_qmode = (diDevInfo.reso_set->prt_mode & PR_PRINT_MODE_MASK);
#else
				def_qmode = diDevInfo.reso_set->prt_mode;
#endif
			}
		}
	}

	/* no combination of resolution, paper kind and quality mode */
	if (agree == 0) {
		/* quality mode is changed to default quality mode */
		/**om_qmode = mnHdwQualityModeOM(def_qmode);*/
		ret |= CHANGE_QUALITYMODE;
	}

	return ret;
}
/*#endif*/

int PrintSysGetCustomSize(OMenum source, int xres, int yres, PAPERINFO *paper)/*check for paperinfo pointer*/
{
	/*HDW_PAPERSOURCE		hdwtray;*/
	int hdwtray = 3;
	di_trayinfo_t		trayinfo;
	di_onetrayinfo_t	*pTray;
	long				p_length;
	long				p_width;
	long				tmp;
	int					i;

	/*hdwtray = mnOMtoHdwPaperSource(source);*/
/*	DI_get_trayinfo(&trayinfo);
    hdwtray = GetMediaType();
	for (pTray = &trayinfo.trayinfo[0], i = 0; i < trayinfo.tray_num; i++, pTray++) {
		if (hdwtray == pTray->id) {
			p_length = pTray->p_length;
			p_width = pTray->p_width;
			break;
		}
	}

*/	/*LOGMPRINTF6(0x212, "[%s]0212 di_get_trayinfo %d %d %d %d %d\n", PDLNAME, 
		trayinfo.tray_num, i, pTray->id, pTray->p_length, pTray->p_width);*/
/*	if (i >= trayinfo.tray_num)
		return(-1);
*/
    p_width = GetCustomPageWidth();
    p_length = GetCustomPageHeight();
#if !defined(USE_INTERNAL_CUSTOMSIZE)
	CustomSizeWidth = p_width;
	CustomSizeLength = p_length;
#endif

	p_width = p_width * xres / 254;
	p_length = p_length * yres / 254;

	PRcustompaperinfo(p_width, p_length, xres, yres);

	return(0);
}

#ifdef PCL5_CUSTOMSIZE_COMMAND
void PrintSysGetMaxPaperSize(Sint32 *width, Sint32 *height)
{
	if (DI_get_maxpapersize(width, height) == 0) {
		if (*width == -1)
			*width = MAXSINT32;
		if (*height == -1)
			*height = MAXSINT32;
	}
	else
		*width = *height = 0;
}
#endif

long PrintSysGetCustomWidth()
{
#if !defined(USE_INTERNAL_CUSTOMSIZE)
	return CustomSizeWidth;
#else
	return 0;
#endif
}

long PrintSysGetCustomLength()
{
#if !defined(USE_INTERNAL_CUSTOMSIZE)
	return CustomSizeLength;
#else
	return 0;
#endif
}

Boolean PrintSysCheckNonRotation(OMenum paper, ORIENTATION orient, int xres, int yres)
{
	OMenum staple, punch, binding;

	if ( paper == PAPERSIZE_CUSTOM ) {
		return FALSE;
	}

	condition.flag = GPS_CHKDIR_RESOLUTION; /* initialize flag. must check resolution */
	condition.resX = xres;
	condition.resY = yres;
	condition.psize = GetPageSize();/*mnOMtoHdwPaperSize( paper );*/

/*
	staple = OMGetCurrentEnum(OMSTAPLE, OMSYSTEM);
	if ( staple != STAPLE_OFF ) {
		condition.flag |= GPS_CHKDIR_STAPLE;
		condition.staple = pcdOMtoGPSStaple( staple );
	}

	punch = OMGetCurrentEnum(OMPUNCH, OMSYSTEM);
	if ( punch != PUNCH_OFF ) {
		condition.flag |= GPS_CHKDIR_PUNCH;
		condition.punch = pcdOMtoGPSPunch( punch );
	}
    */
	binding = OMGetCurrentEnum(OMBINDINGEDGE, OMSYSTEM);
	if ( OMGetCurrentBool(OMDUPLEX, OMSYSTEM) ) {
		condition.flag |= GPS_CHKDIR_BINDING;
		condition.binding = ((unsigned char)(pcdOMtoGPSBinding(orient, binding)));
	}
  /*
	if( GpPlotChkDirection( gpsClientID, plotterID,
		&condition, &direction, &slantdirection ) == GPS_FUNC_SUPPORT ) {
		return ( direction == GPS_ROT_ALL );
	} else {
		DBGPANIC("Not support gpsPlotChkDirection()\n");
		DBGFATAL();
	
    }
    */

}
/* #endif SYS_CHECK_DIRECTION */


/*  PrintSysGetPaperInfo(OMenum paper)
 *
 *  Purpose: tell even if the paper is supported or not.
 */
Boolean PrintSysGetPaperInfo(OMenum paper)
{
	int result;

 	if(paper == _enum_None)
 		return FALSE;
    /*Commenting hdw calls */
	/*result = DI_query_supportpaper(mnOMtoHdwPaperSize(paper));
	LOGMPRINTF3(0x311, "[%s]0311 %d, %d\n", PDLNAME, mnOMtoHdwPaperSize(paper),result);*/
	result = 1;
	return (result == 1) ? TRUE : FALSE;
}

unsigned char pcdOMtoGPSBinding( ORIENTATION orient, OMenum ombind )
{
	if ((orient & 0x01) == 0)
		return (ombind == BIND_LONGEDGE) ? GPS_BIND_LEFTRIGHT : GPS_BIND_TOPBOTTOM;
	else
		return (ombind == BIND_LONGEDGE) ? GPS_BIND_TOPBOTTOM : GPS_BIND_LEFTRIGHT;
}

#ifdef PRINT_QUALITY_MODE
void PrintSysChangeResolution (Uint16 * xres, Uint16 * yres, Uint8 * bit)
{
	Uint16 in_xres = *xres;
	Uint16 in_yres = *yres;
	Uint8 in_bit = *bit;

	if ((in_xres == 600) && (in_yres == 600) && (in_bit == 2)) {
		if (PrintSysIsValidResolution(in_xres * 2, in_yres, 1)) {
			*xres = in_xres * 2;
			*bit = 1;
		}
		else if (PrintSysIsValidResolution(in_xres, in_yres * 2, 1)) {
			*yres = in_yres * 2;
			*bit = 1;
		}
		else if (!PrintSysIsValidResolution(in_xres, in_yres, in_bit)) {
			*bit = 1;
		}
	}
#if CAN_RENDER_CMYK_4_BYPLANE == 0 && CAN_RENDER_GRAY_4 == 0
	if (((in_xres == 300) && (in_yres == 300) && (in_bit == 4)) ||
	    ((in_xres == 150) && (in_yres == 150) && (in_bit == 4))) {
		*bit = 2;
		if (PrintSysIsValidResolution(in_xres * 2, in_yres, *bit)) {
			*xres = in_xres * 2;
		}
		else if (PrintSysIsValidResolution(in_xres, in_yres * 2, *bit)) {
			*yres = in_yres * 2;
		}
	}
#endif
}
#endif
/* PrintSysIsValidResolution()
 *
 * Purpose: find the resolution at the target printer
 */
Boolean PrintSysIsValidResolution(int xres, int yres, Uint8 bits)
{
	int n;
	di_resolutioninfo_t* res_info;
/*
	if (diGIErr & DI_GI_ERR_RESO)
		return FALSE;
*/	
	res_info = diDevInfo.reso_set;
	for (n = 0; n < diDevInfo.resonum; n++, res_info++) {
		if (res_info->x == xres && res_info->y == yres && res_info->bit == bits)
			return TRUE;
	}

	return FALSE;
}

#if defined(PCL5_CUSTOMSIZE_COMMAND) || defined(RP_CUSTOMPAPERSIZE)
void PrintSysSetCustomSize(long p_width, long p_length, int xres, int yres)
{
#if !defined(USE_INTERNAL_CUSTOMSIZE)
	CustomSizeWidth = p_width;
	CustomSizeLength = p_length;
#endif
}
#endif /* PCL5_CUSTOMSIZE_COMMAND || RP_CUSTOMPAPERSIZE */

#ifdef SUPPORT_INSERTER
Boolean PrintSysInserterMatchPaperSize(void)
{
/*	int inserter_size, inserter_indicator, inserter_tray, i;
	di_trayinfo_t trayinfo;
	di_onetrayinfo_t *pTray;
	inserter_indicator = PR_TRAY_INSERTER;*/
/*	inserter_indicator = PDIGetInserterTray(); //For 9.0 //Commenting for now*/
/*
	switch (inserter_indicator) {
		case PR_TRAY_INSERTER: 
			inserter_tray = DI_TRAY_INSERTER;
			break;

		case PR_TRAY_INSERTER2: 
			inserter_tray = DI_TRAY_INSERTER2; 
			break;

		default:
*/			/* Invalid inserter tray. Just return.*/
/*			return FALSE;
	}

	DI_get_trayinfo2(&trayinfo);
*/	/*LOGMPRINTF3(0x212, "[%s]0212 Inserter %d %d\n", PDLNAME, inserter_tray, trayinfo.tray_num);*/
	/* Get the paper size in the inserter tray */
/*	for (i = 0; i < trayinfo.tray_num; i++) {
		
		pTray = &trayinfo.trayinfo[i];
		if (inserter_tray == pTray->id) {
			inserter_size = pTray->p_size; 
*/			/* Check the feed direction of the paper size */ 
/*			if (inserter_size < DI_CODE_NO_SIZE) {
*/				/* This is a long edge paper */
/*				return TRUE;
			} else {
*/				/* This is a short edge paper */
/*				return FALSE;
			}
		}
	}

*/	/* Not found the inserter tray */
	return FALSE;
}
#endif /*SUPPORT_INSERTER*/
