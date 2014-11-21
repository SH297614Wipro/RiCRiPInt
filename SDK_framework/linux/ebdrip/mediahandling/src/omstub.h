#include "di_envdef.h"
#include "di_envdef_hand.h"
#include "device.h"
#include "mh.h"
#define EMPCL5 1
#define EMPCLXL 1
#define SYS_CHECK_DIRECTION 0
#define STAPLE_PUNCH_CONTROLED_BY_PDL 0
//#define TRAYSEARCHMODE_SWITCH 1	/*GPS env ID GPS_PENV_VAL_INT_TRAYSEARCHMODE_SWITCH is used instead of this macro*/
#define SUPPORT_INSERTER 0
#define EN_LIMITLESS_FEED 0
#define BYPASS_FREE_FEED 0
#define TRAY_OVERWRITING 0
#define PRINT_QUALITY_MODE 0
#define PJL_JOB_START_END 1
//#define PCLJOB 1          		/*replaced with current_pdlid=GPS_PDL_PCL*/
#define IPS_MEDIA_HANDLING 1
#define INSERTER_NOTSELECT 0
#define PCL5_CUSTOMSIZE_COMMAND 1
//#define GPS_PDL_PCL 9
#define SUPPORT_EDGE2EDGE 1
#define PCL_CUSTOM_EDGE2EDGE 1
#define RP_CUSTOMPAPERSIZE 1



/* Variables declarations with some default values */
#ifndef	TRUE
#define	TRUE	(1)
#endif

#ifndef	FALSE
#define	FALSE	(0)
#endif

#define	VAR_ID_QUALITYMODE		617
#define CHANGE_MEDIATYPE	0x01
#define CHANGE_QUALITYMODE	0x02
#define DI_CODE_NO_SIZE 128
#define _enum_EOT 26
#define _enum_None 0
#define PAPERSRC_ALL 7
//#define FRONTCOVERPRINT_OFF 0 	/*GPS env ID GPS_PENV_VAL_INT_FRONTCOVERPRINT_OFF is used instead of this macro*/
//#define FRONTCOVERPRINTTRAY_NONE 0 	/*GPS env ID GPS_PENV_VAL_INT_FRONTCOVERPRINTTRAY_NONE is used instead of this macro*/
//#define STAPLE_OFF 0 			/*GPS env ID GPS_PENV_VAL_INT_STAPLE_OFF is used instead of this macro*/
//#define PUNCH_OFF 0 			/*GPS env ID GPS_PENV_VAL_INT_PUNCH_OFF is used instead of this macro*/
#define PAGEOUTRANGE 999
#define DISCARDRANGE 0
#if 0
#define XRESOLUTION 600  /*PDI.xres*/
#define YRESOLUTION 600  /*PDI.yres*/
#endif

/* Paper Sizes */
#define PAPERSIZE_LONGLTR 25
#define PAPERSIZE_A4  26
#define PAPERSIZE_A3 27
#define PAPERSIZE_LETTER 2
#define PAPERSIZE_A4R 27
#define USE_INTERNAL_CUSTOMSIZE 101	 /*default custom value*/
#define PAPERSIZE_CUSTOM 101  		/*default custom value*/

/* Media Types */
#define MEDIATYPE_PLAIN 0
#define MEDIATYPE_AUTO 0
#define MEDIATYPE_RECYCLED 5
#define MEDIATYPE_PLAIN2 4

/* Tray Settings */
#define TRAYINSERTED_IN 1
#define TRAYLOCKED_LOCKED 1
#define TRAYINSERTED_INEMPTY 2
#define TRAYSETTING_COMMAND 3
//#define BYPASSTRAYSETTING_FREEMODE 1 		/*GPS env ID GPS_PENV_VAL_INT_BYPASSTRAYSETTING_FREEMODE is used instead of this macro*/
//#define BYPASSTRAYSETTING_CUSTOMFREEMODE 2 	/*GPS env ID GPS_PENV_VAL_INT_BYPASSTRAYSETTING_CUSTOMFREEMODE is used instead of this macro*/


/* Macro declarations for OM case statements */
#define XRES 0
#define YRES 1
#define OMSYSTEM 1
#define OMPRINTER 2
#define OMBITSPERPIXEL 3
#define OMPAPERSRC 4
#define OMPAPERSIZE 16
#define OMBYPASSTRAYSETTING 5
#define OMFRONTCOVERPRINT 6 
#define OMFRONTCOVERPRINTTRAY 17
#define OMREQPROCREASON 3
#define OMAUTOTRAYCHANGE2 7
#define OMTRAYSEARCHMODE  8 
#define OMBINDINGEDGE 10
#define OMEDGETOEDGE 15
#define OMDUPLEX 9
#define BIND_LONGEDGE 1
//#define BIND_SHORTEDGE 0 	/*GPS env ID GPS_PENV_VAL_INT_BINDING_SHORTEDGE is used instead of this macro*/
#define LONGEDGEFEED 10
#define OMPRINTER 2
#define OMSTAPLE 12
#define OMPUNCH 13
//#define PUNCH_OFF 0 		/*GPS env ID GPS_PENV_VAL_INT_PUNCH_OFF is used instead of this macro*/
/* Macro definitions for OM attributes in Search Path array */
#define OMTRAY1_SIZE  26
#define OMTRAY1_MEDIATYPE 0 
#define OMTRAY1_INSERTED 1
#define OMTRAY1 3
#define PAPERSRC_TRAY1 3 
#define OMTRAY1SETTING 3

#define OMTRAY2_SIZE 2
#define OMTRAY2_MEDIATYPE 1
#define OMTRAY2_INSERTED 1
#define OMTRAY2 4 
#define PAPERSRC_TRAY2 4 
#define OMTRAY2SETTING 4


#define OMTRAY3_SIZE 27
#define OMTRAY3_MEDIATYPE 2  
#define OMTRAY3_INSERTED 0
#define OMTRAY3 5
#define PAPERSRC_TRAY3 5
#define OMTRAY3SETTING 0

#define OMTRAY4_SIZE 1
#define OMTRAY4_MEDIATYPE 3
#define OMTRAY4_INSERTED 0
#define OMTRAY4 6
#define PAPERSRC_TRAY4 6
#define OMTRAY4SETTING 0

#define OMTRAY5_SIZE 3
#define OMTRAY5_MEDIATYPE 4
#define OMTRAY5_INSERTED 0
#define OMTRAY5 7
#define PAPERSRC_TRAY5 7
#define OMTRAY5SETTING 0

#define OMTRAY6_SIZE 24
#define OMTRAY6_MEDIATYPE 5
#define OMTRAY6_INSERTED 0
#define OMTRAY6 8 
#define PAPERSRC_TRAY6 8
#define OMTRAY6SETTING 0

#define OMTRAY7_SIZE 25 
#define OMTRAY7_MEDIATYPE 6
#define OMTRAY7_INSERTED 0        
#define OMTRAY7 9
#define PAPERSRC_TRAY7 9
#define OMTRAY7SETTING 0

#define OMTRAY8_SIZE 26
#define OMTRAY8_MEDIATYPE 7
#define OMTRAY8_INSERTED 0
#define OMTRAY8 10
#define PAPERSRC_TRAY8 10
#define OMTRAY8SETTING 0

#define OMTRAY9_SIZE 2
#define OMTRAY9_MEDIATYPE 8
#define OMTRAY9_INSERTED 0
#define OMTRAY9 11
#define PAPERSRC_TRAY9 11
#define OMTRAY9SETTING 0

#define OMTRAYA_SIZE 26
#define OMTRAYA_MEDIATYPE 9
#define OMTRAYA_INSERTED 0
#define OMTRAYA 12
#define PAPERSRC_TRAYA 12
#define OMTRAYASETTING 0
/*
#define OMBYPASS_SIZE 2
#define OMBYPASS_MEDIATYPE 10 
#define OMBYPASS_INSERTED 0
#define OMBYPASS 13
#define PAPERSRC_BYPASS 13
#define OMTBYPASSRAYSETTING 0
*/
#define PAPERSRC_BYPASS 0
#define FRONTCOVERPRINTTRAY_TRAY1 3
#define FRONTCOVERPRINTTRAY_TRAY2 4
#define FRONTCOVERPRINTTRAY_TRAY3 5
#define FRONTCOVERPRINTTRAY_TRAY4 6
#define FRONTCOVERPRINTTRAY_TRAY5 7
#define FRONTCOVERPRINTTRAY_TRAY6 8
#define FRONTCOVERPRINTTRAY_TRAY7 9
#define FRONTCOVERPRINTTRAY_TRAY8 10
#define FRONTCOVERPRINTTRAY_TRAY9 11
#define FRONTCOVERPRINTTRAY_TRAYA 12
#define FRONTCOVERPRINTTRAY_BYPASS 13
#define GPS_TRAY_LOCKED (1 << 3)
#define MAX_TABLE_SIZE      115

#define GET_PCL_SIZE     0
#define GET_OMCODE       1
#define GET_GPS_SIZE     2
OMenum XRESOLUTION, YRESOLUTION;

/*PAPERINFO structure variables are provided by RICOH*/
#if 0
typedef struct {
   OMenum size, printable, offset, nominal, nomoffset, rotnomsize, rotnomoffset,
   HPnomoffset, HProtnomoffset, PS_PageSize, PS_printable, PS_margins,
   resolution; /*  type is struct {short x, y;}. */
   unsigned short OMcode;
   unsigned short PCLpaperID;
   unsigned char XLpaperID;
   Boolean envelope, noduplex;
} PAPERINFO;
PAPERINFO temppaper[3];
#endif
struct PaperDimension{
int x;
int y;
};

typedef struct {
   struct PaperDimension size, printable, offset, nominal, nomoffset, rotnomsize, rotnomoffset,HPnomoffset, HProtnomoffset; /*  type is struct {short x, y;}. */
   unsigned short OMcode;
   unsigned short PCLpaperID;
   unsigned char XLpaperID;
   Boolean envelope, noduplex;
   struct PaperDimension PS_PageSize, PS_printable, PS_margins,resolution;
} PAPERINFO;
struct Pagesize_OMCode_t{
OMenum PCL5mediasize;
OMenum OMCode;
OMenum GPSmediasize;
} ;


//static PAPERCODE LastPaperSelect,LastPaperSize;
//static OMenum LastPaperSource,LastMediaType;
//static Sint8 ChoosePaperDirectionDone;

OMenum OMGetCurrentInt(OMenum omvar, OMenum omsystem);
OMEnum OMGetDefaultEnum(OMenum omvar, OMenum omsystem);
Boolean OMGetCurrentBool(OMenum omvar, OMenum omsystem);
OMenum Map_Page_Size(int size, int MapValue);
/*#ifndef IPS_MEDIA_HANDLING */
typedef struct {
		OMenum om_source; 
		OMenum om_size;
		OMenum om_mediatype;
		OMname om_stat;
		OMenum om_lock;
		OMenum om_frontcovertray;
#ifdef TRAY_OVERWRITING
		OMenum om_traysetting;
#endif
} search_path_t;
search_path_t *search_path;
#if 0    
= {
		{ PAPERSRC_TRAY1,  OMTRAY1_SIZE, OMTRAY1_MEDIATYPE,
		  OMTRAY1_INSERTED, OMTRAY1, FRONTCOVERPRINTTRAY_TRAY1
#ifdef TRAY_OVERWRITING
		  , OMTRAY1SETTING
#endif
		},
		{ PAPERSRC_TRAY2,  OMTRAY2_SIZE, OMTRAY2_MEDIATYPE,
		  OMTRAY2_INSERTED, OMTRAY2, FRONTCOVERPRINTTRAY_TRAY2
#ifdef TRAY_OVERWRITING
		  , OMTRAY2SETTING
#endif
		},
/*		{ PAPERSRC_LCT,    OMLCT_SIZE,   OMLCT_MEDIATYPE,
		  OMLCT_INSERTED, OMLCT, FRONTCOVERPRINTTRAY_LCT
#ifdef TRAY_OVERWRITING
		  , OMLCTSETTING
#endif
		},*/
		{ PAPERSRC_TRAY3,  OMTRAY3_SIZE, OMTRAY3_MEDIATYPE,
		  OMTRAY3_INSERTED, OMTRAY3, FRONTCOVERPRINTTRAY_TRAY3
#ifdef TRAY_OVERWRITING
		  , OMTRAY3SETTING
#endif
		},
		{ PAPERSRC_TRAY4,  OMTRAY4_SIZE, OMTRAY4_MEDIATYPE,
		  OMTRAY4_INSERTED, OMTRAY4, FRONTCOVERPRINTTRAY_TRAY4
#ifdef TRAY_OVERWRITING
		  , OMTRAY4SETTING
#endif
		},
		{ PAPERSRC_TRAY5,  OMTRAY5_SIZE, OMTRAY5_MEDIATYPE,
		  OMTRAY5_INSERTED, OMTRAY5, FRONTCOVERPRINTTRAY_TRAY5
#ifdef TRAY_OVERWRITING
		  , OMTRAY5SETTING
#endif
		},
		{ PAPERSRC_TRAY6,  OMTRAY6_SIZE, OMTRAY6_MEDIATYPE,
		  OMTRAY6_INSERTED, OMTRAY6, FRONTCOVERPRINTTRAY_TRAY6
#ifdef TRAY_OVERWRITING
		  , OMTRAY6SETTING
#endif
		},
		{ PAPERSRC_TRAY7,  OMTRAY7_SIZE, OMTRAY7_MEDIATYPE,
		  OMTRAY7_INSERTED, OMTRAY7, FRONTCOVERPRINTTRAY_TRAY7
#ifdef TRAY_OVERWRITING
		  , OMTRAY7SETTING
#endif
		},
		{ PAPERSRC_TRAY8,  OMTRAY8_SIZE, OMTRAY8_MEDIATYPE,
		  OMTRAY8_INSERTED, OMTRAY8, FRONTCOVERPRINTTRAY_TRAY8
#ifdef TRAY_OVERWRITING
		  , OMTRAY8SETTING
#endif
		},
		{ PAPERSRC_TRAY9,  OMTRAY9_SIZE, OMTRAY9_MEDIATYPE,
		  OMTRAY9_INSERTED, OMTRAY9, FRONTCOVERPRINTTRAY_TRAY9
#ifdef TRAY_OVERWRITING
		  , OMTRAY9SETTING
#endif
		},
		{ PAPERSRC_TRAYA,  OMTRAYA_SIZE, OMTRAYA_MEDIATYPE,
		  OMTRAYA_INSERTED, OMTRAYA, FRONTCOVERPRINTTRAY_TRAYA
#ifdef TRAY_OVERWRITING
		  , OMTRAYASETTING
#endif
		}
	/*	{ PAPERSRC_BYPASS, OMBYPASS_SIZE, OMBYPASS_MEDIATYPE,
		  OMBYPASS_INSERTED, OMBYPASS, FRONTCOVERPRINTTRAY_BYPASS
#ifdef TRAY_OVERWRITING
		  , OMBYPASSTRAYSETTING
#endif
		}*/
	};
#endif
#define	NSEARCH_PATH  5/* (sizeof(search_path[0]))   sizeof(search_path[0]))*/
/* Below Variable initializations are taken from MnPaper.c */
/*LastPaperSource = (OMenum)-1;
LastMediaType = (OMenum)-1;
LastPaperSelect = 0xFFFF;
LastPaperSize = 0xFFFF;*/

extern void PrintSysChangeResolution (Uint16 * xres, Uint16 * yres, Uint8 * bit);
extern Uint8 PrintSysCheckQualityMode (Sint32 * om_media, OMenum * om_qmode);
extern int PrintSysGetCustomSize(OMenum source, int xres, int yres, PAPERINFO *paper);
extern void PrintSysSetCustomSize(long p_width, long p_length, int xres, int yres);
extern void PrintSysGetMaxPaperSize(Sint32 *width, Sint32 *height);
extern void PRcustompaperinfo(int pwidth, int plength, int xres, int yres);
extern Boolean CheckSamePaperSize();
extern Boolean CheckSameCustomSize();
OMenum mnMediaSizeSelection(OMenum paper);
extern OMenum mnMediaSizeSelectionForInserter(OMenum paper);
extern Boolean PrintSysInserterMatchPaperSize(void);
extern int mnNonRotateDirection( ORIENTATION orient, int papersize, int xres, int yres );
extern OMenum mnSelectionByPreview(OMenum paper, int xres, int yres);
extern Sint32 searchBestPaperSource(OMenum code, OMenum mediatype, OMenum insert);
extern void choosePaperDirection(Sint32 *psize, OMenum longEdgePaper,
			 OMenum shortEdgePaper);
extern void mnGetCustomSize(OMenum tray, int xres, int yres, PAPERINFO *paper);
extern OMenum checkFinisherPrint(OMenum papersize, Sint32 longEdgeTray, Sint32 shortEdgeTray, ORIENTATION orient, int xres, int yres);
OMenum mnSelectionByChoosePaperSource(OMenum papersize, int xres, int yres);
OMenum mnSelectionByAutoPaperSource(OMenum papersize, int xres, int yres);
extern OMenum mnGetOMPaperSize(Sint32 code, int xres, int yres, int (*comp)());
extern void PRpaperPair (PAPERCODE OMsize, int xres, int yres, OMenum *LongEdge, OMenum *ShortEdge );
extern void PRcustompaperinfo(int pwidth, int plength, int xres, int yres);
extern const PAPERINFO * PRpaperfirst(Sint32 code, int xres, int yres, int (*comp)());
extern void PrintSysChoosePaperDirectionOnStaplePunch(Boolean *longEdgeTray,
											   Boolean *shortEdgeTray,
											   ORIENTATION orient);
extern int PrintSysPaperRequest( Sint32 *psize, Sint32 pwidth, Sint32 plength,
							OMenum ptype, Sint32 tray, Boolean direction);
extern void PrintSysSetCompulsionPaperSize( OMenum paper_size );
extern void PrintSysSetCompulsionInTray( OMenum tray );
extern unsigned char pcdOMtoGPSBinding( ORIENTATION orient, OMenum ombind );
extern PAPERINFO * PRpaperinfoOriginal (PAPERCODE size, int xres, int yres);
extern void SetQualityMode(OMenum r_qmode);
int PRpapertable(PAPERINFO *paper, int xres, int yres);
/*extern PAPERINFO * PRpaperinfo(PAPERCODE paper, int xres, int yres);*/
//int  PRpaperinfo(PAPERCODE paper, int xres, int yres);
PAPERINFO * PRpaperinfo(PAPERCODE paper, int xres, int yres);
extern Sint32 searchChoosePaperSource(OMenum tray_code);


int update_TrayInfo_fromGPS();
OMenum OMGetCurrentInt(OMenum omvar, OMenum omsystem);
OMEnum OMGetDefaultEnum(OMenum omvar, OMenum omsystem);
Boolean OMGetCurrentBool(OMenum omvar, OMenum omtype);
OMEnum OMCurrentEnum(OMenum omvar, OMenum omsystem);
extern int GetOrientation();
/*int GetBinding();*/
extern int GetDuplex();
int GetInserterTray();
//int CMDTYPE_PAPERSRC,CMDTYPE_OUTBIN;
typedef int CmdType; 
//typedef PMS_TyMedia OMenum;

void mnInitTrayBinCmd(CmdType type, OMenum * traybintbl, Uint32 ntraybin);
int PrintSysReinitTrayInfo(void);
int PrintSysReinitBinInfo(void); 

