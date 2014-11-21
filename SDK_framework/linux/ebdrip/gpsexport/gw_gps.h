/* -*- C -*-
 *
 * gw_gps.h - gwipc header file created by 'gwipcgen'.
 *      From : gw_gps.msg
 *      Date : Wed Feb  1 16:41:15 2012
 *
 *   CAUTION : This file is a automatically generated file.
 *             Don't edit this by hand
 *             (without user code areas in skelton file).
 *
 *   Copyright(C) 1999, 2000 RICOH CO.LTD
 */


#ifndef __GWIPC_GW_GPS_H__
#define __GWIPC_GW_GPS_H__ 1

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

/******* c description section *******/

#include    "gps/gps_client.h"
#include    "gps/ujobparam.h"
#include    "gps/interp.h"
#include    "gps/program.h"
#include    "gps/penv.h"
#include    "gps/penv_var.h"
#include    "gps/info.h"
#include    "gps/host.h"
#include    "gps/pageprint.h"
#include    "gps/memory.h"
#include    "gps/papman_def.h"
#include    "gps/modelinfo.h"
#include    "gps/sysexec_param.h"
#include    "gps/ustatusparam.h"
#include    "gps/infoio.h"
#include    "gps/jobio.h"
#include    "gps/memio.h"
#include    "gps/gps_color_inc.h"
#include    "gps/gps_color_inc2.h"
#include    "gps/gps_rmtprn.h"
#include    "gps/bitsw.h"
#include    "gps/gps_color_sample.h"
#include    "gps/gps_rgate.h"
#include    "gps/penvio.h"
#include    "gps/channel.h"
#include    "gps/printcond.h"
#include    "gps/gps_func.h"
#include    "gps/gps_func2.h"
#include    "gps/extctl.h"


/******* msg id section *******/
#define	GWID_GpsEv_SysExec	1052		/* SELF */
#define	GWID_GpsEv_PanelMenuSelect	1053		/* SELF */
#define	GWID_GpsEv_Fin_Proc_Data	1124		/* IN */
#define	GWID_GpsEv_Req_Cancel_Job	1125		/* IN */
#define	GWID_GpsEv_Req_Exit	1213		/* IN */
#define	GWID_GpsEv_Req_Proc_Data	1214		/* IN */
#define	GWID_GpsEv_Req_Cancel_Data	1215		/* IN */
#define	GWID_GpsEv_Req_Reset	1218		/* IN */
#define	GWID_GpsEv_Notify_Online	1224		/* IN */
#define	GWID_GpsEv_Notify_Offline	1225		/* IN */
#define	GWID_GpsEv_Req_Testprint	1226		/* IN */
#define	GWID_GpsEv_Req_Exit_Paper	1230		/* IN */
#define	GWID_GpsEv_Notify_Prime_Reset	1233		/* IN */
#define	GWID_GpsEv_Notify_Feed	1239		/* IN */
#define	GWID_GpsEv_Req_XpdlMenuEntry	1290		/* IN */
#define	GWID_GpsEv_Req_Program	1318		/* IN */
#define	GWID_GpsEv_WkMalloc_Res	1419		/* IN */
#define	GWID_GpsPage_FrameCreate_Res	1532		/* OUT */
#define	GWID_GpsPage_FrameOpen_Res	1534		/* OUT */
#define	GWID_GpsPage_FrameGetBand_Res	1542		/* OUT */
#define	GWID_GpsPage_FrameFlushBand_Res	1544		/* OUT */
#define	GWID_GpsPage_TrayRequest_Res	1552		/* OUT */
#define	GWID_GpsPage_PaperRequest_Res	1556		/* OUT */
#define	GWID_GpsEv_Fin_PclFontCount	1632		/* IN */
#define	GWID_GpsEv_Req_PclFontCount	1633		/* IN */
#define	GWID_GpsEv_HostWaitData_Res	1718		/* IN */
#define	GWID_GpsEv_HostWaitBuffer_Res	1719		/* IN */
#define	GWID_GpsEv_PrtInfo	1813		/* IN */
#define	GWID_GpsEv_TrayInfo	1815		/* IN */
#define	GWID_GpsEv_BinInfo	1817		/* IN */
#define	GWID_GpsEv_PrtStatus	1819		/* IN */
#define	GWID_GpsEv_GetTotalCounter_Res	1825		/* IN */
#define	GWID_GpsEv_ExtControl_Res	1889		/* IN */
#define	GWID_pmInit	3000		/* IN */
#define	GWID_pmExit	3001		/* IN */
#define	GWID_pmKeyRcvFromPM	3200		/* OUT */
#define	GWID_pmDispSetEmulation	3020		/* IN */
#define	GWID_pmDispSetPrognum	3021		/* IN */
#define	GWID_pmDispSetCurrentIntray	3022		/* IN */
#define	GWID_pmDispSetCurrentIntray2	3023		/* IN */
#define	GWID_pmDispSetStatusID	3030		/* IN */
#define	GWID_pmDispSetContErrID	3032		/* IN */
#define	GWID_pmDispClrContErr	3034		/* IN */
#define	GWID_pmDispSetWarningID	3035		/* IN */
#define	GWID_pmDispClrWarning	3037		/* IN */
#define	GWID_pmDispSetKeydialogue	3039		/* IN */
#define	GWID_pmDispSetKeydialogue2	3041		/* IN */
#define	GWID_pmDispClrKeydialogue	3040		/* IN */
#define	GWID_pmDispSetKeydialogueCode	3212		/* OUT */
#define	GWID_pmDispSetDialogueID	3050		/* IN */
#define	GWID_pmDispClrDialogue	3052		/* IN */
#define	GWID_pmDispSetKeyDialoguePDL	3053		/* IN */
#define	GWID_pmDispClrKeyDialoguePDL	3054		/* IN */
#define	GWID_pmDispSetKeydialoguePDLCode	3213		/* OUT */
#define	GWID_pmMenuInOutFromPM	3230		/* OUT */
#define	GWID_pmMenuAddItem	3060		/* IN */
#define	GWID_pmMenuGetItem	3061		/* IN */
#define	GWID_pmMenuDeleteItem	3062		/* IN */
#define	GWID_pmMenuDeleteItemS	3063		/* IN */
#define	GWID_pmMenuAddDelItemRtn	3231		/* OUT */
#define	GWID_pmMenuGetItemRtn	3232		/* OUT */
#define	GWID_pmMenuInitFinish	3064		/* IN */
#define	GWID_pmMenuExitFinish	3065		/* IN */
#define	GWID_pmMenuExecModule	3233		/* OUT */
#define	GWID_pmMenuCheckFinish	3066		/* IN */
#define	GWID_pmGetString	3080		/* IN */
#define	GWID_pmGetStringRtn	3250		/* OUT */
#define	GWID_gpsColor_gamReq	2214		/* IN */
#define	GWID_gpsColor_tlimEv	2216		/* IN */
#define	GWID_GpsEv_TrayInfoBusy	2579		/* IN */
#define	GWID_GpsEv_GetPrmInfo_Res	2580		/* IN */
#define	GWID_GpsEv_Notify_PageExit	2581		/* IN */
#define	GWID_GpsEv_Xpdl_Notify	2582		/* IN */
#define	GWID_GpsEv_Auth_Res	2583		/* IN */
#define	GWID_GpsEv_Notify_Feed2	2584		/* IN */
#define	GWID_GpsPage_TrayRequest2_Res	2585		/* IN */
#define	GWID_GpsPage_FormGetImageInfo_Res	2586		/* OUT */
#define	GWID_GpsPage_FormOpen_Res	2587		/* OUT */
#define	GWID_GpsEv_Interp_Pause_Req	2588		/* OUT */
#define	GWID_GpsEv_Interp_Resume_Req	2589		/* OUT */
#define	GWID_GpsEv_Notify_CaptureMode	2590		/* IN */
#define	GWID_GpsEv_Notify_EngineState	2591		/* IN */
#define	GWID_GpsEv_Req_JobEnd	2592		/* IN */
#define	GWID_GpsEv_Req_JobResume	2593		/* IN */
#define	GWID_GpsEv_Req_SessionClose	2594		/* IN */
#define	GWID_GpsEv_Req_Proc_Data2	2595		/* IN */
#define	GWID_GpsEv_Notify_PurgedPages	2596		/* IN */
#define	GWID_GpsEv_Notify_StapleComplete	2597		/* IN */
#define	GWID_GpsEv_Req_Fontreset	2598		/* IN */
#define	GWID_GpsEv_TrayInfo2	2599		/* IN */
#define	GWID_GpsEv_GetPrtTotalCounter_Res	2601		/* IN */
#define	GWID_gpsUjobStart	(1111 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobStart	(1111 | GWMSG_RETURN)
#define	GWID_gpsUjobEnd	(1112 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobEnd	(1112 | GWMSG_RETURN)
#define	GWID_gpsUjobCurrent	(1113 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobCurrent	(1113 | GWMSG_RETURN)
#define	GWID_gpsJobGetOptionStr	(1117 | GWMSG_FUNCTION)
#define	GWID_RET_gpsJobGetOptionStr	(1117 | GWMSG_RETURN)
#define	GWID_gpsUjobSetName	(1118 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobSetName	(1118 | GWMSG_RETURN)
#define	GWID_gpsJobNotifyStart	(1121 | GWMSG_FUNCTION)
#define	GWID_RET_gpsJobNotifyStart	(1121 | GWMSG_RETURN)
#define	GWID_gpsJobNotifyExit	(1122 | GWMSG_FUNCTION)
#define	GWID_RET_gpsJobNotifyExit	(1122 | GWMSG_RETURN)
#define	GWID_gpsJobReqProcData	(1123 | GWMSG_FUNCTION)
#define	GWID_RET_gpsJobReqProcData	(1123 | GWMSG_RETURN)
#define	GWID_gpsUjobResetParam	(1126 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsUjobResetParam	(1126 | GWMSG_RETURN)	*/
#define	GWID_gpsJobNotifySendNext	(1129 | GWMSG_FUNCTION)
#define	GWID_RET_gpsJobNotifySendNext	(1129 | GWMSG_RETURN)
#define	GWID_gpsUjobGetParamShm	(1151 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobGetParamShm	(1151 | GWMSG_RETURN)
#define	GWID_gpsUjobSetParamVarShm	(1152 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobSetParamVarShm	(1152 | GWMSG_RETURN)
#define	GWID_gpsUjobGetParamVarShm	(1153 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobGetParamVarShm	(1153 | GWMSG_RETURN)
#define	GWID_gpsUjobStartOld	(1154 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobStartOld	(1154 | GWMSG_RETURN)
#define	GWID_gpsUjobEndOld	(1155 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsUjobEndOld	(1155 | GWMSG_RETURN)	*/
#define	GWID_gpsUjobEnd2	(1156 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUjobEnd2	(1156 | GWMSG_RETURN)
#define	GWID_gpsRgateSetParamVar	(1130 | GWMSG_FUNCTION)
#define	GWID_RET_gpsRgateSetParamVar	(1130 | GWMSG_RETURN)
#define	GWID_gpsRgateGetParamVar	(1131 | GWMSG_FUNCTION)
#define	GWID_RET_gpsRgateGetParamVar	(1131 | GWMSG_RETURN)
#define	GWID_gpsInterpNotifyStart	(1211 | GWMSG_FUNCTION)
#define	GWID_RET_gpsInterpNotifyStart	(1211 | GWMSG_RETURN)
#define	GWID_gpsInterpNotifyExitOld	(1212 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyExitOld	(1212 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpFinishProcData	(1216 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpFinishProcData	(1216 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpReqChange	(1217 | GWMSG_FUNCTION)
#define	GWID_RET_gpsInterpReqChange	(1217 | GWMSG_RETURN)
#define	GWID_gpsInterpNotifyState	(1221 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyState	(1221 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpNotifyStateStr	(1222 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyStateStr	(1222 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpFinishTestprint	(1227 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpFinishTestprint	(1227 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpNotifyOnline	(1228 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyOnline	(1228 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpNotifyOffline	(1229 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyOffline	(1229 | GWMSG_RETURN)	*/
#define	GWID_gpsGetPdlTable	(1232 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetPdlTable	(1232 | GWMSG_RETURN)
#define	GWID_gpsInterpNotifyWarning	(1234 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyWarning	(1234 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpClearWarning	(1235 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpClearWarning	(1235 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpNotifyAlert	(1236 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyAlert	(1236 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpClearAlert	(1237 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpClearAlert	(1237 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpReqEventFeed	(1238 | GWMSG_FUNCTION)
#define	GWID_RET_gpsInterpReqEventFeed	(1238 | GWMSG_RETURN)
#define	GWID_gpsInterpNotifyStartOld	(1251 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsInterpNotifyStartOld	(1251 | GWMSG_RETURN)	*/
#define	GWID_gpsInterpNotifyError	(1252 | GWMSG_FUNCTION)
#define	GWID_RET_gpsInterpNotifyError	(1252 | GWMSG_RETURN)
#define	GWID_gpsInterpNotifyErrorForce	(1253 | GWMSG_FUNCTION)
#define	GWID_RET_gpsInterpNotifyErrorForce	(1253 | GWMSG_RETURN)
#define	GWID_gpsInterpNotifyExit	(1254 | GWMSG_FUNCTION)
#define	GWID_RET_gpsInterpNotifyExit	(1254 | GWMSG_RETURN)
#define	GWID__gpsProgEntry	(1313 | GWMSG_FUNCTION)
#define	GWID_RET__gpsProgEntry	(1313 | GWMSG_RETURN)
#define	GWID__gpsProgDelete	(1314 | GWMSG_FUNCTION)
#define	GWID_RET__gpsProgDelete	(1314 | GWMSG_RETURN)
#define	GWID_gpsProgFinish	(1319 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsProgFinish	(1319 | GWMSG_RETURN)	*/
#define	GWID__gpsProgGetNextFileno	(1398 | GWMSG_FUNCTION)
#define	GWID_RET__gpsProgGetNextFileno	(1398 | GWMSG_RETURN)
#define	GWID__gpsProgInit	(1399 | GWMSG_FUNCTION)
#define	GWID_RET__gpsProgInit	(1399 | GWMSG_RETURN)
#define	GWID_gpsWkSizeTotal	(1411 | GWMSG_FUNCTION)
#define	GWID_RET_gpsWkSizeTotal	(1411 | GWMSG_RETURN)
#define	GWID_gpsWkSizeFree	(1412 | GWMSG_FUNCTION)
#define	GWID_RET_gpsWkSizeFree	(1412 | GWMSG_RETURN)
#define	GWID_gpsWkFree	(1414 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsWkFree	(1414 | GWMSG_RETURN)	*/
#define	GWID_gpsWkMallocReq	(1418 | GWMSG_FUNCTION)
#define	GWID_RET_gpsWkMallocReq	(1418 | GWMSG_RETURN)
#define	GWID__gpsNvWrite	(1421 | GWMSG_FUNCTION)
#define	GWID_RET__gpsNvWrite	(1421 | GWMSG_RETURN)
#define	GWID__gpsNvRead	(1422 | GWMSG_FUNCTION)
#define	GWID_RET__gpsNvRead	(1422 | GWMSG_RETURN)
#define	GWID__gpsNvDelete	(1423 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET__gpsNvDelete	(1423 | GWMSG_RETURN)	*/
#define	GWID__gpsNvFileCheck	(1424 | GWMSG_FUNCTION)
#define	GWID_RET__gpsNvFileCheck	(1424 | GWMSG_RETURN)
#define	GWID_gpsShmGetId	(1431 | GWMSG_FUNCTION)
#define	GWID_RET_gpsShmGetId	(1431 | GWMSG_RETURN)
#define	GWID__gpsGetFontInfo	(1442 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetFontInfo	(1442 | GWMSG_RETURN)
#define	GWID_gpsGetHddInfo	(1443 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetHddInfo	(1443 | GWMSG_RETURN)
#define	GWID_gpsFsInit	(1444 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFsInit	(1444 | GWMSG_RETURN)
#define	GWID__gpsNvInit	(1497 | GWMSG_FUNCTION)
#define	GWID_RET__gpsNvInit	(1497 | GWMSG_RETURN)
#define	GWID__gpsNvShmLock	(1498 | GWMSG_FUNCTION)
#define	GWID_RET__gpsNvShmLock	(1498 | GWMSG_RETURN)
#define	GWID__gpsNvShmUnlock	(1499 | GWMSG_FUNCTION)
#define	GWID_RET__gpsNvShmUnlock	(1499 | GWMSG_RETURN)
#define	GWID_gpsPlotOpen	(1511 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPlotOpen	(1511 | GWMSG_RETURN)
#define	GWID_gpsPlotClose	(1513 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPlotClose	(1513 | GWMSG_RETURN)
#define	GWID_gpsPlotCancel	(1515 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPlotCancel	(1515 | GWMSG_RETURN)
#define	GWID_gpsPlotSetPageParam	(1517 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPlotSetPageParam	(1517 | GWMSG_RETURN)
#define	GWID_gpsPlotChangePageParam	(1519 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPlotChangePageParam	(1519 | GWMSG_RETURN)
#define	GWID_gpsPlotCancelLater	(1521 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPlotCancelLater	(1521 | GWMSG_RETURN)
#define	GWID_gpsFrameCreate	(1531 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFrameCreate	(1531 | GWMSG_RETURN)
#define	GWID_gpsFrameOpen	(1533 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFrameOpen	(1533 | GWMSG_RETURN)
#define	GWID_gpsFrameClose	(1535 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFrameClose	(1535 | GWMSG_RETURN)
#define	GWID_gpsFrameCancel	(1537 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFrameCancel	(1537 | GWMSG_RETURN)
#define	GWID_gpsFramePrint	(1539 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFramePrint	(1539 | GWMSG_RETURN)
#define	GWID_gpsFrameGetBand	(1541 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFrameGetBand	(1541 | GWMSG_RETURN)
#define	GWID_gpsFrameFlushBandOld	(1543 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFrameFlushBandOld	(1543 | GWMSG_RETURN)
#define	GWID_gpsTrayRequest	(1551 | GWMSG_FUNCTION)
#define	GWID_RET_gpsTrayRequest	(1551 | GWMSG_RETURN)
#define	GWID_gpsPaperRequest	(1555 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPaperRequest	(1555 | GWMSG_RETURN)
#define	GWID_gpsReplotInfo	(1561 | GWMSG_FUNCTION)
#define	GWID_RET_gpsReplotInfo	(1561 | GWMSG_RETURN)
#define	GWID_gpsReplotOpen	(1563 | GWMSG_FUNCTION)
#define	GWID_RET_gpsReplotOpen	(1563 | GWMSG_RETURN)
#define	GWID_gpsReplotClose	(1565 | GWMSG_FUNCTION)
#define	GWID_RET_gpsReplotClose	(1565 | GWMSG_RETURN)
#define	GWID_gpsJupiterFrameCreate	(1571 | GWMSG_FUNCTION)
#define	GWID_RET_gpsJupiterFrameCreate	(1571 | GWMSG_RETURN)
#define	GWID_gpsFrameCreateInfo	(1573 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFrameCreateInfo	(1573 | GWMSG_RETURN)
#define	GWID_gpsFramePrefeed	(1575 | GWMSG_FUNCTION)
#define	GWID_RET_gpsFramePrefeed	(1575 | GWMSG_RETURN)
#define	GWID_gpsGetBandWidthBytes	(1581 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetBandWidthBytes	(1581 | GWMSG_RETURN)
#define	GWID_gpsPageDebug	(1599 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPageDebug	(1599 | GWMSG_RETURN)
#define	GWID_gpsPenvInit	(1611 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsPenvInit	(1611 | GWMSG_RETURN)	*/
#define	GWID_gpsPenvReset	(1612 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsPenvReset	(1612 | GWMSG_RETURN)	*/
#define	GWID_gpsPenvOpen	(1613 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvOpen	(1613 | GWMSG_RETURN)
#define	GWID_gpsPenvClose	(1614 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsPenvClose	(1614 | GWMSG_RETURN)	*/
#define	GWID_gpsPenvGetValue	(1615 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvGetValue	(1615 | GWMSG_RETURN)
#define	GWID_gpsPenvSetValue	(1616 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvSetValue	(1616 | GWMSG_RETURN)
#define	GWID_gpsPenvGetDefValue	(1617 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvGetDefValue	(1617 | GWMSG_RETURN)
#define	GWID_gpsPenvSetDefValue	(1618 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvSetDefValue	(1618 | GWMSG_RETURN)
#define	GWID_gpsPenvGetVarNum	(1619 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvGetVarNum	(1619 | GWMSG_RETURN)
#define	GWID_gpsPenvGetVarListSub	(1620 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvGetVarListSub	(1620 | GWMSG_RETURN)
#define	GWID_gpsPenvGetVarInfo	(1621 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvGetVarInfo	(1621 | GWMSG_RETURN)
#define	GWID_gpsPenvGetValueListSub	(1622 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvGetValueListSub	(1622 | GWMSG_RETURN)
#define	GWID_gpsPenvReqPclFontCount	(1631 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvReqPclFontCount	(1631 | GWMSG_RETURN)
#define	GWID_gpsPenvFinishPclFontCount	(1634 | GWMSG_FUNCTION)
#define	GWID_RET_gpsPenvFinishPclFontCount	(1634 | GWMSG_RETURN)
#define	GWID_gpsHostOpen	(1711 | GWMSG_FUNCTION)
#define	GWID_RET_gpsHostOpen	(1711 | GWMSG_RETURN)
#define	GWID_gpsHostClose	(1712 | GWMSG_FUNCTION)
#define	GWID_RET_gpsHostClose	(1712 | GWMSG_RETURN)
#define	GWID_gpsHostNotifyReadOld	(1713 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsHostNotifyReadOld	(1713 | GWMSG_RETURN)	*/
#define	GWID_gpsHostNotifyWriteOld	(1715 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsHostNotifyWriteOld	(1715 | GWMSG_RETURN)	*/
#define	GWID_gpsHostWaitDataReq	(1716 | GWMSG_FUNCTION)
#define	GWID_RET_gpsHostWaitDataReq	(1716 | GWMSG_RETURN)
#define	GWID_gpsHostWaitBufferReq	(1717 | GWMSG_FUNCTION)
#define	GWID_RET_gpsHostWaitBufferReq	(1717 | GWMSG_RETURN)
#define	GWID_gpsHostNotifyRead	(1753 | GWMSG_FUNCTION)
#define	GWID_RET_gpsHostNotifyRead	(1753 | GWMSG_RETURN)
#define	GWID_gpsHostNotifyWrite	(1755 | GWMSG_FUNCTION)
#define	GWID_RET_gpsHostNotifyWrite	(1755 | GWMSG_RETURN)
#define	GWID_gpsGetSysInfoShm	(1811 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetSysInfoShm	(1811 | GWMSG_RETURN)
#define	GWID_gpsGetPrtInfo	(1812 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetPrtInfo	(1812 | GWMSG_RETURN)
#define	GWID__gpsGetTrayInfo	(1814 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetTrayInfo	(1814 | GWMSG_RETURN)
#define	GWID__gpsGetBinInfo	(1816 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetBinInfo	(1816 | GWMSG_RETURN)
#define	GWID_gpsGetPrtStatus	(1818 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetPrtStatus	(1818 | GWMSG_RETURN)
#define	GWID_gpsGetPaperInfo	(1820 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetPaperInfo	(1820 | GWMSG_RETURN)
#define	GWID_gpsGetCtlError	(1821 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetCtlError	(1821 | GWMSG_RETURN)
#define	GWID__gpsGetModelInfo	(1822 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetModelInfo	(1822 | GWMSG_RETURN)
#define	GWID_gpsGetTotalCounterReq	(1824 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetTotalCounterReq	(1824 | GWMSG_RETURN)
#define	GWID_gpsGetBitSw	(1826 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetBitSw	(1826 | GWMSG_RETURN)
#define	GWID_gpsGetInfoTableChanges	(1827 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetInfoTableChanges	(1827 | GWMSG_RETURN)
#define	GWID_gpsGetInfoTableDataOffset	(1828 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetInfoTableDataOffset	(1828 | GWMSG_RETURN)
#define	GWID_gpsGetAppleTalkInfo	(1829 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetAppleTalkInfo	(1829 | GWMSG_RETURN)
#define	GWID_gpsSetAppleTalkInfo	(1830 | GWMSG_FUNCTION)
#define	GWID_RET_gpsSetAppleTalkInfo	(1830 | GWMSG_RETURN)
#define	GWID_gpsGetTrayIdByOptionIndex	(1831 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetTrayIdByOptionIndex	(1831 | GWMSG_RETURN)
#define	GWID_gpsGetBinIdByOptionIndex	(1832 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetBinIdByOptionIndex	(1832 | GWMSG_RETURN)
#define	GWID_gpsDbgCtl	(1899 | GWMSG_FUNCTION)
#define	GWID_RET_gpsDbgCtl	(1899 | GWMSG_RETURN)
#define	GWID_gpsExtCtl	(1898 | GWMSG_FUNCTION)
#define	GWID_RET_gpsExtCtl	(1898 | GWMSG_RETURN)
#define	GWID_gpsUstatusSetParam	(1911 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUstatusSetParam	(1911 | GWMSG_RETURN)
#define	GWID_gpsUstatusGetParam	(1912 | GWMSG_FUNCTION)
#define	GWID_RET_gpsUstatusGetParam	(1912 | GWMSG_RETURN)
#define	GWID_gpsUstatusDevice	(1913 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsUstatusDevice	(1913 | GWMSG_RETURN)	*/
#define	GWID_gpsGetStatusMsg	(1914 | GWMSG_FUNCTION)
#define	GWID_RET_gpsGetStatusMsg	(1914 | GWMSG_RETURN)
#define	GWID_gpsClearErrorMsg	(1915 | GWMSG_FUNCTION)
#define	GWID_RET_gpsClearErrorMsg	(1915 | GWMSG_RETURN)
#define	GWID_gpsSetCentroSignal	(1921 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET_gpsSetCentroSignal	(1921 | GWMSG_RETURN)	*/
#define	GWID__gpsRmtprnTxStart_Hidden	(2311 | GWMSG_FUNCTION)
#define	GWID_RET__gpsRmtprnTxStart_Hidden	(2311 | GWMSG_RETURN)
#define	GWID__gpsRmtprnShmOffset_get	(2312 | GWMSG_FUNCTION)
#define	GWID_RET__gpsRmtprnShmOffset_get	(2312 | GWMSG_RETURN)
#define	GWID_gpsColor_getShrd	(2211 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getShrd	(2211 | GWMSG_RETURN)
#define	GWID_gpsColor_getID	(2212 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getID	(2212 | GWMSG_RETURN)
#define	GWID_gpsColor_gamUpd	(2213 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_gamUpd	(2213 | GWMSG_RETURN)
#define	GWID_gpsColor_getTlimit	(2215 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getTlimit	(2215 | GWMSG_RETURN)
#define	GWID_gpsColor_getRID	(2217 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getRID	(2217 | GWMSG_RETURN)
#define	GWID_gpsColor_getGoff	(2218 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getGoff	(2218 | GWMSG_RETURN)
#define	GWID_gpsColor_getUGval	(2220 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getUGval	(2220 | GWMSG_RETURN)
#define	GWID_gpsColor_getSGval	(2221 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getSGval	(2221 | GWMSG_RETURN)
#define	GWID_gpsColor_get_drawparam	(2222 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_get_drawparam	(2222 | GWMSG_RETURN)
#define	GWID_gpsColor_getShrd2	(2231 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_getShrd2	(2231 | GWMSG_RETURN)
#define	GWID_gpsColor_CalcGAM	(2232 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_CalcGAM	(2232 | GWMSG_RETURN)
#define	GWID_gpsColor_dbgsock	(2299 | GWMSG_FUNCTION)
#define	GWID_RET_gpsColor_dbgsock	(2299 | GWMSG_RETURN)
#define	GWID_gpsMenuGetTestPrnStr	(2401 | GWMSG_FUNCTION)
#define	GWID_RET_gpsMenuGetTestPrnStr	(2401 | GWMSG_RETURN)
#define	GWID__gpsGetHddInfo2	(2500 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetHddInfo2	(2500 | GWMSG_RETURN)
#define	GWID__gpsPlotSetShift	(2501 | GWMSG_FUNCTION)
/* (oneway)	#define	GWID_RET__gpsPlotSetShift	(2501 | GWMSG_RETURN)	*/
#define	GWID__gpsGetPrmInfo	(2502 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPrmInfo	(2502 | GWMSG_RETURN)
#define	GWID__gpsPlotSetPageParam2	(2503 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotSetPageParam2	(2503 | GWMSG_RETURN)
#define	GWID__gpsFrameLoadEnv	(2504 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFrameLoadEnv	(2504 | GWMSG_RETURN)
#define	GWID__gpsPlotChkDirection	(2505 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotChkDirection	(2505 | GWMSG_RETURN)
#define	GWID__gpsFrameGetMultiBandShm	(2506 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFrameGetMultiBandShm	(2506 | GWMSG_RETURN)
#define	GWID__gpsFrameGetMultiBand	(2507 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFrameGetMultiBand	(2507 | GWMSG_RETURN)
#define	GWID__gpsFrameFlushMultiBand	(2508 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFrameFlushMultiBand	(2508 | GWMSG_RETURN)
#define	GWID__gpsFrameChapterSet	(2509 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFrameChapterSet	(2509 | GWMSG_RETURN)
#define	GWID__gpsGetFontInfoWffn	(2510 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetFontInfoWffn	(2510 | GWMSG_RETURN)
#define	GWID__gpsPlotChangeBinding	(2511 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotChangeBinding	(2511 | GWMSG_RETURN)
#define	GWID__gpsGetFlashMemInfo	(2512 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetFlashMemInfo	(2512 | GWMSG_RETURN)
#define	GWID__gpsXpdlMenuEntryDone	(2513 | GWMSG_FUNCTION)
#define	GWID_RET__gpsXpdlMenuEntryDone	(2513 | GWMSG_RETURN)
#define	GWID__gpsReqEventNotify	(2514 | GWMSG_FUNCTION)
#define	GWID_RET__gpsReqEventNotify	(2514 | GWMSG_RETURN)
#define	GWID__gpsFramePrintInfo	(2515 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFramePrintInfo	(2515 | GWMSG_RETURN)
#define	GWID__gpsGetTrayInfoShm	(2516 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetTrayInfoShm	(2516 | GWMSG_RETURN)
#define	GWID__gpsGetBinInfoShm	(2517 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetBinInfoShm	(2517 | GWMSG_RETURN)
#define	GWID__gpsInterpNotifyExt	(2518 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpNotifyExt	(2518 | GWMSG_RETURN)
#define	GWID__gpsColor_getProfileShm	(2519 | GWMSG_FUNCTION)
#define	GWID_RET__gpsColor_getProfileShm	(2519 | GWMSG_RETURN)
#define	GWID__gpsUjobCancel	(2520 | GWMSG_FUNCTION)
#define	GWID_RET__gpsUjobCancel	(2520 | GWMSG_RETURN)
#define	GWID__gpsPenvDataAllocShm	(2521 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPenvDataAllocShm	(2521 | GWMSG_RETURN)
#define	GWID__gpsPenvDataFreeShm	(2522 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPenvDataFreeShm	(2522 | GWMSG_RETURN)
#define	GWID__gpsPenvSetDataShm	(2523 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPenvSetDataShm	(2523 | GWMSG_RETURN)
#define	GWID__gpsPenvGetDataShm	(2524 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPenvGetDataShm	(2524 | GWMSG_RETURN)
#define	GWID__gpsGetPaperWidLen	(2525 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPaperWidLen	(2525 | GWMSG_RETURN)
#define	GWID__gpsAuthReq	(2526 | GWMSG_FUNCTION)
#define	GWID_RET__gpsAuthReq	(2526 | GWMSG_RETURN)
#define	GWID__gpsColor_getPrmVal	(2527 | GWMSG_FUNCTION)
#define	GWID_RET__gpsColor_getPrmVal	(2527 | GWMSG_RETURN)
#define	GWID__gpsInterpReqEventNotify	(2528 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpReqEventNotify	(2528 | GWMSG_RETURN)
#define	GWID__gpsTrayRequest2	(2529 | GWMSG_FUNCTION)
#define	GWID_RET__gpsTrayRequest2	(2529 | GWMSG_RETURN)
#define	GWID__gpsFrameCreateEx	(2530 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFrameCreateEx	(2530 | GWMSG_RETURN)
#define	GWID__gpsReplotInfoEx	(2531 | GWMSG_FUNCTION)
#define	GWID_RET__gpsReplotInfoEx	(2531 | GWMSG_RETURN)
#define	GWID__gpsPlotChkDirection2	(2532 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotChkDirection2	(2532 | GWMSG_RETURN)
#define	GWID__gpsFormGetImageInfo	(2533 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFormGetImageInfo	(2533 | GWMSG_RETURN)
#define	GWID__gpsFormOpen	(2534 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFormOpen	(2534 | GWMSG_RETURN)
#define	GWID__gpsFormClose	(2535 | GWMSG_FUNCTION)
#define	GWID_RET__gpsFormClose	(2535 | GWMSG_RETURN)
#define	GWID__gpsColor_getID2	(2536 | GWMSG_FUNCTION)
#define	GWID_RET__gpsColor_getID2	(2536 | GWMSG_RETURN)
#define	GWID__gpsColor_getGoff2	(2537 | GWMSG_FUNCTION)
#define	GWID_RET__gpsColor_getGoff2	(2537 | GWMSG_RETURN)
#define	GWID__gpsColor_get_drawparam2	(2538 | GWMSG_FUNCTION)
#define	GWID_RET__gpsColor_get_drawparam2	(2538 | GWMSG_RETURN)
#define	GWID__gpsInterpPauseAns	(2539 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpPauseAns	(2539 | GWMSG_RETURN)
#define	GWID__gpsInterpResumeAns	(2540 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpResumeAns	(2540 | GWMSG_RETURN)
#define	GWID__gpsDispSetFreeMsg	(2541 | GWMSG_FUNCTION)
#define	GWID_RET__gpsDispSetFreeMsg	(2541 | GWMSG_RETURN)
#define	GWID__gpsInterpFinishProcData2	(2542 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpFinishProcData2	(2542 | GWMSG_RETURN)
#define	GWID__gpsInterpJobResumeAns	(2543 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpJobResumeAns	(2543 | GWMSG_RETURN)
#define	GWID__gpsInterpJobEndAns	(2544 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpJobEndAns	(2544 | GWMSG_RETURN)
#define	GWID__gpsInterpSessionCloseAns	(2545 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpSessionCloseAns	(2545 | GWMSG_RETURN)
#define	GWID__gpsGetFormTrayInfo	(2546 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetFormTrayInfo	(2546 | GWMSG_RETURN)
#define	GWID__gpsGetFormTrayList	(2547 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetFormTrayList	(2547 | GWMSG_RETURN)
#define	GWID__gpsPlotChangeFormTray	(2548 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotChangeFormTray	(2548 | GWMSG_RETURN)
#define	GWID__gpsGetFormTrayInfoStr	(2549 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetFormTrayInfoStr	(2549 | GWMSG_RETURN)
#define	GWID__gpsGetFormTrayInfoAttr	(2550 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetFormTrayInfoAttr	(2550 | GWMSG_RETURN)
#define	GWID__gpsInterpFinishFontreset	(2551 | GWMSG_FUNCTION)
#define	GWID_RET__gpsInterpFinishFontreset	(2551 | GWMSG_RETURN)
#define	GWID__gpsUjobCancel2	(2552 | GWMSG_FUNCTION)
#define	GWID_RET__gpsUjobCancel2	(2552 | GWMSG_RETURN)
#define	GWID__gpsGetStapleOkSize	(2553 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetStapleOkSize	(2553 | GWMSG_RETURN)
#define	GWID__gpsGetPunchOkSize	(2554 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPunchOkSize	(2554 | GWMSG_RETURN)
#define	GWID__gpsGetStapleMax	(2555 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetStapleMax	(2555 | GWMSG_RETURN)
#define	GWID__gpsGetStaplePos	(2556 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetStaplePos	(2556 | GWMSG_RETURN)
#define	GWID__gpsGetPunchPos	(2557 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPunchPos	(2557 | GWMSG_RETURN)
#define	GWID__gpsGetPaperExitOkSize	(2558 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPaperExitOkSize	(2558 | GWMSG_RETURN)
#define	GWID__gpsGetPunchOkKind	(2559 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPunchOkKind	(2559 | GWMSG_RETURN)
#define	GWID__gpsGetTrayInfo2	(2560 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetTrayInfo2	(2560 | GWMSG_RETURN)
#define	GWID__gpsPlotPrepare	(2561 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotPrepare	(2561 | GWMSG_RETURN)
#define	GWID__gpsGetStapleOkKind	(2562 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetStapleOkKind	(2562 | GWMSG_RETURN)
#define	GWID__gpsGetPaperExitOkKind	(2563 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPaperExitOkKind	(2563 | GWMSG_RETURN)
#define	GWID__gpsPlotGetShmInfo	(2564 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotGetShmInfo	(2564 | GWMSG_RETURN)
#define	GWID__gpsPlotSetPageParamShm	(2565 | GWMSG_FUNCTION)
#define	GWID_RET__gpsPlotSetPageParamShm	(2565 | GWMSG_RETURN)
#define	GWID__gpsChkDuplexOk	(2566 | GWMSG_FUNCTION)
#define	GWID_RET__gpsChkDuplexOk	(2566 | GWMSG_RETURN)
#define	GWID__gpsChkExtPortOk	(2567 | GWMSG_FUNCTION)
#define	GWID_RET__gpsChkExtPortOk	(2567 | GWMSG_RETURN)
#define	GWID__gpsGetPrtStatus2Shm	(2568 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPrtStatus2Shm	(2568 | GWMSG_RETURN)
#define	GWID__gpsGetTrayInfoBusyShm	(2569 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetTrayInfoBusyShm	(2569 | GWMSG_RETURN)
#define	GWID__gpsGetPdlPrintCondition	(2570 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPdlPrintCondition	(2570 | GWMSG_RETURN)
#define	GWID__gpsGetPdfParam	(2571 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPdfParam	(2571 | GWMSG_RETURN)
#define	GWID__gpsSetPdlPrintInfo	(2572 | GWMSG_FUNCTION)
#define	GWID_RET__gpsSetPdlPrintInfo	(2572 | GWMSG_RETURN)
#define	GWID__gpsGetUcpParamShm	(2573 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetUcpParamShm	(2573 | GWMSG_RETURN)
#define	GWID__gpsGetUcpData	(2574 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetUcpData	(2574 | GWMSG_RETURN)
#define	GWID__gpsGetCipherSeed	(2575 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetCipherSeed	(2575 | GWMSG_RETURN)
#define	GWID__gpsGetPdlPrintConditionShm	(2576 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPdlPrintConditionShm	(2576 | GWMSG_RETURN)
#define	GWID__gpsGetHeadRiseMode	(2577 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetHeadRiseMode	(2577 | GWMSG_RETURN)
#define	GWID__gpsGetPrtTotalCounterReq	(2600 | GWMSG_FUNCTION)
#define	GWID_RET__gpsGetPrtTotalCounterReq	(2600 | GWMSG_RETURN)

/******* msg structure section *******/
typedef struct _gwmsg_GpsEv_SysExec {	/* SELF */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		void			(*efunc)();
		gps_sysexec_param_t	param;
	} gwmsg_GpsEv_SysExec_t;

typedef struct _gwmsg_GpsEv_PanelMenuSelect {	/* SELF */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		unsigned short	panel_id;
		unsigned char	item_type;
		unsigned char	menu_type;
	} gwmsg_GpsEv_PanelMenuSelect_t;

typedef struct _gwmsg_GpsEv_Fin_Proc_Data {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int		ujobid;
		int		njobid;
		int		uel_found;
	} gwmsg_GpsEv_Fin_Proc_Data_t;

typedef struct _gwmsg_GpsEv_Req_Cancel_Job {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int		ujobid;
	} gwmsg_GpsEv_Req_Cancel_Job_t;

typedef struct _gwmsg_GpsEv_Req_Exit {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Req_Exit_t;

typedef struct _gwmsg_GpsEv_Req_Proc_Data {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int	njobid;
		int	ujobid;
		int	host_channel;
		int	hostid_in;
		int	hostid_out;
		int	pdl_id;
		int	do_cancel;
		int	uswitch;
		int	reason;
	} gwmsg_GpsEv_Req_Proc_Data_t;

typedef struct _gwmsg_GpsEv_Req_Cancel_Data {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int	ujobid;
	} gwmsg_GpsEv_Req_Cancel_Data_t;

typedef struct _gwmsg_GpsEv_Req_Reset {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int	pdl_id;
		int	uswitch;
		int	reason;
	} gwmsg_GpsEv_Req_Reset_t;

typedef struct _gwmsg_GpsEv_Notify_Online {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Notify_Online_t;

typedef struct _gwmsg_GpsEv_Notify_Offline {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Notify_Offline_t;

typedef struct _gwmsg_GpsEv_Req_Testprint {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int	ujobid;
		int	req;
	} gwmsg_GpsEv_Req_Testprint_t;

typedef struct _gwmsg_GpsEv_Req_Exit_Paper {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Req_Exit_Paper_t;

typedef struct _gwmsg_GpsEv_Notify_Prime_Reset {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Notify_Prime_Reset_t;

typedef struct _gwmsg_GpsEv_Notify_Feed {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		unsigned char	tray;
	} gwmsg_GpsEv_Notify_Feed_t;

typedef struct _gwmsg_GpsEv_Req_XpdlMenuEntry {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Req_XpdlMenuEntry_t;

typedef struct _gwmsg_GpsEv_Req_Program {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int		req;
		int		prog_no;
	} gwmsg_GpsEv_Req_Program_t;

typedef struct _gwmsg_GpsEv_WkMalloc_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		caddr_t		addr;
	} gwmsg_GpsEv_WkMalloc_Res_t;

typedef struct _gwmsg_GpsPage_FrameCreate_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        int result;
        int frame_id;
        int band_count;
        int line_size;
    } gwmsg_GpsPage_FrameCreate_Res_t;

typedef struct _gwmsg_GpsPage_FrameOpen_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        int result;
        int frame_id;
        int band_count;
        int line_size;
    } gwmsg_GpsPage_FrameOpen_Res_t;

typedef struct _gwmsg_GpsPage_FrameGetBand_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        int result;
        int frame_id;
        int band_id;
        int plane_id;
        long band_xdot;
        long band_ydot;
        void* band_addr;
    } gwmsg_GpsPage_FrameGetBand_Res_t;

typedef struct _gwmsg_GpsPage_FrameFlushBand_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        int result;
        int frame_id;
        int band_id;
        int plane_id;
        int band_skip;
    } gwmsg_GpsPage_FrameFlushBand_Res_t;

typedef struct _gwmsg_GpsPage_TrayRequest_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        int result;
        int tray_id;
    } gwmsg_GpsPage_TrayRequest_Res_t;

typedef struct _gwmsg_GpsPage_PaperRequest_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        int result;
        int tray_id;
        int paper_code;
        int paper_width;
        int paper_length;
    } gwmsg_GpsPage_PaperRequest_Res_t;

typedef struct _gwmsg_GpsEv_Fin_PclFontCount {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Fin_PclFontCount_t;

typedef struct _gwmsg_GpsEv_Req_PclFontCount {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_Req_PclFontCount_t;

typedef struct _gwmsg_GpsEv_HostWaitData_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int	host_id;
	} gwmsg_GpsEv_HostWaitData_Res_t;

typedef struct _gwmsg_GpsEv_HostWaitBuffer_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int	host_id;
	} gwmsg_GpsEv_HostWaitBuffer_Res_t;

typedef struct _gwmsg_GpsEv_PrtInfo {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_PrtInfo_t;

typedef struct _gwmsg_GpsEv_TrayInfo {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_TrayInfo_t;

typedef struct _gwmsg_GpsEv_BinInfo {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_BinInfo_t;

typedef struct _gwmsg_GpsEv_PrtStatus {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_GpsEv_PrtStatus_t;

typedef struct _gwmsg_GpsEv_GetTotalCounter_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		long	counter;
	} gwmsg_GpsEv_GetTotalCounter_Res_t;

typedef struct _gwmsg_GpsEv_ExtControl_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		int	f_id;
		int	Result;
	} gwmsg_GpsEv_ExtControl_Res_t;

typedef struct _gwmsg_pmInit {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        long    dummy;
    } gwmsg_pmInit_t;

typedef struct _gwmsg_pmExit {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        long    dummy;
    } gwmsg_pmExit_t;

typedef struct _gwmsg_pmKeyRcvFromPM {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        unsigned short  key_code;
    } gwmsg_pmKeyRcvFromPM_t;

typedef struct _gwmsg_pmDispSetEmulation {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char    cond_exist;
	char    pnum_exist;
	char    tray_exist;
	char    str[16];
    } gwmsg_pmDispSetEmulation_t;

typedef struct _gwmsg_pmDispSetPrognum {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        unsigned short  progid;
    } gwmsg_pmDispSetPrognum_t;

typedef struct _gwmsg_pmDispSetCurrentIntray {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        unsigned short  idTray;
    } gwmsg_pmDispSetCurrentIntray_t;

typedef struct _gwmsg_pmDispSetCurrentIntray2 {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

        unsigned short  idTray;
        unsigned short  idCutOrient;
    } gwmsg_pmDispSetCurrentIntray2_t;

typedef struct _gwmsg_pmDispSetStatusID {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char               filename[FILENAME_LEN];
	unsigned  short    str_id;
	unsigned  char     column;
	unsigned  char     str_size;
    } gwmsg_pmDispSetStatusID_t;

typedef struct _gwmsg_pmDispSetContErrID {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char               filename[FILENAME_LEN];
	unsigned  short    str_id;
	unsigned  char     column;
	unsigned  char     str_size;
    } gwmsg_pmDispSetContErrID_t;

typedef struct _gwmsg_pmDispClrContErr {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	long     dummy;
    } gwmsg_pmDispClrContErr_t;

typedef struct _gwmsg_pmDispSetWarningID {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char               filename[FILENAME_LEN];
	unsigned  short    str_id;
	unsigned  char     column;
	unsigned  char     str_size;
    } gwmsg_pmDispSetWarningID_t;

typedef struct _gwmsg_pmDispClrWarning {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	long     dummy;
    } gwmsg_pmDispClrWarning_t;

typedef struct _gwmsg_pmDispSetKeydialogue {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char               filename[FILENAME_LEN];
	unsigned  short    str1_id;
	unsigned  short    str2_id;
	unsigned  short    str_btn_id;
	unsigned  char     str1_size;
	unsigned  char     str2_size;
	unsigned  char     str_btn_size;
	unsigned  char     btn_code;
    } gwmsg_pmDispSetKeydialogue_t;

typedef struct _gwmsg_pmDispSetKeydialogue2 {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char               filename[FILENAME_LEN];
	unsigned  short    btn1_id;
	unsigned  short    btn2_id;
	unsigned  short    str1_id;
	unsigned  short    str2_id;
	unsigned  char     btn1_size;
	unsigned  char     btn2_size;
	unsigned  char     str1_size;
	unsigned  char     str2_size;
    } gwmsg_pmDispSetKeydialogue2_t;

typedef struct _gwmsg_pmDispClrKeydialogue {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	long     dummy;
    } gwmsg_pmDispClrKeydialogue_t;

typedef struct _gwmsg_pmDispSetKeydialogueCode {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned int    ret_code;
    } gwmsg_pmDispSetKeydialogueCode_t;

typedef struct _gwmsg_pmDispSetDialogueID {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char               filename[FILENAME_LEN];
	unsigned  short    str1_id;
	unsigned  short    str2_id;
	unsigned  char     str1_size;
	unsigned  char     str2_size;
	unsigned  char     time;
    } gwmsg_pmDispSetDialogueID_t;

typedef struct _gwmsg_pmDispClrDialogue {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	long     dummy;
    } gwmsg_pmDispClrDialogue_t;

typedef struct _gwmsg_pmDispSetKeyDialoguePDL {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned  short    str_id[PM_KDLGPDL_MAX_LINE];
	unsigned  short    btn_exist[PM_KDLGPDL_MAX_BTN];
	unsigned  short    btn_id[PM_KDLGPDL_MAX_BTN];
	unsigned  short    btn_code[PM_KDLGPDL_MAX_BTN];
	unsigned  char     time;
	char               filename[FILENAME_LEN];
    } gwmsg_pmDispSetKeyDialoguePDL_t;

typedef struct _gwmsg_pmDispClrKeyDialoguePDL {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	long     dummy;
    } gwmsg_pmDispClrKeyDialoguePDL_t;

typedef struct _gwmsg_pmDispSetKeydialoguePDLCode {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned int    ret_code;
    } gwmsg_pmDispSetKeydialoguePDLCode_t;

typedef struct _gwmsg_pmMenuInOutFromPM {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned  char  event_id;
    } gwmsg_pmMenuInOutFromPM_t;

typedef struct _gwmsg_pmMenuAddItem {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned char    buf[PM_ITEM_SIZE];
    } gwmsg_pmMenuAddItem_t;

typedef struct _gwmsg_pmMenuGetItem {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned short	panel_id;
	unsigned char	ucItem;
	unsigned char	ucMenu;
    } gwmsg_pmMenuGetItem_t;

typedef struct _gwmsg_pmMenuDeleteItem {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned short	panel_id;
	unsigned char	ucItem;
	unsigned char	ucMenu;
    } gwmsg_pmMenuDeleteItem_t;

typedef struct _gwmsg_pmMenuDeleteItemS {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned char	ucMenu;
    } gwmsg_pmMenuDeleteItemS_t;

typedef struct _gwmsg_pmMenuAddDelItemRtn {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char		result;
    } gwmsg_pmMenuAddDelItemRtn_t;

typedef struct _gwmsg_pmMenuGetItemRtn {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned char    buf[PM_ITEM_SIZE];
    } gwmsg_pmMenuGetItemRtn_t;

typedef struct _gwmsg_pmMenuInitFinish {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	long     dummy;
    } gwmsg_pmMenuInitFinish_t;

typedef struct _gwmsg_pmMenuExitFinish {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	long     dummy;
    } gwmsg_pmMenuExitFinish_t;

typedef struct _gwmsg_pmMenuExecModule {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned char    buf[PM_ITEM_SIZE];
    } gwmsg_pmMenuExecModule_t;

typedef struct _gwmsg_pmMenuCheckFinish {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char	 result;
    } gwmsg_pmMenuCheckFinish_t;

typedef struct _gwmsg_pmGetString {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	char     filename[FILENAME_LEN];
	unsigned short	id;
    } gwmsg_pmGetString_t;

typedef struct _gwmsg_pmGetStringRtn {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	unsigned char buf[PM_STRING_LEN_MAX];
    } gwmsg_pmGetStringRtn_t;

typedef struct _gwmsg_gpsColor_gamReq {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_gpsColor_gamReq_t;

typedef struct _gwmsg_gpsColor_tlimEv {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

	} gwmsg_gpsColor_tlimEv_t;

typedef struct _gwmsg_GpsEv_TrayInfoBusy {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

 } gwmsg_GpsEv_TrayInfoBusy_t;

typedef struct _gwmsg_GpsEv_GetPrmInfo_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int f_id;
  int status;
  long data;
 } gwmsg_GpsEv_GetPrmInfo_Res_t;

typedef struct _gwmsg_GpsEv_Notify_PageExit {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  gps_event_pageexit_t pageexit;
 } gwmsg_GpsEv_Notify_PageExit_t;

typedef struct _gwmsg_GpsEv_Xpdl_Notify {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  gps_event_xpdl_notify_t xpdl_notify;
 } gwmsg_GpsEv_Xpdl_Notify_t;

typedef struct _gwmsg_GpsEv_Auth_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int ujobid;
  u_long limitrole;
  int result;
 } gwmsg_GpsEv_Auth_Res_t;

typedef struct _gwmsg_GpsEv_Notify_Feed2 {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  unsigned char tray;
  unsigned char psize;
 } gwmsg_GpsEv_Notify_Feed2_t;

typedef struct _gwmsg_GpsPage_TrayRequest2_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int result;
  int tray_id;
  int paper_code;
  u_long paper_width;
  u_long paper_length;
  u_char res[16];
 } gwmsg_GpsPage_TrayRequest2_Res_t;

typedef struct _gwmsg_GpsPage_FormGetImageInfo_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int result;
  int formno;
  unsigned char paper_code;
  unsigned long paper_width;
  unsigned long paper_length;
  unsigned long frame_width;
  unsigned long frame_length;
  unsigned long band_length;
  unsigned long line_size;
  unsigned long xoffset;
  unsigned long yoffset;
  unsigned short resolution_x;
  unsigned short resolution_y;
  unsigned char color_count;
  unsigned char color;
  unsigned char depth;
  unsigned char rotate;
 } gwmsg_GpsPage_FormGetImageInfo_Res_t;

typedef struct _gwmsg_GpsPage_FormOpen_Res {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int result;
  int frame_id;
  int band_count;
  int line_size;
 } gwmsg_GpsPage_FormOpen_Res_t;

typedef struct _gwmsg_GpsEv_Interp_Pause_Req {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int ujobid;
  unsigned long param;
 } gwmsg_GpsEv_Interp_Pause_Req_t;

typedef struct _gwmsg_GpsEv_Interp_Resume_Req {	/* OUT */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int ujobid;
  unsigned long param;
 } gwmsg_GpsEv_Interp_Resume_Req_t;

typedef struct _gwmsg_GpsEv_Notify_CaptureMode {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int mode;
 } gwmsg_GpsEv_Notify_CaptureMode_t;

typedef struct _gwmsg_GpsEv_Notify_EngineState {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int state;
 } gwmsg_GpsEv_Notify_EngineState_t;

typedef struct _gwmsg_GpsEv_Req_JobEnd {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int reason;
 } gwmsg_GpsEv_Req_JobEnd_t;

typedef struct _gwmsg_GpsEv_Req_JobResume {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

 } gwmsg_GpsEv_Req_JobResume_t;

typedef struct _gwmsg_GpsEv_Req_SessionClose {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int njobid;
  int reason;
 } gwmsg_GpsEv_Req_SessionClose_t;

typedef struct _gwmsg_GpsEv_Req_Proc_Data2 {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int njobid;
  int host_channel;
  int hostid_in;
  int hostid_out;
  int pdlid;
 } gwmsg_GpsEv_Req_Proc_Data2_t;

typedef struct _gwmsg_GpsEv_Notify_PurgedPages {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int ujobid;
  int pages;
 } gwmsg_GpsEv_Notify_PurgedPages_t;

typedef struct _gwmsg_GpsEv_Notify_StapleComplete {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

  int ujobid;
  int result;
 } gwmsg_GpsEv_Notify_StapleComplete_t;

typedef struct _gwmsg_GpsEv_Req_Fontreset {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

 } gwmsg_GpsEv_Req_Fontreset_t;

typedef struct _gwmsg_GpsEv_TrayInfo2 {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

 } gwmsg_GpsEv_TrayInfo2_t;

typedef struct _gwmsg_GpsEv_GetPrtTotalCounter_Res {	/* IN */
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;

		long	blackcnt;
		long	fullcolorcnt;
		int		result;
	} gwmsg_GpsEv_GetPrtTotalCounter_Res_t;


/******* func structure section *******/
typedef struct _gwfcall_gpsUjobStart {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
	int	kind;
	gps_ujob_attr_t	attr;
} gwfcall_gpsUjobStart_t;

typedef struct _gwfret_gpsUjobStart {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobStart_t;

typedef struct _gwfcall_gpsUjobEnd {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	int	kind;
	gps_ujob_attr_t	attr;
} gwfcall_gpsUjobEnd_t;

typedef struct _gwfret_gpsUjobEnd {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobEnd_t;

typedef struct _gwfcall_gpsUjobCurrent {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall_gpsUjobCurrent_t;

typedef struct _gwfret_gpsUjobCurrent {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobCurrent_t;

typedef struct _gwfcall_gpsJobGetOptionStr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
} gwfcall_gpsJobGetOptionStr_t;

typedef struct _gwfret_gpsJobGetOptionStr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
} gwfret_gpsJobGetOptionStr_t;

typedef struct _gwfcall_gpsUjobSetName {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	long	jobname_size;	/* char	jobname [] */
} gwfcall_gpsUjobSetName_t;

typedef struct _gwfret_gpsUjobSetName {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobSetName_t;

typedef struct _gwfcall_gpsJobNotifyStart {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
} gwfcall_gpsJobNotifyStart_t;

typedef struct _gwfret_gpsJobNotifyStart {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsJobNotifyStart_t;

typedef struct _gwfcall_gpsJobNotifyExit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
	pid_t	procid;
} gwfcall_gpsJobNotifyExit_t;

typedef struct _gwfret_gpsJobNotifyExit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsJobNotifyExit_t;

typedef struct _gwfcall_gpsJobReqProcData {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	int	pdl_id;
	int	reason;
} gwfcall_gpsJobReqProcData_t;

typedef struct _gwfret_gpsJobReqProcData {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsJobReqProcData_t;

typedef struct _gwfcall_gpsUjobResetParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall_gpsUjobResetParam_t;

/* no gwfret_gpsUjobResetParam_t definition (oneway) */

typedef struct _gwfcall_gpsJobNotifySendNext {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	param;
} gwfcall_gpsJobNotifySendNext_t;

typedef struct _gwfret_gpsJobNotifySendNext {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsJobNotifySendNext_t;

typedef struct _gwfcall_gpsUjobGetParamShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsUjobGetParamShm_t;

typedef struct _gwfret_gpsUjobGetParamShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	long	size;
} gwfret_gpsUjobGetParamShm_t;

typedef struct _gwfcall_gpsUjobSetParamVarShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall_gpsUjobSetParamVarShm_t;

typedef struct _gwfret_gpsUjobSetParamVarShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobSetParamVarShm_t;

typedef struct _gwfcall_gpsUjobGetParamVarShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall_gpsUjobGetParamVarShm_t;

typedef struct _gwfret_gpsUjobGetParamVarShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobGetParamVarShm_t;

typedef struct _gwfcall_gpsUjobStartOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
	int	kind;
	gps_ujob_attr_t	attr;
} gwfcall_gpsUjobStartOld_t;

typedef struct _gwfret_gpsUjobStartOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobStartOld_t;

typedef struct _gwfcall_gpsUjobEndOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	gps_ujob_attr_t	attr;
} gwfcall_gpsUjobEndOld_t;

/* no gwfret_gpsUjobEndOld_t definition (oneway) */

typedef struct _gwfcall_gpsUjobEnd2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	int	kind;
	gps_ujob_attr_t	attr;
} gwfcall_gpsUjobEnd2_t;

typedef struct _gwfret_gpsUjobEnd2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUjobEnd2_t;

typedef struct _gwfcall_gpsRgateSetParamVar {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	gps_rgateparam_var_t	rgateparam_var;
} gwfcall_gpsRgateSetParamVar_t;

typedef struct _gwfret_gpsRgateSetParamVar {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsRgateSetParamVar_t;

typedef struct _gwfcall_gpsRgateGetParamVar {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	gps_rgateparam_var_t	rgateparam_var;
} gwfcall_gpsRgateGetParamVar_t;

typedef struct _gwfret_gpsRgateGetParamVar {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_rgateparam_var_t	rgateparam_var;
} gwfret_gpsRgateGetParamVar_t;

typedef struct _gwfcall_gpsInterpNotifyStart {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	interp_id;
} gwfcall_gpsInterpNotifyStart_t;

typedef struct _gwfret_gpsInterpNotifyStart {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsInterpNotifyStart_t;

typedef struct _gwfcall_gpsInterpNotifyExitOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	pid_t	procid;
} gwfcall_gpsInterpNotifyExitOld_t;

/* no gwfret_gpsInterpNotifyExitOld_t definition (oneway) */

typedef struct _gwfcall_gpsInterpFinishProcData {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	int	fin;
	int	uel_found;
} gwfcall_gpsInterpFinishProcData_t;

/* no gwfret_gpsInterpFinishProcData_t definition (oneway) */

typedef struct _gwfcall_gpsInterpReqChange {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	interp_id;
	int	uswitch;
} gwfcall_gpsInterpReqChange_t;

typedef struct _gwfret_gpsInterpReqChange {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsInterpReqChange_t;

typedef struct _gwfcall_gpsInterpNotifyState {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	state;
} gwfcall_gpsInterpNotifyState_t;

/* no gwfret_gpsInterpNotifyState_t definition (oneway) */

typedef struct _gwfcall_gpsInterpNotifyStateStr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	str_size;	/* char	str [] */
} gwfcall_gpsInterpNotifyStateStr_t;

/* no gwfret_gpsInterpNotifyStateStr_t definition (oneway) */

typedef struct _gwfcall_gpsInterpFinishTestprint {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall_gpsInterpFinishTestprint_t;

/* no gwfret_gpsInterpFinishTestprint_t definition (oneway) */

typedef struct _gwfcall_gpsInterpNotifyOnline {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsInterpNotifyOnline_t;

/* no gwfret_gpsInterpNotifyOnline_t definition (oneway) */

typedef struct _gwfcall_gpsInterpNotifyOffline {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsInterpNotifyOffline_t;

/* no gwfret_gpsInterpNotifyOffline_t definition (oneway) */

typedef struct _gwfcall_gpsGetPdlTable {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsGetPdlTable_t;

typedef struct _gwfret_gpsGetPdlTable {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	int	num;
} gwfret_gpsGetPdlTable_t;

typedef struct _gwfcall_gpsInterpNotifyWarning {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	code;
} gwfcall_gpsInterpNotifyWarning_t;

/* no gwfret_gpsInterpNotifyWarning_t definition (oneway) */

typedef struct _gwfcall_gpsInterpClearWarning {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsInterpClearWarning_t;

/* no gwfret_gpsInterpClearWarning_t definition (oneway) */

typedef struct _gwfcall_gpsInterpNotifyAlert {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	code;
} gwfcall_gpsInterpNotifyAlert_t;

/* no gwfret_gpsInterpNotifyAlert_t definition (oneway) */

typedef struct _gwfcall_gpsInterpClearAlert {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsInterpClearAlert_t;

/* no gwfret_gpsInterpClearAlert_t definition (oneway) */

typedef struct _gwfcall_gpsInterpReqEventFeed {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsInterpReqEventFeed_t;

typedef struct _gwfret_gpsInterpReqEventFeed {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsInterpReqEventFeed_t;

typedef struct _gwfcall_gpsInterpNotifyStartOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	interp_id;
} gwfcall_gpsInterpNotifyStartOld_t;

/* no gwfret_gpsInterpNotifyStartOld_t definition (oneway) */

typedef struct _gwfcall_gpsInterpNotifyError {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	error;
} gwfcall_gpsInterpNotifyError_t;

typedef struct _gwfret_gpsInterpNotifyError {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsInterpNotifyError_t;

typedef struct _gwfcall_gpsInterpNotifyErrorForce {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	error;
} gwfcall_gpsInterpNotifyErrorForce_t;

typedef struct _gwfret_gpsInterpNotifyErrorForce {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsInterpNotifyErrorForce_t;

typedef struct _gwfcall_gpsInterpNotifyExit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	pid_t	procid;
} gwfcall_gpsInterpNotifyExit_t;

typedef struct _gwfret_gpsInterpNotifyExit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsInterpNotifyExit_t;

typedef struct _gwfcall__gpsProgEntry {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	prog_no;
	long	fname_size;	/* char	fname [] */
	int	fileno;
} gwfcall__gpsProgEntry_t;

typedef struct _gwfret__gpsProgEntry {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsProgEntry_t;

typedef struct _gwfcall__gpsProgDelete {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	prog_no;
} gwfcall__gpsProgDelete_t;

typedef struct _gwfret__gpsProgDelete {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsProgDelete_t;

typedef struct _gwfcall_gpsProgFinish {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsProgFinish_t;

/* no gwfret_gpsProgFinish_t definition (oneway) */

typedef struct _gwfcall__gpsProgGetNextFileno {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	fname_size;	/* char	fname [] */
} gwfcall__gpsProgGetNextFileno_t;

typedef struct _gwfret__gpsProgGetNextFileno {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsProgGetNextFileno_t;

typedef struct _gwfcall__gpsProgInit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsProgInit_t;

typedef struct _gwfret__gpsProgInit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	offset;
} gwfret__gpsProgInit_t;

typedef struct _gwfcall_gpsWkSizeTotal {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsWkSizeTotal_t;

typedef struct _gwfret_gpsWkSizeTotal {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsWkSizeTotal_t;

typedef struct _gwfcall_gpsWkSizeFree {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsWkSizeFree_t;

typedef struct _gwfret_gpsWkSizeFree {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsWkSizeFree_t;

typedef struct _gwfcall_gpsWkFree {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	caddr_t	addr;
} gwfcall_gpsWkFree_t;

/* no gwfret_gpsWkFree_t definition (oneway) */

typedef struct _gwfcall_gpsWkMallocReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	size;
} gwfcall_gpsWkMallocReq_t;

typedef struct _gwfret_gpsWkMallocReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsWkMallocReq_t;

typedef struct _gwfcall__gpsNvWrite {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	fname_size;	/* char	fname [] */
	int	data_size;
} gwfcall__gpsNvWrite_t;

typedef struct _gwfret__gpsNvWrite {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsNvWrite_t;

typedef struct _gwfcall__gpsNvRead {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	fname_size;	/* char	fname [] */
} gwfcall__gpsNvRead_t;

typedef struct _gwfret__gpsNvRead {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	data_size;
} gwfret__gpsNvRead_t;

typedef struct _gwfcall__gpsNvDelete {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	fname_size;	/* char	fname [] */
} gwfcall__gpsNvDelete_t;

/* no gwfret__gpsNvDelete_t definition (oneway) */

typedef struct _gwfcall__gpsNvFileCheck {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	fname_size;	/* char	fname [] */
} gwfcall__gpsNvFileCheck_t;

typedef struct _gwfret__gpsNvFileCheck {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsNvFileCheck_t;

typedef struct _gwfcall_gpsShmGetId {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsShmGetId_t;

typedef struct _gwfret_gpsShmGetId {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsShmGetId_t;

typedef struct _gwfcall__gpsGetFontInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	font;
} gwfcall__gpsGetFontInfo_t;

typedef struct _gwfret__gpsGetFontInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_fontinfo_t	fontinfo;
} gwfret__gpsGetFontInfo_t;

typedef struct _gwfcall_gpsGetHddInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	hdd;
} gwfcall_gpsGetHddInfo_t;

typedef struct _gwfret_gpsGetHddInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_hddinfo_t	hddinfo;
} gwfret_gpsGetHddInfo_t;

typedef struct _gwfcall_gpsFsInit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	hdd;
} gwfcall_gpsFsInit_t;

typedef struct _gwfret_gpsFsInit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFsInit_t;

typedef struct _gwfcall__gpsNvInit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsNvInit_t;

typedef struct _gwfret__gpsNvInit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	nv_offset;
} gwfret__gpsNvInit_t;

typedef struct _gwfcall__gpsNvShmLock {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsNvShmLock_t;

typedef struct _gwfret__gpsNvShmLock {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsNvShmLock_t;

typedef struct _gwfcall__gpsNvShmUnlock {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsNvShmUnlock_t;

typedef struct _gwfret__gpsNvShmUnlock {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsNvShmUnlock_t;

typedef struct _gwfcall_gpsPlotOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	int	openmode;
} gwfcall_gpsPlotOpen_t;

typedef struct _gwfret_gpsPlotOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPlotOpen_t;

typedef struct _gwfcall_gpsPlotClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall_gpsPlotClose_t;

typedef struct _gwfret_gpsPlotClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPlotClose_t;

typedef struct _gwfcall_gpsPlotCancel {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall_gpsPlotCancel_t;

typedef struct _gwfret_gpsPlotCancel {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPlotCancel_t;

typedef struct _gwfcall_gpsPlotSetPageParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pageparam_t	ppageparam;
} gwfcall_gpsPlotSetPageParam_t;

typedef struct _gwfret_gpsPlotSetPageParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPlotSetPageParam_t;

typedef struct _gwfcall_gpsPlotChangePageParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pageparam_t	ppageparam;
} gwfcall_gpsPlotChangePageParam_t;

typedef struct _gwfret_gpsPlotChangePageParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPlotChangePageParam_t;

typedef struct _gwfcall_gpsPlotCancelLater {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall_gpsPlotCancelLater_t;

typedef struct _gwfret_gpsPlotCancelLater {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPlotCancelLater_t;

typedef struct _gwfcall_gpsFrameCreate {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pagemode_t	ppagemode;
} gwfcall_gpsFrameCreate_t;

typedef struct _gwfret_gpsFrameCreate {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFrameCreate_t;

typedef struct _gwfcall_gpsFrameOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall_gpsFrameOpen_t;

typedef struct _gwfret_gpsFrameOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFrameOpen_t;

typedef struct _gwfcall_gpsFrameClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
} gwfcall_gpsFrameClose_t;

typedef struct _gwfret_gpsFrameClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFrameClose_t;

typedef struct _gwfcall_gpsFrameCancel {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
} gwfcall_gpsFrameCancel_t;

typedef struct _gwfret_gpsFrameCancel {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFrameCancel_t;

typedef struct _gwfcall_gpsFramePrint {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
	gps_pageinfo_t	ppageinfo;
	int	force;
} gwfcall_gpsFramePrint_t;

typedef struct _gwfret_gpsFramePrint {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFramePrint_t;

typedef struct _gwfcall_gpsFrameGetBand {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
	int	bandid;
	int	planeid;
} gwfcall_gpsFrameGetBand_t;

typedef struct _gwfret_gpsFrameGetBand {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFrameGetBand_t;

typedef struct _gwfcall_gpsFrameFlushBandOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
	int	bandid;
	int	planeid;
	int	drawn;
} gwfcall_gpsFrameFlushBandOld_t;

typedef struct _gwfret_gpsFrameFlushBandOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFrameFlushBandOld_t;

typedef struct _gwfcall_gpsTrayRequest {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	int	psize;
	int	nodir;
	int	ptype;
	int	trayid;
} gwfcall_gpsTrayRequest_t;

typedef struct _gwfret_gpsTrayRequest {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsTrayRequest_t;

typedef struct _gwfcall_gpsPaperRequest {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	int	psize;
	int	pwidth;
	int	plength;
	int	nodir;
	int	ptype;
	int	trayid;
} gwfcall_gpsPaperRequest_t;

typedef struct _gwfret_gpsPaperRequest {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPaperRequest_t;

typedef struct _gwfcall_gpsReplotInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall_gpsReplotInfo_t;

typedef struct _gwfret_gpsReplotInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_pagemode_t	pagemode;
	gps_pageinfo_t	pageinfo;
	int	force;
} gwfret_gpsReplotInfo_t;

typedef struct _gwfcall_gpsReplotOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall_gpsReplotOpen_t;

typedef struct _gwfret_gpsReplotOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsReplotOpen_t;

typedef struct _gwfcall_gpsReplotClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
} gwfcall_gpsReplotClose_t;

typedef struct _gwfret_gpsReplotClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsReplotClose_t;

typedef struct _gwfcall_gpsJupiterFrameCreate {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pagemode_t	ppagemode;
	gps_pageinfo_t	ppageinfo;
	int	force;
} gwfcall_gpsJupiterFrameCreate_t;

typedef struct _gwfret_gpsJupiterFrameCreate {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsJupiterFrameCreate_t;

typedef struct _gwfcall_gpsFrameCreateInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pagemode_t	ppagemode;
	gps_pageinfo_t	ppageinfo;
	int	force;
} gwfcall_gpsFrameCreateInfo_t;

typedef struct _gwfret_gpsFrameCreateInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFrameCreateInfo_t;

typedef struct _gwfcall_gpsFramePrefeed {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
} gwfcall_gpsFramePrefeed_t;

typedef struct _gwfret_gpsFramePrefeed {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsFramePrefeed_t;

typedef struct _gwfcall_gpsGetBandWidthBytes {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	width;
	int	depth;
} gwfcall_gpsGetBandWidthBytes_t;

typedef struct _gwfret_gpsGetBandWidthBytes {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsGetBandWidthBytes_t;

typedef struct _gwfcall_gpsPageDebug {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	funcid;
} gwfcall_gpsPageDebug_t;

typedef struct _gwfret_gpsPageDebug {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPageDebug_t;

typedef struct _gwfcall_gpsPenvInit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsPenvInit_t;

/* no gwfret_gpsPenvInit_t definition (oneway) */

typedef struct _gwfcall_gpsPenvReset {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsPenvReset_t;

/* no gwfret_gpsPenvReset_t definition (oneway) */

typedef struct _gwfcall_gpsPenvOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	penv_name_size;	/* char	penv_name [] */
} gwfcall_gpsPenvOpen_t;

typedef struct _gwfret_gpsPenvOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPenvOpen_t;

typedef struct _gwfcall_gpsPenvClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
} gwfcall_gpsPenvClose_t;

/* no gwfret_gpsPenvClose_t definition (oneway) */

typedef struct _gwfcall_gpsPenvGetValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
} gwfcall_gpsPenvGetValue_t;

typedef struct _gwfret_gpsPenvGetValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	val;
} gwfret_gpsPenvGetValue_t;

typedef struct _gwfcall_gpsPenvSetValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
	long	val;
} gwfcall_gpsPenvSetValue_t;

typedef struct _gwfret_gpsPenvSetValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPenvSetValue_t;

typedef struct _gwfcall_gpsPenvGetDefValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
} gwfcall_gpsPenvGetDefValue_t;

typedef struct _gwfret_gpsPenvGetDefValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	val;
} gwfret_gpsPenvGetDefValue_t;

typedef struct _gwfcall_gpsPenvSetDefValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
	long	val;
} gwfcall_gpsPenvSetDefValue_t;

typedef struct _gwfret_gpsPenvSetDefValue {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPenvSetDefValue_t;

typedef struct _gwfcall_gpsPenvGetVarNum {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
} gwfcall_gpsPenvGetVarNum_t;

typedef struct _gwfret_gpsPenvGetVarNum {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	func_ret;
} gwfret_gpsPenvGetVarNum_t;

typedef struct _gwfcall_gpsPenvGetVarListSub {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	start;
	long	num;
} gwfcall_gpsPenvGetVarListSub_t;

typedef struct _gwfret_gpsPenvGetVarListSub {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	var_size;	/* long	var [] */
} gwfret_gpsPenvGetVarListSub_t;

typedef struct _gwfcall_gpsPenvGetVarInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
} gwfcall_gpsPenvGetVarInfo_t;

typedef struct _gwfret_gpsPenvGetVarInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	func_ret;
	gps_penv_varinfo_t	varinfo;
} gwfret_gpsPenvGetVarInfo_t;

typedef struct _gwfcall_gpsPenvGetValueListSub {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
	long	start;
	long	num;
} gwfcall_gpsPenvGetValueListSub_t;

typedef struct _gwfret_gpsPenvGetValueListSub {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	value_size;	/* long	value [] */
} gwfret_gpsPenvGetValueListSub_t;

typedef struct _gwfcall_gpsPenvReqPclFontCount {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	force;
} gwfcall_gpsPenvReqPclFontCount_t;

typedef struct _gwfret_gpsPenvReqPclFontCount {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPenvReqPclFontCount_t;

typedef struct _gwfcall_gpsPenvFinishPclFontCount {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsPenvFinishPclFontCount_t;

typedef struct _gwfret_gpsPenvFinishPclFontCount {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsPenvFinishPclFontCount_t;

typedef struct _gwfcall_gpsHostOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	hostid;
} gwfcall_gpsHostOpen_t;

typedef struct _gwfret_gpsHostOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_hostdesc_t	hostdesc;
} gwfret_gpsHostOpen_t;

typedef struct _gwfcall_gpsHostClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_hostdesc_t	hostdesc;
} gwfcall_gpsHostClose_t;

typedef struct _gwfret_gpsHostClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsHostClose_t;

typedef struct _gwfcall_gpsHostNotifyReadOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_hostdesc_t	hostdesc;
	long	read_byte;
} gwfcall_gpsHostNotifyReadOld_t;

/* no gwfret_gpsHostNotifyReadOld_t definition (oneway) */

typedef struct _gwfcall_gpsHostNotifyWriteOld {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_hostdesc_t	hostdesc;
	long	write_byte;
} gwfcall_gpsHostNotifyWriteOld_t;

/* no gwfret_gpsHostNotifyWriteOld_t definition (oneway) */

typedef struct _gwfcall_gpsHostWaitDataReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_hostdesc_t	hostdesc;
} gwfcall_gpsHostWaitDataReq_t;

typedef struct _gwfret_gpsHostWaitDataReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsHostWaitDataReq_t;

typedef struct _gwfcall_gpsHostWaitBufferReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_hostdesc_t	hostdesc;
} gwfcall_gpsHostWaitBufferReq_t;

typedef struct _gwfret_gpsHostWaitBufferReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsHostWaitBufferReq_t;

typedef struct _gwfcall_gpsHostNotifyRead {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_hostdesc_t	hostdesc;
	long	read_byte;
} gwfcall_gpsHostNotifyRead_t;

typedef struct _gwfret_gpsHostNotifyRead {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsHostNotifyRead_t;

typedef struct _gwfcall_gpsHostNotifyWrite {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_hostdesc_t	hostdesc;
	long	write_byte;
} gwfcall_gpsHostNotifyWrite_t;

typedef struct _gwfret_gpsHostNotifyWrite {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsHostNotifyWrite_t;

typedef struct _gwfcall_gpsGetSysInfoShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsGetSysInfoShm_t;

typedef struct _gwfret_gpsGetSysInfoShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	long	size;
} gwfret_gpsGetSysInfoShm_t;

typedef struct _gwfcall_gpsGetPrtInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	notify;
} gwfcall_gpsGetPrtInfo_t;

typedef struct _gwfret_gpsGetPrtInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_prtinfo_t	prtinfo;
} gwfret_gpsGetPrtInfo_t;

typedef struct _gwfcall__gpsGetTrayInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	num;
	int	notify;
} gwfcall__gpsGetTrayInfo_t;

typedef struct _gwfret__gpsGetTrayInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	trayinfo_size;	/* gps_trayinfo_t	trayinfo [] */
} gwfret__gpsGetTrayInfo_t;

typedef struct _gwfcall__gpsGetBinInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	num;
	int	notify;
} gwfcall__gpsGetBinInfo_t;

typedef struct _gwfret__gpsGetBinInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	bininfo_size;	/* gps_bininfo_t	bininfo [] */
} gwfret__gpsGetBinInfo_t;

typedef struct _gwfcall_gpsGetPrtStatus {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	notify;
} gwfcall_gpsGetPrtStatus_t;

typedef struct _gwfret_gpsGetPrtStatus {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_prtstatus_t	prtstatus;
} gwfret_gpsGetPrtStatus_t;

typedef struct _gwfcall_gpsGetPaperInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	paper_id;
	int	notify;
} gwfcall_gpsGetPaperInfo_t;

typedef struct _gwfret_gpsGetPaperInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_paperinfo_t	paperinfo;
} gwfret_gpsGetPaperInfo_t;

typedef struct _gwfcall_gpsGetCtlError {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	num;
} gwfcall_gpsGetCtlError_t;

typedef struct _gwfret_gpsGetCtlError {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	ctl_error_size;	/* gps_ctl_error_t	ctl_error [] */
} gwfret_gpsGetCtlError_t;

typedef struct _gwfcall__gpsGetModelInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	num;
	long	str_size;	/* char	str [] */
	int	valuelen;
} gwfcall__gpsGetModelInfo_t;

typedef struct _gwfret__gpsGetModelInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	val_size;	/* char	val [] */
} gwfret__gpsGetModelInfo_t;

typedef struct _gwfcall_gpsGetTotalCounterReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsGetTotalCounterReq_t;

typedef struct _gwfret_gpsGetTotalCounterReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsGetTotalCounterReq_t;

typedef struct _gwfcall_gpsGetBitSw {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	no;
} gwfcall_gpsGetBitSw_t;

typedef struct _gwfret_gpsGetBitSw {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsGetBitSw_t;

typedef struct _gwfcall_gpsGetInfoTableChanges {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	table_id;
} gwfcall_gpsGetInfoTableChanges_t;

typedef struct _gwfret_gpsGetInfoTableChanges {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	func_ret;
} gwfret_gpsGetInfoTableChanges_t;

typedef struct _gwfcall_gpsGetInfoTableDataOffset {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	table_id;
} gwfcall_gpsGetInfoTableDataOffset_t;

typedef struct _gwfret_gpsGetInfoTableDataOffset {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	long	size;
} gwfret_gpsGetInfoTableDataOffset_t;

typedef struct _gwfcall_gpsGetAppleTalkInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsGetAppleTalkInfo_t;

typedef struct _gwfret_gpsGetAppleTalkInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_appletalk_info_t	atinfo;
} gwfret_gpsGetAppleTalkInfo_t;

typedef struct _gwfcall_gpsSetAppleTalkInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_appletalk_info_t	atinfo;
} gwfcall_gpsSetAppleTalkInfo_t;

typedef struct _gwfret_gpsSetAppleTalkInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsSetAppleTalkInfo_t;

typedef struct _gwfcall_gpsGetTrayIdByOptionIndex {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	tray_index;
} gwfcall_gpsGetTrayIdByOptionIndex_t;

typedef struct _gwfret_gpsGetTrayIdByOptionIndex {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsGetTrayIdByOptionIndex_t;

typedef struct _gwfcall_gpsGetBinIdByOptionIndex {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	bin_index;
} gwfcall_gpsGetBinIdByOptionIndex_t;

typedef struct _gwfret_gpsGetBinIdByOptionIndex {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsGetBinIdByOptionIndex_t;

typedef struct _gwfcall_gpsDbgCtl {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	argc;
	long	argv_size;	/* char	argv [] */
} gwfcall_gpsDbgCtl_t;

typedef struct _gwfret_gpsDbgCtl {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsDbgCtl_t;

typedef struct _gwfcall_gpsExtCtl {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	f_id;
	long	argv_size;	/* char	argv [] */
} gwfcall_gpsExtCtl_t;

typedef struct _gwfret_gpsExtCtl {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	argv_size;	/* char	argv [] */
} gwfret_gpsExtCtl_t;

typedef struct _gwfcall_gpsUstatusSetParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_ustatusparam_t	ustatusparam;
} gwfcall_gpsUstatusSetParam_t;

typedef struct _gwfret_gpsUstatusSetParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsUstatusSetParam_t;

typedef struct _gwfcall_gpsUstatusGetParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsUstatusGetParam_t;

typedef struct _gwfret_gpsUstatusGetParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_ustatusparam_t	ustatusparam;
} gwfret_gpsUstatusGetParam_t;

typedef struct _gwfcall_gpsUstatusDevice {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	code;
} gwfcall_gpsUstatusDevice_t;

/* no gwfret_gpsUstatusDevice_t definition (oneway) */

typedef struct _gwfcall_gpsGetStatusMsg {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	size;
} gwfcall_gpsGetStatusMsg_t;

typedef struct _gwfret_gpsGetStatusMsg {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	msg_size;	/* char	msg [] */
} gwfret_gpsGetStatusMsg_t;

typedef struct _gwfcall_gpsClearErrorMsg {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsClearErrorMsg_t;

typedef struct _gwfret_gpsClearErrorMsg {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsClearErrorMsg_t;

typedef struct _gwfcall_gpsSetCentroSignal {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	char	sig;
} gwfcall_gpsSetCentroSignal_t;

/* no gwfret_gpsSetCentroSignal_t definition (oneway) */

typedef struct _gwfcall__gpsRmtprnTxStart_Hidden {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall__gpsRmtprnTxStart_Hidden_t;

typedef struct _gwfret__gpsRmtprnTxStart_Hidden {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsRmtprnTxStart_Hidden_t;

typedef struct _gwfcall__gpsRmtprnShmOffset_get {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsRmtprnShmOffset_get_t;

typedef struct _gwfret__gpsRmtprnShmOffset_get {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	func_ret;
} gwfret__gpsRmtprnShmOffset_get_t;

typedef struct _gwfcall_gpsColor_getShrd {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsColor_getShrd_t;

typedef struct _gwfret_gpsColor_getShrd {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	func_ret;
} gwfret_gpsColor_getShrd_t;

typedef struct _gwfcall_gpsColor_getID {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	hdpi;
	int	vdpi;
	int	bit;
	int	draw;
} gwfcall_gpsColor_getID_t;

typedef struct _gwfret_gpsColor_getID {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsColor_getID_t;

typedef struct _gwfcall_gpsColor_gamUpd {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsColor_gamUpd_t;

typedef struct _gwfret_gpsColor_gamUpd {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsColor_gamUpd_t;

typedef struct _gwfcall_gpsColor_getTlimit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	mode;
} gwfcall_gpsColor_getTlimit_t;

typedef struct _gwfret_gpsColor_getTlimit {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsColor_getTlimit_t;

typedef struct _gwfcall_gpsColor_getRID {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	modeID;
} gwfcall_gpsColor_getRID_t;

typedef struct _gwfret_gpsColor_getRID {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	rID_size;	/* gps_color_rid_t	rID [] */
} gwfret_gpsColor_getRID_t;

typedef struct _gwfcall_gpsColor_getGoff {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	modeID;
} gwfcall_gpsColor_getGoff_t;

typedef struct _gwfret_gpsColor_getGoff {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_clr_gmfile_t	gmfile;
} gwfret_gpsColor_getGoff_t;

typedef struct _gwfcall_gpsColor_getUGval {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	mode;
	int	col;
} gwfcall_gpsColor_getUGval_t;

typedef struct _gwfret_gpsColor_getUGval {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsColor_getUGval_t;

typedef struct _gwfcall_gpsColor_getSGval {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	modeID;
	int	col;
	int	pnt;
} gwfcall_gpsColor_getSGval_t;

typedef struct _gwfret_gpsColor_getSGval {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsColor_getSGval_t;

typedef struct _gwfcall_gpsColor_get_drawparam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	modeID;
} gwfcall_gpsColor_get_drawparam_t;

typedef struct _gwfret_gpsColor_get_drawparam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_color_drawparam_t	param;
} gwfret_gpsColor_get_drawparam_t;

typedef struct _gwfcall_gpsColor_getShrd2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall_gpsColor_getShrd2_t;

typedef struct _gwfret_gpsColor_getShrd2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	long	func_ret;
} gwfret_gpsColor_getShrd2_t;

typedef struct _gwfcall_gpsColor_CalcGAM {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_clr_calcgam_t	para;
} gwfcall_gpsColor_CalcGAM_t;

typedef struct _gwfret_gpsColor_CalcGAM {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsColor_CalcGAM_t;

typedef struct _gwfcall_gpsColor_dbgsock {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	argc;
	long	argv_size;	/* char	argv [] */
} gwfcall_gpsColor_dbgsock_t;

typedef struct _gwfret_gpsColor_dbgsock {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret_gpsColor_dbgsock_t;

typedef struct _gwfcall_gpsMenuGetTestPrnStr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	testprn_id;
} gwfcall_gpsMenuGetTestPrnStr_t;

typedef struct _gwfret_gpsMenuGetTestPrnStr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_clr_sample_str_t	str_info;
} gwfret_gpsMenuGetTestPrnStr_t;

typedef struct _gwfcall__gpsGetHddInfo2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	hdd;
} gwfcall__gpsGetHddInfo2_t;

typedef struct _gwfret__gpsGetHddInfo2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	status;
	gps_hddinfo2_t	hddinfo2;
} gwfret__gpsGetHddInfo2_t;

typedef struct _gwfcall__gpsPlotSetShift {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	int	shiftoff;
} gwfcall__gpsPlotSetShift_t;

/* no gwfret__gpsPlotSetShift_t definition (oneway) */

typedef struct _gwfcall__gpsGetPrmInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	f_id;
	int	size;
} gwfcall__gpsGetPrmInfo_t;

typedef struct _gwfret__gpsGetPrmInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	status;
	long	data_size;	/* char	data [] */
} gwfret__gpsGetPrmInfo_t;

typedef struct _gwfcall__gpsPlotSetPageParam2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pageparam2_t	ppageparam2;
} gwfcall__gpsPlotSetPageParam2_t;

typedef struct _gwfret__gpsPlotSetPageParam2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
	ulong	flag;
} gwfret__gpsPlotSetPageParam2_t;

typedef struct _gwfcall__gpsFrameLoadEnv {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
} gwfcall__gpsFrameLoadEnv_t;

typedef struct _gwfret__gpsFrameLoadEnv {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsFrameLoadEnv_t;

typedef struct _gwfcall__gpsPlotChkDirection {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_chkdirprm_t	condition;
} gwfcall__gpsPlotChkDirection_t;

typedef struct _gwfret__gpsPlotChkDirection {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	direction;
	int	slantdirection;
} gwfret__gpsPlotChkDirection_t;

typedef struct _gwfcall__gpsFrameGetMultiBandShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsFrameGetMultiBandShm_t;

typedef struct _gwfret__gpsFrameGetMultiBandShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	int	num;
} gwfret__gpsFrameGetMultiBandShm_t;

typedef struct _gwfcall__gpsFrameGetMultiBand {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
	int	bandid;
} gwfcall__gpsFrameGetMultiBand_t;

typedef struct _gwfret__gpsFrameGetMultiBand {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsFrameGetMultiBand_t;

typedef struct _gwfcall__gpsFrameFlushMultiBand {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
	int	bandid;
} gwfcall__gpsFrameFlushMultiBand_t;

typedef struct _gwfret__gpsFrameFlushMultiBand {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsFrameFlushMultiBand_t;

typedef struct _gwfcall__gpsFrameChapterSet {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
	u_char	mode;
	u_char	paper_type;
} gwfcall__gpsFrameChapterSet_t;

typedef struct _gwfret__gpsFrameChapterSet {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsFrameChapterSet_t;

typedef struct _gwfcall__gpsGetFontInfoWffn {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	font;
} gwfcall__gpsGetFontInfoWffn_t;

typedef struct _gwfret__gpsGetFontInfoWffn {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_fontinfo_wffn_t	fontinfo_wffn;
} gwfret__gpsGetFontInfoWffn_t;

typedef struct _gwfcall__gpsPlotChangeBinding {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	u_char	binding;
} gwfcall__gpsPlotChangeBinding_t;

typedef struct _gwfret__gpsPlotChangeBinding {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsPlotChangeBinding_t;

typedef struct _gwfcall__gpsGetFlashMemInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	fm_id;
} gwfcall__gpsGetFlashMemInfo_t;

typedef struct _gwfret__gpsGetFlashMemInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	status;
	gps_flashmem_info_t	info;
} gwfret__gpsGetFlashMemInfo_t;

typedef struct _gwfcall__gpsXpdlMenuEntryDone {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsXpdlMenuEntryDone_t;

typedef struct _gwfret__gpsXpdlMenuEntryDone {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsXpdlMenuEntryDone_t;

typedef struct _gwfcall__gpsReqEventNotify {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	req;
	u_long	ev;
} gwfcall__gpsReqEventNotify_t;

typedef struct _gwfret__gpsReqEventNotify {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	u_long	res;
} gwfret__gpsReqEventNotify_t;

typedef struct _gwfcall__gpsFramePrintInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	frameid;
	gps_pageinfo2_t	ppageinfo2;
} gwfcall__gpsFramePrintInfo_t;

typedef struct _gwfret__gpsFramePrintInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	ulong	flag;
} gwfret__gpsFramePrintInfo_t;

typedef struct _gwfcall__gpsGetTrayInfoShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	num;
	int	notify;
} gwfcall__gpsGetTrayInfoShm_t;

typedef struct _gwfret__gpsGetTrayInfoShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	ret_code;
	long	offset;
	int	ret_num;
} gwfret__gpsGetTrayInfoShm_t;

typedef struct _gwfcall__gpsGetBinInfoShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	num;
	int	notify;
} gwfcall__gpsGetBinInfoShm_t;

typedef struct _gwfret__gpsGetBinInfoShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	ret_code;
	long	offset;
	int	ret_num;
} gwfret__gpsGetBinInfoShm_t;

typedef struct _gwfcall__gpsInterpNotifyExt {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ext_id;
	gps_interp_notify_ext_t	interp_ext;
} gwfcall__gpsInterpNotifyExt_t;

typedef struct _gwfret__gpsInterpNotifyExt {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	status;
} gwfret__gpsInterpNotifyExt_t;

typedef struct _gwfcall__gpsColor_getProfileShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsColor_getProfileShm_t;

typedef struct _gwfret__gpsColor_getProfileShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	long	num;
} gwfret__gpsColor_getProfileShm_t;

typedef struct _gwfcall__gpsUjobCancel {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall__gpsUjobCancel_t;

typedef struct _gwfret__gpsUjobCancel {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	status;
} gwfret__gpsUjobCancel_t;

typedef struct _gwfcall__gpsPenvDataAllocShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	size;
} gwfcall__gpsPenvDataAllocShm_t;

typedef struct _gwfret__gpsPenvDataAllocShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	int	result;
} gwfret__gpsPenvDataAllocShm_t;

typedef struct _gwfcall__gpsPenvDataFreeShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	offset;
} gwfcall__gpsPenvDataFreeShm_t;

typedef struct _gwfret__gpsPenvDataFreeShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsPenvDataFreeShm_t;

typedef struct _gwfcall__gpsPenvSetDataShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
	long	offset;
	long	val_size;
} gwfcall__gpsPenvSetDataShm_t;

typedef struct _gwfret__gpsPenvSetDataShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsPenvSetDataShm_t;

typedef struct _gwfcall__gpsPenvGetDataShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	penv;
	long	var;
	long	in_size;
} gwfcall__gpsPenvGetDataShm_t;

typedef struct _gwfret__gpsPenvGetDataShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	long	out_size;
	int	result;
} gwfret__gpsPenvGetDataShm_t;

typedef struct _gwfcall__gpsGetPaperWidLen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	psize;
} gwfcall__gpsGetPaperWidLen_t;

typedef struct _gwfret__gpsGetPaperWidLen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	u_short	pwidth;
	u_short	plength;
} gwfret__gpsGetPaperWidLen_t;

typedef struct _gwfcall__gpsAuthReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall__gpsAuthReq_t;

typedef struct _gwfret__gpsAuthReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	status;
} gwfret__gpsAuthReq_t;

typedef struct _gwfcall__gpsColor_getPrmVal {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	param;
} gwfcall__gpsColor_getPrmVal_t;

typedef struct _gwfret__gpsColor_getPrmVal {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	u_long	val;
	int	result;
} gwfret__gpsColor_getPrmVal_t;

typedef struct _gwfcall__gpsInterpReqEventNotify {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	req;
} gwfcall__gpsInterpReqEventNotify_t;

typedef struct _gwfret__gpsInterpReqEventNotify {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsInterpReqEventNotify_t;

typedef struct _gwfcall__gpsTrayRequest2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	int	psize;
	int	nodir;
	int	ptype;
	int	tray;
	gps_trayrequestEx_t	pTrayReq;
} gwfcall__gpsTrayRequest2_t;

typedef struct _gwfret__gpsTrayRequest2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsTrayRequest2_t;

typedef struct _gwfcall__gpsFrameCreateEx {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pagemode2_t	ppagemode2;
	gps_pageinfo2_t	ppageinfo2;
} gwfcall__gpsFrameCreateEx_t;

typedef struct _gwfret__gpsFrameCreateEx {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsFrameCreateEx_t;

typedef struct _gwfcall__gpsReplotInfoEx {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall__gpsReplotInfoEx_t;

typedef struct _gwfret__gpsReplotInfoEx {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_pagemode2_t	ppagemode2;
	gps_pageinfo2_t	ppageinfo2;
	int	result;
} gwfret__gpsReplotInfoEx_t;

typedef struct _gwfcall__gpsPlotChkDirection2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_chkdirprm_t	condition;
	gps_chkdirprmEx_t	condEx;
} gwfcall__gpsPlotChkDirection2_t;

typedef struct _gwfret__gpsPlotChkDirection2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	direction;
	int	slantdirection;
} gwfret__gpsPlotChkDirection2_t;

typedef struct _gwfcall__gpsFormGetImageInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	int	formno;
} gwfcall__gpsFormGetImageInfo_t;

typedef struct _gwfret__gpsFormGetImageInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsFormGetImageInfo_t;

typedef struct _gwfcall__gpsFormOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	int	formno;
} gwfcall__gpsFormOpen_t;

typedef struct _gwfret__gpsFormOpen {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsFormOpen_t;

typedef struct _gwfcall__gpsFormClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	formno;
	int	frameid;
} gwfcall__gpsFormClose_t;

typedef struct _gwfret__gpsFormClose {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsFormClose_t;

typedef struct _gwfcall__gpsColor_getID2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	hdpi;
	int	vdpi;
	int	bit;
	int	draw;
	u_char	prt;
	u_char	paper;
} gwfcall__gpsColor_getID2_t;

typedef struct _gwfret__gpsColor_getID2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	modeID;
} gwfret__gpsColor_getID2_t;

typedef struct _gwfcall__gpsColor_getGoff2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	modeID;
} gwfcall__gpsColor_getGoff2_t;

typedef struct _gwfret__gpsColor_getGoff2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_nclr_gmfile_t	gmfile;
} gwfret__gpsColor_getGoff2_t;

typedef struct _gwfcall__gpsColor_get_drawparam2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	modeID;
} gwfcall__gpsColor_get_drawparam2_t;

typedef struct _gwfret__gpsColor_get_drawparam2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_nclr_drawparam_t	param;
} gwfret__gpsColor_get_drawparam2_t;

typedef struct _gwfcall__gpsInterpPauseAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	int	result;
	ulong	param;
} gwfcall__gpsInterpPauseAns_t;

typedef struct _gwfret__gpsInterpPauseAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsInterpPauseAns_t;

typedef struct _gwfcall__gpsInterpResumeAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	int	result;
	ulong	param;
} gwfcall__gpsInterpResumeAns_t;

typedef struct _gwfret__gpsInterpResumeAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsInterpResumeAns_t;

typedef struct _gwfcall__gpsDispSetFreeMsg {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_freemsg_t	freemsg;
} gwfcall__gpsDispSetFreeMsg_t;

typedef struct _gwfret__gpsDispSetFreeMsg {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsDispSetFreeMsg_t;

typedef struct _gwfcall__gpsInterpFinishProcData2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
} gwfcall__gpsInterpFinishProcData2_t;

typedef struct _gwfret__gpsInterpFinishProcData2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsInterpFinishProcData2_t;

typedef struct _gwfcall__gpsInterpJobResumeAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	result;
} gwfcall__gpsInterpJobResumeAns_t;

typedef struct _gwfret__gpsInterpJobResumeAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsInterpJobResumeAns_t;

typedef struct _gwfcall__gpsInterpJobEndAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	result;
} gwfcall__gpsInterpJobEndAns_t;

typedef struct _gwfret__gpsInterpJobEndAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsInterpJobEndAns_t;

typedef struct _gwfcall__gpsInterpSessionCloseAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
	int	result;
} gwfcall__gpsInterpSessionCloseAns_t;

typedef struct _gwfret__gpsInterpSessionCloseAns {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsInterpSessionCloseAns_t;

typedef struct _gwfcall__gpsGetFormTrayInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	formid;
	long	penvid;
} gwfcall__gpsGetFormTrayInfo_t;

typedef struct _gwfret__gpsGetFormTrayInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_formtray_info_t	formtrayinfo;
} gwfret__gpsGetFormTrayInfo_t;

typedef struct _gwfcall__gpsGetFormTrayList {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsGetFormTrayList_t;

typedef struct _gwfret__gpsGetFormTrayList {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_formtray_list_t	formtraylist;
} gwfret__gpsGetFormTrayList_t;

typedef struct _gwfcall__gpsPlotChangeFormTray {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	int	formid;
} gwfcall__gpsPlotChangeFormTray_t;

typedef struct _gwfret__gpsPlotChangeFormTray {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	result;
} gwfret__gpsPlotChangeFormTray_t;

typedef struct _gwfcall__gpsGetFormTrayInfoStr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	formid;
} gwfcall__gpsGetFormTrayInfoStr_t;

typedef struct _gwfret__gpsGetFormTrayInfoStr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_formtray_info_str_t	formtrayinfostr;
} gwfret__gpsGetFormTrayInfoStr_t;

typedef struct _gwfcall__gpsGetFormTrayInfoAttr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	formid;
} gwfcall__gpsGetFormTrayInfoAttr_t;

typedef struct _gwfret__gpsGetFormTrayInfoAttr {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_formtray_info_attr_t	formtrayinfoattr;
} gwfret__gpsGetFormTrayInfoAttr_t;

typedef struct _gwfcall__gpsInterpFinishFontreset {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsInterpFinishFontreset_t;

typedef struct _gwfret__gpsInterpFinishFontreset {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsInterpFinishFontreset_t;

typedef struct _gwfcall__gpsUjobCancel2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	njobid;
} gwfcall__gpsUjobCancel2_t;

typedef struct _gwfret__gpsUjobCancel2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsUjobCancel2_t;

typedef struct _gwfcall__gpsGetStapleOkSize {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	p_size;
	u_short	p_width;
	u_short	p_length;
	u_char	position;
} gwfcall__gpsGetStapleOkSize_t;

typedef struct _gwfret__gpsGetStapleOkSize {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	func_ret;
} gwfret__gpsGetStapleOkSize_t;

typedef struct _gwfcall__gpsGetPunchOkSize {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	p_size;
	u_short	p_width;
	u_short	p_length;
} gwfcall__gpsGetPunchOkSize_t;

typedef struct _gwfret__gpsGetPunchOkSize {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	func_ret;
} gwfret__gpsGetPunchOkSize_t;

typedef struct _gwfcall__gpsGetStapleMax {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	p_size;
	u_char	p_kind;
	u_short	p_width;
	u_short	p_length;
	u_char	punch;
	u_char	position;
} gwfcall__gpsGetStapleMax_t;

typedef struct _gwfret__gpsGetStapleMax {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	func_ret;
} gwfret__gpsGetStapleMax_t;

typedef struct _gwfcall__gpsGetStaplePos {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsGetStaplePos_t;

typedef struct _gwfret__gpsGetStaplePos {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_long	func_ret;
} gwfret__gpsGetStaplePos_t;

typedef struct _gwfcall__gpsGetPunchPos {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsGetPunchPos_t;

typedef struct _gwfret__gpsGetPunchPos {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_long	func_ret;
} gwfret__gpsGetPunchPos_t;

typedef struct _gwfcall__gpsGetPaperExitOkSize {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	p_size;
	u_short	p_width;
	u_short	p_length;
	u_char	face;
	u_char	trayno;
} gwfcall__gpsGetPaperExitOkSize_t;

typedef struct _gwfret__gpsGetPaperExitOkSize {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_long	func_ret;
} gwfret__gpsGetPaperExitOkSize_t;

typedef struct _gwfcall__gpsGetPunchOkKind {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	p_kind;
} gwfcall__gpsGetPunchOkKind_t;

typedef struct _gwfret__gpsGetPunchOkKind {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	func_ret;
} gwfret__gpsGetPunchOkKind_t;

typedef struct _gwfcall__gpsGetTrayInfo2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	num;
	int	notify;
} gwfcall__gpsGetTrayInfo2_t;

typedef struct _gwfret__gpsGetTrayInfo2 {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	trayinfo_size;	/* gps_trayinfo_t	trayinfo [] */
} gwfret__gpsGetTrayInfo2_t;

typedef struct _gwfcall__gpsPlotPrepare {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
	gps_plotprepareparam_t	param;
} gwfcall__gpsPlotPrepare_t;

typedef struct _gwfret__gpsPlotPrepare {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsPlotPrepare_t;

typedef struct _gwfcall__gpsGetStapleOkKind {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	p_kind;
	u_char	position;
} gwfcall__gpsGetStapleOkKind_t;

typedef struct _gwfret__gpsGetStapleOkKind {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	func_ret;
} gwfret__gpsGetStapleOkKind_t;

typedef struct _gwfcall__gpsGetPaperExitOkKind {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_char	p_kind;
	u_char	face;
	u_char	trayno;
} gwfcall__gpsGetPaperExitOkKind_t;

typedef struct _gwfret__gpsGetPaperExitOkKind {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	u_long	func_ret;
} gwfret__gpsGetPaperExitOkKind_t;

typedef struct _gwfcall__gpsPlotGetShmInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsPlotGetShmInfo_t;

typedef struct _gwfret__gpsPlotGetShmInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	long	size;
} gwfret__gpsPlotGetShmInfo_t;

typedef struct _gwfcall__gpsPlotSetPageParamShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
} gwfcall__gpsPlotSetPageParamShm_t;

typedef struct _gwfret__gpsPlotSetPageParamShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsPlotSetPageParamShm_t;

typedef struct _gwfcall__gpsChkDuplexOk {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_chkduplexok_t	pchkduplexok;
} gwfcall__gpsChkDuplexOk_t;

typedef struct _gwfret__gpsChkDuplexOk {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsChkDuplexOk_t;

typedef struct _gwfcall__gpsChkExtPortOk {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsChkExtPortOk_t;

typedef struct _gwfret__gpsChkExtPortOk {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsChkExtPortOk_t;

typedef struct _gwfcall__gpsGetPrtStatus2Shm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	notify;
} gwfcall__gpsGetPrtStatus2Shm_t;

typedef struct _gwfret__gpsGetPrtStatus2Shm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
} gwfret__gpsGetPrtStatus2Shm_t;

typedef struct _gwfcall__gpsGetTrayInfoBusyShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	num;
	int	notify;
} gwfcall__gpsGetTrayInfoBusyShm_t;

typedef struct _gwfret__gpsGetTrayInfoBusyShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	int	ret_code;
	long	offset;
	int	ret_num;
} gwfret__gpsGetTrayInfoBusyShm_t;

typedef struct _gwfcall__gpsGetPdlPrintCondition {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall__gpsGetPdlPrintCondition_t;

typedef struct _gwfret__gpsGetPdlPrintCondition {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_pdl_printcondition_t	cond;
	gps_pdl_media_printcondition_t	media;
} gwfret__gpsGetPdlPrintCondition_t;

typedef struct _gwfcall__gpsGetPdfParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall__gpsGetPdfParam_t;

typedef struct _gwfret__gpsGetPdfParam {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_pdf_param_t	param;
} gwfret__gpsGetPdfParam_t;

typedef struct _gwfcall__gpsSetPdlPrintInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	plotid;
	gps_pdl_printinfo_t	prtinfo;
} gwfcall__gpsSetPdlPrintInfo_t;

typedef struct _gwfret__gpsSetPdlPrintInfo {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsSetPdlPrintInfo_t;

typedef struct _gwfcall__gpsGetUcpParamShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall__gpsGetUcpParamShm_t;

typedef struct _gwfret__gpsGetUcpParamShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	offset;
	int	result;
} gwfret__gpsGetUcpParamShm_t;

typedef struct _gwfcall__gpsGetUcpData {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	gps_ucp_info_t	ucpinfo;
} gwfcall__gpsGetUcpData_t;

typedef struct _gwfret__gpsGetUcpData {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_ucp_data_t	ucpdata;
	int	result;
} gwfret__gpsGetUcpData_t;

typedef struct _gwfcall__gpsGetCipherSeed {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	size;
} gwfcall__gpsGetCipherSeed_t;

typedef struct _gwfret__gpsGetCipherSeed {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	long	seed_size;	/* u_char	seed [] */
} gwfret__gpsGetCipherSeed_t;

typedef struct _gwfcall__gpsGetPdlPrintConditionShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	ujobid;
} gwfcall__gpsGetPdlPrintConditionShm_t;

typedef struct _gwfret__gpsGetPdlPrintConditionShm {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	u_long	offset;
} gwfret__gpsGetPdlPrintConditionShm_t;

typedef struct _gwfcall__gpsGetHeadRiseMode {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsGetHeadRiseMode_t;

typedef struct _gwfret__gpsGetHeadRiseMode {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
	gps_headrise_mode_t	mode;
	int	result;
} gwfret__gpsGetHeadRiseMode_t;

typedef struct _gwfcall__gpsGetPrtTotalCounterReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
} gwfcall__gpsGetPrtTotalCounterReq_t;

typedef struct _gwfret__gpsGetPrtTotalCounterReq {
    unsigned short	type;
    unsigned short	length;
    pid_t		pid;
    unsigned long	fid;
	int	func_ret;
} gwfret__gpsGetPrtTotalCounterReq_t;


/******* func decl section *******/
int	gpsUjobStart( gwmsg_client_t* client, int njobid, int kind, const gps_ujob_attr_t *attr );
int	gpsUjobEnd( gwmsg_client_t* client, int ujobid, int kind, const gps_ujob_attr_t *attr );
int	gpsUjobCurrent( gwmsg_client_t* client, int ujobid );
int	gpsJobGetOptionStr( gwmsg_client_t* client, int njobid, long *offset );
int	gpsUjobSetName( gwmsg_client_t* client, int ujobid, const char *jobname, long jobname_size );
int	gpsJobNotifyStart( gwmsg_client_t* client, int njobid );
int	gpsJobNotifyExit( gwmsg_client_t* client, int njobid, pid_t procid );
int	gpsJobReqProcData( gwmsg_client_t* client, int ujobid, int pdl_id, int reason );
void	gpsUjobResetParam( gwmsg_client_t* client, int ujobid );
int	gpsJobNotifySendNext( gwmsg_client_t* client, int param );
int	gpsUjobGetParamShm( gwmsg_client_t* client, long *offset, long *size );
int	gpsUjobSetParamVarShm( gwmsg_client_t* client, int ujobid );
int	gpsUjobGetParamVarShm( gwmsg_client_t* client, int ujobid );
int	gpsUjobStartOld( gwmsg_client_t* client, int njobid, int kind, const gps_ujob_attr_t *attr );
void	gpsUjobEndOld( gwmsg_client_t* client, int ujobid, const gps_ujob_attr_t *attr );
int	gpsUjobEnd2( gwmsg_client_t* client, int ujobid, int kind, const gps_ujob_attr_t *attr );
int	gpsRgateSetParamVar( gwmsg_client_t* client, int ujobid, const gps_rgateparam_var_t *rgateparam_var );
int	gpsRgateGetParamVar( gwmsg_client_t* client, int ujobid, gps_rgateparam_var_t *rgateparam_var );
int	gpsInterpNotifyStart( gwmsg_client_t* client, int interp_id );
void	gpsInterpNotifyExitOld( gwmsg_client_t* client, pid_t procid );
void	gpsInterpFinishProcData( gwmsg_client_t* client, int ujobid, int fin, int uel_found );
int	gpsInterpReqChange( gwmsg_client_t* client, int interp_id, int uswitch );
void	gpsInterpNotifyState( gwmsg_client_t* client, int state );
void	gpsInterpNotifyStateStr( gwmsg_client_t* client, const char *str, long str_size );
void	gpsInterpFinishTestprint( gwmsg_client_t* client, int ujobid );
void	gpsInterpNotifyOnline( gwmsg_client_t* client );
void	gpsInterpNotifyOffline( gwmsg_client_t* client );
int	gpsGetPdlTable( gwmsg_client_t* client, long *offset, int *num );
void	gpsInterpNotifyWarning( gwmsg_client_t* client, int code );
void	gpsInterpClearWarning( gwmsg_client_t* client );
void	gpsInterpNotifyAlert( gwmsg_client_t* client, int code );
void	gpsInterpClearAlert( gwmsg_client_t* client );
int	gpsInterpReqEventFeed( gwmsg_client_t* client );
void	gpsInterpNotifyStartOld( gwmsg_client_t* client, int interp_id );
int	gpsInterpNotifyError( gwmsg_client_t* client, int error );
int	gpsInterpNotifyErrorForce( gwmsg_client_t* client, int error );
int	gpsInterpNotifyExit( gwmsg_client_t* client, pid_t procid );
int	_gpsProgEntry( gwmsg_client_t* client, int prog_no, const char *fname, long fname_size, int fileno );
int	_gpsProgDelete( gwmsg_client_t* client, int prog_no );
void	gpsProgFinish( gwmsg_client_t* client );
int	_gpsProgGetNextFileno( gwmsg_client_t* client, const char *fname, long fname_size );
int	_gpsProgInit( gwmsg_client_t* client, int *offset );
int	gpsWkSizeTotal( gwmsg_client_t* client );
int	gpsWkSizeFree( gwmsg_client_t* client );
void	gpsWkFree( gwmsg_client_t* client, caddr_t addr );
int	gpsWkMallocReq( gwmsg_client_t* client, long size );
int	_gpsNvWrite( gwmsg_client_t* client, const char *fname, long fname_size, int data_size );
int	_gpsNvRead( gwmsg_client_t* client, const char *fname, long fname_size, long *data_size );
void	_gpsNvDelete( gwmsg_client_t* client, const char *fname, long fname_size );
int	_gpsNvFileCheck( gwmsg_client_t* client, const char *fname, long fname_size );
int	gpsShmGetId( gwmsg_client_t* client );
int	_gpsGetFontInfo( gwmsg_client_t* client, int font, gps_fontinfo_t *fontinfo );
int	gpsGetHddInfo( gwmsg_client_t* client, int hdd, gps_hddinfo_t *hddinfo );
int	gpsFsInit( gwmsg_client_t* client, int hdd );
int	_gpsNvInit( gwmsg_client_t* client, int *nv_offset );
int	_gpsNvShmLock( gwmsg_client_t* client );
int	_gpsNvShmUnlock( gwmsg_client_t* client );
int	gpsPlotOpen( gwmsg_client_t* client, int ujobid, int openmode );
int	gpsPlotClose( gwmsg_client_t* client, int plotid );
int	gpsPlotCancel( gwmsg_client_t* client, int plotid );
int	gpsPlotSetPageParam( gwmsg_client_t* client, int plotid, const gps_pageparam_t *ppageparam );
int	gpsPlotChangePageParam( gwmsg_client_t* client, int plotid, const gps_pageparam_t *ppageparam );
int	gpsPlotCancelLater( gwmsg_client_t* client, int plotid );
int	gpsFrameCreate( gwmsg_client_t* client, int plotid, const gps_pagemode_t *ppagemode );
int	gpsFrameOpen( gwmsg_client_t* client, int plotid );
int	gpsFrameClose( gwmsg_client_t* client, int frameid );
int	gpsFrameCancel( gwmsg_client_t* client, int frameid );
int	gpsFramePrint( gwmsg_client_t* client, int frameid, const gps_pageinfo_t *ppageinfo, int force );
int	gpsFrameGetBand( gwmsg_client_t* client, int frameid, int bandid, int planeid );
int	gpsFrameFlushBandOld( gwmsg_client_t* client, int frameid, int bandid, int planeid, int drawn );
int	gpsTrayRequest( gwmsg_client_t* client, int plotid, int psize, int nodir, int ptype, int trayid );
int	gpsPaperRequest( gwmsg_client_t* client, int plotid, int psize, int pwidth, int plength, int nodir, int ptype, int trayid );
int	gpsReplotInfo( gwmsg_client_t* client, int plotid, gps_pagemode_t *pagemode, gps_pageinfo_t *pageinfo, int *force );
int	gpsReplotOpen( gwmsg_client_t* client, int plotid );
int	gpsReplotClose( gwmsg_client_t* client, int frameid );
int	gpsJupiterFrameCreate( gwmsg_client_t* client, int plotid, const gps_pagemode_t *ppagemode, const gps_pageinfo_t *ppageinfo, int force );
int	gpsFrameCreateInfo( gwmsg_client_t* client, int plotid, const gps_pagemode_t *ppagemode, const gps_pageinfo_t *ppageinfo, int force );
int	gpsFramePrefeed( gwmsg_client_t* client, int frameid );
int	gpsGetBandWidthBytes( gwmsg_client_t* client, int width, int depth );
int	gpsPageDebug( gwmsg_client_t* client, int funcid );
void	gpsPenvInit( gwmsg_client_t* client );
void	gpsPenvReset( gwmsg_client_t* client );
int	gpsPenvOpen( gwmsg_client_t* client, const char *penv_name, long penv_name_size );
void	gpsPenvClose( gwmsg_client_t* client, int penv );
int	gpsPenvGetValue( gwmsg_client_t* client, int penv, long var, long *val );
int	gpsPenvSetValue( gwmsg_client_t* client, int penv, long var, long val );
int	gpsPenvGetDefValue( gwmsg_client_t* client, int penv, long var, long *val );
int	gpsPenvSetDefValue( gwmsg_client_t* client, int penv, long var, long val );
long	gpsPenvGetVarNum( gwmsg_client_t* client, int penv );
int	gpsPenvGetVarListSub( gwmsg_client_t* client, int penv, long start, long num, long *var, long *var_size );
long	gpsPenvGetVarInfo( gwmsg_client_t* client, int penv, long var, gps_penv_varinfo_t *varinfo );
int	gpsPenvGetValueListSub( gwmsg_client_t* client, int penv, long var, long start, long num, long *value, long *value_size );
int	gpsPenvReqPclFontCount( gwmsg_client_t* client, int force );
int	gpsPenvFinishPclFontCount( gwmsg_client_t* client );
int	gpsHostOpen( gwmsg_client_t* client, int hostid, gps_hostdesc_t *hostdesc );
int	gpsHostClose( gwmsg_client_t* client, gps_hostdesc_t hostdesc );
void	gpsHostNotifyReadOld( gwmsg_client_t* client, gps_hostdesc_t hostdesc, long read_byte );
void	gpsHostNotifyWriteOld( gwmsg_client_t* client, gps_hostdesc_t hostdesc, long write_byte );
int	gpsHostWaitDataReq( gwmsg_client_t* client, gps_hostdesc_t hostdesc );
int	gpsHostWaitBufferReq( gwmsg_client_t* client, gps_hostdesc_t hostdesc );
int	gpsHostNotifyRead( gwmsg_client_t* client, gps_hostdesc_t hostdesc, long read_byte );
int	gpsHostNotifyWrite( gwmsg_client_t* client, gps_hostdesc_t hostdesc, long write_byte );
int	gpsGetSysInfoShm( gwmsg_client_t* client, long *offset, long *size );
int	gpsGetPrtInfo( gwmsg_client_t* client, gps_prtinfo_t *prtinfo, int notify );
int	_gpsGetTrayInfo( gwmsg_client_t* client, int num, gps_trayinfo_t *trayinfo, long *trayinfo_size, int notify );
int	_gpsGetBinInfo( gwmsg_client_t* client, int num, gps_bininfo_t *bininfo, long *bininfo_size, int notify );
int	gpsGetPrtStatus( gwmsg_client_t* client, gps_prtstatus_t *prtstatus, int notify );
int	gpsGetPaperInfo( gwmsg_client_t* client, int paper_id, gps_paperinfo_t *paperinfo, int notify );
int	gpsGetCtlError( gwmsg_client_t* client, long num, gps_ctl_error_t *ctl_error, long *ctl_error_size );
int	_gpsGetModelInfo( gwmsg_client_t* client, int num, const char *str, long str_size, char *val, long *val_size, int valuelen );
int	gpsGetTotalCounterReq( gwmsg_client_t* client );
int	gpsGetBitSw( gwmsg_client_t* client, int no );
long	gpsGetInfoTableChanges( gwmsg_client_t* client, int table_id );
int	gpsGetInfoTableDataOffset( gwmsg_client_t* client, int table_id, long *offset, long *size );
int	gpsGetAppleTalkInfo( gwmsg_client_t* client, gps_appletalk_info_t *atinfo );
int	gpsSetAppleTalkInfo( gwmsg_client_t* client, const gps_appletalk_info_t *atinfo );
int	gpsGetTrayIdByOptionIndex( gwmsg_client_t* client, int tray_index );
int	gpsGetBinIdByOptionIndex( gwmsg_client_t* client, int bin_index );
int	gpsDbgCtl( gwmsg_client_t* client, int argc, const char *argv, long argv_size );
int	gpsExtCtl( gwmsg_client_t* client, int f_id, char *argv, long *argv_size );
int	gpsUstatusSetParam( gwmsg_client_t* client, const gps_ustatusparam_t *ustatusparam );
int	gpsUstatusGetParam( gwmsg_client_t* client, gps_ustatusparam_t *ustatusparam );
void	gpsUstatusDevice( gwmsg_client_t* client, long code );
int	gpsGetStatusMsg( gwmsg_client_t* client, char *msg, long *msg_size, long size );
int	gpsClearErrorMsg( gwmsg_client_t* client );
void	gpsSetCentroSignal( gwmsg_client_t* client, char sig );
int	_gpsRmtprnTxStart_Hidden( gwmsg_client_t* client, int ujobid );
long	_gpsRmtprnShmOffset_get( gwmsg_client_t* client );
long	gpsColor_getShrd( gwmsg_client_t* client );
int	gpsColor_getID( gwmsg_client_t* client, int hdpi, int vdpi, int bit, int draw );
int	gpsColor_gamUpd( gwmsg_client_t* client );
int	gpsColor_getTlimit( gwmsg_client_t* client, int mode );
int	gpsColor_getRID( gwmsg_client_t* client, int modeID, gps_color_rid_t *rID, long *rID_size );
int	gpsColor_getGoff( gwmsg_client_t* client, int modeID, gps_clr_gmfile_t *gmfile );
int	gpsColor_getUGval( gwmsg_client_t* client, int mode, int col );
int	gpsColor_getSGval( gwmsg_client_t* client, int modeID, int col, int pnt );
int	gpsColor_get_drawparam( gwmsg_client_t* client, int modeID, gps_color_drawparam_t *param );
long	gpsColor_getShrd2( gwmsg_client_t* client );
int	gpsColor_CalcGAM( gwmsg_client_t* client, gps_clr_calcgam_t para );
int	gpsColor_dbgsock( gwmsg_client_t* client, int argc, const char *argv, long argv_size );
int	gpsMenuGetTestPrnStr( gwmsg_client_t* client, int testprn_id, gps_clr_sample_str_t *str_info );
int	_gpsGetHddInfo2( gwmsg_client_t* client, int hdd, int *status, gps_hddinfo2_t *hddinfo2 );
void	_gpsPlotSetShift( gwmsg_client_t* client, int plotid, int shiftoff );
int	_gpsGetPrmInfo( gwmsg_client_t* client, int f_id, int *status, int size, char *data, long *data_size );
int	_gpsPlotSetPageParam2( gwmsg_client_t* client, int plotid, const gps_pageparam2_t *ppageparam2, int *result, ulong *flag );
int	_gpsFrameLoadEnv( gwmsg_client_t* client, int frameid );
int	_gpsPlotChkDirection( gwmsg_client_t* client, int plotid, const gps_chkdirprm_t *condition, int *direction, int *slantdirection );
int	_gpsFrameGetMultiBandShm( gwmsg_client_t* client, long *offset, int *num );
int	_gpsFrameGetMultiBand( gwmsg_client_t* client, int frameid, int bandid, int *result );
int	_gpsFrameFlushMultiBand( gwmsg_client_t* client, int frameid, int bandid, int *result );
int	_gpsFrameChapterSet( gwmsg_client_t* client, int frameid, u_char mode, u_char paper_type );
int	_gpsGetFontInfoWffn( gwmsg_client_t* client, int font, gps_fontinfo_wffn_t *fontinfo_wffn );
int	_gpsPlotChangeBinding( gwmsg_client_t* client, int plotid, u_char binding, int *result );
int	_gpsGetFlashMemInfo( gwmsg_client_t* client, int fm_id, int *status, gps_flashmem_info_t *info );
int	_gpsXpdlMenuEntryDone( gwmsg_client_t* client );
int	_gpsReqEventNotify( gwmsg_client_t* client, int req, u_long ev, u_long *res );
int	_gpsFramePrintInfo( gwmsg_client_t* client, int frameid, const gps_pageinfo2_t *ppageinfo2, ulong *flag );
int	_gpsGetTrayInfoShm( gwmsg_client_t* client, int *ret_code, int num, long *offset, int *ret_num, int notify );
int	_gpsGetBinInfoShm( gwmsg_client_t* client, int *ret_code, int num, long *offset, int *ret_num, int notify );
int	_gpsInterpNotifyExt( gwmsg_client_t* client, int ext_id, int *status, gps_interp_notify_ext_t interp_ext );
int	_gpsColor_getProfileShm( gwmsg_client_t* client, long *offset, long *num );
int	_gpsUjobCancel( gwmsg_client_t* client, int ujobid, int *status );
int	_gpsPenvDataAllocShm( gwmsg_client_t* client, int penv, long *offset, long size, int *result );
int	_gpsPenvDataFreeShm( gwmsg_client_t* client, int penv, long offset, int *result );
int	_gpsPenvSetDataShm( gwmsg_client_t* client, int penv, long var, long offset, long val_size, int *result );
int	_gpsPenvGetDataShm( gwmsg_client_t* client, int penv, long var, long *offset, long in_size, long *out_size, int *result );
int	_gpsGetPaperWidLen( gwmsg_client_t* client, u_char psize, u_short *pwidth, u_short *plength );
int	_gpsAuthReq( gwmsg_client_t* client, int ujobid, int *status );
int	_gpsColor_getPrmVal( gwmsg_client_t* client, int param, u_long *val, int *result );
int	_gpsInterpReqEventNotify( gwmsg_client_t* client, int req, int *result );
int	_gpsTrayRequest2( gwmsg_client_t* client, int plotid, int psize, int nodir, int ptype, int tray, const gps_trayrequestEx_t *pTrayReq, int *result );
int	_gpsFrameCreateEx( gwmsg_client_t* client, int plotid, const gps_pagemode2_t *ppagemode2, const gps_pageinfo2_t *ppageinfo2, int *result );
int	_gpsReplotInfoEx( gwmsg_client_t* client, int plotid, gps_pagemode2_t *ppagemode2, gps_pageinfo2_t *ppageinfo2, int *result );
int	_gpsPlotChkDirection2( gwmsg_client_t* client, int plotid, const gps_chkdirprm_t *condition, const gps_chkdirprmEx_t *condEx, int *direction, int *slantdirection );
int	_gpsFormGetImageInfo( gwmsg_client_t* client, int plotid, int formno, int *result );
int	_gpsFormOpen( gwmsg_client_t* client, int plotid, int formno, int *result );
int	_gpsFormClose( gwmsg_client_t* client, int formno, int frameid, int *result );
int	_gpsColor_getID2( gwmsg_client_t* client, int hdpi, int vdpi, int bit, int draw, u_char prt, u_char paper, int *modeID );
int	_gpsColor_getGoff2( gwmsg_client_t* client, int modeID, gps_nclr_gmfile_t *gmfile );
int	_gpsColor_get_drawparam2( gwmsg_client_t* client, int modeID, gps_nclr_drawparam_t *param );
int	_gpsInterpPauseAns( gwmsg_client_t* client, int ujobid, int result, ulong param );
int	_gpsInterpResumeAns( gwmsg_client_t* client, int ujobid, int result, ulong param );
int	_gpsDispSetFreeMsg( gwmsg_client_t* client, const gps_freemsg_t *freemsg );
int	_gpsInterpFinishProcData2( gwmsg_client_t* client, int njobid );
int	_gpsInterpJobResumeAns( gwmsg_client_t* client, int result );
int	_gpsInterpJobEndAns( gwmsg_client_t* client, int result );
int	_gpsInterpSessionCloseAns( gwmsg_client_t* client, int njobid, int result );
int	_gpsGetFormTrayInfo( gwmsg_client_t* client, int formid, long penvid, gps_formtray_info_t *formtrayinfo );
int	_gpsGetFormTrayList( gwmsg_client_t* client, gps_formtray_list_t *formtraylist );
int	_gpsPlotChangeFormTray( gwmsg_client_t* client, int plotid, int formid, int *result );
int	_gpsGetFormTrayInfoStr( gwmsg_client_t* client, int formid, gps_formtray_info_str_t *formtrayinfostr );
int	_gpsGetFormTrayInfoAttr( gwmsg_client_t* client, int formid, gps_formtray_info_attr_t *formtrayinfoattr );
int	_gpsInterpFinishFontreset( gwmsg_client_t* client );
int	_gpsUjobCancel2( gwmsg_client_t* client, int njobid );
u_char	_gpsGetStapleOkSize( gwmsg_client_t* client, u_char p_size, u_short p_width, u_short p_length, u_char position );
u_char	_gpsGetPunchOkSize( gwmsg_client_t* client, u_char p_size, u_short p_width, u_short p_length );
u_char	_gpsGetStapleMax( gwmsg_client_t* client, u_char p_size, u_char p_kind, u_short p_width, u_short p_length, u_char punch, u_char position );
u_long	_gpsGetStaplePos( gwmsg_client_t* client );
u_long	_gpsGetPunchPos( gwmsg_client_t* client );
u_long	_gpsGetPaperExitOkSize( gwmsg_client_t* client, u_char p_size, u_short p_width, u_short p_length, u_char face, u_char trayno );
u_char	_gpsGetPunchOkKind( gwmsg_client_t* client, u_char p_kind );
int	_gpsGetTrayInfo2( gwmsg_client_t* client, int num, gps_trayinfo_t *trayinfo, long *trayinfo_size, int notify );
int	_gpsPlotPrepare( gwmsg_client_t* client, int ujobid, const gps_plotprepareparam_t *param );
u_char	_gpsGetStapleOkKind( gwmsg_client_t* client, u_char p_kind, u_char position );
u_long	_gpsGetPaperExitOkKind( gwmsg_client_t* client, u_char p_kind, u_char face, u_char trayno );
int	_gpsPlotGetShmInfo( gwmsg_client_t* client, long *offset, long *size );
int	_gpsPlotSetPageParamShm( gwmsg_client_t* client, int plotid );
int	_gpsChkDuplexOk( gwmsg_client_t* client, const gps_chkduplexok_t *pchkduplexok );
int	_gpsChkExtPortOk( gwmsg_client_t* client );
int	_gpsGetPrtStatus2Shm( gwmsg_client_t* client, long *offset, int notify );
int	_gpsGetTrayInfoBusyShm( gwmsg_client_t* client, int *ret_code, int num, long *offset, int *ret_num, int notify );
int	_gpsGetPdlPrintCondition( gwmsg_client_t* client, int ujobid, gps_pdl_printcondition_t *cond, gps_pdl_media_printcondition_t *media );
int	_gpsGetPdfParam( gwmsg_client_t* client, int ujobid, gps_pdf_param_t *param );
int	_gpsSetPdlPrintInfo( gwmsg_client_t* client, int plotid, const gps_pdl_printinfo_t *prtinfo );
int	_gpsGetUcpParamShm( gwmsg_client_t* client, int ujobid, long *offset, int *result );
int	_gpsGetUcpData( gwmsg_client_t* client, gps_ucp_info_t ucpinfo, gps_ucp_data_t *ucpdata, int *result );
int	_gpsGetCipherSeed( gwmsg_client_t* client, int size, u_char *seed, long *seed_size );
int	_gpsGetPdlPrintConditionShm( gwmsg_client_t* client, int ujobid, u_long *offset );
int	_gpsGetHeadRiseMode( gwmsg_client_t* client, gps_headrise_mode_t *mode, int *result );
int	_gpsGetPrtTotalCounterReq( gwmsg_client_t* client );

/******* server handler section *******/
void register_func_handler_for_gw_gps( gwmsg_server_t* st );
int gpsUjobStart_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobEnd_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobCurrent_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsJobGetOptionStr_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobSetName_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsJobNotifyStart_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsJobNotifyExit_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsJobReqProcData_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobResetParam_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsJobNotifySendNext_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobGetParamShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobSetParamVarShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobGetParamVarShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobStartOld_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobEndOld_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUjobEnd2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsRgateSetParamVar_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsRgateGetParamVar_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyStart_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyExitOld_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpFinishProcData_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpReqChange_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyState_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyStateStr_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpFinishTestprint_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyOnline_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyOffline_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetPdlTable_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyWarning_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpClearWarning_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyAlert_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpClearAlert_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpReqEventFeed_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyStartOld_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyError_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyErrorForce_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsInterpNotifyExit_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsProgEntry_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsProgDelete_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsProgFinish_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsProgGetNextFileno_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsProgInit_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsWkSizeTotal_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsWkSizeFree_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsWkFree_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsWkMallocReq_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsNvWrite_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsNvRead_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsNvDelete_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsNvFileCheck_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsShmGetId_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetFontInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetHddInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFsInit_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsNvInit_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsNvShmLock_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsNvShmUnlock_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPlotOpen_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPlotClose_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPlotCancel_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPlotSetPageParam_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPlotChangePageParam_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPlotCancelLater_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFrameCreate_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFrameOpen_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFrameClose_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFrameCancel_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFramePrint_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFrameGetBand_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFrameFlushBandOld_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsTrayRequest_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPaperRequest_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsReplotInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsReplotOpen_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsReplotClose_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsJupiterFrameCreate_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFrameCreateInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsFramePrefeed_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetBandWidthBytes_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPageDebug_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvInit_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvReset_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvOpen_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvClose_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvGetValue_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvSetValue_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvGetDefValue_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvSetDefValue_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvGetVarNum_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvGetVarListSub_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvGetVarInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvGetValueListSub_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvReqPclFontCount_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsPenvFinishPclFontCount_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostOpen_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostClose_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostNotifyReadOld_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostNotifyWriteOld_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostWaitDataReq_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostWaitBufferReq_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostNotifyRead_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsHostNotifyWrite_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetSysInfoShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetPrtInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetTrayInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetBinInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetPrtStatus_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetPaperInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetCtlError_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetModelInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetTotalCounterReq_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetBitSw_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetInfoTableChanges_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetInfoTableDataOffset_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetAppleTalkInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsSetAppleTalkInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetTrayIdByOptionIndex_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetBinIdByOptionIndex_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsDbgCtl_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsExtCtl_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUstatusSetParam_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUstatusGetParam_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsUstatusDevice_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsGetStatusMsg_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsClearErrorMsg_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsSetCentroSignal_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsRmtprnTxStart_Hidden_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsRmtprnShmOffset_get_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getShrd_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getID_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_gamUpd_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getTlimit_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getRID_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getGoff_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getUGval_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getSGval_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_get_drawparam_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_getShrd2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_CalcGAM_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsColor_dbgsock_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int gpsMenuGetTestPrnStr_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetHddInfo2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotSetShift_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPrmInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotSetPageParam2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFrameLoadEnv_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotChkDirection_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFrameGetMultiBandShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFrameGetMultiBand_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFrameFlushMultiBand_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFrameChapterSet_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetFontInfoWffn_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotChangeBinding_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetFlashMemInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsXpdlMenuEntryDone_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsReqEventNotify_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFramePrintInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetTrayInfoShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetBinInfoShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpNotifyExt_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsColor_getProfileShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsUjobCancel_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPenvDataAllocShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPenvDataFreeShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPenvSetDataShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPenvGetDataShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPaperWidLen_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsAuthReq_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsColor_getPrmVal_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpReqEventNotify_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsTrayRequest2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFrameCreateEx_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsReplotInfoEx_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotChkDirection2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFormGetImageInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFormOpen_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsFormClose_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsColor_getID2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsColor_getGoff2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsColor_get_drawparam2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpPauseAns_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpResumeAns_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsDispSetFreeMsg_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpFinishProcData2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpJobResumeAns_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpJobEndAns_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpSessionCloseAns_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetFormTrayInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetFormTrayList_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotChangeFormTray_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetFormTrayInfoStr_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetFormTrayInfoAttr_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsInterpFinishFontreset_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsUjobCancel2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetStapleOkSize_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPunchOkSize_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetStapleMax_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetStaplePos_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPunchPos_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPaperExitOkSize_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPunchOkKind_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetTrayInfo2_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotPrepare_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetStapleOkKind_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPaperExitOkKind_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotGetShmInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsPlotSetPageParamShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsChkDuplexOk_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsChkExtPortOk_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPrtStatus2Shm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetTrayInfoBusyShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPdlPrintCondition_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPdfParam_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsSetPdlPrintInfo_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetUcpParamShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetUcpData_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetCipherSeed_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPdlPrintConditionShm_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetHeadRiseMode_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );
int _gpsGetPrtTotalCounterReq_handler( void *svr, gwmsg_t* m, gwmsg_client_id_t cid );

#endif /* __GWIPC_GW_GPS_H__ */
/*
 * Local Variables:
 * c-basic-offset: 4
 * End:
 */

