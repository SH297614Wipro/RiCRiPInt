/*
 *	header for GPS simulator.
 *
 *	Copyright (C) 2006-2008, RICOH Software Inc.
 *	All rights reserved. Proprietary and confidential.
 *
 */


/*
 *	common definition.
 */
#if	!defined(_CNF_BOOL_TYPE) && !defined(bool)
typedef	int				bool;
#endif

#if	!defined(_CNF_UCHAR_TYPE) && !defined(uchar)
typedef	unsigned char	uchar;
#endif

#if !defined(_CNF_USHORT_TYPE) && !defined(ushort)
typedef	unsigned short	ushort;
#endif

#if !defined(_CNF_UINT_TYPE) && !defined(uint)
typedef	unsigned int	uint;
#endif

#if !defined(_CNF_ULONG_TYPE) && !defined(ulong)
typedef	unsigned long	ulong;
#endif

#ifndef	TRUE
#define	TRUE	(1)
#endif

#ifndef	FALSE
#define	FALSE	(0)
#endif

#ifndef	min
#define	min(x, y)	((x) < (y) ? (x) : (y))
#endif

#ifndef	max
#define	max(x, y)	((x) > (y) ? (x) : (y))
#endif


/*
 *	tray information for GPS simulator.
 *
 *	ex. if you want know about these member in detail,
 *		you would get it from the manual of gps_trayinfo_t.
 */
typedef	struct {
	int		id;			/* id of tray.			*/
	int		remain;		/* remains of paper.	*/
	uint	attr;		/* attribute of tray.	*/
	uint	status;		/* status of tray.		*/
	int		p_size;		/* size of paper.(it should be described as RAI.)	*/
	int		p_kind;		/* kind of paper.		*/
	int		p_color;	/* color of paper.		*/
	int		p_length;	/* length of paper.(0.1mm as a unit.)	*/
	int		p_width;	/* width of paper.(0.1mm as a unit.)	*/
	} sim_trayinfo_t;


/*
 *	bin information for GPS simulator.
 *
 *	ex. if you want know about these member in detail,
 *		you would get it from the manual of gps_bininfo_t.
 */
typedef	struct {
	int		id;			/* id of tray.			*/
	int		exist;		/* loading of paper.	*/
	uint	attr;		/* attribute of tray.	*/
	uint	status;		/* status of tray.		*/
	} sim_bininfo_t;


/*
 *	simulation handle of GPS simulator.
 */
#define	STRING_SZ	512		/* size of string or length of file name.		*/
#define	TRAYINFO_SZ	16		/* size of tray information.					*/
#define	BININFO_SZ	16		/* size of bin information.						*/

typedef	struct {
	char	redirect[STRING_SZ];	/* file of redirection of host.			*/
	char	logfilenm[STRING_SZ];	/* file of logging.						*/
	char	variable[STRING_SZ];	/* file of definition of variable.		*/
	char	identifier[STRING_SZ];	/* file of definition of identifier.	*/
	char	outputfilenm[STRING_SZ];/* directory of result(image).			*/
	char	imaq[STRING_SZ];		/* file of IMAQ.						*/
	char	jobname[STRING_SZ];		/* name of job.							*/
	char	bootsvr[STRING_SZ];		/* ip-address of boot-server.			*/

	char	fontrom1[STRING_SZ];	/* file of fontrom.						*/
	char	fontrom2[STRING_SZ];	/* file of fontrom.						*/
	char	viewerappl[STRING_SZ];	/* aplicatioin of viewer.				*/
	char	proof[STRING_SZ];		/* directory of logging.				*/
	char	prefix[STRING_SZ];		/* prefix of result(image).				*/
	char	output[STRING_SZ];		/* directory of result(image).			*/
	char	profile[STRING_SZ];		/* file of profile.						*/
	char	summary[STRING_SZ];		/* file of summary font file.			*/
	char	trayfilenm[STRING_SZ];	/* file of tray configuration.			*/
	char	binfilenm[STRING_SZ];	/* file of bin configuration.			*/

	char	hdd_download[STRING_SZ];/* directory for download(HDD).			*/
	char	hdd_spool[STRING_SZ];	/* directory for spool(HDD).			*/
	char	hdd_temp[STRING_SZ];	/* directory for temporay.				*/
	char	ram_download[STRING_SZ];/* directory for download(RAM).			*/
	char	ram_spool[STRING_SZ];	/* directory for spool(RAM).			*/
	char	sd_download[STRING_SZ];	/* directory for download(SD).			*/

	/* simulation information for gps_sysinfo_t.*/
	uchar	machinecode;			/* associates machinecode.				*/
	uchar	model[STRING_SZ];		/* associates model.					*/
	uchar	maker[STRING_SZ];		/* associates maker.					*/
	ulong	option;					/* associates option.					*/
	ulong	function;				/* associates function.					*/
	uchar	destination;			/* associates destination.				*/
	int		num_tray;				/* associates num_tray.					*/
	int		num_bin;				/* associates num_bin.					*/
	int		disp_lines;				/* associates disp_lines.				*/
	int		disp_columns;			/* associates disp_columns.				*/
	int		punch_unit;				/* associates punch_unit.				*/
	int		punch_hole;				/* associates punch_hole.				*/
	char	machine_number[STRING_SZ];/* associate machine_number.			*/
	ulong	modelcode;				/* associate modelcode.					*/
	ulong	supplemental_modelcode;	/* supplemental modelcode.				*/
	ulong	option_ext_flag;		/* associates option_ext.flag.			*/
	ulong	option_ext_tray;		/* associates option_ext.tray.			*/
	ulong	option_ext_bin;			/* associates option_ext.bin.			*/
	ulong	option_ext_fin;			/* associates option_ext.fin.			*/
	ulong	option_ext_mbox;		/* associates option_ext.mbox.			*/
	ulong	option_ext_misc_prt;	/* associates option_ext.misc_prt.		*/
	ulong	option_ext_misc_non_prt;/* associates option_ext.misc_non_prt.	*/

	/* simulation information for gpsChkDirection2.	*/
	int		direction;				/* return value for gpsChkDirection2.	*/
	int		slantdirection;			/* return value for gpsChkDirection2.	*/

	sim_trayinfo_t	trayinfo[TRAYINFO_SZ];	/* information of tray.			*/
	sim_bininfo_t	bininfo[BININFO_SZ];	/* information of bin.			*/

	int		bitsw[16];				/* value of bitsw.						*/
	int		pdl_id;					/* pdl id of target.					*/
	int		interpreter_id;			/* interpreter id of target.			*/
	int		engine_type;			/* type of engine. 0.mono 1.color 2.twin*/
	int		prof_mode;				/* mode of logging.						*/
	int		font1_type;				/* type of font rom1.					*/
	int		font2_type;				/* type of font rom2.					*/
	int		frame_type;				/* type of frame. 0.big 2.word little.	*/
	int		boundary;				/* boudary bytes of frame.				*/
	ulong	resolution;				/* capability of printable resolution.	*/
	ulong	workmemsz;				/* memory size for PDL.					*/
	ulong	total_ram_size;			/* total ram size.						*/

	int		format;					/* format of image.(0:SunRaster)		*/
	ulong	hinstdrv;				/* instance handle of driver.			*/

	/* debug informatins.	*/
	char	exec_object[STRING_SZ];	/* executable object that has symbols.	*/
	} simhandle_t;

typedef	simhandle_t	gpsconfig_t;


/*
 *	value of variable.
 */
#define	VARTYPE_ID		(0)		/* type is ID.		*/
#define	VARTYPE_INT		(1)		/* type is INT.		*/
#define	VARTYPE_FLOAT	(2)		/* type is FLOAT.	*/
#define	VARTYPE_STR		(3)		/* type is STRING.	*/

typedef	struct {
	int	type;					/* type of variable(0:ID 1:INT 2:FLOAT).	*/
	union {
		int		id_value;		/* value when type is ID.	*/
		int		int_value;		/* value when type is INT.	*/
		float	float_value	;	/* value when type is FLOAT.*/
		char	*str_value;		/* value when type is STR.	*/
	} u;
	} varvalue_t;

/*
 *	tag of variable.
 */
#define	MAX_OF_ID_CNT	128		/* maximum number of ID.	*/

typedef	struct {
	int		id;					/* id of variable.	*/
	int		type;				/* type of variable.(0:ID 1:INT 2:FLOAT 3:STR)*/
	bool	modification;		/* flag of internal modification.	*/
	union {
		int		id_value;		/* value when type is ID.	*/
		int		int_value;		/* value when type is INT.	*/
		float	float_value;	/* value when type is FLOAT.*/
		uchar	*str_value;		/* value when type is STR.	*/
	} u;

	int	enum_count;				/* count of enumuration of ID.	*/
	int	enum_id[MAX_OF_ID_CNT];/* array of enumration of ID.	*/

	union {
		int		id_default;		/* default value when type is ID.	*/
		int		int_default;	/* default value when type is INT.	*/
		float	float_default;	/* default value when type is FLOAT.*/
		uchar	*str_default;	/* default value when type is STR.	*/
	} u_def;
	} variable_t;

/*
 *	list of variable.
 */
#define	MAX_OF_VARIABLE_CNT	256	/* maximum number of variable.	*/ 

typedef	struct {
	int			elements;			/* available number of variables.	*/
	int			max_element;		/* maximum number of variables.		*/
	variable_t	variable[MAX_OF_VARIABLE_CNT];/* area of variable.		*/
	} varlist_t;


/*
 *	tag of identifier.
 */
typedef	struct {
	char	identifier[STRING_SZ];	/* identifier of variable.			*/
	int		value;					/* value of identifier.				*/
	} identifier_t;

/*
 *	list of identifier.
 */
#define	MAX_OF_IDENTIFIER_CNT	768	/* maximum number of identifier.	*/
typedef	struct {
	int		elements;				/* available number of identifier.	*/
	int		max_element;			/* maximum number of identifier.	*/
	identifier_t	ident[MAX_OF_IDENTIFIER_CNT];/* area of identifier.	*/
	} identlist_t;


/*
 *	information of PDL.
 *	
 *	ex. if you want know about these member in detail,
 *		you would get it from the manual of gps_pdlinfo_t.
 */
#define	SHOFTNAME_OF_PDL	3	/* short name length of PDL.			*/
#define	CATEGORY_OF_PDL		7	/* category name length of interpreter.	*/

typedef	struct {
	char	pdl_id;			/* ID of PDL.							*/
	char	interp_id;		/* ID of interpreter.					*/
	char	shortname[SHOFTNAME_OF_PDL+1];/* short name of PDL.		*/
	char	path;			/* ID of path.							*/
	char	category[CATEGORY_OF_PDL+1];/* category name of interpreter.	*/
	} sim_pdlinfo_t;

/*
 *	information of printer.
 *
 *	ex. if you want know about these member in detail,
 *		you would get it from the manual of gps_prtinfo_t.
 */
typedef	struct {
	uchar	default_tray;	/* default input tray.		*/
	ushort	default_bin;	/* default output bin.		*/
	uchar	default_pdl;	/* default PDL(ID of PDL).	*/
	uchar	language;		/* default language.		*/
	} sim_prtinfo_t;

/*
 *	information for search a matching parameter of image.
 */
typedef	struct {
	ulong	fid;	/* id of this parameter(of IMAQ).	*/
	ushort	hdpi;	/* resolution for horizontal.		*/
	ushort	vdpi;	/* resolution for vertical.			*/
	ushort	mode;	/* mode of dither.					*/
	uchar	bit;	/* bits per pixel.					*/
	uchar	prt;	/* mode of printing.				*/
	uchar	id;		/* id of this paramter.				*/
	uchar	fix;	/* flag of updating gamma.			*/
	uchar	paper;	/* paper type.						*/
	ulong	goff[4];/* offset of gamma.					*/
	ulong	doff;	/* offset of dither.				*/
	} sim_imgprm_t;


/*
 *	information for file system.
 */
typedef	struct {
	ulong	f_bsize;	/* fundamental file system block size.	*/
	ulong	f_blocks;	/* total blocks of fs.					*/
	ulong	f_bfree;	/* total free blocks of fs.				*/
	} sim_statfs_t;

/*
 *	information for file.
 */
typedef	struct {
	ulong	st_size;	/* file size.						*/
	ulong	st_blksize;	/* block size of file.				*/
	ulong	st_blocks;	/* blocks of file.					*/
	ulong	st_a_time;	/* accessed time.					*/
	ulong	st_m_time;	/* modified time.					*/
	ulong	st_c_time;	/* created time.					*/
	ulong	st_mode;	/* mode of file.					*/
	} sim_stat_t;

/*
 *	information for gettimeofday.
 */
typedef	struct {
	long	tv_sec;
	long	tv_usec;
	} sim_timeval_t;

typedef	struct {
	int		tz_minuteswest;
	int		tz_dsttime;
	} sim_timezone_t;

/*
 *	definitions for IMAQ file structure.
 *
 *  ex. if you want know about these structure in detail,
 *      you would get it from the manual of gpsColor_XXX().
 */
/*
 *	header of IMAQ file.
 */
typedef	struct {
	ulong	fsize;		/* size of IMAQ file.					*/
	ulong	hsize;		/* size of file header.					*/
	uchar	type;		/* endian of this file. 0:little 1:big.	*/
	uchar	dummy[3];
	char	machine[8];	/* identifier of machine. "RC##XXXX".	*/
	char	ver[12];	/* version of this file. 				*/
	char	date[12];	/* create date of this file.			*/
	char	time[12];	/* create time of this file.			*/
	char	cpy[72];	/* Copyright.							*/
	ulong	common_num;	/* number of header of element.			*/
	uchar	xdpi_num;	/* number of resolution for horizontal.	*/
	uchar	ydpi_num;	/* number of resolution for vertical.	*/
	uchar	bit_num;	/* number of depth.						*/
	uchar	paper_num;	/* number of paper.						*/
	uchar	draw_num;	/* number of draw.						*/
	uchar	color_num;	/* number of color.						*/
	uchar	mode_num;	/* number of mode.						*/
	uchar	varied_num;	/* number of id for head rank.			*/
	ulong	offset;		/* offset of header for each elements.	*/
	ulong	shdmsz;		/* size of shared memory.				*/
	ulong	ext[5];		/* area for extend.						*/
	} imaqhdr_t;

/*
 *	header file for each printing mode.
 */
#define	ELEMENT_TBLINFO_SZ			13
#define	OFFSET_OF_DITHER			1
#define	OFFSET_OF_OUTWARD_GAMMA		2
#define	OFFSET_OF_HOMEWARD_GAMMA	3
#define	OFFSET_OF_DROP_MEASURE		4
#define	OFFSET_OF_LIMITING			5
#define	OFFSET_OF_ED_DATA			6
#define	OFFSET_OF_ED_GAMMA			7
#define	OFFSET_OF_ED_DROP_MEASURE	9
#define	OFFSET_OF_ED_LIMITING		10
#define	OFFSET_OF_BGUCR				11
#define	OFFSET_OF_DUPLEXGAMMA		12

#define	EX_ELEMENT_TBLINFO_SZ		2
#define	EXOFFSET_OF_CALIB			0
#define	EXOFFSET_OF_WISHGCR			1

typedef	struct {
	ulong	id;			/* id of printing mode.					*/
	ulong	fsize;		/* size of this file.					*/
	ulong	hsize;		/* size of this header.					*/
	char	ver[12];	/* string of version.					*/
	ushort	xdpi;		/* resolution for horizontal.			*/
	ushort	ydpi;		/* resolution for vertical.				*/
	uchar	bit;		/* number of bit.						*/
	uchar	paper;		/* type of paper.						*/
	uchar	dit_mode;	/* type of dither.						*/
	uchar	prt_mode;	/* mode of printing.					*/
	uchar	nclr;		/* number of color.						*/
	uchar	flag;		/* flag of updating gamma.				*/
	uchar	dummy[2];

	struct {			/* offset of each element.						*/
		ulong	offset;	/* 0: ACC 1:dither 2: gamma(outward)			*/
		ulong	size;	/* 3: gamma(homeward) 4: drop					*/
		} tblinfo[ELEMENT_TBLINFO_SZ];/* 5: toner limit 6: data for ed	*/
						/* 7: gamma(outward for ed)						*/
						/* 8: gamma(homeward for ed)					*/
						/* 9: drop for ed 10: toner limit for ed		*/
						/* 11: table of BG/UCR 12: gamma(for duplex)	*/
	ulong	ref;		/* ID of refere.								*/

	struct {			/* offset of extra element.						*/
		ulong	offset;	/* 0: calibration 1: wish-gcr.					*/
		ulong	size;
	} tblinfoEX[EX_ELEMENT_TBLINFO_SZ];
	ulong	ext[5];		/* area for extend.								*/
	} imaqelementhdr_t;

/*
 *	header of acc in IMAQ.
 */
typedef	struct {
	ulong	size;		/* size of this tag.							*/
	uchar	color;		/* information of color.(0:K 1:C 2:M 3:Y)		*/
	uchar	ext[3];		/* area for extend.								*/
	uchar	acc_ini_gam[16];/* gamma of factory.						*/
	uchar	acc_target[17];	/* gamma of target.							*/
	ushort	dummy;
	} imaqacc_t;

/*
 *	header of gamma in IMAQ.
 */
typedef	struct {
	ulong	size;		/* size of this tag.							*/
	uchar	color;		/* information of color.(0:K 1:C 2:M 3:Y)		*/
	uchar	varied;		/* id of head rank.								*/
	uchar	rtrip;		/* outward or homeward.(0:outward 1:backward)	*/
	uchar	dummy;
	uchar	g[256];		/* data of gamma.								*/
	} imaqgamma_t;

/*
 *	header of dither in IMAQ.
 */
typedef	struct {
	ulong	size;		/* size of this tag.							*/
	uchar	color;		/* information of color.(0:K 1:C 2:M 3:Y)		*/
	uchar	plane;		/* number of plane.(1 or 3 or 15)				*/
#ifdef USE_FUSER_CTL
	uchar	e_flag;
	uchar	dummy;
#else
	uchar	dummy[2];
#endif
	ushort	x_size;		/* x size of dither.							*/
	ushort	y_size;		/* y size of dither.							*/
	} imaqdither_t;

/*
 *	header of ed in IMAQ.
 */
typedef	struct {
	ulong	size;		/* size of this tag.							*/
	uchar	plane;		/* number of plane.(1 or 3 or 15)				*/
	uchar	dummy[3];
	ushort	mask_x;		/* x size of mask.								*/
	ushort	mask_y;		/* y size of mask.								*/
	uchar	thrdata[3][256];	/* drop table.							*/
	} imaqed_t;

/*
 *	header of drop in IMAQ.
 */
typedef	struct {
	ulong	size;		/* size of this tag.							*/
	uchar	lit[256];	/* convert from logical value to amount of drop.*/
	uchar	inv[256];	/* convert from amount of drop to logical value.*/
	} imaqdrop_t;

/*
 *	header of bg/ucr in IMAQ.
 */
typedef	struct {
	ulong	size;		/* size of this tag.			*/
	uchar	bg[256];	/* table of BG.					*/
	uchar	ucr[256];	/* table of UCR.				*/
	} imaqbgucr_t;

/*
 *	header of toner limitation in IMAQ.
 */
typedef	struct {
	ulong	size;		/* size of this tag.			*/
	ulong	limit[4];/* limitation of toner.(0:photo 1:text 2:fill 3:line.)*/
	} imaqlimit_t;

/*
 *	header of gamma of duplex.
 */
typedef	struct {
	ulong	size;			/* size of this tag.		*/
	uchar	gam_front[4];	/* gamma of front.			*/
	uchar	gam_back[4];	/* gamma of back.			*/
	} imaqdupgamma_t;

/*
 *	header of data for calibration.
 */
typedef	struct {
	ulong	size;		/* size of this tag.				*/
	uchar	color;		/* target color(0:K 1:C 2:M 3:Y)	*/
	uchar	num_point;	/* number of correction points.		*/
	uchar	ext[2];		/* dummy.							*/
	ushort	calib_point[0];	/* variable data of caribation.	*/
	ushort	calib_target[0];/* variable data of target.		*/
	} imaqcalib_t;

/*
 *	header of GCR data.
 */
typedef	struct {
	ulong	size;		/* size of this tag.			*/
	short	CB_bg[4];			/* BG table of CB.		*/
	short	CB_ucr[256][3][3];	/* UCR table of CB.		*/
	short	CG_bg[4];			/* BG table of CG.		*/
	short	CG_ucr[256][3][3];	/* UCR table of CG.		*/
	short	YG_bg[4];			/* BG table of YG.		*/
	short	YG_ucr[256][3][3];	/* UCR table of YG.		*/
	short	MB_bg[4];			/* BG table of MB.		*/
	short	MB_ucr[256][3][3];	/* UCR table of MB.		*/
	short	MR_bg[4];			/* BG table of MR.		*/
	short	MR_ucr[256][3][3];	/* UCR table of MR.		*/
	short	YR_bg[4];			/* BG table of YR.		*/
	short	YR_ucr[256][3][3];	/* UCR table of YR.		*/
	} imaqwishgcr_t;

/*
 *	offset of several data of color on shard memory.
 */
typedef	struct {
	struct {			/* offset of gamma and dither.	*/
		long	gam;	/* offset of gamma.				*/
		long	dit;	/* offset of dither.			*/
		long	ed;		/* offset of data for ed.		*/
		long	ed_gam;	/* offset of gamma for ed.		*/
		} color[4];

	struct {			/* offset of drop.				*/
		ulong	size;	/* size of drop table.			*/
		long	lit;	/* convert from logical value to amount of drop.*/
		long	inv;	/* convert from amount of drop to logical value.*/
		} drop;

	struct {			/* offset of toner limitation.			*/
		ulong	size;	/* size of table for toner limitation.	*/
		long	limit;	/* offset of limit.						*/
		} limit;

	struct {			/* offset of drop table.				*/
		ulong	size;	/* size of table for drop(ED).	*/
		long	lit;	/* convert from logical value to amount of drop.*/
		long	inv;	/* convert from amount of drop to logical value.*/
		} ed_drop;

	struct {			/* offset of toner limitation(ED).		*/
		ulong	size;	/* size of toner limitation.			*/
		long	limit;	/* offset of toner limit.				*/
		} ed_limit;

	struct {			/* offset of table of BG/UCR.			*/
		ulong	size;	/* size of table of BG/UCR.				*/
		long	bg;		/* offset of BG.						*/
		long	ucr;	/* offset of UCR.						*/
		} bgucr;

	struct {			/* offset of gamma for duplex.			*/
		ulong	size;	/* size of gamma for duplex.			*/
		long	gam_front;	/* front page of gamma.				*/
		long	gam_back;	/* back page of gamma.				*/
		} dupgam;

/*
 *	followings has to enable when GPS features WISH-GCR.
 *	becase this structure is related with gps header for application.
 */
#ifdef	_CNF_WISHGCR
	struct {			/* offset of WishGCR.					*/
		ulong	size;	/* size of this tag.					*/
		long	CB_bg;	/* offset of BG table of CB.			*/
		long	CB_ucr;	/* offset of UCR table of CB.			*/
		long	CG_bg;	/* offset of BG table of CG.			*/
		long	CG_ucr;	/* offset of UCR table of CG.			*/
		long	YG_bg;	/* offset of BG table of YG.			*/
		long	YG_ucr;	/* offset of UCR table of YG.			*/
		long	MB_bg;	/* offset of BG table of MB.			*/
		long	MB_ucr;	/* offset of UCR table of MB.			*/
		long	MR_bg;	/* offset of BG table of MR.			*/
		long	MR_ucr;	/* offset of UCR table of MR.			*/
		long	YR_bg;	/* offset of BG table of YR.			*/
		long	YR_ucr;	/* offset of UCR table of YR.			*/
		} wishgcr;
#endif
	} sim_clrdata_t;

/*
 *	tag of gamma on shard memory.
 */
typedef	struct {
	long	gam[9];		/* gamma for outward.					*/
	long	gam2[9];	/* gamma for homeward.					*/
	} sim_clrgam_t;

/*
 *	tag of dither on shared memory.
 */
typedef	struct {
	long	dit;		/* offset of dither.		*/
	ushort	ditsz;		/* size of dither.			*/
	ushort	xsz;		/* xsize of dither.			*/
	ushort	ysz;		/* ysize of dither.			*/
	ushort	thrshpln;	/* number of threshold.		*/
#ifdef USE_FUSER_CTL
	uchar	e_flag_max;
	uchar	e_flag_mid;
#endif
	} sim_clrdit_t;

/*
 *	tag of data of ED on shared memory.
 */
typedef	struct {
	ulong	size;		/* size of this tag.		*/
	ushort	plane;		/* number of plane.			*/
	ushort	mask_x;		/* xsize of mask.			*/
	ushort	mask_y;		/* ysize of mask.			*/
	long	thrdata;	/* offset of threshold.		*/
	long	mask;		/* offset of mask.			*/
	} sim_clred_t;

/*
 *	format of color data on shared memory.
 */
typedef	struct {
	int				size;		/* size of this structure.		*/
	ulong			stat;		/* status						*/
	ushort			dmode;		/* darw mode.					*/
	ushort			numcolor;	/* number of color.				*/
	ulong			off;		/* offset of data(always 0)		*/
	sim_clrdata_t	data[0];	/* several data of color.		*/
	} sim_shdm_t;

/*
 *	format of test print data on shared memory.
 */
typedef	struct {
	int		size;		/* size of this structure.		*/
	int		ext;	
	int		data;
	} sim_shdm2_t;


/*
 *	tag for color maching profile.
 */
#define	SIZE_OF_PROFILE_ATTRIBUTE	27
#define	SIZE_OF_PROFILE_PATH		96
typedef	struct {
	ulong	key;		/* search key of profile.			*/
	uchar	media;		/* media type.						*/
	uchar	attr[SIZE_OF_PROFILE_ATTRIBUTE];/* this member was filled 0.	*/
	char	path[SIZE_OF_PROFILE_PATH];	/* path of profile.	*/
	} sim_profileinfo_t;


/*
 *	tag for shard memory management.
 */
typedef	struct {
	sim_profileinfo_t	*profile;	/* pointer of profile information.		*/
	long				profile_sz;	/* size of profile.						*/
	sim_shdm_t			*imageparam;/* pointer of image adjust information.	*/
	long				imageparam_sz;/* size of imageparam.				*/
	sim_shdm2_t			*testpparam;/* pointer of test print parameter.		*/
	long				testpparam_sz;/* size of testpparam					*/
	uchar				*font1;		/* pointer of font rom.					*/
	long				font1_sz;	/* size of font.						*/
	uchar				*font2;		/* pointer of font rom.					*/
	long				font2_sz;	/* size of font.						*/
	uchar				*summary;	/* pointer of summary font.				*/
	long				summary_sz;	/* size of summary.						*/
	uchar				*pdlinfo;	/* information of gpsGetPdlTable().		*/
	long				pdlinfo_sz;	/* size of pdlinfo.						*/
	uchar				*optionstring;/* startup option of rsh.				*/
	long				optionstring_sz;/* size of optionstring.			*/
	long				num_imgprm;	/* number of image parameter.			*/
	sim_imgprm_t		*imgprm;	/* pointer of search header.			*/

	uchar				*top;		/* top of shard memory.					*/
	long				total_size;	/* size of shard memory.				*/
	uchar				*free;		/* pointer of free block.				*/
	long				free_sz;	/* free size of free block.				*/
	} shrdinfo_t;


/*
 *	tag for product code I/F.
 *		declaration of proto type was omitted.
 *		because gpsxxx structure wants header of gps.
 *		but those delaration of them must becom bottleneck of comile.
 */
typedef	struct _gps_product_codes {
	void	(*pjl_enter_parsing)();	/* notice of start parsing.				*/
	void	(*pjl_get)();			/* notice of reading.					*/
	void	(*pjl_unget)();			/* notice of unreading.					*/
	void	(*pjl_leave_parsing)();	/* notice of end parsing.				*/
	void	(*prm_setsimparam)();	/* notice of fixing parameter.			*/ 
	void	(*frm_setpageparam)();	/* notice of setting page parameter.	*/
	void	(*frm_printpage)();		/* notice of printing page.				*/
	} _gps_products_t;


/*
 *	these macros depend on your machine.
 *
 *	_CNF_ENDIAN_TYPE
 *		0	...	little endian
 *		1	...	big endian
 */
#if	_CNF_ENDIAN_TYPE == 0
/*
 *	get endian type of current system.
 */
#define	Curendian()		(0)

/*
 *	convert little endian to little endian.
 *
 *	following is prepared for conversion of network.
 */
#define	Ldepend(val)	(ulong)(val)
#define	Idepend(val)	(uint)(val)
#define	Sdepend(val)	(ushort)(val)
#else
/*
 *	get endian type of current system.
 */
#define	Curendian()		(1)

/*
 *	convert little endian to big endian.
 *
 *	following is prepared for conversion of network.
 */
#define	Ldepend(val)	((((ulong)(val) >> 24) & 0xff) |\
						(((ulong)(val) >> 8) & 0xff00) |\
						(((ulong)(val) << 8) & 0xff0000) |\
						(((ulong)(val) << 24) & 0xff000000))

#define	Idepend(val)	((((ulong)(val) >> 24) & 0xff) |\
						(((ulong)(val) >> 8) & 0xff00) |\
						(((ulong)(val) << 8) & 0xff0000) |\
						(((ulong)(val) << 24) & 0xff000000))

#define	Sdepend(val)	((((ushort)(val) >> 8) & 0xff) |\
						(((ushort)(val) << 8) & 0xff00))
#endif


/*
 *	following describe configuration of defaults, directory and file name.
 *	(for .gpsconf)
 */
#define	_CNF_CONF_FILE			".gpsconf"		/* gps configuration file.	*/
#define	_CNF_DEF_PROOF_DIR		"./prof"		/* directory of logging.	*/
#define	_CNF_DEF_OUTPUT_DIR		"./output"		/* directory of image file.	*/
#define	_CNF_DEF_PREFIX			"result"		/* prefix of image file.	*/
#define	_CNF_DEF_ENVIRONMENT	"07a.env"		/* environment file.		*/
#define	_CNF_DEF_IDENTIFIER		"07a.ident"		/* identifier file.			*/
#define	_CNF_DEF_PROFILE		"./gps.prof"	/* colormatching profile.	*/
#define	_CNF_DEF_IMAQ			"./imaq"		/* IMAQ file.				*/
#define	_CNF_DEF_HDD_DOWNLOAD	"./hdd_download"/* directory of HDD download.*/
#define	_CNF_DEF_HDD_SPOOL		"./hdd_spool"	/* directory of HDD spool.	*/
#define	_CNF_DEF_RAM_DOWNLOAD	"./ram_download"/* directory of RAM download.*/
#define	_CNF_DEF_RAM_SPOOL		"./ram_spool"	/* directory of RAM spool.	*/
#define	_CNF_DEF_HDD_TEMP		"./hdd_temp"	/* directory of HDD temp.	*/
#define	_CNF_DEF_SD_DOWNLOAD	"./hdd_download"/* directory of SD download.*/
#define	_CNF_DEF_MODEL			"XXXXX"			/* name of model.			*/
#define	_CNF_DEF_MAKER			"RICOH"			/* name of maker.			*/
#define	_CNF_DEF_DISP_LINES		2				/* lines of panel.			*/
#define	_CNF_DEF_DISP_COLUMNS	16				/* columns of panel.		*/
#define	_CNF_DEF_TOTAL_RAM_SIZE	0x1000000		/* 32MB.					*/
#define	_CNF_DEF_RESOLUTION		0x40			/* 600dpi 1bit.				*/
#define	_CNF_DEF_MODELCODE		0x10			/* model code.				*/
#define	_CNF_DEF_MACHINE_NUMBER	"00000000"		/* model number.			*/
#define	_CNF_DEF_INPUT_TRAY		""				/* name of tray.			*/
#define	_CNF_DEF_OUTPUT_BIN		""				/* name of bin.				*/
#define	_CNF_DEF_FONTROM1		""				/* file name of font rom.	*/
#define	_CNF_DEF_FONTROM2		""				/* file name of font rom.	*/
#define	_CNF_DEF_SUMMARY		""				/* file name of summary.	*/
#define	_CNF_DEF_VIEWER			"xv"			/* default viewer.			*/
#define	_CNF_DEF_GPSWKMALLOC	0x800000		/* 8MB.						*/
#define	_CNF_DEF_DIRECTION		0x01			/* for gpsChkDirection2()	*/
#define	_CNF_DEF_SLANTDIRECTION	0x01			/* for gpsChkDirection2()	*/
#define	_CNF_DEF_FONTROM1_TYPE	1				/* fontrom type(RPCS).		*/
#define	_CNF_DEF_FONTROM2_TYPE	1				/* fontrom type(RPCS).		*/
#define	_CNF_DEF_FRAME_TYPE		0				/* 0:big 2:word little.		*/
#define	_CNF_DEF_BOUNDARY		4				/* default : 4byte boundary.*/
#define	_CNF_DEF_SUPPLEMENTAL_MODELCODE		0x100/* supplemental model code.*/

/*
 *	following describe configuration of defaults, directory and file name.
 *	(for input tray.)
 */
#define	_CNF_DEF_TRAY_REMAIN	100				/* remain of paper.			*/
#define	_CNF_DEF_TRAY_ATTR		0				/* attribute of tray.		*/
#define	_CNF_DEF_TRAY_STATUS	0				/* status of tray.			*/
#define	_CNF_DEF_TRAY_P_SIZE	133				/* A4.						*/
#define	_CNF_DEF_TRAY_P_KIND	0				/* plane.					*/
#define	_CNF_DEF_TRAY_P_COLOR	0				/* white.					*/
#define	_CNF_DEF_TRAY_P_LENGTH	2970			/* length of A4				*/
#define	_CNF_DEF_TRAY_P_WIDTH	2100			/* width of A4				*/

/*
 *	following describe configuration of defaults, directory and file name.
 *	(for input tray.)
 */
#define	_CNF_DEF_BIN_EXIST			0
#define	_CNF_DEF_BIN_ATTR			0
#define	_CNF_DEF_BIN_STATUS			0

/*
 *	following describe the definitions of driver APIs.
 */
extern ulong	__os_createdrv(void);
extern ulong	__os_alloc(ulong, size_t);
extern void		__os_free(ulong, ulong);
extern void		*__os_lock(ulong, ulong);
extern void		__os_unlock(ulong, ulong);

extern ulong	__os_initnetwork(ulong, int, int);
extern ulong	__os_initclient(ulong, char *, int, int);
extern ulong	__os_accept(ulong, ulong);
extern void		__os_disconnect(ulong, ulong);
extern int		__os_send(ulong, ulong, char *, size_t);
extern int		__os_recv(ulong, ulong, char *, size_t);

extern ulong	__os_createts(ulong, void *(*)(void *), void *);
extern void		__os_exitts(ulong, ulong);
extern void		__os_joints(ulong, ulong);
extern void		__os_killts(ulong, ulong);

extern ulong	__os_createsem(ulong, void*);
extern void		__os_locksem(ulong, ulong);
extern void		__os_unlocksem(ulong, ulong);
extern void		__os_destroysem(ulong, ulong);
extern ulong	__os_createcond(ulong);
extern void		__os_waitcond(ulong, ulong, ulong);
extern void		__os_signalcond(ulong, ulong);
extern void		__os_destroycond(ulong, ulong);
extern int		__os_exec(ulong, char *, char *[]);

extern ulong	__os_createthread(ulong, ulong, void *(*)(void *), void *);
extern void		__os_jointhread(ulong, ulong, void **);
extern void		__os_cancelthread(ulong, ulong);
extern int		__os_trylocksem(ulong, ulong);
extern void		__os_broadcastcond(ulong, ulong);
extern int		__os_timedwaitcond(ulong, ulong, ulong, void *);
extern ulong	__os_threadself(ulong);
extern void		__os_suspend_thread(ulong, ulong);
extern void		__os_continue_thread(ulong, ulong);

extern ulong	__os_createattr(ulong);
extern void		__os_destroyattr(ulong, ulong);
extern void		__os_attr_setstacksize(ulong, ulong, int);
extern void		__os_attr_setdetachstate(ulong, ulong, int);
extern void		__os_attr_setschedparam(ulong, ulong, int);
extern void		__os_attr_getschedparam(ulong, ulong, int *);

extern void		__os_resettic(ulong);
extern void		__os_gettic(ulong, ulong *, ulong *,
						ulong *, ulong *, ulong *, ulong *);

extern void		__os_resumevar(void);

/*
 *	following describe the definitions of profile APIs.
 */
extern int		__prf_getprofilestring(simhandle_t *, char *, char *, char *);
extern int		__prf_getprofileint(simhandle_t *, char *, char *, int *);
extern int		__prf_getprofilesubstring(simhandle_t *, char *, char *, int);
extern int		__prf_getprofiledelimitstring(simhandle_t *,
					char *, char *, int, char*);
extern void		__prf_stringtoint(simhandle_t *, char *, int *);
extern ulong	__prf_fopen(simhandle_t *, char *, char *);
extern char		*__prf_fgets(simhandle_t *, char *, int, ulong);
extern ulong	__prf_fclose(simhandle_t *, ulong);

extern void		__prf_resumevar(void);


/*
 *	following describe the definitions of controling network APIs.
 */
extern int		_net_initialize(simhandle_t *);
extern void		_net_terminate(simhandle_t *);
extern int		_net_initclient(simhandle_t *, char *);
extern ulong	_net_initrpc(simhandle_t *, char *);
extern int		_net_hangonjob(simhandle_t *, char *);
extern int		_net_recvjob(simhandle_t *, char *, int);
extern int		_net_resetjob(simhandle_t *);
extern int		_net_panelsend(simhandle_t *, char *, int);
extern int		_net_panelrecv(simhandle_t *, char *, int);
extern int		_net_sendjob(simhandle_t *, char *, int);
extern int		_net_sendclient(simhandle_t *, char *, int);
extern int		_net_recvclient(simhandle_t *, char *, int);
extern void		_net_shutdownclient(simhandle_t *);
extern int		_net_sendrpc(simhandle_t *, ulong, void *, int);
extern int		_net_recvrpc(simhandle_t *, ulong, void *, int);
extern void		_net_shutdownrpc(simhandle_t *, ulong);
extern void		_net_resumevar(void);


/*
 *	following describe the definitions of controling file I/O APIs.
 */
extern int		_fl_initialize(simhandle_t *);
extern void		_fl_terminate(simhandle_t *);
extern int		_fl_open(simhandle_t *, char *, char *mode);
extern int		_fl_readplane(uchar *, int, int);
extern int 		_fl_writeplane(uchar *, int, int);
extern int		_fl_write(simhandle_t *,int, uchar **, int, int, int, int, int);
extern void		_fl_close(simhandle_t *);
extern void		_fl_resumevar(void);


/*
 *	following describe the definitions of controling log APIs.
 */
#define	_LOG_FILE	(1)		/* write to file.			*/
#define	_LOG_SCRN	(2)		/* write to screen.			*/
#define	_LOG_SYS	(4)		/* write system message.	*/

extern int		_log_initialize(simhandle_t *);
extern void		_log_terminate(simhandle_t *);
extern void		_log_writestring(simhandle_t *, char *, int);
extern void		_log_resumevar(void);


/*
 *	following describe the definitions of controling running mode APIs.
 */
#define	OPT_EXEC_AND_STAY		0x00000000
#define	OPT_EXEC_ONCE			0x00000001
#define	OPT_EXEC_VIEWER			0x80000000
#define	OPT_EXEC_NOFILE			0x40000000
#define	OPT_EXEC_LAP			0x20000000
#define	OPT_EXEC_NOLOGFILE		0x10000000
#define	OPT_EXEC_NOSYSLOGFILE	0x08000000

extern int		_opt_setrunmode(simhandle_t *, int);
extern int		_opt_getrunmode(simhandle_t *);
extern void		_opt_resumevar(void);


/*
 *	following describe the definitions of host I/F APIs.
 */
extern int		_host_initialize(simhandle_t *);
extern void		_host_terminate(simhandle_t *);
extern void		_host_reset(simhandle_t *);
extern int		_host_read(simhandle_t *, char *, int);
extern int		_host_unread(simhandle_t *, char *, int);
extern int		_host_write(simhandle_t *, char *, int);
extern void		_host_resumevar(void);


/*
 *	following describe the definitions of controling configuration APIs.
 */
extern int			_cnf_initialize(simhandle_t *);
extern void			_cnf_terminate(simhandle_t *);
extern int			_cnf_reconfig(simhandle_t *);
extern gpsconfig_t	*_cnf_getinfo(simhandle_t *);
extern int			_cnf_configtray(simhandle_t *);
extern int			_cnf_configbin(simhandle_t *);
extern void			_cnf_resumevar(void);


/*
 *	following describe the definitions of managing variable APIs.
 */
extern int			_var_initialize(simhandle_t *);
extern void			_var_terminate(simhandle_t *);
extern int			_var_loadsymbols(simhandle_t *, char *, char *);
extern int			_var_enumerate(simhandle_t *, char *, char *, int);
extern int			_var_getbyname(simhandle_t *, char *, varvalue_t *);
extern int			_var_getbyvalue(simhandle_t *, int, varvalue_t *);
extern int			_var_setbyname(simhandle_t *, char *, char *);
extern int			_var_setbyvalue(simhandle_t *, int, int *);
extern int			_var_getcount(simhandle_t *);
extern int			_var_getdefaultbyname(simhandle_t *, char *, varvalue_t *);
extern int			_var_getdefaultbyvalue(simhandle_t *, int, varvalue_t *);
extern int			_var_getbyname(simhandle_t *, char *, varvalue_t *);
extern int			_var_setdefaultbyname(simhandle_t *, char *, char *);
extern int			_var_setdefaultbyvalue(simhandle_t *, int, int *);
extern void			_var_reset(simhandle_t *);
extern int			_var_getinfobyvalue(simhandle_t *, int, variable_t *);
extern int			_var_getinfobyname(simhandle_t *, char *, variable_t *);
extern void			_var_resumevar(void);


/*
 *	following describe the definitions of managing variable APIs.
 */
extern int			_img_initialize(simhandle_t *hsim);
extern void			_img_terminate(simhandle_t *hsim);
extern int			_img_createpage(simhandle_t	*, int, int, int,
							int, int, int, int, int *, int);
extern uchar		*_img_getband(simhandle_t *, int, int);
extern int			_img_releaseband(simhandle_t *, int, int);
extern int			_img_record(simhandle_t *);
extern void			_img_resumevar(void);


/*
 *	following describe the definitions of controling event APIs.
 */
#define	EVTSIM_REQ_CANCEL		0
#define	EVTSIM_NOTIFY_OFFLINE	1
#define	EVTSIM_NOTIFY_ONLINE	2
#define	EVTSIM_REQ_EXIT			3
#define	EVTSIM_REQ_TESTPRINT	4
#define	EVTSIM_GAMREQ			5
#define	EVTSIM_REQ_EXITPAPER	6
#define	EVTSIM_REQ_PDLFONTCOUNT	7
#define	EVTSIM_REQ_PAUSE		8
#define	EVTSIM_REQ_RESUME		9

extern int			_evt_initialize(simhandle_t *, int (*)(simhandle_t *, int));
extern void			_evt_terminate(simhandle_t *);
extern int			_evt_online(simhandle_t *);
extern int			_evt_jobstart(simhandle_t *);
extern int			_evt_jobend(simhandle_t *);
extern int			_evt_send(simhandle_t *, int);
extern void			_evt_resumevar(void);


/*
 *	following describe the definitions of controling panel APIs.
 */
extern int			_pnl_initialize(simhandle_t *);
extern void			_pnl_terminate(simhandle_t *);
extern void			_pnl_resumevar(void);


/*
 *	following describe the definitions of paerser of PJL API.
 */
extern int			_pjl_parse(simhandle_t *);
extern void			_pjl_resumevar(void);


/*
 *	following describe the definitions of shard memory APIs.
 */
/* followings argment of _shrd_loadfont().these specifies font rom.	*/
#define	FONT_ROM1		0	/* rom cartridge No.1.		*/
#define	FONT_ROM2		1	/* rom cartridge No.2.		*/
#define	FONT_SUMMARY	10	/* rom for summary.			*/

extern int			_shrd_initialize(simhandle_t *, uchar **, shrdinfo_t *);
extern void			_shrd_terminate(simhandle_t *);
extern int			_shrd_loadprofile(simhandle_t *, uchar *, long, uchar **);
extern int			_shrd_loadimaq(simhandle_t *, uchar *, long, uchar **,
							sim_imgprm_t **, long *);
extern int			_shrd_loadfont(simhandle_t *, uchar *, long, uchar **, int);
extern void			_shrd_resumevar(void);

/*
 *	following describe the definition of rpc APIs.
 */
extern int			_rpc_initialize(simhandle_t *);
extern void			_rpc_terminate(simhandle_t *);
extern ulong		_rpc_fopen(simhandle_t *, char *, char *);
extern size_t		_rpc_fread(simhandle_t *, void *, size_t, size_t, ulong);
extern size_t		_rpc_fwrite(simhandle_t *, void *, size_t, size_t, ulong);
extern int			_rpc_fseek(simhandle_t *, ulong, long, int);
extern long			_rpc_ftell(simhandle_t *, ulong);
extern char			*_rpc_fgets(simhandle_t *, char *, int, ulong);
#if	defined(_CNF_OS_SOLARIS) || defined(_CNF_OS_VXWORKS)
extern int			_rpc_fscanf();
#else
extern int			_rpc_fscanf(simhandle_t *, ulong, char *, ...);
#endif
extern int			_rpc_fprintf(simhandle_t *, ulong, char *, ...);
extern int			_rpc_vfprintf(simhandle_t *, ulong, char *, void *);
extern int			_rpc_fflush(simhandle_t *, ulong);
extern int			_rpc_putc(simhandle_t *, int, ulong);
extern int			_rpc_stat(simhandle_t *, char *, sim_stat_t *);
extern int			_rpc_statfs(simhandle_t *, char *, sim_statfs_t *);
extern int			_rpc_exec(simhandle_t *, char *, char *[]);
extern int			_rpc_remove(simhandle_t *, char *);
extern void			_rpc_resumevar(void);

/*
 *	following describe the definitions of gps APIs.
 */
extern simhandle_t		*__gps_getsimhandle(void);
extern void				__gps_shutdown(void);
extern void				__gps_resumevar(void);
extern void				__stub_resumevar(void);

/*
 *	followings describe the definition of memory manger APIs.
 *		this APIs will be used when you specify _CNF_MEMORY_POOL
 */
extern ulong		__lm_alloc(int);
extern void			__lm_shrink(ulong, int);
extern void			*__lm_lock(ulong);
extern void			__lm_unlock(ulong);
extern void			__lm_free(ulong);
extern ulong		__lm_biggest(void);
extern ulong		__lm_freesize(void);
extern void			__lm_gcorrect(void);
extern void			__lm_resumevar(void);
extern void			__sm_init(void *, int);
extern void			*__sm_alloc(int);
extern void			__sm_free(void *);
extern ulong		__sm_biggest(void);
extern ulong		__sm_freesize(void);
extern ulong		__sm_biggest(void);
extern void			__sm_resumevar(void);
extern void			__sm_resumevar(void);

/*
 *	following describe the definitions of debug APIs.
 */
extern int			_simdbg_initialize(simhandle_t *);
extern int			_simdbg_terminate(simhandle_t *);
extern void			_simdbg_setmode(simhandle_t *, bool);
extern ulong		_simdbg_setcallback(simhandle_t *, void (*)(void));
extern int			_simdbg_setpoint(simhandle_t *, long);
extern int			_simdbg_clearpoint(simhandle_t *);
extern void			_simdbg_break(simhandle_t *);
extern void			_simdbg_run(simhandle_t *);
extern void			_simdbg_recordhost(simhandle_t *, uchar *, int, long);
extern bool			_simdbg_isreached(simhandle_t *, long);
extern bool			_simdbg_isbreaking(simhandle_t *);
extern void			_simdbg_send(simhandle_t *, char *);
extern int			_simdbg_initheapchk(simhandle_t *, char *);
extern int			_simdbg_heapchkalloc(simhandle_t *, void *, int);
extern int			_simdbg_heapchkalloc(simhandle_t *, void *, int);
extern int			_simdbg_heapchkfree(simhandle_t *, void *);
extern int			_simdbg_heapchkrealloc(simhandle_t *, void *, void *, int);
extern void			_simdbg_heapchkremains(simhandle_t *);
extern void			_simdbg_heapchkdiscard(simhandle_t *, void *p, int);
extern void			_simdbg_termheapchk(simhandle_t *);
extern void			_simdbg_probestartjob(simhandle_t *);
extern void			_simdbg_probeendpage(simhandle_t *);
extern void			_simdbg_probeendjob(simhandle_t *);
extern void			_simdbg_elapsedtime(simhandle_t *, char *);
extern void			_simdbg_setentry(int (*)(int, char **), int, char **);
extern void			_simdbg_dohotstart(void);
extern void			_simdbg_hotstart(void);
extern int			_simdbg_savevar(void *, int);
extern void			_simdbg_resumevar(void);
extern void			_simdbg_doexit(simhandle_t *);
extern void			_simdbg_registerexit(simhandle_t *, ulong);
extern void			_simdbg_deregisterexit(simhandle_t *, ulong);

/*
 *	followings describe the definition of gmon APIs.
 */
extern int			__gmon_initialize(simhandle_t *);
extern int			__gmon_terminate(simhandle_t *);
extern int			__gmon_setup(simhandle_t *, int, char *, int, int);
extern int			__gmon_kprofsetup(simhandle_t *, char *, int, int);
extern void			__gmon_startjob(simhandle_t *);
extern void			__gmon_outputpage(simhandle_t *);
extern void			__gmon_endjob(simhandle_t *);
extern void			__gmon_moncontrol(simhandle_t *, int);

/*
 *	followings describe the definition of gcov APIs.
 */
extern int			___gcov_initialize(simhandle_t *);
extern int			___gcov_terminate(simhandle_t *);
extern int			___gcov_profreset(simhandle_t *);
extern int			___gcov_profsetup(simhandle_t *, int, int, int);
extern int			___gcov_profflush(simhandle_t *);
extern void			___gcov_profstartjob(simhandle_t *);
extern void			___gcov_profoutputpage(simhandle_t *);
extern void			___gcov_profendjob(simhandle_t *);
extern int			___gcov_setroot(simhandle_t *, char *);
extern char *		___gcov_getroot(simhandle_t *);
extern void			___gcov_profexit(simhandle_t *);

/*
 *	following describe the definitions of debug APIs(for printer application).
 */
extern void			__syscall__setdbgmode(bool);
extern void			__syscall__dbgbreak(void);
extern ulong		__syscall__setdbgcallback(void (*func)(void));
extern int			__syscall__initheapchk(char *);
extern int			__syscall__termheapchk(void);
extern int			__syscall__heapchkalloc(void *, int);
extern int			__syscall__heapchkfree(void *);
extern int			__syscall__heapchkremains(void);
extern int			__syscall__heapchkdiscard(void *, int);
extern void			*__syscall__malloc(size_t);
extern void			__syscall__free(void *);
extern void			*__syscall__calloc(size_t, size_t);
extern void			*__syscall__realloc(void *, size_t);
extern void			__syscall__elapsedtime(char *);


/*
 *	following describe the definition of products code APIs(for application).
 */
extern _gps_products_t	*_gps_setupproducts(simhandle_t *, _gps_products_t *);

/*
 *	following describe the definition of products code APIs.
 */
extern void			__prd_pjl_enter_parsing(void);
extern void			__prd_pjl_get(uchar *, int);
extern void			__prd_pjl_unget(uchar *, int);
extern void			__prd_pjl_leave_parsing(void);
extern void			__prd_prm_setsimparam(simhandle_t *);
extern void			__prd_frm_setpageparam(int, void *);
extern void			__prd_frm_printpage(int, int, int, int, int,
							int, int, int, uchar *[]);
extern void			__prd_resumevar(void);

/*
 *	followings describe the definition of __syscall
 *		to use application and this simulator.
 */
extern void			__syscall__cleanupjmpbuf(void);
extern int			__syscall__doexit(void);
extern int			__syscall__exit(int);
