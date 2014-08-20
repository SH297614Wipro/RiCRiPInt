#ifndef _DI_ERRORCODE_H_
#define	_DI_ERRORCODE_H_

/* add by shindoh */
/********************************************

	status

********************************************/
#define	DI_ST_READY			10001
#define	DI_ST_OFFLINE			10002
#define	DI_ST_WARMING_UP		10003
#define	DI_ST_CALIBRATING		10004
#define	DI_ST_JOB_RESETTING		10007
#define	DI_ST_PROCESSING		10023
#define	DI_ST_WAITING			10024
#define	DI_ST_FORM_FEEDING		10029
#define	DI_ST_ENERGY_SAVE		10033
#define	DI_ST_PREHEAT			10034
#define	DI_ST_HEXDUMP			10035
#define	DI_ST_INIT_DEVELOPER		10036   /* initial developer */
#define	DI_ST_SUPPLYING_TONER		10037   /* supplying toner */
#define	DI_ST_SETTING_UP		10038   /* setting up */
#define	DI_ST_COOLING_DOWN		10039	/* cooling down */
#define	DI_ST_CARDSAVE			DI_ST_HEXDUMP
#define	DI_ST_DRYING			10041	/* 乾燥停止中 */
#define DI_ST_APLI_OFFLINE		10042	/* 設定変更中 */
#define	DI_ST_UPDATING_REMOTECERT	10043
#define	DI_ST_MAINTENANCE		10046	/* メンテナンス中 */
#define	DI_ST_PAUSE			10047	/* 一次停止中 */
#define	DI_ST_PRINT_SUSPENDED		10048
#define	DI_ST_TESTPRINT		10080

/********************************************

	warning

********************************************/
#define	DI_ST_OPTRAM_ERROR		50101		/* diag */
#define	DI_ST_PARALELL_ERROR		50102		/* diag */
#define	DI_ST_NVRAM_ERROR		50103		/* diag */
#define	DI_ST_DIMM_ERROR		50104		/* diag */
#define	DI_ST_ETHERNET_ERROR		50108		/* diag */
#define	DI_ST_NIC_ERROR		50108		/* diag */
#define	DI_ST_IEEE1394_ERROR		50109		/* diag */
#define	DI_ST_HDD_ERROR		50105		/* diag */
#define	DI_ST_IEEE802_11b_NOCARD	50110		/* diag */
#define	DI_ST_IEEE802_11b_CARDOUT	50111		/* diag */
#define	DI_ST_IEEE802_11b_CARDERROR	50112		/* diag */
#define	DI_ST_IEEE802_11b_BOARDERROR	50113		/* diag */
#define	DI_ST_USB_ERROR		50114		/* diag */
#define	DI_ST_FONTFILE_ERROR		50115		/* diag */
#define	DI_ST_USBHOST_ERROR		50116		/* diag */

#define	DI_ST_W_PAPER_EMPTY2		14000		/* paper empty ext (RING/PERFECT BINDER) */
#define	DI_ST_W_PAPER_EMPTY		13000		/* paper empty */
#define	DI_ST_W_TRAY_ERROR		12000		/* tray error */

#define	DI_ST_W_BIN_FULL		30300           /* bin full */
#define	DI_ST_W_STD_BIN_FULL		30330
#define	DI_ST_W_1BIN_FULL		30331		/* 1bin */
#define	DI_ST_W_LOWER_FULL		30332
#define	DI_ST_W_MBOX1_FULL		30351
#define	DI_ST_W_MBOX2_FULL		30352
#define	DI_ST_W_MBOX3_FULL		30353
#define	DI_ST_W_MBOX4_FULL		30354
#define	DI_ST_W_MBOX5_FULL		30355
#define	DI_ST_W_MBOX6_FULL		30356
#define	DI_ST_W_MBOX7_FULL		30357
#define	DI_ST_W_MBOX8_FULL		30358
#define	DI_ST_W_MBOX9_FULL		30359

#define	DI_ST_W_MULTIFOLD_UNIT_PROOF_FULL		30362

#define	DI_ST_W_SEQUENTIALSTACK_FULL	30370		/* sequential stack */
#define	DI_ST_W_FIN_MAIN_FULL		30340		/* fin main */
#define	DI_ST_W_FIN_SHIFT_FULL		30341		/* finisher shift */
#define	DI_ST_W_FIN_SADDLE_FULL	30343		/* finisher saddle */
#define	DI_ST_W_EXIT_STOPBUTTON	30371		/* pressed button */
#define DI_ST_W_STAPLETYPE_MISMATCH	30382		/* ZAIRE limitation */

#define	DI_ST_W_FIN_PEXIST		30540		/* finisher paper */
#define	DI_ST_W_DPX_PEXIST		30510		/* duplex paper */
#define	DI_ST_W_SADDLE_PEXIST		30520		/* KARUN */

#define	DI_ST_W_STACKER_PEXIST		30523		/* Paper remaining in stacker tray (Stacker 1) */
#define	DI_ST_W_STACKER2_PEXIST	30524		/* Paper remaining in stacker tray (Stacker 2) */
#define	DI_ST_W_MULTIFOLD_UNIT_PEXIST	30525		/* Paper remaining in multi-function folding unit stacker */

#define	DI_ST_W_LCT_COPEN		12001		/* LCT cover open */
#define	DI_ST_W_INSERTER_COPEN		12901		/* INSERTER cover open */
#define	DI_ST_W_INSERTER_SIDE_COPEN	30217		/* INSERTER side cover open */
#define	DI_ST_W_DPX_ERROR		30260		/* duplex unit error */
#define	DI_ST_W_DPX_COPEN		30261		/* duplex cover open */

#define	DI_ST_W_STACKER_COPEN		30264		/* Stacker cover is open */
#define	DI_ST_W_STACKER2_COPEN		30265		/* Stacker cover is open */

#define	DI_ST_W_LCTUNIT_COPEN		30280		/* ex. ALASKA-B */

#define	DI_ST_W_RINGBIND_STACKER_COPEN		30214	/* [Warning] Stacker open (RING/PERFECT BINDER) */
#define	DI_ST_W_PERFECTBIND_LDTRAY_COPEN	30215	/* [Warning] Loading tray open (RING/PERFECT BINDER) */
#define	DI_ST_W_PERFECTBIND_PAPERCUT_COPEN	30225	/* [Warning] Waste paper receptacle open (RING/PERFECT BINDER) */
#define	DI_ST_W_PERFECTBIND_INSERTER_COPEN	30226	/* [Warning] INSERTER cover open (RING/PERFECT BINDER) */
#define	DI_ST_W_PERFECTBIND_INSERTER_UNIT_COPEN 30227	/* [Warning] INSERTER unit cover open (RING/PERFECT BINDER) */

#define	DI_ST_W_RINGBIND_STACKER_FULL		30344	/* [Warning] Stacker full (RING/PERFECT BINDER) */
#define	DI_ST_W_PERFECTBIND_LDTRAY_FULL	30345	/* [Warning] Loading tray full (RING/PERFECT BINDER) */

#define	DI_ST_W_STACKER_PROOFTRAY_FULL		30346	/* [Warning] Output Tray Full (Stacker Proof Tray) */
#define	DI_ST_W_STACKER_SHIFTTRAY_FULL		30348	/* [Warning] Output Tray Full (Stacker Shift Tray) */
#define	DI_ST_W_STACKER2_SHIFTTRAY_FULL	30349	/* [Warning] Output Tray Full (Stacker Shift Tray2) */

#define	DI_ST_W_RINGBIND_ADJUSTTRAY_PEXIST	30502	/* [Warning] Paper exist in adjust tray (RING/PERFECT BINDER) */
#define	DI_ST_W_PERFECTBIND_COLLECTTRAY_PEXIST	30503	/* [Warning] Paper exist in correct tray (RING/PERFECT BINDER) */

#define	DI_ST_LOW_TONER		10006
#define	DI_ST_LOW_TONER_K		10072
#define	DI_ST_LOW_TONER_C		10073
#define	DI_ST_LOW_TONER_M		10074
#define	DI_ST_LOW_TONER_Y		10075
#define	DI_ST_LOW_TONER_R		10078
#define	DI_ST_ADD_STAPLES		40440
/*#define	DI_ST_STAPLE_NEAREND		40440*/
#define	DI_ST_ADD_BOOKLET_STAPLES	40441
#define	DI_ST_ADD_BOOKLET_STAPLES_UPPER	40442
#define	DI_ST_ADD_BOOKLET_STAPLES_LOWER	40443
#define	DI_ST_PUNCH_FULL		40342
#define	DI_ST_STAPLECUT_FULL		30393

#define	DI_ST_RINGBIND_PUNCH_FULL		30394	/* [Warning] Punch receptacle full (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_PAPERCUT_FULL	30395	/* [Warning] Waste paper receptacle full (RING/PERFECT BINDER) */
#define	DI_ST_TRIMMER_PAPERCUT_FULL		30396	/* [Warning] Waste paper receptacle for trimmer is full */

#define	DI_ST_REPLACE_MKIT		30400
#define	DI_ST_REPLACE_PCU		30401
#define	DI_ST_WEB_NEAREND		30402
#define	DI_ST_REPLACE_MKIT_A		30403		/* PCU_COLOR */
#define	DI_ST_REPLACE_MKIT_B		30404		/* DEVELOPMENT_COLOR */
#define	DI_ST_REPLACE_MKIT_C		30405		/* FUSER */
#define	DI_ST_REPLACE_MKIT_D		30406		/* FEEDROLLER */
#define	DI_ST_REPLACE_MKIT_F		30407		/* PCU_K */
#define	DI_ST_REPLACE_FUSING_OIL_UNIT	30408
#define	DI_ST_REPLACE_TRANSFER_UNIT	30409
#define	DI_ST_REPLACE_CHARGER_UNIT	30410
#define	DI_ST_REPLACE_DEVELOPMENT		30441
#define	DI_ST_REPLACE_DEVELOPMENT_COLOR	30411
#define	DI_ST_REPLACE_DEVELOPMENT_K		30412
#define	DI_ST_REPLACE_DEVELOPMENT_C		30413
#define	DI_ST_REPLACE_DEVELOPMENT_M		30414
#define	DI_ST_REPLACE_DEVELOPMENT_Y		30415
#define	DI_ST_REPLACE_NEAR_DEVELOPMENT		30451
#define	DI_ST_REPLACE_NEAR_DEVELOPMENT_COLOR	30421
#define	DI_ST_REPLACE_NEAR_DEVELOPMENT_K	30422
#define	DI_ST_REPLACE_NEAR_DEVELOPMENT_C	30423
#define	DI_ST_REPLACE_NEAR_DEVELOPMENT_M	30424
#define	DI_ST_REPLACE_NEAR_DEVELOPMENT_Y	30425
#define	DI_ST_REPLACE_NEAR_PCU		30426
#define	DI_ST_REPLACE_NEAR_FUSER	30427
#define	DI_ST_REPLACE_NEAR_MID_TRANSFER_UNIT	30428
#define	DI_ST_REPLACE_NEAR_PCU_COLOR	30429

#define	DI_ST_REPLACE_TRANSFER_ROLLER	30416
#define	DI_ST_REPLACE_TRANSFER_BELT	30417
#define	DI_ST_OIL_NEAR_FULL		30418
#define	DI_ST_SUCTION_MOTOR_NEAREND	30419
#define	DI_ST_REPLACE_TRANSFER_CLEANING	30420
#define	DI_ST_REPLACE_NEAR_TRANSFER_CLEANING	30450
#define	DI_ST_REPLACE_FEEDROLLER_LCT		30430	/* Feed Roller PM */
#define	DI_ST_REPLACE_FEEDROLLER_BYPASS	30431
#define	DI_ST_REPLACE_FEEDROLLER_TRAY1		30432
#define	DI_ST_REPLACE_FEEDROLLER_TRAY2		30433
#define	DI_ST_REPLACE_FEEDROLLER_TRAY3		30434
#define	DI_ST_REPLACE_FEEDROLLER_TRAY4		30435
#define	DI_ST_REPLACE_FEEDROLLER_TRAY5		30436
#define	DI_ST_REPLACE_NEAR_MKIT		30440
#define	DI_ST_REPLACE_NEAR_MKIT_B		30442
#define	DI_ST_REPLACE_MAINTENANCE_UNIT		30460
#define	DI_ST_REPLACE_WASTE_FLUID		30461

#define	DI_ST_RINGBIND_RING_END		30446	/* [Warning] Out of binding ring (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_GLUE_END		30447	/* [Warning] Out of binding glue (RING/PERFECT BINDER) */

#define	DI_ST_REPLACE_DEVELOPER_K		30462
#define	DI_ST_REPLACE_DEVELOPER_C		30463
#define	DI_ST_REPLACE_DEVELOPER_M		30464
#define	DI_ST_REPLACE_DEVELOPER_Y		30465

#define	DI_ST_TONER_NEAR_FULL		10032
#define	DI_ST_TONER2_NEAR_FULL		30019

#define DI_ST_SET_FUSERPARAM		30600
#define DI_ST_SD_LICENSE_ERROR		30607
#define DI_ST_RCG_CONNECT_ERROR	30608
#define DI_ST_SUPPLYCALL_ERROR		30609
#define	DI_ST_REMOTECERT_ERROR		30610
#define	DI_ST_PROXY_CONNECT_ERROR	30616
#define	DI_ST_PROXY_AUTH_ERROR		30617
#define	DI_ST_W_HEADPOSITION_UPPER	30618
#define	DI_ST_LOG_DATA_NEAR_FULL	30619
#define	DI_ST_LOG_DATA_FULL		30620
#define	DI_ST_LOG_TRANSFER_FAILED	30621
#define	DI_ST_RELATION_SD_NONE		30622
#define	DI_ST_RELATION_LICENSE_ERROR	30623

#define	DI_ST_PERFECTBIND_ADJUSTGLUE	30624	/* Adjusting temperature of the glue (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_AUTOOUTPUT	30625	/* Auto Output Paper(RING/PERFECT BINDER) */

#define	DI_ST_COLOR_MISREGIST		30606
#define	DI_ST_COLOR_PCU_ERROR		30601
#define	DI_ST_BLACK_PCU_FUSE		30612
#define	DI_ST_COLOR_PCU_FUSE		30611

#define	DI_ST_SHIFT_DISABLE		30743
#define	DI_ST_STAPLE_DISABLE		30740
#define	DI_ST_FINISHER_DISABLE		30744
#define	DI_ST_PUNCH_DISABLE		30746
#define	DI_ST_FINISHER_TRAY_DISABLE	30747	/* Finisher Tray Disable */

#define	DI_ST_PRINTPOST_DISABLE	30750

#define	DI_ST_STAPLE1_DISABLE		30751
#define	DI_ST_STAPLE2_DISABLE		30752

#define	DI_ST_DPX_DISABLE		30130

#define	DI_ST_RINGBIND_PUNCH_NONE	30131	/* punch unit not set(RING/PERFECT BINDER) */
#define	DI_ST_RINGBIND_RING_NONE	30149	/* [Warning] ring unit not set(RING/PERFECT BINDER) */

#define	DI_ST_W_1BIN_NONE		30140	/* 1bin unit none */
#define	DI_ST_W_DEVELOPMENT_R_NONE	30148	/* Development(R) unit none */
#define	DI_ST_DPXREV_DISABLE		30711
#define	DI_ST_BYPASS_DISABLE		30720	/* [Warning] BYPASS broken */
#define	DI_ST_LCT_DISABLE		30721	/* [Warning] LCT broken */
#define	DI_ST_TRAY1_DISABLE		30722	/* [Warning] TRAY1 broken */
#define	DI_ST_TRAY2_DISABLE		30723	/* [Warning] TRAY2 broken */
#define	DI_ST_TRAY3_DISABLE		30724	/* [Warning] TRAY3 broken */
#define	DI_ST_TRAY4_DISABLE		30725	/* [Warning] TRAY4 broken */
#define	DI_ST_TRAY5_DISABLE		30726	/* [Warning] TRAY5 broken */
#define	DI_ST_TRAY6_DISABLE		30727	/* [Warning] TRAY6 broken */
#define	DI_ST_TRAY7_DISABLE		30728	/* [Warning] TRAY7 broken */
#define	DI_ST_INSERTER_DISABLE		30729	/* [Warning] INSERTER broken */
#define	DI_ST_CHARGEUNIT_DISABLE	30763	/* [Warning] MK1 broken */

#define	DI_ST_PERFECTBIND_DISABLE	30767	/* Device Broken (RING/PERFECT BINDER) */
#define	DI_ST_RINGBIND_DISABLE		30768	/* Device Broken (RING/PERFECT BINDER) */

#define	DI_ST_BOOKLET_PROC_WARNING	30970	/* ex. PLOKMATIC */
#define	DI_ST_PUNCH_UNIT_WARNING	30971	/* [Warning] PUNCH UNIT */
#define	DI_ST_W_CTRAY_PE		30990	/* current tray */
#define	DI_ST_W_CTRAY_PE_LCT		30990
#define	DI_ST_W_CTRAY_PE_BYPASS	30991
#define	DI_ST_W_CTRAY_PE_TRAY1		30992
#define	DI_ST_W_CTRAY_PE_TRAY2		30993
#define	DI_ST_W_CTRAY_PE_TRAY3		30994
#define	DI_ST_W_CTRAY_PE_TRAY4		30995
#define	DI_ST_W_CTRAY_PE_TRAY5		30996
#define	DI_ST_W_CTRAY_PE_TRAY6		30997
#define	DI_ST_W_CTRAY_PE_TRAY7		30998

#define	DI_ST_MPT_ADU_DISABLE		30764	/* [Warning] MPT/ADU Motor broken */
#define	DI_ST_FOLD_UNIT_DISABLE	30765	/* [Warning] Fold Unit broken */
#define	DI_ST_SADDLE_DISABLE		30766	/* [Warning] Saddle Stitching Machine broken */
#define	DI_ST_FINISHER_SHIFT_DISABLE	30769	/* Finisher Shift Disable */
#define	DI_ST_STACKER_SHIFT_DISABLE	30770
#define	DI_ST_STACKER2_SHIFT_DISABLE	30771
#define	DI_ST_TRIMMER_DISABLE		30772
#define	DI_ST_MULTIFOLD_UNIT_DISABLE	30773

#define	DI_ST_W_ADD_TONER_K		30012	/* [Warning] Toner(K) empty */
#define	DI_ST_W_ADD_TONER_C		30013	/* [Warning] Toner(C) empty */
#define	DI_ST_W_ADD_TONER_M		30014	/* [Warning] Toner(M) empty */
#define	DI_ST_W_ADD_TONER_Y		30015	/* [Warning] Toner(Y) empty */
#define	DI_ST_W_ADD_TONER_R		30018	/* [Warning] Toner(R) empty */

#define	DI_ST_TONER_END_ONE_SIDE	30020	/* [W] empty one bottle */

#define	DI_ST_W_LCT_NOT_SET		30150	/* LCT is not set Correctly */

#define	DI_ST_W_STACKER_HANDCRAFT_NOT_SET	30167	/* Set Stacker Handcraft correctly */
#define	DI_ST_W_STACKER2_HANDCRAFT_NOT_SET	30168	/* Set Stacker2 Handcraft correctly */

#define	DI_ST_W_STAMP_UNIT_NONE	30166	/* stamp unit not set */

/********************************************

	print and data error

********************************************/
#define	DI_ST_84_WORKERROR		30800
#define	DI_ST_85_GRAPHIC		30801
#define	DI_ST_86_PARAMETER		30802
#define	DI_ST_87_MEMORYOVER		30803
#define	DI_ST_89_MEMORYSWITCH		30804
#define	DI_ST_90_MEDIAFULL		30805
#define	DI_ST_92_MEMORYOVER		30806
#define	DI_ST_93_MEMORYOVER		30807
#define	DI_ST_94_DOWNLOAD		30808
#define	DI_ST_95_FONTERROR		30809
#define	DI_ST_96_MOJISETERROR		30810
#define	DI_ST_96_SELECTERROR		30811
#define	DI_ST_97_ALLOCATION		30812
#define	DI_ST_98_ACCESSERROR		30813
#define	DI_ST_99_WARNING		30814
#define	DI_ST_C0_ERROR			30815
#define	DI_ST_C1_COMMANDERROR		30816
#define	DI_ST_C2_PARAMETERNUMERROR	30817
#define	DI_ST_C3_PARAMETERLIMITERROR	30818
#define	DI_ST_C6_POSITIONERROR		30819
#define	DI_ST_C7_POLYGONSIZEERROR	30820
#define	DI_ST_D0_RESPONSEERROR		30821
#define	DI_ST_D1_COMMANDERROR		30822
#define	DI_ST_D2_INVALIDPARAMTERERROR	30823
#define	DI_ST_D3_PARAMETERLIMITERROR	30824
#define	DI_ST_D4_PARAMTERNUMERROR	30825
#define	DI_ST_DC_FONTSELECTERROR	30826
#define	DI_ST_DD_FONTERROR		30827
#define	DI_ST_DE_PARAMETERLIMITERROR	30828
#define	DI_ST_DF_WORKMEMORYERROR	30829

#define	DI_ST_RCS_85_GRAPHIC		30830
#define	DI_ST_RCS_86_PARAMETER		30831
#define	DI_ST_RCS_91_MEMORYOVER	30832
#define	DI_ST_RTF_92_MEMORYOVER	30833
#define	DI_ST_RTF_99_FATALERROR	30834
#define	DI_ST_RCS_94_DOWNLOAD		30835
#define	DI_ST_9A_RECEIVEERROR		30836
#define	DI_ST_RCS_ROTATE		30837
#define	DI_ST_C8_FONTCACHEERROR	30838
#define	DI_ST_C9_PATTERNCACHEERROR	30839
#define DI_ST_CA_SIZEDECIDEERROR	30840

#define DI_ST_PDF_NO_FILESYSTEM	30841
#define DI_ST_PDF_FILESYSTEM_FULL	30842
#define DI_ST_PDF_INVALID_PASSWORD	30843
#define DI_ST_PDF_OP_NOT_PERMITTED	30844
#define DI_ST_PDF_INTERNAL_ERROR	30845
#define	DI_ST_P1_COMMANDERROR		30846
#define	DI_ST_P2_MEMORYERROR		30847
#define	DI_ST_P3_MEMORYERROR		30848
#define	DI_ST_P4_SENDDATAABORTED	30849
#define	DI_ST_P5_RECVDATAABORTED	30850
#define	DI_ST_9B_AUTH_INVALID		30851
#define DI_ST_PDF_NO_AUTH_PRINT	30852

#define DI_ST_PJL_DECRYPTIONERROR	30916
#define	DI_ST_PPML_NO_FILESYSTEM	30917
#define	DI_ST_PPML_FILESYSTEM_FULL	30918
#define	DI_ST_PPML_SYNTAX_ERROR	30919
#define	DI_ST_PPML_PDL_NOT_SUPPORT	30920

#define	DI_ST_RPS_DISPLAYLISTOVERFLOW	30016

#define	DI_ST_A3_OVERFLOW		30900		/* GPS */
#define	DI_ST_A4_SORTOVER		30901		/* GPS */
#define	DI_ST_A6_PAGEFULL		30902		/* GPS */
#define	DI_ST_A7_DRAWERROR		30903		/* GPS */
#define	DI_ST_A8_LIBRARY		30904		/* GPS */
#define	DI_ST_B6_AUTH_AUTOREGISTFULL	30924		/* GPS */
#define	DI_ST_B7_AUTH_REGISTERED	30923		/* GPS */
#define	DI_ST_B8_AUTH_TIMEOUT		30921		/* GPS */
#define	DI_ST_B9_AUTH_BUSY		30922		/* GPS */
#define	DI_ST_BA_USERACCESS		30905		/* GPS */
#define	DI_ST_BC_SORTERROR		30906		/* GPS */
#define	DI_ST_BD_STAPLEERROR		30907		/* GPS */
#define	DI_ST_BE_PUNCHERROR		30908		/* GPS */
#define	DI_ST_BF_DUPLEXERROR		30909		/* GPS */
#define	DI_ST_BG_FOLDERROR		30915		/* GPS */
#define	DI_ST_BH_WIDFOLDERROR		30926		/* GPS */
#define	DI_ST_BI_MEDIANAMEERROR	30927		/* GPS */
#define	DI_ST_BJ_BILLINGCODEERROR	30928		/* GPS */

#define	DI_ST_BQ_UNCOMPRESSERROR	30931		/* GPS(DEC) */


#define	DI_ST_F0_PRINTERFAXRELEASE	30910		/* GPS */
#define	DI_ST_F8_PRINTERFAXRELEASE	30911		/* GPS */

#define	DI_ST_A9_PAGEOVER		30211		/* dummy for string */
#define	DI_ST_A9_PAGEOVER_PROOF	30211		/* GPS */
#define	DI_ST_A9_PAGEOVER_SECURE	30231		/* GPS */
#define	DI_ST_AA_DOCUMENTNUMOVER	30210		/* dummy for string */
#define	DI_ST_AA_DOCUMENTNUMOVER_PROOF	30210		/* GPS */
#define	DI_ST_AA_DOCUMENTNUMOVER_SECURE	30230	/* GPS */
#define	DI_ST_AB_HDDFULL		30202		/* dummy for string */
#define	DI_ST_AB_HDDFULL_PROOF		30202		/* GPS */
#define	DI_ST_AB_HDDFULL_SECURE	30203		/* GPS */
#define	DI_ST_AC_HDDFULL		30201		/* GPS */
#define	DI_ST_L2_DOCUMENTNUMOVER_CSV	30220		/* GPS */
#define	DI_ST_L1_HDDFULL_CSV		30221		/* GPS */
#define	DI_ST_L3_PAGEOVER_CSV		30222		/* GPS */
#define DI_ST_L4_SIZEERROR_CSV		30223		/* GPS */
#define DI_ST_L5_INVALID_CSV		30224		/* GPS */
#define	DI_ST_M1_HDDFULL_CAP		30204		/* GPS */
#define	DI_ST_M2_DOCUMENTNUMOVER_CAP	30240		/* GPS */
#define	DI_ST_M3_PAGEOVER_CAP		30241		/* GPS */

#define	DI_ST_EA_OUTBINCHANGE		10070		/* GPS */
#define	DI_ST_92_AUTO_JOB_CANCEL	30912		/* GPS */
#define	DI_ST_91_JOB_CANCEL		30913		/* GPS */
#define	DI_ST_AD_STOREDERROR		30232		/* GPS */
#define	DI_ST_AE_OVERLAY_PAGEOVER	30251		/* GPS */
#define	DI_ST_AF_OVERLAY_NUMOVER	30250		/* GPS */
#define	DI_ST_AG_OVERLAY_HDDFULL	30205		/* GPS */
#define	DI_ST_AH_OVERLAY_REGISTERROR	30252		/* GPS */
#define	DI_ST_AI_OUTSIDE_SIZE		30925		/* GPS */

#define	DI_ST_BK_RINGBIND_PUNCHERROR		30853	/* Ring binding/punch conditions error (RING/PERFECT BINDER) */
#define	DI_ST_BL_RINGBIND_PAGEOVER		30855	/* Ring bind page(Paper) max over (RING/PERFECT BINDER) */
#define	DI_ST_BM_RINGBINDERROR			30929	/* Ring bind error (RING/PERFECT BINDER) */
#define	DI_ST_BN_PERFECTBIND_PARAMERROR	30854	/* Perfect binding conditions error (RING/PERFECT BINDER) */
#define	DI_ST_BO_PERFECTBIND_PAGEOVER		30856	/* Ringbind page(paper) max over(RING/PERFECT BINDER) */
#define	DI_ST_UCPPRINTED_ERROR			30857

#define	DI_ST_BP_PERFECTBINDERROR		30930	/* Perfect bind error (RING/PERFECT BINDER) */

#define	DI_ST_BT_MULTIFOLD_UNIT_PARAMERROR		30932		/* */
#define	DI_ST_BU_MULTIFOLD_UNIT_PAGERROR		30933		/* */
#define	DI_ST_BW_MULTIFOLD_UNIT_CONFLICTERROR	30934		/* */
#define	DI_ST_BR_RINGBIND_CONFLICTERROR	30935		/* */
#define	DI_ST_BS_PERFECTBIND_CONFLICTERROR	30936		/* */
#define	DI_ST_BX_TRIMMERERROR			30937		/* */
#define	DI_ST_BV_MULTIFOLD_UNIT_ERROR		30938		/* */
#define	DI_ST_BY_TRIMMER_PARAMERROR		30939		/* */

#define	DI_ST_W_PDL_ERROR		30979		/* PDL */

/********************************************

	error/alert

********************************************/
#define	DI_ST_CHECK_TONER_K		30132
#define	DI_ST_CHECK_TONER_C		30133
#define	DI_ST_CHECK_TONER_M		30134
#define	DI_ST_CHECK_TONER_Y		30135
#define	DI_ST_NO_GENUINE_TONER		30136

#define	DI_ST_STAPLE_BUSY		30301		/* TBD */
#define	DI_ST_FINISHER_BUSY		30302		/* TBD */
#define	DI_ST_INTRAY_BUSY		30303		/* TBD */

#define	DI_ST_RINGBIND_BUSY		30305	/* Ringbind resource busy (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_BUSY		30306	/* Perfectbind resource busy (RING/PERFECT BINDER) */

#define	DI_ST_MULTIFOLD_UNIT_BUSY		30307	/* Waiting for multi-function folding unit resource */
#define	DI_ST_STACKER_BUSY		30308	/* Waiting for stacker resource */

#define	DI_ST_DPX_UOPEN		40260	/* unit open */
#define	DI_ST_DPX_COPEN		40261	/* 40260 -> 40261 */
#define	DI_ST_DPX_ERROR		40711
#define	DI_ST_WEB_END			40402
#define	DI_ST_FIN_PEXIST		40540
#define	DI_ST_DPX_PEXIST		40510
#define	DI_ST_SADDLE_PEXIST		40520

#define	DI_ST_RINGBIND_ADJUSTTRAY_PEXIST	40521	/* [Error] Paper exist in adjust tray (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_COLLECTTRAY_PEXIST	40522	/* [Error] Paper exist in collect tray (RING/PERFECT BINDER) */

#define	DI_ST_STACKER_TRAY_PEXIST	40523	/* [Error] Paper remaining in stacker tray (Stacker 1) */
#define	DI_ST_STACKER2_TRAY_PEXIST	40524	/* [Error] Paper remaining in stacker tray (Stacker 2) */
#define	DI_ST_MULTIFOLD_UNIT_PEXIST		40525	/* [Error] Paper remaining in multi-function folding unit stacker */

#define	DI_ST_ADD_TONER		40010
#define	DI_ST_ADD_TONER_K		40012
#define	DI_ST_ADD_TONER_C		40013
#define	DI_ST_ADD_TONER_M		40014
#define	DI_ST_ADD_TONER_Y		40015
#define	DI_ST_ADD_TONER_R		40018

#define	DI_ST_TONER_FULL		40011
#define	DI_ST_TONER2_FULL		40019	/* 2nd toner bottle full */
#define	DI_ST_E_REPLACE_MKIT		40020
#define	DI_ST_E_REPLACE_MKIT_B		40021
#define	DI_ST_E_REPLACE_FUSING_OIL_UNIT	40023	/* fusing oil */
#define	DI_ST_E_REPLACE_FUSING_UNIT	40025	/* fusing unit */
#define	DI_ST_E_REPLACE_TRANSFER_ROLLER	40027
#define	DI_ST_E_REPLACE_TRANSFER_BELT		40028
#define	DI_ST_OIL_FULL			40029
#define	DI_ST_E_REPLACE_DEVELOPMENT_K	40032
#define	DI_ST_E_REPLACE_DEVELOPMENT_C	40033
#define	DI_ST_E_REPLACE_DEVELOPMENT_M	40034
#define	DI_ST_E_REPLACE_DEVELOPMENT_Y	40035
#define	DI_ST_E_REPLACE_PCU_COLOR	40041
#define	DI_ST_E_REPLACE_PCU_K		40042
#define	DI_ST_E_ADD_STAPLES		40490
#define	DI_ST_E_ADD_BOOKLET_STAPLES	40491
#define	DI_ST_E_ADD_BOOKLET_STAPLES_UPPER	40492
#define	DI_ST_E_ADD_BOOKLET_STAPLES_LOWER	40493
#define	DI_ST_E_PUNCH_FULL		40392
#define	DI_ST_E_STAPLECUT_FULL		40393

#define	DI_ST_PAPER_EMPTY		41000	/* paper empty */
#define	DI_ST_TRAY_ERROR		41000	/* tray error */
#define	DI_ST_TRAY_ERROR_LCT		41000
#define	DI_ST_TRAY_ERROR_BYPASS	41100
#define	DI_ST_TRAY_ERROR_TRAY1		41200
#define	DI_ST_TRAY_ERROR_TRAY2		41300
#define	DI_ST_TRAY_ERROR_TRAY3		41400
#define	DI_ST_TRAY_ERROR_TRAY4		41500
#define	DI_ST_TRAY_ERROR_TRAY5		41600
#define	DI_ST_TRAY_ERROR_TRAY6		41700
#define	DI_ST_TRAY_ERROR_TRAY7		41800
#define	DI_ST_TRAY_ERROR_INSERTER	41900

#define	DI_ST_PAPER_NONE		45000	/* specified size/media none */
#define	DI_ST_PAPER_MEDIA_ERROR	46000	/* tray media mismatch */
#define	DI_ST_PAPER_SIZE_ERROR		47000	/* tray size mismatch */
#define	DI_ST_PAPER_ERROR		48000	/* tray size/media mismatch */

#define	DI_ST_PAPER_EMPTY2		49000	/* paper empty ext (RING/PERFECT BINDER) */

#define	DI_ST_BIN_FULL			40300		/* bin full */
#define	DI_ST_STD_BIN_FULL		40300
#define	DI_ST_1BIN_FULL		40301		/* 1bin */
#define	DI_ST_LOWER_FULL		40302
#define	DI_ST_MBOXPROOF_FULL		40350
#define	DI_ST_MBOX1_FULL		40351
#define	DI_ST_MBOX2_FULL		40352
#define	DI_ST_MBOX3_FULL		40353
#define	DI_ST_MBOX4_FULL		40354
#define	DI_ST_MBOX5_FULL		40355
#define	DI_ST_MBOX6_FULL		40356
#define	DI_ST_MBOX7_FULL		40357
#define	DI_ST_MBOX8_FULL		40358
#define	DI_ST_MBOX9_FULL		40359
#define	DI_ST_SEQUENTIALSTACK_FULL	40370	/* sequential stack */
#define	DI_ST_FIN_MAIN_FULL		40340	/* fin main */
#define	DI_ST_FIN_SHIFT_FULL		40341	/* finisher shift */
#define	DI_ST_FIN_SADDLE_FULL		40343	/* finisher saddle */

#define	DI_ST_RINGBIND_STACKER_FULL	40344	/* [Error] stacker full (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_LDTRAY_FULL	40345	/* [Error] loading tray full (RING/PERFECT BINDER) */

#define	DI_ST_STACKER_PROOF_FULL	40346	/* [Error] Output Tray Full (Stacker Proof Tray)  */
#define	DI_ST_STACKER_SHIFT_FULL	40348	/* [Error] Output Tray Full (Stacker Shift Tray)  */
#define	DI_ST_STACKER2_SHIFT_FULL	40349	/* [Error] Output Tray Full (Stacker2 Shift Tray)  */
#define	DI_ST_MULTIFOLD_UNIT_PROOF_FULL	40362	/* [Error] Output Tray Full (Multi-Function Folding Unit Proof Tray)  */

#define	DI_ST_EXIT_STOPBUTTON		40371	/* pressed button */
#define DI_ST_LIMITLESS_FULL		40380	/* ZAIRE limitless(full) */
#define DI_ST_EMPTYBIN_NONE		40381	/* ZAIRE limitless(no empty) */
#define DI_ST_STAPLETYPE_MISMATCH	40382	/* ZAIRE limitation */
#define DI_ST_CANNOT_CLEAR_STAPLE	40383	/* ZAIRE limitation */
#define DI_ST_FIN_SHIFT_NOT_EMPTY	40384	/* ZAIRE limitless(finisher shift not empty) */

#define	DI_ST_SHIFT_ERROR		40743

#define	DI_ST_COPEN			40200		/* cover open */
#define	DI_ST_FRONT_COPEN		40200
#define	DI_ST_INTERCHANGE_COPEN	40203
#define	DI_ST_EXIT_COPEN		40204
#define	DI_ST_MBOX_COPEN		40250
#define	DI_ST_UPPER_COPEN		40220	/* 1bin */
#define	DI_ST_SIDE_COPEN		40201
#define	DI_ST_TRAY_COPEN		40202
#define	DI_ST_FRONT_SIDE_COPEN		40206
#define	DI_ST_FRONT_L_COPEN		40207
#define	DI_ST_TOP_COPEN		40208
#define	DI_ST_JAMREMOVE_COPEN		40209
#define	DI_ST_BANK_COPEN		40210
#define	DI_ST_BANK2_COPEN		40211	/* 2nd bank cover */
#define	DI_ST_TRAY4_COPEN		40212	/* 4th tray cover */
#define	DI_ST_TRAY5_COPEN		40213	/* 5th tray cover */
#define	DI_ST_INSERTER_SIDE_COPEN	40217
#define	DI_ST_INSERTER_FRONT_COPEN	40218
#define	DI_ST_1BIN_COPEN		40220	/* dummy */

#define	DI_ST_RINGBIND_STACKER_COPEN		40214	/* [Error] Stacker open (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_LDTRAY_COPEN		40215	/* [Error] Loading tray open(RING/PERFECT BINDER) */
#define	DI_ST_RINGBIND_COPEN			40221	/* Ringbind cover open (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_UPPER_COPEN		40222	/* Perfectbind upper cover open (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_RELAY_COPEN		40223	/* Perfectbind relay cover open (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_FRONT_COPEN		40224	/* Perfectbind front cover open (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_PAPERCUT_COPEN	40225	/* [Error] Waste paper receptacle (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_INSERTER_COPEN	40226	/* [Error] INSERTER cover open (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_INSERTER_UNIT_COPEN	40227	/* [Error] INSERTER unit cover open (RING/PERFECT BINDER) */

#define	DI_ST_RELAY_R_COPEN		40231
#define	DI_ST_RELAY_MID_COPEN		40232
#define	DI_ST_RELAY_L_COPEN		40233
#define	DI_ST_FIN_COPEN		40240	/* dummy */
#define	DI_ST_FIN_JOINT_COPEN		40241
#define	DI_ST_FIN_STAPLE_COPEN		40242
#define	DI_ST_FIN_UPPER_COPEN		40243
#define	DI_ST_FIN_ENTER_COPEN		40244
#define	DI_ST_FIN_EXIT_COPEN		40245
#define	DI_ST_FIN_SADDLE_COPEN		40246
#define	DI_ST_POST_MAIN_COPEN		40251
#define	DI_ST_POST_PT_COPEN		40252
#define	DI_ST_POST_RELAY_COPEN		40253
#define	DI_ST_DPX_LEFT_COPEN		40262
#define	DI_ST_DPX_RIGHT_COPEN		40263
#define	DI_ST_CATCH_UP_COPEN		40270

#define	DI_ST_DECURLER_UNIT_COPEN	40273
#define	DI_ST_MULTIFOLD_UNIT_COPEN		40274
#define	DI_ST_TRIMMER_COPEN		40275
#define	DI_ST_STACKER_COPEN		40276
#define	DI_ST_STACKER2_COPEN		40277
#define	DI_ST_STACKER_UPPER_COPEN	40278
#define	DI_ST_STACKER2_UPPER_COPEN	40279

#define	DI_ST_LCTUNIT_COPEN		40280	/* ex. ALASKA-B */
#define	DI_ST_FOLD_COPEN		40290	/* 折り機ドア */
#define	DI_ST_EJECT_COPEN		40291
#define	DI_ST_FOLDER_COPEN		40292	/* 折り機ドア */

#define	DI_ST_FUSER_NONE		40100
#define	DI_ST_PCU_NONE			40101

#define	DI_ST_JAM			42000	/* jam */
#define	DI_ST_FEED_JAM			42000
#define	DI_ST_INNER_JAM		42001
#define	DI_ST_INNER_JAM_C		42002
#define	DI_ST_EXIT_JAM			42004
#define	DI_ST_FINISHER_JAM		42005
#define	DI_ST_MBOX_JAM			42007
#define	DI_ST_DPX_JAM			42009
#define	DI_ST_INSERTER_JAM		42010
#define	DI_ST_FOLD_JAM			42011	/* 折り機ジャム */
#define	DI_ST_BOOKLET_PROC_JAM		42015	/* ex. PLOKMATIC */

#define	DI_ST_RINGBIND_JAM		42020	/* Ringbind JAM (RING/PERFECT BINDER) */
#define	DI_ST_PERFECTBIND_JAM		42021	/* Perfectbind JAM (RING/PERFECT BINDER) */

#define	DI_ST_STACKER_JAM		42022	/* Paper Jam L (Stacker) */
#define	DI_ST_STACKER2_JAM		42023	/* Paper Jam L (Stacker2) */
#define	DI_ST_TRIMMER_JAM		42024	/* Paper Misfeed (Trimmer) */
#define	DI_ST_DECURLER_UNIT_JAM		42025	/* Paper Misfeed (Decurler Unit) */

#define	DI_ST_PAPER_SIZE_JAM		42099

#define	DI_ST_FORBID_DUPLEX		40902
#define	DI_ST_BYPASS_PEXIST		40903
#define	DI_ST_TEMPERATURE_RANGE	40904
#define DI_ST_SAME_TRAY_SELECT		40906
#define	DI_ST_HEADPOSITION_WRONG	40907
#define	DI_ST_HEADPOSITION_UPPER	40908

#define DI_ST_WAITING_KEYCOUNTER	40910
#define DI_ST_WAITING_KEYCARD		40911
#define DI_ST_WAITING_PREPAIDCARD	40912
#define DI_ST_WAITING_COIN		40913
#define DI_ST_WAITING_KCARD_COUNTER	40914
#define DI_ST_WAITING_PCARD_COUNTER	40915
#define DI_ST_WAITING_COIN_COUNTER	40916

#define	DI_ST_OUTPUT_BIN_CLOSE		40920
#define	DI_ST_OUTPUT_BIN_OPEN		40921
#define	DI_ST_FEED_TRAY_CLOSE		40922
#define	DI_ST_FEED_TRAY_OPEN		40923

#define	DI_ST_BOOKLET_PROC_ERROR	40970	/* ex. PLOKMATIC */
#define	DI_ST_PUNCH_UNIT_ERROR		40971	/* Punch Unit Error */
#define	DI_ST_RESET_INDEX_PAPER	40977	/* インデックス紙再セット要求 */

#define	DI_ST_CTRAY_PE			40990	/* current tray PE */
#define	DI_ST_CTRAY_PE_LCT		40990
#define	DI_ST_CTRAY_PE_BYPASS		40991
#define	DI_ST_CTRAY_PE_TRAY1		40992
#define	DI_ST_CTRAY_PE_TRAY2		40993
#define	DI_ST_CTRAY_PE_TRAY3		40994
#define	DI_ST_CTRAY_PE_TRAY4		40995
#define	DI_ST_CTRAY_PE_TRAY5		40996
#define	DI_ST_CTRAY_PE_TRAY6		40997
#define	DI_ST_CTRAY_PE_TRAY7		40998

#define	DI_ST_REGISTGUIDE_OPEN		40137	/* B2 cover open */
#define	DI_ST_1BIN_NONE		40140	/* 1bin unit none */
#define	DI_ST_MID_TRANSFER_UNIT_NONE	40141
#define	DI_ST_DEVELOPMENT_K_NONE	40142	/* Development(K) unit none */
#define	DI_ST_DEVELOPMENT_C_NONE	40143	/* Development(C) unit none */
#define	DI_ST_DEVELOPMENT_M_NONE	40144	/* Development(M) unit none */
#define	DI_ST_DEVELOPMENT_Y_NONE	40145	/* Development(Y) unit none */
#define	DI_ST_DEVELOPMENT_R_NONE	40148	/* Development(R) unit none */
#define	DI_ST_TRANSFER_CLEANING_NONE	40146	/* transfer cleaning unit */
#define	DI_ST_FOLD_UNIT_OPEN		40147	/* 折り機ドア2 */
#define	DI_ST_PCU_COLOR_NONE		40151	/* PCU(COLOR) none */
#define	DI_ST_PCU_K_NONE		40152	/* PCU(K) none */
#define	DI_ST_PCU_C_NONE		40153	/* PCU(C) unit none */
#define	DI_ST_PCU_M_NONE		40154	/* PCU(M) unit none */
#define	DI_ST_PCU_Y_NONE		40155	/* PCU(Y) unit none */
#define	DI_ST_FINISHER_NONE		40156   /* finisher */
#define	DI_ST_FUSING_OIL_UNIT_NONE	40157   /* fusing oil unit */
#define	DI_ST_TRANSFER_UNIT_NONE	40158   /* transfering unit */
#define	DI_ST_TONER_DISPOSAL_NONE	40159   /* toner disposal bottle */
#define	DI_ST_TONER2_DISPOSAL_NONE	40160   /* 2nd toner bottle none */
#define	DI_ST_CHARGER_UNIT_NONE	40161	/* charger unit none */
#define	DI_ST_TONER_SUPPLY_ERROR_K	40162	/* toner supply error (K) */
#define	DI_ST_TONER_SUPPLY_ERROR_C	40163	/* toner supply error (C) */
#define	DI_ST_TONER_SUPPLY_ERROR_M	40164	/* toner supply error (M) */
#define	DI_ST_TONER_SUPPLY_ERROR_Y	40165	/* toner supply error (Y) */

#define	DI_ST_STAMP_UNIT_NONE		40166	/* stamp unit not set */

#define	DI_ST_STACKER_HANDCRAFT_NONE	40167	/* Set Stacker Handcraft correctly (Error) */
#define	DI_ST_STACKER2_HANDCRAFT_NONE	40167	/* Set Stacker2 Handcraft correctly (Error) */
#define	DI_ST_DECURLER_UNIT_NONE	40169	/* Set Decurler Unit correctly (Error) */

#define	DI_ST_TONER_COPEN		40205	/* Toner cover open */ 
#define	DI_ST_BANK_JAM			42008	/* Bank unit jam */
#define	DI_ST_DPXTRANS_JAM		42019	/* Duplex Trans. Unit Jam */
#define	DI_ST_E_CHECK_TONER		40132	/* [Error] Toner unit none (dummy) */
#define	DI_ST_E_CHECK_TONER_K		40132	/* [Error] Toner(K) unit none */
#define	DI_ST_E_CHECK_TONER_C		40133	/* [Error] Toner(C) unit none */
#define	DI_ST_E_CHECK_TONER_M		40134	/* [Error] Toner(M) unit none */
#define	DI_ST_E_CHECK_TONER_Y		40135	/* [Error] Toner(Y) unit none */

#define	DI_ST_E_RINGBIND_RING_NONE		40149	/* [Error] Ring unit not set (RING/PERFECT BINDER) */
#define	DI_ST_E_RINGBIND_PUNCH_FULL		40394	/* [Error] Punch receptacle full (RING/PERFECT BINDER) */
#define	DI_ST_E_PERFECTBIND_PAPERCUT_FULL	40395	/* [Error] Waste paper receptacle full(RING/PERFECT BINDER) */

#define	DI_ST_E_TRIMMER_PAPERCUT_FULL	40396	/* [Error] Waste paper receptacle for trimmer is full */

#define	DI_ST_E_RINGBIND_RING_END		40446	/* [Error] Out of binding ring (RING/PERFECT BINDER) */
#define	DI_ST_E_PERFECTBIND_GLUE_END		40447	/* [Error] Out of binding glue (RING/PERFECT BINDER) */


#define	DI_ST_E_TRAY_DISABLE		40720           /* dummy */
#define	DI_ST_E_BYPASS_DISABLE		40720	/* [Error] BYPASS broken */
#define	DI_ST_E_LCT_DISABLE		40721	/* [Error] LCT broken */
#define	DI_ST_E_TRAY1_DISABLE		40722	/* [Error] TRAY1 broken */
#define	DI_ST_E_TRAY2_DISABLE		40723	/* [Error] TRAY2 broken */
#define	DI_ST_E_TRAY3_DISABLE		40724	/* [Error] TRAY3 broken */
#define	DI_ST_E_TRAY4_DISABLE		40725	/* [Error] TRAY4 broken */
#define	DI_ST_E_TRAY5_DISABLE		40726	/* [Error] TRAY5 broken */
#define	DI_ST_E_TRAY6_DISABLE		40727	/* [Error] TRAY6 broken */
#define	DI_ST_E_TRAY7_DISABLE		40728	/* [Error] TRAY7 broken */
#define	DI_ST_E_INSERTER_DISABLE      	40729	/* [Error] INSERTER broken */
#define	DI_ST_E_CHARGEUNIT_DISABLE	40763	/* [Error] MK1 broken */
#define	DI_ST_DPXTRANS_NONE		40130	/* Duplex Trans unit none */
#define	DI_ST_TRANSFER_BELT_NONE	40136
#define	DI_ST_DISPOSAL_OR_BELT_NONE	40138
					/* toner disposal or transfer belt */
#define	DI_ST_OIL_DISPOSAL_NONE	40139   /* oil bottle none */

#define	DI_ST_E_PAUSEMODE		40978
#define	DI_ST_E_PDL_ERROR		40979		/* PDL */
#define	DI_ST_E_IPDS_CAPTUREFONT_ERROR	40926	/* PDL(IPDS) */

/********************************************

	SC

********************************************/
#define	DI_ST_SC_ERROR			40800	/* not diag */
#define	DI_ST_SC_COMMUNICATION		40801
#define	DI_ST_SC_RESIDENT_FONTROM	50106	/* Resident Font ROM */
#define	DI_ST_SC_DIAG_ERROR		50199	/* diag error */
#endif /* !_DI_ERRORCODE_H_ */
/*
 * Copyright (c) 2000 Ricoh Company, Ltd.  All Rights Reserved.
 */


