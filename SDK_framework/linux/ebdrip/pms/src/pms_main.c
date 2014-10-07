/* Copyright (C) 2007-2014 Global Graphics Software Ltd. All rights reserved.
 *
 * This example is provided on an "as is" basis and without
 * warranty of any kind. Global Graphics Software Ltd. does not
 * warrant or make any representations regarding the use or results
 * of use of this example.
 *
 * $HopeName: GGEpms_gg_example!src:pms_main.c(EBDSDK_P.1) $
 *
 */
/*! \file
 *  \ingroup PMS
 *  \brief PMS support functions.
 */

#include "pms.h"
#include "pms_platform.h"
#include "pms_malloc.h"
#include "oil_entry.h"
#include "pms_page_handler.h"
#include "pms_engine_simulator.h"
#include "pms_interface_oil2pms.h"
#include "pms_input_manager.h"
#include <string.h> /* for strcpy */
#ifdef PMS_OIL_MERGE_DISABLE
#include "pms_filesys.h"
#endif
#include "pms_config.h"
#ifdef PMS_INPUT_IS_FILE
#include "pms_file_in.h"
#endif
#include "pms_thread.h"
#ifdef PMS_SUPPORT_SOCKET
#include "pms_socket.h"
#endif
#include "pms_thread.h"

#include <ctype.h> /* for toupper */

#ifndef PMS_OIL_MERGE_DISABLE_BU
#include <pthread.h>

#include "gps/gps_client.h"
#include "gpssim.h"
#include "gps/gwipc.h"
#include "gw_gps.h"
#include "gps_func.h"
#include "modelinfo.h"
#include "gps_color_mtype.h"
#include "info.h"
#include "pageprint.h"
#include "gps/pageio.h"
#include "gps/device.h"
#include "gps/pager.h"
#include "gps/di_info.h"
#endif

#ifndef	LPUX200
#define LPUX200
#endif

#ifdef PMS_DEBUG
#define DEBUG_STR   "D"
#else
#define DEBUG_STR   "V"
#endif

#ifdef GPROF_BUILD
void moncontrol(int) ; /* This prototype is missing from some glibc versions */
#endif

/*! \brief Current version of PMS.*/
char    *PMSVersion = DEBUG_STR  "4.0r0";
extern char Changeset[];    /* defined in the pms_version.c file that is updated by the build system from Mercurial */

/* Global variables */
int g_argc;
char **g_argv;
int nJobs;
char **aszJobNames;
PMS_TyPageList *g_pstPageList;
int g_nTimeZero;
int g_nPageCount;
PMS_eRIPState g_eRipState;
PMS_eJOBState g_eJobState;
unsigned int g_SocketInPort;
int g_nInputTrays = 0;
PMS_TyTrayInfo * g_pstTrayInfo = NULL;
int g_nOutputTrays = 0;
PMS_TyOutputInfo * g_pstOutputInfo = NULL;
PMS_TySystem g_tSystemInfo;
PMS_TySystem g_tNextSystemInfo;
PMS_HddInfo g_tHddInfo;
int g_bLogPMSDebugMessages;
int g_bTaggedBackChannel;
int g_bBackChannelPageOutput;
int g_bBiDirectionalSocket;
int g_nPMSStdOutMethod;
void *g_semTaggedOutput; /* Semaphore for keeping start/end tag with the actual message */
void *g_semCheckin;      /* Semaphore to for counting page checkins */
void *g_semPageQueue;    /* Semaphore to syncronize between engine printing out page and RIP */
void *g_semTaggedOutput; /* Semaphore for keeping start/end tag with the actual message */
void *g_semPageComplete; /* Semaphore to syncronize submission of band packets from OIL to PMS */
void *g_csPageList;      /* Critical section for thread-safe accessing of g_pstPageList */
void *g_csMemoryUsage;   /* Critical section for thread-safe accessing of nValidBytes in sockets */
void *g_csSocketInput;   /* Critical section for thread-safe accessing of l_tPMSMem */
int g_printPMSLog;

unsigned int g_bDebugMemory;
#ifdef PMS_OIL_MERGE_DISABLE
int l_bEarlyRIPStart = FALSE;  /* TRUE means start RIP before job is opened/received */
#else
int l_bEarlyRIPStart = TRUE;
#endif

const char *g_mps_log = NULL ;
unsigned long g_mps_telemetry = 0x63 ; /* User, Alloc, Pool, Arena */
const char *g_profile_scope = NULL ;

#ifdef PMS_OIL_MERGE_DISABLE
char * g_pPMSConfigFile = NULL;
#endif
#ifdef PMS_HOT_FOLDER_SUPPORT
char * g_pPMSHotFolderPath = NULL;
#endif

#ifndef PMS_OIL_MERGE_DISABLE_BU
#define REQ_MEMORY 12*1024*1024
#define GPS_PENV_NAME_PCL 	"PCL"
#define GPS_PENV_NAME_COMMON "COMMON"
#endif

#ifndef PMS_OIL_MERGE_DISABLE
OIL_TyJob g_tJob; // This may not requried. Revist & check again.
#endif


#ifndef PMS_OIL_MERGE_DISABLE_BU
static gwmsg_client_t gpsClient;
gwmsg_client_t *gps_client = &gpsClient;
static char *shdm_addr;
char *gps_shdm_addr;
gps_sysinfo_t  sysinfo;
gps_trayinfo_t *gpsTrayInfo;
gps_bininfo_t *gpsBinInfo;
gps_hddinfo2_t hddinfo_download;
extern gps_fontinfo_t fontinfo;
static gps_pageinfo_t  pageinfo;
static gps_prtinfo_t gpsPrtInfo;
gps_paperinfo_t gpsPaperInfo;
static sim_prtinfo_t simPrtInfo;
static gps_pageparam_t pageparam;
gps_color_rid_t rID[4];
caddr_t memaddr;
unsigned int szFreeBytes;
char *gps_fontaddr;
extern long loffset;
extern unsigned char outbuf[MAX_VALUE_LEN];
extern gps_nclr_shdm_t *clr_shm;
di_devinfo_GPS_t *devinfo;
#endif
void *pPMSOutThread = NULL, *pOILThread = NULL;
bool g_bJobSucceeded = FALSE;
bool event_Exit_flag;

/* Forward Declarations */
static void InitGlobals(void);
#ifdef PMS_OIL_MERGE_DISABLE
static PMS_TyJob * CreateJob(unsigned int nJobNumber);
#else
static OIL_TyJob * CreateJob(unsigned int nJobNumber);
#endif
static void CleanUp();
#ifdef PMS_OIL_MERGE_DISABLE
static void ParseCommandLine(void);
#endif

#ifndef PMS_OIL_MERGE_DISABLE_BU

void Init_gps(void);
long GPS_Color_getShrd(void);
int GPS_Color_getID2(int hdpi, int vdpi, int bit, int draw, unsigned char prt,unsigned char paper);
int GPS_Color_getRID( int, gps_color_rid_t*, long* );
int GPS_GetModelInfo(char  dummy, char num,char	*key, char	*category, 	unsigned char value_len);
int GPS_GetSysInfo();
int GPS_TrayInfo();
int GPS_BinInfo();
int GPS_GetFontInfo(int);
int GPS_gpsGetHddInfo2(int hdd);
int GPS_GetBitSw(int num);
int GPS_GetPrmInfo(int f_id, int *status, int size,	long *maxsize);
void InitGlobals_gps(void);
void GetJobSettings_gps(void);
extern int GWID_Event_Handler(void *cl, gwmsg_t *m);
extern int Clean_exit();
extern void PrintSysStart_GPS();
void di_getinfo_GPS_update(di_devinfo_GPS_t *, char *);
extern int di_getinfo_GPS(di_devinfo_GPS_t *, char *);
#endif
/** Array of PMS API function pointers */
static PMS_API_FNS l_apfnRip_IF_KcCalls = NULL;
extern int PMS_RippingComplete();
int g_jobAvailable=0;


struct OmPenvStr
{
        int id;
};


struct OmPenvStr OmPenvPclMap[] = {DI_ENV_VAR_ID_FONTSOURCE, DI_ENV_VAR_ID_FONTNUMBER, DI_ENV_VAR_ID_PITCH, DI_ENV_VAR_ID_PTSIZE, DI_ENV_VAR_ID_SYMSET, DI_ENV_VAR_ID_VMI, DI_ENV_VAR_ID_FILTERTEXT};

struct OmPenvStr OmPenvCommonMap[] = 
{
	DI_ENV_VAR_ID_COPIES,
	DI_ENV_VAR_ID_QTY,
	DI_ENV_VAR_ID_PAPER,
	DI_ENV_VAR_ID_ORIENTATION,
	DI_ENV_VAR_ID_RESOLUTIONPCL,
	DI_ENV_VAR_ID_RESOLUTIONTIFF,
	DI_ENV_VAR_ID_RESOLUTIONPCLXL,
	DI_ENV_VAR_ID_RESOLUTIONPS,
	DI_ENV_VAR_ID_RESOLUTIONPDF,
	DI_ENV_VAR_ID_RESOLUTIONXPS,
	DI_ENV_VAR_ID_PERSONALITY,
	DI_ENV_VAR_ID_TRAY,
	DI_ENV_VAR_ID_OUTBIN,
	DI_ENV_VAR_ID_AUTOTRAYCHANGE,
	DI_ENV_VAR_ID_RENDERMODE,
	DI_ENV_VAR_ID_RENDERMODEXPS,
	DI_ENV_VAR_ID_MEDIATYPE,
	DI_ENV_VAR_ID_MANUALFEED,
	DI_ENV_VAR_ID_JOBOFFSET,
	DI_ENV_VAR_ID_AUTOERRSKIP,
	DI_ENV_VAR_ID_BINDING,
	DI_ENV_VAR_ID_BINDINGXPS,
	DI_ENV_VAR_ID_DUPLEX,
	DI_ENV_VAR_ID_DUPLEXXPS,
	DI_ENV_VAR_ID_ECONOMODE,
	DI_ENV_VAR_ID_ECONOMODEXPS,
	DI_ENV_VAR_ID_INTRAY1,
	DI_ENV_VAR_ID_INTRAY2,
	DI_ENV_VAR_ID_INTRAY3,
	DI_ENV_VAR_ID_INTRAY4,
	DI_ENV_VAR_ID_INTRAY5,
	DI_ENV_VAR_ID_INTRAY6,
	DI_ENV_VAR_ID_INTRAY7,
	DI_ENV_VAR_ID_INTRAYLCT,
	DI_ENV_VAR_ID_INTRAYMULTI,
	DI_ENV_VAR_ID_IOSIZE,
	DI_ENV_VAR_ID_JAMRECOVERY,
	DI_ENV_VAR_ID_LANG,
	DI_ENV_VAR_ID_POWERSAVE,
	DI_ENV_VAR_ID_POWERSAVETIME,
	DI_ENV_VAR_ID_SEQUENTIALSTACK,
	DI_ENV_VAR_ID_SMOOTHING,
	DI_ENV_VAR_ID_TIMEOUT,
	DI_ENV_VAR_ID_DENSITY,
	DI_ENV_VAR_ID_STAPLE,
	DI_ENV_VAR_ID_PUNCH,
	DI_ENV_VAR_ID_FRONTCOVERPRINT,
	DI_ENV_VAR_ID_FRONTCOVERPRINTTRAY,
	DI_ENV_VAR_ID_PLANESELECTK,
	DI_ENV_VAR_ID_PLANESELECTC,
	DI_ENV_VAR_ID_PLANESELECTM,
	DI_ENV_VAR_ID_PLANESELECTY,
	DI_ENV_VAR_ID_SLIPSHEETPRINT,
	DI_ENV_VAR_ID_SLIPSHEETPRINTTRAY,
	DI_ENV_VAR_ID_AUTOERRSKIPTIME,
	DI_ENV_VAR_ID_AUTOOUTPUTTIME,
	DI_ENV_VAR_ID_DOCBODYTRAY,
	DI_ENV_VAR_ID_BITSPERDOTPCL,
	DI_ENV_VAR_ID_BITSPERDOTPCLXL,
	DI_ENV_VAR_ID_BITSPERDOTXPS,
	DI_ENV_VAR_ID_MEMORYUSAGE,
	DI_ENV_VAR_ID_ERRORREPORT,
	DI_ENV_VAR_ID_WHITEPAPERSUPPRESS,
	DI_ENV_VAR_ID_WHITEPAPERSUPPRESSXPS,
	DI_ENV_VAR_ID_DATAMODE,
	DI_ENV_VAR_ID_EDGETOEDGE,
	DI_ENV_VAR_ID_EDGETOEDGEXPS,
	DI_ENV_VAR_ID_WIDEA4,
	DI_ENV_VAR_ID_REQPROCREASON,
	DI_ENV_VAR_ID_BACKCOVERPRINT,
	DI_ENV_VAR_ID_COURIER,
	DI_ENV_VAR_ID_BLACKOVERPRINT,
	DI_ENV_VAR_ID_PCLTRAY1PARAM,
	DI_ENV_VAR_ID_PCLTRAY2PARAM,
	DI_ENV_VAR_ID_PCLTRAY3PARAM,
	DI_ENV_VAR_ID_PCLTRAY4PARAM,
	DI_ENV_VAR_ID_PCLTRAY5PARAM,
	DI_ENV_VAR_ID_PCLTRAY6PARAM,
	DI_ENV_VAR_ID_PCLTRAY7PARAM,
	DI_ENV_VAR_ID_PCLLCTPARAM,
	DI_ENV_VAR_ID_PCLBYPASSPARAM,
	DI_ENV_VAR_ID_PCLTRAYALLPARAM,
	DI_ENV_VAR_ID_TRAYSEARCHMODE,
	DI_ENV_VAR_ID_JOBPARAMSTART,
	DI_ENV_VAR_ID_JOBPARAMEND,
	DI_ENV_VAR_ID_EDGETOEDGEPCL,
	DI_ENV_VAR_ID_DUPLEXPCL,
	DI_ENV_VAR_ID_BINDINGPCL,
	DI_ENV_VAR_ID_WHITEPAPERSUPPRESSPCL,
	DI_ENV_VAR_ID_PAPERPCL,
	DI_ENV_VAR_ID_FORMLINES,
	DI_ENV_VAR_ID_FOLD,
	DI_ENV_VAR_ID_AUTOTRAYCHANGE2,
	DI_ENV_VAR_ID_BYPASSTRAYMODESETTING,
	DI_ENV_VAR_ID_TRAY1MODESETTING,
	DI_ENV_VAR_ID_TRAY2MODESETTING,
	DI_ENV_VAR_ID_TRAY3MODESETTING,
	DI_ENV_VAR_ID_TRAY4MODESETTING,
	DI_ENV_VAR_ID_TRAY5MODESETTING,
	DI_ENV_VAR_ID_TRAY6MODESETTING,
	DI_ENV_VAR_ID_TRAY7MODESETTING,
	DI_ENV_VAR_ID_LCTMODESETTING,
	DI_ENV_VAR_ID_DISKIMAGE,
	DI_ENV_VAR_ID_BANNERPAGEPRINT,
	DI_ENV_VAR_ID_BANNERPAGEPRINTTRAY,	
	DI_ENV_VAR_ID_BANNERPAGEPRINTMEDIA,
	DI_ENV_VAR_ID_SAVEMODE,
	DI_ENV_VAR_ID_TABPOSITION
};
	

/**
 * \brief Entry point for PMS Simulator
 *
 * This routine is the main entry for PMS.\n
 */
int PMS_main()
{
/*#ifdef PMS_OIL_MERGE_DISABLE	*/
  void *pPMSOutThread = NULL;
/*#endif	*/
  void *pOILThread = NULL;
  int retval;
  char *dither_gamma_file = NULL;

#ifndef PMS_OIL_MERGE_DISABLE_BU
  Init_gps();
  devinfo = (di_devinfo_GPS_t *)mmalloc(sizeof(di_devinfo_GPS_t));
#endif
  
  /* Initialise PMS API Function pointers array */
  l_apfnRip_IF_KcCalls = PMS_InitAPI();

  /* Initialise essential structures, this memory will never be released. */
  /* Initialize Global structures */
  InitGlobals();
  
#ifndef PMS_OIL_MERGE_DISABLE_BU
  int gps_notify =0;
  int gps_paperId = 133; /*Needs to be replaced with MACRO in GetPaperInfo() call...*/
  long maxsize[2];
  int status;
  int hdd_download_type;
  int font;
  int interp_type;
  char strbuf[MAX_VALUE_LEN];
  int idx;
  int reso_count;
  int modeID;
  int xres = 0, yres= 0, bit= 0 , drawmode=0, prtmode=0, paperkind=0;
  int max_plane;
  int def_plane;
  int i, j;
  long gpsval;
  int photo_limit;
  long prof_num = 0;	/* ƒvƒƒtƒ@ƒCƒ‹” */
  long hr_id[] = {	   DI_ENV_VAR_ID_HEADRANKK,
			   DI_ENV_VAR_ID_HEADRANKC,
			   DI_ENV_VAR_ID_HEADRANKM,
			   DI_ENV_VAR_ID_HEADRANKY,};
  char envtable[] = "COMMON";
  int table_len = sizeof(envtable);

	retval = GPS_PenvOpen(gps_client, envtable, table_len);
	printf("GPS_PenvOpen() returns [%d]\n",retval);	
	
	if( GPS_PenvGetDefValue(gps_client, retval, DI_ENV_VAR_ID_MEMORYUSAGE, &gpsval) == 0)
	{
		retval = GPS_PenvGetValue(gps_client, retval, DI_ENV_VAR_ID_MEMORYUSAGE, &gpsval);
		printf("GPS_PenvGetValue() returns [%d]\n", retval);
		printf("gpsval = [%d]\n", gpsval);
	}
	GPS_PenvClose(gps_client, retval);

  if( (modeID = GPS_Color_getID2(600, 600, 1, PHOTO_DRAWMODE, NONE_PRINTMODE, GPS_PAPER_AUTO)) == GPS_FUNC_NOT_SUPPORT)
  {
	printf("Default GPS_Color_getID2() Failed.\n");
	return -1;
  }
	devinfo->flag |= DI_SUPPORT_EXT_DEVINFO_PARAM; 
  idx = 1;
  while( idx != 0 )
  {
	  sprintf(strbuf, "reso%d", idx);
	  printf("strbuf = [%s]\n",strbuf);
	
	  if (GPS_GetModelInfo(1, 1, strbuf, "DI",sizeof(outbuf)) == 0)
	  { 
		  sscanf(outbuf, "%d,%d,%d,%d,%d,%d", &xres, &yres, &bit, &drawmode, &prtmode, &paperkind);

		  idx++;
		  reso_count = idx;
		  strcpy( outbuf, "" );
	  }
	  else
	  {
		idx = 0;
	  }
  }

  reso_count--;
  printf("reso_count = [%d]\n",reso_count);
    if(retval = GPS_GetPrmInfo(GPS_PRMINFO_GET_COLOR_MODEL, &status, 2, maxsize))
    {
      switch(maxsize[0])
          {
            case GPS_CM_BW_MACHINE: //B&W
                  max_plane = 1;
                  break;
                case GPS_CM_FULL_COLOR_MACHINE: // Color
                  max_plane = 4;
                  break;
                case GPS_CM_TWIN_COLOR_MACHINE:  //two-color
                  max_plane = 2;
                  break;
                default:
		  max_plane = 0;
		  printf("Invalid Printer colour model..\n");
                  break;
          }
    }
    else
    {
        if( (retval != GPS_FUNC_SUPPORT) || (status != GPS_PRMINFO_SUCCESS) )
                return -1;
    }
	  printf("max_plane = [%d]\n",max_plane);


	memset( devinfo, NULL, sizeof(devinfo));
	printf("devinfo->nplane = [%d]\n", devinfo->nplane);
	di_getinfo_GPS_update(devinfo, dither_gamma_file);


//  if( (retval = GPS_GetModelInfo(0, 1, "color_prm_val", "COLOR", 32)) != SERCH_OK ) 
  if( (retval = GPS_GetModelInfo(1, 1, "color_prm_val", "COLOR", 32)) != SERCH_OK ) //dummy value is changed to 1. 
  {
	printf("GPS_GetModelInfo() Failed, returning [%d]\n",retval);
	return retval;
  }  

  if( (retval =  GPS_GetSysInfo())  < 0)
  {
	printf("GPS_GetSysInfo() Failed, returning [%d].\n",retval);
	return -1;
  }

  strcpy(g_tSystemInfo.szManufacturer, sysinfo.maker);
  strcpy(g_tSystemInfo.szProduct, sysinfo.model);
  g_nInputTrays = sysinfo.num_tray; /*Override by EngineGetTrayInfo(), Do reassign in GPS_TrayInfo.*/
  g_nOutputTrays = sysinfo.num_bin; /*Override by EngineGetTrayInfo(), Do reassign in GPS_BinInfo.*/

  printf("g_nInputTrays = [%d]\ng_nOutputTrays = [%d]\n",g_nInputTrays, g_nOutputTrays);
	
  /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 8 to 13*/
  /*
  num_tray ----- Number of input trays.
  num_bin ------ Number of output bins.
  disp_lines/disp_columns  -------  The number of lines displayed on the screen, and the number of characters per line.
  */

  int GPSGetPaperInfoRetVal;
  int statusHDD;
#endif

#ifdef PMS_OIL_MERGE_DISABLE
  /* Initialise file system */
  PMS_FS_InitFS();

  /* Parse command line */
  ParseCommandLine();
#else
  g_tSystemInfo.eOutputType = PMS_TIFF;
  strcpy(g_tSystemInfo.szOutputPath, "../../output");
  nJobs = 1;
  char *JobName = "../../output/test.prn";
  g_tSystemInfo.uUseEngineSimulator = FALSE;
  g_tSystemInfo.uUseRIPAhead = FALSE;
  printf("g_SocketInPort = %d \n", g_SocketInPort);
  g_tSystemInfo.bFileInput = FALSE;
#endif

#ifdef PMS_OIL_MERGE_DISABLE_BU
  /* Initialise input trays */
  g_nInputTrays = EngineGetTrayInfo();

  /* Initialise output trays */
  g_nOutputTrays = EngineGetOutputInfo();

#else
  if(GPS_TrayInfo() < 0 )
  {
	printf("GPS_TrayInfo() Failed.\n");
	return -1;
  } 
  if(GPS_BinInfo() < 0 )
  {
	printf("GPS_BinInfo() Failed.\n");
	return -1;
  }

interp_type = DI_FONT_PCL;

	switch( interp_type ) 
	{
		case DI_INTERP_RPCS:		 /* RPCS */
			font = GPS_FONT_COMMON;
			printf("Font type is GPS_FONT_COMMON..\n");
			break;

		case DI_FONT_RPCS_EXP:		 /* RPCS(EXP) */
			break;

		case DI_FONT_PS:		 /* PS */
			break;

		case DI_FONT_PCL: /* PCL */
		   	  font = GPS_FONT_PCL;
			  if(GPS_GetFontInfo(font) < 0 )
			  {
			        printf("GPS_GetFontInfo() Failed.\n");
			        return -1;
			  }
			break;

		default:
		        printf("GPS_GetFontInfo() has not been invoked for other than PCL..\n");
			return -1;

	}
	printf("fontinfo.addr = [%p]\n",fontinfo.addr);
	printf("fontinfo.size = [%d]\n",fontinfo.size);
	printf("fontinfo.offset = [%d]\n",fontinfo.offset);

	gps_fontaddr = &fontinfo; 
	printf("gps_fontaddr = [%p]\n",gps_fontaddr);

#endif

#ifdef PMS_OIL_MERGE_DISABLE
  /* Read any config file specified on command line */
  if( g_pPMSConfigFile != NULL )
  {
    if( ! ReadConfigFile( g_pPMSConfigFile ) )
    {
      PMS_SHOW_ERROR("\n Failed to read PMS configuration file: %s.\n Exiting.....", g_pPMSConfigFile);
      CleanUp();
      return 0;
    }
  }
#endif

/*PENV Calls for COMMON table..	*/
	retval = GPS_PenvOpen(gps_client, envtable, table_len);
        printf("GPS_PenvOpen() returns [%d]\n",retval);
	
	i = (sizeof(OmPenvCommonMap)) / 4;
	printf("(sizeof(OmPenvCommonMap)) / 4 = [%d]\n", i);

		for( i = 0; i < ((sizeof(OmPenvCommonMap)) / 4); i++)
		{
			if( GPS_PenvGetDefValue(gps_client, retval, OmPenvCommonMap[i].id, &gpsval) == 0)
			{
                printf("GPS_PenvGetDefValue() returns Default Value = [%d]\n", gpsval);
				GPS_PenvGetDefValue(gps_client, retval, OmPenvCommonMap[i].id, &gpsval);
				printf("GPS_PenvGetValue() returns current Value = [%d]\n", gpsval);
			}
		}
        GPS_PenvClose(gps_client, retval);


/*PENV Calls for PCL table..	*/
        printf("PENV Calls for PCL table ..\n");
	memset(envtable, 0, sizeof(envtable));
	strncpy(envtable, "PCL", sizeof("PCL"));
	table_len = sizeof(envtable);

	retval = GPS_PenvOpen(gps_client, envtable, table_len);
        printf("GPS_PenvOpen() returns [%d]\n",retval);
	
	i = (sizeof(OmPenvPclMap)) / 4;
	printf("(sizeof(OmPenvPclMap)) / 4 = [%d]\n", i);

		for( i = 0; i < ((sizeof(OmPenvPclMap)) / 4); i++)
		{
			if( GPS_PenvGetDefValue(gps_client, retval, OmPenvPclMap[i].id, &gpsval) == 0)
			{
		                printf("GPS_PenvGetDefValue() returns Default Value = [%d]\n", gpsval);
				GPS_PenvGetDefValue(gps_client, retval, OmPenvPclMap[i].id, &gpsval);
				printf("GPS_PenvGetValue() returns current Value = [%d]\n", gpsval);
			}
		}
        GPS_PenvClose(gps_client, retval);

 retval = GPS_GetPaperInfo(gps_client, gps_paperId, &gpsPaperInfo, gps_notify);
  if( retval == 0)
	printf("Paper size is not supported by this printer, paperid = [%d]",gps_paperId);
  else
  {
	if(retval == -1)
	{
		printf("GPS_GetPaperInfo() API not supported.\n");
		return -1;
	}
  }
  /* Set up default job settings (after ParseCommandLine() so as to honour its settings) */
#ifdef PMS_OIL_MERGE_DISABLE_JS
  EngineGetJobSettings();
#else
  GetJobSettings_gps();
#endif
  
#ifndef PMS_OIL_MERGE_DISABLE_BU

hdd_download_type = GPS_HDD_DOWNLOAD;
  if( GPS_gpsGetHddInfo2(hdd_download_type)  != 0 )
  {
	return -1;
  }
          g_tHddInfo.stat = hddinfo_download.stat;
          strcpy(g_tHddInfo.path, hddinfo_download.path);
          g_tHddInfo.f_bsize  = hddinfo_download.f_bsize;
          g_tHddInfo.f_blocks = hddinfo_download.f_blocks;
          g_tHddInfo.f_bfree  = hddinfo_download.f_bfree;
          g_tHddInfo.reserve  = hddinfo_download.reserve;

hdd_download_type = GPS_SD_DOWNLOAD; 
  if( (GPS_gpsGetHddInfo2(hdd_download_type))  != 0 )
  {
	return -1;
  } 
          g_tHddInfo.stat = hddinfo_download.stat;
          strcpy(g_tHddInfo.path, hddinfo_download.path);
          g_tHddInfo.f_bsize  = hddinfo_download.f_bsize;
          g_tHddInfo.f_blocks = hddinfo_download.f_blocks;
          g_tHddInfo.f_bfree  = hddinfo_download.f_bfree;
          g_tHddInfo.reserve  = hddinfo_download.reserve;
 
hdd_download_type = GPS_HDD_TMP;
  if( (GPS_gpsGetHddInfo2(hdd_download_type))  != 0 )
  {
	return -1;
  } 
          g_tHddInfo.stat = hddinfo_download.stat;
          strcpy(g_tHddInfo.path, hddinfo_download.path);
          g_tHddInfo.f_bsize  = hddinfo_download.f_bsize;
          g_tHddInfo.f_blocks = hddinfo_download.f_blocks;
          g_tHddInfo.f_bfree  = hddinfo_download.f_bfree;
          g_tHddInfo.reserve  = hddinfo_download.reserve;

/*PENV VAR Calls for COMMON table..	*/
        printf("PENV VAR Calls for COMMON table ..\n");
        memset(envtable, 0, sizeof(envtable));
        strncpy(envtable, "COMMON", sizeof("COMMON"));
        table_len = sizeof(envtable);

        retval = GPS_PenvOpen(gps_client, envtable, table_len);
        printf("GPS_PenvOpen() returns [%d]\n",retval);

	gps_penv_varinfo_t envinfo;
	long retVarInfo, start = 0, end = 0, list = 0, list_num = 0;

/* COPIES_VALUE_LIST_NUM has to be verified since there is NO information about this, and #defined to 2 based on Logs..	*/
#define	COPIES_VALUE_LIST_NUM 2
	int t_list[DI_MAX_TRAY_NUM],  bin_list[DI_MAX_BIN_NUM], copies_list[COPIES_VALUE_LIST_NUM], copies_num;
/*	Env List for DI_ENV_VAR_ID_TRAY;	*/
	long env_id = DI_ENV_VAR_ID_TRAY;

	retVarInfo = gpsPenvGetVarInfo( gps_client, retval, env_id, &envinfo );
	GPS_PenvClose(gps_client, retval);

	if(retVarInfo == 0)
	{
		end = (sizeof(t_list) / sizeof((t_list)[0]));

		retval = GPS_PenvOpen(gps_client, envtable, table_len);
		retval = gpsPenvGetValueList( gps_client, retval, env_id, start, end, &list, &list_num );

	}
	GPS_PenvClose(gps_client, retval);

/*	Env List for DI_ENV_VAR_ID_OUTBIN;	*/
	env_id = DI_ENV_VAR_ID_OUTBIN;
	retval = GPS_PenvOpen(gps_client, envtable, table_len);
        printf("GPS_PenvOpen() returns [%d]\n",retval);
	retVarInfo = gpsPenvGetVarInfo( gps_client, retval, env_id, &envinfo );
        GPS_PenvClose(gps_client, retval);

	if(retVarInfo == 0)
        {

        end = (sizeof(bin_list) / sizeof((bin_list)[0]));

                retval = GPS_PenvOpen(gps_client, envtable, table_len);
                retval = gpsPenvGetValueList( gps_client, retval, env_id, start, end, &list, &list_num );
        }
        GPS_PenvClose(gps_client, retval);

/*	Env List for  DI_ENV_VAR_ID_MEDIATYPE*/
	printf("ENV-VAR list for DI_ENV_VAR_ID_MEDIATYPE has to be implemented in Bootup..\n");
#if 0
	env_id = DI_ENV_VAR_ID_MEDIATYPE;
        retval = GPS_PenvOpen(gps_client, envtable, table_len);
        printf("GPS_PenvOpen() returns [%d]\n",retval);
        retVarInfo = gpsPenvGetVarInfo( gps_client, retval, env_id, &envinfo );
        GPS_PenvClose(gps_client, retval);

        if(retVarInfo == 0)
        {

        int t_list[DI_MAX_TRAY_NUM];
        end = (sizeof(bin_list) / sizeof((bin_list)[0]));

                retval = GPS_PenvOpen(gps_client, envtable, table_len);
                retval = gpsPenvGetValueList( gps_client, retval, env_id, start, end, &list, &list_num );
                printf("start = [%d]\n",start);
                printf("end = [%d]\n",end);
                printf("list = [%d]\n",list);
                printf("list_num = [%d]\n",list_num);

        }
        GPS_PenvClose(gps_client, retval);
#endif	

/*	Env List for  DI_ENV_VAR_ID_COPIES	*/
        env_id = DI_ENV_VAR_ID_COPIES;
        retval = GPS_PenvOpen(gps_client, envtable, table_len);
        printf("GPS_PenvOpen() returns [%d]\n",retval);
        retVarInfo = gpsPenvGetVarInfo( gps_client, retval, env_id, &envinfo );
        GPS_PenvClose(gps_client, retval);

        if(retVarInfo == 0)
        {
		start = 0;
	        end = (sizeof(copies_list) / sizeof((copies_list)[0]));

                retval = GPS_PenvOpen(gps_client, envtable, table_len);
                retval = gpsPenvGetValueList( gps_client, retval, env_id, start, end, &copies_list, &copies_num );

        }
        GPS_PenvClose(gps_client, retval);

/*	Env List for  //DI_ENV_VAR_ID_INTRAYMULTI	*/
        env_id = DI_ENV_VAR_ID_INTRAYMULTI;
        retval = GPS_PenvOpen(gps_client, envtable, table_len);
        printf("GPS_PenvOpen() returns [%d]\n",retval);
        retVarInfo = gpsPenvGetVarInfo( gps_client, retval, env_id, &envinfo );
        GPS_PenvClose(gps_client, retval);

        if(retVarInfo != 0)
        {
		printf("gpsPenvGetVarInfo() failed for DI_ENV_VAR_ID_INTRAYMULTI..\n");
        }
	else
	{
		printf("ENV VAR list implementation has to be done for DI_ENV_VAR_ID_INTRAYMULTI..\n");
	}	
	
        GPS_PenvClose(gps_client, retval);

PrintSysStart_GPS();

    if(retval = GPS_GetPrmInfo(GPS_PRMINFO_GET_COLOR_MODEL, &status, 2, maxsize))
    {
      switch(maxsize[0])
	  {
	    case GPS_CM_BW_MACHINE: /*B&W	*/
		  g_tSystemInfo.eDefaultColMode = OIL_Mono;
		  break;
		case GPS_CM_FULL_COLOR_MACHINE: /* Color	*/
		  g_tSystemInfo.eDefaultColMode = OIL_CMYK_Separations; /* revisit OIL_eColorMode	*/
		  break;
		case GPS_CM_TWIN_COLOR_MACHINE:  /*two-color	*/
		  g_tSystemInfo.eDefaultColMode = OIL_Mono; /* revisit OIL_eColorMode	*/
		  break;
		default:
		  g_tSystemInfo.eDefaultColMode = OIL_Mono;
		  break;
	  }
    }
    else
    {
	if( (retval != GPS_FUNC_SUPPORT) || (status != GPS_PRMINFO_SUCCESS) ) 
		return -1;
    }

  gpsInterpNotifyStart(gps_client, GPS_INTERP_PCL5c);
  gpsInterpNotifyOnline(gps_client);
  
#endif

  if(PMS_IM_Initialize() == 0)
  {
      CleanUp();
      return 0;
  }
  /* Run the RIP by calling OIL interface functions */
  if(strcmp("unknown", Changeset) == 0) 
  {
    PMS_SHOW_ERROR("PMS version: %s\r\n", PMSVersion);
  }
  else
  {
    PMS_SHOW_ERROR("\n PMS Version %s Changeset %s\n",PMSVersion ,Changeset);
  }
  
  /* Loop if last job contained a restart command. */
  do {
    if(g_tSystemInfo.nRestart)
    {
      g_tSystemInfo.nRestart = 0;
      g_tSystemInfo = g_tNextSystemInfo;
    }

    /* Clear the RIP and job states. */
    g_eRipState = PMS_Rip_Inactive;
    g_eJobState = PMS_Job_Inactive;

/*#ifdef PMS_OIL_MERGE_DISABLE_JS	*/
    pPMSOutThread = (void*)StartOutputThread();
/*#endif	*/
    pOILThread = (void*)StartOILThread();

    /* wait for everything to finish.... */
    while(g_eJobState != PMS_AllJobs_Completed)
    {
      /* currently only supoprted under windows/linux */
#ifndef INTR_NO_SUPPORT
      if (PMS_CheckKeyPress())
      {
        if (PMS_GetKeyPress() == '!')
        {
          printf("****** INTERRUPT *******\n");
          OIL_JobCancel();
        }
      }
	  if(event_Exit_flag == TRUE && g_bJobSucceeded == TRUE)// && g_pstCurrentJob == NULL)
	  {
			Clean_exit();
			event_Exit_flag = FALSE;
	  }
#endif
      PMS_Delay(100);
    };

    /* The OIL thread should not take make time to exit, so
       we'll allow it 1 second */
    PMS_CloseThread(pOILThread, 1000);
    pOILThread = NULL;

/*#ifdef PMS_OIL_MERGE_DISABLE_JS	*/

    /* The PMS output thread may have to wait for mechanical
       hardware before if finishes, and so we'll allow longer
       for the thread to close cleanly */
    PMS_CloseThread(pPMSOutThread, 5000);
    pPMSOutThread = NULL;
/*#endif	*/

  } while(g_tSystemInfo.nRestart);

  /* Cleanup and free input modules */
  PMS_IM_Finalize();

#ifdef PMS_OIL_MERGE_DISABLE
  /* Shut down file system */
  PMS_FS_ShutdownFS();
#endif

  CleanUp();

#ifdef PMS_MEM_LIMITED_POOLS
  /* check if memory stat should be displayed */
  if (g_bDebugMemory)
    DisplayMemStats();

  CheckMemLeaks();
#endif

#ifndef PMS_OIL_MERGE_DISABLE
  gpsClose(gps_client, shdm_addr);
#endif

  return 1;
} /*main()*/

/**
 * \brief PMS Global Structures initializing routine
 *
 * This routine intializes the global variables used in PMS.\n
 */
static void InitGlobals(void)
{
  /* Initialise g_nTimeZero = 0 to be used inside PMS_TimeInMilliSecs */
  g_nTimeZero = 0;
  g_nTimeZero = PMS_TimeInMilliSecs();

  g_pstPageList = NULL;
  g_nPageCount = 0;
  g_eRipState = PMS_Rip_Inactive;
  g_eJobState = PMS_Job_Inactive;
  g_tSystemInfo.uUseEngineSimulator = FALSE;
  g_tSystemInfo.uUseRIPAhead = TRUE;
  g_SocketInPort = 9150;                 /* initialise to 0, this means no socket input is enabled */
  g_printPMSLog = 1;
  g_bLogPMSDebugMessages = 0;
  g_bTaggedBackChannel = 0;
  g_bBackChannelPageOutput = 0;
  g_bBiDirectionalSocket = 0;
  g_nPMSStdOutMethod = 1;


  memset(g_tSystemInfo.szOutputPath,0,PMS_MAX_OUTPUTFOLDER_LENGTH);
  g_tSystemInfo.cbRIPMemory = DEFAULT_WORKING_MEMSIZE * 1024 * 1024;
  g_tSystemInfo.nOILconfig = 0;                        /* no custom OIL config */
#ifdef PMS_OIL_MERGE_DISABLE
  g_tSystemInfo.ePaperSelectMode = PMS_PaperSelRIP;
#else
  g_tSystemInfo.ePaperSelectMode = OIL_PaperSelRIP;
#endif
  g_tSystemInfo.uDefaultResX = 0;    /* set the default resolution in ParseCommandLine() */
  g_tSystemInfo.uDefaultResY = 0;
  g_tSystemInfo.eImageQuality = PMS_1BPP;
  g_tSystemInfo.bOutputBPPMatchesRIP = 1;
  g_tSystemInfo.uOutputBPP = 1;
  g_tSystemInfo.bForceMonoIfCMYblank = TRUE;
#ifdef PMS_OIL_MERGE_DISABLE
  g_tSystemInfo.eDefaultColMode = PMS_CMYK_Composite;
  g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_ORIPDefault;
#else
  g_tSystemInfo.eDefaultColMode = OIL_CMYK_Composite;
  g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_ORIPDefault;
#endif
  g_tSystemInfo.cPagesPrinted = 0;                    /* TODO: make this value persist */
  g_tSystemInfo.uPjlPassword = 0;                     /* TODO: make this value persist */
  g_tSystemInfo.ePersonality = PMS_PERSONALITY_AUTO;  /* TODO: make this value persist */
  g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND; //PMS_PUSH_PAGE; -- commented as part of integration
  g_tSystemInfo.bScanlineInterleave = FALSE;
  g_tSystemInfo.fTrapWidth = 0.0f;
  g_tSystemInfo.uColorManagement = 0;
  g_tSystemInfo.szProbeTraceOption[0] = '\0';
  memset(g_tSystemInfo.szProbeTraceOption,0,sizeof(g_tSystemInfo.szProbeTraceOption));
  g_tSystemInfo.nRestart = 0;
  g_tSystemInfo.nStrideBoundaryBytes = 4;
  g_tSystemInfo.nPrintableMode = 1;
  g_tSystemInfo.nStoreJobBeforeRip = FALSE;
  g_tSystemInfo.cbReceiveBuffer = (1 * 1024 * 1024);
  strcpy(g_tSystemInfo.szManufacturer, PMS_PRINTER_MANUFACTURER);
  strcpy(g_tSystemInfo.szProduct, PMS_PRINTER_PRODUCT);
  strcpy(g_tSystemInfo.szPDFSpoolDir, PMS_PDFSPOOL_DIR);
  g_tSystemInfo.bFileInput = FALSE;
#ifdef MULTI_PROCESS
  g_tSystemInfo.nRendererThreads = 1;
#endif
#ifdef PMS_SUPPORT_TIFF_OUT
  g_tSystemInfo.eOutputType = PMS_TIFF; /* Default to TIFF if supported */
#else
  g_tSystemInfo.eOutputType = PMS_NONE;
#endif
  g_tSystemInfo.eOutputType = PMS_NONE;

  /* Initialise all the memory pools to 0, which means unrestricated */
  g_tSystemInfo.cbSysMemory = 0;
  g_tSystemInfo.cbAppMemory = 0;
  g_tSystemInfo.cbJobMemory = 0;
  g_tSystemInfo.cbMiscMemory = 0;
  g_tSystemInfo.cbPMSMemory = 0;
#ifdef SDK_MEMTRACE
  g_bDebugMemory = FALSE;
#endif

  /* Memory usage critical sections must be created before OSMalloc (therefore PMSmalloc) is called */
  g_csMemoryUsage = PMS_CreateCriticalSection();
  g_csPageList = PMS_CreateCriticalSection();
  g_csSocketInput = PMS_CreateCriticalSection();

  /* Create semaphore function uses OSMalloc, therefore must be done after Memory usage critical section is created */
  g_semCheckin = PMS_CreateSemaphore(0);
  g_semPageQueue = PMS_CreateSemaphore(0);
  g_semTaggedOutput = PMS_CreateSemaphore(1);
  g_semPageComplete = PMS_CreateSemaphore(0);
  
  InitGlobals_gps();

}

#ifdef PMS_OIL_MERGE_DISABLE
/**
 * \brief Routine to display the command line options
 *
 * This routine displays the commandline flags available\n
 */
static void DisplayCommandLine(void)
{
          printf("\nPMS version %s\n", PMSVersion);
          printf("OIL version %s\n", OILVersion);
          printf("RIP version %s\n\n", RIPVersion);
          printf("[-o <none");
#ifdef PMS_SUPPORT_TIFF_OUT
          printf("|tiff|tiff_sep");
#ifdef DIRECTVIEWPDFTIFF
          printf("|tiffv");
#endif
#endif
#ifdef PMS_SUPPORT_PDF_OUT
          printf("|pdf");
#ifdef DIRECTVIEWPDFTIFF
          printf("|pdfv");
#endif
#endif
#ifdef DIRECTPRINTPCLOUT
          printf("|print|printx");
#endif
          printf(">]\n");
          printf("[-m <RIP memory in MB>]\n");
#ifdef PMS_MEM_LIMITED_POOLS
          printf("[-msys <SYSTEM memory pool in MB>]\n");
          printf("[-mapp <APPLICATION memory pool in MB>]\n");
          printf("[-mjob <JOB memory pool in MB>]\n");
          printf("[-mmisc <MISCELANEOUS memory pool in MB>]\n");
          printf("[-mpms <PMS memory pool in MB>]\n");
#endif
          printf("[-mbuf <Store job in memory buffer before ripping (size MB)>]\n");
          printf("[-x <horizonal resolution in dpi>]\n");
          printf("[-y <vertical resolution in dpi>]\n");
          printf("[-n <number of renderer threads>]\n");
          printf("[-d <RIP depth in bpp>[,<Output depth in bpp>]]\n");
          printf("[-r <color mode 1=Mono; 3=CMYK Composite; 5=RGB Composite; 6=RGB Pixel Interleaved>]\n");
          printf("[-k <to force mono if cmy absent in cmyk jobs yes|no>]\n");
          printf("[-h <screen mode 0=auto, 1=photo, 2=graphics, 3=text, 4=rip_default(default), 5=job, 6=module>]\n");
          printf("[-j <delivery method 0=push page (default), 1=pull band, 2=push band, 3=direct single, 4=direct frame\n");
          printf("                     5=direct single scanline interleaved 6=direct frame scanline interleaved>]\n");
          printf("[-e <engine simulator on|off|bypass>]\n");
#ifdef PMS_HOT_FOLDER_SUPPORT
          printf("[-i <hot folder input path>]\n");
#endif
          printf("[-f <output path>]\n");
          printf("[-p <media selection mode 0=none(default), 1=rip, 2=pms>]\n");
#ifdef PMS_SUPPORT_SOCKET
          printf("[-s <a number for socket port to listen>]\n");
          printf("[-t n]\n");
          printf("     0 <unidirectional communication>\n");
          printf("     1 <bidirectional communication>\n");
          printf("     2 <bidirectional tagged communication>\n");
#endif
          printf("[-c <PMS configuration file path>]\n");
          printf("[-a <Trap width in points. 0.0 or not specified means no trapping (default is no trapping)>]\n");
          printf("[-v when the only parameter         <for retrieving version and changeset>]\n");
          printf("    when used with other parameters <for turning on PMS log messages on|off>]\n");
          printf("[-l <for turning on logging to file of PMS debug message calls on|off>]\n");
          printf("[-z n]\n");
          printf("     1 <enable scalable consumption features in RIP>\n");
          printf("     2 <for turning on OIL performance data>\n");
          printf("     3 <enable page checksum in OIL>\n");
          printf("     4 <disable genoa compliance settings in OIL>\n");
          /* Image Decimation command line control is disabled until further notice.
          printf("     5 <disable image decimation>\n"); */
          printf("     6 <enable HVD Internal setting in OIL>\n");
          printf("     7 <enable job config feedback in monitor output>\n");
          printf("    10 <for turning on memory usage data>\n");
          printf("    11 <start RIP before opening/receiving job>\n");
          printf("[-b <trace parameter. \'-b help' for options.>]\n");
          printf("[-g <color management method>]\n");
          printf("[-q n]\n");
          printf("     0 <no PMS stdout>\n");
          printf("     1 <PMS stdout (default)>\n");
}
/**
 * \brief Routine to parse the command line
 *
 * This routine parses the commandline (only for configurable options)
 * and intializes the global variables used in PMS.\n
 */
static void ParseCommandLine(void)
{
  int i;
  char *str;
  int nArgc = g_argc;  /* leave global pointers to arguments intact to be used elsewhere */
  char **aszArgv = g_argv;

  if (nArgc < 2)
  {
    DisplayCommandLine();
    PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
    exit(1);
  }

  /* check for command line arguments */
  for ( ++aszArgv ; --nArgc > 0 ; ++aszArgv )
  {
    if (*aszArgv[0] == '-')
    {
      char * pszSwitch = aszArgv[0];
      switch (pszSwitch[1])
      {
        case '?':
          DisplayCommandLine();
          break;

        case 'a':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for default trap width.\n");
            break;
          }

          g_tSystemInfo.fTrapWidth = (float)atof(str);
          break;

        case 'b':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          if(strlen(*aszArgv) + strlen(g_tSystemInfo.szProbeTraceOption) >= (sizeof(g_tSystemInfo.szProbeTraceOption)))
          {
            PMS_SHOW_ERROR("\n Trace parameter string too long. Increase size of string buffer, or consider adding a new probe group.\n Exiting.....");
            exit(1);
          }
          else
          {
            if(strlen(g_tSystemInfo.szProbeTraceOption) > 0)
            {
              strcat(g_tSystemInfo.szProbeTraceOption, " ");
            }
            strcat(g_tSystemInfo.szProbeTraceOption, *aszArgv);
          }
          break;

        case 'c':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          g_pPMSConfigFile = *aszArgv;
          break;

        case 'd':
          {
            char *opt;
            int nRIPbpp;
            int nOutputbpp;

            if (--nArgc < 1 || pszSwitch[2] != 0)
            {
              DisplayCommandLine();
              PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
              exit(1);
            }
            ++aszArgv;

            /* convert to number */
            str = *aszArgv;

            if(str == NULL)
            {
              PMS_SHOW_ERROR("Input a number for default depth.\n");
              break;
            }

            nRIPbpp = atoi(str);
            switch (nRIPbpp)
            {
            case 1:
              g_tSystemInfo.eImageQuality = PMS_1BPP;
              break;
            case 2:
              g_tSystemInfo.eImageQuality = PMS_2BPP;
              break;
            case 4:
              g_tSystemInfo.eImageQuality = PMS_4BPP;
              break;
            case 8:
              g_tSystemInfo.eImageQuality = PMS_8BPP_CONTONE;
              break;
            case 16:
              g_tSystemInfo.eImageQuality = PMS_16BPP_CONTONE;
              break;
            default:
              PMS_SHOW_ERROR("Error: -d (%d) - Unsupported RIP bit depth request, setting 1bpp\n", nRIPbpp);
              g_tSystemInfo.eImageQuality = PMS_1BPP;
              nRIPbpp = 1;
              break;
            }

            /* Default output bit depth matches rendered bit depth */
            g_tSystemInfo.bOutputBPPMatchesRIP = 1;

            opt = strstr(str, ",");
            if(opt)
            {
              nOutputbpp = atoi(opt+1);
              switch(nOutputbpp)
              {
              case 8:
                {
                  switch(nRIPbpp)
                  {
                  case 1:
                    g_tSystemInfo.uOutputBPP = 8;
                    g_tSystemInfo.bOutputBPPMatchesRIP = 0;
                    break;
                  default:
                    PMS_SHOW_ERROR("Error: -d (%d,%d) - Unsupported RIP to output bit depth conversion requested, setting default output depth to %dbpp.\n",
                      nRIPbpp, nOutputbpp, nRIPbpp);
                    break;
                  }
                }
                break;
              default:
                PMS_SHOW_ERROR("Error: -d (%d,%d) - Unsupported RIP to output bit output bit depth conversion requested, setting default output depth to %dbpp.\n",
                  nRIPbpp, nOutputbpp, nRIPbpp);
                break;
              }
            }
            else
            {
              /* Optional Output BPP not supplied. Make Output BPP the same as RIP BPP */
              g_tSystemInfo.uOutputBPP = nRIPbpp;
            }
          }
          break;

        case 'e':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to lowercase */
          str = *aszArgv;
          for( i = 0; str[ i ]; i++)
            str[ i ] = (char)tolower( str[ i ] );

          if(!strcmp("on", *aszArgv))
          {
            g_tSystemInfo.uUseEngineSimulator = TRUE;
            g_tSystemInfo.uUseRIPAhead = TRUE;
          }
          else if(!strcmp("off", *aszArgv))
          {
            g_tSystemInfo.uUseEngineSimulator = FALSE;
            g_tSystemInfo.uUseRIPAhead = TRUE;
          }
          else if(!strcmp("bypass", *aszArgv))
          {
            g_tSystemInfo.uUseEngineSimulator = FALSE;
            g_tSystemInfo.uUseRIPAhead = FALSE;
          }
          else
          {
            PMS_SHOW_ERROR("\n******Engine Simulation option \"%s\" is not supported.\n", *aszArgv);
            PMS_SHOW_ERROR(" Available options : on, off, bypass \n");
            PMS_SHOW_ERROR(" Defaulting to Engine Simulation %s... \n\n", g_tSystemInfo.uUseEngineSimulator==TRUE?"ON":"OFF");
          }
          break;

        case 'f':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          if(strlen(*aszArgv)<PMS_MAX_OUTPUTFOLDER_LENGTH)
          {
            strcpy(g_tSystemInfo.szOutputPath,*aszArgv);
            for(i=0;i<(int)(strlen(g_tSystemInfo.szOutputPath));i++)
            {
              if(g_tSystemInfo.szOutputPath[i] == 92) /* backslash */
                g_tSystemInfo.szOutputPath[i] = 47; /* forwardslash */
            }
            /* Do not send the page data back to the back channel */
            g_bBackChannelPageOutput = 0;
          }
          break;

        case 'g':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for color management method.\n");
            break;
          }

          g_tSystemInfo.uColorManagement = atoi(str);
          break;

        case 'h':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for default screen mode.\n");
            break;
          }

#ifdef PMS_OIL_MERGE_DISABLE
          switch (atoi(str))
          {
          case 0:
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_Auto;
            break;
          case 1:
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_Photo;
            break;
          case 2:
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_Graphics;
            break;
          case 3:
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_Text;
            break;
          case 4:
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_ORIPDefault;
            break;
          case 5:
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_Job;
            break;
          case 6:
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_Module;
            break;
          default:
            PMS_SHOW_ERROR("Error: -h (%d) - Unsupported screen mode request, setting auto \n", atoi(str));
            g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_Auto;
            break;
          }
#else
          switch (atoi(str))
          {
          case 0:
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_Auto;
            break;
          case 1:
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_Photo;
            break;
          case 2:
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_Graphics;
            break;
          case 3:
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_Text;
            break;
          case 4:
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_ORIPDefault;
            break;
          case 5:
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_Job;
            break;
          case 6:
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_Module;
            break;
          default:
            PMS_SHOW_ERROR("Error: -h (%d) - Unsupported screen mode request, setting auto \n", atoi(str));
            g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_Auto;
            break;
          }
#endif
          break;
#ifdef PMS_HOT_FOLDER_SUPPORT
          case 'i':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          g_pPMSHotFolderPath = *aszArgv;
          break;
#endif
        case 'j':
          /* TODO jonw this is a temporary switch, for
             convenience. Not to be documented. */
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            g_tSystemInfo.eBandDeliveryType = PMS_PUSH_PAGE;
            break;
          }
          ++aszArgv;
          str = *aszArgv;

          switch (atoi(str))
          {
          case 1:
            g_tSystemInfo.eBandDeliveryType = PMS_PULL_BAND;
            break;
          case 2:
            g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND;
            break;
          case 3:
            g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND_DIRECT_SINGLE;
            break;
          case 4:
            g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND_DIRECT_FRAME;
            break;
          case 5:
            g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND_DIRECT_SINGLE;
            g_tSystemInfo.bScanlineInterleave = TRUE;
            break;
          case 6:
            g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND_DIRECT_FRAME;
            g_tSystemInfo.bScanlineInterleave = TRUE;
            break;
          default:
          case 0:
            g_tSystemInfo.eBandDeliveryType = PMS_PUSH_PAGE;
            break;
          }

          break; 

        case 'k':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to lowercase */
          str = *aszArgv;
          for( i = 0; str[ i ]; i++)
            str[ i ] = (char)tolower( str[ i ] );

          if(!strcmp("yes", *aszArgv))
          {
            g_tSystemInfo.bForceMonoIfCMYblank = TRUE;
          }
          else if(!strcmp("no", *aszArgv))
          {
            g_tSystemInfo.bForceMonoIfCMYblank = FALSE;
          }
          else
          {
            PMS_SHOW_ERROR("\n******Force mono if CMY absent option \"%s\" is not supported.\n", *aszArgv);
            PMS_SHOW_ERROR(" Available options : yes, no \n");
            PMS_SHOW_ERROR(" Defaulting to Force mono if CMY absent = %s... \n\n", g_tSystemInfo.bForceMonoIfCMYblank==TRUE?"YES":"NO");
          }
          break;

        case 'l':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to lowercase */
          str = *aszArgv;
          for( i = 0; str[ i ]; i++)
            str[ i ] = (char)tolower( str[ i ] );

          if(strcmp(*aszArgv,"on") == 0)
            g_bLogPMSDebugMessages = 1;
          else
            g_bLogPMSDebugMessages = 0;

          break;

        case 'm': /* Output raster handling override. */
          if (--nArgc < 1)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for memory size\n");
            break;
          }

          if(!strcmp(pszSwitch,"-m"))
          {
            g_tSystemInfo.cbRIPMemory = (atoi(str)) * 1024U * 1024U;
            if(g_tSystemInfo.cbRIPMemory < MIN_REQUIRED_RIP_MEM)
            {
              g_tSystemInfo.cbRIPMemory = MIN_REQUIRED_RIP_MEM;
              PMS_SHOW_ERROR("User has input insufficient memory requirement for RIP to run\n");
              PMS_SHOW_ERROR("Overwritting it to %d\n",MIN_REQUIRED_RIP_MEM);
            }
          }
#ifdef PMS_MEM_LIMITED_POOLS
          else if(!strncmp(pszSwitch,"-msys",strlen("-msys")))
            g_tSystemInfo.cbSysMemory = atoi(str)* 1024U * 1024U;
          else if(!strncmp(pszSwitch,"-mapp",strlen("-mapp")))
            g_tSystemInfo.cbAppMemory = atoi(str)* 1024U * 1024U;
          else if(!strncmp(pszSwitch,"-mjob",strlen("-mjob")))
            g_tSystemInfo.cbJobMemory = atoi(str)* 1024U * 1024U;
          else if(!strncmp(pszSwitch,"-mmisc",strlen("-mmisc")))
            g_tSystemInfo.cbMiscMemory = atoi(str)* 1024U * 1024U;
          else if(!strncmp(pszSwitch,"-mpms",strlen("-mpms")))
            g_tSystemInfo.cbPMSMemory = atoi(str)* 1024U * 1024U;
#endif
          else if(!strncmp(pszSwitch,"-mbuf",strlen("-mbuf"))) {
            g_tSystemInfo.cbReceiveBuffer = atoi(str)* 1024U * 1024U;
            g_tSystemInfo.nStoreJobBeforeRip = TRUE;
          }
          else {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
          }
          break;


        case 'n': /* Number of renderer threads */
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for number of renderer threads.\n");
            break;
          }

          g_tSystemInfo.nRendererThreads = atoi(str);
          if( g_tSystemInfo.nRendererThreads < 1 )
          {
            g_tSystemInfo.nRendererThreads = 1;
          }
          break;

        case 'o': /* Output raster handling override. */
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to uppercase */
          str = *aszArgv;
          for( i = 0; str[ i ]; i++)
            str[ i ] = (char)toupper( str[ i ] );

          if(!strcmp("NONE", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_NONE;
          }
#ifdef PMS_SUPPORT_TIFF_OUT
          else if(!strcmp("TIFF", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_TIFF;
          }
          else if(!strcmp("TIFF_SEP", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_TIFF_SEP;
          }
#ifdef DIRECTVIEWPDFTIFF
          else if(!strcmp("TIFFV", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_TIFF_VIEW;
          }
#endif
#endif
#ifdef PMS_SUPPORT_PDF_OUT
          else if(!strcmp("PDF", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_PDF;
          }
#ifdef DIRECTVIEWPDFTIFF
          else if(!strcmp("PDFV", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_PDF_VIEW;
          }
#endif
#endif
#ifdef DIRECTPRINTPCLOUT
          else if(!strcmp("PRINT", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_DIRECT_PRINT;
          }
          else if(!strcmp("PRINTX", *aszArgv))
          {
            g_tSystemInfo.eOutputType = PMS_DIRECT_PRINTXL;
          }
#endif
          else
          {
            PMS_SHOW_ERROR("%s Output Type is not supported.\n", *aszArgv);
#ifdef PMS_SUPPORT_TIFF_OUT
            PMS_SHOW_ERROR(" Defaulting to TIFF... \n");
            g_tSystemInfo.eOutputType = PMS_TIFF;
#else
            PMS_SHOW_ERROR(" Defaulting to no output... \n");
            g_tSystemInfo.eOutputType = PMS_NONE;
#endif
          }
          break;

        case 'p':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for Media selection mode (0=None, 1=RIP, 2=PMS).\n");
            break;
          }

#ifdef PMS_OIL_MERGE_DISABLE
          switch (atoi(str))
          {
          case 0:
            g_tSystemInfo.ePaperSelectMode = PMS_PaperSelNone;
            break;
          case 1:
            g_tSystemInfo.ePaperSelectMode = PMS_PaperSelRIP;
            break;
          case 2:
            g_tSystemInfo.ePaperSelectMode = PMS_PaperSelPMS;
            break;
          default:
            PMS_SHOW_ERROR("Error: -t (%d) - Unsupported media selection mode request, setting default \n", atoi(str));
            break;
          }
#else
          switch (atoi(str))
          {
          case 0:
            g_tSystemInfo.ePaperSelectMode = OIL_PaperSelNone;
            break;
          case 1:
            g_tSystemInfo.ePaperSelectMode = OIL_PaperSelRIP;
            break;
          case 2:
            g_tSystemInfo.ePaperSelectMode = OIL_PaperSelPMS;
            break;
          default:
            PMS_SHOW_ERROR("Error: -t (%d) - Unsupported media selection mode request, setting default \n", atoi(str));
            break;
          }
#endif
          break;

        case 'q':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for PMS stdout method.\n");
            break;
          }

          g_nPMSStdOutMethod = atoi(str);
          break;

        case 'r':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for default color mode \n(1=Mono; 3=CompositeCMYk; 5=CompositeRGB; 6=RGBPixelInterleaved)\n");
            break;
          }

#ifdef PMS_OIL_MERGE_DISABLE
          switch (atoi(str))
          {
          case 1:
            g_tSystemInfo.eDefaultColMode = PMS_Mono;
            break;
          case 2:
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n CMYK Separations not valid in current version.\n Exiting.....");
            exit(1);
/*            g_tSystemInfo.eDefaultColMode = PMS_CMYK_Separations;
            break;
            */
          case 3:
            g_tSystemInfo.eDefaultColMode = PMS_CMYK_Composite;
            break;
          case 4:
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n RGB Separations not valid in current version.\n Exiting.....");
            exit(1);
/*            g_tSystemInfo.eDefaultColMode = PMS_RGB_Separations;
            break;
            */
          case 5:
            g_tSystemInfo.eDefaultColMode = PMS_RGB_Composite;
            break;
          case 6:
            g_tSystemInfo.eDefaultColMode = PMS_RGB_PixelInterleaved;
            break;
          default:
            PMS_SHOW_ERROR("Error: -r (%d) - Unsupported color mode request, setting cmyk comp\n", atoi(str));
            g_tSystemInfo.eDefaultColMode = PMS_CMYK_Composite;
            break;
          }
#else
          switch (atoi(str))
          {
          case 1:
            g_tSystemInfo.eDefaultColMode = OIL_Mono;
            break;
          case 2:
            g_tSystemInfo.eDefaultColMode = OIL_CMYK_Separations;
            break;
          case 3:
            g_tSystemInfo.eDefaultColMode = OIL_CMYK_Composite;
            break;
          case 4:
            g_tSystemInfo.eDefaultColMode = OIL_RGB_Separations;
            break;
          case 5:
            g_tSystemInfo.eDefaultColMode = OIL_RGB_Composite;
            break;
          case 6:
            g_tSystemInfo.eDefaultColMode = OIL_RGB_PixelInterleaved;
            break;
          default:
            PMS_SHOW_ERROR("Error: -r (%d) - Unsupported color mode request, setting cmyk comp\n", atoi(str));
            g_tSystemInfo.eDefaultColMode = OIL_CMYK_Composite;
            break;
          }
#endif
          break;

        case 's':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for socket port to listen on.\n");
            break;
          }

          g_SocketInPort = atoi(str);
          break;

        case 't':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for mode (0=unidirectional, 1=bidirectioanl, 2=bidirectional tagged).\n");
            break;
          }

          switch (atoi(str))
          {
          case 0:
            g_bBiDirectionalSocket = 0;
            g_bBackChannelPageOutput = 0;
            g_bTaggedBackChannel = 0;
            break;
          case 1:
            g_bBiDirectionalSocket = 1;
            g_bBackChannelPageOutput = 0;
            g_bTaggedBackChannel = 0;
            break;
          case 2:
            g_bBiDirectionalSocket = 1;
            g_bBackChannelPageOutput = 1;
            g_bTaggedBackChannel = 1;
            break;
          default:
            PMS_SHOW_ERROR("Error: -t (%d) - Unsupported communication operational mode request, setting default \n", atoi(str));
            break;
          }

          break;

        case 'v':
          if (nArgc == 1)
          {
            PMS_SHOW_ERROR("\n PMS Version %s Changeset %s\n",PMSVersion ,Changeset);
            exit(1);
          }
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }

          ++aszArgv;

          /* convert to lowercase */
          str = *aszArgv;
          for( i = 0; str[ i ]; i++)
            str[ i ] = (char)tolower( str[ i ] );

          if(strcmp(*aszArgv,"on") == 0)
            g_printPMSLog = 1;
          else
            g_printPMSLog = 0;

          break;

        case 'x':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for default horizontal resolution.\n");
            break;
          }

          g_tSystemInfo.uDefaultResX = atoi(str);

          if(g_tSystemInfo.uDefaultResY == 0)
          {
            g_tSystemInfo.uDefaultResY = g_tSystemInfo.uDefaultResX;
          }
          break;

        case 'y':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for default vertical resolution.\n");
            break;
          }

          g_tSystemInfo.uDefaultResY = atoi(str);

          if(g_tSystemInfo.uDefaultResX == 0)
          {
            g_tSystemInfo.uDefaultResX = g_tSystemInfo.uDefaultResY;
          }
          break;

        case 'z':
          if (--nArgc < 1 || pszSwitch[2] != 0)
          {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch.\n Exiting.....");
            exit(1);
          }
          ++aszArgv;

          /* convert to number */
          str = *aszArgv;

          if(str == NULL)
          {
            PMS_SHOW_ERROR("Input a number for OIL configuration mode.\n");
            break;
          }

          /* QA can understand decimal...
             -z 1 to -z 8 are reserved for OIL configurations
             -z 10 and above are used for PMS features
           */
          switch(atoi(str))
          {
          case 1:
            g_tSystemInfo.nOILconfig |= 0x01; /* bitfield - 1 = enable scalable consumption RIP features */
            break;
          case 2:
            g_tSystemInfo.nOILconfig |= 0x02; /* bitfield - 2 = display OIL timing info */
            break;
          case 3:
            g_tSystemInfo.nOILconfig |= 0x04; /* bitfield - 3 = enable checksum */
            break;
          case 4:
            g_tSystemInfo.nOILconfig |= 0x08; /* bitfield - 4 = disable genoa compliance settings */
            break;
          /* Image Decimation command line control is disabled until further notice.
          case 5:
            g_tSystemInfo.nOILconfig |= 0x10; / * bitfield - 5 = disable image decimation settings * /
            break;
          */
          case 6:
            g_tSystemInfo.nOILconfig |= 0x20; /* bitfield - 6 = enable retained raster settings (HVD internal)*/
            break;
          case 7:
            g_tSystemInfo.nOILconfig |= 0x40;  /* bitfield - 7 = enable job config feedback */
            break;
          case 8:
            g_tSystemInfo.nOILconfig |= 0x80; /* bitfield - 8 = enable raster output byte swapping */
            break;
          /* The next controllable oil feature will be -z 9 which will use bit 0x100 in the nOILconfig value
          case 9:
            g_tSystemInfo.nOILconfig |= 0x100; / * bitfield - 8 = enable ... * /
            break;
          */
#ifdef PMS_MEM_LIMITED_POOLS
          case 10:
            g_bDebugMemory = TRUE;
            break;
#endif
          case 11:
            l_bEarlyRIPStart = TRUE;
            break;
          /* The next controllable pms feature will be -z 12
          case 12:
            g_b<NextPMSFeature> = TRUE;
            break;
          */
          default:
            PMS_SHOW_ERROR("-z - invalid option\n");
            break;
          }

          break;

        case 'M':
          if (--nArgc < 1 || pszSwitch[2] != 0 ) {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch\n");
            break;
          }
          if ( g_mps_log != NULL) {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Duplicate -M log argument\n");
          }

          g_mps_log = *++aszArgv;
          break ;

        case 'E': /* MPS telemetry control */
          if (--nArgc < 1 || pszSwitch[2] != 0) {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing arguments or improper switch\n");
            break;
          }
          g_mps_telemetry = strtoul(*++aszArgv, NULL, 0);
          break ;

        case 'T':
#ifdef GPROF_BUILD
          moncontrol(0) ;
#endif /* !GPROF_BUILD */
          if (--nArgc < 1 || pszSwitch[2] != 0 ) {
            DisplayCommandLine();
            PMS_SHOW_ERROR("\n Missing -T profile argument\n");
          }
          g_profile_scope = *++aszArgv ;
          break ;

        default:
            PMS_SHOW_ERROR("ParseCommandLine: unknown option %c\n", pszSwitch[1]);
            DisplayCommandLine();
            exit(1);
            break;
      }
    }
    else
    {
      /* next argument is the jobname so we have to handover the remaining
         arguments to other routines which may want to read the jobnames */
      nJobs = nArgc;
      aszJobNames = aszArgv;
      g_tSystemInfo.bFileInput = TRUE;
      break;
    }
  }

  /* Direct raster delivery methods cannot also change bit depth doing output as there is no copy
     raster stage... the RIP renderers directly into memory supplied by the destination callback. */
  if(g_tSystemInfo.bOutputBPPMatchesRIP == 0) {
    if((g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_SINGLE) ||
       (g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_FRAME)) {
      PMS_SHOW_ERROR("Configuration Error: Bit depth cannot be changed when using 'direct' raster delivery methods.  Changing to 'Push Band' (-j 2).\n");
      g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND;
    }
  }

  /* RGB pixel interleaved direct from RIP require 8 bpp */
#ifdef PMS_OIL_MERGE_DISABLE
  if(g_tSystemInfo.eDefaultColMode == PMS_RGB_PixelInterleaved) {
#else
  if(g_tSystemInfo.eDefaultColMode == OIL_RGB_PixelInterleaved) {
#endif
    if(g_tSystemInfo.eImageQuality != PMS_8BPP_CONTONE) {
      PMS_SHOW_ERROR("Warning: In-RIP RGB Pixel Interleaving requires 8 bits per pixel per colorant.  Changing to 8 bpp (-d 8).\n");
      g_tSystemInfo.eImageQuality = PMS_8BPP_CONTONE;
    }
  }

  /* if x and y are not set expicitly, then set them to default here */
  if(g_tSystemInfo.uDefaultResX == 0)
  {
    g_tSystemInfo.uDefaultResY = g_tSystemInfo.uDefaultResX = 600;
  }

  /* ensure that if socket is not used then no data is returned through socket - ie reset anything set by t flag */
  if ((g_SocketInPort == 0) && (g_bBiDirectionalSocket != 0))
  {
    PMS_SHOW_ERROR("Warning: no socket specified - ignoring 't' flag\n");
    g_bBiDirectionalSocket = 0;
    g_bBackChannelPageOutput = 0;
    g_bTaggedBackChannel = 0;
  }

  /* Push direct methods rely on the gFrameBuffer memory, but only one buffer has been
     allocated, therefore rip ahead cannot work. Rip Ahead can only work if there
     are more than one frame buffer or band buffer - so that the rip can continue
     rendering whilst the pms take its time to print the previous bands/frames.
     Other band delivery methods use the page store in OIL (oil_page_handler.c).
     Consider allocating more buffers if rip ahead is required.
     \todo Remove this section when the generic 'Page Store' module is implemented. */
  if(g_tSystemInfo.uUseRIPAhead == TRUE) {
    if((g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_FRAME)) {
      PMS_SHOW_ERROR("Warning: 'Push Band Direct Frame' does not work with 'Rip Ahead'. Switching to '-e bypass'.\n");
      g_tSystemInfo.uUseEngineSimulator = FALSE;
      g_tSystemInfo.uUseRIPAhead = FALSE;
    }
    if((g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_SINGLE)) {
      PMS_SHOW_ERROR("Warning: 'Push Band Direct Single' does not work with 'Rip Ahead'. Switching to '-e bypass'.\n");
      g_tSystemInfo.uUseEngineSimulator = FALSE;
      g_tSystemInfo.uUseRIPAhead = FALSE;
    }
  }

  if( g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_SINGLE &&
      g_tSystemInfo.nRendererThreads > 1 ) {
    PMS_SHOW_ERROR("Warning: 'Push Band Direct Single' does not work with more than 1 thread. Switching to 'Push Band'.\n");
    g_tSystemInfo.eBandDeliveryType = PMS_PUSH_BAND;
  }
}
#endif


/**
 * \brief Starts the RIP
 *
 * This routine calls OIL interface functions to start the RIP and pass it PMS callback function pointers.\n
 */
void StartOIL()
{
#ifdef PMS_OIL_MERGE_DISABLE
  PMS_TyJob * pstJob;
#else
  OIL_TyJob * pstJob;
#endif
  static unsigned int  nJobNumber = 1;
  int bJobSubmitted;
  int bJobSucceeded;

  g_eRipState = PMS_Rip_Initializing;

  /* Check that the PMS API function pointers have been initialised */
  PMS_ASSERT(l_apfnRip_IF_KcCalls, ("StartOIL: PMS API function array point not initialised.\n"));

  /* initialise the PDL */
  if(!OIL_Init((void(***)())l_apfnRip_IF_KcCalls))
  {
    PMS_RippingComplete();
    return ;
  }

  if(l_bEarlyRIPStart) {
    /* Used to start the RIP before a job is received.
       The default behaviour is to start the RIP when the first job is opened.
       The RIP is only shutdown if the shutdown mode is "OIL_RIPShutdownTotal".
       If start RIP isn't called now, it will be called at some point during OIL_Start function. */
    OIL_StartRIP();
  }

  while(PMS_IM_WaitForInput())
  {
    /* there is some data to process */
    pstJob = CreateJob(nJobNumber);

    if( pstJob!=NULL )
    {
      g_eRipState = PMS_Rip_In_Progress;

#ifdef PMS_INPUT_IS_FILE
      strcpy(pstJob->szJobName, szJobFilename);
      if(pstJob->bFileInput)
        strcpy(pstJob->szJobFilename,szJobFilename);
      else
        pstJob->szJobFilename[0] = '\0';
#endif

      do
      {
        /* start interpreter */
        bJobSucceeded = OIL_Start(pstJob, &bJobSubmitted);

        if( bJobSubmitted )
        {
          nJobNumber++;
          pstJob->uJobId = nJobNumber;
        }

      } while( bJobSucceeded );

      PMS_IM_CloseActiveDataStream();
	  if(event_Exit_flag == TRUE)
	  	{
			g_bJobSucceeded = OIL_JobDone();
	  	}

      /* job finished, free resource */
#ifdef PMS_OIL_MERGE_DISABLE_MEM
      OSFree(pstJob,PMS_MemoryPoolPMS);
#else
      mfree(pstJob);
#endif
    }
    /* If restart is requested, then get out of this loop */
    if(g_tSystemInfo.nRestart) {
      break;
    }
  }

  /* tidy up at the end */
  FreePMSFramebuffer();
  OIL_Exit();
}

/**
 * \brief Clean-Up Routine
 *
 * Routine to release the resources after job completion.\n
 */
static void CleanUp()
{
  if( g_pstTrayInfo != NULL )
  {
#ifdef PMS_OIL_MERGE_DISABLE_MEM
    OSFree( g_pstTrayInfo, PMS_MemoryPoolPMS );
#else
    mfree( g_pstTrayInfo);
#endif
    g_pstTrayInfo = NULL;
    g_nInputTrays = 0;
  }
  if( g_pstOutputInfo != NULL )
  {
#ifdef PMS_OIL_MERGE_DISABLE_MEM
    OSFree( g_pstOutputInfo, PMS_MemoryPoolPMS );
#else
    mfree( g_pstOutputInfo);
#endif
    g_pstOutputInfo = NULL;
    g_nOutputTrays = 0;
  }

  PMS_DestroySemaphore(g_semCheckin);
  PMS_DestroySemaphore(g_semPageQueue);
  PMS_DestroySemaphore(g_semTaggedOutput);
  PMS_DestroySemaphore(g_semPageComplete);

  PMS_DestroyCriticalSection(g_csPageList);
  PMS_DestroyCriticalSection(g_csSocketInput);
  PMS_DestroyCriticalSection(g_csMemoryUsage);
}

/**
 * \brief Job intializing routine
 *
 * Routine to initialize the job structure which is then passed on to the RIP.\n
 */
#ifdef PMS_OIL_MERGE_DISABLE
static PMS_TyJob * CreateJob(unsigned int nJobNumber)
{
#ifdef PMS_OIL_MERGE_DISABLE_MEM
  PMS_TyJob * pstJob = (PMS_TyJob *)OSMalloc(sizeof(PMS_TyJob),PMS_MemoryPoolPMS);
#else
  PMS_TyJob * pstJob = (PMS_TyJob *)mmalloc(sizeof(PMS_TyJob));
#endif
  if( pstJob != NULL )
  {
    memcpy( pstJob, &g_tJob, sizeof(PMS_TyJob) );
#else
static OIL_TyJob * CreateJob(unsigned int nJobNumber)
{
#ifdef PMS_OIL_MERGE_DISABLE_MEM
  OIL_TyJob * pstJob = (OIL_TyJob *)OSMalloc(sizeof(OIL_TyJob),PMS_MemoryPoolPMS);
#else
  OIL_TyJob * pstJob = (OIL_TyJob *)mmalloc(sizeof(OIL_TyJob));
#endif
  if( pstJob != NULL )
  {
    memcpy( pstJob, &g_tJob, sizeof(OIL_TyJob) );
#endif

    pstJob->uJobId = nJobNumber;              /* Job ID number */
#ifdef PMS_INPUT_IS_FILE
    pstJob->szJobName[0] = '\0';              /* Job name */
#else
    strcpy(pstJob->szJobName, "Streamed");    /* Job name */
#endif
  }

  return pstJob;
}


#ifndef PMS_OIL_MERGE_DISABLE_BU
void Init_gps(void) 
{
  pthread_attr_t attr;
  struct sched_param di_param;

  pthread_attr_init(&attr);

#ifdef LPUX200
  pthread_attr_setschedpolicy(&attr, SCHED_RR);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  di_param.sched_priority = sched_get_priority_max(SCHED_RR);
#endif

#ifdef LPUX600 
  pthread_attr_setschedpolicy(&attr, SCHED_NORMAL);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  di_param.sched_priority = sched_get_priority_max(SCHED_NORMAL);
#endif

  pthread_attr_setschedparam(&attr, &di_param);

  int ret;
  gps_shdm_addr = NULL;
  memaddr = NULL;
  szFreeBytes = 0;
  unsigned char interp_name[16] = "";

  if ( 0 != (ret = gpsOpen(gps_client, GWID_Event_Handler, &attr, (void *)(&shdm_addr))) )
  {
    printf("gpsOpen() ERROR, returning [%d].\n",ret);
	exit(0); /*error handling for gpsOpen() API.	*/
  }
  gps_shdm_addr = shdm_addr;
  

  if(gpsPmInit(gps_client, 0, 0) != PM_SUCCESS)
		return -1; /*error handling for gpsPmInit() API.	*/

  strcpy(interp_name , "PCL5c" );/*Can be updated with different PDL interp name for another PDL based on another condition.	*/
  gpsPmDispSetEmulation(SET_DISP, SET_DISP,SET_DISP, interp_name);

  szFreeBytes = gpsWkSizeFree(gps_client);
  if( szFreeBytes > 0 )
  {
  	memaddr = gpsWkMalloc(gps_client, szFreeBytes );

	if ( memaddr == NULL)
	{
		printf("GPS could'nt allocate memory, exiting..\n");
		exit(0);
	}
  }
  else
  {
        printf("Not enough memory \n");
	exit(0); /*Error handling for gpsWkSizeFree() API.	*/

  }
  printf("memaddr = %p \n", (void*)memaddr);
}

void InitGlobals_gps()
{
  long gps_value;
  int retval;

        retval = GPS_PenvOpen(gps_client, GPS_PENV_NAME_COMMON, sizeof(GPS_PENV_NAME_COMMON));
        printf("GPS_PenvOpen() returns [%d]\n",retval);

        if( GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_RESOLUTION, &gps_value) == 0)
		{
			g_tSystemInfo.uDefaultResX = gps_value;
			g_tSystemInfo.uDefaultResY = gps_value;
			printf("DefaultResX = %d \n", gps_value);
			printf("DefaultResY = %d \n", gps_value);
		}
	else
		printf("GPS_PenvGetDefValue() failed.\n");


	if( GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_QUALITYMODE, &gps_value) == 0)
	{
		printf("GPS_PENV_VAR_ID_QUALITYMODE = %d \n",gps_value);
		switch(gps_value)
		{
		  case PR_BITBLT_1BPP:  /*PR_DEPTH_1BIT ???	*/
		    g_tSystemInfo.eImageQuality = PMS_1BPP;
			g_tSystemInfo.bOutputBPPMatchesRIP = 1;
			g_tSystemInfo.uOutputBPP = 1;
			break;
		  case PR_BITBLT_2BPP: 
		    g_tSystemInfo.eImageQuality = PMS_2BPP;
			g_tSystemInfo.bOutputBPPMatchesRIP = 2;
			g_tSystemInfo.uOutputBPP = 2;
			break;
		  case PR_BITBLT_4BPP: /*values need to be conformed	*/
		    g_tSystemInfo.eImageQuality = PMS_4BPP;
			g_tSystemInfo.bOutputBPPMatchesRIP = 4;
			g_tSystemInfo.uOutputBPP = 4;
			break;
		  case PR_BITBLT_8BPP: /*values need to be conformed	*/
		    g_tSystemInfo.eImageQuality = PMS_8BPP_CONTONE;
			g_tSystemInfo.bOutputBPPMatchesRIP = 8;
			g_tSystemInfo.uOutputBPP = 8;
			break;
		  default: /*values need to be conformed	*/
		    g_tSystemInfo.eImageQuality = PMS_1BPP;
			g_tSystemInfo.bOutputBPPMatchesRIP = 1;
			g_tSystemInfo.uOutputBPP = 1;
			break;
		}
	}
	else
		printf("GPS_PenvGetDefValue() failed.\n");

/* g_tJob.bForceMonoIfCMYblank has been updated as g_tJob.bForceMonoIfCMYblank = g_tSystemInfo.bForceMonoIfCMYblank;*/
/*g_tSystemInfo.eDefaultColMode is updated in GPS_GetPrmInfo(). 	*/

/*Updating g_tSystemInfo.eDefaultScreenMode from GPS .	*/
g_tSystemInfo.eDefaultScreenMode = OBJECT_TYPE_LINE;

/*g_tSystemInfo.uPjlPassword has not been updated..	*/
/* unsigned char pdfpassword[PCND_PDFPASSWORD_LEN]; in struct PDF_PrintCondition in GPS.	*/

/* For g_tSystemInfo.uColorManagement , below macros are found in GPS.	*/

/*g_tSystemInfo.szProbeTraceOption[0] = '\0'; is not updated from GPS.	*/
/* static bool		probe_started = FALSE; is present in GPS>			*/

/*g_tSystemInfo.szManufacturer , g_tSystemInfo.szProduct is updated after GPS_GetSysInfo() Call.	*/

	if( GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_OUTPUT, &gps_value) == 0)
	{
/*		g_tSystemInfo.eOutputType = gps_value;	*/
        printf("FOR g_tSystemInfo.eOutputType, gps_value <GPS_PENV_VAR_ID_OUTPUT>  = [%d]\n", gps_value);
/*	    based on the gps_value, we need to use switch statement to map.	*/
	}
	else
		printf("GPS_PenvGetDefValue() failed.\n");
	
        GPS_PenvClose(gps_client, retval);
}

void GetJobSettings_gps()
{

//******Initilize with Default values******later replace values from gps**********

  PMS_TyPaperInfo * pPaperInfo = NULL;

  g_tJob.uJobId = 0;                        /* Job ID number */
  strcpy(g_tJob.szHostName, "Immortal");    /* Printer hostname */
  strcpy(g_tJob.szUserName, "Scott");       /* Job user name */
  g_tJob.szJobName[0] = '\0';               /* Job name */
  g_tJob.szPjlJobName[0] = '\0';            /* PJL Job name */
  g_tJob.uCopyCount = 1;                    /* Total copies to print */
  g_tJob.uXResolution = g_tSystemInfo.uDefaultResX; /* x resolution */
  g_tJob.uYResolution = g_tSystemInfo.uDefaultResY; /* y resolution */
  g_tJob.uOrientation = 0;                  /* orientation, 0-portrait or 1-landscape */
  
  g_tJob.tCurrentJobMedia.ePaperSize = PMS_SIZE_A4;	/* A4*/
  g_tJob.tCurrentJobMedia.uInputTray = PMS_TRAY_AUTO; 		   /* media source selection */
  g_tJob.tCurrentJobMedia.uOutputTray = PMS_OUTPUT_TRAY_AUTO;   /* selected output tray */
  strcpy((char*)g_tJob.tCurrentJobMedia.szMediaType, "");
  strcpy((char*)g_tJob.tCurrentJobMedia.szMediaColor, "");
  g_tJob.tCurrentJobMedia.uMediaWeight = 0;
  PMS_GetPaperInfo(g_tJob.tCurrentJobMedia.ePaperSize, &pPaperInfo);
  g_tJob.tCurrentJobMedia.dWidth = pPaperInfo->dWidth;
  g_tJob.tCurrentJobMedia.dHeight = pPaperInfo->dHeight;

  g_tJob.bAutoA4Letter = FALSE;   /* Automatic A4/letter switching */
  /* get CUSTOM_PAPER size to initialise job structure (set from PJL) */
  PMS_GetPaperInfo(PMS_SIZE_CUSTOM, &pPaperInfo);
  g_tJob.dUserPaperWidth = pPaperInfo->dWidth;   /* User defined paper width */
  g_tJob.dUserPaperHeight = pPaperInfo->dHeight ;  /* User defined paper height */
  g_tJob.bManualFeed = FALSE;     /* Manual feed */
  g_tJob.uPunchType = 1;          /* Punch type, single double etc */
  g_tJob.uStapleType = 1;         /* staple operation, 1 hole, 2 hole, centre etc */
  g_tJob.bDuplex = FALSE;         /* true = duplex, false = simplex */
  g_tJob.bTumble = FALSE;         /* true = tumble, false = no tumble */
  g_tJob.bCollate = FALSE;        /* true = collate, false = no collate */
  g_tJob.bReversePageOrder = FALSE;   /* Reverse page order */
  g_tJob.uBookletType = 1;        /* booklet binding, left, right */
  g_tJob.uOhpMode = 1;            /* OHP interleaving mode */
  g_tJob.uOhpType = 1;            /* OHP interleaving media type */
  g_tJob.uOhpInTray = 1;          /* OHP interleaving feed tray */
  g_tJob.uCollatedCount = 1;      /* Total collated copies in a job */

  switch( g_tSystemInfo.eImageQuality )
  {
  case PMS_1BPP:
    g_tJob.uRIPDepth = 1;
    break;
  case PMS_2BPP:
    g_tJob.uRIPDepth = 2;
    break;
  case PMS_4BPP:
    g_tJob.uRIPDepth = 4;
    break;
  case PMS_8BPP_CONTONE:
    g_tJob.uRIPDepth = 8;
    break;
  case PMS_16BPP_CONTONE:
    g_tJob.uRIPDepth = 16;
    break;
  default:
    HQFAIL("Invalid image quality");
    break;
  }
  g_tJob.bOutputDepthMatchesRIP = g_tSystemInfo.bOutputBPPMatchesRIP; /* Output bit depth. */
  g_tJob.dVMI = 8.0;

  g_tJob.uOutputBPP = g_tSystemInfo.uOutputBPP;         /* Output bit depth. */
  g_tJob.eColorMode = g_tSystemInfo.eDefaultColMode;    /* 1=Mono; 2=SeparationsCMYK; 3=CompositeCMYK; 4=SeparationsRGB; 5=CompositeRGB; */
  g_tJob.bForceMonoIfCMYblank = g_tSystemInfo.bForceMonoIfCMYblank; /* true = force mono if cmy absent, false = output all 4 planes */
  g_tJob.eScreenMode = g_tSystemInfo.eDefaultScreenMode;/* Screening type */
  g_tJob.bSuppressBlank = TRUE;  /* true = suppress blank pages, false = let blank pages pass through */
  g_tJob.bPureBlackText = FALSE;  /* true = Pure Black Text enabled */
  g_tJob.bAllTextBlack = FALSE;   /* true = All Text Black Enabled */
  g_tJob.bBlackSubstitute = FALSE; /* true = Black Substitute enabled */

  g_tJob.uFontNumber = 0;
  strcpy(g_tJob.szFontSource, "I");
  g_tJob.uLineTermination = 0;
  g_tJob.dPitch = 10.0;
  g_tJob.dPointSize = 12.0;
  g_tJob.uSymbolSet = 277;        /* 8U - Roman-8 */

  g_tJob.eRenderMode = PMS_RenderMode_Color;
  g_tJob.eRenderModel = PMS_RenderModel_CMYK8B;
  g_tJob.uJobOffset = 0;
  g_tJob.bCourierDark = FALSE;
  g_tJob.bWideA4 = FALSE;
  g_tJob.bInputIsImage = FALSE; 
  g_tJob.szImageFile[0] = '\0';   /* Image File */

  g_tJob.eTestPage = OIL_TESTPAGE_NONE;   /* Test Page */

  g_tJob.uPrintErrorPage = 0;   /* Print Error Page is off */
  g_tJob.bFileInput = g_tSystemInfo.bFileInput; /* true = job input from file */
  g_tJob.szJobFilename[0] = '\0';   
  strcpy(g_tJob.szPDFPassword, "thassos");
  g_tNextSystemInfo=g_tSystemInfo;


//******************end********************************
  long gps_value;
	int retval; 
        retval = GPS_PenvOpen(gps_client, GPS_PENV_NAME_COMMON, sizeof(GPS_PENV_NAME_COMMON));
        printf("GPS_PenvOpen() returns [%d]\n",retval);

        if( GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_RESOLUTION, &gps_value) == 0)
		{
			g_tJob.uXResolution = gps_value;
			g_tJob.uYResolution = gps_value;
		}
	else
		printf("GPS_PenvGetDefValue() failed.\n");

   
   if( GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_ORIENTATION, &gps_value) == 0)
                {
    			g_tJob.uOrientation = gps_value;
			printf("uOrientation = %d \n",gps_value);
                }
        else
                printf("GPS_PenvGetDefValue() failed.\n");

  if(GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_MEDIATYPE, &gps_value) == 0)
  {
	printf("MediaType = %d \n",gps_value);
    switch(gps_value)
    {
      case DI_PAPER_NORMAL:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Plain" );
      break;
      case DI_PAPER_BOND:
       strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Bond" );
      break;
      case DI_PAPER_SPECIAL:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Special" );
      break;
      case DI_PAPER_GLOSSY:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Glossy" );
      break;
      case DI_PAPER_OHP:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Transparency" );
      break;
      case DI_PAPER_RECYCLE:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Recycled" );
      break;
      case DI_PAPER_ENVELOPE:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Envelope" );
      break;
      case DI_PAPER_POSTCARD:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Postcard" );
      break;
      case DI_PAPER_THIN:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Thin" );
      break;
      case DI_PAPER_LABEL:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Label" );
      break;
      case DI_PAPER_PREPRINT:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Preprinted" );
      break;
      case DI_PAPER_LETTER_HEAD:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Letterhead" );
      break;
      default:
        strcpy( (char *)g_tJob.tCurrentJobMedia.szMediaType, "Plain" );
      break;
    }
  }
	else
		printf("GPS_PenvGetDefValue() failed.\n");
  
if(GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_TRAY, &gps_value) == 0)
  {
    /*g_tJob.tCurrentJobMedia.uInputTray = gps_value;	*/
	printf("uInputTray = %d \n",gps_value);
  }
  
if(GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_OUTBIN, &gps_value) == 0)
  {
    /*g_tJob.tCurrentJobMedia.uOutputTray = gps_value;	*/
	printf("uOutputTray = %d \n",gps_value);
  }
  
if(GPS_PenvGetDefValue(gps_client, retval, GPS_PENV_VAR_ID_BOOKLETBINDING, &gps_value) == 0)
  {
    g_tJob.uBookletType = gps_value;
  }

        GPS_PenvClose(gps_client, retval);
 
}
#endif
