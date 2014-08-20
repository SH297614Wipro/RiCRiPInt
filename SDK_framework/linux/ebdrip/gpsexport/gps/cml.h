/*
 *      cml.h :  Header File for libCMM Users
 *
 *      COPYRIGHT (C) 2001-2005 RICOH COMPANY LTD.
 *      All rights reserved.
 */

#define AP_tablesize 256

extern long CMM_Init(long (*)(), void (*)(), void *, unsigned long);
extern long CMM_End(long);
extern long CMM_OpenProfile(long, unsigned char, char *, unsigned long);
extern long CMM_CloseProfile(long, unsigned long);
extern long CMM_DoConversion4_bgr(long, unsigned char *, unsigned char
	*, unsigned long, unsigned long);
extern long CMM_DoConversion4_rgb(long, void *, void *, unsigned long,
	unsigned long, char, char);
extern long CMM_DoConversion4_rgb_1(long, void *, void *, unsigned
	long, unsigned long, char, char);
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
extern long CMM_DoConversion4_cmy(long, void *, void *, unsigned long,
	unsigned long, char, char);
extern long CMM_DoConversion4_rgbcmy(long, unsigned char *, unsigned
	char *, unsigned long, unsigned long);
extern long CMM_DoConversion3_bgr(long, unsigned char *, unsigned char
	*, unsigned long, unsigned long);
extern long CMM_MakeTable(long, unsigned long, unsigned long, unsigned
	char *, unsigned char [AP_tablesize]);
extern long CMM_UpdateCLUTdata(long, unsigned long, unsigned char [AP_tablesize]);
extern long CMM_UpdateCLUTdata_cmyk(long, unsigned long, unsigned char
	[AP_tablesize]);
extern long CMM_SaveCLUTdata(long, unsigned long);
extern long CMM_RestoreCLUTdata(long, unsigned long);
extern long   CMM_GetGridTableData(long hCmm, unsigned long ulProfileId, void	**ppvGridTable) ;

/*
 *
 *      COPYRIGHT (C) 2002-2005 RICOH COMPANY LTD.
 *      All rights reserved.
 *
 */
