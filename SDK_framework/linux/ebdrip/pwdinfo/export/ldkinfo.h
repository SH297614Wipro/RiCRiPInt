#ifndef __LDKINFO_H__
#define __LDKINFO_H__

/* Copyright (C) 2012 Global Graphics Software Ltd. All rights reserved.
 * Global Graphics Software Ltd. Confidential Information.
 *
 * $HopeName: DPPpwdinfo!export:ldkinfo.h(EBDSDK_P.1) $
 *
 */


#include "ldkdefs.h"


/* Feature IDs for subfeatures (plugins and languages)
 *
 * Add new entries at end of the relevant section
 *
 * Note that some entries may not appear in the big table
 * in pwdinfo.c.  This is possible if the feature only
 * has to work in an LDK-enabled RIP, and so doesn't need
 * to have a password generated for it.
 */
enum {
  /* Core Module plugins */
  LDKKEY_CM_ECRMDM = 2200,
  LDKKEY_CM_HEDS = 2201,


  /* Output plugins */
  LDKKEY_DEV_C8000 = 3300,
  LDKKEY_DEV_CANON_12CMYK = 3301,
  LDKKEY_DEV_CANON_12COLOR = 3302,
  LDKKEY_DEV_CANON_12RGB = 3303,
  LDKKEY_DEV_CANON_iPF8000S = 3304,
  LDKKEY_DEV_CANON_iPF8010S = 3305,
  LDKKEY_DEV_CANON_iPF9000S = 3306,
  LDKKEY_DEV_CANON_iPF9010S = 3307,
  LDKKEY_DEV_CANON_W2200 = 3308,
  LDKKEY_DEV_CANON_W72x0 = 3309,
  LDKKEY_DEV_CGS = 3310,
  LDKKEY_DEV_CIP3 = 3311,
  LDKKEY_DEV_COMPOSE1 = 3312,
  LDKKEY_DEV_COMPOSE2 = 3313,
  LDKKEY_DEV_COMPOSE3 = 3314,
  LDKKEY_DEV_COMPOSE4 = 3315,
  LDKKEY_DEV_COMPOSE5 = 3316,
  LDKKEY_DEV_COMPOSE6 = 3317,
  LDKKEY_DEV_COMPOSE7 = 3318,
  LDKKEY_DEV_COMPOSE8 = 3319,
  LDKKEY_DEV_COMPOSEA = 3320,
  LDKKEY_DEV_COMPOSEB = 3321,
  LDKKEY_DEV_DISPLAYMAK = 3322,
  LDKKEY_DEV_DPP1200ECRM = 3323,
  LDKKEY_DEV_DPX_LITE = 3324,
  LDKKEY_DEV_DUPLO = 3325,
  LDKKEY_DEV_ECRM_SUNFISH = 3326,
  LDKKEY_DEV_ECRMTiff2Folder = 3327,
  LDKKEY_DEV_ENCAD = 3328,
  LDKKEY_DEV_ENCAD_NJ700_36 = 3329,
  LDKKEY_DEV_ENCAD_NJ700_42 = 3330,
  LDKKEY_DEV_ENCAD_NJ700_60 = 3331,
  LDKKEY_DEV_ENCAD_NJ850 = 3332,
  LDKKEY_DEV_EPSON = 3333,
  LDKKEY_DEV_EPSON10000VSD = 3334,
  LDKKEY_DEV_EPSON10600VSD = 3335,
  LDKKEY_DEV_EPSON11880VSD = 3336,
  LDKKEY_DEV_EPSON2200VSD = 3337,
  LDKKEY_DEV_EPSON3000 = 3338,
  LDKKEY_DEV_EPSON3800VSD = 3339,
  LDKKEY_DEV_EPSON4000VSD = 3340,
  LDKKEY_DEV_EPSON4800VSD = 3341,
  LDKKEY_DEV_EPSON4880PLATE = 3342,
  LDKKEY_DEV_EPSON4880VSD = 3343,
  LDKKEY_DEV_EPSON4900 = 3344,
  LDKKEY_DEV_EPSON5000 = 3345,
  LDKKEY_DEV_EPSON5500VSD = 3346,
  LDKKEY_DEV_EPSON7000 = 3347,
  LDKKEY_DEV_EPSON7500 = 3348,
  LDKKEY_DEV_EPSON7600VSD = 3349,
  LDKKEY_DEV_EPSON7800VSD = 3350,
  LDKKEY_DEV_EPSON7880VSD = 3351,
  LDKKEY_DEV_EPSON7890 = 3352,
  LDKKEY_DEV_EPSON7900PLATE = 3353,
  LDKKEY_DEV_EPSON7900VSD = 3354,
  LDKKEY_DEV_EPSON9000 = 3355,
  LDKKEY_DEV_EPSON7900X = 3356,
  LDKKEY_DEV_EPSON9500 = 3357,
  LDKKEY_DEV_EPSON9600VSD = 3358,
  LDKKEY_DEV_EPSON9800VSD = 3359,
  LDKKEY_DEV_EPSON9880VSD = 3360,
  LDKKEY_DEV_EPSON9890 = 3361,
  LDKKEY_DEV_EPSON9900 = 3362,
  LDKKEY_DEV_FUJI_P_3000 = 3363,
  LDKKEY_DEV_FUJI_PP_4000 = 3364,
  LDKKEY_DEV_FUSION_Designjet = 3365,
  LDKKEY_DEV_FUSION_DigiPage = 3366,
  LDKKEY_DEV_FUSION_Epson = 3367,
  LDKKEY_DEV_FUSION_FTIFF = 3368,
  LDKKEY_DEV_GICCPRINTCOPIERS = 3369,
  LDKKEY_DEV_GIEPROOFESPSON = 3370,
  LDKKEY_DEV_GIEPROOFESPSON9K = 3371,
  LDKKEY_DEV_GILPPROOFLPT = 3372,
  LDKKEY_DEV_GIRTLPROOFRTL = 3373,
  LDKKEY_DEV_HIGHWIMINOLTA = 3374,
  LDKKEY_DEV_HIGHW_PRINT_COLOUR = 3375,
  LDKKEY_DEV_HIGHW_PRINT_MONO = 3376,
  LDKKEY_DEV_HP1050DJ = 3377,
  LDKKEY_DEV_HP120DJ = 3378,
  LDKKEY_DEV_HP130DJ = 3379,
  LDKKEY_DEV_HP2000 = 3380,
  LDKKEY_DEV_HP3000DJ = 3381,
  LDKKEY_DEV_HP2000DJ = 3382,
  LDKKEY_DEV_HP5000DJ = 3383,
  LDKKEY_DEV_HP5500DJ = 3384,
  LDKKEY_DEV_HPT1100DJ = 3385,
  LDKKEY_DEV_HPT610DJ = 3386,
  LDKKEY_DEV_HPZ2100DJ = 3387,
  LDKKEY_DEV_HPZ6100DJ = 3388,
  LDKKEY_DEV_HP_50PS = 3389,
  LDKKEY_DEV_HP_750 = 3390,
  LDKKEY_DEV_HP_PCL = 3391,
  LDKKEY_DEV_HP_ROLL_FED = 3392,
  LDKKEY_DEV_HP_RTL = 3393,
  LDKKEY_DEV_HWDQM_DI = 3394,
  LDKKEY_DEV_HWPCI = 3395,
  LDKKEY_DEV_HWPLATESTREAM = 3396,
  LDKKEY_DEV_IJ2P = 3397,
  LDKKEY_DEV_IMPOS_DJ_2000 = 3398,
  LDKKEY_DEV_IMPOS_DJ_3000 = 3399,
  LDKKEY_DEV_IMPOS_IMPRESS = 3400,
  LDKKEY_DEV_INKJETDIRECTIJD11 = 3401,
  LDKKEY_DEV_INKJETDIRECTIJD4 = 3402,
  LDKKEY_DEV_INKJETDIRECTIJD7 = 3403,
  LDKKEY_DEV_INKJETDIRECTIJD7C = 3404,
  LDKKEY_DEV_INKJETDIRECTIJD9 = 3405,
  LDKKEY_DEV_INTEC2020 = 3406,
  LDKKEY_DEV_IPLATEMAKINGX1 = 3407,
  LDKKEY_DEV_JETPLATE2100 = 3408,
  LDKKEY_DEV_JETPLATE4000 = 3409,
  LDKKEY_DEV_JETPLATE7600 = 3410,
  LDKKEY_DEV_Kammann_KP_file = 3411,
  LDKKEY_DEV_MAXWORKFLOW = 3412,
  LDKKEY_DEV_MINOLTAFILE = 3413,
  LDKKEY_DEV_MSERIESPRINTER = 3414,
  LDKKEY_DEV_OKIC9650 = 3415,
  LDKKEY_DEV_OKIPRO511DW = 3416,
  LDKKEY_DEV_OL_GS_618 = 3417,
  LDKKEY_DEV_OL_GS_624 = 3418,
  LDKKEY_DEV_OL_GS_636 = 3419,
  LDKKEY_DEV_OL_GS_642 = 3420,
  LDKKEY_DEV_OL_SE_1800 = 3421,
  LDKKEY_DEV_OL_SE_2800 = 3422,
  LDKKEY_DEV_OL_XE_1800 = 3423,
  LDKKEY_DEV_OL_XE_1812 = 3424,
  LDKKEY_DEV_OL_XE_1812M = 3425,
  LDKKEY_DEV_OL_XE_2812 = 3426,
  LDKKEY_DEV_OL_XE_2812M = 3427,
  LDKKEY_DEV_OL_XE_2800 = 3428,
  LDKKEY_DEV_OL_XE_3600 = 3429,
  LDKKEY_DEV_OL_XE_3612 = 3430,
  LDKKEY_DEV_OL_XE_3612M = 3431,
  LDKKEY_DEV_OL_XE_4200 = 3432,
  LDKKEY_DEV_OL_XE_4212 = 3433,
  LDKKEY_DEV_OL_XE_5400 = 3434,
  LDKKEY_DEV_OL_XE_5412 = 3435,
  LDKKEY_DEV_OL_XE_5412M = 3436,
  LDKKEY_DEV_OYO_DIABLO_1812P = 3437,
  LDKKEY_DEV_OYO_DIABLO_1812M = 3438,
  LDKKEY_DEV_OYO_GM_1800 = 3439,
  LDKKEY_DEV_OYO_GM_2800 = 3440,
  LDKKEY_DEV_OYO_GM_3600 = 3441,
  LDKKEY_DEV_OYO_GM_4200 = 3442,
  LDKKEY_DEV_OYO_GM_5400 = 3443,
  LDKKEY_DEV_OYO_GOBLINP = 3444,
  LDKKEY_DEV_OYO_GOBLINM = 3445,
  LDKKEY_DEV_OYO_TECSET = 3446,
  LDKKEY_DEV_OYO_TS = 3447,
  LDKKEY_DEV_OYO_TSII = 3448,
  LDKKEY_DEV_OYO_TSTYLER = 3449,
  LDKKEY_DEV_OYO_TSTYLERII = 3450,
  LDKKEY_DEV_PDFRASTER = 3451,
  LDKKEY_DEV_PISCES_JP_3000 = 3452,
  LDKKEY_DEV_PISCES_JP_7600 = 3453,
  LDKKEY_DEV_PLATEJET = 3454,
  LDKKEY_DEV_PLATEWRITER2000 = 3455,
  LDKKEY_DEV_PLATEWRITER2400 = 3456,
  LDKKEY_DEV_PLATEWRITER4200 = 3457,
  LDKKEY_DEV_PRISM = 3458,
  LDKKEY_DEV_ScreenDTR4100 = 3459,
  LDKKEY_DEV_ScreenDTR8000 = 3460,
  LDKKEY_DEV_ScreenDTR8100 = 3461,
  LDKKEY_DEV_SETGOLD_PRO = 3462,
  LDKKEY_DEV_SETGOLD = 3463,
  LDKKEY_DEV_SONG_CLASER_A = 3464,
  LDKKEY_DEV_SONG_CLASER_B = 3465,
  LDKKEY_DEV_SONG_CALCOMP_B = 3466,
  LDKKEY_DEV_SONG_E6COLOR = 3467,
  LDKKEY_DEV_SONG_GEN586I = 3468,
  LDKKEY_DEV_SONG_HP_LASER = 3469,
  LDKKEY_DEV_SONG_HP_RTL_A = 3470,
  LDKKEY_DEV_SONG_HP_RTL_B = 3471,
  LDKKEY_DEV_SONG_HP_RTL_C = 3472,
  LDKKEY_DEV_SONG_MAESTRO_C = 3473,
  LDKKEY_DEV_SONG_MIMAKI_C = 3474,
  LDKKEY_DEV_SONG_MUTOH_B = 3475,
  LDKKEY_DEV_SONG_MUTOH_C = 3476,
  LDKKEY_DEV_SONG_NOVA_A = 3477,
  LDKKEY_DEV_SONG_NOVA_B = 3478,
  LDKKEY_DEV_SONG_NOVA_C = 3479,
  LDKKEY_DEV_SONG_P6COLOR_B = 3480,
  LDKKEY_DEV_SONG_P6COLOR_S_B = 3481,
  LDKKEY_DEV_SONG_STYLUS = 3482,
  LDKKEY_DEV_SONG_STYLUS_A = 3483,
  LDKKEY_DEV_SPECTRUM_AM = 3484,
  LDKKEY_DEV_TIFFIT_OUT = 3485,
  LDKKEY_DEV_TIFF = 3486,
  LDKKEY_DEV_ULTRE5K_5400 = 3487,
  LDKKEY_DEV_ULTRE5K_5800 = 3488,
  LDKKEY_DEV_VUTEK = 3489,
  LDKKEY_DEV_WIDEEPSON = 3490,
  LDKKEY_DEV_WINPRINT = 3491,
  LDKKEY_DEV_X_EPSONS_10K = 3492,
  LDKKEY_DEV_X_EPSONVDOT = 3493,
  LDKKEY_DEV_X_EPSONVDOT_LITE = 3494,
  LDKKEY_DEV_X_EPSON2VDOT2 = 3495,
  LDKKEY_DEV_X_EPSON2VDOT2_LITE = 3496,
  LDKKEY_DEV_X_EPSON3VDOT3 = 3497,
  LDKKEY_DEV_X_EPSON3VDOT3_LITE = 3498,
  LDKKEY_DEV_X_EPSONVDOT34880 = 3499,
  LDKKEY_DEV_X_EPSONVDOT37880 = 3500,
  LDKKEY_DEV_X_EPSONVDOT39880 = 3501,
  LDKKEY_DEV_X_EPSONVDOT4 = 3502,
  LDKKEY_DEV_XPROOF_ADV = 3503,
  LDKKEY_DEV_XPROOF_PCL = 3504,
  LDKKEY_DEV_XITRONX2 = 3505,
  LDKKEY_DEV_PDFRASTER2 = 3506,


  /* Languages */
  LDKKEY_LANG_CHINESE_SIMPLE = 4400,
  LDKKEY_LANG_CHINESE_TRAD = 4401,
  LDKKEY_LANG_FRENCH = 4402,
  LDKKEY_LANG_GERMAN = 4403,
  LDKKEY_LANG_ITALIAN = 4404,
  LDKKEY_LANG_JAPANESE = 4405,
  LDKKEY_LANG_KOREAN = 4406,
  LDKKEY_LANG_KOREAN_J = 4407,
  LDKKEY_LANG_POLISH = 4408,
  LDKKEY_LANG_RUSSIAN = 4409,
  LDKKEY_LANG_SPANISH = 4410,
  LDKKEY_LANG_SPANISH_MEX = 4411,
  LDKKEY_LANG_SPANISH_TRAD = 4412,


  /* Fonts */
  LDKKEY_FONTS_LINOTYPE_35 = 4700,
  LDKKEY_FONTS_SHIVA_35PS1 = 4701,


  /* Non-RIP products */
  LDKKEY_SETGOLD = 5500,
  LDKKEY_SETGOLD_PRO = 5501, 

  LDKKEY_DONGLETOOL = 5600, 


  /* Out of range ID for options never required with LDK */
  LDKKEY_UNSUPPORTED = 99999
};



#endif


/* Modification history:
* Log stripped */
