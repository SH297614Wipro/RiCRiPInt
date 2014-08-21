/*
 *	version informations of simulator.
 *
 *	Copyright (C) 2006-2008, RICOH Software Inc.
 *	All rights reserved. Proprietary and confidential.
 *
 */

/*
 *	following is the version of specification.
 *	if you change the protocol of this tool, you should increment follow.
 */
#define	SIMULATOR_SPEC	"RICOH Print System Simulator(Spec 3.05)"

/*
 *	following are formats for build logo.
 */
#define	LOGO_BANNER		"<><><><><><><><><><><><><><><><><><><><><><><><><><>\n"
#define	LOGO_SEPARATOR	"<> ============================================== <>\n"
#define	LOGO_BLANK		"<>                                                <>\n"
#define	LOGO_TITLE		"<> %-46s <>\n"
#define	LOGO_ITEM		"<> %-23s : %-20s <>\n"

/*
 *	following are messages for initialize.
 */
#define	LOGO_STANDBY	"> initializing now... please standby.\r"

#define	LOGO_SUCCEEDED	"<> RICOH Print System Simulator is active.        <>\n"
#define	LOGO_FAILED		"<> initialization failed.                         <>\n"
#define	LOGO_RETRY		"<> after a while, please execute again.           <>\n"

/*
 *	following describe the optional feature of SIMULATOR.
 */
#if defined(_CNF_TARGET_LPUX3_0)
#define	FTR_TARGET_OS					"RICOH LPUX 3.0"
#elif defined(_CNF_TARGET_LPUX2_0)
#define	FTR_TARGET_OS					"RICOH LPUX 2.0"
#elif defined(_CNF_TARGET_VXWORKS)
#define	FTR_TARGET_OS					"vxWorks 6.5"
#elif defined(_CNF_TARGET_LPUX)
#define	FTR_TARGET_OS					"RICOH LPUX 1.5"
#else
#define	FTR_TARGET_OS					"Unknown target"
#endif

#if defined(_CNF_OS_SOLARIS)
#define	FTR_SIM_OS						"Sun Solaris"
#elif defined(_CNF_OS_LINUX)
#define	FTR_SIM_OS						"RH Linux"
#elif defined(_CNF_OS_LPUX)
#define	FTR_SIM_OS						"RICOH LPUX 1.5"
#elif defined(_CNF_OS_LPUX2_0)
#define	FTR_SIM_OS						"RICOH LPUX 2.0"
#elif defined(_CNF_OS_LPUX3_0)
#define	FTR_SIM_OS						"RICOH LPUX 3.0"
#elif defined(_CNF_OS_CYGWIN)
#define	FTR_SIM_OS						"Cygwin"
#elif defined(_CNF_OS_FREEBSD)
#define	FTR_SIM_OS						"FreeBSD"
#elif defined(_CNF_OS_VXWORKS)
#define	FTR_SIM_OS						"vxWorks 6.5"
#else
#define	FTR_SIM_OS						"Unknown"
#endif

#if	defined(_CNF_CPU_86)
#define	FTR_SIM_CPU						"x86"
#elif defined(_CNF_CPU_PPC)
#define	FTR_SIM_CPU						"ppc"
#elif defined(_CNF_CPU_SPARC)
#define	FTR_SIM_CPU						"sparc"
#elif defined(_CNF_CPU_MIPS)
#define	FTR_SIM_CPU						"mips"
#else
#if defined(_CNF_OS_SOLARIS)
#define FTR_SIM_CPU                    	"sparc"
#elif defined(_CNF_OS_LINUX)||defined(_CNF_OS_CYGWIN)||defined(_CNF_OS_FREEBSD)
#define	FTR_SIM_CPU						"x86"
#else
#define	FTR_SIM_CPU						"unknown"
#endif
#endif

#if	!defined(_CNF_ENDIAN_TYPE)
#define	FTR_ENDIAN						"unknown endian"
#elif _CNF_ENDIAN_TYPE == 0
#define	FTR_ENDIAN						"little endian"
#elif _CNF_ENDIAN_TYPE == 1
#define	FTR_ENDIAN						"big endian"
#else
#define	FTR_ENDIAN						"unknown endian"
#endif

#if	defined(_CNF_WISHGCR)
#define	FTR_WISHGCR						"o"
#else
#define	FTR_WISHGCR						"x"
#endif

#if	defined(_CNF_BACKCHANEL)
#define	FTR_BACKCHANEL					"o"
#else
#define	FTR_BACKCHANEL					"x"
#endif

#if defined(_CNF_NETBOOT)
#if defined(_CNF_NETBOOT_PROMPT)
#define	FTR_NETBOOT						"o(prompt mode)"
#else
#define	FTR_NETBOOT						"o(without prompt)"
#endif
#else
#define	FTR_NETBOOT						"x"
#endif

#if defined(_CNF_MEMORY_POOL)
#define	FTR_MEMORY_POOL					"o"
#define	FTR_MEMORY_POOLSZ				_CNF_MEMORY_POOL
#else
#define	FTR_MEMORY_POOL					"x"
#define	FTR_MEMORY_POOLSZ				0
#endif

#if	defined(_CNF_API_gpsPlotSetPageParamShm)
#define	FTR_API_gpsPlotSetPageParamShm	"o"
#else
#define	FTR_API_gpsPlotSetPageParamShm	"x"
#endif

#if defined(_CNF_API_gpsColor_get_drawparam2)
#define	FTR_API_gpsColor_get_drawparam2	"o"
#else
#define	FTR_API_gpsColor_get_drawparam2	"x"
#endif

#if defined(_CNF_API_gpsPlotPrepare)
#define	FTR_API_API_gpsPlotPrepare		"o"
#else
#define	FTR_API_API_gpsPlotPrepare		"x"
#endif

#if	defined(_CNF_OS_VXWORKS) && defined(_CNF_SIMULATE_LPUX_API)
#define	FTR_SIMULATE_LPUX_API			"o"
#else
#define	FTR_SIMULATE_LPUX_API			"x"
#endif

#if	defined(_CNF_OS_VXWORKS) && defined(_CNF_PTHREAD_STACKCTRL)
#define	FTR_PTHREAD_STACKCTRL			"o"
#else
#define	FTR_PTHREAD_STACKCTRL			"x"
#endif

#if _CNF_TRANSMODE == 0
#define	FTR_TRANSMODE					"binary"
#elif _CNF_TRANSMODE == 1
#define	FTR_TRANSMODE					"text"
#else
#define	FTR_TRANSMODE					"unknown"
#endif

#if	defined(_CNF_HEAP_CHECK)
#define	FTR_HEAP_CHECK					"o"
#else
#define	FTR_HEAP_CHECK					"x"
#endif

#if	defined(_CNF_GMON)
#define	FTR_GMON						"o"
#else
#define	FTR_GMON						"x"
#endif

#if	!defined(_CNF_GCOV)
#define	FTR_GCOV						"x"
#elif _CNF_GCOV == 0
#define	FTR_GCOV						"o"
#elif _CNF_GCOV == 1
#define	FTR_GCOV						"o(limited)"
#else
#define	FTR_GCOV						"x"
#endif


/*
 *	following are prepared for displaying logo.
 */
static void
__logo_display(int mode)
{
typedef	struct {
	char	*feature;
	char	*state;
} configure_t;

static char	memorysz[32];
static configure_t configure_tbl[] = {
	{"Target OS", FTR_TARGET_OS},
	{"Working on(OS)", FTR_SIM_OS},
	{"Working on(CPU)", FTR_SIM_CPU},
	{"Endian", FTR_ENDIAN},
	{"WishGCR", FTR_WISHGCR},
	{"BackChanel", FTR_BACKCHANEL},
	{"NetBoot", FTR_NETBOOT},
	{"Memory Management", FTR_MEMORY_POOL},
	{"Size of MemoryPool", memorysz},
	{"Transfer mode of TCP/IP", FTR_TRANSMODE},
	{"Heap Checker", FTR_HEAP_CHECK},
	{"Profiler", FTR_GMON},
	{"Coverage", FTR_GCOV},
	{"gpsPlotSetPageParamShm", FTR_API_gpsPlotSetPageParamShm},
	{"gpsColor_get_drawparam2", FTR_API_gpsColor_get_drawparam2},
	{"gpsPlotPrepare", FTR_API_API_gpsPlotPrepare},
#if	defined(_CNF_OS_VXWORKS)
	{"lpux api simulation", FTR_SIMULATE_LPUX_API},
	{"pthread stack control", FTR_PTHREAD_STACKCTRL},
#endif
};
	configure_t	*p, *pe;


	printf("\n");
	printf(LOGO_BANNER);
	printf(LOGO_BLANK);
	printf(LOGO_TITLE, SIMULATOR_SPEC);
	printf(LOGO_BLANK);

	if (mode) {

		printf(LOGO_SEPARATOR);
		printf(LOGO_TITLE, "Your simulator is configured as below.");
		printf(LOGO_BLANK);
		sprintf(memorysz, "%d MB", FTR_MEMORY_POOLSZ / (1024 * 1024));

		p = configure_tbl;
		pe = p + sizeof(configure_tbl) / sizeof(configure_t);

		for (; p < pe; p++)
			printf(LOGO_ITEM, p->feature, p->state);

		printf(LOGO_BLANK);
	}
	printf(LOGO_BANNER);
}

static void
__logo_initialization(void)
{
	printf(LOGO_STANDBY);
	fflush(stdout);
}

static void
__logo_initialization_succeeded(void)
{
	printf(LOGO_SUCCEEDED);
	printf(LOGO_BANNER);
	fflush(stdout);
}

static void
__logo_initialization_failed(int phase)
{
	printf(LOGO_SEPARATOR);
	printf(LOGO_FAILED);
	printf(LOGO_RETRY);
	printf(LOGO_SEPARATOR);
	printf(LOGO_BANNER);
	fflush(stdout);
}
