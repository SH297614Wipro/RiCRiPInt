#include "omstub.h"
#define FIRSTPAGE_DONE	0x01
#define LEF_SELECTED	0x02
#define SEF_SELECTED	0x04
#define PR_ROT_ERROR 0
//#define TRAYSEARCHMODE_SWITCH 1
//#define PAPERSRC_ALL 3
OMenum CompulsionOutPaperSize;
OMenum CompulsionOutInTray;
extern Sint8 ChoosePaperDirectionDone;
int plotterID = -1;
int direction;
#if 0
static int SimplexBinding = GPS_PENV_VAL_INT_BINDING_LEFT;

typedef struct _staple_available_position {
	Sint8 physicalPosition;
	OMenum omStaple;
	ORIENTATION setOrient;
} STAPLE_AVAILABLE_POSITION;

typedef struct _finish_printmode {
	FEED_DIRECTION direction;
	OMenum	staple;
	OMenum	punch;
	DUPLEX_MODE	duplex;
	ORIENTATION	orient;
} FINISH_PRINTMODE;

typedef struct _finish_print_result {
	ORIENTATION	orient;
	Boolean	staple;
	Boolean	slant;
	Boolean	punch;
} FINISH_PRINT_RESULT;

typedef struct {
	ORIENTATION	orient;
	int	direction;
	Boolean	chooseLEF;
} OrientDirectionPair;

static CONST OrientDirectionPair directionMap[] = {
	{ GPS_PENV_VAL_INT_ORIENTATION_PORTRAIT, (PR_ROT_90B|PR_ROT_270B), TRUE },
	{ GPS_PENV_VAL_INT_ORIENTATION_PORTRAIT, (PR_ROT_0B|PR_ROT_180B), FALSE },
	{ GPS_PENV_VAL_INT_ORIENTATION_LANDSCAPE, (PR_ROT_0B|PR_ROT_180B), TRUE },
	{ GPS_PENV_VAL_INT_ORIENTATION_LANDSCAPE, (PR_ROT_90B|PR_ROT_270B), FALSE },
	{ GPS_PENV_VAL_INT_ORIENTATION_REVERSEPORTRAIT, (PR_ROT_90B|PR_ROT_270B), TRUE },
	{ GPS_PENV_VAL_INT_ORIENTATION_REVERSEPORTRAIT, (PR_ROT_0B|PR_ROT_180B), FALSE },
	{ GPS_PENV_VAL_INT_ORIENTATION_REVERSELANDSCAPE, (PR_ROT_0B|PR_ROT_180B), TRUE },
	{ GPS_PENV_VAL_INT_ORIENTATION_REVERSELANDSCAPE, (PR_ROT_90B|PR_ROT_270B), FALSE }
};
#endif
//static Boolean setEdgeFeedOnOrientDirection( ORIENTATION orient, int direction, Boolean *chooseLEF )
//{
/*	CONST OrientDirectionPair *p_dirMap; //temporarily dependent on directionmap
	int i, dirNum;

	p_dirMap = directionMap;
	dirNum = dimof(directionMap);

	for ( i = 0 ; i < dirNum ; i++, p_dirMap++ ) {
		if ( orient == p_dirMap->orient && (direction & p_dirMap->direction) ) {
			*chooseLEF = p_dirMap->chooseLEF;
			return TRUE;
		}
	}

	return FALSE;
*/
//}

void PrintSysChoosePaperDirectionOnStaplePunch(Boolean *longEdgeTray,
											   Boolean *shortEdgeTray,
											   ORIENTATION orient)
{

	//Boolean chooseLEF;

	if (ChoosePaperDirectionDone & FIRSTPAGE_DONE) {
		if (*longEdgeTray && (ChoosePaperDirectionDone & LEF_SELECTED))
			*shortEdgeTray = FALSE;
		else if (*shortEdgeTray && (ChoosePaperDirectionDone & SEF_SELECTED))
			*longEdgeTray = FALSE;
		return;
	}

	ChoosePaperDirectionDone |= FIRSTPAGE_DONE;

/*	if ( !(condition.flag & (PR_CHKDIR_STAPLE | PR_CHKDIR_PUNCH)) ) {
		return; * Nomal Handling case *
	}*//*

	if ( direction == PR_ROT_ERROR ) {
		return;
	}

	if ( *longEdgeTray && *shortEdgeTray ) {
		if ( (slantdirection != PR_ROT_ERROR) &&
			(condition.staple == STAPLE_LEFTTOPSLANT || condition.staple == PR_STAPLE_RIGHT_TOP_SLANT) )
		{
			if ( !setEdgeFeedOnOrientDirection( orient, slantdirection, &chooseLEF ) ) {
				setEdgeFeedOnOrientDirection( orient, direction, &chooseLEF );
			}
		} else {
			setEdgeFeedOnOrientDirection( orient, direction, &chooseLEF );
		}
	} else if ( *longEdgeTray ) {
		chooseLEF = TRUE;
	} else if ( *shortEdgeTray ) {
		chooseLEF = FALSE;
	} else {
		return; *//* Illegal case */
/*	}

	if ( chooseLEF ) {
		ChoosePaperDirectionDone |= LEF_SELECTED;
		*shortEdgeTray = FALSE;
		setSimplexBinding( orient, chooseLEF );
	} else {
		ChoosePaperDirectionDone |= SEF_SELECTED;
		*longEdgeTray = FALSE;
		setSimplexBinding( orient, chooseLEF );
	}
*/
}

//#ifdef COMMON_PLATFORM
//#if (defined(EMPCL5)||defined(EMPCLXL)) || (defined(EMPOSTSCRIPT)||defined(EMPDF))
int PrintSysPaperRequest( Sint32 *psize, Sint32 pwidth, Sint32 plength,
							OMenum ptype, Sint32 tray, Boolean direction)
{
#if 0   
    /*more related to job start and hdw */
    int ret, i;
	Sint32	lsize, ssize;
#ifdef	ROTATE_FORCE_PRINT
	Sint32	newpsize;
#endif	
#if defined(EMPOSTSCRIPT)||defined(EMPDF)
 	di_res_reqtray_t response;
#else
 	di_res_reqpaper_t response;
#endif/*defined(EMPOSTSCRIPT)||defined(EMPDF)*/
	di_onetrayinfo_t * pTray;
	di_trayinfo_t trayinfo;
	/*TimeVal tmwait = { 0, 200000 };*/
	Sint32	sec_size;	/* second selection if psize is unsupported by the printer */

#if defined(EMPOSTSCRIPT)||defined(EMPDF)
	int res = 0;
	di_trayrequest_t trayreq;  	
	trayreq.flag = DI_TRAYREQFLAG_ALL;
	trayreq.pwidth = pwidth;
	trayreq.plength = plength;
	trayreq.mode = DI_REQ_MODE1;
#endif/*defined(EMPOSTSCRIPT)||defined(EMPDF)*/
	
	if (plotterID == -1)
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if (PrintSysIsInterpPS()) {
		PRJobStart(pPDIstatePS, g_prh, -1);
	}else{
		PRJobStart(pPDIstatePCL, g_prh, -1);
	}
#elif defined(EMPCL5) || defined(EMPCLXL)
		PRJobStart(pPDIstatePCL, g_prh, -1);
#elif (defined(EMPOSTSCRIPT)||defined(EMPDF))
		PRJobStart(pPDIstatePS, g_prh, -1);
#endif /*(defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))*/

#ifdef EN_LIMITLESS_FEED
	if (OMGetCurrentBool(OMAUTOTRAYCHANGE2, OMSYSTEM) || (OMGetCurrentEnum(OMTRAYSEARCHMODE, OMSYSTEM) == GPS_PENV_VAL_INT_TRAYSEARCHMODE_SWITCH)){
		tray = PAPERSRC_ALL;
  }
#else
if (!PrintSysIsInterpPS()) {
	if (OMGetCurrentEnum(OMTRAYSEARCHMODE, OMSYSTEM) == GPS_PENV_VAL_INT_TRAYSEARCHMODE_SWITCH)
		tray = PAPERSRC_ALL;
}
#endif

#if defined(EMPOSTSCRIPT)||defined(EMPDF)
 	init_ReqTrayResponseStatus();
#endif/*defined(EMPOSTSCRIPT)||defined(EMPDF)*/
 
   	while (1) {
 /*		
#if defined(EMPOSTSCRIPT)||defined(EMPDF)
 		ret = DI_request_tray ( plotterID, mnOMtoHdwPaperSize(*psize), direction ? 0 : 1,
 						mnOMtoHdwMediaType(ptype), mnOMtoHdwPaperSource(tray),&trayreq, &res) ;
 	
 		if ( res  !=  -1) {*/ 	/* -1: FAILURE, but can retry */
 /*      		break;
     	}
#else
 		ret = DI_request_paper(plotterID, mnOMtoHdwPaperSize(*psize), direction ? 0 : 1,
 						mnOMtoHdwMediaType(ptype), mnOMtoHdwPaperSource(tray),&response);
 		if (ret != -2){*/	/* !PAGE_BUSY */
/*       		break;
     	}
#endif *defined(EMPOSTSCRIPT)||defined(EMPDF)*
     	else if (PrintSysGetJobCancel()) {			
 			response.result = DI_TRAY_CANCEL;		
  			break;
     	}
  
  		TaskSleep(&tmwait);*/
   	}
 

/*	LOGMPRINTF6(0x309, "[%s]0309 %d, %d, %d, %d, %d\n", PDLNAME, *psize, pwidth, plength, ptype, direction);
*/
	ASSERT( ret != -1 );	/* !PAGE_FAILURE */

#if defined(EMPOSTSCRIPT)||defined(EMPDF)
 	while (1) {
 			
 		if (PrintSysGetJobCancel()) {			
 			response.result = DI_TRAY_CANCEL;		
 			break;
     		}
 		else if ( TRUE == GetReqTrayResponseStatus() )
 		{
 			response = GetRequestTrayRes();
 			break;
 		}
 		
 		TaskSleep(&tmwait);	
 	}	
#endif/*defined(EMPOSTSCRIPT)||defined(EMPDF)*/
 
	switch (response.result) {
	case DI_TRAY_FOUND:
#ifdef DI_TRAY_ANOTHER
	case DI_TRAY_ANOTHER:
#endif
#ifndef IPS_MEDIA_HANDLING
/*#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))*/
		if (PrintSysIsInterpPS()) {
				return (1);
		} else {
	/*  *psize = mnHdwPaperSizetoOM(response.paper_code);*/
		break;
		}
/*#elif (defined(EMPCL5)||defined(EMPCLXL))*/
/*		*psize = mnHdwPaperSizetoOM(response.paper_code);*/
		break;
/*#else*/
		return (1);
/*#endif *//* (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF) */
#else /* IPS_MEDIA_HANDLING */
	/*		*psize = mnHdwPaperSizetoOM(response.paper_code);*/
			break;
#endif /* IPS_MEDIA_HANDLING */

	case DI_TRAY_ERRSKIP:
#ifndef IPS_MEDIA_HANDLING
/*#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))*/
				if (PrintSysIsInterpPS()) {
					return (1);
				} else {
		DI_get_trayinfo(&trayinfo);

/*		for (i = 0; i < trayinfo.tray_num; i++) {
			pTray = &trayinfo.trayinfo[i];

			if (pTray->id == response.tray_id) {
				if (pTray->p_size < DI_CODE_T) {
					if (response.paper_code < DI_CODE_T)
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code);
						sec_size = mnHdwPaperSizetoOM(response.paper_code + DI_CODE_T);
					}
					else
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code -
													DI_CODE_T);
						sec_size = mnHdwPaperSizetoOM(response.paper_code);
					}
				} else {
					if (response.paper_code < DI_CODE_T)
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code +
													DI_CODE_T);
						sec_size = mnHdwPaperSizetoOM(response.paper_code);
					}
					else
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code);
						sec_size = mnHdwPaperSizetoOM(response.paper_code - DI_CODE_T);
					}
				}
				if (!(PrintSysGetPaperInfo(*psize)) && PrintSysGetPaperInfo(sec_size))
					*psize = sec_size;
				break;
			}
		} */
		return(1);
				}
/*#elif (defined(EMPCL5)||defined(EMPCLXL))*/
		DI_get_trayinfo(&trayinfo);

	/*	for (i = 0; i < trayinfo.tray_num; i++) {
			pTray = &trayinfo.trayinfo[i];

			if (pTray->id == response.tray_id) {
				if (pTray->p_size < DI_CODE_T) {
					if (response.paper_code < DI_CODE_T)
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code);
						sec_size = mnHdwPaperSizetoOM(response.paper_code + DI_CODE_T);
					}
					else
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code -
													DI_CODE_T);
						sec_size = mnHdwPaperSizetoOM(response.paper_code);
					}
				} else {
					if (response.paper_code < DI_CODE_T)
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code +
													DI_CODE_T);
						sec_size = mnHdwPaperSizetoOM(response.paper_code);
					}
					else
					{
						*psize = mnHdwPaperSizetoOM(response.paper_code);
						sec_size = mnHdwPaperSizetoOM(response.paper_code - DI_CODE_T);
					}
				}
				if (!(PrintSysGetPaperInfo(*psize)) && PrintSysGetPaperInfo(sec_size))
					*psize = sec_size;
				break;
			}
		} */
		return (1);
/*#else*/
		return (1);
/*#endif *//* (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF) */
#else /* IPS_MEDIA_HANDLING */
					DI_get_trayinfo(&trayinfo);

	/*				for (i = 0; i < trayinfo.tray_num; i++) {
						pTray = &trayinfo.trayinfo[i];

						if (pTray->id == response.tray_id) {
							if (pTray->p_size < DI_CODE_T) {
								if (response.paper_code < DI_CODE_T)
								{
									*psize = mnHdwPaperSizetoOM(response.paper_code);
									sec_size = mnHdwPaperSizetoOM(response.paper_code + DI_CODE_T);
								}
								else
								{
									*psize = mnHdwPaperSizetoOM(response.paper_code -
																DI_CODE_T);
									sec_size = mnHdwPaperSizetoOM(response.paper_code);
								}
							} else {
								if (response.paper_code < DI_CODE_T)
								{
									*psize = mnHdwPaperSizetoOM(response.paper_code +
																DI_CODE_T);
									sec_size = mnHdwPaperSizetoOM(response.paper_code);
								}
								else
								{
									*psize = mnHdwPaperSizetoOM(response.paper_code);
									sec_size = mnHdwPaperSizetoOM(response.paper_code - DI_CODE_T);
								}
							}
							if (!(PrintSysGetPaperInfo(*psize)) && PrintSysGetPaperInfo(sec_size))
								*psize = sec_size;
							break;
						}
					} */
				return (1);
#endif /* IPS_MEDIA_HANDLING */

	case DI_TRAY_FORCE:
#ifndef IPS_MEDIA_HANDLING
/*#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))*/
				if (PrintSysIsInterpPS()) {
					return (1);
				} else {
		DI_get_trayinfo(&trayinfo);

	/*	for (i = 0; i < trayinfo.tray_num; i++) {
			pTray = &trayinfo.trayinfo[i];

			if (pTray->id == response.tray_id) {
				if (pTray->p_size < DI_CODE_T) {
					ssize = mnHdwPaperSizetoOM(pTray->p_size);
					lsize = mnHdwPaperSizetoOM(pTray->p_size + DI_CODE_T);
				} else {
					lsize = mnHdwPaperSizetoOM(pTray->p_size);
					ssize = mnHdwPaperSizetoOM(pTray->p_size - DI_CODE_T);
				}

				if (ssize == *psize || lsize == *psize) {
					*psize = mnHdwPaperSizetoOM(pTray->p_size);
					PrintSysSetCompulsionPaperSize(*psize);
					PrintSysSetCompulsionInTray(
						mnHdwPaperSourcetoOM(response.tray_id));
					break;
				} else {
#ifdef	ROTATE_FORCE_PRINT
					newpsize = mnOMtoHdwPaperSize(*psize);

					if (pTray->p_size < DI_CODE_T) {
						newpsize = newpsize < DI_CODE_T ?
							newpsize : newpsize - DI_CODE_T;
					} else {
						newpsize = newpsize < DI_CODE_T ?
							newpsize + DI_CODE_T : newpsize;
					}

					*psize = mnHdwPaperSizetoOM(newpsize);
#endif
					PrintSysSetCompulsionPaperSize(
						mnHdwPaperSizetoOM(pTray->p_size));
					PrintSysSetCompulsionInTray(
						mnHdwPaperSourcetoOM(response.tray_id));
					return(1);
				}
			}
		} */ 
		return(1);
		break;
				}
/*#elif (defined(EMPCL5)||defined(EMPCLXL))*/
		DI_get_trayinfo(&trayinfo);

	/*	for (i = 0; i < trayinfo.tray_num; i++) {
			pTray = &trayinfo.trayinfo[i];

			if (pTray->id == response.tray_id) {
				if (pTray->p_size < DI_CODE_T) {
					ssize = mnHdwPaperSizetoOM(pTray->p_size);
					lsize = mnHdwPaperSizetoOM(pTray->p_size + DI_CODE_T);
				} else {
					lsize = mnHdwPaperSizetoOM(pTray->p_size);
					ssize = mnHdwPaperSizetoOM(pTray->p_size - DI_CODE_T);
				}

				if (ssize == *psize || lsize == *psize) {
					*psize = mnHdwPaperSizetoOM(pTray->p_size);
					PrintSysSetCompulsionPaperSize(*psize);
					PrintSysSetCompulsionInTray(
						mnHdwPaperSourcetoOM(response.tray_id));
					break;
				} else {
#ifdef	ROTATE_FORCE_PRINT
					newpsize = mnOMtoHdwPaperSize(*psize);

					if (pTray->p_size < DI_CODE_T) {
						newpsize = newpsize < DI_CODE_T ?
							newpsize : newpsize - DI_CODE_T;
					} else {
						newpsize = newpsize < DI_CODE_T ?
							newpsize + DI_CODE_T : newpsize;
					}

					*psize = mnHdwPaperSizetoOM(newpsize);
#endif
					PrintSysSetCompulsionPaperSize(
						mnHdwPaperSizetoOM(pTray->p_size));
					PrintSysSetCompulsionInTray(
						mnHdwPaperSourcetoOM(response.tray_id));
					return(1);
				}
			}
		}*/
		return(1);
		break;
/*#else*/
		return (1);
/*#endif*/ /* (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF) */
#else /* IPS_MEDIA_HANDLING */
					DI_get_trayinfo(&trayinfo);

				/*	for (i = 0; i < trayinfo.tray_num; i++) {
						pTray = &trayinfo.trayinfo[i];

						if (pTray->id == response.tray_id) {
							if (pTray->p_size < DI_CODE_T) {
								ssize = mnHdwPaperSizetoOM(pTray->p_size);
								lsize = mnHdwPaperSizetoOM(pTray->p_size + DI_CODE_T);
							} else {
								lsize = mnHdwPaperSizetoOM(pTray->p_size);
								ssize = mnHdwPaperSizetoOM(pTray->p_size - DI_CODE_T);
							}

							if (ssize == *psize || lsize == *psize) {
								*psize = mnHdwPaperSizetoOM(pTray->p_size);
								PrintSysSetCompulsionPaperSize(*psize);
								PrintSysSetCompulsionInTray(
									mnHdwPaperSourcetoOM(response.tray_id));
								break;
							} else {
#ifdef	ROTATE_FORCE_PRINT
								newpsize = mnOMtoHdwPaperSize(*psize);

								if (pTray->p_size < DI_CODE_T) {
									newpsize = newpsize < DI_CODE_T ?
										newpsize : newpsize - DI_CODE_T;
								} else {
									newpsize = newpsize < DI_CODE_T ?
										newpsize + DI_CODE_T : newpsize;
								}

								*psize = mnHdwPaperSizetoOM(newpsize);
#endif
								PrintSysSetCompulsionPaperSize(
									mnHdwPaperSizetoOM(pTray->p_size));
								PrintSysSetCompulsionInTray(
									mnHdwPaperSourcetoOM(response.tray_id));
								return(1);
							}
						}
					}*/ return(1);
					break;
#endif /* IPS_MEDIA_HANDLING */

	case DI_TRAY_CANCEL:
/*#ifndef IPS_MEDIA_HANDLING
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))*/
		if (PrintSysIsInterpPS()) {
			return (PANEL_JOB_CANCEL);
		} else {
		PrintSysSetJobCancel( TRUE );
#ifdef PRINTSYS_GJ_DEPEND
		jobCancelFlag |= JOB_CANCEL_FROM_SYSTEM;
#endif
		return(1);
		}
/*#elif (defined(EMPCL5)||defined(EMPCLXL))*/
		PrintSysSetJobCancel( TRUE );
		return(1);
/*#elif (defined(EMPOSTSCRIPT)||defined(EMPDF))
		return (PANEL_JOB_CANCEL);*/
/*#endif*/ /* (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF) */
/*#else*/ /* IPS_MEDIA_HANDLING */
			PrintSysSetJobCancel( TRUE );
			return(1);
/*#endif*/ /* IPS_MEDIA_HANDLING */
	}
	/* LOGMPRINTF5(0x310, "[%s]0310 %d, %d, %d, %d\n", PDLNAME, response.result, response.paper_code, response.tray_id, *psize); */
#endif  /* endof #if 0 */
	return(0);
}
//#endif /*(defined(EMPCL5)||defined(EMPCLXL)) || (defined(EMPOSTSCRIPT)||defined(EMPDF))*/

void PrintSysSetCompulsionPaperSize( OMenum paper_size )
{
    CompulsionOutPaperSize = paper_size;
}

void PrintSysSetCompulsionInTray( OMenum tray )
{
    CompulsionOutInTray = tray;
}
//static void setSimplexBinding ( Boolean doStaple, OMenum staple, Boolean doPunch, OMenum punch )
//{
/*
	if ( doStaple ) {
		SimplexBinding = ( staple == STAPLE_TOP2 || doPunch && punch == PUNCH_TOP ) ? GPS_PENV_VAL_INT_BINDING_TOP : GPS_PENV_VAL_INT_BINDING_LEFT;
	} else if ( doPunch ) {
		SimplexBinding = ( punch == PUNCH_TOP ) ? GPS_PENV_VAL_INT_BINDING_TOP : GPS_PENV_VAL_INT_BINDING_LEFT ;
	}
*/
//}
