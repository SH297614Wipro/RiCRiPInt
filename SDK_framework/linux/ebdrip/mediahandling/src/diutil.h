#include<stdio.h>
struct BitSWConfig{
#ifdef COLOR_RENDERING
        unsigned int         is_datamode_mono:1;
#ifdef PCL_FORCE_MONO
        unsigned int         is_force_mono:1;
#endif
#endif
//#if HP_PAGE_ROTATE == 2
        unsigned int          is_mixedrot_old:1;
//#endif
#if defined(CUSTOM_MIXPLEX) || defined(RP_DUPLEX_INTERLEAVE)
    unsigned int              is_mixplex_on:1;
#endif
#ifdef ECONOMY_COLOR_FEATURE
    unsigned int              is_ecocolormethod_one:1;
#endif
//#if BYPASS_FREE_FEED >= 2
    unsigned int              is_direction_SEF:1;
//#endif
    unsigned int              is_timeout_invalid:1;
#if TRAY_OVERWRITING >= 2
    unsigned int              is_directionoverwriting_invalid:1;
#endif
}BitSWConfig;

