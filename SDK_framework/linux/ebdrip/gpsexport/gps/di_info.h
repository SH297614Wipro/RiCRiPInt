#include "device.h"
typedef unsigned int u_int;
#include "gps/gps_client.h"

#define GPS_MAX_CPF_PATH_LEN            96
#define GPS_MAX_CPF_ATTR_LEN            27
#define GPS_FUNC_SUPPORT        (1) 
#define GPS_FUNC_NOT_SUPPORT    (0)

extern gwmsg_client_t *gps_client ;

typedef struct gps_color_profile_info_GPS {
        unsigned long           key;
        unsigned char           media;
        unsigned char           attr[GPS_MAX_CPF_ATTR_LEN];
        char                    path[GPS_MAX_CPF_PATH_LEN];
} gps_color_profile_info_GPS_t;


/*Populating di_devinfo_GPS_t struct	*/
struct di_devinfo_GPS
{
		di_ditinfo_t	*dither_info;
        di_ditinfo_t	*dither_info_mono;

		unsigned char	**gamma_info;
        unsigned char	**gamma_info_mono;

        void	*profaddress;
        long	profnumber;
        unsigned long	flag;

		unsigned int	resonum;
		di_resolutioninfo_t	*reso_set;
        int	ndit;                       /* ¿f¿B¿U¿í¿Þ¿ */
        int	nplane;                 /* ¿T¿|[¿gÅ¿å¿v¿¿[¿¿¿ */

        di_bgucrinfo_t	**bgucr_info;   /* BG/UCR(¿e[¿u¿¿) */

        di_gcrinfo_t	*gcr_info;           /* WiShGCR */

        di_gcrinfo_t	*gcrhgr_info;     /* WiShGCR(¿¿n¿p) */

        di_dropinfo_t	**drop_info;     /* ¿K¿Ê¿e[¿u¿¿ */

        di_dupgaminfo_t	**dupgam_info;              /* ¿¼¿Ê¿Á¿¿¿ */
		char	*shdm_addr;

		float	bg_startp;	/* BG ‚ªŽn‚Ü‚éŠJŽnƒŒƒxƒ‹ */
		float	bg_slant;	/* BG ’¼üŒù”z */
		float	ucr_startp;	/* UCR ‚ªŽn‚Ü‚éŠJŽnƒŒƒxƒ‹ */
		float	ucr_slant;	/* UCR ’¼üŒù”z */
		int	support_drop;

};
typedef struct di_devinfo_GPS di_devinfo_GPS_t;

int di_getinfo_GPS(di_devinfo_GPS_t * , char *);
int get_render_info_GPS_di_ (di_devinfo_GPS_t * );
int get_resocombo_GPS(di_devinfo_GPS_t * );
int get_appinfo_di_GPS( char *, char *, long , char * );
int get_dither_info_di_GPS(di_devinfo_GPS_t *devinfo);

typedef struct dg_param {
	unsigned int	resox;	/* x•ûŒü‰ð‘œ“x */
	unsigned int	resoy;	/* y•ûŒü‰ð‘œ“x */
	unsigned char	bit;	/* ƒrƒbƒg” */
	int		dit;	/* ƒfƒBƒUƒ‚[ƒh[0:photo,1:text,2:graphics,3:cad] */
	int		color;	/* ƒJƒ‰[ƒ‚[ƒh[0:K, 1:C, 2:M, 3:Y] */
/*#ifdef USE_IMAQ	*/
	unsigned char   paper;		/* Ž†Ží */
	unsigned char   prt_mode;	/* ƒvƒŠƒ“ƒ^ƒhƒ‰ƒCƒo‚Å‚Ìƒ‚[ƒh */
/*#endif 	*/
} dg_param_t;

int get_dinfo_GPS(di_devinfo_GPS_t *, int , int , int , di_ditinfo_t *);
void adjust_dgparam_GPS( dg_param_t * );
int get_1dit_di_GPS( di_devinfo_GPS_t *, int , int , int , int , int , unsigned char , unsigned char , di_ditinfo_t * );

int get_gamma_info_di_GPS(di_devinfo_GPS_t *);
int get_ginfo_GPS( di_devinfo_GPS_t *,  int , int , int , unsigned char **);
int get_1gam_di_GPS( di_devinfo_GPS_t *, int , int , int ,int , int , unsigned char , unsigned char ,unsigned char **);

int get_gcr_di_GPS(di_devinfo_GPS_t *);
int get_1gcr_table_di_GPS(di_devinfo_GPS_t *, int , int , int ,int,  unsigned char,  unsigned char , di_gcrinfo_t *, di_gcrinfo_t *);

int get_bgucr_param_di_GPS(di_devinfo_GPS_t *);
int get_1bgucr_table_di_GPS( di_devinfo_GPS_t *, int , int , int ,int , unsigned char , unsigned char ,di_bgucrinfo_t *);

int get_drop_di_GPS( di_devinfo_GPS_t *);
int get_1drop_di_GPS( di_devinfo_GPS_t *, int , int , int ,int , unsigned char , unsigned char , di_dropinfo_t *);

int get_dupgam_di_GPS( di_devinfo_GPS_t * );
int get_profile_di_GPS( di_devinfo_GPS_t * );
