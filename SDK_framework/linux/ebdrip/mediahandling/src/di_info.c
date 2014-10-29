#include "gps/di_info.h"
#include "gps/di_getinfo.h"
#include "gps/gps_color_inc.h"
#include "gps/gps_color_inc2.h"


/*
 * startup.
 */
#define	CATEGORY_DI		"DI"
#define DEF_PAPER           DI_PAPER_NORMAL
#define DEF_PRT_MODE        0
#define DEF_DIT_MODE        0
#define DEF_RESO            600
#define DEF_BIT             1 
#define DEF_RESONUM		1
#define DEF_DIT			2
#define DEF_PLANE		1
#define	DI_GET_OK	0
#define	MAX_KEY_LEN		(32)
#define	MAX_CATEGORY_LEN	MAX_KEY_LEN
#define	MAX_VALUE_LEN		MAX_KEY_LEN
#define	SERCH_OK			(0)
#define	SERCH_KEY_NOT_FOUND		(-1)
#define	SERCH_CATEGORY_NOT_FOUND	(-2)
#define	SERCH_BUFFER_OVER		(-3)
#define	SERCH_ILLEGAL_PARAM		(-4)
#define	SERCH_INIT_ERROR		(-5)
#define SERCH_KEY_OK			0
#define	DI_GET_NG			-1
#define DI_OK				0
#define FALSE 			0         
#define TRUE 			1
#define DEF_BG_SP           0.0
#define DEF_BG_SLANT        1.0
#define DEF_UCR_SP          0.0
#define DEF_UCR_SLANT       1.0

static int  def_resox = DEF_RESO;
static int  def_resoy = DEF_RESO;
static int  def_bit = DEF_BIT;
static int  def_paper = DEF_PAPER;
static int  def_prt_mode = DEF_PRT_MODE;
static int  def_dit_mode = DEF_DIT_MODE;
static int	support_dithergamma;
static char buf[DI_MAX_VALUE_LEN];
extern unsigned char outbuf[MAX_VALUE_LEN];
extern char *gps_shdm_addr;
extern long loffset;
extern long prof_num;
typedef unsigned short gps_color_rid_GPS_t;
gps_color_rid_GPS_t rID[4]; 

int get_maxdit( int *max_dit );
int get_maxplane( int *max_plane );
static int gps_dgmd[5] = { PHOTO_DRAWMODE, TEXT_DRAWMODE, THIN_DRAWMODE, GRAP_DRAWMODE, PHOTO2_DRAWMODE	};
static char *category_di = "DI";
int fflag = 0;

int get_appinfo_di_GPS( char *key, char *category, long  len, char *buf )
{
	int retval;
	printf("Entering get_appinfo_di_GPS()..\n");
	retval = GPS_GetModelInfo(1, 1, key, category,sizeof(outbuf));
	
	switch( retval ) 
	{
	case SERCH_OK: /* Â�Â¬Å’Ã· */
		return DI_PINI_OK;
	case SERCH_KEY_NOT_FOUND: /* Å Yâ€œâ€“â€šÂ·â€šÃ©keyâ€šÂªâ€šÃ�â€šÃ‚â€šÂ©â€šÃ§â€šÃˆâ€šÂ©â€šÃ�â€šÂ½ */
		return DI_PINI_KEY_NOT_FOUND;
	case SERCH_CATEGORY_NOT_FOUND: /* Å Yâ€œâ€“â€šÂ·â€šÃ©categoryâ€šÂªâ€šÃ�â€šÃ‚â€šÂ©â€šÃ§â€šÃˆâ€šÂ©â€šÃ�â€šÂ½ */
		return DI_PINI_CATEGORY_NOT_FOUND;
	case SERCH_BUFFER_OVER: /* valueâ€šÃ‰â€œÃ¼â€šÃ¨Â�Ã˜â€šÃ§â€šÃˆâ€šÂ©â€šÃ�â€šÂ½ */
		/*
	 	 * â€šÂ±â€šÃŒÆ’GÆ’â€°Â�[â€šÃ�Å’Â»Â�Ã³Æ’TÆ’|Â�[Æ’gâ€šÂ³â€šÃªâ€šÃ„â€šÂ¢â€šÃˆâ€šÂ¢â€šÃŒâ€šÃ…,Â�Â«â€”Ë†â€šÃ â€šÂµÆ’TÆ’|Â�[Æ’gâ€šÂ³â€šÃªâ€šÃ„â€šÃ 
	 	 * Â�Â®Â�â€¡â€šÃ°â€šÃ†â€šÃ©â€šÂ½â€šÃŸâ€™ÃŠÂ�Ã­Æ’GÆ’â€°Â�[â€šÃ†â€šÂµâ€šÃ„â€šÂ¨â€šÂ­
		 * Â�Â¨â€šÂ¢â€šÃ‚â€šÃŒâ€šÃœâ€šÃ‰â€šÂ©Æ’TÆ’|Â�[Æ’gâ€šÂ³â€šÃªâ€šÃ„â€šÂ¢â€šÂ½â€šÃŒâ€šÃ…Â�Aâ€¢ÃŠÆ’GÆ’â€°Â�[â€šÃ†â€šÂµâ€šÂ½
		 * (2005/10/14 Å’Fâ€™J)
	 	 */
		return DI_PINI_TOOLONG_VALUE;
	case SERCH_ILLEGAL_PARAM: /* â€¢sÂ�Â³â€šÃˆÆ’pÆ’â€°Æ’Â�Â�[Æ’^ */
		return DI_PINI_ERROR;
	case SERCH_INIT_ERROR: /* Æ’tÆ’@Æ’CÆ’â€¹â€šÃŒÆ’IÂ�[Æ’vÆ’â€œâ€šÂ©mmapâ€šÃ‰Å½Â¸â€�s */
		return DI_PINI_ERROR;
	default:
		return DI_PINI_ERROR;

	}
	printf("Exiting get_appinfo_di_GPS()..\n");
}
int get_resocombo_GPS(di_devinfo_GPS_t *devinfo)
{
	printf("Entering get_resocombo_GPS()..\n");

	unsigned int	idx, i;
	di_resolutioninfo_t	*reso;
	char			strbuf[32];
	unsigned int		x, y, bit;
/*	#ifdef USE_IMAQ	*/
	int			search;
	int			paper = DEF_PAPER, prt_mode = DEF_PRT_MODE, dit_mode = DEF_DIT_MODE;
/*	#endif 	*/	/* USE_IMAQ */

	/* â€°Ã°â€˜Å“â€œxÂ�â€¢Â�[â€šÂ³Å½Ã­â€”ÃžÂ�â€�â€šÃ°Å½Ã¦â€œÂ¾ */
	idx = 1;
	while( idx ) {	/* â€�Ã”Â�â€ Â�â€¡â€šÃ‰Å’Å¸Â�Ãµ */
		sprintf( strbuf, "reso%d", idx );

		if( get_appinfo_di_GPS(strbuf, CATEGORY_DI ,sizeof(buf),buf) != SERCH_KEY_OK ) 
		{
			search = 0;
		} 
		else 
		{
			search = 1;
		}
		if( !search ) 
		{ /* Å’Å¸Â�ÃµÅ½Â¸â€�s */
			/* â€°Ã°â€˜Å“â€œxÂ�â€¢Â�[â€šÂ³Å½Ã­â€”ÃžÂ�â€�Å’Ë†â€™Ã¨ */
			if( idx > 1 ) 
			{ /* â€šPâ€šÃ‚â€šÃ�Æ’JÆ’eÆ’SÆ’Å â€šÂªâ€šÂ â€šÃ�â€šÂ½Â�ÃªÂ�â€¡ */
				devinfo->resonum = --idx;
			} 
			else 
			{
				/* Æ’fÆ’tÆ’HÆ’â€¹Æ’gÆ’pÆ’â€°Æ’Â�Â�[Æ’^ */
				devinfo->resonum = DEF_RESONUM;
			}
			break;
		}

		if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
		{
			/* Â�VÅ½dâ€”lâ€šÃ�Æ’pÆ’â€°Æ’Â�Â�[Æ’^â€šÂªâ€šUâ€šÃ‚ */
			if( sscanf(outbuf,"%d,%d,%d,%d,%d,%d" ,&x,&y,&bit,&paper,&prt_mode,&dit_mode) != 6 ) 
			{
				search = 0;
			} 
			else 
			{
				search = 1;
			}
		} 
		else 
		{
			/* â€¹Å’Å½dâ€”lâ€šÃ�Æ’pÆ’â€°Æ’Â�Â�[Æ’^â€šÂªâ€šRâ€šÃ‚ */
			if( sscanf(outbuf,"%d,%d,%d",&x,&y,&bit) != 3 ) 
			{
				search = 0;
			} 
			else 
			{
				search = 1;
			}
		}
		if( !search ) 
		{ /* Å’Å¸Â�ÃµÅ½Â¸â€�s */
			/* â€°Ã°â€˜Å“â€œxÂ�â€¢Â�[â€šÂ³Å½Ã­â€”ÃžÂ�â€�Å’Ë†â€™Ã¨ */
			if( idx > 1 ) 
			{ /* â€šPâ€šÃ‚â€šÃ�Æ’JÆ’eÆ’SÆ’Å â€šÂªâ€šÂ â€šÃ�â€šÂ½Â�ÃªÂ�â€¡ */
				devinfo->resonum = --idx;
			} 
			else 
			{
				/* Æ’fÆ’tÆ’HÆ’â€¹Æ’gÆ’pÆ’â€°Æ’Â�Â�[Æ’^ */
				devinfo->resonum = DEF_RESONUM;
			}
			break;
		}
/*	#endif 	*/	/* USE_IMAQ */
		if( idx == 1 ) { /* â€šÂ¨â€šÂ·â€šÂ·â€šÃŸâ€°Ã°â€˜Å“â€œxÂ�â€¢Â�[â€šÂ³ */
			def_resox = x;
			def_resoy = y;
			def_bit   = bit;
/*#ifdef USE_IMAQ	*/
			def_paper = paper;
			def_prt_mode = prt_mode;
			def_dit_mode = dit_mode;
/*	#endif 	*/	/* USE_IMAQ */
		}
		idx++;
	}
	/* Æ’Â�Æ’â€šÆ’Å Å mâ€¢Ã› */
	devinfo->reso_set = (di_resolutioninfo_t *)
		mmalloc(sizeof(di_resolutioninfo_t) * devinfo->resonum);
	if( !devinfo->reso_set ) {
		return DI_GET_NG;
	}

	/* Å½Ã€Â�Ã›â€šÃ‰Æ’pÆ’â€°Æ’Â�Â�[Æ’^Å½Ã¦â€œÂ¾ */
	reso = devinfo->reso_set;
	for( i=1; i<=idx; i++ ) {
		sprintf( strbuf, "reso%d", i );

		if( get_appinfo_di_GPS(strbuf
					,CATEGORY_DI
					,sizeof(buf),buf) != SERCH_KEY_OK ) {
			search = 0;
		} else {
			search = 1;
		}
		if( !search ) { /* Å’Å¸Â�ÃµÅ½Â¸â€�s */
			/* â€°Ã°â€˜Å“â€œxÂ�â€¢Â�[â€šÂ³Å½Ã­â€”ÃžÂ�â€�Å’Ë†â€™Ã¨ */
			if( idx > 1 ) { /* â€šPâ€šÃ‚â€šÃ�Æ’JÆ’eÆ’SÆ’Å â€šÂªâ€šÂ â€šÃ�â€šÂ½Â�ÃªÂ�â€¡ */
				devinfo->resonum = --idx;
			} else {
				/* Æ’fÆ’tÆ’HÆ’â€¹Æ’gÆ’pÆ’â€°Æ’Â�Â�[Æ’^ */
				devinfo->resonum = DEF_RESONUM;
			}
			break;
		}

		if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) {
			/* Â�VÅ½dâ€”lâ€šÃ�Æ’pÆ’â€°Æ’Â�Â�[Æ’^â€šÂªâ€šUâ€šÃ‚ */
			if( sscanf(outbuf,"%d,%d,%d,%d,%d,%d"
				   ,&x,&y,&bit,&paper,&prt_mode,&dit_mode) != 6 ) {
				search = 0;
			} else {
				search = 1;
			}
		} else {
			/* â€¹Å’Å½dâ€”lâ€šÃ�Æ’pÆ’â€°Æ’Â�Â�[Æ’^â€šÂªâ€šRâ€šÃ‚ */
			if( sscanf(outbuf,"%d,%d,%d",&x,&y,&bit) != 3 ) {
				search = 0;
			} else {
				search = 1;
			}
		}
		if( !search ) { /* Å’Å¸Â�ÃµÅ½Â¸â€�s */
			/* â€°Ã°â€˜Å“â€œxÂ�â€¢Â�[â€šÂ³Å½Ã­â€”ÃžÂ�â€�Å’Ë†â€™Ã¨ */
			if( idx > 1 ) { /* â€šPâ€šÃ‚â€šÃ�Æ’JÆ’eÆ’SÆ’Å â€šÂªâ€šÂ â€šÃ�â€šÂ½Â�ÃªÂ�â€¡ */
				devinfo->resonum = --idx;
			} else {
				/* Æ’fÆ’tÆ’HÆ’â€¹Æ’gÆ’pÆ’â€°Æ’Â�Â�[Æ’^ */
				devinfo->resonum = DEF_RESONUM;
			}
			break;
		}

		reso->x = x;
		reso->y = y;
		reso->bit = (unsigned char)bit;
/* #ifdef USE_IMAQ	*/
		reso->paper = paper;
		reso->prt_mode = prt_mode;
		reso->dit_mode = dit_mode;
/* #endif */	/* USE_IMAQ */
		reso++;
	}

	return DI_GET_OK;

	printf("Exiting get_resocombo_GPS()..\n");
}
int get_maxdit( int *max_dit ) /* Should it be static??*/
{
	printf("Entered  get_maxdit()..\n");
	if( (get_appinfo_di_GPS("max_dit" ,CATEGORY_DI ,sizeof(buf),buf) != SERCH_KEY_OK)
		|| (sscanf(outbuf, "%d", max_dit) != 1) ) {
		/* Æ’GÆ’â€°Â�[â€šÃŒÂ�ÃªÂ�â€¡â€šÃ�Æ’fÆ’tÆ’HÆ’â€¹Æ’gâ€™l */
		*max_dit = DEF_DIT;
	}

	/* Æ’fÆ’BÆ’Uâ€šÃŒÆ’TÆ’|Â�[Æ’gâ€”Lâ€“Â³ */
	support_dithergamma = (*max_dit) ? 1 : 0;

	printf("Exiting get_maxdit()..\n");
	return DI_GET_OK;	
}
int get_maxplane( int *max_plane )
{

	printf("Entered  get_maxplane()..\n");
	if( (get_appinfo_di_GPS("max_plane" ,CATEGORY_DI ,sizeof(buf),buf) != SERCH_KEY_OK)
		|| (sscanf(outbuf, "%d", max_plane) != 1) ) {
		/* Æ’GÆ’â€°Â�[â€šÃŒÂ�ÃªÂ�â€¡â€šÃ�Æ’fÆ’tÆ’HÆ’â€¹Æ’gâ€™l */
		*max_plane = DEF_PLANE;
	}
		
	printf("Exiting get_maxplane()..\n");
	return DI_GET_OK;
}
int get_render_info_GPS_di_ (di_devinfo_GPS_t *devinfo)
{
	printf("Entering get_render_info_di_()..\n");

	if( get_resocombo_GPS( devinfo ) != DI_GET_OK )
		return DI_GET_NG;	
	if( get_maxdit( &devinfo->ndit ) != DI_GET_OK )
		return DI_GET_NG;

	/* Æ’TÆ’|Â�[Æ’gÂ�Ã…â€˜Ã¥Æ’vÆ’Å’Â�[Æ’â€œÂ�â€� */
	if( get_maxplane( &devinfo->nplane ) != DI_GET_OK )
		return DI_GET_NG;
	printf("Exiting get_render_info_di_()..\n");
	return DI_GET_OK;
}
/* adjust_dgparam_GPS( &dgparam );	*/
void adjust_dgparam_GPS( dg_param_t *para ) /* This API is static in GPS, and in here?? */
{
	printf("Enrtering adjust_dgparam_GPS()..\n");
	
	int	no = 1;
	int	org_resox, org_resoy, org_bit, org_dit;
	int	new_resox, new_resoy, new_bit, new_dit;
	char	strbuf[16];

	while( 1 ) {
		sprintf( strbuf, "trans_dg%d", no );
		if( (get_appinfo_di_GPS(strbuf
#ifdef USE_SET_CATEGORY
					,category_di
#else /* USE_SET_CATEGORY */
					,CATEGORY_DI
#endif /* USE_SET_CATEGORY */
					,sizeof(buf),buf) != SERCH_KEY_OK)
			|| (sscanf(outbuf, "%d,%d,%d,%d,%d,%d,%d,%d", &org_resox,&org_resoy,&org_bit,&org_dit, &new_resox,&new_resoy,&new_bit,&new_dit) != 8) ) 
		{
			break;
		}
		if( (para->resox == org_resox) && (para->resoy == org_resoy) &&
			(para->bit == org_bit) && (para->dit == org_dit) ) 
		{
			/* â€¢Ã�Å Â·â€šÂ·â€šÃ©â€°Ã°â€˜Å“â€œxÂ�â€¢Â�[â€šÂ³Â�â€¢Æ’fÆ’BÆ’Uâ€šÂªÅ’Â©â€šÃ‚â€šÂ©â€šÃ�â€šÂ½â€šÃŒâ€šÃ…,â€¢Ã�Å Â·â€šÂ·â€šÃ© */
			if (fflag == 0)
			{
				printf(("trans=%dx%dx%d-%d->%dx%dx%d-%d,",
					para->resox, para->resoy, para->bit, para->dit,
					new_resox, new_resoy, new_bit, new_dit));
				fflag = 1;
			}
			para->resox = new_resox;
			para->resoy = new_resoy;
			para->bit   = new_bit;
			para->dit   = new_dit;
			break;
		}
		no++;
	}/* End of While loop.	*/
	
	printf("Exiting adjust_dgparam_GPS()..\n");
}
int get_1dit_di_GPS( di_devinfo_GPS_t *devinfo, int bit, int dpix, int dpiy, int mode, int c, unsigned char paper, unsigned char prt_mode, di_ditinfo_t *ditinfo )
{
	printf("Entered get_1dit_di_GPS()..\n");

	long	off;
	int		id;
	int		adr;
	gps_clr_shdm_t	*shdm;
	gps_clr_data_t	*dt;
	gps_clr_plane_t	*pln;
	gps_clr_dit_t	*dit;

	gps_nclr_shdm_t 	*nshdm;
	gps_nclr_data_t		*ndt;
	gps_nclr_plane_t	*npln;
	gps_nclr_dit_t		*ndit;
	long rID_size;
		
	GPS_Color_getShrd();
	off = loffset; /* Got from GPS Wrapper function of Shrd() call..*/
	if( off < 0 ) {
		return -1;
	}
	
	devinfo->shdm_addr = gps_shdm_addr;	
	shdm = (gps_clr_shdm_t*)(devinfo->shdm_addr + off);

	id = GPS_Color_getID2(dpix, dpiy, bit, mode, prt_mode, paper);

	if( id < 0 ) 
	{
		printf("returning -1 at line # 373..\n");
		return -1;
	}
	
	/* get data */
	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{
		nshdm = (gps_nclr_shdm_t *)shdm;
		ndt = &(nshdm->data);
		ndt = &(ndt[id]);
		adr = (int)nshdm;

		npln = &((*ndt).color[c]);
		ndit = (gps_nclr_dit_t *)(adr + npln->dit);

		ditinfo->dit_ptr = (unsigned char *)(adr + (unsigned char *)ndit->dit);
		/* Å’^â€”Å½â€šÂ¿â€™Â�Ë†Ã“ */
		ditinfo->x_size = (unsigned char)ndit->xsz;
		ditinfo->y_size = (unsigned char)ndit->ysz;

#ifdef USE_FUSER_CTL
		ditinfo->e_flag_max = ndit->e_flag_max;
		ditinfo->e_flag_mid = ndit->e_flag_mid;
#else
		ditinfo->e_flag_max = ditinfo->e_flag_mid = 0;
#endif
	} 
	else 
	{
	dt = &(shdm->data);
	dt = &(dt[id]);
	adr = (int)shdm;

	pln = &((*dt).color[c]);
	dit = (gps_clr_dit_t *)(adr + pln->dit);

	ditinfo->dit_ptr = (unsigned char *)(adr + (unsigned char *)dit->dit);
	/* Å’^â€”Å½â€šÂ¿â€™Â�Ë†Ã“ */
	ditinfo->x_size = (unsigned char)dit->xsz;
	ditinfo->y_size = (unsigned char)dit->ysz;

	ditinfo->e_flag_max = ditinfo->e_flag_mid = 0;
	}


	if (gpsColor_getRID(gps_client, id, rID, &rID_size) >= 0)
		ditinfo->rearrange = rID[c];
	

	printf("rID[c] = [%d]\n", rID[c]);
	printf("ditinfo->rearrange = [%d]\n",ditinfo->rearrange);
	printf("Exiting get_1dit_di_GPS() ..\n");
	return 0;

}
/*	get_dinfo() definition..	*/
int get_dinfo_GPS(di_devinfo_GPS_t *devinfo, int reso, int dit, int color, di_ditinfo_t *ditinfo) /* It is Static in GPS code, here? */
{
	printf("Entering get_dinfo_GPS() ..\n");
	int	i;
	dg_param_t	dgparam;

	/* Æ’fÆ’BÆ’UÂ�EÆ’Ã�Æ’â€šÂ�[Æ’hâ€”pÆ’pÆ’â€°Æ’Â�Â�[Æ’^â€šÃŒÆ’ZÆ’bÆ’g */
	dgparam.resox = devinfo->reso_set[reso].x;
	dgparam.resoy = devinfo->reso_set[reso].y;
	dgparam.bit   = devinfo->reso_set[reso].bit;
	dgparam.color = color;

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{ /* Å gâ€™Â£Å½dâ€”l */
		dgparam.dit      = devinfo->reso_set[reso].dit_mode;
		dgparam.paper    = devinfo->reso_set[reso].paper;
		dgparam.prt_mode = devinfo->reso_set[reso].prt_mode;
	} else 
	{ /* â€¹Å’Å½dâ€”l */
		/* â€šÂ â€šÃ§â€šÂ©â€šÂ¶â€šÃŸâ€šÂ±â€šÂ±â€šÃ…GPSâ€šÃŒÅ½dâ€”lâ€šÃ‰â€¢Ã�Â�Xâ€šÂµâ€šÃ„â€šÂ¨â€šÂ­ */
		dgparam.dit   = gps_dgmd[dit];
	}

	/* â€šÂ±â€šÂ±â€šÃ… ditinfo â€šÃŒâ€˜SÆ’Â�Æ’â€œÆ’oâ€šÃ°â€“â€žâ€šÃŸâ€šÃ© */

	/* Å eâ€¹@Å½Ã­â€“Ë†â€šÃŒÆ’pÆ’â€°Æ’Â�Â�[Æ’^â€¢Ã¢Â�Â³ */
	adjust_dgparam_GPS( &dgparam );

/*#ifdef SUPPORT_DITHERGAMMA_PRODUCT*/
	if( support_dithergamma ) 
	{

	/* dither Get! */

	if (get_1dit_di_GPS( devinfo, dgparam.bit, dgparam.resox, dgparam.resoy,
			  dgparam.dit, dgparam.color, dgparam.paper,
			  dgparam.prt_mode, ditinfo ) < 0)
	{
		printf("returning ERROR at line # 461..\n");
		return DI_GET_NG;
	}

/*#else*/	/* !SUPPORT_DITHERGAMMA_PRODUCT */
	} 
	else 
	{

#ifdef UNIX
	ditinfo->dit_ptr = (unsigned char *)0 ;
	ditinfo->x_size = ditinfo->y_size = 0 ;
#endif /* UNIX */
#ifdef GPS
	/* NOT YET */
	ditinfo->dit_ptr = (unsigned char *)0 ;
	ditinfo->x_size = ditinfo->y_size = 0 ;
#endif /* GPS */

/*#endif*/	/* !SUPPORT_DITHERGAMMA_PRODUCT */
	}

	printf("Exiting get_dinfo_GPS() ..\n");
	return DI_GET_OK ;
}

/*get_dither_info_di_GPS() Starts*/
int get_dither_info_di_GPS(di_devinfo_GPS_t *devinfo)
{
	printf("Entered get_dither_info_di_GPS()..\n");

	int		reso, dit, c;

	di_ditinfo_t	*ditinfo;
/*	di_ditinfo_t	*ditinfo_mono;	*/

	unsigned int 	modenum;

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) {
		modenum = devinfo->resonum * devinfo->nplane;
	} else {
		modenum = devinfo->resonum * devinfo->ndit * devinfo->nplane;
	}
	
	devinfo->dither_info =
		(di_ditinfo_t *)mmalloc(sizeof(di_ditinfo_t) * modenum);

	if (devinfo->dither_info == 0)
	{
		printf("returning ERROR at line #507..\n");
		return DI_GET_NG;
	}

	ditinfo = devinfo->dither_info;

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{ 
	for (reso = 0; reso < devinfo->resonum; reso++)
		for (c = 0; c < devinfo->nplane; c++)
			if (get_dinfo_GPS(devinfo, reso, 0, c, ditinfo++) != DI_GET_OK)
			{
				printf("returning ERROR at line # 519..\n");
				return DI_GET_NG;
			}
	} 
	
	printf("Exiting get_dither_info_di_GPS()..\n");
	return DI_GET_OK;
}
/*get_dither_info_di_GPS() Ends*/

/*	get_1gam_di_GPS()*/
int get_1gam_di_GPS( di_devinfo_GPS_t *devinfo, int bit, int dpix, int dpiy, int mode, int c, unsigned char paper, unsigned char prt_mode, unsigned char **ptr )
{
	printf("Entered get_1gam_di_GPS() .\n");

	long		off;
	int		id;
	int		adr;
	int		retval;
	gps_clr_shdm_t	*shdm;
	gps_clr_data_t	*dt;
	gps_clr_plane_t	*pln;
	gps_clr_gam_t	*gam;

	gps_nclr_shdm_t 	*nshdm;
	gps_nclr_data_t		*ndt;
	gps_nclr_plane_t	*npln;
	gps_nclr_gam_t		*ngam;

	long	headrank;
	long	hr_id[] = {DI_ENV_VAR_ID_HEADRANKK,
			   DI_ENV_VAR_ID_HEADRANKC,
			   DI_ENV_VAR_ID_HEADRANKM,
			   DI_ENV_VAR_ID_HEADRANKY,};

	GPS_Color_getShrd();
	off = loffset;
	
	if( off < 0 ) 
	{
		return -1;
	}

	devinfo->shdm_addr = gps_shdm_addr;		
	shdm = (gps_clr_shdm_t*)(devinfo->shdm_addr + off);

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{
		id = GPS_Color_getID2(dpix, dpiy, bit, mode, prt_mode, paper);
	}

	if( id < 0 ) 
	{
		return -1;
	}
	

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{
		nshdm = (gps_nclr_shdm_t *)shdm;
		ndt = &(nshdm->data);
		ndt = &(ndt[id]);
		adr = (int)nshdm;

		npln = &((*ndt).color[c]);
		ngam = (gps_nclr_gam_t *)(adr + npln->gam);


	        retval = GPS_PenvOpen(gps_client, DI_PENV_NAME_COMMON, sizeof(DI_PENV_NAME_COMMON));
        	printf("GPS_PenvOpen() returns [%d]\n",retval);

	        if( GPS_PenvGetDefValue(gps_client, retval, hr_id[c], &headrank) == 0)
	        {
			if (retval = GPS_PenvGetValue(gps_client, retval, hr_id[c], &headrank) < 0)
			{
		                printf("headrank = [%d]\n", headrank);
				headrank = 0;
			}
		}
		else
		{
			printf("GPS_PenvGetDefValue() is failed for hr_id[c] = hr_id[%d]", c);
		}

	        GPS_PenvClose(gps_client, retval);


		/* Å’Â»Â�Ã³â€°Â�ËœHÆ’Ã�Å’Ã…â€™Ã¨ */
		if (ngam->gam[headrank]) 
		{
			*ptr = (unsigned char *)(adr + (unsigned char *)ngam->gam[headrank]);
		} 
		else 
		{
			*ptr = 0;
		}

	} 
	else 
	{

	/* get data */
	dt = &(shdm->data);
	dt = &(dt[id]);
	adr = (int)shdm;

	pln = &((*dt).color[c]);
	gam = (gps_clr_gam_t *)(adr + pln->gam);

	*ptr = (unsigned char *)(adr + (unsigned char *)gam->gam);
	/*
	 * Æ’Ã�â€™Â²Â�Â®Å’Ã£â€šÃŒÂ�Ã„Å½Ã¦â€œÂ¾â€šÃ‰â€šÃ‚â€šÂ¢â€šÃ„â€šÃ�â€”vÅ’Å¸â€œÂ¢â€šÂ¾â€šÂªÂ�AÅ’Â»Â�Ã³â€šÃ…â€šÃ� GPS â€˜Â¤â€šÃ…
	 * gpscolor_getShrd() Å½Å¾â€šÃ‰Â�Ã„Å’vÅ½Zâ€šÂµâ€šÃ„â€šÂ­â€šÃªâ€šÃ©â€šÃŒâ€šÃ… CDC â€šÃ…â€šÃ�
	 * Å Ã–â€™mâ€šÂµâ€šÃˆâ€šÂ¢(00/06/13)
	 */
	}

	printf("Exiting get_1gam_di_GPS() .\n");
	return 0;

}


/*get_ginfo_GPS() Implementation..*/
int get_ginfo_GPS( di_devinfo_GPS_t *devinfo,  int reso, int dit, int color, unsigned char **ptr) /*Should it be static */
{
	printf("Entering get_ginfo_GPS() .\n");
	dg_param_t	dgparam;

	/* Æ’fÆ’BÆ’UÂ�EÆ’Ã�Æ’â€šÂ�[Æ’hâ€”pÆ’pÆ’â€°Æ’Â�Â�[Æ’^â€šÃŒÆ’ZÆ’bÆ’g */
	dgparam.resox = devinfo->reso_set[reso].x;
	dgparam.resoy = devinfo->reso_set[reso].y;
	dgparam.bit   = devinfo->reso_set[reso].bit;
	dgparam.color = color;

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) { /* Å gâ€™Â£Å½dâ€”l */
		dgparam.dit      = devinfo->reso_set[reso].dit_mode;
		dgparam.paper    = devinfo->reso_set[reso].paper;
		dgparam.prt_mode = devinfo->reso_set[reso].prt_mode;
	} else { /* â€¹Å’Å½dâ€”l */
		/* â€šÂ â€šÃ§â€šÂ©â€šÂ¶â€šÃŸâ€šÂ±â€šÂ±â€šÃ…GPSâ€šÃŒÅ½dâ€”lâ€šÃ‰â€¢Ã�Â�Xâ€šÂµâ€šÃ„â€šÂ¨â€šÂ­ */
		dgparam.dit   = gps_dgmd[dit];
	}

	/* Å eâ€¹@Å½Ã­â€“Ë†â€šÃŒÆ’pÆ’â€°Æ’Â�Â�[Æ’^â€¢Ã¢Â�Â³ */
	adjust_dgparam_GPS( &dgparam );

/*#ifdef SUPPORT_DITHERGAMMA_PRODUCT*/
	if( support_dithergamma ) {

	/* Æ’Ã� Get! */
	if (get_1gam_di_GPS( devinfo, dgparam.bit, dgparam.resox, dgparam.resoy,
			  dgparam.dit, dgparam.color, dgparam.paper,
			  dgparam.prt_mode, ptr ) < 0)

		return DI_GET_NG;

/*#else*/	/* !SUPPORT_DITHERGAMMA_PRODUCT */
	} 
	else 
	{

	*ptr = 0 ;

/*#endif*/	/* !SUPPORT_DITHERGAMMA_PRODUCT */
	}

	printf("Exiting get_ginfo_GPS() .\n");
	return DI_GET_OK;
}



/* get_gamma_info_di_GPS() implementation.*/
int get_gamma_info_di_GPS(di_devinfo_GPS_t *devinfo)
{
	printf("Entered get_ginfo_GPS() .\n");
	int		reso, dit, c;
	unsigned char	**gam_ptr;

	unsigned int 	modenum;

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{
		/* Å gâ€™Â£Å½dâ€”lâ€šÃ…â€šÃ�,resonumâ€“Ë†â€šÃ‰Æ’KÆ’â€œÂªâ€šPâ€šÃ‚Å’Ë†â€™Ã¨â€šÂµâ€šÃ„â€šÂ¢â€šÃ© */
		modenum = devinfo->resonum * devinfo->nplane;
	} 
	else 
	{
		/* â€¹Å’Å½dâ€”lâ€šÃ…â€šÃ�,resonumâ€“Ë†â€šÃ‰Æ’KÆ’â€œÆ’â€šÂªâ€¢Â¡Â�â€�â€šÂ â€šÃ© */
		modenum = devinfo->resonum * devinfo->ndit * devinfo->nplane;
	}

	devinfo->gamma_info = (unsigned char **)mmalloc(sizeof(unsigned char *) * modenum);

	if (devinfo->gamma_info == 0)
		return DI_GET_NG;

	gam_ptr = devinfo->gamma_info;

	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{ /* Å gâ€™Â£Å½dâ€”l */
	for (reso = 0; reso < devinfo->resonum; reso++)
		for (c = 0; c < devinfo->nplane; c++)
			/* â€šPÅ½Ã­â€”Ãžâ€šÃŒÆ’KÆ’â€œÆ’Å½Ã¦â€œÂ¾ */

			if (get_ginfo_GPS(devinfo, reso, 0, c, gam_ptr++)	!= DI_GET_OK)
				return DI_GET_NG;
	} 
	else 
	{ /* â€¹Å’Å½dâ€”l */
	for (reso = 0; reso < devinfo->resonum; reso++)
			for (dit = 0; dit < devinfo->ndit; dit++)
				for (c = 0; c < devinfo->nplane; c++)
					/* â€šPÅ½Ã­â€”Ãžâ€šÃŒÆ’KÆ’â€œÆ’Å½Ã¦â€œÂ¾ */

					if (get_ginfo_GPS(devinfo, reso, dit, c, gam_ptr++)	!= DI_GET_OK)
						return DI_GET_NG;
	}

	printf("Exiting get_ginfo_GPS() .\n");
	return DI_GET_OK ;
}

/*	get_1gcr_table_di_GPS() impl.	*/
int get_1gcr_table_di_GPS(di_devinfo_GPS_t *devinfo, int dpix, int dpiy, int bit,int dit, unsigned char paper, unsigned char prt_mode, di_gcrinfo_t *gcr, di_gcrinfo_t *gcrhgr)
{
	printf("Entered get_1gcr_table_di_GPS().\n");
	
			long			off;
		int			id;
		int			adr;
		gps_nclr_shdm_t 	*nshdm;
		gps_nclr_data_t		*ndt;
	
		gcr->flag = gcrhgr->flag = FALSE;
	
		GPS_Color_getShrd();
		off = loffset;
	
		if (off < 0) {
			return -1;
		}
		
		if (!(devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM)) {
			return -1;
		}
		devinfo->shdm_addr = gps_shdm_addr;
		nshdm = (gps_nclr_shdm_t*)(devinfo->shdm_addr + off);
	
		id = GPS_Color_getID2(dpix, dpiy, bit, dit , prt_mode, paper);
		
		if (id < 0) {
			return -1;
		}
	
		/* get data */
		ndt = &(nshdm->data);
		ndt = &(ndt[id]);
		adr = (int)nshdm;

/*Needs review here..		*/
		if (ndt->wishgcr.size == 0) {
			return -1;
		}
	
		if (ndt->wishgcr.CB_bg_wish == 0 || ndt->wishgcr.CB_ucr_wish == 0 ||
			ndt->wishgcr.CG_bg_wish == 0 || ndt->wishgcr.CG_ucr_wish == 0 ||
			ndt->wishgcr.YG_bg_wish == 0 || ndt->wishgcr.YG_ucr_wish == 0 ||
			ndt->wishgcr.MB_bg_wish == 0 || ndt->wishgcr.MB_ucr_wish == 0 ||
			ndt->wishgcr.MR_bg_wish == 0 || ndt->wishgcr.MR_ucr_wish == 0 ||
			ndt->wishgcr.YR_bg_wish == 0 || ndt->wishgcr.YR_ucr_wish == 0) {
			return -1;
		}
			
		/* set data */
		gcr->CB_bg  = (short *)(adr + ndt->wishgcr.CB_bg_wish);
		gcr->CB_ucr = (short *)(adr + ndt->wishgcr.CB_ucr_wish);
		gcr->CG_bg  = (short *)(adr + ndt->wishgcr.CG_bg_wish);
		gcr->CG_ucr = (short *)(adr + ndt->wishgcr.CG_ucr_wish);
		gcr->YG_bg  = (short *)(adr + ndt->wishgcr.YG_bg_wish);
		gcr->YG_ucr = (short *)(adr + ndt->wishgcr.YG_ucr_wish);
		gcr->MB_bg  = (short *)(adr + ndt->wishgcr.MB_bg_wish);
		gcr->MB_ucr = (short *)(adr + ndt->wishgcr.MB_ucr_wish);
		gcr->MR_bg  = (short *)(adr + ndt->wishgcr.MR_bg_wish);
		gcr->MR_ucr = (short *)(adr + ndt->wishgcr.MR_ucr_wish);
		gcr->YR_bg  = (short *)(adr + ndt->wishgcr.YR_bg_wish);
		gcr->YR_ucr = (short *)(adr + ndt->wishgcr.YR_ucr_wish);
	
		gcr->flag = TRUE;
	
#if 0		
			if (ndt->wishgcr_hgr.size == 0) {
				return 0;
			}
			if (ndt->wishgcr_hgr.CB_bg_wish == 0 || ndt->wishgcr_hgr.CB_ucr_wish == 0 ||
				ndt->wishgcr_hgr.CG_bg_wish == 0 || ndt->wishgcr_hgr.CG_ucr_wish == 0 ||
				ndt->wishgcr_hgr.YG_bg_wish == 0 || ndt->wishgcr_hgr.YG_ucr_wish == 0 ||
				ndt->wishgcr_hgr.MB_bg_wish == 0 || ndt->wishgcr_hgr.MB_ucr_wish == 0 ||
				ndt->wishgcr_hgr.MR_bg_wish == 0 || ndt->wishgcr_hgr.MR_ucr_wish == 0 ||
				ndt->wishgcr_hgr.YR_bg_wish == 0 || ndt->wishgcr_hgr.YR_ucr_wish == 0) {
				return 0;
			}
			/* set data */
			gcrhgr->CB_bg  = (short *)(adr + ndt->wishgcr_hgr.CB_bg_wish);
			gcrhgr->CB_ucr = (short *)(adr + ndt->wishgcr_hgr.CB_ucr_wish);
			gcrhgr->CG_bg  = (short *)(adr + ndt->wishgcr_hgr.CG_bg_wish);
			gcrhgr->CG_ucr = (short *)(adr + ndt->wishgcr_hgr.CG_ucr_wish);
			gcrhgr->YG_bg  = (short *)(adr + ndt->wishgcr_hgr.YG_bg_wish);
			gcrhgr->YG_ucr = (short *)(adr + ndt->wishgcr_hgr.YG_ucr_wish);
			gcrhgr->MB_bg  = (short *)(adr + ndt->wishgcr_hgr.MB_bg_wish);
			gcrhgr->MB_ucr = (short *)(adr + ndt->wishgcr_hgr.MB_ucr_wish);
			gcrhgr->MR_bg  = (short *)(adr + ndt->wishgcr_hgr.MR_bg_wish);
			gcrhgr->MR_ucr = (short *)(adr + ndt->wishgcr_hgr.MR_ucr_wish);
			gcrhgr->YR_bg  = (short *)(adr + ndt->wishgcr_hgr.YR_bg_wish);
			gcrhgr->YR_ucr = (short *)(adr + ndt->wishgcr_hgr.YR_ucr_wish);
#endif		
			gcrhgr->flag = TRUE;

	printf("Exiting  get_1gcr_table_di_GPS().\n");
	return 0;

}


/*	get_gcr_di_GPS() implementation.*/	
int get_gcr_di_GPS(di_devinfo_GPS_t *devinfo)
{
	printf("Entered get_gcr_di_GPS().\n");

	int reso;
	di_gcrinfo_t *gcr_ptr;
	di_gcrinfo_t *gcrhgr_ptr;
	dg_param_t dgparam;

	if ((devinfo->gcr_info = (di_gcrinfo_t *)mmalloc(sizeof(di_gcrinfo_t) * devinfo->resonum)) == 0)
			return DI_GET_NG;

	gcr_ptr = devinfo->gcr_info;

	if ((devinfo->gcrhgr_info = (di_gcrinfo_t *)mmalloc(sizeof(di_gcrinfo_t) * devinfo->resonum)) == 0)
			return DI_GET_NG;

	gcrhgr_ptr = devinfo->gcrhgr_info;

	if (devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM) 
	{
		for (reso = 0; reso < devinfo->resonum; reso++) 
		{
			dgparam.resox		= devinfo->reso_set[reso].x;
			dgparam.resoy		= devinfo->reso_set[reso].y;
			dgparam.bit			= devinfo->reso_set[reso].bit;
			dgparam.dit			= devinfo->reso_set[reso].dit_mode;
			dgparam.paper		= devinfo->reso_set[reso].paper;
			dgparam.prt_mode	= devinfo->reso_set[reso].prt_mode;
			adjust_dgparam_GPS( &dgparam );
			get_1gcr_table_di_GPS(devinfo, dgparam.resox, dgparam.resoy, dgparam.bit, dgparam.dit, dgparam.paper, dgparam.prt_mode, gcr_ptr, gcrhgr_ptr);
			gcrhgr_ptr++;
			gcr_ptr++;
		}
	} 
	else 
	{
		for (reso = 0; reso < devinfo->resonum; reso++)
			(gcrhgr_ptr++)->flag =
			(gcr_ptr++)->flag = FALSE;
	}

	printf("Exiting get_gcr_di_GPS().\n");
	return DI_GET_OK;

}

/*	get_1bgucr_table_di_GPS()	*/
int get_1bgucr_table_di_GPS(di_devinfo_GPS_t *devinfo , int dpix, int dpiy, int bit, int dit, unsigned char paper, unsigned char prt_mode, di_bgucrinfo_t *bgucr )
{
        printf("Entering get_1bgucr_table_di_GPS()..\n");


	long		off;
	int			id;
	int			adr;
	gps_nclr_shdm_t 	*nshdm;
	gps_nclr_data_t		*ndt;

	GPS_Color_getShrd();
	off = loffset; /*Got from GPS Wrapper function of Shrd() call..	*/
	
	if( off < 0 ) {
		return -1;
	}
	
	if( !(devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM) ) {
		return -1;
	}

	devinfo->shdm_addr = gps_shdm_addr;
	nshdm = (gps_nclr_shdm_t*)(devinfo->shdm_addr + off);

	id = GPS_Color_getID2(dpix, dpiy, bit, dit, prt_mode, paper);

	if( id < 0 ) {
		return -1;
	}

	/* get data */
	ndt = &(nshdm->data);
	ndt = &(ndt[id]);
	adr = (int)nshdm;

	/* set data */
	bgucr->bg  = (unsigned char *)(adr + ndt->bgucr.bg);
	bgucr->ucr = (unsigned char *)(adr + ndt->bgucr.ucr);

#ifdef USE_GCRHGR
	if ((ndt->bgucr_hgr.bg != 0) &&
			(ndt->bgucr_hgr.ucr != 0)) {
		bgucr->bg_hgr =
			(unsigned char *)(adr + ndt->bgucr_hgr.bg);
		bgucr->ucr_hgr =
			(unsigned char *)(adr + ndt->bgucr_hgr.ucr);
	} else {
		bgucr->bg_hgr = (unsigned char *)0;
		bgucr->ucr_hgr = (unsigned char *)0;
	}
#else	/* USE_GCRHGR */
	bgucr->bg_hgr = (unsigned char *)0;
	bgucr->ucr_hgr = (unsigned char *)0;
#endif	/* USE_GCRHGR */


#ifdef USE_COMPOSITEBLACK
	if ((ndt->bgucr.bg_compositebk != 0) &&
			(ndt->bgucr.ucr_compositebk != 0)) {
		bgucr->bg_compbk =
			(unsigned char *)(adr + ndt->bgucr.bg_compositebk);
		bgucr->ucr_compbk =
			(unsigned char *)(adr + ndt->bgucr.ucr_compositebk);
	} else {
		bgucr->bg_compbk = (unsigned char *)0;
		bgucr->ucr_compbk = (unsigned char *)0;
	}
#else
	bgucr->bg_compbk = (unsigned char *)0;
	bgucr->ucr_compbk = (unsigned char *)0;
#endif

        printf("Exiting get_1bgucr_table_di_GPS()..\n");
	return 0;

}

int get_bgucr_param_di_GPS(di_devinfo_GPS_t *devinfo)
{

        printf("Entering get_bgucr_param_di_GPS()..\n");	
	
	
	/* BG/UCRÆ’pÆ’â€°Æ’Â�Â�[Æ’^ */
	int reso;
	di_bgucrinfo_t *bgucr_ptr;
	dg_param_t dgparam;
	
	if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) 
	{ /* Å gâ€™Â£Å½dâ€”l */
		devinfo->bgucr_info = (di_bgucrinfo_t **)mmalloc( sizeof(di_bgucrinfo_t) * devinfo->resonum);

		if (devinfo->bgucr_info == 0)
			return DI_GET_NG;

		bgucr_ptr = (di_bgucrinfo_t *)devinfo->bgucr_info;

		for (reso = 0; reso < devinfo->resonum; reso++) {
			dgparam.resox		= devinfo->reso_set[reso].x;
			dgparam.resoy		= devinfo->reso_set[reso].y;
			dgparam.bit		= devinfo->reso_set[reso].bit;
			dgparam.dit		= devinfo->reso_set[reso].dit_mode;
			dgparam.paper		= devinfo->reso_set[reso].paper;
			dgparam.prt_mode	= devinfo->reso_set[reso].prt_mode;

			adjust_dgparam_GPS( &dgparam );

			if (get_1bgucr_table_di_GPS(devinfo,
				dgparam.resox, dgparam.resoy, dgparam.bit,
				dgparam.dit, dgparam.paper, dgparam.prt_mode,
				bgucr_ptr++ ) < 0) {
				return DI_GET_NG;
			}
		}
	} 
	else 
	{
		if( (get_appinfo_di_GPS("bgucr" ,category_di, sizeof(buf), buf) != SERCH_KEY_OK)
			|| (sscanf(outbuf, "%f,%f,%f,%f", &devinfo->bg_startp, &devinfo->bg_slant, 
					&devinfo->ucr_startp, &devinfo->ucr_slant) != 4) ) 
		{
			/* Æ’LÂ�[â€šÂªÅ’Â©â€šÃ‚â€šÂ©â€šÃ§â€šÃˆâ€šÂ¢Â�ÃªÂ�â€¡â€šÃ�Æ’fÆ’tÆ’HÆ’â€¹Æ’gÆ’pÆ’â€°Æ’Â�Â�[Æ’^â€šÃ°â€¢Ã”â€šÂ· */
			devinfo->bg_startp  = DEF_BG_SP;
			devinfo->bg_slant   = DEF_BG_SLANT;
			devinfo->ucr_startp = DEF_UCR_SP;
			devinfo->ucr_slant  = DEF_UCR_SLANT;
		}
	}

        printf("Exiting get_bgucr_param_di_GPS()..\n");
	return DI_GET_OK;

}

int get_1tlimit_di_GPS(di_devinfo_GPS_t *devinfo, int dpix, int dpiy, int bit,
			int dit, unsigned char paper, unsigned char prt_mode,
			di_tlimitinfo_t *tlimit )
{
	unsigned long		*ptr;
	long			off;
	int			id;
	int			adr;
	gps_nclr_shdm_t 	*nshdm;
	gps_nclr_data_t		*ndt;


	/* gps_color_socket.c ‚É‚ ‚é‚Ì‚Å,‚ ‚Æ‰ñ‚µ */
	GPS_Color_getShrd();
	off = loffset; /*Got from GPS Wrapper function of Shrd() call..	*/

	if( off < 0 ) {
		return -1;
	}
	/*; assert(off >= 0) ;*/

	if( !(devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM) ) {
		return -1;
	}

	nshdm = (gps_nclr_shdm_t*)(devinfo->shdm_addr + off);

	id = GPS_Color_getID2(dpix, dpiy, bit, dit, prt_mode, paper);

	if( id < 0 ) {
		return -1;
	}

	/* get data */
	ndt = &(nshdm->data);
	ndt = &(ndt[id]);
	adr = (int)nshdm;

	/* set data */

	/* ‘�—Ê‹K�§’l */
	ptr = (unsigned long *)(adr + ndt->limit.limit);
	/* ŽÊ�^, •¶Žš, “h‚è, �ü‰æ‚Ì�‡ */
	tlimit->phot  = *ptr++;
	tlimit->text  = *ptr++;
	tlimit->fill  = *ptr++;
	tlimit->line  = *ptr;

	return 0;
}

int get_tlimit_di_GPS(di_devinfo_GPS_t *devinfo)
{
	unsigned int	i;
	dg_param_t dgparam;

	if( devinfo->toner_limit == TRUE ) {	/* ƒgƒi�[�§ŒÀ‚ ‚è */
		int		idx;
		char	strbuf[32];
		char	text,phot,grap,thin;
		int		resox,resoy,bit;

		/* ‘�—Ê‹K�§’lƒpƒ^�[ƒ“�”Žæ“¾ */
		if( devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM ) { /* Šg’£Žd—l */
			int reso;
			di_tlimitinfo_t *tlimit_ptr;

			/* ‘�—Ê‹K�§’l‚Íƒ‚�[ƒh•ª‚ ‚é */
			devinfo->tlimit_num = devinfo->resonum;

			devinfo->tlimit_val = (di_tlimitinfo_t **)mmalloc( sizeof(di_tlimitinfo_t) * devinfo->resonum);

			if (devinfo->tlimit_val == 0)
				return DI_GET_NG;

			tlimit_ptr = (di_tlimitinfo_t *)devinfo->tlimit_val;

			for (reso = 0; reso < devinfo->resonum; reso++) {
				dgparam.resox		= devinfo->reso_set[reso].x;
				dgparam.resoy		= devinfo->reso_set[reso].y;
				dgparam.bit			= devinfo->reso_set[reso].bit;
				dgparam.dit			= devinfo->reso_set[reso].dit_mode;
				dgparam.paper		= devinfo->reso_set[reso].paper;
				dgparam.prt_mode	= devinfo->reso_set[reso].prt_mode;
				adjust_dgparam_GPS( &dgparam );
				if (get_1tlimit_di_GPS(devinfo,
					dgparam.resox, dgparam.resoy, dgparam.bit,
					dgparam.dit, dgparam.paper, dgparam.prt_mode,
					tlimit_ptr++ ) < 0) {
					return DI_GET_NG;
				}
			}

		}
	} else {	/* ƒgƒi�[�§ŒÀ–³‚µ */
		devinfo->tlimit_num = 0;
		devinfo->tlimit_val = 0;
	}

	return DI_GET_OK;
}


int get_1drop_di_GPS( di_devinfo_GPS_t *devinfo, int dpix, int dpiy, int bit,int dit, unsigned char paper, unsigned char prt_mode, di_dropinfo_t *drop )
{

        printf("Entering get_1drop_di_GPS()..\n");

	long			off;
	int			id;
	int			adr;
	gps_nclr_shdm_t 	*nshdm;
	gps_nclr_data_t		*ndt;

	    GPS_Color_getShrd();
	    off = loffset; /*Got from GPS Wrapper function of Shrd() call..	*/
	if( off < 0 ) {
		return -1;
	}
	
	if( !(devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM) ) {
		return -1;
	}

	devinfo->shdm_addr = gps_shdm_addr;
	nshdm = (gps_nclr_shdm_t*)(devinfo->shdm_addr + off);

	id = GPS_Color_getID2(dpix, dpiy, bit, dit, prt_mode, paper);

	if( id < 0 ) {
		return -1;
	}

	/* get data */
	ndt = &(nshdm->data);
	ndt = &(ndt[id]);
	adr = (int)nshdm;

	if( (ndt->drop.lit == 0) || (ndt->drop.inv == 0) ) {
		drop->lit = (unsigned char *)0;
		drop->inv = (unsigned char *)0;
	} else {
		/* set data */
		drop->lit = (unsigned char *)(adr + ndt->drop.lit);
		drop->inv = (unsigned char *)(adr + ndt->drop.inv);
	}


        printf("Exiting get_1drop_di_GPS()..\n");
	return 0;
}

int get_drop_di_GPS( di_devinfo_GPS_t *devinfo)
{
        printf("Entering get_drop_di_GPS()..\n");
	int reso;
	di_dropinfo_t *drop_ptr;
	dg_param_t dgparam;

	if( !(devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM) ) {
		return DI_GET_OK;
	}

	/* â€œKâ€”ÃŠÆ’fÂ�[Æ’^â€šÃ°Æ’TÆ’|Â�[Æ’gâ€šÂµâ€šÃ„â€šÂ¢â€šÃˆâ€šÂ¢Â�ÃªÂ�â€¡â€šÃ�â€šÃˆâ€šÃ‰â€šÃ â€šÂµâ€šÃˆâ€šÂ¢ */
	if( devinfo->support_drop == FALSE ) {
		return DI_GET_OK;
	}

	devinfo->drop_info = (di_dropinfo_t **)mmalloc( sizeof(di_dropinfo_t) * devinfo->resonum);

	if (devinfo->drop_info == 0)
		return DI_GET_NG;

	drop_ptr = (di_dropinfo_t *)devinfo->drop_info;

	for (reso = 0; reso < devinfo->resonum; reso++) {
		dgparam.resox		= devinfo->reso_set[reso].x;
		dgparam.resoy		= devinfo->reso_set[reso].y;
		dgparam.bit		= devinfo->reso_set[reso].bit;
		dgparam.dit		= devinfo->reso_set[reso].dit_mode;
		dgparam.paper		= devinfo->reso_set[reso].paper;
		dgparam.prt_mode	= devinfo->reso_set[reso].prt_mode;

		adjust_dgparam_GPS( &dgparam );

		if (get_1drop_di_GPS(devinfo,
			dgparam.resox, dgparam.resoy, dgparam.bit,
			dgparam.dit, dgparam.paper, dgparam.prt_mode, 
			drop_ptr++ ) < 0) {
			return DI_GET_NG;
		}
	}

        printf("Exiting get_drop_di_GPS()..\n");
	return DI_GET_OK;
}

int get_1dupgam_di_GPS( di_devinfo_GPS_t *devinfo, int dpix, int dpiy, int bit,int dit, unsigned char paper, unsigned char prt_mode, di_dupgaminfo_t *dupgam )
{

	printf("Entered get_1dupgam_di_GPS() ..\n");
	long			*ptr;
	long			off;
	int			id;
	int			adr;
	gps_nclr_shdm_t 	*nshdm;
	gps_nclr_data_t		*ndt;

	GPS_Color_getShrd();
	off = loffset; /*Got from GPS Wrapper function of Shrd() call..	*/
	
	if( off < 0 ) {
		return -1;
	}
	
	if( !(devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM) ) {
		return -1;
	}

	devinfo->shdm_addr = gps_shdm_addr;
	nshdm = (gps_nclr_shdm_t*)(devinfo->shdm_addr + off);

	id = GPS_Color_getID2(dpix, dpiy, bit, dit, prt_mode, paper);

	if( id < 0 ) {
		return -1;
	}

	/* get data */
	ndt = &(nshdm->data);
	ndt = &(ndt[id]);
	adr = (int)nshdm;

	/* set data */
	if (ndt->dupgam.gam_front == 0 ||
	    ndt->dupgam.gam_back  == 0 ) {
	  /* â€”Â¼â€“ÃŠÆ’Ã�â€�Ã¤â€”Â¦Æ’fÂ�[Æ’^â€šÂªâ€˜Â¶Â�Ã�â€šÂµâ€šÃˆâ€šÂ¢Â�ÃªÂ�â€¡(Æ’IÆ’tÆ’ZÆ’bÆ’gâ€šÂª0)â€šÃ�
	     dupgam->gam_*â€šÃ�(uchar *)0â€šÃ†â€šÂµâ€šÃ„â€šÂ¨â€šÂ­(PRâ€˜Â¤â€šÃ…Æ’`Æ’FÆ’bÆ’N) */
	  dupgam->gam_front = (unsigned char *)0;
	  dupgam->gam_back  = (unsigned char *)0;
	} else {
	  dupgam->gam_front = (unsigned char *)(adr + ndt->dupgam.gam_front);
	  dupgam->gam_back  = (unsigned char *)(adr + ndt->dupgam.gam_back);
	}

	printf("Exiting get_1dupgam_di_GPS() ..\n");
	return 0;
}

int get_dupgam_di_GPS( di_devinfo_GPS_t *devinfo )
{
	printf("Entered get_dupgam_di_GPS() ..\n");
	int reso;
	di_dupgaminfo_t *dupgam_ptr;
	dg_param_t dgparam;
	
	if( !(devinfo->flag & DI_SUPPORT_EXT_DEVINFO_PARAM) ) {
		return DI_GET_OK;
	}

	devinfo->dupgam_info = (di_dupgaminfo_t **)mmalloc(sizeof(di_dupgaminfo_t) * devinfo->resonum);

	if (devinfo->dupgam_info == 0)
		return DI_GET_NG;

	dupgam_ptr = (di_dupgaminfo_t *)devinfo->dupgam_info;

	for (reso = 0; reso < devinfo->resonum; reso++) {
		dgparam.resox		= devinfo->reso_set[reso].x;
		dgparam.resoy		= devinfo->reso_set[reso].y;
		dgparam.bit			= devinfo->reso_set[reso].bit;
		dgparam.dit			= devinfo->reso_set[reso].dit_mode;
		dgparam.paper		= devinfo->reso_set[reso].paper;
		dgparam.prt_mode	= devinfo->reso_set[reso].prt_mode;

		adjust_dgparam_GPS( &dgparam );

		if (get_1dupgam_di_GPS(devinfo,
			dgparam.resox, dgparam.resoy, dgparam.bit,
			dgparam.dit, dgparam.paper, dgparam.prt_mode, 
			dupgam_ptr++ ) < 0) {
			return DI_GET_NG;
		}
	}

	printf("Exiting get_dupgam_di_GPS() ..\n");
	return DI_GET_OK;
}

int get_profile_di_GPS( di_devinfo_GPS_t *devinfo )
{
	printf("Entered get_profile_di_GPS() ..\n");

	long	prof_num = 0;	/* Æ’vÆ’Â�Æ’tÆ’@Æ’CÆ’â€¹Â�â€� */
	gps_color_profile_info_GPS_t	*prof_addr = 0;	/* Æ’vÆ’Â�Æ’tÆ’@Æ’CÆ’â€¹â€”ÃŒË†Ã¦â€šÃŒÆ’AÆ’hÆ’Å’Æ’X */

	if( GPS_Color_getProfile( gps_client, &prof_addr, &prof_num )== GPS_FUNC_SUPPORT)
                printf("gpsColor_getProfile() Successful..\n");
        else
                printf("gpsColor_getProfile() failed..\n");
				

	/* DI â€šÃ‰Æ’ZÆ’bÆ’g */
	devinfo->profaddress = (void *)prof_addr;
	devinfo->profnumber  = prof_num;

	printf("Entered get_profile_di_GPS() ..\n");
	return 0;
}

int di_getinfo_GPS(di_devinfo_GPS_t *devinfo, char *dither_gamma_file)
{
	DI_CALLBACK_MEMALLOC alloc_func;
	printf("Entering di_getinfo_GPS()..\n");
        int ret = DI_OK;
        printf("Assuming gpsOpen() updated shdm_addr properly....\n");
        printf(" gps_shdm_addr = [%p]\n", gps_shdm_addr);
	
			if (get_render_info_GPS_di_(devinfo) == DI_GET_OK)
			{
					/* Æ’fÆ’BÆ’UÆ’pÆ’â€°Æ’<81><81>[Æ’^Å½Ã¦â€œÂ¾ */
					if (get_dither_info_di_GPS(devinfo) != DI_GET_OK)
		{
			printf("returning ERROR at line #1256..\n");
							ret |= DI_GI_ERR_DITHER;
		}
                        /* Æ’KÆ’â€œÆ’Æ’pÆ’â€°Æ’<81><81>[Æ’^Å½Ã¦â€œÂ¾ */
                        if (get_gamma_info_di_GPS(devinfo) != DI_GET_OK)
                                ret |= DI_GI_ERR_GAMMA;
                }
                else
                { /*  Æ’Å’Æ’â€œÆ’_Æ’Å Æ’â€œÆ’OÆ’pÆ’â€°Æ’<81><81>[Æ’^Å½Ã¦â€œÂ¾Å½Â¸â€�s */
                        ret |= DI_GI_ERR_RESO | DI_GI_ERR_NDIT
                                   | DI_GI_ERR_DITHER | DI_GI_ERR_GAMMA;

                        printf("get_render_info_di_() failed..\n");
                }

		devinfo->dither_info->dit_order	= 	0x40;

		/* get GCR parameters */
		if (get_gcr_di_GPS(devinfo) != DI_GET_OK)
			ret |= DI_GI_ERR_GCR;

		/* BG/UCR Æ’pÆ’â€°Æ’Â�Â�[Æ’^Å½Ã¦â€œÂ¾ */
		if( get_bgucr_param_di_GPS(devinfo) != DI_GET_OK )
			ret |= DI_GI_ERR_BGUCR;

		/* â€˜Â�â€”ÃŠâ€¹KÂ�Â§â€™lÅ½Ã¦â€œÂ¾ */
		if( get_tlimit_di_GPS( devinfo) != DI_GET_OK )
			ret |= DI_GI_ERR_TLIMIT_R;


		/* â€œKâ€”ÃŠÆ’eÂ�[Æ’uÆ’â€¹Å½Ã¦â€œÂ¾ */
		if( get_drop_di_GPS( devinfo ) != DI_GET_OK )
			ret |= DI_GI_ERR_DROP;

		/* â€”Â¼â€“ÃŠÆ’Ã�Å â€žÂ�â€¡Å½Ã¦â€œÂ¾ */
		if( get_dupgam_di_GPS( devinfo ) != DI_GET_OK )
			ret |= DI_GI_ERR_DUPGAM;

		/* Æ’vÆ’Â�Æ’tÆ’@Æ’CÆ’â€¹Â�Ã®â€¢Ã±Å½Ã¦â€œÂ¾ */
		if( get_profile_di_GPS( devinfo ) != DI_GET_OK )
			ret |= DI_GI_ERR_PROF;


        	printf("Exiting di_getinfo_GPS()..\n");
		return ret;
}
