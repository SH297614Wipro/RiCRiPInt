#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "gps/gps_client.h"
#include "gps/gwipc.h"
#include "gw_gps.h"
#include "gps_func.h"
#include "modelinfo.h"
#include "gps_color_mtype.h"
#include "info.h"
#include "pageprint.h"
#include "memory.h"
#include "gps/pageio.h"
#include "pms_export.h"
#include "gps/device.h"

extern gwmsg_client_t *gps_client;
extern char *gps_shdm_addr;
gps_color_rid_t rID[4];

extern gps_bininfo_t *gpsBinInfo;
extern gps_trayinfo_t *gpsTrayInfo;
extern PMS_TyTrayInfo * g_pstTrayInfo;
extern PMS_TyOutputInfo * g_pstOutputInfo;
extern int g_nInputTrays;
extern int g_nOutputTrays;
extern PMS_HddInfo g_tHddInfo;
unsigned char outbuf[MAX_VALUE_LEN];
long loffset;
gps_nclr_shdm_t *clr_shm;

extern gps_sysinfo_t  sysinfo;
extern gps_hddinfo2_t hddinfo_download;
extern gps_paperinfo_t gpsPaperInfo;
static gps_prtstatus2_t prtStatus;
static gps_plotprepareparam_t plotPrepare;
static gps_pageparam_shm_t param;
static gps_pagemode2_t pagemode2;
gps_fontinfo_t fontinfo;

static gps_pageinfo2_t pageinfo2;
static gps_pagemode_t pagemode;
static gps_pageinfo_t pageinfo;
static gwmsg_GpsPage_FrameCreate_Res_t	pFCR;
static gwmsg_GpsPage_FrameGetBand_Res_t pFGBR;
static gwmsg_GpsPage_FrameFlushBand_Res_t pFFBR;

char  GPS_PmInit(gwmsg_client_t *client, void(*pfunc1)(), void(*pfunc2)());
int GPS_PenvOpen(gwmsg_client_t *client, char *penv_name, long size);
int	GPS_PenvGetValue( gwmsg_client_t* client, int penv, long gps_var, long *penv_val );
void GPS_PenvClose(gwmsg_client_t *client, int penv);
int GPS_Color_getProfile(gwmsg_client_t 	*client, void **addr, long	*num);
int  GPS_InterpNotifyStart(gwmsg_client_t *, int);
void GPS_InterpNotifyOnline(gwmsg_client_t *);
int  GPS_PenvGetValueList(gwmsg_client_t *, int, long, long, long, long *, long *);
int  GPS_PenvGetDefValue(gwmsg_client_t *, int, long, long *);
void GPS_PmDispSetEmulation(char, char, char, char *);
caddr_t GPS_WkMalloc(gwmsg_client_t *client, long mallocsize);
int GPS_WkSizeFree(gwmsg_client_t *);

int GPS_GetPdlPrintConditionShm(gwmsg_client_t *, int, int *, unsigned long *);
int GPS_GetPaperInfo(gwmsg_client_t *, int, gps_paperinfo_t *, int);
void GPS_InterpNotifyState(gwmsg_client_t *, int);
gps_hostbuf_p GPS_SinOpen(gwmsg_client_t *, int);
gps_hostbuf_p GPS_SoutOpen(gwmsg_client_t *, int);
int GPS_GetPdlTable(gwmsg_client_t *, long *, int *);
int GPS_GetPrtStatus2(gwmsg_client_t *, gps_prtstatus2_t *, int, int *);
int GPS_PlotPrepare(gwmsg_client_t *, int, gps_plotprepareparam_t *);
int GPS_PlotOpen(gwmsg_client_t *client, int plotOpen_ujobid, int plotOpen_openmode);
int GPS_PlotSetPageParamShm(gwmsg_client_t *client, int	PlotSet_plotid, gps_pageparam_shm_t	*param, int	*PlotSet_result);
int GPS_FrameCreateEx(gwmsg_client_t *client, int framecreate_plotid, const gps_pagemode2_t *pagemode2, const gps_pageinfo2_t *pageinfo2, int	*framecreate_result);
int GPS_FrameCreateInfoRes(gwmsg_client_t *client, int FCinfo_plotid, gps_pagemode_p pagemode, gps_pageinfo_t *pageinfo, int FCinfo_force, gwmsg_GpsPage_FrameCreate_Res_t	*pFCR);
int GPS_FrameGetBandRes(gwmsg_client_t *client, int	FGband_frameid, int FGband_bandid, int FGband_planeid, gwmsg_GpsPage_FrameGetBand_Res_t *pFGBR);
int GPS_FrameFlushBandRes(gwmsg_client_t *client,int FFB_frameid,int FFB_bandid,int	FFB_planeid,int	FFB_drawn,int FFB_flush,gwmsg_GpsPage_FrameFlushBand_Res_t	*pFFBR);
int GPS_FramePrintInfo(gwmsg_client_t *client, int FP_frameid, const gps_pageinfo2_t *pageinfo2, unsigned long *FP_flag);
int GPS_FramePrint(gwmsg_client_t *client, int FP_frameid, const gps_pageinfo_t *pageinfo, int FP_force);
int GPS_FrameClose(gwmsg_client_t *client, int FP_frameid);
int GPS_PenvSetDefValue(gwmsg_client_t *client, int penv, long penv_var, long penv_val);
int GPS_PlotClose(gwmsg_client_t *client, int plotid);
int GPS_SinClose(gps_hostbuf_p host_inBuff);
int GPS_SoutClose(gps_hostbuf_p host_outBuff);
void GPS_InterpFinishProcData(gwmsg_client_t *client, int ujobid, int fin, int uel_found);
void GPS_Close(gwmsg_client_t *client, void *shdm_addr);
void init_page_structs();


void init_page_structs()
 {
 /* assign values to structures*/
pagemode2.flag = 0x7;
pagemode2.frame_width = 6814;
pagemode2.frame_length = 4760;
pagemode2.band_length = 2048;

pageinfo2.flag = 0x7e;
pageinfo2.bypass_dir = 0x0;
pageinfo2.page_shift = 0x0;
pageinfo2.print_mode = 0x2;
pageinfo2.paper_width = 2970;
pageinfo2.paper_length = 2100;
pageinfo2.frame_width = 6814;
pageinfo2.frame_length = 4760;
pageinfo2.band_length = 2048;


pagemode.frame_width = 6814;
pagemode.frame_length = 4760;
pagemode.band_length = 2048;
pagemode.color_count = 4;
pagemode.depth = 1;
pagemode.skip_level = 0;
pagemode.rotate = 2;
pagemode.face = 1;
pagemode.upsidedown = 0;
pagemode.ra_id_k = 1;
pagemode.ra_id_c = 1;
pagemode.ra_id_m = 1;
pagemode.ra_id_y = 1;
pagemode.ra_offx_k = 0;
pagemode.ra_offy_k = 0;
pagemode.ra_offx_c = 0;
pagemode.ra_offy_c = 0;
pagemode.ra_offx_m = 0;
pagemode.ra_offy_m = 0;
pagemode.ra_offx_y = 0;
pagemode.ra_offy_y = 0;

pageinfo.paper_code = 5;
pageinfo.paper_width = 2970;
pageinfo.paper_length = 2100;
pageinfo.band_length = 2048;
pageinfo.line_size = 0;
pageinfo.xoffset = 100;
pageinfo.yoffset = 100;
pageinfo.resolution_x = 600;
pageinfo.resolution_y = 600;
pageinfo.compress = 4;
pageinfo.color = 1;
pageinfo.fci = 0;
pageinfo.input_tray = 15;
pageinfo.paper_type = 0;
pageinfo.limitless_feed = 1;
pageinfo.paper_count = 1;
pageinfo.count_off = 0;
 }
 
 
 
/***********************************************************************************************************
*Function Name: GPS_GetPrmInfo()
*Attributes:
*client  IN   Client identifier
*f_id IN Type of information that has been obtained
**status OUT Status of obtained information
*size IN Size of buf // use only when ID is specified to use buf 
*buf OUT Obtained information // use only when the ID is designated to use buf 
*Description: This function obtains information of print material.
************************************************************************************************************/
int GPS_GetPrmInfo(int f_id, int *status, int size,   long *maxsize)
{
    return gpsGetPrmInfo( gps_client, f_id, status, size, maxsize );
}

/***********************************************************************************************************
*Function Name: GPS_PmInit()
*Attributes:
*client  IN   Client identifier
*Description: 'gps' entry to initialize panel manager.
************************************************************************************************************/
char GPS_PmInit(gwmsg_client_t *client, void(*pfunc1)(), void(*pfunc2)())
{
     printf("------------------------------------- \n");
	printf("Call gpsPmInit\n");
    return gpsPmInit(client, pfunc1, pfunc2);
}
/***********************************************************************************************************
*Function Name: GPS_GetModelInfo()
*Attributes:
*client  IN   Client identifier
*dummy   IN   Remove the loops from the code
*num     IN   The integer starting from 1.
*key     IN   Search key
*category  IN Category
*value_len IN The size of value[] (the array for return value).
*value     OUT The address for the array for return value. Values acceptable for key are copied.
*Description: This function retrieves model-specific information.
************************************************************************************************************/
int GPS_GetModelInfo(char  dummy, char num,char       *key, char      *category,      unsigned char value_len)
{
	printf("Call gpsGetModelInfo \n");
	int retval;

	printf("GPS_GetModelInfo(), key = [%s]\n",key);
	printf("GPS_GetModelInfo(), value_len  = [%d]\n",value_len);
	retval = gpsGetModelInfo(gps_client, dummy, num, (unsigned char *) key, (unsigned char *)category, value_len, outbuf) ;
	
	printf("GPS_GetModelInfo(), outbuf  = [%s]\n",outbuf);
	if(retval != SERCH_OK)
		return -1;

   /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 208 209	*/

   return 0;
}

/***********************************************************************************************************
*Function Name: GPS_PenvOpen()
*Attributes:
*client  IN   Client identifier
*penv IN Environment variable table handler
*Description: This function opens the environment variable table.
************************************************************************************************************/
int GPS_PenvOpen(gwmsg_client_t *client, char *penv_name, long size)
{
    printf("------------------------------------- \n");
	printf("Calling gpsPenvOpen\n");
	return gpsPenvOpen(gps_client, penv_name, size);
}
/***********************************************************************************************************
*Function Name: GPS_PenvGetValue()
*Attributes:
*client  IN   Client identifier
*penv IN Environment variable table handler
*        Value obtained as the return value of gpsPenvOpen() function
*var IN Environment variable ID (defined separately)
*val OUT Environment variable value obtained
*Description: This function obtains the current environment variable setting.
************************************************************************************************************/
int GPS_PenvGetValue( gwmsg_client_t* client, int penv, long gps_var, long *penv_val )
{
	printf("------------------------------------- \n");
    printf("Calling gpsPenvGetVal \n");
	return gpsPenvGetValue( gps_client, penv, gps_var, penv_val );
}
/***********************************************************************************************************
*Function Name: GPS_Color_getShrd()
*Attributes:
*client  IN   Client identifier
*= Return value =
*Offset from the shared memory pointer to the color data shared memory pointer.
*Description: This function retrieves color data shared memory
************************************************************************************************************/
long GPS_Color_getShrd(void)
{

  if(loffset = gpsColor_getShrd( gps_client ))
    clr_shm = (gps_nclr_shdm_t*)((long)gps_shdm_addr + loffset);
  else
    return -1;

  /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 292	*/
  return 0;
}

/***********************************************************************************************************
*Function Name: GPS_Color_getRID()
*Attributes:
*client  IN   Client identifier
*modeID IN ID obtained by gpsColor_getID()
*rID OUT Stores rearrange ID
*rID_size OUT Number of bytes of rID
*Description: This function retrieves ID for Page Structure's rearrange matrix pattern ID, from color mode ID.
************************************************************************************************************/
int GPS_Color_getRID( int modeID, gps_color_rid_t *rID, long *rID_size )
{
	int ret;
	printf("Calling gpsColor_getRID\n");
	ret = gpsColor_getRID(gps_client, modeID, rID, rID_size);
	return ret;
}

/***********************************************************************************************************
*Function Name: GPS_Color_getProfile()
*Attributes:
*client  IN   Client identifier
**addr   OUT  Address of the shared memory area for the Color Matching Profile table
*num     OUT  Number of profiles in Color Matching Profile table
*Description: This function obtains the address to the shared memory for the Color Matching Profile table used for PDL.
************************************************************************************************************/
int GPS_Color_getProfile(gwmsg_client_t  *client, void **addr, long	*num)
{ 
     printf("------------------------------------- \n");
	 printf("Calling gpsColor_getProfile\n");
    return gpsColor_getProfile( gps_client, addr, num );
}
/***********************************************************************************************************
*Function Name: GPS_GetFontInfo()
*Attributes:
*client  IN   Client identifier
*font IN Font type
**fontinfo OUT Font Information Structure
*Description: This function obtains font information.
************************************************************************************************************/
int GPS_GetFontInfo(int font)
{
  if( -1 == gpsGetFontInfo(gps_client, font, &fontinfo) )
    return -1;

  /*No need to map the GPS font structure with SDK, as we have created similar struct in SDK..	*/
  return 0;
}

/***********************************************************************************************************
*Function Name: GPS_PenvClose()
*Attributes:
*client  IN   Client identifier
*penv    IN Environment variable table handler
*Description: This function closes the environment variable table.
************************************************************************************************************/
void GPS_PenvClose(gwmsg_client_t *client, int penv)
{
    printf("------------------------------------- \n");
	printf("Calling gpsPenvClose\n");
   gpsPenvClose( gps_client , penv );
   
}
/***********************************************************************************************************
*Function Name: GPS_TrayInfo()
*Attributes:
*client  IN   Client identifier
*num     IN   Number of the trayinfo[] arrays. Set the number of trays indicated in the information obtained
*                by gpsGetSysInfo() function.
*trayinfo OUT Input Tray Information Structure
*trayinfo_num OUT Returns the number of trays set to trayinfo[] array.
*notify IN Set to receive / not receive event whenever there is a change in the information.
*Description: This function obtains input tray information.
************************************************************************************************************/
int GPS_TrayInfo()
{
  long trayNum;
  int nTrayIndex;

#define YET_TO_FIND_0 200
#define YET_TO_FIND_1 201
#define YET_TO_FIND_2 202
#define YET_TO_FIND_3 203
#define YET_TO_FIND_4 204
#define YET_TO_FIND_5 205
#define YET_TO_FIND_6 206
#define YET_TO_FIND_7 207

#ifdef PMS_OIL_MERGE_DISABLE_MEM
  gpsTrayInfo = (gps_trayinfo_t*) OSMalloc(sysinfo.num_tray * sizeof(gps_trayinfo_t), PMS_MemoryPoolPMS);
  g_pstTrayInfo = (PMS_TyTrayInfo*) OSMalloc(sysinfo.num_tray * sizeof(PMS_TyTrayInfo), PMS_MemoryPoolPMS);
#else
  gpsTrayInfo = (gps_trayinfo_t*) mmalloc(sysinfo.num_tray * sizeof(gps_trayinfo_t));
  g_pstTrayInfo = (PMS_TyTrayInfo*) mmalloc(sysinfo.num_tray * sizeof(PMS_TyTrayInfo));
#endif

  if( -1 == gpsGetTrayInfo(gps_client, sysinfo.num_tray, gpsTrayInfo, &trayNum, GPS_NOTIFY_CHANGE_OFF) )
    return -1;
  /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 37	*/
  /* gpsGetTrayInfo - page no 197	*/

  for(nTrayIndex = 0; nTrayIndex < trayNum; nTrayIndex++)
  {
    switch(gpsTrayInfo[nTrayIndex].id)
	{
	  case 0:
        g_pstTrayInfo[nTrayIndex].eMediaSource = PMS_TRAY_MANUALFEED;
		break;
      case 1:
        g_pstTrayInfo[nTrayIndex].eMediaSource = PMS_TRAY_TRAY1;
		break;
      case 2:
        g_pstTrayInfo[nTrayIndex].eMediaSource = PMS_TRAY_TRAY2;
		break;
      case 3:
        g_pstTrayInfo[nTrayIndex].eMediaSource = PMS_TRAY_TRAY3;
		break;
      default:
        g_pstTrayInfo[nTrayIndex].eMediaSource = PMS_TRAY_AUTO; 
		break;
		
		//Yet to map PMS_TRAY_BYPASS, PMS_TRAY_ENVELOPE
	}
	
	
	//Guess!!!!!!  the paper size.
	/*
	GPS_CODE_NO_PAPER = 0,
	GPS_CODE_A0,		GPS_CODE_A1,		GPS_CODE_A2,		GPS_CODE_A3,
	GPS_CODE_A4,		GPS_CODE_A5,		GPS_CODE_A6,		GPS_CODE_A7,
	GPS_CODE_B0,		GPS_CODE_B1,		GPS_CODE_B2,		GPS_CODE_B3,
	GPS_CODE_B4,		GPS_CODE_B5,		GPS_CODE_B6,		GPS_CODE_B7,
	GPS_CODE_WMAIL,		GPS_CODE_MAIL,		GPS_CODE_LINE1,		GPS_CODE_LINE2,
	GPS_CODE_LIB6,		GPS_CODE_LIB8,		GPS_CODE_210x170,	GPS_CODE_210x182,
	GPS_CODE_267x388,

	GPS_CODE_FREEmm = 31,
	GPS_CODE_11x17,
	GPS_CODE_11x14,		GPS_CODE_10x15,		GPS_CODE_10x14,		GPS_CODE_8Hx14,
	GPS_CODE_8Hx13,		GPS_CODE_8Hx11,		GPS_CODE_8Qx14,		GPS_CODE_8Qx13,
	GPS_CODE_8x13,		GPS_CODE_8x10H,		GPS_CODE_8x10,		GPS_CODE_5Hx8H,
	GPS_CODE_7Qx10H,

	GPS_CODE_12x18 = 47,
	GPS_CODE_12x14H,
	GPS_CODE_11x15,		GPS_CODE_9Hx11,		 GPS_CODE_8Hx12,	GPS_CODE_13x19,

	GPS_CODE_8KAI = 66,
	GPS_CODE_16KAI,

	GPS_CODE_NO_10 = 80,
	GPS_CODE_NO_7,

	GPS_CODE_C5 = 83,
	GPS_CODE_C6,		GPS_CODE_DL,

	GPS_CODE_NO_SIZE = 128,
	GPS_CODE_A0T,		GPS_CODE_A1T,		GPS_CODE_A2T,		GPS_CODE_A3T,
	GPS_CODE_A4T,		GPS_CODE_A5T,		GPS_CODE_A6T,		GPS_CODE_A7T,
	GPS_CODE_B0T,		GPS_CODE_B1T,		GPS_CODE_B2T,		GPS_CODE_B3T,
	GPS_CODE_B4T,		GPS_CODE_B5T,		GPS_CODE_B6T,		GPS_CODE_B7T,
	GPS_CODE_WMAILT,	GPS_CODE_MAILT,		GPS_CODE_LINE1T,	GPS_CODE_LINE2T,
	GPS_CODE_LIB6T,		GPS_CODE_LIB8T,		GPS_CODE_210x170T,	GPS_CODE_210x182T,
	GPS_CODE_267x388T,

	GPS_CODE_FREEmmT = 159,
	GPS_CODE_11x17T,
	GPS_CODE_11x14T,	GPS_CODE_10x15T,	GPS_CODE_10x14T,	GPS_CODE_8Hx14T,
	GPS_CODE_8Hx13T,	GPS_CODE_8Hx11T,	GPS_CODE_8Qx14T,	GPS_CODE_8Qx13T,
	GPS_CODE_8x13T,		GPS_CODE_8x10HT,	GPS_CODE_8x10T,		GPS_CODE_5Hx8HT,
	GPS_CODE_7Qx10HT,

	GPS_CODE_12x18T = 175,
	GPS_CODE_12x14HT,
	GPS_CODE_11x15T,	GPS_CODE_9Hx11T,	 GPS_CODE_8Hx12T,	GPS_CODE_13x19T,

	GPS_CODE_8KAIT = 194,
	GPS_CODE_16KAIT,

	GPS_CODE_NO_10T = 208,
	GPS_CODE_NO_7T,

	GPS_CODE_C5T = 211,
	GPS_CODE_C6T,		GPS_CODE_DL_T
	*/
	
	switch(gpsTrayInfo[nTrayIndex].p_size)
	{
	  case GPS_CODE_8Hx11:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_LETTER;
	    break;
	  case GPS_CODE_A4:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A4;
	    break;
	  case GPS_CODE_8Hx14:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_LEGAL;
	    break;
	  case GPS_CODE_7Qx10H:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_EXE;
	    break;
	  case GPS_CODE_A3:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A3;
	    break;
	  case GPS_CODE_11x17:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_TABLOID;
	    break;
	  case GPS_CODE_A5:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A5;
	    break;
	  case GPS_CODE_A6:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A6;
	    break;
	  case GPS_CODE_C5:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_C5_ENV;
	    break;
	  case GPS_CODE_DL:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_DL_ENV;
	    break;
	  case YET_TO_FIND_0:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_LEDGER;
	    break;
	  case YET_TO_FIND_2:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_OFUKU;
	    break;
	  case GPS_CODE_10x14:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_JISB4;
	    break;
	  case YET_TO_FIND_3:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_JISB5;
	    break;
	  case GPS_CODE_8Hx11T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_LETTER_R;
	    break;
	  case GPS_CODE_A4T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A4_R;
	    break;
	  case GPS_CODE_8Hx14T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_LEGAL_R;
	    break;
	  case GPS_CODE_7Qx10HT:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_EXE_R;
	    break;
	  case GPS_CODE_A3T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A3_R;
	    break;
	  case GPS_CODE_11x17T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_TABLOID_R;
	    break;
	  case GPS_CODE_A5T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A5_R;
	    break;
	  case GPS_CODE_A6T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_A6_R;
	    break;
	  case GPS_CODE_C5T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_C5_ENV_R;
	    break;
	  case GPS_CODE_DL_T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_DL_ENV_R;
	    break;
	  case YET_TO_FIND_4:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_LEDGER_R;
	    break;
	  case YET_TO_FIND_5:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_OFUKU_R;
	    break;
	  case GPS_CODE_10x14T:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_JISB4_R;
	    break;
	  case YET_TO_FIND_6:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_JISB5_R;
	    break;
	  case YET_TO_FIND_7:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_CUSTOM;
	    break;
	  default:
	    g_pstTrayInfo[nTrayIndex].ePaperSize = PMS_SIZE_DONT_KNOW;
	    break;
	}
	
	switch(gpsTrayInfo[nTrayIndex].p_kind)
	{
	  case DI_PAPER_NORMAL:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_PLAIN;
	    break;
	  case DI_PAPER_BOND:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_BOND;
	    break;
	  case DI_PAPER_SPECIAL:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_SPECIAL;
	    break;
	  case DI_PAPER_GLOSSY:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_GLOSSY;
	    break;
	  case DI_PAPER_OHP:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_TRANSPARENCY;
	    break;
	  case DI_PAPER_RECYCLE:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_RECYCLED;
	    break;
	  case DI_PAPER_MIDDLETHICK:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_THICK;
	    break;
	  case DI_PAPER_ENVELOPE:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_ENVELOPE;
	    break;
	  case DI_PAPER_POSTCARD:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_POSTCARD;
	    break;
	  case DI_PAPER_THIN:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_THIN;
	    break;
	  case DI_PAPER_LABEL:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_LABEL;
	    break;
	  case DI_PAPER_PREPRINT:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_PREPRINTED;
	    break;
	  case DI_PAPER_LETTER_HEAD:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_LETTERHEAD;
	    break;
	  default:
	    g_pstTrayInfo[nTrayIndex].eMediaType = PMS_TYPE_DONT_KNOW;
	    break;
	}
	
	g_pstTrayInfo[nTrayIndex].eMediaColor = PMS_COLOR_DONT_KNOW; /* yet to map	*/
    g_pstTrayInfo[nTrayIndex].uMediaWeight = 0; /* yet to map	*/
    g_pstTrayInfo[nTrayIndex].nPriority = nTrayIndex; /* assumption yet to conform. 	*/
	
	g_pstTrayInfo[nTrayIndex].bTrayEmptyFlag = (GPS_TRAY_PAPEREND == gpsTrayInfo[nTrayIndex].status);
    g_pstTrayInfo[nTrayIndex].nNoOfSheets = gpsTrayInfo[nTrayIndex].remain;

  }
  
  g_nInputTrays = sysinfo.num_tray;
#ifdef PMS_OIL_MERGE_DISABLE_MEM
  OSFree( gpsTrayInfo, PMS_MemoryPoolPMS );
#else
  mfree( gpsTrayInfo );
#endif
  gpsTrayInfo = NULL;
    
  return 0;
}
/***********************************************************************************************************
*Function Name: GPS_BinInfo()
*Attributes:
*client  IN   Client identifier
*num     IN Number of bininfo[] array. Set the number of output bins obtained by gpsGetSysInfo().
*bininfo OUT Output Bin Information Structure
*bininfo_num OUT Returns the number of bins set to bininfo[] array.
*notify  IN Enable/disable receiving an event whenever there is a change in the information.
*Description: This function obtains output bin information.
************************************************************************************************************/
int GPS_BinInfo()
{
  long binInfo;
  int nTrayIndex;
#ifdef PMS_OIL_MERGE_DISABLE_MEM
  gpsBinInfo = (gps_bininfo_t*) OSMalloc(sysinfo.num_bin * sizeof(gps_bininfo_t), PMS_MemoryPoolPMS);
  g_pstOutputInfo = (PMS_TyOutputInfo*) OSMalloc(sysinfo.num_bin * sizeof(PMS_TyOutputInfo), PMS_MemoryPoolPMS);
#else
  gpsBinInfo = (gps_bininfo_t*) mmalloc(sysinfo.num_bin * sizeof(gps_bininfo_t));
  g_pstOutputInfo = (PMS_TyOutputInfo*) mmalloc(sysinfo.num_bin * sizeof(PMS_TyOutputInfo));
#endif

  if( -1 == gpsGetBinInfo(gps_client, sysinfo.num_bin, gpsBinInfo, &binInfo, GPS_NOTIFY_CHANGE_OFF) )
    return -1;
  
  /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 40	*/
  /* gpsGetTrayInfo - page no 200	*/
  
  for(nTrayIndex = 0; nTrayIndex < binInfo; nTrayIndex++)
  {
    /*g_pstOutputInfo[nTrayIndex].eOutputTray = gpsBinInfo[nTrayIndex].id;	*/
	switch (gpsBinInfo[nTrayIndex].id)
	{
	  case 1:
	  case 2:
	  case 3:
	    g_pstOutputInfo[nTrayIndex].eOutputTray = gpsBinInfo[nTrayIndex].id;
	    break;
	  default:
	    g_pstOutputInfo[nTrayIndex].eOutputTray = PMS_OUTPUT_TRAY_AUTO;
	    break;
      /* yet to map  PMS_OUTPUT_TRAY_UPPER, PMS_OUTPUT_TRAY_LOWER, PMS_OUTPUT_TRAY_EXTRA	*/
	}
    g_pstOutputInfo[nTrayIndex].nPriority = nTrayIndex;	/*assumption yet to conform. 	*/
	
  }

  g_nOutputTrays = sysinfo.num_bin;
#ifdef PMS_OIL_MERGE_DISABLE_MEM
  OSFree( gpsBinInfo, PMS_MemoryPoolPMS );
#else
  mfree( gpsBinInfo );
#endif
  gpsBinInfo = NULL;
  
  return 0;
}
/***********************************************************************************************************
*Function Name: GPS_PenvGetDefValue()
*Attributes:
*client  IN   Client identifier
*penv IN Environment variable table handler
*         IN Value obtained as the return value by gpsPenvOpen() function
*var IN Environment variable ID (defined separately)
*val OUT Environment variable value obtained
*Description: This function retrieves default environment variable value.
************************************************************************************************************/
int GPS_PenvGetDefValue(gwmsg_client_t *client, int p_env, long Var, long *Val)
{
	 printf("------------------------------------- \n");
	 printf("Call Environment Def value\n");
	return gpsPenvGetDefValue(client, p_env, Var, Val);
}
/***********************************************************************************************************
*Function Name: GPS_PenvGetValueList()
*Attributes:
*client  IN   Client identifier
*penv    IN   Handler for environment variable table
*              The value obtained as returned value by gpsPenvOpen() function
*var IN Environment variable ID
*start IN Number of the environment variable to be obtained from the list (the number starting
*           from the top)
*num IN Number of the environment variable values to be obtained == the length of the array
*         value[]
*value OUT Pointer to the array to assign the list of values
*value_size OUT Number of valid entries from the variable list entered to var[]
*Description: This function obtains the list of environment variable values.
************************************************************************************************************/
int  GPS_PenvGetValueList(gwmsg_client_t *client, int p_env, long Var, long Start, long Number1, long *Val, long *Val_num)
{
	 printf("------------------------------------- \n");
	 printf("Call Environmental variable\n");
          return gpsPenvGetValueList(client, p_env, Var, Start, Number1, Val, Val_num);
}
/***********************************************************************************************************
*Function Name: GPS_GetBitSw()
*Attributes:
*client  IN   Client identifier
*no IN Bit Switch number (BIT_SW_001 -- BIT_SW_016)
*Description: This function obtains values of specified Bit Switch number.
************************************************************************************************************/
int GPS_GetBitSw(int num)
{
	 printf("------------------------------------- \n");
	 printf("Call GPS_getBitSW\n");
	 return gpsGetBitSw(gps_client, num);
}

/***********************************************************************************************************
*Function Name: GPS_InterpNotifyStart()
*Attributes:
*client  IN   Client identifier
*interp_id IN Interpreter ID
*Description: This function notifies the system the start of the interpreter.
************************************************************************************************************/
int GPS_InterpNotifyStart(gwmsg_client_t *client, int interpre_ID)
{
	 printf("------------------------------------- \n");
	 printf("call notifyStart\n");
	return gpsInterpNotifyStart(client, interpre_ID);
}
/***********************************************************************************************************
*Function Name: GPS_InterpNotifyOnline()
*Attributes:
*client  IN   Client identifier
*Description: This event notifies the printer's online state to the interpreter.
************************************************************************************************************/
void GPS_InterpNotifyOnline(gwmsg_client_t *client)
	{
		 printf("------------------------------------- \n");
		 printf("Call notify Online\n");
		return gpsInterpNotifyOnline(client);
	}
	
/***********************************************************************************************************
*Function Name: GPS_PmDispSetEmulation()
*Attributes:
*client  IN   Client identifier
*
*Description: 
************************************************************************************************************/
void GPS_PmDispSetEmulation(char	cond_exist,	char	pnum_exist,	char	tray_exist,	char	*str)
{
     printf("------------------------------------- \n");
	 printf("Call gpsPmDispSetEmulation\n");
    gpsPmDispSetEmulation(cond_exist, pnum_exist,tray_exist, str);
}
/***********************************************************************************************************
*Function Name: GPS_GetSysInfo()
*Attributes:
*client  IN   Client identifier
*sysinfo OUT System Information Structure
*Description: This function obtains system information.
************************************************************************************************************/
int GPS_GetSysInfo()
{
  printf("Call gpsGetSysInfo()..\n");
  if( 0 != gpsGetSysInfo(gps_client, &sysinfo) )
    return -1;

/*  strcpy(g_tSystemInfo.szManufacturer, sysinfo.maker);	*/
/*  strcpy(g_tSystemInfo.szProduct, sysinfo.model);	*/
/*  g_nInputTrays = sysinfo.num_tray; 	*/	/*Override by EngineGetTrayInfo(), Do reassign in GPS_TrayInfo.*/
/*  g_nOutputTrays = sysinfo.num_bin; 	*/	/*Override by EngineGetTrayInfo(), Do reassign in GPS_BinInfo.	*/

  /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 8 to 13	*/
  /*
  num_tray ----- Number of input trays.
  num_bin ------ Number of output bins.
  disp_lines/disp_columns  -------  The number of lines displayed on the screen, and the number of characters per line.
  */
  return 0;
}

/***********************************************************************************************************
*Function Name: GPS_WkSizeFree()
*Attributes:
*client  IN   Client identifier
*= Return value =
*byte value
*Description: This function obtains the size of available working memory in bytes.
************************************************************************************************************/
int GPS_WkSizeFree(gwmsg_client_t *client)  
{
	printf("------------------------------------- \n");
	printf("Call gpsWkSizeFree\n");

	return gpsWkSizeFree(client );
}
/***********************************************************************************************************
*Function Name: GPS_WkMalloc()
*Attributes:
*client  IN   Client identifier
*= Return value =
*byte value
*Description: This function obtains the size of available working memory in bytes.
************************************************************************************************************/
caddr_t GPS_WkMalloc(gwmsg_client_t *client, long mallocsize) 
{
  printf("------------------------------------- \n");
  printf("Call gpsWkMalloc\n");
  return gpsWkMalloc(client, mallocsize );
}
/***********************************************************************************************************
*Function Name: GPS_ColorgetID2()
*Attributes:
*client  IN   Client identifier
*hdpi IN Horizontal resolution
*vdpi IN Vertical resolution
*bit IN Quantifying bit
*draw IN Drawing mode
*prt IN Print mode
*paper IN Paper type
*modeID OUT Color mode ID
*Description: Obtains dither data and gamma data array number within shared memory.
************************************************************************************************************/
int GPS_Color_getID2(int hdpi, int vdpi, int bit, int draw, unsigned char prt,unsigned char paper)
{
  int modeID ;
  gpsColor_getID2(gps_client, hdpi, vdpi, bit, draw, prt, paper, &modeID);
  return modeID;
}
/***********************************************************************************************************
*Function Name: GPS_gpsGetHddInfo2()
*Attributes:
*client   IN   Client identifier
*hdd      IN   Memory type: HDD/RAM/SD
**status  OUT  indicates whether information is obtained.
**hddinfo2 OUT HDD information structure 2
*Description: Obtains information of HDD/RAM/SD.
************************************************************************************************************/
int GPS_gpsGetHddInfo2(int hdd)
{
  int status;
	gpsGetHddInfo2(gps_client, hdd, &status, &hddinfo_download);
	return status;
}


/***********************************************************************************************************
*Function Name: GPS_GetPdlPrintConditionShm()
*Attributes:
*client IN      Client identifier
*ujobid IN      User job ID
*status OUT     result
**offset OUT    Offset to the storage area of Printing Conditions
*Description: This API retrieves information on printing conditions
************************************************************************************************************/

int GPS_GetPdlPrintConditionShm(gwmsg_client_t *client,int ujobid,int *status,unsigned long *offset)
{
	printf("------------------------------------- \n");
    printf("Call gpsGetPdlPrintConditionShm\n");
    return gpsGetPdlPrintConditionShm(client, ujobid,status,offset);
}

/***********************************************************************************************************
*Function Name: GPS_GetPaperInfo()
*Attributes:
*client    IN     Client identifier
*paper_id  IN     Paper size ID
*paperinfo OUT     Paper Information Structure (Reply is currently not supported)
*notify    IN     Undefined
*Description: This function obtains paper (media) information
************************************************************************************************************/

int GPS_GetPaperInfo(gwmsg_client_t *client, int PaperId, gps_paperinfo_t *gpsPaperInfo, int notify)
{
	printf("------------------------------------- \n");
	printf("Call gpsGetPaperInfo\n");
	return gpsGetPaperInfo(client, PaperId, gpsPaperInfo, notify);
}

/***********************************************************************************************************
*Function Name: GPS_InterpNotifyState()
*Attributes:
*client IN      Client identifier
*state  IN      Status
*Description: This function notifies the status of the interpreter
************************************************************************************************************/

void GPS_InterpNotifyState(gwmsg_client_t *client, int number)
{
	printf("------------------------------------- \n");
	printf("Call gpsInterpNotifyState\n");
	return gpsInterpNotifyState(client, number);
}

/***********************************************************************************************************
*Function Name: GPS_SinOpen()
*Attributes:
*client IN      Client identifier
*hostid IN      Host ID
*Description: This function opens receiving buffer.
************************************************************************************************************/
gps_hostbuf_p GPS_SinOpen(gwmsg_client_t *client, int host_id)
{
	printf("------------------------------------- \n");
	printf("Call gpsSinOpen\n");
	return gpsSinOpen(client, host_id);
}

/***********************************************************************************************************
*Function Name: GPS_SoutOpen()
*Attributes:
*client IN     Client identifier
*hostid IN     Host ID
*Description: This function opens sending buffer.
************************************************************************************************************/
gps_hostbuf_p GPS_SoutOpen(gwmsg_client_t *client, int host_id)
{
	printf("------------------------------------- \n");
	printf("Call gpsSoutOpen\n");
	return gpsSoutOpen(client, host_id);
}

/***********************************************************************************************************
*Function Name: GPS_GetPdlTable()
*Attributes:
*client     IN     Client identifier
**offset    OUT     Offset of the PDL Information Structure arrays
**num       OUT     The number of structures (arrays)
*Description: This function obtains information of the installed PDL.
************************************************************************************************************/
int GPS_GetPdlTable(gwmsg_client_t *client, long *pdl_offset, int *pdl_num)
{
	printf("------------------------------------- \n");
	printf("Call gpsGetPdlTable\n");
	return gpsGetPdlTable(client, pdl_offset, pdl_num);
}

/***********************************************************************************************************
*Function Name: GPS_GetPrtStatus2()
*Attributes:
*client     IN    Client identifier
*prtstatus  OUT    Printer Status Information Structure
*notify     IN    Enable/disable receiving event notification whenever printer status changes.
*result     OUT    Return value (0: Successful, -1: Failed)
*Description: This function obtains printer status information.
************************************************************************************************************/
int GPS_GetPrtStatus2(gwmsg_client_t *client, gps_prtstatus2_t *prtStatus, int prt_notify, int *prt_res)
{
	printf("------------------------------------- \n");
	printf("Call gpsGetPrtStatus2\n");
	return gpsGetPrtStatus2(client, prtStatus, prt_notify, prt_res);
}
/***********************************************************************************************************
*Function Name: GPS_PlotPrepare()
*Attributes:
*client     IN   
*uJobid     OUT    
**Param     OUT    
*Description: 
************************************************************************************************************/
int GPS_PlotPrepare(gwmsg_client_t *client, int uJobid, gps_plotprepareparam_t *Param)
{
	printf("------------------------------------- \n");
	printf("Call gpsPlotPrepare\n");
	/*return 0;*/ /* Call to gpsPlotPrepare(client, uJobid, Param); is commented
                as there is dependency on _CNF_API_gpsPlotPrepare*/
    return gpsPlotPrepare(client, uJobid, Param);
}

/***********************************************************************************************************
*Function Name: GPS_PlotOpen()
*Attributes:
*client    IN    Client identifier
*ujobid    IN    User Job ID
*openmode  IN    Open mode    
*Description:  This function obtains plotter structure for printing, and starts print process.
************************************************************************************************************/
int GPS_PlotOpen(gwmsg_client_t *client, int plotOpen_ujobid, int plotOpen_openmode)
{
	printf("------------------------------------- \n");
	printf("Call gpsPlotOpen\n");
	return gpsPlotOpen(client, plotOpen_ujobid, plotOpen_openmode);
}

/***********************************************************************************************************
*Function Name: GPS_PlotSetPageParamShm()
*Attributes:
*client         IN      Client identifier
*plotid         IN      Plotter ID
*ppageparam_shm IN      Print Page Conditions structure
*result         OUT      Return value (0: Successful, -1: Busy, -2: Failed)   
*Description:  This function sets the printing conditions for the Plotter structure
************************************************************************************************************/
int GPS_PlotSetPageParamShm(gwmsg_client_t *client, int	PlotSet_plotid, gps_pageparam_shm_t	*param, int	*PlotSet_result)
{
	printf("------------------------------------- \n");
	printf("Call gpsPlotSetPageParamShm\n");
	/*return 0;		*/	
	/* Call to gpsPlotSetPageParamShm(client, PlotSet_plotid, param, PlotSet_result); is commented as there is dependency on _CNF_API_gpsPlotSetPageParamShm */
	return gpsPlotSetPageParamShm(client, PlotSet_plotid, param, PlotSet_result);
}

/***********************************************************************************************************
*Function Name: GPS_FrameCreateEx()
*Attributes:
*client                     
*framecreate_plotid         
*pagemode2                 
*pageinfo2                    
*framecreate_result 
*Description:  
************************************************************************************************************/
int GPS_FrameCreateEx(gwmsg_client_t *client, int framecreate_plotid, const gps_pagemode2_t *pagemode2, const gps_pageinfo2_t *pageinfo2, int *framecreate_result)
{
	printf("------------------------------------- \n");
	printf("Call gpsFrameCreateEx\n");
	return gpsFrameCreateEx(client, framecreate_plotid, pagemode2, pageinfo2, framecreate_result);
}

/***********************************************************************************************************
*Function Name: GPS_FrameCreateInfoRes()
*Attributes:
*client         IN     Client identifier
*plotid         IN     Plotter ID
*pagemode       IN   Pointer to the Print Page Mode Structure
*ppageinfo      IN  Print page information
*force          IN      Form Feed flag
*pFCR           OUT       Frame creation result
*Description:  This function creates frame, and passes the information necessary to print frame.
************************************************************************************************************/
int GPS_FrameCreateInfoRes(gwmsg_client_t *client, int FCinfo_plotid, gps_pagemode_p pagemode, gps_pageinfo_t *pageinfo, int FCinfo_force, gwmsg_GpsPage_FrameCreate_Res_t	*pFCR)
{
	printf("------------------------------------- \n");
	printf("Call gpsFrameCreateInfoRes\n");
	return gpsFrameCreateInfoRes(client, FCinfo_plotid, pagemode, pageinfo, FCinfo_force, pFCR);
}

/***********************************************************************************************************
*Function Name: GPS_FrameGetBandRes()
*Attributes:
*client    IN        Client identifier
*frameid   IN        Frame ID
*bandid    IN        Band ID (ID for the frame buffer)
*planeid   IN        Plane ID
*pFGBR     OUT        Frame buffer obtained result
*Description:  This function Obtains frame buffer.
************************************************************************************************************/
int GPS_FrameGetBandRes(gwmsg_client_t *client, int	FGband_frameid, int FGband_bandid, int FGband_planeid, gwmsg_GpsPage_FrameGetBand_Res_t *pFGBR)
{
	printf("------------------------------------- \n");
	printf("Call gpsFrameGetBandRes\n");
	return gpsFrameGetBandRes(client, FGband_frameid, FGband_bandid, FGband_planeid, pFGBR);
}

/***********************************************************************************************************
*Function Name: GPS_FrameFlushBandRes()
*Attributes:
*client    IN      Client identifier
*frameid   IN      Frame ID
*bandid    IN      Band ID (assigned from 0)
*planeid   IN      Plane ID
*drawn     IN      Drawing result
*flush     IN      Flush flag
*pFFBR     OUT      Result of the ending of drawing
*Description:  This function ends drawing to the frame buffer.
************************************************************************************************************/
int GPS_FrameFlushBandRes(gwmsg_client_t *client,int FFB_frameid,int FFB_bandid,int	FFB_planeid,int	FFB_drawn,int FFB_flush,gwmsg_GpsPage_FrameFlushBand_Res_t	*pFFBR)
{
	printf("------------------------------------- \n");
	printf("Call gpsFrameFlushBandRes\n");
	return gpsFrameFlushBandRes(client, FFB_frameid, FFB_bandid, FFB_planeid, FFB_drawn, FFB_flush, pFFBR);
}

/***********************************************************************************************************
*Function Name: GPS_FramePrintInfo()
*Attributes:
*client      IN      Client identifier
*frameid 	 IN      Frame ID
*ppageinfo2  IN      Print Page Information Structure 2
*flag 		 OUT      Supported parameters
*Description:  This function Sets the information of the page to print.
************************************************************************************************************/
int GPS_FramePrintInfo(gwmsg_client_t *client, int FP_frameid, const gps_pageinfo2_t *pageinfo2, unsigned long *FP_flag)
{
	printf("------------------------------------- \n");
	printf("Call gpsFramePrintInfo\n");
	return gpsFramePrintInfo(client, FP_frameid, pageinfo2, FP_flag);
}

/***********************************************************************************************************
*Function Name: GPS_FramePrint()
*Attributes:
*client 	IN     Client identifier
*frameid 	IN     Frame ID
*ppageinfo 	IN     Print Page Information
*force 		IN     Form Feed flag
*Description:  This function prints frames.
************************************************************************************************************/
int GPS_FramePrint(gwmsg_client_t *client, int FP_frameid, const gps_pageinfo_t *pageinfo, int FP_force)
{
	printf("------------------------------------- \n");
	printf("Call gpsFramePrint\n");
	return gpsFramePrint(client, FP_frameid, pageinfo, FP_force);
}

/***********************************************************************************************************
*Function Name: GPS_FrameClose()
*Attributes:
*client     IN         Client identifier
*frameid    IN         Frame ID
*Description:  This function ends creating frames.
************************************************************************************************************/
int GPS_FrameClose(gwmsg_client_t *client, int FP_frameid)
{
	printf("------------------------------------- \n");
	printf("Call gpsFrameClose\n");
	return gpsFrameClose(client, FP_frameid);
}

/***********************************************************************************************************
*Function Name: GPS_PenvSetDefValue()
*Attributes:
*client 			IN 		Client identifier
*penv 				IN 		Environment variable table handler
*penv_var 			IN 		Environment variable ID (defined separately)
*penv_val 			IN 		Environment variable value to set
*Description:  This function sets default environment variable value
************************************************************************************************************/
int GPS_PenvSetDefValue(gwmsg_client_t *client, int penv, long penv_var, long penv_val)
{
	printf("------------------------------------- \n");
	printf("Call gpsPenvSetDefValue\n");
	return gpsPenvSetDefValue(client, penv, penv_var, penv_val);
}

/***********************************************************************************************************
*Function Name: GPS_PlotClose()
*Attributes:
*client 	IN 		Client identifier
*plotid 	IN 		Plotter ID
*Description:  This function ends print process, and frees the Plotter Structure
************************************************************************************************************/
int GPS_PlotClose(gwmsg_client_t *client, int plotid)
{
	printf("------------------------------------- \n");
	printf("Call gpsPlotClose\n");
	return gpsPlotClose(client, plotid);
}
/***********************************************************************************************************
*Function Name: GPS_SinClose()
*Attributes:
*hostbuf 	IN 		Pointer to the Host Buffer Structure retrieved by gpsSinOpen() function
*Description:  This function closes receiving buffer.
************************************************************************************************************/
int GPS_SinClose(gps_hostbuf_p hostbuf)
{
	printf("------------------------------------- \n");
	printf("Call gpsSinClose\n");
	return gpsSinClose(hostbuf);
}
/***********************************************************************************************************
*Function Name: GPS_SoutClose()
*Attributes:
*hostbuf 	IN 		Pointer to Host Buffer Structure obtained by gpsSoutOpen() function.
*Description:  This function closes the sending buffer
************************************************************************************************************/
int GPS_SoutClose(gps_hostbuf_p hostbuf)
{
	printf("------------------------------------- \n");
	printf("Call gpsSoutClose\n");
	return gpsSoutClose(hostbuf);
}
/***********************************************************************************************************
*Function Name: GPS_InterpFinishProcData()
*Attributes:
*client 	IN    Client identifier
*ujobid 	IN    User Job ID
*fin 		IN    End status
*uel_found 	IN    Set 1 if UEL is detected and read from the host buffer. Set 0 if UEL is not detected
*Description:  Interpreter notifies GPS the end of PDL data processing
************************************************************************************************************/
void GPS_InterpFinishProcData(gwmsg_client_t *client, int ujobid, int fin, int uel_found)
{
	printf("------------------------------------- \n");
	printf("Call gpsInterpFinishProcData\n");
	return gpsInterpFinishProcData(client, ujobid, fin, uel_found);
}
/***********************************************************************************************************
*Function Name: GPS_Close()
*Attributes:
*client   IN   Client identifier
*shm_addr IN Shared memory address
*Description: This function closes GPS as the client connecting to GPS.
************************************************************************************************************/
void GPS_Close(gwmsg_client_t *client, void *shm_addr)
{
   printf("------------------------------------- \n");   
   printf("Call gpsClose\n");
	gpsClose(client, shm_addr); 
}
