/* Copyright (c) 2006-2007 Global Graphics Software Ltd. All Rights Reserved.
 *
 * $HopeName: SWebd_OIL_example_gg!src:oil_cmm.c(EBDSDK_P.1) $
 *
 * This example is provided on an "as is" basis and without
 * warranty of any kind. Global Graphics Software Ltd. does not
 * warrant or make any representations regarding the use or results
 * of use of this example.
 */
/**
 * @file
 * @ingroup CMMexamples
 * @brief  Simple example showing how to create a color management module
 * (CMM) that implements custom color mapping.
 *
 * This example provides an implementation of a CMM that
 * can be loaded into the RIP and used to provide alternative color
 * mapping functionality.
 *
 * To tell the RIP which CMM to use when rendering the coming
 * page you should use a PostScript language command similar
 * to the following:
 * <pre>
 *   <</AlternateCMM (CMM_OILExample) >> setpagedevice
 * </pre>
 *
 */

#include "oil.h"
#include "oil_cmm.h"
#include "oil_interface_oil2pms.h"
#include "gps/cl_color.h"
#include "gps/pager.h"
#include "colormatching.h"
#include "gps/cml.h"
#include <string.h>  /* memcpy */
#include "gps/di_info.h"

#define kInternalName  "CMM_OILExample"  /**< Short CMM name for configuration. */
#define kDisplayName   "Custom color space example OIL CMM"  /**< UTF-8 CMM name for display. */

#define kGrayChannelCount   (1)
#define kRGBChannelCount    (3)
#define kCMYKChannelCount   (4)

/*
 * Color conversion type
 */
#define COLOR_CONV_RGB_CMYK   1     /* RGB to CMYK conversion */
#define COLOR_CONV_RGB_RGB    0     /* RGB to RGB conversion  */

/*
 * Media group type
 */
#define COLOR_MEDIA_NORMAL    1

/*
 * Color matching type
 */
#define COLOR_MATCH_GRAPHIC         1
#define COLOR_MATCH_IMAGE           2
#define COLOR_MATCH_TEXT            3
#define COLOR_MATCH_GRAPHIC_JUDGE   4
#define COLOR_MATCH_IMAGE_JUDGE     5
#define COLOR_MATCH_TEXT_JUDGE      6
#define COLOR_MATCH_GRAPHIC_CUD     7
#define COLOR_MATCH_IMAGE_CUD       8
#define COLOR_MATCH_TEXT_CUD        9

/*
 * c : Color conversion type
 * m : Media group type
 * t : Color matching type
 */
#define COLOR_MAKE_PROF_KEY(c, m, t) ((c) << 31 | (m) << 16 | (t))

#define CMM_8BIT_PRECISSION  1 /* 8 bit precision */
#define CMM_16BIT_PRECISSION 2 /* 16 bit precision */

#define CMM_PRECISSION CMM_8BIT_PRECISSION

#define COLOR_8BIT_FLT(c) ((c) / 255.0f)
#define COLOR_FLT_8BIT(c) ((c) * 255)

#if CMM_PRECISSION == CMM_8BIT_PRECISSION
#define MAX_COLOR          255
#define COLOR_BALANCE_TOL  128
typedef unsigned char      color_t;
#else
#define MAX_COLOR          65535
#define COLOR_BALANCE_TOL  32768
typedef unsigned short     color_t;
#endif

#define COLOR_BALANCE_RATIO  1.5

di_bgucrinfo_t *pBgucr;
di_gcrinfo_t *pWishgcr;
di_gcrinfo_t *pGcrhgr;
unsigned char** ppucSrcGam;
di_dropinfo_t* pDropinfo;

#define GPS_CLR_PLANE 4
#define	SET_GRAY_IMAG(gmod)	((gmod & GRAY_MASK) << 24)
#define	SET_GRAY_GRAP(gmod)	((gmod & GRAY_MASK) << 16)
#define	SET_GRAY_TEXT(gmod)	((gmod & GRAY_MASK) << 8)
#define	SET_GRAY_LINE(gmod)	((gmod & GRAY_MASK) << 0)

#define	DIT_IMAG_MODE(ditmod)	((ditmod >> 6) & DIT_MASK)
#define	DIT_GRAP_MODE(ditmod)	((ditmod >> 4) & DIT_MASK)
#define	DIT_TEXT_MODE(ditmod)	((ditmod >> 2) & DIT_MASK)
#define	DIT_LINE_MODE(ditmod)	((ditmod >> 0) & DIT_MASK)

#define	SET_DIT_IMAG(ditmod)	((ditmod & DIT_MASK) << 6)
#define	SET_DIT_GRAP(ditmod)	((ditmod & DIT_MASK) << 4)
#define	SET_DIT_TEXT(ditmod)	((ditmod & DIT_MASK) << 2)
#define	SET_DIT_LINE(ditmod)	((ditmod & DIT_MASK) << 0)

long CMMalloc(unsigned long size, void* lprh);
void CMMfree(void* addr, void* lprh);
/* extern PCLXL_PARSER_CONTEXT pclxl_get_parser_context();
extern Color_State_CP *get_color_state_CP(PCL5Context *pcl5_ctxt);
extern PCL5Context* pcl5_current_context(void) ;
extern uint8 pclxlColorDataread_(PCLXL_PARSER_CONTEXT parser_context);
extern PCLXL_PARSER_CONTEXT pclxl_get_parser_context(); */

long            cmm = 0;
unsigned long cmmProfile = 0;
/* extern variables */
extern OIL_TyJob *g_pstCurrentJob;
extern di_devinfo_GPS_t *devinfo;

/* ------------ */
int nGrayMode = 0;
int nObjMode  = 0;
int nOrigObjMode = 0;//For color image and mono image
unsigned long ulFlag = 0/*16908811*/;
void* ColorData;
/* New */
ulong ulOpe;
unsigned char ucColorMode;
int GrayReproduction;
unsigned char m_ucIsGrayJudge;
unsigned long ulVectorGray;
unsigned long ulGrayJudgeMode;
unsigned char ucDither;
unsigned char ucDitherMode;
di_tlimitinfo_t pLimit;
unsigned short usTLimit[REN_DIT_MAX][REN_OBJ_MAX];
//unsigned char ucFlag;
int nNDither;
int nObjectType = 0;//unused
/* New */

di_tlimitinfo_t  *tlimit;
extern di_ditinfo_t   dit[GPS_CLR_PLANE];

void SetIsGrayJudge (int nObjMode,unsigned long ulGrayJudgeMode)
{
	switch (nObjMode & PR_OBJ_MASK)
	{
		case PR_OBJ_IMAG:
			m_ucIsGrayJudge = GRAY_IMAG_MODE (ulGrayJudgeMode);
			break;
		case PR_OBJ_GRAP:
			m_ucIsGrayJudge = GRAY_GRAP_MODE (ulGrayJudgeMode);
			break;
		case PR_OBJ_TEXT:
			m_ucIsGrayJudge = GRAY_TEXT_MODE (ulGrayJudgeMode);
			break;
		default:
			break;
	}
}

void setColorProfile()
{
    if( g_pstCurrentJob->ePDLType == OIL_PDL_PCL5c || 
        g_pstCurrentJob->ePDLType == OIL_PDL_PCL5e )
    {
    Color_State_CP* pColorProfile = NULL;
        
    pColorProfile = get_color_state_CP( pcl5_current_context() );

    switch( pColorProfile->nColorProfile)
    {
        case NO_COLOR_MATCH:    
             cmmProfile   = NO_COLOR_MATCH;
             break;
        case TEXT_COLOR_MATCH:  
             cmmProfile = TEXT_KEY;
             break;
        case VIVID_COLOR_MATCH: 
             cmmProfile = VIVID_KEY;
             break;
        case OUT_OF_GAMUT:  
             cmmProfile = GRADA_KEY;
             break;    
        default: 
             break;
      }
    GrayReproduction = pColorProfile->nGrayReproduction;
 }
 else if( g_pstCurrentJob->ePDLType == OIL_PDL_PCLXL )
 {
        unsigned int nColorProfile = (unsigned int)pclxlColorDataread_( pclxl_get_parser_context() );
        switch ( nColorProfile )
        {
            case 1: 
                 cmmProfile = VIVID_KEY;
                 break;
            case 3:
                 cmmProfile = TEXT_KEY;
                 break;
            case 4:
                 cmmProfile = GRADA_KEY;
                 break;
            default:
                 break;
        }
        cmmProfile = TEXT_KEY;
 }


    /*if( cmmProfile )
    {
        CMM_OpenProfile(cmm, FILEBASE, pProfilePath, cmmProfile);
    }*/
}

int setColorMode()
{ 
    switch( g_pstCurrentJob->eColorMode )
    {
         case OIL_Mono: //MONO
              ulOpe = PR_DEVICE_MONO;
              break;
         case OIL_CMYK_Separations:
         case OIL_CMYK_Composite:
              ulOpe = PR_DEVICE_CMYK;
              break;
         case OIL_RGB_Separations:
         case OIL_RGB_Composite:
         case OIL_RGB_PixelInterleaved:
              ulOpe = PR_DEVICE_RGB;
              break;
    }

	// Setting of bit depth
	
	switch (ulOpe & PR_DEPTH_MASK)
	{
		case PR_DEPTH_1BIT:
			ucColorMode = COLOR_DEPTH_1;
			break;
		case PR_DEPTH_2BIT:
			ucColorMode = COLOR_DEPTH_2;
			break;
		case PR_DEPTH_4BIT:
			ucColorMode = COLOR_DEPTH_4;
			break;
		case PR_DEPTH_8BIT:
			ucColorMode = COLOR_DEPTH_8;
			break;
		default:
			break;
	}

	// Setting of device color
    // When appointment of the device color and type ability does not agree,
	// the black and white
	switch (ulOpe & PR_DEVICE_MASK)
	{
		case PR_DEVICE_MONO:	// MONO
			ucColorMode |= PAGE_COLOR_K;
			break;
		case PR_DEVICE_CMY:	// CMY
			// It corresponds with Gray conversion mode
			if (devinfo->nplane >= 4)
			{
					ulVectorGray = SET_GRAY_IMAG(GRAY_CMY)
					| SET_GRAY_GRAP(GRAY_CMY)
					| SET_GRAY_TEXT(GRAY_CMY)
					| SET_GRAY_LINE(GRAY_CMY);
					ucColorMode |= PAGE_COLOR_CMY;
			}
			else
			{
					ucColorMode |= PAGE_COLOR_K;
			}
			break;
	    /* CMM : For RK and RK2 Need to get confirmation from customer regarding INPUTS */
		case PR_DEVICE_RK:	// It is dark red two colors
			if (devinfo->nplane >= 2)
			{
					ucColorMode |= PAGE_COLOR_RK;
			}
			else
			{
				ucColorMode |= PAGE_COLOR_K;
			}
			break;
		case PR_DEVICE_RK2:	// It is dark red two colors
			if (devinfo->nplane >= 2)
			{
				ucColorMode |= PAGE_COLOR_RK2;
			}
			else
			{
				ucColorMode |= PAGE_COLOR_K;
			}
			break;
		case PR_DEVICE_CMYK:	// CMYK
			if (devinfo->nplane >= 4)
			{
				ucColorMode |= PAGE_COLOR_CMYK;
			}
			else
			{
				ucColorMode |= PAGE_COLOR_K;
			}
			break;
		case PR_DEVICE_RGB:	// RGB
		default:
				return PR_ERROR;
			//error(prh->m_objError.m_ulErrCode = PR_ERR_SYNTAX);
		
		}
    return PR_OK;
}

int getModeID()
{
	int modeID;
	di_resolutioninfo_t	*reso_set = devinfo->reso_set;
if(!devinfo->reso_set)
	return 0;

    for( modeID = 0; modeID < devinfo->resonum; modeID++, reso_set++)
    {
        if( ( reso_set->x == g_pstCurrentJob->uXResolution ) &&
            ( reso_set->y == g_pstCurrentJob->uYResolution ) &&
            ( reso_set->bit == g_pstCurrentJob->uRIPDepth ) &&
            ( reso_set->dit_mode == 0/*PHOTO_DRAWMODE*/ ) &&
            ( reso_set->prt_mode == 2/*GPS_PRINT_MODE_NORMAL*/ ) &&
            ( reso_set->paper == 1/*pageparam.paper_type*/ ) )
        {
            return modeID;
        }
            
    }
    
	return 0;
}
 void setGrayMode(ulVectorGray,nObjMode,nOrigObjMode)
 {
	unsigned long ulGmod = ulVectorGray;
	 switch (nObjMode)
	{
		case PR_OBJ_IMAG:
			ulGmod = GRAY_IMAG_MODE (ulGmod);
			/*
			 * StretchBlt(COLOR)窶堙搾ｿｽﾃｭ窶堙烏RAY_CMYK
			 * StretchBlt(MONO)窶堙隈2Kﾋ�闇�窶堙�RAY_CMYK
			 * 窶堙遺�ﾃ娯�ﾃ��ﾂｮ�ｽﾂｫﾅｽw窶凖ｨ窶堙��ﾃ��ﾂｯ窶罵窶堙娯�ﾂｮ窶堋ｫ窶堙俄�ﾂｷ窶堙ｩ�ｽB
			 */
			switch (nOrigObjMode &
				PR_OBJ_MASK_1ST)
			{
				case PR_OBJ_IMAG_COLOR:
				/* ABOUTK窶堙姑辰ﾆ抵ｿｽ�ｽ[ﾆ淡窶堙宏2K窶堙��ﾂｯ窶堋ｶ
				   MAYBEK窶堙行etcolor窶堙俄�ﾃ坂�K窶牌窶堙遺�ﾂ｢ */
					if ((ulGmod != GRAY_CMY)
						&& (ulGmod != GRAY_HGRCMYK)
						&& (ulGmod != GRAY_PIXELK)
						&& (ulGmod != GRAY_IMAGEK))
					{
						if(ulGmod == GRAY_HGRG2K)
						{
							ulGmod = GRAY_HGRCMYK;
						}
						else
						{
							ulGmod = GRAY_CMYK;
						}
					}
					break;
				case PR_OBJ_IMAG_MONO:
					if ((ulGmod != GRAY_G2K)
						&& (ulGmod != GRAY_HGRG2K)
						&& (ulGmod != GRAY_HGRCMYK)
						&& (ulGmod != GRAY_CMY)
						&& (ulGmod != GRAY_PIXELK)
#ifdef SUPPORT_COMPOSITEBLACK
						&& (ulGmod != GRAY_COMPBK)
#endif
						&& (ulGmod != GRAY_MAYBEK)
						&& (ulGmod != GRAY_ABOUTK)
						&& (ulGmod != GRAY_IMAGEK))
					{
						ulGmod = GRAY_CMYK;
					}
					else if(ulGmod == GRAY_IMAGEK)
					{//ﾆ停�ﾆ知ﾆ辰ﾆ抵ｿｽ�ｽ[ﾆ淡窶堙栗MAGEK窶堙宏2K
						ulGmod = GRAY_G2K;
					}
					break;
				default:
					/* Stretchblt, Bitblt窶堙遺�ﾃｧ窶堋ｱ窶堋ｿ窶堙ｧ */
					break;
			}
			break;
		case PR_OBJ_GRAP:
			ulGmod = GRAY_GRAP_MODE (ulGmod);
			break;
		case PR_OBJ_TEXT:
			ulGmod = GRAY_TEXT_MODE (ulGmod);
			break;
	}
	 ulFlag |= ulGmod;
}
 unsigned char
 IsValidDither(int nNDither, int nDither)
 {
 	if ((DIT_IMAG_MODE(nDither) >= nNDither) ||
 		(DIT_GRAP_MODE(nDither) >= nNDither) ||
 		(DIT_TEXT_MODE(nDither) >= nNDither) ||
 		(DIT_LINE_MODE(nDither) >= nNDither))
 	{
 		return FALSE;
 	}
 	return TRUE;
 }

 void setDitherMode(int nNDither)
 {
	 int nDit = SET_DIT_IMAG(DIT_PHOT)|SET_DIT_GRAP(DIT_PHOT)|
	 	SET_DIT_TEXT(DIT_TEXT)|SET_DIT_LINE(DIT_PHOT);
	 // Check whether you can use PHOT and TEXT both dither,
	if (IsValidDither(nNDither, nDit) == TRUE)
	{
		ucDitherMode = nDit;
	}
	else
	{
		// It sets to all PHOT dither
		ucDitherMode = SET_DIT_IMAG(DIT_PHOT)|SET_DIT_GRAP(DIT_PHOT)
		|SET_DIT_TEXT(DIT_PHOT)|SET_DIT_LINE(DIT_PHOT);
	}
	// Using the initial value of PAGE, setting one for drawing
	ucDither = ucDitherMode;
 }

 int GetGrayMode(unsigned long ulFlag)
 {
 	int nGrayFlag = ulFlag & CR_GRAYP_MASK;

 	switch (nGrayFlag) {
 		case CR_GRAYP_G2K:
 			nGrayMode = GRAY_G2K;
 			break;
 		case CR_GRAYP_HGRG2K:
 			nGrayMode = GRAY_HGRG2K;
 			break;
 		case CR_GRAYP_CMYK:
 			nGrayMode = GRAY_CMYK;
 			break;
 		case CR_GRAYP_HGRCMYK:
 			nGrayMode = GRAY_HGRCMYK;
 			break;
 		case CR_GRAYP_K2K:
 			nGrayMode = GRAY_K2K;
 			break;
 		case CR_GRAYP_CMY:
 			nGrayMode = GRAY_CMY;
 			break;
 		case CR_GRAYP_IMAGEK:
 			nGrayMode = GRAY_IMAGEK;
 			break;
 		case CR_GRAYP_PIXELK:
 			nGrayMode = GRAY_PIXELK;
 			break;
 		case CR_GRAYP_MAYBEK:
 			nGrayMode = GRAY_MAYBEK;
 			break;
 		case CR_GRAYP_ABOUTK:
 			nGrayMode = GRAY_ABOUTK;
 			break;
 		default:
 			break;
 	}
 	return nGrayMode;
 }

 //Commented as if drop in PRcolor this will be handled.
 /*int SubPRSetTonerLimitRatio(int nDit,int nText, int nLine, int nPhot, int nFill)
 {
 	 if (nText != -1)
 	{
 		pLimit.text =  calc_tlimit(nText);
 	}
 	if (nLine != -1)
 	{
 		pLimit.line = calc_tlimit(nLine);
 	}
 	if (nPhot != -1)
 	{
 		pLimit.phot = calc_tlimit(nPhot);
 	}
 	if (nFill != -1)
 	{
 		pLimit.fill = calc_tlimit(nFill);
 	}

 	return PR_OK;
 }*/

 void setGrayReproduction()
 {
	 if(GrayReproduction == 0)//Toner Black
	 {
		 ulVectorGray = SET_GRAY_IMAG(GRAY_PIXELK)|SET_GRAY_GRAP(GRAY_PIXELK)|
		 		SET_GRAY_TEXT(GRAY_PIXELK)|SET_GRAY_LINE(GRAY_PIXELK);
	 }
	 else if(GrayReproduction == 1)//Process Black
	 {
		 ulVectorGray = SET_GRAY_IMAG(GRAY_G2K)|SET_GRAY_GRAP(GRAY_G2K)|
		 		SET_GRAY_TEXT(GRAY_G2K)|SET_GRAY_LINE(GRAY_CMYK);
	 }
	 else if(GrayReproduction == 3)//High Ink
	 {
		 ulVectorGray = SET_GRAY_IMAG(GRAY_HGRG2K)|SET_GRAY_GRAP(GRAY_HGRG2K)|
		 		SET_GRAY_TEXT(GRAY_HGRG2K)|SET_GRAY_LINE(GRAY_HGRG2K);
	 }
 }

 void setPageStartDefault(int nObjMode)
 {
	 // Default of PageStart option
	ulVectorGray = SET_GRAY_IMAG(GRAY_G2K)|SET_GRAY_GRAP(GRAY_G2K)|
		SET_GRAY_TEXT(GRAY_G2K)|SET_GRAY_LINE(GRAY_G2K);
	setGrayReproduction();
	ulGrayJudgeMode = SET_GRAY_IMAG(CR_JUDGE_GRAY_AFTER_CMM_ON)
	| SET_GRAY_GRAP(CR_JUDGE_GRAY_AFTER_CMM_ON)
	| SET_GRAY_TEXT(CR_JUDGE_GRAY_AFTER_CMM_ON)
	| SET_GRAY_LINE(CR_JUDGE_GRAY_AFTER_CMM_ON);
	//SetIsGrayJudge (nObjMode,ulGrayJudgeMode);
	//setGrayMode(ulVectorGray,nObjMode,nOrigObjMode);
	//nGrayMode = GetGrayMode(ulFlag);
	nNDither = devinfo->ndit;
	setDitherMode(nNDither);

//Commented as if drop in PRcolor this will be handled.
//	// Regulation of total emission is NOT applied
//
//	// Is regulation of total emission supported?: Yes
//	// Is regulation of total emission applied?: No
//	// Is regulation of total emission value appointed?: Don't care
//
//	// When is, regulation of total emission value is designated as 0
//	for (nI = 0; nI < DIT_MAX; nI++)
//	{
//		SubPRSetTonerLimitRatio(nI,
//			MAX_4C_TONER_LIMIT_RATIO,
//			MAX_4C_TONER_LIMIT_RATIO,
//			MAX_4C_TONER_LIMIT_RATIO,
//			MAX_4C_TONER_LIMIT_RATIO);
//	}

 }

/**
 * @brief  Array of supported custom color spaces.
 */
static sw_cmm_custom_colorspace gCCSArray[] = {
  #define kCCS_TextColorMapFeaturesCMYKIndex  (0)
  { (uint8*) "TextColorMapFeaturesCMYK", kCMYKChannelCount, kCMYKChannelCount },
  #define kCCS_PictureColorMapFeaturesCMYKIndex  (1)
  { (uint8*) "PictureColorMapFeaturesCMYK", kCMYKChannelCount, kCMYKChannelCount },
  #define kCCS_DefaultColorMapFeaturesCMYKIndex  (2)
  { (uint8*) "DefaultColorMapFeaturesCMYK", kCMYKChannelCount, kCMYKChannelCount },

  #define kCCS_DefaultColorMapFeaturesRGBTextIndex  (3)
  { (uint8*) "DefaultColorMapFeaturesRGBText", kRGBChannelCount, kCMYKChannelCount },
 #define kCCS_DefaultColorMapFeaturesRGBImageIndex  (4)
 { (uint8*) "DefaultColorMapFeaturesRGBImage", kRGBChannelCount, kCMYKChannelCount },
 #define kCCS_DefaultColorMapFeaturesRGBIndex  (5)
 { (uint8*) "DefaultColorMapFeaturesRGB", kRGBChannelCount, kCMYKChannelCount },

#define kCCS_DefaultColorMapFeaturesGrayTextIndex  (6)
 { (uint8*) "DefaultColorMapFeaturesGrayText", kGrayChannelCount, kGrayChannelCount },
#define kCCS_DefaultColorMapFeaturesGrayImageIndex  (7)
{ (uint8*) "DefaultColorMapFeaturesGrayImage", kGrayChannelCount, kGrayChannelCount },
#define kCCS_DefaultColorMapFeaturesGrayIndex  (8)
{ (uint8*) "DefaultColorMapFeaturesGray", kGrayChannelCount, kGrayChannelCount },

/* For PS mono */
#define kCCS_PSDefaultColorMapFeaturesCMYK_Gray  (9)
{ (uint8*) "PSDefaultColorMapFeaturesCMYK_Gray", kCMYKChannelCount, kGrayChannelCount },
#define kCCS_PSDefaultColorMapFeaturesRGB_Gray   (10)
{ (uint8*) "PSDefaultColorMapFeaturesRGB_Gray", kRGBChannelCount, kGrayChannelCount },
#define kCCS_PSDefaultColorMapFeaturesGray_Gray  (11)
{ (uint8*) "PSDefaultColorMapFeaturesGray_Gray", kGrayChannelCount, kGrayChannelCount },

/* For PS color */
#define kCCS_PSDefaultColorMapFeaturesCMYK_CMYK  (12)
{ (uint8*) "PSDefaultColorMapFeaturesCMYK_CMYK", kCMYKChannelCount, kCMYKChannelCount },
#define kCCS_PSDefaultColorMapFeaturesRGB_CMYK   (13)
{ (uint8*) "PSDefaultColorMapFeaturesRGB_CMYK", kRGBChannelCount, kCMYKChannelCount },
#define kCCS_PSTextColorMapFeaturesRGB_CMYK   (14)
{ (uint8*) "PSTextColorMapFeaturesRGB_CMYK", kRGBChannelCount, kCMYKChannelCount },
#define kCCS_PSPictureColorMapFeaturesRGB_CMYK   (15)
{ (uint8*) "PSPictureColorMapFeaturesRGB_CMYK", kRGBChannelCount, kCMYKChannelCount },
#define kCCS_PSDefaultColorMapFeaturesGray_CMYK  (16)
{ (uint8*) "PSDefaultColorMapFeaturesGray_CMYK", kGrayChannelCount, kCMYKChannelCount }

};

typedef void   (*CMYKColorMappingFunc)(float cmykValue[]); /**< Typedef for the color modifying callback function. */
typedef struct CMM_TRANSFORM CMM_TRANSFORM;

/**
 * @brief  Use the specified transform to adjust color data
 *
 * The RIP will place color data in memory beginning at input_data. This
 * function should converts the data using the transform and places the
 * output values in memory beginning at output_data.
 *
 * @param[in]  instance      The alternate CMM instance.
 * @param[in]  transform     The transform to use for color conversions.
 * @param[in]  input_data    RIP-allocated array of input color values.
 * @param[out]  output_data  RIP-allocated array to fill with output color values.
 * @param[in]  num_pixels    Number of color values to transform.
 * @return <code>TRUE</code> on success, <code>FALSE</code> otherwise.
 *
 * @see ccs_open_transform(), ccs_close_transform()
 */
typedef sw_cmm_result RIPCALL ccs_transformer(sw_cmm_instance  *instance,
                                                 CMM_TRANSFORM *transform,
                                                 float         *input_data,
                                                 float         *output_data,
                                                 uint32        num_pixels);
												 
typedef sw_cmm_result RIPCALL cmm_transformer(long           rcmm,
                                              CMM_TRANSFORM  *transform,
                                              color_t        *input_data,
                                              color_t        *output_data);
/**
 * @brief  Description of a profile specific to this CMM.
 */
typedef struct CMM_PROFILE
{
  cmm_transformer      *prf_pTransformFn; /**< Conversion routine for this profile using CMM */
  CMYKColorMappingFunc pMappingFunc;     /**< Function pointer to CMYK modifying code. */
  uint32 nInputChannels;                 /**< The number of input color channels. */
  uint32 nOutputChannels;                /**< The number of output color channels. */
} CMM_PROFILE;

/**
 * @brief  Description of a transform specific to this CMM.
 */
/* typedef struct CMM_TRANSFORM */
struct CMM_TRANSFORM
{
  long             trf_cmm;           /**< CMM to be used for this transform */
  di_devinfo_GPS_t *trf_devinfo;      /**< device information for this transform */
  ccs_transformer  *trf_pTransformFn; /**< Conversion routine for this transform */
  CMM_PROFILE*     pProfileArray;    /**< Array of profile objects required in the transform. */
  uint32           nProfiles;        /**< The number of profile entries in the array. */
} /* CMM_TRANSFORM */;


/* Forward declarations */
static sw_cmm_result RIPCALL ccs_construct(sw_cmm_instance *instance);
static sw_cmm_result RIPCALL ccs_open_profile(sw_cmm_instance *instance,
                                              sw_blob_instance *profile_source,
                                              sw_cmm_profile *handle);
static void RIPCALL ccs_close_profile(sw_cmm_instance *instance,
                                      sw_cmm_profile profile);
static sw_cmm_custom_colorspace* RIPCALL ccs_declare_custom_colorspace(sw_cmm_instance *instance,
                                                                       uint32 index);
static sw_cmm_result RIPCALL ccs_open_custom_colorspace(sw_cmm_instance *instance,
                                                        uint32 index,
                                                        sw_cmm_profile *handle);
static sw_cmm_result RIPCALL ccs_open_transform(sw_cmm_instance *instance,
                                                sw_cmm_profile profiles[],
                                                uint32 num_profiles,
                                                int32 intents[],
                                                HqBool black_point_compensations[],
                                                uint32* num_input_channels,
                                                uint32* num_output_channels,
                                                sw_cmm_transform *handle);
static void RIPCALL ccs_close_transform(sw_cmm_instance *instance,
                                        sw_cmm_transform transform);
static sw_cmm_result RIPCALL ccs_invoke_transform(sw_cmm_instance *instance,
                                                  sw_cmm_transform transform,
                                                  float* input_data,
                                                  float* output_data,
                                                  uint32 num_pixels);
static ccs_transformer ccs_invoke_transform_ps; 

static inline color_t ClampColor(int adj_c)
{
    color_t col;
    
    if (adj_c > MAX_COLOR)
        col = MAX_COLOR;
    else if (adj_c < 0)
        col = 0;
    else
        col = (color_t)adj_c;  /* safe typecast */
    return col;
}

static inline color_t AdjustBrightness(color_t col, int bri)
{
    if (col > COLOR_BALANCE_TOL)
    {
        int adj_c;
    
        bri = -bri;
        adj_c = (int)
                (
                    (
                       (COLOR_BALANCE_TOL - bri * COLOR_BALANCE_RATIO) * col 
                       + 
                       (MAX_COLOR * bri * COLOR_BALANCE_RATIO)
                    ) 
                    /
                    COLOR_BALANCE_TOL
                );
        col = ClampColor(adj_c);
    }
    else if (col < COLOR_BALANCE_TOL)
    {
        int adj_c;
    
        bri = -bri;
        adj_c = (int)((COLOR_BALANCE_TOL + bri * COLOR_BALANCE_RATIO) * col / COLOR_BALANCE_TOL);
        col = ClampColor(adj_c);
    }
    return col;
}

static inline color_t AdjustContrast(color_t col, int con)
{
#if CMM_PRECISSION != CMM_8BIT_PRECISSION
#error "Constrast only handled for 8 bit color"
#endif
    int adj_c =
         (int)((256 - 2 * con) / 256.0 * col + con);
    return ClampColor(adj_c);
}

static void ApplyColorBalanceCMYK(color_t c, 
                                  color_t m,
                                  color_t y,
                                  color_t k,
                                  int     bri, 
                                  int     bk,
                                  int     cy,
                                  int     ma,
                                  int     ye,
                                  int     con,
                                  color_t *c_out,
                                  color_t *m_out,
                                  color_t *y_out,
                                  color_t *k_out)
{
   /*
    * Step 1: Adjust brightness
    */
   int adj_c = (int)AdjustBrightness(c, bri);
   int adj_m = (int)AdjustBrightness(m, bri);
   int adj_y = (int)AdjustBrightness(y, bri);
   int adj_k = (int)AdjustBrightness(k, bri);
   
   /*
    * Step 2: Adjust Cyan, Magenta, Yellow and Black
    */
    adj_k += bk;
    adj_c += cy;
    adj_m += ma;
    adj_y += ye;
    
    /*
     * Step 3: Adjust contrast
     */
    *c_out = AdjustContrast(adj_c, con);
    *m_out = AdjustContrast(adj_m, con);
    *y_out = AdjustContrast(adj_y, con);
    *k_out = AdjustContrast(adj_k, con);
}
/**
 * @brief Function to implement black substitution.
 *
 * This function detects grey tones made up of a mixture of cyan,
 * magenta and yellow inks and replaces them with black only.
 * If the cyan, magenta and yellow values are equal, they are set to
 * zero and an equivalent amount of black is added to the existing
 * black value, capped at full black.
 *
 * If C=M=Y  -> C=M=Y=0, K=K+C (capped at 1.0f)
 *
 * @param[in,out]  cmykValue  An array containing a single CMYK value,
 * which is modified by the function, if required.
 */
static void BlackSubstitute(float cmykValue[])
{
  HQASSERT((cmykValue != NULL), "CMM: Black substitute invalid CMYK");

  /* if C M and Y components are equal, replace with K */
  if ((cmykValue[0] == cmykValue[1])
    && (cmykValue[0] == cmykValue[2]))
  {
    cmykValue[3] = cmykValue[3] + cmykValue[0];
    if (cmykValue[3] > 1.0f)
    {
      cmykValue[3] = 1.0f;
    }
    cmykValue[0] = cmykValue[1] = cmykValue[2] = 0;
  }
}

/**
 * @brief Function to implement pure black text feature.
 *
 * This function ensures that all black text is printed with 100% black ink,
 * and no colored ink.
 *
 * Convert C=M=Y=100% to K=100% C=M=Y=0
 *
 * @param[in,out]  cmykValue  An array containing a single CMYK value,
 * which is modified by the function, if required.
 */
static void PureBlackText(float cmykValue[])
{
  HQASSERT((cmykValue != NULL), "CMM: Pure Black Text invalid CMYK");

  /* if C M and Y components are all 1.0, replace with K */
  if ((cmykValue[0] == 1.0f)
    &&(cmykValue[1] == 1.0f)
    &&(cmykValue[2] == 1.0f))
  {
    cmykValue[3] = 1.0f;
    cmykValue[0] = cmykValue[1] = cmykValue[2] = 0;
  }
}

/**
 * @brief Function to implement all text black feature.
 *
 * This function forces all text to be rendered as soid black, using only
 * black ink, regardless of the requested color.
 *
 * Conversion forces K=100% and C=M=Y=0%
 *
 * @param[in,out]  cmykValue  An array containing a single CMYK input value,
 * which is modified by the function, if required.
 */
static void AllBlackText(float cmykValue[])
{
  HQASSERT((cmykValue != NULL), "CMM: All Black Text invalid CMYK");

  cmykValue[3] = 1.0f;
  cmykValue[0] = cmykValue[1] = cmykValue[2] = 0;
}

/**
 * @brief  Function to manage color mapping features for CMYK text.
 *
 * This function is called for all CMYK text. It calls various color
 * mapping functions, depending on the enabled features.
 *
 * The PMS function @c PMS_CMYKtoCMYK is also called to allow the
 * PMS code to apply any CMYK to CMYK color transform.
 *
 * @param[in,out]  cmykValue  An array containing a single CMYK input value,
 * which is modified by the function, if required.
 */
static void TextColorMapFeaturesCMYK(float cmykValue[])
{
  HQASSERT((cmykValue != NULL), "CMM: TextColorMapFeaturesCMYK invalid CMYK");

    unsigned char ucRGB[4];

    ucRGB[1]=(unsigned char)(cmykValue[0]*255);
    ucRGB[2]=(unsigned char)(cmykValue[1]*255);
    ucRGB[3]=(unsigned char)(cmykValue[2]*255);

    if( ucColorMode )
    {
        ulFlag = ulFlag | CR_STRBLT_24BPP | CR_STRBLT_RGB_ORDER | CR_STRBLT_RGB | CR_ATTR_TEXT;
    }
    
    setRGB( (void*)ColorData, ulFlag, nGrayMode, ppucSrcGam, nObjMode,
			 	ucColorMode, (unsigned char*) ucRGB, kCMYKChannelCount);

    cmykValue[3]=(float)(ucRGB[0]);///255.0;
    cmykValue[0]=(float)(ucRGB[1])/255.0;
    cmykValue[1]=(float)(ucRGB[2])/255.0;
    cmykValue[2]=(float)(ucRGB[3])/255.0;

    /*ORIGINAL*/
  /*if (g_pstCurrentJob->bBlackSubstitute)
    BlackSubstitute(cmykValue);
  if (g_pstCurrentJob->bPureBlackText)
    PureBlackText(cmykValue);
  if (g_pstCurrentJob->bAllTextBlack)
    AllBlackText(cmykValue);

   The PMS now has a chance to change the values 
  (void)PMS_CMYKtoCMYK(cmykValue); */

  
}

/**
 * @brief  Function to implement color mapping for 'Other' CMYK objects.
 *
 * This function is called for all CMYK object in the 'Other' category.
 * 'Other' objects are all objects excluding images, vignettes, and text.
 *
 * In this example, this function only calls the black substitute color
 * mapping function, if the black substitute feature is enabled.
 *
 * The PMS function @c PMS_CMYKtoCMYK is also called to allow the
 * PMS code to apply a CMYK to CMYK color transform.
 *
 * @param[in,out]  cmykValue  An array containing a single CMYK input value,
 * which is modified by the function, if required.
 */
static void DefaultColorMapFeaturesCMYK(float cmykValue[])
{
  HQASSERT((cmykValue != NULL), "CMM: DefaultColorMapFeaturesCMYK invalid CMYK");

  if (g_pstCurrentJob->bBlackSubstitute)
    BlackSubstitute(cmykValue);

  /* The PMS now has a chance to change the values */
  (void)PMS_CMYKtoCMYK(cmykValue);
}

static void PictureColorMapFeaturesCMYK(float cmykValue[])
{
    HQASSERT((cmykValue != NULL), "CMM: PictureColorMapFeaturesCMYK invalid CMYK");

    unsigned char ucRGB[4];

    ucRGB[1]=(unsigned char)(cmykValue[0]*255);
    ucRGB[2]=(unsigned char)(cmykValue[1]*255);
    ucRGB[3]=(unsigned char)(cmykValue[2]*255);

    if( ucColorMode )
    {
        ulFlag = ulFlag | CR_STRBLT_24BPP | CR_STRBLT_RGB_ORDER | CR_STRBLT_RGB | CR_ATTR_TEXT;
    }

    setRGB( (void*)ColorData, ulFlag, nGrayMode, ppucSrcGam, nObjMode,
			 	ucColorMode, (unsigned char*) ucRGB, kCMYKChannelCount);

    cmykValue[3]=(float)(ucRGB[0]);///255.0;
    cmykValue[0]=(float)(ucRGB[1])/255.0;
    cmykValue[1]=(float)(ucRGB[2])/255.0;
    cmykValue[2]=(float)(ucRGB[3])/255.0;

    /*ORIGINAL*/
  /*if (g_pstCurrentJob->bBlackSubstitute)
    BlackSubstitute(cmykValue);
  if (g_pstCurrentJob->bPureBlackText)
    PureBlackText(cmykValue);
  if (g_pstCurrentJob->bAllTextBlack)
    AllBlackText(cmykValue); */

  /* The PMS now has a chance to change the values
  (void)PMS_CMYKtoCMYK(cmykValue); */


}

/**
 * @brief  Function to implement RGB to CMYK transformation.
 *
 * In this example, the function merely calls the PMS function
 * @c PMS_RGBtoCMYK to allow PMS to apply a RGB to CMYK color
 * transform.
 *
 * @param[in, out] rgbInCMYKOutValue  An array of floating point values which is
 * assumed to contain an RGB color when it is passed in, and is populated with
 * the corresponding CMYK value by the call.
 */
static void DefaultColorMapFeaturesRGB(float rgbInCMYKOutValue[])
{
    unsigned char ucRGB[4];

    nObjMode = PR_OBJ_GRAP;
    ulFlag = PR_COLOR_RGB ;

    //g_pstCurrentJob->eColorMode = OIL_CMYK_Composite;
   	// setColorMode();

    setPageStartDefault(nObjMode);

    HQASSERT((rgbInCMYKOutValue != NULL), "CMM: DefaultColorMapFeaturesRGB invalid color array");

    ucRGB[0]=(unsigned char)(rgbInCMYKOutValue[0]*255);
    ucRGB[1]=(unsigned char)(rgbInCMYKOutValue[1]*255);
    ucRGB[2]=(unsigned char)(rgbInCMYKOutValue[2]*255);
    ucRGB[3]=0;

   // setRGB( (void*)ColorData, ulFlag, nGrayMode, ppucSrcGam, nObjMode,
			 	//ucColorMode, (unsigned char*) ucRGB, kCMYKChannelCount);
    SetcolorGG(ulVectorGray,ulGrayJudgeMode,ucColorMode,devinfo->toner_limit, ucDither,pLimit, ulFlag,
   			    		(void*)ColorData, (unsigned char*) ucRGB,(unsigned char*)rgbInCMYKOutValue, nObjMode,
   			    		nObjectType, ppucSrcGam,tlimit);

       rgbInCMYKOutValue[3]=(float)(ucRGB[0])/255.0;
       rgbInCMYKOutValue[0]=(float)(ucRGB[1])/255.0;
       rgbInCMYKOutValue[1]=(float)(ucRGB[2])/255.0;
       rgbInCMYKOutValue[2]=(float)(ucRGB[3])/255.0;

      /* ORIGINAL */
      /*float rgbValue[3];

      rgbValue[0] = rgbInCMYKOutValue[0];
      rgbValue[1] = rgbInCMYKOutValue[1];
      rgbValue[2] = rgbInCMYKOutValue[2];*/

      /* The PMS now has a chance to change the values 
      (void)PMS_RGBtoCMYK(rgbValue, rgbInCMYKOutValue);*/

  /* The PMS now has a chance to change the values 
  (void)PMS_RGBtoCMYK(rgbValue, rgbInCMYKOutValue); */
}

static void DefaultColorMapFeaturesRGBText(float rgbInCMYKOutValue[])
 {
 	printf("\n Entered DefaultColorMapFeaturesRGBText");
	unsigned char ucRGB[4];
	nObjMode = PR_OBJ_TEXT;
    // Default of PageStart option
	setPageStartDefault(nObjMode);

	ulFlag = PR_COLOR_RGB;

	 //g_pstCurrentJob->eColorMode = OIL_CMYK_Composite;
	 //setColorMode();

	 ucRGB[0]=(unsigned char)(rgbInCMYKOutValue[0]*255);
	 ucRGB[1]=(unsigned char)(rgbInCMYKOutValue[1]*255);
	 ucRGB[2]=(unsigned char)(rgbInCMYKOutValue[2]*255);
	 ucRGB[3]=0;

		//setRGB( (void*)ColorData, ulFlag, nGrayMode, ppucSrcGam, nObjMode,
					//ucColorMode, (unsigned char*) ucRGB, kCMYKChannelCount,m_ulColorFlag);
		 SetcolorGG(ulVectorGray,ulGrayJudgeMode,ucColorMode,devinfo->toner_limit, ucDither, pLimit, ulFlag,
		   			    		(void*)ColorData, (unsigned char*) ucRGB,(unsigned char*)rgbInCMYKOutValue, nObjMode,
		   			    		nObjectType, ppucSrcGam,&tlimit);

		 rgbInCMYKOutValue[3]=(float)(ucRGB[0])/255.0;
		  rgbInCMYKOutValue[0]=(float)(ucRGB[1])/255.0;
		   rgbInCMYKOutValue[1]=(float)(ucRGB[2])/255.0;
		       rgbInCMYKOutValue[2]=(float)(ucRGB[3])/255.0;

 }

static void DefaultColorMapFeaturesRGBImage(float rgbInCMYKOutValue[])
 {
 	printf("\n Entered DefaultColorMapFeaturesRGBImage");
	unsigned char ucRGB[4];
	nObjMode = PR_OBJ_IMAG;
	//nObjMode |= PR_OBJ_IMAG_COLOR;
	setPageStartDefault(nObjMode);

	ulFlag = PR_COLOR_RGB;

	 //g_pstCurrentJob->eColorMode = OIL_CMYK_Composite;
	 //setColorMode();

	 ucRGB[0]=(unsigned char)(rgbInCMYKOutValue[0]*255);
	 ucRGB[1]=(unsigned char)(rgbInCMYKOutValue[1]*255);
	 ucRGB[2]=(unsigned char)(rgbInCMYKOutValue[2]*255);
	 ucRGB[3]=0;

		//setRGB( (void*)ColorData, ulFlag, nGrayMode, ppucSrcGam, nObjMode,
					//ucColorMode, (unsigned char*) ucRGB, kCMYKChannelCount,m_ulColorFlag);
		 SetcolorGG(ulVectorGray,ulGrayJudgeMode,ucColorMode,devinfo->toner_limit, ucDither, pLimit, ulFlag,
		   			    		(void*)ColorData, (unsigned char*) ucRGB,(unsigned char*)rgbInCMYKOutValue, nObjMode,
		   			    		nObjectType, ppucSrcGam,&tlimit);

		 rgbInCMYKOutValue[3]=(float)(ucRGB[0])/255.0;
		       rgbInCMYKOutValue[0]=(float)(ucRGB[1])/255.0;
		       rgbInCMYKOutValue[1]=(float)(ucRGB[2])/255.0;
		       rgbInCMYKOutValue[2]=(float)(ucRGB[3])/255.0;

 }

static void DefaultColorMapFeaturesGray(float rgbInCMYKOutValue[])
{
    unsigned char ucRGB[4];

    nObjMode = PR_OBJ_GRAP;
    ulFlag = PR_COLOR_GRAY;

    setPageStartDefault(nObjMode);

    HQASSERT((rgbInCMYKOutValue != NULL), "CMM: DefaultColorMapFeaturesRGB invalid color array");

    ucRGB[0]=(unsigned char)(rgbInCMYKOutValue[0]*255);
    ucRGB[1]=0;//(unsigned char)(rgbInCMYKOutValue[1]*255);
    ucRGB[2]=0;//(unsigned char)(rgbInCMYKOutValue[2]*255);
    ucRGB[3]=0;

    SetcolorGG(ulVectorGray,ulGrayJudgeMode,ucColorMode,devinfo->toner_limit, ucDither,pLimit, ulFlag,
   			    		(void*)ColorData, (unsigned char*) ucRGB,(unsigned char*)rgbInCMYKOutValue, nObjMode,
   			    		nObjectType, ppucSrcGam,tlimit);

    rgbInCMYKOutValue[0]=(float)(ucRGB[0])/255.0;
           rgbInCMYKOutValue[1]=0;//(float)(ucRGB[1]/255);
         	rgbInCMYKOutValue[2]=0; //(float)(ucRGB[2]/255);
         	rgbInCMYKOutValue[3]=0;//(float)(ucRGB[3]/255);
}

static void DefaultColorMapFeaturesGrayText(float rgbInCMYKOutValue[])
{
    unsigned char ucRGB[4];

    nObjMode = PR_OBJ_TEXT;
    ulFlag = PR_COLOR_GRAY;

    setPageStartDefault(nObjMode);

    HQASSERT((rgbInCMYKOutValue != NULL), "CMM: DefaultColorMapFeaturesRGB invalid color array");

    ucRGB[0]=(unsigned char)(rgbInCMYKOutValue[0]*255);
       ucRGB[1]=0;//(unsigned char)(rgbInCMYKOutValue[1]*255);
       ucRGB[2]=0;//(unsigned char)(rgbInCMYKOutValue[2]*255);
       ucRGB[3]=0;

    SetcolorGG(ulVectorGray,ulGrayJudgeMode,ucColorMode,devinfo->toner_limit, ucDither,pLimit, ulFlag,
   			    		(void*)ColorData, (unsigned char*) ucRGB,(unsigned char*)rgbInCMYKOutValue, nObjMode,
   			    		nObjectType, ppucSrcGam,tlimit);

    rgbInCMYKOutValue[0]=(float)(ucRGB[0])/255.0;
        rgbInCMYKOutValue[1]=0;//(float)(ucRGB[1]/255);
      	rgbInCMYKOutValue[2]=0; //(float)(ucRGB[2]/255);
      	rgbInCMYKOutValue[3]=0;//(float)(ucRGB[3]/255);
}

static void DefaultColorMapFeaturesGrayImage(float rgbInCMYKOutValue[])
{
    unsigned char ucRGB[4];

    nObjMode = PR_OBJ_IMAG;
    nObjMode |= PR_OBJ_IMAG_MONO;
    ulFlag = PR_COLOR_GRAY;

    setPageStartDefault(nObjMode);

    HQASSERT((rgbInCMYKOutValue != NULL), "CMM: DefaultColorMapFeaturesRGB invalid color array");

    ucRGB[0]=(unsigned char)(rgbInCMYKOutValue[0]*255);
       ucRGB[1]=0;//(unsigned char)(rgbInCMYKOutValue[1]*255);
       ucRGB[2]=0;//(unsigned char)(rgbInCMYKOutValue[2]*255);
       ucRGB[3]=0;

    SetcolorGG(ulVectorGray,ulGrayJudgeMode,ucColorMode,devinfo->toner_limit, ucDither,pLimit, ulFlag,
   			    		(void*)ColorData, (unsigned char*) ucRGB,(unsigned char*)rgbInCMYKOutValue, nObjMode,
   			    		nObjectType, ppucSrcGam,tlimit);

    rgbInCMYKOutValue[0]=(float)(ucRGB[0])/255.0;
           rgbInCMYKOutValue[1]=0;//(float)(ucRGB[1]/255);
         	rgbInCMYKOutValue[2]=0; //(float)(ucRGB[2]/255);
         	rgbInCMYKOutValue[3]=0;//(float)(ucRGB[3]/255);

}

/**
  * Conversion routines for PS grayscale 
  */
/*
 * CMYK to Gray conversion
 */
static sw_cmm_result RIPCALL PSDefaultColorMapFeaturesCMYK_Gray(long           rcmm,
                                                                CMM_TRANSFORM  *transform,
                                                                color_t        *input_data,
                                                                color_t        *output_data )
{
    HQASSERT(FALSE, "Not implemented yet");
    return SW_CMM_SUCCESS;
}

/*
 * RGB to Gray conversion
 */
static sw_cmm_result RIPCALL PSDefaultColorMapFeaturesRGB_Gray(long           rcmm,
                                                               CMM_TRANSFORM  *transform,
                                                               color_t        *input_data,
                                                               color_t        *output_data)
{
    HQASSERT(FALSE, "Not implemented yet");
    return SW_CMM_SUCCESS;
}

/*
 * Gray to Gray conversion
 */
static sw_cmm_result RIPCALL PSDefaultColorMapFeaturesGray_Gray(long           rcmm,
                                                                CMM_TRANSFORM  *transform,
                                                                color_t        *input_data,
                                                                color_t        *output_data)
{
    HQASSERT(FALSE, "Not implemented yet");
    return SW_CMM_SUCCESS;
}

/**
 * Conversion routines for PS color 
 */

 /*
 * CMYK to CMYK color matching
 */
static sw_cmm_result RIPCALL PSDefaultColorMapFeaturesCMYK_CMYK(long           rcmm,
                                                                CMM_TRANSFORM  *transform,
                                                                color_t        *input_data,
                                                                color_t        *output_data)
{
    HQASSERT(FALSE, "Not implemented yet");
    return SW_CMM_SUCCESS;
}
static sw_cmm_result RIPCALL PSColorMapFeaturesRGB_CMYK(long           rcmm,
                                                        unsigned int   key,
                                                        CMM_TRANSFORM  *transform,
                                                        color_t        *input_data,
                                                        color_t        *output_data)
{
    long    ret;
    color_t c;
    color_t m;
    color_t y;
    color_t min;
    
    ret = CMM_DoConversion4_rgb(cmm,
                                input_data,
                                output_data,
                                1, /* number of pixel */
                                key,
                                CMM_8BIT_PRECISSION,
                                CMM_8BIT_PRECISSION);
    if (ret == -1)
        return SW_CMM_ERROR;
    c = MAX_COLOR - output_data[0];
    m = MAX_COLOR - output_data[1];
    y = MAX_COLOR - output_data[2];
    min = c < m ? c : m;
    min = y < min ? y : min; 
    /*
     * need to apply UCR/BG etc here
     */
    output_data[0] = c - min;
    output_data[1] = m - min;
    output_data[2] = y - min;
    output_data[3] = min;
    
    ApplyColorBalanceCMYK
    (
        output_data[0],
        output_data[1], 
        output_data[2],
        output_data[3],
        0,
        0,
        0,
        0,
        0,
        0,
        &output_data[0],
        &output_data[1], 
        &output_data[2],
        &output_data[3]
    );
    return SW_CMM_SUCCESS;
}

/*
 * Default RGB to CMYK color matching
 */
static sw_cmm_result RIPCALL PSDefaultColorMapFeaturesRGB_CMYK(long           rcmm,
                                                               CMM_TRANSFORM  *transform,
                                                               unsigned char  *input_data,
                                                               unsigned char  *output_data)
{
    unsigned int key = COLOR_MAKE_PROF_KEY(COLOR_CONV_RGB_RGB,
                                           COLOR_MEDIA_NORMAL,
                                           COLOR_MATCH_GRAPHIC);
    return PSColorMapFeaturesRGB_CMYK(rcmm, key, transform, input_data, output_data);
}

static sw_cmm_result RIPCALL PSTextColorMapFeaturesRGB_CMYK(long           rcmm,
                                                            CMM_TRANSFORM  *transform,
                                                            unsigned char  *input_data,
                                                            unsigned char  *output_data)
{
    unsigned int key = COLOR_MAKE_PROF_KEY(COLOR_CONV_RGB_RGB,
                                           COLOR_MEDIA_NORMAL,
                                           COLOR_MATCH_TEXT);
    return PSColorMapFeaturesRGB_CMYK(rcmm, key, transform, input_data, output_data);
}

static sw_cmm_result RIPCALL PSPictureColorMapFeaturesRGB_CMYK(long           rcmm,
                                                               CMM_TRANSFORM  *transform,
                                                               unsigned char  *input_data,
                                                               unsigned char  *output_data)
{
    unsigned int key = COLOR_MAKE_PROF_KEY(COLOR_CONV_RGB_RGB,
                                           COLOR_MEDIA_NORMAL,
                                           COLOR_MATCH_IMAGE);
    return PSColorMapFeaturesRGB_CMYK(rcmm, key, transform, input_data, output_data);
}
/*
 * GRAY to CMYK color matching
 */
static sw_cmm_result RIPCALL PSDefaultColorMapFeaturesGray_CMYK(long           rcmm,
                                               CMM_TRANSFORM  *transform,
                                               unsigned char  *input_data,
                                               unsigned char  *output_data)
{
    HQASSERT(FALSE, "Not implemented yet");
    return SW_CMM_SUCCESS;
}

/**
 * @brief  Singleton instance describing this alternate CMM.
 */
static sw_cmm_api gCCSExampleImplementation =
{
  {
    SW_CMM_API_VERSION_20071109,    /* version */
    (uint8*) kInternalName,         /* name */
    (uint8*) kDisplayName,          /* name_display */
    sizeof(sw_cmm_instance)         /* instance size */
  },
  NULL,                           /* init callback */
  NULL,                           /* finish callback */
  ccs_construct,                  /* construct callback. */
  NULL,                           /* destruct callback */
  ccs_open_profile,               /* open_profile callback. */
  ccs_close_profile,              /* close_profile callback. */
  ccs_declare_custom_colorspace,  /* declare_custom_colorspace callback. */
  ccs_open_custom_colorspace,     /* open_custom_colorspace callback. */
  ccs_open_transform,             /* open_transform callback. */
  ccs_close_transform,            /* close_transform callback. */
  ccs_invoke_transform,           /* invoke_transform callback. */
  NULL,                           /* security callback. */
};

/**
 * @brief Retrieve a pointer to the sample
 * CMM implemented by this code.
 */
sw_cmm_api* oilccs_getInstance(void)
{
  return &gCCSExampleImplementation;
}

/**
 * @brief Allocate memory for use by the CMM.
 */
static void* cmmMemAlloc(sw_memory_instance *instance, size_t n)
{
  HQASSERT(instance, "No memory API instance") ;
  HQASSERT(instance->implementation != NULL, "No memory API implementatio");
  HQASSERT(instance->implementation->info.version >= SW_MEMORY_API_VERSION_20071110,
           "Memory API version insufficient");
  HQASSERT(instance->implementation->alloc != NULL, "No memory API alloc");
  return instance->implementation->alloc(instance, n);
}

/**
 * @brief  Release memory allocated by the CMM.
 */
static void cmmMemFree(sw_memory_instance *instance, void* p)
{
  HQASSERT(instance, "No memory API instance") ;
  HQASSERT(instance->implementation != NULL, "No memory API implementatio");
  HQASSERT(instance->implementation->info.version >= SW_MEMORY_API_VERSION_20071110,
           "Memory API version insufficient");
  HQASSERT(instance->implementation->free != NULL, "No memory API free");
  instance->implementation->free(instance, p);
}
///////////////////////////////////////////////////////////////////////////////
//Function      :CMMalloc
//Description   :Malloc function
//Arguments     :
//              :unsigned long size:[IN]
//              :void *inst:[IN]
//Return value  :long:Handle to Memory, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
long
CMMalloc(unsigned long size, void *inst)
{
sw_memory_instance *instance =(sw_memory_instance *)inst;
	
  HQASSERT(instance, "No memory API instance") ;
  HQASSERT(instance->implementation != NULL, "No memory API implementatio");
  HQASSERT(instance->implementation->info.version >= SW_MEMORY_API_VERSION_20071110,
           "Memory API version insufficient");
  HQASSERT(instance->implementation->free != NULL, "No memory API free");
 return ((long)(instance->implementation->alloc(instance, size)));

}
///////////////////////////////////////////////////////////////////////////////
//Function      :CMMfree
//Description   : Free function
//Arguments     :
//              :void* addr:[IN]
//              :void* inst:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CMMfree(void* addr, void* inst)
{
sw_memory_instance *instance =(sw_memory_instance *)inst;
  HQASSERT(instance, "No memory API instance") ;
  HQASSERT(instance->implementation != NULL, "No memory API implementatio");
  HQASSERT(instance->implementation->info.version >= SW_MEMORY_API_VERSION_20071110,
           "Memory API version insufficient");
  HQASSERT(instance->implementation->free != NULL, "No memory API free");
  instance->implementation->free(instance, addr);
}
/**
 * @brief Construct an instance of the @c sw_cmm_api interface.
 *
 * The RIP constructs an instance of each CMM module after booting the
 * interpreter. The RIP fills in the implementation pointer and pointers to
 * the memory API and blob API instances. The module is expected to fill in
 * the remaining fields, which contain flags defining the capabilities of
 * the module. Some of the information returned will be used by the RIP to
 * determine whether a particular profile or transform can be handled by
 * a given module, and in other cases the RIP will use this information to
 * divert color conversions through its built-in CMM if appropriate.
 *
 * @param[in,out]  instance
 * @return A @c sw_cmm_result result code.
 */
static sw_cmm_result RIPCALL ccs_construct(sw_cmm_instance *instance)
{
  HQASSERT(instance != NULL, "No CMM instance");
  HQASSERT(instance->implementation == &gCCSExampleImplementation,
           "Invalid CMM instance");
  HQASSERT(instance->mem != NULL, "No memory API");

  /* The alloc/free functions need at least this version. */
  if ( instance->mem->implementation->info.version < SW_MEMORY_API_VERSION_20071110 )
    return SW_CMM_ERROR_VERSION ;

  instance->support_input_profiles = FALSE;
  instance->support_output_profiles = FALSE;
  instance->support_devicelink_profiles = FALSE;
  instance->support_display_profiles = FALSE;
  instance->support_colorspace_profiles = FALSE;
  instance->support_abstract_profiles = FALSE;
  instance->support_named_color_profiles = FALSE;
  instance->support_ICC_v4 = FALSE;
  instance->support_black_point_compensation = FALSE;
  instance->support_extra_absolute_intents = FALSE;
  instance->maximum_input_channels = kCMYKChannelCount;
  instance->maximum_output_channels = kCMYKChannelCount;
  instance->allow_retry = FALSE;

/*	cmm = CMM_Init(cmmMemAlloc, cmmMemFree, NULL, 33554432);	*/
	cmm = CMM_Init((long (*)())CMMalloc,(void (*)())CMMfree,(void *)(instance->mem), 12000);

	gps_color_profile_info_GPS_t *profaddress = (gps_color_profile_info_GPS_t *)devinfo->profaddress;
	while (devinfo->profnumber--)
	{
		printf("CMM_OpenProfile() for [%s]\n",profaddress->path); 
		printf("[CMM]profaddress->key = [0x%ld], profaddress->path = [%s]\n", profaddress->key, profaddress->path);

		if (CMM_OK != CMM_OpenProfile(cmm, FILEBASE, profaddress->path, profaddress->key))
		{
			printf ("[CMM] CMM_OpenProfile() failed for [%s]\n",profaddress->path);
		}
		profaddress++;
	}


/* 	cmmMemAlloc(instance->mem, sizeof(CMM_PROFILE));*/
  return SW_CMM_SUCCESS ;
}

/**
 * @brief  Create an internal profile structure for ICC profile data accessed
 * using a seekable file stream.
 *
 * @note Not supported in this implementation.
 *
 * @param[in]      instance         The alternate CMM instance.
 * @param[in]      profile_source   A blob reference to access the profile data.
 * @param[in,out]  handle           A pointer to the profile created by the function.
 * @return A @c sw_cmm_result result code.
 *
 * @see ccs_close_profile()
 */
static sw_cmm_result RIPCALL ccs_open_profile(sw_cmm_instance *instance,
                                              sw_blob_instance *profile_source,
                                              sw_cmm_profile *handle)
{
  HQASSERT(instance, "No CMM instance") ;
  HQASSERT(profile_source != NULL, "No CMM profile data");

  UNUSED_PARAM(sw_cmm_instance *, instance);
  UNUSED_PARAM(sw_blob_instance*, profile_source);
  UNUSED_PARAM(sw_cmm_profile*, handle);

  /* Should never be called in this implementation */
  HQFAIL("Should never call this function");

  return SW_CMM_ERROR;
}

/**
 * @brief  Close a profile with a handle previously created
 * with ccs_open_profile().
 *
 * @param[in]  instance         The alternate CMM instance.
 * @param[in]  profile          Pointer to the CMM profile to be closed.
 *
 * @see ccs_open_profile()
 */
static void RIPCALL ccs_close_profile(sw_cmm_instance *instance,
                                      sw_cmm_profile profile)
{
  HQASSERT(instance, "No CMM instance") ;
  HQASSERT(profile != NULL, "No CMM profile");
  cmmMemFree(instance->mem, profile);
}

/**
 * @brief  Declare a custom color space to the RIP.
 *
 * @param[in]  instance         The alternate CMM instance.
 * @param[in]  index            Zero-based index into an array of color spaces
 * handled by this CMM.
 * @return                      A pointer to a sw_cmm_custom_colorspace object,
 *                              or <code>NULL</code> if index is out of bounds.
 */
static sw_cmm_custom_colorspace* RIPCALL ccs_declare_custom_colorspace(sw_cmm_instance *instance,
                                                               uint32 index)
{
  const uint32 kCustomColorSpaceCount = sizeof (gCCSArray) / sizeof (gCCSArray[0]);

  UNUSED_PARAM(sw_cmm_instance *, instance);
  HQASSERT(instance, "No CMM instance") ;

  if (index < kCustomColorSpaceCount)
    return &gCCSArray[index];

  /* index is out of bounds */
  return NULL;
}


/**
 * @brief  Create an internal profile structure for a custom colorspace.
 *
 * This function initializes a function pointer which is later used to perform
 * the color transform.
 *
 * @param[in]      instance         The alternate CMM instance.
 * @param[in]      index            Zero-based index into an array of color spaces
 *                                  handled by this CMM.
 * @param[in,out]  handle           A pointer to the profile created by the function.
 * @return A @c sw_cmm_result result code.
 *
 * @see ccs_declare_custom_colorspace()
 */
static sw_cmm_result RIPCALL ccs_open_custom_colorspace(sw_cmm_instance *instance,
                                                        uint32 index,
                                                        sw_cmm_profile *handle)
{
  const uint32 kCustomColorSpaceCount = sizeof(gCCSArray) / sizeof(gCCSArray[0]);
  CMM_PROFILE* pProfile;

  HQASSERT(instance, "No CMM instance") ;
  HQASSERT(handle, "No CMM profile") ;

  if (index >= kCustomColorSpaceCount)
    return SW_CMM_ERROR_INVALID; /* index out of bounds */

  pProfile = cmmMemAlloc(instance->mem, sizeof(CMM_PROFILE));
  if (! pProfile)
    return SW_CMM_ERROR_MEMORY;

  switch (index)
  {
  case kCCS_TextColorMapFeaturesCMYKIndex:
    pProfile->prf_pTransformFn = NULL;
    pProfile->pMappingFunc = TextColorMapFeaturesCMYK;
    pProfile->nInputChannels = kCMYKChannelCount;
    pProfile->nOutputChannels = kCMYKChannelCount;
    break;

  case kCCS_PictureColorMapFeaturesCMYKIndex:
     pProfile->prf_pTransformFn = NULL;
     pProfile->pMappingFunc = PictureColorMapFeaturesCMYK;
     pProfile->nInputChannels = kCMYKChannelCount;
     pProfile->nOutputChannels = kCMYKChannelCount;
     break;

  case kCCS_DefaultColorMapFeaturesCMYKIndex:
    pProfile->prf_pTransformFn = NULL;
    pProfile->pMappingFunc = DefaultColorMapFeaturesCMYK;
    pProfile->nInputChannels = kCMYKChannelCount;
    pProfile->nOutputChannels = kCMYKChannelCount;
    break;
  case kCCS_DefaultColorMapFeaturesRGBTextIndex:
      pProfile->prf_pTransformFn = NULL;
      pProfile->pMappingFunc = DefaultColorMapFeaturesRGBText;
      pProfile->nInputChannels = kRGBChannelCount;
      pProfile->nOutputChannels = kCMYKChannelCount;
      break;
  case kCCS_DefaultColorMapFeaturesRGBImageIndex:
      pProfile->prf_pTransformFn = NULL;
      pProfile->pMappingFunc = DefaultColorMapFeaturesRGBImage;
      pProfile->nInputChannels = kRGBChannelCount;
      pProfile->nOutputChannels = kCMYKChannelCount;
      break;
  case kCCS_DefaultColorMapFeaturesRGBIndex:
    pProfile->prf_pTransformFn = NULL;
    pProfile->pMappingFunc = DefaultColorMapFeaturesRGB;
    pProfile->nInputChannels = kRGBChannelCount;
    pProfile->nOutputChannels = kCMYKChannelCount;
    break;
  case kCCS_DefaultColorMapFeaturesGrayTextIndex:
      pProfile->prf_pTransformFn = NULL;
      pProfile->pMappingFunc = DefaultColorMapFeaturesGrayText;
      pProfile->nInputChannels = kGrayChannelCount;
      pProfile->nOutputChannels = kGrayChannelCount;
      break;
  case kCCS_DefaultColorMapFeaturesGrayImageIndex:
      pProfile->prf_pTransformFn = NULL;
      pProfile->pMappingFunc = DefaultColorMapFeaturesGrayImage;
      pProfile->nInputChannels = kGrayChannelCount;
      pProfile->nOutputChannels = kGrayChannelCount;
      break;
  case kCCS_DefaultColorMapFeaturesGrayIndex:
    pProfile->prf_pTransformFn = NULL;
    pProfile->pMappingFunc = DefaultColorMapFeaturesGray;
    pProfile->nInputChannels = kGrayChannelCount;
    pProfile->nOutputChannels = kGrayChannelCount;
    break;
  /* PS grayscale conversion */
  case kCCS_PSDefaultColorMapFeaturesCMYK_Gray:
      pProfile->prf_pTransformFn = PSDefaultColorMapFeaturesCMYK_Gray;
      pProfile->pMappingFunc     = NULL;
      pProfile->nInputChannels   = kCMYKChannelCount;
      pProfile->nOutputChannels  = kGrayChannelCount;
      break;
  case kCCS_PSDefaultColorMapFeaturesRGB_Gray:
      pProfile->prf_pTransformFn  = PSDefaultColorMapFeaturesRGB_Gray;
      pProfile->pMappingFunc    = NULL;
      pProfile->nInputChannels  = kRGBChannelCount;
      pProfile->nOutputChannels = kGrayChannelCount;
      break;
  case kCCS_PSDefaultColorMapFeaturesGray_Gray:
     pProfile->prf_pTransformFn    = PSDefaultColorMapFeaturesGray_Gray;
     pProfile->pMappingFunc    = NULL;
     pProfile->nInputChannels  = kGrayChannelCount;
     pProfile->nOutputChannels = kGrayChannelCount;
     break;
  /* PS color conversion */
  case kCCS_PSDefaultColorMapFeaturesCMYK_CMYK:
     pProfile->prf_pTransformFn    = PSDefaultColorMapFeaturesCMYK_CMYK;
     pProfile->pMappingFunc    = NULL;
     pProfile->nInputChannels  = kCMYKChannelCount;
     pProfile->nOutputChannels = kCMYKChannelCount;
     break;
  case kCCS_PSTextColorMapFeaturesRGB_CMYK:
     pProfile->prf_pTransformFn    = PSTextColorMapFeaturesRGB_CMYK;
     pProfile->pMappingFunc    = NULL;
     pProfile->nInputChannels  = kRGBChannelCount;
     pProfile->nOutputChannels = kCMYKChannelCount;
     break;
  case kCCS_PSPictureColorMapFeaturesRGB_CMYK:
     pProfile->prf_pTransformFn    = PSPictureColorMapFeaturesRGB_CMYK;
     pProfile->pMappingFunc    = NULL;
     pProfile->nInputChannels  = kRGBChannelCount;
     pProfile->nOutputChannels = kCMYKChannelCount;
     break;
  case kCCS_PSDefaultColorMapFeaturesRGB_CMYK:
     pProfile->prf_pTransformFn    = PSDefaultColorMapFeaturesRGB_CMYK;
     pProfile->pMappingFunc    = NULL;
     pProfile->nInputChannels  = kRGBChannelCount;
     pProfile->nOutputChannels = kCMYKChannelCount;
     break;
  case kCCS_PSDefaultColorMapFeaturesGray_CMYK:
     pProfile->prf_pTransformFn    = PSDefaultColorMapFeaturesGray_CMYK;
     pProfile->pMappingFunc    = NULL;
     pProfile->nInputChannels  = kGrayChannelCount;
     pProfile->nOutputChannels = kCMYKChannelCount;
     break;
  default:
    /* index out of bounds - Should never be reached */
    HQFAIL("Colorspace index out of bounds");
    cmmMemFree(instance->mem, pProfile);
    return SW_CMM_ERROR_INVALID;
  }

  *handle = pProfile;
  return SW_CMM_SUCCESS;
}

/**
 * @brief  Create a transform structure.
 *
 * @param[in]  instance         The alternate CMM instance.
 * @param[in]  profiles  An array of sw_cmm_profile handles, each of which refers to
 * profiles in the same sequence as required by the transform.
 * @param[in]  num_profiles  Number of entries in profiles array.
 * @param[in]  intents Array indicating the rendering intent to use when converting
 * colors between neighboring profiles. Contains (num_profiles - 1) entries.
 * @param[in]  black_point_compensations  Array indicating whether to apply black
 * point compensation when converting colors between neighboring profiles.
 * Contains (num_profiles - 1) entries.
 * @param[out]  num_input_channels  Should be set as the number of color
 * channels in the input space of profiles[0].
 * @param[out]  num_output_channels  Should be set as the number of color
 * channels in the output space of profiles[num_profiles - 1].
 * @param[out]  handle  A pointer to the created@c  sw_cmm_transform strucure.
 * @return A @c sw_cmm_result result code.
 *
 * @see ccs_close_transform(), ccs_invoke_transform()
 */
static sw_cmm_result RIPCALL ccs_open_transform(sw_cmm_instance *instance,
                                                sw_cmm_profile profiles[],
                                                uint32 num_profiles,
                                                int32 intents[],
                                                HqBool black_point_compensations[],
                                                uint32* num_input_channels,
                                                uint32* num_output_channels,
                                                sw_cmm_transform *handle)
{
  CMM_TRANSFORM* pTransform;
  CMM_PROFILE* pProfiles;
  uint32 i;

  HQASSERT(instance, "No CMM instance") ;
  HQASSERT(profiles != NULL, "No CMM profiles");
  HQASSERT(num_input_channels != NULL, "No input data");
  HQASSERT(num_output_channels != NULL, "No output data");
  HQASSERT(num_profiles > 0, "Not enough profiles");
  HQASSERT(handle, "No CMM transform") ;

  UNUSED_PARAM(int32*,intents);
  UNUSED_PARAM(HqBool*, black_point_compensations);

  /* Allocate memory for a transform object */
  pTransform = cmmMemAlloc(instance->mem, sizeof(CMM_TRANSFORM));
  if (! pTransform)
    return SW_CMM_ERROR_MEMORY;

  pTransform->nProfiles = num_profiles;
  pTransform->pProfileArray = cmmMemAlloc(instance->mem, sizeof(CMM_PROFILE) * num_profiles);
  if (! pTransform->pProfileArray)
  {
    cmmMemFree(instance->mem, pTransform);
    return SW_CMM_ERROR_MEMORY;
  }

  /* Create transform */
  pProfiles = (CMM_PROFILE*) profiles;
  for (i = 0; i < num_profiles; i ++)
    pTransform->pProfileArray[i] = pProfiles[i];

  /* Set channel counts */
  *num_input_channels = pProfiles[0].nInputChannels;
  *num_output_channels = pProfiles[num_profiles - 1].nOutputChannels;
  /* Set conversion routine if required */
  if (g_pstCurrentJob->ePDLType == OIL_PDL_PS)
  {
    pTransform->trf_pTransformFn = ccs_invoke_transform_ps;
  }
  else
  {
    pTransform->trf_pTransformFn = NULL;
  }
  pTransform->trf_cmm     = cmm;
  pTransform->trf_devinfo = devinfo;
  *handle = pTransform;
  return SW_CMM_SUCCESS;
}

/**
 * @brief  Close a transform previously opened with ccs_open_transform().
 *
 * @param[in]  instance         The alternate CMM instance.
 * @param[in]  transform        Pointer to a CMM transform structure.
 *
 * @see ccs_open_transform(), ccs_invoke_transform()
 */
static void RIPCALL ccs_close_transform(sw_cmm_instance *instance,
                                        sw_cmm_transform transform)
{
  CMM_TRANSFORM* pTransform = (CMM_TRANSFORM*) transform;

  HQASSERT(instance, "No CMM instance") ;
  HQASSERT(pTransform != NULL, "No CMM transform");
  cmmMemFree(instance->mem, pTransform->pProfileArray);
  cmmMemFree(instance->mem, pTransform);
}

/**
 * @brief  Use the specified transform to adjust color data for PS
 *
 * The RIP will place color data in memory beginning at input_data. This
 * function should converts the data using the transform and places the
 * output values in memory beginning at output_data.
 *
 * @param[in]  instance      The alternate CMM instance.
 * @param[in]  transform     The transform to use for color conversions.
 * @param[in]  input_data    RIP-allocated array of input color values.
 * @param[out]  output_data  RIP-allocated array to fill with output color values.
 * @param[in]  num_pixels    Number of color values to transform.
 * @return <code>TRUE</code> on success, <code>FALSE</code> otherwise.
 *
 * @see ccs_open_transform(), ccs_close_transform()
 */
static sw_cmm_result RIPCALL ccs_invoke_transform_ps(sw_cmm_instance *instance,
                                                     CMM_TRANSFORM   *transform,
                                                     float           *input_data,
                                                     float           *output_data,
                                                     uint32          num_pixels)
{
   uint32         nInputChannels;
   uint32         nOutputChannels;
   unsigned  char src[kCMYKChannelCount];
   unsigned  char dst[kCMYKChannelCount];
   unsigned  char *psrc;
   unsigned  char *pdst;
   int            i;
   int            j;
   
   HQASSERT(transform->nProfiles > 0, "No Profiles selected in transform");
   
   nInputChannels  = transform->pProfileArray[0].nInputChannels;
   nOutputChannels = transform->pProfileArray[transform->nProfiles - 1].nOutputChannels;
   HQASSERT(nInputChannels <= kCMYKChannelCount, "No of Input channels exceeds buffer size");
   HQASSERT(nOutputChannels <= kCMYKChannelCount, "No of Input channels exceeds buffer size");
   
   for (i = 0; i < num_pixels; i++)
   {
       for (j = 0; j < nInputChannels; j++)
          src[j] = COLOR_FLT_8BIT(input_data[j]);
       
       psrc = src;
       pdst = dst;
       for (j = 0; j < transform->nProfiles; j++)
       {
          if (transform->pProfileArray[j].prf_pTransformFn)
          {
             transform->pProfileArray[j].prf_pTransformFn(cmm, transform, src, dst);
             if (j != (transform->nProfiles - 1))
             {
                 psrc = dst;
                 pdst = src;
             }
         }
       }
       for (j = 0; j < nOutputChannels; j++)
          output_data[j] = COLOR_8BIT_FLT(pdst[j]);
   }
   return SW_CMM_SUCCESS;
}

/**
 * @brief  Use the specified transform to adjust color data.
 *
 * The RIP will place color data in memory beginning at input_data. This
 * function should converts the data using the transform and places the
 * output values in memory beginning at output_data.
 *
 * @param[in]  instance      The alternate CMM instance.
 * @param[in]  transform     The transform to use for color conversions.
 * @param[in]  input_data    RIP-allocated array of input color values.
 * @param[out]  output_data  RIP-allocated array to fill with output color values.
 * @param[in]  num_pixels    Number of color values to transform.
 * @return <code>TRUE</code> on success, <code>FALSE</code> otherwise.
 *
 * @see ccs_open_transform(), ccs_close_transform()
 */
static sw_cmm_result RIPCALL ccs_invoke_transform(sw_cmm_instance *instance,
                                                  sw_cmm_transform transform,
                                                  float* input_data,
                                                  float* output_data,
                                                  uint32 num_pixels)
{
  uint32 i;
  CMM_TRANSFORM* pTransform = (CMM_TRANSFORM*) transform;
  uint32 nPixelInIndex;
  uint32 nPixelOutIndex;

  HQASSERT(instance, "No CMM instance") ;
  HQASSERT(pTransform != NULL, "No CMM transform");
  HQASSERT(input_data != NULL, "No input data");
  HQASSERT(output_data != NULL, "No output data");

  UNUSED_PARAM(sw_cmm_instance *, instance);
  
  if (pTransform->trf_pTransformFn != NULL)
  {
    return pTransform->trf_pTransformFn(instance,
                                        pTransform,
                                        input_data,
                                        output_data,
                                        num_pixels);
  }
  /* Call the Shared Memory function */
  setColorProfile();
  setColorMode();
  setGrayReproduction();
  int id = getModeID();
  if( id < 0 )
  {
	 return -1;
  }
    
  pBgucr      = (di_bgucrinfo_t *) devinfo->bgucr_info + id;
  pWishgcr    = (di_gcrinfo_t *) devinfo->gcr_info + id;
  pGcrhgr     = (di_gcrinfo_t *) devinfo->gcrhgr_info + id;
  pDropinfo   = (di_dropinfo_t*) devinfo->drop_info;
  ppucSrcGam  = devinfo->gamma_info + (id * GPS_CLR_PLANE);
  tlimit =    (di_tlimitinfo_t  *)devinfo->tlimit_val;

  ColorData   = getColorData( cmm, pDropinfo, tlimit, pBgucr, pWishgcr, pGcrhgr, cmmProfile );
    
  /* Call array of CMYKColorMappingFunc values for each pixel */
  nPixelInIndex = 0;
  nPixelOutIndex = 0;
  for (i = 0; i < num_pixels; i ++)
  {
    uint32 nMappingFunc;
    float cmykOrRGBValue[kCMYKChannelCount];
    uint32 nInputChannels;
    uint32 nOutputChannels;

    /* Store input value */
    nInputChannels = pTransform->pProfileArray[0].nInputChannels;
    nOutputChannels = pTransform->pProfileArray[pTransform->nProfiles - 1].nOutputChannels;
    memcpy(cmykOrRGBValue, &input_data[nPixelInIndex], sizeof(float) * nInputChannels);


   /* Apply transform */
   for (nMappingFunc = 0; nMappingFunc < pTransform->nProfiles; nMappingFunc ++)
   {
	 if (pTransform->pProfileArray[nMappingFunc].pMappingFunc)
	   pTransform->pProfileArray[nMappingFunc].pMappingFunc(cmykOrRGBValue);
   }

   /* Store result */
   memcpy(&output_data[nPixelOutIndex], cmykOrRGBValue, sizeof(float) * nOutputChannels);

   nPixelInIndex += nInputChannels;
   nPixelOutIndex += nOutputChannels;
  }

  return SW_CMM_SUCCESS;
}

