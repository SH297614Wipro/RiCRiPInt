#include "di_envdef.h"
#include "omstub.h"
#include "ricohpaper.h"
#include "device.h"
#include "oil.h"
#include "pms_export.h"
#include "gpssim.h"
#include "gps/penv_var.h"


extern int GetMediaType();
extern void SetPageSize();
extern void SetMediaType(Uint32 media);
extern OMenum GetPaperSource();
extern Uint32 GetCustomPageWidth();
extern Uint32 GetCustomPageHeight();
extern long PrintSysGetCustomWidth();
extern long PrintSysGetCustomLength();
extern Boolean PrintSysCheckNonRotation(OMenum paper, ORIENTATION orient, int xres, int yres);
extern Boolean PrintSysGetPaperInfo(OMenum paper);
extern OMEnum OMGetCurrentEnum(OMenum omvar, OMenum omsystem);
extern void SetPaperSource(int tray);
extern int getMhPaperSource();
extern OMenum GetPageSize();

extern OIL_TyJob *g_pstCurrentJob;
extern int g_nInputTrays;
extern PMS_TyTrayInfo *g_pstTrayInfo;
extern PMS_TySystem g_tSystemInfo;
bool tray_selected=FALSE;
int print_force_flag=FALSE;
int  selected_traynum=-1;
int longEdge_val,shortEdge_val;
/* #define NULL 0 */
extern int current_pdlid;
extern PAPERINFO paper_table_variable_resolution[MAX_TABLE_SIZE];
extern PAPERINFO System_Paper_table[MAX_TABLE_SIZE];
static PAPERCODE LastPaperSelect,LastPaperSize;
static OMenum LastPaperSource,LastMediaType;
Sint8 ChoosePaperDirectionDone;
struct {
	OMenum size;
	OMenum stat;
} sizestat_tbl[] = {
	{ PAPERSIZE_LONGLTR, TRAYINSERTED_IN },
	{ PAPERSIZE_A4,      TRAYINSERTED_IN },

	{ PAPERSIZE_LETTER, TRAYINSERTED_IN },
	{ PAPERSIZE_A4R,    TRAYINSERTED_IN },
};

struct Pagesize_OMCode_t PageSize_OMCode[15] ={
   /* PCL Page size 	OMCode              GPSPageSize   */
  {  PMS_PCL5_EXE     ,  498 ,              GPS_CODE_7Qx10H },
  {  PMS_PCL5_LETTER  ,  603 ,    			GPS_CODE_8Hx11  },
  {  PMS_PCL5_LEGAL   ,  514 ,    			GPS_CODE_8Hx14  },
  {  PMS_PCL5_LEDGER  ,  0   , 		            0			},
  {  PMS_PCL5_A6      ,  579 , 				GPS_CODE_A6     },
  {  PMS_PCL5_A5      ,  580 ,				GPS_CODE_A5     },
  {  PMS_PCL5_A4      ,  581 ,				GPS_CODE_A4     },
  {  PMS_PCL5_A3      ,  582 ,				GPS_CODE_A3     },
  {  PMS_PCL5_JISB5   ,  574 ,                 0            },
  {  PMS_PCL5_JISB4   ,  575 ,                 0            },
  {  PMS_PCL5_OFUKU   ,  523 ,                 0            },
  {  PMS_PCL5_DL_ENV  ,  490 ,				GPS_CODE_DL     },
  {  PMS_PCL5_C5_ENV  ,  488 ,				GPS_CODE_C5     },
  {  PMS_PCL5_CUSTOM  ,  522 ,					0           },/*approximate size 340*666*/
  {  PMS_PCL5_TABLOID ,  516 ,				GPS_CODE_11x17  }   
};

/* #define NSIZESTAT_TBL	(sizeof(sizestat_tbl)/sizeof(sizestat_tbl[0])) */
Boolean paper_setted = FALSE;
di_onetrayinfo_t	*pTray = NULL;


#if defined(EMPCL5) || defined(EMPCLXL) 
int mnSetPaperInfo()
{
    paper_setted = FALSE;
    simhandle_t *hsim =NULL;
    Uint8 ret;
    int trayInserter;
    Sint32 r_media_s;
#ifdef PJL_JOB_START_END
	/*int pagerange = PrintSysQueryPageRange(pPDIstatePCL->pageCount);*/
    int pagerange, retenv,rettray;
    varvalue_t val;
    pagerange = g_pstCurrentJob->uPagesToPrint;
    rettray = update_TrayInfo_fromGPS();
#endif
	if (!paper_setted) {
#ifdef PRINT_QUALITY_MODE
		Uint32 r_media = GetMediaType();
      /*  retenv = _var_getbyname(hsim, "GPS_PENV_VAR_ID_QUALITYMODE", &val); 
        OMenum r_qmode = val.u.id_value; */
        OMenum r_qmode = g_tSystemInfo.eImageQuality;
#endif

#ifdef SUPPORT_INSERTER 
      	if (_var_getbyname(hsim, "GPS_PENV_VAL_INT_TRAY_INSERTER", &val) == 0) {
		if ((val.type == 0) && (val.u.id_value != 0) && ( val.u.id_value < DI_MAX_TRAY_NUM)) /*5 to be replaced with tray range*/
        {
         trayInserter =  val.u.id_value;
       
       if (trayInserter != INSERTER_NOTSELECT)
       {
        /*PDIsetpaper(mnMediaSizeSelectionForInserter(PDIRgetpapercode(pPDIstatePCL)));*/
        SetPageSize(mnMediaSizeSelectionForInserter(GetPageSize()));
        return(0);
       }
     }
  }
#endif  /* <<Inseter tray>>*/

#ifdef PJL_JOB_START_END
      if(pagerange > PAGEOUTRANGE || pagerange < DISCARDRANGE)
        return(0);
#endif
#ifdef DEBUG
/*	DBGPRINTF(DBGBIOS, 16, "mnSetPaperInfo: === set the paper information ===\n"); */
#endif
		paper_setted = TRUE;

#ifdef PRINT_QUALITY_MODE
		r_media_s = r_media;
		ret = PrintSysCheckQualityMode(&r_media_s, &r_qmode);
		if (ret & CHANGE_MEDIATYPE) {
			/*PDIsetmedia(r_media);*/
			SetMediaType(r_media);
		}
		if (ret & CHANGE_QUALITYMODE) {
			/*PDIsetqualitymode(r_qmode);* quality mode is available in PMS structure which will be updated from GPS as part of boot up*/
            SetQualityMode(r_qmode);
		}
#endif
/*
		if(!CheckSamePaperSize() || PDIRgetpapersource(pPDIstatePCL) != LastPaperSource || PDImediatype != LastMediaType){ Replaced PDI calls*/
        if(!CheckSamePaperSize() || GetPaperSource() != LastPaperSource || r_media != LastMediaType){
			LastPaperSize = GetPageSize();/*PDIRgetpapercode(pPDIstatePCL);*/
			LastPaperSource = GetPaperSource();/*PDIRgetpapersource(pPDIstatePCL);*/
			LastMediaType = r_media;
			/*PDIsetpaper(mnMediaSizeSelection(GetPageSize()));*/
                    /*(PDIRgetpapercode(pPDIstatePCL)));*/
		    SetPageSize(mnMediaSizeSelection(GetPageSize()));
			LastPaperSelect = GetPageSize();/*PDIRgetpapercode(pPDIstatePCL);*/
		}
		else {
			if(LastPaperSelect == 0xFFFF)
				LastPaperSelect = mnMediaSizeSelection(GetPageSize());/*(PDIRgetpapercode(pPDIstatePCL));*/
			/*PDIsetpaper(LastPaperSelect);*/
            SetPageSize(LastPaperSelect);
		}
		/*Recalc();*/
		return 1;
	} else 
		return 0;
}
#endif  /*defined(EMPCL5) || defined(EMPCLXL)*/

Boolean CheckSamePaperSize()
 {
	/*if(PDIRgetpapercode(pPDIstatePCL) != LastPaperSize)*/
     if(GetPageSize() != LastPaperSize)
		return FALSE;
#ifdef PCL5_CUSTOMSIZE_COMMAND
	else if((GetPageSize() == PAPERSIZE_CUSTOM) && (!CheckSameCustomSize()))/*(PDIRgetpapercode(pPDIstatePCL)==PAPERSIZE_CUSTOM)&&!CheckSameCustomSize())*/ 
	{
		return FALSE;
	}
#endif
	 return TRUE;
 }
 
Boolean CheckSameCustomSize()
{
	Sint32 CustomWidth, CustomLength, CurrentWidth, CurrentLength, p_max_width, p_max_height;
	CustomWidth = GetCustomPageWidth();
	CustomLength = GetCustomPageHeight();
	/*if ((PDIcustomwidth <= 0) || (PDIcustomheight <= 0))*/ /* check the difference between PDIcustomwidth and currentwidth*/
	if (( CustomWidth <= 0) || ( CustomLength <= 0))
			return FALSE;
	else
	{
		/*CurrentWidth = (long)((float)PDIcustomwidth * 254 / 720 + 0.5);
		CurrentLength = (long)((float)PDIcustomheight * 254 / 720 + 0.5);*/
		CurrentWidth = (long)((float)CustomWidth * 254 / 720 + 0.5);
		CurrentLength = (long)((float)CustomLength * 254 / 720 + 0.5);
		PrintSysGetMaxPaperSize(&p_max_width, &p_max_height);
		
		if (p_max_width && (CurrentWidth > p_max_width)) {
			CurrentWidth = p_max_width;
		}
		if (p_max_height && (CurrentLength > p_max_height)) {
			CurrentLength = p_max_height;
		}
		
		if(CurrentWidth !=PrintSysGetCustomWidth()||CurrentLength !=PrintSysGetCustomLength())
			return FALSE;
	}
	return TRUE;
}
/* #endif */
void Init_ResolutionTable()
{
//paper_table_variable_resolution=System_Paper_table ;

   memcpy(&paper_table_variable_resolution,&System_Paper_table,sizeof(paper_table_variable_resolution));
}
void UpdatePaperTableResolution()
{
int i;

	for(i=0;i<=115;i++)
	{
	paper_table_variable_resolution[i].resolution.x = g_pstCurrentJob->uXResolution;
	paper_table_variable_resolution[i].resolution.y = g_pstCurrentJob->uYResolution;
	paper_table_variable_resolution[i].size.x = ((paper_table_variable_resolution[i].PS_PageSize.x * paper_table_variable_resolution[i].resolution.x) /72 );
	paper_table_variable_resolution[i].size.y =(( paper_table_variable_resolution[i].PS_PageSize.y * paper_table_variable_resolution[i].resolution.y) /72);
	}
}
#if defined(EMPCL5) || defined(EMPCLXL) 
OMenum mnMediaSizeSelection(OMenum paper)
{
	int papersize = 0;

	PrintSysSetCompulsionPaperSize(_enum_EOT);
	PrintSysSetCompulsionInTray(_enum_EOT);
    
#ifdef SYS_CHECK_DIRECTION
	/*if ( PrintSysCheckNonRotation( paper, PDI1.orient, PDI1res.x, PDI1res.y ) ) {
		return mnNonRotateDirection( PDI1.orient, paper, PDI1res.x, PDI1res.y );
	}*/
	if ( PrintSysCheckNonRotation( paper, GetOrientation(), XRESOLUTION, YRESOLUTION ) ) {
		return mnNonRotateDirection( GetOrientation(), paper, XRESOLUTION, YRESOLUTION );
	}
#endif /* SYS_CHECK_DIRECTION */

#ifdef PCL_PREVIEW
	if( PrintSysGetPrintCondition_JobType() == GPS_PCND_PDL_JOBTYPE_SDK_THUMBNAIL ){
		papersize = mnSelectionByPreview(paper, XRESOLUTION, YRESOLUTION );/*PDI1res.x, PDI1res.y);*/
		return papersize;		
	}
#endif /* PCL_PREVIEW */
	/*if(PDIRgetpapersource(pPDIstatePCL) == PAPERSRC_ALL){*/
    Init_ResolutionTable();
	UpdatePaperTableResolution();
	 if(GetPaperSource() == PAPERSRC_ALL){
		papersize = mnSelectionByAutoPaperSource(paper, XRESOLUTION, YRESOLUTION );/*PDI1res.x, PDI1res.y);*/
	}else{
		papersize = mnSelectionByChoosePaperSource(paper, XRESOLUTION, YRESOLUTION );/*PDI1res.x, PDI1res.y);*/
	}

/*	DBGPRINTF1(DBGBIOS, 16,
		"mnMediaSizeSelection: return paper size %d\n", papersize); */
#ifdef DEBUG_LOGS	
      	      printf("\nTRAY SELECTED IS  %d \n", GetPaperSource() );
#endif			  

	return papersize;
}
#endif /* defined(EMPCL5) || defined(EMPCLXL) */

#ifdef SUPPORT_INSERTER
OMenum mnMediaSizeSelectionForInserter(OMenum paper)

{
    OMenum longEdge, shortEdge;
    Boolean longSupport, shortSupport;
    OMenum XRESOLUTION = OMGetCurrentInt(XRES, OMSYSTEM);
    OMenum YRESOLUTION = OMGetCurrentInt(YRES, OMSYSTEM);

    PRpaperPair(paper, XRESOLUTION, YRESOLUTION, &longEdge, &shortEdge);

    longSupport = PrintSysGetPaperInfo(longEdge);
    shortSupport = PrintSysGetPaperInfo(shortEdge);

    if (longSupport && shortSupport) {
	if (PrintSysInserterMatchPaperSize()) {
	    return longEdge;
	} else {
	    return shortEdge;
	}
    } else if (longSupport) {
	return longEdge;
    } else if (shortSupport) {
	return shortEdge;
    }
    return longEdge; // temporarily
}
#endif /*SUPPORT_INSERTER*/

#ifdef SYS_CHECK_DIRECTION
OMenum mnNonRotateDirection( ORIENTATION orient, OMenum papersize, int xres, int yres )
{
	OMenum paper, longEdge, shortEdge;
  //  Boolean ORportrait, ORrevport; //temporarily
//	ORportrait = 0;
//	ORrevport = 1;
	PRpaperPair ( papersize, xres, yres, &longEdge, &shortEdge );

	if ( longEdge != 0 && shortEdge != 0 ) {
		if ( orient == GPS_PENV_VAL_INT_ORIENTATION_PORTRAIT || orient == GPS_PENV_VAL_INT_ORIENTATION_REVERSEPORTRAIT ) {
			paper = shortEdge;
		} else {
			paper = longEdge;
		}
	} else if ( longEdge != 0 ) {
		paper = longEdge;
	} else if ( shortEdge != 0 ) {
		paper = shortEdge;
	} else {
		/*DBGPANIC("mnNonRotationDirection() : longEdge & shorEdge not Found\n");
		DBGFATAL();*/
	}

	return paper;
}
#endif /* SYS_CHECK_DIRECTION */

#ifdef PCL_PREVIEW
OMenum mnSelectionByPreview(OMenum paper, int xres, int yres)
{
	long	p_width, p_height;
	long	width, height;
	long	p_max_width, p_max_height;
	OMenum longEdge, shortEdge;
	Boolean longSupport, shortSupport;
    int customwidth, customheight;
	customwidth = GetCustomPageWidth();
	customheight = GetCustomPageHeight();
	
	if( paper == PAPERSIZE_CUSTOM ){
		if (customwidth <= 0)
		{
			customwidth = 6120;
		}
		if (customheight <= 0)
		{
			customheight = 7920;
		}
		width = (long)((float)customwidth * xres / 720 + 0.5);
		height = (long)((float)customheight * yres / 720 + 0.5);

		p_width = (long)((float)customwidth * 254 / 720 + 0.5);
		p_height = (long)((float)customheight * 254 / 720 + 0.5);

		PrintSysGetMaxPaperSize(&p_max_width, &p_max_height);
		
		if (p_max_width && (p_width > p_max_width)) {
			p_width = p_max_width;
			width = (long)((float)p_width * xres / 254 + 0.5);
		}
		if (p_max_height && (p_height > p_max_height)) {
			p_height = p_max_height;
			height = (long)((float)p_height * yres / 254 + 0.5);
		}

		PrintSysSetCustomSize(p_width, p_height, xres, yres);

		PRcustompaperinfo(width, height, xres, yres);
	}
	else{
		/*PRpaperPair(paper, PDI1res.x, PDI1res.y, &longEdge, &shortEdge);*/
		PRpaperPair(paper, XRESOLUTION, YRESOLUTION, &longEdge, &shortEdge);

		longSupport = PrintSysGetPaperInfo(longEdge);
		shortSupport = PrintSysGetPaperInfo(shortEdge);

		if (longSupport) {
			return longEdge;
		} else if (shortSupport) {
			return shortEdge;
		}
		else {
			PrintSysSetJobCancel( TRUE );
			LOGMPRINTF2(0x905, "[%s]0905 %d,Preview size not support %d\n", PDLNAME, paper);
		}
	}

	return paper;
}
#endif




bool check_paper_size(int priori)
{
    int i;
   
 	tray_selected=FALSE;	
  for (i=0;i<g_nInputTrays;i++)
  {
       if(g_pstTrayInfo[i].nPriority==priori)
       {
       		if(GetPageSize()==search_path[i].om_size)
       		{
				 if( search_path[i].om_lock == TRAYLOCKED_LOCKED)/* if tray is locked*/
				 {
#ifdef DEBUG_LOGS
               		        	printf("\n Tray %d is Locked..Searching for next matching tray....\n",(i+1));
#endif
			                continue;
                		}
                		else
				{
				tray_selected=TRUE;
				selected_traynum=search_path[i].om_source;
				print_force_flag=FALSE;
				break;
 			    	}
		}

       	}
  }
        if(tray_selected==FALSE)
        {
		/*selected_traynum=GetPaperSource();*/
				
					print_force_flag=TRUE;
					selected_traynum=PMS_PCL5TRAY_TRAY1;/* to be changed with hardware*/

			

        }
	return tray_selected;

}
void Pick_priority_tray()
{
	int i;
	int temp_priority;
		
	for (i=0,temp_priority=0;i<g_nInputTrays, temp_priority<=g_nInputTrays;i++,temp_priority++)
	{
             if(TRUE==(check_paper_size( temp_priority)))
             {
			break;

             }
	}

}

int check_source()
{
	int papersrc=0;
        selected_traynum=-1;
		tray_selected=FALSE;	
	papersrc=GetPaperSource();
	if(papersrc==PAPERSRC_ALL)
	{
		Pick_priority_tray();
		SetPaperSource(selected_traynum);
                return selected_traynum;
	}
        else 
        {
             if(papersrc!=-1)
		{
             	 selected_traynum=papersrc; 
                 SetPaperSource(selected_traynum);
 		}
             return papersrc;
        }	
}

#if defined(EMPCL5) || defined(EMPCLXL)
OMenum mnSelectionByAutoPaperSource(OMenum papersize, int xres, int yres)
{
	OMenum paper, longEdge, shortEdge;
	Sint32 paper_S;
	Sint32 le_tray = NSEARCH_PATH, se_tray = NSEARCH_PATH;
	Boolean se_pe_tray = FALSE, le_pe_tray = FALSE;
#if BYPASS_FREE_FEED == 2
	OMenum bypass_mode;
#endif

	PRpaperPair ( papersize, xres, yres, &longEdge, &shortEdge );
	longEdge_val = longEdge;
	shortEdge_val = shortEdge;
/*	DBGPRINTF1(DBGBIOS, 16,
		"mnSelectionByAutoPaperSource: found shortEdge %d\n", shortEdge);
	DBGPRINTF1(DBGBIOS, 16,
		"mnSelectionByAutoPaperSource: found longEdge %d\n", longEdge);
*/
    /*shortEdge = papersize;  //temoporarily
    longEdge = 0;         */  //temporarily
	/* check short edge feed tray */
	se_tray = searchBestPaperSource(shortEdge, GetMediaType(), TRAYINSERTED_IN);/*PDImediatype, TRAYINSERTED_IN);*/
#ifdef DEBUG
	if (se_tray < NSEARCH_PATH) {
	/*	DBGPRINTF1(DBGBIOS, 16,
			"mnSelectionByAutoPaperSource: found short edge besttray %d\n", se_tray); */
	}
#endif

	if (se_tray == NSEARCH_PATH) {
		se_tray = searchBestPaperSource(shortEdge, GetMediaType(), TRAYINSERTED_IN);/*PDImediatype, TRAYINSERTED_INEMPTY);*/
		se_pe_tray = (se_tray != NSEARCH_PATH);
#ifdef DEBUG
		if (se_tray < NSEARCH_PATH) {
		/*	DBGPRINTF1(DBGBIOS, 16,
				"mnSelectionByAutoPaperSource: found short edge bettertray %d\n", se_tray); */
		}
#endif
	}

	/* check long edge feed tray */
	if (longEdge) {
		le_tray = searchBestPaperSource(longEdge, GetMediaType(), TRAYINSERTED_IN);/*PDImediatype, TRAYINSERTED_IN);*/
#ifdef DEBUG
		if (le_tray < NSEARCH_PATH) {
/*		DBGPRINTF1(DBGBIOS, 16,
				"mnSelectionByAutoPaperSource: found long edge besttray %d\n", le_tray); */
		}
#endif

		if (le_tray == NSEARCH_PATH) {
			le_tray = searchBestPaperSource(longEdge, GetMediaType(), TRAYINSERTED_INEMPTY);/*PDImediatype, TRAYINSERTED_INEMPTY);*/
			le_pe_tray = (le_tray != NSEARCH_PATH);
#ifdef DEBUG
			if (le_tray < NSEARCH_PATH) {
		/*		DBGPRINTF1(DBGBIOS, 16,
					"mnSelectionByAutoPaperSource: found long edge bettertray %d\n", le_tray); */
			}
#endif
		}

	}


	if( ((se_tray != NSEARCH_PATH) && !se_pe_tray)
		|| ((le_tray != NSEARCH_PATH) && !le_pe_tray) ) {
		if( se_pe_tray )
			se_tray = NSEARCH_PATH;;
		if( le_pe_tray )
			le_tray = NSEARCH_PATH;
	}

	if( (se_tray == NSEARCH_PATH) && (le_tray == NSEARCH_PATH) ) {
		/* No much ALL tray */
		paper = papersize;
		paper_S =paper;
		choosePaperDirection(&paper_S,longEdge,shortEdge); 	
		if( paper == PAPERSIZE_CUSTOM ) {
			/* for Custom paper size */
#ifdef PCL5e_CUSTOM_BUGFIX
           PAPERINFO  *custom_paperinfo;
			OMenum tray;

			/*PrintSysPaperRequest(&paper, 0, 0,
								 PDImediatype, PDIRgetpapersource(pPDIstatePCL), FALSE);*/
			PrintSysPaperRequest(&paper_S, 0, 0,
								 GetMediaType(), GetPaperSource(), FALSE);

            custom_paperinfo = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
         
            //if( (PDIRgetinterpreter(pPDIstatePCL) == PDI_PCL) && !PrintSysGetJobCancel() ){
			if( (current_pdlid == GPS_PDL_PCL) && !PrintSysGetJobCancel() ){
				tray = searchBestPaperSource(PAPERSIZE_CUSTOM, GetMediaType(), TRAYINSERTED_IN);/*PDImediatype,
						TRAYINSERTED_IN);*/
				if ( tray == NSEARCH_PATH )
					tray = searchBestPaperSource(PAPERSIZE_CUSTOM, GetMediaType(), TRAYINSERTED_INEMPTY);/*PDImediatype,
							TRAYINSERTED_INEMPTY);*/
                 /*SetPaperSource(tray);*/
#ifdef PCL5_CUSTOMSIZE_COMMAND  /*check for omsource once */
				mnGetCustomSize( (tray == NSEARCH_PATH
					? OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM)
					: search_path[tray].om_source),
					xres, yres, custom_paperinfo );
#else
				PrintSysGetCustomSize( (tray == NSEARCH_PATH
					? OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM)
					: search_path[tray].om_source),
					xres, yres, custom_paperinfo );
#endif
			}
#else
			PAPERINFO  *custom_paperinfo; 
			OMenum priority_tray;
			Sint32 p_width, p_length;

			//custom_paperinfo.size = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
            custom_paperinfo = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);

			/*if( PDIRgetinterpreter(pPDIstatePCL) == PDI_PCL ) {*/
            if(current_pdlid == GPS_PDL_PCL)
            {
				/*priority_tray = OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM);*/
					priority_tray = check_source();
				#ifdef DEBUG_LOGS
					printf("Priority_tray = %d\n",priority_tray);
				#endif

#ifdef PCL5_CUSTOMSIZE_COMMAND
				mnGetCustomSize( priority_tray, xres, yres, custom_paperinfo );
#else
				PrintSysGetCustomSize( priority_tray, xres, yres, custom_paperinfo );
#endif
			}

			p_width = custom_paperinfo->size.x * 254 / xres;
			p_length = custom_paperinfo->size.y * 254 / yres;;

			PrintSysPaperRequest(&paper_S, p_width, p_length,
			                      GetMediaType(), GetPaperSource(), FALSE);   
								 /*PDImediatype, PDIRgetpapersource(pPDIstatePCL), FALSE);*/

#endif
		} else if (PrintSysPaperRequest(&paper_S, 0, 0, GetMediaType(), GetPaperSource(), FALSE) == 0){
		/*PDImediatype, PDIRgetpapersource(pPDIstatePCL), FALSE) == 0) {*/
			PAPERINFO  *ResultPaperinfo;
			Boolean LEFfound, SEFfound;

            ResultPaperinfo = PRpaperinfo(paper, xres, yres);
			SEFfound = FALSE;/*LongEdgeLeading(ResultPaperinfo)*/ //temporarily
                       /*PDIlongedgeleading(&ResultPaperinfo) ? FALSE : TRUE; */
			LEFfound = SEFfound ? FALSE : TRUE;

		    PrintSysChoosePaperDirectionOnStaplePunch(&LEFfound, &SEFfound, GetOrientation());
													 /* *PDI1.orient);*/
		}
	} else {
		/* found much tray */
#if BYPASS_FREE_FEED == 2
			bypass_mode = OMGetCurrentEnum(OMBYPASSTRAYSETTING, OMSYSTEM);
			if ((bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE) && (papersize != PAPERSIZE_CUSTOM) && (search_path[se_tray].om_source == PAPERSRC_BYPASS) && (search_path[le_tray].om_source == PAPERSRC_BYPASS))
			{
				if (PrintSysIsDirectionSEF())
					paper = (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
				else
					paper = (PrintSysGetPaperInfo(longEdge)) ? longEdge : shortEdge;
			}
			else {
		paper = checkFinisherPrint( papersize, le_tray, se_tray, GetOrientation(), xres, yres );
		if (paper != shortEdge && paper != longEdge)
			paper = (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
			}
#else
		paper = checkFinisherPrint( papersize, le_tray, se_tray, GetOrientation(), xres, yres );
#ifdef BYPASS_FREE_FEED
		if (paper != shortEdge && paper != longEdge)
			paper = (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
#endif
#endif
	}
	
	return paper;
}
#endif  /* defined(EMPCL5) || defined(EMPCLXL) */

Sint32 searchBestPaperSource(OMenum code, OMenum mediatype, OMenum insert)
{
    Boolean bypass_traylock = FALSE;
	Sint32 best_tray;
	OMenum paper, stat, lock, media, priority_tray, frontcover_tray;
#ifdef BYPASS_FREE_FEED
	OMenum bypass_mode;
#ifdef IOTESTPFLAG
	extern TESTPMODE testprintmode;
#endif
	
	/*Get bypass tray setting */
	bypass_mode = OMGetCurrentEnum(OMBYPASSTRAYSETTING, OMSYSTEM);
#endif

	/* Get priority tray*/
	priority_tray = check_source();
/*OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM);*/
        
	/* Get front cover tray (for front cover print*/
	if( OMGetCurrentEnum(OMFRONTCOVERPRINT, OMSYSTEM) == GPS_PENV_VAL_INT_FRONTCOVERPRINT_OFF ) {
		frontcover_tray = GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_NONE; /*front cover print off*/
	} else {
		frontcover_tray = OMGetCurrentEnum(OMFRONTCOVERPRINTTRAY, OMSYSTEM);
	}

	for (best_tray = 0; best_tray < NSEARCH_PATH; best_tray++) {
		if ( priority_tray == search_path[best_tray].om_source ) {
			lock = search_path[best_tray].om_lock; //OMGetCurrentEnum(search_path[best_tray].om_lock, OMPRINTER);
			if(bypass_traylock){
				if ((lock == TRAYLOCKED_LOCKED)&& (search_path[best_tray].om_source!=PAPERSRC_BYPASS)) 
				break;
#ifdef BYPASS_FREE_FEED
				else if ((search_path[best_tray].om_source == PAPERSRC_BYPASS) 
						&& (bypass_mode != GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE && 
							bypass_mode != GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE )) break;
#else
				else if (search_path[best_tray].om_source == PAPERSRC_BYPASS) break;
#endif
			}
 			else{
				if ( lock == TRAYLOCKED_LOCKED ) break;
			}
				/* Priority tray was locked */
			if ( frontcover_tray == search_path[best_tray].om_frontcovertray ) break;
				/* Priority tray is front cover tray */
			paper = search_path[best_tray].om_size; //OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER);
			media = search_path[best_tray].om_mediatype; //OMGetCurrentEnum(search_path[best_tray].om_mediatype, OMPRINTER);
			stat = (int)(search_path[best_tray].om_stat); //OMGetCurrentEnum(search_path[best_tray].om_stat, OMPRINTER);
#ifdef BYPASS_FREE_FEED
			if (search_path[best_tray].om_source == PAPERSRC_BYPASS
				 && insert == stat
#ifdef IOTESTPFLAG
				 && testprintmode == TESTPMODE_NORMAL
#endif
				 ) {
				if (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE)
					return best_tray;
				if (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE){
					if (code == PAPERSIZE_CUSTOM)
						return best_tray;
					else
						break;
			}
			}
#endif
			if( mediatype == MEDIATYPE_AUTO ) {
				if (code == paper && insert == stat &&
					((media == MEDIATYPE_PLAIN) || (media == MEDIATYPE_RECYCLED) || (media == MEDIATYPE_PLAIN2)) )
					return best_tray;
			} else {
				if (code == paper && insert == stat && mediatype == media)
				return best_tray;
			}
			break;	/* Priority tray no match */
		}
	}

	for (best_tray = 0; best_tray < NSEARCH_PATH; best_tray++) {
		lock = 0;/*OMGetCurrentEnum(search_path[best_tray].om_lock, OMPRINTER);*/
		if(bypass_traylock){
			if ((lock == TRAYLOCKED_LOCKED)&&(search_path[best_tray].om_source!=PAPERSRC_BYPASS)) 
			{continue;}
#ifdef BYPASS_FREE_FEED
			else if ((search_path[best_tray].om_source == PAPERSRC_BYPASS) 
					&& (bypass_mode != GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE && 
						bypass_mode != GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE )) continue;
#else
            else if (search_path[best_tray].om_source == PAPERSRC_BYPASS) continue;
#endif
		}
		else{
			if (lock == TRAYLOCKED_LOCKED) {continue;}
		}
			/* locked tray skip */
		if ( frontcover_tray == search_path[best_tray].om_frontcovertray ) {continue;}
			/* Priority tray is front cover tray */
		paper = search_path[best_tray].om_size; //OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER);
		media = search_path[best_tray].om_mediatype; //OMGetCurrentEnum(search_path[best_tray].om_mediatype, OMPRINTER);
		stat = (int)(search_path[best_tray].om_stat); //OMGetCurrentEnum(search_path[best_tray].om_stat, OMPRINTER);
#ifdef BYPASS_FREE_FEED
		if (search_path[best_tray].om_source == PAPERSRC_BYPASS
			 && insert == stat
#ifdef IOTESTPFLAG
			 && testprintmode == TESTPMODE_NORMAL
#endif
			 ) {
			if (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE)
				return best_tray;
			if (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE){
				if (code == PAPERSIZE_CUSTOM)
					return best_tray;
				else
					continue;
		}
		}
#endif
		if( mediatype == MEDIATYPE_AUTO ) {
			if (code == paper && insert == stat &&
				((media == MEDIATYPE_PLAIN) || (media == MEDIATYPE_RECYCLED) || (media == MEDIATYPE_PLAIN2)) )
				break;
		} else {
			if (code == paper && insert == stat && mediatype == media)
			break;
		}
	}
        /* SetPaperSource(best_tray);*/
	return best_tray;
}

void choosePaperDirection(Sint32 *psize, OMenum longEdgePaper,
			 OMenum shortEdgePaper)
{
	Boolean LEFfound = TRUE, SEFfound = TRUE; 
    if((*psize == PAPERSIZE_CUSTOM) || !PrintSysGetPaperInfo(longEdgePaper)
	 || ((OMGetCurrentEnum(OMSTAPLE,OMSYSTEM) == GPS_PENV_VAL_INT_STAPLE_OFF) &&
	(OMGetCurrentEnum(OMPUNCH,OMSYSTEM) == GPS_PENV_VAL_INT_PUNCH_OFF))) {
		return;
	}

	PrintSysChoosePaperDirectionOnStaplePunch(&LEFfound, &SEFfound,
						  GetOrientation());
	ChoosePaperDirectionDone = 0;
	if(!SEFfound){
	*psize = longEdgePaper;
	}
} 
/* #endif defined(EMPCL5) || defined(EMPCLXL)*/

#ifdef PCL5_CUSTOMSIZE_COMMAND
void mnGetCustomSize(OMenum tray, int xres, int yres, PAPERINFO *paper)
{
	long	p_width, p_height;
	long	width, height;
	long	p_max_width, p_max_height;
    long customwidth, customheight;
    customwidth = GetCustomPageWidth();
    customheight = GetCustomPageHeight();
	if ((customwidth <= 0) || (customheight <= 0))
		PrintSysGetCustomSize(tray, xres, yres, paper);
	else {
		width = (long)((float)customwidth * xres / 720 + 0.5);
		height = (long)((float)customheight * yres / 720 + 0.5);

		p_width = (long)((float)customwidth * 254 / 720 + 0.5);
		p_height = (long)((float)customheight * 254 / 720 + 0.5);

		PrintSysGetMaxPaperSize(&p_max_width, &p_max_height);
		
		if (p_max_width && (p_width > p_max_width)) {
			p_width = p_max_width;
			width = (long)((float)p_width * xres / 254 + 0.5);
		}
		if (p_max_height && (p_height > p_max_height)) {
			p_height = p_max_height;
			height = (long)((float)p_height * yres / 254 + 0.5);
		}

		PrintSysSetCustomSize(p_width, p_height, xres, yres);
		PRcustompaperinfo(width, height, xres, yres);
	}
}
#endif

#if defined(EMPCL5) || defined(EMPCLXL)  
OMenum checkFinisherPrint(OMenum papersize, Sint32 longEdgeTray, Sint32 shortEdgeTray, ORIENTATION orient, int xres, int yres)
{
	PAPERINFO  *custom_paperinfo;
	OMenum paper = 0, priority_tray;
	Boolean SEFfound, LEFfound;
#ifdef BYPASS_FREE_FEED
	OMenum bypass_mode;

	/* Get bypass tray setting*/
	bypass_mode = OMGetCurrentEnum(OMBYPASSTRAYSETTING, OMSYSTEM);
#endif
/*
#ifdef STAPLE_PUNCH_CONTROLED_BY_PDL
	ReflectOptionCondition(&longEdgeTray, &shortEdgeTray, orient);
#endif
*/
	SEFfound = ( shortEdgeTray != NSEARCH_PATH ) ? TRUE : FALSE;
	LEFfound = ( longEdgeTray != NSEARCH_PATH ) ? TRUE : FALSE;
#ifdef SYS_CHECK_DIRECTION
	if ( papersize != PAPERSIZE_CUSTOM )
#endif
	PrintSysChoosePaperDirectionOnStaplePunch( &LEFfound, &SEFfound, orient );
	shortEdgeTray = SEFfound ? shortEdgeTray : NSEARCH_PATH;
	longEdgeTray = LEFfound ? longEdgeTray : NSEARCH_PATH;

	/* Get priority tray*/
		priority_tray = check_source();
/*	priority_tray = OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM);*/

	if ( longEdgeTray != NSEARCH_PATH && shortEdgeTray != NSEARCH_PATH ) {
		/* found ShortEdge & LongEdge */
		Sint32 shortPathTray;

		if (priority_tray == search_path[shortEdgeTray].om_source)
			shortPathTray = shortEdgeTray;
		else
			shortPathTray = longEdgeTray;

#ifdef BYPASS_FREE_FEED
		if ((papersize == PAPERSIZE_CUSTOM) &&
			 search_path[shortPathTray].om_source == PAPERSRC_BYPASS &&
			 (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE ||
			 bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE))
			paper = papersize;
		else
#endif
		paper = search_path[shortPathTray].om_size; //OMGetCurrentEnum(search_path[shortPathTray].om_size, OMPRINTER);

		/* Get custom Papersize */
		if( (paper == PAPERSIZE_CUSTOM) && (current_pdlid == GPS_PDL_PCL) ) {
			//custom_paperinfo.size = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
            custom_paperinfo = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
#ifdef PCL5_CUSTOMSIZE_COMMAND
			mnGetCustomSize( search_path[shortPathTray].om_source,
				xres, yres, custom_paperinfo );
#else
			PrintSysGetCustomSize( search_path[shortPathTray].om_source,
				xres, yres, custom_paperinfo );
#endif
		}

		return paper;

	} else if ( longEdgeTray != NSEARCH_PATH ) {
		/* Only LongEdge found */
#ifdef BYPASS_FREE_FEED
		if ((papersize == PAPERSIZE_CUSTOM) &&
			 search_path[longEdgeTray].om_source == PAPERSRC_BYPASS &&
			 (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE ||
			 bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE))
			paper = papersize;
		else
#endif
		paper = search_path[longEdgeTray].om_size; //OMGetCurrentEnum(search_path[longEdgeTray].om_size, OMPRINTER);

		/* Get custom Papersize */
		if( (paper == PAPERSIZE_CUSTOM) && (current_pdlid == GPS_PDL_PCL) ) {
			//custom_paperinfo.size = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
            custom_paperinfo = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
#ifdef PCL5_CUSTOMSIZE_COMMAND
			mnGetCustomSize( search_path[longEdgeTray].om_source,
				xres, yres, custom_paperinfo );
#else
			PrintSysGetCustomSize( search_path[longEdgeTray].om_source,
				xres, yres, custom_paperinfo );
#endif
		}

		return paper;

	} else if ( shortEdgeTray != NSEARCH_PATH ) {
		/* Only ShortEdge was found */
#ifdef BYPASS_FREE_FEED
		if ((papersize == PAPERSIZE_CUSTOM) &&
			 search_path[shortEdgeTray].om_source == PAPERSRC_BYPASS &&
			 (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE ||
			 bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE))
			paper = papersize;
		else
#endif
		paper = search_path[shortEdgeTray].om_size; //OMGetCurrentEnum(search_path[shortEdgeTray].om_size, OMPRINTER);

		/* Get custom Papersize */
		if( (paper == PAPERSIZE_CUSTOM) && (current_pdlid == GPS_PDL_PCL) ) {
			//custom_paperinfo.size = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
            custom_paperinfo = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
#ifdef PCL5_CUSTOMSIZE_COMMAND
			mnGetCustomSize( search_path[shortEdgeTray].om_source,
				xres, yres, custom_paperinfo );
#else
			PrintSysGetCustomSize( search_path[shortEdgeTray].om_source,
				xres, yres, custom_paperinfo );
#endif
		}

		return paper;

	}
#ifdef NOUSE_ALL_NOMATCH_CASE
	 else {	/*( longEdgeTray == NSEARCH_PATH && shortEdgeTray == NSEARCH_PATH )*/

		OMenum longEdge, shortEdge;
		PRpaperPair ( papersize, xres, yres, &longEdge, &shortEdge );

		/* Get custom Papersize */
		if( (papersize == PAPERSIZE_CUSTOM) && (current_pdlid == GPS_PDL_PCL) ) {
			//custom_paperinfo.size = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
            custom_paperinfo = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
#ifdef PCL5_CUSTOMSIZE_COMMAND
			mnGetCustomSize( ((GetPaperSource() == PAPERSRC_ALL) ? priority_tray : (OMenum)GetPaperSource() ),
				xres, yres, custom_paperinfo );
#else
			PrintSysGetCustomSize( ((GetPaperSource() == PAPERSRC_ALL) ? priority_tray : (OMenum)GetPaperSource() ),
				xres, yres, custom_paperinfo );
#endif
		}

		/* return default value */
		if ( longEdge != 0 ) {	/* "longEdge == 0" is not supported Long edge feed paper size*/
			return longEdge;
		}
        paper = papersize;
		return papersize;
	}
#endif /* NOTUSE_ALL_NOMATCH_CASE */
     return paper;
}

OMenum mnSelectionByChoosePaperSource(OMenum papersize, int xres, int yres)
{
    OMenum longEdge, shortEdge;
    Uint32 paper, mediatype, tray;
    Sint32 paper_S;
#ifdef BYPASS_FREE_FEED
	OMenum bypass_mode;
#endif
	/*Sint32 tray;*/
	Sint32 p_width, p_length;
#if TRAY_OVERWRITING >= 2
	/* Sint32 hdwpsize; */
#endif
    tray = getMhPaperSource();
	tray = searchChoosePaperSource(tray);/*PDIRgetpapersource(pPDIstatePCL));*/

	paper = search_path[tray].om_size; //OMGetCurrentEnum(search_path[tray].om_size, OMPRINTER);
/*#if TRAY_OVERWRITING >= 2
	hdwpsize = mnOMtoHdwPaperSize(paper);
#endif*/
	mediatype = search_path[tray].om_mediatype; //OMGetCurrentEnum(search_path[tray].om_mediatype, OMPRINTER);

#ifdef EN_LIMITLESS_FEED
	if(OMGetCurrentBool(OMAUTOTRAYCHANGE2, OMSYSTEM)) {    
		/*PDImediatype = mediatype;*/
		SetMediaType(mediatype);
	}
#endif

	PRpaperPair ( papersize, xres, yres, &longEdge, &shortEdge );

/*	DBGPRINTF1(DBGBIOS, 16,
		"mnSelectionByChoosePaperSource: found short edge %d\n", shortEdge);
	DBGPRINTF1(DBGBIOS, 16,
		"mnSelectionByChoosePaperSource: found long edge %d\n", longEdge);
*/
   /* shortEdge = papersize;
    longEdge = 0; */
#ifdef BYPASS_FREE_FEED
	bypass_mode = OMGetCurrentEnum(OMBYPASSTRAYSETTING, OMSYSTEM);
#if BYPASS_FREE_FEED == 2
	if( !((bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE && search_path[tray].om_source == PAPERSRC_BYPASS) || (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE && search_path[tray].om_source == PAPERSRC_BYPASS))) {
#else
	if (!(bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE && search_path[tray].om_source == PAPERSRC_BYPASS)) {
#endif
#endif
	if( shortEdge == paper ) {
		paper = checkFinisherPrint( papersize, (Sint32)NSEARCH_PATH, tray, GetOrientation(), xres, yres);/*PDI1.orient, xres, yres );*/
		return paper;
	}

	if( longEdge && longEdge == paper ) {
		paper = checkFinisherPrint( papersize, tray, (Sint32)NSEARCH_PATH, GetOrientation(), xres, yres);/*PDI1.orient, xres, yres );*/
		return paper;
    }
#ifdef BYPASS_FREE_FEED
	}
#endif

	/* No much paper size */
	paper = papersize;

	if( paper == PAPERSIZE_CUSTOM ) {
		/* for Custom paper size */
		PAPERINFO  *custom_paperinfo;

		//custom_paperinfo.size = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);
        custom_paperinfo = PRpaperinfo(PAPERSIZE_CUSTOM, xres, yres);

		//if( PDIRgetinterpreter(pPDIstatePCL) == PDI_PCL ) {
         if(current_pdlid == GPS_PDL_PCL) {
#ifdef PCL5_CUSTOMSIZE_COMMAND
			//mnGetCustomSize( PDIRgetpapersource(pPDIstatePCL), xres, yres, &custom_paperinfo );
            mnGetCustomSize( GetPaperSource(), xres, yres, custom_paperinfo );
#else
			//PrintSysGetCustomSize( PDIRgetpapersource(pPDIstatePCL), xres, yres, &custom_paperinfo );
            PrintSysGetCustomSize( GetPaperSource(), xres, yres, custom_paperinfo );
#endif
		}

		p_width = custom_paperinfo->size.x * 254 / xres;
		p_length = custom_paperinfo->size.y * 254 / yres;;
	} else {
		p_width = 0;
		p_length = 0;
	}

	/* specially procces for bypass tray */
	/*if(PDIRgetpapersource(pPDIstatePCL) == PAPERSRC_BYPASS) {*/
	if(GetPaperSource() == PAPERSRC_BYPASS) {
#if BYPASS_FREE_FEED == 2
		if (bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE) {
			if (PrintSysIsDirectionSEF())
				return (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
			else
				return (PrintSysGetPaperInfo(longEdge)) ? longEdge : shortEdge;
			} else
#endif
		paper = (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
#if TRAY_OVERWRITING >= 2
	/*	if(!PrintSysIsDirectionoverwritingInvalid() && hdwpsize < DI_CODE_NO_SIZE)
			paper = (PrintSysGetPaperInfo(longEdge)) ? longEdge : shortEdge;*/
#endif
		return paper;
	} 

#ifdef TRAY_OVERWRITING
	if (search_path[tray].om_traysetting == TRAYSETTING_COMMAND)
			return (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
#endif

#ifdef EN_LIMITLESS_FEED
	if(OMGetCurrentBool(OMAUTOTRAYCHANGE2, OMSYSTEM) || 
	    (OMGetCurrentEnum(OMTRAYSEARCHMODE, OMSYSTEM) == GPS_PENV_VAL_INT_TRAYSEARCHMODE_SWITCH)) {
#else
	if(OMGetCurrentEnum(OMTRAYSEARCHMODE, OMSYSTEM) == GPS_PENV_VAL_INT_TRAYSEARCHMODE_SWITCH) {
#endif
		Sint32 le_tray = NSEARCH_PATH, se_tray = NSEARCH_PATH;
		Boolean se_pe_tray = FALSE, le_pe_tray = FALSE; 
		
		/* check short edge feed tray */
		se_tray = searchBestPaperSource(shortEdge, GetMediaType(), TRAYINSERTED_IN);/*PDImediatype, TRAYINSERTED_IN); */
		
		if (se_tray == NSEARCH_PATH) {
			se_tray = searchBestPaperSource(shortEdge, GetMediaType(), TRAYINSERTED_INEMPTY);/*PDImediatype, TRAYINSERTED_INEMPTY);*/
			se_pe_tray = (se_tray != NSEARCH_PATH);
		} 
		
		/* check long edge feed tray */
		if (longEdge) {
			le_tray = searchBestPaperSource(longEdge, GetMediaType(), TRAYINSERTED_IN);/*PDImediatype, TRAYINSERTED_IN);*/
			
			if (le_tray == NSEARCH_PATH) {
				le_tray = searchBestPaperSource(longEdge, GetMediaType(), TRAYINSERTED_INEMPTY);/*PDImediatype, TRAYINSERTED_INEMPTY);*/
				le_pe_tray = (le_tray != NSEARCH_PATH);
			} 
		} 
		
		if(((se_tray != NSEARCH_PATH) && !se_pe_tray)
				|| ((le_tray != NSEARCH_PATH) && !le_pe_tray)) {
			if(se_pe_tray)
				se_tray = NSEARCH_PATH;;
			if(le_pe_tray)
				le_tray = NSEARCH_PATH;
		} 
		
#ifdef BYPASS_FREE_FEED
		if((se_tray != NSEARCH_PATH) || (le_tray != NSEARCH_PATH)) {
#if BYPASS_FREE_FEED == 2
			if ((bypass_mode == GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE) && (papersize != PAPERSIZE_CUSTOM) && (search_path[se_tray].om_source == PAPERSRC_BYPASS) && (search_path[le_tray].om_source == PAPERSRC_BYPASS))
			{
				if (PrintSysIsDirectionSEF())
					paper = (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
				else
					paper = (PrintSysGetPaperInfo(longEdge)) ? longEdge : shortEdge;
			}
			else {
			paper = checkFinisherPrint(papersize, le_tray, se_tray, GetOrientation(), xres, yres);/*PDI1.orient, xres, yres);*/
			if (paper != shortEdge && paper != longEdge)
				paper = (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
			return paper;
			}
#else
			paper = checkFinisherPrint(papersize, le_tray, se_tray, GetOrientation(), xres, yres);/*PDI1.orient, xres, yres);*/
			if (paper != shortEdge && paper != longEdge)
				paper = (PrintSysGetPaperInfo(shortEdge)) ? shortEdge : longEdge;
			return paper;
#endif
		}
#else
		if((se_tray != NSEARCH_PATH) || (le_tray != NSEARCH_PATH))
			return (checkFinisherPrint(papersize, le_tray, se_tray, GetOrientation(), xres, yres));/*PDI1.orient, xres, yres);*/
#endif
	}
	paper_S=paper;
	choosePaperDirection(&paper_S,longEdge,shortEdge); 	
	if (paper == PAPERSIZE_CUSTOM)
		PrintSysPaperRequest(&paper_S, p_width, p_length, GetMediaType(), GetPaperSource(), FALSE);
							 /*PDImediatype, PDIRgetpapersource(pPDIstatePCL), FALSE);*/
	else if (PrintSysPaperRequest(&paper_S, 0, 0, GetMediaType(), GetPaperSource(), FALSE) == 0) {
	/*PDImediatype, PDIRgetpapersource(pPDIstatePCL),
								  FALSE) == 0) */
								  
		PAPERINFO  *ResultPaperinfo;
		Boolean LEFfound, SEFfound;

		//ResultPaperinfo.size = PRpaperinfo(paper, xres, yres);
        ResultPaperinfo = PRpaperinfo(paper, xres, yres);
		SEFfound = FALSE;/*PDIlongedgeleading(ResultPaperinfo) ? FALSE : TRUE;*/
		LEFfound = SEFfound ? FALSE : TRUE;

		PrintSysChoosePaperDirectionOnStaplePunch(&LEFfound, &SEFfound, GetOrientation());
												  /*PDI1.orient);*/
	}
    
	return paper;
}
#endif /* defined(EMPCL5) || defined(EMPCLXL) */

#if defined(EMPCL5) || defined(EMPCLXL) 
OMenum mnGetOMPaperSize(Sint32 code, int xres, int yres, int (*comp)())
{
    PAPERINFO * primary;

    /* get the 1st paper information into paper table */
    primary = (PAPERINFO *)PRpaperfirst(code, xres, yres, comp);
    if (primary == (PAPERINFO *)NULL)
        return (OMenum)0;               /* illeagal paper code */

  /*  DBGPRINTF1(DBGBIOS, 16,
        "mnGetOMPaperSize: found OM paper code %d\n", primary->OMcode); */

    return primary->OMcode;
}
#endif /* defined(EMPCL5) || defined(EMPCLXL) */

Sint32 searchChoosePaperSource(OMenum tray_code)
{
	Sint32 choose_tray;
	OMenum om_code;
    /* int trayret; */
//    trayret = update_TrayInfo_fromGPS();
	for (choose_tray = 0; choose_tray < NSEARCH_PATH; choose_tray++) {
		om_code = search_path[choose_tray].om_source;
		if ( om_code == tray_code )
			break;
	}
   /* SetPaperSource(choose_tray);*/
	return choose_tray;

}

#if 0 
/*Newly added from here related to PCL5 / PCLXL as part of feature enabling */
#define -1 -1
#ifndef IPS_MEDIA_HANDLING
#define PAPER_MISSMATCH (-1)

typedef struct TRAYREQUEST
{
	enum {NON_EVENT = -1, TRAY_FOUND, TRAY_ERRSKIP, TRAY_CANCEL, TRAY_FORCE} result;
	OMenum tray;
}TrayRequest_t;

TrayRequest_t TrayRequest;

typedef struct Bind_Valid_Table {
	OMenum	option;
	Boolean	valid;
}BindValid;

typedef enum {
	StapleLeftTopSlant,
	StapleRightTopSlant,
	StapleLeft2,
	StapleTop2,
	StapleRight2,
	StapleLeftTopHoriz,
	StapleLeftTopVert,
	StapleRightTopHoriz,
	StapleRightTopVert,
	StapleLeftTop,
	StapleRightTop,

	StapleMaxPosition = 16,
} StaplePosition;

#define	PJL_LeftTopSlant	(1 << StapleLeftTopSlant)
#define	PJL_RightTopSlant	(1 << StapleRightTopSlant)
#define	PJL_Left2			(1 << StapleLeft2)
#define	PJL_Top2			(1 << StapleTop2)
#define	PJL_Right2			(1 << StapleRight2)
#define	PJL_LeftTopHoriz	(1 << StapleLeftTopHoriz)
#define	PJL_LeftTopVert		(1 << StapleLeftTopVert)
#define	PJL_RightTopHoriz	(1 << StapleRightTopHoriz)
#define	PJL_RightTopVert	(1 << StapleRightTopVert)
#define PJL_LeftTop			(1 << StapleLeftTop)
#define	PJL_RightTop		(1 << StapleRightTop)

#define	YUKON		(PJL_LeftTopSlant|PJL_RightTopSlant)
#define	LAWRENCE	(PJL_LeftTopSlant|PJL_RightTopSlant|PJL_Left2 \
					|PJL_Top2|PJL_Right2|PJL_LeftTopHoriz \
					|PJL_LeftTopVert|PJL_RightTopHoriz|PJL_RightTopVert \
					|PJL_LeftTop|PJL_RightTop)

typedef struct StapleTable {
	Field32	p_edge:1;			/* Feed paper type 0/1:Short/Long */
	Field32	orient:1;			/* paper orientation 0/1:Portrait/Landscape */
	Field32	rotate:1;			/* rotate print 0/1:0/180 */

	unsigned short position;			/* RPJL position */
	unsigned char gps[StapleMaxPosition];	/* GPS data */
} StapleTable_t;

typedef enum {
	PunchLeft,
	PunchTop,
	PunchRight,

	MaxPunchNum,
} PunchType;

typedef struct PunchSingleTable {
	Field8	p_edge:1;
	Field8	orient:1;
	Uint8	rotate[MaxPunchNum];
} PunchSingle_t;

typedef struct StaplePunchResult {
	Field16	use:1;
	Field16	p_edge:1;
	Field16	orient:1;
	Field16	rotate:1;
	Uint8   staple;
	Uint8	punch;
} StaplePunch_t;

typedef enum {
	StaplePunch_Short,
	StaplePunch_Long,

	StaplePunch_MAX,
} StaplePunchEdge;

typedef enum {
	FEED_ShortEdge,
	FEED_LongEdge,

	FEED_Edge_Max,
} FeedPaperEdge;

typedef enum {
	ORI_Portrait,
	ORI_Landscape,

	ORIENTATION_Max,
} OrientationType;

#endif /* IPS_MEDIA_HANDLING */

#ifdef PDL_TRAY_REQUEST
OMenum searchErrorSkipPaperSource()
{
	Sint32 tray;
	OMenum priority_tray, stat, lock, frontcover_tray;

	/* Get priority tray*/
        	priority_tray = check_source();
/*	priority_tray = OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM);*/

	/* Get front cover tray (for front cover print*/
	if( OMGetCurrentEnum(OMFRONTCOVERPRINT, OMSYSTEM) == GPS_PENV_VAL_INT_FRONTCOVERPRINT_OFF ) {
		frontcover_tray = GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_NONE;	/*front cover print off*/
	} else {
		frontcover_tray = OMGetCurrentEnum(FRONTCOVERPRINTTRAY, OMSYSTEM);
	}

	for (tray = 0; tray < NSEARCH_PATH; tray++) {
		if ( priority_tray == search_path[tray].om_source ) {
			lock = search_path[tray].om_lock; //OMGetCurrentEnum(search_path[tray].om_lock, OMPRINTER);
			if ( lock == TRAYLOCKED_LOCKED ) break;
				/* Priority tray was locked */
			if ( frontcover_tray == search_path[best_tray].om_frontcovertray ) break;
				/* Priority tray is front cover tray */
			stat = search_path[tray].om_stat; //OMGetCurrentEnum(search_path[tray].om_stat, OMPRINTER);
			if ( stat == TRAYINSERTED_IN ) {
				return (search_path[tray].om_source);
			}
			break;	/* Priority tray no match */
		}
	}

	for (tray = 0; tray < NSEARCH_PATH; tray++) {
		lock = search_path[tray].om_lock; //OMGetCurrentEnum(search_path[tray].om_lock, OMPRINTER);
		if ( lock == TRAYLOCKED_LOCKED ) {continue;}
			/* locked tray skip */
		if ( frontcover_tray == search_path[best_tray].om_frontcovertray ) {continue;}
			/* Priority tray is front cover tray */
		stat = search_path[tray].om_stat; //OMGetCurrentEnum(search_path[tray].om_stat, OMPRINTER);
		if ( stat == TRAYINSERTED_IN )
			break;
	}

	return (tray != NSEARCH_PATH? search_path[tray].om_source: -1);
}
#endif /* PDL_TRAY_REQUEST */

OMenum mnPaperSizeSelectionForConfigPage(OMenum * papersrc)
{
	Sint32 i, next, tray_LEF,tray_SEF, best_tray;
	OMenum stat;
	OMenum priority_tray;
       	priority_tray = check_source();
	/*priority_tray = OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM);*/

	/* search for Letter or A4, LEF */
	tray_LEF = NSEARCH_PATH;
	for (i = 0; i < NSIZESTAT_TBL / 2; i++) {
		next = searchBestPaperSource(sizestat_tbl[i].size,
										MEDIATYPE_AUTO, sizestat_tbl[i].stat);
		if (tray_LEF > next) tray_LEF = next;
		ASSERT(papersrc);
		ASSERT((next >= 0) && ( next < dimof(search_path)));
		if (next != NSEARCH_PATH && priority_tray == search_path[next].om_source)
		{
			*papersrc = search_path[next].om_source;
			return search_path[next].om_size;
	//	return OMGetCurrentEnum(search_path[next].om_size, OMPRINTER);

		}
	}

	/* search for Letter or A4, SEF */
	tray_SEF = NSEARCH_PATH;
	for (; i < NSIZESTAT_TBL; i++) {
		next = searchBestPaperSource(sizestat_tbl[i].size,
										MEDIATYPE_AUTO, sizestat_tbl[i].stat);
		if (tray_SEF > next) tray_SEF = next;
		ASSERT((next >= 0) && ( next < dimof(search_path)));
		if (next != NSEARCH_PATH && priority_tray == search_path[next].om_source)
		{
			*papersrc = search_path[next].om_source;
			return search_path[next].om_size;
	//	return OMGetCurrentEnum(search_path[next].om_size, OMPRINTER);

		}
	}
	if (tray_LEF < NSEARCH_PATH) {
		ASSERT((tray_LEF>= 0) && ( tray_LEF< dimof(search_path)));
		*papersrc = search_path[tray_LEF].om_source;
		return search_path[tray_LEF].om_size;
	//	return OMGetCurrentEnum(search_path[tray_LEF].om_size, OMPRINTER);
	}
	if (tray_SEF < NSEARCH_PATH) {
		ASSERT((tray_SEF>= 0) && ( tray_SEF< dimof(search_path)));
		*papersrc = search_path[tray_SEF].om_source;
		return search_path[tray_SEF].om_size;
	//	return OMGetCurrentEnum(search_path[tray_SEF].om_size, OMPRINTER);
        }

	/* use default papersize */
	*papersrc = OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM);
	for (best_tray = 0; best_tray < NSEARCH_PATH; best_tray++) {
		if (*papersrc == search_path[best_tray].om_source) {
		    if (OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER) == PAPERSIZE_UNKNOWN)
		        break;
		    else
			return search_path[best_tray].om_size;
		//	return OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER);
		}
	}

	for (best_tray = 0; best_tray < NSEARCH_PATH; best_tray++)
	{ 
		for (i = 0; i < NSIZESTAT_TBL; i++) 
		{ 
			if (search_path[best_tray].om_size == sizestat_tbl[i].size && search_path[best_tray].om_stat != TRAYINSERTED_OUT)
		//	if (OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER) == sizestat_tbl[i].size && 
		//	    OMGetCurrentEnum(search_path[best_tray].om_stat, OMPRINTER) != TRAYINSERTED_OUT)
		   	{
			    *papersrc = search_path[best_tray].om_source;
				return search_path[best_tray].om_size;
		//	    return OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER);
		   	}
	   	}
	}
	
	for (best_tray = 0; best_tray < NSEARCH_PATH; best_tray++)
	{
		if (search_path[best_tray].om_size != PAPERSIZE_UNKNOWN && search_path[best_tray].om_stat == TRAYINSERTED_IN)
	//	if (OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER) != PAPERSIZE_UNKNOWN &&
	//	    OMGetCurrentEnum(search_path[best_tray].om_stat, OMPRINTER) == TRAYINSERTED_IN)
		{
		    *papersrc = search_path[best_tray].om_source;
			return search_path[best_tray].om_size;
	//	    return OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER);
		}
	}

	for (best_tray = 0; best_tray < NSEARCH_PATH; best_tray++)
	{
		if (search_path[best_tray].om_size != PAPERSIZE_UNKNOWN && search_path[best_tray].om_stat != TRAYINSERTED_OUT)
	//	if (OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER) != PAPERSIZE_UNKNOWN &&
	//	    OMGetCurrentEnum(search_path[best_tray].om_stat, OMPRINTER) != TRAYINSERTED_OUT)
		{
		    *papersrc = search_path[best_tray].om_source;
			return search_path[best_tray].om_size;
	//	    return OMGetCurrentEnum(search_path[best_tray].om_size, OMPRINTER);
		}
	}

	return OMGetCurrentEnum(OMPAPERSIZE, OMPRINTER);
}

#ifdef PCL5_CUSTOMSIZE_COMMAND
void mnGetCustomSize(OMenum tray, int xres, int yres, PAPERINFO *paper)
{
	long	p_width, p_height;
	long	width, height;
	long	p_max_width, p_max_height;
	
	if ((PDIcustomwidth <= 0) || (PDIcustomheight <= 0))
		PrintSysGetCustomSize(tray, xres, yres, paper);
	else {
		width = (long)((float)PDIcustomwidth * xres / 720 + 0.5);
		height = (long)((float)PDIcustomheight * yres / 720 + 0.5);

		p_width = (long)((float)PDIcustomwidth * 254 / 720 + 0.5);
		p_height = (long)((float)PDIcustomheight * 254 / 720 + 0.5);

		PrintSysGetMaxPaperSize(&p_max_width, &p_max_height);
		
		if (p_max_width && (p_width > p_max_width)) {
			p_width = p_max_width;
			width = (long)((float)p_width * xres / 254 + 0.5);
		}
		if (p_max_height && (p_height > p_max_height)) {
			p_height = p_max_height;
			height = (long)((float)p_height * yres / 254 + 0.5);
		}

		PrintSysSetCustomSize(p_width, p_height, xres, yres);

		PRcustompaperinfo(width, height, xres, yres);
	}
}
#endif

#if defined(EMPCL5) || defined(EMPCLXL)  
void choosePaperDirection(Sint32 *psize,OMenum longEdgePaper,
			 OMenum shortEdgePaper)
{
	extern Sint8 ChoosePaperDirectionDone;
	Boolean LEFfound = TRUE, SEFfound = TRUE; 
	if((*psize == PAPERSIZE_CUSTOM) || !PrintSysGetPaperInfo(longEdgePaper)
	 || ((OMGetCurrentEnum(OMSTAPLE,OMSYSTEM) == GPS_PENV_VAL_INT_STAPLE_OFF) &&
	(OMGetCurrentEnum(OMPUNCH,OMSYSTEM) == GPS_PENV_VAL_INT_PUNCH_OFF))) {
		return;
	}
	PrintSysChoosePaperDirectionOnStaplePunch(&LEFfound, &SEFfound,
						  PDI1.orient);
	ChoosePaperDirectionDone = 0;
	if(!SEFfound){
	*psize = longEdgePaper;
	}
} 
#endif  /*defined(EMPCL5) || defined(EMPCLXL)*/

#if defined(EMPCL5) || defined(EMPCLXL)  
OMenum mnGetOMPaperSize(Sint32 code, int xres, int yres, int (*comp)())
{
    PAPERINFO * primary;

    /* get the 1st paper information into paper table */
    primary = (PAPERINFO *)PRpaperfirst(code, xres, yres, comp);
    if (primary == (PAPERINFO *)NULL)
        return (OMenum)0;               /* illeagal paper code */

    DBGPRINTF1(DBGBIOS, 16,
        "mnGetOMPaperSize: found OM paper code %d\n", primary->OMcode);

    return primary->OMcode;
}
#endif /* defined(EMPCL5) || defined(EMPCLXL) */

#ifdef PDL_TRAY_REQUEST

Boolean mnTrayRequest( OMenum MediaSize, OMenum MediaSource, OMenum MediaType )
{
	Sint32 search_tray;
	OMenum tray_mediasize, tray_mediatype;

	if( MediaSource == PAPERSRC_ALL ) {

		search_tray = searchBestPaperSource(MediaSize, MediaType, TRAYINSERTED_IN);

#ifdef DEBUG
		if (search_tray < NSEARCH_PATH) {
			DBGPRINTF1(DBGBIOS, 16,
				"mnTrayRequest: found besttray %d\n", search_tray);
		}
#endif

		if (search_tray >= NSEARCH_PATH) {
			PrintSysTrayRequest( mnOMtoHdwPaperSize(MediaSize), 0,
				mnOMtoHdwMediaType(MediaType), mnOMtoHdwPaperSource(MediaSource) );
			return TRUE;
		} else {
			return FALSE;
		}

	} else {

		search_tray = searchChoosePaperSource( MediaSource );

		tray_mediasize = search_path[search_tray].om_size; //OMGetCurrentEnum(search_path[search_tray].om_size, OMPRINTER);
		tray_mediatype = search_path[search_tray].om_mediatype; //OMGetCurrentEnum(search_path[search_tray].om_mediatype, OMPRINTER);

		if( MediaSize == tray_mediasize ) {
			if( MediaType == MEDIATYPE_AUTO ) {
				if ( (tray_mediatype == MEDIATYPE_PLAIN) ||
					 (tray_mediatype == MEDIATYPE_RECYCLED) ) {
					return FALSE;
				}
			} else {
				if ( MediaType == tray_mediatype) {
					return FALSE;
				}
			}
		}
		PrintSysTrayRequest( mnOMtoHdwPaperSize(MediaSize), 0,
			mnOMtoHdwMediaType(MediaType), mnOMtoHdwPaperSource(MediaSource) );
		return TRUE;
	}

}

Boolean mnGetTrayInfo( OMenum MediaSource, OMenum *MediaSize, OMenum *MediaType )
{
	Sint32 tray;
	OMenum tray_mediasize, tray_mediatype, tray_stat;

	tray = searchChoosePaperSource( MediaSource );

    ASSERT (tray != NSEARCH_PATH);
	
	tray_mediasize = search_path[tray].om_size; //OMGetCurrentEnum(search_path[tray].om_size, OMPRINTER);
	tray_mediatype = search_path[tray].om_mediatype; //OMGetCurrentEnum(search_path[tray].om_mediatype, OMPRINTER);
	tray_stat = search_path[tray].om_stat; //OMGetCurrentEnum(search_path[tray].om_stat, OMPRINTER);

	*MediaSize = tray_mediasize;
	*MediaType = tray_mediatype;

	return tray_stat;

}

#endif /* PDL_TRAY_REQUEST */


/* For supportted PaperRequestRes() */

static Boolean paper_setted = FALSE;

void mnResetPaperInfo()
{
	paper_setted = FALSE;
#ifdef DEBUG
	DBGPRINTF(DBGBIOS, 16, "mnResetPaperInfo: reset paper info\n");
#endif
}

#if defined(EMPCL5) || defined(EMPCLXL)  
static OMenum LastPaperSource,LastMediaType;		/*Create new global variable*/
static PAPERCODE LastPaperSelect,LastPaperSize;
void mnInitPageInfo(void)
{
  LastPaperSource = (OMenum)-1;
  LastMediaType = (OMenum)-1;
  LastPaperSelect = 0xFFFF;
  LastPaperSize = 0xFFFF;
}

PAPERCODE mnGetLastPaperSize(void)
{
   return LastPaperSize;
}
OMenum mnGetLastMediaType(void)
{
   return LastMediaType;
}
#ifdef DEBUG
#if defined(STAPLE_PUNCH_CONTROLED_BY_PDL)
static BindValid StapleSidebind[] =
{
	{ STAPLE_LEFTTOPSLANT,		TRUE },
	{ STAPLE_LEFTTOPVERT,		TRUE },
	{ STAPLE_LEFT2,				TRUE },
	{ STAPLE_RIGHT2,			TRUE },
	{ STAPLE_RIGHTTOPVERT,		TRUE },
	{ STAPLE_RIGHTTOPSLANT,		TRUE },
	{ STAPLE_RIGHTTOPHORIZ,		FALSE },
	{ STAPLE_TOP2,				FALSE },
	{ STAPLE_LEFTTOPHOORIZ,		TRUE },
	{ STAPLE_LEFTTOP,			TRUE },
	{ STAPLE_RIGHTTOP,			TRUE }
};

static BindValid StapleTopbind[] =
{
	{ STAPLE_LEFTTOPSLANT,		TRUE },
	{ STAPLE_LEFTTOPVERT,		TRUE },
	{ STAPLE_LEFT2,				FALSE },
	{ STAPLE_RIGHT2,			FALSE },
	{ STAPLE_RIGHTTOPVERT,		FALSE },
	{ STAPLE_RIGHTTOPSLANT,		TRUE },
	{ STAPLE_RIGHTTOPHORIZ,		TRUE },
	{ STAPLE_TOP2,				TRUE },
	{ STAPLE_LEFTTOPHOORIZ,		TRUE },
	{ STAPLE_LEFTTOP,			TRUE },
	{ STAPLE_RIGHTTOP,			TRUE }
};

static BindValid PunchSidebind[] =
{
	{ PUNCH_LEFT,				TRUE },
	{ PUNCH_TOP,				FALSE },
	{ PUNCH_RIGHT,				TRUE }
};

static BindValid PunchTopbind[] =
{
	{ PUNCH_LEFT,				FALSE },
	{ PUNCH_TOP,				TRUE },
	{ PUNCH_RIGHT,				FALSE }
};

static unsigned char StaplePunchTable[MaxPunchNum][StapleMaxPosition] = {
	{
	TRUE, FALSE, TRUE, FALSE, FALSE, TRUE, TRUE, FALSE,
	FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE },
	{
	TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, TRUE,
	TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE },
	{
	FALSE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, TRUE,
	TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE }
};

static unsigned char StaplePunchLeftTable[ORIENTATION_Max][FEED_Edge_Max] = {
	{ PunchTop,		PunchLeft },
	{ PunchLeft,	PunchTop }
};

static unsigned char StaplePunchRightTable[ORIENTATION_Max][FEED_Edge_Max] = {
	{ PunchTop,		PunchRight },
	{ PunchRight,	PunchTop }
};

static unsigned char StapleCheckTable[ORIENTATION_Max][FEED_Edge_Max] = {
	{ FALSE,	TRUE },
	{ TRUE,		FALSE }
};

int LogicalStapleRelease(OMenum staple, ORIENTATION orient, DUPLEX_MODE duplex)
{
	int cnt; /* roop counter */

	if( (staple == GPS_PENV_VAL_INT_STAPLE_OFF) || (duplex == DUPsimplex) )
		return 0;

	if( ((orient == GPS_PENV_VAL_INT_ORIENTATION_PORTRAIT) && (duplex == DUPlong))
		||  ((orient == GPS_PENV_VAL_INT_ORIENTATION_LANDSCAPE) && (duplex == DUPshort))
		||  ((orient == GPS_PENV_VAL_INT_ORIENTATION_REVERSEPORTRAIT) && (duplex == DUPlong))
		||  ((orient == GPS_PENV_VAL_INT_ORIENTATION_REVERSELANDSCAPE) && (duplex == DUPshort)) )
		for(cnt = 0; cnt < dimof(StapleSidebind); cnt++){
			if((StapleSidebind[cnt].option == staple)){
				return(StapleSidebind[cnt].valid == FALSE);
			}
		}
	else{
		for(cnt = 0; cnt < dimof(StapleTopbind); cnt++){
			if((StapleTopbind[cnt].option == staple)){
				return(StapleTopbind[cnt].valid == FALSE);
			}
		}
	}
	return 0;
}

int LogicalPunchRelease(OMenum punch, ORIENTATION orient, DUPLEX_MODE duplex)
{
	int cnt; /* roop counter */

	if( (punch == GPS_PENV_VAL_INT_PUNCH_OFF) || (duplex == 0) )
		return 0;

	if( ((orient == GPS_PENV_VAL_INT_ORIENTATION_PORTRAIT) && (duplex == DUPlong))
		||  ((orient == GPS_PENV_VAL_INT_ORIENTATION_LANDSCAPE) && (duplex == DUPshort))
		||  ((orient == GPS_PENV_VAL_INT_ORIENTATION_REVERSEPORTRAIT) && (duplex == DUPlong))
		||  ((orient == GPS_PENV_VAL_INT_ORIENTATION_REVERSELANDSCAPE) && (duplex == DUPshort)) )
		for(cnt = 0; cnt < dimof(PunchSidebind); cnt++){
			if((PunchSidebind[cnt].option == punch)){
				return(PunchSidebind[cnt].valid == FALSE);
			}
		}
	else{
		for(cnt = 0; cnt < dimof(PunchTopbind); cnt++){
			if((PunchTopbind[cnt].option == punch)){
				return(PunchTopbind[cnt].valid == FALSE);
			}
		}
	}
	return 0;
}

Boolean LogicalStaplePunchRelease()
{
	return (StaplePunchTable[ChangePunchNum()][ChangeStapleNum()] == FALSE);
}

#if defined(EMPCL5) || defined(EMPCLXL)  
void ReflectOptionCondition(Sint32 *longEdgeTray, Sint32 *shortEdgeTray, ORIENTATION orient)
{
	char doStaple = TRUE;
	char doPunch = TRUE;
	OMenum staple;
	OMenum punch;
	DUPLEX_MODE dup_mode;
	
	int option_info;
	int finitype;

	int lef_tray = *longEdgeTray != NSEARCH_PATH;
	int sef_tray = *shortEdgeTray != NSEARCH_PATH;

	if(lef_tray == 0 && sef_tray == 0) 
		sef_tray = 1; 

/* Initialize parameters */

    option_info = OMGetDefaultInt(OMOPTION, OMSYSTEM);

	if( option_info & (1<<4) ){
		finitype = 1; 	/* finisher1000 */
		doPunch = FALSE;
	}else if( option_info & (1<<5) ){
		finitype = 2; 	/* finisher2250 */
	}else{
		finitype = 0; 	/* no finisher */
		doStaple = FALSE;
		doPunch = FALSE;
	}

	staple = OMGetCurrentEnum(OMSTAPLE, OMSYSTEM);
	punch = OMGetCurrentEnum(OMPUNCH, OMSYSTEM);

	if(staple == GPS_PENV_VAL_INT_STAPLE_OFF)
		doStaple = FALSE;
	if(punch == GPS_PENV_VAL_INT_PUNCH_OFF)
		doPunch = FALSE;

/* Logical check & option-release */

	dup_mode = DUPsimplex;
	if (OMGetCurrentBool(OMDUPLEX, OMSYSTEM)) {
		dup_mode = OMGetCurrentEnum(OMBINDINGEDGE, OMSYSTEM) == GPS_PENV_VAL_INT_BINDING_SHORTEDGE ? DUPshort : DUPlong;
	}
	if(doStaple) {
		if (ChangeStapleNum() < 0)
			doStaple = 0;
		else if (LogicalStapleRelease(staple, orient, dup_mode))
			doStaple = FALSE;
	}
	if(doPunch)
		if(LogicalPunchRelease(punch, orient, dup_mode)){
			doPunch = FALSE;
		}
	if (doStaple && doPunch)
		if (LogicalStaplePunchRelease()) {
			doPunch = FALSE;
		}

/* Dicide paper-direction, rotation, option-release */

	InitStaplePunchData();

	if(doStaple)
		CheckStaple(lef_tray, sef_tray, orient, finitype);

	if(doPunch)
		CheckPunch(lef_tray, sef_tray, orient, finitype, dup_mode, doStaple);

	SetOptionParams(longEdgeTray, shortEdgeTray);
}
#endif /* defined(EMPCL5) || defined(EMPCLXL) */

#define	Rotate_0		0
#define	Rotate_180		1

static Uint16 StapleMask[2] = { YUKON, LAWRENCE };

static StapleTable_t StaplePosi[8] = {
	{ 0, 0, 0, 0x0223,
		{	GPS_STAPLE_RIGHT_TOP_HORIZ, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_RIGHT_TOP_HORIZ,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_TOP,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_RIGHT_TOP_HORIZ,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } },
	{ 0, 0, 1, 0x048b,
		{	GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_LEFT_TOP_SLANT,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_DOUBLE_LEFT,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_LEFT_TOP_HORIZ,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_LEFT_TOP_SLANT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } },
	{ 0, 1, 0, 0x0747,
		{	GPS_STAPLE_LEFT_TOP_SLANT, GPS_STAPLE_RIGHT_TOP_VERT,
			GPS_STAPLE_DOUBLE_LEFT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_LEFT_TOP_HORIZ, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_RIGHT_TOP_HORIZ, GPS_STAPLE_LEFT_TOP_SLANT,
			GPS_STAPLE_RIGHT_TOP_VERT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } },
	{ 0, 1, 1, 0x0010,
		{	GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_DOUBLE_LEFT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } },
	{ 1, 0, 0, 0x0010,
		{	GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_DOUBLE_LEFT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } },
	{ 1, 0, 1, 0x0747,
		{	GPS_STAPLE_LEFT_TOP_SLANT, GPS_STAPLE_RIGHT_TOP_VERT,
			GPS_STAPLE_DOUBLE_LEFT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_LEFT_TOP_HORIZ, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_RIGHT_TOP_HORIZ, GPS_STAPLE_LEFT_TOP_SLANT,
			GPS_STAPLE_RIGHT_TOP_VERT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } },
	{ 1, 1, 0, 0x0221,
		{	GPS_STAPLE_RIGHT_TOP_HORIZ, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_RIGHT_TOP_HORIZ,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_RIGHT_TOP_HORIZ,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } },
	{ 1, 1, 1, 0x048a,
		{	GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_LEFT_TOP_SLANT,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_DOUBLE_LEFT,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_STAPLE_LEFT_TOP_HORIZ,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_STAPLE_LEFT_TOP_SLANT, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF,
			GPS_PENV_VAL_INT_STAPLE_OFF, GPS_PENV_VAL_INT_STAPLE_OFF } }
};

typedef enum {
	PunchNo,
	Punch_0,
	Punch_180,
} PunchRotationType;

static PunchSingle_t PunchSingle[4] = {
	{ 0, 0, { PunchNo, Punch_180, PunchNo } },
	{ 0, 1, { Punch_0, PunchNo, Punch_180 } },
	{ 1, 0, { Punch_180, PunchNo, Punch_0 } },
	{ 1, 1, { PunchNo, Punch_180, PunchNo } }
};

int ChangeStapleNum()
{
	switch (OMGetCurrentEnum(OMSTAPLE, OMSYSTEM)) {
	case STAPLE_LEFTTOPSLANT:		return StapleLeftTopSlant;
	case STAPLE_RIGHTTOPSLANT:		return StapleRightTopSlant;
	case STAPLE_LEFT2:				return StapleLeft2;
	case STAPLE_TOP2:				return StapleTop2;
	case STAPLE_RIGHT2:				return StapleRight2;
	case STAPLE_LEFTTOPHOORIZ:		return StapleLeftTopHoriz;
	case STAPLE_LEFTTOPVERT:		return StapleLeftTopVert;
	case STAPLE_RIGHTTOPHORIZ:		return StapleRightTopHoriz;
	case STAPLE_RIGHTTOPVERT:		return StapleRightTopVert;
	case STAPLE_LEFTTOP:			return StapleLeftTop;
	case STAPLE_RIGHTTOP:			return StapleRightTop;
	default:						return -1;
	}
}

int ChangePunchNum()
{
	switch (OMGetCurrentEnum(OMPUNCH, OMSYSTEM)) {
	case PUNCH_LEFT:		return PunchLeft;
	case PUNCH_TOP:			return PunchTop;
	case PUNCH_RIGHT:		return PunchRight;
	default:				return -1;
	}
}

static StaplePunch_t sp_data[StaplePunch_MAX];

void InitStaplePunchData()
{
	StaplePunch_t *res;
	int i;

	for ( i = 0; i < StaplePunch_MAX; i++) {
		res = &sp_data[i];
		res->use = 0;
		res->p_edge = 0;
		res->orient = 0;
		res->rotate = 0;
		res->staple = GPS_PENV_VAL_INT_STAPLE_OFF;
		res->punch = GPS_PENV_VAL_INT_PUNCH_OFF;
	}
}

void CheckStaple(Sint32 longEdgeTray, Sint32 shortEdgeTray, ORIENTATION orient, int finitype)
{
	StapleTable_t *stap_p = StaplePosi;
	int staple = ChangeStapleNum();
	StaplePunch_t *res;
	Boolean b_orient = (orient & 1);
	int i;

	if (staple < 0 || finitype == 0)
		return;

	finitype--;
	for (i = 0; i < sizeof(StaplePosi)/sizeof(StaplePosi[0]); i++, stap_p++) {
		if (b_orient == stap_p->orient
		&& ((shortEdgeTray && !stap_p->p_edge) || (longEdgeTray && stap_p->p_edge))) {
			if ((stap_p->position & StapleMask[finitype]) & (1 << staple)) {
				res = &sp_data[stap_p->p_edge];
				if (res->staple == GPS_PENV_VAL_INT_STAPLE_OFF) {
					res->use = 1;
					res->p_edge = stap_p->p_edge;
					res->orient = stap_p->orient;
					if (orient & 2)
						res->rotate = stap_p->rotate == 0;
					else
						res->rotate = stap_p->rotate;
					res->staple = stap_p->gps[staple];
				}
			}
		}
	}
}

void CheckPunch(Sint32 longEdgeTray, Sint32 shortEdgeTray, ORIENTATION orient, int finitype, DUPLEX_MODE dup_mode, int doStaple)
{
	StaplePunch_t *res;
	PunchSingle_t *single_p;
	int i;
	int staple = ChangeStapleNum();
	int punch = ChangePunchNum();
	Boolean b_orient = (orient & 1);
	Uint8 rot;

	if (finitype != 2 || punch < 0)
		return;

	/* noset staple mode or cancel staple */
	if (doStaple == FALSE
	|| (sp_data[StaplePunch_Short].staple == GPS_PENV_VAL_INT_STAPLE_OFF
		&& sp_data[StaplePunch_Long].staple == GPS_PENV_VAL_INT_STAPLE_OFF))
		staple = -1;

	if (staple < 0 || dup_mode == DUPsimplex) {
		/* Punch only mode (set rotate) */
		single_p = PunchSingle;
		for (i = 0; i < sizeof(PunchSingle)/sizeof(PunchSingle[0]); i++) {
			if (b_orient == single_p->orient) {
				if ((single_p->p_edge == 0 && shortEdgeTray)
				|| (single_p->p_edge == 1 && longEdgeTray)) {
					res = &sp_data[single_p->p_edge];
					res->use = 1;
					rot = single_p->rotate[punch];
					if (rot) {
						res->punch = GPS_PUNCH_ON;
						if (!res->staple) {
							if (orient & 2)
								res->rotate = rot == Punch_0;
							else
								res->rotate = rot != Punch_0;
						} else {
							if (orient & 2)
								rot = (rot == Punch_0);
							else
								rot = (rot != Punch_0);
							if (res->rotate != rot)
								res->punch = GPS_PENV_VAL_INT_PUNCH_OFF;
						}
					} else
						res->punch = GPS_PENV_VAL_INT_PUNCH_OFF;
				}
			}
			single_p++;
		}
	} else {
		/* Staple and Punch mode (noset rotate) */
		for (i = 0; i < StaplePunch_MAX; i++) {
			res = &sp_data[i];
			switch (staple) {
			case StapleLeftTopSlant:
			case StapleLeftTop:
				if (StaplePunchLeftTable[res->orient][res->p_edge] == punch) {
					res->punch = GPS_PUNCH_ON;
				}
				break;
			case StapleRightTopSlant:
			case StapleRightTop:
				if (StaplePunchRightTable[res->orient][res->p_edge] == punch)
					res->punch = GPS_PUNCH_ON;
				break;

			default:
				if (res->staple != GPS_PENV_VAL_INT_STAPLE_OFF)
					res->punch = GPS_PUNCH_ON;
				break;
			}
		}
	}
}

#if defined(EMPCL5) || defined(EMPCLXL)   
void SetOptionParams(Sint32 *longEdgeTray, Sint32 *shortEdgeTray)
{
	char LongCounter = 0;
	char ShortCounter = 0;
	OMenum priority_tray;

	LongCounter = ( ((sp_data[StaplePunch_Long].staple != GPS_PENV_VAL_INT_STAPLE_OFF) <<1)
				| (sp_data[StaplePunch_Long].punch != GPS_PENV_VAL_INT_PUNCH_OFF) );

	ShortCounter =( ((sp_data[StaplePunch_Short].staple != GPS_PENV_VAL_INT_STAPLE_OFF) <<1)
				| (sp_data[StaplePunch_Short].punch != GPS_PENV_VAL_INT_PUNCH_OFF) );

	switch (ChangeStapleNum()) {
	/* Priority Long edge Tray */
	case StapleLeftTopSlant:
	case StapleRightTopSlant:
		if (*longEdgeTray != NSEARCH_PATH)
			LongCounter |= 1<<2;
		break;
	/* Priority slant */
	case StapleLeftTop:
	case StapleRightTop:
		if ((*shortEdgeTray != NSEARCH_PATH)
		&& (sp_data[StaplePunch_Short].staple == GPS_STAPLE_LEFT_TOP_SLANT)) /*to be confirmed whether to replace GPS_PENV_VAL_INT_STAPLE_LEFTTOPSLANTPORT */
			ShortCounter |= 1<<2;
		if ((*longEdgeTray != NSEARCH_PATH)
		&& (sp_data[StaplePunch_Long].staple == GPS_STAPLE_LEFT_TOP_SLANT))
			LongCounter |= 1<<2;
		break;
	}

	if(LongCounter > ShortCounter){
		*shortEdgeTray = NSEARCH_PATH;
		PDIsetstaple(sp_data[StaplePunch_Long].staple);
		PDIsetpunch(sp_data[StaplePunch_Long].punch);
		if(sp_data[StaplePunch_Long].rotate)
			PDI1.orient = (PDI1.orient ^ 2);
	}else if(LongCounter < ShortCounter){
		*longEdgeTray = NSEARCH_PATH;
		PDIsetstaple(sp_data[StaplePunch_Short].staple);
		PDIsetpunch(sp_data[StaplePunch_Short].punch);
		if(sp_data[StaplePunch_Short].rotate)
			PDI1.orient = (PDI1.orient ^ 2);
	}else{ 	/* LongCounter == ShortCounter */
                	priority_tray = check_source();
		/*priority_tray = OMGetDefaultEnum(OMPAPERSRC, OMSYSTEM);*/
		if( priority_tray == search_path[*shortEdgeTray].om_source ){
			*longEdgeTray = NSEARCH_PATH;
			PDIsetstaple(sp_data[StaplePunch_Short].staple);
			PDIsetpunch(sp_data[StaplePunch_Short].punch);
			if(sp_data[StaplePunch_Short].rotate)
				PDI1.orient = (PDI1.orient ^ 2);
		} else if ( priority_tray == search_path[*longEdgeTray].om_source ){
			*shortEdgeTray = NSEARCH_PATH;
			PDIsetstaple(sp_data[StaplePunch_Long].staple);
			PDIsetpunch(sp_data[StaplePunch_Long].punch);
			if(sp_data[StaplePunch_Long].rotate)
				PDI1.orient = (PDI1.orient ^ 2);
		} else {
			if ( *longEdgeTray < *shortEdgeTray ) { /* more shortpass tray */
				*shortEdgeTray = NSEARCH_PATH;
				PDIsetstaple(sp_data[StaplePunch_Long].staple);
				PDIsetpunch(sp_data[StaplePunch_Long].punch);
				if(sp_data[StaplePunch_Long].rotate)
					PDI1.orient = (PDI1.orient ^ 2);
			} else {
				*longEdgeTray = NSEARCH_PATH;
				PDIsetstaple(sp_data[StaplePunch_Short].staple);
				PDIsetpunch(sp_data[StaplePunch_Short].punch);
				if(sp_data[StaplePunch_Short].rotate)
					PDI1.orient = (PDI1.orient ^ 2);
			}
		}

	}
}
#endif /* defined(EMPCL5) || defined(EMPCLXL) */
#endif /* STAPLE_PUNCH_CONTROLED_BY_PDL */

#endif /* DEBUG */

#endif /* defined(EMPCL5) || defined(EMPCLXL) */
#endif /*#if 0*/


