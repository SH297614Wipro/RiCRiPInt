/*
 *	Copyright (c) 2004 RICOH TOTTORI SOFTWARE TECHNOLOGY CO., LTD.
 *	All rights reserved.  Proprietary and confidential.
 */
/*
 * FILE
 *     pjl/pjlricoh.c
 *
 * DESCRIPTION
 *	Port-specific RPJL stuff.  Actually, most ports use this file.
 *
 *	===== HISTORY of changes in //depot/ips/oem/2k8_0/newR2MS/pjl/pjlsun.c
 *	
 *	20/Sep/12 #3 bm11 Add support for NUP, NUPPAGEORDER, MIRROR, NEGATIVEOUTPUT,
 *	FITTOPAGESIZE, OUTPUT, BORDERLINE, SCALE and CORNERLOCK PJL commands.
 *	PRINTPAGES PJL command no longer requires setting the emulation to PDF
 *	in order to use it.
 *	7/Sep/12 #2 bm11 Add PDF specific command PRINTPAGES.
 *	
 */
#include "device.h"		/* for LibDI */
//#include "paper.h"
#include "pms_export.h"


extern OIL_TyJob g_tJob;

struct PanelSetting{
 OPanel panelitem;
 long   defaultvalue;
 long   currentvalue;
 };
  
 struct PanelSetting OperPanel[5]={
	{ OMFONTSRC      ,0 ,0 },
	{ OMFONTNUMBER   ,0 ,0 },
    { OMFONTPITCH    ,0 ,0 },
    { OMFONTSIZE     ,0 ,0 },
    { OMSYMSET       ,0 ,0 } 
 };
 
/* It is differnt from other Enum Table and not for Standard Enum Conversion.
   This table is used in PenvInttoOMSymset() */
 struct PenvOmPair
{
	long val;
	char* om;
	long  tempvalue; /* adding this temporarily, need to change as per requirement*/
};


struct PenvOmPair PenvSymsetMap[56] = {
	{DI_ENV_VAL_INT_SYMSET_DESKTOP,	    "7J" ,0},
	{DI_ENV_VAL_INT_SYMSET_ISO4,		"1E" ,1},	
	{DI_ENV_VAL_INT_SYMSET_ISO6,		"0U", 2},	
	{DI_ENV_VAL_INT_SYMSET_ISO11,		"0S", 3},	
	{DI_ENV_VAL_INT_SYMSET_ISO15,		"0I", 4},	
	{DI_ENV_VAL_INT_SYMSET_ISO17,		"2S", 5},	
	{DI_ENV_VAL_INT_SYMSET_ISO21,		"1G", 6},	
	{DI_ENV_VAL_INT_SYMSET_ISO60,		"0D", 7},	
	{DI_ENV_VAL_INT_SYMSET_ISO69,		"1F", 8},	
	{DI_ENV_VAL_INT_SYMSET_ISOL1,		"0N", 9},	
	{DI_ENV_VAL_INT_SYMSET_ISOL2,		"2N", 10},	
	{DI_ENV_VAL_INT_SYMSET_ISOL5,		"5N", 11},	
	{DI_ENV_VAL_INT_SYMSET_LEGAL,		"1U", 12},	
	{DI_ENV_VAL_INT_SYMSET_MATH8,		"8M", 13},	
	{DI_ENV_VAL_INT_SYMSET_MSPUBL,	    "6J", 14},	
	{DI_ENV_VAL_INT_SYMSET_PC8,		    "10U", 15},	
	{DI_ENV_VAL_INT_SYMSET_PC850,		"12U", 16},	
	{DI_ENV_VAL_INT_SYMSET_PC852,		"17U", 17},	
	{DI_ENV_VAL_INT_SYMSET_PC8DN,		"11U", 18},	
	{DI_ENV_VAL_INT_SYMSET_PC8TK,		"9T", 19},	
	{DI_ENV_VAL_INT_SYMSET_PIFONT,	    "15U", 20},	
	{DI_ENV_VAL_INT_SYMSET_PSMATH,	    "5M", 21},	
	{DI_ENV_VAL_INT_SYMSET_PSTEXT,	    "10J", 22},	
	{DI_ENV_VAL_INT_SYMSET_ROMAN8,	    "8U", 23},	
#ifdef VN_SYMSET_SUPPORT
	{DI_ENV_VAL_INT_SYMSET_VNINTL,	"13J", 24},	
	{DI_ENV_VAL_INT_SYMSET_VNMATH,	"6M", 25},	
	{DI_ENV_VAL_INT_SYMSET_VNUS,	"14J", 26},	
#endif
	{DI_ENV_VAL_INT_SYMSET_WIN30,		"9U", 27},	
	{DI_ENV_VAL_INT_SYMSET_WINL1,		"19U", 28},	
	{DI_ENV_VAL_INT_SYMSET_WINL2,		"9E", 29},	
	{DI_ENV_VAL_INT_SYMSET_WINL5,		"5T", 30},	
	{DI_ENV_VAL_INT_SYMSET_ROMAN9,		"4U", 31},	
	{DI_ENV_VAL_INT_SYMSET_ISOL6,		"6N", 32},	
	{DI_ENV_VAL_INT_SYMSET_ISOL9,		"9N", 33},	
	{DI_ENV_VAL_INT_SYMSET_PC775,		"26U", 34},	
	{DI_ENV_VAL_INT_SYMSET_PC858,		"13U", 35},	
	{DI_ENV_VAL_INT_SYMSET_UCS2,		"18N", 36},	
	{DI_ENV_VAL_INT_SYMSET_PC864,		"10V", 37},	
	{DI_ENV_VAL_INT_SYMSET_ARABIC8,		"8V", 38},	
	{DI_ENV_VAL_INT_SYMSET_WINARB,		"9V", 39},	
	{DI_ENV_VAL_INT_SYMSET_PC866,		"3R", 40},	
	{DI_ENV_VAL_INT_SYMSET_PC866U,		"14R", 41},	
	{DI_ENV_VAL_INT_SYMSET_ISOCYR,		"10N", 42},	
	{DI_ENV_VAL_INT_SYMSET_WINCYR,		"9R", 43},	
	{DI_ENV_VAL_INT_SYMSET_PC851,		"10G", 44},	
	{DI_ENV_VAL_INT_SYMSET_GREEK8,		"8G", 45},	
	{DI_ENV_VAL_INT_SYMSET_ISOGRK,		"12N", 46},	
	{DI_ENV_VAL_INT_SYMSET_PC8GRK,		"12G", 47},	
	{DI_ENV_VAL_INT_SYMSET_WINGRK,		"9G", 48},	
	{DI_ENV_VAL_INT_SYMSET_PC862,		"15H", 49},	
	{DI_ENV_VAL_INT_SYMSET_HEBREW7,		"0H", 50},	
	{DI_ENV_VAL_INT_SYMSET_HEBREW8,		"8H", 51},	
	{DI_ENV_VAL_INT_SYMSET_ISOHEB,		"7H", 52},	
	{DI_ENV_VAL_INT_SYMSET_PC1004,		"9J", 53},	
	{DI_ENV_VAL_INT_SYMSET_WINBALTIC,	"19L", 54},	
	{DI_ENV_VAL_INT_SYMSET_MCTEXT,		"12J", 55},	
};


void setDefaultOpernPanel(OPanel item,long val)
{
  OperPanel[item].defaultvalue = val;
}

void setCurrentOpernPanel(OPanel item,long val)
{
  OperPanel[item].currentvalue = val;
}

/*******************************************************************
 * Synopsis:     void PenvtoOMInt()
 *
 * Description: Conver Penv Value and Set to Option Manager
 * Arguments:	tbl_ptr : pointer to OMPenvMap's member
 *				val 	: set value of PenvID
 *				OMLevel	: Set Level to OM 
 *				stat	: value status  
 *							0 -> val=user disignation
 *							1 -> val=default (There is no user's disignation)
 *
 * Return:
 * Uses:
 * Sets:
 * Changes:
 * Heap Use:    none.
********************************************************************/
void PenvtoOMInt(OPanel item, int OMlevel, long val)
{
	/* Set up 'val' directly in option manager */
	switch(OMlevel)
	{
	case DEFAULT_LEVEL:
						setDefaultOpernPanel(item,val);
						break;
	case CURRENT_LEVEL:
						setCurrentOpernPanel(item,val);
						break;
	default:
						break;
	}
	g_tJob.uFontNumber=val;
}

/*******************************************************************
 * Synopsis:     void PenvtoOMFontSrc()
 *
 * Description: Conver Penv Value and Set to Option Manager
 * Arguments:	tbl_ptr : pointer to OMPenvMap's member
 * 				val 	: set value of PenvID
 *				OMLevel	: Set Level to OM 
 *				stat	: value status  
 *							0 -> val=user disignation
 *							1 -> val=default (There is no user's disignation)
 *
 * Return:
 * Uses:
 * Sets:
 * Changes:
 * Heap Use:    none.
********************************************************************/
void PenvtoOMFontSrc(OPanel item, int OMlevel, long val)
{

	int setval;			/* value to OM */	
	

	switch(val)
	{
	case DI_ENV_VAL_INT_FONTSOURCE_I:	    
		setval = OrgRomSys; 
		strcpy(g_tJob.szFontSource,"I");
		break;
	case DI_ENV_VAL_INT_FONTSOURCE_C:
		setval = OrgRomCart;
		strcpy(g_tJob.szFontSource,"C");
		break;
	case DI_ENV_VAL_INT_FONTSOURCE_S:
		setval = OrgRamDLL;
		strcpy(g_tJob.szFontSource,"S");
		break;
#ifdef HDD_DOWNLOAD_FONT
	case DI_ENV_VAL_INT_FONTSOURCE_D:
		setval = OrgRomDLL;
		strcpy(g_tJob.szFontSource,"D");
		break;
#endif
#if defined(SD_DOWNLOAD_ENABLE) && defined(DI_ENV_VAL_INT_FONTSOURCE_SD)
	case DI_ENV_VAL_INT_FONTSOURCE_SD:
		setval = OrgSDDLL;
		strcpy(g_tJob.szFontSource,"SD");
		break;
#endif
	default:
	case DI_ENV_VAL_INT_FONTSOURCE_M1:
	case DI_ENV_VAL_INT_FONTSOURCE_M2:
	case DI_ENV_VAL_INT_FONTSOURCE_M3:
	case DI_ENV_VAL_INT_FONTSOURCE_M4:
		setval = OrgRomSIMM;
		strcpy(g_tJob.szFontSource,"M");
		break;
	}

	switch(OMlevel)
	{
		case DEFAULT_LEVEL:
							setDefaultOpernPanel(item,setval);
							break;
		case CURRENT_LEVEL:
							setCurrentOpernPanel(item,setval);
							break;
		default:
							break;
	}
}


/*******************************************************************
 * Synopsis:     void PenvtoOMFloat_100()
 *
 * Description: Conver Penv Value and Set to Option Manager
 * Arguments:	tbl_ptr : pointer to OMPenvMap's member
 *				val 	: set value of PenvID
 *				OMLevel	: Set Level to OM 
 *				stat	: value status  
 *							0 -> val=user disignation
 *							1 -> val=default (There is no user's disignation)
 *
 * Return:
 * Uses:
 * Sets:
 * Changes:
 * Heap Use:    none.
********************************************************************/
void PenvtoOMFloat_100(OPanel item, int OMlevel, long val, int denom)
{

	int setval;			/* value to OM */	
	setval = val * 100 / denom;
	
	switch(OMlevel)
	{
	case DEFAULT_LEVEL:
						setDefaultOpernPanel(item,setval);
						break;
	case CURRENT_LEVEL:
						setCurrentOpernPanel(item,setval);
						break;
	default:
						break;
	}
	if(item==OMFONTPITCH)
		g_tJob.dPitch=setval;
	else if(item==OMFONTSIZE)
		g_tJob.dPointSize=setval;
}

/*******************************************************************
 * Synopsis:     void PenvtoOMSymset()
 *
 * Description: Conver Penv Value and Set to Option Manager
 * Arguments:	tbl_ptr : pointer to OMPenvMap's member
 *				val 	: set value of PenvID
 *				OMLevel	: Set Level to OM 
 *				stat	: value status  
 *							0 -> val=user disignation
 *							1 -> val=default (There is no user's disignation)
 *
 * Return:
 * Uses:
 * Sets:
 * Changes:
 * Heap Use:    none.
********************************************************************/
void PenvtoOMSymset(OPanel item, int OMlevel, long val)
{

	
	int tbl_size	= 56;//dimof(PenvSymsetMap);		/* size of Enum Pair Table */
	int cnt;									/* counter */

	for(cnt = 0; cnt < tbl_size; cnt++){
		if(PenvSymsetMap[cnt].val == val){
			
			switch(OMlevel)
			{
			case DEFAULT_LEVEL:
								setDefaultOpernPanel(item,PenvSymsetMap[cnt].tempvalue);
								break;
			case CURRENT_LEVEL:
								setCurrentOpernPanel(item,PenvSymsetMap[cnt].tempvalue);
								break;
			default:
								break;
			}		
			break;
		}
	}	
	 g_tJob.uSymbolSet = PenvSymsetMap[cnt].tempvalue; 
}


/*******************************************************************
 * Synopsis:     void PenvtoOMFontnum()
 *
 * Description: Conver Penv Value and Set to Option Manager
 * Arguments:	tbl_ptr : pointer to OMPenvMap's member
 *				val 	: set value of PenvID
 *				OMLevel	: Set Level to OM 
 *				stat	: value status  
 *							0 -> val=user disignation
 *							1 -> val=default (There is no user's disignation)
 *
 * Return:
 * Uses:
 * Sets:
 * Changes:
 * Heap Use:    none.
********************************************************************/
void PenvtoOMFontnum(OPanel item, int OMlevel, long val)
{
	int setval;			/* value to OM */	
	int fontsrc;		/* font source of OMlevel */

	if (OMlevel == DEFAULT_LEVEL)
		fontsrc = OperPanel[OMFONTSRC].defaultvalue;
	else
		fontsrc = OperPanel[OMFONTSRC].currentvalue;

/*	setval = HPtoPageID(val, fontsrc);
	if (setval == -1) {
		if (OMlevel == DEFAULT_LEVEL)
			setval = OperPanel[OMFONTNUMBER].defaultvalue;
		else
			setval = OperPanel[OMFONTNUMBER].currentvalue;
	}
*/
    setval =val; /* need to change if required*/
	switch(OMlevel)
	{
	case DEFAULT_LEVEL:
						setDefaultOpernPanel(item,setval);
						break;
	case CURRENT_LEVEL:
						setCurrentOpernPanel(item,setval);
						break;
	default:
						break;
	}
	g_tJob.uFontNumber=setval;
}





/* Local Variables:
 * mode: C
 * tab-width: 4
 * c-indent-level: 4
 * End:
 */
/* Used by vim and some versions of vi: set tabstop=4 shiftwidth=4: */
