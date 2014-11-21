#ifndef _MH_ENUM_H_
#define _MH_ENUM_H

#if 0
typedef int OMenum;
typedef char* OMname;
typedef int OMEnum;
typedef int Uint16;
typedef int Uint8;
typedef unsigned long int Uint32;
typedef unsigned long int Field32;
typedef int Sint8;
typedef int Sint16;
typedef long int Sint32;
typedef int PAPERCODE;
typedef int Boolean;
/*typedef int bool;*/   /*Available in gpssim.h*/
typedef int ORIENTATION;
#define GPS_PRINT_MODE_NONE (0)
#endif

#if 1
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
  PMS_PCL5TRAY_TRAY4 = 8,
  PMS_PCL5TRAY_TRAY5 = 9 ,
  PMS_PCL5TRAY_TRAY6 =10 ,
  PMS_PCL5TRAY_TRAY7 =11,
  PMS_PCL5TRAY_LCT,
  PMS_PCL5TRAY_INSERTER,
  PMS_PCL5TRAY_INSERTER2,
  PMS_PCL5TRAY_PERF_INSERTER,
  PMS_PCL5TRAY_PERF_INSERTER2,
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
enum
{
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
  PMS_PCL5_TABLOID              /**< Unknown value for PCL5???*/
};
#endif

#if 0
enum
{
    PORTRAIT = 0,
    LANDSCAPE = 1,
    REVERSE_PORTRAIT = 2,
    REVERSE_LANDSCAPE =3
};

/* Moved to Mhwrapper.h
void SetMediaType(Uint32 media);
int GetMediaType();
OMenum GetPaperSource();
Uint32 GetPageSize();
void SetPageSize();
Uint32 GetCustomPageWidth();
Uint32 GetCustomPageHeight();
Uint32 GetPageWidth();
Uint32 GetPageHeight();
Uint32 GetOrientation();
Uint32 GetQualityMode();
int getMhPageSize();
int getMhMediaType();
int getMhPaperSource();
void SetPaperSource(int tray);
*/

/*FOR CMM*/
typedef struct Color_State_CP {
  unsigned char nColorProfile; 
  unsigned char nGrayReproduction; 
  int nDitherObj;
} Color_State_CP ;
#endif
#endif /* _MH_ENUM_H_ */

