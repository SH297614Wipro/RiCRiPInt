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
#include "mh_enum.h"


extern OMenum GetPaperSource();
extern OMenum GetPageSize();
extern int GetBinding();

extern long bits_pcl, autotray, bypass_tray, frontcover, frontcover_tray, traysearch, req_proc, edge;
extern gps_trayinfo_t *gpsTrayInfo;
extern gwmsg_client_t *gps_client ;
extern gps_sysinfo_t  sysinfo;
extern OIL_TyJob *g_pstCurrentJob;
extern search_path_t *search_path;
extern int g_nInputTrays;
extern PAPERINFO paper_table_variable_resolution[MAX_TABLE_SIZE];

simhandle_t *hsim=NULL;
varvalue_t val;

OMenum OMGetCurrentInt(OMenum omvar, OMenum omsystem)
{
    OMenum xres, yres, bit;
      if (omsystem == 1)
    { 
        switch(omvar)
        {
           case XRES: xres = g_pstCurrentJob->uXResolution; 
                      XRESOLUTION = xres;
                               return xres;
                               break;
           case YRES: yres = g_pstCurrentJob->uYResolution;  
                      YRESOLUTION = yres;
                               return yres;
                               break;
           case OMBITSPERPIXEL:// bit = 2; 
				//retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_BITSPERDOT", &val);
				//bit = val.u.id_value;
				bit = bits_pcl;
                               return bit;
                               break;
           default: return 0; break;
         }
      }
	  return 0;
}

OMEnum OMGetCurrentEnum(OMenum omvar, OMenum omsystem)
{
    /*int afour = 26;
    int letter = 2;*/
    OMEnum papersize, papersource, bypasstray, frontcoverprint, frontcoverprinttray, binding, traysearchmode, reqproc, staple, punch;
    if (omsystem == 1)
    { 
        switch(omvar)
        {
              case OMPAPERSRC: papersource = GetPaperSource();
                               return papersource;
                               break;
	      case OMPAPERSIZE: papersize = GetPageSize();
 				return papersize;
				break;

              case OMBYPASSTRAYSETTING: //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_GPSBYPASSTRAYMODESETTING", &val);
                                        //bypasstray = val.u.id_value;
					bypasstray = bypass_tray;
					return bypasstray;
                                        break;

              case OMFRONTCOVERPRINT:  //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_FRONTCOVERPRINT", &val);
				       //frontcoverprint = val.u.id_value;
					frontcoverprint = frontcover;
			                return frontcoverprint;
					break;
		case OMFRONTCOVERPRINTTRAY:  //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_FRONTCOVERPRINTTRAY", &val);
						//frontcoverprinttray = val.u.id_value;
						frontcoverprinttray = frontcover_tray;
						return frontcoverprinttray;
					     break;
		case OMTRAYSEARCHMODE:  //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_TRAYSEARCHMODE", &val);
					//traysearchmode = val.u.id_value;
					traysearchmode = traysearch;
					return traysearchmode;
					break;
		case OMREQPROCREASON:  //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_REQPROCREASON", &val);
					//reqproc = val.u.id_value;
					reqproc = req_proc;
					return reqproc;
					break;

              case OMBINDINGEDGE: binding = GetBinding();
                                  return binding;
                                  break;

              case OMSTAPLE:// retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_STAPLE", &val);
				//staple = val.u.id_value;
				staple = g_pstCurrentJob->uStapleType;
				return staple;
                             	break;
              case OMPUNCH: //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_PUNCH", &val);
			//	punch = val.u.id_value;
				punch = g_pstCurrentJob->uPunchType;
				return punch;
                            	break;

              default: return 0;
                       break;
        }
     }
	return 0;
}

OMEnum OMGetDefaultEnum(OMenum omvar, OMenum omsystem)
{
    OMEnum papersource;
//    OMEnum bypasstray, frontcoverprint, binding;
    if (omsystem == 1)
    { 
        switch(omvar)
        {
              case OMPAPERSRC: papersource = GetPaperSource(); 
                               return papersource;
                               break;
              default: return 0; break;

        }
     }
	return 0;
 
}
Boolean OMGetCurrentBool(OMenum omvar, OMenum omtype)
{
    int duplex =0;
    int autotraychange2, traysearchmode, edgetoedge;
    if (omtype == 1)
    { 
        switch(omvar)
        {
            case OMAUTOTRAYCHANGE2: //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_AUTOTRAYCHANGE2", &val);
					//autotraychange2 = val.u.id_value;
					autotraychange2 = autotray;
					return autotraychange2;
			                break;

			case OMTRAYSEARCHMODE: //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_TRAYSEARCHMODE", &val);
						//traysearchmode = val.u.id_value;
						traysearchmode = traysearch;
						return traysearchmode;
			                        break;

			case OMDUPLEX: duplex = GetDuplex(); 
		        	                return duplex;
                                    		break;

            case LONGEDGEFEED: return 0;
                               break;
	    case OMEDGETOEDGE: //retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_EDGETOEDGE", &val);
				//edgetoedge = val.u.id_value;
				edgetoedge = edge;
				return edgetoedge;
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
	 return TRUE;
}


int PRpapertable(PAPERINFO *papers, int xres, int yres)
{
     memcpy(papers, paper_table_variable_resolution, sizeof(paper_table_variable_resolution));
     /*papers = (PAPERINFO *) paper_table_variable_resolution;*/
       return MAX_TABLE_SIZE;
    
}

PAPERINFO * PRpaperinfo(PAPERCODE size, int xres, int yres)
{
    PAPERINFO *paperinfo;
	int retval;
	
	retval = Map_Page_Size(size,GET_OMCODE);
	size=retval;	
    paperinfo = PRpaperinfoOriginal (size, xres, yres);
    return paperinfo;

/*    return PAPERSIZE_A4;*/
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
  search_path = (search_path_t *) malloc(sysinfo.num_tray * sizeof(search_path_t));	
  if( -1 == gpsGetTrayInfo(gps_client, sysinfo.num_tray, gpsTrayInfo, &trayNum, GPS_NOTIFY_CHANGE_OFF) )
    return -1;
  /* To do - Map SDK str from GPS Specification DB - 01.pdf  : page no 37
   gpsGetTrayInfo - page no 197*/
  for(nTrayIndex = 0; nTrayIndex < g_nInputTrays; nTrayIndex++)
  {
    switch(gpsTrayInfo[nTrayIndex].id)
	{
      case 0:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_MANUALFEED;
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
      case 4:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_TRAY4;
		break;
      case 5:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_TRAY5;
		break;
      case 6:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_TRAY6;
		break;
      case 7:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_TRAY7;
		break;
	  case 10:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_LCT;
		break;
	  case 16:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_INSERTER;
		break;
      case 17:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_INSERTER2;
		break;
      case 18:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_PERF_INSERTER;
		break;
	  case 19:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_PERF_INSERTER2;
		break;
	  case 20:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_BYPASS;
		break;
      case 21:
        search_path[nTrayIndex].om_source = PMS_PCL5TRAY_ENVELOPE;
		break;      
		
      default:
        search_path[nTrayIndex].om_source  = PMS_PCL5TRAY_AUTO; 
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
	     search_path[nTrayIndex].om_size = PMS_PCL5_LETTER;   
	    break;
	  case GPS_CODE_A4T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_A4;
	    break;
	  case GPS_CODE_8Hx14T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_LEGAL;
	    break;
	  case GPS_CODE_7Qx10HT:
	     search_path[nTrayIndex].om_size= PMS_PCL5_EXE;
	    break;
	  case GPS_CODE_A3T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_A3;
	    break;
	  case GPS_CODE_11x17T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_TABLOID;
	    break;
	  case GPS_CODE_A5T:
	    search_path[nTrayIndex].om_size = PMS_PCL5_A5;
	    break;
	  case GPS_CODE_A6T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_A6;
	    break;
	  case GPS_CODE_C5T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_C5_ENV;
	    break;
	  case GPS_CODE_DL_T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_DL_ENV;
	    break;
	  case YET_TO_FIND_4:
	     search_path[nTrayIndex].om_size = PMS_PCL5_LEDGER;
	    break;
	  case YET_TO_FIND_5:
	     search_path[nTrayIndex].om_size = PMS_PCL5_OFUKU;
	    break;
	  case GPS_CODE_10x14T:
	     search_path[nTrayIndex].om_size = PMS_PCL5_JISB4;
	    break;
	  case YET_TO_FIND_6:
	     search_path[nTrayIndex].om_size = PMS_PCL5_JISB5;
	    break;
	  case YET_TO_FIND_7:
	     search_path[nTrayIndex].om_size= PMS_PCL5_CUSTOM;
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
	
    search_path[nTrayIndex].om_stat = ( char*)gpsTrayInfo[nTrayIndex].status;	
	if(gpsTrayInfo[nTrayIndex].attr == GPS_TRAY_LOCKED)
    {
       search_path[nTrayIndex].om_lock = 1;
    }
    else
    {
       search_path[nTrayIndex].om_lock = 0;
    }
    /*printf("nTrayIndex = %d \n", nTrayIndex);
    printf("search_path[nTrayIndex].om_size = %d \n", search_path[nTrayIndex].om_size);
    printf("search_path[nTrayIndex].om_mediatype = %d \n", search_path[nTrayIndex].om_mediatype);	
	printf("search_path[nTrayIndex].om_source = %d \n", search_path[nTrayIndex].om_source);	
	printf("search_path[nTrayIndex].om_lock = %d \n", search_path[nTrayIndex].om_lock);*/	
	
  }
  
  //g_nInputTrays = sysinfo.num_tray;

		  
  return 0;
}

int GetOrientation()
{
    return (g_pstCurrentJob->uOrientation);
}
/*int GetBinding()
{
    return (g_pstCurrentJob->uPCL5PaperSize);
}*/
int GetDuplex()
{
    return (g_pstCurrentJob->bDuplex);
}

int GetInserterTray()
{ 
    simhandle_t *hsim=NULL;
  //  int retenv;
    int trayInserter;
    varvalue_t val;
    	if (_var_getbyname(hsim, "GPS_PENV_VAL_INT_TRAY_INSERTER", &val) == 0) {
		if (val.type == 0 && val.u.id_value != 0)
            trayInserter =  val.u.id_value;
       }
    return trayInserter;     
}


