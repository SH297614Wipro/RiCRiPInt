/******************************************************
 * $Id$
 *
 * Copyright (C) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : ujobparam.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 18 Oct 1999: Created.
 *	 $Log$
 *
 ******************************************************/
#ifndef _GPS_UJOBPARAM_H_
#define	_GPS_UJOBPARAM_H_

/*
 *	kind
 */
#define	GPS_UJOB_UNDEF			(0)	/* undefined job */
#define	GPS_UJOB_PJL			(1)	/* PJL job (JOB/EOJ) */
#define	GPS_UJOB_RPDL			(2)	/* RPDL job (job command) */
#define	GPS_UJOB_HEXDUMP		(11)	/* HEXDUMP */
#define	GPS_UJOB_TESTPRINT		(12)	/* TESTPRINT */
#define	GPS_UJOB_TESTPRINT_INTERP	(13)	/* TESTPRINT(interp) */
#define	GPS_UJOB_PROOF			(14)	/* PROOF (internal use) */
#define	GPS_UJOB_SECURE			(15)	/* SECURE (internal use) */
#define	GPS_UJOB_CARDSAVE		(16)	/* CARDSAVE */
#define	GPS_UJOB_KEEP			(17)	/* KEEP (internal use) */
#define	GPS_UJOB_PAUSE			(18)	/* PAUSE (internal use) */

#define	GPS_UJOB_IPDS			(3)	/* IPDS JOB */

/* === 上記 kind を追加したらこの項目も見直すこと ===
   パネルからの COPIES, STAPLE, PUNCH 等の設定を無視するジョブの種類(GPS内のみで使用) */
#define GPS_UJOB_IGNORE_PENV_KIND_BIT	((1<<GPS_UJOB_HEXDUMP)|(1<<GPS_UJOB_TESTPRINT)|(1<<GPS_UJOB_TESTPRINT_INTERP))

/*
 *	ujob attr
 */
#define	GPS_UJOB_ATTR_NAME	(1 << 0)
#define	GPS_MAX_UJOB_ATTR_NAME_LEN	80

typedef struct gps_ujob_attr {
	unsigned long	flag;
	char	name[GPS_MAX_UJOB_ATTR_NAME_LEN + 1];
} gps_ujob_attr_t;

/*
 *	flag
 */
#define	GPS_UPARAM_DATE			(1 << 0)
#define	GPS_UPARAM_TIME			(1 << 1)
#define	GPS_UPARAM_TRACKID		(1 << 2)
#define	GPS_UPARAM_USERCODE		(1 << 3)
#define	GPS_UPARAM_USERID		(1 << 4)
#define	GPS_UPARAM_JOBID		(1 << 5)
#define	GPS_UPARAM_JOBPASSWORD		(1 << 6)
#define	GPS_UPARAM_DISPCHARSET		(1 << 7)
#define	GPS_UPARAM_HOSTCHARSET		(1 << 8)
#define	GPS_UPARAM_HOSTLOGINNAME	(1 << 9)
#define	GPS_UPARAM_HOSTNAME		(1 << 10)
#define	GPS_UPARAM_HOSTPORTNAME		(1 << 11)
#define	GPS_UPARAM_HOSTPRINTERNAME	(1 << 12)
#define	GPS_UPARAM_PROOFJOB		(1 << 13)
#define	GPS_UPARAM_SECUREJOB		(1 << 14)
#define	GPS_UPARAM_JOBNAME		(1 << 15)
#define	GPS_UPARAM_OWNERID		(1 << 16)
#define	GPS_UPARAM_PRINTINFO		(1 << 17)
#define	GPS_UPARAM_AUTHUSERNAME		(1 << 18)
#define	GPS_UPARAM_AUTHPASSWORD		(1 << 19)
#define	GPS_UPARAM_AUTHENCRYPTMETHOD	(1 << 20)
#define	GPS_UPARAM_AUTHENCRYPTSETTING	(1 << 21)
#define	GPS_UPARAM_JOBPASSWORD_EXT	(1 << 22)
#define	GPS_UPARAM_PAUSEDJOB		(1 << 23)
#define	GPS_UPARAM_FORMJOB		(1 << 24)
#define	GPS_UPARAM_AUTHUSERNAMECHARSET	(1 << 25)
#define	GPS_UPARAM_AUTHPASSWORDCHARSET	(1 << 26)
#define	GPS_UPARAM_NDISPCHARSET		(1 << 27)
#define	GPS_UPARAM_NHOSTCHARSET		(1 << 28)
#define	GPS_UPARAM_BILLINGCODE		(1 << 29)
#define	GPS_UPARAM_PRINTAPPOINTEDTIME	(1 << 30)	/* 印刷時刻指定(11A～) */
#define	GPS_UPARAM_EXT2			(1 << 31)

/*
 *	flag2
 */
#define	GPS_UPARAM_DRIVERKINDINFO		(1 << 0)	/* 利用ドライバ種別(11A～) */
#define	GPS_UPARAM_FOLDERNUMBER		(1 << 1)
#define	GPS_UPARAM_FOLDERPASSWORD		(1 << 2)
#define	GPS_UPARAM_EXT3			(1 << 31)

/*
 *	max length
 */
#define	GPS_MAX_UPARAM_DATE_LEN			10
#define	GPS_MAX_UPARAM_TIME_LEN			8
#define	GPS_MAX_UPARAM_TRACKID_LEN		20
#define	GPS_MAX_UPARAM_USERCODE_LEN		8
#define	GPS_MAX_UPARAM_USERID_LEN		8
#define	GPS_MAX_UPARAM_JOBID_LEN		20
#define	GPS_MAX_UPARAM_JOBPASSWORD_LEN		4
#define	GPS_MAX_UPARAM_DISPCHARSET_LEN		63
#define	GPS_MAX_UPARAM_HOSTCHARSET_LEN		63
#define	GPS_MAX_UPARAM_HOSTLOGINNAME_LEN	20
#define	GPS_MAX_UPARAM_HOSTNAME_LEN		63
#define	GPS_MAX_UPARAM_HOSTPORTNAME_LEN		64
#define	GPS_MAX_UPARAM_HOSTPRINTERNAME_LEN	64
#define	GPS_MAX_UPARAM_JOBNAME_LEN		232
#define	GPS_MAX_UPARAM_OWNERID_LEN		20
#define	GPS_MAX_UPARAM_PRINTINFO_LEN		230
#define	GPS_MAX_UPARAM_AUTHUSERNAME_LEN		217
#define	GPS_MAX_UPARAM_AUTHPASSWORD_LEN		217
#define	GPS_MAX_UPARAM_JOBPASSWORD_EXT_LEN	8
#define	GPS_MAX_UPARAM_BILLINGCODE_LEN		32
#define	GPS_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN	5	/* 印刷時刻指定(11A～) */
#define	GPS_MAX_UPARAM_FOLDERPASSWORD_LEN		8

/*
 *	利用ドライバ種別
 */
#define	GPS_UPARAM_DRIVERKINDINFO_INBOX			(1)
#define	GPS_UPARAM_DRIVERKINDINFO_PCL6			(2)
#define	GPS_UPARAM_DRIVERKINDINFO_PCL6UD		(3)
#define	GPS_UPARAM_DRIVERKINDINFO_PCL6UDGENERIC	(4)
#define	GPS_UPARAM_DRIVERKINDINFO_PS			(5)
#define	GPS_UPARAM_DRIVERKINDINFO_PSUD			(6)
#define	GPS_UPARAM_DRIVERKINDINFO_PSUDGENERIC	(7)
#define	GPS_UPARAM_DRIVERKINDINFO_RPCSBASIC		(8)
#define	GPS_UPARAM_DRIVERKINDINFO_RPCSXPS		(9)
#define	GPS_UPARAM_DRIVERKINDINFO_RPCS			(10)

/*
 *	gps_ujobparam_var_t
 */
typedef struct gps_ujobparam_var {
	unsigned long	flag;
	union {
		unsigned char	date[GPS_MAX_UPARAM_DATE_LEN + 1];
		unsigned char	time[GPS_MAX_UPARAM_TIME_LEN + 1];
		unsigned char	trackid[GPS_MAX_UPARAM_TRACKID_LEN + 1];
		unsigned char	usercode[GPS_MAX_UPARAM_USERCODE_LEN + 1];
		unsigned char	billingcode[GPS_MAX_UPARAM_BILLINGCODE_LEN + 2];
		unsigned char	userid[GPS_MAX_UPARAM_USERID_LEN + 1];
		unsigned char	jobid[GPS_MAX_UPARAM_JOBID_LEN + 1];
		unsigned char	jobpassword[GPS_MAX_UPARAM_JOBPASSWORD_LEN + 1];
		unsigned char	dispcharset[GPS_MAX_UPARAM_DISPCHARSET_LEN + 1];
		unsigned char	hostcharset[GPS_MAX_UPARAM_HOSTCHARSET_LEN + 1];
		unsigned char	hostloginname[GPS_MAX_UPARAM_HOSTLOGINNAME_LEN + 1];
		unsigned char	hostname[GPS_MAX_UPARAM_HOSTNAME_LEN + 1];
		unsigned char	hostportname[GPS_MAX_UPARAM_HOSTPORTNAME_LEN + 1];
		unsigned char	hostprintername[GPS_MAX_UPARAM_HOSTPRINTERNAME_LEN + 1];
		unsigned char	jobname[GPS_MAX_UPARAM_JOBNAME_LEN + 1];
		unsigned char	ownerid[GPS_MAX_UPARAM_OWNERID_LEN + 1];
		unsigned char	printinfo[GPS_MAX_UPARAM_PRINTINFO_LEN + 1];
		unsigned char	authusername[GPS_MAX_UPARAM_AUTHUSERNAME_LEN + 1];
		unsigned char	authpassword[GPS_MAX_UPARAM_AUTHPASSWORD_LEN + 1];
		int		authencryptmethod;
		int		authencryptsetting;
		unsigned char	jobpassword_ext[GPS_MAX_UPARAM_JOBPASSWORD_EXT_LEN + 1];
		short		authusernamecharset;
		short		authpasswordcharset;
		short		ndispcharset;
		short		nhostcharset;
		unsigned char	printappointedtime[GPS_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN + 1];	/* 印刷時刻指定(11A～) */
		int		driverkindinfo;								/* 利用ドライバ種別(11A～) */
		unsigned short  foldernumber;        /* フォルダ番号(12A～) */
		unsigned char	folderpassword[GPS_MAX_UPARAM_FOLDERPASSWORD_LEN + 1]; /* フォルダパスワード(12A～) */
		unsigned char	dummy[240];
	} up;

	unsigned long	flag2;
} gps_ujobparam_var_t;

#define	up_date			up.date
#define	up_time			up.time
#define	up_trackid		up.trackid
#define	up_usercode		up.usercode
#define	up_userid		up.userid
#define	up_jobid		up.jobid
#define	up_jobpassword		up.jobpassword
#define	up_dispcharset		up.dispcharset
#define	up_hostcharset		up.hostcharset
#define	up_hostloginname	up.hostloginname
#define	up_hostname		up.hostname
#define	up_hostportname		up.hostportname
#define	up_hostprintername	up.hostprintername
#define	up_jobname		up.jobname
#define	up_ownerid		up.ownerid
#define	up_printinfo		up.printinfo
#define	up_authusername		up.authusername
#define	up_authpassword		up.authpassword
#define	up_authencryptmethod	up.authencryptmethod
#define	up_authencryptsetting	up.authencryptsetting
#define	up_jobpassword_ext	up.jobpassword_ext
#define	up_authusernamecharset	up.authusernamecharset
#define	up_authpasswordcharset	up.authpasswordcharset
#define	up_ndispcharset		up.ndispcharset
#define	up_nhostcharset		up.nhostcharset
#define	up_billingcode		up.billingcode
#define	up_printappointedtime	up.printappointedtime	/* 印刷時刻指定(11A～) */

#define	up_driverkindinfo		up.driverkindinfo		/* 利用ドライバ種別(11A～) */
#define up_foldernumber			up.foldernumber    /* フォルダ番号(12A～) */
#define up_folderpassword		up.folderpassword    /* フォルダパスワード(12A～) */

/*
 *	gps_ujobparam_t
 */
typedef struct gps_ujobparam {
	unsigned long	flag;
	unsigned long	flag2;
	unsigned char	date[GPS_MAX_UPARAM_DATE_LEN + 1];
	unsigned char	time[GPS_MAX_UPARAM_TIME_LEN + 1];
	unsigned char	trackid[GPS_MAX_UPARAM_TRACKID_LEN + 1];
	unsigned char	usercode[GPS_MAX_UPARAM_USERCODE_LEN + 1];
	unsigned char	billingcode[GPS_MAX_UPARAM_BILLINGCODE_LEN + 2];
	unsigned char	userid[GPS_MAX_UPARAM_USERID_LEN + 1];
	unsigned char	jobid[GPS_MAX_UPARAM_JOBID_LEN + 1];
	unsigned char	jobpassword[GPS_MAX_UPARAM_JOBPASSWORD_EXT_LEN + 1];
	unsigned char	dispcharset[GPS_MAX_UPARAM_DISPCHARSET_LEN + 1];
	unsigned char	hostcharset[GPS_MAX_UPARAM_HOSTCHARSET_LEN + 1];
	unsigned char	hostloginname[GPS_MAX_UPARAM_HOSTLOGINNAME_LEN + 1];
	unsigned char	hostname[GPS_MAX_UPARAM_HOSTNAME_LEN + 1];
	unsigned char	hostportname[GPS_MAX_UPARAM_HOSTPORTNAME_LEN + 1];
	unsigned char	hostprintername[GPS_MAX_UPARAM_HOSTPRINTERNAME_LEN + 1];
	unsigned char	jobname[GPS_MAX_UPARAM_JOBNAME_LEN + 1];
	unsigned char	ownerid[GPS_MAX_UPARAM_OWNERID_LEN + 1];
	unsigned char	printinfo[GPS_MAX_UPARAM_PRINTINFO_LEN + 1];
	unsigned char	authusername[GPS_MAX_UPARAM_AUTHUSERNAME_LEN + 1];
	unsigned char	authpassword[GPS_MAX_UPARAM_AUTHPASSWORD_LEN + 1];
	int		authencryptmethod;
	int		authencryptsetting;
	short		authusernamecharset;
	short		authpasswordcharset;
	short		ndispcharset;
	short		nhostcharset;
	unsigned char	printappointedtime[GPS_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN + 1];	/* 印刷時刻指定(11A～) */
	int		driverkindinfo;								/* 利用ドライバ種別(11A～) */
	unsigned short  	foldernumber;        /* フォルダ番号(12A～) */
	unsigned char	folderpassword[GPS_MAX_UPARAM_FOLDERPASSWORD_LEN + 1]; /* フォルダパスワード(12A～) */
} gps_ujobparam_t;

#endif /* !_GPS_UJOBPARAM_H_ */
/*
 * Copyright (c) 1999 Ricoh Company, Ltd.  All Rights Reserved.
 */
