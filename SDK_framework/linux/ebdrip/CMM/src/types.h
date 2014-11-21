/*
 *	configuration header for FresaWIN emulator.
 *	Copyright(c) 1996 by RICOH.
 *
 *	$Author: Najeesha $
 *	$Date: 2009/01/01 15:19:01 $
 *	$Revision: 1.5 $
 */
#ifndef __TYPES_H__
#define __TYPES_H__

/*
#ifndef TRUE
#define	TRUE	(1)			Function TRUE  value	    
#endif
#ifndef	FALSE
#define	FALSE	(0)			Function FALSE value	    
#endif
#ifndef NULL
#define	NULL	0			Null character value	    
#endif*/

#define	MAX_UCHAR_VALUE		(0xFF)			/* Max unsigned char value */
#define MAX_INTEGER_VALUE	(0xFFFFFFFF)	/* Max integer value */
#define	MAX_ULONG_VALUE		(0xFFFFFFFF)	/* Max unsigned long value */
/*
 *	using class define.
 */
#ifndef TARGET_KIBO
#define	uchar	unsigned char
typedef int BOOL;
#else
typedef	unsigned char uchar;
#endif /* TARGET_KIBO */

#if !defined(__sys_types_h) && !defined(_SYS_TYPES_H_) && !defined(_SYS_TYPES_H)
#if (!defined(UNIX) || defined(NETBSD)) && !defined(TARGET_KIBO)
#ifndef USE_SYS_TYPES
#include </proj/lpux/1.3/netbsd/usr/include/sys/types.h>
#else
#include "sys/types.h"
#endif /* USE_SYS_TYPES */
#else
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
#endif /* GPS */
#endif

#ifndef GLOBAL
/* for gamma.h */
#define	GLOBAL
#ifndef TARGET_KIBO
typedef char BYTE;
typedef unsigned char UBYTE;
#endif /* TARGET_KIBO */
typedef unsigned long ULONG;
#endif

#ifndef __POS__
#define __POS__

typedef long POS;
typedef unsigned long UPOS;
typedef short RPOS;
typedef unsigned short URPOS;

#endif /* __POS__ */

#ifdef USE_REGISTER
#define REG	register
#else
#define REG
#endif /* USE_REGISTER */

/*
 *	type define for MSIS informations.
 */
typedef struct SEARCH_PARAMETER SEARCHPARAMETER;
typedef struct FONT_HEADER FONTHEADER;
typedef struct FONT_TABLE FONTTABLE;
typedef struct FONT_DIRECTORY fontdir_t;

#endif
