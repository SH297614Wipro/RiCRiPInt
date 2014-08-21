#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "gps/gps_client.h"
#include "gps/gwipc.h"
#include "bfd.h"
#include "gw_gps.h"
#include "gps_func.h"
#include "modelinfo.h"
#include "gps_color_mtype.h"
#include "info.h"
#include "pageprint.h"
#include "memory.h"
#include "gps/pageio.h"

/*
#define	GPS_INTERP_RTIFF		6
#define GPS_PRMINFO_SUCCESS     0
#define GPS_PRMINFO_FAILED      1
#define PM_SUCCESS              0
#define GPS_PRMINFO_GET_COLOR_MODEL 6

#define GPS_PENV_NAME_COMMON "COMMON"
#define GPS_PENV_NAME_PCL "PCL"

#define	PENV_HANDLER 	      5
#define	GPS_PENV_ERR_NOTABLE  (-3)
#define	GPS_PENV_ERR_BUSY	  (-2)

#define	GPS_PENV_VAR_ID_COPIES			1
#define	GPS_PENV_VAR_ID_RESOLUTION		5
#define	GPS_FONT_PCL		            2


#define GPS_INTERP_PCL5c            10  
#define BIT_SW_003                   2  
#define BIT_SW_001					 0
#define BIT_SW_004                   3
#define BIT_SW_016					15   
#define SET_DISP                   3
#define	GPS_HDD_TMP		             4 
#define PHOTO_DRAWMODE               0
#define	HIGH_PRINTMODE		         1	
#define GPS_PAPER_NORMAL        (0x01)      
#define   RESET_DISP           5
#define GPS_INTERP_FIN_NORMAL 0 /* Normal end */
/*#define GPS_PRINT_NORMAL (0) /* Normal printing */


//typedef	unsigned short	gps_color_rid_t;

//static gwmsg_client_t gpsClient;
extern gwmsg_client_t *gps_client;
//static char *shdm_addr;
gps_color_rid_t rID[4];

static gps_bininfo_t gpsBinInfo;
static gps_trayinfo_t gpsTrayInfo;
//static gps_sysinfo_t  sysinfo;
static gps_hddinfo2_t hddinfo;
static gps_paperinfo_t gpsPaperInfo;
static gps_prtstatus2_t prtStatus;
static gps_plotprepareparam_t plotPrepare;
static gps_pageparam_shm_t param;
static gps_pagemode2_t pagemode2;

static gps_pageinfo2_t pageinfo2;
static gps_pagemode_t pagemode;
static gps_pageinfo_t pageinfo;
static gwmsg_GpsPage_FrameCreate_Res_t	pFCR;
static gwmsg_GpsPage_FrameGetBand_Res_t pFGBR;
static gwmsg_GpsPage_FrameFlushBand_Res_t pFFBR;
static int gwmsg_interp_handler(void *cl, gwmsg_t *m)
{
    printf("interp handler\n");
    return 0;
}


int  GPS_Open(gwmsg_client_t *client, gwmsg_handler_t gwmsg_interp_handler, pthread_attr_t attr, void **shdm_addr);
int  GPS_GetPrmInfo(gwmsg_client_t *client, int f_id, int *status, int size, long *maxsize);
char  GPS_PmInit(gwmsg_client_t *client, void(*pfunc1)(), void(*pfunc2)());
int  GPS_GetModelInfo(gwmsg_client_t *client, char dummy, char num,	char	*key, char *category, unsigned char value_len, unsigned char	*value);
int GPS_PenvOpen(gwmsg_client_t *client, char *penv_name, long size);
int	GPS_PenvGetValue( gwmsg_client_t* client, int penv, long gps_var, long *penv_val );
void GPS_PenvClose(gwmsg_client_t *client, int penv);
long GPS_Color_getShrd(gwmsg_client_t *client);
int	GPS_Color_getRID( gwmsg_client_t* client, int modeID, gps_color_rid_t *rID, long *rID_size );
int GPS_Color_getProfile(gwmsg_client_t 	*client, void **addr, long	*num);
int GPS_GetFontInfo(gwmsg_client_t *client, int font, gps_fontinfo_t *fontinfo);
int  GPS_GetBitSw(gwmsg_client_t *, int);
int  GPS_InterpNotifyStart(gwmsg_client_t *, int);
void GPS_InterpNotifyOnline(gwmsg_client_t *);
int  GPS_PenvGetValueList(gwmsg_client_t *, int, long, long, long, long *, long *);
int  GPS_PenvGetDefValue(gwmsg_client_t *, int, long, long *);
int  GPS_BinInfo(gwmsg_client_t *, int , gps_bininfo_t *, long *, int );
int  GPS_TrayInfo(gwmsg_client_t *, int , gps_trayinfo_t *, long *, int); 
void GPS_PmDispSetEmulation(char, char, char, char *);
int GPS_GetSysInfo(gwmsg_client_t *, gps_sysinfo_t *);
caddr_t GPS_WkMalloc(gwmsg_client_t *client, long mallocsize);
int GPS_WkSizeFree(gwmsg_client_t *);
int GPS_ColorgetID2(gwmsg_client_t *, int, int, int, int, unsigned char, unsigned char, int *) ; 
int GPS_gpsGetHddInfo2(gwmsg_client_t *, int, int, gps_hddinfo2_t);

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
*Function Name: GPS_Open()
*Attributes:
*client  IN   Client identifier
*handler IN   GW-IPC handler to process events coming from GPS
*attr    IN   Specifies an attribute of pthread to process GW-IPC events.
*shm_addr OUT   Sheared memory address that is necessary to receive/send data with GPS.
*Description: This function initializes the system to act as the client connected to GPS.
************************************************************************************************************/
int GPS_Open(gwmsg_client_t *client, gwmsg_handler_t gwmsg_handler_t, pthread_attr_t attr, void **shm_addr)
{
    printf("------------------------------------- \n");
	printf("Call gpsOpen\n");
    return gpsOpen(gps_client, gwmsg_interp_handler, &attr, (void *)(&shm_addr));
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
int GPS_GetPrmInfo(gwmsg_client_t *client, int f_id, int *status, int size,	long *maxsize)
{
	printf("------------------------------------- \n");   
   printf("Call gpsGetPrmInfo\n");
    return gpsGetPrmInfo( client, f_id, status, size, maxsize );
    printf("Returned from gpsGetPrmInfo\n");
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
int GPS_GetModelInfo(gwmsg_client_t *client, char  dummy, char num,char	*key, char	*category, 	unsigned char value_len, unsigned char	*value)
{
   printf("------------------------------------- \n");
   printf("Call gpsGetModelInfo \n");
   return gpsGetModelInfo(client, 0, 1, (unsigned char *) key, (unsigned char *)category, value_len, value);
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
long GPS_Color_getShrd(gwmsg_client_t *client)
{
    printf("------------------------------------- \n");
	printf("Calling gpsColor_getShrd\n");
   return gpsColor_getShrd( gps_client );
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
int	GPS_Color_getRID( gwmsg_client_t *client, int modeID, gps_color_rid_t *rID, long *rID_size )
{ 
    printf("------------------------------------- \n");
	printf("Calling gpsColor_getRID\n");
   return gpsColor_getRID(client, 1, rID, rID_size);
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
int GPS_GetFontInfo(gwmsg_client_t *client, int font, gps_fontinfo_t *fontinfo)
{
     printf("------------------------------------- \n");
	 printf("Calling gpsGetFontInfo\n");
	return gpsGetFontInfo(gps_client, font, fontinfo);
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
int GPS_TrayInfo(gwmsg_client_t *client, int num, gps_trayinfo_t *gpsTrayInfo, long *trayNum, int notify)
{
	 printf("------------------------------------- \n");
	 printf("Call Tray Info value\n");
	return gpsGetTrayInfo(client, num, gpsTrayInfo, trayNum, notify);
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
int GPS_BinInfo(gwmsg_client_t *client, int num, gps_bininfo_t *gpsBinInfo, long *binInfo, int notify)
{
	 printf("------------------------------------- \n");
	 printf("Call Bin Info value\n");
	return gpsGetBinInfo(client, num, gpsBinInfo, binInfo, notify);
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
int GPS_GetBitSw(gwmsg_client_t *client, int num)
{
	 printf("------------------------------------- \n");
	 printf("Call GPS_getBitSW\n");
	return gpsGetBitSw(client, num);
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
int GPS_GetSysInfo(gwmsg_client_t	*client, gps_sysinfo_t *sysinfo)
{
     printf("------------------------------------- \n");
	 printf("Call gpsGetSysInfo\n");
   	return gpsGetSysInfo( client, sysinfo );

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
int GPS_ColorgetID2(gwmsg_client_t *client, int hdpi, int vdpi, int bit, int draw, unsigned char prt,unsigned char paper, int *modeID)  
{
	printf("------------------------------------- \n");
	printf("Call gpsColor_getID2\n");
	return gpsColor_getID2(client, hdpi, vdpi, bit, draw, prt, paper, modeID);
}

/***********************************************************************************************************
*Function Name: PS_gpsGetHddInfo2()
*Attributes:
*client   IN   Client identifier
*hdd      IN   Memory type: HDD/RAM/SD
**status  OUT  indicates whether information is obtained.
**hddinfo2 OUT HDD information structure 2
*Description: Obtains information of HDD/RAM/SD.
************************************************************************************************************/
int GPS_gpsGetHddInfo2(gwmsg_client_t* client, int hdd, int status, gps_hddinfo2_t hddinfo2)  
{
	printf("------------------------------------- \n");
	printf("Call gpsGetHddInfo2\n");
	return gpsGetHddInfo2( client, hdd, &status, &hddinfo2 );
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
	/*return 0;/* Call to gpsPlotPrepare(client, uJobid, Param); is commented
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
	//return 0;/* Call to gpsPlotSetPageParamShm(client, PlotSet_plotid, param, PlotSet_result); is commented as there is dependency on _CNF_API_gpsPlotSetPageParamShm */
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
