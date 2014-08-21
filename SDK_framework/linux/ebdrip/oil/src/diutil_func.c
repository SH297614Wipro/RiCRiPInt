/* Wipro
by Vimala
 */


#include "diutil_func.h"
#include <stdio.h>
#include <stdlib.h>

extern gwmsg_client_t *gps_client;
extern gps_sysinfo_t *sysinfo;


/*  mnInitTrayBinCmd(CmdType type, OMenum * traybintbl, int ntraybin)
 *
 *  Purpose: initialize static tray/bin table
 */
void mnInitTrayBinCmd(CmdType type, OMenum * traybintbl, int ntraybin)
{
	int CMDTYPE_PAPERSRC = 0;
	int CMDTYPE_XLPAPERSRC = 1;
	int index;
	static OMenum         current_traybin_tbl[NUMOF_TRAYBINTBL][NUMOF_TRAYBINITEM];
	static int         current_ntraybin[NUMOF_TRAYBINTBL];
	/*ASSERT(traybintbl);*/
	/* Because there must be no PAPERSRC_ALL in 'traybintbl' */
	if (type == CMDTYPE_PAPERSRC || type == CMDTYPE_XLPAPERSRC) {
		current_traybin_tbl[type / 2][0] = PAPERSRC_ALL;
	}

	/*current_ntraybin[type / 2] = MIN(ntraybin + 1, NUMOF_TRAYBINITEM);*/
	/*current_ntraybin[type / 2] = min(ntraybin + 1, NUMOF_TRAYBINITEM);*/
	for (index = 1; index < current_ntraybin[type / 2]; ++index) {
		current_traybin_tbl[type / 2][index] = traybintbl[index - 1];
	}
}

/*  PrintSysReinitTrayInfo(void)
 *
 *  Purpose: reset intray information if it has changed
 */
void PrintSysReinitTrayInfo()
{
	int CMDTYPE_PAPERSRC = 0;
	int CMDTYPE_XLPAPERSRC = 1;
	int SIZEOF_TRAYBINTBL = 10;
	gps_trayinfo_t  trayinfo, *trayinfoPtr;
	OMenum         traytbl[SIZEOF_TRAYBINTBL];
	int            i;
	int				num;
	long			*tray_cnt;
	int				notify = 0;
	
	num = sysinfo->num_tray;
/*#ifdef DI_ENV_VAR_ID_PCLTRAYALLPARAM*/
	int            j;
/*#endif*/

	if (gpsGetTrayInfo(&gps_client, num, &trayinfo, &tray_cnt, notify)!= 0)
	{
		/*LOGMPRINTF1(0x212, "[%s]0212 di_get_trayinfo error\n", PDLNAME);*/
		printf("gpsGetTrayInfo returned error...");
		return;
	}
	/*LOGMPRINTF2(0x212, "[%s]0212 di_get_trayinfo %d\n", PDLNAME, trayinfo.tray_num);*/
	for (i = 0; i < num; ++i) {
		/*traytbl[i] = mnHdwPaperSourcetoOM(trayinfo.trayinfo[i].id);*/
		traytbl[i] = trayinfoPtr->id;
/*#ifdef DI_ENV_VAR_ID_PCLTRAYALLPARAM*/
		/*for (j = 0; j < DIMOF_TRAYPARAMMAP - 1; j++) {
			if (traytbl[i] == PenvTrayParamMap[j].PaperSource) {
				PenvTrayParamMap[j].install = 1;
				break;
			}
		}*/
		trayinfoPtr++;
/*#endif*/
	}
	mnInitTrayBinCmd(CMDTYPE_PAPERSRC, traytbl, num);
}

/*  PrintSysReinitBinInfo(void)
 *
 *  Purpose: reset outbin information if it has changed
 */
void PrintSysReinitBinInfo()
{
	int SIZEOF_TRAYBINTBL = 10;
	int CMDTYPE_OUTBIN = 2;
	gps_bininfo_t  bininfo, *bininfoPtr;
	OMenum         bintbl[SIZEOF_TRAYBINTBL];
	int            i;
	int				num;
	long			*tray_cnt;
	int				notify = 0;
	
	num = sysinfo->num_bin;
	if (gpsGetBinInfo(&gps_client, num, &bininfo, &tray_cnt, notify)!= 0)
	{
		/*LOGMPRINTF1(0x113, "[%s]0113 di_get_bininfo error\n", PDLNAME);*/
		printf("gpsGetBinInfo returned error...");
		return;
	}
	/*LOGMPRINTF2(0x113, "[%s]0113 di_get_bininfo %d\n", PDLNAME, bininfo.bin_num);*/
	for (i = 0; i < num; ++i) 
	{
		/*bintbl[i] = mnHdwOutBinOM(bininfo.bininfo[i].id);*/
		bintbl[i] = bininfoPtr->id;
		bininfoPtr++;
	}
	mnInitTrayBinCmd(CMDTYPE_OUTBIN, bintbl,num);
}

