/* Copyright (C) 2005-2013 Global Graphics Software Ltd. All rights reserved.
 *
 * This example is provided on an "as is" basis and without
 * warranty of any kind. Global Graphics Software Ltd. does not
 * warrant or make any representations regarding the use or results
 * of use of this example.
 *
 * $HopeName: SWebd_OIL_example_gg!src:gwid_eventhandle.c(EBDSDK_P.1) $
 *
 */
/*! \file
 *  \ingroup OIL
 *  \brief Implementation of the event handling functions.
 *
 * This file contains the definitions of the functions which does event handling 
 * for registered events that occurs in GPS.
 *
 */

/**
 * \brief  this function is a common Event handler for all GPS events
 *
 * GPS events
 */
#include "gps/di_info.h"
#include <dirent.h>
#include "gwid_eventhandle.h"
#include "pms_export.h"
#include "oil.h"
#include "gps/device.h"
#include "gps/penv_var.h"
#include "gps/modelinfo.h"
#include "gps_func.h"
#include "pthread.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

  extern char *gps_shdm_addr;
  extern caddr_t memaddr;
  extern bool g_bJobSucceeded;
  extern bool event_Exit_flag;
  extern unsigned char buffer1[20],buffer2[20],buffer3[20],buffer4[20],buffer5[20];
  extern int event_Pause_flag;
  extern int event_Exit_Paper_flag;
  /*static int			  reqint;*/
  extern bool event_Cancel_flag;
  static pthread_mutex_t  reqp_mutex;
  static pthread_cond_t   reqp_online_cond;

  extern void * pPMSOutThread;
  extern void * pOILThread;

  extern int g_nInputTrays;
  extern PMS_TyTrayInfo * g_pstTrayInfo;
  extern int g_nOutputTrays;
  extern PMS_TyOutputInfo * g_pstOutputInfo;
  extern int GPS_Tray_notify_flag;
  extern int GPS_Bin_notify_flag;
  int Binding_Enable;
  extern void *g_semTaggedOutput; /* Semaphore for keeping start/end tag with the actual message */
  extern  void *g_semCheckin;	   /* Semaphore to for counting page checkins */
  extern  void *g_semPageQueue;    /* Semaphore to syncronize between engine printing out page and RIP */
  extern  void *g_semTaggedOutput; /* Semaphore for keeping start/end tag with the actual message */
  extern  void *g_semPageComplete; /* Semaphore to syncronize submission of band packets from OIL to PMS */
  extern  void *g_csPageList;	   /* Critical section for thread-safe accessing of g_pstPageList */
  extern  void *g_csMemoryUsage;   /* Critical section for thread-safe accessing of nValidBytes in sockets */
  extern  void *g_csSocketInput;   /* Critical section for thread-safe accessing of l_tPMSMem */
 gps_pageparam_shm_t param;  
long bits_pcl, autotray, bypass_tray, frontcover, frontcover_tray, traysearch, req_proc, edge;
  static bool	first_job_req_proc = TRUE;
  static bool online_flag = TRUE;
  bool check_online_flag = FALSE;
  int		job_hostid_in = -1;	
  int		job_hostid_out = -1;	
  int       jobid;
  int GPSPenvOpenretval;
  int Binding_type;
  int Mixedrot_type;
  int ProcessAllPages,PrintUptoLastPage,StopPrinting;
  int cur_media_val;
  int nup;
  int nup_layout;
  extern   int       gpsJobId, gpsPDLType;
  BOOL 		PageDuplex;
  int    g_JobStart; 	/* This variable can be used to get the information can be used to skip pages from parsing(Set Start page)	*/
  int    g_JobEnd;		/* This variable can be used to get the information can be used to skip pages from parsing(Set End Page)	*/
  extern int JobEndFlag,PageCount; 
  extern int g_jobAvailable;
  extern gwmsg_client_t *gps_client;
  int auto_tray_change = 0, tray_search_mode = 0;
  extern OIL_TyPage *g_pstCurrentPage;
  extern OIL_TyJob *g_pstCurrentJob;
  extern PMS_TyTrayInfo *g_pstTrayInfo;
  extern OIL_TyJob g_tJob;
  gps_paperinfo_t gpsPaperInfo;
  extern int	PlotSet_plotid ;
  extern OIL_tyRIPFeatures *g_pstCurrentRipFeatures;
  extern OIL_TyPlane *g_pstCurrentMedia;
  extern PMS_TySystem g_tSystemInfo;
  extern int current_pdlid; 
  extern di_devinfo_GPS_t *devinfo;
  int g_GPSEnvResolutionPCL = 0; /*This Variable can be used to update X and Y resolution as per Gradation and Resolution output from GPS ENV call*/
  int  Reso_StrctCount = 0;/*This variable is used in getting the count for key entries from Printer.ini for Reso*/
  static bool EXACT_ResoMatch_Found = FALSE, INI_ResoMatch_Found = FALSE;
  extern int IsBannerPageJob;

  extern int GPS_GetBitSw(int num);
  extern int GPS_GetPdlTable(gwmsg_client_t *, long *, int *);
  extern int GPS_GetPrmInfo(int f_id, int *status, int size,	long *maxsize);
  extern int GPS_GetPrtStatus2(gwmsg_client_t *, gps_prtstatus2_t *, int, int *);
  extern int GPS_PlotPrepare(gwmsg_client_t *, int, gps_plotprepareparam_t *);
  extern int GPS_gpsGetHddInfo2(int hdd,gps_hddinfo2_t *hddinfo_download);
  extern int GPS_PlotOpen(gwmsg_client_t *client, int plotOpen_ujobid, int plotOpen_openmode);
  extern void GPS_PmDispSetEmulation(char, char, char, char *);
  extern int GPS_PenvOpen(gwmsg_client_t *client, char *penv_name, long size);
  extern int  GPS_PenvGetDefValue(gwmsg_client_t *, int, long, long *);
  extern int	GPS_PenvGetValue( gwmsg_client_t* client, int penv, long gps_var, long *penv_val );
  extern void GPS_PenvClose(gwmsg_client_t *client, int penv);
  extern void PMS_LeaveCriticalSection(void * ptCritical_Section);
  extern void PMS_DestroySemaphore(void * semaHandle);
  extern void PMS_DestroyCriticalSection(void * ptCritical_Section);
  extern int GPS_GetPdlPrintConditionShm(gwmsg_client_t *, int, int *, unsigned long *);
  extern int PMS_CloseThread(void *pThread, int nWaitForThreadToExit);
  extern int GPS_BinInfo();
  extern int GPS_TrayInfo();
  extern void OIL_JobCancel(void);
  extern int PrintSysReinitTrayInfo(void);
  extern int GPS_PenvSetDefValue(gwmsg_client_t *client, int penv, long penv_var, long penv_val);
  extern void gpsPmExit(void);
  extern int PrintSysReinitBinInfo(void); 
  extern void mfree(void *r);

  
#define GPS_GETDEFAULTVAL_FAILED (0) /*GPS_PenvGetDefValue() call is failed so for PCL, Vaiable update is not required*/
#define FONT_DIR_COUNT 2
#define DIR_PCL_FONT "/pcl/fonts"
#define DIR_PCL_TTFONT "/pcl/TTfonts"

int Get_Data_From_GPS()
{
    int GPSGetPaperInfoRetVal;
    int GPSPdlTableval;
    int GPSGetPrtStatus2val;
    int gps_notify=0;
    int ret;
    int GPSBitSWRetVal = 0;
    /* int GPSGetModelInfoRetVal;*/
    int GPSGetHddInfo2RetVal;

    long pdl_offset; int pdl_num ;
    int prt_res;
    /*char * modelinfovalue;*/
    simhandle_t *hsim;
    gps_prtstatus2_t prtStatus;
    varvalue_t gps_paperId;
    gps_hddinfo2_t hddinfo;	
	int GPSPenvGetDefListRetVal;
    long penv_val;
    long gps_value;
	long gps_var;
	int GPSPenvOpenretval;
    int retGPSPenvGetVal;

	long maxsize[2];
	int f_id = GPS_PRMINFO_GET_COLOR_MODEL;
	int status;
	int retGPSPrmInfo;

    if ((hsim = __gps_getsimhandle()) == (simhandle_t *)0)
		return(-1);


    /************************** Call to gpsGetPaperInfo() *************************/
    
    ret = _var_getbyname(hsim, "GPS_PENV_VAR_ID_APLPAGESIZE", &gps_paperId);
       
    GPSGetPaperInfoRetVal = GPS_GetPaperInfo(gps_client, gps_paperId.u.int_value, &gpsPaperInfo, gps_notify);
	
	if(GPSGetPaperInfoRetVal)
		{
			printf("GPS_GetPaperInfo : SUCCESS\n");
		}
		else
		{
			printf("GPS_GetPaperInfo : FAILED\n");
		}	
    /*************Call to gpsInterpNotifyState()*************************************/
        GPS_InterpNotifyState(gps_client, GPS_INTERP_STATE_PROCESSING);

      
    
    /*************Call to gpsGetBitSw*************************************************/
    GPSBitSWRetVal = GPS_GetBitSw(BIT_SW_002); 
	
    if((GPSBitSWRetVal = BIT_SW_001) || (GPSBitSWRetVal <= BIT_SW_016))
		printf("GPS_getBitSW is success\n");
	else
		printf("GPS_getBitSW is failed\n");

     /*************Call to gpsPdlTable*************************************************/

    GPSPdlTableval = GPS_GetPdlTable(gps_client, &pdl_offset, &pdl_num);
	if(!GPSPdlTableval)
	{
		printf("GetPdlTable : Successful\n");
	}

	     /*************Call to gpsPrmInfo*************************************************/

    retGPSPrmInfo = GPS_GetPrmInfo(f_id, &status, 2, maxsize ); /*2 needs  to be verified */
    if(retGPSPrmInfo == 1)
              printf("GPS_GetPrmInfo: SUCCESS \n");
    else
              printf("GPS_GetPrmInfo: FAILED \n");

        if(status == GPS_PRMINFO_SUCCESS)
              printf("GPS_GetPrmInfo: STATUS SUCCESS\n");
    else
              printf("GPS_GetPrmInfo:STATUS FAILED\n");

      switch(maxsize[0])
          {
            case GPS_CM_BW_MACHINE: /*B&W	*/
                  g_tSystemInfo.eDefaultColMode = OIL_Mono;
                  break;
                case GPS_CM_FULL_COLOR_MACHINE: /* Color	*/
                  g_tSystemInfo.eDefaultColMode = OIL_CMYK_Composite; /* revisit OIL_eColorMode	*/
                  break;
                case GPS_CM_TWIN_COLOR_MACHINE:  //two-color
                  g_tSystemInfo.eDefaultColMode = OIL_Mono; /* revisit OIL_eColorMode	*/
                  break;
                default:
                  g_tSystemInfo.eDefaultColMode = OIL_Mono;
                  break;
          }

     /*************Call to gpsPrtStatus2*************************************************/
    
    GPSGetPrtStatus2val = GPS_GetPrtStatus2(gps_client, &prtStatus, gps_notify, &prt_res);
	if(GPSGetPrtStatus2val)
	{
		printf("GetPrtStatus2 : Success\n");
	}

	/*************Call to gpsGetModelInfo*************************************************/

	/*GPSGetModelInfoRetVal = GPS_GetModelInfo(1, 1,	"color_prm_val", "COLOR", 32, modelinfovalue);
	if(GPSGetModelInfoRetVal== 0)
	     printf("GPS_GetModelInfo: Search Successful\n");
	else
	     printf("GPS_GetModelInfo: Search Failed\n"); */
    /*Either key or category not found, buffer overflow, illegal param, init error */

    /*************Call to gpsGetHddInfo2*************************************************/

	GPSGetHddInfo2RetVal = GPS_gpsGetHddInfo2(GPS_HDD_TMP, &hddinfo );
	
    if(GPSGetHddInfo2RetVal == 0 ) 
		printf("GPS_gpsGetHddInfo2 is success\n");
	else 
	    printf("GPS_gpsGetHddInfo2 is failed\n");


  //Check for Banner Page Print. OFF, before job & after job.
  GPSPenvOpenretval = GPS_PenvOpen( gps_client, GPS_PENV_NAME_COMMON, strlen(GPS_PENV_NAME_COMMON)+1);
		
  if(GPSPenvOpenretval == PENV_HANDLER)
  {
    g_tJob.uPrintBannerPage = GPS_PENV_VAL_INT_BANNERPAGEPRINT_OFF;
    gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINT;
    GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
    if(GPSPenvGetDefListRetVal >= 0)
    {
      g_tJob.uPrintBannerPage = gps_value;
      retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
      if(retGPSPenvGetVal >= 0)
        g_tJob.uPrintBannerPage = penv_val;
    }
    GPS_PenvClose(gps_client, GPSPenvOpenretval);
  }
  return 0;
}

void Get_Env_var_From_GPS(OIL_TyJob *pstJob)
{

    unsigned long offset = 0;
    int GPS_GetPdlPrintConditionShmRetVal;
  //  int GPSPenvOpenretval;
    int status;
    int retGPSPenvGetVal;
    int GPSPenvGetDefListRetVal;
    long penv_val;
    long gps_value;
	long gps_var = 8, checkDuplex;
    char *pdl_name = NULL;
	gps_plotprepareparam_t plotPrepare;    
   
    	int GPSPlotPrepRetVal;
	int ret_ResoValue, INI_KeyCount = 1, ResoCount = 0;
	unsigned char outbuffer[MAX_VALUE_LEN];
	char strbuf[MAX_VALUE_LEN];
	int xres = 0, yres= 0, bit= 0 , drawmode=0, prtmode=0, paperkind=0;
		
	#define YET_TO_FIND_0 200
	#define YET_TO_FIND_1 201
	#define YET_TO_FIND_2 202
	#define YET_TO_FIND_3 203
	#define YET_TO_FIND_4 204
	#define YET_TO_FIND_5 205
	#define YET_TO_FIND_6 206
	#define YET_TO_FIND_7 207
	
    //int job_id= g_pstCurrentJob->>uJobId;
    /*************Call to gpsPmDispSetEmulation***********************************************/
     switch(pstJob->ePDLType)
     {
		case OIL_PDL_XPS:
			pdl_name = "XPS";
			break;
		case OIL_PDL_PDF:
			break;
		case OIL_PDL_PS:
		    pdl_name = "PS";
			break;
		case OIL_PDL_PCL5c:
			pdl_name = "PCL5c";
			break;
		case OIL_PDL_PCL5e:
			pdl_name = "PCL5e";
			break;
		case OIL_PDL_PCLXL:
			pdl_name = "PCLXL";
			break;
		default:
			return -1;
     }

#ifdef USE_SIMULATION_ENVIRONMENT
     if (pdl_name != NULL)
        GPS_PmDispSetEmulation(SET_DISP, SET_DISP, SET_DISP, pdl_name);
#endif

     /*************Call to gpsGetPdlPrintCondtionShm*******************************************/

     GPS_GetPdlPrintConditionShmRetVal = GPS_GetPdlPrintConditionShm(gps_client,jobid,&status, &offset);
	if(GPS_GetPdlPrintConditionShmRetVal)
		{
			printf("GPS_GetPdlPrintConditionShm : SUCCESS\n");
		}
		else
		{
			printf("GPS_GetPdlPrintConditionShm : FAILED\n");
		}

	/************************Call to gpsGetModelInfo************************/
	/*Below part of code is to update TResolution structure with the values of X-resolution, Y-resolution and Gradation values*/
	/*which are present in Printer.ini, and these values will be used to decide the final X-resolution Y-Resolution and Gradation values*/
	do
		{
			sprintf(strbuf, "reso%d", INI_KeyCount);
			ret_ResoValue = gpsGetModelInfo(gps_client,1, 1,	strbuf, "DI", 32, outbuffer);
			if(ret_ResoValue == SERCH_OK)
				{
					printf("retvalue == SERCH_OK");
					sscanf((const char *)outbuffer, "%d,%d,%d,%d,%d,%d", &xres, &yres, &bit, &drawmode, &prtmode, &paperkind);
					TResolution_val[Reso_StrctCount].uINI_XResoluion = xres;
					TResolution_val[Reso_StrctCount].uINI_YResoluion = yres;
					TResolution_val[Reso_StrctCount].uINI_Gradation = bit;
					/*printf("TResolution_val[Reso_StrctCount].uINI_XResoluion = [%d] \n",TResolution_val[Reso_StrctCount].uINI_XResoluion);
					printf("TResolution_val[Reso_StrctCount].uINI_YResoluion = [%d] \n",TResolution_val[Reso_StrctCount].uINI_YResoluion);
					printf("TResolution_val[Reso_StrctCount].uINI_Gradation = [%d] \n",TResolution_val[Reso_StrctCount].uINI_Gradation);*/
					Reso_StrctCount++;
				}
			else
				{
					printf("retvalue != SERCH_OK");
					break;
				}
			INI_KeyCount++;
		}while(ret_ResoValue == SERCH_OK);
      /*************Call to gpsPenvOpen*******************************************/

       GPSPenvOpenretval = GPS_PenvOpen( gps_client, GPS_PENV_NAME_COMMON, strlen(GPS_PENV_NAME_COMMON)+1);
	
    if(GPSPenvOpenretval == PENV_HANDLER)
		     printf("GPS_PenvOpen: SUCCESS\n");
    else 
             printf("GPS_PenvOpen: FAILED\n");
		gps_var = GPS_PENV_VAR_ID_COPIES; 
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
			/*	pstJob->uCopyCount=penv_val;*/
            }
			
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
				
		gps_var = GPS_PENV_VAR_ID_QTY;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				
/*			pstJob->uPagesToPrint = penv_val;	*/
			pstJob->uPagesToPrint = 0 ; /*For tumble*/
			
			param.qty = penv_val ;
		#ifdef DEBUG_LOGS
			printf("QTY value from ENV. call = %ld\n",penv_val);
		#endif
            }
			printf("penv_val = [%ld]\n",penv_val);
	printf("pstJob->uCopyCount = [%ld]\n",pstJob->uCopyCount);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        
        //For bannerpage job get paper size by GPS_PENV_VAR_ID_BANNERPAGEPRINTMEDIA ID.
        if(IsBannerPageJob == TRUE)
          gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINTMEDIA;
        else
          gps_var = GPS_PENV_VAR_ID_PAPER;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			pstJob->tCurrentJobMedia.ePaperSize = gps_value;
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				pstJob->tCurrentJobMedia.ePaperSize = penv_val;
#if 0				
				switch(penv_val)
				{
				 printf("SWITCH SUCCESS: SUCCESS\n");
					  case GPS_CODE_8Hx11:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_LETTER;
						break;
					  case GPS_CODE_A4:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A4;
						break;
					  case GPS_CODE_8Hx14:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_LEGAL;
						break;
					  case GPS_CODE_7Qx10H:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_EXE;
						break;
					  case GPS_CODE_A3:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A3;
						break;
					  case GPS_CODE_11x17:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_TABLOID;
						break;
					  case GPS_CODE_A5:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A5;
						break;
					  case GPS_CODE_A6:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A6;
						break;
					  case GPS_CODE_C5:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_C5_ENV;
						break;
					  case GPS_CODE_DL:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_DL_ENV;
						break;
					  case YET_TO_FIND_0:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_LEDGER;
						break;
					  case YET_TO_FIND_2:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_OFUKU;
						break;
					  case GPS_CODE_10x14:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_JISB4;
						break;
					  case YET_TO_FIND_3:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_JISB5;
						break;
					  case GPS_CODE_8Hx11T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_LETTER_R;
						break;
					  case GPS_CODE_A4T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A4_R;
						break;
					  case GPS_CODE_8Hx14T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_LEGAL_R;
						break;
					  case GPS_CODE_7Qx10HT:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_EXE_R;
						break;
					  case GPS_CODE_A3T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A3_R;
						break;
					  case GPS_CODE_11x17T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_TABLOID_R;
						break;
					  case GPS_CODE_A5T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A5_R;
						break;
					  case GPS_CODE_A6T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_A6_R;
						break;
					  case GPS_CODE_C5T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_C5_ENV_R;
						break;
					  case GPS_CODE_DL_T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_DL_ENV_R;
						break;
					  case YET_TO_FIND_4:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_LEDGER_R;
						break;
					  case YET_TO_FIND_5:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_OFUKU_R;
						break;
					  case GPS_CODE_10x14T:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_JISB4_R;
						break;
					  case YET_TO_FIND_6:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_JISB5_R;
						break;
					  case YET_TO_FIND_7:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_CUSTOM;
						break;
					  default:
						pstJob->tCurrentJobMedia.ePaperSize = PMS_SIZE_DONT_KNOW;
						break;
				}
#endif				
				printf("pstJob->tCurrentJobMedia.ePaperSize = [%d]\n",pstJob->tCurrentJobMedia.ePaperSize);
	
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

        
	//printf("---GPS_PENV_VAR_ID_ORIENTATION---------------------------------------------------4---");
		gps_var = GPS_PENV_VAR_ID_ORIENTATION;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				pstJob->uOrientation=penv_val; //0= Portrait, 1= Landscape
            }
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
         
	/* Autotraychange*/
        gps_var = DI_ENV_VAR_ID_AUTOTRAYCHANGE;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				auto_tray_change = penv_val; 
            }
        }
        else
        {
            printf("Environment Def List: failed\n");
        }


    /*traysearchmode*/
        	gps_var = DI_ENV_VAR_ID_TRAYSEARCHMODE;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				tray_search_mode = penv_val; 
            }
        }
        else
        {
            printf("Environment Def List: failed\n");
        }

 if(current_pdlid == GPS_PDL_PCL)    /* Check the job, if it is PCL5c then proceed else skip below part*/
   {
		gps_var = GPS_PENV_VAR_ID_RESOLUTIONPCL;
			GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
			if(GPSPenvGetDefListRetVal >= 0)
			{
				printf("Environment Def List: success\n");
				retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
				if(retGPSPenvGetVal < 0)
				{
					printf("GPS_PenvGetValue: FAILED\n");
				}
				else
				{
					printf("GPS_PenvGetValue: SUCCESS\n");
					/*pstJob->uXResolution = penv_val;
					pstJob->uYResolution = penv_val;*/
					g_GPSEnvResolutionPCL = penv_val;
				}
			}
			else
			{
				printf("Environment Def List: failed\n");
			}
		gps_var = GPS_PENV_VAR_ID_BITSPERDOTPCL;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				printf("penv_val = [%ld]\n",penv_val);
				bits_pcl = penv_val;
			}
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	}			

if(current_pdlid == GPS_PDL_PCLXL)    /* Check the job, if it is PCLXL then proceed else skip below part*/
   {
			gps_var = GPS_PENV_VAR_ID_RESOLUTIONPCLXL;
			GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
			if(GPSPenvGetDefListRetVal >= 0)
			{
				printf("Environment Def List: success\n");
				
				retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
				if(retGPSPenvGetVal < 0)
				{
					printf("GPS_PenvGetValue: FAILED\n");
				}
				else
				{
					printf("GPS_PenvGetValue: SUCCESS\n");
					/*pstJob->uXResolution = penv_val;
					pstJob->uYResolution = penv_val;*/
					g_GPSEnvResolutionPCL = penv_val;
				}
				printf("penv_val = [%ld]\n",penv_val);
			}
			else
			{
				printf("Environment Def List: failed\n");
			}
			
			
		printf("---GPS_PENV_VAR_ID_BITSPERDOTPCLXL---2018---");/*Not required for PCL as Gradation is not being used in PCL*/
		gps_var = GPS_PENV_VAR_ID_BITSPERDOTPCLXL;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				bits_pcl = penv_val;
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
       printf("gps_value = [%ld]\n",gps_value);
	}		

if(current_pdlid == GPS_PDL_POSTSCRIPT)    /* Check the job, if it is PS then proceed else skip below part*/
   {
	gps_var = GPS_PENV_VAR_ID_RESOLUTIONPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				g_GPSEnvResolutionPCL = penv_val;
				/*pstJob->uXResolution = penv_val;
				printf(" pstJob->uXResolution= [%d]\n",pstJob->uXResolution);
				pstJob->uYResolution = penv_val;
				printf(" pstJob->uYResolution= [%d]\n",pstJob->uYResolution);*/
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

	gps_var = GPS_PENV_VAR_ID_BITSPERDOTPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				bits_pcl = penv_val;
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

	}	

if(current_pdlid == GPS_PDL_PDF)    /* Check the job, if it is PDF then proceed else skip below part*/
   {
		gps_var = GPS_PENV_VAR_ID_RESOLUTIONPDF;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				g_GPSEnvResolutionPCL = penv_val;
				/*pstJob->uXResolution = penv_val;
				pstJob->uYResolution = penv_val;*/
            }
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
		
		gps_var = GPS_PENV_VAR_ID_BITSPERDOTPDF;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				bits_pcl = penv_val;
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		gps_var = GPS_PENV_VAR_ID_EDGETOEDGE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
			edge = penv_val;
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		/*======================================================================*
		 *		BACKCOVERPRINT
		*======================================================================
				GPS_PENV_VAL_INT_BACKCOVERPRINT_OFF		(0)
				GPS_PENV_VAL_INT_BACKCOVERPRINT_BLANK		(1)
				GPS_PENV_VAL_INT_BACKCOVERPRINT_INNERCOPY	(2)
				GPS_PENV_VAL_INT_BACKCOVERPRINT_OUTERCOPY	(3)
		*======================================================================*/
				
		gps_var = GPS_PENV_VAR_ID_BACKCOVERPRINT;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
		{
#ifdef DEBUG_LOGS
			printf("GPS_PENV_VAR_ID_BACKCOVERPRINT Environment Def List: success. gps_value = [%ld]\n",gps_value);
#endif			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
#ifdef DEBUG_LOGS			
				printf("GPS_PENV_VAR_ID_BACKCOVERPRINT GPS_PenvGetValue: FAILED\n");
#endif
			}
			else
			{
#ifdef DEBUG_LOGS			
				printf("GPS_PENV_VAR_ID_BACKCOVERPRINT GPS_PenvGetValue: SUCCESS. penv_val = [%ld]\n",penv_val);
#endif
			}
			param.Cover.back = penv_val;
		}
		else
		{
#ifdef DEBUG_LOGS		
			printf("GPS_PENV_VAR_ID_BACKCOVERPRINT Environment Def List: failed\n");
#endif
		}
		
		/*======================================================================*
		 *		BACKCOVERPRINTTRAY
		*======================================================================
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_NONE	GPS_TRAY_NONE
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_TRAY1	GPS_TRAY_1
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_TRAY2	GPS_TRAY_2
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_TRAY3	GPS_TRAY_3
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_TRAY4	GPS_TRAY_4
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_TRAY5	GPS_TRAY_5
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_TRAY6	GPS_TRAY_6
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_TRAY7	GPS_TRAY_7
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_LCT	        GPS_TRAY_LCT
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_BYPASS	GPS_TRAY_MAN
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_ENVFEED	GPS_TRAY_ENVFEED
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_INSERTER	GPS_TRAY_INSERTER
				GPS_PENV_VAL_INT_BACKCOVERPRINTTRAY_INSERTER2	GPS_TRAY_INSERTER2
		*======================================================================*/
		
		
		gps_var = GPS_PENV_VAR_ID_BACKCOVERPRINTTRAY;
		
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
		{
#ifdef DEBUG_LOGS
			printf("GPS_PENV_VAR_ID_BACKCOVERPRINTTRAY Environment Def List: success. gps_value = [%ld]\n",gps_value);	
#endif
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
#ifdef DEBUG_LOGS			
				printf("GPS_PENV_VAR_ID_BACKCOVERPRINTTRAY GPS_PenvGetValue: FAILED\n");
#endif
			}
			else
			{
#ifdef DEBUG_LOGS			
				printf("GPS_PENV_VAR_ID_BACKCOVERPRINTTRAY GPS_PenvGetValue: SUCCESS. penv_val = [%ld]\n",penv_val);
#endif
			} 
			param.Cover.bcover_tray = penv_val;
		}
		else
		{
#ifdef DEBUG_LOGS		
			printf("GPS_PENV_VAR_ID_BACKCOVERPRINTTRAY Environment Def List: failed\n");
#endif
		}
		
		gps_var = GPS_PENV_VAR_ID_TRAYSEARCHMODE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
			traysearch = penv_val;
        }
        else
        {
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%ld]\n",gps_value);
		
        
		gps_var = GPS_PENV_VAR_ID_FOLD;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("gps_value = [%ld]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
			
	}
			
			/*======================================================================*
			 *		FRONTCOVERPRINT
			  *======================================================================
					GPS_PENV_VAL_INT_FRONTCOVERPRINT_OFF		(0)
					GPS_PENV_VAL_INT_FRONTCOVERPRINT_BLANK		(1)
					GPS_PENV_VAL_INT_FRONTCOVERPRINT_SIMPLEXCOPY	(2)
					GPS_PENV_VAL_INT_FRONTCOVERPRINT_DUPLEXCOPY	(3)
			 *======================================================================*/
	
	
	
			gps_var = GPS_PENV_VAR_ID_FRONTCOVERPRINT;
			GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
			if(GPSPenvGetDefListRetVal >= 0)
			{
#ifdef DEBUG_LOGS
				printf("GPS_PENV_VAR_ID_FRONTCOVERPRINT Environment Def List: success. gps_value = [%ld]\n",gps_value);
#endif				
				retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
				if(retGPSPenvGetVal < 0)
				{
#ifdef DEBUG_LOGS
					printf("GPS_PENV_VAR_ID_FRONTCOVERPRINT GPS_PenvGetValue: FAILED\n");
#endif
				}
				else
				{
#ifdef DEBUG_LOGS
					printf("GPS_PENV_VAR_ID_FRONTCOVERPRINT GPS_PenvGetValue: SUCCESS. penv_val = [%ld]\n",penv_val);
#endif
				} 
				frontcover = penv_val;
				param.Cover.front=penv_val;
			}
			else
			{
#ifdef DEBUG_LOGS			
				printf("GPS_PENV_VAR_ID_FRONTCOVERPRINT Environment Def List: failed\n");
#endif
			} 
			
			/*======================================================================*
			 *		FRONTCOVERPRINTTRAY
			 *======================================================================
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_NONE	GPS_TRAY_NONE
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_TRAY1	GPS_TRAY_1
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_TRAY2	GPS_TRAY_2
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_TRAY3	GPS_TRAY_3
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_TRAY4	GPS_TRAY_4
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_TRAY5	GPS_TRAY_5
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_TRAY6	GPS_TRAY_6
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_TRAY7	GPS_TRAY_7
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_LCT	GPS_TRAY_LCT
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_BYPASS	GPS_TRAY_MAN
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_ENVFEED	GPS_TRAY_ENVFEED
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_INSERTER	GPS_TRAY_INSERTER
				GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_INSERTER2	GPS_TRAY_INSERTER2
			*======================================================================*/
	
			
			gps_var = GPS_PENV_VAR_ID_FRONTCOVERPRINTTRAY;
			GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
			if(GPSPenvGetDefListRetVal >= 0)
			{
#ifdef DEBUG_LOGS
				printf("GPS_PENV_VAR_ID_FRONTCOVERPRINTTRAY Environment Def List: success. gps_value = [%ld]\n",gps_value);
#endif				
				retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
				if(retGPSPenvGetVal < 0)
				{
#ifdef DEBUG_LOGS				
					printf("GPS_PENV_VAR_ID_FRONTCOVERPRINTTRAY GPS_PenvGetValue: FAILED\n");
#endif
				}
				else
				{
#ifdef DEBUG_LOGS				
					printf("GPS_PENV_VAR_ID_FRONTCOVERPRINTTRAY GPS_PenvGetValue: SUCCESS. penv_val = [%ld]\n",penv_val);
#endif
				}
				frontcover_tray = penv_val;
				param.Cover.fcover_tray =penv_val;
			}
			else
			{
#ifdef DEBUG_LOGS			
				printf("GPS_PENV_VAR_ID_FRONTCOVERPRINTTRAY Environment Def List: failed\n");
#endif
			}
			
        //For bannerpage job get tray value by GPS_PENV_VAR_ID_BANNERPAGEPRINTTRAY ID.
		if(IsBannerPageJob == TRUE)
		  gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINTTRAY;
		else
          gps_var = GPS_PENV_VAR_ID_TRAY;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
          pstJob->tCurrentJobMedia.uInputTray = gps_value;
          retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
          if(retGPSPenvGetVal >= 0)
            pstJob->tCurrentJobMedia.uInputTray = penv_val;
        }
				
	gps_var = GPS_PENV_VAR_ID_OUTBIN;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				pstJob->tCurrentJobMedia.uOutputTray = penv_val;
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_AUTOTRAYCHANGE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
				autotray = penv_val;

        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

if(current_pdlid == GPS_PDL_POSTSCRIPT)
                gps_var = GPS_PENV_VAR_ID_RENDERMODEPS;
else
		gps_var = GPS_PENV_VAR_ID_RENDERMODE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("GPS_PenvGetDefValue(): success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				if(penv_val == GPS_PENV_VAL_INT_RENDERMODE_COLOR) 
				{
					pstJob->eRenderMode = PMS_RenderMode_Color;
				}
				else if(penv_val == GPS_PENV_VAL_INT_RENDERMODE_GRAYSCALE)
				{
					pstJob->eRenderMode = PMS_RenderMode_Grayscale;
				}
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


		gps_var = GPS_PENV_VAR_ID_MEDIATYPE;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				cur_media_val = penv_val;
				switch(penv_val)
				{
				  case DI_PAPER_NORMAL:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Plain" );
					break;
				 case DI_PAPER_BOND:
				 strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Bond" );
					break;
				  case DI_PAPER_SPECIAL:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Special" );
					break;
				  case DI_PAPER_GLOSSY:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Glossy" );
					break;
				  case DI_PAPER_OHP:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Transparency" );
					break;
				  case DI_PAPER_RECYCLE:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Recycled" );
					break;
				  case DI_PAPER_ENVELOPE:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Envelope" );
					break;
				  case DI_PAPER_POSTCARD:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Postcard" );
					break;
				  case DI_PAPER_THIN:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Thin" );
					break;
				  case DI_PAPER_LABEL:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Label" );
					break;
				  case DI_PAPER_PREPRINT:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Preprinted" );
					break;
				  case DI_PAPER_LETTER_HEAD:
				  strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Letterhead" );
					break;
				  default:
				 strcpy( (char *)pstJob->tCurrentJobMedia.szMediaType, "Plain" );
					break;
				}
			
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


		gps_var = GPS_PENV_VAR_ID_JOBOFFSET;
		 GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				pstJob->uJobOffset = penv_val; 
				printf("pstJob->uJobOffset = [%d]\n",pstJob->uJobOffset);
		#ifdef DEBUG_LOGS
			printf("JobOffset value from ENV. call = %ld\n",penv_val);
		#endif

            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
				
				
		gps_var = GPS_PENV_VAR_ID_AUTOERRSKIP;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


if(current_pdlid == GPS_PDL_POSTSCRIPT)
		gps_var = GPS_PENV_VAR_ID_BINDINGPS;
else
		gps_var = GPS_PENV_VAR_ID_BINDING;////////////////NEEDS TO BE CHECKED///////////////////////

		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("GPS_PenvGetDefValue(): success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				pstJob->uBookletType = penv_val;
				printf("pstJob->uBookletType= [%d]\n",pstJob->uBookletType);

				pstJob->uBindingType = penv_val;
				Binding_type = pstJob->uBindingType;
				printf("pstJob->uBindingType= [%d]\n",pstJob->uBindingType);

            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


if(current_pdlid == GPS_PDL_POSTSCRIPT)
		gps_var = GPS_PENV_VAR_ID_DUPLEXPS;
else
	gps_var = GPS_PENV_VAR_ID_DUPLEX;

        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("GPS_PenvGetDefValue(): success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				pstJob->bDuplex = penv_val;
				printf("pstJob->bDuplex= [%d]\n",pstJob->bDuplex);

            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	

if(current_pdlid == GPS_PDL_POSTSCRIPT)
                gps_var = GPS_PENV_VAR_ID_ECONOMODEPS; 
else
	gps_var = GPS_PENV_VAR_ID_ECONOMODE;////////////////////////PENDING FOR CLARIFICATION////////////////
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("GPS_PenvGetDefValue(): success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_JAMRECOVERY;////////////////////////PENDING FOR CLARIFICATION////////////////
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		
		gps_var = GPS_PENV_VAR_ID_SMOOTHING;/////////////////////////PENDING FOR CLARIFICATION////////////////
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_STAPLE;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				
				pstJob->uStapleType = penv_val;
				printf("pstJob->uStapleType = [%d]\n",pstJob->uStapleType);
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
				

		gps_var = GPS_PENV_VAR_ID_PUNCH;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				pstJob->uPunchType = penv_val;
				printf("pstJob->uPunchType= [%d]\n",pstJob->uPunchType);
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_MIXEDDIRROTATION;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				Mixedrot_type = penv_val;
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
        gps_var = GPS_PENV_VAR_ID_NUP;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
                    retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
                    if(retGPSPenvGetVal < 0)
                        printf("GPS_PenvGetValue: FAILED\n");
                    printf("penv_val = [%d]\n",penv_val);
                    nup = penv_val;
                }
        else
            printf("Environment Def List: failed\n");
        printf("gps_value = [%d]\n",gps_value);

        gps_var = GPS_PENV_VAR_ID_NUPPAGEORDER;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {			
            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
                printf("GPS_PenvGetValue: FAILED\n");
            printf("penv_val = [%d]\n",penv_val);
            nup_layout = penv_val;
        }
        else
            printf("Environment Def List: failed\n");
        printf("gps_value = [%d]\n",gps_value);

		
	    gps_var = GPS_PENV_VAR_ID_WIDEA4;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
		if(penv_val == 1)
			pstJob->bWideA4 = TRUE;
		else
			pstJob->bWideA4 = FALSE;
				printf("pstJob->bWideA4= [%d]\n",pstJob->bWideA4);
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

if(current_pdlid == GPS_PDL_POSTSCRIPT)
                gps_var = GPS_PENV_VAR_ID_EDGETOEDGEPS;
else
	gps_var = GPS_PENV_VAR_ID_EDGETOEDGE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue(): success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
			edge = penv_val;
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

	gps_var = GPS_PENV_VAR_ID_PCLOUTLINEFONT;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
	        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		printf("****************BANNERPAGEPRINT***************");
		gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINT;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
				printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%ld]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


		gps_var = GPS_PENV_VAR_ID_AUTOTRAYCHANGE2;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
		        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		gps_var = GPS_PENV_VAR_ID_CHAPTERPRINT;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
			chapter_val = penv_val;
		        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_TRAYSEARCHMODE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
			traysearch = penv_val;
        }
        else
        {
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%ld]\n",gps_value);
		
	gps_var = GPS_PENV_VAR_ID_BYPASSTRAYSETTING;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
	            }
			bypass_tray = penv_val;
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	gps_var = GPS_PENV_VAR_ID_COURIER;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
		if(penv_val == 1)
			pstJob->bCourierDark = TRUE;
		else
			pstJob->bCourierDark = FALSE;
				printf("pstJob->bWideA4= [%d]\n",pstJob->bWideA4);
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		printf("****************BANNERPAGEPRINT***************");
		gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINT;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
				printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%ld]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		
		gps_var = GPS_PENV_VAR_ID_SLIPSHEETPRINT;//////////PENDING FOR CLARIFICATION///////////////
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		/*gps_var = GPS_PENV_VAR_ID_BITSPERDOTPCL;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			pstJob->uRIPDepth=penv_val;
			printf("penv_val = [%ld]\n",penv_val);
			bits_pcl = penv_val;
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);*/
		
		gps_var = GPS_PENV_VAR_ID_MEMORYUSAGE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_ERRORREPORT;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
						
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                 printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
						if(penv_val == 1)
						pstJob->uPrintErrorPage = TRUE;
						else
						pstJob->uPrintErrorPage = FALSE;
						printf("pstJob->uPrintErrorPage= [%d]\n",pstJob->uPrintErrorPage);
            }
			printf("penv_val = [%ld]\n",penv_val);
			
        }
        else
		{
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

if(current_pdlid == GPS_PDL_POSTSCRIPT)
                gps_var = GPS_PENV_VAR_ID_WHITEPAPERSUPPRESSPS; 
else
		gps_var = GPS_PENV_VAR_ID_WHITEPAPERSUPPRESS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue(): success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				if(penv_val == 1)
				pstJob->bSuppressBlank = TRUE;
				else
				pstJob->bSuppressBlank = FALSE;
				printf("pstJob->bSuppressBlank= [%d]\n",pstJob->bSuppressBlank);
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_DATAMODE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
             printf("Environment Def List: success\n");
			 
			 retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

	if(current_pdlid == GPS_PDL_XPS)
	{
		printf("---GPS_PENV_VAR_ID_EDGETOEDGEXPS------------------------------------2823---");
		gps_var = GPS_PENV_VAR_ID_EDGETOEDGEXPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	}
	
	gps_var = GPS_PENV_VAR_ID_REQPROCREASON;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
			req_proc = penv_val;
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_JOBPARAMSTART;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
                printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
                printf("GPS_PenvGetValue: SUCCESS\n");
				
				g_JobStart = penv_val;	//Needs to be checked if correct as in GPS ID "GPS_PENV_VAR_ID_JOBPARAMSTART" is not being used only defined
				printf("g_JobStart= [%d]\n",g_JobStart);
			}
			printf("penv_val = [%ld]\n",penv_val);
		}
		else
		{
            printf("Environment Def List: failed\n");
		}
		printf("gps_value = [%ld]\n",gps_value);
				
		gps_var = GPS_PENV_VAR_ID_JOBPARAMEND;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
                printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
                printf("GPS_PenvGetValue: SUCCESS\n");
				g_JobEnd = penv_val;		//Needs to be checked if correct as in GPS ID "GPS_PENV_VAR_ID_JOBPARAMEND" is not being used only defined
				printf("g_JobEnd = [%u]\n",g_JobEnd);	
			}
			printf("penv_val = [%ld]\n",penv_val);
		}
		else
		{
            printf("Environment Def List: failed\n");
		}
		printf("gps_value = [%ld]\n",gps_value);

	if(g_JobStart < 1 && g_JobEnd <1)
		ProcessAllPages = 1;
		
	if(g_JobStart < 1 && g_JobEnd > 1)
		g_JobStart=1;

	if(g_JobEnd < g_JobStart)

	{	
	  if(g_JobEnd < 0)
		PrintUptoLastPage = 1;

	   if(g_JobEnd > 0)
		StopPrinting = 1;

			
	}

	if(ProcessAllPages == 0 && pstJob->bDuplex == 1)
	{

	if((g_JobStart%2)== 0)
		g_JobStart--;
	
	if((g_JobEnd%2)!= 0)
		g_JobEnd++;
	}




		gps_var = GPS_PENV_VAR_ID_DUPLEXPCL;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
if((current_pdlid == GPS_PDL_POSTSCRIPT) || (current_pdlid == GPS_PDL_PDF))
{
		gps_var = GPS_PENV_VAR_ID_BLACKOVERPRINT;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
}

#if GPS_GETDEFAULTVAL_FAILED  /*GPS_PenvGetDefValue() call is failed so for PCL, Vaiable update is not required*/
printf("---GPS_PENV_VAR_ID_RESOLUTIONTIFF---242---"); 
	gps_var = GPS_PENV_VAR_ID_RESOLUTIONTIFF;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_RESOLUTIONXPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				g_GPSEnvResolutionPCL = penv_val;
		    }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_BITSPERDOTXPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
				bits_pcl = penv_val;
		    }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_PERSONALITY;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_RENDERMODEXPS;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
							
		gps_var = GPS_PENV_VAR_ID_MANUALFEED;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

				
		gps_var = GPS_PENV_VAR_ID_BINDINGXPS;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
			
			
	gps_var = GPS_PENV_VAR_ID_DUPLEXXPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_ECONOMODEXPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_INTRAY1;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
			
		gps_var = GPS_PENV_VAR_ID_INTRAY2;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		
		gps_var = GPS_PENV_VAR_ID_INTRAY3;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_INTRAY4;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_INTRAY5;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_INTRAY6;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);	

		gps_var = GPS_PENV_VAR_ID_INTRAY7;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_INTRAYLCT;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
			
		gps_var = GPS_PENV_VAR_ID_INTRAYMULTI;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_IOSIZE;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
			
		gps_var = GPS_PENV_VAR_ID_LANG;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_POWERSAVE;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_POWERSAVETIME;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_SEQUENTIALSTACK;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_TIMEOUT;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_DENSITY;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
			
		gps_var = GPS_PENV_VAR_ID_PLANESELECTK;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_PLANESELECTC;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
				
		gps_var = GPS_PENV_VAR_ID_PLANESELECTM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
				
		gps_var = GPS_PENV_VAR_ID_PLANESELECTY;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	

		gps_var = GPS_PENV_VAR_ID_SLIPSHEETPRINTTRAY;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
			
			
		gps_var = GPS_PENV_VAR_ID_AUTOERRSKIPTIME;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
				
		gps_var = GPS_PENV_VAR_ID_AUTOOUTPUTTIME;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_DOCBODYTRAY;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


		gps_var = GPS_PENV_VAR_ID_WHITEPAPERSUPPRESSXPS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
		{
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_COURIER;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_PCLTRAY1PARAM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
					
	gps_var = GPS_PENV_VAR_ID_PCLTRAY2PARAM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
			printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
					
		gps_var = GPS_PENV_VAR_ID_PCLTRAY3PARAM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
           printf("Environment Def List: success\n");
		   
		   retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
			
		gps_var = GPS_PENV_VAR_ID_PCLTRAY4PARAM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
						
		gps_var = GPS_PENV_VAR_ID_PCLTRAY5PARAM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
			
			
		gps_var = GPS_PENV_VAR_ID_PCLTRAY6PARAM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
           printf("Environment Def List: success\n");
		   
		   retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
		
			
		gps_var = GPS_PENV_VAR_ID_PCLTRAY7PARAM;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
		{
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
			

		gps_var = GPS_PENV_VAR_ID_PCLLCTPARAM;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		

		gps_var = GPS_PENV_VAR_ID_PCLBYPASSPARAM;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	     
		gps_var = GPS_PENV_VAR_ID_PCLTRAYALLPARAM;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_EDGETOEDGEPCL;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_BINDINGPCL;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_WHITEPAPERSUPPRESSPCL;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%ld]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_PAPERPCL;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
			{
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
        
		
	printf("---GPS_PENV_VAR_ID_FORMLINES--------------------------------------81---");
	gps_var = GPS_PENV_VAR_ID_FORMLINES;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_AUTOTRAYCHANGE2;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
			autotray = penv_val;
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		

		gps_var = GPS_PENV_VAR_ID_GPSBYPASSTRAYMODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
			bypass_tray = penv_val;
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_GPSTRAY1MODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_GPSTRAY2MODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%d]\n",gps_value);
       
		
		gps_var = GPS_PENV_VAR_ID_GPSTRAY3MODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_GPSTRAY4MODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
				printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_GPSTRAY5MODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_GPSTRAY6MODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                 printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
		{
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_GPSTRAY7MODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_GPSLCTMODESETTING;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
			}
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
             printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_DISKIMAGE;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",penv_val);
		printf("****************BANNERPAGEPRINT***************");
		gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINT;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
				printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINTTRAY;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_BANNERPAGEPRINTMEDIA;
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
			}
			else
            {
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_SAVEMODE ;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		gps_var = GPS_PENV_VAR_ID_TABPOSITION ;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
					
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
			else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
			printf("penv_val = [%d]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	#endif /*GPS_PenvGetDefValue() call is failed so for PCL, Vaiable update is not required*/

if(current_pdlid == GPS_PDL_POSTSCRIPT)
        {

         gps_var = GPS_PENV_VAR_ID_PSTRAY1PARAM;
	
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAY1PARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);



         gps_var = GPS_PENV_VAR_ID_PSTRAY2PARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAY2PARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSTRAY3PARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAY3PARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSTRAY4PARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAY4PARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSTRAY5PARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAY5PARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSTRAY6PARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAY6PARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSTRAY7PARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAY7PARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSBYPASSPARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSBYPASSPARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSLCTPARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSLCTPARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);


         gps_var = GPS_PENV_VAR_ID_PSTRAYALLPARAM;
         GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("GPS_PenvGetDefValue() : success\n");

            retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
            if(retGPSPenvGetVal < 0)
            {
                printf("GPS_PenvGetValue: FAILED\n");
            }
            else
            {
                printf("GPS_PenvGetValue: SUCCESS\n");
            }
        printf("penv_val for GPS_PENV_VAR_ID_PSTRAYALLPARAM = [%ld]\n",penv_val);
        }
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);

	}
GPS_PenvClose(gps_client, GPSPenvOpenretval);



 /*************Call to gpsPenvOpen*******************************************/
	printf("***************GPS_PenvOpen call for PCL********************");
       GPSPenvOpenretval = GPS_PenvOpen( gps_client, GPS_PENV_NAME_PCL, strlen(GPS_PENV_NAME_PCL)+1);

    if(GPSPenvOpenretval == PENV_HANDLER)
		printf("GPS_PenvOpen: SUCCESS\n");
    else
        printf("GPS_PenvOpen: FAILED\n");
#if GPS_GETDEFAULTVAL_FAILED /*GPS_PenvGetDefValue() call is failed so for PCL, Vaiable update is not required*/
	printf("---GPS_PENV_VAR_ID_FONTSOURCE-------------------------------------------------151---");
		gps_var = GPS_PENV_VAR_ID_FONTSOURCE;	 
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval, gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval, gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
				printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
			printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
					

	printf("---GPS_PENV_VAR_ID_FONTNUMBER------------------------------------------152---");
		gps_var = GPS_PENV_VAR_ID_FONTNUMBER;	 
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval, gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval, gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
				printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
								
					
		gps_var = GPS_PENV_VAR_ID_PITCH;	 
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval, gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval, gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
				printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
					
					
	printf("---GPS_PENV_VAR_ID_PTSIZE------------------------------154---");
		gps_var = GPS_PENV_VAR_ID_PTSIZE;	 
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval, gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval, gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
				printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
					
  
	printf("---GPS_PENV_VAR_ID_SYMSET---------------------------------155---");
		gps_var = GPS_PENV_VAR_ID_SYMSET;	 
		GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval, gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
            printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval, gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
				printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
				pstJob->uSymbolSet = penv_val;
			printf("penv_val = [%d]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
					
					
	printf("---GPS_PENV_VAR_ID_VMI----------------------------------------159---");
		gps_var = GPS_PENV_VAR_ID_VMI;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
			printf("Environment Def List: success\n");
			
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
				printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
	
		
	printf("---GPS_PENV_VAR_ID_FILTERTEXT--------------------------------------157---");
		gps_var = GPS_PENV_VAR_ID_FILTERTEXT;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval,gps_var , &gps_value);
		if(GPSPenvGetDefListRetVal >= 0)
        {
			printf("Environment Def List: success\n");
				
			retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval,gps_var , &penv_val );
			if(retGPSPenvGetVal < 0)
			{
				printf("GPS_PenvGetValue: FAILED\n");
			}
			else
			{
				printf("GPS_PenvGetValue: SUCCESS\n");
			}
			printf("penv_val = [%d]\n",penv_val);
		}
        else
		{
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%d]\n",gps_value);
	#endif /*GPS_PenvGetDefValue() call is failed so for PCL, Vaiable update is not required*/
		
		GPS_PenvClose(gps_client, GPSPenvOpenretval);
	
		
	GPSPenvOpenretval = GPS_PenvOpen( gps_client, GPS_PENV_NAME_PCL, strlen(GPS_PENV_NAME_PCL)+1);
	if(GPSPenvOpenretval == PENV_HANDLER)
		printf("GPS_PenvOpen: SUCCESS\n");
	else
		printf("GPS_PenvOpen: FAILED\n");
				   
	gps_var = GPS_PENV_VAR_ID_FONTDOWNLOADEDONRAM;
	GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval, gps_var , &gps_value);
	if(GPSPenvGetDefListRetVal >= 0)
        {
		printf("Environment Def List: success\n");
			
		retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval, gps_var , &penv_val );
		if(retGPSPenvGetVal < 0)
		{
			printf("GPS_PenvGetValue: FAILED\n");
		}
		else
		{
			printf("GPS_PenvGetValue: SUCCESS\n");
		}
		printf("penv_val = [%ld]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%ld]\n",gps_value);
		
		GPS_PenvClose(gps_client, GPSPenvOpenretval);


	GPSPenvOpenretval = GPS_PenvOpen( gps_client, GPS_PENV_NAME_POSTSCRIPT, strlen(GPS_PENV_NAME_POSTSCRIPT)+1);
	if(GPSPenvOpenretval == PENV_HANDLER)
		printf("GPS_PenvOpen: SUCCESS\n");
	else
		printf("GPS_PenvOpen: FAILED\n");

        gps_var = GPS_PENV_VAR_ID_PRTPSERRS;
        GPSPenvGetDefListRetVal = GPS_PenvGetDefValue(gps_client, GPSPenvOpenretval, gps_var , &gps_value);
        if(GPSPenvGetDefListRetVal >= 0)
        {
                printf("GPS_PenvGetDefValue() : success\n");

                retGPSPenvGetVal = GPS_PenvGetValue( gps_client, GPSPenvOpenretval, gps_var , &penv_val );
                if(retGPSPenvGetVal < 0)
                {
                        printf("GPS_PenvGetValue: FAILED\n");
                }
                else
                {
                        printf("GPS_PenvGetValue: SUCCESS\n");
                }
                printf("penv_val for GPS_PENV_VAR_ID_PRTPSERRS = [%ld]\n",penv_val);
        }       
        else
        {
            printf("GPS_PenvGetDefValue(): failed\n");
        }
        printf("gps_value = [%ld]\n",gps_value);
	GPS_PenvClose(gps_client, GPSPenvOpenretval);

	for( ResoCount = 0;ResoCount < Reso_StrctCount;ResoCount++)
	{
		if(g_GPSEnvResolutionPCL == TResolution_val[ResoCount].uINI_XResoluion && bits_pcl == TResolution_val[ResoCount].uINI_Gradation)
		{
			pstJob->uXResolution = TResolution_val[ResoCount].uINI_XResoluion;
			pstJob->uYResolution = TResolution_val[ResoCount].uINI_YResoluion;
			pstJob->uRIPDepth = TResolution_val[ResoCount].uINI_Gradation;
			EXACT_ResoMatch_Found = TRUE;
			break;
		}
	}
		
	if(!EXACT_ResoMatch_Found)
	{
		for( ResoCount = 0;ResoCount < Reso_StrctCount;ResoCount++)
		{
			if(g_GPSEnvResolutionPCL == TResolution_val[ResoCount].uINI_XResoluion)
			{
				pstJob->uXResolution = TResolution_val[ResoCount].uINI_XResoluion;
				pstJob->uYResolution = TResolution_val[ResoCount].uINI_YResoluion;
				pstJob->uRIPDepth = TResolution_val[ResoCount].uINI_Gradation;
				INI_ResoMatch_Found = TRUE;
				break; /*To Do: The behaviour if Printer.ini has 2 entries for this X resolution(Symmetric and Asymmetric)*/
			}
		}
	}
	if((!EXACT_ResoMatch_Found)&&(!INI_ResoMatch_Found)) /* Set Default values */
	{
		pstJob->uXResolution = GPS_PENV_VAL_INT_RESOLUTION_600;
		pstJob->uYResolution = GPS_PENV_VAL_INT_RESOLUTION_600;
		pstJob->uRIPDepth = 1;
	}

	plotPrepare.resolution_x = pstJob->uXResolution;
	plotPrepare.resolution_y = pstJob->uYResolution;
	plotPrepare.depth = pstJob->uRIPDepth;
	#ifdef DEBUG_LOGS
	printf("X-Resolution value from ENV call =  [%ld]\n",pstJob->uXResolution);
	printf("Y-Resolution value from ENV call = [%ld]\n",pstJob->uYResolution);
	printf("Gradation value from ENV call = [%ld]\n",pstJob->uRIPDepth);
	#endif

    /*************Call to gpsPlotPrepare*************************************************/
  if(PlotSet_plotid < 0)
  {
	GPSPlotPrepRetVal = GPS_PlotPrepare(gps_client,jobid, &plotPrepare);
	if(GPSPlotPrepRetVal)
	{
		printf("GPS_PlotPrepare : Success\n");
	}
	else 
	{
		printf("GPS_PlotPrepare : Failed\n");
	}

    /*************Call to gpsPlotOpen*************************************************/

	PlotSet_plotid = GPS_PlotOpen(gps_client, jobid, GPS_PLOT_NORMAL);
    if(PlotSet_plotid >= 0)
	{
		printf("GPS_PlotOpen : Success\n");
	}
	else
	{
		printf("GPS_PlotOpen : Failed\n");
	}
     /*************************Call to gpsPloSetPageParamShm**************************/

	//We need to update this str properly. For time being hard code.
	param.acs = GPS_ACS_OFF; //off & on. what is ACS?
	param.binding = GPS_BIND_LEFT;
	param.color_count = GPS_COLOR_CMYK;
	param.color_separate = GPS_COLOR_SEPARATE_K;

	/*======================================================================*
		outmode:
		 GPS_OUT_IMGINFO				(0)
		 GPS_OUT_SINGLE 				(1)
		 GPS_OUT_DUPLEX 				(2)
	
		 if  Front cover sheet is set, 
		 1. if print mode is simplex, outmode is set to GPS_OUT_SINGLE, fronntcover could be blank or one-side print.
		 2. if print mode is duplex, outmode is set to GPS_OUT_DUPLEX, fronntcover could be blank or one-side print or both side print
	
		 if  Front cover sheet is OFF,
		 by default outmode is set to GPS_OUT_IMGINFO.
	*======================================================================*/
	if(param.Cover.front == GPS_PENV_VAL_INT_FRONTCOVERPRINT_OFF)
			param.outmode = GPS_OUT_IMGINFO;
	
	else if(pstJob->bDuplex == FALSE && (param.Cover.front == GPS_PENV_VAL_INT_FRONTCOVERPRINT_BLANK || 
		param.Cover.front == GPS_PENV_VAL_INT_FRONTCOVERPRINT_SIMPLEXCOPY))
			param.outmode = GPS_OUT_SINGLE;
	
	else if(pstJob->bDuplex == TRUE && 
		(param.Cover.front == GPS_PENV_VAL_INT_FRONTCOVERPRINT_BLANK || 
		 param.Cover.front == GPS_PENV_VAL_INT_FRONTCOVERPRINT_SIMPLEXCOPY ||
		 param.Cover.front == GPS_PENV_VAL_INT_FRONTCOVERPRINT_DUPLEXCOPY))
			param.outmode = GPS_OUT_DUPLEX;
 
	param.duplexmode = GPS_DUPLEXMODE_ON;
	param.face_up = GPS_FACEUP_ON;
	param.finish = GPS_FINISH_OFF;
	param.flag[0] = GPS_PARAM_SHM_QTY;
	param.flag[1] = GPS_PARAM_SHM_MAGAZINE;
	param.qty = 1;
	param.limitless_exit = GPS_LIMITLESS_OFF;
	 
   	
  }
}

int	updatePclFontCountSD()
{
	
	int status       = 1;
	long fontCount   = 0;
	DIR * dirp;
	struct dirent  *entry;
	gps_hddinfo2_t hddinfo2;
	char	path[GPS_MAX_HDD_PATH_LEN];
	
	int dirCount;

	gpsGetHddInfo2( gps_client, GPS_SD_DOWNLOAD, &status, &hddinfo2 );
	if (status == 0 && hddinfo2.stat == GPS_HDDSTAT_READY) 
	{


		for(dirCount = 0; dirCount < FONT_DIR_COUNT; dirCount++)
			{
			   strcpy(path,hddinfo2.path);
			
				if(dirCount == 0)
				{
					strcat(path,DIR_PCL_FONT);
				}
				else if(dirCount == 1)
				{
					strcat(path,DIR_PCL_TTFONT);
				}

				printf("\nSD installed and can be used\n");
				dirp = opendir(path); /* There should be error handling after this */
				if(dirp == NULL)
				{
					printf("FAILED TO OPEN THE FONT DIRECTORY");
					break;
				}
				while ((entry = readdir(dirp)) != NULL) 
					{
						if (!strncmp(entry->d_name, ".",1)) /* checking the first character of the file name*/
						{
								continue;    /* skip self and parent */
						}
			
						fontCount++;
					}
				closedir(dirp);
				
			}
			printf("\n Total SD fontCount = %ld\n", fontCount);
		}

	return fontCount;

}


int	updatePclFontCountHDD()
{


	int status   = 1;
	bool HddEnableFlag    = FALSE;
	bool HddSupportedFlag = FALSE;
	bool HddErrFlag       = FALSE;
	long fontCount        = 0;
	gps_hddinfo2_t hddinfo2;
	DIR * dirp;
	char	path[GPS_MAX_HDD_PATH_LEN];
	struct dirent * entry;
	int dirCount;

	do
	{

		gpsGetHddInfo2( gps_client, GPS_HDD_DOWNLOAD, &status, &hddinfo2 );
		if(status == 0 && hddinfo2.stat == GPS_HDDSTAT_READY)
		{
			printf("\nHard Drive is installed\n");
			HddEnableFlag = TRUE;
		}
		else
		{
			printf("\n Hard Drive is not installed\n");
			break;
		}

		gps_sysinfo_t gpsSysInfo;
		gpsGetSysInfo(gps_client, &gpsSysInfo);
		HddSupportedFlag = gpsSysInfo.function & (GPS_SYS_FUNC_HDD | GPS_SYS_FUNC_HDD_FS);

		gps_prtstatus_t prtstatus;
		gpsGetPrtStatus(gps_client, &prtstatus, GPS_NOTIFY_CHANGE_OFF);
		HddErrFlag = prtstatus.function_disable & (GPS_SYS_FUNC_HDD | GPS_SYS_FUNC_HDD_FS);

		if((HddSupportedFlag) && (!HddErrFlag))
		{
			printf("\nHard Drive can be used\n");
			
			for(dirCount = 0; dirCount < FONT_DIR_COUNT; dirCount++)
			{
			   strcpy(path,hddinfo2.path);
			
				if(dirCount == 0)
				{
					strcat(path,DIR_PCL_FONT);
				}
				else if(dirCount == 1)
				{
					strcat(path,DIR_PCL_TTFONT);
				}
							
				dirp = opendir(path); /* There should be error handling after this */
				if(dirp == NULL)
				{
					printf("FAILED TO OPEN THE FONT DIRECTORY");
					break;
				}
				while ((entry = readdir(dirp)) != NULL) 
				{
					if (!strncmp(entry->d_name, ".", 1)) /* checking the first character of the file name*/
					{
						continue;    /* skip self and parent */
					}
				
					fontCount++;
				}
				closedir(dirp);
			
				
			}
			
			printf("\n Total HDD fontCount = %ld\n", fontCount);
		}

	}while(0);

	return fontCount;
}

void Clean_exit()
{
#ifdef DEBUG_LOGS
	printf("\nClean_Exit() Called for REQ_Exit event\n");
#endif

	gwmsg_GpsEv_Req_Exit_t gpsReqExit;
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
	PMS_LeaveCriticalSection(g_csPageList);
	PMS_LeaveCriticalSection(g_csSocketInput);
	PMS_LeaveCriticalSection(g_csMemoryUsage);
						  
	PMS_DestroySemaphore(g_semCheckin);
	PMS_DestroySemaphore(g_semPageQueue);
	PMS_DestroySemaphore(g_semTaggedOutput);
	PMS_DestroySemaphore(g_semPageComplete);
						
	PMS_DestroyCriticalSection(g_csPageList);
	PMS_DestroyCriticalSection(g_csSocketInput);
	PMS_DestroyCriticalSection(g_csMemoryUsage);
	
#ifdef PMS_MEM_LIMITED_POOLS
	/* check if memory stat should be displayed */
	if (g_bDebugMemory)
		DisplayMemStats();
									
	CheckMemLeaks();
#endif

			
	gpsWkFree(gps_client,memaddr);
#ifdef DEBUG_LOGS
	printf("\n calling gpsWkFree...\n");
#endif			
	/* The OIL thread should not take make time to exit, so we'll allow it 1 second */
	PMS_CloseThread(pOILThread, 1000);
	pOILThread = NULL;
			
	/* The PMS output thread may have to wait for mechanical hardware before if finishes,
	and so we'll allow longer for the thread to close cleanly */
	PMS_CloseThread(pPMSOutThread, 5000);
	pPMSOutThread = NULL;
			
	/* Cleanup and free input modules */
	/*PMS_IM_Finalize(); TODO*/
						
#ifdef PMS_OIL_MERGE_DISABLE
	/* Shut down file system */
	PMS_FS_ShutdownFS();
#endif
	gpsReqExit.pid = (pid_t)getpid();
	gpsInterpNotifyExit(gps_client, gpsReqExit.pid); 
#ifdef DEBUG_LOGS
	printf("\n calling gpsInterpNotifyExit...\n");
#endif
	gpsPmExit();

#ifdef DEBUG_LOGS
	printf("\n calling gpsPmExit...\n");
#endif

	gpsClose(gps_client, gps_shdm_addr);
#ifdef DEBUG_LOGS
	printf("\n calling gpsClose...\n");
#endif
	exit(0);
}

int GWID_Event_Handler(void *cl, gwmsg_t *m)
{
	static gwmsg_GpsEv_Req_Proc_Data_t *processJobData = NULL;
	gwfcall_gpsFrameCancel_t gpsFrmCncl;
	gwmsg_GpsEv_Req_Testprint_t	*msg;
    int retgps;
	long fontCountHDD = 0, fontCountSD = 0;
	int  penv_handle,ret;
#ifdef DEBUG_LOGS	
	printf("\n ******************************************************\n");				
	printf("\n Event handling.....\n");
	printf("\n ******************************************************\n");
#endif	
	
    switch(m->type)
    {
#ifdef DEBUG_LOGS	
		printf("\n ******************************************************\n");				
		printf("\n gpsevent is %d.....\n",m->type);
		printf("\n ******************************************************\n");
#endif		
        case GWID_GpsEv_Req_Proc_Data: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Job Process Request event occurred successfully.....\n");
			printf("\n ******************************************************\n"); 		
#endif			


			strcpy(buffer1,"\0");
			strcpy(buffer2,"\0");
			strcpy(buffer3,"\0");
			strcpy(buffer4,"\0");
			strcpy(buffer5,"\0");

			JobEndFlag = 0;
			ProcessAllPages = 0;
			PrintUptoLastPage = 0;
			StopPrinting  = 0;
			PageCount = 0;
			processJobData = ( gwmsg_GpsEv_Req_Proc_Data_t	*)m;

				while( online_flag == FALSE && g_SystemState.eCurrentState != OIL_Sys_Active)
				{										
					/* wait */
#ifdef DEBUG_LOGS					
					printf("\n ******************************************************\n");				
					printf("\n System is offline: Job Process Request will be accepted when system is online.....\n");
					printf("\n ******************************************************\n");
					printf("\n *********waiting....for....job processing");
					/* lock */
					printf("\n *************waiting lock:1");
#endif					
					pthread_mutex_lock(&reqp_mutex);
					pthread_cond_wait(&reqp_online_cond, &reqp_mutex);
#ifdef DEBUG_LOGS					
					printf("\n *************waiting:2");
#endif					
					/* unlock */
					pthread_mutex_unlock(&reqp_mutex);
#ifdef DEBUG_LOGS					
					printf("\n *************waiting unlock:3");
#endif

				}
#ifdef DEBUG_LOGS				
			printf("\n ******************************************************\n");				
			printf("\n System is online: Job Process Request event accepted.....\n");
			printf("\n ******************************************************\n");	
#endif			
			gpsJobId = processJobData->ujobid;
			gpsPDLType=current_pdlid=( OIL_eTyPDLType )processJobData->pdl_id; /*VENKAT ADDED*/
			job_hostid_in = processJobData->hostid_in;
			job_hostid_out = processJobData->hostid_out;
			/*Get_Data_From_GPS(hostid_in,hostid_out,jobid); */
			 retgps=Get_Data_From_GPS();
			g_jobAvailable=1;
			first_job_req_proc = FALSE;
			break;

		case GWID_GpsEv_Req_Cancel_Data: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Job Cancel Request event occurred successfully.....\n");
			printf("\n ******************************************************\n");
#endif			
			if(g_pstCurrentJob != NULL)
			{
				event_Cancel_flag = TRUE;
				if(check_online_flag == TRUE)
				{
					check_online_flag = FALSE;
				}
				processJobData->do_cancel = 1;
				g_SystemState.bJobCancelReq = TRUE;
				processJobData = NULL;
				if(event_Exit_flag == TRUE)
				{
#ifdef DEBUG_LOGS
	  		printf("\n\n...Terminating current PDL after cancelling of current job processing : REQ_EXIT event...\n\n");
#endif				
					Clean_exit();
				}
			}
			break;
							
		case GWID_GpsEv_Notify_Offline: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies offline to PDL event occurred successfully.....\n");
			printf("\n ******************************************************\n");	
#endif			
			online_flag = FALSE;
			if(g_pstCurrentJob != NULL)
			{
				if(check_online_flag == FALSE)
				 {
				 		check_online_flag = TRUE;
#ifdef DEBUG_LOGS
	  					printf("\n...OFFLINE_EVENT : Job paused...\n");
#endif
				 }
			}
			g_SystemState.eCurrentState = OIL_Sys_Inactive;
			gpsInterpNotifyOffline(gps_client);
			break;
			
		case GWID_GpsEv_Notify_Online: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies online to PDL event occurred successfully.....\n");
			printf("\n ******************************************************\n");
#endif			

			if(first_job_req_proc == FALSE || g_SystemState.eCurrentState == OIL_Sys_Inactive)
			{
#ifdef DEBUG_LOGS			
				printf("\n *************Online lock:1");
#endif


				pthread_mutex_lock(&reqp_mutex);
#ifdef DEBUG_LOGS				
				printf("\n *************Online conditional waiting:2");
#endif

				pthread_cond_signal(&reqp_online_cond);
				pthread_mutex_unlock(&reqp_mutex);
#ifdef DEBUG_LOGS				
				printf("\n *************Online unlock:3");
#endif

			}
			online_flag = TRUE;								
			if(g_pstCurrentJob != NULL)
			{
				if(check_online_flag == TRUE)
					{
						check_online_flag = FALSE;
#ifdef DEBUG_LOGS
				  		printf("\n...ONLINE_EVENT : Job resumed...\n");
#endif
					}
			}
			g_SystemState.eCurrentState = OIL_Sys_Active;
			gpsInterpNotifyOnline(gps_client);
			break;
			
		case GWID_GpsEv_Req_Exit: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to terminate PDL event occurred successfully.....\n");
			printf("\n ******************************************************\n");
#endif			
			if( g_pstCurrentJob != NULL)
			{
				event_Exit_flag = TRUE;
#ifdef DEBUG_LOGS				
				printf("\n....Job processing...please wait...\n");
#endif
			}

			if(g_pstCurrentJob == NULL && event_Exit_flag == FALSE)
			{
#ifdef DEBUG_LOGS
	  		printf("\n\n...Terminating current PDL : REQ_EXIT event...\n\n");
#endif			
				Clean_exit();
			}
            break;
			
		case GWID_GpsEv_Req_Testprint: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to print a test page event occurred successfully.....\n");
			printf("\n ******************************************************\n");	
#endif			
			msg = ( gwmsg_GpsEv_Req_Testprint_t	*)m;
			jobid = msg->ujobid;
			g_tJob.eTestPage = OIL_TESTPAGE_PCL;
			break;
			
		case GWID_gpsColor_gamReq: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to recalculate gamma data event occurred successfully.....\n");
			printf("\n ******************************************************\n");	
#endif			
			gpsColor_gamUpd(gps_client);
			get_gamma_info_di_GPS(devinfo);
            break;
			
		case GWID_GpsEv_TrayInfo: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies the change of input tray information event occurred successfully.....\n");
			printf("\n ******************************************************\n");
#endif
			GPS_Tray_notify_flag = TRUE;
			if(GPS_TrayInfo() < 0 )
  			{
#ifdef DEBUG_LOGS			  			
				printf("GPS_TrayInfo() Failed.\n");
#endif
				return -1;
  			}
			//does this needed to update media handling logic???
			ret =PrintSysReinitTrayInfo();
			if(ret == -1)
			{
#ifdef DEBUG_LOGS
				printf("GPS_TrayInfo() Failed.\n");
#endif
				return -1;
			}
			break;
			
		case GWID_GpsEv_BinInfo: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies the change of output bin information event occurred successfully.....\n");
			printf("\n ******************************************************\n");
#endif			
			GPS_Bin_notify_flag = TRUE;
			if(GPS_BinInfo() < 0 )
  			{
#ifdef DEBUG_LOGS			  			
				printf("GPS_BinInfo() Failed.\n");
#endif				
				return -1;
  			}
			//does this needed to update media handling logic???
			ret =PrintSysReinitBinInfo();
			if(ret == -1)
			{
#ifdef DEBUG_LOGS
				printf("GPS_TrayInfo() Failed.\n");
#endif
				return -1;
			}
			break;
			
		case GWID_GpsEv_Req_Exit_Paper: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Form feed request event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
#endif
			event_Exit_Paper_flag = TRUE;
			processJobData->do_cancel = 1;
			g_SystemState.bJobCancelReq = TRUE;
			processJobData = NULL;
            break;
			
		case GWID_GpsEv_Req_PclFontCount: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to provide information on Font Count event occurred successfully.....\n");
			printf("\n ******************************************************\n");
#endif			
			fontCountHDD = updatePclFontCountHDD();
			fontCountSD  = updatePclFontCountSD();
			penv_handle = GPS_PenvOpen( gps_client, GPS_PENV_NAME_PCL, strlen(GPS_PENV_NAME_PCL)+1);
	
			GPS_PenvSetDefValue(gps_client, penv_handle, GPS_PENV_VAR_ID_FONTDOWNLOADEDONHDD, fontCountHDD);
	
			GPS_PenvSetDefValue(gps_client, penv_handle, GPS_PENV_VAR_ID_FONTDOWNLOADEDONSD, fontCountSD);
	
			gpsPenvClose(gps_client, penv_handle);
			/* Update the GPS that font count updation is over */
			gpsPenvFinishPclFontCount(gps_client);
            break;
			
		case GWID_GpsEv_PrtStatus: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies the change of information on Printer status event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
#endif			
            break;
			
		case GWID_GpsEv_Interp_Pause_Req: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to pause processing event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
#endif			
			if(g_pstCurrentJob != NULL)
			{
				event_Pause_flag = TRUE;
#ifdef DEBUG_LOGS
				  		printf("\n...PAUSE_EVENT : Job paused...\n");
#endif					
				//if(g_pstCurrentPage)
				//{
					gpsInterpPauseAns(&gps_client,gpsJobId,GPS_INTERP_PAUSE_NG,GPS_INTERP_STATE_PROCESSING);
					//assuming it will return after above call. ???once the page completes and issue this event again???. need to find what it will do in GPS????
				//}
			}
			else
#ifdef DEBUG_LOGS				
				printf("\n ******job not yet started or job already completed");
#endif
            break;
			
		case GWID_GpsEv_Interp_Resume_Req: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to resume processing event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
#endif			
			if(g_pstCurrentJob != NULL)
			{
				event_Pause_flag = FALSE;
#ifdef DEBUG_LOGS
				  		printf("\n...RESUME_EVENT : Job resumed...\n");
#endif				
				//if(g_pstCurrentPage)
				//{
					gpsInterpResumeAns(&gps_client,gpsJobId,GPS_INTERP_RESUME_OK,GPS_INTERP_STATE_WAITING);
					//assuming it will return after above call. ???once the page completes and issue this event again???. need to find what it will do in GPS????
				//}
			}
#ifdef DEBUG_LOGS				
				printf("\n ******job not yet started or job already completed");
#endif
			break;
		case GWID_GpsEv_Req_Program: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests operation related to program event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
#endif			
            break;
			
		case GWID_GpsEv_Notify_Prime_Reset: 
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies prime reset event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
#endif			
            break;
			
		case GWID_GpsEv_Auth_Res: 		
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies authentication result event occurred successfully.....\n");		
			printf("\n ******************************************************\n");							
#endif			
            break;
			
		case GWID_GpsPage_TrayRequest2_Res: 			
#ifdef DEBUG_LOGS			
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies tray request result event occurred successfully.....\n");	
			printf("\n ******************************************************\n");							
#endif
            break;
    }
	return 0;
}

