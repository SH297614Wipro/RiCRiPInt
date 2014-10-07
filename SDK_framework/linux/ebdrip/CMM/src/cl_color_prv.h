////////////////////////////////////////////////////////////////////////////////
// File Name            : cl_color_prv.h
// Author				: Wipro Technologies
// $Date				:  $
// Description          : Header file for the color related data
// Copyright(c)			: 2007 by RICOH Co.,LTD.
// $Revision			: 1.1 $
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CL_COLOR_PRV_H_
#define _CL_COLOR_PRV_H_

#include	"cl_color.h"
#include	"wishgcr.h"
#include	"cl_linear_index_prv.h"
#define ICL_FIX_SHIFT	16
#define TONER_LIMIT(LIMIT, SUM, K, C, M, Y) \
{ \
	unsigned long	ratio; \
	;assert(SUM > K);\
	ratio = (((LIMIT - K) << ICL_FIX_SHIFT) / (SUM - K)); \
	C = (ratio * C) >> ICL_FIX_SHIFT; \
	M = (ratio * M) >> ICL_FIX_SHIFT; \
	Y = (ratio * Y) >> ICL_FIX_SHIFT; \
}
// CMY —p 
#define TONER_LIMIT_CMY(LIMIT, SUM, C, M, Y) \
{ \
	unsigned long	ratio; \
	ratio = ((LIMIT << ICL_FIX_SHIFT) / SUM); \
	C = (ratio * C) >> ICL_FIX_SHIFT; \
	M = (ratio * M) >> ICL_FIX_SHIFT; \
	Y = (ratio * Y) >> ICL_FIX_SHIFT; \
}

//	BG/UCR

#define BG_UCR(R, G, B, K, C, M, Y, BGTBL, UCRTBL) \
{ \
	unsigned char	buC, buM, buY, buMINCOLOR; \
	unsigned int	buUCR; \
\
	buMINCOLOR = buC = ~(R); \
	if ((buM = ~(G)) < buMINCOLOR) buMINCOLOR = buM; \
	if ((buY = ~(B)) < buMINCOLOR) buMINCOLOR = buY; \
	K = BGTBL[buMINCOLOR]; \
	buUCR = UCRTBL[buMINCOLOR]; \
	C = buC - buUCR; \
	M = buM - buUCR; \
	Y = buY - buUCR; \
}

// BGUCR + SRCNOT
#define BG_UCR_SRCNOT(R, G, B, K, C, M, Y, BGTBL, UCRTBL) \
{ \
	unsigned char	buC, buM, buY, buMINCOLOR; \
	unsigned int	buUCR; \
\
	buMINCOLOR = buC = (R); \
	if ((buM = (G)) < buMINCOLOR) buMINCOLOR = buM; \
	if ((buY = (B)) < buMINCOLOR) buMINCOLOR = buY; \
	K = BGTBL[buMINCOLOR]; \
	buUCR = UCRTBL[buMINCOLOR]; \
	C = buC - buUCR; \
	M = buM - buUCR; \
	Y = buY - buUCR; \
}

// BGUCR + GAMMA
#define BG_UCR_GAMMA(R, G, B, K, C, M, Y, BGTBL, UCRTBL, GAMK, GAMC, GAMM, GAMY) \
{ \
	unsigned char	buC, buM, buY, buMINCOLOR; \
	unsigned int	buUCR; \
\
	buMINCOLOR = buC = ~(R); \
	if ((buM = ~(G)) < buMINCOLOR) buMINCOLOR = buM; \
	if ((buY = ~(B)) < buMINCOLOR) buMINCOLOR = buY; \
	buUCR = UCRTBL[buMINCOLOR]; \
	K = GAMK[BGTBL[buMINCOLOR]]; \
	C = GAMC[buC - buUCR]; \
	M = GAMM[buM - buUCR]; \
	Y = GAMY[buY - buUCR]; \
}

// BGUCR + SRCNOT + GAMMA
#define BG_UCR_SRCNOT_GAMMA(R, G, B, K, C, M, Y, BGTBL, UCRTBL, GAMK, GAMC, GAMM, GAMY) \
{ \
	unsigned char	buC, buM, buY, buMINCOLOR; \
	unsigned int	buUCR; \
\
	buMINCOLOR = buC = (R); \
	if ((buM = (G)) < buMINCOLOR) buMINCOLOR = buM; \
	if ((buY = (B)) < buMINCOLOR) buMINCOLOR = buY; \
	buUCR = UCRTBL[buMINCOLOR]; \
	K = GAMK[BGTBL[buMINCOLOR]]; \
	C = GAMC[buC - buUCR]; \
	M = GAMM[buM - buUCR]; \
	Y = GAMY[buY - buUCR]; \
}

#define	ICL_WR		306
#define	ICL_WG		601
#define	IC_WB		117
#define	IC_WBIAS	1024

static void
TransGcrLimit(
	CPRColor* color,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	int toner_limit,
	unsigned char **gamma)
{
	int K;
	int C = (int)*c;
	int M = (int)*m;
	int Y = (int)*y;
	unsigned char *gtk = gamma[0];
	unsigned char *gtc = gamma[1];
	unsigned char *gtm = gamma[2];
	unsigned char *gty = gamma[3];
	int sum_cmyk;

	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&color->m_sGcrInfo;;
	assert(gtk && gtc && gtm && gty);

	WiShGCR(m_sGcrInfo, C, M, Y, K);

	K = (int)gtk[K];
	C = (int)gtc[C];
	M = (int)gtm[M];
	Y = (int)gty[Y];

	sum_cmyk = K + C + M + Y;
	if (sum_cmyk > toner_limit)
	{
		TONER_LIMIT (toner_limit, sum_cmyk, K, C, M, Y);
	}
	*k = (unsigned char)K;
	*c = (unsigned char)C;
	*m = (unsigned char)M;
	*y = (unsigned char)Y;
	return;
}

static void
TransGcrHgrLimit(
	CPRColor* color,
	unsigned char *k,
	unsigned char *c,
	unsigned char *m,
	unsigned char *y,
	int toner_limit,
	unsigned char **gamma)
{
	int K;
	int C = (int)*c;
	int M = (int)*m;
	int Y = (int)*y;
	unsigned char *gtk = gamma[0];
	unsigned char *gtc = gamma[1];
	unsigned char *gtm = gamma[2];
	unsigned char *gty = gamma[3];
	int sum_cmyk;

	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&color->m_sGcrHgrInfo;;
	assert(gtk && gtc && gtm && gty);

	WiShGCR(m_sGcrInfo, C, M, Y, K);

	K = (int)gtk[K];
	C = (int)gtc[C];
	M = (int)gtm[M];
	Y = (int)gty[Y];

	sum_cmyk = K + C + M + Y;
	if (sum_cmyk > toner_limit)
	{
		TONER_LIMIT (toner_limit, sum_cmyk, K, C, M, Y);
	}
	*k = (unsigned char)K;
	*c = (unsigned char)C;
	*m = (unsigned char)M;
	*y = (unsigned char)Y;
	return;
}

static void
TransGcr(
	CPRColor* color,
	int C,
	int M,
	int Y,
	unsigned char kcmy[])
{
	int K;

	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&color->m_sGcrInfo;

	WiShGCR(m_sGcrInfo, C, M, Y, K);

	kcmy[0] = (unsigned char)K;
	kcmy[1] = (unsigned char)C;
	kcmy[2] = (unsigned char)M;
	kcmy[3] = (unsigned char)Y;
}

static void
TransGcrHgr(
	CPRColor* color,
	int C,
	int M,
	int Y,
	unsigned char kcmy[])
{
	int K;

	TETRA6_TYPE *m_sGcrInfo = (TETRA6_TYPE *)&color->m_sGcrHgrInfo;

	WiShGCR(m_sGcrInfo, C, M, Y, K);

	kcmy[0] = (unsigned char)K;
	kcmy[1] = (unsigned char)C;
	kcmy[2] = (unsigned char)M;
	kcmy[3] = (unsigned char)Y;
}

#endif // _CL_COLOR_PRV_H_


