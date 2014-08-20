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

char * g_pPMSConfigFile = NULL;
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
static gps_bininfo_t *gpsBinInfo;
static gps_hddinfo2_t hddinfo_download;
static gps_pageinfo_t  pageinfo;
static gps_prtinfo_t gpsPrtInfo;
static gps_paperinfo_t gpsPaperInfo;
static sim_prtinfo_t simPrtInfo;
static gps_pageparam_t pageparam;
gps_color_rid_t rID[4];
caddr_t memaddr;
#endif


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
int gwmsg_interp_handler(void *cl, gwmsg_t *m);
int GPS_Color_getShrd_1(void);
int GPS_Color_getID2_1(int hdpi, int vdpi, int bit, int draw, unsigned char prt,unsigned char paper);
int	GPS_Color_getRID_1( int, gps_color_rid_t*, long* );
int GPS_GetModelInfo_1(char  dummy, char num,char	*key, char	*category, 	unsigned char value_len);
int GPS_GetSysInfo_1();
int GPS_TrayInfo_1();
int GPS_BinInfo_1();
int GPS_GetFontInfo_1();
int GPS_gpsGetHddInfo2_1(int hdd, gps_hddinfo2_t hddinfo2);
int GPS_GetBitSw_1(int num);
int GPS_GetPrmInfo_1(int f_id, int *status, int size,	long *maxsize);
void InitGlobals_gps(void);
void GetJobSettings_gps(void);
extern void GWID_Event_Handler(void *cl, gwmsg_t *m);
#endif
/** Array of PMS API function pointers */
static PMS_API_FNS l_apfnRip_IF_KcCalls = NULL;
extern int PMS_RippingComplete();
int g_jobAvailable=0;


/**
 * \brief Entry point for PMS Simulator
 *
 * This routine is the main entry for PMS.\n
 */
int PMS_main()
{
//#ifdef PMS_OIL_MERGE_DISABLE
  void *pPMSOutThread = NULL;
//#endif
  void *pOILThread = NULL;

#ifndef PMS_OIL_MERGE_DISABLE_BU
  Init_gps();
#endif
  
  /* Initialise PMS API Function pointers array */
  l_apfnRip_IF_KcCalls = PMS_InitAPI();

  /* Initialise essential structures, this memory will never be released. */
  /* Initialize Global structures */
  InitGlobals();
  
#ifndef PMS_OIL_MERGE_DISABLE_BU
  GPS_Color_getShrd_1();

  //revisit - why gpsColor_getID2, gpsColor_getID, GPS_Color_getRID_1    - should be in job seq & media handling
  GPS_Color_getID2_1(600, 600, 2, PHOTO_DRAWMODE, HIGH_PRINTMODE, GPS_PAPER_NORMAL);
  int modeID = gpsColor_getID(gps_client, 1200, 1200, 1, PHOTO_DRAWMODE);
//  gps_color_rid_t rID[5];
  long rID_size;
	int gps_notify =0;
//  int gps_paperId = 133; //Needs to be updated with MACRO or....
  int gps_paperId = 130; //Needs to be replaced with MACRO in GetPaperInfo() call...
  GPS_Color_getRID_1( modeID, rID, &rID_size );
  GPS_GetModelInfo_1(0, 1, "color_prm_val", "COLOR", 32);
  GPS_GetSysInfo_1();
	int GPSGetPaperInfoRetVal;
#endif

#ifdef PMS_OIL_MERGE_DISABLE
  /* Initialise file system */
  PMS_FS_InitFS();

  /* Parse command line */
  ParseCommandLine();
#else
  g_tSystemInfo.eOutputType = PMS_TIFF;
  strcpy(g_tSystemInfo.szOutputPath, "../../output");
  g_pPMSConfigFile = "../../output/tray_SEF.cnf";
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
  GPS_TrayInfo_1();
  GPS_BinInfo_1();
  GPS_GetFontInfo_1();
  GPS_GetPaperInfo(gps_client, gps_paperId, &gpsPaperInfo, gps_notify);
#endif


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

  /* Set up default job settings (after ParseCommandLine() so as to honour its settings) */
#ifdef PMS_OIL_MERGE_DISABLE_JS
  EngineGetJobSettings();
#else
  GetJobSettings_gps();
#endif
  
#ifndef PMS_OIL_MERGE_DISABLE_BU

// call env functions

  GPS_gpsGetHddInfo2_1(GPS_HDD_DOWNLOAD, hddinfo_download);
  GPS_GetBitSw_1(BIT_SW_004); //should not be here --- review
  {//just a block to declare a variable
    long maxsize[2];
	int status;
    if(GPS_GetPrmInfo_1(GPS_PRMINFO_GET_COLOR_MODEL, &status, 2, maxsize))
    {
      switch(maxsize[0])
	  {
	    case GPS_CM_BW_MACHINE: //B&W
		  g_tSystemInfo.eDefaultColMode = OIL_Mono;
		  break;
		case GPS_CM_FULL_COLOR_MACHINE: // Color
		  g_tSystemInfo.eDefaultColMode = OIL_CMYK_Separations; // revisit OIL_eColorMode
		  break;
		case GPS_CM_TWIN_COLOR_MACHINE:  //two-color
		  g_tSystemInfo.eDefaultColMode = OIL_Mono; // revisit OIL_eColorMode
		  break;
		default:
		  g_tSystemInfo.eDefaultColMode = OIL_Mono;
		  break;
	  }
    }
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

//#ifdef PMS_OIL_MERGE_DISABLE_JS
    pPMSOutThread = (void*)StartOutputThread();
//#endif
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
#endif
      PMS_Delay(100);
    };

    /* The OIL thread should not take make time to exit, so
       we'll allow it 1 second */
    PMS_CloseThread(pOILThread, 1000);
    pOILThread = NULL;

//#ifdef PMS_OIL_MERGE_DISABLE_JS

    /* The PMS output thread may have to wait for mechanical
       hardware before if finishes, and so we'll allow longer
       for the thread to close cleanly */
    PMS_CloseThread(pPMSOutThread, 5000);
    pPMSOutThread = NULL;
//#endif

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
  g_tSystemInfo.ePaperSelectMode = PMS_PaperSelNone;
#else
  g_tSystemInfo.ePaperSelectMode = OIL_PaperSelNone;
#endif
  g_tSystemInfo.uDefaultResX = 0;    /* set the default resolution in ParseCommandLine() */
  g_tSystemInfo.uDefaultResY = 0;
  g_tSystemInfo.eImageQuality = PMS_1BPP;
  g_tSystemInfo.bOutputBPPMatchesRIP = 1;
  g_tSystemInfo.uOutputBPP = 1;
  g_tSystemInfo.bForceMonoIfCMYblank = TRUE;
#ifdef PMS_OIL_MERGE_DISABLE
  g_tSystemInfo.eDefaultColMode = PMS_CMYK_Separations;
  g_tSystemInfo.eDefaultScreenMode = PMS_Scrn_ORIPDefault;
#else
  g_tSystemInfo.eDefaultColMode = OIL_CMYK_Separations;
  g_tSystemInfo.eDefaultScreenMode = OIL_Scrn_ORIPDefault;
#endif
  g_tSystemInfo.cPagesPrinted = 0;                    /* TODO: make this value persist */
  g_tSystemInfo.uPjlPassword = 0;                     /* TODO: make this value persist */
  g_tSystemInfo.ePersonality = PMS_PERSONALITY_AUTO;  /* TODO: make this value persist */
  g_tSystemInfo.eBandDeliveryType = PMS_PUSH_PAGE;
  g_tSystemInfo.bScanlineInterleave = FALSE;
  g_tSystemInfo.fTrapWidth = 0.0f;
  g_tSystemInfo.uColorManagement = 0;
  g_tSystemInfo.szProbeTraceOption[0] = '\0';
  memset(g_tSystemInfo.szProbeTraceOption,0,sizeof(g_tSystemInfo.szProbeTraceOption));
  g_tSystemInfo.nRestart = 0;
  g_tSystemInfo.nStrideBoundaryBytes = 4;
  g_tSystemInfo.nPrintableMode = 0;
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
            PMS_SHOW_ERROR("Error: -r (%d) - Unsupported color mode request, setting cmyk sep\n", atoi(str));
            g_tSystemInfo.eDefaultColMode = OIL_CMYK_Separations;
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
  pthread_attr_setschedpolicy(&attr, SCHED_RR);
  pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  di_param.sched_priority = sched_get_priority_max(SCHED_RR);
  pthread_attr_setschedparam(&attr, &di_param);
  
  gps_shdm_addr = NULL;
  memaddr = NULL;
  if ( 0 != gpsOpen(gps_client, GWID_Event_Handler, &attr, (void *)(&shdm_addr)) )
  {
    printf("gpsOpen() ERROR \n");
	//exit(0);
  }
  gps_shdm_addr = &shdm_addr;
  
  gpsPmInit(gps_client, 0, 0);
  gpsPmDispSetEmulation(SET_DISP, SET_DISP,SET_DISP, "PCL5e");
  
  if ( gpsWkSizeFree(gps_client) > REQ_MEMORY )
    memaddr = gpsWkMalloc(gps_client, REQ_MEMORY );
  else
  {
    printf("Not enough memory \n");
	//exit(0);
  }
  printf("memaddr = %p \n", (void*)memaddr);
}

int GPS_Color_getShrd_1(void)
{
  long loffset;
  gps_nclr_shdm_t *clr_shm;
  if(loffset = gpsColor_getShrd( gps_client ))
    clr_shm = (gps_nclr_shdm_t*)((long)gps_shdm_addr + loffset);
  else
    return -1;
	
  // To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 292
  
  
  return 0;
}

int GPS_Color_getID2_1(int hdpi, int vdpi, int bit, int draw, unsigned char prt,unsigned char paper)
{
  int modeID ;
  gpsColor_getID2(gps_client, hdpi, vdpi, bit, draw, prt, paper, &modeID);
  return modeID;
}

int	GPS_Color_getRID_1( int modeID, gps_color_rid_t *rID, long *rID_size )
{ 
   return gpsColor_getRID(gps_client, modeID, rID, rID_size);
}

int GPS_GetModelInfo_1(char  dummy, char num,char	*key, char	*category, 	unsigned char value_len)
{
  unsigned char value[65];
  if( SERCH_OK != gpsGetModelInfo(gps_client, dummy, num, (unsigned char *) key, (unsigned char *)category, value_len, value) )
    return -1;
	
   // To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 208 209
   
   return 0;
}

int GPS_GetSysInfo_1()
{
  if( 0 != gpsGetSysInfo(gps_client, &sysinfo) )
    return -1;
	
  strcpy(g_tSystemInfo.szManufacturer, sysinfo.maker);
  strcpy(g_tSystemInfo.szProduct, sysinfo.model);
  g_nInputTrays = sysinfo.num_tray; //Override by EngineGetTrayInfo(), Do reassign in GPS_TrayInfo.
  g_nOutputTrays = sysinfo.num_bin; //Override by EngineGetTrayInfo(), Do reassign in GPS_BinInfo.
  
  // To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 8 to 13
  /*
  num_tray ----- Number of input trays.
  num_bin ------ Number of output bins.
  disp_lines/disp_columns  -------  The number of lines displayed on the screen, and the number of characters per line.
  */
  return 0;
}

int GPS_TrayInfo_1()
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
  // To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 37
  // gpsGetTrayInfo - page no 197

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
	
	
	
    g_pstTrayInfo[nTrayIndex].eMediaColor = PMS_COLOR_DONT_KNOW; // yet to map
    g_pstTrayInfo[nTrayIndex].uMediaWeight = 0; // yet to map
    g_pstTrayInfo[nTrayIndex].nPriority = nTrayIndex; // assumption yet to conform. 
	
	
	
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

int GPS_BinInfo_1()
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
  
  // To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 40
  // gpsGetTrayInfo - page no 200
  
  for(nTrayIndex = 0; nTrayIndex < binInfo; nTrayIndex++)
  {
    //g_pstOutputInfo[nTrayIndex].eOutputTray = gpsBinInfo[nTrayIndex].id;
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
      // yet to map  PMS_OUTPUT_TRAY_UPPER, PMS_OUTPUT_TRAY_LOWER, PMS_OUTPUT_TRAY_EXTRA
	}
    g_pstOutputInfo[nTrayIndex].nPriority = nTrayIndex     ;//assumption yet to conform. 
	
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

int GPS_GetFontInfo_1()
{
  gps_fontinfo_t fontinfo;
  if( -1 == gpsGetFontInfo(gps_client, GPS_FONT_PCL, &fontinfo) )
    return -1;
  
  // To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 141, 70
  return 0;
}

int GPS_PenvGetValue_1( char *penv_name, long gps_varID, long *penv_val )
{
  int penv = gpsPenvOpen(gps_client, penv_name, strlen(penv_name)+1);
  if (penv < 0)
    return -1;

  gpsPenvGetValue(gps_client, penv, gps_varID, penv_val);
  gpsPenvClose(gps_client, penv);

  return 0;
}
/*
int GPS_PenvSetValue( char *penv_name, long gps_varID, long *penv_val )
{
  int penv = gpsPenvOpen(gps_client, penv_name, strlen(penv_name)+1);
  if (penv < 0)
    return -1;

  gpsPenvSetValue(gps_client, penv, gps_varID, penv_val);
  gpsPenvClose(gps_client, penv);

  return 0;
}*/

int GPS_PenvGetDefValue_1( char *penv_name, long gps_varID, long *penv_val )
{
  int penv = gpsPenvOpen(gps_client, penv_name, strlen(penv_name)+1);
  if (penv < 0)
    return -1;

  gpsPenvGetDefValue(gps_client, penv, gps_varID, penv_val);
  gpsPenvClose(gps_client, penv);

  return 0;
}

int GPS_PenvSetDefValue_1( char *penv_name, long gps_varID, long penv_val )
{
  int penv = gpsPenvOpen(gps_client, penv_name, strlen(penv_name)+1);
  if (penv < 0)
    return -1;

  gpsPenvSetDefValue(gps_client, penv, gps_varID, penv_val);
  gpsPenvClose(gps_client, penv);

  return 0;
}


//still more env functions.


int GPS_gpsGetHddInfo2_1(int hdd, gps_hddinfo2_t hddinfo2)  
{
  int status;
  if(gpsGetHddInfo2(gps_client, hdd, &status, &hddinfo2))
    return status;

  return -1;
}

int GPS_GetBitSw_1(int num)
{
  return gpsGetBitSw(gps_client, num);
}

int GPS_GetPrmInfo_1(int f_id, int *status, int size,	long *maxsize)
{
    return gpsGetPrmInfo( gps_client, f_id, status, size, maxsize );
} 

void InitGlobals_gps()
{
  long gps_value;

  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_RESOLUTION, &gps_value))
  {
    g_tSystemInfo.uDefaultResX = gps_value;
	g_tSystemInfo.uDefaultResY = gps_value;
	printf("DefaultResX = %d \n", gps_value);
  }

  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_QUALITYMODE, &gps_value))
  {
    printf("GPS_PENV_VAR_ID_QUALITYMODE = %d \n",gps_value);
	switch(gps_value)
	{
	  case PR_BITBLT_1BPP:  //PR_DEPTH_1BIT ???
	    g_tSystemInfo.eImageQuality = PMS_1BPP;
		g_tSystemInfo.bOutputBPPMatchesRIP = 1;
		g_tSystemInfo.uOutputBPP = 1;
		break;
	  case PR_BITBLT_2BPP: 
	    g_tSystemInfo.eImageQuality = PMS_2BPP;
		g_tSystemInfo.bOutputBPPMatchesRIP = 2;
		g_tSystemInfo.uOutputBPP = 2;
		break;
	  case PR_BITBLT_4BPP: //values need to be conformed
	    g_tSystemInfo.eImageQuality = PMS_4BPP;
		g_tSystemInfo.bOutputBPPMatchesRIP = 4;
		g_tSystemInfo.uOutputBPP = 4;
		break;
	  case PR_BITBLT_8BPP: //values need to be conformed
	    g_tSystemInfo.eImageQuality = PMS_8BPP_CONTONE;
		g_tSystemInfo.bOutputBPPMatchesRIP = 8;
		g_tSystemInfo.uOutputBPP = 8;
		break;
	  default: //values need to be conformed
	    g_tSystemInfo.eImageQuality = PMS_1BPP;
		g_tSystemInfo.bOutputBPPMatchesRIP = 1;
		g_tSystemInfo.uOutputBPP = 1;
		break;
	}
  }

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
  
  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_RESOLUTION, &gps_value))
  {
    g_tJob.uXResolution = gps_value;
	g_tJob.uYResolution = gps_value;
	printf("DefaultResX = %d \n",gps_value);
  }

  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_ORIENTATION, &gps_value))
  {
    g_tJob.uOrientation = gps_value;
	printf("uOrientation = %d \n",gps_value);
  }

  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_MEDIATYPE, &gps_value))
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
  
  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_TRAY, &gps_value))
  {
    //g_tJob.tCurrentJobMedia.uInputTray = gps_value;
	printf("uInputTray = %d \n",gps_value);
  }
  
  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_OUTBIN, &gps_value))
  {
    //g_tJob.tCurrentJobMedia.uOutputTray = gps_value;
	printf("uOutputTray = %d \n",gps_value);
  }
  
  if(0 == GPS_PenvGetDefValue_1(GPS_PENV_NAME_COMMON, GPS_PENV_VAR_ID_BOOKLETBINDING, &gps_value))
  {
    g_tJob.uBookletType = gps_value;
  }
 
}

int gwmsg_interp_handler(void *cl, gwmsg_t *m)
{
    printf("Inside GPS handler function...\n\n");
    return 0;
}

#endif
