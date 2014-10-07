////////////////////////////////////////////////////////////////////////////////
// File Name            : cl_color.h
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CL_COLOR_H_
#define _CL_COLOR_H_

#ifdef __cplusplus
#include "pager.h"
#endif
#include "gps/device.h"



#define NUM_CMMOBJECT	4
#define	CMM_CMYK	(0x80000000)
#define FULLX86		0x00ffffff

/* FROM PRGrawphicsDrawinfo.h*/
#define	DIT_PHOT		0	/* ŽÊ^ƒfƒBƒU */
#define	DIT_TEXT		1	/* •¶ŽšƒfƒBƒU */
#define	DIT_GRAP		2	/* ƒOƒ‰ƒtƒBƒbƒNƒXƒfƒBƒU */
#define	DIT_CAD			3	/* CADƒfƒBƒU */
#define	DIT_MAX			4	/* ƒfƒBƒUŽí—Þ” */
#define	DIT_MASK		0x03

#define GRAY_G2K			0	/* ƒOƒŒƒC‚Ì‚Ý••ÏŠ·orBG/UCR */
#define GRAY_CMYK			1	/* í‚ÉBG/UCR */
#define GRAY_K2K			2	/* •‚Ì‚Ý••ÏŠ·orBG/UCR */
#define GRAY_CMY			3	/* BG/UCR‚µ‚È‚¢(RGB->CMY‚Ì‚Ý) */
#define GRAY_PIXELK  		4	/* ƒJƒ‰[ƒCƒ[ƒW‚Å‚àƒOƒŒƒC‚Ì‚Ý
				   ••ÏŠ·orBG/UCRi–{“–‚ÌG2Kj */
#define GRAY_MAYBEK  		5	/* ‰æ‘f—š—ð‚ðŒ©‚ÄGRAY->K•ÏŠ·‚ðs‚È‚¤ */
#define GRAY_ABOUTK   		6	/* RàGàB‚ÅGRAY->K•ÏŠ·‚ðs‚È‚¤ */
#define GRAY_IMAGEK			7	/* ƒCƒ[ƒW‚Å‚àK2K‚ðs‚È‚¤      */
#define GRAY_COMPBK			8	/* Gray change to composite k */
#define GRAY_HGRG2K			10	/* ƒOƒŒƒC‚Ì‚Ý••ÏŠ·orBG/UCR(‚–n—p) */
#define GRAY_HGRCMYK		11	/* í‚ÉBG/UCR(‚–n—p) */

#define GRAY_MASK			0xff

/* FROM PRGrawphicsDrawinfo.h*/

/* FROM PRSpool.h*/
#define FUSER_CTL_AREA_OVER		0x01	/* use FuserCtlTbl index of over area limit */
/* FROM PRSpool.h*/

/*#ifndef TRUE
#define	TRUE	(1)		// Function TRUE  value
#endif
#ifndef	FALSE
#define	FALSE	(0)		// Function FALSE value
#endif*/
#ifndef NULL
#define	NULL	0		// Null character value
#endif
#define	ICL_WR		306
#define	ICL_WG		601
#define	IC_WB		117
#define	IC_WBIAS	1024

#define CR_OBJ_IMAG	0
#define CR_OBJ_GRAP	1
#define CR_OBJ_TEXT	2
#define	CR_OBJ_LINE	3
#define	CR_OBJ_MASK	0x03	// OBJ_{IMAG,GRAP,TEXT,LINE}

#define CR_GRAY_G2K	0
#define CR_GRAY_CMYK 1
#define CR_GRAY_K2K	2
#define CR_GRAY_CMY	3
#define	CR_GRAY_PIXELK	4
#define	CR_GRAY_MAYBEK	5
#define	CR_GRAY_ABOUTK	6
#define	CR_GRAY_IMAGEK	7
#define	CR_GRAY_COMPBK	8
#define CR_GRAY_HGRG2K	10
#define CR_GRAY_HGRCMYK 11

#define CR_GRAY_MASK	0xff
#define CR_GRAY_ABOUTRANGE      1
#define CR_GRAYABS(x)           ((x) < 0 ? -(x) : (x))
#define CR_MAYBE_RANGE  8

#define CR_JUDGE_GRAY_AFTER_CMM_ON	0	/* CMMãÌOC»èðsÈ€iftHgj */
#define CR_JUDGE_GRAY_AFTER_CMM_OFF	1	/* CMMãÌOC»èðsÈíÈ¢ */

#define	CR_STRBLT_BPP_MASK	0x00000007	// BPP Mask
#define	CR_STRBLT_1BPP		0x00000000	// 1BPP
#define	CR_STRBLT_4BPP		0x00000001	// 4BPP 
#define	CR_STRBLT_8BPP		0x00000002	// 8BPP 
#define	CR_STRBLT_24BPP		0x00000003	// 24BPP 
#define	CR_STRBLT_32BPP		0x00000004	// 32BPP 

#define	CR_STRBLT_COLOR_MASK	0x00000038
#define	CR_STRBLT_MONO		0x00000000
#define	CR_STRBLT_RGB		0x00000008
#define	CR_STRBLT_KCMY		0x00000010
#define	CR_STRBLT_INDEX_MASK	0x000000c0	// Index Table
#define	CR_STRBLT_INDEX_OFF	0x00000000	// Index Table
#define CR_STRBLT_REVERSE	0x00000800	// on:Bit reverse    
#define CR_STRBLT_RGB_ORDER	0x00000200	// on:R,G,B  off:B,G,R 
#define	CR_STRBLT_INDEX_ON	0x00000040	// Index Table
#define	CR_STRBLT_THROUGH	0x00040000
#define	CR_STRBLT_SRCNOT	0x00200000
#define	CR_ATTR_TEXT		0x04000000
#define	CR_ATTR_MASK		0x07000000

/* Check CMM */
#ifdef __cplusplus

// Index Table
#define	PALSZ_1		2	// 1bit pallete size.   
#define	PALSZ_4		16	// 4bit pallete size.   
#define	PALSZ_8		256	// 8bit pallete size.   
#define	PALSZ_24	0	// 24bit color pallete size.    
#define	PALSZ_1C	6	// 1bit color pallete size.     
#define	PALSZ_4C	48	// 4bit color pallete size.     
#define	PALSZ_8C	768	// 8bit color pallete size.     
#define	PALSZ_MX	1024	// 8bit CMYK color pallete size. 

#define	CR_COLORTREATMENT_OFF	0x80000000

#define	CR_DIT_MASK		0x300000
#define	CR_DIT_PHOT		0x000000
#define	CR_DIT_TEXT		0x100000
#define	CR_DIT_GRAP		0x200000
#define	CR_DIT_CAD		0x300000

#define CR_JUDGE_GRAY_MASK	0x80000
#define CR_JUDGE_GRAY_ON	0x80000
#define CR_JUDGE_GRAY_OFF	0x00000

#define	CR_UGAMMA_MASK		0x40000
#define	CR_UGAMMA_ON		0x40000
#define	CR_UGAMMA_OFF		0x00000

#define CR_CMM_MASK		0x20000
#define CR_CMM_ON		0x20000
#define CR_CMM_OFF		0x00000
#define	CR_TONERLIMIT_MASK	0x10000
#define	CR_TONERLIMIT_ON	0x10000
#define	CR_TONERLIMIT_OFF	0x00000

#define	CR_GAMMA_MASK		0x8000
#define	CR_GAMMA_ON		0x8000
#define	CR_GAMMA_OFF		0x0000

#define	CR_GRAYP_G2K		0x0400
#define	CR_GRAYP_CMYK		0x0800
#define	CR_GRAYP_K2K		0x0C00
#define	CR_GRAYP_CMY		0x1000
#define	CR_GRAYP_PIXELK		0x1400
#define	CR_GRAYP_MAYBEK		0x1800
#define	CR_GRAYP_ABOUTK		0x1C00
#define	CR_GRAYP_IMAGEK		0x2000
#define	CR_GRAYP_HGRG2K		0x2C00
#define	CR_GRAYP_HGRCMYK	0x3000
#define	CR_GRAYP_MASK		0x3C00

#define	CR_OUTPUT_ORDER_MASK	0x100
#define	CR_OUTPUT_ORDER_NORMAL	0x100
#define	CR_OUTPUT_ORDER_REVERSE	0x000

#define	CR_OUTPUT_SPACE_MASK	0x70
#define	CR_OUTPUT_SPACE_MONO	0x10
#define	CR_OUTPUT_SPACE_RGB	0x20
#define	CR_OUTPUT_SPACE_CMY	0x30
#define	CR_OUTPUT_SPACE_CMYK	0x40
#define	CR_OUTPUT_SPACE_RK	0x50
#define	CR_OUTPUT_SPACE_XRGB	0x60
#define	CR_OUTPUT_SPACE_RK2	0x70

#define	CR_INPUT_ORDER_MASK	0x08
#define	CR_INPUT_ORDER_NORMAL	0x08
#define	CR_INPUT_ORDER_REVERSE	0x00

#define	CR_INPUT_SPACE_MASK	0x03
#define	CR_INPUT_SPACE_RGB	0x02
#define	CR_INPUT_SPACE_CMYK	0x01
#define	CR_INPUT_SPACE_GRAY	0x00

#define CR_BGUCR_NORMAL		0
#define CR_BGUCR_COMPBK		1
#define CR_BGUCR_TABLE_NORMAL	0x01
#define CR_BGUCR_TABLE_COMPBK	0x02

#ifdef PR_XPS_SUPPORT
#define XPS_ATTR_PHOTO 0x0
#define XPS_ATTR_TEXT 0x40
#define XPS_ATTR_FILL 0x80
#define XPS_ATTR_LINE 0xC0
#define XPS_ATTR_MASK 0xC0

#endif

#ifdef SUPPORT_CUTTING_RGBVALUE
#define DEFAULT_RGB_RATIO 100
#define DEFAULT_TONERLIMIT_RATIO 100

#define CR_GRAP_SRCNOT_OFF 0x00
#define CR_GRAP_SRCNOT_ON 0x01
#endif

#define	CR_NUM_FOR_NONREPEAT_URF 257
#endif

#ifdef __cplusplus
#ifndef __ARM
extern "C"
{
	void abort();
}
#endif /* __ARM */
#endif

#ifdef __cplusplus
extern "C" {
#endif

void* getColorData( unsigned long pCmm, 
                    di_dropinfo_t* pDropInfo, 
                    int limit, 
                    di_bgucrinfo_t* bgi_ptr,
                    di_gcrinfo_t* wishgcr, 
                    di_gcrinfo_t* gcrhgr_ptr, 
                    unsigned long cmmProfile );
void setRGB( void* pCPRColor, unsigned long ulFlag,
			 int nGrayMode, unsigned char **ppucGamma, int nObjMode,
			 int ucSpoolColor, unsigned char* pucPtr, int nOutputChannels);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// WiShGCR of BG and UCR parameters
typedef struct gcr_bgucr
{
	short* bg;
	short* ucr;
	gcr_bgucr()
	{
		bg = NULL;
		ucr = NULL;
	};
} gcr_bgucr_t;

// WiShGCR structure
typedef struct cr_gcrinfo
{
	gcr_bgucr_t CB;
	gcr_bgucr_t CG;
	gcr_bgucr_t YG;
	gcr_bgucr_t MB;
	gcr_bgucr_t MR;
	gcr_bgucr_t YR;
} cr_gcrinfo_t;

typedef struct clr_tlimit
{
	unsigned short text;
	unsigned short line;
	unsigned short phot;
	unsigned short fill;
	clr_tlimit()
	{
		text = 0;
		line = 0;
		phot = 0;
		fill = 0;
	}
} clr_tlimit_t;

#define	CR_CACHE_SIZE		2

typedef struct clr_cache
{
	unsigned long ulRGB;
	unsigned char ucK;
	unsigned char ucC;
	unsigned char ucM;
	unsigned char ucY;
} clr_cache_t;

#define	toner_limit_text	(limit->text)
#define	toner_limit_line	(limit->line)
#define	toner_limit_phot	(limit->phot)
#define	toner_limit_fill	(limit->fill)

#define	calc_tlimit(val)	(val * 255 / 100)

#define	SIZEOF_LUT	256
#define	MAX_LUT		255

// ROP
#define	CR_ROPEE	0x01

class CPRColor;

// type definition of function pointer
typedef void (*GCR_Method_pfT) (CPRColor*, int, int, int, unsigned
	char[]);

typedef void (*GCR_LIMIT_Method_pfT) (CPRColor*,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	int,
	unsigned char**);

typedef void (*LIMIT_Method_pfT) (CPRColor*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	int,
	int,
	unsigned char**);
typedef void (*TRANS_FN_TYPE) (CPRColor*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	int,
	int,
	clr_tlimit_t*,
	unsigned char**);

typedef void (* TRANS_FN_TYPE_1) (CPRColor*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	unsigned char*,
	int,
	unsigned char**);
#ifdef PR_XPS_SUPPORT
typedef void (*CONVN_FN_TYPE)(CPRColor *, unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned char *,
	unsigned long *,
	unsigned long *,
	int,
	unsigned char **,
	clr_tlimit_t *);
#endif
class CPRColor
{
public:
	CPRColor();

    /* CMM Instance received from CMM_init() */
	long m_lIsCmm;
	unsigned long m_ulCmmProfiles[NUM_CMMOBJECT];
    unsigned long m_ulCurId;
#ifdef SUPPORT_DYNAMIC_PROFILEOPEN
	unsigned long m_ulCurProfileGroup;
#endif
#ifdef SUPPORT_COMPOSITEBLACK
	unsigned long m_ulCmmProfilesCompbk[NUM_CMMOBJECT];
#ifdef SUPPORT_DYNAMIC_PROFILEOPEN
	unsigned long m_ulCurProfileGroupCompbk;
#endif
#endif

	/* CMM Instance */
	unsigned char m_ucBgLut[SIZEOF_LUT];	// BG look-up table
	unsigned char m_ucUcrLut[SIZEOF_LUT];	// UCR look-up table
	struct cr_gcrinfo m_sGcrInfo;		// WiShGCR parameters
	unsigned char m_ucBgHgrLut[SIZEOF_LUT];		// BG look-up table (HGR)
	unsigned char m_ucUcrHgrLut[SIZEOF_LUT];	// UCR look-up table (HGR)
	struct cr_gcrinfo m_sGcrHgrInfo;		// WiShGCR parameters (HGR)
#ifdef PR_SUPPORT_FUSER_CTL
	/*
	 * fuser temperature controlling table of current page
	 *	for (area) (photo dither -> text dither)
	 *		for (dither kind) (photo->text->graphics->cad)
	 *			for (plane) (K->C->M->Y)
	 *				for (color level)
	 */
	unsigned char m_ucFuserCtlTbl[2][DIT_MAX][4][256];
#endif /* PR_SUPPORT_FUSER_CTL */

	struct clr_tlimit m_sPqLimit;
	unsigned char* m_pucPqTbl;
	unsigned char* m_pucRPqTbl;

	struct clr_tlimit m_sPqLimitPhot;
	unsigned char* m_pucPqTblPhot;
	unsigned char* m_pucRPqTblPhot;

	struct clr_tlimit m_sPqLimitText;
	unsigned char* m_pucPqTblText;
	unsigned char* m_pucRPqTblText;

	struct clr_tlimit m_sPqLimitGrap;
	unsigned char* m_pucPqTblGrap;
	unsigned char* m_pucRPqTblGrap;

	struct clr_tlimit pqlimit_ed;
	unsigned char *pqtbl_ed;
	unsigned char *rpqtbl_ed;
#ifdef SUPPORT_CUTTING_RGBVALUE
	unsigned char m_ucRgbRatio[4];
	unsigned char m_ucRatioColorTbl[OBJ_MAX][256];
#ifdef SUPPORT_COMPOSITEBLACK
	unsigned char m_ucRgbRatioCompbk[4];
	unsigned char m_ucRatioColorTblCompbk[OBJ_MAX][256];
#endif
#endif
#ifdef SUPPORT_CUTTING_TONERLIMIT
	unsigned char m_ucTonerLimitRatio[4];
#endif
#ifdef SUPPORT_COMPOSITEBLACK
	unsigned char m_ucBgLutCompbk[SIZEOF_LUT];
	unsigned char m_ucUcrLutCompbk[SIZEOF_LUT];
	unsigned long m_ulBgucrTblFlag;	/*
					 * bgucr flag for
					 * which data had set
					 * 0x01:normal, 0x02:compbk, 0x03:both
					 */
	GCR_Method_pfT		m_pFuncGcrCompbk;	/* pointer of compbk function */
	GCR_LIMIT_Method_pfT	m_pFuncGcrLimitCompbk;
	unsigned char m_ucRenderingIsmono;
#endif
	struct CPRCmm* m_psCmmColor;
	unsigned long m_ulGrayCount;
	unsigned short m_usGrayHistory;
	unsigned long m_ulClrUsedPlane;	// KKCCMMYY
	int m_nIsPqtc;	//pqtc flag for current resolution and depth
	int m_nDevPqtc;	//pqtc flag for the printer model
	int m_nIsGcr;		// GCR presence flag
	GCR_Method_pfT m_pFuncGcr;
	GCR_Method_pfT m_pFuncGcrHgr;
	GCR_LIMIT_Method_pfT m_pFuncGcrLimit;
	GCR_LIMIT_Method_pfT m_pFuncGcrHgrLimit;
	LIMIT_Method_pfT m_pFuncLimit;
	
	int m_nRenderNColor;	// Number of Render color (equals prh->m_objRender.m_nNColor)
	unsigned char m_ucIsGrayJudge;	//»ÝÌ`æR}hÉÂ¢ÄÌCMMãÌOC»èÌL³ðÛ¶
	clr_cache_t m_sCache[CR_CACHE_SIZE];

public:
#ifdef PR_XPS_SUPPORT
	int DoColorProcessing(CPRPageRenderer *prh);
	int SetPixelAttribute(prh_t* prh, unsigned char *pcATBuf, int&
		rnGrayMode, int& rnObjMode);
	void ApplyBgucrsGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);

	CONVN_FN_TYPE SetClrPrcsFn(uchar* pucPixAttr, int nGrayMode);
	void ApplyBgucrImageKsGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);

	void
	ApplyBgucrKeepgraysGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);
	void ApplyBgucrMaybeKeepgraysGammasXPS(unsigned char *pucPRGB,
		unsigned char *r,
		unsigned char *g,
		unsigned char *b,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		unsigned long *pulRGB,
		unsigned long *pulRGBO,
		int size,
		int nObjectMode,
		unsigned char **pucGamma,
		clr_tlimit_t *limit);
#endif
#ifdef PR_SUPPORT_FUSER_CTL
	///////////////////////////////////////////////////////////////////////////////
	//Function      :GetFuserCtlKCMY 
	//Description   :Get the Fuser temperature information for KCMY
	//Arguments     :
	//              :unsigned char ucK:[IN]
	//              :unsigned char ucC:[IN]
	//              :unsigned char ucM:[IN]
	//              :unsigned char ucY:[IN]
	//              :unsigned char *pucTbl:[IN]
	//Return value  :unsigned char
	///////////////////////////////////////////////////////////////////////////////
	inline unsigned char GetFuserCtlKCMY(unsigned char ucK, unsigned char ucC,
		unsigned char ucM, unsigned char ucY, unsigned char *pucTbl)
	{
		return (*(pucTbl + ucK) &
				*(pucTbl + 256 + ucC) &
				*(pucTbl + 256 * 2 + ucM) &
				*(pucTbl + 256 * 3 + ucY));
	}
	///////////////////////////////////////////////////////////////////////////////
	//Function      :GetFuserCtlK
	//Description   :Get the Fuser temperature information for K
	//Arguments     :
	//              :unsigned char ucK:[IN]
	//              :unsigned char *pucTbl:[IN]
	//Return value  :unsigned char
	///////////////////////////////////////////////////////////////////////////////
	inline unsigned char GetFuserCtlK(unsigned char ucK, unsigned char *pucTbl)
	{
		return (*(pucTbl + ucK));
	}
	///////////////////////////////////////////////////////////////////////////////
	//Function      :GetFuserCtlKC
	//Description   :Get the Fuser temperature information for KC
	//Arguments     :
	//              :unsigned char ucK:[IN]
	//              :unsigned char ucC:[IN]
	//              :unsigned char *pucTbl:[IN]
	//Return value  :unsigned char
	///////////////////////////////////////////////////////////////////////////////
	inline unsigned char GetFuserCtlKC(unsigned char ucK, unsigned char ucC,
		unsigned char *pucTbl)
	{
		return (*(pucTbl + ucK) &
				*(pucTbl + 256 + ucC));
	}
	int MakePaletteColor(unsigned long,
		unsigned char *,
		unsigned char *,
		unsigned char,
		int,
		int,
		unsigned long,
		clr_tlimit_t *,
		TRANS_FN_TYPE,
		unsigned char **,
		unsigned char *);
	int MakePaletteMono (unsigned long,
		unsigned char *,
		unsigned char *,
		unsigned char,
		int,
		unsigned long,
		TRANS_FN_TYPE_1,
		unsigned char **,
		unsigned char *);
#else
	int MakePaletteColor(unsigned long,
		unsigned char *,
		unsigned char *,
		int,
		int,
		clr_tlimit_t *,
		TRANS_FN_TYPE,
		unsigned char **);
	int MakePaletteMono (unsigned long,
		unsigned char *,
		unsigned char *,
		int,
		TRANS_FN_TYPE_1,
		unsigned char **);
#endif /* PR_SUPPORT_FUSER_CTL */
	TRANS_FN_TYPE SetTransrgb (unsigned long, int);
	TRANS_FN_TYPE SetTransrgbRK2 (unsigned long, int);
	TRANS_FN_TYPE_1 SetTransgray (unsigned long, int);
	TRANS_FN_TYPE SetTransrgbBrush (int);
	TRANS_FN_TYPE_1 SetTransgrayBrush (void);
	void ApplyRgb2Cmy(unsigned char[], unsigned char[]);
#ifdef SUPPORT_CUTTING_RGBVALUE
	void ApplyBgucr(unsigned char[], unsigned char[], int, unsigned long);
	void ApplyBgucrHgr(unsigned char[], unsigned char[], int, unsigned long);
	void ApplyBgucrKeepgray(unsigned char[], unsigned char[],
							int, unsigned long);
	void ApplyBgucrHgrKeepgray(unsigned char[], unsigned char[],
							int, unsigned long);
#else
	void ApplyBgucr(unsigned char[], unsigned char[]);
	void ApplyBgucrHgr(unsigned char[], unsigned char[]);
	void ApplyBgucrKeepgray(unsigned char[], unsigned char[]);
	void ApplyBgucrHgrKeepgray(unsigned char[], unsigned char[]);
#endif
	void ApplyBgucrKeepblack(unsigned char[], unsigned char[]);
#ifdef SUPPORT_COMPOSITEBLACK
	void ApplyBgucrCompbk(unsigned char[], unsigned char[], int, unsigned long);
#endif
	void ApplyBgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrsHgrGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyTwinColorRK2BgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrsGammasURF (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrsHgrGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotTwinColorRK2BgucrsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrHgrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrHgrKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrAboutKeepgray(unsigned char rgb[], unsigned char
		kcmy[]);
	void ApplyBgucrMaybeKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrAboutKeepgraysGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplyBgucrImageKsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrImageKsGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
#ifdef SUPPORT_COMPOSITEBLACK
	void ApplyBgucrCompbksGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	void ApplySrcnotBgucrCompbksGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
#endif
	void ApplyRgb2CmyGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	///////////////////////////////////////////////////////////////////////////////
	//Function      :ApplyUserGammas 
	//Description   :Apply the user gamma 
	//Arguments     :
	//              :unsigned char* pucUserGamma:[IN]
	//              :int size:[IN]
	//              :unsigned char *pucValue:[IN/OUT]
	//Return value  :void
	///////////////////////////////////////////////////////////////////////////////
	void
	ApplyUserGammas(unsigned char* pucUserGamma,
		int nSize,
		unsigned char* pucValue)
	{
		if (pucUserGamma == (unsigned char*)0)
		{
			return;
		}
		for(int i=0; i<nSize; i++)
		{
			pucValue[i] = pucUserGamma[ pucValue[i] ];
		}
	}
	inline void DoGammaK(unsigned char *in_k,
		unsigned char *out_k,
		unsigned char **gamma)
	{;
		/* CMMassert (in_k && out_k);*/
		*out_k = *in_k;
	#ifdef GAMMA_THROUGH
		return;
	#endif
		ApplyUserGammas(*(gamma+m_nRenderNColor), 1, out_k);
		*out_k = (*gamma)[*out_k];
	}
	//private:
	void GammaSNoTonerLimit (unsigned char **ppucGamma,
		int nSize,
		unsigned char *pucK,
		unsigned char *pucC,
		unsigned char *pucM,
		unsigned char *pucY);
	void DoGamma(unsigned char[], int, int, clr_tlimit_t*, unsigned
		char**);
	void DoGammaRK2(unsigned char[], int, int, clr_tlimit_t*, unsigned
		char**);
	void PreDoGammaRK2(unsigned char[], int, int, clr_tlimit_t*, unsigned
		char**);
	void DoGammaS (int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma,
		int size,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y);
	void DoTonerLimits(int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma,
		int size,
		unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y);
	int SetTonerLimitInColor (int obj_kind, clr_tlimit_t * limit);
	void UpdateLut(unsigned char *, unsigned char *,
					unsigned char *, unsigned char *);
#ifdef SUPPORT_COMPOSITEBLACK
	void UpdateLutExt(unsigned char *, unsigned char *, int);
#endif
	void MakeLut (float, float, float, float);
	/* CMMvoid GetDeviceColor (ginf_t *,
		unsigned char **,
		unsigned char *,
		unsigned char *);*/

	void TransURF2Cmyk (const unsigned char *pucSrcPtr,
		unsigned char *ptr,
		const unsigned long ulWidth,
		const unsigned long ulHeight,
		const unsigned long ulImgSize,
		unsigned char nTLimit,
		clr_tlimit_t * pVal,
		unsigned char **ppucGamma);
	void TransURFDirect (
		unsigned long ulFlag,
		unsigned long ulWidth,
		unsigned long ulHeight,
		unsigned long ulImgSize,
		unsigned char *pucSrcptr,
		unsigned char *ptr,
		unsigned char *pucIndexTable,
		unsigned char nTLimit,
		clr_tlimit_t * pVal,
		unsigned char **ppucGamma);

	void TransrgbDirect (
		unsigned long,
		int,
		unsigned char *,
		unsigned char *,
		unsigned char,
		clr_tlimit_t *,
		TRANS_FN_TYPE,
		unsigned char **gamma,
		int,
		int);
	void ApplySrcnotRgb2CmyGammas (unsigned char *k,
		unsigned char *c,
		unsigned char *m,
		unsigned char *y,
		int size,
		int obj_kind,
		int toner_limit_on,
		clr_tlimit_t * limit,
		unsigned char **gamma);
	inline void GammaK(unsigned char* Blk,
		unsigned char* Cyan,
		unsigned char* Mag,
		unsigned char* Yel,
		unsigned char** Gam,
		unsigned char& KPlane)
	{
		unsigned char ucK = ~*Yel;
		ApplyUserGammas(*(Gam+m_nRenderNColor), 1, &ucK);
		*Blk = (*Gam)[ucK];
		*Cyan = 0;
		*Mag = 0;
		*Yel = 0;
		KPlane |= *Blk;
	}
	inline void GammaKcmy(unsigned char* Blk,
		unsigned char* Cyan,
		unsigned char* Mag,
		unsigned char* Yel,
		unsigned char** Gam,
		unsigned char& KPlane)
	{
		unsigned char ucK = *Yel;
		ApplyUserGammas(*(Gam+m_nRenderNColor), 1, &ucK);
		*Blk = (*Gam)[ucK];
		*Cyan = 0;
		*Mag = 0;
		*Yel = 0;
		KPlane |= *Blk;
	}
	void ApplyTwinColor (
		unsigned char rgb[],
		unsigned char kcmy[])
	{
		unsigned char R, G, B;

		R = rgb[0];
		G = rgb[1];
		B = rgb[2];

		if (R == G && G == B)
		{
			kcmy[0] = ~R;
			kcmy[1] = 0;
			kcmy[2] = kcmy[3] = 0;
			return;
		}

		kcmy[0] = 0;
		kcmy[1] = R;
		kcmy[2] = 0;
		kcmy[3] = 0;
	}
	void
	ApplyCmyk2Gray (unsigned char kcmy[])
	{
		unsigned int g;

		g = kcmy[0] + (kcmy[1] * ICL_WR + kcmy[2] * ICL_WG + kcmy[3] *
			IC_WB) / IC_WBIAS;
		if (g > 255)
			g = 255;
		kcmy[0] = g;
		kcmy[1] = 0;
		kcmy[2] = 0;
		kcmy[3] = 0;
	}
	/* CMM void SetColorGinfColorMask(prh_t *prh, int obj_mode, uchar *fgp,
		uchar *bgp,
		uchar **gamma, ginf_t * ginf, int orig_obj_mode, clr_tlimit_t
		*limit);
	void SetcolorGinfIsColor(prh_t *prh, int obj_mode, uchar *fgp,
		uchar *bgp, uchar **gamma,
		int orig_obj_mode, clr_tlimit_t *limit, ginf_t * ginf);
	int SetcolorGinfColorGradation(prh_t *prh, ginf_t *ginf,
		clr_tlimit_t *limit, int obj_mode);
	int SetcolorGinfForDespool(prh_t *prh, ginf_t *ginf,
		clr_tlimit_t *limit, int obj_mode);*/

	void SetTransgcr(void);
	// CMMvoid SetIsGrayJudge(prh_t *prh, int obj_mode);
#ifdef SUPPORT_CUTTING_RGBVALUE
	void CPRColor::SetRgbRatioAndTable(unsigned char ucMode,
		unsigned char ucPhot,
		unsigned char ucFill,
		unsigned char ucText,
		unsigned char ucLine);
#endif /* SUPPORT_CUTTING_RGBVALUE */
#ifdef SUPPORT_COMPOSITEBLACK
	int CheckCompbk(void);
#endif
#ifdef PR3_SUPPORT_GIPA1
	int GetGrayMode(unsigned long ulColorFlag);
#endif
	/* CMMbool IsUseColorBrush(CPRPageRenderer * prh,
		int nObjectType,
		CPRPrintElement * pobjPrintElement,
		int &nBrushUsedPlane);*/
};

#ifdef SUPPORT_CUTTING_RGBVALUE
#define ApplyRgbRatioRgb(pobjColor, pucR, pucG, pucB, nSize, \
		nObjKind, ulSrcNot) \
{ \
	int nRatio = (pobjColor)->m_ucRgbRatio[(nObjKind)]; \
	unsigned char *pucTbl; \
	unsigned char *pucTempR, *pucTempG, *pucTempB; \
	int nCnt; \
	pucTbl = &((pobjColor)->m_ucRatioColorTbl[(nObjKind)][0]); \
	pucTempR = (pucR); \
	pucTempG = (pucG); \
	pucTempB = (pucB); \
	if (nRatio != 100) { \
		if ((ulSrcNot)) { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = 255 - *(pucTbl + 255 - *pucTempR); \
				*pucTempG = 255 - *(pucTbl + 255 - *pucTempG); \
				*pucTempB = 255 - *(pucTbl + 255 - *pucTempB); \
			} \
		} else { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = *(pucTbl + *pucTempR); \
				*pucTempG = *(pucTbl + *pucTempG); \
				*pucTempB = *(pucTbl + *pucTempB); \
			} \
		} \
	} \
}

#define ApplyRgbRatioGray(pobjColor, pucK, nSize, nObjKind, ulSrcNot) \
{ \
	int nRatio = (pobjColor)->m_ucRgbRatio[(nObjKind)]; \
	unsigned char *pucTbl; \
	unsigned char *pucTempK; \
	int nCnt; \
	pucTbl = &((pobjColor)->m_ucRatioColorTbl[(nObjKind)][0]); \
	pucTempK = (pucK); \
	if (nRatio != 100) { \
		if ((ulSrcNot)) { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, pucTempK++) { \
				*pucTempK = *(pucTbl + *pucTempK); \
			} \
		} else { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, pucTempK++) { \
				*pucTempK = 255 - *(pucTbl + 255 - *pucTempK); \
			} \
		} \
	} \
}

#ifdef SUPPORT_COMPOSITEBLACK
#define ApplyRgbRatioRgbCompbk(pobjColor, pucR, pucG, pucB, nSize, \
		nObjKind, ulSrcNot) \
{ \
	int nRatio = (pobjColor)->m_ucRgbRatioCompbk[(nObjKind)]; \
	unsigned char *pucTbl; \
	unsigned char *pucTempR, *pucTempG, *pucTempB; \
	int nCnt; \
	pucTbl = &((pobjColor)->m_ucRatioColorTblCompbk[(nObjKind)][0]); \
	pucTempR = (pucR); \
	pucTempG = (pucG); \
	pucTempB = (pucB); \
	if (nRatio != 100) { \
		if ((ulSrcNot)) { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = 255 - *(pucTbl + 255 - *pucTempR); \
				*pucTempG = 255 - *(pucTbl + 255 - *pucTempG); \
				*pucTempB = 255 - *(pucTbl + 255 - *pucTempB); \
			} \
		} else { \
			for (nCnt = (nSize); nCnt > 0; nCnt--, \
				pucTempR++, pucTempG++, pucTempB++) { \
				*pucTempR = *(pucTbl + *pucTempR); \
				*pucTempG = *(pucTbl + *pucTempG); \
				*pucTempB = *(pucTbl + *pucTempB); \
			} \
		} \
	} \
}
#endif
#endif /* SUPPORT_CUTTING_RGBVALUE */
extern void MakeLut (CPRColor*,
	float,
	float,
	float,
	float);
#ifdef SUPPORT_CUTTING_RGBVALUE
extern void ApplyRgb2Gray (CPRColor *, unsigned char[], int, unsigned long);
#else
extern void ApplyRgb2Gray (unsigned char[]);
#endif

extern void ApplyTwinColorGammas (CPRColor*,
	unsigned char[],
	unsigned char[],
	unsigned char[],
	unsigned char[],
	unsigned char[],
	int,
	unsigned char **);
//extern void ApplyCmyk2Gray (unsigned char[]);

#ifdef	PR_HAVE_XRGB_DRAW
extern void SetXRGBbyPixel(CPRColor*, int, unsigned char *, unsigned
	char *);
extern void SetRGBXbyPlaner(CPRColor*, unsigned char *,
	unsigned char *, unsigned char *, unsigned char *,
	int, int, clr_tlimit_t *, unsigned char **);
#endif

/* CMM
int
PrRgb2Cmyk (prh_t * prh,
	uchar obj,
	uchar r,	// IN
	uchar g,	// IN
	uchar b,	// IN
	uchar * c,	// OUT
	uchar * m,	// OUT
	uchar * y,	// OUT
	uchar * k);	// OUT

int
PrRgb2CmykPixels (prh_t * prh,
	uchar obj,
	uchar * pucRgb,		// IN
	uchar * pucCmyk,	// OUT
	ulong ulSize);

int
PrRgb2K (prh_t * prh,
	uchar obj,
	uchar r,	// IN
	uchar g,	// IN
	uchar b,	// IN
	uchar * k);	// OUT

int
PrRgb2KPixels (prh_t * prh,
	uchar obj,
	uchar * pucRgb,		// IN
	uchar * pucK,		// OUT
	ulong ulSize);
CMM*/
/* CMM
#if defined(PR_SUPPORT_FUSER_CTL) || defined(USE_SINGLE_ROP66_PARTIAL_DETECTION)
int SetcolorGinf (CPRPageRenderer * prh,
	ginf_t * ginf,
	int obj_mode,
	int obj_type,
	long lSx,
	long lEx,
	long lSy,
	long lEy,
	uchar ucCoordFlag,
	CPRPrintElement * pobjPrintElement = NULL);
#else
int SetcolorGinf (CPRPageRenderer * prh,
	ginf_t * ginf,
	int obj_mode,
	int obj_type,
	CPRPrintElement * pobjPrintElement = NULL);
#endif
CMM*/
#ifdef PR_XPS_SUPPORT
static void TransrgbBgucrPhotXPS(CPRColor* color, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrTextXPS(CPRColor *color, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void
TransrgbBgucrImageKPhotXPS(CPRColor *color, unsigned char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);

static void TransrgbBgucrImageKTextXPS(CPRColor *color, unsigned char
	*pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrKeepgrayTextXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrKeepgrayPhotXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrMaykeepgrayTextXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
static void TransrgbBgucrMaykeepgrayTextXPS(CPRColor *color, unsigned
	char *pucPRGB,
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	unsigned long *RGB,
	unsigned long *RGBO,
	int size,
	unsigned char **pucGamma,
	clr_tlimit_t *limit);
#endif // __cplusplus
#endif // PR_XPS_SUPPORT
#endif // _CL_COLOR_H_


