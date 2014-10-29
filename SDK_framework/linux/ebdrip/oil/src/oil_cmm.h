/* Copyright (c) 2006 Global Graphics Software Ltd. All Rights Reserved.
 *
 * $HopeName: SWebd_OIL_example_gg!src:oil_cmm.h(EBDSDK_P.1) $
 *
 * This example is provided on an "as is" basis and without
 * warranty of any kind. Global Graphics Software Ltd. does not
 * warrant or make any representations regarding the use or results
 * of use of this example.
 */


/**
 * \file
 * \ingroup OIL CMM
 * \brief This is a simple example of a color management module.  It shows
 * how some custom color mapping can be done to implement features like pure 
 * black text, black substitution and all-black text.
 */

#ifndef __OIL_CMM_H__
#define __OIL_CMM_H__

#include "skinkit.h"
#include "swcmm.h"


/*FOR CMM*/
typedef struct Color_State_CP 
{
  unsigned char nColorProfile; 
  unsigned char nGrayReproduction; 
  int nDitherObj;
} Color_State_CP ;

/* Keys for color Profile*/
#define VIVID_KEY 0x10001
#define GRADA_KEY 0x10002
#define TEXT_KEY  0x10003
#define SIM_1_KEY 0x10011


// Color Match
enum
{
    NO_COLOR_MATCH = 0,
    TEXT_COLOR_MATCH,
    VIVID_COLOR_MATCH,
    TRANS_COLOR_MATCH,
    OUT_OF_GAMUT
};

// color mode.
#define	PAGE_COLOR_K	0x00		// mono print mode.		
#define	PAGE_COLOR_CMYK	0x80		// CMYK color print mode.	
#define	PAGE_COLOR_RK	0x40		// RK color print mode.		
#define	PAGE_COLOR_CMY	0x20		// CMY color print mode.	
#define	PAGE_COLOR_MASK	0xFC		// color mode mask.	
#define	PAGE_COLOR_XRGB	0x10	// XRGB color print mode.	
#define	PAGE_COLOR_XG	0x08	//XG color print mode.	
#define	PAGE_COLOR_RK2	0x04		// RK2 color print mode.	

#define	COLOR_DEPTH_1	0x00		// 1 bit color by each plane.	
#define	COLOR_DEPTH_2	0x01		// 2 bit color by each plane.	
#define	COLOR_DEPTH_4	0x02		// 4 bit color by each plane.	
#define	COLOR_DEPTH_8	0x03		// 8 bit color by each plane.	
#define	DEPTH_MASK	0x03			// bit depth mask	

sw_cmm_api* oilccs_getInstance ();


#endif /* __OIL_CMM_H__ */
