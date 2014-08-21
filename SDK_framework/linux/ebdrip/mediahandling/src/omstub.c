/**file
 * in group pcl5in
 * Contains stub implementations to update media attributes
 */
#include "pageprint.h"
#include "omstub.h"
#include <pthread.h>
typedef unsigned int u_int;
#include "gpssim.h"
#include "gps/gps_client.h"
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
#include "oil.h" 

extern gps_trayinfo_t *gpsTrayInfo;
extern gwmsg_client_t *gps_client ;
extern gps_sysinfo_t  sysinfo;
extern OIL_TyJob *g_pstCurrentJob;

OMenum OMGetCurrentInt(OMenum omvar, OMenum omsystem)
{
    OMenum xres, yres, bit;
    if (omsystem == 1)
    { 
        switch(omvar)
        {
           case XRES: xres = g_pstCurrentJob->uXResolution;  /*600; PCL default */
                      XRESOLUTION = xres;
                               return xres;
                               break;
           case YRES: yres = g_pstCurrentJob->uYResolution;  /*600; PCL default */
                      YRESOLUTION = yres;
                               return yres;
                               break;
           case OMBITSPERPIXEL: bit = 2; /*check bit value*/
                               return bit;
                               break;
           default: return 0; break;
         }
      }
}

OMEnum OMGetCurrentEnum(OMenum omvar, OMenum omsystem)
{
    /*int afour = 26;
    int letter = 2;*/
    OMEnum papersource, bypasstray, frontcoverprint, binding;
    if (omsystem == 1)
    { 
        switch(omvar)
        {
              case OMPAPERSRC: papersource = GetPaperSource();
                               return papersource;
                               break;

              case OMBYPASSTRAYSETTING: bypasstray = 0;
                                        return bypasstray;
                                        break;

              case OMFRONTCOVERPRINT:  frontcoverprint = 0;
			                           return frontcoverprint;
									   break;

              case OMBINDINGEDGE: binding = GetBinding();
                                  return binding;
                                  break;

              case OMTRAY1_SIZE:  return (search_path[0].om_size);
			                      break;

			  case OMTRAY2_SIZE:  return (search_path[1].om_size);
			                      break;

			  case OMTRAY1_MEDIATYPE: return (search_path[0].om_mediatype);
                                      break;

			  case OMTRAY2_MEDIATYPE: return (search_path[1].om_mediatype);
				                      break;
              default: return 0;
                       break;
        }
     }
}

OMEnum OMGetDefaultEnum(OMenum omvar, OMenum omsystem)
{
    OMEnum papersource, bypasstray, frontcoverprint, binding;
    if (omsystem == 1)
    { 
        switch(omvar)
        {
              case OMPAPERSRC: papersource = 7; /*By default Tray Auto*/
                               return papersource;
                               break;
              default: return 0; break;

        }
     }
}
Boolean OMGetCurrentBool(OMenum omvar, OMenum omtype)
{
    int duplex =0;
    if (omtype == 1)
    { 
        switch(omvar)
        {
            case OMAUTOTRAYCHANGE2: return FALSE; /* hardcoded */
			                        break;

			case OMTRAYSEARCHMODE:  return TRUE;  /*hardcoded */
			                        break;

			case OMDUPLEX: duplex = GetDuplex(); /*duplex off*/ 
		        	                return duplex;
                                    break;

            case LONGEDGEFEED: return 1;
                               break;

            default: return 0; break;
            
        }                          
     }

     if(omtype == 2)
     {
         switch(omvar)
         {
             case LONGEDGEFEED: return TRUE; /*Update binding value*/
                                break;
             default: break;
          }
      }
}


int PRpapertable(PAPERINFO *papers, int xres, int yres)
{
     /*PAPERINFO temppaper[2];*/
     temppaper[0].OMcode = PAPERSIZE_A4;
     temppaper[0].PCLpaperID = PMS_PCL5_A4;
     temppaper[1].OMcode = PAPERSIZE_LETTER;
     temppaper[1].PCLpaperID = PMS_PCL5_LETTER;
     papers = &temppaper;
     /*paper->OMcode = PAPERSIZE_LETTER;*/
     return 0;
}

int  PRpaperinfo(PAPERCODE paper, int xres, int yres)
{
    return PAPERSIZE_A4;
}

int update_TrayInfo_fromGPS()
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

    if( 0 != gpsGetSysInfo(gps_client, &sysinfo) )
    return -1;

  /*gps_trayinfo_t *gpsTrayInfo;*/
  gpsTrayInfo = (gps_trayinfo_t*) malloc(sysinfo.num_tray * sizeof(gps_trayinfo_t));
	
  if( -1 == gpsGetTrayInfo(gps_client, sysinfo.num_tray, gpsTrayInfo, &trayNum, GPS_NOTIFY_CHANGE_OFF) )
    return -1;
  /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 37
   gpsGetTrayInfo - page no 197*/
  for(nTrayIndex = 0; nTrayIndex < 5; nTrayIndex++)
  {
    switch(gpsTrayInfo[nTrayIndex].id)
	{
	  case 0:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_AUTO;
		break;
      case 1:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_TRAY1;
		break;
      case 2:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_TRAY2;
		break;
      case 3:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_TRAY3;
		break;
      default:
        search_path[nTrayIndex].om_source  = PMS_PCL5TRAY_MANUALFEED; 
		break;
		
		//Yet to map PMS_TRAY_BYPASS, PMS_TRAY_ENVELOPE
	}
		
	switch(gpsTrayInfo[nTrayIndex].p_size)
	{
	  case GPS_CODE_8Hx11:
	    search_path[nTrayIndex].om_size = PMS_PCL5_LETTER;
	    break;
	  case GPS_CODE_A4:
	     search_path[nTrayIndex].om_size = PMS_PCL5_A4;
	    break;
	  case GPS_CODE_8Hx14:
	     search_path[nTrayIndex].om_size = PMS_PCL5_LEGAL;
	    break;
	  case GPS_CODE_7Qx10H:
	     search_path[nTrayIndex].om_size = PMS_PCL5_EXE;
	    break;
	  case GPS_CODE_A3:
	     search_path[nTrayIndex].om_size = PMS_PCL5_A3;
	    break;
	  case GPS_CODE_11x17:
	     search_path[nTrayIndex].om_size = PMS_PCL5_TABLOID;
	    break;
	  case GPS_CODE_A5:
	     search_path[nTrayIndex].om_size = PMS_PCL5_A5;
	    break;
	  case GPS_CODE_A6:
	     search_path[nTrayIndex].om_size = PMS_PCL5_A6;
	    break;
	  case GPS_CODE_C5:
	     search_path[nTrayIndex].om_size= PMS_PCL5_C5_ENV;
	    break;
	  case GPS_CODE_DL:
	     search_path[nTrayIndex].om_size = PMS_PCL5_DL_ENV;
	    break;
	  case YET_TO_FIND_0:
	     search_path[nTrayIndex].om_size = PMS_PCL5_LEDGER;
	    break;
	  case YET_TO_FIND_2:
	     search_path[nTrayIndex].om_size = PMS_PCL5_OFUKU;
	    break;
	  case GPS_CODE_10x14:
	     search_path[nTrayIndex].om_size = PMS_PCL5_JISB4;
	    break;
	  case YET_TO_FIND_3:
	     search_path[nTrayIndex].om_size = PMS_PCL5_JISB5;
	    break;
	  case GPS_CODE_8Hx11T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_LETTER_R;
	    break;
	  case GPS_CODE_A4T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_A4_R;
	    break;
	  case GPS_CODE_8Hx14T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_LEGAL_R;
	    break;
	  case GPS_CODE_7Qx10HT:
	     search_path[nTrayIndex].om_size= PMS_SIZE_EXE_R;
	    break;
	  case GPS_CODE_A3T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_A3_R;
	    break;
	  case GPS_CODE_11x17T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_TABLOID_R;
	    break;
	  case GPS_CODE_A5T:
	    search_path[nTrayIndex].om_size = PMS_SIZE_A5_R;
	    break;
	  case GPS_CODE_A6T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_A6_R;
	    break;
	  case GPS_CODE_C5T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_C5_ENV_R;
	    break;
	  case GPS_CODE_DL_T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_DL_ENV_R;
	    break;
	  case YET_TO_FIND_4:
	     search_path[nTrayIndex].om_size = PMS_SIZE_LEDGER_R;
	    break;
	  case YET_TO_FIND_5:
	     search_path[nTrayIndex].om_size = PMS_SIZE_OFUKU_R;
	    break;
	  case GPS_CODE_10x14T:
	     search_path[nTrayIndex].om_size = PMS_SIZE_JISB4_R;
	    break;
	  case YET_TO_FIND_6:
	     search_path[nTrayIndex].om_size = PMS_SIZE_JISB5_R;
	    break;
	  case YET_TO_FIND_7:
	     search_path[nTrayIndex].om_size= PMS_SIZE_CUSTOM;
	    break;
	  default:
	     search_path[nTrayIndex].om_size = PMS_SIZE_DONT_KNOW;
	    break;
	}
	
	switch(gpsTrayInfo[nTrayIndex].p_kind)
	{
	  case DI_PAPER_NORMAL:
	     search_path[nTrayIndex].om_mediatype= PMS_TYPE_PLAIN;
	    break;
	  case DI_PAPER_BOND:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_BOND;
	    break;
	  case DI_PAPER_SPECIAL:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_SPECIAL;
	    break;
	  case DI_PAPER_GLOSSY:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_GLOSSY;
	    break;
	  case DI_PAPER_OHP:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_TRANSPARENCY;
	    break;
	  case DI_PAPER_RECYCLE:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_RECYCLED;
	    break;
	  case DI_PAPER_MIDDLETHICK:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_THICK;
	    break;
	  case DI_PAPER_ENVELOPE:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_ENVELOPE;
	    break;
	  case DI_PAPER_POSTCARD:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_POSTCARD;
	    break;
	  case DI_PAPER_THIN:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_THIN;
	    break;
	  case DI_PAPER_LABEL:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_LABEL;
	    break;
	  case DI_PAPER_PREPRINT:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_PREPRINTED;
	    break;
	  case DI_PAPER_LETTER_HEAD:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_LETTERHEAD;
	    break;
	  default:
	    search_path[nTrayIndex].om_mediatype = PMS_TYPE_DONT_KNOW;
	    break;
	}
	
    search_path[nTrayIndex].om_stat == gpsTrayInfo[nTrayIndex].status;	
	if(gpsTrayInfo[nTrayIndex].attr == GPS_TRAY_LOCKED)
    {
       search_path[nTrayIndex].om_lock = 1;
    }
    else
    {
       search_path[nTrayIndex].om_lock = 0;
    }
    printf("nTrayIndex = %d \n", nTrayIndex);
    printf("search_path[nTrayIndex].om_size = %d \n", search_path[nTrayIndex].om_size);
    printf("search_path[nTrayIndex].om_mediatype = %d \n", search_path[nTrayIndex].om_mediatype);	
	printf("search_path[nTrayIndex].om_source = %d \n", search_path[nTrayIndex].om_source);	
	printf("search_path[nTrayIndex].om_lock = %d \n", search_path[nTrayIndex].om_lock);	
	
  }
  
  //g_nInputTrays = sysinfo.num_tray;

		  
  return 0;
}

