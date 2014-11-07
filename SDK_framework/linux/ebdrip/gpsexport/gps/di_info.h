#include "device.h"
typedef unsigned int u_int;
#include "gps/gps_client.h"

#define GPS_MAX_CPF_PATH_LEN            96
#define GPS_MAX_CPF_ATTR_LEN            27
#define GPS_FUNC_SUPPORT        (1) 
#define GPS_FUNC_NOT_SUPPORT    (0)

#define DEF_SUPPORT_TLIMIT  FALSE /* ãƒˆãƒŠãƒ¼ãƒªãƒŸãƒƒãƒˆã�®ã‚µãƒ�ãƒ¼ãƒˆã�ªã�— */

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
        int	ndit;                       /* ï¾‚ï½¿fï¾‚ï½¿Bï¾‚ï½¿Uï¾‚ï½¿ï¾ƒï½­ï¾‚ï½¿ï¾ƒæ¥ªé�’ï½¿ */
        int	nplane;                 /* ï¾‚ï½¿Tï¾‚ï½¿|ï¾‚ãƒ¼ï¾‚ï½¿gï¾‚å‚¬ï¿½ï½¿ï¾ƒï½¥ï¾‚ï½¿vï¾‚ï½¿ï¾‚ï½¿ï¾‚ãƒ¼ï¾‚ï½¿ï¾‚ï½¿ï¾‚é�’ï½¿ */

        di_bgucrinfo_t	**bgucr_info;   /* BG/UCR(ï¾‚ï½¿eï¾‚ãƒ¼ï¾‚ï½¿uï¾‚ï½¿ï¾‚ï½¿) */

        di_gcrinfo_t	*gcr_info;           /* WiShGCR */

        di_gcrinfo_t	*gcrhgr_info;     /* WiShGCR(ï¾‚å‚µï½¿ï¾‚ï½¿nï¾‚ï½¿p) */

        di_dropinfo_t	**drop_info;     /* ï¾‚ï½¿Kï¾‚ï½¿ï¾ƒç’°ï½¿eï¾‚ãƒ¼ï¾‚ï½¿uï¾‚ï½¿ï¾‚ï½¿ */

        di_dupgaminfo_t	**dupgam_info;              /* ï¾‚ï½¿ï¾‚ï½¼ï¾‚ï½¿ï¾ƒç’°ï½¿ï¾ƒï¿½ï½¿ï¾‚ï½¿ï¾‚å‚µï½¿ */
		char	*shdm_addr;

		float	bg_startp;	/* BG çª¶å ‹ï½ªï¾…ï½½nçª¶å ™æ‡Œï¿½ï¾ƒï½©ï¾…ï¿½ï¾…ï½½nï¾†æ¤Žæ§Œé�…ï¾†å�œï¿½ */
		float	bg_slant;	/* BG çª¶å��ï½¼ï¾‚é�™ï½¼ï¾…æ´¥ï½¹çª¶æŽ� */
		float	ucr_startp;	/* UCR çª¶å ‹ï½ªï¾…ï½½nçª¶å ™æ‡Œï¿½ï¾ƒï½©ï¾…ï¿½ï¾…ï½½nï¾†æ¤Žæ§Œé�…ï¾†å�œï¿½ */
		float	ucr_slant;	/* UCR çª¶å��ï½¼ï¾‚é�™ï½¼ï¾…æ´¥ï½¹çª¶æŽ� */
		int	support_drop;
		int toner_limit;	/* ç·�é‡�è¦�åˆ¶ã�®ã‚µãƒ�ãƒ¼ãƒˆ[1:ã�‚ã‚Š, 0:ã�ªã�—] */
		unsigned int tlimit_num;	/* æ©Ÿç¨®ã�Œã‚µãƒ�ãƒ¼ãƒˆã�—ã�¦ã�„ã‚‹ç·�é‡�è¦�åˆ¶å€¤ã�®ç¨®é¡žæ•° */
		di_tlimitinfo_t *tlimit_val;
};
typedef struct di_devinfo_GPS di_devinfo_GPS_t;

int di_getinfo_GPS(di_devinfo_GPS_t * , char *);
int get_render_info_GPS_di_ (di_devinfo_GPS_t * );
int get_resocombo_GPS(di_devinfo_GPS_t * );
int get_appinfo_di_GPS( char *, char *, long , char * );
int get_dither_info_di_GPS(di_devinfo_GPS_t *devinfo);

typedef struct dg_param {
	unsigned int	resox;	/* xçª¶ï½¢ï¾ƒï½»ï¾…æ´¥ï½¼çª¶ï½°ï¾ƒï½°çª¶ä½›å‡ªï¿½x */
	unsigned int	resoy;	/* yçª¶ï½¢ï¾ƒï½»ï¾…æ´¥ï½¼çª¶ï½°ï¾ƒï½°çª¶ä½›å‡ªï¿½x */
	unsigned char	bit;	/* ï¾†æ± ï¾†é�›ï¾†æš–ï¾‚çµ¶ï¿½ */
	int		dit;	/* ï¾†æ–­ï¾†é�”ï¾†æ—¦ï¾†å�œï¿½ï¾‚ãƒ¼ï¾†æª€[0:photo,1:text,2:graphics,3:cad] */
	int		color;	/* ï¾†è°·ï¾†å�œï¿½ï¾‚ãƒ¼ï¾†å�œï¿½ï¾‚ãƒ¼ï¾†æª€[0:K, 1:C, 2:M, 3:Y] */
/*#ifdef USE_IMAQ	*/
	unsigned char   paper;		/* ï¾…ï½½çª¶ï¿½ï½½ï¾ƒï½­ */
	unsigned char   prt_mode;	/* ï¾†è‡´ï¾†æ¤Žï¿½å�œï¿½ï¾†è€½ï¾†æª€ï¾†å�œï¿½ï¾†è¾°ï¾†å¼›çª¶å ™ï¿½ï¿½ï¾ƒå§‘å�œï¿½ï¾‚ãƒ¼ï¾†æª€ */
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
