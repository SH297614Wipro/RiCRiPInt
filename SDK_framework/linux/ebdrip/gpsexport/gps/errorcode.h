/******************************************************
 * $Id$
 *
 * Copyright (C) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 *
 *   FILE NAME       : errorcode.h
 *   VERSION         : $Revision$
 *   AUTHOR          : SHINDOH Nobuhiro
 *-----------------------------------------------------
 *       HISTORY
 *	 shindoh - 06 Jan 2000: Created.
 *	 $Log$
 *
 ******************************************************/
#ifndef _GPS_ERRORCODE_H_
#define	_GPS_ERRORCODE_H_

/* add by shindoh */
/********************************************

	status

********************************************/
#define	GPS_ST_READY			10001
#define	GPS_ST_OFFLINE			10002
#define	GPS_ST_WARMING_UP		10003
#define	GPS_ST_CALIBRATING		10004
#define	GPS_ST_JOB_RESETTING		10007
#define	GPS_ST_PROCESSING		10023
#define	GPS_ST_WAITING			10024
#define	GPS_ST_FORM_FEEDING		10029
#define	GPS_ST_ENERGY_SAVE		10033
#define	GPS_ST_PREHEAT			10034
#define	GPS_ST_HEXDUMP			10035
#define	GPS_ST_INIT_DEVELOPER		10036   /* initial developer */
#define	GPS_ST_SUPPLYING_TONER		10037   /* supplying toner */
#define	GPS_ST_SETTING_UP		10038   /* setting up */
#define	GPS_ST_COOLING_DOWN		10039	/* cooling down */
#define	GPS_ST_CARDSAVE			GPS_ST_HEXDUMP
#define	GPS_ST_DRYING			10041	/* 乾燥停止中 */
#define GPS_ST_APLI_OFFLINE		10042	/* 設定変更中 */
#define	GPS_ST_UPDATING_REMOTECERT	10043
#define	GPS_ST_MAINTENANCE		10046	/* メンテナンス中 */
#define	GPS_ST_PAUSE			10047	/* 一次停止中 */
#define	GPS_ST_PRINT_SUSPENDED		10048
#define	GPS_ST_TESTPRINT		10080
#define	GPS_ST_PRENEAREND_TONER		10081	/* トナープレニアエンド(モノクロ) */
#define	GPS_ST_PRENEAREND_TONER_K	10082	/* トナープレニアエンド:K */
#define	GPS_ST_PRENEAREND_TONER_C	10083	/* トナープレニアエンド:C */
#define	GPS_ST_PRENEAREND_TONER_M	10084	/* トナープレニアエンド:M */
#define	GPS_ST_PRENEAREND_TONER_Y	10085	/* トナープレニアエンド:Y */

/********************************************

	warning

********************************************/
#define	GPS_ST_OPTRAM_ERROR		50101		/* diag */
#define	GPS_ST_PARALELL_ERROR		50102		/* diag */
#define	GPS_ST_NVRAM_ERROR		50103		/* diag */
#define	GPS_ST_DIMM_ERROR		50104		/* diag */
#define	GPS_ST_ETHERNET_ERROR		50108		/* diag */
#define	GPS_ST_NIC_ERROR		50108		/* diag */
#define	GPS_ST_IEEE1394_ERROR		50109		/* diag */
#define	GPS_ST_HDD_ERROR		50105		/* diag */
#define	GPS_ST_IEEE802_11b_NOCARD	50110		/* diag */
#define	GPS_ST_IEEE802_11b_CARDOUT	50111		/* diag */
#define	GPS_ST_IEEE802_11b_CARDERROR	50112		/* diag */
#define	GPS_ST_IEEE802_11b_BOARDERROR	50113		/* diag */
#define	GPS_ST_USB_ERROR		50114		/* diag */
#define	GPS_ST_FONTFILE_ERROR		50115		/* diag */
#define	GPS_ST_USBHOST_ERROR		50116		/* diag */

#define	GPS_ST_W_PAPER_EMPTY2		14000		/* paper empty ext (RING/PERFECT BINDER) */
#define	GPS_ST_W_PAPER_EMPTY		13000		/* paper empty */
#define	GPS_ST_W_TRAY_ERROR		12000		/* tray error */

#define	GPS_ST_W_BIN_FULL		30300           /* bin full */
#define	GPS_ST_W_STD_BIN_FULL		30330
#define	GPS_ST_W_1BIN_FULL		30331		/* 1bin */
#define	GPS_ST_W_LOWER_FULL		30332
#define	GPS_ST_W_MBOX1_FULL		30351
#define	GPS_ST_W_MBOX2_FULL		30352
#define	GPS_ST_W_MBOX3_FULL		30353
#define	GPS_ST_W_MBOX4_FULL		30354
#define	GPS_ST_W_MBOX5_FULL		30355
#define	GPS_ST_W_MBOX6_FULL		30356
#define	GPS_ST_W_MBOX7_FULL		30357
#define	GPS_ST_W_MBOX8_FULL		30358
#define	GPS_ST_W_MBOX9_FULL		30359

#define	GPS_ST_W_MULTIFOLD_UNIT_PROOF_FULL		30362

#define	GPS_ST_W_SEQUENTIALSTACK_FULL	30370		/* sequential stack */
#define	GPS_ST_W_FIN_MAIN_FULL		30340		/* fin main */
#define	GPS_ST_W_FIN_SHIFT_FULL		30341		/* finisher shift */
#define	GPS_ST_W_FIN_SADDLE_FULL	30343		/* finisher saddle */
#define	GPS_ST_W_EXIT_STOPBUTTON	30371		/* pressed button */
#define GPS_ST_W_STAPLETYPE_MISMATCH	30382		/* ZAIRE limitation */

#define	GPS_ST_W_FIN_PEXIST		30540		/* finisher paper */
#define	GPS_ST_W_DPX_PEXIST		30510		/* duplex paper */
#define	GPS_ST_W_SADDLE_PEXIST		30520		/* KARUN */

#define	GPS_ST_W_STACKER_PEXIST		30523		/* Paper remaining in stacker tray (Stacker 1) */
#define	GPS_ST_W_STACKER2_PEXIST	30524		/* Paper remaining in stacker tray (Stacker 2) */
#define	GPS_ST_W_MULTIFOLD_UNIT_PEXIST	30525		/* Paper remaining in multi-function folding unit stacker */

#define	GPS_ST_W_LCT_COPEN		12001		/* LCT cover open */
#define	GPS_ST_W_INSERTER_COPEN		12901		/* INSERTER cover open */
#define	GPS_ST_W_INSERTER_SIDE_COPEN	30217		/* INSERTER side cover open */
#define	GPS_ST_W_DPX_ERROR		30260		/* duplex unit error */
#define	GPS_ST_W_DPX_COPEN		30261		/* duplex cover open */

#define	GPS_ST_W_STACKER_COPEN		30276		/* Stacker cover is open */
#define	GPS_ST_W_STACKER2_COPEN		30277		/* Stacker cover is open */

#define	GPS_ST_W_LCTUNIT_COPEN		30280		/* ex. ALASKA-B */

#define	GPS_ST_W_RINGBIND_STACKER_COPEN		30214	/* [Warning] Stacker open (RING/PERFECT BINDER) */
#define	GPS_ST_W_PERFECTBIND_LDTRAY_COPEN	30215	/* [Warning] Loading tray open (RING/PERFECT BINDER) */
#define	GPS_ST_W_PERFECTBIND_PAPERCUT_COPEN	30225	/* [Warning] Waste paper receptacle open (RING/PERFECT BINDER) */
#define	GPS_ST_W_PERFECTBIND_INSERTER_COPEN	30226	/* [Warning] INSERTER cover open (RING/PERFECT BINDER) */
#define	GPS_ST_W_PERFECTBIND_INSERTER_UNIT_COPEN 30227	/* [Warning] INSERTER unit cover open (RING/PERFECT BINDER) */

#define	GPS_ST_W_RINGBIND_STACKER_FULL		30344	/* [Warning] Stacker full (RING/PERFECT BINDER) */
#define	GPS_ST_W_PERFECTBIND_LDTRAY_FULL	30345	/* [Warning] Loading tray full (RING/PERFECT BINDER) */

#define	GPS_ST_W_STACKER_PROOFTRAY_FULL		30346	/* [Warning] Output Tray Full (Stacker Proof Tray) */
#define	GPS_ST_W_STACKER_SHIFTTRAY_FULL		30348	/* [Warning] Output Tray Full (Stacker Shift Tray) */
#define	GPS_ST_W_STACKER2_SHIFTTRAY_FULL	30349	/* [Warning] Output Tray Full (Stacker Shift Tray2) */

#define	GPS_ST_W_RINGBIND_ADJUSTTRAY_PEXIST	30502	/* [Warning] Paper exist in adjust tray (RING/PERFECT BINDER) */
#define	GPS_ST_W_PERFECTBIND_COLLECTTRAY_PEXIST	30503	/* [Warning] Paper exist in correct tray (RING/PERFECT BINDER) */

#define	GPS_ST_LOW_TONER		10006
#define	GPS_ST_LOW_TONER_K		10072
#define	GPS_ST_LOW_TONER_C		10073
#define	GPS_ST_LOW_TONER_M		10074
#define	GPS_ST_LOW_TONER_Y		10075
#define	GPS_ST_LOW_TONER_R		10078
#define	GPS_ST_ADD_STAPLES		40440
//#define	GPS_ST_STAPLE_NEAREND		40440
#define	GPS_ST_ADD_BOOKLET_STAPLES	40441
#define	GPS_ST_ADD_BOOKLET_STAPLES_UPPER	40442
#define	GPS_ST_ADD_BOOKLET_STAPLES_LOWER	40443
#define	GPS_ST_PUNCH_FULL		40342
#define	GPS_ST_STAPLECUT_FULL		30393

#define	GPS_ST_RINGBIND_PUNCH_FULL		30394	/* [Warning] Punch receptacle full (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_PAPERCUT_FULL	30395	/* [Warning] Waste paper receptacle full (RING/PERFECT BINDER) */
#define	GPS_ST_TRIMMER_PAPERCUT_FULL		30396	/* [Warning] Waste paper receptacle for trimmer is full */

#define	GPS_ST_REPLACE_MKIT		30400
#define	GPS_ST_REPLACE_PCU		30401
#define	GPS_ST_WEB_NEAREND		30402
#define	GPS_ST_REPLACE_MKIT_A		30403		/* PCU_COLOR */
#define	GPS_ST_REPLACE_MKIT_B		30404		/* DEVELOPMENT_COLOR */
#define	GPS_ST_REPLACE_MKIT_C		30405		/* FUSER */
#define	GPS_ST_REPLACE_MKIT_D		30406		/* FEEDROLLER */
#define	GPS_ST_REPLACE_MKIT_F		30407		/* PCU_K */
#define	GPS_ST_REPLACE_FUSING_OIL_UNIT	30408
#define	GPS_ST_REPLACE_TRANSFER_UNIT	30409
#define	GPS_ST_REPLACE_CHARGER_UNIT	30410
#define	GPS_ST_REPLACE_DEVELOPMENT		30441
#define	GPS_ST_REPLACE_DEVELOPMENT_COLOR	30411
#define	GPS_ST_REPLACE_DEVELOPMENT_K		30412
#define	GPS_ST_REPLACE_DEVELOPMENT_C		30413
#define	GPS_ST_REPLACE_DEVELOPMENT_M		30414
#define	GPS_ST_REPLACE_DEVELOPMENT_Y		30415
#define	GPS_ST_REPLACE_NEAR_DEVELOPMENT		30451
#define	GPS_ST_REPLACE_NEAR_DEVELOPMENT_COLOR	30421
#define	GPS_ST_REPLACE_NEAR_DEVELOPMENT_K	30422
#define	GPS_ST_REPLACE_NEAR_DEVELOPMENT_C	30423
#define	GPS_ST_REPLACE_NEAR_DEVELOPMENT_M	30424
#define	GPS_ST_REPLACE_NEAR_DEVELOPMENT_Y	30425
#define	GPS_ST_REPLACE_NEAR_PCU		30426
#define	GPS_ST_REPLACE_NEAR_FUSER	30427
#define	GPS_ST_REPLACE_NEAR_MID_TRANSFER_UNIT	30428
#define	GPS_ST_REPLACE_NEAR_PCU_COLOR	30429

#define	GPS_ST_REPLACE_TRANSFER_ROLLER	30416
#define	GPS_ST_REPLACE_TRANSFER_BELT	30417
#define	GPS_ST_OIL_NEAR_FULL		30418
#define	GPS_ST_SUCTION_MOTOR_NEAREND	30419
#define	GPS_ST_REPLACE_TRANSFER_CLEANING	30420
#define	GPS_ST_REPLACE_NEAR_TRANSFER_CLEANING	30450
#define	GPS_ST_REPLACE_FEEDROLLER_LCT		30430	/* Feed Roller PM */
#define	GPS_ST_REPLACE_FEEDROLLER_BYPASS	30431
#define	GPS_ST_REPLACE_FEEDROLLER_TRAY1		30432
#define	GPS_ST_REPLACE_FEEDROLLER_TRAY2		30433
#define	GPS_ST_REPLACE_FEEDROLLER_TRAY3		30434
#define	GPS_ST_REPLACE_FEEDROLLER_TRAY4		30435
#define	GPS_ST_REPLACE_FEEDROLLER_TRAY5		30436
#define	GPS_ST_REPLACE_NEAR_MKIT		30440
#define	GPS_ST_REPLACE_NEAR_MKIT_B		30442
#define	GPS_ST_REPLACE_MAINTENANCE_UNIT		30460
#define	GPS_ST_REPLACE_WASTE_FLUID		30461

#define	GPS_ST_RINGBIND_RING_END		30446	/* [Warning] Out of binding ring (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_GLUE_END		30447	/* [Warning] Out of binding glue (RING/PERFECT BINDER) */

#define	GPS_ST_REPLACE_DEVELOPER_K		30462
#define	GPS_ST_REPLACE_DEVELOPER_C		30463
#define	GPS_ST_REPLACE_DEVELOPER_M		30464
#define	GPS_ST_REPLACE_DEVELOPER_Y		30465

#define	GPS_ST_TONER_NEAR_FULL		10032
#define	GPS_ST_TONER2_NEAR_FULL		30019

#define GPS_ST_SET_FUSERPARAM		30600
#define GPS_ST_SD_LICENSE_ERROR		30607
#define GPS_ST_RCG_CONNECT_ERROR	30608
#define GPS_ST_SUPPLYCALL_ERROR		30609
#define	GPS_ST_REMOTECERT_ERROR		30610
#define	GPS_ST_PROXY_CONNECT_ERROR	30616
#define	GPS_ST_PROXY_AUTH_ERROR		30617
#define	GPS_ST_W_HEADPOSITION_UPPER	30618
#define	GPS_ST_LOG_DATA_NEAR_FULL	30619
#define	GPS_ST_LOG_DATA_FULL		30620
#define	GPS_ST_LOG_TRANSFER_FAILED	30621
#define	GPS_ST_RELATION_SD_NONE		30622
#define	GPS_ST_RELATION_LICENSE_ERROR	30623

#define	GPS_ST_PERFECTBIND_ADJUSTGLUE	30624	/* Adjusting temperature of the glue (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_AUTOOUTPUT	30625	/* Auto Output Paper(RING/PERFECT BINDER) */

#define	GPS_ST_COLOR_MISREGIST		30606
#define	GPS_ST_COLOR_PCU_ERROR		30601
#define	GPS_ST_BLACK_PCU_FUSE		30612
#define	GPS_ST_COLOR_PCU_FUSE		30611

#define	GPS_ST_SHIFT_DISABLE		30743
#define	GPS_ST_STAPLE_DISABLE		30740
#define	GPS_ST_FINISHER_DISABLE		30744
#define	GPS_ST_PUNCH_DISABLE		30746
#define	GPS_ST_FINISHER_TRAY_DISABLE	30747	/* Finisher Tray Disable */

#define	GPS_ST_PRINTPOST_DISABLE	30750

#define	GPS_ST_STAPLE1_DISABLE		30751
#define	GPS_ST_STAPLE2_DISABLE		30752

#define	GPS_ST_DPX_DISABLE		30130

#define	GPS_ST_RINGBIND_PUNCH_NONE	30131	/* punch unit not set(RING/PERFECT BINDER) */
#define	GPS_ST_RINGBIND_RING_NONE	30149	/* [Warning] ring unit not set(RING/PERFECT BINDER) */

#define	GPS_ST_W_1BIN_NONE		30140	/* 1bin unit none */
#define	GPS_ST_W_DEVELOPMENT_R_NONE	30148	/* Development(R) unit none */
#define	GPS_ST_DPXREV_DISABLE		30711
#define	GPS_ST_BYPASS_DISABLE		30720	/* [Warning] BYPASS broken */
#define	GPS_ST_LCT_DISABLE		30721	/* [Warning] LCT broken */
#define	GPS_ST_TRAY1_DISABLE		30722	/* [Warning] TRAY1 broken */
#define	GPS_ST_TRAY2_DISABLE		30723	/* [Warning] TRAY2 broken */
#define	GPS_ST_TRAY3_DISABLE		30724	/* [Warning] TRAY3 broken */
#define	GPS_ST_TRAY4_DISABLE		30725	/* [Warning] TRAY4 broken */
#define	GPS_ST_TRAY5_DISABLE		30726	/* [Warning] TRAY5 broken */
#define	GPS_ST_TRAY6_DISABLE		30727	/* [Warning] TRAY6 broken */
#define	GPS_ST_TRAY7_DISABLE		30728	/* [Warning] TRAY7 broken */
#define	GPS_ST_INSERTER_DISABLE		30729	/* [Warning] INSERTER broken */
#define	GPS_ST_CHARGEUNIT_DISABLE	30763	/* [Warning] MK1 broken */

#define	GPS_ST_PERFECTBIND_DISABLE	30767	/* Device Broken (RING/PERFECT BINDER) */
#define	GPS_ST_RINGBIND_DISABLE		30768	/* Device Broken (RING/PERFECT BINDER) */

#define	GPS_ST_BOOKLET_PROC_WARNING	30970	/* ex. PLOKMATIC */
#define	GPS_ST_PUNCH_UNIT_WARNING	30971	/* [Warning] PUNCH UNIT */

#define	GPS_ST_STACKER_WARNING		30972	/* [Warning] Stacker Cover Open/Handcraft None */
#define	GPS_ST_STACKER2_WARNING		30973	/* [Warning] Stacker2 Cover Open/Handcraft None */

#define	GPS_ST_W_CTRAY_PE		30990	/* current tray */
#define	GPS_ST_W_CTRAY_PE_LCT		30990
#define	GPS_ST_W_CTRAY_PE_BYPASS	30991
#define	GPS_ST_W_CTRAY_PE_TRAY1		30992
#define	GPS_ST_W_CTRAY_PE_TRAY2		30993
#define	GPS_ST_W_CTRAY_PE_TRAY3		30994
#define	GPS_ST_W_CTRAY_PE_TRAY4		30995
#define	GPS_ST_W_CTRAY_PE_TRAY5		30996
#define	GPS_ST_W_CTRAY_PE_TRAY6		30997
#define	GPS_ST_W_CTRAY_PE_TRAY7		30998
#define	GPS_ST_W_CTRAY_PE_INSERTER	30999

#define	GPS_ST_MPT_ADU_DISABLE		30764	/* [Warning] MPT/ADU Motor broken */
#define	GPS_ST_FOLD_UNIT_DISABLE	30765	/* [Warning] Fold Unit broken */
#define	GPS_ST_SADDLE_DISABLE		30766	/* [Warning] Saddle Stitching Machine broken */
#define	GPS_ST_FINISHER_SHIFT_DISABLE	30769	/* Finisher Shift Disable */
#define	GPS_ST_STACKER_SHIFT_DISABLE	30770
#define	GPS_ST_STACKER2_SHIFT_DISABLE	30771
#define	GPS_ST_TRIMMER_DISABLE		30772
#define	GPS_ST_MULTIFOLD_UNIT_DISABLE	30773

#define	GPS_ST_W_ADD_TONER_K		30012	/* [Warning] Toner(K) empty */
#define	GPS_ST_W_ADD_TONER_C		30013	/* [Warning] Toner(C) empty */
#define	GPS_ST_W_ADD_TONER_M		30014	/* [Warning] Toner(M) empty */
#define	GPS_ST_W_ADD_TONER_Y		30015	/* [Warning] Toner(Y) empty */
#define	GPS_ST_W_ADD_TONER_R		30018	/* [Warning] Toner(R) empty */

#define	GPS_ST_TONER_END_ONE_SIDE	30020	/* [W] empty one bottle */

#define	GPS_ST_W_LCT_NOT_SET		30150	/* LCT is not set Correctly */

#define	GPS_ST_W_STACKER_HANDCRAFT_NOT_SET	30167	/* Set Stacker Handcraft correctly */
#define	GPS_ST_W_STACKER2_HANDCRAFT_NOT_SET	30168	/* Set Stacker2 Handcraft correctly */

#define	GPS_ST_W_STAMP_UNIT_NONE	30166	/* stamp unit not set */

#define	GPS_ST_W_COVERFEEDER_NONE		30170	/*  [Warning] Cover Feeder Unit not set  */
#define	GPS_ST_COLORMATCHING_FAILED	30628	/* Color Matching failed (Warning) */
#define GPS_ST_REPLACE_NEAR_FUSING_ROLLER		30452 /* fusing roller */

#define GPS_ST_REPLACE_NEAR_FUSING_BELT		30448 /* 定着ベルト ニアエンド */
#define	GPS_ST_W_ADD_LUBRICANT_C			30073	/* [Warning] 潤滑剤エンド：C */
#define	GPS_ST_W_ADD_LUBRICANT_M			30074	/* [Warning] 潤滑剤エンド：M */
#define	GPS_ST_W_ADD_LUBRICANT_Y			30075	/* [Warning] 潤滑剤エンド：Y */
#define	GPS_ST_LOW_LUBRICANT_K				10092	/* [Warning] 潤滑剤ニアエンド：K */
#define	GPS_ST_LOW_LUBRICANT_C				10093	/* [Warning] 潤滑剤ニアエンド：C */
#define	GPS_ST_LOW_LUBRICANT_M				10094	/* [Warning] 潤滑剤ニアエンド：M */
#define	GPS_ST_LOW_LUBRICANT_Y				10095	/* [Warning] 潤滑剤ニアエンド：Y */
#define	GPS_ST_LOW_LUBRICANT				10096	/* [Warning] 潤滑剤ニアエンド(モノクロ機) */
#define	GPS_ST_REPLACE_PERFECTBIND_GLUE		30449	/* [Warning] くるみ製本機：糊ニアエンド */
/********************************************

	print and data error

********************************************/
#define	GPS_ST_84_WORKERROR		30800
#define	GPS_ST_85_GRAPHIC		30801
#define	GPS_ST_86_PARAMETER		30802
#define	GPS_ST_87_MEMORYOVER		30803
#define	GPS_ST_89_MEMORYSWITCH		30804
#define	GPS_ST_90_MEDIAFULL		30805
#define	GPS_ST_92_MEMORYOVER		30806
#define	GPS_ST_93_MEMORYOVER		30807
#define	GPS_ST_94_DOWNLOAD		30808
#define	GPS_ST_95_FONTERROR		30809
#define	GPS_ST_96_MOJISETERROR		30810
#define	GPS_ST_96_SELECTERROR		30811
#define	GPS_ST_97_ALLOCATION		30812
#define	GPS_ST_98_ACCESSERROR		30813
#define	GPS_ST_99_WARNING		30814
#define	GPS_ST_C0_ERROR			30815
#define	GPS_ST_C1_COMMANDERROR		30816
#define	GPS_ST_C2_PARAMETERNUMERROR	30817
#define	GPS_ST_C3_PARAMETERLIMITERROR	30818
#define	GPS_ST_C6_POSITIONERROR		30819
#define	GPS_ST_C7_POLYGONSIZEERROR	30820
#define	GPS_ST_D0_RESPONSEERROR		30821
#define	GPS_ST_D1_COMMANDERROR		30822
#define	GPS_ST_D2_INVALIDPARAMTERERROR	30823
#define	GPS_ST_D3_PARAMETERLIMITERROR	30824
#define	GPS_ST_D4_PARAMTERNUMERROR	30825
#define	GPS_ST_DC_FONTSELECTERROR	30826
#define	GPS_ST_DD_FONTERROR		30827
#define	GPS_ST_DE_PARAMETERLIMITERROR	30828
#define	GPS_ST_DF_WORKMEMORYERROR	30829

#define	GPS_ST_RCS_85_GRAPHIC		30830
#define	GPS_ST_RCS_86_PARAMETER		30831
#define	GPS_ST_RCS_91_MEMORYOVER	30832
#define	GPS_ST_RTF_92_MEMORYOVER	30833
#define	GPS_ST_RTF_99_FATALERROR	30834
#define	GPS_ST_RCS_94_DOWNLOAD		30835
#define	GPS_ST_9A_RECEIVEERROR		30836
#define	GPS_ST_RCS_ROTATE		30837
#define	GPS_ST_C8_FONTCACHEERROR	30838
#define	GPS_ST_C9_PATTERNCACHEERROR	30839
#define GPS_ST_CA_SIZEDECIDEERROR	30840

#define GPS_ST_PDF_NO_FILESYSTEM	30841
#define GPS_ST_PDF_FILESYSTEM_FULL	30842
#define GPS_ST_PDF_INVALID_PASSWORD	30843
#define GPS_ST_PDF_OP_NOT_PERMITTED	30844
#define GPS_ST_PDF_INTERNAL_ERROR	30845
#define	GPS_ST_P1_COMMANDERROR		30846
#define	GPS_ST_P2_MEMORYERROR		30847
#define	GPS_ST_P3_MEMORYERROR		30848
#define	GPS_ST_P4_SENDDATAABORTED	30849
#define	GPS_ST_P5_RECVDATAABORTED	30850
#define	GPS_ST_9B_AUTH_INVALID		30851
#define GPS_ST_PDF_NO_AUTH_PRINT	30852

#define GPS_ST_PJL_DECRYPTIONERROR	30916
#define	GPS_ST_PPML_NO_FILESYSTEM	30917
#define	GPS_ST_PPML_FILESYSTEM_FULL	30918
#define	GPS_ST_PPML_SYNTAX_ERROR	30919
#define	GPS_ST_PPML_PDL_NOT_SUPPORT	30920

#define	GPS_ST_RPS_DISPLAYLISTOVERFLOW	30016

#define	GPS_ST_A3_OVERFLOW		30900		/* GPS */
#define	GPS_ST_A4_SORTOVER		30901		/* GPS */
#define	GPS_ST_A6_PAGEFULL		30902		/* GPS */
#define	GPS_ST_A7_DRAWERROR		30903		/* GPS */
#define	GPS_ST_A8_LIBRARY		30904		/* GPS */
#define	GPS_ST_B6_AUTH_AUTOREGISTFULL	30924		/* GPS */
#define	GPS_ST_B7_AUTH_REGISTERED	30923		/* GPS */
#define	GPS_ST_B8_AUTH_TIMEOUT		30921		/* GPS */
#define	GPS_ST_B9_AUTH_BUSY		30922		/* GPS */
#define	GPS_ST_BA_USERACCESS		30905		/* GPS */
#define	GPS_ST_BC_SORTERROR		30906		/* GPS */
#define	GPS_ST_BD_STAPLEERROR		30907		/* GPS */
#define	GPS_ST_BE_PUNCHERROR		30908		/* GPS */
#define	GPS_ST_BF_DUPLEXERROR		30909		/* GPS */
#define	GPS_ST_BG_FOLDERROR		30915		/* GPS */
#define	GPS_ST_BH_WIDFOLDERROR		30926		/* GPS */
#define	GPS_ST_BI_MEDIANAMEERROR	30927		/* GPS */
#define	GPS_ST_BJ_BILLINGCODEERROR	30928		/* GPS */

#define	GPS_ST_BQ_UNCOMPRESSERROR	30931		/* GPS(DEC) */


#define	GPS_ST_F0_PRINTERFAXRELEASE	30910		/* GPS */
#define	GPS_ST_F8_PRINTERFAXRELEASE	30911		/* GPS */

#define	GPS_ST_A9_PAGEOVER		30211		/* dummy for string */
#define	GPS_ST_A9_PAGEOVER_PROOF	30211		/* GPS */
#define	GPS_ST_A9_PAGEOVER_SECURE	30231		/* GPS */
#define	GPS_ST_AA_DOCUMENTNUMOVER	30210		/* dummy for string */
#define	GPS_ST_AA_DOCUMENTNUMOVER_PROOF	30210		/* GPS */
#define	GPS_ST_AA_DOCUMENTNUMOVER_SECURE	30230	/* GPS */
#define	GPS_ST_AB_HDDFULL		30202		/* dummy for string */
#define	GPS_ST_AB_HDDFULL_PROOF		30202		/* GPS */
#define	GPS_ST_AB_HDDFULL_SECURE	30203		/* GPS */
#define	GPS_ST_AC_HDDFULL		30201		/* GPS */
#define	GPS_ST_L2_DOCUMENTNUMOVER_CSV	30220		/* GPS */
#define	GPS_ST_L1_HDDFULL_CSV		30221		/* GPS */
#define	GPS_ST_L3_PAGEOVER_CSV		30222		/* GPS */
#define GPS_ST_L4_SIZEERROR_CSV		30223		/* GPS */
#define GPS_ST_L5_INVALID_CSV		30224		/* GPS */
#define GPS_ST_L6_FOLDER_NONE		30228		/* GPS */
#define GPS_ST_L7_FOLDER_INVALID_PASSWORD		30229		/* GPS */
#define GPS_ST_L8_FOLDER_LOCK		30320		/* GPS */

#define	GPS_ST_M1_HDDFULL_CAP		30204		/* GPS */
#define	GPS_ST_M2_DOCUMENTNUMOVER_CAP	30240		/* GPS */
#define	GPS_ST_M3_PAGEOVER_CAP		30241		/* GPS */

#define	GPS_ST_EA_OUTBINCHANGE		10070		/* GPS */
#define	GPS_ST_92_AUTO_JOB_CANCEL	30912		/* GPS */
#define	GPS_ST_91_JOB_CANCEL		30913		/* GPS */
#define	GPS_ST_AD_STOREDERROR		30232		/* GPS */
#define	GPS_ST_AE_OVERLAY_PAGEOVER	30251		/* GPS */
#define	GPS_ST_AF_OVERLAY_NUMOVER	30250		/* GPS */
#define	GPS_ST_AG_OVERLAY_HDDFULL	30205		/* GPS */
#define	GPS_ST_AH_OVERLAY_REGISTERROR	30252		/* GPS */
#define	GPS_ST_AI_OUTSIDE_SIZE		30925		/* GPS */

#define	GPS_ST_BK_RINGBIND_PUNCHERROR		30853	/* Ring binding/punch conditions error (RING/PERFECT BINDER) */
#define	GPS_ST_BL_RINGBIND_PAGEOVER		30855	/* Ring bind page(Paper) max over (RING/PERFECT BINDER) */
#define	GPS_ST_BM_RINGBINDERROR			30929	/* Ring bind error (RING/PERFECT BINDER) */
#define	GPS_ST_BN_PERFECTBIND_PARAMERROR	30854	/* Perfect binding conditions error (RING/PERFECT BINDER) */
#define	GPS_ST_BO_PERFECTBIND_PAGEOVER		30856	/* Ringbind page(paper) max over(RING/PERFECT BINDER) */

#define	GPS_ST_BP_PERFECTBINDERROR		30930	/* Perfect bind error (RING/PERFECT BINDER) */

#define	GPS_ST_BT_MULTIFOLD_UNIT_PARAMERROR		30932		/* */
#define	GPS_ST_BU_MULTIFOLD_UNIT_PAGERROR		30933		/* */
#define	GPS_ST_BW_MULTIFOLD_UNIT_CONFLICTERROR	30934		/* */
#define	GPS_ST_BR_RINGBIND_CONFLICTERROR	30935		/* */
#define	GPS_ST_BS_PERFECTBIND_CONFLICTERROR	30936		/* */
#define	GPS_ST_BX_TRIMMERERROR			30937		/* */
#define	GPS_ST_BV_MULTIFOLD_UNIT_ERROR		30938		/* */
#define	GPS_ST_BY_TRIMMER_PARAMERROR		30939		/* */

#define	GPS_ST_W_PDL_ERROR		30979		/* PDL */

#define	GPS_ST_AJ_INPUT_MEDIA_ERROR		30941	/* GPS */
#define	GPS_ST_BB_LIMITNUM_ERROR	30942	/* Reached the upper limit number of sheets */

#define GPS_ST_ERRORJOBSTORED_HDDFULL			30206		/* GPS */
#define GPS_ST_ERRORJOBSTORED_DOCUMENTNUM_ERROR	30190		/* GPS */
#define GPS_ST_ERRORJOBSTORED_PAGE_ERROR		30191		/* GPS */
#define GPS_ST_UCPPRINTED_ERROR					30857		/* GPS */

#define GPS_ST_ERRSKIP						30943		/* GPS エラースキップ発生 */
#define GPS_ST_BZ_SECURITY_PRINT_ERROR		30944		/* GPS セキュリティ印字不可 */

#define GPS_ST_SADDLE_FOLDFINHALF_ERROR		30945	/* 中綴じ/中折りエラー */
#define GPS_ST_FOLDFINHALF_PAGEOVER			30946	/* 重ね折り可能枚数超過エラー */
/********************************************

	error/alert

********************************************/
#define	GPS_ST_CHECK_TONER_K		30132
#define	GPS_ST_CHECK_TONER_C		30133
#define	GPS_ST_CHECK_TONER_M		30134
#define	GPS_ST_CHECK_TONER_Y		30135
#define	GPS_ST_NO_GENUINE_TONER		30136

#define	GPS_ST_STAPLE_BUSY		30301		/* TBD */
#define	GPS_ST_FINISHER_BUSY		30302		/* TBD */
#define	GPS_ST_INTRAY_BUSY		30303		/* TBD */

#define	GPS_ST_RINGBIND_BUSY		30305	/* Ringbind resource busy (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_BUSY		30306	/* Perfectbind resource busy (RING/PERFECT BINDER) */

#define	GPS_ST_MULTIFOLD_UNIT_BUSY		30307	/* Waiting for multi-function folding unit resource */
#define	GPS_ST_STACKER_BUSY		30308	/* Waiting for stacker resource */

#define	GPS_ST_DPX_UOPEN		40260	/* unit open */
#define	GPS_ST_DPX_COPEN		40261	/* 40260 -> 40261 */
#define	GPS_ST_DPX_ERROR		40711
#define	GPS_ST_WEB_END			40402
#define	GPS_ST_FIN_PEXIST		40540
#define	GPS_ST_DPX_PEXIST		40510
#define	GPS_ST_SADDLE_PEXIST		40520

#define	GPS_ST_RINGBIND_ADJUSTTRAY_PEXIST	40521	/* [Error] Paper exist in adjust tray (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_COLLECTTRAY_PEXIST	40522	/* [Error] Paper exist in collect tray (RING/PERFECT BINDER) */

#define	GPS_ST_STACKER_TRAY_PEXIST	40523	/* [Error] Paper remaining in stacker tray (Stacker 1) */
#define	GPS_ST_STACKER2_TRAY_PEXIST	40524	/* [Error] Paper remaining in stacker tray (Stacker 2) */
#define	GPS_ST_MULTIFOLD_UNIT_PEXIST		40525	/* [Error] Paper remaining in multi-function folding unit stacker */

#define	GPS_ST_ADD_TONER		40010
#define	GPS_ST_ADD_TONER_K		40012
#define	GPS_ST_ADD_TONER_C		40013
#define	GPS_ST_ADD_TONER_M		40014
#define	GPS_ST_ADD_TONER_Y		40015
#define	GPS_ST_ADD_TONER_R		40018

#define	GPS_ST_TONER_FULL		40011
#define	GPS_ST_TONER2_FULL		40019	/* 2nd toner bottle full */
#define	GPS_ST_E_REPLACE_MKIT		40020
#define	GPS_ST_E_REPLACE_MKIT_B		40021
#define	GPS_ST_E_REPLACE_FUSING_OIL_UNIT	40023	/* fusing oil */
#define	GPS_ST_E_REPLACE_FUSING_UNIT	40025	/* fusing unit */
#define	GPS_ST_E_REPLACE_TRANSFER_ROLLER	40027
#define	GPS_ST_E_REPLACE_TRANSFER_BELT		40028
#define	GPS_ST_OIL_FULL			40029
#define	GPS_ST_E_REPLACE_DEVELOPMENT_K	40032
#define	GPS_ST_E_REPLACE_DEVELOPMENT_C	40033
#define	GPS_ST_E_REPLACE_DEVELOPMENT_M	40034
#define	GPS_ST_E_REPLACE_DEVELOPMENT_Y	40035
#define	GPS_ST_E_REPLACE_PCU_COLOR	40041
#define	GPS_ST_E_REPLACE_PCU_K		40042
#define GPS_ST_E_TRANSFER_UNIT_NONE	40178
#define GPS_ST_E_PAPER_GUIDE_BOARD_NONE	40179	/* 用紙ガイド板セット不良 */
#define GPS_ST_E_FUSING_CLEANING_WEB_NONE	40180	/* 定着クリーニングウェブセット不良 */
#define GPS_ST_K_DRUM_CLEANING_UNIT_NONE	40182	/* BKドラムクリーナユニットが正しくセットされていない */
#define GPS_ST_C_DRUM_CLEANING_UNIT_NONE	40183	/* Cドラムクリーナユニットが正しくセットされていない */
#define GPS_ST_M_DRUM_CLEANING_UNIT_NONE	40184	/* Mドラムクリーナユニットが正しくセットされていない */
#define GPS_ST_Y_DRUM_CLEANING_UNIT_NONE	40185	/* Yドラムクリーナユニットが正しくセットされていない */
#define	GPS_ST_E_ADD_STAPLES		40490
#define	GPS_ST_E_ADD_BOOKLET_STAPLES	40491
#define	GPS_ST_E_ADD_BOOKLET_STAPLES_UPPER	40492
#define	GPS_ST_E_ADD_BOOKLET_STAPLES_LOWER	40493
#define	GPS_ST_E_PUNCH_FULL		40392
#define	GPS_ST_E_STAPLECUT_FULL		40393

#define	GPS_ST_PAPER_EMPTY		41000	/* paper empty */
#define	GPS_ST_TRAY_ERROR		41000	/* tray error */
#define	GPS_ST_TRAY_ERROR_LCT		41000
#define	GPS_ST_TRAY_ERROR_BYPASS	41100
#define	GPS_ST_TRAY_ERROR_TRAY1		41200
#define	GPS_ST_TRAY_ERROR_TRAY2		41300
#define	GPS_ST_TRAY_ERROR_TRAY3		41400
#define	GPS_ST_TRAY_ERROR_TRAY4		41500
#define	GPS_ST_TRAY_ERROR_TRAY5		41600
#define	GPS_ST_TRAY_ERROR_TRAY6		41700
#define	GPS_ST_TRAY_ERROR_TRAY7		41800
#define	GPS_ST_TRAY_ERROR_INSERTER	41900

#define	GPS_ST_PAPER_NONE		45000	/* specified size/media none */
#define	GPS_ST_PAPER_MEDIA_ERROR	46000	/* tray media mismatch */
#define	GPS_ST_PAPER_SIZE_ERROR		47000	/* tray size mismatch */
#define	GPS_ST_PAPER_ERROR		48000	/* tray size/media mismatch */

#define	GPS_ST_PAPER_EMPTY2		49000	/* paper empty ext (RING/PERFECT BINDER) */

#define	GPS_ST_BIN_FULL			40300		/* bin full */
#define	GPS_ST_STD_BIN_FULL		40300
#define	GPS_ST_1BIN_FULL		40301		/* 1bin */
#define	GPS_ST_LOWER_FULL		40302
#define	GPS_ST_MBOXPROOF_FULL		40350
#define	GPS_ST_MBOX1_FULL		40351
#define	GPS_ST_MBOX2_FULL		40352
#define	GPS_ST_MBOX3_FULL		40353
#define	GPS_ST_MBOX4_FULL		40354
#define	GPS_ST_MBOX5_FULL		40355
#define	GPS_ST_MBOX6_FULL		40356
#define	GPS_ST_MBOX7_FULL		40357
#define	GPS_ST_MBOX8_FULL		40358
#define	GPS_ST_MBOX9_FULL		40359
#define	GPS_ST_SEQUENTIALSTACK_FULL	40370	/* sequential stack */
#define	GPS_ST_FIN_MAIN_FULL		40340	/* fin main */
#define	GPS_ST_FIN_SHIFT_FULL		40341	/* finisher shift */
#define	GPS_ST_FIN_SADDLE_FULL		40343	/* finisher saddle */

#define	GPS_ST_RINGBIND_STACKER_FULL	40344	/* [Error] stacker full (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_LDTRAY_FULL	40345	/* [Error] loading tray full (RING/PERFECT BINDER) */

#define	GPS_ST_STACKER_PROOF_FULL	40346	/* [Error] Output Tray Full (Stacker Proof Tray)  */
#define	GPS_ST_STACKER_SHIFT_FULL	40348	/* [Error] Output Tray Full (Stacker Shift Tray)  */
#define	GPS_ST_STACKER2_SHIFT_FULL	40349	/* [Error] Output Tray Full (Stacker2 Shift Tray)  */
#define	GPS_ST_MULTIFOLD_UNIT_PROOF_FULL	40362	/* [Error] Output Tray Full (Multi-Function Folding Unit Proof Tray)  */

#define	GPS_ST_EXIT_STOPBUTTON		40371	/* pressed button */
#define GPS_ST_LIMITLESS_FULL		40380	/* ZAIRE limitless(full) */
#define GPS_ST_EMPTYBIN_NONE		40381	/* ZAIRE limitless(no empty) */
#define GPS_ST_STAPLETYPE_MISMATCH	40382	/* ZAIRE limitation */
#define GPS_ST_CANNOT_CLEAR_STAPLE	40383	/* ZAIRE limitation */
#define GPS_ST_FIN_SHIFT_NOT_EMPTY	40384	/* ZAIRE limitless(finisher shift not empty) */

#define	GPS_ST_SHIFT_ERROR		40743

#define	GPS_ST_COPEN			40200		/* cover open */
#define	GPS_ST_FRONT_COPEN		40200
#define	GPS_ST_INTERCHANGE_COPEN	40203
#define	GPS_ST_EXIT_COPEN		40204
#define	GPS_ST_MBOX_COPEN		40250
#define	GPS_ST_UPPER_COPEN		40220	/* 1bin */
#define	GPS_ST_SIDE_COPEN		40201
#define	GPS_ST_TRAY_COPEN		40202
#define	GPS_ST_FRONT_SIDE_COPEN		40206
#define	GPS_ST_FRONT_L_COPEN		40207
#define	GPS_ST_TOP_COPEN		40208
#define	GPS_ST_JAMREMOVE_COPEN		40209
#define	GPS_ST_BANK_COPEN		40210
#define	GPS_ST_BANK2_COPEN		40211	/* 2nd bank cover */
#define	GPS_ST_TRAY4_COPEN		40212	/* 4th tray cover */
#define	GPS_ST_TRAY5_COPEN		40213	/* 5th tray cover */
#define	GPS_ST_INSERTER_SIDE_COPEN	40217
#define	GPS_ST_INSERTER_FRONT_COPEN	40218
#define	GPS_ST_ROLL_COPEN	40219
#define	GPS_ST_1BIN_COPEN		40220	/* dummy */

#define	GPS_ST_RINGBIND_STACKER_COPEN		40214	/* [Error] Stacker open (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_LDTRAY_COPEN		40215	/* [Error] Loading tray open(RING/PERFECT BINDER) */
#define	GPS_ST_RINGBIND_COPEN			40221	/* Ringbind cover open (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_UPPER_COPEN		40222	/* Perfectbind upper cover open (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_RELAY_COPEN		40223	/* Perfectbind relay cover open (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_FRONT_COPEN		40224	/* Perfectbind front cover open (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_PAPERCUT_COPEN	40225	/* [Error] Waste paper receptacle (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_INSERTER_COPEN	40226	/* [Error] INSERTER cover open (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_INSERTER_UNIT_COPEN	40227	/* [Error] INSERTER unit cover open (RING/PERFECT BINDER) */

#define	GPS_ST_RELAY_R_COPEN		40231
#define	GPS_ST_RELAY_MID_COPEN		40232
#define	GPS_ST_RELAY_L_COPEN		40233
#define	GPS_ST_FIN_COPEN		40240	/* dummy */
#define	GPS_ST_FIN_JOINT_COPEN		40241
#define	GPS_ST_FIN_STAPLE_COPEN		40242
#define	GPS_ST_FIN_UPPER_COPEN		40243
#define	GPS_ST_FIN_ENTER_COPEN		40244
#define	GPS_ST_FIN_EXIT_COPEN		40245
#define	GPS_ST_FIN_SADDLE_COPEN		40246
#define	GPS_ST_POST_MAIN_COPEN		40251
#define	GPS_ST_POST_PT_COPEN		40252
#define	GPS_ST_POST_RELAY_COPEN		40253
#define	GPS_ST_DPX_LEFT_COPEN		40262
#define	GPS_ST_DPX_RIGHT_COPEN		40263
#define	GPS_ST_CATCH_UP_COPEN		40270

#define	GPS_ST_DECURLER_UNIT_COPEN	40273
#define	GPS_ST_MULTIFOLD_UNIT_COPEN		40274
#define	GPS_ST_TRIMMER_COPEN		40275
#define	GPS_ST_STACKER_COPEN		40276
#define	GPS_ST_STACKER2_COPEN		40277
#define	GPS_ST_STACKER_UPPER_COPEN	40278
#define	GPS_ST_STACKER2_UPPER_COPEN	40279

#define	GPS_ST_LCTUNIT_COPEN		40280	/* ex. ALASKA-B */
#define	GPS_ST_SECOND_TRANSFER_COPEN	40287	/* 二次転写カバーオープン(エラー) */
#define	GPS_ST_BYPASS_COPEN		40288	/* 手差しドアオープン(エラー) */
#define	GPS_ST_DRAWER_COPEN		40289	/* 引出しドアオープン(エラー) */
#define	GPS_ST_FOLD_COPEN		40290	/* 折り機ドア */
#define	GPS_ST_EJECT_COPEN		40291
#define	GPS_ST_FOLDER_COPEN		40292	/* 折り機ドア */

#define	GPS_ST_COOLING_UNIT_COPEN	40295	/* Cooling Option Cover Open */
#define GPS_ST_FUSER_COPEN		40298	/* 定着カバー */
#define GPS_ST_MOVEROLLER_COPEN	40299	/* 移動ローラ開閉ガイド板 */

#define	GPS_ST_FUSER_NONE		40100
#define	GPS_ST_PCU_NONE			40101

#define	GPS_ST_JAM			42000	/* jam */
#define	GPS_ST_FEED_JAM			42000
#define	GPS_ST_INNER_JAM		42001
#define	GPS_ST_INNER_JAM_C		42002
#define	GPS_ST_EXIT_JAM			42004
#define	GPS_ST_FINISHER_JAM		42005
#define	GPS_ST_MBOX_JAM			42007
#define	GPS_ST_DPX_JAM			42009
#define	GPS_ST_INSERTER_JAM		42010
#define	GPS_ST_FOLD_JAM			42011	/* 折り機ジャム */
#define	GPS_ST_INCBANK_JAM		42012	/* 増設バンク 1段目のジャム */
#define	GPS_ST_INCBANK2_JAM		42013	/* 増設バンク 2段目のジャム */
#define	GPS_ST_INCBANK3_JAM		42014	/* 増設バンク 3段目のジャム */
#define	GPS_ST_BOOKLET_PROC_JAM		42015	/* ex. PLOKMATIC */
#define	GPS_ST_INCBANK4_JAM		42016	/* 増設バンク 4段目のジャム */

#define	GPS_ST_RINGBIND_JAM		42020	/* Ringbind JAM (RING/PERFECT BINDER) */
#define	GPS_ST_PERFECTBIND_JAM		42021	/* Perfectbind JAM (RING/PERFECT BINDER) */

#define	GPS_ST_STACKER_JAM		42022	/* Paper Jam L (Stacker) */
#define	GPS_ST_STACKER2_JAM		42023	/* Paper Jam L (Stacker2) */
#define	GPS_ST_TRIMMER_JAM		42024	/* Paper Misfeed (Trimmer) */
#define	GPS_ST_DECURLER_UNIT_JAM		42025	/* Paper Misfeed (Decurler Unit) */
#define	GPS_ST_COOLING_UNIT_JAM			42026	/* Paper Misfeed (Cooling Option) */

#define	GPS_ST_PAPER_SIZE_JAM		42099

#define	GPS_ST_FORBID_DUPLEX		40902
#define	GPS_ST_BYPASS_PEXIST		40903
#define	GPS_ST_TEMPERATURE_RANGE	40904
#define GPS_ST_SAME_TRAY_SELECT		40906
#define	GPS_ST_HEADPOSITION_WRONG	40907
#define	GPS_ST_HEADPOSITION_UPPER	40908

#define GPS_ST_WAITING_KEYCOUNTER	40910
#define GPS_ST_WAITING_KEYCARD		40911
#define GPS_ST_WAITING_PREPAIDCARD	40912
#define GPS_ST_WAITING_COIN		40913
#define GPS_ST_WAITING_KCARD_COUNTER	40914
#define GPS_ST_WAITING_PCARD_COUNTER	40915
#define GPS_ST_WAITING_COIN_COUNTER	40916

#define	GPS_ST_OUTPUT_BIN_CLOSE		40920
#define	GPS_ST_OUTPUT_BIN_OPEN		40921
#define	GPS_ST_FEED_TRAY_CLOSE		40922
#define	GPS_ST_FEED_TRAY_OPEN		40923

#define	GPS_ST_WSHEETFEED_DETECT_ERROR	40928	/* 重送検知エラー */

#define	GPS_ST_BOOKLET_PROC_ERROR	40970	/* ex. PLOKMATIC */
#define	GPS_ST_PUNCH_UNIT_ERROR		40971	/* Punch Unit Error */

#define	GPS_ST_STACKER_ERROR		40972	/* Stacker Cover Open/Handcraft None */
#define	GPS_ST_STACKER2_ERROR		40973	/* Stacker2 Cover Open/Handcraft None */

#define	GPS_ST_RESET_INDEX_PAPER	40977	/* インデックス紙再セット要求 */

#define	GPS_ST_CTRAY_PE			40990	/* current tray PE */
#define	GPS_ST_CTRAY_PE_LCT		40990
#define	GPS_ST_CTRAY_PE_BYPASS		40991
#define	GPS_ST_CTRAY_PE_TRAY1		40992
#define	GPS_ST_CTRAY_PE_TRAY2		40993
#define	GPS_ST_CTRAY_PE_TRAY3		40994
#define	GPS_ST_CTRAY_PE_TRAY4		40995
#define	GPS_ST_CTRAY_PE_TRAY5		40996
#define	GPS_ST_CTRAY_PE_TRAY6		40997
#define	GPS_ST_CTRAY_PE_TRAY7		40998

#define	GPS_ST_REGISTGUIDE_OPEN		40137	/* B2 cover open */
#define	GPS_ST_1BIN_NONE		40140	/* 1bin unit none */
#define	GPS_ST_MID_TRANSFER_UNIT_NONE	40141
#define	GPS_ST_DEVELOPMENT_K_NONE	40142	/* Development(K) unit none */
#define	GPS_ST_DEVELOPMENT_C_NONE	40143	/* Development(C) unit none */
#define	GPS_ST_DEVELOPMENT_M_NONE	40144	/* Development(M) unit none */
#define	GPS_ST_DEVELOPMENT_Y_NONE	40145	/* Development(Y) unit none */
#define	GPS_ST_DEVELOPMENT_R_NONE	40148	/* Development(R) unit none */
#define	GPS_ST_TRANSFER_CLEANING_NONE	40146	/* transfer cleaning unit */
#define	GPS_ST_FOLD_UNIT_OPEN		40147	/* 折り機ドア2 */
#define	GPS_ST_PCU_COLOR_NONE		40151	/* PCU(COLOR) none */
#define	GPS_ST_PCU_K_NONE		40152	/* PCU(K) none */
#define	GPS_ST_PCU_C_NONE		40153	/* PCU(C) unit none */
#define	GPS_ST_PCU_M_NONE		40154	/* PCU(M) unit none */
#define	GPS_ST_PCU_Y_NONE		40155	/* PCU(Y) unit none */
#define	GPS_ST_FINISHER_NONE		40156   /* finisher */
#define	GPS_ST_FUSING_OIL_UNIT_NONE	40157   /* fusing oil unit */
#define	GPS_ST_TRANSFER_UNIT_NONE	40158   /* transfering unit */
#define	GPS_ST_TONER_DISPOSAL_NONE	40159   /* toner disposal bottle */
#define	GPS_ST_TONER2_DISPOSAL_NONE	40160   /* 2nd toner bottle none */
#define	GPS_ST_CHARGER_UNIT_NONE	40161	/* charger unit none */
#define	GPS_ST_TONER_SUPPLY_ERROR_K	40162	/* toner supply error (K) */
#define	GPS_ST_TONER_SUPPLY_ERROR_C	40163	/* toner supply error (C) */
#define	GPS_ST_TONER_SUPPLY_ERROR_M	40164	/* toner supply error (M) */
#define	GPS_ST_TONER_SUPPLY_ERROR_Y	40165	/* toner supply error (Y) */

#define	GPS_ST_STAMP_UNIT_NONE		40166	/* stamp unit not set */

#define	GPS_ST_STACKER_HANDCRAFT_NONE	40167	/* Set Stacker Handcraft correctly (Error) */
#define	GPS_ST_STACKER2_HANDCRAFT_NONE	40167	/* Set Stacker2 Handcraft correctly (Error) */
#define	GPS_ST_DECURLER_UNIT_NONE	40169	/* Set Decurler Unit correctly (Error) */
#define	GPS_ST_COVERFEEDER_NONE		40170	/*  [Error] Cover Feeder Unit not set  */

#define	GPS_ST_MICR_CARTRIDGE_NONE	40176	/* Replace MICR Cartridge */
#define	GPS_ST_STD_CARTRIDGE_NONE	40177	/* Replace STD Cartridge */

#define	GPS_ST_TONER_COPEN		40205	/* Toner cover open */
#define	GPS_ST_BANK_JAM			42008	/* Bank unit jam */
#define	GPS_ST_DPXTRANS_JAM		42019	/* Duplex Trans. Unit Jam */
#define	GPS_ST_E_CHECK_TONER		40132	/* [Error] Toner unit none (dummy) */
#define	GPS_ST_E_CHECK_TONER_K		40132	/* [Error] Toner(K) unit none */
#define	GPS_ST_E_CHECK_TONER_C		40133	/* [Error] Toner(C) unit none */
#define	GPS_ST_E_CHECK_TONER_M		40134	/* [Error] Toner(M) unit none */
#define	GPS_ST_E_CHECK_TONER_Y		40135	/* [Error] Toner(Y) unit none */

#define	GPS_ST_E_RINGBIND_RING_NONE		40149	/* [Error] Ring unit not set (RING/PERFECT BINDER) */
#define	GPS_ST_E_RINGBIND_PUNCH_FULL		40394	/* [Error] Punch receptacle full (RING/PERFECT BINDER) */
#define	GPS_ST_E_PERFECTBIND_PAPERCUT_FULL	40395	/* [Error] Waste paper receptacle full(RING/PERFECT BINDER) */

#define	GPS_ST_E_TRIMMER_PAPERCUT_FULL	40396	/* [Error] Waste paper receptacle for trimmer is full */

#define	GPS_ST_E_RINGBIND_RING_END		40446	/* [Error] Out of binding ring (RING/PERFECT BINDER) */
#define	GPS_ST_E_PERFECTBIND_GLUE_END		40447	/* [Error] Out of binding glue (RING/PERFECT BINDER) */


#define	GPS_ST_E_TRAY_DISABLE		40720           /* dummy */
#define	GPS_ST_E_BYPASS_DISABLE		40720	/* [Error] BYPASS broken */
#define	GPS_ST_E_LCT_DISABLE		40721	/* [Error] LCT broken */
#define	GPS_ST_E_TRAY1_DISABLE		40722	/* [Error] TRAY1 broken */
#define	GPS_ST_E_TRAY2_DISABLE		40723	/* [Error] TRAY2 broken */
#define	GPS_ST_E_TRAY3_DISABLE		40724	/* [Error] TRAY3 broken */
#define	GPS_ST_E_TRAY4_DISABLE		40725	/* [Error] TRAY4 broken */
#define	GPS_ST_E_TRAY5_DISABLE		40726	/* [Error] TRAY5 broken */
#define	GPS_ST_E_TRAY6_DISABLE		40727	/* [Error] TRAY6 broken */
#define	GPS_ST_E_TRAY7_DISABLE		40728	/* [Error] TRAY7 broken */
#define	GPS_ST_E_INSERTER_DISABLE      	40729	/* [Error] INSERTER broken */
#define	GPS_ST_E_CHARGEUNIT_DISABLE	40763	/* [Error] MK1 broken */
#define	GPS_ST_DPXTRANS_NONE		40130	/* Duplex Trans unit none */
#define	GPS_ST_TRANSFER_BELT_NONE	40136
#define	GPS_ST_DISPOSAL_OR_BELT_NONE	40138
					/* toner disposal or transfer belt */
#define	GPS_ST_OIL_DISPOSAL_NONE	40139   /* oil bottle none */

#define	GPS_ST_E_PAUSEMODE		40978
#define	GPS_ST_E_PDL_ERROR		40979		/* PDL */
#define	GPS_ST_E_IPDS_CAPTUREFONT_ERROR	40926	/* PDL(IPDS) */
#define GPS_ST_E_REPLACE_FUSING_ROLLER	40036 /* [Error] fusing roller */

#define GPS_ST_OIL_COPEN	40296	/* oil cover open */
#define	GPS_ST_TONER_END_STOP	40941	/* [Error] カラートナーエンド時のモノクロ印刷制限 */

#define GPS_ST_E_REPLACE_FUSING_BELT	40037	/* 定着ベルトユニット交換 */
#define	GPS_ST_PDL_AUTOJOBCANCEL	40942	/* [Error] PDLによるオートジョブキャンセル */
#define	GPS_ST_ADD_LUBRICANT_K			40072	/* [Error] 潤滑剤エンド：K */
#define	GPS_ST_ADD_LUBRICANT_C			40073	/* [Error] 潤滑剤エンド：C */
#define	GPS_ST_ADD_LUBRICANT_M			40074	/* [Error] 潤滑剤エンド：M */
#define	GPS_ST_ADD_LUBRICANT_Y			40075	/* [Error] 潤滑剤エンド：Y */
#define	GPS_ST_ADD_LUBRICANT			40076	/* [Error] 潤滑剤エンド(モノクロ機) */
#define	GPS_ST_E_DRAWER_NONE			40186	/* [Error] 引き出しセット不良 */
#define	GPS_ST_E_HEATPIPEUNIT_NONE		40187	/* [Error] ヒートパイプユニットセット不良 */
#define	GPS_ST_E_TONERRECOVERUNIT_NONE	40188	/* [Error] トナー補給ユニットセット不良 */

/********************************************

	SC

********************************************/
#define	GPS_ST_SC_ERROR			40800	/* not diag */
#define	GPS_ST_SC_COMMUNICATION		40801
#define	GPS_ST_SC_RESIDENT_FONTROM	50106	/* Resident Font ROM */
#define	GPS_ST_SC_DIAG_ERROR		50199	/* diag error */

/********************************************

	error/alert

********************************************/
#define	GPS_ST_PAPER_SIZE_ERROR_FREE	72000	/* for Free mode */

#endif /* !_GPS_ERRORCODE_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */


