///////////////////////////////////////////////////////////////////////////////
// File Name    :OIl_Color.cpp
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "assert.h"
//#include "types.h"
#include "config.h"
//#include "PageRenderer.h"
#include "cl_color_prv.h"
#include "cl_color.h"
#include "types.h"
/*#ifdef PR3_SUPPORT_GIPA1
#include "GIPAOrder.h"
#endif*/

/* CMM */
//#include "cl_cmm_prv.h"
#include "colormatching.h"
long m_lIsCmm = 0;
#define DEBUGCMM
#define DEBUG_SETCOLOR

//todo
#define GAMMA_THROUGH


#ifdef __cplusplus
extern "C" {
#endif
extern long CMM_Init(long (*)(), void (*)(), void *, unsigned long);
extern long CMM_End(long);
extern long CMM_OpenProfile(long, unsigned char, char *, unsigned long);
extern long CMM_CloseProfile(long, unsigned long);

extern long CMM_DoConversion4_plane(long, unsigned char *, unsigned
	char *, unsigned char *, unsigned char *, unsigned char *,
	unsigned char *, unsigned long, unsigned long);
extern long CMM_DoConversion4_plane_cmyk(long, unsigned char *,
	unsigned char *, unsigned char *, unsigned char *, unsigned char *,
	unsigned char *, unsigned char *, unsigned long, unsigned long);
extern long CMM_DoConversion4_padding(long, unsigned long *, unsigned
	long *, unsigned long, unsigned long);
extern long CMM_DoConversion4_padding_kcmy(long, unsigned long *,
	unsigned long *, unsigned long, unsigned long);
/* CMM : Commented out since these functions have not been used
extern long CMM_DoConversion4_cmy(long, void *, void *, unsigned long,
	unsigned long, char, char);
extern long CMM_DoConversion4_rgbcmy(long, unsigned char *, unsigned
	char *, unsigned long, unsigned long);
extern long CMM_DoConversion3_bgr(long, unsigned char *, unsigned char
	*, unsigned long, unsigned long);
extern long CMM_DoConversion4_bgr(long, unsigned char *, unsigned char
	*, unsigned long, unsigned long);
extern long CMM_DoConversion4_rgb(long, void *, void *, unsigned long,
	unsigned long, char, char);
extern long CMM_DoConversion4_rgb_1(long, void *, void *, unsigned
	long, unsigned long, char, char);*/

/* CMM Code to set the parameters*/
void* getColorData( unsigned long pCmm, 
                    di_dropinfo_t* pDropInfo, 
                    di_tlimitinfo_t  *limit,
                    di_bgucrinfo_t* bgi_ptr,
                    di_gcrinfo_t* wishgcr, 
                    di_gcrinfo_t* gcrhgr_ptr, 
                    unsigned long cmmProfile )
{
      static CPRColor oColorData;
      oColorData.m_sPqLimit.text = limit->text;
      oColorData.m_sPqLimit.line = limit->line;
      oColorData.m_sPqLimit.phot = limit->phot;
      oColorData.m_sPqLimit.fill = limit->fill;

      /* Setting the CMM pointer */
      oColorData.m_lIsCmm = 0;
      if( pCmm )
      {
	        oColorData.m_lIsCmm = pCmm;
	        m_lIsCmm = pCmm;
	  }

	  /* Setting the Wishgcr and Hgr data */
	  oColorData.m_nIsGcr = FALSE;
	  if(wishgcr)
	  {
	      oColorData.m_nIsGcr    = wishgcr->flag;
	      if( oColorData.m_nIsGcr )
	      {
			    // settings of WiShGCR information of PR
			    oColorData.m_sGcrInfo.CB.bg  = wishgcr->CB_bg;
			    oColorData.m_sGcrInfo.CB.ucr = wishgcr->CB_ucr;
			    oColorData.m_sGcrInfo.CG.bg  = wishgcr->CG_bg;
			    oColorData.m_sGcrInfo.CG.ucr = wishgcr->CG_ucr;
			    oColorData.m_sGcrInfo.YG.bg  = wishgcr->YG_bg;
			    oColorData.m_sGcrInfo.YG.ucr = wishgcr->YG_ucr;
			    oColorData.m_sGcrInfo.MB.bg  = wishgcr->MB_bg;
			    oColorData.m_sGcrInfo.MB.ucr = wishgcr->MB_ucr;
			    oColorData.m_sGcrInfo.MR.bg  = wishgcr->MR_bg;
			    oColorData.m_sGcrInfo.MR.ucr = wishgcr->MR_ucr;
			    oColorData.m_sGcrInfo.YR.bg  = wishgcr->YR_bg;
			    oColorData.m_sGcrInfo.YR.ucr = wishgcr->YR_ucr;

			    if ((gcrhgr_ptr != NULL) && (gcrhgr_ptr->flag)) 
	            {
				    oColorData.m_sGcrHgrInfo.CB.bg  = gcrhgr_ptr->CB_bg;
				    oColorData.m_sGcrHgrInfo.CB.ucr = gcrhgr_ptr->CB_ucr;
				    oColorData.m_sGcrHgrInfo.CG.bg  = gcrhgr_ptr->CG_bg;
				    oColorData.m_sGcrHgrInfo.CG.ucr = gcrhgr_ptr->CG_ucr;
				    oColorData.m_sGcrHgrInfo.YG.bg  = gcrhgr_ptr->YG_bg;
				    oColorData.m_sGcrHgrInfo.YG.ucr = gcrhgr_ptr->YG_ucr;
				    oColorData.m_sGcrHgrInfo.MB.bg  = gcrhgr_ptr->MB_bg;
				    oColorData.m_sGcrHgrInfo.MB.ucr = gcrhgr_ptr->MB_ucr;
				    oColorData.m_sGcrHgrInfo.MR.bg  = gcrhgr_ptr->MR_bg;
				    oColorData.m_sGcrHgrInfo.MR.ucr = gcrhgr_ptr->MR_ucr;
				    oColorData.m_sGcrHgrInfo.YR.bg  = gcrhgr_ptr->YR_bg;
				    oColorData.m_sGcrHgrInfo.YR.ucr = gcrhgr_ptr->YR_ucr;
		        } 
		        else 
		        {
				    oColorData.m_sGcrHgrInfo.CB.bg  = wishgcr->CB_bg;
				    oColorData.m_sGcrHgrInfo.CB.ucr = wishgcr->CB_ucr;
				    oColorData.m_sGcrHgrInfo.CG.bg  = wishgcr->CG_bg;
				    oColorData.m_sGcrHgrInfo.CG.ucr = wishgcr->CG_ucr;
				    oColorData.m_sGcrHgrInfo.YG.bg  = wishgcr->YG_bg;
				    oColorData.m_sGcrHgrInfo.YG.ucr = wishgcr->YG_ucr;
				    oColorData.m_sGcrHgrInfo.MB.bg  = wishgcr->MB_bg;
				    oColorData.m_sGcrHgrInfo.MB.ucr = wishgcr->MB_ucr;
				    oColorData.m_sGcrHgrInfo.MR.bg  = wishgcr->MR_bg;
				    oColorData.m_sGcrHgrInfo.MR.ucr = wishgcr->MR_ucr;
				    oColorData.m_sGcrHgrInfo.YR.bg  = wishgcr->YR_bg;
				    oColorData.m_sGcrHgrInfo.YR.ucr = wishgcr->YR_ucr;
		        }
	      }
	  }
	  else /* IF WISHGCR DATA IS NOT PRESENT */
	  {
	      /* Setting the BG/UCR Data */
#ifdef SUPPORT_COMPOSITEBLACK
		  oColorData.UpdateLutExt( bgi_ptr->bg, bgi_ptr->ucr, BGUCR_NORMAL);
		  oColorData.UpdateLutExt( bgi_ptr->bg_compbk, bgi_ptr->ucr_compbk,
				                   BGUCR_COMPBK);
#else
	      oColorData.UpdateLut(bgi_ptr->bg, bgi_ptr->ucr,
				               bgi_ptr->bg_hgr, bgi_ptr->ucr_hgr);
#endif
	  }

      /* Setting the Drop Info Tables */
      oColorData.m_nIsPqtc = FALSE;
	  if(pDropInfo)
	  {
	    if(pDropInfo->lit && pDropInfo->inv)
	    {
	        oColorData.m_nIsPqtc   = TRUE;
	        oColorData.m_pucPqTbl  = pDropInfo->lit;
	        oColorData.m_pucRPqTbl = pDropInfo->inv;
	    }
	  }

      /* Set Profile for RGB*/
	  oColorData.m_ulCmmProfiles[0] = cmmProfile;
	  oColorData.m_ulCmmProfiles[1] = cmmProfile;
	  oColorData.m_ulCmmProfiles[2] = cmmProfile;
	  oColorData.m_ulCmmProfiles[3] = 0;
	  
	  oColorData.SetTransgcr();
      return ((void*)&oColorData);
} 
/* Set the Profile Data and call the Color Conversion function */
void setRGB( void* pCPRColor, unsigned long ulFlag,
			 int nGrayMode, unsigned char **ppucGamma, int nObjMode,
			 int ucSpoolColor, unsigned char* pucPtr, int nOutputChannels)
{
    CPRColor* cur_data = (CPRColor*)pCPRColor;
    TRANS_FN_TYPE transfunc;
    TRANS_FN_TYPE_1 transfunc1;

    if( ucSpoolColor )
    {
	    transfunc = cur_data->SetTransrgb( ulFlag, nGrayMode );
	}
	else
	{
	    transfunc1 = cur_data->SetTransgray( ulFlag, nGrayMode );
	    transfunc  = (TRANS_FN_TYPE)transfunc1;
	}

	cur_data->TransrgbDirect (ulFlag, 1/* SIZE IS ONE BYTE */,
	                          pucPtr, NULL, 1, &cur_data->m_sPqLimit, 
	                          transfunc, ppucGamma, nObjMode, ucSpoolColor);
}

int
SetcolorGG(unsigned long ulVectorGray,unsigned long ulGrayJudgeMode, unsigned char ucColorMode,
	int	toner_limit, unsigned char ucDither,di_tlimitinfo_t usLimit,
	unsigned long ulFlag,void* pCPRColor,
	unsigned char* pucPtr,
	unsigned char* pucoutPtr,
	int nObjMode,
	int nObjectType,
	unsigned char **ppucSrcGam,
	di_tlimitinfo_t  *tlimit)
{
	unsigned char *pucFGPointer=0, *pucBGPointer=0;
	int nSetSecond = FALSE;
	clr_tlimit_t pLimit;
	unsigned char **ppucGamma=0;
	CPRColor* cur_color = (CPRColor*) pCPRColor;
	unsigned char ucDitherMode;
	int nOrigObjMode = nObjMode;
	bool bFlag = false;

	/*
	 * OBJ_IMAG_{COLOR, MONO}窶堙�	 * GRAYﾆ停��ｽ[ﾆ檀窶堙娯�ﾂｻ窶凖ｨﾋ�闇�窶堙��ﾃ弘BJ_IMAG窶堙俄�u窶堋ｫﾅ�ｷ窶堋ｦ窶堙ｩ�ｽB
	 */
	if ((nOrigObjMode & OBJ_MASK_1ST) == OBJ_IMAG_COLOR ||
		(nOrigObjMode & OBJ_MASK_1ST) == OBJ_IMAG_MONO)
	{
		nObjMode = PR_OBJ_IMAG;
	}

	/* ﾆ棚ﾆ置ﾆ淡ﾆ巽ﾆ誰ﾆ暖ﾅｽﾃｭ窶氾樞�ﾋ��ﾃ姑断ﾆ達ﾆ旦ﾅｽﾃｭ窶氾樞�ﾃｰﾅｽﾃｦ窶慊ｾ */
	switch (nObjMode & PR_OBJ_MASK)
	{
		case PR_OBJ_IMAG:
			ucDitherMode = DIT_IMAG_MODE (ucDither);
			break;
		case PR_OBJ_GRAP:
			ucDitherMode = DIT_GRAP_MODE (ucDither);
			break;
		case PR_OBJ_TEXT:
			ucDitherMode = DIT_TEXT_MODE (ucDither);
			break;
		case PR_OBJ_LINE:
			ucDitherMode = DIT_LINE_MODE (ucDither);
			break;
		default:;
			return PR_ERROR;
	}
	pLimit.text = tlimit->text;
	pLimit.line = tlimit->line;
	pLimit.phot = tlimit->phot;
	pLimit.fill = tlimit->fill;

	//todo
	pucFGPointer = pucPtr;
	pucBGPointer = 0;

	do
	{
		//Check the number of color plane calculation - todo
		ppucGamma = ppucGamma;
		if (cur_color->m_nIsPqtc)
		{
//			// todo
//			if (ucDitherMode == DIT_PHOT)
//			{
//				cur_color->m_sPqLimit = cur_color->m_sPqLimitPhot;
//				cur_color->m_pucPqTbl = cur_color->m_pucPqTblPhot;
//				cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblPhot;
//			}
//			else if (ucDitherMode == DIT_GRAP)
//			{
//				cur_color->m_sPqLimit = cur_color->m_sPqLimitGrap;
//				cur_color->m_pucPqTbl = cur_color->m_pucPqTblGrap;
//				cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblGrap;
//			}
//			else
//			{;
//				assert (ucDitherMode == DIT_TEXT);
//				cur_color->m_sPqLimit = cur_color->m_sPqLimitText;
//				cur_color->m_pucPqTbl = cur_color->m_pucPqTblText;
//				cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblText;
//			}
		}

		cur_color->SetColorGinfColorMask(ulVectorGray,ulGrayJudgeMode, ucColorMode,toner_limit,ulFlag,
					nObjMode, pucFGPointer, pucBGPointer, ppucGamma,
					nOrigObjMode, &pLimit);
#ifdef DEBUG_SETCOLOR
		printf ("KCMY=(%d,%d,%d,%d) ", pucFGPointer[0], pucFGPointer[1],
			pucFGPointer[2], pucFGPointer[3]);
#endif
		/* ﾆ丹ﾆ停�ﾆ断�ｽ[ﾆ歎ﾆ停�ﾆ停�窶堙�Used_plane 窶堙ｰ�ｽﾃ昶�ﾃｨ窶堋ｷ窶堙ｩ       */
		/* ﾆ丹ﾆ停�ﾆ断�ｽ[ﾆ歎ﾆ停�ﾆ停�ﾅｽw窶凖ｨ(ﾆ丹ﾆ停�ﾆ断�ｽ[ﾆ歎ﾆ停�ﾆ停�ﾆ稚ﾆ停�ﾆ丹ON 窶堋ｩ窶堙�窶佚ｦ2FG/BG窶堙��ﾃ坂�ﾃ遺�ﾂ｢) */
		if ((ulFlag & COLOR_GRADATION) &&
			(nSetSecond == FALSE))
		{
			//todo related to BG/FG mode
//			if (prh->m_objColor.SetcolorGinfColorGradation(prh,
//				ginf, &pLimit, nObjMode) == PR_ERROR)
//			{
//				return PR_ERROR;
//			}
		}
//todo
//		if (bUseColBrush && (nSetSecond == FALSE))
//		{
//			Used_plane |= nBrushUsedPlane;
//		}
//		else
//		{
//			Used_plane |= *(int *) pucFGPointer;
//		}
		bFlag = false;
		if ((ulFlag & COLOR_2NDFGBG) && (nSetSecond
				== FALSE))
		{
			/*
			 * 窶佚ｦ2 FG/BG 窶堋ｪ窶堋��ﾃｩ窶堙娯�ﾃ��ﾂｻ窶堙ｪ窶堙鯉ｿｽF窶｢ﾃ焦�ｷ窶堙ｰ�ｽs窶堋､�ｽB
			 */
			pucFGPointer = pucPtr;
			//pucBGPointer =  0;
			nSetSecond = TRUE;
			bFlag = true;
			/* 窶佚ｦ2 FG/BG 窶堙俄�ﾂｮ�ｽﾂｫﾅｽw窶凖ｨ窶堋ｪ窶堋��ﾃｩ窶堋ｩﾆ蛋ﾆ巽ﾆ鍛ﾆ誰  */
			if ((nOrigObjMode & OBJ_MASK_2ND) !=
				OBJ_DEF_2ND)
			{
				switch (nOrigObjMode &
					OBJ_MASK_2ND)
				{
					case OBJ_IMAG_2ND:
						nObjMode = OBJ_IMAG;
						break;
					case OBJ_GRAP_2ND:
						nObjMode = OBJ_GRAP;
						break;
					case OBJ_TEXT_2ND:
						nObjMode = OBJ_TEXT;
						break;
					case OBJ_LINE_2ND:
						nObjMode = OBJ_LINE;
						break;
					case OBJ_IMAG_COLOR_2ND:
						nObjMode = OBJ_IMAG;
						/* gray mode窶堙戸�冷�ﾃ会ｿｽﾃ昶�ﾃｨ窶堋ｵ窶堙��ﾂｨ窶堋ｭ */
						nOrigObjMode =
							OBJ_IMAG_COLOR;
						break;
					case OBJ_IMAG_MONO_2ND:
						nObjMode = OBJ_IMAG;
						/* gray mode窶堙戸�冷�ﾃ会ｿｽﾃ昶�ﾃｨ窶堋ｵ窶堙��ﾂｨ窶堋ｭ */
						nOrigObjMode =
							OBJ_IMAG_MONO;
						break;
					default:;
						assert (0);
						break;
				}
			}

		}
	} while (bFlag);
	return PR_OK;
}

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
//Function      :SetTonerLimitInColor
//Description   :
//Arguments     :
//              :int nObjectKind:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//Return value  :int:nVal
///////////////////////////////////////////////////////////////////////////////
int
CPRColor::SetTonerLimitInColor (int nObjectKind,
				clr_tlimit_t * pLimit)
{
	int nVal = 0;

	if (m_nIsPqtc)
	{;
		assert (m_pucPqTbl);;
		assert (m_pucRPqTbl);;
		assert (m_sPqLimit.phot);;
		assert (m_sPqLimit.fill);;
		assert (m_sPqLimit.text);;
		assert (m_sPqLimit.line);

		switch (nObjectKind)
		{
			case CR_OBJ_IMAG:
				nVal = m_sPqLimit.phot;
				break;
			case CR_OBJ_GRAP:
				nVal = m_sPqLimit.fill;
				break;
			case CR_OBJ_TEXT:
				nVal = m_sPqLimit.text;
				break;
			case CR_OBJ_LINE:
				nVal = m_sPqLimit.line;
				break;
			default:;
				assert (0);
				break;
		}
	}
	else
	{
		switch (nObjectKind)
		{
			case CR_OBJ_IMAG:
				nVal = pLimit->phot;
				break;
			case CR_OBJ_GRAP:
				nVal = pLimit->fill;
				break;
			case CR_OBJ_TEXT:
				nVal = pLimit->text;
				break;
			case CR_OBJ_LINE:
				nVal = pLimit->line;
				break;
			default:;
				assert (0);
				break;
		}
	}
	return nVal;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :MakeLut
//Description   :Make Look Up Table
//Arguments     :
//              :float nBGSP:[IN]
//              :float nBGSL:[IN]
//              :float nUCRP:[IN]
//              :float nUCRSl:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
void 
CPRColor::MakeLut (float nBGSP,
	float nBGSL,
	float nUCRP,
	float nUCRSl)
{
	int nI = 0;
	int nSL = 0;
	

	nSL = (int)(MAX_LUT * nBGSP);;
	assert (nSL >= 0 && nSL < SIZEOF_LUT);
	for (nI = 0; nI < SIZEOF_LUT; nI++)
	{
		if (nI <= nSL)
			m_ucBgLut[nI] = 0;
		else
			m_ucBgLut[nI] = (uchar) ((nI - nSL) * nBGSL);
	}

	m_ucBgLut[255] = 255;	// for ROP
	nSL = (int)(MAX_LUT * nUCRP);;
	assert (nSL >= 0 && nSL < SIZEOF_LUT);
	for (nI = 0; nI < SIZEOF_LUT; nI++)
	{
		if (nI <= nSL)
			m_ucUcrLut[nI] = 0;
		else
			m_ucUcrLut[nI] = (uchar)((nI - nSL) * nUCRSl);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :UpdateLut 
//Description   :Update Look up table
//Arguments     :
//              :unsigned char *pucBG:[IN]
//              :unsigned char *pucUCR:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
void CPRColor::
UpdateLut (
	unsigned char *pucBG,
	unsigned char *pucUCR,
	unsigned char *pucBGHGR,
	unsigned char *pucUCRHGR)
{
	

	// copy to BGtbl
	memcpy (m_ucBgLut, pucBG, SIZEOF_LUT);

	// copy to UCRtbl
	memcpy (m_ucUcrLut, pucUCR, SIZEOF_LUT);

	if ((pucBGHGR != 0) && (pucUCRHGR != 0))
	{
		memcpy (m_ucBgHgrLut, pucBGHGR, SIZEOF_LUT);
		memcpy (m_ucUcrHgrLut, pucUCRHGR, SIZEOF_LUT);
	}
	else
	{
		memcpy (m_ucBgHgrLut, pucBG, SIZEOF_LUT);
		memcpy (m_ucUcrHgrLut, pucUCR, SIZEOF_LUT);
	}
}

#ifdef SUPPORT_COMPOSITEBLACK
///////////////////////////////////////////////////////////////////////////////
//Function      :UpdateLutExt 
//Description   :Update Look up table 
//Arguments     :
//              :unsigned char *pucBG:[IN]
//              :unsigned char *pucUCR:[IN]
//              :int nType[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
void CPRColor::
UpdateLutExt (
	unsigned char *pucBG,
	unsigned char *pucUCR,
	int nType)
{
	if ((pucBG != 0) && (pucUCR != 0))
	{
		if (nType == CR_BGUCR_NORMAL)
		{
			m_ulBgucrTblFlag |= CR_BGUCR_TABLE_NORMAL;
			memcpy (m_ucBgLut, pucBG, SIZEOF_LUT);
			memcpy (m_ucUcrLut, pucUCR, SIZEOF_LUT);
		}
		else if (nType == CR_BGUCR_COMPBK)
		{
			m_ulBgucrTblFlag |= CR_BGUCR_TABLE_COMPBK;
			memcpy (m_ucBgLutCompbk, pucBG, SIZEOF_LUT);
			memcpy (m_ucUcrLutCompbk, pucUCR, SIZEOF_LUT);
		}
		else
		{
			assert(0);
		}
	}	
}
#endif

///////////////////////////////////////////////////////////////////////////////
//Function      :TransBgucr
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :int nC:[IN]
//              :int nM:[IN]
//              :int nY:[IN]
//              :unsigned char ucKCMY[]:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucr(
	CPRColor* pobjColor,
	int nC,
	int nM,
	int nY,
	unsigned char ucKCMY[])
{
	int nMinColor;
	int nUCR;

	nMinColor = nC;
	if (nM < nMinColor)
		nMinColor = nM;
	if (nY < nMinColor)
		nMinColor = nY;

	ucKCMY[0] = pobjColor->m_ucBgLut[nMinColor];
	nUCR = (int)pobjColor->m_ucUcrLut[nMinColor];
	ucKCMY[1] = (unsigned char)(nC - nUCR);
	ucKCMY[2] = (unsigned char)(nM - nUCR);
	ucKCMY[3] = (unsigned char)(nY - nUCR);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransBgucrHgr
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :int nC:[IN]
//              :int nM:[IN]
//              :int nY:[IN]
//              :unsigned char ucKCMY[]:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucrHgr(
	CPRColor* pobjColor,
	int nC,
	int nM,
	int nY,
	unsigned char ucKCMY[])
{
	int nMinColor;
	int nUCR;

	nMinColor = nC;
	if (nM < nMinColor)
		nMinColor = nM;
	if (nY < nMinColor)
		nMinColor = nY;

	ucKCMY[0] = pobjColor->m_ucBgHgrLut[nMinColor];
	nUCR = (int)pobjColor->m_ucUcrHgrLut[nMinColor];
	ucKCMY[1] = (unsigned char)(nC - nUCR);
	ucKCMY[2] = (unsigned char)(nM - nUCR);
	ucKCMY[3] = (unsigned char)(nY - nUCR);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransLimit
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransLimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK, nC, nM, nY;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	int nSumCMYK;
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		nK = (int)pucGtK[*pucK];
		nC = (int)pucGtC[*pucC];
		nM = (int)pucGtM[*pucM];
		nY = (int)pucGtY[*pucY];

		nSumCMYK = nK + nC + nM + nY;
		if (nSumCMYK > nTonerLimit)
		{
			TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
		}
		*pucK = (unsigned char)nK;
		*pucC = (unsigned char)nC;
		*pucM = (unsigned char)nM;
		*pucY = (unsigned char)nY;
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransPQlimit
//Description   : USER GAMMA -> PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransPQlimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK, nC, nM, nY;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	unsigned char *pucUserGtK = ppucGamma[4];
	unsigned char *pucUserGtC = ppucGamma[5];
	unsigned char *pucUserGtM = ppucGamma[6];
	unsigned char *pucUserGtY = ppucGamma[7];
	int nSumCMYK;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;
	
	assert(pucGtK && pucGtC && pucGtM && pucGtY);
	
	pobjColor->ApplyUserGammas(pucUserGtK, nSize, pucK);
	pobjColor->ApplyUserGammas(pucUserGtC, nSize, pucC);
	pobjColor->ApplyUserGammas(pucUserGtM, nSize, pucM);
	pobjColor->ApplyUserGammas(pucUserGtY, nSize, pucY);
	
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		nK = (int)pucPQTable[*pucK];
		nC = (int)pucPQTable[*pucC];
		nM = (int)pucPQTable[*pucM];
		nY = (int)pucPQTable[*pucY];

		nSumCMYK = nK + nC + nM + nY;
		if (nSumCMYK > nTonerLimit)
		{
#ifdef SUPPORT_LIMITING_K
			if (nTonerLimit > nK) {
				TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
				*pucK = pucGtK[*pucK];
				*pucC = pucGtC[pucRPQTable[nC]];
				*pucM = pucGtM[pucRPQTable[nM]];
				*pucY = pucGtY[pucRPQTable[nY]];
			}
			else
			{
				*pucK = pucGtK[pucRPQTable[nTonerLimit]];
				*pucC = *pucM = *pucY = 0;
			}
#else
			TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
			*pucK = pucGtK[*pucK];
			*pucC = pucGtC[pucRPQTable[nC]];
			*pucM = pucGtM[pucRPQTable[nM]];
			*pucY = pucGtY[pucRPQTable[nY]];
#endif
		}
		else
		{
			*pucK = pucGtK[*pucK];
			*pucC = pucGtC[*pucC];
			*pucM = pucGtM[*pucM];
			*pucY = pucGtY[*pucY];
		}
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransBgucrLimit
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucrLimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK, nC, nM, nY, nMinColor;
	int nUCR;

    unsigned char *pucGtK = (unsigned char*)ppucGamma[0];
	unsigned char *pucGtC = (unsigned char*)ppucGamma[1];
	unsigned char *pucGtM = (unsigned char*)ppucGamma[2];
	unsigned char *pucGtY = (unsigned char*)ppucGamma[3];
	int nSumCMYK;
	unsigned char *UCRtbl = pobjColor->m_ucUcrLut;
	unsigned char *BGtbl  = pobjColor->m_ucBgLut;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);

	nMinColor = nC = (int)*pucC;
	nM = (int)*pucM;
	if (nM < nMinColor)
		nMinColor = nM;
	nY = (int)*pucY;
	if (nY < nMinColor)
		nMinColor = nY;

	nUCR = (int)UCRtbl[nMinColor];

	nK = (int)pucGtK[BGtbl[nMinColor]];
	nC = (int)pucGtC[nC - nUCR];
	nM = (int)pucGtM[nM - nUCR];
	nY = (int)pucGtY[nY - nUCR];

	nSumCMYK = nK + nC + nM + nY;
	if (nSumCMYK > nTonerLimit)
	{
		TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
	}
	*pucK = (unsigned char)nK;
	*pucC = (unsigned char)nC;
	*pucM = (unsigned char)nM;
	*pucY = (unsigned char)nY;
	return;
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransBgucrHgrLimit
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucrHgrLimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK, nC, nM, nY, nMinColor;
	int nUCR;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	int nSumCMYK;
	unsigned char *UCRtbl = pobjColor->m_ucUcrHgrLut;
	unsigned char *BGtbl = pobjColor->m_ucBgHgrLut;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);

	nMinColor = nC = (int)*pucC;
	nM = (int)*pucM;
	if (nM < nMinColor)
		nMinColor = nM;
	nY = (int)*pucY;
	if (nY < nMinColor)
		nMinColor = nY;

	nUCR = (int)UCRtbl[nMinColor];

	nK = (int)pucGtK[BGtbl[nMinColor]];
	nC = (int)pucGtC[nC - nUCR];
	nM = (int)pucGtM[nM - nUCR];
	nY = (int)pucGtY[nY - nUCR];

	nSumCMYK = nK + nC + nM + nY;
	if (nSumCMYK > nTonerLimit)
	{
		TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
	}
	*pucK = (unsigned char)nK;
	*pucC = (unsigned char)nC;
	*pucM = (unsigned char)nM;
	*pucY = (unsigned char)nY;
	return;
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransBgucrPQlimit
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma)	:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucrPQlimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK, nC, nM, nY, nMinColor;
	int nUCR;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	int nSumCMYK;
	unsigned char *UCRtbl = pobjColor->m_ucUcrLut;
	unsigned char *BGtbl = pobjColor->m_ucBgLut;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);


	nMinColor = nC = (int)*pucC;
	nM = (int)*pucM;
	if (nM < nMinColor)
		nMinColor = nM;
	nY = (int)*pucY;
	if (nY < nMinColor)
		nMinColor = nY;

	nUCR = (int)UCRtbl[nMinColor];

	nK = (int)pucPQTable[*pucK = BGtbl[nMinColor]];
	nC = (int)pucPQTable[*pucC = nC - nUCR];
	nM = (int)pucPQTable[*pucM = nM - nUCR];
	nY = (int)pucPQTable[*pucY = nY - nUCR];

	nSumCMYK = nK + nC + nM + nY;
	if (nSumCMYK > nTonerLimit)
	{
#ifdef SUPPORT_LIMITING_K
		if (nTonerLimit > nK) {
			TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
			*pucK = pucGtK[*pucK];
			*pucC = pucGtC[pucRPQTable[nC]];
			*pucM = pucGtM[pucRPQTable[nM]];
			*pucY = pucGtY[pucRPQTable[nY]];
		}
		else
		{
			*pucK = pucGtK[pucRPQTable[nTonerLimit]];
			*pucC = *pucM = *pucY = 0;
		}
#else
		TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
		*pucK = pucGtK[*pucK];
		*pucC = pucGtC[pucRPQTable[nC]];
		*pucM = pucGtM[pucRPQTable[nM]];
		*pucY = pucGtY[pucRPQTable[nY]];
#endif
	}
	else
	{
		*pucK = pucGtK[*pucK];
		*pucC = pucGtC[*pucC];
		*pucM = pucGtM[*pucM];
		*pucY = pucGtY[*pucY];
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransBgucrHgrPQlimit
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma)	:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucrHgrPQlimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK, nC, nM, nY, nMinColor;
	int nUCR;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	int nSumCMYK;
	unsigned char *UCRtbl = pobjColor->m_ucUcrHgrLut;
	unsigned char *BGtbl = pobjColor->m_ucBgHgrLut;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);


	nMinColor = nC = (int)*pucC;
	nM = (int)*pucM;
	if (nM < nMinColor)
		nMinColor = nM;
	nY = (int)*pucY;
	if (nY < nMinColor)
		nMinColor = nY;

	nUCR = (int)UCRtbl[nMinColor];

	nK = (int)pucPQTable[*pucK = BGtbl[nMinColor]];
	nC = (int)pucPQTable[*pucC = nC - nUCR];
	nM = (int)pucPQTable[*pucM = nM - nUCR];
	nY = (int)pucPQTable[*pucY = nY - nUCR];

	nSumCMYK = nK + nC + nM + nY;
	if (nSumCMYK > nTonerLimit)
	{
#ifdef SUPPORT_LIMITING_K
		if (nTonerLimit > nK) {
			TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
			*pucK = pucGtK[*pucK];
			*pucC = pucGtC[pucRPQTable[nC]];
			*pucM = pucGtM[pucRPQTable[nM]];
			*pucY = pucGtY[pucRPQTable[nY]];
		}
		else
		{
			*pucK = pucGtK[pucRPQTable[nTonerLimit]];
			*pucC = *pucM = *pucY = 0;
		}
#else
		TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
		*pucK = pucGtK[*pucK];
		*pucC = pucGtC[pucRPQTable[nC]];
		*pucM = pucGtM[pucRPQTable[nM]];
		*pucY = pucGtY[pucRPQTable[nY]];
#endif
	}
	else
	{
		*pucK = pucGtK[*pucK];
		*pucC = pucGtC[*pucC];
		*pucM = pucGtM[*pucM];
		*pucY = pucGtY[*pucY];
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransGcrPQlimit
//Description   : BG/UCR(WishGCR) -> USER GAMMA -> PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransGcrPQlimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK;
	int nC = (int)*pucC;
	int nM = (int)*pucM;
	int nY = (int)*pucY;
	int nKp, nCp, nMp, nYp;
	unsigned char ucK, ucC, ucM, ucY;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	unsigned char *pucUserGtK = ppucGamma[4];
	unsigned char *pucUserGtC = ppucGamma[5];
	unsigned char *pucUserGtM = ppucGamma[6];
	unsigned char *pucUserGtY = ppucGamma[7];
	int nSumCMYK;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;
	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&pobjColor->m_sGcrInfo;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);

	WiShGCR(m_sGcrInfo, nC, nM, nY, nK);
	
	ucK = nK;
	ucC = nC;
	ucM = nM;
	ucY = nY;
	pobjColor->ApplyUserGammas(pucUserGtK, 1, &ucK);
	pobjColor->ApplyUserGammas(pucUserGtC, 1, &ucC);
	pobjColor->ApplyUserGammas(pucUserGtM, 1, &ucM);
	pobjColor->ApplyUserGammas(pucUserGtY, 1, &ucY);
	
	nKp = (int)pucPQTable[ucK];
	nCp = (int)pucPQTable[ucC];
	nMp = (int)pucPQTable[ucM];
	nYp = (int)pucPQTable[ucY];

	nSumCMYK = nKp + nCp + nMp + nYp;
	if (nSumCMYK > nTonerLimit)
	{
#ifdef SUPPORT_LIMITING_K
		if (nTonerLimit > nKp) {
			TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp, nYp);
			*pucK = pucGtK[ucK];
			*pucC = pucGtC[pucRPQTable[nCp]];
			*pucM = pucGtM[pucRPQTable[nMp]];
			*pucY = pucGtY[pucRPQTable[nYp]];
		}
		else
		{
			*pucK = pucGtK[pucRPQTable[nTonerLimit]];
			*pucC = *pucM = *pucY = 0;
		}
#else
		TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp,
			nYp);
		*pucK = pucGtK[ucK];
		*pucC = pucGtC[pucRPQTable[nCp]];
		*pucM = pucGtM[pucRPQTable[nMp]];
		*pucY = pucGtY[pucRPQTable[nYp]];
#endif
	}
	else
	{
		*pucK = pucGtK[ucK];
		*pucC = pucGtC[ucC];
		*pucM = pucGtM[ucM];
		*pucY = pucGtY[ucY];
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransGcrHgrPQlimit
//Description   : BG/UCR(WishGCRHGR) -> USER GAMMA -> PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransGcrHgrPQlimit(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK;
	int nC = (int)*pucC;
	int nM = (int)*pucM;
	int nY = (int)*pucY;
	int nKp, nCp, nMp, nYp;
	unsigned char ucK, ucC, ucM, ucY;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	unsigned char *pucUserGtK = ppucGamma[4];
	unsigned char *pucUserGtC = ppucGamma[5];
	unsigned char *pucUserGtM = ppucGamma[6];
	unsigned char *pucUserGtY = ppucGamma[7];
	int nSumCMYK;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;
	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&pobjColor->m_sGcrHgrInfo;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);

	WiShGCR(m_sGcrInfo, nC, nM, nY, nK);
	
	ucK = nK;
	ucC = nC;
	ucM = nM;
	ucY = nY;
	pobjColor->ApplyUserGammas(pucUserGtK, 1, &ucK);
	pobjColor->ApplyUserGammas(pucUserGtC, 1, &ucC);
	pobjColor->ApplyUserGammas(pucUserGtM, 1, &ucM);
	pobjColor->ApplyUserGammas(pucUserGtY, 1, &ucY);
	
	nKp = (int)pucPQTable[ucK];
	nCp = (int)pucPQTable[ucC];
	nMp = (int)pucPQTable[ucM];
	nYp = (int)pucPQTable[ucY];

	nSumCMYK = nKp + nCp + nMp + nYp;
	if (nSumCMYK > nTonerLimit)
	{
#ifdef SUPPORT_LIMITING_K
		if (nTonerLimit > nKp) {
			TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp, nYp);
			*pucK = pucGtK[ucK];
			*pucC = pucGtC[pucRPQTable[nCp]];
			*pucM = pucGtM[pucRPQTable[nMp]];
			*pucY = pucGtY[pucRPQTable[nYp]];
		}
		else
		{
			*pucK = pucGtK[pucRPQTable[nTonerLimit]];
			*pucC = *pucM = *pucY = 0;
		}
#else
		TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp,
			nYp);
		*pucK = pucGtK[ucK];
		*pucC = pucGtC[pucRPQTable[nCp]];
		*pucM = pucGtM[pucRPQTable[nMp]];
		*pucY = pucGtY[pucRPQTable[nYp]];
#endif
	}
	else
	{
		*pucK = pucGtK[ucK];
		*pucC = pucGtC[ucC];
		*pucM = pucGtM[ucM];
		*pucY = pucGtY[ucY];
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransGcrPQlimitNoUserGamma
//Description   : BG/UCR(WishGCR) -> PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransGcrPQlimitNoUserGamma(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK;
	int nC = (int)*pucC;
	int nM = (int)*pucM;
	int nY = (int)*pucY;
	int nKp, nCp, nMp, nYp;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	int nSumCMYK;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;
	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&pobjColor->m_sGcrInfo;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);

	WiShGCR(m_sGcrInfo, nC, nM, nY, nK);
	
	nKp = (int)pucPQTable[nK];
	nCp = (int)pucPQTable[nC];
	nMp = (int)pucPQTable[nM];
	nYp = (int)pucPQTable[nY];

	nSumCMYK = nKp + nCp + nMp + nYp;
	if (nSumCMYK > nTonerLimit)
	{
#ifdef SUPPORT_LIMITING_K
		if (nTonerLimit > nKp) {
			TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp, nYp);
			*pucK = pucGtK[nK];
			*pucC = pucGtC[pucRPQTable[nCp]];
			*pucM = pucGtM[pucRPQTable[nMp]];
			*pucY = pucGtY[pucRPQTable[nYp]];
		}
		else
		{
			*pucK = pucGtK[pucRPQTable[nTonerLimit]];
			*pucC = *pucM = *pucY = 0;
		}
#else
		TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp,
			nYp);
		*pucK = pucGtK[nK];
		*pucC = pucGtC[pucRPQTable[nCp]];
		*pucM = pucGtM[pucRPQTable[nMp]];
		*pucY = pucGtY[pucRPQTable[nYp]];
#endif
	}
	else
	{
		*pucK = pucGtK[nK];
		*pucC = pucGtC[nC];
		*pucM = pucGtM[nM];
		*pucY = pucGtY[nY];
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      : TransGcrHgrPQlimitNoUserGamma
//Description   : BG/UCR(WishGCRHGR) -> PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransGcrHgrPQlimitNoUserGamma(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK;
	int nC = (int)*pucC;
	int nM = (int)*pucM;
	int nY = (int)*pucY;
	int nKp, nCp, nMp, nYp;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	int nSumCMYK;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;
	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&pobjColor->m_sGcrHgrInfo;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);

	WiShGCR(m_sGcrInfo, nC, nM, nY, nK);
	
	nKp = (int)pucPQTable[nK];
	nCp = (int)pucPQTable[nC];
	nMp = (int)pucPQTable[nM];
	nYp = (int)pucPQTable[nY];

	nSumCMYK = nKp + nCp + nMp + nYp;
	if (nSumCMYK > nTonerLimit)
	{
#ifdef SUPPORT_LIMITING_K
		if (nTonerLimit > nKp) {
			TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp, nYp);
			*pucK = pucGtK[nK];
			*pucC = pucGtC[pucRPQTable[nCp]];
			*pucM = pucGtM[pucRPQTable[nMp]];
			*pucY = pucGtY[pucRPQTable[nYp]];
		}
		else
		{
			*pucK = pucGtK[pucRPQTable[nTonerLimit]];
			*pucC = *pucM = *pucY = 0;
		}
#else
		TONER_LIMIT (nTonerLimit, nSumCMYK, nKp, nCp, nMp,
			nYp);
		*pucK = pucGtK[nK];
		*pucC = pucGtC[pucRPQTable[nCp]];
		*pucM = pucGtM[pucRPQTable[nMp]];
		*pucY = pucGtY[pucRPQTable[nYp]];
#endif
	}
	else
	{
		*pucK = pucGtK[nK];
		*pucC = pucGtC[nC];
		*pucM = pucGtM[nM];
		*pucY = pucGtY[nY];
	}
}

#ifdef SUPPORT_COMPOSITEBLACK
///////////////////////////////////////////////////////////////////////////////
//Function      :TransBgucrCompbk
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :int nC:[IN]
//              :int nM:[IN]
//              :int nY:[IN]
//              :unsigned char ucKCMY[]:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucrCompbk(
	CPRColor* pobjColor,
	int nC,
	int nM,
	int nY,
	unsigned char ucKCMY[])
{
	int nMinColor;
	int nUCR;

	nMinColor = nC;
	if (nM < nMinColor)
		nMinColor = nM;
	if (nY < nMinColor)
		nMinColor = nY;

	ucKCMY[0] = pobjColor->m_ucBgLutCompbk[nMinColor];
	nUCR = (int)pobjColor->m_ucUcrLutCompbk[nMinColor];
	ucKCMY[1] = (unsigned char)(nC - nUCR);
	ucKCMY[2] = (unsigned char)(nM - nUCR);
	ucKCMY[3] = (unsigned char)(nY - nUCR);
}
///////////////////////////////////////////////////////////////////////////////
//Function      : TransBgucrPQlimitCompbk
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nTonerLimit:[IN]
//              :unsigned char **ppucGamma)	:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransBgucrPQlimitCompbk(
	CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nTonerLimit,
	unsigned char **ppucGamma)
{
	int nK, nC, nM, nY, nMinColor;
	int nUCR;
	unsigned char *pucGtK = ppucGamma[0];
	unsigned char *pucGtC = ppucGamma[1];
	unsigned char *pucGtM = ppucGamma[2];
	unsigned char *pucGtY = ppucGamma[3];
	int nSumCMYK;
	unsigned char *UCRtbl = pobjColor->m_ucUcrLutCompbk;
	unsigned char *BGtbl = pobjColor->m_ucBgLutCompbk;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;;
	assert(pucGtK && pucGtC && pucGtM && pucGtY);


	nMinColor = nC = (int)*pucC;
	nM = (int)*pucM;
	if (nM < nMinColor)
		nMinColor = nM;
	nY = (int)*pucY;
	if (nY < nMinColor)
		nMinColor = nY;

	nUCR = (int)UCRtbl[nMinColor];

	nK = (int)pucPQTable[*pucK = BGtbl[nMinColor]];
	nC = (int)pucPQTable[*pucC = nC - nUCR];
	nM = (int)pucPQTable[*pucM = nM - nUCR];
	nY = (int)pucPQTable[*pucY = nY - nUCR];

	nSumCMYK = nK + nC + nM + nY;
	if (nSumCMYK > nTonerLimit)
	{
#ifdef SUPPORT_LIMITING_K
		if (nTonerLimit > nK) {
			TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
			*pucK = pucGtK[*pucK];
			*pucC = pucGtC[pucRPQTable[nC]];
			*pucM = pucGtM[pucRPQTable[nM]];
			*pucY = pucGtY[pucRPQTable[nY]];
		}
		else
		{
			*pucK = pucGtK[pucRPQTable[nTonerLimit]];
			*pucC = *pucM = *pucY = 0;
		}
#else
		TONER_LIMIT (nTonerLimit, nSumCMYK, nK, nC, nM, nY);
		*pucK = pucGtK[*pucK];
		*pucC = pucGtC[pucRPQTable[nC]];
		*pucM = pucGtM[pucRPQTable[nM]];
		*pucY = pucGtY[pucRPQTable[nY]];
#endif
	}
	else
	{
		*pucK = pucGtK[*pucK];
		*pucC = pucGtC[*pucC];
		*pucM = pucGtM[*pucM];
		*pucY = pucGtY[*pucY];
	}
	return;
}
#endif /* SUPPORT_COMPOSITEBLACK */

///////////////////////////////////////////////////////////////////////////////
//Function      :SetTransgcr
//Description   : 
//Arguments     :
//              :void
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::SetTransgcr(void)
{
	if (m_nIsGcr)
	{
		m_pFuncGcr = TransGcr;
		m_pFuncGcrHgr = TransGcrHgr;
		if (m_nIsPqtc)
		{
			m_pFuncGcrLimit = TransGcrPQlimit;
			m_pFuncGcrHgrLimit = TransGcrHgrPQlimit;
			m_pFuncLimit = TransPQlimit;
		}
		else
		{
			m_pFuncGcrLimit = TransGcrLimit;
			m_pFuncGcrHgrLimit = TransGcrHgrLimit;
			m_pFuncLimit = TransLimit;
		}
	}
	else
	{
		m_pFuncGcr = TransBgucr;
		m_pFuncGcrHgr = TransBgucrHgr;
		if (m_nIsPqtc)
		{
			m_pFuncGcrLimit = TransBgucrPQlimit;
			m_pFuncGcrHgrLimit = TransBgucrHgrPQlimit;
			m_pFuncLimit = TransPQlimit;
		}
		else
		{
			m_pFuncGcrLimit = TransBgucrLimit;
			m_pFuncGcrHgrLimit = TransBgucrHgrLimit;
			m_pFuncLimit = TransLimit;
		}
#ifdef SUPPORT_COMPOSITEBLACK
		m_pFuncGcrCompbk = TransBgucrCompbk;
		m_pFuncGcrLimitCompbk = TransBgucrPQlimitCompbk;
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :CPRColor
//Description   :Constructor
//Arguments     :
//Return value  ::
///////////////////////////////////////////////////////////////////////////////
CPRColor::CPRColor()
{
	for (int nCount = 0; nCount < SIZEOF_LUT; nCount++)
	{
		m_ucBgLut[nCount] = '\0';
		m_ucUcrLut[nCount] = '\0';
	}
	m_pucPqTbl = NULL;
	m_pucRPqTbl = NULL;
	m_pucPqTblPhot = NULL;
	m_pucRPqTblPhot = NULL;
	m_pucPqTblText = NULL;
	m_pucRPqTblText = NULL;
	pqtbl_ed = NULL;
	rpqtbl_ed =NULL;
#ifdef SUPPORT_CUTTING_RGBVALUE
	m_ucRgbRatio[OBJ_IMAG] =
	m_ucRgbRatio[OBJ_GRAP] =
	m_ucRgbRatio[OBJ_TEXT] =
	m_ucRgbRatio[OBJ_LINE] = DEFAULT_RGB_RATIO;
	for (int nLevel = 0; nLevel < 256; nLevel++)
	{
		m_ucRatioColorTbl[OBJ_IMAG][nLevel] =
		m_ucRatioColorTbl[OBJ_GRAP][nLevel] =
		m_ucRatioColorTbl[OBJ_TEXT][nLevel] =
		m_ucRatioColorTbl[OBJ_LINE][nLevel] = nLevel;
	}
#ifdef SUPPORT_COMPOSITEBLACK
	m_ucRgbRatioCompbk[OBJ_IMAG] =
	m_ucRgbRatioCompbk[OBJ_GRAP] =
	m_ucRgbRatioCompbk[OBJ_TEXT] =
	m_ucRgbRatioCompbk[OBJ_LINE] = DEFAULT_RGB_RATIO;
	for (int nLevel = 0; nLevel < 256; nLevel++)
	{
		m_ucRatioColorTblCompbk[OBJ_IMAG][nLevel] =
		m_ucRatioColorTblCompbk[OBJ_GRAP][nLevel] =
		m_ucRatioColorTblCompbk[OBJ_TEXT][nLevel] =
		m_ucRatioColorTblCompbk[OBJ_LINE][nLevel] = nLevel;
	}
	m_ulBgucrTblFlag = 0L;
#endif
#endif
#ifdef SUPPORT_CUTTING_TONERLIMIT
	m_ucTonerLimitRatio[OBJ_IMAG] = 
	m_ucTonerLimitRatio[OBJ_GRAP] = 
	m_ucTonerLimitRatio[OBJ_TEXT] = 
	m_ucTonerLimitRatio[OBJ_LINE] = DEFAULT_TONERLIMIT_RATIO;
#endif
	// CMM m_psCmmColor = NULL;
	m_ulGrayCount = 0L;
	m_usGrayHistory = 0;
	m_ulClrUsedPlane = 0L;
	m_nIsPqtc = 0;
	m_nDevPqtc = 0;
	m_nIsGcr = 0;
	m_nRenderNColor = 0;
	m_ucIsGrayJudge = 0;
	for (int nCacheNum = 0; nCacheNum < CR_CACHE_SIZE; ++nCacheNum) {
		m_sCache[nCacheNum].ulRGB = 0xffffffff;
		m_sCache[nCacheNum].ucK = 0xff;
		m_sCache[nCacheNum].ucC = 0xff;
		m_sCache[nCacheNum].ucM = 0xff;
		m_sCache[nCacheNum].ucY = 0xff;
	}
}

#ifdef SUPPORT_CUTTING_RGBVALUE
///////////////////////////////////////////////////////////////////////////////
//Function      :SetRgbRatioAndTable
//Description   :This function is responsible for Setting the  Ratio for
//               Input Color into the color object (CPRColor). 
//Arguments     :
//              :unsigned char ucMode:[IN]
//              :unsigned char ucPhot:[IN]
//              :unsigned char ucFill:[IN]
//              :unsigned char ucText:[IN]
//              :unsigned char ucLine:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::SetRgbRatioAndTable (unsigned char ucMode,
	unsigned char ucPhot,
	unsigned char ucFill,
	unsigned char ucText,
	unsigned char ucLine)
{
	int nLevel;

	if (ucMode == PR_PRINT_NORMAL)
	{
		if (ucPhot != m_ucRgbRatio[OBJ_IMAG])
		{
			m_ucRgbRatio[OBJ_IMAG] = ucPhot;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTbl[OBJ_IMAG][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatio[OBJ_IMAG] / 100;
			}
		}
		if (ucFill != m_ucRgbRatio[OBJ_GRAP])
		{
			m_ucRgbRatio[OBJ_GRAP] = ucFill;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTbl[OBJ_GRAP][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatio[OBJ_GRAP] / 100;
			}
		}
		if (ucText != m_ucRgbRatio[OBJ_TEXT])
		{
			m_ucRgbRatio[OBJ_TEXT] = ucText;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTbl[OBJ_TEXT][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatio[OBJ_TEXT] / 100;
			}
		}
		if (ucLine != m_ucRgbRatio[OBJ_LINE])
		{
			m_ucRgbRatio[OBJ_LINE] = ucLine;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTbl[OBJ_LINE][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatio[OBJ_LINE] / 100;
			}
		}
	}
#ifdef SUPPORT_COMPOSITEBLACK
	else  if (ucMode == PR_PRINT_COMPBK)
	{
		if (ucPhot != m_ucRgbRatioCompbk[OBJ_IMAG])
		{
			m_ucRgbRatioCompbk[OBJ_IMAG] = ucPhot;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTblCompbk[OBJ_IMAG][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatioCompbk[OBJ_IMAG] / 100;
			}
		}
		if (ucFill != m_ucRgbRatioCompbk[OBJ_GRAP])
		{
			m_ucRgbRatioCompbk[OBJ_GRAP] = ucFill;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTblCompbk[OBJ_GRAP][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatioCompbk[OBJ_GRAP] / 100;
			}
		}
		if (ucText != m_ucRgbRatioCompbk[OBJ_TEXT])
		{
			m_ucRgbRatioCompbk[OBJ_TEXT] = ucText;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTblCompbk[OBJ_TEXT][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatioCompbk[OBJ_TEXT] / 100;
			}
		}
		if (ucLine != m_ucRgbRatioCompbk[OBJ_LINE])
		{
			m_ucRgbRatioCompbk[OBJ_LINE] = ucLine;
			for (nLevel = 0; nLevel < 256; nLevel++)
			{
				m_ucRatioColorTblCompbk[OBJ_LINE][nLevel] =
					255 - (255 - nLevel) * m_ucRgbRatioCompbk[OBJ_LINE] / 100;
			}
		}
	}
#endif
}
#endif /* SUPPORT_CUTTING_RGBVALUE */

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyRgb2Cmy 
//Description   : 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned	char ucKCMY[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyRgb2Cmy (unsigned char ucRGB[], unsigned
	char ucKCMY[])
{
	// CMM if (m_lIsCmm)
	if( m_lIsCmm )
	{
		//if (m_psCmmColor->m_ulCurId & CMM_CMYK)
		if( m_ulCurId & CMM_CMYK)
		{;
			assert (FALSE);
		}
		else
		{
		    unsigned long *ucRGBData = (unsigned long*)ucRGB;
#ifdef X86
			if (*ucRGBData == 0 || *ucRGBData == FULLX86)
			{
#else
			if (*ucRGBData == 0 || *ucRGBData == FULL)
			{
#endif // X86
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
#ifdef X86
				*ucRGBData = LSWAP (*ucRGBData);
#endif // X86
				if (CMM_DoConversion4_padding (m_lIsCmm, (unsigned long*)ucRGBData, (unsigned long*)ucRGBData, 1,
											m_ulCurId))
				{
#ifdef X86
					*ucRGBData = LSWAP (*ucRGBData);
#endif // X86
				}
#ifdef X86
				*ucRGBData = LSWAP (*ucRGBData);
#endif // X86
			}

		}
	}
	ucKCMY[0] = 0;		// Black: Not use
	ucKCMY[1] = ~(ucRGB[0]);	// Cyan = 255 - Red
	ucKCMY[2] = ~(ucRGB[1]);	// Mazenta = 255 - Green
	ucKCMY[3] = ~(ucRGB[2]);	// Yellow = 255 - Blue
}

#ifdef SUPPORT_CUTTING_RGBVALUE
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucr 
//Description   :Conver RGB to KCMY in BG/UCR method. 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned	char ucKCMY[]:[IN]
//              :int		nObjMode:[IN]
//              :unsigned long ulSrcNot:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucr(unsigned char ucRGB[], unsigned char ucKCMY[],
	int nObjMode, unsigned long ulSrcNot)
#else
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucr 
//Description   : 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned	char ucKCMY[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucr (unsigned char ucRGB[], unsigned
	char ucKCMY[])
#endif /* SUPPORT_CUTTING_RGBVALUE */
{

#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(this, &ucRGB[0], &ucRGB[1], &ucRGB[2], 1,
			nObjMode, ulSrcNot);
#endif

	 /* CMM if (m_lIsCmm) */
    if( m_lIsCmm )
	{
		/* CMM if (m_psCmmColor->m_ulCurId & CMM_CMYK) */
		if( m_ulCurId & CMM_CMYK )
		{
#ifdef X86
			unsigned long tmprgb;
#endif // X86	
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			  unsigned long *rgbdata  = (unsigned long *) ucRGB;
			  unsigned long *kcmydata = (unsigned long *) ucKCMY;
#ifdef X86
			tmprgb = *rgbdata;
			tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
			if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
							kcmydata, 1, m_ulCurId))
			{
#else // X86
			if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, rgbdata,
							kcmydata, 1, m_ulCurId))
			{
#endif // X86
			printf ("\t[CMM-padding]ERROR ");
			}
#ifdef X86
			*ucKCMY = LSWAP (*ucKCMY);
#endif // X86
			}
			return;
		}
		else
		{
#ifdef X86
			if (*ucRGB == 0 || *ucRGB == FULLX86)
			{
#else
			if (*ucRGB == 0 || *ucRGB == FULL)
			{
#endif // X86
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			    unsigned long *rgbdata  = (unsigned long *) ucRGB;
#ifdef X86
			    *rgbdata = LSWAP (*rgbdata);
#endif // X86
				if (CMM_DoConversion4_padding (m_lIsCmm, rgbdata, rgbdata, 1,
										m_ulCurId))
				{
#ifdef X86
					*rgbdata = LSWAP (*rgbdata);
#endif // X86
				}
#ifdef X86
				*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}
		}
	}
	m_pFuncGcr(this, 255 - (int)ucRGB[0],
		255 - (int)ucRGB[1], 255 - (int)ucRGB[2], ucKCMY);
}

#ifdef SUPPORT_CUTTING_RGBVALUE
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrHgr 
//Description   :Conver RGB to KCMY in BG/UCR(HGR) method. 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned	char ucKCMY[]:[IN]
//              :int		nObjMode:[IN]
//              :unsigned long ulSrcNot:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrHgr(unsigned char ucRGB[], unsigned char ucKCMY[],
	int nObjMode, unsigned long ulSrcNot)
#else
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrHgr 
//Description   : 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned	char ucKCMY[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrHgr (unsigned char ucRGB[], unsigned
	char ucKCMY[])
#endif /* SUPPORT_CUTTING_RGBVALUE */
{

#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(this, &ucRGB[0], &ucRGB[1], &ucRGB[2], 1,
			nObjMode, ulSrcNot);
#endif
	if (m_lIsCmm)
	{
		if (m_ulCurId & CMM_CMYK)
		{
#ifdef X86
			unsigned long tmprgb;
#endif // X86	
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			    unsigned long *rgbdata  = (unsigned long *) ucRGB;
			    unsigned long *kcmydata = (unsigned long *) ucKCMY;
#ifdef X86
			    tmprgb = *rgbdata;
			    tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
			    if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
							    kcmydata, 1, m_ulCurId))
			    {
#else // X86
			    if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, rgbdata,
							kcmydata, 1, m_ulCurId))
			    {
#endif // X86
			        printf ("\t[CMM-padding]ERROR ");
			    }
#ifdef X86
			    *ucKCMY = LSWAP (*ucKCMY);
#endif // X86
			    }
			    return;
		}
		else
		{
#ifdef X86
			if (*ucRGB == 0 || *ucRGB == FULLX86)
			{
#else
			if (*ucRGB == 0 || *ucRGB == FULL)
			{
#endif // X86
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			    unsigned long *rgbdata  = (unsigned long *) ucRGB;
#ifdef X86
				*rgbdata = LSWAP (*rgbdata);
#endif // X86
				if (CMM_DoConversion4_padding (m_lIsCmm, rgbdata, rgbdata, 1,
											m_ulCurId))
				{
#ifdef X86
					*rgbdata = LSWAP (*rgbdata);
#endif // X86
				}
#ifdef X86
				*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}

		}
	}
	m_pFuncGcrHgr(this, 255 - (int)ucRGB[0],
		255 - (int)ucRGB[1], 255 - (int)ucRGB[2], ucKCMY);
}

#ifdef SUPPORT_CUTTING_RGBVALUE
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrKeepgray 
//Description   :Conver RGB to KCMY in BG/UCR method, but convert R=G=B to 1K. 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned char ucKCMY[]:[IN]
//              :int	nObjMode:[IN]
//              :unsigned long ulSrcNot:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrKeepgray(unsigned char ucRGB[], unsigned char ucKCMY[],
	int nObjMode, unsigned long ulSrcNot)
#else
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrKeepgray 
//Description   : 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned char ucKCMY[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrKeepgray (unsigned char ucRGB[],
	unsigned char ucKCMY[])
#endif /* SUPPORT_CUTTING_RGBVALUE */
{


	if (ucRGB[0] == ucRGB[1] && ucRGB[1] == ucRGB[2])
	{
		ucKCMY[0] = ~(ucRGB[0]);
		ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgbRatioGray(this, &ucKCMY[0], 1, nObjMode, ulSrcNot);
#endif
		return;
	}

#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(this, &ucRGB[0], &ucRGB[1], &ucRGB[2], 1,
			nObjMode, ulSrcNot);
#endif
	if (m_lIsCmm)
	{
		if (m_ulCurId & CMM_CMYK)
		{
#ifdef X86
			unsigned long tmprgb;
#endif // X86	
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			    unsigned long *rgbdata  = (unsigned long *) ucRGB;
                unsigned long *kcmydata = (unsigned long *) ucKCMY;
#ifdef X86
				tmprgb = *rgbdata;
				tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
							kcmydata, 1, m_ulCurId))
				{
#else // X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, rgbdata,
							kcmydata, 1, m_ulCurId))
				{
#endif // X86
						printf ("\t[CMM-padding]ERROR ");
				}
#ifdef X86
				*kcmydata = LSWAP (*kcmydata);
#endif // X86
			}
			return;

		}
		else
		{
#ifdef X86
			if (*ucRGB == 0 || *ucRGB == FULLX86)
			{
#else
			if (*ucRGB == 0 || *ucRGB == FULL)
			{
#endif // X86
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			unsigned long *rgbdata  = (unsigned long *) ucRGB;
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			if (CMM_DoConversion4_padding (m_lIsCmm, rgbdata, rgbdata, 1,
							m_ulCurId))
			{
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}

			if( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
				&& (ucRGB[0] == ucRGB[1]) && (ucRGB[1] == ucRGB[2]) )
			{
				ucKCMY[0] = ~(ucRGB[0]);
				ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
				return;
			}
		}
	}
	m_pFuncGcr(this, 255 - (int)ucRGB[0],
		255 - (int)ucRGB[1], 255 - (int)ucRGB[2], ucKCMY);
}

#ifdef SUPPORT_CUTTING_RGBVALUE
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrHgrKeepgray 
//Description   :Conver RGB to KCMY in BG/UCR(HGR) method, but convert R=G=B to 1K. 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned char ucKCMY[]:[IN]
//              :int	nObjMode:[IN]
//              :unsigned long ulSrcNot:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrHgrKeepgray(unsigned char ucRGB[], unsigned char ucKCMY[],
	int nObjMode, unsigned long ulSrcNot)
#else
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrHgrKeepgray 
//Description   : 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned char ucKCMY[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrHgrKeepgray (unsigned char ucRGB[],
	unsigned char ucKCMY[])
#endif /* SUPPORT_CUTTING_RGBVALUE */
{


	if (ucRGB[0] == ucRGB[1] && ucRGB[1] == ucRGB[2])
	{
		ucKCMY[0] = ~(ucRGB[0]);
		ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgbRatioGray(this, &ucKCMY[0], 1, nObjMode, ulSrcNot);
#endif
		return;
	}

#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(this, &ucRGB[0], &ucRGB[1], &ucRGB[2], 1,
			nObjMode, ulSrcNot);
#endif
	if (m_lIsCmm)
	{
		if (m_ulCurId & CMM_CMYK)
		{
#ifdef X86
			unsigned long tmprgb;
#endif // X86	
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			    unsigned long *rgbdata  = (unsigned long *) ucRGB;
                unsigned long *kcmydata = (unsigned long *) ucKCMY;
#ifdef X86
				tmprgb = *rgbdata;
				tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
										kcmydata, 1, m_ulCurId))
				{
#else // X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, rgbdata,
										kcmydata, 1, m_ulCurId))
				{
#endif // X86
					printf ("\t[CMM-padding]ERROR ");
				}
#ifdef X86
				*kcmydata = LSWAP (*kcmydata);
#endif // X86
			}
			return;
		}
		else
		{
#ifdef X86
			if (*ucRGB == 0 || *ucRGB == FULLX86)
			{
#else
			if (*ucRGB == 0 || *ucRGB == FULL)
			{
#endif // X86
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			unsigned long *rgbdata  = (unsigned long *) ucRGB;
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			if (CMM_DoConversion4_padding (m_lIsCmm, rgbdata, rgbdata, 1,
							m_ulCurId))
			{
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}


			if( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
				&& (ucRGB[0] == ucRGB[1]) && (ucRGB[1] == ucRGB[2]) )
			{
				ucKCMY[0] = ~(ucRGB[0]);
				ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
				return;
			}
		}
	}
	m_pFuncGcrHgr(this, 255 - (int)ucRGB[0],
		255 - (int)ucRGB[1], 255 - (int)ucRGB[2], ucKCMY);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrKeepblack 
//Description   : 
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned char ucKCMY[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrKeepblack (unsigned char ucRGB[],
	unsigned char ucKCMY[])
{

	if (ucRGB[0] == 0 && ucRGB[1] == 0 && ucRGB[2] == 0)
	{
		ucKCMY[0] = 255;
		ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
		return;
	}

	if (m_lIsCmm)
	{
		if (m_ulCurId & CMM_CMYK)
		{
#ifdef X86
			unsigned long tmprgb;
#endif // X86	
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			unsigned long *rgbdata  = (unsigned long *) ucRGB;
            unsigned long *kcmydata = (unsigned long *) ucKCMY;
#ifdef X86
			tmprgb = *rgbdata;
			tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
			if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
							kcmydata, 1, m_ulCurId))
			{
#else // X86
			if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, rgbdata,
							kcmydata, 1, m_ulCurId))
			{
#endif // X86
			printf ("\t[CMM-padding]ERROR ");
			}
#ifdef X86
			*kcmydata = LSWAP (*kcmydata);
#endif // X86
			}
			return;
		}
		else
		{
#ifdef X86
			if (*ucRGB == 0 || *ucRGB == FULLX86)
			{
#else
			if (*ucRGB == 0 || *ucRGB == FULL)
			{
#endif // X86
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			unsigned long *rgbdata  = (unsigned long *) ucRGB;
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			if (CMM_DoConversion4_padding (m_lIsCmm, rgbdata, rgbdata, 1,
							m_ulCurId))
			{
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}

			/* CMMﾅ津｣窶堙渓eepblack窶敖ｻ窶凖ｨ */
			if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
				&& (ucRGB[0] == 0) && (ucRGB[1] == 0) && (ucRGB[2] == 0) )
			{
				ucKCMY[0] = 255;
				ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
				return;
			}
		}
	}
	m_pFuncGcr(this, 255 - (int)ucRGB[0],
		255 - (int)ucRGB[1], 255 - (int)ucRGB[2], ucKCMY);
}

#ifdef SUPPORT_COMPOSITEBLACK
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrCompbk
//Description   :Convert GRAY to COMPBK
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned	char ucKCMY[]:[IN]
//              :int		nObjectKind:[IN]
//              :unsigned long ulSrcNot:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrCompbk (unsigned char ucRGB[], unsigned char ucKCMY[],
	int nObjectKind, unsigned long ulSrcNot)
{
	unsigned int nGray;
	unsigned int nIsgray;

	nIsgray = ((ucRGB[0] == ucRGB[1]) && (ucRGB[1] == ucRGB[2]));

	if (m_ucRenderingIsmono && !nIsgray)
	{
		nGray = (ucRGB[0] * ICL_WR + ucRGB[1] * ICL_WG + ucRGB[2] * IC_WB)
			/ IC_WBIAS;
		if (nGray > 255)
		{
			nGray = 255;
		}
		ucRGB[0] = ucRGB[1] = ucRGB[2] = nGray;
		nIsgray = TRUE;
	}

	if (nIsgray)	/* GRAY -> CMM -> COMPBK */
	{
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgbRatioRgbCompbk(this, &ucRGB[0], &ucRGB[1], &ucRGB[2],
						1, nObjectKind, ulSrcNot);
#endif
		if (m_lIsCmm)
		{
			// Set profile ID
			m_ulCurId =
				m_ulCmmProfilesCompbk[nObjectKind];

			if (m_ulCurId & CMM_CMYK)
			{
#ifdef X86
				unsigned long tmprgb;
#endif // X86	
				if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
				}
				else
				{
#ifdef X86
				tmprgb = *ucRGB;
				tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
								ucKCMY, 1, m_ulCurId))
				{
#else // X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, ucRGB,
								ucKCMY, 1, m_ulCurId))
				{
#endif // X86
				printf ("\t[CMM-padding]ERROR ");
				}
#ifdef X86
				*ucKCMY = LSWAP (*ucKCMY);
#endif // X86
				}
				return;
			}
			else
			{
#ifdef X86
				if (*ucRGB == 0 || *ucRGB == FULLX86)
				{
#else
				if (*ucRGB == 0 || *ucRGB == FULL)
				{
#endif // X86
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
				}
				else
				{
#ifdef X86
				*ucRGB = LSWAP (*ucRGB);
#endif // X86
				if (CMM_DoConversion4_padding (m_lIsCmm, ucRGB, ucRGB, 1,
								m_ulCurId))
				{
#ifdef X86
				*ucRGB = LSWAP (*ucRGB);
#endif // X86
				}
#ifdef X86
				*ucRGB = LSWAP (*ucRGB);
#endif // X86
				}

			}
		}
		m_pFuncGcrCompbk(this, 255 - (int)ucRGB[0],
			255 - (int)ucRGB[1], 255 - (int)ucRGB[2], ucKCMY);
	}
	else	/* RGB -> CMM -> CMYK */
	{
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgbRatioRgb(this, &ucRGB[0], &ucRGB[1], &ucRGB[2],
					1, nObjectKind, ulSrcNot);
#endif
		if (m_lIsCmm)
		{
			if (m_ulCurId & CMM_CMYK)
			{
#ifdef X86
				unsigned long tmprgb;
#endif // X86	
				if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
				}
				else
				{
#ifdef X86
				tmprgb = *ucRGB;
				tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
								ucKCMY, 1, m_ulCurId))
				{
#else // X86
				if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, ucRGB,
								ucKCMY, 1, m_ulCurId))
				{
#endif // X86
				printf ("\t[CMM-padding]ERROR ");
				}
#ifdef X86
				*ucKCMY = LSWAP (*ucKCMY);
#endif // X86
				}
				return;
			}
			else
			{
#ifdef X86
				if (*ucRGB == 0 || *ucRGB == FULLX86)
				{
#else
				if (*ucRGB == 0 || *ucRGB == FULL)
				{
#endif // X86
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-padding]SKIP ");
#endif
				}
				else
				{
#ifdef X86
				*ucRGB = LSWAP (*ucRGB);
#endif // X86
				if (CMM_DoConversion4_padding (m_lIsCmm, ucRGB, ucRGB, 1,
								m_ulCurId))
				{
#ifdef X86
				*ucRGB = LSWAP (*ucRGB);
#endif // X86
				}
#ifdef X86
				*ucRGB = LSWAP (*ucRGB);
#endif // X86
				}

			}
		}
		m_pFuncGcr(this, 255 - (int)ucRGB[0],
			255 - (int)ucRGB[1], 255 - (int)ucRGB[2], ucKCMY);
	}
}
#endif /* SUPPORT_COMPOSITEBLACK */

/************************************************************************
 *	ﾆ狸ﾆ停�ﾆ筑窶倪ぎ�ｽﾃｬﾅ�厄ｿｽ窶�						*
 ************************************************************************/
///////////////////////////////////////////////////////////////////////////////
//Function      :DoGamma
//Description   : USER GAMMA -> PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :unsigned char ucKCMY[]:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t* pLimit:[IN]
//              :unsigned char** ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::DoGamma(unsigned char ucKCMY[],
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t* pLimit,
	unsigned char** ppucGamma)
{
	int nTonerLimit, nSumCMYK;
	unsigned char ucK, ucC, ucM, ucY;
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	unsigned char *pucUserGtK, *pucUserGtC, *pucUserGtM, *pucUserGtY;
	unsigned char ucKp, ucCp, ucMp, ucYp;
#ifdef GAMMA_THROUGH
	return;
#endif
	ucK = ucKCMY[0];
	ucC = ucKCMY[1];
	ucM = ucKCMY[2];
	ucY = ucKCMY[3];

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	pucUserGtK = ppucGamma[4];
	pucUserGtC = ppucGamma[5];
	pucUserGtM = ppucGamma[6];
	pucUserGtY = ppucGamma[7];
	
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);

	if (m_nIsPqtc)
	{
		ApplyUserGammas(pucUserGtK, 1, &ucK);
		ApplyUserGammas(pucUserGtC, 1, &ucC);
		ApplyUserGammas(pucUserGtM, 1, &ucM);
		ApplyUserGammas(pucUserGtY, 1, &ucY);
		
		ucKp = m_pucPqTbl[ucK];
		ucCp = m_pucPqTbl[ucC];
		ucMp = m_pucPqTbl[ucM];
		ucYp = m_pucPqTbl[ucY];

		nSumCMYK = ucCp + ucMp + ucYp + ucKp;
#ifdef SUPPORT_LIMITING_K
		if (nSumCMYK > nTonerLimit)
		{
			if (nTonerLimit > ucKp)
			{
				TONER_LIMIT (nTonerLimit, nSumCMYK,
							ucKp, ucCp, ucMp, ucYp);
				ucKCMY[0] = pucGtK[ucK];
				ucKCMY[1] = pucGtC[m_pucRPqTbl[ucCp]];
				ucKCMY[2] = pucGtM[m_pucRPqTbl[ucMp]];
				ucKCMY[3] = pucGtY[m_pucRPqTbl[ucYp]];
			}
			else
			{
				ucKCMY[0] = pucGtK[m_pucRPqTbl[nTonerLimit]];
				ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
			}
		}
		else
		{
			/* gamma */
			ucKCMY[0] = pucGtK[ucK];
			ucKCMY[1] = pucGtC[ucC];
			ucKCMY[2] = pucGtM[ucM];
			ucKCMY[3] = pucGtY[ucY];
		}
#else
		if (nSumCMYK > nTonerLimit)
		{
			TONER_LIMIT (nTonerLimit, nSumCMYK, ucKp, ucCp, ucMp, ucYp);
			ucC = m_pucRPqTbl[ucCp];
			ucM = m_pucRPqTbl[ucMp];
			ucY = m_pucRPqTbl[ucYp];
		}
		// ppucGamma
		ucKCMY[0] = pucGtK[ucK];
		ucKCMY[1] = pucGtC[ucC];
		ucKCMY[2] = pucGtM[ucM];
		ucKCMY[3] = pucGtY[ucY];
#endif	// SUPPORT_LIMITING_K
	}
	else
	{	// pobjColor->m_nIsPqtc
		ucK = pucGtK[ucK];
		ucC = pucGtC[ucC];
		ucM = pucGtM[ucM];
		ucY = pucGtY[ucY];
		nSumCMYK = ucC + ucM + ucY + ucK;
		if (nSumCMYK > nTonerLimit)
		{
			TONER_LIMIT (nTonerLimit, nSumCMYK, ucK, ucC,ucM, ucY);
		}
		ucKCMY[0] = ucK;
		ucKCMY[1] = ucC;
		ucKCMY[2] = ucM;
		ucKCMY[3] = ucY;
	}	// pobjColor->m_nIsPqtc
}

/************************************************************************
 *	ﾆ狸ﾆ停�ﾆ筑窶倪ぎ�ｽﾃｬﾅ�厄ｿｽ窶�RK2)							*
 ************************************************************************/
///////////////////////////////////////////////////////////////////////////////
//Function      :DoGammaRK2
//Description   : PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :unsigned char ucKCMY[]:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t* pLimit:[IN]
//              :unsigned char** ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::DoGammaRK2(unsigned char ucKCMY[],
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t* pLimit,
	unsigned char** ppucGamma)
{
	int nTonerLimit, nSumCK;
	unsigned char ucK, ucC, ucM, ucY;
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC;
	unsigned char ucKp, ucCp, ucMp, ucYp;
#ifdef GAMMA_THROUGH
	return;
#endif
	ucK = ucKCMY[0];
	ucC = ucKCMY[1];
	ucM = ucKCMY[2];
	ucY = ucKCMY[3];

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	
	assert (pucGtK && pucGtC);
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);

	if (m_nIsPqtc)
	{
		ucKp = m_pucPqTbl[ucK];
		ucCp = m_pucPqTbl[ucC];
		ucMp = 0;
		ucYp = 0;

		nSumCK = ucCp + ucKp;
#ifdef SUPPORT_LIMITING_K
		if (nSumCK > nTonerLimit)
		{
			if (nTonerLimit > ucKp)
			{
				TONER_LIMIT (nTonerLimit, nSumCK,
							ucKp, ucCp, ucMp, ucYp);
				ucKCMY[0] = pucGtK[ucK];
				ucKCMY[1] = pucGtC[m_pucRPqTbl[ucCp]];
				ucKCMY[2] = 0;
				ucKCMY[3] = 0;
			}
			else
			{
				ucKCMY[0] = pucGtK[m_pucRPqTbl[nTonerLimit]];
				ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
			}
		}
		else
		{
			/* gamma */
			ucKCMY[0] = pucGtK[ucK];
			ucKCMY[1] = pucGtC[ucC];
			ucKCMY[2] = 0;
			ucKCMY[3] = 0;
		}
#else
		if (nSumCK > nTonerLimit)
		{
			TONER_LIMIT (nTonerLimit, nSumCK, ucKp, ucCp, ucMp, ucYp);
			ucC = m_pucRPqTbl[ucCp];
			ucM = 0;
			ucY = 0;
		}
		// ppucGamma
		ucKCMY[0] = pucGtK[ucK];
		ucKCMY[1] = pucGtC[ucC];
		ucKCMY[2] = 0;
		ucKCMY[3] = 0;
#endif	// SUPPORT_LIMITING_K
	}
	else
	{	// pobjColor->m_nIsPqtc
		ucK = pucGtK[ucK];
		ucC = pucGtC[ucC];
		ucM = 0;
		ucY = 0;
		nSumCK = ucC + ucK;
		if (nSumCK > nTonerLimit)
		{
			TONER_LIMIT (nTonerLimit, nSumCK, ucK, ucC,ucM, ucY);
		}
		ucKCMY[0] = ucK;
		ucKCMY[1] = ucC;
		ucKCMY[2] = 0;
		ucKCMY[3] = 0;
	}	// pobjColor->m_nIsPqtc
}

///////////////////////////////////////////////////////////////////////////////
//Function      :PreDoGammaRK2
//Description   : call DoGammaRK2
//Arguments     :
//              :unsigned char ucKCMY[]:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t* pLimit:[IN]
//              :unsigned char** ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::PreDoGammaRK2(unsigned char ucKCMY[],
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t* pLimit,
	unsigned char** ppucGamma)
{
	ucKCMY[2] = ucKCMY[3] = 0;
	DoGammaRK2(ucKCMY, nObjectKind, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :DoGammaS 
//Description   : USER GAMMA -> PQTC -> TONER LIMIT -> SYSTEM GAMMA
//Arguments     :
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//              :int nSize:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::DoGammaS (int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma,
	int nSize,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY)
{
	int nTonerLimit, nSumCMYK;
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	unsigned char *pucUserGtK, *pucUserGtC, *pucUserGtM, *pucUserGtY;
	unsigned char ucK, ucC, ucM, ucY;
	unsigned char ucKp, ucCp, ucMp, ucYp;

#ifdef GAMMA_THROUGH
	return;
#endif
	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	pucUserGtK = ppucGamma[4];
	pucUserGtC = ppucGamma[5];
	pucUserGtM = ppucGamma[6];
	pucUserGtY = ppucGamma[7];
	
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);
	
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	if (m_nIsPqtc)
	{
		ApplyUserGammas(pucUserGtK, nSize, pucK);
		ApplyUserGammas(pucUserGtC, nSize, pucC);
		ApplyUserGammas(pucUserGtM, nSize, pucM);
		ApplyUserGammas(pucUserGtY, nSize, pucY);
		
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			ucK = *pucK;
			ucC = *pucC;
			ucM = *pucM;
			ucY = *pucY;
			ucKp = m_pucPqTbl[ucK];
			ucCp = m_pucPqTbl[ucC];
			ucMp = m_pucPqTbl[ucM];
			ucYp = m_pucPqTbl[ucY];
			nSumCMYK = ucCp + ucMp + ucYp + ucKp;
#ifdef SUPPORT_LIMITING_K
			if (nSumCMYK > nTonerLimit)
			{
				if (nTonerLimit > ucKp)
				{
					TONER_LIMIT (nTonerLimit, nSumCMYK,
								ucKp, ucCp, ucMp, ucYp);
					*pucK = pucGtK[ucK];
					*pucC = pucGtC[m_pucRPqTbl[ucCp]];
					*pucM = pucGtM[m_pucRPqTbl[ucMp]];
					*pucY = pucGtY[m_pucRPqTbl[ucYp]];
				}
				else
				{
					*pucK = pucGtK[m_pucRPqTbl[nTonerLimit]];
					*pucC = *pucM = *pucY = 0;
				}
			}
			else
			{
				/* gamma */
				*pucK = pucGtK[ucK];
				*pucC = pucGtC[ucC];
				*pucM = pucGtM[ucM];
				*pucY = pucGtY[ucY];
			}
#else
			if (nSumCMYK > nTonerLimit)
			{
				TONER_LIMIT (nTonerLimit, nSumCMYK, ucKp, ucCp, ucMp, ucYp);
				ucC = m_pucRPqTbl[ucCp];
				ucM = m_pucRPqTbl[ucMp];
				ucY = m_pucRPqTbl[ucYp];
			}
			// ppucGamma
			*pucK = pucGtK[ucK];
			*pucC = pucGtC[ucC];
			*pucM = pucGtM[ucM];
			*pucY = pucGtY[ucY];
#endif	// SUPPORT_LIMITING_K
		}		// for loop
	}
	else
	{			// pobjColor->m_nIsPqtc
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			ucK = pucGtK[*pucK];
			ucC = pucGtC[*pucC];
			ucM = pucGtM[*pucM];
			ucY = pucGtY[*pucY];
			nSumCMYK = ucC + ucM + ucY + ucK;
			if (nSumCMYK > nTonerLimit)
			{
				TONER_LIMIT (nTonerLimit, nSumCMYK, ucK, ucC, ucM, ucY);
			}
			*pucK = ucK;
			*pucC = ucC;
			*pucM = ucM;
			*pucY = ucY;
		}	// for loop
	}	// pobjColor->m_nIsPqtc
}

///////////////////////////////////////////////////////////////////////////////
//Function      :GammaSNoTonerLimit 
//Description   : USERﾆ津�SYSTEMﾆ津�//Arguments     :
//              :unsigned char **ppucGamma:[IN]
//              :int nSize:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::GammaSNoTonerLimit (unsigned char **ppucGamma,
	int nSize,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY)
{
	int nI;
	unsigned char *pucGam;
	
	ApplyUserGammas(ppucGamma[4], nSize, pucK);
	
	pucGam = ppucGamma[0];		// K Plane Gamma
	for (nI = 0; nI < nSize; nI++)
	{
		*pucK = pucGam[*pucK];
		pucK++;
	}
	
	ApplyUserGammas(ppucGamma[5], nSize, pucC);
	
	pucGam = ppucGamma[1];		// ucC Plane Gamma
	for (nI = 0; nI < nSize; nI++)
	{
		*pucC = pucGam[*pucC];
		pucC++;
	}
	
	ApplyUserGammas(ppucGamma[6], nSize, pucM);
	
	pucGam = ppucGamma[2];		// ucM Plane Gamma
	for (nI = 0; nI < nSize; nI++)
	{
		*pucM = pucGam[*pucM];
		pucM++;
	}
	
	ApplyUserGammas(ppucGamma[7], nSize, pucY);
	
	pucGam = ppucGamma[3];		// ucY Plane Gamma
	for (nI = 0; nI < nSize; nI++)
	{
		*pucY = pucGam[*pucY];
		pucY++;
	}
}

///////////////////////////////////////////////////////////////////////////////
//	ApplyBgucrsGammas		窶｢ﾂ｡�ｽ窶�CMM+CMY+BG/UCR+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplySrcnotBgucrsGammas		窶｢ﾂ｡�ｽ窶�CMM+CMY+NOT+BG/UCR+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplyBgucrsHgrGammas		窶｢ﾂ｡�ｽ窶�CMM+CMY+BG/UCR(HGR)+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplySrcnotBgucrsHgrGammas		窶｢ﾂ｡�ｽ窶�CMM+CMY+NOT+BG/UCR(HGR)+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplyBgucrKeepgraysGammas	窶｢ﾂ｡�ｽ窶�CMM+CMY+BG/UCR+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplySrcnotBgucrKeepgraysGammas	窶｢ﾂ｡�ｽ窶�CMM+CMY+NOT+BG/UCR+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplyBgucrHgrKeepgraysGammas	窶｢ﾂ｡�ｽ窶�CMM+CMY+BG/UCR(HGR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplySrcnotBgucrHgrKeepgraysGammas	窶｢ﾂ｡�ｽ窶�CMM+CMY+NOT+BG/UCR(HGR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplyRgb2CmyGammas		窶｢ﾂ｡�ｽ窶�CMM+CMY+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplySrcnotRgb2CmyGammas        窶｢ﾂ｡�ｽ窶�CMM+CMY+NOT+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplyBgucrMaybeKeepgraysGammas	窶｢ﾂ｡�ｽ窶�CMM+CMY+BG/UCR+MaybeGray+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplyBgucrAboutKeepgraysGammas	窶｢ﾂ｡�ｽ窶�CMM+CMY+BG/UCR+AboutGray+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplyBgucrImageKsGammas	        窶｢ﾂ｡�ｽ窶�CMM+CMY+BG/UCR+PureBlack+USERﾆ津�PQTC+SYSTEMﾆ津�
//	ApplySrcnotBgucrImageKsGammas	窶｢ﾂ｡�ｽ窶�CMM+CMY+NOT+BG/UCR+PureBlack+USERﾆ津�PQTC+SYSTEMﾆ津�
///////////////////////////////////////////////////////////////////////////////

// CMM+CMY+BG/UCR(WiShGCR)+USERﾆ津�PQTC+SYSTEMﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrsGammas 
//Description   :Apply the Black Gradation under color Removal process
//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrsGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char ucK=0, ucC=0, ucM=0, ucY=0;
	int nTonerLimit =0;
	unsigned long RGBO = 0, RGB = 0;

	assert (nTonerLimitOn);

	//nTonerLimit = SetTonerLimit (this, nObjectKind, pLimit);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(this, pucY, pucM, pucC, nSize,
			nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
	//if (m_psCmmColor->m_lIsCmm)
	if( m_lIsCmm )
	{
		// Set profile ID
		/* m_psCmmColor->m_ulCurId = m_psCmmColor->m_ulCmmProfiles[nObjectKind];

		if (m_psCmmColor->m_ulCurId & CMM_CMYK) */
		unsigned long m_ulCurId = m_ulCmmProfiles[nObjectKind];
		if( m_ulCurId != 0 ) // Check if id!=0
		{
			if( m_ulCurId & CMM_CMYK )
			{
				// USE RGB->CMYK profile 			
				if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
												  pucC, pucM, pucY, pucK, nSize, m_ulCurId))

				{
					printf("\t[CMM-CMTK] NG Apply !!\r\n");
				}
				m_pFuncLimit(this, pucK, pucC, pucM, pucY, nSize,
				nTonerLimit, ppucGamma);
				return;

			}
			else
			{
				// Use RGB->RGB profile
				if (*pucY == 0 && *pucM == 0 && *pucY == 0)
				{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, nSize, m_ulCurId))

					{
						printf("\t[CMM-RGB] NG ApplyBgucrsGammas() !!\r\n");
					}
				}
			}
		}
	}

	RGBO = 0xffffffff;
	RGB = (*pucY);
	RGB |= ((*pucM) << 8);
	RGB |= ((*pucC) << 16);
	
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	// BG/UCR & ppucGamma
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		if (RGB != RGBO)
		{
			RGBO = RGB;	// RGB
			ucC = ~(*pucY);	// R->ucC
			ucM = ~(*pucM);	// G->ucM
			ucY = ~(*pucC);	// B->ucY
			m_pFuncGcrLimit(this, &ucK, &ucC, &ucM, &ucY,
				nTonerLimit, ppucGamma);
		}
		RGB = (*(pucY + 1));
		RGB |= ((*(pucM + 1)) << 8);
		RGB |= ((*(pucC + 1)) << 16);
		*pucK = ucK;
		*pucM = ucM;
		*pucC = ucC;
		*pucY = ucY;
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

// CMM+CMY+BG/UCR(WiShGCR)(HGR)+USERﾆ津�PQTC+SYSTEMﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrsHgrGammas 
//Description   :Apply the Black Gradation under color Removal process
//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrsHgrGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char ucK=0, ucC=0, ucM=0, ucY=0;
	int nTonerLimit =0;
	unsigned long RGBO = 0, RGB = 0;

	assert (nTonerLimitOn);

	//nTonerLimit = SetTonerLimit (this, nObjectKind, pLimit);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(this, pucY, pucM, pucC, nSize,
			nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
	if (m_lIsCmm)
	{

		// Set profile ID
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			// USE RGB->CMYK profile
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{			
				if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
								pucC, pucM, pucY, pucK, nSize, m_ulCurId))
				
				{
					printf("\t[CMM-CMTK] NG Apply !!\r\n");
				}
			}
			m_pFuncLimit(this, pucK, pucC, pucM, pucY, nSize,
				nTonerLimit, ppucGamma);
			return;

		}
		else
		{
			// Use RGB->RGB profile
			if (*pucY == 0 && *pucM == 0 && *pucY == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{
				if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
											 pucM, pucC, nSize, m_ulCurId))
				
				{
					printf("\t[CMM-RGB] NG ApplyBgucrsGammas() !!\r\n");
				}
			}
		}
	}

	RGBO = 0xffffffff;
	RGB = (*pucY);
	RGB |= ((*pucM) << 8);
	RGB |= ((*pucC) << 16);
	
	// not use User Gamma
	if ((m_pFuncGcrHgrLimit == TransGcrHgrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimitNoUserGamma;
	}
	// BG/UCR & ppucGamma
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		if (RGB != RGBO)
		{
			RGBO = RGB;	// RGB
			ucC = ~(*pucY);	// R->ucC
			ucM = ~(*pucM);	// G->ucM
			ucY = ~(*pucC);	// B->ucY
			m_pFuncGcrHgrLimit(this, &ucK, &ucC, &ucM, &ucY,
				nTonerLimit, ppucGamma);
		}
		RGB = (*(pucY + 1));
		RGB |= ((*(pucM + 1)) << 8);
		RGB |= ((*(pucC + 1)) << 16);
		*pucK = ucK;
		*pucM = ucM;
		*pucC = ucC;
		*pucY = ucY;
	}
	if (m_pFuncGcrHgrLimit == TransGcrHgrPQlimitNoUserGamma)
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimit;
	}
}

// CMM+CMY+BG/UCR(WiShGCR)+USERﾆ津�PQTC+SYSTEMﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrsGammasURF
//Description   :Apply the Black Gradation under color Removal process
//Arguments     :
//              :unsigned char *pucK:[OUT]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrsGammasURF(unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char ucK=0, ucC=0, ucM=0, ucY=0;
	int nTonerLimit =0;

	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(this, pucY, pucM, pucC, nSize,
			nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
	if (m_lIsCmm)
	{

		// Set profile ID
		m_ulCurId = m_ulCmmProfiles[nObjectKind];
		// Use RGB->RGB profile
		if (*pucY == 0 && *pucM == 0 && *pucY == 0)
		{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
		}
		else if (m_ulCurId == 0)
		{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
		}
		else
		{
			if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
										 pucM, pucC, nSize, m_ulCurId))
			
			{
				printf("\t[CMM-RGB] NG ApplyBgucrsGammas() !!\r\n");
			}
		}

	}
	// BG/UCR & ppucGamma
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++) {
		ucC = ~(*pucY);	// R->ucC
		ucM = ~(*pucM);	// G->ucM
		ucY = ~(*pucC);	// B->ucY
		m_pFuncGcrLimit(this, &ucK, &ucC, &ucM, &ucY, nTonerLimit, ppucGamma);
		*pucK = ucK;
		*pucM = ucM;
		*pucC = ucC;
		*pucY = ucY;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotBgucrsGammas 
//Description   :CMM+CMY+NOT+BG/UCR(WiShGCR)+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplySrcnotBgucrsGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	int nTonerLimit;
	
	assert (nTonerLimitOn);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
#ifdef SUPPORT_CUTTING_RGBVALUE
	/* srcnot passes CR_GRAP_SRCNOT_OFF, because there is SRCNOT processing
	   after application of the ratio. */
	ApplyRgbRatioRgb(this, pucY, pucM, pucC, nSize,
			nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			unsigned char *pucR, *pucG, *pucB;
			pucR = pucY;
			pucG = pucM;
			pucB = pucC;
			for (int nTempSize = nSize; nTempSize > 0; --nTempSize)
			{
				*pucR = (unsigned char)~(*pucR);
				*pucG = (unsigned char)~(*pucG);
				*pucB = (unsigned char)~(*pucB);
				++pucR;
				++pucG;
				++pucB;
			}
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{			
				if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
								pucC, pucM, pucY, pucK, (unsigned long)nSize, m_ulCurId))
				
				{
					printf("\t[CMM-CMTK] NG Apply !!\r\n");
				}
			}

			m_pFuncLimit(this, pucK, pucC, pucM, pucY, nSize,
				nTonerLimit, ppucGamma);
			return;
		}
		else
		{
			if (*pucY == 0 && *pucM == 0 && *pucY == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{
			if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
										 pucM, pucC, nSize, m_ulCurId))
			
			{
			printf("\t[CMM-RGB] NG ApplyBgucrsGammas() !!\r\n");
			}
			}

		}
	};

	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	
	// BG/UCR & ppucGamma
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		unsigned char ucTemp = *pucC;

		*pucC = *pucY;
		*pucY = ucTemp;
		m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY, nTonerLimit,ppucGamma);
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotBgucrsHgrGammas 
//Description   :CMM+CMY+NOT+BG/UCR(WiShGCR)(HGR)+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplySrcnotBgucrsHgrGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	int nTonerLimit;
	
	assert (nTonerLimitOn);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
#ifdef SUPPORT_CUTTING_RGBVALUE
	/* srcnot passes CR_GRAP_SRCNOT_OFF, because there is SRCNOT processing
	   after application of the ratio. */
	ApplyRgbRatioRgb(this, pucY, pucM, pucC, nSize,
			nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			unsigned char *pucR, *pucG, *pucB;
			pucR = pucY;
			pucG = pucM;
			pucB = pucC;
			for (int nTempSize = nSize; nTempSize > 0; --nTempSize)
			{
				*pucR = (unsigned char)~(*pucR);
				*pucG = (unsigned char)~(*pucG);
				*pucB = (unsigned char)~(*pucB);
				++pucR;
				++pucG;
				++pucB;
			}
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{			
				if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
								pucC, pucM, pucY, pucK, (unsigned long)nSize, m_ulCurId))
				
				{
					printf("\t[CMM-CMTK] NG Apply !!\r\n");
				}
			}

			m_pFuncLimit(this, pucK, pucC, pucM, pucY, nSize,
				nTonerLimit, ppucGamma);
			return;
		}
		else
		{
			if (*pucY == 0 && *pucM == 0 && *pucY == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{
			if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
										 pucM, pucC, nSize, m_ulCurId))
			
			{
			printf("\t[CMM-RGB] NG Apply !!\r\n");
			}
			}

		}
	};

	// not use User Gamma
	if ((m_pFuncGcrHgrLimit == TransGcrHgrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimitNoUserGamma;
	}
	
	// BG/UCR & ppucGamma
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		unsigned char ucTemp = *pucC;

		*pucC = *pucY;
		*pucY = ucTemp;
		m_pFuncGcrHgrLimit(this, pucK, pucC, pucM, pucY, nTonerLimit,ppucGamma);
	}
	if (m_pFuncGcrHgrLimit == TransGcrHgrPQlimitNoUserGamma)
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimit;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrKeepgraysGammas 
//Description   :CMM+CMY+BG/UCR(WiShGCR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrKeepgraysGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	
	// BG/UCR & ppucGamma

	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// set a value for nUsedPlane
					GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
										pucC, pucM, pucY, pucK, 1, m_ulCurId))
						
						{
						printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}

					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}
			// store to pobjColor->nUsedPlane
			//In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
		else
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// set a value for nUsedPlane
					GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, 1, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					/* CMMﾅ津｣窶堙渓eepgray窶敖ｻ窶凖ｨ */
					if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
						&& (*pucY == *pucM) && (*pucY == *pucC) )
					{
						// set a value for nUsedPlane
						GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
					}
					else
					{
						unsigned char ucTemp = *pucC;

						*pucC = (unsigned char)~*pucY;
						*pucM = (unsigned char)~*pucM;
						*pucY = (unsigned char)~ucTemp;
						m_pFuncGcrLimit(this, pucK, pucC, pucM,
							pucY, nTonerLimit, ppucGamma);
					}
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}	// size loop
			// store to pobjColor->nUsedPlane
			//In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}		// CMM_CMYK or CMM_RGB
	}
	else
	{			// CMM OFF
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				// keepgray
				// set a value for nUsedPlane
				GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				unsigned char ucTemp = *pucC;

				*pucC = (unsigned char)~*pucY;
				*pucM = (unsigned char)~*pucM;
				*pucY = (unsigned char)~ucTemp;
				m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;

			}
		}
		// store to pobjColor->nUsedPlane
		//In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16
				| ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrHgrKeepgraysGammas 
//Description   :CMM+CMY+BG/UCR(WiShGCR)(HGR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrHgrKeepgraysGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrHgrLimit == TransGcrHgrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimitNoUserGamma;
	}
	
	// BG/UCR & ppucGamma

	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// set a value for nUsedPlane
					GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
										pucC, pucM, pucY, pucK, 1, m_ulCurId))
						
						{
							printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}

					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}
			// store to pobjColor->nUsedPlane
			//In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
		else
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// set a value for nUsedPlane
					GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, nSize, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					/* CMMﾅ津｣窶堙渓eepgray窶敖ｻ窶凖ｨ */
					if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
						&& (*pucY == *pucM) && (*pucY == *pucC) )
					{
						// set a value for nUsedPlane
						GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
					}
					else
					{
						unsigned char ucTemp = *pucC;

						*pucC = (unsigned char)~*pucY;
						*pucM = (unsigned char)~*pucM;
						*pucY = (unsigned char)~ucTemp;
						m_pFuncGcrHgrLimit(this, pucK, pucC, pucM,
							pucY, nTonerLimit, ppucGamma);
					}
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}	// size loop
			// store to pobjColor->nUsedPlane
			//In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}		// CMM_CMYK or CMM_RGB
	}
	else
	{			// CMM OFF
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				// keepgray
				// set a value for nUsedPlane
				GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				unsigned char ucTemp = *pucC;

				*pucC = (unsigned char)~*pucY;
				*pucM = (unsigned char)~*pucM;
				*pucY = (unsigned char)~ucTemp;
				m_pFuncGcrHgrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;

			}
		}
		// store to pobjColor->nUsedPlane
		//In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16
				| ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrHgrLimit == TransGcrHgrPQlimitNoUserGamma)
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimit;
	}
}

// CMM+CMY+NOT+BG/UCR+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotBgucrKeepgraysGammas 
//Description   :CMM+CMY+NOT+BG/UCR+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplySrcnotBgucrKeepgraysGammas (unsigned
	char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	
	if (m_lIsCmm)
	{

		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioGray(this, pucY, 1,
							nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
					// set a value for nUsedPlane
					GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
					   because there is SRCNOT processing
					   after application of the ratio. */
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					*pucC = (unsigned char)~(*pucC);
					*pucM = (unsigned char)~(*pucM);
					*pucY = (unsigned char)~(*pucY);
					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{ 			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
												pucC, pucM, pucY, pucK, 1, m_ulCurId))

						{
							printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}	
					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));

		}
		else
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioGray(this, pucY, 1,
							nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
					// set a value for nUsedPlane
					GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
					   because there is SRCNOT processing
					   after application of the ratio. */
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
						if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
													 pucM, pucC, 1, m_ulCurId))
						
						{
							printf("\t[CMM-RGB] NG Apply !!\r\n");
						}
					}

					/* CMMﾅ津｣窶堙渓eepgray窶敖ｻ窶凖ｨ */
					if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
						&& (*pucY == *pucM) && (*pucY == *pucC) )
					{
						// set a value for nUsedPlane
						GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
					}
					else
					{
						// GCR, srcnot
						unsigned char ucTemp = *pucC;

						*pucC = *pucY;
						*pucY = ucTemp;
						m_pFuncGcrLimit(this, pucK, pucC, pucM,
							pucY, nTonerLimit, ppucGamma);
						// set a value for nUsedPlane
						ucKp |= *pucK;
						ucCp |= *pucC;
						ucMp |= *pucM;
						ucYp |= *pucY;
					}
				}
			}
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
	}
	else
	{			// is_cmm = OFF
		// BG/UCR & ppucGamma
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this, pucY, 1,
						nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
				// keepgray, srcnot
				// set a value for nUsedPlane
				GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
				   because there is SRCNOT processing
				   after application of the ratio. */
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				// GCR, srcnot
				unsigned char ucTemp = *pucC;

				*pucC = *pucY;
				*pucY = ucTemp;
				m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);
				//	set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
		}
		// store to pobjColor->nUsedPlane
		// In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16
				| ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

// CMM+CMY+NOT+BG/UCR(HGR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotBgucrHgrKeepgraysGammas 
//Description   :CMM+CMY+NOT+BG/UCR(HGR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplySrcnotBgucrHgrKeepgraysGammas (unsigned
	char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrHgrLimit == TransGcrHgrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimitNoUserGamma;
	}
	
	if (m_lIsCmm)
	{

		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioGray(this, pucY, 1,
							nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
					// set a value for nUsedPlane
					GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
					   because there is SRCNOT processing
					   after application of the ratio. */
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					*pucC = (unsigned char)~(*pucC);
					*pucM = (unsigned char)~(*pucM);
					*pucY = (unsigned char)~(*pucY);
					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{ 			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
										pucC, pucM, pucY, pucK, 1, m_ulCurId))

						{
							printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}	
					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));

		}
		else
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == *pucM && *pucY == *pucC)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioGray(this, pucY, 1,
							nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
					// set a value for nUsedPlane
					GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
					   because there is SRCNOT processing
					   after application of the ratio. */
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
							nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, nSize, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					/* CMMﾅ津｣窶堙渓eepgray窶敖ｻ窶凖ｨ */
					if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
						&& (*pucY == *pucM) && (*pucY == *pucC) )
					{
						// set a value for nUsedPlane
						GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
					}
					else
					{
						// GCR, srcnot
						unsigned char ucTemp = *pucC;

						*pucC = *pucY;
						*pucY = ucTemp;
						m_pFuncGcrHgrLimit(this, pucK, pucC, pucM,
							pucY, nTonerLimit, ppucGamma);
						// set a value for nUsedPlane
						ucKp |= *pucK;
						ucCp |= *pucC;
						ucMp |= *pucM;
						ucYp |= *pucY;
					}
				}
			}
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
	}
	else
	{			// is_cmm = OFF
		// BG/UCR & ppucGamma
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this, pucY, 1,
						nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
				// keepgray, srcnot
				// set a value for nUsedPlane
				GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
				   because there is SRCNOT processing
				   after application of the ratio. */
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				// GCR, srcnot
				unsigned char ucTemp = *pucC;

				*pucC = *pucY;
				*pucY = ucTemp;
				m_pFuncGcrHgrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);
				//	set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
		}
		// store to pobjColor->nUsedPlane
		// In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16
				| ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrHgrLimit == TransGcrHgrPQlimitNoUserGamma)
	{
		m_pFuncGcrHgrLimit = TransGcrHgrPQlimit;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrAboutKeepgray 
//Description   :Apply the Black Gradation under color Removal process
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//              :unsigned char ucKCMY[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrAboutKeepgray (unsigned char ucRGB[],
	unsigned char ucKCMY[])
{
	unsigned char R, G, B;
	unsigned char ucResult;

	R = ucRGB[0];
	G = ucRGB[1];
	B = ucRGB[2];

	if ((CR_GRAYABS (R - G) <= CR_GRAY_ABOUTRANGE) &&
		(CR_GRAYABS (G - B) <= CR_GRAY_ABOUTRANGE) &&
		(CR_GRAYABS (B - R) <= CR_GRAY_ABOUTRANGE))
	{

		if (R == G)
		{
			ucResult = R;
		}
		else if (G == B)
		{
			ucResult = G;
		}
		else
		{
			ucResult = B;
		}

		ucKCMY[0] = ~ucResult;
		ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
		return;
	}

	if (m_lIsCmm)
	{
		if (m_ulCurId & CMM_CMYK)
		{
#ifdef X86
			unsigned long tmprgb;
#endif // X86	
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			unsigned long *rgbdata  = (unsigned long *) ucRGB;
            unsigned long *kcmydata = (unsigned long *) ucKCMY;
#ifdef X86
			tmprgb = *rgbdata;
			tmprgb = LSWAP (tmprgb);
#endif // X86
#ifdef X86
			if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, &tmprgb,
							kcmydata, 1, m_ulCurId))
			{
#else // X86
			if (CMM_DoConversion4_padding_kcmy (m_lIsCmm, rgbdata,
							kcmydata, 1, m_ulCurId))
			{
#endif // X86
			printf ("\t[CMM-padding]ERROR ");
			}
#ifdef X86
			*kcmydata = LSWAP (*kcmydata);
#endif // X86
			}
			return;
		}
		else
		{
#ifdef X86
			if (*ucRGB == 0 || *ucRGB == FULLX86)
			{
#else
			if (*ucRGB == 0 || *ucRGB == FULL)
			{
#endif // X86
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-padding]SKIP ");
#endif
			}
			else
			{
			unsigned long *rgbdata  = (unsigned long *) ucRGB;
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			if (CMM_DoConversion4_padding (m_lIsCmm, rgbdata, rgbdata, 1,
							m_ulCurId))
			{
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}
#ifdef X86
			*rgbdata = LSWAP (*rgbdata);
#endif // X86
			}

			/* CMMﾅ津｣窶堙径bout keepgray窶敖ｻ窶凖ｨ */
			if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
				 && (CR_GRAYABS (ucRGB[0] - ucRGB[1]) <=
						CR_GRAY_ABOUTRANGE) &&
					(CR_GRAYABS (ucRGB[1] - ucRGB[2]) <=
						CR_GRAY_ABOUTRANGE) &&
					(CR_GRAYABS (ucRGB[2] - ucRGB[0]) <=
						CR_GRAY_ABOUTRANGE) )
			{

				if (R == G)
				{
					ucResult = R;
				}
				else if (G == B)
				{
					ucResult = G;
				}
				else
				{
					ucResult = B;
				}

				ucKCMY[0] = ~ucResult;
				ucKCMY[1] = ucKCMY[2] = ucKCMY[3] = 0;
				return;
			}
		}
	}
	m_pFuncGcr(this, 255 - R, 255 - G, 255 - B, ucKCMY);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrMaybeKeepgraysGammas 
//Description   :CMM+CMY+BG/UCR(WiShGCR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrMaybeKeepgraysGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	//nTonerLimit = SetTonerLimit (this, nObjectKind, pLimit);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if ((m_ulGrayCount >= (unsigned long)m_usGrayHistory)
					&& (*pucY == *pucM && *pucY == *pucC))
				{
					// maybe keepgray
					// set a value for nUsedPlane
					GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
					m_ulGrayCount++;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);
				}
				else
				{

					if (*pucY != *pucM || *pucY != *pucC)
						m_ulGrayCount = 0;
					else
						m_ulGrayCount++;


					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
													pucC, pucM, pucY, pucK, 1, m_ulCurId))
						
						{
							printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}


					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);

					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}	// size loop
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
		else
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if ((m_ulGrayCount >= (unsigned long)m_usGrayHistory)
					&& (*pucY == *pucM && *pucY == *pucC))
				{
					// maybe keepgray
					// set a value for nUsedPlane
					GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
					m_ulGrayCount++;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);
				}
				else
				{
					unsigned char ucTemp;

					if (*pucY != *pucM || *pucY != *pucC)
						m_ulGrayCount = 0;
					else
						m_ulGrayCount++;

					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, nSize, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					ucTemp = *pucC;
					*pucC = (unsigned char)~*pucY;
					*pucM = (unsigned char)~*pucM;
					*pucY = (unsigned char)~ucTemp;
					m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}	// size loop
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
	}
	else
	{			// CMM OFF
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if ((m_ulGrayCount >= (unsigned long)m_usGrayHistory)
				&& (*pucY == *pucM && *pucY == *pucC))
			{
				// maybe keepgray
				// set a value for nUsedPlane
				GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				m_ulGrayCount++;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0 &&
					pucGtY[0] == 0);
			}
			else
			{
				unsigned char ucTemp;

				if (*pucY != *pucM || *pucY != *pucC)
					m_ulGrayCount = 0;
				else
					m_ulGrayCount++;

				ucTemp = *pucC;
				*pucC = (unsigned char)~*pucY;
				*pucM = (unsigned char)~*pucM;
				*pucY = (unsigned char)~ucTemp;
				m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
		}	// size loop
		// store to pobjColor->nUsedPlane
		//	In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16
				| ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

// CMM+CMY+BG/UCR+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrAboutKeepgraysGammas 
//Description   :Apply the Black Gradation under color Removal process
//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrAboutKeepgraysGammas (unsigned
	char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	unsigned char *pucUserGtK;
	unsigned char ucResult;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;
	int nTonerLimit;
	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];
	pucUserGtK = ppucGt[4];
	
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	
	// BG/UCR & ppucGamma

	if (m_lIsCmm)
	{			// CMM ON
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if ((CR_GRAYABS (*pucC - *pucM) <=
						CR_GRAY_ABOUTRANGE) &&
					(CR_GRAYABS (*pucM - *pucY) <=
						CR_GRAY_ABOUTRANGE) &&
					(CR_GRAYABS (*pucY - *pucC) <=
						CR_GRAY_ABOUTRANGE))
				{
					if (*pucC == *pucM)
						ucResult = *pucC;
					else if (*pucM == *pucY)
						ucResult = *pucM;
					else
						ucResult = *pucY;
					
					*pucK = ~ucResult;
					ApplyUserGammas(pucUserGtK, 1, pucK);
					*pucK = pucGtK[*pucK];
					*pucC = 0;
					*pucM = 0;
					*pucY = 0;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);

					// set a value for nUsedPlane
					ucKp |= *pucK;
				}
				else
				{
					// RGB -> R'G'B' -> CMYK
					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
													pucC, pucM, pucY, pucK, 1, m_ulCurId))
						
						{
							printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}

					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}	// size loop
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
		else
		{	// Use RGB->RGB profile
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				// about keepgray
				if ((CR_GRAYABS (*pucC - *pucM) <=
						CR_GRAY_ABOUTRANGE) &&
					(CR_GRAYABS (*pucM - *pucY) <=
						CR_GRAY_ABOUTRANGE) &&
					(CR_GRAYABS (*pucY - *pucC) <=
						CR_GRAY_ABOUTRANGE))
				{
					if (*pucC == *pucM)
						ucResult = *pucC;
					else if (*pucM == *pucY)
						ucResult = *pucM;
					else
						ucResult = *pucY;
					*pucK = ~ucResult;
					ApplyUserGammas(pucUserGtK, 1, pucK);
					*pucK = pucGtK[*pucK];
					*pucC = 0;
					*pucM = 0;
					*pucY = 0;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);

					// set a value for nUsedPlane
					ucKp |= *pucK;
				}
				else
				{
					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, 1, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					if ((CR_GRAYABS(*pucC - *pucM) <= CR_GRAY_ABOUTRANGE) &&
						(CR_GRAYABS(*pucM - *pucY) <= CR_GRAY_ABOUTRANGE) &&
						(CR_GRAYABS(*pucY - *pucC) <= CR_GRAY_ABOUTRANGE))
					{

						if (*pucC == *pucM)
							ucResult = *pucC;
						else if (*pucM == *pucY)
							ucResult = *pucM;
						else
							ucResult = *pucY;

						*pucK = ~ucResult;
						ApplyUserGammas(pucUserGtK, 1, pucK);
						*pucK = pucGtK[*pucK];
						*pucC = 0;
						*pucM = 0;
						*pucY = 0;;
						assert(pucGtC[0] == 0 && pucGtM[0]
							== 0 && pucGtY[0] == 0);

						// set a value for nUsedPlane
						ucKp |= *pucK;
					}
					else
					{
						unsigned char ucTemp = *pucC;

						*pucC = (unsigned char)~*pucY;
						*pucM = (unsigned char)~*pucM;
						*pucY = (unsigned char)~ucTemp;
						m_pFuncGcrLimit(this, pucK, pucC, pucM,
							pucY, nTonerLimit, ppucGamma);
						// set a value for nUsedPlane
						ucKp |= *pucK;
						ucCp |= *pucC;
						ucMp |= *pucM;
						ucYp |= *pucY;
					}
				}
			}	// size loop
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
	}
	else
	{			// CMM OFF
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			// about keepgray
			if ((CR_GRAYABS (*pucC - *pucM) <=
					CR_GRAY_ABOUTRANGE) &&
				(CR_GRAYABS (*pucM - *pucY) <=
					CR_GRAY_ABOUTRANGE) &&
				(CR_GRAYABS (*pucY - *pucC) <=
					CR_GRAY_ABOUTRANGE))
			{
				if (*pucC == *pucM)
					ucResult = *pucC;
				else if (*pucM == *pucY)
					ucResult = *pucM;
				else
					ucResult = *pucY;

				*pucK = ~ucResult;
				ApplyUserGammas(pucUserGtK, 1, pucK);
				*pucK = pucGtK[*pucK];
				*pucC = 0;
				*pucM = 0;
				*pucY = 0;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0 &&
					pucGtY[0] == 0);

				// set a value for nUsedPlane
				ucKp |= *pucK;
			}
			else
			{
				unsigned char ucTemp = *pucC;

				*pucC = (unsigned char)~*pucY;
				*pucM = (unsigned char)~*pucM;
				*pucY = (unsigned char)~ucTemp;

				m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);

				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
		}	// size loop
		// store to pobjColor->nUsedPlane
		//	In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16
				| ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrImageKsGammas 
//Description   :CMM+CMY+BG/UCR(WiShGCR)+PureBlack+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrImageKsGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	unsigned char *pucUserGtK;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];
	pucUserGtK = ppucGt[4];
	
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	
	// BG/UCR & ppucGamma

	if (m_lIsCmm)
	{			// CMM ON

		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == 0 && *pucM == 0 && *pucC == 0)
				{
					*pucK = 255;
					ApplyUserGammas(pucUserGtK, 1, pucK);
					*pucK = pucGtK[*pucK];
					*pucC = 0;
					*pucM = 0;
					*pucY = 0;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);

					// set a value for nUsedPlane
					ucKp |= *pucK;
				}
				else
				{
					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
													pucC, pucM, pucY, pucK, 1, m_ulCurId))
						
						{
							printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}

					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			} // size loop
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
		else
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == 0 && *pucM == 0 && *pucC == 0)
				{
					*pucK = 255;
					ApplyUserGammas(pucUserGtK, 1, pucK);
					*pucK = pucGtK[*pucK];
					*pucC = 0;
					*pucM = 0;
					*pucY = 0;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);

					// set a value for nUsedPlane
					ucKp |= *pucK;
				}
				else
				{
					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, 1, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					/* CMMﾅ津｣窶堙渓eepblack窶敖ｻ窶凖ｨ */
					if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
						&& (*pucY == 0) && (*pucM == 0) && (*pucC == 0) )
					{
						*pucK = 255;
						ApplyUserGammas(pucUserGtK, 1, pucK);
						*pucK = pucGtK[*pucK];
						*pucC = 0;
						*pucM = 0;
						*pucY = 0;;
						assert(pucGtC[0] == 0 && pucGtM[0]
							== 0 && pucGtY[0] == 0);

						// set a value for nUsedPlane
						ucKp |= *pucK;
					}
					else
					{
						unsigned char ucTemp = *pucC;

						*pucC = (unsigned char)~*pucY;
						*pucM = (unsigned char)~*pucM;
						*pucY = (unsigned char)~ucTemp;
						m_pFuncGcrLimit(this, pucK, pucC, pucM,
							pucY, nTonerLimit, ppucGamma);
						// set a value for nUsedPlane
						ucKp |= *pucK;
						ucCp |= *pucC;
						ucMp |= *pucM;
						ucYp |= *pucY;
					}
				}
			}
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}		// CMM_CMYK or CMM_RGB
	}
	else
	{			// CMM OFF
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == 0 && *pucM == 0 && *pucC == 0)
			{
				*pucK = 255;
				ApplyUserGammas(pucUserGtK, 1, pucK);
				*pucK = pucGtK[*pucK];
				*pucC = 0;
				*pucM = 0;
				*pucY = 0;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0 &&
					pucGtY[0] == 0);

				// set a value for nUsedPlane
				ucKp |= *pucK;
			}
			else
			{
				unsigned char ucTemp = *pucC;

				*pucC = (unsigned char)~*pucY;
				*pucM = (unsigned char)~*pucM;
				*pucY = (unsigned char)~ucTemp;
				m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
		}	// size loop
		// store to pobjColor->nUsedPlane
		//	In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16 | ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotBgucrImageKsGammas 
//Description   :CMM+CMY+NOT+BG/UCR(WiShGCR)+PureBlack+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplySrcnotBgucrImageKsGammas (unsigned char
	*pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC, *pucGtM, *pucGtY;
	unsigned char *pucUserGtK;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;
	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];
	pucUserGtK = ppucGt[4];
	
	assert (pucGtK && pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}
	
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{
			// BG/UCR & ppucGamma
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				*pucC = (unsigned char)~(*pucC);
				*pucM = (unsigned char)~(*pucM);
				*pucY = (unsigned char)~(*pucY);
				if (*pucY == 0 && *pucM == 0 && *pucC == 0)
				{
					// pureblack, srcnot
					*pucK = 255;
					ApplyUserGammas(pucUserGtK, 1, pucK);
					*pucK = pucGtK[*pucK];
					*pucC = 0;
					*pucM = 0;
					*pucY = 0;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);
					// set a value for nUsedPlane
					ucKp |= *pucK;
				}
				else
				{
					if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{ 			
						if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
														pucC, pucM, pucY, pucK, 1, m_ulCurId))

						{
							printf("\t[CMM-CMTK] NG Apply !!\r\n");
						}
					}	
					m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
						nTonerLimit, ppucGamma);
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;

				}	// keepgray

			}	// size loop
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}
		else
		{
			// BG/UCR & ppucGamma
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if (*pucY == 0 && *pucM == 0 && *pucC == 0)
				{
					// pureblack, srcnot
					*pucK = 0;
					ApplyUserGammas(pucUserGtK, 1, pucK);
					*pucK = pucGtK[*pucK];
					*pucC = 0;
					*pucM = 0;
					*pucY = 0;;
					assert(pucGtC[0] == 0 && pucGtM[0] == 0
						&& pucGtY[0] == 0);
					// set a value for nUsedPlane
					ucKp |= *pucK;
				}
				else
				{
					if (*pucY == 0 && *pucM == 0 && *pucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
												 pucM, pucC, 1, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					/* CMMﾅ津｣窶堙渓eepblack窶敖ｻ窶凖ｨ */
					if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
						&& (*pucY == 0) && (*pucM == 0) && (*pucC == 0) )
					{
						// pureblack, srcnot
						*pucK = 0;
						ApplyUserGammas(pucUserGtK, 1, pucK);
						*pucK = pucGtK[*pucK];
						*pucC = 0;
						*pucM = 0;
						*pucY = 0;;
						assert(pucGtC[0] == 0 && pucGtM[0]
							== 0 && pucGtY[0] == 0);
						// set a value for nUsedPlane
						ucKp |= *pucK;
					}
					else
					{
						unsigned char ucTemp;

						ucTemp = *pucC;
						*pucC = *pucY;
						*pucY = ucTemp;
						m_pFuncGcrLimit(this, pucK, pucC, pucM,
							pucY, nTonerLimit, ppucGamma);
						// set a value for nUsedPlane
						ucKp |= *pucK;
						ucCp |= *pucC;
						ucMp |= *pucM;
						ucYp |= *pucY;
					}
				}
			}
			// store to pobjColor->nUsedPlane
			//	In PRImage.cpp it's added to Used_plane
			m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
					16 | ucMp << 8 | ucYp));
		}		// CMM_CMYK or CMM_RGB
	}
	else
	{	// is_cmm = OFF
		// BG/UCR & ppucGamma
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == 0 && *pucM == 0 && *pucC == 0)
			{
				// pureblack, srcnot
				*pucK = 0;
				ApplyUserGammas(pucUserGtK, 1, pucK);
				*pucK = pucGtK[*pucK];
				*pucC = 0;
				*pucM = 0;
				*pucY = 0;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0 &&
					pucGtY[0] == 0);
				// set a value for nUsedPlane
				ucKp |= *pucK;
			}
			else
			{
				unsigned char ucTemp;

				ucTemp = *pucC;
				*pucC = *pucY;
				*pucY = ucTemp;
				m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
					nTonerLimit, ppucGamma);
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
		} // size loop
		// store to pobjColor->nUsedPlane
		//	In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP ((ucKp << 24 | ucCp << 16
				| ucMp << 8 | ucYp));
	}
	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

#ifdef SUPPORT_COMPOSITEBLACK
// CMM+CMY+COMPBK+PQTC+SYSTEMﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrCompbksGammas
//Description   :Apply the Black Gradation under color Removal process
//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrCompbksGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char ucTmpB;
	int nTonerLimit;

	assert (nTonerLimitOn);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);

	if (m_ucRenderingIsmono)
	{
		int nTmpSize = nSize;
		unsigned char *pucTmpR = pucY, *pucTmpG = pucM, *pucTmpB = pucC;
		unsigned char ucK = 0, ucC = 0, ucM = 0, ucY = 0;
		unsigned long RGBO, RGB;
		unsigned int nGray;

		/* RGB -> GRAY -> RGB */
		for (; nTmpSize > 0; nTmpSize--, pucTmpR++, pucTmpG++, pucTmpB++)
		{
			nGray = (*pucTmpR * ICL_WR + *pucTmpG * ICL_WG + *pucTmpB * IC_WB)
				/ IC_WBIAS;
			if (nGray > 255)
			{
				nGray = 255;
			}
			*pucTmpR = *pucTmpG = *pucTmpB = nGray;
		}
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgbRatioRgbCompbk(this, pucY, pucM, pucC, nSize,
				nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
		if (m_lIsCmm)
		{
			// Set profile ID
			m_ulCurId =
				m_ulCmmProfilesCompbk[nObjectKind];

			if (m_ulCurId & CMM_CMYK)
			{
				// USE RGB->CMYK profile
				if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{			
					if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
									pucC, pucM, pucY, pucK, (unsigned long)nSize, m_ulCurId))
					
					{
						printf("\t[CMM-CMTK] NG Apply !!\r\n");
					}
				}

				m_pFuncLimit(this, pucK, pucC, pucM, pucY, nSize,
					nTonerLimit, ppucGamma);
				return;

			}	
			else
			{
				// Use RGB->RGB profile
				if (*pucY == 0 && *pucM == 0 && *pucY == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{
				if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
											 pucM, pucC, nSize, m_ulCurId))
				
				{
				printf("\t[CMM-RGB] NG Apply !!\r\n");
				}
				}

			}
		}

		RGBO = 0xffffffff;
		RGB = (*pucY);
		RGB |= ((*pucM) << 8);
		RGB |= ((*pucC) << 16);

		// BG/UCR & ppucGamma
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (RGB != RGBO)
			{
				RGBO = RGB;	// RGB
				ucC = ~(*pucY);	// R->ucC
				ucM = ~(*pucM);	// G->ucM
				ucY = ~(*pucC);	// B->ucY
				m_pFuncGcrLimitCompbk(this, &ucK, &ucC, &ucM, &ucY,
					nTonerLimit, ppucGamma);
			}
			RGB = (*(pucY + 1));
			RGB |= ((*(pucM + 1)) << 8);
			RGB |= ((*(pucC + 1)) << 16);
			*pucK = ucK;
			*pucM = ucM;
			*pucC = ucC;
			*pucY = ucY;
		}
	}
	else	/* color print */
	{
		if (m_lIsCmm)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if ((*pucY == *pucM) && (*pucY == *pucC))
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgbCompbk(this, pucY, pucM, pucC, nSize,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// Set profile ID
					m_ulCurId =
						m_ulCmmProfilesCompbk[nObjectKind];

					if (m_ulCurId & CMM_CMYK)
					{
						// USE RGB->CMYK profile
						if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
							printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{			
							if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
											pucC, pucM, pucY, pucK, 1, m_ulCurId))
							
							{
								printf("\t[CMM-CMTK] NG Apply !!\r\n");
							}
						}

						m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
							nTonerLimit, ppucGamma);
					}	
					else
					{
						// Use RGB->RGB profile
						if (*pucY == 0 && *pucM == 0 && *pucY == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{
						if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
													 pucM, pucC, 1, m_ulCurId))
						
						{
						printf("\t[CMM-RGB] NG Apply !!\r\n");
						}
						}


						ucTmpB = *pucC;
						*pucC = ~(*pucY);	// R->*pucC
						*pucM = ~(*pucM);	// G->*pucM
						*pucY = ~(ucTmpB);	// B->*pucY
						m_pFuncGcrLimitCompbk(this, pucK, pucC, pucM, pucY,
							nTonerLimit, ppucGamma);
					}
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// Set profile ID
					m_ulCurId =
						m_ulCmmProfiles[nObjectKind];

					if (m_ulCurId & CMM_CMYK)
					{
						// USE RGB->CMYK profile
						if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
							printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{			
							if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
											pucC, pucM, pucY, pucK, 1, m_ulCurId))
							
							{
								printf("\t[CMM-CMTK] NG Apply !!\r\n");
							}
						}


						m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
							nTonerLimit, ppucGamma);
					}	
					else
					{
						// Use RGB->RGB profile
						if (*pucY == 0 && *pucM == 0 && *pucY == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{
						if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
													 pucM, pucC, 1, m_ulCurId))
						
						{
						printf("\t[CMM-RGB] NG Apply !!\r\n");
						}
						}


						ucTmpB = *pucC;
						*pucC = ~(*pucY);	// R->*pucC
						*pucM = ~(*pucM);	// G->*pucM
						*pucY = ~(ucTmpB);	// B->*pucY
						m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
							nTonerLimit, ppucGamma);
					}
				}
			}
		}
		else	/* CMM_OFF */
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if ((*pucY == *pucM) && (*pucY == *pucC))
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgbCompbk(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					ucTmpB = *pucC;
					*pucC = ~(*pucY);	// R->*pucC
					*pucM = ~(*pucM);	// G->*pucM
					*pucY = ~(ucTmpB);	// B->*pucY
					m_pFuncGcrLimitCompbk(this, pucK, pucC, pucM, pucY,
						nTonerLimit, ppucGamma);
				}	
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					ucTmpB = *pucC;
					*pucC = ~(*pucY);	// R->*pucC
					*pucM = ~(*pucM);	// G->*pucM
					*pucY = ~(ucTmpB);	// B->*pucY
					m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
						nTonerLimit, ppucGamma);
				}
			}
		}
	}
}

// CMM+CMY+NOT+COMPBK+PQTC+ﾆ津�///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotBgucrCompbksGammas
//Description   :Apply the Black Gradation under color Removal process
//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplySrcnotBgucrCompbksGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char ucTmpB;
	int nTonerLimit;

	assert (nTonerLimitOn);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);

	if (m_ucRenderingIsmono)
	{
		int nTmpSize = nSize;
		unsigned char *pucTmpR = pucY, *pucTmpG = pucM, *pucTmpB = pucC;
		unsigned int nGray;

		/* RGB -> GRAY -> RGB */
		for (; nTmpSize > 0; nTmpSize--, pucTmpR++, pucTmpG++, pucTmpB++)
		{
			nGray = (*pucTmpR * ICL_WR + *pucTmpG * ICL_WG + *pucTmpB * IC_WB)
				/ IC_WBIAS;
			if (nGray > 255)
			{
				nGray = 255;
			}
			*pucTmpR = *pucTmpG = *pucTmpB = nGray;
		}
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgbRatioRgbCompbk(this, pucY, pucM, pucC, nSize,
				nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
		if (m_lIsCmm)
		{
			// Set profile ID
			m_ulCurId =
				m_ulCmmProfilesCompbk[nObjectKind];

			if (m_ulCurId & CMM_CMYK)
			{
				unsigned char *pucR, *pucG, *pucB;
				pucR = pucY;
				pucG = pucM;
				pucB = pucC;
				for (int nTempSize = nSize; nTempSize > 0; --nTempSize)
				{
					*pucR = (unsigned char)~(*pucR);
					*pucG = (unsigned char)~(*pucG);
					*pucB = (unsigned char)~(*pucB);
					++pucR;
					++pucG;
					++pucB;
				}
				if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{			
					if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
									pucC, pucM, pucY, pucK, (unsigned long)nSize, m_ulCurId))
					
					{
						printf("\t[CMM-CMTK] NG Apply !!\r\n");
					}
				}

				m_pFuncLimit(this, pucK, pucC, pucM, pucY, nSize,
					nTonerLimit, ppucGamma);
				return;
			}	
			else
			{
				// Use RGB->RGB profile
				if (*pucY == 0 && *pucM == 0 && *pucY == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{
				if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
											 pucM, pucC, nSize, m_ulCurId))
				
				{
				printf("\t[CMM-RGB] NG Apply !!\r\n");
				}
				}

			}
		}

		// BG/UCR & ppucGamma
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			ucTmpB = *pucC;
			*pucC = *pucY;
			*pucY = ucTmpB;
			m_pFuncGcrLimitCompbk(this, pucK, pucC, pucM, pucY,
				nTonerLimit, ppucGamma);
		}
	}
	else	/* color print */
	{
		if (m_lIsCmm)
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if ((*pucY == *pucM) && (*pucY == *pucC))
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgbCompbk(this, pucY, pucM, pucC, nSize,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// Set profile ID
					m_ulCurId =
						m_ulCmmProfilesCompbk[nObjectKind];

					if (m_ulCurId & CMM_CMYK)
					{
						*pucC = (unsigned char)~(*pucC);
						*pucM = (unsigned char)~(*pucM);
						*pucY = (unsigned char)~(*pucY);
						if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
							printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{			
							if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
											pucC, pucM, pucY, pucK, 1, m_ulCurId))
							
							{
								printf("\t[CMM-CMTK] NG Apply !!\r\n");
							}
						}

						m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
							nTonerLimit, ppucGamma);
					}	
					else
					{
						// Use RGB->RGB profile
						if (*pucY == 0 && *pucM == 0 && *pucY == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{
						if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
													 pucM, pucC, 1, m_ulCurId))
						
						{
						printf("\t[CMM-RGB] NG Apply !!\r\n");
						}
						}

						ucTmpB = *pucC;
						*pucC = *pucY;
						*pucY = ucTmpB;
						m_pFuncGcrLimitCompbk(this, pucK, pucC, pucM, pucY,
							nTonerLimit, ppucGamma);
					}
				}
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					// Set profile ID
					m_ulCurId =
						m_ulCmmProfiles[nObjectKind];

					if (m_ulCurId & CMM_CMYK)
					{
						*pucC = (unsigned char)~(*pucC);
						*pucM = (unsigned char)~(*pucM);
						*pucY = (unsigned char)~(*pucY);
						if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
							printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{			
							if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
											pucC, pucM, pucY, pucK, 1, m_ulCurId))
							
							{
								printf("\t[CMM-CMTK] NG Apply !!\r\n");
							}
						}


						m_pFuncLimit(this, pucK, pucC, pucM, pucY, 1,
							nTonerLimit, ppucGamma);
					}	
					else
					{
						// Use RGB->RGB profile
						if (*pucY == 0 && *pucM == 0 && *pucY == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else if (m_ulCurId == 0)
						{
#ifdef DEBUGCMM
						printf ("\t[CMM-plane]SKIP ");
#endif
						}
						else
						{
						if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
													 pucM, pucC, 1, m_ulCurId))
						
						{
						printf("\t[CMM-RGB] NG Apply !!\r\n");
						}
						}

						ucTmpB = *pucC;
						*pucC = *pucY;
						*pucY = ucTmpB;
						m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
							nTonerLimit, ppucGamma);
					}
				}
			}
		}
		else	/* CMM_OFF */
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
			{
				if ((*pucY == *pucM) && (*pucY == *pucC))
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgbCompbk(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					ucTmpB = *pucC;
					*pucC = *pucY;
					*pucY = ucTmpB;
					m_pFuncGcrLimitCompbk(this, pucK, pucC, pucM, pucY,
						nTonerLimit, ppucGamma);
				}	
				else
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
					ucTmpB = *pucC;
					*pucC = *pucY;
					*pucY = ucTmpB;
					m_pFuncGcrLimit(this, pucK, pucC, pucM, pucY,
						nTonerLimit, ppucGamma);
				}
			}
		}
	}
}
#endif /* SUPPORT_COMPOSITEBLACK */

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyRgb2CmyGammas 
//Description   :CMM+CMY+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyRgb2CmyGammas (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char ucC = 0, ucM = 0, ucY = 0;
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtC, *pucGtM, *pucGtY;
	unsigned char *pucUserGtC, *pucUserGtM, *pucUserGtY;
	int nTonerLimit;
	int nSumCMYK;
	unsigned char ucCp, ucMp, ucYp;
	unsigned char RO, GO = 0, BO = 0;

	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];
		if (m_ulCurId & CMM_CMYK)
		{;
			assert (FALSE);
		}
		else
		{
			if (*pucY == 0 && *pucM == 0 && *pucY == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{
			if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
										 pucM, pucC, nSize, m_ulCurId))
			
			{
			printf("\t[CMM-RGB] NG Apply !!\r\n");
			}
			}

		}
	}

	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	pucUserGtC = ppucGamma[5];
	pucUserGtM = ppucGamma[6];
	pucUserGtY = ppucGamma[7];
	
	assert (pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	//nTonerLimit = SetTonerLimit (this, nObjectKind, pLimit);
	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);

	RO = (unsigned char) (~*pucY);

	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		if (m_nIsPqtc)
		{	// m_nIsPqtc
			if (*pucY != RO || *pucM != GO || *pucC != BO)
			{
				RO = *pucY;	// R
				GO = *pucM;	// G
				BO = *pucC;	// B
				// RGB -> CMY
				ucC = ~RO;	// Cyan = ~Red
				ucM = ~GO;	// Mazenta = ~Green
				ucY = ~BO;	// Yellow = ~Blue
				
				ApplyUserGammas(pucUserGtC, 1, &ucC);
				ApplyUserGammas(pucUserGtM, 1, &ucM);
				ApplyUserGammas(pucUserGtY, 1, &ucY);
				
				ucCp = m_pucPqTbl[ucC];
				ucMp = m_pucPqTbl[ucM];
				ucYp = m_pucPqTbl[ucY];
				nSumCMYK = ucCp + ucMp + ucYp;
				if (nSumCMYK > nTonerLimit)
				{
					TONER_LIMIT_CMY (nTonerLimit,
						nSumCMYK, ucCp, ucMp, ucYp);
					ucC = m_pucRPqTbl[ucCp];
					ucM = m_pucRPqTbl[ucMp];
					ucY = m_pucRPqTbl[ucYp];
				}
				ucC = pucGtC[ucC];
				ucM = pucGtM[ucM];
				ucY = pucGtY[ucY];
			}
		}
		else
		{	// m_nIsPqtc
			// RGB -> CMY(+ppucGamma)
			ucC = pucGtC[(unsigned char) ~*pucY];
			ucM = pucGtM[(unsigned char) ~*pucM];
			ucY = pucGtY[(unsigned char) ~*pucC];
			nSumCMYK = ucC + ucM + ucY;
			if (nSumCMYK > nTonerLimit)
			{
				TONER_LIMIT_CMY (nTonerLimit,
					nSumCMYK, ucC, ucM, ucY);
			}
		}	// m_nIsPqtc
		*pucK = 0;
		*pucM = ucM;
		*pucC = ucC;
		*pucY = ucY;
	}		// for loop
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotRgb2CmyGammas 
//Description   :CMM+CMY+NOT+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
void CPRColor::
ApplySrcnotRgb2CmyGammas (
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char ucC, ucM, ucY;
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtC, *pucGtM, *pucGtY;
	unsigned char *pucUserGtC, *pucUserGtM, *pucUserGtY;
	int nTonerLimit;
	int nSumCMYK;
	unsigned char ucCp, ucMp, ucYp;
	unsigned char *pucPQTable = m_pucPqTbl;
	unsigned char *pucRPQTable = m_pucRPqTbl;
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];

		if (m_ulCurId & CMM_CMYK)
		{;
			assert (FALSE);

		}
		else
		{
			if (*pucY == 0 && *pucM == 0 && *pucY == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{
			if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
										 pucM, pucC, nSize, m_ulCurId))
			
			{
			printf("\t[CMM-RGB] NG Apply !!\r\n");
			}
			}

		}
	}
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	pucUserGtC = ppucGamma[5];
	pucUserGtM = ppucGamma[6];
	pucUserGtY = ppucGamma[7];
	
	assert (pucGtC && pucGtM && pucGtY);;
	assert (nTonerLimitOn);

	//nTonerLimit = SetTonerLimit (pobjColor, nObjectKind, pLimit);
	nTonerLimit =SetTonerLimitInColor(nObjectKind, pLimit);

	if (m_nIsPqtc)
	{			// m_nIsPqtc
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			// CMY, srcnot
			ucC = (unsigned char) *pucY;	// R
			ucM = (unsigned char) *pucM;	// G
			ucY = (unsigned char) *pucC;	// B
			
			ApplyUserGammas(pucUserGtC, 1, &ucC);
			ApplyUserGammas(pucUserGtM, 1, &ucM);
			ApplyUserGammas(pucUserGtY, 1, &ucY);
			
			ucCp = pucPQTable[ucC];
			ucMp = pucPQTable[ucM];
			ucYp = pucPQTable[ucY];
			nSumCMYK = ucCp + ucMp + ucYp;
			if (nSumCMYK > nTonerLimit)
			{
				TONER_LIMIT_CMY (nTonerLimit, nSumCMYK,
					ucCp, ucMp, ucYp);
				ucC = pucRPQTable[ucCp];
				ucM = pucRPQTable[ucMp];
				ucY = pucRPQTable[ucYp];
			}
			*pucK = 0;
			*pucM = pucGtM[ucM];
			*pucC = pucGtC[ucC];
			*pucY = pucGtY[ucY];
		}		// nSize loop
	}
	else
	{			// m_nIsPqtc
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			// CMY + ppucGamma, srcnot
			ucC = pucGtC[(unsigned char) *pucY];
			ucM = pucGtM[(unsigned char) *pucM];
			ucY = pucGtY[(unsigned char) *pucC];
			nSumCMYK = ucC + ucM + ucY;
			if (nSumCMYK > nTonerLimit)
			{
				TONER_LIMIT_CMY (nTonerLimit, nSumCMYK,
					ucC, ucM, ucY);
			}
			*pucK = 0;
			*pucM = ucM;
			*pucC = ucC;
			*pucY = ucY;
		}		// nSize loop
	}			// m_nIsPqtc
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyPqtc 
//Description   :Apply PQCT toner Limit
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjMode:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
ApplyPqtc (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjMode)
{
	unsigned char ucK, ucC, ucM, ucY;
	int nTonerLimit = 0;
	int nSumCMYK;
	unsigned char *pucPQTable = pobjColor->m_pucPqTbl;
	unsigned char *pucRPQTable = pobjColor->m_pucRPqTbl;;
	assert (pobjColor->m_pucPqTbl);;
	assert (pobjColor->m_pucRPqTbl);;
	assert (pobjColor->m_sPqLimit.phot);;
	assert (pobjColor->m_sPqLimit.fill);;
	assert (pobjColor->m_sPqLimit.text);;
	assert (pobjColor->m_sPqLimit.line);

	switch (nObjMode)
	{
		case CR_OBJ_IMAG:
			nTonerLimit = pobjColor->m_sPqLimit.phot;
			break;
		case CR_OBJ_GRAP:
			nTonerLimit = pobjColor->m_sPqLimit.fill;
			break;
		case CR_OBJ_TEXT:
			nTonerLimit = pobjColor->m_sPqLimit.text;
			break;
		case CR_OBJ_LINE:
			nTonerLimit = pobjColor->m_sPqLimit.line;
			break;
		default:
			assert (0);
			break;
	}
	for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
	{
		ucK = pucPQTable[*pucK];
		ucC = pucPQTable[*pucC];
		ucM = pucPQTable[*pucM];
		ucY = pucPQTable[*pucY];
		nSumCMYK = ucK + ucC + ucM + ucY;
#ifdef SUPPORT_LIMITING_K
		if (nSumCMYK > nTonerLimit)
		{
			if (nTonerLimit > ucK)
			{
				TONER_LIMIT (nTonerLimit, nSumCMYK, ucK, ucC, ucM, ucY);
				*pucC = pucRPQTable[ucC];	// convert ink drops to color
				*pucM = pucRPQTable[ucM];
				*pucY = pucRPQTable[ucY];
			}
			else
			{
				*pucK = pucRPQTable[nTonerLimit];
				*pucC = *pucM = *pucY = 0;
			}
		}
#else
		if (nSumCMYK > nTonerLimit)
		{
			TONER_LIMIT (nTonerLimit, nSumCMYK, ucK, ucC, ucM, ucY);
			*pucC = pucRPQTable[ucC];
			*pucM = pucRPQTable[ucM];
			*pucY = pucRPQTable[ucY];
		}
#endif
	}
}

#ifdef SUPPORT_CUTTING_RGBVALUE
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyRgb2Gray 
//Description   :RGB to Gray Conversion
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char ucRGB[]:[IN]
//              :int nObjMode:[IN]
//              :unsigned long ulSrcNot[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
ApplyRgb2Gray (CPRColor *pobjColor, unsigned char ucRGB[], int nObjMode,
		unsigned long ulSrcNot)
#else
///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyRgb2Gray 
//Description   :RGB to Gray Conversion
//Arguments     :
//              :unsigned char ucRGB[]:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
ApplyRgb2Gray (unsigned char ucRGB[])
#endif /* SUPPORT_CUTTING_RGBVALUE */
{
	unsigned int unG;

#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(pobjColor, &ucRGB[0], &ucRGB[1], &ucRGB[2], 1,
						nObjMode, ulSrcNot);
#endif
	unG = (ucRGB[0] * ICL_WR + ucRGB[1] * ICL_WG + ucRGB[2] *
		IC_WB) / IC_WBIAS;
	if (unG > 255)
		unG = 255;
	ucRGB[0] = 255 - unG;
	ucRGB[1] = 0;
	ucRGB[2] = 0;
	ucRGB[3] = 0;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyTwinColorGammas 
//Description   : Aplly twin color gammas.
//Arguments     :
//              :CPRColor* pobjColor:[I/O]
//              :unsigned char *pucR:[I/O]
//              :unsigned char *pucG:[I/O]
//              :unsigned char *pucB:[I/O]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :int nSize:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
ApplyTwinColorGammas (CPRColor* pobjColor,
	unsigned char *pucR,
	unsigned char *pucG,
	unsigned char *pucB,
	unsigned char *pucK,
	unsigned char *pucC,
	int nSize,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];;
	assert (pucGtK && pucGtC);

	for (; nSize > 0; nSize--, pucR++, pucG++, pucB++, pucK++, pucC++)
	{
		if (*pucR == *pucG && *pucG == *pucB)
		{
			// keepgray
#ifdef GAMMA_THROUGH
			*pucK = ~*pucR;
#else
			*pucK = pucGtK[(unsigned char) ~*pucR];;
			assert (pucGtC[0] == 0);
#endif
			*pucC = 0;
		}
		else
		{
			*pucK = 0;
#ifdef GAMMA_THROUGH
			*pucC = *pucR;
#else
			*pucC = pucGtC[*pucR];
#endif
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :MakePaletteColor 
//Description   :Create CMYK palette (color output devices)
//Arguments     :
//              :unsigned long ulFlag:[IN]
//              :unsigned char *pucIndexTable:[IN]
//              :unsigned char *pucPalette:[IN]
//              :int nGrayMode:[IN]
//              :int nTLimit:[IN]
//              :clr_tlimit_t * pVal:[IN]
//              :TRANS_FN_TYPE transfunc:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :int:Used Plane
///////////////////////////////////////////////////////////////////////////////
#ifdef PR_SUPPORT_FUSER_CTL
int
CPRColor::MakePaletteColor (unsigned long ulFlag,
	unsigned char *pucIndexTable,
	unsigned char *pucPalette,
	unsigned char ucDitherMode,
	int nGrayMode,
	int nTLimit,
	unsigned long ulArea,
	clr_tlimit_t * pVal,
	TRANS_FN_TYPE transfunc,
	unsigned char **ppucGamma,
	unsigned char *pucFuserCtl)
#else
int
CPRColor::MakePaletteColor (unsigned long ulFlag,
	unsigned char *pucIndexTable,
	unsigned char *pucPalette,
	int nGrayMode,
	int nTLimit,
	clr_tlimit_t * pVal,
	TRANS_FN_TYPE transfunc,
	unsigned char **ppucGamma)
#endif /* PR_SUPPORT_FUSER_CTL */
{
	int nPal;
	unsigned char *pucTbk, *pucTbc, *pucTbm, *pucTby;
	int nUsedPlane = 0;
	unsigned char *pucOrgTable;
	pucTbk = pucPalette;
	nPal = palnum[ulFlag & CR_STRBLT_BPP_MASK];	// pucPalette
#ifdef PR_SUPPORT_FUSER_CTL
	unsigned char ucCurFuserCtlFlag = *pucFuserCtl;
	unsigned char *pucFuserTbl = NULL; /* CMM */
	//unsigned long ulLimit = 0;
#endif

#if defined(PR_SUPPORT_FUSER_CTL) && defined(PR_SUPPORT_FUSER_CTL2)
	if ( ucCurFuserCtlFlag )
	{
		/*
		switch(ucDitherMode)
		{
			case DIT_PHOT:
				ulLimit = FUSER_CTL_LIMIT_PHOT;
				break;
			case DIT_TEXT:
				ulLimit = FUSER_CTL_LIMIT_TEXT;
				break;
		}
		*/
		ulLimit = FUSER_CTL_LIMIT_PHOT;

		if (ulArea > ulLimit)
		{
			pucFuserTbl = &(m_ucFuserCtlTbl[FUSER_CTL_AREA_OVER]
				[ucDitherMode][0][0]);
		}
		else
		{
			pucFuserTbl = &(m_ucFuserCtlTbl[FUSER_CTL_AREA_NOTOVER]
				[ucDitherMode][0][0]);
		}
	}
#elif defined(PR_SUPPORT_FUSER_CTL)
	if ( ucCurFuserCtlFlag )
	{
		pucFuserTbl = &(m_ucFuserCtlTbl[FUSER_CTL_AREA_OVER]
			[ucDitherMode][0][0]);
	}
#endif //PR_SUPPORT_FUSER_CTL

	pucTbc = pucTbk + 1;
	pucTbm = pucTbc + 1;
	pucTby = pucTbm + 1;

	if ((ulFlag & CR_STRBLT_COLOR_MASK) !=
		CR_STRBLT_MONO)
	{			// (RGB->CLP)
		switch (ulFlag & CR_STRBLT_INDEX_MASK)
		{
			case CR_STRBLT_INDEX_ON:	// Index (RGB+INDEX->CLP)
				if ((ulFlag & CR_STRBLT_COLOR_MASK) ==
					CR_STRBLT_KCMY)
				{
					// KCMY
					for (; nPal > 0; nPal--, pucTbk += 4,
						pucTbc += 4, pucTbm += 4, pucTby += 4)
					{
						*pucTbk = *pucIndexTable++;
						*pucTbc = *pucIndexTable++;
						*pucTbm = *pucIndexTable++;
						*pucTby = *pucIndexTable++;
						nUsedPlane |= *(unsigned int *)
						pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
						if (ucCurFuserCtlFlag)
						{
							ucCurFuserCtlFlag &= 
							GetFuserCtlKCMY(*pucTbk, *pucTbc, *pucTbm, *pucTby,
								pucFuserTbl);
						}
#endif /* PR_SUPPORT_FUSER_CTL */
					}
				}
				else
				{
					// RGB
					for (; nPal > 0; nPal--, pucTbk += 4,
						pucTbc += 4, pucTbm += 4, pucTby += 4)
					{
						*pucTbc = *pucIndexTable++;
						*pucTbm = *pucIndexTable++;
						*pucTby = *pucIndexTable++;
						transfunc (this, pucTbk, pucTbc, pucTbm,
							pucTby, 1, nTLimit, pVal, ppucGamma);
						nUsedPlane |= *(unsigned int *)
						pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
						if (ucCurFuserCtlFlag)
						{
							ucCurFuserCtlFlag &= 
							GetFuserCtlKCMY(*pucTbk, *pucTbc, *pucTbm, *pucTby,
								pucFuserTbl);
						}
#endif /* PR_SUPPORT_FUSER_CTL */
					}
				}
				break;
			case CR_STRBLT_INDEX_OFF:	// Index (RGB->CLP)
				pucOrgTable = idxtbls[0][ulFlag &
					CR_STRBLT_BPP_MASK];

				for (; nPal > 0; nPal--, pucTbk += 4, pucTbc
					+= 4, pucTbm += 4, pucTby += 4)
				{
					*pucTbc = *pucOrgTable++;
					*pucTbm = *pucOrgTable++;
					*pucTby = *pucOrgTable++;
					transfunc (this, pucTbk, pucTbc, pucTbm,
						pucTby, 1, nTLimit, pVal, ppucGamma);
					nUsedPlane |= *(unsigned int *)
					pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
					if (ucCurFuserCtlFlag)
					{
						ucCurFuserCtlFlag &= 
						GetFuserCtlKCMY(*pucTbk, *pucTbc, *pucTbm, *pucTby,
							pucFuserTbl);
					}
#endif /* PR_SUPPORT_FUSER_CTL */
				}
				break;
		}
	}
	else
	{			//KCMY (GRAY->CLP)
		switch (ulFlag & CR_STRBLT_INDEX_MASK)
		{
			case CR_STRBLT_INDEX_ON:	// Index (GRAY+INDEX->CLP)
				for (; nPal > 0; nPal--, pucIndexTable++, pucTbk
					+= 4, pucTbc += 4, pucTbm += 4, pucTby += 4)
				{
					*pucTbc = *pucTbm = *pucTby = 255 - *pucIndexTable;
					transfunc (this, pucTbk, pucTbc, pucTbm,
						pucTby, 1, nTLimit, pVal, ppucGamma);
					nUsedPlane |= *(unsigned int *)
					pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
					if (ucCurFuserCtlFlag)
					{
						ucCurFuserCtlFlag &= 
						GetFuserCtlKCMY(*pucTbk, *pucTbc, *pucTbm, *pucTby,
							pucFuserTbl);
					}
#endif /* PR_SUPPORT_FUSER_CTL */
				}
				break;
			case CR_STRBLT_INDEX_OFF:	// Index (GRAY->CLP)
				if (ulFlag & CR_STRBLT_REVERSE)
				{	// PR_STRBLT_REVERSE
					pucOrgTable = idxtbls_k[0][ulFlag &
						CR_STRBLT_BPP_MASK];
				}
				else
				{
					pucOrgTable = idxtbls[0][ulFlag &
						CR_STRBLT_BPP_MASK];
				};
				assert (pucOrgTable);
				for (; nPal > 0; nPal--, pucTbk += 4, pucTbc
					+= 4, pucTbm += 4, pucTby += 4)
				{
					*pucTbc = *pucOrgTable++;
					*pucTbm = *pucOrgTable++;
					*pucTby = *pucOrgTable++;
					transfunc (this, pucTbk, pucTbc, pucTbm,
						pucTby, 1, nTLimit, pVal, ppucGamma);
					nUsedPlane |= *(unsigned int *)
					pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
					if (ucCurFuserCtlFlag)
					{
						ucCurFuserCtlFlag &= 
						GetFuserCtlKCMY(*pucTbk, *pucTbc, *pucTbm, *pucTby,
							pucFuserTbl);
					}
#endif /* PR_SUPPORT_FUSER_CTL */
				}
				break;
		}
	}
#ifdef PR_SUPPORT_FUSER_CTL
	*pucFuserCtl = ucCurFuserCtlFlag;
#endif
	return nUsedPlane;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :MakePaletteMono 
//Description   :Create CMYK palette (black and white output device)
//Arguments     :
//              :unsigned long ulFlag:[IN]
//              :unsigned char *pucIndexTable:[IN]
//              :unsigned char *pucPalette:[IN]
//              :int nGrayMode:[IN]
//              :TRANS_FN_TYPE_1 transfunc:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :int:Used Plane
///////////////////////////////////////////////////////////////////////////////
#ifdef PR_SUPPORT_FUSER_CTL
int
CPRColor::MakePaletteMono (unsigned long ulFlag,
	unsigned char *pucIndexTable,
	unsigned char *pucPalette,
	unsigned char ucDitherMode,
	int nGrayMode,
	unsigned long ulArea,
	TRANS_FN_TYPE_1 transfunc,
	unsigned char **ppucGamma,
	unsigned char *pucFuserCtl)
#else
int
CPRColor::MakePaletteMono (unsigned long ulFlag,
	unsigned char *pucIndexTable,
	unsigned char *pucPalette,
	int nGrayMode,
	TRANS_FN_TYPE_1 transfunc,
	unsigned char **ppucGamma)
#endif /* PR_SUPPORT_FUSER_CTL */
{
	int nPal;
	unsigned char ucRGB[3];
	unsigned char *pucTbk;
	int nUsedPlane = 0;
	unsigned char *pucOrgTable;
#ifdef PR_SUPPORT_FUSER_CTL
	unsigned char ucCurFuserCtlFlag = *pucFuserCtl;
	unsigned char *pucFuserTbl = NULL; /* CMM */
	//unsigned long ulLimit = 0;
#endif

#if defined(PR_SUPPORT_FUSER_CTL) && defined(PR_SUPPORT_FUSER_CTL2)
	if ( ucCurFuserCtlFlag )
	{
		/*
		switch(ucDitherMode)
		{
			case DIT_PHOT:
				ulLimit = FUSER_CTL_LIMIT_PHOT;
				break;
			case DIT_TEXT:
				ulLimit = FUSER_CTL_LIMIT_TEXT;
				break;
			case DIT_GRAP:
				ulLimit = FUSER_CTL_LIMIT_GRAP;
				break;
			default:
				break;
		}
		*/
		ulLimit = FUSER_CTL_LIMIT_PHOT;

		if (ulArea > ulLimit)
		{
			pucFuserTbl = &(m_ucFuserCtlTbl[FUSER_CTL_AREA_OVER]
				[ucDitherMode][0][0]);
		}
		else
		{
			pucFuserTbl = &(m_ucFuserCtlTbl[FUSER_CTL_AREA_NOTOVER]
				[ucDitherMode][0][0]);
		}
	}
#elif defined(PR_SUPPORT_FUSER_CTL)
	if ( ucCurFuserCtlFlag )
	{
		pucFuserTbl = &(m_ucFuserCtlTbl[FUSER_CTL_AREA_OVER]
			[ucDitherMode][0][0]);
	}
#endif //PR_SUPPORT_FUSER_CTL
	pucTbk = pucPalette;
	nPal = palnum[ulFlag & CR_STRBLT_BPP_MASK];	// pucPalette

	if (ulFlag & CR_STRBLT_COLOR_MASK)
	{
		// (RGB->MONOP)
		switch (ulFlag & CR_STRBLT_INDEX_MASK)
		{
			case CR_STRBLT_INDEX_ON:	// Index (RGB+INDEX->MONOP)
				for (; nPal > 0; nPal--, pucTbk++)
				{
					ucRGB[0] = *pucIndexTable++;
					ucRGB[1] = *pucIndexTable++;
					ucRGB[2] = *pucIndexTable++;
					transfunc (this, pucTbk, &ucRGB[0], &ucRGB[1],
						&ucRGB[2], 1, ppucGamma);
					if (ulFlag & CR_STRBLT_SRCNOT)
						*pucTbk = ~*pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
						if (ucCurFuserCtlFlag)
						{
							ucCurFuserCtlFlag &=  GetFuserCtlK(*pucTbk, pucFuserTbl);
						}
#endif /* PR_SUPPORT_FUSER_CTL */
				}
				break;
			case CR_STRBLT_INDEX_OFF:	// Index (RGB->MONOP)
				pucOrgTable = idxtbls[1][ulFlag &
					CR_STRBLT_BPP_MASK];

				for (; nPal > 0; nPal--, pucTbk++)
				{
					ucRGB[0] = *pucOrgTable++;
					ucRGB[1] = *pucOrgTable++;
					ucRGB[2] = *pucOrgTable++;
					if (ulFlag & CR_STRBLT_RGB_ORDER)
						// R,G,B
						transfunc (this, pucTbk, &ucRGB[2], &ucRGB[1],
						&ucRGB[0], 1, ppucGamma);
					else
						// B,G,R
						transfunc (this, pucTbk, &ucRGB[0], &ucRGB[1],
						&ucRGB[2], 1, ppucGamma);
					if (ulFlag & CR_STRBLT_SRCNOT)
						*pucTbk = ~*pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
					if (ucCurFuserCtlFlag)
					{
						ucCurFuserCtlFlag &=  GetFuserCtlK(*pucTbk, pucFuserTbl);
					}
#endif /* PR_SUPPORT_FUSER_CTL */
				}
				break;
		}
	}
	else
	{
#ifdef SUPPORT_CUTTING_RGBVALUE
		int nObjMode = ((ulFlag & CR_ATTR_MASK) == CR_ATTR_TEXT) ?
				CR_OBJ_TEXT : CR_OBJ_IMAG;
#endif
		switch (ulFlag & CR_STRBLT_INDEX_MASK)
		{
			case CR_STRBLT_INDEX_ON:	// Index (GRAY+INDEX->MONOP)
				for (; nPal > 0; nPal--, pucTbk++, pucIndexTable++)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					*pucTbk = *pucIndexTable;
					ApplyRgbRatioGray(this, pucTbk, 1,
							nObjMode, CR_GRAP_SRCNOT_OFF);
					DoGammaK (pucTbk, pucTbk, ppucGamma);
#else
					DoGammaK (pucIndexTable, pucTbk, ppucGamma);
#endif
					if (ulFlag & CR_STRBLT_SRCNOT)
						*pucTbk = ~*pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
					if (ucCurFuserCtlFlag)
					{
						ucCurFuserCtlFlag &=  GetFuserCtlK(*pucTbk, pucFuserTbl);
					}
#endif /* PR_SUPPORT_FUSER_CTL */
				}
				break;
			case CR_STRBLT_INDEX_OFF:	// Index (GRAY->MONOP)
				if (ulFlag & CR_STRBLT_REVERSE)
				{	// PR_STRBLT_REVERSE
					pucOrgTable = idxtbls_k[1][ulFlag &
						CR_STRBLT_BPP_MASK];
				}
				else
				{
					pucOrgTable = idxtbls[1][ulFlag &
						CR_STRBLT_BPP_MASK];
				};
				assert (pucOrgTable);
				for (; nPal > 0; nPal--, pucOrgTable++, pucTbk++)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					*pucTbk = *pucOrgTable;
					ApplyRgbRatioGray(this, pucTbk, 1,
							nObjMode, CR_GRAP_SRCNOT_OFF);
					DoGammaK (pucTbk, pucTbk, ppucGamma);
#else
					DoGammaK (pucOrgTable, pucTbk, ppucGamma);
#endif
					if (ulFlag & CR_STRBLT_SRCNOT)
						*pucTbk = ~*pucTbk;
#ifdef PR_SUPPORT_FUSER_CTL
					if (ucCurFuserCtlFlag)
					{
						ucCurFuserCtlFlag &=  GetFuserCtlK(*pucTbk, pucFuserTbl);
					}
#endif /* PR_SUPPORT_FUSER_CTL */
			}
				break;
		}
	}
#ifdef PR_SUPPORT_FUSER_CTL
	*pucFuserCtl = ucCurFuserCtlFlag;
#endif
#ifndef X86
	return nUsedPlane |= 0xff000000;
#else //  X86
	return nUsedPlane |= 0x000000ff;
#endif //  X86
}


///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrPhot 
//Description   :It calls the color processing function with image 
//               quality as photo.
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrsGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrHgrPhot 
//Description   :It calls the color processing function with image 
//               quality as photo.
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrHgrPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrsHgrGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrPhotRK2 
//Description   :It calls the color processing function with image 
//               quality as photo.
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrPhotRK2 (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyTwinColorRK2BgucrsGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyTwinColorRK2BgucrsGammas
//Description   :CMM+CMY+BG/UCR(WiShGCR)+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyTwinColorRK2BgucrsGammas (
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	assert (pucGtK && pucGtC);
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	// BG/UCR & ppucGamma

	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];
		assert(!(m_ulCurId & CMM_CMYK));

		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				// set a value for nUsedPlane
				GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				if (*pucY == 0 && *pucM == 0 && *pucY == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{
				if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
											 pucM, pucC, 1, m_ulCurId))
				
				{
				printf("\t[CMM-RGB] NG Apply !!\r\n");
				}
				}

				/* CMMﾅ津｣窶堙渓eepgray窶敖ｻ窶凖ｨ */
				if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
					&& (*pucY == *pucM) && (*pucY == *pucC) )
				{
					// set a value for nUsedPlane
					GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
					unsigned char ucTemp = *pucC;

					*pucC = (unsigned char)~*pucY;
					*pucM = (unsigned char)~*pucM;
					*pucY = (unsigned char)~ucTemp;
					{
						int nK, nC, nM, nY, nMinColor;
						int nUCR;
						unsigned char *pucGtK = ppucGamma[0];
						unsigned char *pucGtC = ppucGamma[1];
						int nSumCK;
						unsigned char *UCRtbl = m_ucUcrLut;
						unsigned char *BGtbl = m_ucBgLut;
						unsigned char *pucPQTable = m_pucPqTbl;
						unsigned char *pucRPQTable = m_pucRPqTbl;
						assert (m_pucPqTbl && m_pucRPqTbl);
						assert(pucGtK && pucGtC);
											
						nMinColor = nC = (int)*pucC;
						nM = (int)*pucM;
						if (nM < nMinColor)
							nMinColor = nM;
						nY = (int)*pucY;
						if (nY < nMinColor)
							nMinColor = nY;

						nUCR = (int)UCRtbl[nMinColor];

						nK = (int)pucPQTable[*pucK = BGtbl[nMinColor]];
						nC = (int)pucPQTable[*pucC = nC - nUCR];
						nM = 0;
						nY = 0;

						nSumCK = nK + nC;
						if (nSumCK > nTonerLimit)
						{
#ifdef SUPPORT_LIMITING_K
							if (nTonerLimit > nK) {
								TONER_LIMIT (nTonerLimit, nSumCK,
												nK, nC, nM, nY);
								*pucK = pucGtK[*pucK];
								*pucC = pucGtC[pucRPQTable[nC]];
								*pucM = 0;
								*pucY = 0;
							}
							else
							{
								*pucK = pucGtK[pucRPQTable[nTonerLimit]];
								*pucC = *pucM = *pucY = 0;
							}
#else
							TONER_LIMIT (nTonerLimit, nSumCK, nK, nC, nM, nY);
							*pucK = pucGtK[*pucK];
							*pucC = pucGtC[pucRPQTable[nC]];
							*pucM = 0;
							*pucY = 0;
#endif
						}
						else
						{
							*pucK = pucGtK[*pucK];
							*pucC = pucGtC[*pucC];
							*pucM = 0;
							*pucY = 0;
						}
					}
				}
				ucKp |= *pucK;
				ucCp |= *pucC;
			}
		}	// size loop
		// store to pobjColor->nUsedPlane
		//In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16));
	}
	else
	{			// CMM OFF
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				// keepgray
				// set a value for nUsedPlane
				GammaK(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				unsigned char ucTemp = *pucC;

				*pucC = (unsigned char)~*pucY;
				*pucM = (unsigned char)~*pucM;
				*pucY = (unsigned char)~ucTemp;
				{
					int nK, nC, nM, nY, nMinColor;
					int nUCR;
					unsigned char *pucGtK = ppucGamma[0];
					unsigned char *pucGtC = ppucGamma[1];
					int nSumCK;
					unsigned char *UCRtbl = m_ucUcrLut;
					unsigned char *BGtbl = m_ucBgLut;
					unsigned char *pucPQTable = m_pucPqTbl;
					unsigned char *pucRPQTable = m_pucRPqTbl;
					assert (m_pucPqTbl && m_pucRPqTbl);
					assert(pucGtK && pucGtC);

					nMinColor = nC = (int)*pucC;
					nM = (int)*pucM;
					if (nM < nMinColor)
						nMinColor = nM;
					nY = (int)*pucY;
					if (nY < nMinColor)
						nMinColor = nY;

					nUCR = (int)UCRtbl[nMinColor];

					nK = (int)pucPQTable[*pucK = BGtbl[nMinColor]];
					nC = (int)pucPQTable[*pucC = nC - nUCR];
					nM = 0;
					nY = 0;

					nSumCK = nK + nC;
					if (nSumCK > nTonerLimit)
					{
#ifdef SUPPORT_LIMITING_K
						if (nTonerLimit > nK) {
							TONER_LIMIT (nTonerLimit, nSumCK, nK, nC, nM, nY);
							*pucK = pucGtK[*pucK];
							*pucC = pucGtC[pucRPQTable[nC]];
							*pucM = 0;
							*pucY = 0;
						}
						else
						{
							*pucK = pucGtK[pucRPQTable[nTonerLimit]];
							*pucC = *pucM = *pucY = 0;
						}
#else
						TONER_LIMIT (nTonerLimit, nSumCK, nK, nC, nM, nY);
						*pucK = pucGtK[*pucK];
						*pucC = pucGtC[pucRPQTable[nC]];
						*pucM = 0;
						*pucY = 0;
#endif
					}
					else
					{
						*pucK = pucGtK[*pucK];
						*pucC = pucGtC[*pucC];
						*pucM = 0;
						*pucY = 0;
					}
				}
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
			}
		}
		// store to pobjColor->nUsedPlane
		//In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbCmyPhot 
//Description   :Convert RGB to CMY.
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbCmyPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyRgb2CmyGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrsGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrHgrText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrHgrText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrsHgrGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrTextRK2
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrTextRK2 (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyTwinColorRK2BgucrsGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static voidTransrgbCmyText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbCmyText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyRgb2CmyGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static voidTransrgbBgucrImageKPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrImageKPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrImageKsGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static voidTransrgbBgucrImageKText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrImageKText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrImageKsGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :inline static void TransrgbBgucrKeepgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
inline static void
TransrgbBgucrKeepgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrKeepgraysGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :inline static void TransrgbBgucrHgrKeepgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
inline static void
TransrgbBgucrHgrKeepgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrHgrKeepgraysGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static voidTransrgbBgucrKeepgrayText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrKeepgrayText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrKeepgraysGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrHgrKeepgrayText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrHgrKeepgrayText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrHgrKeepgraysGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static voidTransrgbnotBgucrPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrsGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrHgrPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrHgrPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrsHgrGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrPhotRK2 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrPhotRK2 (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotTwinColorRK2BgucrsGammas(
		pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplySrcnotTwinColorRK2BgucrsGammas
//Description   :CMM+CMY+NOT+BG/UCR+Gray+USERﾆ津�PQTC+SYSTEMﾆ津�//Arguments     :
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :int nObjectKind:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplySrcnotTwinColorRK2BgucrsGammas (
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nObjectKind,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned char **ppucGt = ppucGamma;
	unsigned char *pucGtK, *pucGtC;
	int nTonerLimit;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	assert (pucGtK && pucGtC);
	assert (nTonerLimitOn);

	nTonerLimit = SetTonerLimitInColor(nObjectKind, pLimit);
	
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectKind];
		assert(!(m_ulCurId & CMM_CMYK));

		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this, pucY, 1,
						nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
				// set a value for nUsedPlane
				GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
				   because there is SRCNOT processing
				   after application of the ratio. */
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				if (*pucY == 0 && *pucM == 0 && *pucY == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{
				if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
											 pucM, pucC, 1, m_ulCurId))
				
				{
				printf("\t[CMM-RGB] NG Apply !!\r\n");
				}
				}

				/* CMMﾅ津｣窶堙渓eepgray窶敖ｻ窶凖ｨ */
				if ( (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON)
					&& (*pucY == *pucM) && (*pucY == *pucC) )
				{
					// set a value for nUsedPlane
					GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
				}
				else
				{
					// GCR, srcnot
					unsigned char ucTemp = *pucC;

					*pucC = *pucY;
					*pucY = ucTemp;
					{
						int nK, nC, nM, nY, nMinColor;
						int nUCR;
						unsigned char *pucGtK = ppucGamma[0];
						unsigned char *pucGtC = ppucGamma[1];
						int nSumCK;
						unsigned char *UCRtbl = m_ucUcrLut;
						unsigned char *BGtbl = m_ucBgLut;
						unsigned char *pucPQTable = m_pucPqTbl;
						unsigned char *pucRPQTable = m_pucRPqTbl;
						assert (m_pucPqTbl && m_pucRPqTbl);
						assert(pucGtK && pucGtC);
											
						nMinColor = nC = (int)*pucC;
						nM = (int)*pucM;
						if (nM < nMinColor)
							nMinColor = nM;
						nY = (int)*pucY;
						if (nY < nMinColor)
							nMinColor = nY;

						nUCR = (int)UCRtbl[nMinColor];

						nK = (int)pucPQTable[*pucK = BGtbl[nMinColor]];
						nC = (int)pucPQTable[*pucC = nC - nUCR];
						nM = 0;
						nY = 0;

						nSumCK = nK + nC;
						if (nSumCK > nTonerLimit)
						{
#ifdef SUPPORT_LIMITING_K
							if (nTonerLimit > nK) {
								TONER_LIMIT (nTonerLimit, nSumCK,
												nK, nC, nM, nY);
								*pucK = pucGtK[*pucK];
								*pucC = pucGtC[pucRPQTable[nC]];
								*pucM = 0;
								*pucY = 0;
							}
							else
							{
								*pucK = pucGtK[pucRPQTable[nTonerLimit]];
								*pucC = *pucM = *pucY = 0;
							}
#else
							TONER_LIMIT (nTonerLimit, nSumCK, nK, nC, nM, nY);
							*pucK = pucGtK[*pucK];
							*pucC = pucGtC[pucRPQTable[nC]];
							*pucM = 0;
							*pucY = 0;
#endif
						}
						else
						{
							*pucK = pucGtK[*pucK];
							*pucC = pucGtC[*pucC];
							*pucM = 0;
							*pucY = 0;
						}
					}
					// set a value for nUsedPlane
					ucKp |= *pucK;
					ucCp |= *pucC;
				}
			}
		}
		// store to pobjColor->nUsedPlane
		//	In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16));
	}
	else
	{			// is_cmm = OFF
		// BG/UCR & ppucGamma
		for (; nSize > 0; nSize--, pucK++, pucC++, pucM++, pucY++)
		{
			if (*pucY == *pucM && *pucY == *pucC)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this, pucY, 1,
						nObjectKind, CR_GRAP_SRCNOT_ON);
#endif
				// keepgray, srcnot
				// set a value for nUsedPlane
				GammaKcmy(pucK, pucC, pucM, pucY, ppucGt, ucKp);
			}
			else
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				/* ulSrcNot passes CR_GRAP_SRCNOT_OFF,
				   because there is SRCNOT processing
				   after application of the ratio. */
				ApplyRgbRatioRgb(this, pucY, pucM, pucC, 1,
						nObjectKind, CR_GRAP_SRCNOT_OFF);
#endif
				// GCR, srcnot
				unsigned char ucTemp = *pucC;

				*pucC = *pucY;
				*pucY = ucTemp;
				{
					int nK, nC, nM, nY, nMinColor;
					int nUCR;
					unsigned char *pucGtK = ppucGamma[0];
					unsigned char *pucGtC = ppucGamma[1];
					int nSumCK;
					unsigned char *UCRtbl = m_ucUcrLut;
					unsigned char *BGtbl = m_ucBgLut;
					unsigned char *pucPQTable = m_pucPqTbl;
					unsigned char *pucRPQTable = m_pucRPqTbl;
					assert (m_pucPqTbl && m_pucRPqTbl);
					assert(pucGtK && pucGtC);
										
					nMinColor = nC = (int)*pucC;
					nM = (int)*pucM;
					if (nM < nMinColor)
						nMinColor = nM;
					nY = (int)*pucY;
					if (nY < nMinColor)
						nMinColor = nY;

					nUCR = (int)UCRtbl[nMinColor];

					nK = (int)pucPQTable[*pucK = BGtbl[nMinColor]];
					nC = (int)pucPQTable[*pucC = nC - nUCR];
					nM = 0;
					nY = 0;

					nSumCK = nK + nC;
					if (nSumCK > nTonerLimit)
					{
#ifdef SUPPORT_LIMITING_K
						if (nTonerLimit > nK) {
							TONER_LIMIT (nTonerLimit, nSumCK, nK, nC, nM, nY);
							*pucK = pucGtK[*pucK];
							*pucC = pucGtC[pucRPQTable[nC]];
							*pucM = 0;
							*pucY = 0;
						}
						else
						{
							*pucK = pucGtK[pucRPQTable[nTonerLimit]];
							*pucC = *pucM = *pucY = 0;
						}
#else
						TONER_LIMIT (nTonerLimit, nSumCK, nK, nC, nM, nY);
						*pucK = pucGtK[*pucK];
						*pucC = pucGtC[pucRPQTable[nC]];
						*pucM = 0;
						*pucY = 0;
#endif
					}
					else
					{
						*pucK = pucGtK[*pucK];
						*pucC = pucGtC[*pucC];
						*pucM = 0;
						*pucY = 0;
					}
				}
				//	set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
			}
		}
		// store to pobjColor->nUsedPlane
		// In PRImage.cpp it's added to Used_plane
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp << 16));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotCmyPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotCmyPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotRgb2CmyGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrsGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrHgrText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrHgrText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrsHgrGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrTextRK2
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrTextRK2 (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotTwinColorRK2BgucrsGammas(
		pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotCmyText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotCmyText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotRgb2CmyGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}


///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrKeepgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrKeepgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_IMAG, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrHgrKeepgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrHgrKeepgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrHgrKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_IMAG, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrKeepgrayText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrKeepgrayText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_TEXT, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrHgrKeepgrayText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrHgrKeepgrayText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrHgrKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_TEXT, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrImageKPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrImageKPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrImageKsGammas (pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_IMAG, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrImageKText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrImageKText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrImageKsGammas (pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_TEXT, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrMaykeepgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrMaykeepgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrMaybeKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_IMAG, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrMaykeepgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrMaykeepgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned long cnt;
	unsigned char *tc = pucC;
	unsigned char *tm = pucM;
	unsigned char *ty = pucY;

	for (cnt = 0; cnt <(unsigned long) nSize; cnt++, tc++, tm++, ty++)
	{
		*tc = ~*tc;
		*tm = ~*tm;
		*ty = ~*ty;
	}

	pobjColor->ApplyBgucrMaybeKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_IMAG, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrMaykeepgrayText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrMaykeepgrayText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrMaybeKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_TEXT, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrMaykeepgrayText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrMaykeepgrayText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	unsigned long cnt;
	unsigned char *tc = pucC;
	unsigned char *tm = pucM;
	unsigned char *ty = pucY;

	for (cnt = 0; cnt < (ulong)nSize; cnt++, tc++, tm++, ty++)
	{
		*tc = ~*tc;
		*tm = ~*tm;
		*ty = ~*ty;
	}

	pobjColor->ApplyBgucrMaybeKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_TEXT, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrAboutkeepgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrAboutkeepgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrAboutKeepgraysGammas(pucK, pucC, pucM, pucY,
		nSize, CR_OBJ_IMAG, nTonerLimitOn, pLimit,ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransgrayPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransgrayPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	unsigned char **ppucGamma)
{
#ifdef	PR_HAVE_FAST_TRANSGRAY
	unsigned char *ep, *gp, *ugp;


#ifdef SUPPORT_CUTTING_RGBVALUE
	ApplyRgbRatioRgb(pobjColor, pucY, pucM, pucC, nSize,
				CR_OBJ_IMAG, CR_GRAP_SRCNOT_OFF);
#endif
	//	The following procedes directly instead of ApplyRgb2Gray()
	//	and DoGammaK() as these functions are so slow.
	
	if ((ugp = *(ppucGamma+pobjColor->m_nRenderNColor)) != NULL)
	{
		for (ep = pucK + nSize, gp = *ppucGamma; pucK < ep;)
		{
			*pucK++ = gp[ugp[255 - (*pucY * ICL_WR + *pucM * ICL_WG + *pucC
					* IC_WB) / IC_WBIAS]];
			*pucY++ = *pucM++ = *pucC++ = 0;
		}
	}
	else
	{
		for (ep = pucK + nSize, gp = *ppucGamma; pucK < ep;)
		{
			*pucK++ = gp[255 - (*pucY * ICL_WR + *pucM * ICL_WG + *pucC
					* IC_WB) / IC_WBIAS];
			*pucY++ = *pucM++ = *pucC++ = 0;
		}
	}
#else
	unsigned char wk[4];
	int cnt = 0;

	do
	{
#ifdef ORIG
		wk[0] = *pucY++;
		wk[1] = *pucM++;
		wk[2] = *pucC++;
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgb2Gray(pobjColor, wk, CR_OBJ_IMAG, CR_GRAP_SRCNOT_OFF);
#else
		ApplyRgb2Gray (wk);
#endif
		pobjColor->DoGammaK (wk, pucK++, ppucGamma);
#else

		wk[0] = *pucY;
		wk[1] = *pucM;
		wk[2] = *pucC;
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgb2Gray(pobjColor, wk, CR_OBJ_IMAG, CR_GRAP_SRCNOT_OFF);
#else
		ApplyRgb2Gray (wk);
#endif
		*pucC = *pucM = *pucY = 0;
		pucC++;
		pucM++;
		pucY++;
		pobjColor->DoGammaK (wk, pucK++, ppucGamma);
#endif
	}
	while (++cnt < nSize);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransgrayText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :int nSize:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransgrayText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	unsigned char **ppucGamma)
{
	unsigned char wk[4];
	int cnt = 0;

	do
	{
#ifdef ORIG
		wk[0] = *pucY++;
		wk[1] = *pucM++;
		wk[2] = *pucC++;
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgb2Gray (pobjColor, wk, CR_OBJ_TEXT, CR_GRAP_SRCNOT_OFF);
#else
		ApplyRgb2Gray (wk);
#endif
		pobjColor->DoGammaK (wk, pucK++, ppucGamma);
#else
		wk[0] = *pucY;
		wk[1] = *pucM;
		wk[2] = *pucC;
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgb2Gray (pobjColor, wk, CR_OBJ_TEXT, CR_GRAP_SRCNOT_OFF);
#else
		ApplyRgb2Gray (wk);
#endif
		*pucC = *pucM = *pucY = 0;
		pucC++;
		pucM++;
		pucY++;
		pobjColor->DoGammaK (wk, pucK++, ppucGamma);
#endif
	}
	while (++cnt < nSize);
}

#ifdef SUPPORT_COMPOSITEBLACK
///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbToGrayPhot
//Description   :
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbToGrayPhot(CPRColor* pobjColor,
		unsigned char *pucK,
		unsigned char *pucC,
		unsigned char *pucM,
		unsigned char *pucY,
		int nSize,
		int nTonerLimitOn,
		clr_tlimit_t * pLimit,
		unsigned char **ppucGamma)
{
#ifdef SUPPORT_CUTTING_RGBVALUE
	TransgrayPhot(pobjColor, pucK, pucC, pucM, pucY, nSize, ppucGamma);
#else
	TransgrayPhot(pucK, pucC, pucM, pucY, nSize, ppucGamma);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbToGrayText
//Description   :
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbToGrayText(CPRColor* pobjColor,
		unsigned char *pucK,
		unsigned char *pucC,
		unsigned char *pucM,
		unsigned char *pucY,
		int nSize,
		int nTonerLimitOn,
		clr_tlimit_t * pLimit,
		unsigned char **ppucGamma)
{
#ifdef SUPPORT_CUTTING_RGBVALUE
	TransgrayText(pobjColor, pucK, pucC, pucM, pucY, nSize, ppucGamma);
#else
	TransgrayText(pucK, pucC, pucM, pucY, nSize, ppucGamma);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbnotToGrayPhot
//Description   :
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotToGrayPhot(CPRColor* pobjColor,
		unsigned char *pucK,
		unsigned char *pucC,
		unsigned char *pucM,
		unsigned char *pucY,
		int nSize,
		int nTonerLimitOn,
		clr_tlimit_t * pLimit,
		unsigned char **ppucGamma)
{
	unsigned char *pucKEnd;

#ifdef SUPPORT_CUTTING_RGBVALUE
	TransgrayPhot(pobjColor, pucK, pucC, pucM, pucY, nSize, ppucGamma);
#else
	TransgrayPhot(pucK, pucC, pucM, pucY, nSize, ppucGamma);
#endif
	for (pucKEnd = pucK + nSize; pucK < pucKEnd; pucK++)
	{
		*pucK = ~(*pucK);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbnotToGrayText
//Description   :
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotToGrayText(CPRColor* pobjColor,
		unsigned char *pucK,
		unsigned char *pucC,
		unsigned char *pucM,
		unsigned char *pucY,
		int nSize,
		int nTonerLimitOn,
		clr_tlimit_t * pLimit,
		unsigned char **ppucGamma)
{
	unsigned char *pucKEnd;

#ifdef SUPPORT_CUTTING_RGBVALUE
	TransgrayText(pobjColor, pucK, pucC, pucM, pucY, nSize, ppucGamma);
#else
	TransgrayText(pucK, pucC, pucM, pucY, nSize, ppucGamma);
#endif
	for (pucKEnd = pucK + nSize; pucK < pucKEnd; pucK++)
	{
		*pucK = ~(*pucK);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrCompbkPhot 
//Description   :It calls the composite black processing function with image 
//               quality as photo.
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrCompbkPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrCompbksGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbBgucrCompbkText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrCompbkText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplyBgucrCompbksGammas(pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrCompbkPhot 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbnotBgucrCompbkPhot (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrCompbksGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_IMAG, nTonerLimitOn, pLimit, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransrgbnotBgucrCompbkText 
//Description   : 
//Arguments     :
//              :CPRColor* pobjColor:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :int nSize:[IN]
//              :int nTonerLimitOn:[IN]
//              :clr_tlimit_t * pLimit:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void

TransrgbnotBgucrCompbkText (CPRColor* pobjColor,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	int nSize,
	int nTonerLimitOn,
	clr_tlimit_t * pLimit,
	unsigned char **ppucGamma)
{
	pobjColor->ApplySrcnotBgucrCompbksGammas (pucK, pucC, pucM, pucY, nSize,
		CR_OBJ_TEXT, nTonerLimitOn, pLimit, ppucGamma);
}
#endif /* SUPPORT_COMPOSITEBLACK */

///////////////////////////////////////////////////////////////////////////////
//Function      :SetTransrgbBrush 
//Description   : 
//Arguments     :
//              :int nGrayMode:[IN]
//Return value  :Pointer to the Function
///////////////////////////////////////////////////////////////////////////////
TRANS_FN_TYPE
CPRColor::SetTransrgbBrush (int nGrayMode)
{
	TRANS_FN_TYPE func = 0;
	switch (nGrayMode)
	{
		case CR_GRAY_G2K:
		case CR_GRAY_PIXELK:
		case CR_GRAY_MAYBEK:
			func = TransrgbBgucrKeepgrayPhot;
			break;
		case CR_GRAY_HGRG2K:
			func = TransrgbBgucrHgrKeepgrayPhot;
			break;
		case CR_GRAY_CMY:
			func = TransrgbCmyPhot;
			break;
		case CR_GRAY_CMYK:
		case CR_GRAY_K2K:
			func = TransrgbBgucrPhot;
			break;
		case CR_GRAY_HGRCMYK:
			func = TransrgbBgucrHgrPhot;
			break;
		case CR_GRAY_IMAGEK:
			func = TransrgbBgucrImageKPhot;
			break;
		case CR_GRAY_ABOUTK:
			func = TransrgbBgucrAboutkeepgrayPhot;
			break;
#ifdef SUPPORT_COMPOSITEBLACK
		case CR_GRAY_COMPBK:
			if (CheckCompbk() == TRUE)
			{
				func = TransrgbBgucrCompbkPhot;
			}
			else	/* parameter of compbk is insufficient */
			{
				if (m_ucRenderingIsmono)
				{
					func = TransrgbToGrayPhot;
				}
				else
				{
					func = TransrgbBgucrKeepgrayPhot;
				}
			}
			break;
#endif
		default:;
			assert (FALSE);
	}
	return func;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :SetTransgrayBrush 
//Description   : 
//Arguments     :
//              :void
//Return value  :TRANS_FN_TYPE_1:Function Type
///////////////////////////////////////////////////////////////////////////////
TRANS_FN_TYPE_1
CPRColor::SetTransgrayBrush (void)
{
	TRANS_FN_TYPE_1 func;

	func = TransgrayPhot;

	return func;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :SetTransrgb 
//Description   : 
//Arguments     :
//              :unsigned long ulFlag:[IN]
//              :int nGrayMode:[IN]
//Return value  :TRANS_FN_TYPE:
///////////////////////////////////////////////////////////////////////////////
TRANS_FN_TYPE
CPRColor::SetTransrgb (unsigned long ulFlag,
	int nGrayMode)
{
	TRANS_FN_TYPE func = 0;

	if (!((ulFlag & CR_ATTR_MASK) == CR_ATTR_TEXT))
	{
		switch (nGrayMode)
		{
			case CR_GRAY_CMYK:
			case CR_GRAY_K2K:
				func = TransrgbBgucrPhot;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotBgucrPhot;
				break;
			case CR_GRAY_HGRCMYK:
				func = TransrgbBgucrHgrPhot;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotBgucrHgrPhot;
				break;
			case CR_GRAY_IMAGEK:
				if (ulFlag & CR_STRBLT_COLOR_MASK)
				{
					func = TransrgbBgucrImageKPhot;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func =
							TransrgbnotBgucrImageKPhot;
				}
				else
				{
					func = TransrgbBgucrKeepgrayPhot;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func =
							TransrgbnotBgucrKeepgrayPhot;
				}
				break;
#ifdef SUPPORT_COMPOSITEBLACK
			case CR_GRAY_COMPBK:
				if (CheckCompbk() == TRUE)
				{
					/* color print mode and color data */
					/* draw as same as CR_GRAY_CMYK */
					if (!m_ucRenderingIsmono &&
						((ulFlag & CR_STRBLT_COLOR_MASK) != 0))
					{
						func = TransrgbBgucrPhot;
						if ((ulFlag & CR_STRBLT_SRCNOT) != 0)
						{
							func = TransrgbnotBgucrPhot;
						}
					}
					else
					{
					/* monochrome print mode or mono data */
					/* draw with compbk */
						func = TransrgbBgucrCompbkPhot;
						if ((ulFlag & CR_STRBLT_SRCNOT) != 0)
						{
						   func = TransrgbnotBgucrCompbkPhot;
						}
					}
					break;
				}
				else	/* parameter of compbk is insufficeint */
				{
					/* monochrome print mode will draw to K */
					if (m_ucRenderingIsmono)
					{
						func = TransrgbToGrayPhot;
						if ((ulFlag & CR_STRBLT_SRCNOT) != 0)
						{
							func = TransrgbnotToGrayPhot;
						}
						break;
					}
					/* through to G2K */
				}
#endif /* SUPPORT_COMPOSITEBLACK */
			case CR_GRAY_G2K:
			case CR_GRAY_ABOUTK:
				if (ulFlag & CR_STRBLT_COLOR_MASK)
				{
					func = TransrgbBgucrPhot;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrPhot;
				}
				else
				{
					func = TransrgbBgucrKeepgrayPhot;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrKeepgrayPhot;
				}
				break;
			case CR_GRAY_HGRG2K:
				if (ulFlag & CR_STRBLT_COLOR_MASK)
				{
					func = TransrgbBgucrHgrPhot;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrHgrPhot;
				}
				else
				{
					func = TransrgbBgucrHgrKeepgrayPhot;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrHgrKeepgrayPhot;
				}
				break;
			case CR_GRAY_CMY:
				func = TransrgbCmyPhot;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotCmyPhot;
				break;
			case CR_GRAY_PIXELK:
				func = TransrgbBgucrKeepgrayPhot;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func =
						TransrgbnotBgucrKeepgrayPhot;
				break;
			case CR_GRAY_MAYBEK:
				func = TransrgbBgucrMaykeepgrayPhot;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotBgucrMaykeepgrayPhot;
				break;
			default:;
				assert (FALSE);
		}
	}
	else
	{
		switch (nGrayMode)
		{
			case CR_GRAY_CMYK:
			case CR_GRAY_K2K:
				func = TransrgbBgucrText;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotBgucrText;
				break;
			case CR_GRAY_HGRCMYK:
				func = TransrgbBgucrHgrText;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotBgucrHgrText;
				break;
			case CR_GRAY_IMAGEK:
				if (ulFlag & CR_STRBLT_COLOR_MASK)
				{
					func = TransrgbBgucrImageKText;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrImageKText;
				}
				else
				{
					func = TransrgbBgucrKeepgrayText;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrKeepgrayText;
				}
				break;
#ifdef SUPPORT_COMPOSITEBLACK
			case CR_GRAY_COMPBK:
				if (CheckCompbk() == TRUE)
				{
					/* color print mode and color data */
					/* draw as same as CR_GRAY_CMYK */
					if (!m_ucRenderingIsmono &&
						((ulFlag & CR_STRBLT_COLOR_MASK) != 0))
					{
						func = TransrgbBgucrText;
						if ((ulFlag & CR_STRBLT_SRCNOT) != 0)
						{
							func = TransrgbnotBgucrText;
						}
					}
					else
					{
					/* monochrome print mode or mono data */
					/* draw with composite black */
						func = TransrgbBgucrCompbkText;
						if ((ulFlag & CR_STRBLT_SRCNOT) != 0)
						{
						   func = TransrgbnotBgucrCompbkText;
						}
					}
					break;
				}
				else	/* parameter of compbk is insufficient */
				{
					/* monochrome print mode will draw to K */
					if (m_ucRenderingIsmono)
					{
						func = TransrgbToGrayText;
						if ((ulFlag & CR_STRBLT_SRCNOT) != 0)
						{
							func = TransrgbnotToGrayText;
						}
						break;
					}
					/* through to G2K */
				}
#endif /* SUPPORT_COMPOSITEBLACK */
			case CR_GRAY_G2K:
			case CR_GRAY_ABOUTK:
				if (ulFlag & CR_STRBLT_COLOR_MASK)
				{
					func = TransrgbBgucrText;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrText;
				}
				else
				{
					func = TransrgbBgucrKeepgrayText;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrKeepgrayText;
				}
				break;
			case CR_GRAY_HGRG2K:
				if (ulFlag & CR_STRBLT_COLOR_MASK)
				{
					func = TransrgbBgucrHgrText;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrHgrText;
				}
				else
				{
					func = TransrgbBgucrHgrKeepgrayText;
					if (ulFlag & CR_STRBLT_SRCNOT)
						func = TransrgbnotBgucrHgrKeepgrayText;
				}
				break;
			case CR_GRAY_CMY:
				func = TransrgbCmyText;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotCmyText;
				break;
			case CR_GRAY_PIXELK:
				func = TransrgbBgucrKeepgrayText;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotBgucrKeepgrayText;
				break;
			case CR_GRAY_MAYBEK:
				func = TransrgbBgucrMaykeepgrayText;
				if (ulFlag & CR_STRBLT_SRCNOT)
					func = TransrgbnotBgucrMaykeepgrayText;
				break;
			default:;
				assert (FALSE);
		}
	}
	return func;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :SetTransrgbRK2
//Description   : 
//Arguments     :
//              :unsigned long ulFlag:[IN]
//              :int nGrayMode:[IN]
//Return value  :TRANS_FN_TYPE:
///////////////////////////////////////////////////////////////////////////////
TRANS_FN_TYPE
CPRColor::SetTransrgbRK2 (unsigned long ulFlag, int nGrayMode)
{
	TRANS_FN_TYPE func = 0;

	if (!((ulFlag & CR_ATTR_MASK) == CR_ATTR_TEXT))
	{
		func = TransrgbBgucrPhotRK2;
		if (ulFlag & CR_STRBLT_SRCNOT)
		{
			func = TransrgbnotBgucrPhotRK2;
		}
	}
	else
	{
		func = TransrgbBgucrTextRK2;
		if (ulFlag & CR_STRBLT_SRCNOT)
		{
			func = TransrgbnotBgucrTextRK2;
		}
	}
	return func;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :SetTransgray 
//Description   : 
//Arguments     :
//              :unsigned long ulFlag:[IN]
//              :int nGrayMode:[IN]
//Return value  :TRANS_FN_TYPE_1
///////////////////////////////////////////////////////////////////////////////
TRANS_FN_TYPE_1
CPRColor::SetTransgray (unsigned long ulFlag, int nGrayMode)
{
	TRANS_FN_TYPE_1 func;

	if (!((ulFlag & CR_ATTR_MASK) == CR_ATTR_TEXT))
		func = TransgrayPhot;
	else
		func = TransgrayText;

	return func;
}

//////////////////////////////////////////////////////////////////////////
//        INDEX->CMYK, INDEX->GRAY
//////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransIdx2Cmyk 
//Description   :Index to CMYK
//Arguments     :
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned char *pucPalette:[IN]
//              :int nSize:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransIdx2Cmyk (unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned char *pucPalette,
	int nSize)
{
	int nData;

	while (nSize--)
	{			// nSize loop
		nData = (*pucK << 2);	// Index
		*pucK++ = pucPalette[nData++];	// Black data
		*pucC++ = pucPalette[nData++];	// Cyan data
		*pucM++ = pucPalette[nData++];	// Mazenta data
		*pucY++ = pucPalette[nData];	// Yellow data
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static void TransIdx2Gray 
//Description   :Index to Gray
//Arguments     :
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucPalette:[IN]
//              :int nSize:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransIdx2Gray (unsigned char *pucK,
	unsigned char *pucPalette,
	int nSize)
{
	while (nSize--)
	{
		// nSize loop
		*pucK = pucPalette[*pucK];	// Index -> Gray
		pucK++;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbDirect 
//Description   : 
//Arguments     :
//              :unsigned long ulFlag:[IN]
//              :int nSize:[IN]
//              :int plane_size:[IN]
//              :unsigned char *ptr:[IN]
//              :unsigned char *pucIndexTable:[IN]
//              :unsigned char nTLimit:[IN]
//              :clr_tlimit_t * pVal:[IN]
//              :TRANS_FN_TYPE transfunc:[IN]
//              :unsigned char **ppucGamma:[IN]
//              :int nObjMode:[IN]
//              :int nColorMode:[IN]
//Return value  :void 
///////////////////////////////////////////////////////////////////////////////
void CPRColor::
TransrgbDirect (
	unsigned long ulFlag,
	int nSize,
	unsigned char *ptr,
	unsigned char *pucIndexTable,
	unsigned char nTLimit,
	clr_tlimit_t * pVal,
	TRANS_FN_TYPE transfunc,
	unsigned char **ppucGamma,
	int nObjMode,
	int nColorMode)
{

	TRANS_FN_TYPE_1 transfunc1 = (TRANS_FN_TYPE_1)
	transfunc;

	if ((ulFlag & CR_STRBLT_BPP_MASK) == CR_STRBLT_24BPP)
	{			// 24bitRGB
		if (nColorMode)
		{
			if (ulFlag & CR_STRBLT_RGB_ORDER)
			{
				ulong i;
#ifndef O2_OPTION
				ulong swap;
#endif
				for (i = 0; i <(ulong) nSize; i++)
				{
#ifndef O2_OPTION
					swap = *(ptr + nSize + i);
					*(ptr + nSize + i) = *(ptr + nSize * 3 + i);
					*(ptr + nSize * 3 + i) = swap;
#else
					(*(ptr + nSize + i)) = (*(ptr +
							nSize + i))^(*(ptr + nSize * 3 + i));
					(*(ptr + nSize * 3 + i)) = (*(ptr +
							nSize * 3 + i))^(*(ptr + nSize + i));
					(*(ptr + nSize + i)) = (*(ptr +
							nSize + i))^(*(ptr + nSize * 3 + i));
#endif
				}
			}
			transfunc (this, ptr, ptr + nSize, ptr +
				nSize * 2, ptr + nSize * 3, nSize, nTLimit,
				pVal, ppucGamma);
		}
		else
		{
#ifdef	PR_HAVE_FAST_TRANSGRAY
			if (ulFlag & CR_STRBLT_RGB_ORDER)
			{
				transfunc1 (this, ptr, ptr + nSize * 3, ptr +
					nSize * 2, ptr + nSize, nSize, ppucGamma);
			}
			else
			{
				transfunc1 (this, ptr, ptr + nSize, ptr +
					nSize * 2, ptr + nSize * 3, nSize, ppucGamma);
			}
#else	// PR_HAVE_FAST_TRANSGRAY
		if (ulFlag & CR_STRBLT_RGB_ORDER)
		{	// R,G,B
			ulong i;
#ifndef O2_OPTION
			ulong swap;
#endif
			for (i = 0; i < nSize; i++)
			{
#ifndef O2_OPTION
				swap = *(ptr + nSize + i);
				*(ptr + nSize + i) = *(ptr + nSize * 3 + i);
				*(ptr + nSize * 3 + i) = swap;
#else
				(*(ptr + nSize + i)) = (*(ptr +
						nSize + i))^(*(ptr + nSize * 3 + i));
				(*(ptr + nSize * 3 + i)) = (*(ptr +
						nSize * 3 + i))^(*(ptr + nSize + i));
				(*(ptr + nSize + i)) = (*(ptr +
						nSize + i))^(*(ptr + nSize * 3 + i));
#endif
			}
			transfunc1 (this, ptr, ptr + nSize, ptr +
				nSize * 2, ptr + nSize * 3, nSize,
				ppucGamma);
#endif	// PR_HAVE_FAST_TRANSGRAY
		}
	}
	else if ((ulFlag & CR_STRBLT_BPP_MASK) == CR_STRBLT_32BPP)
	{			// 32bit
		if (ulFlag & CR_STRBLT_THROUGH) {
			if (!nColorMode) {
				unsigned char ucKCMY[4], *pucK, *pucC, *pucM, *pucY;
				for (pucK = ptr, pucC = ptr + nSize, pucM = ptr
					+ nSize * 2, pucY = ptr + nSize * 3;
					pucK < (ptr + nSize);
					pucK++, pucC++, pucM++, pucY++)
				{
					ucKCMY[0] = *pucK;
					ucKCMY[1] = *pucC;
					ucKCMY[2] = *pucM;
					ucKCMY[3] = *pucY;
					ApplyCmyk2Gray (ucKCMY);	// KCMY -> GRAY
					*pucK = ucKCMY[0];
					*pucC = *pucM = *pucY = 0;
				}
			}
			return;
		}
		if (nColorMode && !nTLimit)
		{
			GammaSNoTonerLimit (ppucGamma, nSize,
				ptr, ptr + nSize,
				ptr + nSize * 2, ptr + nSize * 3);
		}
		else if (nColorMode)
		{
			DoGammaS(nObjMode, (int) nTLimit,
				pVal, ppucGamma, nSize, ptr, ptr +
				nSize,
				ptr + nSize * 2, ptr + nSize * 3);
		}
		else
		{
			unsigned char ucKCMY[4], *pucK, *pucC, *pucM, *pucY;
			for (pucK = ptr, pucC = ptr + nSize, pucM = ptr
				+ nSize * 2, pucY = ptr + nSize * 3;
				pucK < (ptr + nSize);
				pucK++, pucC++, pucM++, pucY++)
			{
				ucKCMY[0] = *pucK;
				ucKCMY[1] = *pucC;
				ucKCMY[2] = *pucM;
				ucKCMY[3] = *pucY;
				ApplyCmyk2Gray (ucKCMY);	// KCMY -> GRAY
				DoGammaK (ucKCMY, ucKCMY, ppucGamma);
				*pucK = ucKCMY[0];
				*pucC = *pucM = *pucY = 0;
			}
		}
	}
	else
	{
		if (nColorMode)
		{
			TransIdx2Cmyk (ptr, ptr + nSize, ptr +
				nSize * 2, ptr + nSize * 3, pucIndexTable, nSize);
		}
		else
		{
			TransIdx2Gray (ptr, ppucGamma[0], nSize);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static inline bool UseCache
//Description   :If cache hit, use cache,
//Arguments     :
//              :const clr_cache_t sCache[]:[IN]
//              :const unsigned long ulRGB:[IN]
//              :unsigned char*& pucPlaneK:[OUT]
//              :unsigned char*& pucPlaneC:[OUT]
//              :unsigned char*& pucPlaneM:[OUT]
//              :unsigned char*& pucPlaneY:[OUT]
//Return value  :bool:true -> use cache, false -> don't hit cache
///////////////////////////////////////////////////////////////////////////////
static inline bool
UseCache(const clr_cache_t sCache[],
	const unsigned long ulRGB,
	unsigned char*& pucPlaneK,
	unsigned char*& pucPlaneC,
	unsigned char*& pucPlaneM,
	unsigned char*& pucPlaneY)
{
	for (int nI = 0; nI < CR_CACHE_SIZE; ++nI) {
		if (ulRGB == sCache[nI].ulRGB) {
			*pucPlaneK++ = sCache[nI].ucK;
			*pucPlaneC++ = sCache[nI].ucC;
			*pucPlaneM++ = sCache[nI].ucM;
			*pucPlaneY++ = sCache[nI].ucY;
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static inline void UpdateCache
//Description   :Update color cache. Head is latest.
//Arguments     :
//              :clr_cache_t sCache[]:[OUT]
//              :const unsigned long ulRGB:[IN]
//              :const unsigned char ucK:[IN]
//              :const unsigned char ucC:[IN]
//              :const unsigned char ucM:[IN]
//              :const unsigned char ucY:[IN]
//Return value  :void
///////////////////////////////////////////////////////////////////////////////
static inline void
UpdateCache(clr_cache_t sCache[],
	const unsigned long ulRGB,
	const unsigned char ucK,
	const unsigned char ucC,
	const unsigned char ucM,
	const unsigned char ucY)
{
	for (int nI = CR_CACHE_SIZE - 1; nI > 0; --nI) {
		sCache[nI] = sCache[nI - 1];
	}
	sCache[0].ulRGB = ulRGB;
	sCache[0].ucK = ucK;
	sCache[0].ucC = ucC;
	sCache[0].ucM = ucM;
	sCache[0].ucY = ucY;
}

//////////////////////////////////////////////////////////////////////////
//        URF->CMYK, URF->GRAY
//////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Function      :TransURF2Cmyk 
//Description   :RGB URF to CMYK URF
//Arguments     :
//              :const unsigned char *pucSrcPtr:[IN]
//              :unsigned char *ptr:[OUT]
//              :const unsigned long ulWidth:[IN]
//              :const unsigned long ulHeight:[IN]
//              :const unsigned long ulImgSize:[IN]
//              :unsigned char nTLimit:[IN]
//              :clr_tlimit_t * pVal:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::TransURF2Cmyk (const unsigned char *pucSrcPtr,
	unsigned char *ptr,
	const unsigned long ulWidth,
	const unsigned long ulHeight,
	const unsigned long ulImgSize,
	unsigned char nTLimit,
	clr_tlimit_t * pVal,
	unsigned char **ppucGamma)
{
	unsigned char ucK, ucC, ucM, ucY;
	unsigned long ulCnt, ulRGB, ulLineLoop, ulPixelRepeat;
	unsigned long nPlaneSize = ulImgSize / 4;
	unsigned char *pucPlaneK = ptr;
	unsigned char *pucPlaneC = pucPlaneK + nPlaneSize;
	unsigned char *pucPlaneM = pucPlaneC + nPlaneSize;
	unsigned char *pucPlaneY = pucPlaneM + nPlaneSize;
	unsigned char *pucOrgPlaneC, *pucOrgPlaneM, *pucOrgPlaneY;
	// not use User Gamma
	if ((m_pFuncGcrLimit == TransGcrPQlimit) && (ppucGamma[4] == NULL) &&
		(ppucGamma[5] == NULL) && (ppucGamma[6] == NULL) && (ppucGamma[7] == NULL))
	{
		m_pFuncGcrLimit = TransGcrPQlimitNoUserGamma;
	}

	for (unsigned long ulHeightCnt = 0; ulHeightCnt < ulHeight;
										ulHeightCnt += ulLineLoop) {
		*pucPlaneK++ =
		*pucPlaneC++ =
		*pucPlaneM++ =
		*pucPlaneY++ = *pucSrcPtr;
		ulLineLoop = *pucSrcPtr++;

		for (unsigned long ulWidthCnt = 0; ulWidthCnt < ulWidth;
												ulWidthCnt += ulCnt) {
			*pucPlaneK++ =
			*pucPlaneC++ =
			*pucPlaneM++ =
			*pucPlaneY++ = *pucSrcPtr;
			ulCnt = *pucSrcPtr++;

			if (ulCnt < 0x80) {
				ucY = *pucSrcPtr++;		// R
				ucM = *pucSrcPtr++;		// G
				ucC = *pucSrcPtr++;		// B

				ulRGB = ucY;
				ulRGB |= (ucM << 8);
				ulRGB |= (ucC << 16);

				if (UseCache(m_sCache, ulRGB, pucPlaneK, pucPlaneC,
												pucPlaneM, pucPlaneY)) {
					++ulCnt;
					continue;
				}
				ApplyBgucrsGammasURF(&ucK, &ucC, &ucM, &ucY, 1,
									CR_OBJ_IMAG, nTLimit, pVal, ppucGamma);
						
				*pucPlaneK++ = ucK;
				*pucPlaneC++ = ucC;
				*pucPlaneM++ = ucM;
				*pucPlaneY++ = ucY;
				UpdateCache(m_sCache, ulRGB, ucK, ucC, ucM, ucY);
				++ulCnt;
				continue;
			}

			if (ulCnt > 0x80) {
				ulPixelRepeat = CR_NUM_FOR_NONREPEAT_URF - ulCnt;
				pucOrgPlaneY = pucPlaneY;
				pucOrgPlaneM = pucPlaneM;
				pucOrgPlaneC = pucPlaneC;

				for (unsigned long ulPixelCnt = 0;
							ulPixelCnt < ulPixelRepeat; ++ulPixelCnt) {

					*pucPlaneY++ = *pucSrcPtr++;	// R
					*pucPlaneM++ = *pucSrcPtr++;	// G
					*pucPlaneC++ = *pucSrcPtr++;	// B
				}
				ApplyBgucrsGammasURF(pucPlaneK, pucOrgPlaneC,
								pucOrgPlaneM, pucOrgPlaneY, ulPixelRepeat,
								CR_OBJ_IMAG, nTLimit, pVal, ppucGamma);

				pucPlaneK += ulPixelRepeat;
				ulCnt = ulPixelRepeat;
				continue;
			}
			break;
		}
		++ulLineLoop;
	}

	if (m_pFuncGcrLimit == TransGcrPQlimitNoUserGamma)
	{
		m_pFuncGcrLimit = TransGcrPQlimit;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static inline void TransURF2Gray 
//Description   :K URF to Gray URF
//Arguments     :
//              :const unsigned char *pucSrcPtr:[IN]
//              :unsigned char *pucK:[OUT]
//              :const unsigned char *pucPalette:[IN]
//              :const unsigned long ulWidth:[IN]
//              :const unsigned long ulHeight:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static inline void
TransURF2Gray (const unsigned char *pucSrcPtr,
	unsigned char *pucK,
	const unsigned char *pucPalette,
	const unsigned long ulWidth,
	const unsigned long ulHeight)
{
	unsigned long ulCnt, ulLineLoop;

	for (unsigned long ulHeightCnt = 0; ulHeightCnt < ulHeight;
										ulHeightCnt += ulLineLoop) {
		*pucK++ = *pucSrcPtr;
		ulLineLoop = *pucSrcPtr++;

		for (unsigned long ulWidthCnt = 0; ulWidthCnt < ulWidth;
													ulWidthCnt += ulCnt) {
			*pucK++ = *pucSrcPtr;
			ulCnt = *pucSrcPtr++;

			if (ulCnt < 0x80) {
				*pucK++ = pucPalette[*pucSrcPtr++];	// K -> Gray
				++ulCnt;
				continue;
			}

			if (ulCnt > 0x80) {
				ulCnt = CR_NUM_FOR_NONREPEAT_URF - ulCnt;

				for (unsigned long ulPixelCnt = 0;
							ulPixelCnt < ulCnt; ++ulPixelCnt) {

					*pucK++ = pucPalette[*pucSrcPtr++];	// K -> Gray
				}
				continue;
			}
			break;
		}
		++ulLineLoop;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransURFDirect 
//Description   :Spool URF image. 
//Arguments     :
//              :unsigned long ulFlag:[IN]
//              :unsigned long ulWidth:[IN]
//              :unsigned long ulHeight:[IN]
//              :unsigned long ulImgSize:[IN]
//              :unsigned char *pucSrcPtr:[IN]
//              :unsigned char *ptr:[OUT]
//              :unsigned char *pucIndexTable:[IN]
//              :unsigned char nTLimit:[IN]
//              :clr_tlimit_t * pVal:[IN]
//              :unsigned char **ppucGamma:[IN]
//Return value  :void 
///////////////////////////////////////////////////////////////////////////////
void CPRColor::TransURFDirect (
	unsigned long ulFlag,
	unsigned long ulWidth,
	unsigned long ulHeight,
	unsigned long ulImgSize,
	unsigned char *pucSrcPtr,
	unsigned char *ptr,
	unsigned char *pucIndexTable,
	unsigned char nTLimit,
	clr_tlimit_t * pVal,
	unsigned char **ppucGamma)
{
	if ((ulFlag & CR_STRBLT_COLOR_MASK) == CR_STRBLT_MONO) {
		TransURF2Gray(pucSrcPtr, ptr, pucIndexTable, ulWidth, ulHeight);
		return;
	}
	TransURF2Cmyk(pucSrcPtr, ptr, ulWidth, ulHeight,
						ulImgSize, nTLimit, pVal, ppucGamma);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :GetDeviceColor 
//Description   : 
//Arguments     :
//              :ginf_t *psGinf:[IN]
//              :unsigned char **ppucGamma:[IN]
//              :unsigned char *incolor:[IN]
//              :unsigned char *outcolor:[IN]
//Return value  :void 
///////////////////////////////////////////////////////////////////////////////
/* CMMvoid CPRColor::
GetDeviceColor (
	ginf_t *psGinf,
	unsigned char **ppucGamma,
	unsigned char *incolor,
	unsigned char *outcolor)
{
	int nSumCMYK;
	unsigned char ucK, ucC, ucM, ucY;
	unsigned char ucKp, ucCp, ucMp, ucYp;
	
	short pLimit = psGinf->m_siColorLimit;
	unsigned long ulFlag = psGinf->m_ulColorFlag;
	unsigned long ulCmmProfileId = psGinf->m_ulCmmProfileId;
	
	switch (ulFlag & CR_INPUT_SPACE_MASK)
	{
		case CR_INPUT_SPACE_GRAY:;
			assert (incolor[1] == incolor[2] ==
				incolor[3] == 0);
				ucK = incolor[0];
			ucC = 0;
			ucM = 0;
			ucY = 0;
			if ((ulFlag & CR_OUTPUT_SPACE_MASK) ==
				CR_OUTPUT_SPACE_CMYK)
			{
				if ((ulFlag & CR_UGAMMA_MASK) == CR_UGAMMA_ON)
				{
					ApplyUserGammas(ppucGamma[4], 1, &ucK);
					ApplyUserGammas(ppucGamma[5], 1, &ucC);
					ApplyUserGammas(ppucGamma[6], 1, &ucM);
					ApplyUserGammas(ppucGamma[7], 1, &ucY);
				}
				if ((ulFlag & CR_GAMMA_MASK) ==
					CR_GAMMA_ON)
				{
					assert(ppucGamma[0] && ppucGamma[1] &&
						ppucGamma[2] && ppucGamma[3]);
					ucK = ppucGamma[0][ucK];
					ucC = ppucGamma[1][ucC];
					ucM = ppucGamma[2][ucM];
					ucY = ppucGamma[3][ucY];
				}
				if ((ulFlag & CR_OUTPUT_ORDER_MASK)
					== CR_OUTPUT_ORDER_NORMAL)
				{
					outcolor[0] = ucC;
					outcolor[1] = ucM;
					outcolor[2] = ucY;
					outcolor[3] = ucK;
				}
				else
				{;
					assert ((ulFlag &
							CR_OUTPUT_ORDER_MASK)
						== CR_OUTPUT_ORDER_REVERSE);
					outcolor[0] = ucK;
					outcolor[1] = ucC;
					outcolor[2] = ucM;
					outcolor[3] = ucY;
				}
			}
			else if ((ulFlag & CR_OUTPUT_SPACE_MASK)
				== CR_OUTPUT_SPACE_MONO)
			{
				if ((ulFlag & CR_UGAMMA_MASK) == CR_UGAMMA_ON)
				{
					ApplyUserGammas(ppucGamma[4], 1, &ucK);
				}
				if ((ulFlag & CR_GAMMA_MASK) == CR_GAMMA_ON)
				{
					assert(ppucGamma[0]);
					ucK = ppucGamma[0][ucK];
				}
				outcolor[0] = ucK;
				outcolor[1] = outcolor[2] =
				outcolor[3] = 0;
			}
			break;

		case CR_INPUT_SPACE_RGB:
		{
			union
			{
				ulong l;
				uchar b[4];
			} in;
			union
			{
				ulong l;
				uchar b[4];
			} out;
			in.b[3] = 0;
			if ((ulFlag & CR_INPUT_ORDER_MASK) ==
				CR_INPUT_ORDER_NORMAL)
			{
				in.b[0] = incolor[0];
				in.b[1] = incolor[1];
				in.b[2] = incolor[2];
			}
			else
			{;
				assert ((ulFlag &
						CR_INPUT_ORDER_MASK) ==
						CR_INPUT_ORDER_REVERSE) in.b[0]
					= incolor[2];
				in.b[1] = incolor[1];
				in.b[2] = incolor[0];
			}

			switch (ulFlag & CR_OUTPUT_SPACE_MASK)
			{
				case CR_OUTPUT_SPACE_CMYK:	// CMYK
				case CR_OUTPUT_SPACE_CMY:	// CMY
				{
					//save the current CMM information
					long is_cmm_org = m_psCmmColor->m_lIsCmm;
					m_psCmmColor->m_lIsCmm = ulFlag & CR_CMM_MASK;
					unsigned long ucOrgCmmProfileId = m_psCmmColor->m_ulCurId;
					m_psCmmColor->m_ulCurId = ulCmmProfileId;
					//save the current Gray Judge after CMM
					unsigned char ucOrgIsGrayJudge = m_ucIsGrayJudge;
					m_ucIsGrayJudge	= 
					( (ulFlag & CR_JUDGE_GRAY_MASK) == CR_JUDGE_GRAY_ON) ? 
					CR_JUDGE_GRAY_AFTER_CMM_ON : CR_JUDGE_GRAY_AFTER_CMM_OFF;

					switch (ulFlag & CR_GRAYP_MASK)
					{
						case CR_GRAYP_G2K:
						case CR_GRAYP_PIXELK:
						case CR_GRAYP_MAYBEK:
#ifdef SUPPORT_CUTTING_RGBVALUE
							ApplyBgucrKeepgray (in.b, out.b, CR_OBJ_IMAG,
									CR_GRAP_SRCNOT_OFF);
#else
							ApplyBgucrKeepgray (in.b,
								out.b);
#endif
							break;
						case CR_GRAYP_HGRG2K:
							ApplyBgucrHgrKeepgray (in.b,
								out.b);
							break;
						case CR_GRAYP_CMYK:
#ifdef SUPPORT_CUTTING_RGBVALUE
							ApplyBgucr(in.b, out.b, CR_OBJ_IMAG,
									CR_GRAP_SRCNOT_OFF);
#else
							ApplyBgucr(in.b, out.b);
#endif
							break;
						case CR_GRAYP_HGRCMYK:
							ApplyBgucrHgr(in.b, out.b);
							break;
						case CR_GRAYP_CMY:
							ApplyRgb2Cmy (in.b, out.b);
							break;
						case CR_GRAYP_K2K:
						case CR_GRAYP_IMAGEK:
							ApplyBgucrKeepblack (in.b,
								out.b);
							break;
						case CR_GRAYP_ABOUTK:
							ApplyBgucrAboutKeepgray
							(in.b, out.b);
							break;
					}
					
					m_psCmmColor->m_lIsCmm = is_cmm_org;
					m_psCmmColor->m_ulCurId = ucOrgCmmProfileId;
					m_ucIsGrayJudge = ucOrgIsGrayJudge;
					}
					ucK = out.b[0];
					ucC = out.b[1];
					ucM = out.b[2];
					ucY = out.b[3];
					if ((ulFlag & CR_UGAMMA_MASK) == CR_UGAMMA_ON)
					{
						ApplyUserGammas(ppucGamma[4], 1, &ucK);
						ApplyUserGammas(ppucGamma[5], 1, &ucC);
						ApplyUserGammas(ppucGamma[6], 1, &ucM);
						ApplyUserGammas(ppucGamma[7], 1, &ucY);
					}
					if (m_nIsPqtc)
					{
						if ((ulFlag & CR_TONERLIMIT_MASK)== CR_TONERLIMIT_ON)
						{
							ucKp = m_pucPqTbl[ucK];
							ucCp = m_pucPqTbl[ucC];
							ucMp = m_pucPqTbl[ucM];
							ucYp = m_pucPqTbl[ucY];
							nSumCMYK = ucKp + ucCp + ucMp +	ucYp;
							if (nSumCMYK > pLimit)
							{
								TONER_LIMIT (pLimit, nSumCMYK, ucKp, ucCp,
									ucMp, ucYp);
								ucC = m_pucRPqTbl[ucCp];
								ucM = m_pucRPqTbl[ucMp];
								ucY = m_pucRPqTbl[ucYp];
							}
						}
						if ((ulFlag & CR_GAMMA_MASK) ==	CR_GAMMA_ON)
						{
							assert(ppucGamma[0] && ppucGamma[1] &&
								ppucGamma[2] && ppucGamma[3]);
							ucK = ppucGamma[0][ucK];
							ucC = ppucGamma[1][ucC];
							ucM = ppucGamma[2][ucM];
							ucY = ppucGamma[3][ucY];
						}
					}
					else
					{
						if ((ulFlag & CR_GAMMA_MASK) ==	CR_GAMMA_ON)
						{
							assert(ppucGamma[0] && ppucGamma[1] &&
								ppucGamma[2] && ppucGamma[3]);
							ucK = ppucGamma[0][ucK];
							ucC = ppucGamma[1][ucC];
							ucM = ppucGamma[2][ucM];
							ucY = ppucGamma[3][ucY];
						}
						if ((ulFlag & CR_TONERLIMIT_MASK) == CR_TONERLIMIT_ON)
						{
							nSumCMYK = ucC + ucM + ucY + ucK;
							if (nSumCMYK > pLimit)
							{
								TONER_LIMIT (pLimit,nSumCMYK, ucK, ucC, ucM, ucY);
							}
						}
					}
					if ((ulFlag & CR_OUTPUT_ORDER_MASK)
						== CR_OUTPUT_ORDER_NORMAL)
					{
						outcolor[0] = ucC;
						outcolor[1] = ucM;
						outcolor[2] = ucY;
						outcolor[3] = ucK;
					}
					else
					{;
						assert ((ulFlag & CR_OUTPUT_ORDER_MASK)
							== CR_OUTPUT_ORDER_REVERSE);
						outcolor[0] = ucK;
						outcolor[1] = ucC;
						outcolor[2] = ucM;
						outcolor[3] = ucY;
					}
					break;
				case CR_OUTPUT_SPACE_RK:

					ApplyTwinColor (in.b, out.b);
					if ((ulFlag & CR_UGAMMA_MASK) == CR_UGAMMA_ON)
					{
						ApplyUserGammas(ppucGamma[4], 1, &out.b[0]);
						ApplyUserGammas(ppucGamma[5], 1, &out.b[1]);
					}
					if ((ulFlag & CR_GAMMA_MASK) ==
						CR_GAMMA_ON)
					{
						assert(ppucGamma[0] && ppucGamma[1]);
						out.b[0] = ppucGamma[0][out.b[0]];
						out.b[1] = ppucGamma[1][out.b[1]];
					}


					outcolor[0] = out.b[0];
					outcolor[1] = out.b[1];
					outcolor[2] = outcolor[3] = 0;
					break;
				case CR_OUTPUT_SPACE_MONO:
				{
					unsigned int g;
					g = (in.b[0] * ICL_WR + in.b[1] *
						ICL_WG + in.b[2] * IC_WB) /
					IC_WBIAS;
					if (g > 255)
						g = 255;
					out.b[0] = 255 - g;
					if ((ulFlag & CR_UGAMMA_MASK) == CR_UGAMMA_ON)
					{
						ApplyUserGammas(ppucGamma[4], 1, &out.b[0]);
					}
					if ((ulFlag & CR_GAMMA_MASK) ==
						CR_GAMMA_ON)
					{
						assert(ppucGamma[0]);
						out.b[0] = ppucGamma[0][out.b[0]];
					}
					outcolor[0] = out.b[0];
					outcolor[1] = outcolor[2] =
						outcolor[3] = 0;

					break;
				}
				case CR_OUTPUT_SPACE_RK2:
				default:;
					assert (0);
					break;
			}

			break;
		}
		case CR_INPUT_SPACE_CMYK:
			if ((ulFlag & CR_INPUT_ORDER_MASK) ==
				CR_INPUT_ORDER_NORMAL)
			{
				ucK = incolor[3];
				ucC = incolor[0];
				ucM = incolor[1];
				ucY = incolor[2];
			}
			else
			{;
				assert ((ulFlag &
						CR_INPUT_ORDER_MASK) ==
					CR_INPUT_ORDER_REVERSE);
				ucK = incolor[0];
				ucC = incolor[1];
				ucM = incolor[2];
				ucY = incolor[3];
			}
			if ((ulFlag & CR_OUTPUT_SPACE_MASK) ==
				CR_OUTPUT_SPACE_CMYK)
			{
				if ((ulFlag & CR_UGAMMA_MASK) == CR_UGAMMA_ON)
				{
					ApplyUserGammas(ppucGamma[4], 1, &ucK);
					ApplyUserGammas(ppucGamma[5], 1, &ucC);
					ApplyUserGammas(ppucGamma[6], 1, &ucM);
					ApplyUserGammas(ppucGamma[7], 1, &ucY);
				}
				if (m_nIsPqtc)
				{
					if ((ulFlag & CR_TONERLIMIT_MASK)
						== CR_TONERLIMIT_ON)
					{
						ucKp = m_pucPqTbl[ucK];
						ucCp = m_pucPqTbl[ucC];
						ucMp = m_pucPqTbl[ucM];
						ucYp = m_pucPqTbl[ucY];
						nSumCMYK = ucKp + ucCp + ucMp +
							ucYp;
						if (nSumCMYK > pLimit)
						{
							TONER_LIMIT (pLimit,
								nSumCMYK, ucKp, ucCp,
								ucMp, ucYp);
							ucC = m_pucRPqTbl[ucCp];
							ucM = m_pucRPqTbl[ucMp];
							ucY = m_pucRPqTbl[ucYp];
						}
					}
					if ((ulFlag & CR_GAMMA_MASK) ==
						CR_GAMMA_ON)
					{
						assert(ppucGamma[0] && ppucGamma[1] &&
							ppucGamma[2] && ppucGamma[3]);
						ucK = ppucGamma[0][ucK];
						ucC = ppucGamma[1][ucC];
						ucM = ppucGamma[2][ucM];
						ucY = ppucGamma[3][ucY];
					}
				}
				else
				{
					if ((ulFlag & CR_GAMMA_MASK) ==
						CR_GAMMA_ON)
					{
						assert(ppucGamma[0] && ppucGamma[1] &&
							ppucGamma[2] && ppucGamma[3]);
						ucK = ppucGamma[0][ucK];
						ucC = ppucGamma[1][ucC];
						ucM = ppucGamma[2][ucM];
						ucY = ppucGamma[3][ucY];
					}
					if ((ulFlag & CR_TONERLIMIT_MASK)
						== CR_TONERLIMIT_ON)
					{
						nSumCMYK = ucK + ucC + ucM + ucY;
						if (nSumCMYK > pLimit)
						{
							TONER_LIMIT (pLimit,
								nSumCMYK, ucK, ucC, ucM,
								ucY);
						}
					}
				}
				if ((ulFlag & CR_OUTPUT_ORDER_MASK)
					== CR_OUTPUT_ORDER_NORMAL)
				{
					outcolor[0] = ucC;
					outcolor[1] = ucM;
					outcolor[2] = ucY;
					outcolor[3] = ucK;
				}
				else
				{;
					assert ((ulFlag &
							CR_OUTPUT_ORDER_MASK)
						== CR_OUTPUT_ORDER_REVERSE)
					outcolor[0] = ucK;
					outcolor[1] = ucC;
					outcolor[2] = ucM;
					outcolor[3] = ucY;
				}
			}
			else if ((ulFlag & CR_OUTPUT_SPACE_MASK)
				== CR_OUTPUT_SPACE_MONO)
			{
				unsigned char in[4];
				in[0] = ucK;
				in[1] = ucC;
				in[2] = ucM;
				in[3] = ucY;
				ApplyCmyk2Gray (in);	// KCMY -> GRAY
				if ((ulFlag & CR_UGAMMA_MASK) == CR_UGAMMA_ON)
				{
					ApplyUserGammas(ppucGamma[4], 1, &in[0]);
				}
				if ((ulFlag & CR_GAMMA_MASK) ==
					CR_GAMMA_ON)
				{
					assert(ppucGamma[0]);
					in[0] = ppucGamma[0][in[0]];
				}
				outcolor[0] = in[0];
				outcolor[1] = outcolor[2] =
					outcolor[3] = 0;
			}
			break;
		default:;
			assert (FALSE);
	}
} CMM*/

///////////////////////////////////////////////////////////////////////////////
//Function      :SetcolorGinf 
//Description   : 
//Arguments     :
//              :CPRPageRenderer* prh:[IN]
//              :ginf_t * ginf:[IN]
//              :int nObjMode:[IN]
//              :int nObjectType:[IN]
//              :long lSx:[IN]
//              :long lEx:[IN]
//              :long lSy:[IN]
//              :long lEy:[IN]
//              :uchar ucCoordFlag:[IN]
//              :CPRPrintElement * pobjPrintElement:[IN]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
/* CMM #if defined(PR_SUPPORT_FUSER_CTL) || defined(USE_SINGLE_ROP66_PARTIAL_DETECTION)
int
SetcolorGinf (CPRPageRenderer* prh,
	ginf_t * ginf,
	int nObjMode,
	int nObjectType,
	long lSx,
	long lEx,
	long lSy,
	long lEy,
	uchar ucCoordFlag,
	CPRPrintElement * pobjPrintElement)
#else
int
SetcolorGinf (CPRPageRenderer* prh,
	ginf_t * ginf,
	int nObjMode,
	int nObjectType,
	CPRPrintElement * pobjPrintElement)
#endif
{

	uchar *pucFGPointer=0, *pucBGPointer=0;
	int nSetSecond = FALSE;
	clr_tlimit_t pLimit;
	uchar **ppucGamma=0;
		CPRColor* cur_color = (CPRColor*) &(prh->m_objColor);
	unsigned char ucDitherMode;
	int nOrigObjMode = nObjMode;
	bool bFlag = false;;
#ifdef PR_SUPPORT_FUSER_CTL
	unsigned char ucCurFuserCtlFlag = prh->m_objSpool.m_ucFuserCtlFlag;
	unsigned long ulLimit = 0, ulArea = 0;
	unsigned char *pucFuserTbl;
#endif CMM*//* PR_SUPPORT_FUSER_CTL */
	/* CMM assert (prh && ginf);

#ifdef USE_SINGLE_ROP66_DETECTION
	nObjMode &= ~OBJ_ROP66_DETECT;
#endif
	;
	assert (OBJ_IMAG <= (nObjMode & OBJ_MASK));;
	assert ((nObjMode & OBJ_MASK) <= OBJ_LINE);;
	assert (OBJ_DEF_2ND <= (nObjMode &
			OBJ_MASK_2ND));;
	assert ((nObjMode & OBJ_MASK_2ND) <=
		OBJ_IMAG_MONO_2ND);

	nObjMode &= OBJ_MASK; CMM*//* 窶佚ｦ1FG/BG 窶堙姑棚ﾆ置ﾆ淡ﾆ巽ﾆ誰ﾆ暖ﾅｽﾃｭ窶氾� */

	/*
	 * OBJ_IMAG_{COLOR, MONO}窶堙�	 * GRAYﾆ停��ｽ[ﾆ檀窶堙娯�ﾂｻ窶凖ｨﾋ�闇�窶堙��ﾃ弘BJ_IMAG窶堙俄�u窶堋ｫﾅ�ｷ窶堋ｦ窶堙ｩ�ｽB
	 */
	/* CMMif ((nOrigObjMode & OBJ_MASK_1ST) == OBJ_IMAG_COLOR ||
		(nOrigObjMode & OBJ_MASK_1ST) == OBJ_IMAG_MONO)
	{
		nObjMode = OBJ_IMAG;
	}
	CMM*/
	/* ﾆ棚ﾆ置ﾆ淡ﾆ巽ﾆ誰ﾆ暖ﾅｽﾃｭ窶氾樞�ﾋ��ﾃ姑断ﾆ達ﾆ旦ﾅｽﾃｭ窶氾樞�ﾃｰﾅｽﾃｦ窶慊ｾ */
	/* CMMswitch (nObjMode & OBJ_MASK)
	{
		case OBJ_IMAG:
			ucDitherMode = DIT_IMAG_MODE (ginf->m_ucDither);
			break;
		case OBJ_GRAP:
			ucDitherMode = DIT_GRAP_MODE (ginf->m_ucDither);
			break;
		case OBJ_TEXT:
			ucDitherMode = DIT_TEXT_MODE (ginf->m_ucDither);
			break;
		case OBJ_LINE:
			ucDitherMode = DIT_LINE_MODE (ginf->m_ucDither);
			break;
		default:;
			assert (0);
			return PR_ERROR;
	}
	pLimit.text = prTLIMIT[ucDitherMode][OBJ_TEXT];
	pLimit.line = prTLIMIT[ucDitherMode][OBJ_LINE];
	pLimit.phot = prTLIMIT[ucDitherMode][OBJ_IMAG];
	pLimit.fill = prTLIMIT[ucDitherMode][OBJ_GRAP];
#ifdef PR_XPS_SUPPORT
	if (prh->m_nSupportBlending ==
		PR_ENABLE_BLENDING_FALSE)
	{
#endif
#ifdef USE_SINGLE_ROP66_PARTIAL_DETECTION
		if (prh->m_objGraphics.CheckRop(prh, ginf,
				nOrigObjMode, nObjectType,
				lSx, lEx, lSy, lEy, pobjPrintElement))
#else
		if (prh->m_objGraphics.CheckRop(prh, ginf,
				nOrigObjMode, nObjectType))
#endif
		{ CMM*/
		/*
		 * EOR 窶堙架�坂�ﾃ懌�ﾃｪ窶堋ｽ EOR ﾋ�闇�窶堙姑棚ﾆ置ﾆ淡ﾆ巽ﾆ誰ﾆ暖窶堙遺�ﾃ娯�ﾃ�		 * ﾆ筑ﾆ湛ﾆ誰窶堙��ﾂｵ窶堙��ﾃ鯉ｿｽF (K=C=M=Y=0xff) 窶堋ｪ�ｽﾃ昶�ﾃｨ窶堋ｳ窶堙ｪ窶堋ｽ
		 */
/* CMM#ifdef OLD
			Used_plane = 0xffffffff;
#endif
#ifdef PR3_SUPPORT_GIPA1
			if (prh->m_pobjGIPAOrder->GetIsMakeSpoolForOL() == true)
			{
				if (prh->m_objColor.SetcolorGinfForDespool(prh, ginf, &pLimit, nObjMode)
					 == PR_ERROR)
				{
					return PR_ERROR;
				}
			}
#endif //PR3_SUPPORT_GIPA1
			return PR_OK;
		}
#ifdef PR_XPS_SUPPORT
	}
#endif
	pucFGPointer = ginf->m_objFg.b;
	pucBGPointer = ginf->m_objBg.b;

#if defined(PR_SUPPORT_FUSER_CTL) && defined(PR_SUPPORT_FUSER_CTL2)
	if ( ucCurFuserCtlFlag )
	{ CMM*/
		/*
		switch(ucDitherMode)
		{
			case DIT_PHOT:
				ulLimit = FUSER_CTL_LIMIT_PHOT;
				break;
			case DIT_TEXT:
				ulLimit = FUSER_CTL_LIMIT_TEXT;
				break;
			case DIT_GRAP:
				ulLimit = FUSER_CTL_LIMIT_GRAP;
				break;
			default:
				break;
		}
		*/
		/* CMMulLimit = FUSER_CTL_LIMIT_PHOT;

		if (ucCoordFlag)
		{
			ulArea = (lEy - lSy + 1) * (lEx - lSx + 1);
			if (ulArea > ulLimit)
			{
				pucFuserTbl = &(prh->m_objColor.m_ucFuserCtlTbl
					[FUSER_CTL_AREA_OVER][ucDitherMode][0][0]);
			}
			else
			{
				pucFuserTbl = &(prh->m_objColor.m_ucFuserCtlTbl
					[FUSER_CTL_AREA_NOTOVER][ucDitherMode][0][0]);
			}
		}
		else
		{
			pucFuserTbl = &(prh->m_objColor.m_ucFuserCtlTbl
				[FUSER_CTL_AREA_OVER][ucDitherMode][0][0]);
		}
	}
#elif defined(PR_SUPPORT_FUSER_CTL)
	if ( ucCurFuserCtlFlag )
	{
		pucFuserTbl = &(prh->m_objColor.m_ucFuserCtlTbl
			[FUSER_CTL_AREA_OVER][ucDitherMode][0][0]);
	}
#endif CMM*/

	/*
	 * ﾆ谷ﾆ停��ｽ[ﾆ置ﾆ停�ﾆ歎窶堙ｰﾅｽg窶廃窶堋ｵ窶堋ｽ窶｢`窶ｰﾃｦ窶堋ｩ窶堙��ﾂ､窶堋ｩ窶堙娯�ﾂｻ窶凖ｨ窶堋ｵ�ｽA
	 * ﾆ置ﾆ停�ﾆ歎窶堋ｪﾅｽg窶廃窶堋ｵ窶堙��ﾂ｢窶堙ｩﾆ致ﾆ椎抵ｿｽ[ﾆ停�窶堙ｰﾅｽﾃｦ窶慊ｾ窶堋ｷ窶堙ｩ�ｽB
	 */
	/*CMMbool bUseColBrush = false;
	int nBrushUsedPlane = 0;

	if (((Used_plane & COLOR_CMYK_K) == 0) ||
		((Used_plane & COLOR_CMYK_C) == 0) ||
		((Used_plane & COLOR_CMYK_M) == 0) ||
		((Used_plane & COLOR_CMYK_Y) == 0))
	{
		bUseColBrush = cur_color->IsUseColorBrush(prh, nObjectType,
										pobjPrintElement, nBrushUsedPlane);
	}

	prh->m_objRender.SelectRender(prh, ginf->m_ucDither);
	do
	{

		ppucGamma = prh->m_objRender.m_objGamma.GetCurrentSysGamma(nObjMode,
			prh->m_objRender.m_nNColor);

		if (prh->m_objColor.m_nIsPqtc)
		{
			// prh->pobjColor->m_nIsPqtc
			if (ucDitherMode == DIT_PHOT)
			{
				cur_color->m_sPqLimit = cur_color->m_sPqLimitPhot;
				cur_color->m_pucPqTbl = cur_color->m_pucPqTblPhot;
				cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblPhot;
			}
			else if (ucDitherMode == DIT_GRAP)
			{
				cur_color->m_sPqLimit = cur_color->m_sPqLimitGrap;
				cur_color->m_pucPqTbl = cur_color->m_pucPqTblGrap;
				cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblGrap;
			}
			else
			{;
				assert (ucDitherMode == DIT_TEXT);
				cur_color->m_sPqLimit = cur_color->m_sPqLimitText;
				cur_color->m_pucPqTbl = cur_color->m_pucPqTblText;
				cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblText;
			}
		}

		prh->m_objColor.SetColorGinfColorMask(prh,
			nObjMode, pucFGPointer, pucBGPointer, ppucGamma, ginf,
			nOrigObjMode, &pLimit);

#ifdef DEBUG_SETCOLOR
		printf ("KCMY=(%d,%d,%d,%d) ", pucFGPointer[0], pucFGPointer[1],
			pucFGPointer[2], pucFGPointer[3]);
#endif

#ifdef PR_SUPPORT_FUSER_CTL
		if (ucCurFuserCtlFlag) {
			switch (spl_ncolor) {
			case 4:
				ucCurFuserCtlFlag &= prh->m_objColor.GetFuserCtlKCMY(
					pucFGPointer[0], pucFGPointer[1], pucFGPointer[2],
					pucFGPointer[3], pucFuserTbl);
				break;
			case 2:
				ucCurFuserCtlFlag &= prh->m_objColor.GetFuserCtlKC(
					pucFGPointer[0], pucFGPointer[1], pucFuserTbl);
				break;
			case 1:
				ucCurFuserCtlFlag &= prh->m_objColor.GetFuserCtlK(
					pucFGPointer[0], pucFuserTbl);
				break;
			default:
				ucCurFuserCtlFlag = PR_DEGREEDOWN_OFF;
				assert(0);
				break;
			}
		}
#endif CMM*//* PR_SUPPORT_FUSER_CTL */

		/* ﾆ丹ﾆ停�ﾆ断�ｽ[ﾆ歎ﾆ停�ﾆ停�窶堙�Used_plane 窶堙ｰ�ｽﾃ昶�ﾃｨ窶堋ｷ窶堙ｩ       */
		/* ﾆ丹ﾆ停�ﾆ断�ｽ[ﾆ歎ﾆ停�ﾆ停�ﾅｽw窶凖ｨ(ﾆ丹ﾆ停�ﾆ断�ｽ[ﾆ歎ﾆ停�ﾆ停�ﾆ稚ﾆ停�ﾆ丹ON 窶堋ｩ窶堙�窶佚ｦ2FG/BG窶堙��ﾃ坂�ﾃ遺�ﾂ｢) */
		/*CMMif ((ginf->m_ucFlag & COLOR_GRADATION) &&
			(nSetSecond == FALSE))
		{

			if (prh->m_objColor.SetcolorGinfColorGradation(prh,
				ginf, &pLimit, nObjMode) == PR_ERROR)
			{
				return PR_ERROR;
			}
		}
#ifdef PR3_SUPPORT_GIPA1
		else if ((prh->m_pobjGIPAOrder->GetIsMakeSpoolForOL() == true)
			&& (nSetSecond == FALSE))
		{
			if (prh->m_objColor.SetcolorGinfForDespool(prh, ginf, &pLimit, nObjMode)
				 == PR_ERROR)
			{
				return PR_ERROR;
			}
			if (bUseColBrush)
			{
				Used_plane |= nBrushUsedPlane;
			}
			else
			{
				Used_plane |= *(int *) pucFGPointer;
			}
		}
#endif //PR3_SUPPORT_GIPA1
#ifdef	PR_HAVE_XRGB_DRAW
		else if (prh->m_objRender.m_ucIsColor ==
			PAGE_COLOR_XRGB)
		{
			Used_plane |= 0xffffffff;
		}
#endif
		else
		{
			if (bUseColBrush && (nSetSecond == FALSE))
			{
				Used_plane |= nBrushUsedPlane;
			}
			else
			{
				Used_plane |= *(int *) pucFGPointer;
			}
		}

#ifdef	PR_HAVE_XRGB_DRAW
		if (prh->m_objRender.m_ucIsColor ==
			PAGE_COLOR_XRGB)
		{
			//if (IS_OPAQUE)
			Used_plane |= 0xffffffff;
		}
		else
		{
#endif CMM*//* PR_HAVE_XRGB_DRAW */
		/* CMMif (ginf->m_ucFlag & COLOR_BGMODE)
		{
			if (bUseColBrush && (nSetSecond == FALSE))
			{
				Used_plane |= nBrushUsedPlane;
			}
			else
			{
				Used_plane |= *(int *) pucBGPointer;
			}
#ifdef PR_SUPPORT_FUSER_CTL
			if (ucCurFuserCtlFlag) {
				switch (spl_ncolor) {
				case 4:
					ucCurFuserCtlFlag &= prh->m_objColor.GetFuserCtlKCMY(
						pucBGPointer[0], pucBGPointer[1], pucBGPointer[2],
						pucBGPointer[3], pucFuserTbl);
					break;
				case 2:
					ucCurFuserCtlFlag &= prh->m_objColor.GetFuserCtlKC(
						pucBGPointer[0], pucBGPointer[1], pucFuserTbl);
					break;
				case 1:
					ucCurFuserCtlFlag &= prh->m_objColor.GetFuserCtlK(
						pucBGPointer[0], pucFuserTbl);
					break;
				default:
					ucCurFuserCtlFlag = PR_DEGREEDOWN_OFF;
					assert(0);
					break;
				}
			}
#endif CMM*//* PR_SUPPORT_FUSER_CTL */
		/* CMM}
#ifdef	PR_HAVE_XRGB_DRAW
		}
#endif
		bFlag = false;
		if ((ginf->m_ucFlag & COLOR_2NDFGBG) && (nSetSecond
				== FALSE))
		{ CMM*/
			/*
			 * 窶佚ｦ2 FG/BG 窶堋ｪ窶堋��ﾃｩ窶堙娯�ﾃ��ﾂｻ窶堙ｪ窶堙鯉ｿｽF窶｢ﾃ焦�ｷ窶堙ｰ�ｽs窶堋､�ｽB
			 */
			/* CMMpucFGPointer = ginf->m_objFg2.b;
			pucBGPointer = ginf->m_objBg2.b;
			nSetSecond = TRUE;
			bFlag = true; CMM*/
			/* 窶佚ｦ2 FG/BG 窶堙俄�ﾂｮ�ｽﾂｫﾅｽw窶凖ｨ窶堋ｪ窶堋��ﾃｩ窶堋ｩﾆ蛋ﾆ巽ﾆ鍛ﾆ誰  */
			/* CMMif ((nOrigObjMode & OBJ_MASK_2ND) !=
				OBJ_DEF_2ND)
			{
				switch (nOrigObjMode &
					OBJ_MASK_2ND)
				{
					case OBJ_IMAG_2ND:
						nObjMode = OBJ_IMAG;
						break;
					case OBJ_GRAP_2ND:
						nObjMode = OBJ_GRAP;
						break;
					case OBJ_TEXT_2ND:
						nObjMode = OBJ_TEXT;
						break;
					case OBJ_LINE_2ND:
						nObjMode = OBJ_LINE;
						break;
					case OBJ_IMAG_COLOR_2ND:
						nObjMode = OBJ_IMAG; CMM*/
						/* gray mode窶堙戸�冷�ﾃ会ｿｽﾃ昶�ﾃｨ窶堋ｵ窶堙��ﾂｨ窶堋ｭ */
						/* CMMnOrigObjMode =
							OBJ_IMAG_COLOR;
						break;
					case OBJ_IMAG_MONO_2ND:
						nObjMode = OBJ_IMAG; CMM*/
						/* gray mode窶堙戸�冷�ﾃ会ｿｽﾃ昶�ﾃｨ窶堋ｵ窶堙��ﾂｨ窶堋ｭ */
						/* CMMnOrigObjMode =
							OBJ_IMAG_MONO;
						break;
					default:;
						assert (0);
						break;
				}
			}

		}
	} while (bFlag);
#ifdef PR_SUPPORT_FUSER_CTL
	prh->m_objSpool.m_ucFuserCtlFlag &= ucCurFuserCtlFlag;
#endif
	return PR_OK;
}*/


///////////////////////////////////////////////////////////////////////////////
//Function      :SetColorGinfColorMask
//Description   :
//Arguments     :
//              :prh_t *prh:[IN]
//              :int nObjMode:[IN]
//              :uchar *pucFGPointer:[IN]
//              :uchar *pucBGPointer:[IN]
//              :uchar **ppucGamma:[IN]
//              :ginf_t * ginf:[IN]
//              :int nOrigObjMode:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  : void
///////////////////////////////////////////////////////////////////////////////
void CPRColor::SetColorGinfColorMask(unsigned long ulVectorGray,unsigned long ulGrayJudgeMode,
	unsigned char ucColorMode, int	toner_limit, unsigned long ulFlag,
	int nObjMode, unsigned char *pucFGPointer, unsigned char *pucBGPointer,
	unsigned char **ppucGamma, int nOrigObjMode, clr_tlimit_t *pLimit)

 {
	uchar ucFG[4];//, ucBG[4];
	//todo clarification asked to the client
#ifdef SUPPORT_CUTTING_RGBVALUE
		unsigned long ulSrcNot = (ginf->m_ulGraphicColorFlag & COLOR_GRAP_SRCNOT) ?
								GRAP_SRCNOT_ON : GRAP_SRCNOT_OFF;
#endif

	switch (ulFlag & COLOR_MASK)
	{
		case COLOR_GRAY:
#ifndef SUPPORT_COMPOSITEBLACK
	#ifdef DEBUG_SETCOLOR
				printf ("GRAY=(%d)->", pucFGPointer[0]);
	#endif
		;
		assert (pucFGPointer[1] == 0 && pucFGPointer[2] == 0 &&
			pucFGPointer[3] == 0);;
		//assert (pucBGPointer[1] == 0 && pucBGPointer[2] == 0 &&
			//pucBGPointer[3] == 0);
//todo clarification asked to the client
#ifdef SUPPORT_CUTTING_RGBVALUE
		ApplyRgbRatioGray(this, &pucFGPointer[0], 1,
				nObjMode, ulSrcNot);
//		if (ucFlag & COLOR_BGMODE)
//		{
//			ApplyRgbRatioGray(this, &pucBGPointer[0], 1,
//					nObjMode, ulSrcNot);
//		}
#endif
		//DoGammaK (pucFGPointer, pucFGPointer, ppucGamma); //bala todo

//		if (ulFlag & COLOR_BGMODE)
//		{
//			DoGammaK (pucBGPointer, pucBGPointer, ppucGamma);
//		}
		break;
#endif /* SUPPORT_COMPOSITEBLACK */
	case COLOR_RGB:
		// RGB -> CMYK/CMY/RK/K
	#ifdef DEBUG_SETCOLOR
				printf ("RGB=(%d,%d,%d)->", pucFGPointer[0],
					pucFGPointer[1], pucFGPointer[2]);
	#endif
		SetcolorGinfIsColor(ulVectorGray,ulGrayJudgeMode,ucColorMode,toner_limit, ulFlag, nObjMode, pucFGPointer,
								pucBGPointer, ppucGamma, nOrigObjMode, pLimit);
				break;

			case COLOR_CMYK:
				*(int *) ucFG = *(int *) pucFGPointer;
				//*(int *) ucBG = *(int *) pucBGPointer;

				pucFGPointer[0] = ucFG[3];	// ucK
				pucFGPointer[1] = ucFG[0];	// ucC
				pucFGPointer[2] = ucFG[1];	// ucM
				pucFGPointer[3] = ucFG[2];	// ucY
//				pucBGPointer[0] = ucBG[3];	// ucK
//				pucBGPointer[1] = ucBG[0];	// ucC
//				pucBGPointer[2] = ucBG[1];	// ucM
//				pucBGPointer[3] = ucBG[2];	// ucY

				if (ucColorMode == PAGE_COLOR_RK2)
				{
					pucFGPointer[2] = pucFGPointer[3] =
					pucBGPointer[2] = pucBGPointer[3] = 0;
					DoGammaRK2(pucFGPointer, nObjMode,
							toner_limit, pLimit, ppucGamma);
//					if (ulFlag & COLOR_BGMODE)
//					{
//						DoGammaRK2(pucBGPointer, nObjMode,
//								toner_limit,
//								pLimit, ppucGamma);
//					}

				}
				else if (ucColorMode)
				{
					DoGamma(pucFGPointer, nObjMode,toner_limit,
						pLimit, ppucGamma);
//					if (ulFlag & COLOR_BGMODE)
//						DoGamma(pucBGPointer, nObjMode,toner_limit,
//						pLimit, ppucGamma);
				}
				else
				{
					ApplyCmyk2Gray (pucFGPointer);	// KCMY -> GRAY
					DoGammaK (pucFGPointer, pucFGPointer, ppucGamma);
//					if (ulFlag & COLOR_BGMODE)
//					{
//						ApplyCmyk2Gray (pucBGPointer);	// KCMY -> GRAY
//						DoGammaK (pucBGPointer, pucBGPointer, ppucGamma);
//					}
				}
				break;

			default:
				assert (FALSE);
		}
 }

void CPRColor::SetcolorGinfIsColor(unsigned long ulVectorGray,unsigned long ulGrayJudgeMode,
	unsigned char ucColorMode, int toner_limit, unsigned long ulFlag,int nObjMode,unsigned char *pucFGPointer, unsigned char *pucBGPointer, unsigned char **ppucGamma,
	int nOrigObjMode, clr_tlimit_t *pLimit)
 {
	union
	{
		ulong l;
		uchar b[4];
	} fg;
//	union
//	{
//		ulong l;
//		uchar b[4];
//	} bg;
//todo
#ifdef SUPPORT_CUTTING_RGBVALUE
	unsigned long ulSrcNot = (ginf->m_ulGraphicColorFlag & COLOR_GRAP_SRCNOT) ?
							GRAP_SRCNOT_ON : GRAP_SRCNOT_OFF;
#endif
	switch (ucColorMode)
	{
		case PAGE_COLOR_CMYK:
		case PAGE_COLOR_CMY:	/* CMY 窶堙哉丹ﾆ椎槌辰ﾋ�ｳ�ｽﾃｼ窶｢ﾃｻﾅｽﾂｮ窶堙��ﾃ寂�ﾅｾ */
		case PAGE_COLOR_RK2:
		{
			unsigned long ulGmod;

			fg.l = *(ulong *) pucFGPointer;
			//bg.l = 0;//*(ulong *) pucBGPointer;

			/* ﾆ棚ﾆ置ﾆ淡ﾆ巽ﾆ誰ﾆ暖窶突��ﾃ嫁ｽw窶凖ｨ窶堋ｳ窶堙ｪ窶堋ｽﾆ丹ﾆ椎槌辰ﾋ�ｳ�ｽﾃｼ窶｢ﾃｻﾅｽﾂｮ窶堙ｰ窶卍ｲ窶堙冷�ﾃｩ */
			ulGmod = ulVectorGray;
			SetIsGrayJudge (ulGrayJudgeMode, nObjMode);
			switch (nObjMode)
			{
				case OBJ_IMAG:
					ulGmod = GRAY_IMAG_MODE (ulGmod);
					/*
					 * StretchBlt(COLOR)窶堙搾ｿｽﾃｭ窶堙烏RAY_CMYK
					 * StretchBlt(MONO)窶堙隈2Kﾋ�闇�窶堙�RAY_CMYK
					 * 窶堙遺�ﾃ娯�ﾃ��ﾂｮ�ｽﾂｫﾅｽw窶凖ｨ窶堙��ﾃ��ﾂｯ窶罵窶堙娯�ﾂｮ窶堋ｫ窶堙俄�ﾂｷ窶堙ｩ�ｽB
					 */
					switch (nOrigObjMode &
						OBJ_MASK_1ST)
					{
						case OBJ_IMAG_COLOR:
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
						case OBJ_IMAG_MONO:
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
				case OBJ_GRAP:
					ulGmod = GRAY_GRAP_MODE (ulGmod);
					break;
				case OBJ_TEXT:
					ulGmod = GRAY_TEXT_MODE (ulGmod);
					break;
				case OBJ_LINE:
					ulGmod = GRAY_LINE_MODE (ulGmod);
					break;
			}
			//m_psCmmColor = &(prh->m_objCmm);
			//m_psCmmColor->m_ulCurId = Cmmprofiles(nObjMode);


			if ((ulFlag & COLOR_MASK) == COLOR_GRAY)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this,
					&pucFGPointer[0], 1, nObjMode, ulSrcNot);
#endif
				DoGammaK(pucFGPointer, pucFGPointer, ppucGamma);
//				if (ulFlag & COLOR_BGMODE)
//				{
//#ifdef SUPPORT_CUTTING_RGBVALUE
//					ApplyRgbRatioGray(this,
//						&pucBGPointer[0], 1,
//						nObjMode, ulSrcNot);
//#endif
//					DoGammaK(pucBGPointer, pucBGPointer, ppucGamma);
//				}
				break;
			}
			else if ((ulFlag & COLOR_MASK) == COLOR_RGB)
			{
			/* ﾅｽw窶凖ｨ窶堋ｳ窶堙ｪ窶堋ｽﾆ丹ﾆ椎槌辰ﾋ�ｳ�ｽﾃｼ窶｢ﾃｻﾅｽﾂｮ窶堙�RGB->CMYK 窶｢ﾃ焦�ｷ窶堋ｷ窶堙ｩ */
			switch (ulGmod)
			{
				case GRAY_G2K:
				case GRAY_PIXELK:
				case GRAY_MAYBEK:
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyBgucrKeepgray (fg.b, pucFGPointer, nObjMode, ulSrcNot);
					//ApplyBgucrKeepgray (bg.b, pucBGPointer, nObjMode, ulSrcNot);
#else
					ApplyBgucrKeepgray (fg.b, pucFGPointer);
					//ApplyBgucrKeepgray (bg.b, pucBGPointer);
#endif
					break;
				case GRAY_HGRG2K:
					ApplyBgucrHgrKeepgray (fg.b, pucFGPointer);
					//ApplyBgucrHgrKeepgray (bg.b, pucBGPointer);
					break;
				case GRAY_CMYK:
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyBgucr (fg.b, pucFGPointer, nObjMode, ulSrcNot);
					//ApplyBgucr (bg.b, pucBGPointer, nObjMode, ulSrcNot);
#else
					ApplyBgucr (fg.b, pucFGPointer);
					//ApplyBgucr (bg.b, pucBGPointer);
#endif
					break;
				case GRAY_HGRCMYK:
					ApplyBgucrHgr (fg.b, pucFGPointer);
					//ApplyBgucrHgr (bg.b, pucBGPointer);
					break;
				case GRAY_CMY:
					ApplyRgb2Cmy (fg.b, pucFGPointer);
					//ApplyRgb2Cmy (bg.b, pucBGPointer);
					break;
				case GRAY_K2K:
				case GRAY_IMAGEK:
					ApplyBgucrKeepblack (fg.b, pucFGPointer);
					//ApplyBgucrKeepblack (bg.b, pucBGPointer);
					break;
				case GRAY_ABOUTK:
					ApplyBgucrAboutKeepgray (fg.b,
						pucFGPointer);
					//ApplyBgucrAboutKeepgray (bg.b,
						//pucBGPointer);
					break;
			}
		}

			if (ucColorMode == PAGE_COLOR_RK2)
			{
				pucFGPointer[2] = pucFGPointer[3] = 0;
				//pucBGPointer[2] = pucBGPointer[3] = 0;
				DoGammaRK2(pucFGPointer, nObjMode, toner_limit,
					pLimit, ppucGamma);
				//if (ulFlag & COLOR_BGMODE)
					//DoGammaRK2(pucBGPointer, nObjMode, toner_limit, pLimit, ppucGamma);
			}
			else
			{
				DoGamma(pucFGPointer, nObjMode, toner_limit,
					pLimit, ppucGamma);
				//if (ulFlag & COLOR_BGMODE)
					//DoGamma(pucBGPointer, nObjMode, toner_limit, pLimit, ppucGamma);
			}
			break;

		}
		case PAGE_COLOR_RK:
		{
			fg.l = *(ulong *) pucFGPointer;
			//bg.l = *(ulong *) pucBGPointer;

			ApplyTwinColorGammas (this, &fg.b[0], &fg.b[1],
				&fg.b[2], pucFGPointer, pucFGPointer + 1, 1, ppucGamma);
			//ApplyTwinColorGammas (this, &bg.b[0], &bg.b[1],
				//&bg.b[2], pucBGPointer, pucBGPointer + 1, 1, ppucGamma);
			pucFGPointer[2] = pucFGPointer[3] = 0; //pucBGPointer[2] = pucBGPointer[3] = 0;

			break;
		}
		case PAGE_COLOR_K:
#ifdef SUPPORT_CUTTING_RGBVALUE
			// RGB -> GRAY
			ApplyRgb2Gray (this, pucFGPointer, nObjMode, ulSrcNot);
#else
			ApplyRgb2Gray (pucFGPointer);	// RGB -> GRAY
#endif
			DoGammaK (pucFGPointer, pucFGPointer, ppucGamma);
//			if (ulFlag & COLOR_BGMODE)
//			{
//#ifdef SUPPORT_CUTTING_RGBVALUE
//				// RGB -> GRAY
//				ApplyRgb2Gray (this, pucBGPointer, nObjMode, ulSrcNot);
//#else
//				ApplyRgb2Gray (pucBGPointer);	// RGB -> GRAY
//#endif
//				DoGammaK (pucBGPointer, pucBGPointer, ppucGamma);
//			}
			break;
		default:;
			assert (0);
	}

 }

void CPRColor::SetIsGrayJudge (unsigned long ulGrayJudgeMode, int nObjMode)
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




///////////////////////////////////////////////////////////////////////////////
//Function      :SetColorGinfColorMask
//Description   : 
//Arguments     :
//              :prh_t *prh:[IN]
//              :int nObjMode:[IN]
//              :uchar *pucFGPointer:[IN]
//              :uchar *pucBGPointer:[IN]
//              :uchar **ppucGamma:[IN]
//              :ginf_t * ginf:[IN]
//              :int nOrigObjMode:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  : void 
///////////////////////////////////////////////////////////////////////////////
/* CMM void CPRColor::SetColorGinfColorMask(prh_t *prh,
	int nObjMode, uchar *pucFGPointer, uchar *pucBGPointer,
	uchar **ppucGamma, ginf_t * ginf, int
	nOrigObjMode, clr_tlimit_t *pLimit)

{

	//CPRColor* cur_color = (CPRColor*) &(prh->m_objColor);
	uchar ucFG[4], ucBG[4];
#ifdef SUPPORT_CUTTING_RGBVALUE
	unsigned long ulSrcNot = (ginf->m_ulGraphicColorFlag & COLOR_GRAP_SRCNOT) ?
							GRAP_SRCNOT_ON : GRAP_SRCNOT_OFF;
#endif
	// clr_tlimit_t pLimit;
	switch (ginf->m_ucFlag & COLOR_MASK)
	{
		case COLOR_GRAY:
#ifndef SUPPORT_COMPOSITEBLACK
#ifdef DEBUG_SETCOLOR
			printf ("GRAY=(%d)->", pucFGPointer[0]);
#endif
			;
			assert (pucFGPointer[1] == 0 && pucFGPointer[2] == 0 &&
				pucFGPointer[3] == 0);;
			assert (pucBGPointer[1] == 0 && pucBGPointer[2] == 0 &&
				pucBGPointer[3] == 0);

#ifdef	PR_HAVE_XRGB_DRAW
			if (prh->m_objRender.m_ucIsColor !=
				PAGE_COLOR_XRGB)
			{
#endif

#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this, &pucFGPointer[0], 1,
						nObjMode, ulSrcNot);
				if (ginf->m_ucFlag & COLOR_BGMODE)
				{
					ApplyRgbRatioGray(this, &pucBGPointer[0], 1,
							nObjMode, ulSrcNot);
				}
#endif
				DoGammaK (pucFGPointer, pucFGPointer, ppucGamma);

				if (ginf->m_ucFlag & COLOR_BGMODE)
				{
					DoGammaK (pucBGPointer, pucBGPointer, ppucGamma);
				}

#ifdef	PR_HAVE_XRGB_DRAW
			}
#endif
			break;
#endif CMM*//* SUPPORT_COMPOSITEBLACK */

		/* CMM case COLOR_RGB:
			// RGB -> CMYK/CMY/RK/K
#ifdef DEBUG_SETCOLOR
			printf ("RGB=(%d,%d,%d)->", pucFGPointer[0],
				pucFGPointer[1], pucFGPointer[2]);
#endif
			SetcolorGinfIsColor(prh, nObjMode, pucFGPointer,
				pucBGPointer, ppucGamma, nOrigObjMode, pLimit,
				ginf);
			break;

		case COLOR_CMYK:
			*(int *) ucFG = *(int *) pucFGPointer;
			*(int *) ucBG = *(int *) pucBGPointer;

			pucFGPointer[0] = ucFG[3];	// ucK
			pucFGPointer[1] = ucFG[0];	// ucC
			pucFGPointer[2] = ucFG[1];	// ucM
			pucFGPointer[3] = ucFG[2];	// ucY
			pucBGPointer[0] = ucBG[3];	// ucK
			pucBGPointer[1] = ucBG[0];	// ucC
			pucBGPointer[2] = ucBG[1];	// ucM
			pucBGPointer[3] = ucBG[2];	// ucY

			if (prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK2)
			{
				pucFGPointer[2] = pucFGPointer[3] = 
				pucBGPointer[2] = pucBGPointer[3] = 0;
				DoGammaRK2(pucFGPointer, nObjMode,
						prh->m_objJobCtrl.GetTonerLimit(), pLimit, ppucGamma);
				if (ginf->m_ucFlag & COLOR_BGMODE)
				{
					DoGammaRK2(pucBGPointer, nObjMode,
							prh->m_objJobCtrl.GetTonerLimit(),
							pLimit, ppucGamma);
				}
				
			}
			else if (prh->m_objRender.m_ucIsColor)
			{
				DoGamma(pucFGPointer, nObjMode, prh->m_objJobCtrl.GetTonerLimit(),
					pLimit, ppucGamma);
				if (ginf->m_ucFlag & COLOR_BGMODE)
					DoGamma(pucBGPointer, nObjMode, prh->m_objJobCtrl.GetTonerLimit(),
					pLimit, ppucGamma);
			}
			else
			{
				ApplyCmyk2Gray (pucFGPointer);	// KCMY -> GRAY
				DoGammaK (pucFGPointer, pucFGPointer, ppucGamma);
				if (ginf->m_ucFlag & COLOR_BGMODE)
				{
					ApplyCmyk2Gray (pucBGPointer);	// KCMY -> GRAY
					DoGammaK (pucBGPointer, pucBGPointer, ppucGamma);
				}
			}
			break;

		default:;
			assert (FALSE);
	}
} CMM*/

///////////////////////////////////////////////////////////////////////////////
//Function      :SetcolorGinfIsColor
//Description   : 
//Arguments     :
//              :prh_t *prh:[IN]
//              :int nObjMode:[IN]
//              :uchar *pucFGPointer:[IN]
//              :uchar *pucBGPointer:[IN]
//              :uchar **ppucGamma:[IN]
//              :int nOrigObjMode:[IN]
//              :clr_tlimit_t *pLimit:[IN]
//              :ginf_t * ginf:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
/* CMMvoid CPRColor::SetcolorGinfIsColor(prh_t *prh, int
	nObjMode, uchar *pucFGPointer, uchar *pucBGPointer, uchar **ppucGamma,
	int nOrigObjMode, clr_tlimit_t *pLimit, ginf_t
	* ginf)
{
	union
	{
		ulong l;
		uchar b[4];
	} fg;
	union
	{
		ulong l;
		uchar b[4];
	} bg;
#ifdef SUPPORT_CUTTING_RGBVALUE
	unsigned long ulSrcNot = (ginf->m_ulGraphicColorFlag & COLOR_GRAP_SRCNOT) ?
							GRAP_SRCNOT_ON : GRAP_SRCNOT_OFF;
#endif
	switch (prh->m_objRender.m_ucIsColor)
	{
		case PAGE_COLOR_CMYK:
		case PAGE_COLOR_CMY:	CMM*//* CMY 窶堙哉丹ﾆ椎槌辰ﾋ�ｳ�ｽﾃｼ窶｢ﾃｻﾅｽﾂｮ窶堙��ﾃ寂�ﾅｾ */
		/* CMMcase PAGE_COLOR_RK2:
		{
			ulong ulGmod;

			fg.l = *(ulong *) pucFGPointer;
			bg.l = *(ulong *) pucBGPointer; CMM*/

			/* ﾆ棚ﾆ置ﾆ淡ﾆ巽ﾆ誰ﾆ暖窶突��ﾃ嫁ｽw窶凖ｨ窶堋ｳ窶堙ｪ窶堋ｽﾆ丹ﾆ椎槌辰ﾋ�ｳ�ｽﾃｼ窶｢ﾃｻﾅｽﾂｮ窶堙ｰ窶卍ｲ窶堙冷�ﾃｩ */
			/* CMMulGmod = prh->m_objPageCtrl.GetVectorGray();
			SetIsGrayJudge (prh, nObjMode);
			switch (nObjMode)
			{
				case OBJ_IMAG:
					ulGmod = GRAY_IMAG_MODE (ulGmod); CMM*/
					/*
					 * StretchBlt(COLOR)窶堙搾ｿｽﾃｭ窶堙烏RAY_CMYK
					 * StretchBlt(MONO)窶堙隈2Kﾋ�闇�窶堙�RAY_CMYK
					 * 窶堙遺�ﾃ娯�ﾃ��ﾂｮ�ｽﾂｫﾅｽw窶凖ｨ窶堙��ﾃ��ﾂｯ窶罵窶堙娯�ﾂｮ窶堋ｫ窶堙俄�ﾂｷ窶堙ｩ�ｽB
					 */
					/* CMM switch (nOrigObjMode &
						OBJ_MASK_1ST)
					{
						case OBJ_IMAG_COLOR: CMM*/
						/* ABOUTK窶堙姑辰ﾆ抵ｿｽ�ｽ[ﾆ淡窶堙宏2K窶堙��ﾂｯ窶堋ｶ
						   MAYBEK窶堙行etcolor窶堙俄�ﾃ坂�K窶牌窶堙遺�ﾂ｢ */
							/* CMMif ((ulGmod != GRAY_CMY)
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
						case OBJ_IMAG_MONO:
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
						default: CMM*/
							/* Stretchblt, Bitblt窶堙遺�ﾃｧ窶堋ｱ窶堋ｿ窶堙ｧ */
							/* CMMbreak;
					}
					break;
				case OBJ_GRAP:
					ulGmod = GRAY_GRAP_MODE (ulGmod);
					break;
				case OBJ_TEXT:
					ulGmod = GRAY_TEXT_MODE (ulGmod);
					break;
				case OBJ_LINE:
					ulGmod = GRAY_LINE_MODE (ulGmod);
					break;
			}
			m_psCmmColor = &(prh->m_objCmm);
			m_psCmmColor->m_ulCurId = Cmmprofiles
			(nObjMode);
			
#ifdef SUPPORT_COMPOSITEBLACK
			if (ulGmod == GRAY_COMPBK)
			{
				if (CheckCompbk() == TRUE)
				{
					if ((ginf->m_ucFlag & COLOR_MASK)
						== COLOR_GRAY)
					{ CMM*/
						/* Gray->RGB */
						/*CMMfg.b[0] = fg.b[1] =
						fg.b[2] = 255 - *pucFGPointer;
						fg.b[3] = 0;
						bg.b[0] = bg.b[1] =
						bg.b[2] = 255 - *pucBGPointer;
						bg.b[3] = 0;
					}
					ApplyBgucrCompbk(&fg.b[0], pucFGPointer,
						nObjMode, ulSrcNot);
					ApplyBgucrCompbk(&bg.b[0], pucBGPointer,
						nObjMode, ulSrcNot);
					break;
				}
				else
				{
					if (m_ucRenderingIsmono
					    && ((ginf->m_ucFlag & COLOR_MASK)
						== COLOR_RGB))
					{
#ifdef SUPPORT_CUTTING_RGBVALUE
						ApplyRgb2Gray(
							this,
							pucFGPointer,
							nObjMode,
							ulSrcNot);
#else
						ApplyRgb2Gray(pucFGPointer);
#endif
						DoGammaK(pucFGPointer, pucFGPointer,
							ppucGamma);
						if (ginf->m_ucFlag &
							COLOR_BGMODE)
						{
#ifdef SUPPORT_CUTTING_RGBVALUE
						    ApplyRgb2Gray(
								this,
								pucBGPointer,
								nObjMode,
								ulSrcNot);
#else
						    ApplyRgb2Gray(pucBGPointer);
#endif
						    DoGammaK(pucBGPointer, pucBGPointer,
								ppucGamma);
						}
						break;
					}
					ulGmod = GRAY_G2K;
				}
			}
			if ((ginf->m_ucFlag & COLOR_MASK) == COLOR_GRAY)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this,
					&pucFGPointer[0], 1, nObjMode, ulSrcNot);
#endif
				DoGammaK(pucFGPointer, pucFGPointer, ppucGamma);
				if (ginf->m_ucFlag & COLOR_BGMODE)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioGray(this,
						&pucBGPointer[0], 1,
						nObjMode, ulSrcNot);
#endif
					DoGammaK(pucBGPointer, pucBGPointer, ppucGamma);
				}
				break;
			}
			else if ((ginf->m_ucFlag & COLOR_MASK) == COLOR_RGB)
			{
#endif CMM*//* SUPPORT_COMPOSITEBLACK */
			/* ﾅｽw窶凖ｨ窶堋ｳ窶堙ｪ窶堋ｽﾆ丹ﾆ椎槌辰ﾋ�ｳ�ｽﾃｼ窶｢ﾃｻﾅｽﾂｮ窶堙�RGB->CMYK 窶｢ﾃ焦�ｷ窶堋ｷ窶堙ｩ */
			/* CMMswitch (ulGmod)
			{
				case GRAY_G2K:
				case GRAY_PIXELK:
				case GRAY_MAYBEK:
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyBgucrKeepgray (fg.b, pucFGPointer, nObjMode, ulSrcNot);
					ApplyBgucrKeepgray (bg.b, pucBGPointer, nObjMode, ulSrcNot);
#else
					ApplyBgucrKeepgray (fg.b, pucFGPointer);
					ApplyBgucrKeepgray (bg.b, pucBGPointer);
#endif
					break;
				case GRAY_HGRG2K:
					ApplyBgucrHgrKeepgray (fg.b, pucFGPointer);
					ApplyBgucrHgrKeepgray (bg.b, pucBGPointer);
					break;
				case GRAY_CMYK:
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyBgucr (fg.b, pucFGPointer, nObjMode, ulSrcNot);
					ApplyBgucr (bg.b, pucBGPointer, nObjMode, ulSrcNot);
#else
					ApplyBgucr (fg.b, pucFGPointer);
					ApplyBgucr (bg.b, pucBGPointer);
#endif
					break;
				case GRAY_HGRCMYK:
					ApplyBgucrHgr (fg.b, pucFGPointer);
					ApplyBgucrHgr (bg.b, pucBGPointer);
					break;
				case GRAY_CMY:
					ApplyRgb2Cmy (fg.b, pucFGPointer);
					ApplyRgb2Cmy (bg.b, pucBGPointer);
					break;
				case GRAY_K2K:
				case GRAY_IMAGEK:
					ApplyBgucrKeepblack (fg.b, pucFGPointer);
					ApplyBgucrKeepblack (bg.b, pucBGPointer);
					break;
				case GRAY_ABOUTK:
					ApplyBgucrAboutKeepgray (fg.b,
						pucFGPointer);
					ApplyBgucrAboutKeepgray (bg.b,
						pucBGPointer);
					break;
			}

			if (prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK2)
			{
				pucFGPointer[2] = pucFGPointer[3] =
				pucBGPointer[2] = pucBGPointer[3] = 0;
				DoGammaRK2(pucFGPointer, nObjMode, prh->m_objJobCtrl.GetTonerLimit(),
					pLimit, ppucGamma);
				if (ginf->m_ucFlag & COLOR_BGMODE)
					DoGammaRK2(pucBGPointer, nObjMode, prh->m_objJobCtrl.
						GetTonerLimit(), pLimit, ppucGamma);
			}
			else
			{
				DoGamma(pucFGPointer, nObjMode, prh->m_objJobCtrl.GetTonerLimit(),
					pLimit, ppucGamma);
				if (ginf->m_ucFlag & COLOR_BGMODE)
					DoGamma(pucBGPointer, nObjMode, prh->m_objJobCtrl.
						GetTonerLimit(), pLimit, ppucGamma);
			}
			break;
#ifdef	SUPPORT_COMPOSITEBLACK
			}
#endif
		}
#ifdef	PR_HAVE_XRGB_DRAW
		case PAGE_COLOR_XRGB:
		{
			int Attr;

			fg.l = *(ulong *) pucFGPointer;
			bg.l = *(ulong *) pucBGPointer;

			if (nObjMode == OBJ_IMAG)
			{
				SetXRGBbyPixel(this, XRGB_ATTR_IMAGE, &fg.b[0], pucFGPointer);
			}
			else
			{
				if (pucFGPointer[0] == pucFGPointer[1] && pucFGPointer[1] ==
					pucFGPointer[2])
				{
					Attr = pucFGPointer[0] == 0xff ?
					XRGB_ATTR_WHITE : XRGB_ATTR_K1;
				}
				else
				{
					Attr = XRGB_ATTR_OTHER;
				}
				SetXRGBbyPixel(this, Attr, &fg.b[0], pucFGPointer);
			}

			if (pucBGPointer[0] == pucBGPointer[1] && pucBGPointer[1] == 
					pucBGPointer[2])
			{
				Attr = pucBGPointer[0] == 0xff ?
				XRGB_ATTR_WHITE : XRGB_ATTR_K1;
			}
			else
			{
				Attr = XRGB_ATTR_OTHER;
			}
			SetXRGBbyPixel(this, Attr, &bg.b[0], pucBGPointer);
			break;
		}
#endif
		case PAGE_COLOR_RK:
		{
			fg.l = *(ulong *) pucFGPointer;
			bg.l = *(ulong *) pucBGPointer;

			ApplyTwinColorGammas (this, &fg.b[0], &fg.b[1],
				&fg.b[2], pucFGPointer, pucFGPointer + 1, 1, ppucGamma);
			ApplyTwinColorGammas (this, &bg.b[0], &bg.b[1],
				&bg.b[2], pucBGPointer, pucBGPointer + 1, 1, ppucGamma);
			pucFGPointer[2] = pucFGPointer[3] = pucBGPointer[2] = 
													pucBGPointer[3] = 0;

			break;
		}
		case PAGE_COLOR_K:
#ifdef SUPPORT_COMPOSITEBLACK
			if ((ginf->m_ucFlag & COLOR_MASK) == COLOR_GRAY)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				ApplyRgbRatioGray(this,
					&pucFGPointer[0], 1, nObjMode, ulSrcNot);
#endif
				DoGammaK(pucFGPointer, pucFGPointer, ppucGamma);
				if (ginf->m_ucFlag & COLOR_BGMODE)
				{
#ifdef SUPPORT_CUTTING_RGBVALUE
					ApplyRgbRatioGray(this,
						&pucBGPointer[0], 1,
						nObjMode, ulSrcNot);
#endif
					DoGammaK(pucBGPointer, pucBGPointer, ppucGamma);
				}
			}
			else
			{
#endif
#ifdef SUPPORT_CUTTING_RGBVALUE
			// RGB -> GRAY
			ApplyRgb2Gray (this, pucFGPointer, nObjMode, ulSrcNot);
#else
			ApplyRgb2Gray (pucFGPointer);	// RGB -> GRAY
#endif
			DoGammaK (pucFGPointer, pucFGPointer, ppucGamma);
			if (ginf->m_ucFlag & COLOR_BGMODE)
			{
#ifdef SUPPORT_CUTTING_RGBVALUE
				// RGB -> GRAY
				ApplyRgb2Gray (this, pucBGPointer, nObjMode, ulSrcNot);
#else
				ApplyRgb2Gray (pucBGPointer);	// RGB -> GRAY
#endif
				DoGammaK (pucBGPointer, pucBGPointer, ppucGamma);
			}
#ifdef SUPPORT_COMPOSITEBLACK
			}
#endif
			break;
		default:;
			assert (0);
	}
} CMM */

///////////////////////////////////////////////////////////////////////////////
//Function      :SetcolorGinfColorGradation
//Description   : 
//Arguments     :
//              :prh_t *prh:[IN]
//              :ginf_t *ginf:[IN]
//              :clr_tlimit_t *pLimit:[IN]
//              :int	nObjMode:[IN]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error 
///////////////////////////////////////////////////////////////////////////////
/* CMMint CPRColor::SetcolorGinfColorGradation(prh_t *prh,
	ginf_t *ginf, clr_tlimit_t *pLimit, int
	nObjMode)
{
	// setting color processing parameter for despool
	if(SetcolorGinfForDespool(prh, ginf, pLimit, nObjMode) == PR_ERROR)
	{
		return PR_ERROR;
	}
	
	//RGB窶堙��ﾃ遺�ﾂｯ窶堙ｪ窶堙擦MM窶堙弘FF
	if((ginf->m_objGra.m_sGradationInfo.ucGradationFlag
				& COLOR_MASK) != COLOR_RGB)
	{
		ginf->m_ulColorFlag &= ~(CR_CMM_ON);
	}
	
	switch (prh->m_objRender.m_ucIsColor)
	{
		case PAGE_COLOR_K:
			ginf->m_ulColorFlag |=
				CR_OUTPUT_SPACE_MONO;
			break;
		case PAGE_COLOR_CMYK:
			ginf->m_ulColorFlag |=
				CR_OUTPUT_SPACE_CMYK;
			break;
		case PAGE_COLOR_CMY:
			ginf->m_ulColorFlag |=
				CR_OUTPUT_SPACE_CMY;
			break;
		case PAGE_COLOR_RK:
			ginf->m_ulColorFlag |=
				CR_OUTPUT_SPACE_RK;
			break;
		case PAGE_COLOR_RK2:
			ginf->m_ulColorFlag |=
				CR_OUTPUT_SPACE_RK2;
			break;
#ifdef	PR_HAVE_XRGB_DRAW
		case PAGE_COLOR_XRGB:
			ginf->m_ulColorFlag |=
				CR_OUTPUT_SPACE_XRGB;
			break;
#endif
		default:;
			assert (0);
			break;
	}
	switch (ginf->m_objGra.m_sGradationInfo.ucGradationFlag
		& COLOR_MASK)
	{
		case COLOR_GRAY:
			ginf->m_ulColorFlag |=
				CR_INPUT_SPACE_GRAY;
			break;
		case COLOR_RGB:
			ginf->m_ulColorFlag |=
				CR_INPUT_SPACE_RGB;
			break;
		case COLOR_CMYK:
			ginf->m_ulColorFlag |=
				CR_INPUT_SPACE_CMYK;
			break;
		default:;
			assert (0);
			break;
	}CMM*/
	/* �ｽo窶氾搾ｿｽF窶ｹﾃｳﾅ�費ｿｽA窶愿ｼ窶氾搾ｿｽF窶ｹﾃｳﾅ�披�ﾃ娯�ﾃ��ﾃ�ﾆ丹ﾆ停�ﾆ断�ｽ[ﾆ歎ﾆ停�ﾆ停�窶堙��ﾃ最津��ﾃｨ) */
	/* CMMginf->m_ulColorFlag |= CR_OUTPUT_ORDER_REVERSE
		| CR_INPUT_ORDER_NORMAL;
	
	if ((prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK) ||
		(prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK2))
#ifndef X86
		Used_plane |= 0xffff0000;
#else // X86
		Used_plane |= 0x0000ffff;
#endif // X86
	else if (prh->m_objRender.m_ucIsColor ==
		PAGE_COLOR_K)
#ifndef X86
		Used_plane |= 0xff000000;
#else // X86
		Used_plane |= 0x000000ff;
#endif
	else
		Used_plane |= 0xffffffff;
#ifdef PR_SUPPORT_FUSER_CTL CMM*/
	/*
	* fuser temperature controlling function(TEC) not support
	* for gradation
	*/
	/* CMMprh->m_objSpool.m_ucFuserCtlFlag = PR_DEGREEDOWN_OFF;
#endif
	return PR_OK;
} CMM*/

///////////////////////////////////////////////////////////////////////////////
//Function      :SetcolorGinfForDespool
//Description   : set color information to process  color for despool
//Arguments     :
//              :prh_t *prh:[IN]
//              :ginf_t *ginf:[IN]
//              :clr_tlimit_t *pLimit:[IN]
//              :int	nObjMode:[IN]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error 
///////////////////////////////////////////////////////////////////////////////
/* CMMint CPRColor::SetcolorGinfForDespool(prh_t *prh,
	ginf_t *ginf, clr_tlimit_t *pLimit, int
	nObjMode)
{
	ulong ulGmod;
	unsigned char ucUseUGamma = FALSE, ucDitMod = 0;
	int nI;
	// set gamma for despool
	if ((prh->m_objRender.m_objGamma.UpdateSysGammaList(prh, nObjMode) == PR_ERROR) ||
		(prh->m_objRender.m_objGamma.UpdateUserGammaList(prh, nObjMode) == PR_ERROR))
	{
		CPRDeCache objDECache;
		objDECache.ClearDE(prh);
		if ((prh->m_objRender.m_objGamma.UpdateSysGammaList(prh, nObjMode) == PR_ERROR) ||
			(prh->m_objRender.m_objGamma.UpdateUserGammaList(prh, nObjMode) == PR_ERROR))
		{
			return PR_ERROR;
		}
	}
	
	for (nI = 0; nI < prh->m_objRender.m_nNColor; ++nI)
	{
		ginf->m_pucGamma[nI] =
			prh->m_objRender.m_objGamma.m_pucCurSysGammaList[nObjMode][nI];
		ginf->m_pucGamma[RENDER_N_COLOR+nI] = 
			prh->m_objRender.m_objGamma.m_pucCurUserGammaList[nObjMode][nI];
		if (ginf->m_pucGamma[RENDER_N_COLOR+nI] != NULL)
		{
			ucUseUGamma = TRUE;
		}
	}
	ginf->m_ulColorFlag = 0;
	
	//set color processing flag
	
	//ﾆ停��ｽ[ﾆ旦�ｽ[ﾆ津�稚ﾆ停�ﾆ丹
	if (ucUseUGamma == TRUE)
	{
		ginf->m_ulColorFlag |= CR_UGAMMA_ON;
	}
	else
	{
		ginf->m_ulColorFlag |= CR_UGAMMA_OFF;
	}
	
	//窶假ｿｽ窶氾岩�K�ｽﾂｧﾆ稚ﾆ停�ﾆ丹
	if (prh->m_objJobCtrl.GetTonerLimit())
		ginf->m_ulColorFlag |= CR_TONERLIMIT_ON;
	else
		ginf->m_ulColorFlag |= CR_TONERLIMIT_OFF;
	
	//ﾆ歎ﾆ湛ﾆ弾ﾆ停ぎﾆ津�稚ﾆ停�ﾆ丹
	if (prh->m_objRender.m_objGamma.m_ucGammaThrough)
		ginf->m_ulColorFlag |= CR_GAMMA_OFF;
	else
		ginf->m_ulColorFlag |= CR_GAMMA_ON;
	
	//窶假ｿｽ窶氾岩�K�ｽﾂｧ窶冤 & Diter Mode & Gray Mode
	ulGmod = prh->m_objPageCtrl.GetVectorGray();
	switch (nObjMode)
	{
	case OBJ_IMAG:
		ginf->m_siColorLimit = pLimit->phot;
		ucDitMod = DIT_IMAG_MODE (prh->m_pobjGinf->m_ucDither);
		ulGmod = GRAY_IMAG_MODE (ulGmod);
		break;
	case OBJ_GRAP:
		ginf->m_siColorLimit = pLimit->fill;
		ucDitMod = DIT_GRAP_MODE (prh->m_pobjGinf->m_ucDither);
		ulGmod = GRAY_GRAP_MODE (ulGmod);
		break;
	case OBJ_TEXT:
		ginf->m_siColorLimit = pLimit->text;
		ucDitMod = DIT_TEXT_MODE (prh->m_pobjGinf->m_ucDither);
		ulGmod = GRAY_TEXT_MODE (ulGmod);
		break;
	case OBJ_LINE:
		ginf->m_siColorLimit = pLimit->line;
		ucDitMod = DIT_LINE_MODE (prh->m_pobjGinf->m_ucDither);
		ulGmod = GRAY_LINE_MODE (ulGmod);
		break;
	default:;
		assert (0);
		break;
	}
	
	// Dither Mode
	switch (ucDitMod)
	{
	case DIT_PHOT:
		ginf->m_ulColorFlag |= CR_DIT_PHOT;
		break;
	case DIT_TEXT:
		ginf->m_ulColorFlag |= CR_DIT_TEXT;
		break;
	case DIT_GRAP:
		ginf->m_ulColorFlag |= CR_DIT_GRAP;
		break;
	case DIT_CAD:
	default:
		assert(0);
		break;
	}
	
	//ﾆ丹ﾆ椎槌辰ﾆ停��ｽ[ﾆ檀
	switch (ulGmod)
	{
	case GRAY_G2K:
		ginf->m_ulColorFlag |= CR_GRAYP_G2K;
		break;
	case GRAY_HGRG2K:
		ginf->m_ulColorFlag |= CR_GRAYP_HGRG2K;
		break;
	case GRAY_CMYK:
		ginf->m_ulColorFlag |= CR_GRAYP_CMYK;
		break;
	case GRAY_HGRCMYK:
		ginf->m_ulColorFlag |= CR_GRAYP_HGRCMYK;
		break;
	case GRAY_K2K:
		ginf->m_ulColorFlag |= CR_GRAYP_K2K;
		break;
	case GRAY_CMY:
		ginf->m_ulColorFlag |= CR_GRAYP_CMY;
		break;
	case GRAY_IMAGEK:
		ginf->m_ulColorFlag |= CR_GRAYP_IMAGEK;
		break;
	case GRAY_PIXELK:
		ginf->m_ulColorFlag |= CR_GRAYP_PIXELK;
		break;
	case GRAY_MAYBEK:
		ginf->m_ulColorFlag |= CR_GRAYP_MAYBEK;
		break;
	case GRAY_ABOUTK:
		ginf->m_ulColorFlag |= CR_GRAYP_ABOUTK;
		break;
	default:
		break;
	} CMM*/
	/*
	 * CMM,Profile 窶堙鯉ｿｽﾃ昶�ﾃｨ
	 */
	/* CMMif (prh->m_objCmm.m_lIsCmm && 
		((prh->m_objRender.m_ucIsColor == PAGE_COLOR_CMY) ||
			(prh->m_objRender.m_ucIsColor == PAGE_COLOR_CMYK)) &&
		(m_psCmmColor))
	{
		ginf->m_ulColorFlag |= CR_CMM_ON;
		ginf->m_ulCmmProfileId = m_psCmmColor->m_ulCmmProfiles[nObjMode];
		ginf->m_ulColorFlag |= (m_ucIsGrayJudge == CR_JUDGE_GRAY_AFTER_CMM_ON) 
			? CR_JUDGE_GRAY_ON : CR_JUDGE_GRAY_OFF;
	}
	else
	{
		ginf->m_ulColorFlag |= CR_CMM_OFF;
		ginf->m_ulColorFlag |= CR_JUDGE_GRAY_OFF;
	}
#ifdef PR3_SUPPORT_GIPA1
	//Mask
	ginf->m_uTransColor.l = prh->m_objPageCtrl.m_uTransColor.l;
#endif //PR3_SUPPORT_GIPA1
	return PR_OK;
} CMM*/

///////////////////////////////////////////////////////////////////////////////
//Function      :PrRgb2Cmyk 
//Description   : 
//Arguments     :
//              :prh_t * prh:[IN]
//              :uchar obj:[IN]
//              :uchar r:[IN]
//              :uchar g:[IN]
//              :uchar b:[IN]
//              :uchar * pucC:[OUT]
//              :uchar * pucM:[OUT]
//              :uchar * pucY:[OUT]
//              :uchar * pucK):[OUT]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
/* CMM int
PrRgb2Cmyk (prh_t * prh,
	uchar obj,
	uchar r,		 
	uchar g,		 
	uchar b,		 
	uchar * pucC,	 
	uchar * pucM,	 
	uchar * pucY,	 
	uchar * pucK)	 

{
	union
	{
		ulong l;
		uchar b[4];
	} rgb;
	union
	{
		ulong l;
		uchar b[4];
	} kcmy;
	int graymode;
	uchar **ppucGamma;
	clr_tlimit_t pLimit;
	CPRColor* cur_color = (CPRColor*) &(prh->m_objColor);
	ginf_t *ginf;
	unsigned char ucDitherMode;

	if (!pucC || !pucM || !pucY || !pucK)
	{
		error(prh->m_objError.m_ulErrCode =
				PR_ERR_SYNTAX);
		return (PR_ERROR);
	}


	switch (obj & PR_OBJ_MASK)
	{
		case PR_OBJ_IMAG:
			graymode = GRAY_IMAG_MODE (prh->m_objPageCtrl.GetVectorGray());
			switch (graymode)
			{
				case PR_GRAY_G2K:
#ifdef SUPPORT_COMPOSITEBLACK
				case PR_GRAY_COMPBK:
#endif
					if (obj & OBJ_MONOIMAGE)
						break;
				case PR_GRAY_K2K:
					graymode = PR_GRAY_CMYK;
					break;
				case PR_GRAY_HGRG2K:
					if (obj & OBJ_MONOIMAGE)
						break;
					graymode = PR_GRAY_HGRCMYK;
					break;
				default:
					break;
			}
			break;
		case PR_OBJ_GRAP:
			graymode = GRAY_GRAP_MODE (prh->m_objPageCtrl.GetVectorGray());
			break;
		case PR_OBJ_TEXT:
			graymode = GRAY_TEXT_MODE (prh->m_objPageCtrl.GetVectorGray());

			if (obj & OBJ_TEXT_DITHER)
			{
				switch (graymode)
				{
					case PR_GRAY_G2K:
#ifdef SUPPORT_COMPOSITEBLACK
					case PR_GRAY_COMPBK:
#endif
						if (obj & OBJ_MONOIMAGE)
							break;
					case PR_GRAY_K2K:
						graymode = PR_GRAY_CMYK;
						break;
					case PR_GRAY_HGRG2K:
						if (obj & OBJ_MONOIMAGE)
							break;
						graymode = PR_GRAY_HGRCMYK;
						break;
					default:
						break;
				}
			}
			break;
		case PR_OBJ_LINE:
			graymode = GRAY_LINE_MODE (prh->m_objPageCtrl.GetVectorGray());
			break;
		default:
			error(prh->m_objError.m_ulErrCode =
					PR_ERR_SYNTAX);
			return (PR_ERROR);
		}

#ifdef SUPPORT_PAGE_PREFEED
	if ((!(prh->m_ulJobState & PR_START_JOB)) ||
		(!(prh->m_ulJobState & PR_START_PAGE)) ||
		(!((prh->m_ulJobState & PR_START_BAND) || 
			prh->m_objPageCtrl.m_nSplFlushMode)))
#else
	if (!(prh->m_ulJobState & PR_START_JOB) || !(prh->m_ulJobState
			& PR_START_PAGE) || !(prh->m_ulJobState & PR_START_BAND))
#endif
	{
		error(prh->m_objError.m_ulErrCode =
				PR_ERR_STATUS);
		return (PR_ERROR);

	}

	ppucGamma = prh->m_objRender.m_objGamma.GetCurrentSysGamma(obj
		& PR_OBJ_MASK, prh->m_objRender.m_nNColor);

	ginf = prh->m_pobjGinf;
	switch (obj & PR_OBJ_MASK)
	{
		case PR_OBJ_IMAG:
			ucDitherMode = DIT_IMAG_MODE (ginf->m_ucDither);
			break;
		case PR_OBJ_GRAP:
			ucDitherMode = DIT_GRAP_MODE (ginf->m_ucDither);
			break;
		case PR_OBJ_TEXT:
			ucDitherMode = DIT_TEXT_MODE (ginf->m_ucDither);
			break;
		case PR_OBJ_LINE:
			ucDitherMode = DIT_LINE_MODE (ginf->m_ucDither);
			break;
		default:;
			assert (0);
			return PR_ERROR;
	}
	if (prh->m_objColor.m_nIsPqtc)
	{
		if (ucDitherMode == DIT_PHOT)
		{
			cur_color->m_sPqLimit = cur_color->m_sPqLimitPhot;
			cur_color->m_pucPqTbl = cur_color->m_pucPqTblPhot;
			cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblPhot;
		}
		else if (ucDitherMode == DIT_GRAP)
		{
			cur_color->m_sPqLimit = cur_color->m_sPqLimitGrap;
			cur_color->m_pucPqTbl = cur_color->m_pucPqTblGrap;
			cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblGrap;
		}
		else
		{;
			assert (ucDitherMode == DIT_TEXT);
			cur_color->m_sPqLimit = cur_color->m_sPqLimitText;
			cur_color->m_pucPqTbl = cur_color->m_pucPqTblText;
			cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblText;
		}
	}	// prh->pobjColor->m_nIsPqtc

	cur_color->m_psCmmColor = &(prh->m_objCmm);
	cur_color->m_psCmmColor->m_ulCurId =
		Cmmprofiles (obj & PR_OBJ_MASK);

#ifdef SUPPORT_COMPOSITEBLACK
	if (graymode == PR_GRAY_COMPBK)
	{
		if (cur_color->CheckCompbk() == FALSE)
		{
			graymode = PR_GRAY_G2K;
		}
	}
#endif

	if ((prh->m_objRender.m_ucIsColor == PAGE_COLOR_K) ||
#ifdef SUPPORT_COMPOSITEBLACK
		(prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK) ||
			((graymode != PR_GRAY_COMPBK) &&
				(prh->m_objRender.m_ucRenderingColor == PAGE_RENDERING_MONO)))
#else
		(prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK))
#endif
	{

		kcmy.b[0] = r;
		kcmy.b[1] = g;
		kcmy.b[2] = b;
#ifdef SUPPORT_CUTTING_RGBVALUE
		// RGB -> GRAY
		ApplyRgb2Gray (cur_color, kcmy.b, obj & PR_OBJ_MASK, GRAP_SRCNOT_OFF);
#else
		ApplyRgb2Gray (kcmy.b);	// RGB -> GRAY
#endif
		prh->m_objColor.DoGammaK (&kcmy.b[0], &kcmy.b[0], ppucGamma);
		*pucK = kcmy.b[0];
		*pucC = kcmy.b[1];
		*pucM = kcmy.b[2];
		*pucY = kcmy.b[3];

		return PR_OK;
	}

	rgb.b[0] = r;
	rgb.b[1] = g;
	rgb.b[2] = b;
	rgb.b[3] = 0;

	switch (graymode)
	{
		case PR_GRAY_G2K:
		case PR_GRAY_PIXELK:
		case PR_GRAY_MAYBEK:
#ifdef SUPPORT_CUTTING_RGBVALUE
			cur_color->ApplyBgucrKeepgray (rgb.b, kcmy.b, obj & PR_OBJ_MASK,
				GRAP_SRCNOT_OFF);
#else
			cur_color->ApplyBgucrKeepgray (rgb.b,
				kcmy.b);
#endif
			break;
		case PR_GRAY_HGRG2K:
			cur_color->ApplyBgucrHgrKeepgray (rgb.b,
				kcmy.b);
			break;
		case PR_GRAY_CMYK:
#ifdef SUPPORT_CUTTING_RGBVALUE
			cur_color->ApplyBgucr (rgb.b, kcmy.b, obj & PR_OBJ_MASK,
				GRAP_SRCNOT_OFF);
#else
			cur_color->ApplyBgucr (rgb.b, kcmy.b);
#endif
			break;
		case PR_GRAY_HGRCMYK:
			cur_color->ApplyBgucrHgr (rgb.b, kcmy.b);
			break;
		case PR_GRAY_K2K:
		case PR_GRAY_IMAGEK:
			cur_color->ApplyBgucrKeepblack (rgb.b,
				kcmy.b);
			break;
		case PR_GRAY_CMY:
			cur_color->ApplyRgb2Cmy(rgb.b, kcmy.b);
			break;
		case PR_GRAY_ABOUTK:
			cur_color->ApplyBgucrAboutKeepgray (rgb.b,
				kcmy.b);
			break;
#ifdef SUPPORT_COMPOSITEBLACK
		case PR_GRAY_COMPBK:
			cur_color->ApplyBgucrCompbk(rgb.b, kcmy.b,
				obj & PR_OBJ_MASK, GRAP_SRCNOT_OFF);
			break;
#endif
		default:;
			assert (0);
	}

	pLimit.text = prTLIMIT[ucDitherMode][OBJ_TEXT];
	pLimit.line = prTLIMIT[ucDitherMode][OBJ_LINE];
	pLimit.phot = prTLIMIT[ucDitherMode][OBJ_IMAG];
	pLimit.fill = prTLIMIT[ucDitherMode][OBJ_GRAP];
	if (prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK2)
	{
		kcmy.b[2] = kcmy.b[3] = 0;
		cur_color->DoGammaRK2(kcmy.b, obj & PR_OBJ_MASK,
			prh->m_objJobCtrl.GetTonerLimit(), &pLimit,
			ppucGamma);
	}
	else
	{
		cur_color->DoGamma(kcmy.b, obj & PR_OBJ_MASK,
			prh->m_objJobCtrl.GetTonerLimit(), &pLimit,
			ppucGamma);
	}

	*pucK = kcmy.b[0];
	*pucC = kcmy.b[1];
	*pucM = kcmy.b[2];
	*pucY = kcmy.b[3];

	return PR_OK;
} CMM*/

///////////////////////////////////////////////////////////////////////////////
//Function      :PrRgb2CmykPixels
//Description   :
//Arguments     :
//              :prh_t * prh:[IN]
//              :uchar obj:[IN]
//              :uchar * pucRgb:[IN]
//              :uchar * pucCmyk:[OUT]
//              :ulong ulSize:[IN]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
/* CMMint
PrRgb2CmykPixels (prh_t * prh,
	uchar obj,
	uchar * pucRgb,
	uchar * pucCmyk,
	ulong ulSize)
{
	union
	{
		ulong l;
		uchar b[4];
	} rgb;
	union
	{
		ulong l;
		uchar b[4];
	} kcmy;
	int graymode;
	uchar **ppucGamma;
	clr_tlimit_t pLimit;
	CPRColor* cur_color = (CPRColor*) &(prh->m_objColor);
	ginf_t *ginf;
	unsigned char ucDitherMode;
	unsigned long ulRGBIdx=0, ulCMYKIdx=0;
	unsigned long ulOldRGB, ulNowRGB;

	switch (obj & PR_OBJ_MASK)
	{
		case PR_OBJ_IMAG:
			graymode = GRAY_IMAG_MODE (prh->m_objPageCtrl.GetVectorGray());
			switch (graymode)
			{
				case PR_GRAY_G2K:
#ifdef SUPPORT_COMPOSITEBLACK
				case PR_GRAY_COMPBK:
#endif
					if (obj & OBJ_MONOIMAGE)
						break;
				case PR_GRAY_K2K:
					graymode = PR_GRAY_CMYK;
					break;
				case PR_GRAY_HGRG2K:
					if (obj & OBJ_MONOIMAGE)
						break;
					graymode = PR_GRAY_HGRCMYK;
					break;
				default:
					break;
			}
			break;
		case PR_OBJ_GRAP:
			graymode = GRAY_GRAP_MODE (prh->m_objPageCtrl.GetVectorGray());
			break;
		case PR_OBJ_TEXT:
			graymode = GRAY_TEXT_MODE (prh->m_objPageCtrl.GetVectorGray());

			if (obj & OBJ_TEXT_DITHER)
			{
				switch (graymode)
				{
					case PR_GRAY_G2K:
#ifdef SUPPORT_COMPOSITEBLACK
					case PR_GRAY_COMPBK:
#endif
						if (obj & OBJ_MONOIMAGE)
							break;
					case PR_GRAY_K2K:
						graymode = PR_GRAY_CMYK;
						break;
					case PR_GRAY_HGRG2K:
						if (obj & OBJ_MONOIMAGE)
							break;
						graymode = PR_GRAY_HGRCMYK;
						break;
					default:
						break;
				}
			}
			break;
		case PR_OBJ_LINE:
			graymode = GRAY_LINE_MODE (prh->m_objPageCtrl.GetVectorGray());
			break;
		default:
			error(prh->m_objError.m_ulErrCode =
					PR_ERR_SYNTAX);
			return (PR_ERROR);
		}

#ifdef SUPPORT_PAGE_PREFEED
	if ((!(prh->m_ulJobState & PR_START_JOB)) ||
		(!(prh->m_ulJobState & PR_START_PAGE)) ||
		(!((prh->m_ulJobState & PR_START_BAND) || 
			prh->m_objPageCtrl.m_nSplFlushMode)))
#else
	if (!(prh->m_ulJobState & PR_START_JOB) || !(prh->m_ulJobState
			& PR_START_PAGE) || !(prh->m_ulJobState & PR_START_BAND))
#endif
	{
		error(prh->m_objError.m_ulErrCode = PR_ERR_STATUS);
		return (PR_ERROR);

	}

	ppucGamma = prh->m_objRender.m_objGamma.GetCurrentSysGamma(obj
		& PR_OBJ_MASK, prh->m_objRender.m_nNColor);

	ginf = prh->m_pobjGinf;
	switch (obj & PR_OBJ_MASK)
	{
		case PR_OBJ_IMAG:
			ucDitherMode = DIT_IMAG_MODE (ginf->m_ucDither);
			break;
		case PR_OBJ_GRAP:
			ucDitherMode = DIT_GRAP_MODE (ginf->m_ucDither);
			break;
		case PR_OBJ_TEXT:
			ucDitherMode = DIT_TEXT_MODE (ginf->m_ucDither);
			break;
		case PR_OBJ_LINE:
			ucDitherMode = DIT_LINE_MODE (ginf->m_ucDither);
			break;
		default:;
			assert (0);
			return PR_ERROR;
	}
	if (prh->m_objColor.m_nIsPqtc)
	{
		if (ucDitherMode == DIT_PHOT)
		{
			cur_color->m_sPqLimit = cur_color->m_sPqLimitPhot;
			cur_color->m_pucPqTbl = cur_color->m_pucPqTblPhot;
			cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblPhot;
		}
		else if (ucDitherMode == DIT_GRAP)
		{
			cur_color->m_sPqLimit = cur_color->m_sPqLimitGrap;
			cur_color->m_pucPqTbl = cur_color->m_pucPqTblGrap;
			cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblGrap;
		}
		else
		{;
			assert (ucDitherMode == DIT_TEXT);
			cur_color->m_sPqLimit = cur_color->m_sPqLimitText;
			cur_color->m_pucPqTbl = cur_color->m_pucPqTblText;
			cur_color->m_pucRPqTbl = cur_color->m_pucRPqTblText;
		}
	}	// prh->pobjColor->m_nIsPqtc

	cur_color->m_psCmmColor = &(prh->m_objCmm);
	cur_color->m_psCmmColor->m_ulCurId =
		Cmmprofiles (obj & PR_OBJ_MASK);

#ifdef SUPPORT_COMPOSITEBLACK
	if (graymode == PR_GRAY_COMPBK)
	{
		if (cur_color->CheckCompbk() == FALSE)
		{
			graymode = PR_GRAY_G2K;
		}
	}
#endif

	ulOldRGB = 0xffffffff;

	if ((prh->m_objRender.m_ucIsColor == PAGE_COLOR_K) ||
#ifdef SUPPORT_COMPOSITEBLACK
		(prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK) ||
			((graymode != PR_GRAY_COMPBK) &&
				(prh->m_objRender.m_ucRenderingColor == PAGE_RENDERING_MONO)))
#else
		(prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK))
#endif
	{
		// monochrome page print

		for (; 0 < ulSize; ulRGBIdx+=3, ulCMYKIdx+=4, ulSize--)
		{
			kcmy.b[0] = *(pucRgb + ulRGBIdx);
			kcmy.b[1] = *(pucRgb + ulRGBIdx + 1);
			kcmy.b[2] = *(pucRgb + ulRGBIdx + 2);
			ulNowRGB = kcmy.b[0];
			ulNowRGB |= kcmy.b[1] << 8;
			ulNowRGB |= kcmy.b[2] << 16;

			if (ulNowRGB == ulOldRGB)
			{
				*((ulong *)(pucCmyk + ulCMYKIdx)) =
					*((ulong *)(pucCmyk + ulCMYKIdx) - 1);
			}
			else
			{
				ulOldRGB = ulNowRGB;
#ifdef SUPPORT_CUTTING_RGBVALUE
				// RGB -> GRAY
				ApplyRgb2Gray (cur_color, kcmy.b, obj & PR_OBJ_MASK, GRAP_SRCNOT_OFF);
#else
				ApplyRgb2Gray (kcmy.b);	// RGB -> GRAY
#endif
				prh->m_objColor.DoGammaK (&kcmy.b[0], &kcmy.b[0], ppucGamma);

				*(pucCmyk + ulCMYKIdx) = kcmy.b[1];
				*(pucCmyk + ulCMYKIdx + 1) = kcmy.b[2];
				*(pucCmyk + ulCMYKIdx + 2) = kcmy.b[3];
				*(pucCmyk + ulCMYKIdx + 3) = kcmy.b[0];
			}
		}
	}
	else
	{
		// color page print
		void (CPRColor::*pvBgucrFunc)(uchar*, uchar*);
		void (CPRColor::*pvGammaFunc)(uchar*, int, int, clr_tlimit_t*, uchar**);
#if defined(SUPPORT_CUTTING_RGBVALUE) || defined(SUPPORT_COMPOSITEBLACK)
		void (CPRColor::*pvBgucrFunc2)(uchar*, uchar*, int, ulong);
#endif
		switch (graymode)
		{
			case PR_GRAY_G2K:
			case PR_GRAY_PIXELK:
			case PR_GRAY_MAYBEK:
#ifdef SUPPORT_CUTTING_RGBVALUE
				pvBgucrFunc2 = &CPRColor::ApplyBgucrKeepgray;
#else
				pvBgucrFunc = &CPRColor::ApplyBgucrKeepgray;
#endif
				break;
			case PR_GRAY_HGRG2K:
				pvBgucrFunc = &CPRColor::ApplyBgucrHgrKeepgray;
				break;
			case PR_GRAY_CMYK:
#ifdef SUPPORT_CUTTING_RGBVALUE
				pvBgucrFunc2 = &CPRColor::ApplyBgucr;
#else
				pvBgucrFunc = &CPRColor::ApplyBgucr;
#endif
				break;
			case PR_GRAY_HGRCMYK:
				pvBgucrFunc = &CPRColor::ApplyBgucrHgr;
				break;
			case PR_GRAY_K2K:
			case PR_GRAY_IMAGEK:
				pvBgucrFunc = &CPRColor::ApplyBgucrKeepblack;
				break;
			case PR_GRAY_CMY:
				pvBgucrFunc = &CPRColor::ApplyRgb2Cmy;
				break;
			case PR_GRAY_ABOUTK:
				pvBgucrFunc = &CPRColor::ApplyBgucrAboutKeepgray;
				break;
#ifdef SUPPORT_COMPOSITEBLACK
			case PR_GRAY_COMPBK:
				pvBgucrFunc2 = &CPRColor::ApplyBgucrCompbk;
				break;
#endif
			default:
				assert (0);
		}

		if (prh->m_objRender.m_ucIsColor == PAGE_COLOR_RK2)
		{
			pvGammaFunc = &CPRColor::PreDoGammaRK2;
		}
		else
		{
			pvGammaFunc = &CPRColor::DoGamma;
		}

		pLimit.text = prTLIMIT[ucDitherMode][OBJ_TEXT];
		pLimit.line = prTLIMIT[ucDitherMode][OBJ_LINE];
		pLimit.phot = prTLIMIT[ucDitherMode][OBJ_IMAG];
		pLimit.fill = prTLIMIT[ucDitherMode][OBJ_GRAP];
		
		for (; 0 < ulSize; ulRGBIdx+=3, ulCMYKIdx+=4, ulSize--)
		{
			rgb.b[0] = *(pucRgb + ulRGBIdx);
			rgb.b[1] = *(pucRgb + ulRGBIdx + 1);
			rgb.b[2] = *(pucRgb + ulRGBIdx + 2);
			rgb.b[3] = 0;
			ulNowRGB = rgb.b[0];
			ulNowRGB |= rgb.b[1] << 8;
			ulNowRGB |= rgb.b[2] << 16;

			if (ulNowRGB != ulOldRGB)
			{
				ulOldRGB = ulNowRGB;
				// BG/UCR
#if defined(SUPPORT_CUTTING_RGBVALUE) || defined(SUPPORT_COMPOSITEBLACK)
				switch (graymode)
				{
					case PR_GRAY_G2K:
					case PR_GRAY_PIXELK:
					case PR_GRAY_MAYBEK:
					case PR_GRAY_CMYK:
#ifdef SUPPORT_CUTTING_RGBVALUE
						(cur_color->*pvBgucrFunc2)(rgb.b, kcmy.b,
							obj & PR_OBJ_MASK, GRAP_SRCNOT_OFF);
#else
						(cur_color->*pvBgucrFunc)(rgb.b, kcmy.b);
#endif
						break;
#ifdef SUPPORT_COMPOSITEBLACK
					case PR_GRAY_COMPBK:
						(cur_color->*pvBgucrFunc2)(rgb.b, kcmy.b,
							obj & PR_OBJ_MASK, GRAP_SRCNOT_OFF);
						break;
#endif
					default:
						(cur_color->*pvBgucrFunc)(rgb.b, kcmy.b);
						break;
				}
#else
				(cur_color->*pvBgucrFunc)(rgb.b, kcmy.b);
#endif // SUPPORT_CUTTING_RGBVALUE || SUPPORT_COMPOSITEBLACK

				// Gamma
				(cur_color->*pvGammaFunc)(kcmy.b, obj & PR_OBJ_MASK,
					prh->m_objJobCtrl.GetTonerLimit(), &pLimit, ppucGamma);
			}

			*(pucCmyk + ulCMYKIdx) = kcmy.b[1];
			*(pucCmyk + ulCMYKIdx + 1) = kcmy.b[2];
			*(pucCmyk + ulCMYKIdx + 2) = kcmy.b[3];
			*(pucCmyk + ulCMYKIdx + 3) = kcmy.b[0];
		} // for (; 0 < ulSize; ulRGBIdx+=3, ulCMYKIdx+=4, ulSize--)
	}

	return PR_OK;
} CMM*/

///////////////////////////////////////////////////////////////////////////////
//Function      :PrRgb2K
//Description   : 
//Arguments     :
//              :prh_t * prh:[IN]
//              :uchar obj:[IN]
//              :uchar r:[IN]
//              :uchar g:[IN]
//              :uchar b:[IN]
//              :uchar * pucK):[OUT]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
/* CMMint
PrRgb2K (prh_t * prh,
	uchar obj,
	uchar r,		 
	uchar g,		 
	uchar b,		 
	uchar * pucK)	 
{
	union
	{
		ulong l;
		uchar b[4];
	} kcmy;
	uchar **ppucGamma;
	CPRColor* cur_color = (CPRColor*) &(prh->m_objColor);

#ifdef SUPPORT_PAGE_PREFEED
	if ((!(prh->m_ulJobState & PR_START_JOB)) ||
		(!(prh->m_ulJobState & PR_START_PAGE)) ||
		(!((prh->m_ulJobState & PR_START_BAND) || 
			prh->m_objPageCtrl.m_nSplFlushMode)))
#else
	if (!(prh->m_ulJobState & PR_START_JOB) || !(prh->m_ulJobState
			& PR_START_PAGE) || !(prh->m_ulJobState & PR_START_BAND))
#endif
	{
		error(prh->m_objError.m_ulErrCode = PR_ERR_STATUS);
		return (PR_ERROR);
	}

	ppucGamma = prh->m_objRender.m_objGamma.GetCurrentSysGamma(obj
		& PR_OBJ_MASK, prh->m_objRender.m_nNColor);

	kcmy.b[0] = r;
	kcmy.b[1] = g;
	kcmy.b[2] = b;
#ifdef SUPPORT_CUTTING_RGBVALUE
	// RGB -> GRAY
	ApplyRgb2Gray (cur_color, kcmy.b, obj & PR_OBJ_MASK, GRAP_SRCNOT_OFF);
#else
	ApplyRgb2Gray (kcmy.b);	// RGB -> GRAY
#endif
	prh->m_objColor.DoGammaK (&kcmy.b[0], &kcmy.b[0], ppucGamma);

	*pucK = kcmy.b[0];

	return PR_OK;
} CMM */

///////////////////////////////////////////////////////////////////////////////
//Function      :PrRgb2KPixels
//Description   :
//Arguments     :
//              :prh_t * prh:[IN]
//              :uchar obj:[IN]
//              :uchar * pucRgb:[IN]
//              :uchar * pucK:[OUT]
//              :ulong ulSize:[IN]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
/*int
PrRgb2KPixels (prh_t * prh,
	uchar obj,
	uchar * pucRgb,
	uchar * pucK,
	ulong ulSize)
{
	union
	{
		ulong l;
		uchar b[4];
	} kcmy;
	uchar **ppucGamma;
	CPRColor* cur_color = (CPRColor*) &(prh->m_objColor);
	unsigned long ulRGBIdx=0, ulKIdx=0;
	unsigned long ulOldRGB, ulNowRGB;

#ifdef SUPPORT_PAGE_PREFEED
	if ((!(prh->m_ulJobState & PR_START_JOB)) ||
		(!(prh->m_ulJobState & PR_START_PAGE)) ||
		(!((prh->m_ulJobState & PR_START_BAND) || 
			prh->m_objPageCtrl.m_nSplFlushMode)))
#else
	if (!(prh->m_ulJobState & PR_START_JOB) || !(prh->m_ulJobState
			& PR_START_PAGE) || !(prh->m_ulJobState & PR_START_BAND))
#endif
	{
		error(prh->m_objError.m_ulErrCode = PR_ERR_STATUS);
		return (PR_ERROR);
	}

	ppucGamma = prh->m_objRender.m_objGamma.GetCurrentSysGamma(obj
		& PR_OBJ_MASK, prh->m_objRender.m_nNColor);

	ulOldRGB = 0xffffffff;

	for (; 0 < ulSize; ulRGBIdx+=3, ulKIdx++, ulSize--)
	{
		kcmy.b[0] = *(pucRgb + ulRGBIdx);
		kcmy.b[1] = *(pucRgb + ulRGBIdx + 1);
		kcmy.b[2] = *(pucRgb + ulRGBIdx + 2);
		ulNowRGB = kcmy.b[0];
		ulNowRGB |= kcmy.b[1] << 8;
		ulNowRGB |= kcmy.b[2] << 16;

		if (ulNowRGB == ulOldRGB)
		{
			*(pucK + ulKIdx) = *(pucK + ulKIdx - 1);
		}
		else
		{
			ulOldRGB = ulNowRGB;
#ifdef SUPPORT_CUTTING_RGBVALUE
			// RGB -> GRAY
			ApplyRgb2Gray (cur_color, kcmy.b, obj & PR_OBJ_MASK, GRAP_SRCNOT_OFF);
#else
			ApplyRgb2Gray (kcmy.b);	// RGB -> GRAY
#endif
			prh->m_objColor.DoGammaK (&kcmy.b[0], &kcmy.b[0], ppucGamma);

			*(pucK + ulKIdx) = kcmy.b[0];
		}
	}

	return PR_OK;
} CMM*/

///////////////////////////////////////////////////////////////////////////////
//Function      :SetIsGrayJudge 
//Description   : set gray judge mode after CMM
//Arguments     :
//              :prh_t * prh:[IN]
//              :int obj_mode:[IN]
//Return value  :
///////////////////////////////////////////////////////////////////////////////
/* CMMvoid CPRColor::SetIsGrayJudge (prh_t * prh,
	int obj_mode)

{
	switch (obj_mode & OBJ_MASK)
	{
		case OBJ_IMAG:
			m_ucIsGrayJudge = GRAY_IMAG_MODE (prh->m_objPageCtrl.GetGrayJudgeMode());
			break;
		case OBJ_GRAP:
			m_ucIsGrayJudge = GRAY_GRAP_MODE (prh->m_objPageCtrl.GetGrayJudgeMode());
			break;
		case OBJ_TEXT:
			m_ucIsGrayJudge = GRAY_TEXT_MODE (prh->m_objPageCtrl.GetGrayJudgeMode());
			break;
		case OBJ_LINE:
			m_ucIsGrayJudge = GRAY_LINE_MODE (prh->m_objPageCtrl.GetGrayJudgeMode());
			break;
		default:
			assert(0);
			break;
	}
} CMM*/

#ifdef PR_XPS_SUPPORT

///////////////////////////////////////////////////////////////////////////////
//Function      :SetPixelAttribute
//Description   :Set Pixel attribute(photo/text/graph/line)
//Arguments     :
//              :prh_t* prh:[IN]
//              :unsigned	char *pucPixAttr:[IN]
//              :int& rnGrayMode:[IN]
//              :int&	rnObjMode:[IN]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
int
CPRColor::SetPixelAttribute(prh_t* prh, unsigned
	char *pucPixAttr, int& rnGrayMode, int&
	rnObjMode)
{
	switch (*pucPixAttr & XPS_ATTR_MASK)
	{
		case XPS_ATTR_PHOTO:
		rnGrayMode = GRAY_IMAG_MODE(prh->m_objPageCtrl.GetVectorGray());
			rnObjMode = OBJ_IMAG;
			break;
		case XPS_ATTR_TEXT:
			rnGrayMode = GRAY_TEXT_MODE(prh->m_objPageCtrl.GetVectorGray());
			rnObjMode = OBJ_TEXT;
			break;
		case XPS_ATTR_FILL:
			rnObjMode = OBJ_GRAP;
			break;
		case XPS_ATTR_LINE:
			rnObjMode = OBJ_LINE;
			break;
		default:;
			assert(0);
			return (PR_ERROR);
	}
	return (PR_OK);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :DoColorProcessing
//Description   :This function does pobjColor processing pixel wise.
//Arguments     :
//              :CPRPageRenderer *prh:[IN]
//Return value  :int:PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
int
CPRColor::DoColorProcessing(CPRPageRenderer *prh)
{
	uchar* pcPRGBBuf = prh->m_objRender.m_psDr->m_pucPRGBBuffer;
	uchar* pucKCMYBuf = prh->m_objRender.m_psDr->m_pucKCMYABuffer;
	uchar* pucPixAttr = prh->m_objRender.m_psDr->m_pucATBuffer;
	int nI = 0;
	int j = 0;
	int nRet = 0;
	int nTonerLimit = 0;
	int nGrayMode = 0;
	int nObjectMode = 0;
	int nBandHeight = prh->m_objRotate.m_nDoBanding;
	int nBandWidth = (prh->m_objPageCtrl.GetPageWidth());
	clr_tlimit_t pLimit;
	//To traverse PRGB buffer
	unsigned char *pucPRGB = prh->m_objRender.m_psDr->m_pucPRGBBuffer;
	++pcPRGBBuf; // remove the pdata
	unsigned char* r = pcPRGBBuf;	//R->ucC
	++pcPRGBBuf;
	unsigned char* g = pcPRGBBuf;	//G->ucM
	++pcPRGBBuf;
	unsigned char* b = pcPRGBBuf;	//B->ucY

	if (!nBandHeight)
		nBandHeight = prh->m_objBandCtrl.GetBandHeight();

	int planesize = prh->m_objPageCtrl.GetPageWidth()
	*nBandHeight;// nSize of one plane
	int nSize = planesize *4; // Total nSize of the KCMY buffer
	unsigned char* pucK = pucKCMYBuf;
	unsigned char* pucC = pucK + planesize;
	unsigned char* pucM = pucC + planesize;
	unsigned char* pucY = pucM+ planesize;

	unsigned long RGBO =0, RGB=0;

	unsigned char ucDitherMode = 0;
	unsigned char **pucGamma=0;
	CONVN_FN_TYPE ConversnFnPtr = NULL;
	prh->m_objRender.SelectRender(prh, prh->m_pobjGinf->m_ucDither);
	RGBO = 0xffffffff;
	RGB = (*r);
	RGB |= ((*g) << 8);
	RGB |= ((*b) << 16);
	for (j = 0; j< nBandHeight; j++)//Traversing the PRGB buffer
	{
		for (nI=0; nI < nBandWidth; nI++)
		{
			nRet = SetPixelAttribute(prh,
				pucPixAttr, nGrayMode, nObjectMode);
			if (PR_OK != nRet)
			{
				return (PR_ERROR);
			}
			if (nObjectMode == OBJ_IMAG)
			{

				ucDitherMode = DIT_IMAG_MODE (prh->m_pobjGinf->m_ucDither);
			}
			else
			{;
				assert (nObjectMode == OBJ_TEXT);
				ucDitherMode = DIT_TEXT_MODE (prh->m_pobjGinf->m_ucDither);
			}
			pucGamma = prh->m_objRender.m_objGamma.GetCurrentSysGamma(nObjectMode,
				prh->m_objRender.m_nNColor);
			if (prh->m_objColor.m_nIsPqtc)
			{
				if (ucDitherMode == DIT_PHOT)
				{
					m_sPqLimit = m_sPqLimitPhot;
					m_pucPqTbl =m_pucPqTblPhot;
					m_pucRPqTbl = m_pucRPqTblPhot;
				}
				else
				{;
					assert (ucDitherMode ==
						DIT_TEXT);
					m_sPqLimit = m_sPqLimitText;
					m_pucPqTbl = m_pucPqTblText;
					m_pucRPqTbl = m_pucRPqTblText;
				}
			}
			pLimit.text = prTLIMIT[ucDitherMode][OBJ_TEXT];
			pLimit.line = prTLIMIT[ucDitherMode][OBJ_LINE];
			pLimit.phot = prTLIMIT[ucDitherMode][OBJ_IMAG];
			pLimit.fill = prTLIMIT[ucDitherMode][OBJ_GRAP];

			ConversnFnPtr=SetClrPrcsFn(pucPixAttr,
				nGrayMode);
			ConversnFnPtr(this, pucPRGB, r, g, b,
				pucK, pucC, pucM, pucY, &RGB, &RGBO, nSize,
				pucGamma, &pLimit);
			r = r+4;
			g = g+4;
			b = b+4;

			pucK++;
			pucC++;
			pucM++;
			pucY++;
			pucPixAttr = pucPixAttr+2;
		}
	}
	return PR_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static voidTransrgbBgucrPhotXPS
//Description   :It calls the corresponding color processing function with 
//               image quality as photo.
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :unsigned	char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit:[IN]
//Return value  ::void
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrPhotXPS(CPRColor *pobjColor, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
pobjColor->ApplyBgucrsGammasXPS(pucPRGB, r, g, b,
		pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_IMAG, pucGamma, pLimit);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :static voidTransrgbBgucrImageKPhotXPS
//Description   :It calls the corresponding color processing function with 
//               image quality as photo.
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :unsigned char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit:[IN]
//Return value  ::PR_OK ->OK, PR_ERROR->Error
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrImageKPhotXPS(CPRColor *pobjColor,
	unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	pobjColor->ApplyBgucrImageKsGammasXPS(pucPRGB, r,
		g, b, pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_IMAG, pucGamma, pLimit);
}
/////////////////////////////////////////////////////////////////////////
//Function      :TransrgbBgucrTextXPS
//Description   :It calls the corresponding color processing function 
//               image quality as text.
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :unsigned		char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	static void	
///////////////////////////////////////////////////////////////////////////////
static void
TransrgbBgucrTextXPS(CPRColor *pobjColor, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	pobjColor->ApplyBgucrsGammasXPS(pucPRGB, r, g, b,
		pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_TEXT, pucGamma, pLimit);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbBgucrImageKTextXPS
//Description   : 
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :unsigned char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	static void 
///////////////////////////////////////////////////////////////////////////////
static void TransrgbBgucrImageKTextXPS(CPRColor *pobjColor,
	unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	pobjColor->ApplyBgucrImageKsGammasXPS(pucPRGB, r,
		g, b, pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_TEXT, pucGamma, pLimit);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbBgucrKeepgrayPhotXPS
//Description   :It calls the corresponding color processing function with 
//               image quality as photo.
//Arguments     :
//              :CPRColor		*pobjColor:[IN]
//              :unsigned char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	static void 
///////////////////////////////////////////////////////////////////////////////
static void TransrgbBgucrKeepgrayPhotXPS(CPRColor
	*pobjColor, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	pobjColor->ApplyBgucrKeepgraysGammasXPS(pucPRGB, r,
		g, b, pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_IMAG, pucGamma, pLimit);
}
///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbBgucrKeepgrayTextXPS
//Description   :It calls the corresponding color processing function 
//               image quality as text.
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :unsigned char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  : static void 
///////////////////////////////////////////////////////////////////////////////
static void TransrgbBgucrKeepgrayTextXPS(CPRColor
	*pobjColor, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	pobjColor->ApplyBgucrKeepgraysGammasXPS(pucPRGB, r,
		g, b, pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_TEXT, pucGamma, pLimit);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbBgucrMaykeepgrayPhotXPS
//Description   :It calls the corresponding color processing function with 
//                image quality as photo.
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :unsigned char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	static void 
///////////////////////////////////////////////////////////////////////////////
static void TransrgbBgucrMaykeepgrayPhotXPS(CPRColor
	*pobjColor, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	pobjColor->ApplyBgucrMaybeKeepgraysGammasXPS(pucPRGB,
		r, g, b, pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_IMAG, pucGamma, pLimit);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :TransrgbBgucrMaykeepgrayTextXPS
//Description   :It calls the corresponding color processing function with 
//                image quality as text.
//Arguments     :
//              :CPRColor		*pobjColor:[IN]
//              :unsigned char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[IN]
//              :unsigned char *pucC:[IN]
//              :unsigned char *pucM:[IN]
//              :unsigned char *pucY:[IN]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	static void 
///////////////////////////////////////////////////////////////////////////////
static void TransrgbBgucrMaykeepgrayTextXPS(CPRColor
	*pobjColor, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	pobjColor->ApplyBgucrMaybeKeepgraysGammasXPS(pucPRGB,
		r, g, b, pucK, pucC, pucM, pucY, pulRGB, pulRGBO, nSize,
		CR_OBJ_TEXT, pucGamma, pLimit);
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrMaybeKeepgraysGammasXPS
//Description   :Color Processing function when the gray mode is CR_GRAY_MAYBEK.
//Arguments     :
//              :unsigned		char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :int nObjectMode:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	void	
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrMaybeKeepgraysGammasXPS(unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	int nObjectMode,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	unsigned char **ppucGt = pucGamma;
	unsigned char *pucGtK =NULL, *pucGtC = NULL, *pucGtM =
		NULL, *pucGtY = NULL;
	int nTonerLimit = 0;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;
	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	assert (pucGtK && pucGtC && pucGtM && pucGtY);
	unsigned char ucK = '\0', ucC= '\0', ucM= '\0', ucY=
		'\0';
	nTonerLimit = SetTonerLimitInColor(nObjectMode,
		pLimit);
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectMode];
		if (m_ulCurId & CMM_CMYK)
		{
			if ((m_ulGrayCount >= (unsigned long)m_usGrayHistory)
				&& (*r == *g && *r == *b))
			{
					ucC = *b;
				ucM = *g;
				ucY = *r;
				GammaK(&ucK, &ucC, &ucM, &ucY, pucGtK, ucKp);
				*pucK = ucK;
				*pucC = ucC;
				*pucM =ucM;
				*pucY = ucY;
				m_ulGrayCount++;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0
					&& pucGtY[0] == 0);
			}
			else
			{

				if (*r != *g || *r != *b)
					m_ulGrayCount = 0;
				else
					m_ulGrayCount++;

				ucC = *b;
				ucM = *g;
				ucY = *r;
				if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{			
					if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
									pucC, pucM, pucY, pucK, 1, m_ulCurId))
					
					{
						printf("\t[CMM-CMTK] NG Apply !!\r\n");
					}
				}

				*pucK = ucK;
				*pucC = ucC;
				*pucM =ucM;
				*pucY = ucY;

				ucK = *pucK;
				ucC = *pucC;
				ucM = *pucM;
				ucY = *pucY;
				ApplyTonerLimit(&ucK, &ucC, &ucM, &ucY, 1,
					nTonerLimit, pucGamma);
				*pucK = ucK;
				*pucC = ucC;
				*pucM =ucM;
				*pucY = ucY;

				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
			m_ulClrUsedPlane = LSWAP((ucKp << 24 |
					ucCp << 16 | ucMp << 8 | ucYp));

		}
		else
		{

			if ((m_ulGrayCount >= (unsigned long)m_usGrayHistory)
				&& (*r == *g && *r == *b))
			{
				ucC = *b;
				ucM = *g;
				ucY = *r;
				GammaK(&ucK, &ucC, &ucM, &ucY, pucGtK, ucKp);
				*pucK = ucK;
				*pucC = ucC;
				*pucM =ucM;
				*pucY = ucY;
				m_ulGrayCount++;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0
					&& pucGtY[0] == 0);
			}
			else
			{
				unsigned char ucTemp;

				if (*r != *g || *r != *b)
					m_ulGrayCount = 0;
				else
					m_ulGrayCount++;
				ucC = *b;
				ucM = *g;
				ucY = *r;
				if (*pucY == 0 && *pucM == 0 && *pucY == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{
				if (CMM_DoConversion4_plane (m_lIsCmm, pucY, pucM, pucC, pucY,
											 pucM, pucC, 1, m_ulCurId))
				
				{
				printf("\t[CMM-RGB] NG Apply !!\r\n");
				}
				}
				*b = ucC;
				*g = ucM;
				*r = ucY;
				ucC= ~*r;
				ucM = ~*g;
				ucY = ~*b;
				ApplyGCRAndTonerLimit(&ucK, &ucC, &ucM,
					&ucY, nTonerLimit, pucGamma);
				*pucK = ucK;
				*pucM = ucM;
				*pucC = ucC;
				*pucY = ucY;
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
			m_ulClrUsedPlane = LSWAP((ucKp << 24 |
					ucCp << 16 | ucMp << 8 | ucYp));
		}
	}
	else
	{
		if ((m_ulGrayCount >= (unsigned long)m_usGrayHistory)
			&& (*pucY == *pucM && *pucY == *pucC))
		{
			// maybe keepgray
			// set a value for nUsedPlane
			ucC = *b;
			ucM = *g;
			ucY = *r;
			GammaK(&ucK, &ucC, &ucM, &ucY, pucGtK, ucKp);
			*pucK = ucK;
			*pucC = ucC;
			*pucM =ucM;
			*pucY = ucY;
			m_ulGrayCount++;;
			assert(pucGtC[0] == 0 && pucGtM[0] == 0 &&
				pucGtY[0] == 0);
		}
		else
		{


			if (*r != *g || *r != *b)
				m_ulGrayCount = 0;
			else
				m_ulGrayCount++;

			ucC= ~*r;
			ucM = ~*g;
			ucY = ~*b;
			ApplyGCRAndTonerLimit(&ucK, &ucC, &ucM, &ucY,
				nTonerLimit, pucGamma);
			*pucK = ucK;
			*pucM = ucM;
			*pucC = ucC;
			*pucY = ucY;
			// set a value for nUsedPlane
			ucKp |= *pucK;
			ucCp |= *pucC;
			ucMp |= *pucM;
			ucYp |= *pucY;
		}
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
				16 | ucMp << 8 | ucYp));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrKeepgraysGammasXPS
//Description   :Color Processing function when the gray mode is CR_GRAY_PIXELK.
//Arguments     :
//              :unsigned		char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :int nObjectMode:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	void	
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrKeepgraysGammasXPS(unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	int nObjectMode,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	unsigned char **ppucGt = pucGamma;
	unsigned char *pucGtK = NULL, *pucGtC= NULL, *pucGtM=
		NULL, *pucGtY= NULL;
	int nTonerLimit = 0;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;

	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];;
	assert (pucGtK && pucGtC && pucGtM && pucGtY);
	nTonerLimit = SetTonerLimitInColor(nObjectMode,
		pLimit);
	unsigned char ucK, ucC, ucM, ucY;
	if (m_lIsCmm)
	{
		m_ulCurId = m_ulCmmProfiles[nObjectMode];
		if (m_ulCurId & CMM_CMYK)
		{
			if (*r == *g && *r == *b)
			{;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0
					&& pucGtY[0] == 0);
				ucC = *b;
				ucM = *g;
				ucY = *r;
				GammaK(&ucK, &ucC, &ucM, &ucY, pucGtK, ucKp);
				*pucK = ucK;
				*pucC = ucC;
				*pucM =ucM;
				*pucY = ucY;
			}
			else
			{
				ucC = *b;
				ucM = *g;
				ucY = *r;
				if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{			
					if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
													pucC, pucM, pucY, pucK, 1, m_ulCurId))
					
					{
						printf("\t[CMM-CMTK] NG Apply !!\r\n");
					}
				}

				ApplyTonerLimit(&ucK, &ucC, &ucM, &ucY, 1,
					nTonerLimit, pucGamma);
				*pucK = ucK;
				*pucC = ucC;
				*pucM =ucM;
				*pucY = ucY;
				// set a value for nUsedPlane
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
			m_ulClrUsedPlane = LSWAP((ucKp << 24 |
					ucCp << 16 | ucMp << 8 | ucYp));
		}
		else
		{
			for (; nSize > 0; nSize--, pucK++, pucC++, pucM++,
				pucY++)
			{
				if (*r == *g && *r == *b)
				{;
					assert(pucGtC[0] == 0 && pucGtM[0]
						== 0 && pucGtY[0] == 0);
					ucC = *b;
					ucM = *g;
					ucY = *r;
					GammaK(&ucK, &ucC, &ucM, &ucY, pucGtK, ucKp);
					*pucK = ucK;
					*pucC = ucC;
					*pucM =ucM;
					*pucY = ucY;
				}
				else
				{
					ucC = *b;
					ucM = *g;
					ucY = *r;
					if (*ucY == 0 && *ucM == 0 && *ucY == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else if (m_ulCurId == 0)
					{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
					}
					else
					{
					if (CMM_DoConversion4_plane (m_lIsCmm, ucY, ucM, ucC, ucY,
												 ucM, ucC, 1, m_ulCurId))
					
					{
					printf("\t[CMM-RGB] NG Apply !!\r\n");
					}
					}

					*b = ucC;
					*g = ucM;
					*r = ucY;
					if (*r == *g && *r == *b)
					{;
						assert(pucGtC[0] == 0 && pucGtM[0]
							== 0 && pucGtY[0] == 0);
						ucC = *b;
						ucM = *g;
						ucY = *r;
						GammaK(&ucK, &ucC, &ucM, &ucY, pucGtK,
							ucKp);
						*pucK = ucK;
						*pucC = ucC;
						*pucM =ucM;
						*pucY = ucY;
					}
					else
					{
						ucC= ~*r;
						ucM = ~*g;
						ucY = ~*b;
						ApplyGCRAndTonerLimit(&ucK,
							&ucC, &ucM, &ucY,
							nTonerLimit, pucGamma);
						*pucK = ucK;
						*pucM = ucM;
						*pucC = ucC;
						*pucY = ucY;
					}
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}	// nSize loop
			m_ulClrUsedPlane = LSWAP((ucKp << 24 |
					ucCp << 16 | ucMp << 8 | ucYp));
		}		// CMM_CMYK or CMM_RGB
	}
	else
	{

		if (*r == *g && *r == *b)
		{
			ucC = *b;
			ucM = *g;
			ucY = *r;
			GammaK(&ucK, &ucC, &ucM, &ucY, pucGtK, ucKp);
			*pucK = ucK;
			*pucC = ucC;
			*pucM =ucM;
			*pucY = ucY;
		}
		else
		{

			ucC = ~*r;
			ucM = ~*g;
			ucY = ~*b;
			ApplyGCRAndTonerLimit(&ucK, &ucC, &ucM, &ucY,
				nTonerLimit, pucGamma);
			*pucK = ucK;
			*pucM = ucM;
			*pucC = ucC;
			*pucY = ucY;
			ucKp |= *pucK;
			ucCp |= *pucC;
			ucMp |= *pucM;
			ucYp |= *pucY;

		}
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
				16 | ucMp << 8 | ucYp));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrImageKsGammasXPS
//Description   :Color Processing function when the gray mode is CR_GRAY_IMAGEK 
//Arguments     :
//              :unsigned char*pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :int nObjectMode:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	void	
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrImageKsGammasXPS(unsigned char
	*pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	int nObjectMode,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	unsigned char **ppucGt = pucGamma;
	unsigned char *pucGtK = NULL, *pucGtC= NULL, *pucGtM =
		NULL, *pucGtY = NULL;
	int nTonerLimit = 0;
	unsigned char ucKp = 0;
	unsigned char ucCp = 0;
	unsigned char ucMp = 0;
	unsigned char ucYp = 0;
	pucGtK = ppucGt[0];
	pucGtC = ppucGt[1];
	pucGtM = ppucGt[2];
	pucGtY = ppucGt[3];
	unsigned char ucK, ucC, ucM, ucY;
	nTonerLimit = SetTonerLimitInColor(nObjectMode,
		pLimit);
	// BG/UCR & ppucGamma
	if (m_lIsCmm)
	{			// CMM ON
		m_ulCurId = m_ulCmmProfiles[nObjectMode];
		if (m_ulCurId & CMM_CMYK)
		{
			if (*r == 0 && *g == 0 && *b == 0)
			{
				*pucK = pucGtK[(unsigned char)255];
				*pucC = 0;
				*pucM = 0;
				*pucY = 0;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0
					&& pucGtY[0] == 0);
			}
			else
			{
				ucC = *b;
				ucM = *g;
				ucY = *r;
				if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
					printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{			
					if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
									pucC, pucM, pucY, pucK, 1, m_ulCurId))
					
					{
						printf("\t[CMM-CMTK] NG Apply !!\r\n");
					}
				}

				ApplyTonerLimit(&ucK, &ucC, &ucM, &ucY, 1,
					nTonerLimit, pucGamma);
				*pucK = ucK;
				*pucC = ucC;
				*pucM = ucM;
				*pucY = ucY;
				ucKp |= *pucK;
				ucCp |= *pucC;
				ucMp |= *pucM;
				ucYp |= *pucY;
			}
			m_ulClrUsedPlane = LSWAP((ucKp << 24 |
					ucCp << 16 | ucMp << 8 | ucYp));
		}
		else
		{
			if (*r == 0 && *g == 0 && *b == 0)
			{
				*pucK = pucGtK[(unsigned char)255];
				*pucC = 0;
				*pucM = 0;
				*pucY = 0;;
				assert(pucGtC[0] == 0 && pucGtM[0] == 0
					&& pucGtY[0] == 0);
				ucKp |= *pucK;
			}
			else
			{
				ucC = *b;
				ucM = *g;
				ucY = *r;
				if (*ucY == 0 && *ucM == 0 && *ucY == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else if (m_ulCurId == 0)
				{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
				}
				else
				{
				if (CMM_DoConversion4_plane (m_lIsCmm, ucY, ucM, ucC, ucY,
											 ucM, ucC, 1, m_ulCurId))
				
				{
				printf("\t[CMM-RGB] NG Apply !!\r\n");
				}
				}

				*b = ucC;
				*g = ucM;
				*r = ucY;
				if (*r == 0 && *g == 0 && *b == 0)
				{
					*pucK = pucGtK[(unsigned char)255];
					*pucC = 0;
					*pucM = 0;
					*pucY = 0;;
					assert(pucGtC[0] == 0 && pucGtM[0]
						== 0 && pucGtY[0] == 0);
					ucKp |= *pucK;
				}
				else
				{
					ucC= ~*r;
					ucM = ~*g;
					ucY = ~*b;
					ApplyGCRAndTonerLimit(&ucK, &ucC,
						&ucM, &ucY, nTonerLimit,
						pucGamma);
					*pucK = ucK;
					*pucM = ucM;
					*pucC = ucC;
					*pucY = ucY;
					ucKp |= *pucK;
					ucCp |= *pucC;
					ucMp |= *pucM;
					ucYp |= *pucY;
				}
			}
			m_ulClrUsedPlane = LSWAP((ucKp << 24 |
					ucCp << 16 | ucMp << 8 | ucYp));
		}		// CMM_CMYK or CMM_RGB
	}
	else
	{			// CMM OFF
		if (*r == 0 && *g == 0 && *b == 0)
		{
			*pucK = pucGtK[(unsigned char)255];
			*pucC = 0;
			*pucM = 0;
			*pucY = 0;;
			assert(pucGtC[0] == 0 && pucGtM[0] == 0 &&
				pucGtY[0] == 0);
			ucKp |= *pucK;
		}
		else
		{
			unsigned char ucK = 0, ucC = 0, ucM = 0, ucY =
				0;
			ucC= ~*r;
			ucM = ~*g;
			ucY = ~*b;
			ApplyGCRAndTonerLimit(&ucK, &ucC, &ucM, &ucY,
				nTonerLimit, pucGamma);
			*pucK = ucK;
			*pucM = ucM;
			*pucC = ucC;
			*pucY = ucY;
			ucKp |= *pucK;
			ucCp |= *pucC;
			ucMp |= *pucM;
			ucYp |= *pucY;

		}
		m_ulClrUsedPlane = LSWAP((ucKp << 24 | ucCp <<
				16 | ucMp << 8 | ucYp));
	}
	return;
}

///////////////////////////////////////////////////////////////////////////////
//Function      :ApplyBgucrsGammasXPS
//Description   :Color processing function when the gray mode is CR_GRAY_G2K,
//                CR_GRAY_ABOUTK, CR_GRAY_K2K or CR_GRAY_CMYK.
//Arguments     :
//              :unsigned char *pucPRGB:[IN]
//              :unsigned char *r:[IN]
//              :unsigned char *g:[IN]
//              :unsigned char *b:[IN]
//              :unsigned char *pucK:[I/O]
//              :unsigned char *pucC:[I/O]
//              :unsigned char *pucM:[I/O]
//              :unsigned char *pucY:[I/O]
//              :unsigned long *pulRGB:[IN]
//              :unsigned long *pulRGBO:[IN]
//              :int nSize:[IN]
//              :int nObjectMode:[IN]
//              :unsigned char **pucGamma:[IN]
//              :clr_tlimit_t *pLimit):[IN]
//Return value  :	void	
///////////////////////////////////////////////////////////////////////////////
void
CPRColor::ApplyBgucrsGammasXPS(unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *pucK,
	unsigned char *pucC,
	unsigned char *pucM,
	unsigned char *pucY,
	unsigned long *pulRGB,
	unsigned long *pulRGBO,
	int nSize,
	int nObjectMode,
	unsigned char **pucGamma,
	clr_tlimit_t *pLimit)
{
	int nTonerLimit = 0;
	unsigned char ucK = '\0', ucC= '\0', ucM= '\0', ucY=
		'\0';
	nTonerLimit = SetTonerLimitInColor(nObjectMode,
		pLimit);
	if (m_lIsCmm)
	{
		//If CMM is true  and pulRGB->CMYK profile then Color conversion 
		//and ppucGamma correction.
		if (m_ulCurId & CMM_CMYK)
		{
			ucC = *b;
			ucM = *g;
			ucY = *r;
			if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
				printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{			
				if (CMM_DoConversion4_plane_cmyk (m_lIsCmm, pucY, pucM, pucC,
								pucC, pucM, pucY, pucK, (unsigned long)nSize, m_ulCurId))
				
				{
					printf("\t[CMM-CMTK] NG Apply !!\r\n");
				}
			}

			ApplyTonerLimit(&ucK, &ucC, &ucM, &ucY, 1,
				nTonerLimit, pucGamma);
			*pucK = ucK;
			*pucC = ucC;
			*pucM = ucM;
			*pucY = ucY;
			return;
		}
		else
		{
			// Use pulRGB->pulRGB profile
			ucC = *b;
			ucM = *g;
			ucY = *r;
			if (*ucY == 0 && *ucM == 0 && *ucY == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else if (m_ulCurId == 0)
			{
#ifdef DEBUGCMM
			printf ("\t[CMM-plane]SKIP ");
#endif
			}
			else
			{
			if (CMM_DoConversion4_plane (m_lIsCmm, ucY, ucM, ucC, ucY,
										 ucM, ucC, nSize, m_ulCurId))
			
			{
			printf("\t[CMM-RGB] NG Apply !!\r\n");
			}
			}

			*b = ucC;
			*g = ucM;
			*r = ucY;

		}
	}
	if (*pulRGB != *pulRGBO)
	{
		*pulRGBO = *pulRGB;	// RGB
		ucC = ~(*r);	// R->ucC
		ucM = ~(*g);	// G->ucM
		ucY = ~(*b);	// B->ucY
		ApplyGCRAndTonerLimit(pucK, &ucC, &ucM, &ucY,
			nTonerLimit, pucGamma);
		*pucM = ucM;
		*pucC = ucC;
		*pucY = ucY;

	}
	else
	{
		*pucK = *(pucK-1);
		*pucM = *(pucM-1);
		*pucC = *(pucC-1);
		*pucY = *(pucY-1);
	}
	*pulRGB = (*(r + 4));
	*pulRGB |= ((*(g + 4)) << 8);
	*pulRGB |= ((*(b + 4)) << 16);

}


///////////////////////////////////////////////////////////////////////////////
//Function      :SetClrPrcsFn
//Description   :This function sets the color processing function depending 
//                upon the graymode and pixel quality.
//Arguments     :
//              :uchar* pucPixAttr:[IN]
//              :int nGrayMode:[IN]
//Return value  : CONVN_FN_TYPE
///////////////////////////////////////////////////////////////////////////////
CONVN_FN_TYPE
CPRColor::SetClrPrcsFn(uchar* pucPixAttr, int
	nGrayMode)
{
	CONVN_FN_TYPE ConVersn = 0;
	//Checking for pixel quality
	if (!((*pucPixAttr & XPS_ATTR_MASK) ==
			XPS_ATTR_TEXT))
	{
		switch (nGrayMode)
		{
			case CR_GRAY_CMYK:
			case CR_GRAY_K2K:
				ConVersn=TransrgbBgucrPhotXPS;
				break;
			case CR_GRAY_IMAGEK:
				ConVersn=TransrgbBgucrImageKPhotXPS;
				break;
			case CR_GRAY_G2K:
			case CR_GRAY_ABOUTK:
				ConVersn=TransrgbBgucrPhotXPS;
				break;
			case CR_GRAY_PIXELK:
				ConVersn=TransrgbBgucrKeepgrayPhotXPS;
				break;
			case CR_GRAY_MAYBEK:
				ConVersn=TransrgbBgucrMaykeepgrayPhotXPS;
				break;
			default:;
				assert (FALSE);
		}
	}
	//If pixel quality is text
	else
	{
		switch (nGrayMode)
		{
			case CR_GRAY_CMYK:
			case CR_GRAY_K2K:
				ConVersn=TransrgbBgucrTextXPS;
				break;
			case CR_GRAY_IMAGEK:
				ConVersn=TransrgbBgucrImageKTextXPS;
				break;
			case CR_GRAY_G2K:
			case CR_GRAY_ABOUTK:
				ConVersn=TransrgbBgucrTextXPS;
				break;
			case CR_GRAY_PIXELK:

				ConVersn=TransrgbBgucrKeepgrayTextXPS;
				break;
			case CR_GRAY_MAYBEK:
				ConVersn=TransrgbBgucrMaykeepgrayTextXPS;
				break;
			default:;
				assert (FALSE);
		}

	}
	return ConVersn;;
}

#endif
#ifdef	PR_HAVE_XRGB_DRAW

///////////////////////////////////////////////////////////////////////////////
//Function      :SetXRGBbyPixel
//Description   :Entry to set xrgb value by pixel.
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :int nObjMode:[IN]
//              :unsigned char *pucRGB:[IN]
//              :unsigned		char *pucXRGB):[IN]
//Return value  :	void 
///////////////////////////////////////////////////////////////////////////////
void SetXRGBbyPixel(CPRColor *pobjColor,
	int nObjMode, unsigned char *pucRGB, unsigned
	char *pucXRGB)
{
	pucXRGB[0] = nObjMode;
	pucXRGB[1] = pucRGB[0];
	pucXRGB[2] = pucRGB[1];
	pucXRGB[3] = pucRGB[2];
}

///////////////////////////////////////////////////////////////////////////////
//Function      :SetRGBXbyPlaner
//Description   :Entry to set xrgb value by planer.
//Arguments     :
//              :CPRColor *pobjColor:[IN]
//              :unsigned char *pucR:[OUT]
//              :unsigned char *pucG:[OUT]
//              :unsigned char *pucB:[OUT]
//              :unsigned char *pucX:[OUT]
//              :int nSize:[IN]
//              :int ucTlimit:[IN]
//              :clr_tlimit_t *pobjVal:[IN]
//              :unsigned char **pucGamma):[IN]
//Return value  :	void 
///////////////////////////////////////////////////////////////////////////////
void SetRGBXbyPlaner(CPRColor *pobjColor,
	unsigned char *pucR,
	unsigned char *pucG,
	unsigned char *pucB,
	unsigned char *pucX,
	int nSize,
	int ucTlimit,
	clr_tlimit_t *pobjVal,
	unsigned char **pucGamma)

{
	memcpy(pucR, pucG, nSize);
	memcpy(pucG, pucB, nSize);
	memcpy(pucB, pucR, nSize);
	memcpy(pucR, pucX, nSize);
	memset(pucX, XRGB_ATTR_IMAGE, nSize);
}
#endif

#ifdef SUPPORT_COMPOSITEBLACK
int CPRColor::CheckCompbk(void)
{
	unsigned long ulNormalAll, ulCompbkAll;

	if ((m_ulBgucrTblFlag & CR_BGUCR_TABLE_COMPBK) == 0)
	{
		return FALSE;
	}

	ulNormalAll = m_ulCmmProfiles[CR_OBJ_IMAG] |
			m_ulCmmProfiles[CR_OBJ_GRAP] |
			m_ulCmmProfiles[CR_OBJ_TEXT] |
			m_ulCmmProfiles[CR_OBJ_LINE];
	ulCompbkAll = m_ulCmmProfilesCompbk[CR_OBJ_IMAG] |
			m_ulCmmProfilesCompbk[CR_OBJ_GRAP] |
			m_ulCmmProfilesCompbk[CR_OBJ_TEXT] |
			m_ulCmmProfilesCompbk[CR_OBJ_LINE];

	if (((ulNormalAll == 0) && (ulCompbkAll != 0)) ||
		((ulNormalAll != 0) && (ulCompbkAll == 0)))
	{
		return FALSE;
	}

	return TRUE;
}
#endif

#ifdef PR3_SUPPORT_GIPA1
///////////////////////////////////////////////////////////////////////////////
//Function      :GetGrayMode
//Description   :make m_ulColorFlag's GrayMode into nGrayMode.
//Arguments     :unsigned long (CPRGraphicDrawInfo.)m_ulColorFlag:[IN]
//Return value  :int :nGrayMode [for SetTransrgb()]
///////////////////////////////////////////////////////////////////////////////
int CPRColor::GetGrayMode(unsigned long ulColorFlag)
{
	int nGrayMode = 0;
	int nGrayFlag = ulColorFlag & CR_GRAYP_MASK;

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
			assert(0);
			break;
	}
	return nGrayMode;
}
#endif //PR3_SUPPORT_GIPA1

///////////////////////////////////////////////////////////////////////////////
//Function      :IsUseColorBrush
//Description   :Judged whether ColorBrush is used or not.
//Arguments     :
//              :CPRPageRenderer* prh:[IN]
//              :int nObjectType:[IN]
//              :CPRPrintElement * pobjPrintElement:[IN]
//              :int &nBrushUsedPlane:[OUT]
//Return value  :true->use ColorBrush  false->not use ColorBrush
///////////////////////////////////////////////////////////////////////////////
/* CMMbool CPRColor::IsUseColorBrush(CPRPageRenderer* prh,
	int nObjectType,
	CPRPrintElement * pobjPrintElement,
	int &nBrushUsedPlane)
{
	nBrushUsedPlane = 0;
	sBrushSet *psBrush = prh->m_objBrush.GetBrushPattern();

	if (psBrush == (sBrushSet *)0)
	{
		return false;
	}
	if (psBrush->ulBrushId == 0)
	{
		return false;
	}
	if (((psBrush->ulBrushType & BRUSH_MASK) == BRUSH_MONO) &&
		 ((psBrush->ucUsedPlane & BRUSH_COLORtoMONO) != BRUSH_COLORtoMONO))
	{
		return false;
	}

	switch (nObjectType)
	{
		case OBJTYPE_GRAPHICS:
		case OBJTYPE_OBJGRAPHICS:
			if (pobjPrintElement != NULL)
			{
				switch (pobjPrintElement->GetPEFlag())
				{ CMM*/
					/*
					 * Rectangle, Polyline, Polybezier窶堙�					 * Fill�ｽi窶徂窶堙ｨ�ｽj窶堙鯉ｿｽﾃｪ�ｽ窶｡窶堙哉谷ﾆ停��ｽ[ﾆ置ﾆ停�ﾆ歎ﾅｽg窶廃
					 * Fill�ｽi窶徂窶堙ｨ�ｽj窶堙�raw�ｽi�ｽﾃｼ窶ｰﾃｦ�ｽj窶堙娯�ﾂｯﾅｽﾅｾﾅｽw窶凖ｨ窶堙鯉ｿｽﾃｪ�ｽ窶｡窶堙轡raw窶堙坂�ﾃｦ2FG/BG窶堙ｰ
					 * ﾅｽg窶廃窶堋ｷ窶堙ｩ窶堋ｽ窶堙滂ｿｽA窶堋ｱ窶堋ｱ窶堙��ﾃ糠alse窶堙俄�ﾂｵ窶堙遺�ﾂ｢
					 * Clip窶堙鯉ｿｽﾃｪ�ｽ窶｡窶堙坂�ﾂｱ窶堙固�厄ｿｽ窶昶�ﾂｪﾅ津��ﾃ寂�ﾃｪ窶堙ｩ窶堋ｱ窶堙��ﾃ坂�ﾂ��ﾃｨ窶堋ｦ窶堙遺�ﾂ｢窶堋ｽ窶堙歿alse窶堙��ﾂｷ窶堙ｩ
					 */
					/* CMMcase PRINTELEMENT_RECTANGLE:
						switch (((CPRRectangle *)pobjPrintElement)->m_ulOpe & PR_DRAW_MASK)
						{
							case PR_DRAWALTFILL:
							case PR_DRAWWINDFILL:
							case PR_ALTFILL:
							case PR_WINDFILL:
								break;
							default:
								return false;
						}
						break;
					case PRINTELEMENT_POLYLINE:
						switch (((CPRPolyline *)pobjPrintElement)->m_ulOpeCode & PR_DRAW_MASK)
						{
							case PR_DRAWALTFILL:
							case PR_DRAWWINDFILL:
							case PR_ALTFILL:
							case PR_WINDFILL:
								break;
							default:
								return false;
						}
						break;
					case PRINTELEMENT_POLYBEZIER:
						switch (((CPRPolyBezier *)pobjPrintElement)->m_ulOpe & PR_DRAW_MASK)
						{
							case PR_DRAWALTFILL:
							case PR_DRAWWINDFILL:
							case PR_ALTFILL:
							case PR_WINDFILL:
								break;
							default:
								return false;
						}
						break;
					default:
						break;
				}
			}
		case OBJTYPE_TEXT:
			if ((psBrush->ucUsedPlane & BRUSH_USEDPLANE_K) == BRUSH_USEDPLANE_K)
			{
				nBrushUsedPlane |= COLOR_CMYK_K;
			}
			if ((psBrush->ucUsedPlane & BRUSH_USEDPLANE_C) == BRUSH_USEDPLANE_C)
			{
				nBrushUsedPlane |= COLOR_CMYK_C;
			}
			if ((psBrush->ucUsedPlane & BRUSH_USEDPLANE_M) == BRUSH_USEDPLANE_M)
			{
				nBrushUsedPlane |= COLOR_CMYK_M;
			}
			if ((psBrush->ucUsedPlane & BRUSH_USEDPLANE_Y) == BRUSH_USEDPLANE_Y)
			{
				nBrushUsedPlane |= COLOR_CMYK_Y;
			}
			return true;
		default:
			break;
	}

	return false;
}
CMM*/

//          Copyright (c) 2007-2009 RICOH COMPANY,LTD.
//          All Rights Reserved.
