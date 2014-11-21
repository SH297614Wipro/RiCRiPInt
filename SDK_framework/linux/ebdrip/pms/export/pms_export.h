/* Copyright (C) 2007-2014 Global Graphics Software Ltd. All rights reserved.
 *
 * This example is provided on an "as is" basis and without
 * warranty of any kind. Global Graphics Software Ltd. does not
 * warrant or make any representations regarding the use or results
 * of use of this example.
 *
 * $HopeName: GGEpms_gg_example!export:pms_export.h(EBDSDK_P.1) $
 *
 */

/*! \mainpage
 *  \ingroup PMS
 *  \brief PMS

  <b>Overview of PMS (Print Management System) Simulator</b>

  The PMS is a simulation of typical Print Management System which is responsible for submitting print
  jobs to RIP via OIL (OEM Interface Layer) and handling the Raster Outputs thrown back by the RIP.

  The generic implementation supports
  the following:\n
  main()\n
  PMS_ReadDataStream()\n
  StartOIL()\n
  PMS_CheckinPage()\n
  PrintPage()


  <b>How to use this document</b>

  You should refer to the File List section for an overview of the
  files and functions. You should then refer to the Data
  Structures section for an overview of the associated data structures.

  Note: This document is designed for online viewing, with lots of
  hyperlinks (blue text) allowing you to quickly jump to related
  information. We do not recommend that you print this document.
 */

/*! \file
 *  \ingroup PMS
 *  \brief Defines the PMS API.
 *
 */

#ifndef _PMS_EXPORT_H_
#define _PMS_EXPORT_H_

#ifndef PMS_OIL_MERGE_DISABLE
#include "oil.h"
#endif

#define DEBUG_LOGS 1

/* Custom/Test defined data that would be set up dependant on user requirements */
/* Remove the following definition if not using IMEM in the system */
#define HWA_USE_IMEM
/* HWA1 buffer max buffer size */
#define PMS_HWA1_BUFFER_SIZE            7864320 /* 7.5M */
/* HWA1 buffer max buffers */
#define PMS_HWA1_MAX_BUFFERS            2
/* Define this to be the required fixed base VDATAAD, or leave it undefined to
 * use our actual address. */
#define PMS_HWA1_FIXED_VDATAAD 0x100000
/* Define this to be the required fixed VCOMAD, or leave it undefined to use
 * our actual address */
#define PMS_HWA1_FIXED_VCOMAD 0x8000
/* Hacky fiddle to force single-band-per-page output. This is only for use with
 * the FPGA simulator. */
#define PMS_HWA1_ALL_ONE_BAND 1
/* Whether to define 'buffer assets' in their own block, or defer them until
 * the first band in the buffer. Define to defer, leave undefined to use a
 * separate block. */
#define PMS_HWA1_DEFER_BUFFER_ASSETS 0

/* PMS defined band height set up used for direct output (-j 3) and HWA */
#define PMS_BAND_HEIGHT                 128

#ifdef DEFAULT_PDL
/* TEC Level definitions */
enum {
  TECVALUETWO =0,
  TECVALUEONE,
  TECVALUENORMAL
};

//TEC mapping used by GPS 
#define GPS_FUSER_CTL_LEVEL2 (3) /* image processing Level 2 */
#define GPS_FUSER_CTL_LEVEL1 (1) /* image processing Level 1 */
#define GPS_FUSER_CTL_STD (0) /* standard image processing */
#endif

enum
{
  OMFONTSRC,              /**< font source */
  OMFONTNUMBER,           /**< font number */
  OMFONTPITCH,            /**< font pitch*/
  OMFONTSIZE,             /**< font size */
  OMSYMSET                /**< Symbol set*/
};
typedef int OPanel;
enum
{
DEFAULT_LEVEL=0,
CURRENT_LEVEL=1 
};
typedef int OPLevel;
enum
{
OrgRomSys=0,
OrgRomCart=1,
OrgRamDLL,
OrgRomDLL,
OrgSDDLL,
OrgRomSIMM
};
/*! \brief Printer Specific definition strings. */
#define PMS_PRINTER_MANUFACTURER "GG"
#define PMS_PRINTER_PRODUCT "SDK"

/* define  a path for the pdf to spool to on HDD when running a swinram build */
/* the root needs to be defined within two % characters e.g. c:  would be %c%. */
#ifdef WIN32
#define PMS_PDFSPOOL_DIR "%c%/temp/"
#else
#define PMS_PDFSPOOL_DIR "%/%/app/"
#endif

/*
Max path length for HDD path.
*/
#define GPS_MAX_HDD_PATH_LEN	64
/* Default path to directory to store and look for permanent PCL 5 resources. */
#ifdef WIN32
#define PMS_PCLRESOURCE_DIR "C:\\TEMP"
#else
#define PMS_PCLRESOURCE_DIR "/tmp"
#endif

/**
 * \brief List of function pointers to PMS callback functions.
 *
 * First one is assigned zero, and all others should not be assigned a value.
 * The
 */
enum {
  EPMS_FN_ReadDataStream = 0,  /**< Read (and consume) more job data. */ /* TODO: This is going to be removed very soon */
  EPMS_FN_PeekDataStream,      /**< Look at more job data. */
  EPMS_FN_ConsumeDataStream,   /**< Consume job data. */
  EPMS_FN_WriteDataStream,     /**< Write data. */
  EPMS_FN_CheckinPage,         /**< Check in page. */
  EPMS_FN_CheckinBand,         /**< Check in band. */
  EPMS_FN_DeletePrintedPage,
  EPMS_FN_CMYKtoCMYK,          /**< Gives PMS a chance to transform CMYK values. */
  EPMS_FN_RGBtoCMYK,           /**< Gives PMS a chance to transform RGB into CMYK values. */
  EPMS_FN_MediaSelect,
  EPMS_FN_GetPaperInfo,
  EPMS_FN_SetPaperInfo,
  EPMS_FN_GetMediaType,
  EPMS_FN_GetMediaSource,
  EPMS_FN_GetMediaDest,
  EPMS_FN_GetMediaColor,
  EPMS_FN_GetTrayInfo,
  EPMS_FN_SetTrayInfo,
  EPMS_FN_GetOutputInfo,
  EPMS_FN_GetScreenInfo,
  EPMS_FN_GetSystemInfo,
  EPMS_FN_SetSystemInfo,
  EPMS_FN_PutBackChannel,
  EPMS_FN_PutDebugMessage,
  EPMS_FN_GetBandInfo,
  EPMS_FN_RasterLayout,
  EPMS_FN_RasterRequirements,
  EPMS_FN_RasterDestination,
  EPMS_FN_RippingComplete,
  EPMS_FN_Malloc,
  EPMS_FN_Free,
  EPMS_FN_GetJobSettings,
  EPMS_FN_SetJobSettings,
  EPMS_FN_SetJobSettingsToDefaults,
  EPMS_FN_FSInitVolume,
  EPMS_FN_FSMkDir,
  EPMS_FN_FSOpen,
  EPMS_FN_FSRead,
  EPMS_FN_FSWrite,
  EPMS_FN_FSClose,
  EPMS_FN_FSSeek,
  EPMS_FN_FSDelete,
  EPMS_FN_FSDirEntryInfo,
  EPMS_FN_FSQuery,
  EPMS_FN_FSFileSystemInfo,
  EPMS_FN_FSGetDisklock,
  EPMS_FN_FSSetDisklock,
  EPMS_FN_GetResource,
  EPMS_FN_FileOpen,
  EPMS_FN_FileRead,
  EPMS_FN_FileClose,
  EPMS_FN_FileSeek,
  EPMS_FN_FileBytes,
  EPMS_FN_SetJobRIPConfig,
  EPMS_FN_PCL5ResourceStart,
  EPMS_FN_PCL5ResourceFinish,
  EPMS_FN_PCL5ResourceError,
  EPMS_FN_PCL5ResourceTransfer,

#if defined(USE_UFST5) || defined(USE_UFST7)
  /* The following CGIF calls simply give us exposure to
     the UFST module. */
  EPMS_FN_CGIFfco_Access,
  EPMS_FN_CGIFfco_Plugin,
  EPMS_FN_CGIFfco_Open,
  EPMS_FN_CGIFenter,
  EPMS_FN_CGIFconfig,
  EPMS_FN_CGIFinit,
  EPMS_FN_CGIFinitRomInfo,
  EPMS_FN_CGIFfco_Close,
  EPMS_FN_CGIFmakechar,
  EPMS_FN_CGIFchar_size,
  EPMS_FN_CGIFfont,
  EPMS_FN_PCLswapHdr,
  EPMS_FN_PCLswapChar,

  EPMS_FN_UFSTSetCallbacks,

  /* The following UFST functions get the raw data stored
     in the PS3, Wingdings and plugin fco support files. */
  EPMS_FN_UFSTGetPS3FontDataPtr,
  EPMS_FN_UFSTGetWingdingFontDataPtr,
  EPMS_FN_UFSTGetPluginDataPtr,
  EPMS_FN_UFSTGetSymbolSetDataPtr,
#endif

  EPMS_FN_HWA1_GetBuffer,
  EPMS_FN_HWA1_SubmitBuffer,
  EPMS_FN_HWA1_DiscardBuffer,
  EPMS_FN_HWA1_GetBands,
  EPMS_FN_HWA1_DiscardBands,
#ifdef DEFAULT_PDL

  EPMS_FN_TEC_SetLevel,
#endif

  PMS_TOTAL_NUMBER_OF_API_FUNCTIONS  /**< Always last, equal to number of PMS API functions. */

};
typedef int EPMSOILAPI;

/*! \brief Printer Specific definition strings. */
#define PMS_PRINTER_MANUFACTURER "GG"
#define PMS_PRINTER_PRODUCT "SDK"

/* define  a path for the pdf to spool to on HDD when running a swinram build */
/* the root needs to be defined within two % characters e.g. c:  would be %c%. */
#ifdef WIN32
#define PMS_PDFSPOOL_DIR "%c%/temp/"
#else
#define PMS_PDFSPOOL_DIR "%/%/app/"
#endif

/*! \brief Maximum number of band information element in band
 *  array. NOTE this number is greater than the OIL_BAND_LIMIT.
 *  as the direct band write to PMS uses the RIP defined band height
 * This gives a band number of approx 900 for a 1200 dpi Ledger output
 * Tempoarary change to allow 30 metre height with 128 lines per band
 */
/* #define PMS_BAND_LIMIT              1024 */
#define PMS_BAND_LIMIT              9457

/*! \brief Maximum hostname length. */
#define PMS_MAX_HOSTNAME_LENGTH     100

/*! \brief Maximum username length. */
#define PMS_MAX_USERNAME_LENGTH     100

/*! \brief Maximum length of job name. */
#define PMS_MAX_JOBNAME_LENGTH      256

/*! \brief Maximum length of image job filename. */
#define PMS_MAX_IMAGEFILENAME_LENGTH      256

/*! \brief Maximum length of Outpur Folder. */
#define PMS_MAX_OUTPUTFOLDER_LENGTH      256

/*! \brief Maximum number of media names. */
#define PMS_MEDIA_STRINGS           100

/*! \brief Maximum output type length. */
#define PMS_MAX_OUTPUTTYPE_LENGTH   30

/*! \brief Maximum colorant name length. */
#define PMS_MAX_COLORANTNAME_LENGTH 30

/*! \brief Maximum number of plane information elements in band array. */
#define PMS_MAX_PLANES_COUNT        4

/*! \brief Maximum length of name string.for Paper sizes*/
#define PMS_MAX_PAPERSIZE_LENGTH        16

/*! \brief Maximum length of MediaSource string. */
#define PMS_MAX_MEDIASRC_LENGTH        32

/*! \brief Maximum length of MediaDest string. */
#define PMS_MAX_MEDIADEST_LENGTH        32

/*! \brief Maximum length of MediaType string. */
#define PMS_MAX_MEDIATYPE_LENGTH        32

/*! \brief Maxmum length of MediaColor string. */
#define PMS_MAX_MEDIACOLOR_LENGTH        32

/*! \brief Maxmum valid planes for different color families. rgb=3, cmyk=4, gray=1 */
#define PMS_MAX_VALID_PLANES_COUNT(x)   ((x==PMS_ColorantFamily_RGB)? 3:((x==PMS_ColorantFamily_CMYK)? 4:1))

/*! \brief Maxmum length of string for System Info definition for Printer Manufacturer and Product */
#define PMS_MAX_PRINTER_DEF_STRING        50


/*! \brief Enumeration of personalities
 */
enum {
  PMS_PERSONALITY_NONE = 0,
  PMS_PERSONALITY_AUTO,
  PMS_PERSONALITY_PS,
  PMS_PERSONALITY_PDF,
  PMS_PERSONALITY_XPS,
  PMS_PERSONALITY_PCL5,
  PMS_PERSONALITY_PCLXL
};
typedef int PMS_ePersonality;

#ifdef PMS_OIL_MERGE_DISABLE
/*! \brief Enumeration of test pages
 */
enum {
  PMS_TESTPAGE_NONE = 0,
  PMS_TESTPAGE_CFG,
  PMS_TESTPAGE_PS,
  PMS_TESTPAGE_PCL
};
typedef int PMS_eTestPage;
#endif

/*! \brief Output methods.
*/
enum {
    PMS_TIFF,           /**< Output to TIFF */
    PMS_TIFF_SEP,       /**< Output to separated TIFF */
    PMS_TIFF_VIEW,      /**< Output to TIFF and View*/
    PMS_PDF,            /**< Output to PDF */
    PMS_PDF_VIEW,       /**< Output to PDF and View*/
    PMS_DIRECT_PRINT,   /**< Output to PCL 5 to default printer*/
    PMS_DIRECT_PRINTXL, /**< Output to PCL XL to default printer*/
    PMS_NONE,           /**< Output to None */
};
typedef int PMS_eOutputType;

/*! \brief Band delivery methods.
*/
enum {
    PMS_PUSH_PAGE,        /**< OIL should push page into PMS */
    PMS_PULL_BAND,        /**< PMS will Pull Bands from OIL */
    PMS_PUSH_BAND,        /**< OIL should push bands(on the fly) into PMS */
    PMS_PUSH_BAND_DIRECT_SINGLE, /**< The RIP should render directly into memory provided by the PMS, one band at a time. */
    PMS_PUSH_BAND_DIRECT_FRAME,  /**< The RIP should render directly into memory provided by the PMS, which is part of a framebuffer. The framebuffer can also be used to store the results of partial paints, which has large performance advantages. */
};
typedef int PMS_eBandDeliveryType;

/*! \brief Colorant Families.
*/
enum {
    PMS_ColorantFamily_CMYK = 1,
    PMS_ColorantFamily_RGB,
    PMS_ColorantFamily_Gray,
    PMS_ColorantFamily_Unsupported,
};
typedef int PMS_eTyColorantFamily;

/*! \brief Page states.
*/
enum {
    PMS_CREATED,        /**< The Page has been created */
    PMS_CHECKEDIN,      /**< The Page has been checked-in */
    PMS_PRINTING,       /**< The Page is currently in printing process */
    PMS_COMPLETE        /**< The processing of the Page is complete */
};
typedef int PMS_ePageState;

#ifdef PMS_OIL_MERGE_DISABLE
/*! \brief Colourants
*/
enum {
    PMS_CYAN,         /**< PMS Cyan */
    PMS_MAGENTA,      /**< PMS Magenta */
    PMS_YELLOW,       /**< PMS Yellow */
    PMS_BLACK,        /**< PMS Black */
    PMS_RED,          /**< PMS Red */
    PMS_GREEN,        /**< PMS Green */
    PMS_BLUE,         /**< PMS Blue */
    PMS_INVALID_COLOURANT
};
typedef int PMS_eColourant;
#endif

/* WIDE A4 definitions used in oil_psconfig.c */
#define PRINTABLEAREAWIDEA4  "[9.6 9.6 12 12]"
#define LOGICALPAGE40PX  "[9.6 9.6 9.6 9.6]"
#define MICROINCHTOPOINTS  0.000072

#define NUMFIXEDMEDIASIZES 14
/* Update the number above to the number of fixed portrait paper sizes in enum table */
/* This is used for setting up the PCL configuration data in oil_psconfig.c */
/* The actual definition table in pms_interface_oil2pms.c must match the definitions here */
/*! \brief Page sizes defined in PMS.
*/
#if 0
enum
{
  PMS_SIZE_LETTER = 0,          /**< Letter paper size */
  PMS_SIZE_A4,                  /**< A4 paper size */
  PMS_SIZE_LEGAL,               /**< Legal paper size */
  PMS_SIZE_EXE,                 /**< Executive paper size */
  PMS_SIZE_A3,                  /**< A3 paper size */
  PMS_SIZE_TABLOID,             /**< Tabloid paper size */
  PMS_SIZE_A5,                  /**< A5 paper size */
  PMS_SIZE_A6,                  /**< A6 paper size */
  PMS_SIZE_C5_ENV,              /**< C5 Envelope paper size */
  PMS_SIZE_DL_ENV,              /**< DL Envelope paper size */
  PMS_SIZE_LEDGER,              /**< Ledger paper size */
  PMS_SIZE_OFUKU ,              /**< Ofuku paper size */
  PMS_SIZE_JISB4 ,              /**< JIS B4 paper size */
  PMS_SIZE_JISB5 ,              /**< JIS B5 paper size */

  /* Landscape feed sizes */
  PMS_SIZE_LETTER_R,            /**< Letter rotated paper size */
  PMS_SIZE_A4_R,                /**< A4 rotated paper size */
  PMS_SIZE_LEGAL_R,             /**< Legal rotated paper size */
  PMS_SIZE_EXE_R,               /**< Executive rotated paper size */
  PMS_SIZE_A3_R,                /**< A3 rotated paper size */
  PMS_SIZE_TABLOID_R,           /**< Tabloid rotated paper size */
  PMS_SIZE_A5_R,                /**< A5 rotated paper size */
  PMS_SIZE_A6_R,                /**< A6 rotated paper size */
  PMS_SIZE_C5_ENV_R,            /**< C5 Envelope rotated paper size */
  PMS_SIZE_DL_ENV_R,            /**< DL Envelope rotated paper size */
  PMS_SIZE_LEDGER_R,            /**< Ledger rotated paper size */
  PMS_SIZE_OFUKU_R ,            /**< Ofuku rotated paper size */
  PMS_SIZE_JISB4_R ,            /**< JIS B4 rotated paper size */
  PMS_SIZE_JISB5_R ,            /**< JIS B5 rotated paper size */

  /* The following two items must remain in this order CUSTOM - DONT_KNOW */
  PMS_SIZE_CUSTOM,              /**< Custom paper size */
  PMS_SIZE_DONT_KNOW            /**< PaperSize not known*/
};
#endif

enum
{
	PMS_SIZE_NO_PAPER = 0,
	PMS_SIZE_A0,		PMS_SIZE_A1,		PMS_SIZE_A2,		PMS_SIZE_A3,
	PMS_SIZE_A4,		PMS_SIZE_A5,		PMS_SIZE_A6,		PMS_SIZE_A7,
	PMS_SIZE_B0,		PMS_SIZE_B1,		PMS_SIZE_B2,		PMS_SIZE_B3,
	PMS_SIZE_B4,		PMS_SIZE_B5,		PMS_SIZE_B6,		PMS_SIZE_B7,
	PMS_SIZE_WMAIL,		PMS_SIZE_MAIL,		PMS_SIZE_LINE1,		PMS_SIZE_LINE2,
	PMS_SIZE_LIB6,		PMS_SIZE_LIB8,		PMS_SIZE_210x170,	PMS_SIZE_210x182,
	PMS_SIZE_267x388,	PMS_SIZE_SRA3,
	PMS_SIZE_SRA4,

	PMS_SIZE_FREEmm = 31,
	PMS_SIZE_11x17,
	PMS_SIZE_11x14,		PMS_SIZE_10x15,		PMS_SIZE_10x14,		PMS_SIZE_8Hx14,
	PMS_SIZE_8Hx13,		PMS_SIZE_8Hx11,		PMS_SIZE_8Qx14,		PMS_SIZE_8Qx13,
	PMS_SIZE_8x13,		PMS_SIZE_8x10H,		PMS_SIZE_8x10,		PMS_SIZE_5Hx8H,
	PMS_SIZE_7Qx10H,	PMS_SIZE_17x22,

	PMS_SIZE_12x18 = 47,
	PMS_SIZE_12x14H,
	PMS_SIZE_11x15,		PMS_SIZE_9Hx11,		 PMS_SIZE_8Hx12,	PMS_SIZE_13x19,
	PMS_SIZE_13x19Q,	PMS_SIZE_13x18,

	PMS_SIZE_36x48 = 55,
	PMS_SIZE_24x36,		PMS_SIZE_18x24,		PMS_SIZE_9x12,

	PMS_SIZE_34x44 = 60,
	PMS_SIZE_22x34,		PMS_SIZE_30x42,		PMS_SIZE_21x30,

	PMS_SIZE_8KAI = 66,
	PMS_SIZE_16KAI,

	PMS_SIZE_12_6x18_5 = 70,
	PMS_SIZE_12_6x19_2,

	PMS_SIZE_NO_10 = 80,
	PMS_SIZE_NO_7,

	PMS_SIZE_C5 = 83,
	PMS_SIZE_C6,		PMS_SIZE_DL,

	PMS_SIZE_841mmRoll = 97,
	PMS_SIZE_594mmRoll,	PMS_SIZE_420mmRoll,	PMS_SIZE_297mmRoll,	PMS_SIZE_210mmRoll,
	PMS_SIZE_660mmRoll,	PMS_SIZE_440mmRoll,	PMS_SIZE_880mmRoll,	PMS_SIZE_800mmRoll,

	PMS_SIZE_728mmRoll,	PMS_SIZE_515mmRoll,	PMS_SIZE_364mmRoll,	PMS_SIZE_257mmRoll,
	PMS_SIZE_182mmRoll,	PMS_SIZE_625mmRoll,

	PMS_SIZE_YOH_ENV_0 = 112,
	PMS_SIZE_YOH_ENV_2, PMS_SIZE_YOH_ENV_4, PMS_SIZE_JAPANESE_ENV_3, PMS_SIZE_JAPANESE_ENV_4,
	PMS_SIZE_KAKU_ENV_2 = 119,

	PMS_SIZE_226x310 = 121,
	PMS_SIZE_310x432,

	PMS_SIZE_NO_SIZE = 128,
	PMS_SIZE_A0T,		PMS_SIZE_A1T,		PMS_SIZE_A2T,		PMS_SIZE_A3T,
	PMS_SIZE_A4T,		PMS_SIZE_A5T,		PMS_SIZE_A6T,		PMS_SIZE_A7T,
	PMS_SIZE_B0T,		PMS_SIZE_B1T,		PMS_SIZE_B2T,		PMS_SIZE_B3T,
	PMS_SIZE_B4T,		PMS_SIZE_B5T,		PMS_SIZE_B6T,		PMS_SIZE_B7T,
	PMS_SIZE_WMAILT,	PMS_SIZE_MAILT,		PMS_SIZE_LINE1T,	PMS_SIZE_LINE2T,
	PMS_SIZE_LIB6T,		PMS_SIZE_LIB8T,		PMS_SIZE_210x170T,	PMS_SIZE_210x182T,
	PMS_SIZE_267x388T,	PMS_SIZE_SRA3T,
	PMS_SIZE_SRA4T,

	PMS_SIZE_FREEmmT = 159,
	PMS_SIZE_11x17T,
	PMS_SIZE_11x14T,	PMS_SIZE_10x15T,	PMS_SIZE_10x14T,	PMS_SIZE_8Hx14T,
	PMS_SIZE_8Hx13T,	PMS_SIZE_8Hx11T,	PMS_SIZE_8Qx14T,	PMS_SIZE_8Qx13T,
	PMS_SIZE_8x13T,		PMS_SIZE_8x10HT,	PMS_SIZE_8x10T,		PMS_SIZE_5Hx8HT,
	PMS_SIZE_7Qx10HT,	PMS_SIZE_17x22T,

	PMS_SIZE_12x18T = 175,
	PMS_SIZE_12x14HT,
	PMS_SIZE_11x15T,	PMS_SIZE_9Hx11T,	 PMS_SIZE_8Hx12T,	PMS_SIZE_13x19T,
	PMS_SIZE_13x19QT,	PMS_SIZE_13x18T,

	PMS_SIZE_36x48T = 183,
	PMS_SIZE_24x36T,	PMS_SIZE_18x24T,	PMS_SIZE_9x12T,

	PMS_SIZE_34x44T = 188,
	PMS_SIZE_22x34T,	PMS_SIZE_30x42T,	PMS_SIZE_21x30T,

	PMS_SIZE_8KAIT = 194,
	PMS_SIZE_16KAIT,

	PMS_SIZE_12_6x18_5T = 198,
	PMS_SIZE_12_6x19_2T,

	PMS_SIZE_NO_10T = 208,
	PMS_SIZE_NO_7T,

	PMS_SIZE_C5T = 211,
	PMS_SIZE_C6T,		PMS_SIZE_DL_T,

	PMS_SIZE_36inchRoll = 225,
	PMS_SIZE_24inchRoll,	PMS_SIZE_18inchRoll,	PMS_SIZE_12inchRoll,	PMS_SIZE_9inchRoll,
	PMS_SIZE_30inchRoll,	PMS_SIZE_707mmRoll,

	PMS_SIZE_490mmRoll = 232,
	PMS_SIZE_680mmRoll,		PMS_SIZE_34inchRoll,	PMS_SIZE_22inchRoll,	PMS_SIZE_17inchRoll,
	PMS_SIZE_11inchRoll,	PMS_SIZE_8HinchRoll,	PMS_SIZE_620mmRoll,

	PMS_SIZE_YOH_ENV_0T = 240,
	PMS_SIZE_YOH_ENV_2T, PMS_SIZE_YOH_ENV_4T, PMS_SIZE_JAPANESE_ENV_3T, PMS_SIZE_JAPANESE_ENV_4T,
	PMS_SIZE_KAKU_ENV_2T = 247,

	PMS_SIZE_226x310T = 249,
	PMS_SIZE_310x432T,
	/* adding temporarily , yet to be mapped to the apprpriate GPS macro*/
	 PMS_SIZE_LEDGER,              /**< Ledger paper size */
     PMS_SIZE_OFUKU ,              /**< Ofuku paper size */
     PMS_SIZE_JISB5 ,              /**< JIS B5 paper size */
	 PMS_SIZE_LEDGER_R,			  /**< Ledger rotated paper size */
	 PMS_SIZE_OFUKU_R ,			/**< Ofuku rotated paper size */
	 PMS_SIZE_JISB5_R ,			/**< JIS B5 rotated paper size */
	/* The following two items must remain in this order CUSTOM - DONT_KNOW */
    PMS_SIZE_CUSTOM,              /**< Custom paper size */
    PMS_SIZE_DONT_KNOW            /**< PaperSize not known*/
};
typedef int PMS_ePaperSize;

enum
{
  PMS_PCL5_NO_PAPER = 0,
  PMS_PCL5_EXE = 1,             /**< Executive paper size */
  PMS_PCL5_LETTER = 2,              /**< Letter paper size */
  PMS_PCL5_LEGAL = 3,               /**< Legal paper size */
  PMS_PCL5_LEDGER = 6,          /**< Ledger paper size */
  PMS_PCL5_A6 = 24,             /**< A6 paper size */
  PMS_PCL5_A5 = 25,                  /**< A5 paper size */
  PMS_PCL5_A4 = 26,                  /**< A4 paper size */
  PMS_PCL5_A3 = 27,                  /**< A3 paper size */
  PMS_PCL5_JISB5 = 45 ,         /**< JISB5  paper size */
  PMS_PCL5_JISB4 = 46 ,         /**< JISB4  paper size */
  PMS_PCL5_OFUKU = 72,          /**< Ofuku paper size */
  PMS_PCL5_DL_ENV = 90,         /**< DL Envelope paper size */
  PMS_PCL5_C5_ENV = 91,              /**< C5 Envelope paper size */
  PMS_PCL5_CUSTOM = 101,        /**< Custom Envelope paper size */
  PMS_PCL5_TABLOID,              /**< Unknown value for PCL5???*/
  
  /**<New Addition*/
	PMS_PCL5_A0,		PMS_PCL5_A1,		PMS_PCL5_A2,		PMS_PCL5_A7,
	PMS_PCL5_B0,		PMS_PCL5_B1,		PMS_PCL5_B2,		PMS_PCL5_B3,
	PMS_PCL5_B4,		PMS_PCL5_B5,		PMS_PCL5_B6,		PMS_PCL5_B7,
	PMS_PCL5_WMAIL,		PMS_PCL5_MAIL,		PMS_PCL5_LINE1,		PMS_PCL5_LINE2,
	PMS_PCL5_LIB6,		PMS_PCL5_LIB8,		PMS_PCL5_210x170,	PMS_PCL5_210x182,
	PMS_PCL5_267x388,	PMS_PCL5_SRA3,
	PMS_PCL5_SRA4,

	PMS_PCL5_FREEmm,
	PMS_PCL5_11x17,
	PMS_PCL5_11x14,		PMS_PCL5_10x15,		PMS_PCL5_10x14,		PMS_PCL5_8Hx14,
	PMS_PCL5_8Hx13,		PMS_PCL5_8Hx11,		PMS_PCL5_8Qx14,		PMS_PCL5_8Qx13,
	PMS_PCL5_8x13,		PMS_PCL5_8x10H,		PMS_PCL5_8x10,		PMS_PCL5_5Hx8H,
	PMS_PCL5_7Qx10H,	PMS_PCL5_17x22,

	PMS_PCL5_12x18,
	PMS_PCL5_12x14H,
	PMS_PCL5_11x15,		PMS_PCL5_9Hx11,		 PMS_PCL5_8Hx12,	PMS_PCL5_13x19,
	PMS_PCL5_13x19Q,	PMS_PCL5_13x18,

	PMS_PCL5_36x48,
	PMS_PCL5_24x36,		PMS_PCL5_18x24,		PMS_PCL5_9x12,

	PMS_PCL5_34x44,
	PMS_PCL5_22x34,		PMS_PCL5_30x42,		PMS_PCL5_21x30,

	PMS_PCL5_8KAI,
	PMS_PCL5_16KAI,

	PMS_PCL5_12_6x18_5,
	PMS_PCL5_12_6x19_2,

	PMS_PCL5_NO_10,
	PMS_PCL5_NO_7,

	PMS_PCL5_C5,
	PMS_PCL5_C6,		PMS_PCL5_DL,

	PMS_PCL5_841mmRoll,
	PMS_PCL5_594mmRoll,	PMS_PCL5_420mmRoll,	PMS_PCL5_297mmRoll,	PMS_PCL5_210mmRoll,
	PMS_PCL5_660mmRoll,	PMS_PCL5_440mmRoll,	PMS_PCL5_880mmRoll,	PMS_PCL5_800mmRoll,

	PMS_PCL5_728mmRoll,	PMS_PCL5_515mmRoll,	PMS_PCL5_364mmRoll,	PMS_PCL5_257mmRoll,
	PMS_PCL5_182mmRoll,	PMS_PCL5_625mmRoll,

	PMS_PCL5_YOH_ENV_0,
	PMS_PCL5_YOH_ENV_2, PMS_PCL5_YOH_ENV_4, PMS_PCL5_JAPANESE_ENV_3, PMS_PCL5_JAPANESE_ENV_4,
	PMS_PCL5_KAKU_ENV_2,

	PMS_PCL5_226x310,
	PMS_PCL5_310x432,

	PMS_PCL5_NO_SIZE,
	PMS_PCL5_A0T,		PMS_PCL5_A1T,		PMS_PCL5_A2T,		PMS_PCL5_A3T,
	PMS_PCL5_A4T,		PMS_PCL5_A5T,		PMS_PCL5_A6T,		PMS_PCL5_A7T,
	PMS_PCL5_B0T,		PMS_PCL5_B1T,		PMS_PCL5_B2T,		PMS_PCL5_B3T,
	PMS_PCL5_B4T,		PMS_PCL5_B5T,		PMS_PCL5_B6T,		PMS_PCL5_B7T,
	PMS_PCL5_WMAILT,	PMS_PCL5_MAILT,		PMS_PCL5_LINE1T,	PMS_PCL5_LINE2T,
	PMS_PCL5_LIB6T,		PMS_PCL5_LIB8T,		PMS_PCL5_210x170T,	PMS_PCL5_210x182T,
	PMS_PCL5_267x388T,	PMS_PCL5_SRA3T,
	PMS_PCL5_SRA4T,

	PMS_PCL5_FREEmmT,
	PMS_PCL5_11x17T,
	PMS_PCL5_11x14T,	PMS_PCL5_10x15T,	PMS_PCL5_10x14T,	PMS_PCL5_8Hx14T,
	PMS_PCL5_8Hx13T,	PMS_PCL5_8Hx11T,	PMS_PCL5_8Qx14T,	PMS_PCL5_8Qx13T,
	PMS_PCL5_8x13T,		PMS_PCL5_8x10HT,	PMS_PCL5_8x10T,		PMS_PCL5_5Hx8HT,
	PMS_PCL5_7Qx10HT,	PMS_PCL5_17x22T,

	PMS_PCL5_12x18T,
	PMS_PCL5_12x14HT,
	PMS_PCL5_11x15T,	PMS_PCL5_9Hx11T,	 PMS_PCL5_8Hx12T,	PMS_PCL5_13x19T,
	PMS_PCL5_13x19QT,	PMS_PCL5_13x18T,

	PMS_PCL5_36x48T,
	PMS_PCL5_24x36T,	PMS_PCL5_18x24T,	PMS_PCL5_9x12T,

	PMS_PCL5_34x44T,
	PMS_PCL5_22x34T,	PMS_PCL5_30x42T,	PMS_PCL5_21x30T,

	PMS_PCL5_8KAIT,
	PMS_PCL5_16KAIT,

	PMS_PCL5_12_6x18_5T,
	PMS_PCL5_12_6x19_2T,

	PMS_PCL5_NO_10T,
	PMS_PCL5_NO_7T,

	PMS_PCL5_C5T,
	PMS_PCL5_C6T,		PMS_PCL5_DL_T,

	PMS_PCL5_36inchRoll,
	PMS_PCL5_24inchRoll,	PMS_PCL5_18inchRoll,	PMS_PCL5_12inchRoll,	PMS_PCL5_9inchRoll,
	PMS_PCL5_30inchRoll,	PMS_PCL5_707mmRoll,

	PMS_PCL5_490mmRoll,
	PMS_PCL5_680mmRoll,		PMS_PCL5_34inchRoll,	PMS_PCL5_22inchRoll,	PMS_PCL5_17inchRoll,
	PMS_PCL5_11inchRoll,	PMS_PCL5_8HinchRoll,	PMS_PCL5_620mmRoll,

	PMS_PCL5_YOH_ENV_0T,
	PMS_PCL5_YOH_ENV_2T, PMS_PCL5_YOH_ENV_4T, PMS_PCL5_JAPANESE_ENV_3T, PMS_PCL5_JAPANESE_ENV_4T,
	PMS_PCL5_KAKU_ENV_2T,

	PMS_PCL5_226x310T,
	PMS_PCL5_310x432T
};
typedef int PMS_ePCL5size;

enum
{
  PMS_PCLX_CUSTOM = -1,         /* not used in PCLXL */
  PMS_PCLX_LETTER = 0,          /**< Letter paper size */
  PMS_PCLX_LEGAL = 1,               /**< Legal paper size */
  PMS_PCLX_A4 = 2,                  /**< A4 paper size */
  PMS_PCLX_EXE = 3,                 /**< Executive paper size */
  PMS_PCLX_LEDGER = 4,              /**< Ledger paper size */
  PMS_PCLX_A3 = 5,                  /**< A3 paper size */
  PMS_PCLX_C5_ENV = 8,          /**< C5 Envelope paper size */
  PMS_PCLX_DL_ENV = 9,              /**< DL Envelope paper size */
  PMS_PCLX_JISB4 = 10 ,         /**< JISB4  paper size */
  PMS_PCLX_JISB5 = 11 ,         /**< JISB5  paper size */
  PMS_PCLX_A5 = 16,             /**< A5 paper size */
  PMS_PCLX_A6 = 17,                  /**< A6 paper size */
  PMS_PCLX_DEFAULT = 96,        /**< Default paper size */
  PMS_PCLX_OFUKU,               /**< Unknown value for PCLXL???*/
  PMS_PCLX_TABLOID              /**< Unknown value for PCLXL???*/
};
typedef int PMS_ePCLXLsize;

#define NUMFIXEDMEDIATYPES 13
/* Update the number above to the number of fixed media types in enum table */
/* This is used for setting up the PCL configuration data in oil_psconfig.c */
/* The actual definition table in pms_interface_oil2pms.c must match the definitions here */
/*! \brief Media types defined in PMS.
*/
#if 0
enum
{
  PMS_TYPE_PLAIN = 0,               /**< Plain media type */
  PMS_TYPE_BOND,                /**< Bond media type */
  PMS_TYPE_SPECIAL,             /**< Special media type */
  PMS_TYPE_GLOSSY,              /**< Glossy media type */
  PMS_TYPE_TRANSPARENCY,        /**< Transparency media type */
  PMS_TYPE_RECYCLED,            /**< Recycled media type */
  PMS_TYPE_THICK,               /**< Thick media type */
  PMS_TYPE_ENVELOPE,            /**< Envelope media type */
  PMS_TYPE_POSTCARD,            /**< Postcard media type */
  PMS_TYPE_THIN,                /**< Thin media type */
  PMS_TYPE_LABEL,               /**< Label media type */
  PMS_TYPE_PREPRINTED,          /**< Preprinted media type */
  PMS_TYPE_LETTERHEAD,          /**< Letterhead media type */
  PMS_TYPE_DONT_KNOW            /**< Media type not known*/
};
#endif
enum
{
 //PMS_TYPE_AUTO=1, 	
 PMS_TYPE_NORMAL=1,
 PMS_TYPE_RECYCLE,			
 PMS_TYPE_SPECIAL,			
 PMS_TYPE_TRACING,			
 PMS_TYPE_OHP,		
 PMS_TYPE_LABEL,			
 PMS_TYPE_BOND,			
 PMS_TYPE_CARDSTOCK,		
 PMS_TYPE_CARDBOARD,		
 PMS_TYPE_PREPRINT,		
 PMS_TYPE_LETTER_HEAD,		
 PMS_TYPE_PUNCH,
 PMS_TYPE_TAB,			
 PMS_TYPE_COLOR,			
 PMS_TYPE_NORMAL2ND,		
 PMS_TYPE_CARDBOARD2ND,		
 PMS_TYPE_THIN,
 PMS_TYPE_GLOSSY, 			
 PMS_TYPE_USED,			
 PMS_TYPE_POSTCARD,			
 PMS_TYPE_POSTCARD2ND,		
 PMS_TYPE_CARDBOARD2,	
 PMS_TYPE_FILM,		
 PMS_TYPE_INKPOST,			
 PMS_TYPE_HG_NORMAL,		
 PMS_TYPE_ENVELOPE,		
 PMS_TYPE_CARDBOARD3,		
 PMS_TYPE_SPECIAL2,		
 PMS_TYPE_SPECIAL3,		
 PMS_TYPE_MIDDLETHICK,		
 PMS_TYPE_COATED,	
 PMS_TYPE_CARDBOARD2REV,
 PMS_TYPE_CARDBOARD3REV,
 PMS_TYPE_NORMAL2,	
 PMS_TYPE_THICKGLOSSY,
 PMS_TYPE_SPECIAL4,	
 PMS_TYPE_SPECIAL5,		
 PMS_TYPE_SPECIAL6,		

 PMS_TYPE_USER_DEF1=48,				
 PMS_TYPE_USER_DEF2,				
 PMS_TYPE_USER_DEF3,			
 PMS_TYPE_USER_DEF4,			
 PMS_TYPE_USER_DEF5,			
 PMS_TYPE_USER_DEF6,			
 PMS_TYPE_USER_DEF7,			
 PMS_TYPE_USER_DEF8,			
 PMS_TYPE_USER_DEF0,			

 PMS_TYPE_COLOR1=64,	
 PMS_TYPE_COLOR2,		

 PMS_TYPE_COLOR_WHITE=80,
 PMS_TYPE_COLOR_YELLOW,
 PMS_TYPE_COLOR_GREEN,
 PMS_TYPE_COLOR_BLUE,
 PMS_TYPE_COLOR_PURPLE,
 PMS_TYPE_COLOR_IVORY,
 PMS_TYPE_COLOR_ORANGE,
 PMS_TYPE_COLOR_PINK,
 PMS_TYPE_COLOR_RED,
 PMS_TYPE_COLOR_GRAY,

 PMS_TYPE_GLOSSY_COATED,
 PMS_TYPE_THICK_GLOSSY_COATED,
 PMS_TYPE_MAT_COATED,
 PMS_TYPE_THICK_MAT_COATED,
 PMS_TYPE_WATER_PROOF,	
 PMS_TYPE_CARDBOARD4,		
 PMS_TYPE_CARDBOARD4REV,
 PMS_TYPE_COATED_HIGH_GLOSSY,

 PMS_TYPE_SEMIGLOSSY,	
 PMS_TYPE_INKJETPLAIN,
 PMS_TYPE_MONO_TRACING,
 PMS_TYPE_COLOR_TRACING,
 PMS_TYPE_MATFILM,		
 PMS_TYPE_CADCOATED,

 PMS_TYPE_NONE=128,				

 PMS_TYPE_USER_DEF9,
 PMS_TYPE_USER_DEF10,
 PMS_TYPE_USER_DEF11,
 PMS_TYPE_USER_DEF12,
 PMS_TYPE_USER_DEF13,
 PMS_TYPE_USER_DEF14,
 PMS_TYPE_USER_DEF15,
 PMS_TYPE_USER_DEF16,
 PMS_TYPE_USER_DEF17,
 PMS_TYPE_USER_DEF18,
 PMS_TYPE_USER_DEF19,
 PMS_TYPE_USER_DEF20,
 PMS_TYPE_USER_DEF21,
 PMS_TYPE_USER_DEF22,			
 PMS_TYPE_USER_DEF23,			
 PMS_TYPE_USER_DEF24,			
 PMS_TYPE_USER_DEF25,			
 PMS_TYPE_USER_DEF26,			
 PMS_TYPE_USER_DEF27,			
 PMS_TYPE_USER_DEF28,			
 PMS_TYPE_USER_DEF29,			
 PMS_TYPE_USER_DEF30,			
 PMS_TYPE_USER_DEF31,			
 PMS_TYPE_USER_DEF32,			
 PMS_TYPE_USER_DEF33,			
 PMS_TYPE_USER_DEF34,			
 PMS_TYPE_USER_DEF35,			
 PMS_TYPE_USER_DEF36,			
 PMS_TYPE_USER_DEF37,			
 PMS_TYPE_USER_DEF38,			
 PMS_TYPE_USER_DEF39,			
 PMS_TYPE_USER_DEF40,			
 PMS_TYPE_USER_DEF41,			
 PMS_TYPE_USER_DEF42,			
 PMS_TYPE_USER_DEF43,			
 PMS_TYPE_USER_DEF44,			
 PMS_TYPE_USER_DEF45,			
 PMS_TYPE_USER_DEF46,			
 PMS_TYPE_USER_DEF47,			
 PMS_TYPE_USER_DEF48,			
 PMS_TYPE_USER_DEF49,			
 PMS_TYPE_USER_DEF50,			
 PMS_TYPE_USER_DEF51,			
 PMS_TYPE_USER_DEF52,			
 PMS_TYPE_USER_DEF53,			
 PMS_TYPE_USER_DEF54,			
 PMS_TYPE_USER_DEF55,			
 PMS_TYPE_USER_DEF56,			
 PMS_TYPE_USER_DEF57,			
 PMS_TYPE_USER_DEF58,			
 PMS_TYPE_USER_DEF59,			
 PMS_TYPE_USER_DEF60,			
 PMS_TYPE_USER_DEF61,			
 PMS_TYPE_USER_DEF62,			
 PMS_TYPE_USER_DEF63,			
 PMS_TYPE_USER_DEF64,			
 PMS_TYPE_USER_DEF65,			
 PMS_TYPE_USER_DEF66,			
 PMS_TYPE_USER_DEF67,			
 PMS_TYPE_USER_DEF68,			
 PMS_TYPE_USER_DEF69,			
 PMS_TYPE_USER_DEF70,			
 PMS_TYPE_USER_DEF71,			
 PMS_TYPE_USER_DEF72,			
 PMS_TYPE_USER_DEF73,			
 PMS_TYPE_USER_DEF74,			
 PMS_TYPE_USER_DEF75,			
 PMS_TYPE_USER_DEF76,			
 PMS_TYPE_USER_DEF77,			
 PMS_TYPE_USER_DEF78,			
 PMS_TYPE_USER_DEF79,			
 PMS_TYPE_USER_DEF80,			
 PMS_TYPE_USER_DEF81,			
 PMS_TYPE_USER_DEF82,			
 PMS_TYPE_USER_DEF83,			
 PMS_TYPE_USER_DEF84,			
 PMS_TYPE_USER_DEF85,			
 PMS_TYPE_USER_DEF86,			
 PMS_TYPE_USER_DEF87,			
 PMS_TYPE_USER_DEF88,			
 PMS_TYPE_USER_DEF89,			
 PMS_TYPE_USER_DEF90,			
 PMS_TYPE_USER_DEF91,			
 PMS_TYPE_USER_DEF92,			
 PMS_TYPE_USER_DEF93,			
 PMS_TYPE_USER_DEF94,			
 PMS_TYPE_USER_DEF95,			
 PMS_TYPE_USER_DEF96,			
 PMS_TYPE_USER_DEF97,			
 PMS_TYPE_USER_DEF98,			
 PMS_TYPE_USER_DEF99,			
 PMS_TYPE_USER_DEF100,			
 PMS_TYPE_DONT_KNOW            /**< Media type not known*/
};
typedef int PMS_eMediaType;

enum
{
  PMS_PCL5TYPE_PLAIN = 0,               /**< Plain media type */
  PMS_PCL5TYPE_BOND = 1,                /**< Bond media type */
  PMS_PCL5TYPE_SPECIAL = 2,             /**< Special media type */
  PMS_PCL5TYPE_GLOSSY = 3,              /**< Glossy media type */
  PMS_PCL5TYPE_TRANSPARENCY = 4,        /**< Transparency media type */
  PMS_PCL5TYPE_RECYCLED = 5,            /**< Recycled media type */
  PMS_PCL5TYPE_THICK = 6,               /**< Thick media type */
  PMS_PCL5TYPE_ENVELOPE = 7,            /**< Envelope media type */
  PMS_PCL5TYPE_POSTCARD = 8,            /**< Postcard media type */
  PMS_PCL5TYPE_THIN,                /**< Thin media type */
  PMS_PCL5TYPE_LABEL,               /**< Label media type */
  PMS_PCL5TYPE_PREPRINTED,          /**< Preprinted media type */
  PMS_PCL5TYPE_LETTERHEAD,          /**< Letterhead media type */
  
  
  /**<New Addition*/
  PMS_PCL5TYPE_AUTO,
  PMS_PCL5TYPE_NORMAL,
  PMS_PCL5TYPE_TRACING,			
  PMS_PCL5TYPE_OHP,		
  PMS_PCL5TYPE_CARDSTOCK,		
  PMS_PCL5TYPE_CARDBOARD,		
  PMS_PCL5TYPE_PUNCH,
  PMS_PCL5TYPE_TAB,			
  PMS_PCL5TYPE_COLOR,			
  PMS_PCL5TYPE_NORMAL2ND,		
  PMS_PCL5TYPE_CARDBOARD2ND,		
  PMS_PCL5TYPE_USED,			
  PMS_PCL5TYPE_POSTCARD2ND,		
  PMS_PCL5TYPE_CARDBOARD2,	
  PMS_PCL5TYPE_FILM,		
  PMS_PCL5TYPE_INKPOST,			
  PMS_PCL5TYPE_HG_NORMAL,		
  PMS_PCL5TYPE_CARDBOARD3,		
  PMS_PCL5TYPE_SPECIAL2,		
  PMS_PCL5TYPE_SPECIAL3,		
  PMS_PCL5TYPE_MIDDLETHICK,		
  PMS_PCL5TYPE_COATED,	
  PMS_PCL5TYPE_CARDBOARD2REV,
  PMS_PCL5TYPE_CARDBOARD3REV,
  PMS_PCL5TYPE_NORMAL2,	
  PMS_PCL5TYPE_THICKGLOSSY,
  PMS_PCL5TYPE_SPECIAL4,	
  PMS_PCL5TYPE_SPECIAL5,		
  PMS_PCL5TYPE_SPECIAL6,

  PMS_PCL5TYPE_USER_DEF1,		
  PMS_PCL5TYPE_USER_DEF2,				
  PMS_PCL5TYPE_USER_DEF3,			
  PMS_PCL5TYPE_USER_DEF4,			
  PMS_PCL5TYPE_USER_DEF5,			
  PMS_PCL5TYPE_USER_DEF6,			
  PMS_PCL5TYPE_USER_DEF7,			
  PMS_PCL5TYPE_USER_DEF8,			
  PMS_PCL5TYPE_USER_DEF0,			 

  PMS_PCL5TYPE_COLOR1,	
  PMS_PCL5TYPE_COLOR2,		

  PMS_PCL5TYPE_COLOR_WHITE,
  PMS_PCL5TYPE_COLOR_YELLOW,
  PMS_PCL5TYPE_COLOR_GREEN,
  PMS_PCL5TYPE_COLOR_BLUE,
  PMS_PCL5TYPE_COLOR_PURPLE,
  PMS_PCL5TYPE_COLOR_IVORY,
  PMS_PCL5TYPE_COLOR_ORANGE,
  PMS_PCL5TYPE_COLOR_PINK,
  PMS_PCL5TYPE_COLOR_RED,
  PMS_PCL5TYPE_COLOR_GRAY,

  PMS_PCL5TYPE_GLOSSY_COATED,
  PMS_PCL5TYPE_THICK_GLOSSY_COATED,
  PMS_PCL5TYPE_MAT_COATED,
  PMS_PCL5TYPE_THICK_MAT_COATED,
  PMS_PCL5TYPE_WATER_PROOF,	
  PMS_PCL5TYPE_CARDBOARD4,		
  PMS_PCL5TYPE_CARDBOARD4REV,
  PMS_PCL5TYPE_COATED_HIGH_GLOSSY, 

  PMS_PCL5TYPE_SEMIGLOSSY,	
  PMS_PCL5TYPE_INKJETPLAIN,
  PMS_PCL5TYPE_MONO_TRACING,
  PMS_PCL5TYPE_COLOR_TRACING,
  PMS_PCL5TYPE_MATFILM,		
  PMS_PCL5TYPE_CADCOATED, 

  PMS_PCL5TYPE_NONE,
  PMS_PCL5TYPE_USER_DEF9,
  PMS_PCL5TYPE_USER_DEF10,
  PMS_PCL5TYPE_USER_DEF11,
  PMS_PCL5TYPE_USER_DEF12,
  PMS_PCL5TYPE_USER_DEF13,
  PMS_PCL5TYPE_USER_DEF14,
  PMS_PCL5TYPE_USER_DEF15,
  PMS_PCL5TYPE_USER_DEF16,
  PMS_PCL5TYPE_USER_DEF17,
  PMS_PCL5TYPE_USER_DEF18,
  PMS_PCL5TYPE_USER_DEF19,
  PMS_PCL5TYPE_USER_DEF20,
  PMS_PCL5TYPE_USER_DEF21,
  PMS_PCL5TYPE_USER_DEF22,			
  PMS_PCL5TYPE_USER_DEF23,			
  PMS_PCL5TYPE_USER_DEF24,			
  PMS_PCL5TYPE_USER_DEF25,			
  PMS_PCL5TYPE_USER_DEF26,			
  PMS_PCL5TYPE_USER_DEF27,			
  PMS_PCL5TYPE_USER_DEF28,			
  PMS_PCL5TYPE_USER_DEF29,			
  PMS_PCL5TYPE_USER_DEF30,			
  PMS_PCL5TYPE_USER_DEF31,			
  PMS_PCL5TYPE_USER_DEF32,			
  PMS_PCL5TYPE_USER_DEF33,			
  PMS_PCL5TYPE_USER_DEF34,			
  PMS_PCL5TYPE_USER_DEF35,			
  PMS_PCL5TYPE_USER_DEF36,			
  PMS_PCL5TYPE_USER_DEF37,			
  PMS_PCL5TYPE_USER_DEF38,			
  PMS_PCL5TYPE_USER_DEF39,			
  PMS_PCL5TYPE_USER_DEF40,			
  PMS_PCL5TYPE_USER_DEF41,			
  PMS_PCL5TYPE_USER_DEF42,			
  PMS_PCL5TYPE_USER_DEF43,			
  PMS_PCL5TYPE_USER_DEF44,			
  PMS_PCL5TYPE_USER_DEF45,			
  PMS_PCL5TYPE_USER_DEF46,			
  PMS_PCL5TYPE_USER_DEF47,			
  PMS_PCL5TYPE_USER_DEF48,			
  PMS_PCL5TYPE_USER_DEF49,			
  PMS_PCL5TYPE_USER_DEF50,			
  PMS_PCL5TYPE_USER_DEF51,			
  PMS_PCL5TYPE_USER_DEF52,			
  PMS_PCL5TYPE_USER_DEF53,			
  PMS_PCL5TYPE_USER_DEF54,			
  PMS_PCL5TYPE_USER_DEF55,			
  PMS_PCL5TYPE_USER_DEF56,			
  PMS_PCL5TYPE_USER_DEF57,			
  PMS_PCL5TYPE_USER_DEF58,			
  PMS_PCL5TYPE_USER_DEF59,			
  PMS_PCL5TYPE_USER_DEF60,			
  PMS_PCL5TYPE_USER_DEF61,			
  PMS_PCL5TYPE_USER_DEF62,			
  PMS_PCL5TYPE_USER_DEF63,			
  PMS_PCL5TYPE_USER_DEF64,			
  PMS_PCL5TYPE_USER_DEF65,			
  PMS_PCL5TYPE_USER_DEF66,			
  PMS_PCL5TYPE_USER_DEF67,			
  PMS_PCL5TYPE_USER_DEF68,			
  PMS_PCL5TYPE_USER_DEF69,			
  PMS_PCL5TYPE_USER_DEF70,			
  PMS_PCL5TYPE_USER_DEF71,			
  PMS_PCL5TYPE_USER_DEF72,			
  PMS_PCL5TYPE_USER_DEF73,			
  PMS_PCL5TYPE_USER_DEF74,			
  PMS_PCL5TYPE_USER_DEF75,			
  PMS_PCL5TYPE_USER_DEF76,			
  PMS_PCL5TYPE_USER_DEF77,			
  PMS_PCL5TYPE_USER_DEF78,			
  PMS_PCL5TYPE_USER_DEF79,			
  PMS_PCL5TYPE_USER_DEF80,			
  PMS_PCL5TYPE_USER_DEF81,			
  PMS_PCL5TYPE_USER_DEF82,			
  PMS_PCL5TYPE_USER_DEF83,			
  PMS_PCL5TYPE_USER_DEF84,			
  PMS_PCL5TYPE_USER_DEF85,			
  PMS_PCL5TYPE_USER_DEF86,			
  PMS_PCL5TYPE_USER_DEF87,			
  PMS_PCL5TYPE_USER_DEF88,			
  PMS_PCL5TYPE_USER_DEF89,			
  PMS_PCL5TYPE_USER_DEF90,			
  PMS_PCL5TYPE_USER_DEF91,			
  PMS_PCL5TYPE_USER_DEF92,			
  PMS_PCL5TYPE_USER_DEF93,			
  PMS_PCL5TYPE_USER_DEF94,			
  PMS_PCL5TYPE_USER_DEF95,			
  PMS_PCL5TYPE_USER_DEF96,			
  PMS_PCL5TYPE_USER_DEF97,			
  PMS_PCL5TYPE_USER_DEF98,			
  PMS_PCL5TYPE_USER_DEF99,			
  PMS_PCL5TYPE_USER_DEF100,
  PMS_PCL5TYPE_DONT_KNOW,            /**< Media type not known*/
};
typedef int PMS_ePCL5MediaType;

#define NUMFIXEDMEDIACOLORS 4
/* Update the number above to the number of fixed media colors in enum table */
/* This is used for setting up the tray configuration data in oil_media.c */
/* The actual definition table in pms_interface_oil2pms.c must match the definitions here */
/*! \brief Media colors defined in PMS.
*/
enum
{
  PMS_COLOR_WHITE,              /**< white media color */
  PMS_COLOR_RED,                /**< red media color */
  PMS_COLOR_YELLOW,             /**< yellow media color */
  PMS_COLOR_GREEN,              /**< green media color */
  PMS_COLOR_DONT_KNOW           /**< Color not known*/
};
typedef int PMS_eMediaColor;

#define NUMFIXEDMEDIASOURCES 7
/* Update the number above to the number of fixed media sources (input trays) in enum table */
/* This is used for setting up the PCL configuration data in oil_psconfig.c */
/* The actual definition table in pms_interface_oil2pms.c must match the definitions here */
/*! \brief Media Sources defined in PMS.
*/
#if 0
enum
{
  PMS_TRAY_AUTO = 0,            /**< Auto tray */
  PMS_TRAY_BYPASS,              /**< Bypass tray */
  PMS_TRAY_MANUALFEED,          /**< Manual Feed tray (physically maybe same as Bypass) */
  PMS_TRAY_TRAY1,               /**< Tray 1 Cassette */
  PMS_TRAY_TRAY2,               /**< Tray 2 Cassette */
  PMS_TRAY_TRAY3,               /**< Tray 3 Cassette */
  PMS_TRAY_ENVELOPE,            /**< Envelope feeder */
};
#endif
enum
{
 PMS_TRAY_MAN=0,
 PMS_TRAY_TRAY1,
 PMS_TRAY_TRAY2,
 PMS_TRAY_TRAY3,
 PMS_TRAY_TRAY4,
 PMS_TRAY_TRAY5,
 PMS_TRAY_TRAY6,
 PMS_TRAY_TRAY7,
 PMS_TRAY_LCT=10,
 PMS_TRAY_AUTO=15,
 PMS_TRAY_INSERTER,
 PMS_TRAY_INSERTER2,
 PMS_TRAY_PERF_INSERTER,
 PMS_TRAY_PERF_INSERTER2,
 PMS_TRAY_BYPASS,
 PMS_TRAY_ENVELOPE
};
typedef int PMS_eMediaSource;

enum
{
  PMS_PSTRAY_AUTO = 0,            /**< Auto tray */
  PMS_PSTRAY_BYPASS,              /**< Bypass tray */
  PMS_PSTRAY_MANUALFEED,          /**< Manual Feed tray (physically maybe same as Bypass) */
  PMS_PSTRAY_TRAY1,               /**< Tray 1 Cassette */
  PMS_PSTRAY_TRAY2,               /**< Tray 2 Cassette */
  PMS_PSTRAY_TRAY3,               /**< Tray 3 Cassette */
  PMS_PSTRAY_ENVELOPE,            /**< Envelope feeder */
  PMS_PSTRAY_TRAY4,               /**< Tray 4 Cassette */
  PMS_PSTRAY_TRAY5,               /**< Tray 5 Cassette */
  PMS_PSTRAY_TRAY6,               /**< Tray 6 Cassette */
  PMS_PSTRAY_TRAY7,               /**< Tray 7 Cassette */
  PMS_PSTRAY_LCT,                 /**< LCT */
  PMS_PSTRAY_INSERTER,            /**< Inserter Cassette */
  PMS_PSTRAY_INSERTER2,           /**< Inserter2 Cassette */
  PMS_PSTRAY_PERF_INSERTER,       /**< Perf inserter Cassette */
  PMS_PSTRAY_PERF_INSERTER2,      /**< Perf inserter2 Cassette */
  
};
typedef int PMS_ePSMediaSource;

enum
{
#if 0
  PMS_PCL5TRAY_TRAY1 = 1,               /**< Tray 1 Cassette */
  PMS_PCL5TRAY_MANUALFEED =2,           /**< Manual Feed tray (physically maybe same as Bypass) */
  PMS_PCL5TRAY_BYPASS = 3,              /**< Bypass tray */
  PMS_PCL5TRAY_TRAY2 = 4,               /**< Tray 2 Cassette */
  PMS_PCL5TRAY_TRAY3 = 5,               /**< Tray 3 Cassette  */
  PMS_PCL5TRAY_ENVELOPE = 6,            /**< Envelope feeder  */
  PMS_PCL5TRAY_AUTO = 7,                /**< Auto tray */
  
  /**<New Addition*/
  PMS_PCL5TRAY_TRAY4,
  PMS_PCL5TRAY_TRAY5,
  PMS_PCL5TRAY_TRAY6,
  PMS_PCL5TRAY_TRAY7,
  PMS_PCL5TRAY_LCT,
  PMS_PCL5TRAY_INSERTER,
  PMS_PCL5TRAY_INSERTER2,
  PMS_PCL5TRAY_PERF_INSERTER,
  PMS_PCL5TRAY_PERF_INSERTER2
#endif
  PMS_PCL5TRAY_TRAY2 = 1,               /**< Tray 1 Cassette */
  PMS_PCL5TRAY_MANUALFEED =2,           /**< Manual Feed tray (physically maybe same as Bypass) */
  PMS_PCL5TRAY_BYPASS = 2,              /**< Bypass tray */
  PMS_PCL5TRAY_TRAY3 = 3,               /**< Tray 2 Cassette */
  PMS_PCL5TRAY_TRAY4 = 4,               /**< Tray 3 Cassette  */
  PMS_PCL5TRAY_ENVELOPE = 9,            /**< Envelope feeder  */
  PMS_PCL5TRAY_AUTO = 10,                /**< Auto tray */
  PMS_PCL5TRAY_TRAY1 = 8,
  PMS_PCL5TRAY_TRAY5 = 5 ,
  PMS_PCL5TRAY_TRAY6 =6 ,
  PMS_PCL5TRAY_TRAY7 =7,
  PMS_PCL5TRAY_LCT = 11,
  PMS_PCL5TRAY_INSERTER=12,
  PMS_PCL5TRAY_INSERTER2=13,
  PMS_PCL5TRAY_PERF_INSERTER=14,
  PMS_PCL5TRAY_PERF_INSERTER2=15
  
  
  
};
typedef int PMS_ePCL5MediaSource;

enum
{
  PMS_PCLXTRAY_AUTO = 1,                /**< Auto tray */
  PMS_PCLXTRAY_MANUALFEED = 2,          /**< Manual Feed tray (physically maybe same as Bypass) */
  PMS_PCLXTRAY_BYPASS = 3,              /**< Bypass tray */
  PMS_PCLXTRAY_TRAY1 = 4,               /**< Tray 1 Cassette */
  PMS_PCLXTRAY_TRAY2 = 5,               /**< Tray 2 Cassette */
  PMS_PCLXTRAY_ENVELOPE = 6,            /**< Envelope feeder */
  PMS_PCLXTRAY_TRAY3 = 7,               /**< Tray 3 Cassette */
  PMS_PCLXTRAY_TRAY4 = 8,               /**< Tray 4 Cassette */
  PMS_PCLXTRAY_TRAY5 = 9,               /**< Tray 5 Cassette */
  PMS_PCLXTRAY_TRAY6 = 10,               /**< Tray 6 Cassette */ 
  PMS_PCLXTRAY_TRAY7 = 11,               /**< Tray 7 Cassette */
  PMS_PCLXTRAY_LCT,
  PMS_PCLXTRAY_INSERTER,
  PMS_PCLXTRAY_INSERTER2,
  PMS_PCLXTRAY_PERF_INSERTER,
  PMS_PCLXTRAY_PERF_INSERTER2       
};
typedef int PMS_ePCLXLMediaSource;

#define NUMFIXEDMEDIADESTS 4
/* Update the number above to the number of media destinations (output trays) in enum table */
/* This is used for setting up the PCL configuration data in oil_psconfig.c */
/* The actual definition table in pms_interface_oil2pms.c must match the definitions here */
/*! \brief Output trays defined in PMS.
*/
enum
{
  PMS_OUTPUT_TRAY_AUTO = 0,     /**< Auto tray */
  PMS_OUTPUT_TRAY_UPPER,        /**< Upper tray */
  PMS_OUTPUT_TRAY_LOWER,        /**< Lower tray */
  PMS_OUTPUT_TRAY_EXTRA,        /**< Lower tray */
};
typedef int PMS_eOutputTray;

enum
{
  PMS_PCL5OUTPUT_TRAY_AUTO = 0,         /**< Auto tray */
  PMS_PCL5OUTPUT_TRAY_UPPER = 1,        /**< Upper tray */
  PMS_PCL5OUTPUT_TRAY_LOWER = 2,        /**< Lower tray */
  PMS_PCL5OUTPUT_TRAY_EXTRA = 3,        /**< Lower tray */
};
typedef int PMS_ePCL5OutputTray;

enum
{
  PMS_PCLXOUTPUT_TRAY_AUTO = 0,         /**< Auto tray */
  PMS_PCLXOUTPUT_TRAY_UPPER = 1,        /**< Upper tray */
  PMS_PCLXOUTPUT_TRAY_LOWER = 2,       /**< Lower tray */
  PMS_PCLXOUTPUT_TRAY_EXTRA = 3,        /**< Lower tray */
};
typedef int PMS_ePCLXLOutputTray;

#define MAX_PCLCONFIG_BUF (NUMFIXEDMEDIASIZES*370)+\
                          (NUMFIXEDMEDIATYPES*60)+\
                          (NUMFIXEDMEDIASOURCES*28)+\
                          (NUMFIXEDMEDIADESTS*50)

#ifdef PMS_OIL_MERGE_DISABLE
/*! \brief Media Selection Mode.
*/
enum {
  PMS_PaperSelNone,                    /*!< no media selection */
  PMS_PaperSelRIP,                     /*!< for RIP defined paper selection */
  PMS_PaperSelPMS,                     /*!< for PMS defined paper selection */
};
typedef int PMS_ePaperSelectMode;
#endif

/*! \brief Image Quality defined in PMS.
*/
enum
{
  PMS_1BPP,                     /**< 1 bit per pixel - screened */
  PMS_2BPP,                     /**< 2 bit per pixel - screened */
  PMS_4BPP,                     /**< 4 bit per pixel - screened */
  PMS_8BPP_CONTONE,             /**< 8 bit per pixel - contone */
  PMS_16BPP_CONTONE,            /**< 16 bit per pixel - contone */
};
typedef int PMS_eImageQuality;

#ifdef PMS_OIL_MERGE_DISABLE
/*! \brief Color Modes defined in PMS.
*/
enum {
    PMS_Mono = 1,                         /*!< Monochrome job */
    PMS_CMYK_Separations,                 /*!< CMYK Color separation job */
    PMS_CMYK_Composite,                   /*!< CMYK Color composite job */
    PMS_RGB_Separations,                  /*!< RGB Color separation job */
    PMS_RGB_Composite,                    /*!< RGB Color composite job */
    PMS_RGB_PixelInterleaved,             /*!< RGB Pixel interleaved job */
};
typedef int PMS_eColorMode;

/*! \brief Screen Modes defined in PMS.
*/
enum {
    PMS_Scrn_Auto = 0,                    /*!< Screen mode Auto */
    PMS_Scrn_Photo,                       /*!< Screen mode Photo */
    PMS_Scrn_Graphics,                    /*!< Screen mode Graphics */
    PMS_Scrn_Text,                        /*!< Screen mode Text */
    PMS_Scrn_ORIPDefault,                 /*!< Screen mode RIP default */
    PMS_Scrn_Job,                         /*!< Screen mode Job settings */
    PMS_Scrn_Module,                      /*!< Screen mode Screening API module */
};
typedef int PMS_eScreenMode;

/*! \brief Render Modes defined in PMS.
*/
enum {
    PMS_RenderMode_Color = 0,             /*!< Render mode color */
    PMS_RenderMode_Grayscale,             /*!< Render mode grayscale */
};
typedef int PMS_eRenderMode;

/*! \brief Render Models defined in PMS.
*/
enum {
    PMS_RenderModel_CMYK8B = 0,           /*!< Render model for PCL5c jobs */
    PMS_RenderModel_G1,                   /*!< Render model for PCL5e jobs */
};
typedef int PMS_eRenderModel;
#endif

/*! \brief Structure type to hold tray information.
*/
typedef struct PMS_TyTrayInfo
{
  PMS_eMediaSource eMediaSource;      /**< Input Source. */
  PMS_ePaperSize ePaperSize;          /**< Papersize in the tray. */
  PMS_eMediaType eMediaType;          /**< MediaType in the tray. */
  PMS_eMediaColor eMediaColor;         /**< MediaColor in the tray. */
  unsigned int uMediaWeight;           /**< Media Weight (gsm) integer. */
  int nPriority;                       /**< Tray priority. */
  unsigned char bTrayEmptyFlag;        /**< TRUE if tray is empty. */
  unsigned int nNoOfSheets;            /**< Number of sheets in the tray. */
} PMS_TyTrayInfo;

/*! \brief Structure type to hold output tray information.
*/
typedef struct PMS_TyOutputInfo
{
  PMS_eOutputTray eOutputTray;      /**< Output tray. */
  int nPriority;                       /**< Tray priority. */
} PMS_TyOutputInfo;

/*! \brief Stores paper information.
*/
typedef struct PMS_TyPaperInfo {
    PMS_ePaperSize  ePaperSize;          /**< Paper size ID. */
    double          dWidth;              /**< Media width in ps points. */
    double          dHeight;             /**< Media height in ps points. */
    unsigned char   szPJLName[PMS_MAX_PAPERSIZE_LENGTH];  /**< PJL Paper size name . */
    int             nTopUnprintable;     /**< Unprintable distance at top (microinches). */
    int             nBottomUnprintable;  /**< Unprintable distance at bottom (microinches). */
    int             nLeftUnprintable;    /**< Unprintable distance on left (microinches). */
    int             nRightUnprintable;   /**< Unprintable distance on right (microinches). */
    int             nTopLogicalPage;     /**< Physical to logical page distance at top (microinches). */
    int             nBottomLogicalPage;  /**< Physical to logical page distance at bottom (microinches). */
    int             nLeftLogicalPage;    /**< Physical to logical page distance on left (microinches). */
    int             nRightLogicalPage;   /**< Physical to logical page distance on right (microinches). */
    /* PCL definitions */
    PMS_ePCL5size   ePCL5size;           /**<PCL 5 Paper size ID. */
    PMS_ePCLXLsize  ePCLXLsize;          /**< PCL XL Paper size ID. */
    unsigned char   szPSName[PMS_MAX_PAPERSIZE_LENGTH];  /**< Postscript name. */
    unsigned char   szXLName[PMS_MAX_PAPERSIZE_LENGTH];  /**< XL Paper size name . */
} PMS_TyPaperInfo;

typedef struct PMS_TyMediaType {
    PMS_eMediaType  eMediaType;          /**< Paper size ID. */
    unsigned char   szPSType[PMS_MAX_MEDIATYPE_LENGTH];  /**< PS Paper type string. */
    unsigned char   szPJLType[PMS_MAX_MEDIATYPE_LENGTH];  /**< PJL Paper type string. */
/* PCL definitions */
    PMS_ePCL5MediaType   ePCL5type;           /**<PCL 5 Paper size ID. */
    unsigned char   szPCL5Type[PMS_MAX_MEDIATYPE_LENGTH];  /**< PCL5 Paper type string . */
    unsigned char   szXLType[PMS_MAX_MEDIATYPE_LENGTH];  /**< XL Paper type string . */
} PMS_TyMediaType;

typedef struct PMS_TyMediaSource {
    PMS_eMediaSource  eMediaSource;          /**< Media Source ID. */
    PMS_ePSMediaSource  ePSMediaSource;          /**< PS Media Source number. */
    unsigned char   szPJLMediaSource[PMS_MAX_MEDIASRC_LENGTH];  /**< PJL Media Source string. */
    /* PCL definitions */
    PMS_ePCL5MediaSource   ePCL5MediaSource;           /**<PCL 5 Media Source ID. */
    PMS_ePCLXLMediaSource  ePCLXLMediaSource;          /**< PCL XL Media Source ID. */
    unsigned char   szXLName[PMS_MAX_MEDIASRC_LENGTH];  /**< XL Media Source name . */
} PMS_TyMediaSource;

typedef struct PMS_TyMediaDest {
    PMS_eOutputTray  eMediaDest;          /**< Media Dest ID. */
    unsigned char   szPSMediaDest[PMS_MAX_MEDIADEST_LENGTH];  /**< PS Media Dest name . */
    unsigned char   szPJLMediaDest[PMS_MAX_MEDIADEST_LENGTH];  /**< PS Media Dest name . */
/* PCL definitions */
    PMS_ePCL5OutputTray   ePCL5Mediadest;           /**<PCL 5 Media Dest ID. */
    PMS_ePCLXLOutputTray  ePCLXLMediadest;          /**< PCL XL Media Dest ID. */
} PMS_TyMediaDest;
typedef int PMS_eColorMode;
typedef struct PMS_TyMediaColor {
    PMS_eMediaColor eMediaColor;
    unsigned char   szMediaColor[PMS_MAX_MEDIACOLOR_LENGTH];
    unsigned char   szPJLColor[PMS_MAX_MEDIACOLOR_LENGTH];
} PMS_TyMediaColor;

#ifdef PMS_OIL_MERGE_DISABLE
/*! \brief Stores media information.
*/
typedef struct PMS_TyMedia {
    PMS_ePaperSize  ePaperSize;          /**< Paper size ID. */
    unsigned int    uInputTray;          /**< Selected input tray. */
    PMS_eOutputTray eOutputTray;         /**< Selected output tray. */
    unsigned char   szMediaType[PMS_MAX_MEDIATYPE_LENGTH];     /**< Media type string. */
    unsigned char   szMediaColor[PMS_MAX_MEDIACOLOR_LENGTH];    /**< Media color string. */
    unsigned int    uMediaWeight;        /**< Media Weight . */
    double          dWidth;              /**< Media width in ps points. */
    double          dHeight;             /**< Media height in ps points. */
} PMS_TyMedia;

/*! \brief Stores job information.
*/
typedef struct PMS_TyJob
{
    unsigned int    uJobId;              /**< Job ID number. */
    char            szHostName[PMS_MAX_HOSTNAME_LENGTH]; /**< Printer hostname. */
    char            szUserName[PMS_MAX_USERNAME_LENGTH]; /**< Job user name .*/
    char            szJobName[PMS_MAX_JOBNAME_LENGTH];   /**< Job name. */
    char            szPjlJobName[PMS_MAX_JOBNAME_LENGTH]; /**< Job name from PJL JOBNAME. */
    unsigned int    uCopyCount;          /**< Total copies to print. */
    unsigned int    uXResolution;        /**< Horizontal Resolution. */
    unsigned int    uYResolution;        /**< Vertical Resolution. */
    unsigned int    uOrientation;        /**< Orientation, portrait or landscape. */
    PMS_TyMedia     tDefaultJobMedia;    /**< Default media settings, typically from PMS front panel. */
    unsigned char   bAutoA4Letter;       /**< Automatic A4/letter switching. */
    double          dUserPaperWidth;     /**< User defined paper width. */
    double          dUserPaperHeight;    /**< User defined paper height. */
    unsigned char   bManualFeed;         /**< true = Manual feed */
    unsigned int    uPunchType;          /**< Punch type, single double etc. */
    unsigned int    uStapleType;         /**< Staple operation, 1 hole, 2 hole, centre etc. */
    unsigned char   bDuplex;             /**< Duplex = true, false = simplex. */
    unsigned char   bTumble;             /*!< true = tumble, false = no tumble */
    unsigned char   bCollate;            /**< Collate = true, false = no collate. */
    unsigned char   bReversePageOrder;   /**< Reverse page order. */
    unsigned int    uBookletType;        /**< Booklet binding, left, right. */
    unsigned int    uOhpMode;            /**< OHP interleaving mode. */
    unsigned int    uOhpType;            /**< OHP interleaving media type. */
    unsigned int    uOhpInTray;          /**< OHP interleaving feed tray. */
    unsigned int    uCollatedCount;      /**< Total collated copies in a job. */
    PMS_eImageQuality eImageQuality;     /**< 1bpp, 2bpp, 8bpp contone etc */
    unsigned int    bOutputBPPMatchesRIP;/**< Output bit depth same as rendered bit depth */
    unsigned int    uOutputBPP;          /**< Output bit depth if not matching rendered bit depth */
    PMS_eColorMode  eColorMode;          /*!< Default color (1-mono, 2-CMYKsep, 3-CMYKcomp, 4-RGBsep, 5-RGBcomp) */
    unsigned char   bForceMonoIfCMYblank;/*!< true = force monochrome if CMY absent, false = output all planes even if blank*/
    PMS_eScreenMode eScreenMode;         /**< Screening type auto, photo, text etc. */
    unsigned char   bSuppressBlank;      /**< true = suppress blank pages , false = do not suppress blank pages. */
    unsigned char   bPureBlackText;      /**< true = Pure Black Text enabled */
    unsigned char   bAllTextBlack;       /**< true = All Text Black Enabled */
    unsigned char   bBlackSubstitute;    /**< true = Black Substitute enabled */
    unsigned int    uFontNumber;         /**< PCL font number */
    char            szFontSource[4];     /**< PCL font source */
    unsigned int    uLineTermination;    /**< PCL line termination */
    double          dPitch;              /**< Pitch of the default PCL font in characters per inch */
    double          dPointSize;          /**< Height of the default PCL font in points */
    unsigned int    uSymbolSet;          /**< PCL symbol set */
    double          dLineSpacing;        /**< Number of lines per inch */
    PMS_eRenderMode eRenderMode;         /**< Render mode */
    PMS_eRenderModel eRenderModel;       /**< Render model */
    unsigned int    uJobOffset;          /**< Job offset: 0=off, 1=on */
    unsigned char   bCourierDark;        /**< CourierDark: FALSE=regular, TRUE=dark */
    unsigned char   bWideA4;             /**< WideA4: FALSE=no, TRUE=yes */
    unsigned char   bInputIsImage;       /**< Image Input FALSE=no, TRUE=yes */
    char            szImageFile[PMS_MAX_IMAGEFILENAME_LENGTH];   /**< Image File Path. */
    PMS_eTestPage   eTestPage;           /**< Test page selected PMS_TESTPAGE_NONE = off */
    unsigned int    uPrintErrorPage;     /**< Print error page selected  0 or 1*/
    unsigned char   bFileInput;          /**< File Input FALSE=no, TRUE=yes */
    char            szJobFilename[PMS_MAX_JOBNAME_LENGTH]; /**< Job file name */
    char            szPDFPassword[32];   /**< PDF File Password */
} PMS_TyJob;

/*! \brief Stores band information.
*/
typedef struct {
    unsigned int    uBandNumber;         /**< Number of band within page. */
    unsigned int    uBandHeight;         /**< Height of band in pixels. */
    unsigned int    cbBandSize;          /**< Size of raster in bytes. */
    unsigned char   *pBandRaster;        /**< Uncompressed Band data. */
} PMS_TyBand;
#endif

/*! \brief Stores band specifications.
*/
typedef struct {
    int  LinesPerBand;         /**< Number of lines in each band. */
    int  BytesPerLine;         /**< Number of bytes in each line. */
} PMS_TyBandInfo;

#ifdef PMS_OIL_MERGE_DISABLE
/*! \brief Stores plane information.
*/
typedef struct {
#ifdef PMS_OIL_MERGE_DISABLE
    PMS_eColourant  ePlaneColorant;      /**< C=0, M=1, Y=2, K=3 Invalid = -1. */
#else
    OIL_eColorant	ePlaneColorant;
#endif
    unsigned int    uBandTotal;          /**< Total number of bands in page. */
#ifdef PMS_OIL_MERGE_DISABLE
    PMS_TyBand      atBand[PMS_BAND_LIMIT];   /**< Pointer to band data. */
#else
    OIL_TyBand		atBand[PMS_BAND_LIMIT];   /**< Pointer to band data. */
#endif
    unsigned char   bBlankPlane;
} PMS_TyPlane;

/*! \brief Stores page information.
*/
typedef struct {
    unsigned int    JobId;                  /**< Unique number for this job. */
    PMS_TyJob       *pJobPMSData;           /* pointer to the PMS job structure */
    char            szJobName[PMS_MAX_JOBNAME_LENGTH]; /**< The name of the job. */
    unsigned int    PageId;                 /**< Unique number for this page (reset
                                                  to zero at   the start of each job). */
    int             nPageWidthPixels;        /**< Page width in pixels. */
    int             nPageHeightPixels;       /**< Page height in pixels. */
    int             nRasterWidthBits;        /**< Bits in a scan line (even in multiple bits per pixel
                                                  case): Divisible by 32.
                                                  Three times larger for RGB pixel interleaved.
                                                  */
    int             nRasterWidthPixels;      /**< Number of pixels in one line (inc. padding) */
    double          dXResolution;            /**< X dpi. */
    double          dYResolution;            /**< Y dpi. */
    int             uRIPDepth;               /**< Bits per pixel to be used when ripping. */
    int             uOutputDepth;            /**< Bits per pixel required when receiving raster. */
    int             nTopMargin;              /**< Top margin (pixels). */
    int             nBottomMargin;           /**< Bottom margin (pixels). */
    int             nLeftMargin;             /**< Left margin (pixels). */
    int             nRightMargin;            /**< Right margin (pixels). */
    PMS_eTyColorantFamily eColorantFamily;   /*!< Colorant Family (1-cmyk, 2-rgb, 3-gray, 4-unsupported) */
    int             bForceMonoIfCMYblank;    /*!< true = force monochrome if CMY absent, false = output all planes even if blank*/
    unsigned int    uTotalPlanes;            /*** Total number of valid planes. 1 -> mono, 4 -> CMYK. */
    PMS_TyPlane     atPlane[PMS_MAX_PLANES_COUNT]; /**< plane data structures. */
    int             nCopies;                 /**< integer: number of copies of this page to be printed. */
    int             bIsRLE;                  /**< true if raster is run-length encoded? */
    int             nBlankPage;              /**< 0=not blank, 1=blank in PDL, 2=blank for other reason */
    int             bDuplex;                 /*!< true = duplex, false = simplex */
    int             bTumble;                 /*!< true = tumble, false = no tumble */
    int             bCollate;                /*!< true = collate, false = no collate */
    int             uOrientation;            /*!< Orientation of image on page */
    int             bFaceUp;                 /*!< Output Order True = faceup, false=facedown */
    PMS_eColorMode  eColorMode;              /**< 1=Mono; 2=SeparationsColor; 3=SeparationsAuto; 4=CompositeColor; 5=CompositeAuto */
    PMS_eScreenMode eScreenMode;             /**< Screening type auto, photo, text etc. */
    unsigned long   ulPickupTime;            /**< Arrival time. */
    unsigned long   ulOutputTime;            /**< Output time. */
    PMS_ePageState  eState;                  /**< Page state. */
    PMS_TyMedia     stMedia;
#ifdef DEFAULT_PDL
    int             uTECValue;
#endif
}PMS_TyPage;
#endif

/*! \brief Stores band data information.
*/
typedef struct {
#ifdef PMS_OIL_MERGE_DISABLE
    PMS_eColourant  ePlaneColorant;       /**< C=0, M=1, Y=2, K=3, R=4, G=5, B=6, Invalid = 7. */
#else
    OIL_eColorant	ePlaneColorant; 	  /**< C=0, M=1, Y=2, K=3, R=4, G=5, B=6, Invalid = -1. */
#endif
    unsigned int    uBandHeight;          /**< Height of band in pixels */
    unsigned int    cbBandSize;           /**< Size of raster in bytes */
    unsigned char   *pBandRaster;         /**< Uncompressed Band data */
} PMS_TyColoredBand;

/*! \brief Band Packet Structure
*/
typedef struct tyBandPacket{
    unsigned int    uBandNumber;          /**< Band number within page */
    unsigned int    uTotalPlanes;         /**< Total number of valid planes. 1 -> mono, 4 -> CMYK, 3 -> RGB */
    PMS_TyColoredBand atColoredBand[PMS_MAX_PLANES_COUNT]; /**< plane data structures. */
} PMS_TyBandPacket;                       /**< PMS Band Structure */

/*! \brief Stores page list.
*/
typedef struct stPageList{
#ifdef PMS_OIL_MERGE_DISABLE
    PMS_TyPage *    pPage;
#else
    OIL_TyPage *    pPage;                   /**< Page information. */
#endif
    struct stPageList * pNext;               /**< Next page. */
}PMS_TyPageList;

/*! \brief Screen tables defined in PMS.
*/
enum
{
  PMS_SCREEN_1BPP_GFX_CYAN = 0,  /**< Screen table */
  PMS_SCREEN_1BPP_GFX_MAGENTA,   /**< Screen table */
  PMS_SCREEN_1BPP_GFX_YELLOW,    /**< Screen table */
  PMS_SCREEN_1BPP_GFX_BLACK,     /**< Screen table */
  PMS_SCREEN_1BPP_IMAGE_CYAN,    /**< Screen table */
  PMS_SCREEN_1BPP_IMAGE_MAGENTA, /**< Screen table */
  PMS_SCREEN_1BPP_IMAGE_YELLOW,  /**< Screen table */
  PMS_SCREEN_1BPP_IMAGE_BLACK,   /**< Screen table */
  PMS_SCREEN_1BPP_TEXT_CYAN,     /**< Screen table */
  PMS_SCREEN_1BPP_TEXT_MAGENTA,  /**< Screen table */
  PMS_SCREEN_1BPP_TEXT_YELLOW,   /**< Screen table */
  PMS_SCREEN_1BPP_TEXT_BLACK,    /**< Screen table */

  PMS_SCREEN_2BPP_GFX_CYAN,      /**< Screen table */
  PMS_SCREEN_2BPP_GFX_MAGENTA,   /**< Screen table */
  PMS_SCREEN_2BPP_GFX_YELLOW,    /**< Screen table */
  PMS_SCREEN_2BPP_GFX_BLACK,     /**< Screen table */
  PMS_SCREEN_2BPP_IMAGE_CYAN,    /**< Screen table */
  PMS_SCREEN_2BPP_IMAGE_MAGENTA, /**< Screen table */
  PMS_SCREEN_2BPP_IMAGE_YELLOW,  /**< Screen table */
  PMS_SCREEN_2BPP_IMAGE_BLACK,   /**< Screen table */
  PMS_SCREEN_2BPP_TEXT_CYAN,     /**< Screen table */
  PMS_SCREEN_2BPP_TEXT_MAGENTA,  /**< Screen table */
  PMS_SCREEN_2BPP_TEXT_YELLOW,   /**< Screen table */
  PMS_SCREEN_2BPP_TEXT_BLACK,    /**< Screen table */

  PMS_SCREEN_4BPP_GFX_CYAN,      /**< Screen table */
  PMS_SCREEN_4BPP_GFX_MAGENTA,   /**< Screen table */
  PMS_SCREEN_4BPP_GFX_YELLOW,    /**< Screen table */
  PMS_SCREEN_4BPP_GFX_BLACK,     /**< Screen table */
  PMS_SCREEN_4BPP_IMAGE_CYAN,    /**< Screen table */
  PMS_SCREEN_4BPP_IMAGE_MAGENTA, /**< Screen table */
  PMS_SCREEN_4BPP_IMAGE_YELLOW,  /**< Screen table */
  PMS_SCREEN_4BPP_IMAGE_BLACK,   /**< Screen table */
  PMS_SCREEN_4BPP_TEXT_CYAN,     /**< Screen table */
  PMS_SCREEN_4BPP_TEXT_MAGENTA,  /**< Screen table */
  PMS_SCREEN_4BPP_TEXT_YELLOW,   /**< Screen table */
  PMS_SCREEN_4BPP_TEXT_BLACK,    /**< Screen table */
};
typedef int PMS_eScreens;

/*! \brief Number of screen tables per colorant.
 15 for 4bpp.
*/
#define MAX_TABLES 15

/*! \brief Screen information data declaration style.
*/
#define THRARRAY_DECL static const

/*! \brief Screen information and data defined in PMS.
*/
typedef struct stScreenInfo
{
    PMS_eScreens eScreen;
    int nCellWidth;
    int nCellHeight;
    int nTables;
    const unsigned char * pTable[MAX_TABLES];
}PMS_TyScreenInfo;


/**
 * \brief Enum for getting system params
 */

enum {
  PMS_CurrentSettings = 0,
  PMS_NextSettings
};
typedef int PMS_eSysParams;


/*! \brief Current System State.
*/
typedef struct {
    char              szOutputPath[PMS_MAX_OUTPUTFOLDER_LENGTH];   /**< Output Location. */
    PMS_eOutputType   eOutputType;     /*!< Output Fileformat */
    unsigned int      uUseEngineSimulator;/*!< Engine Simulation option */
    unsigned int      uUseRIPAhead;    /*!< RIP Ahead option */
    unsigned int      cbSysMemory;     /*!< size of the memory allocated for System in bytes */
    unsigned int      cbRIPMemory;     /*!< size of the memory allocated for RIP in bytes */
    unsigned int      cbAppMemory;     /*!< size of the memory allocated for Application in bytes */
    int               cbReceiveBuffer; /*!< size of the memory allocated for Storing Job in bytes */
    unsigned int      cbJobMemory;     /*!< size of the memory allocated for Job in bytes */
    unsigned int      cbMiscMemory;    /*!< size of the memory allocated for Miscellaneous in bytes */
    unsigned int      cbPMSMemory;     /*!< size of the memory allocated for PMS in bytes */
    unsigned int      nStoreJobBeforeRip;/*!<store whole job before passing to rip */
    unsigned int      nOILconfig;      /*!< bitfield to setup OIL for custom config eg scalable consumption */
#ifdef PMS_OIL_MERGE_DISABLE
    PMS_ePaperSelectMode ePaperSelectMode; /*!< Paper selection mode */
#else
    OIL_ePaperSelectMode ePaperSelectMode; /*!< Paper selection mode */
#endif
    unsigned int      uDefaultResX;    /*!< Default horizontal resolution (can  be overriden by job). */
    unsigned int      uDefaultResY;    /*!< Default vertical resolution (can  be overriden by job). */
    PMS_eImageQuality eImageQuality;   /*!< Default bpp (can  be overriden by job). */
    unsigned int      bOutputBPPMatchesRIP;/*!< Output bit depth same as rendered bit depth */
    unsigned int      uOutputBPP;          /*!< Output bit depth if not matching rendered bit depth */
#ifdef PMS_OIL_MERGE_DISABLE
    PMS_eColorMode    eDefaultColMode; /*!< Default color mode (can be overriden by job). */
#else
    OIL_eColorMode	  eDefaultColMode; /*!< Default color mode (can be overriden by job). */
#endif
    unsigned char     bForceMonoIfCMYblank;/*!< true = force monochrome if CMY absent, false = output all planes even if blank*/
#ifdef PMS_OIL_MERGE_DISABLE
    PMS_eScreenMode   eDefaultScreenMode; /*!< Default screen mode (can be overriden by job). */
#else
    OIL_eScreenMode   eDefaultScreenMode; /*!< Default screen mode (can be overriden by job). */
#endif
    unsigned int      cPagesPrinted;   /*!< Count of pages printed */
    unsigned int      uPjlPassword;    /*!< Password for protected PJL commands */
    PMS_ePersonality  ePersonality;    /* Default PDL */
    PMS_eBandDeliveryType eBandDeliveryType; /*!< push the page or pull bands */
    unsigned int      bScanlineInterleave; /*!< When PMS is providing band memory, this controls scanline interleaving. */
    float             fTrapWidth;            /*!< Trap width: zero means no trapping */
    unsigned int      uColorManagement;      /*!< Color management method, 0 = disabled */
    char              szProbeTraceOption[128]; /*!< Probe names parameter */
    int               nRestart;        /*!< Restart OIL after current job */
    int               nStrideBoundaryBytes; /*!< Configure raster stride boundary (allows easier testing) */
    int               nPrintableMode;  /*!< Configure printable area method (allows easier testing) */
    char              szManufacturer[PMS_MAX_PRINTER_DEF_STRING];   /*!< Printer Manufacturer string for Font List */
    char              szProduct[PMS_MAX_PRINTER_DEF_STRING];        /*!< Printer Product/Model string for Font List  */
    char              szPDFSpoolDir[PMS_MAX_OUTPUTFOLDER_LENGTH];   /*!< PDF spool directory for HDD when using swinram  */
    unsigned char     bFileInput;          /**< File Input FALSE=no, TRUE=yes */
    int               nRendererThreads; /*!< Number of RIP renderer threads */
    unsigned char     bHWA;
    void              *pHWA1_buf1;
    int               cbHWA1_buf1;
    void              *pHWA1_buf2;
    int               cbHWA1_buf2;
    unsigned char     bHWA_FPGA;
    PMS_eColorMode    eHWAColMode;     /*!< HWA color mode */
    unsigned int      uHWAOutputDepth; /*!< HWA bpp */
}PMS_TySystem;


/*! \brief File system definitions.
*/
#define PMS_FSENTRY_PATHLEN 255
#define PMS_FSENTRY_NAMELEN 100

/* flag values for PMS_FS_Open() */
#define PMS_FS_CREAT  0x01
#define PMS_FS_READ   0x02
#define PMS_FS_WRITE  0x04
#define PMS_FS_TRUNC  0x08
#define PMS_FS_APPEND 0x10
#define PMS_FS_EXCL   0x20

/* whence values for PMS_FS_Seek() */
#define PMS_FS_SEEK_SET 1
#define PMS_FS_SEEK_CUR 2
#define PMS_FS_SEEK_END 3

enum
{
  ePMS_FS_None = 0,       /* Non-existent */
  ePMS_FS_Dir  = 1,       /* Directory */
  ePMS_FS_File = 2        /* File */

};
typedef int PMS_eFileType;


typedef struct PMS_TyStat
{
  unsigned char aName[ PMS_FSENTRY_NAMELEN + 1 ];
  PMS_eFileType type;
  unsigned long cbSize;     /* Size in bytes if type is ePMS_FS_File */

} PMS_TyStat;


typedef struct PMS_TyFileSystem
{
  int cbCapacity;
  int cbFree;
  char * pLocation;
  char * pLabel;

} PMS_TyFileSystem;

typedef struct PMS_HddInfo
{
	char	stat;						/* status        */
	char	path[GPS_MAX_HDD_PATH_LEN];			/* path          */
	long	f_bsize;					/* block size    */
	long	f_blocks;					/* total blocks  */
	long	f_bfree;					/* free blocks   */
	long	reserve;					/* reserve       */
} PMS_HddInfo;

/*! \brief Turn on and off PMS Log Message.
*/
extern int g_printPMSLog;
extern PMS_TySystem g_tSystemInfo;

/**
 * \brief List of resource types.
 */
enum
{
  EPMS_FONT_PCL_BITMAP = 0,    /* Bitmap font in PCL command form, eg lineprinter */
  EPMS_PCL_XLMAP,              /* Tables used to map XL font names to PCL5 fonts */
  EPMS_PCL_SSMAP,              /* SymbolSet mapping table.
                                  Length is the number of entries. */
  EPMS_PCL_GLYPHS,             /* Default encoding in compact form */
#if defined(USE_UFST5) || defined(USE_UFST7)
  EPMS_UFST_FCO,              /* UFST FCO data */
  EPMS_UFST_SS,               /* UFST symbolset data */
  EPMS_UFST_MAP,              /* The mapping from UFST FCO to PCL typeface.
                                 Length is actually the number of entries. */
#endif
#ifdef USE_FF
  EPMS_FF_PFR,                /* FontFusion PFR data. */
  EPMS_FF_FIT,                /* FontFusion FIT data. */
  EPMS_FF_MAP,                /* Mapping from FontFusion PFR to PCL typeface.
                                 Length is the number of entries. */
  EPMS_FF_SYMSET,             /* Definitions of symbol sets for FontFusion.
                                 Length is number of entries. */
  EPMS_FF_SYMSET_MAPDATA,     /* Data for the symbol set mappings. */
#endif
  EPMS_HWA1_API,                   /* Rift HWA1 API */
  EPMS_HWA1_GIPA2_CMM,             /* Rift HWA1 pointer for CMM data */
  EPMS_HWA1_GIPA2_BLACK,           /* Rift HWA1 pointer for Balck Generation data */
  EPMS_HWA1_GIPA2_GAMMA,           /* Rift HWA1 pointer for Gamma data */
  EPMS_HWA1_GIPA2_USER,            /* Rift HWA1 pointer for User data */
  EPMS_HWA1_GIPA2_DITHER,          /* Rift HWA1 pointer for Dither data */
  EPMS_HWA1_GIPA2_TONERLIMIT,      /* Rift HWA1 pointer for Toner Limit data */
  EPMS_PCL5RESOURCE_API,           /* PCL5 resources API */
#ifdef DEFAULT_PDL
  EPMS_TEC_API                     /* TEC API */
#endif
};
typedef int PMS_eResourceType;

/**
 * \brief resource types priorities.
 */
enum
{
  EPMS_Priority_Low = 0,
  EPMS_Priority_Normal,
  EPMS_Priority_High

};
typedef int PMS_eResourcePriority;

/**
 * \brief resource information.
 */
typedef struct PMS_TyResource
{
  unsigned char * pData;
  unsigned int    length;
  int             id;
  int             ePriority;

} PMS_TyResource;


/*! \brief Types of data sent back to sender.
*/
enum {
  PMS_WRITE_BACK_CHANNEL,     /**< Data is important and should be treated
                                   as what you should expect from a RIP. */
  PMS_WRITE_DEBUG_MESSAGE,    /**< Data is extra progress information. */
  PMS_WRITE_FILE_OUT,         /**< Data is already formatted and just needs to be saved on disk. */
};
typedef int PMS_eBackChannelWriteTypes;

/*! \brief Stores file information to be passed back via the backchannel.
*/
typedef struct PMS_TyBackChannelWriteFileOut {
  char szFilename[PMS_MAX_JOBNAME_LENGTH]; /**< Filename to be saved. */
  unsigned int uFlags;    /**< Bit field for values set.
                               bit 0: Absolute file position set, \c ulAbsPos.*/
  unsigned long ulAbsPos; /**< Absolute file position. Position to write data */
} PMS_TyBackChannelWriteFileOut;

#if defined(USE_UFST5) || defined(USE_UFST7) || defined(USE_FF)
/**
 * \brief UFST font map.
 * Matches RIP's PCL_FONTMAP so that map can be passed on unchanged
 * by OIL.
 * FontFusion can reuse the same strucuture.
 */
typedef struct PMS_TyUfstFontMap
{
  int            ufst;     /* UFST's "font number" */
  unsigned short typeface; /* PCL "typeface number" to match */
  unsigned short ord;      /* ordering in the target device font list (or 999) */
  unsigned short also;     /* optional additional PCL typeface number to match (or 0) */
  float          hmi;      /* HMI override (or 0) */
  float          scale;    /* Additional font scaling (or 0) */
  float          height;   /* Additional font height scaling (or 0) */

} PMS_TyUfstFontMap;
#endif

#if defined(USE_FF)
/**
 * \brief Symbol set definition for FontFusion.
 *  Matches the RIP's ff_symbol_set_t type to allow data to be passed
 *  from OIL.
 */
typedef struct PMS_s_FFSymbolSetType {
  int symbolSetID;
  unsigned char type;
  unsigned int tt_char_requirements_msw;
  unsigned int tt_char_requirements_lsw;
  unsigned int char_requirements_msw;
  unsigned int char_requirements_lsw;
  char platformID;
  char specificID;
  struct symbol_map {
    unsigned char first;
    unsigned char last;
    unsigned char count;
    unsigned int dataoffset; /* offset into the map_data; */
  } maps [2];
} PMS_FFSymbolSetType;
#endif

/*! \brief PMS memory pools
 *
 * These enums do not have to be aligned with OIL_TyMemPool, but must always start from 0.
 *
*/
enum {
  PMS_MemoryPoolSys = 0,
  PMS_MemoryPoolApp,
  PMS_MemoryPoolJob,
  PMS_MemoryPoolMisc,
  PMS_MemoryPoolPMS,
  PMS_NumOfMemPools,
};
typedef int PMS_TyMemPool;

/*! \brief PCL5 Resource types.
 */
enum {
  PMS_PCL5ResourceFont = 0,
  PMS_PCL5ResourceSymbolSet,
  PMS_PCL5ResourceUDP,
  PMS_PCL5ResourceMacro
};

/*! \brief PCL5 Resource operations.
 */
enum {
  PMS_PCL5ResourceLoad = 0,
  PMS_PCL5ResourceStore
};

/*! \brief PCL5 Resource operation return values.
 */
enum {
  PMS_PCL5ResourceOk = 0,
  PMS_PCL5ResourceFail
};


#endif /* _PMS_EXPORT_H_ */
