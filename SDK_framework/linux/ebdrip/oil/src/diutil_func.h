/* wipro
 *by Vimala
 */
#ifndef _DIUTIL_FUNC_H_
#define _DIUTIL_FUNC_H_

#include "gw_gps.h"

typedef int CmdType;
typedef int OMenum;
typedef struct PenvTrayParamtr
{
	int PaperSource, install;
}PenvTrayParam;

#define DIMOF_TRAYPARAMMAP 10
#define NUMOF_TRAYBINTBL  2
#define NUMOF_TRAYBINITEM 32

#define OMTRAYBYPASSPARAM 0
#define OMTRAY1PARAM 1
#define OMTRAY2PARAM 2	
#define OMTRAY3PARAM 3	
#define OMTRAY4PARAM 4	
#define OMTRAY5PARAM 5	
#define OMTRAY6PARAM 6	
#define OMTRAY7PARAM 7	
#define OMTRAYLCTPARAM 8
#define OMTRAYALLPARAM 9

#define PAPERSRC_BYPASS 0
#define PAPERSRC_TRAY1 1
#define PAPERSRC_TRAY2 2
#define PAPERSRC_TRAY3 3
#define PAPERSRC_TRAY4 4	
#define PAPERSRC_TRAY5 5
#define PAPERSRC_TRAY6 6
#define PAPERSRC_TRAY7 7
#define PAPERSRC_LCT 8
#define PAPERSRC_ALL 9	

/*PenvTrayParam PenvTrayParamMap[] = {
	{OMTRAYBYPASSPARAM,	0,	{0xFF,0xFF,0xFF},	PAPERSRC_BYPASS	},
	{OMTRAY1PARAM,		0,	{0xFF,0xFF,0xFF},	PAPERSRC_TRAY1	},
	{OMTRAY2PARAM,		0,	{0xFF,0xFF,0xFF},	PAPERSRC_TRAY2	},
	{OMTRAY3PARAM,		0,	{0xFF,0xFF,0xFF},	PAPERSRC_TRAY3	},
	{OMTRAY4PARAM,		0,	{0xFF,0xFF,0xFF},	PAPERSRC_TRAY4	},
	{OMTRAY5PARAM,		0,	{0xFF,0xFF,0xFF},	PAPERSRC_TRAY5	},
	{OMTRAY6PARAM,		0,	{0xFF,0xFF,0xFF},	PAPERSRC_TRAY6	},
	{OMTRAY7PARAM,		0,	{0xFF,0xFF,0xFF},	PAPERSRC_TRAY7	},
	{OMTRAYLCTPARAM,	0,	{0xFF,0xFF,0xFF},	PAPERSRC_LCT	},
	{OMTRAYALLPARAM,	1,	{0xFF,0xFF,0xFF},	PAPERSRC_ALL	}
};*/

void mnInitTrayBinCmd(CmdType type, OMenum * traybintbl, int ntraybin);
void PrintSysReinitTrayInfo();
void PrintSysReinitBinInfo();


#endif /* _DIUTIL_FUNC_H_ */
