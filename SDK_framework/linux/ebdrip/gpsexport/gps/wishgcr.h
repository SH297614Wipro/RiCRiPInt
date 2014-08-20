/*
 *	wishgcr.h : Header File for WiShGCR
 *
 *	COPYRIGHT (C) 2006 RICOH COMPANY LTD.
 *	All rights reserved.
 *
 *	2006/12/8
 *		Created from WiShGCR.h, WiShGCR.c(Version2.30)
 */

#ifndef __WISHGCR_H__
#define __WISHGCR_H__

/*
 *	Declaration of GCR parameters
 */

/* Declaration of Constant */

#define BG_SHIFT	8
#define UCR_SHIFT	8

#define	N_BLACK		256
#define	N_UCR		3
#define	N_COEF		3
#define	N_TETRA_EDGE	4

/* parameters of each tetrahedron */

typedef struct
{
	/* pointer to BG table */
	short int *BG_tbl_0123;
	/* pointer to UCR table */
	short int *d_UCR_tbl_coef;
} TETRA_PARAM_TYPE;

/* binded structure of 6 tetrahedron */

typedef struct
{
	TETRA_PARAM_TYPE tetra_CB;
	TETRA_PARAM_TYPE tetra_CG;
	TETRA_PARAM_TYPE tetra_YG;
	TETRA_PARAM_TYPE tetra_MB;
	TETRA_PARAM_TYPE tetra_MR;
	TETRA_PARAM_TYPE tetra_YR;
} TETRA6_TYPE;

/*
 *	procedure for WiShGCR
 */
#define sub_WiShGCR(ptetra, d0, d1, d2, k)				\
{									\
	short int	*BG_tbl;	/* pointer to BG */		\
	short int	*UCR_coef;	/* pointer to UCR */		\
	int		black;		/* black */			\
	int		d0_1, d1_2;	/* color differece */		\
									\
	/* calculate color difference */				\
	d0_1 = (d0) - (d1);						\
	d1_2 = (d1) - (d2);						\
									\
	/* generate black */						\
	BG_tbl = (ptetra)->BG_tbl_0123;					\
	black = ((int)*BG_tbl * (255 - (d0))				\
		+ (int)*(BG_tbl + 1) * d0_1				\
		+ (int)*(BG_tbl + 2) * d1_2				\
		+ (int)*(BG_tbl + 3) * (d2)) >> BG_SHIFT;		\
									\
	if (black > 0) {						\
		/* black generated */					\
		(k) = black;						\
									\
		/* calculate and remove UCR */				\
		UCR_coef = (ptetra)->d_UCR_tbl_coef			\
			+ black * N_UCR * N_COEF;			\
									\
		(d0) -= (int)*UCR_coef					\
			- (((int)*(UCR_coef + 1)	* d0_1			\
			 + (int)*(UCR_coef + 2) * d1_2)			\
				>> UCR_SHIFT);				\
		UCR_coef += N_COEF;					\
		(d1) -= (int)*UCR_coef					\
			- (((int)*(UCR_coef + 1)	* d0_1			\
			 + (int)*(UCR_coef + 2) * d1_2)			\
				>> UCR_SHIFT);				\
		UCR_coef += N_COEF;					\
		(d2) -= (int)*UCR_coef					\
			- (((int)*(UCR_coef + 1)	* d0_1			\
			 + (int)*(UCR_coef + 2) * d1_2)			\
				>> UCR_SHIFT);				\
	} else {							\
		/* no black */						\
		(k) = 0;						\
	}								\
}

#define WiShGCR(ptetra6, c, m, y, k)					\
{									\
	TETRA_PARAM_TYPE	*ptetra;				\
									\
	/* determine a tetrahedron */					\
	if ((m) <= (c)) {						\
		if ((y) <= (m)) {					\
			/* WCBK */					\
			ptetra = &((ptetra6)->tetra_CB);		\
			sub_WiShGCR(ptetra, c, m, y, k);		\
		}							\
		else if ((y) <= (c)) { 					\
			/* WCGK */					\
			ptetra = &((ptetra6)->tetra_CG);		\
			sub_WiShGCR(ptetra, c, y, m, k);		\
		}							\
		else {							\
			/* WTGK */					\
			ptetra = &((ptetra6)->tetra_YG);		\
			sub_WiShGCR(ptetra, y, c, m, k);		\
		}							\
	}								\
	else {								\
		if ((m) <= (y)) {					\
			/* WYRK */					\
			ptetra = &((ptetra6)->tetra_YR);		\
			sub_WiShGCR(ptetra, y, m, c, k);		\
		}							\
		else if ((y) <= (c)) { 					\
			/* WMBK */					\
			ptetra = &((ptetra6)->tetra_MB);		\
			sub_WiShGCR(ptetra, m, c, y, k);		\
		}							\
		else {							\
			/* WMRK */					\
			ptetra = &((ptetra6)->tetra_MR);		\
			sub_WiShGCR(ptetra, m, y, c, k);		\
		}							\
	}								\
									\
}

#endif	/* __WISHGCR_H__ */
