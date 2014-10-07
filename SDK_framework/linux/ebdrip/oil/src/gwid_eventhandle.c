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
#include "gps_func.h"
#include "pthread.h"

  extern char *gps_shdm_addr;
  extern caddr_t memaddr;
  extern bool g_bJobSucceeded;
  extern bool event_Exit_flag;

  static int			  reqint;
  static pthread_mutex_t  reqp_mutex;
  static pthread_cond_t   reqp_cond, reqp_online_cond;

  extern void * pPMSOutThread;
  extern void * pOILThread;

  extern int g_nInputTrays;
  extern PMS_TyTrayInfo * g_pstTrayInfo;
  extern int g_nOutputTrays;
  extern PMS_TyOutputInfo * g_pstOutputInfo;

  extern void *g_semTaggedOutput; /* Semaphore for keeping start/end tag with the actual message */
  extern  void *g_semCheckin;	   /* Semaphore to for counting page checkins */
  extern  void *g_semPageQueue;    /* Semaphore to syncronize between engine printing out page and RIP */
  extern  void *g_semTaggedOutput; /* Semaphore for keeping start/end tag with the actual message */
  extern  void *g_semPageComplete; /* Semaphore to syncronize submission of band packets from OIL to PMS */
  extern  void *g_csPageList;	   /* Critical section for thread-safe accessing of g_pstPageList */
  extern  void *g_csMemoryUsage;   /* Critical section for thread-safe accessing of nValidBytes in sockets */
  extern  void *g_csSocketInput;   /* Critical section for thread-safe accessing of l_tPMSMem */

  static bool	first_job_req_proc = TRUE;
  static bool online_flag = TRUE;
  int		job_hostid_in = -1;	
  int		job_hostid_out = -1;	
  int       jobid;
  extern   int       gpsJobId, gpsPDLType;
  BOOL 		PageDuplex;
  unsigned int    g_JobStart; 	/* This variable can be used to get the information can be used to skip pages from parsing(Set Start page)	*/
  unsigned int    g_JobEnd;		/* This variable can be used to get the information can be used to skip pages from parsing(Set End Page)	*/
  extern int g_jobAvailable;
  extern gwmsg_client_t *gps_client;

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
#define GPS_GETDEFAULTVAL_FAILED (0) /*GPS_PenvGetDefValue() call is failed so for PCL, Vaiable update is not required*/

int Get_Data_From_GPS()
{
    int GPSGetPaperInfoRetVal;
    int GPSPdlTableval;
    int GPSGetPrtStatus2val;
    int gps_notify=0;
    int ret;
    int GPSBitSWRetVal = 0;
    int GPSGetModelInfoRetVal;
    int GPSGetHddInfo2RetVal;
    int GPSPlotPrepRetVal;
    long pdl_offset; int pdl_num ;
    int prt_res;
    int hdd_status;
    char * modelinfovalue;
    simhandle_t *hsim;
    gps_prtstatus2_t prtStatus;
    varvalue_t gps_paperId;
    gps_hddinfo2_t hddinfo;	
    gps_plotprepareparam_t plotPrepare;    

    gps_pageparam_shm_t param;
    int GPSPlotSetPageParamShmretval;
    int PlotSet_result;

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

	GPSGetHddInfo2RetVal = GPS_gpsGetHddInfo2(GPS_HDD_TMP, hddinfo );
	
    if(GPSGetHddInfo2RetVal == 0 ) 
		printf("GPS_gpsGetHddInfo2 is success\n");
	else 
	    printf("GPS_gpsGetHddInfo2 is failed\n");

    /*************Call to gpsPlotPrepare*************************************************/
	
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
	param.Cover.mode = GPS_COVER_OFF; 
	param.Cover.front = GPS_COVER_BLANK;
	param.Cover.back = GPS_COVER_BLANK;
	param.Cover.fcover_tray = 0;
	param.Cover.bcover_tray = 0;
	param.duplexmode = GPS_DUPLEXMODE_ON;
	param.face_up = GPS_FACEUP_ON;
	param.finish = GPS_FINISH_OFF;
	param.flag[0] = GPS_PARAM_SHM_QTY;
	param.flag[1] = GPS_PARAM_SHM_MAGAZINE;
	param.qty = 1;
	param.limitless_exit = GPS_LIMITLESS_OFF;
	 
    GPSPlotSetPageParamShmretval = GPS_PlotSetPageParamShm(gps_client, PlotSet_plotid, &param, &PlotSet_result);
	if(PlotSet_result == 0 )
	{
		printf("GPS_PlotSetPageParamShm : Success\n");
	}
    else
    {
		printf("GPS_PlotSetPageParamShm : Failed\n");
	}


        return 0;
}

void Get_Env_var_From_GPS(OIL_TyJob *pstJob)
{

    unsigned long offset = 0;
    int GPS_GetPdlPrintConditionShmRetVal;
    int GPSPenvOpenretval;
    int status;
    int retGPSPenvGetVal;
    int GPSPenvGetDefListRetVal;
    long penv_val;
    long gps_value;
	long gps_var = 8;
		
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
     GPS_PmDispSetEmulation(SET_DISP, SET_DISP, SET_DISP, "PCL5e");

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
				pstJob->uCopyCount=penv_val;				
            }
			
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
				
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
				
				pstJob->uPagesToPrint = penv_val;
				
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        
		gps_var = GPS_PENV_VAR_ID_PAPER;
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
				printf("pstJob->tCurrentJobMedia.ePaperSize = [%d]\n",pstJob->tCurrentJobMedia.ePaperSize);
	
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

        
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
					pstJob->uXResolution = penv_val;
					pstJob->uYResolution = penv_val;
				}
			}
			else
			{
				printf("Environment Def List: failed\n");
			}
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
					pstJob->uXResolution = penv_val;
					pstJob->uYResolution = penv_val;
				}
				printf("penv_val = [%d]\n",penv_val);
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
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
       printf("gps_value = [%d]\n",gps_value);
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
				pstJob->uXResolution = penv_val;
				printf(" pstJob->uXResolution= [%d]\n",pstJob->uXResolution);
				pstJob->uYResolution = penv_val;
				printf(" pstJob->uYResolution= [%d]\n",pstJob->uYResolution);
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
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
				pstJob->uXResolution = penv_val;
				pstJob->uYResolution = penv_val;
            }
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
		gps_var = GPS_PENV_VAR_ID_FRONTCOVERPRINT;//////////PDF  Specific///////////////
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

		gps_var = GPS_PENV_VAR_ID_FRONTCOVERPRINTTRAY;
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
		gps_var = GPS_PENV_VAR_ID_BACKCOVERPRINT;
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%d]\n",gps_value);
		
        
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
			printf("gps_value = [%d]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
			
	}
	
		gps_var = GPS_PENV_VAR_ID_TRAY;
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
				pstJob->tCurrentJobMedia.uInputTray = penv_val;
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
				
				
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);


		gps_var = GPS_PENV_VAR_ID_RENDERMODE;
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
				if(penv_val == GPS_PENV_VAL_INT_RENDERMODE_COLOR) 
				{
					pstJob->eRenderMode = PMS_RenderMode_Color;
				}
				else if(penv_val == GPS_PENV_VAL_INT_RENDERMODE_GRAYSCALE)
				{
					pstJob->eRenderMode = PMS_RenderMode_Grayscale;
				}
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);


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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);


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
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
				
				
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);


		gps_var = GPS_PENV_VAR_ID_BINDING;////////////////NEEDS TO BE CHECKED///////////////////////
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
				pstJob->uBookletType = penv_val;
				printf("pstJob->uBookletType= [%d]\n",pstJob->uBookletType);
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);


	gps_var = GPS_PENV_VAR_ID_DUPLEX;
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

		gps_var = GPS_PENV_VAR_ID_ECONOMODE;////////////////////////PENDING FOR CLARIFICATION////////////////
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
				

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
            }
			pstJob->uRIPDepth=penv_val;
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
			
        }
        else
		{
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

		gps_var = GPS_PENV_VAR_ID_WHITEPAPERSUPPRESS;
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
				pstJob->bSuppressBlank = TRUE;
				else
				pstJob->bSuppressBlank = FALSE;
				printf("pstJob->bSuppressBlank= [%d]\n",pstJob->bSuppressBlank);
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
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
			printf("penv_val = [%d]\n",penv_val);
		}
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
		}
		else
		{
            printf("Environment Def List: failed\n");
		}
		printf("gps_value = [%d]\n",gps_value);
				
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
				printf("g_JobEnd = [%d]\n",g_JobEnd);	
			}
			printf("penv_val = [%d]\n",penv_val);
		}
		else
		{
            printf("Environment Def List: failed\n");
		}
		printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
		    }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
							
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
			
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
        printf("gps_value = [%d]\n",gps_value);
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);	

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
				
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
				
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
	

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
			
			
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
			printf("penv_val = [%d]\n",penv_val);
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
            }
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
					
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
					
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
						
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
			
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
		
			
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
		{
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
			

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
	     
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
		}
        printf("gps_value = [%d]\n",gps_value);
        
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
			printf("penv_val = [%d]\n",penv_val);
        }
		else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
        
		
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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
        printf("gps_value = [%d]\n",gps_value);
		
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
        printf("gps_value = [%d]\n",gps_value);
	#endif /*GPS_PenvGetDefValue() call is failed so for PCL, Vaiable update is not required*/
        

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
			printf("penv_val = [%d]\n",penv_val);
        }
        else
        {
            printf("Environment Def List: failed\n");
        }
		printf("gps_value = [%d]\n",gps_value);
		
		GPS_PenvClose(gps_client, GPSPenvOpenretval);
	}


int	updatePclFontCountSD()
{
	int i;
	int status       = 1;
	long fontCount   = 0;
	DIR * dirp;
	struct dirent  *entry;
	gps_hddinfo2_t hddinfo2;

	gpsGetHddInfo2( gps_client, GPS_SD_DOWNLOAD, &status, &hddinfo2 );
	if (status == 0 && hddinfo2.stat == GPS_HDDSTAT_READY) 
	{

		printf("\nSD installed and can be used\n");
		dirp = opendir(hddinfo2.path); /* There should be error handling after this */
		while ((entry = readdir(dirp)) != NULL) 
		{
			if (!strncmp(entry->d_name, ".",1)) /* checking the first character of the file name*/
			{
				i = fontCount;
				i++;
				continue;    /* skip self and parent */
			}
			
			fontCount++;
		}
		closedir(dirp);
		printf("\n SD fontCount = %d\n", fontCount);
	}

	return fontCount;

}


int	updatePclFontCountHDD()
{
	int i;
	unsigned int status   = 1;
	bool HddEnableFlag    = FALSE;
	bool HddSupportedFlag = FALSE;
	bool HddErrFlag       = FALSE;
	long fontCount        = 0;
	gps_hddinfo2_t hddinfo2;
	DIR * dirp;
	struct dirent * entry;

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
		GPS_GetSysInfo(gps_client, &gpsSysInfo);
		HddSupportedFlag = gpsSysInfo.function & (GPS_SYS_FUNC_HDD | GPS_SYS_FUNC_HDD_FS);

		gps_prtstatus_t prtstatus;
		gpsGetPrtStatus(gps_client, &prtstatus, GPS_NOTIFY_CHANGE_OFF);
		HddErrFlag = prtstatus.function_disable & (GPS_SYS_FUNC_HDD | GPS_SYS_FUNC_HDD_FS);

		if((HddSupportedFlag) && (!HddErrFlag))
		{
			printf("\nHard Drive can be used\n");
			dirp = opendir(hddinfo2.path); /* There should be error handling after this */
			while ((entry = readdir(dirp)) != NULL) 
			{
				if (!strncmp(entry->d_name, ".", 1)) /* checking the first character of the file name*/
				{
					i = fontCount;
					i++;
					continue;    /* skip self and parent */
				}
				
				fontCount++;
			}
			closedir(dirp);
			printf("\n HDD fontCount = %d\n", fontCount);
		}

	}while(0);

	return fontCount;
}

void Clean_exit()
{
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

			
	gpsWkFree(&gps_client,memaddr);
	printf("\n calling gpsWkFree...\n");
			
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
	gpsInterpNotifyExit(&gps_client, gpsReqExit.pid); 
	printf("\n calling gpsInterpNotifyExit...\n");
	gpsPmExit();
	printf("\n calling gpsPmExit...\n");
	gpsClose(&gps_client, gps_shdm_addr);
	printf("\n calling gpsClose...\n");
	exit(0);
}

int GWID_Event_Handler(void *cl, gwmsg_t *m)
{
	static gwmsg_GpsEv_Req_Proc_Data_t *processJobData = NULL;
	gwfcall_gpsPlotCancel_t gpsPltCncl;
	gwfcall_gpsFrameCancel_t gpsFrmCncl;
	gwmsg_GpsEv_Req_Exit_t gpsReqExit;
	gwmsg_GpsEv_Req_Testprint_t	*msg;
    int retgps;
	long fontCountHDD = 0, fontCountSD = 0;
	int  penv_handle;
	printf("\n ******************************************************\n");				
	printf("\n Event handling.....\n");
	printf("\n ******************************************************\n");
	
    switch(m->type)
    {
	
		printf("\n ******************************************************\n");				
		printf("\n gpsevent is %d.....\n",m->type);
		printf("\n ******************************************************\n");
        case GWID_GpsEv_Req_Proc_Data: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Job Process Request event occurred successfully.....\n");
			printf("\n ******************************************************\n"); 		
			
			processJobData = ( gwmsg_GpsEv_Req_Proc_Data_t	*)m;

				while( online_flag == FALSE && g_SystemState.eCurrentState != OIL_Sys_Active)
				{										
					/* wait */
					printf("\n ******************************************************\n");				
					printf("\n System is offline: Job Process Request will be accepted when system is online.....\n");
					printf("\n ******************************************************\n");
					printf("\n *********8 : waiting....for....job processing");
					/* lock */
					printf("\n *************waiting lock:1");
					pthread_mutex_lock(&reqp_mutex);
					pthread_cond_wait(&reqp_online_cond, &reqp_mutex);
					printf("\n *************waiting:2");
					/* unlock */
					pthread_mutex_unlock(&reqp_mutex);
					printf("\n *************waiting unlock:3");
				}
				
			printf("\n ******************************************************\n");				
			printf("\n System is online: Job Process Request event accepted.....\n");
			printf("\n ******************************************************\n");	
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
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Job Cancel Request event occurred successfully.....\n");
			printf("\n ******************************************************\n");
			if(g_pstCurrentJob != NULL)
			{
				processJobData->do_cancel = 1;
			   (void)gpsInterpNotifyState(&gps_client, GPS_INTERP_STATE_FLUSHING);
				g_SystemState.bJobCancelReq = TRUE;
				OIL_JobCancel();

				#ifdef PMS_OIL_MERGE_DISABLE_MEM
				OSFree(g_pstCurrentJob,PMS_MemoryPoolPMS);
				#else
				mfree(g_pstCurrentJob);
				#endif
				frameID = gpsFrmCncl.frameid; 
				gpsFrameCancel(&gps_client, frameID);
				plotID = PlotSet_plotid; /*gpsPltCncl.plotid;*/
				gpsPlotCancel(&gps_client, plotID);
				gpsInterpFinishProcData(&gps_client, gpsJobId, GPS_INTERP_FIN_CANCEL, 0);
				processJobData = NULL;
				if(event_Exit_flag == TRUE)
					Clean_exit();
			}
			break;
							
		case GWID_GpsEv_Notify_Offline: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies offline to PDL event occurred successfully.....\n");
			printf("\n ******************************************************\n");	
			online_flag = FALSE;
			g_SystemState.eCurrentState = OIL_Sys_Inactive;
			gpsInterpNotifyOffline(&gps_client);
			break;
			
		case GWID_GpsEv_Notify_Online: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies online to PDL event occurred successfully.....\n");
			printf("\n ******************************************************\n");

			if(first_job_req_proc == FALSE || g_SystemState.eCurrentState == OIL_Sys_Inactive)
			{
				printf("\n *************Online:1");
				pthread_mutex_lock(&reqp_mutex);
				printf("\n *************Online:2");
				pthread_cond_signal(&reqp_online_cond);
				pthread_mutex_unlock(&reqp_mutex);
				printf("\n *************Online:3");
			}
			online_flag = TRUE;								
			g_SystemState.eCurrentState = OIL_Sys_Active;
			gpsInterpNotifyOnline(&gps_client);
			break;
			
		case GWID_GpsEv_Req_Exit: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to terminate PDL event occurred successfully.....\n");
			printf("\n ******************************************************\n");	
			if(g_SystemState.eCurrentState == OIL_Sys_JobActive)
			{
				if( g_pstCurrentJob != NULL)
				{
					event_Exit_flag = TRUE;
					printf("\n....Job processing...please wait...\n");
				}
			}

			if(g_pstCurrentJob == NULL && event_Exit_flag == FALSE)
			{
				Clean_exit();
			}
            break;
			
		case GWID_GpsEv_Req_Testprint: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to print a test page event occurred successfully.....\n");
			printf("\n ******************************************************\n");	
			msg = ( gwmsg_GpsEv_Req_Testprint_t	*)m;
			jobid = msg->ujobid;
			g_tJob.eTestPage = OIL_TESTPAGE_PCL;
			break;
			
		case GWID_gpsColor_gamReq: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to recalculate gamma data event occurred successfully.....\n");
			printf("\n ******************************************************\n");	
			
			gpsColor_gamUpd(&gps_client);
			get_gamma_info_di_GPS(devinfo);
            break;
			
		case GWID_GpsEv_TrayInfo: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies the change of input tray information event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
			PrintSysReinitTrayInfo();
			break;
			
		case GWID_GpsEv_BinInfo: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies the change of output bin information event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
			PrintSysReinitBinInfo();
			break;
			
		case GWID_GpsEv_Req_Exit_Paper: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Form feed request event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
            break;
			
		case GWID_GpsEv_Req_PclFontCount: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to provide information on Font Count event occurred successfully.....\n");
			printf("\n ******************************************************\n");
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
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies the change of information on Printer status event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
            break;
			
		case GWID_GpsEv_Interp_Pause_Req: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to pause processing event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
            break;
			
		case GWID_GpsEv_Interp_Resume_Req: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests to resume processing event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
            break;
			
		case GWID_GpsEv_Req_Program: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Requests operation related to program event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
            break;
			
		case GWID_GpsEv_Notify_Prime_Reset: 
			printf("\n ******************************************************\n");				
			printf("\n gpsOpen Notifies prime reset event occurred successfully.....\n");
			printf("\n ******************************************************\n");		
            break;
			
		case GWID_GpsEv_Auth_Res: 		
			printf("\n gpsOpen Notifies authentication result event occurred successfully.....\n");		
            break;
			
		case GWID_GpsPage_TrayRequest2_Res: 			
			printf("\n gpsOpen Notifies tray request result event occurred successfully.....\n");	
            break;
    }
	return 0;
}

