/************************************************************************
 * ファイル名   : pageprint.h
 * 機能概要     : GPS - 印刷ページ管理
 * 著作者       : Copyright (C) RICOH CO., LTD. 1999-2001.
 * 設計者       : T.Kitazawa
 * 変更履歴     : 1999-09-27 開始
 *                2002-09-12 Version 1.143 std / 2.35 kipw / 4.41 jupw / 8.43 urpw / 9.20 jcfw / 11.44 kip2w / 12.13 urcw / 13.03 kai3
 *		  2000-07-24 Version 1.34 (Miyazaki)
 ************************************************************************/
/*      */
#ifndef _PAGEPRINT_H
#define _PAGEPRINT_H
#ifdef  __cplusplus
extern "C" {
#endif  /* !__cplusplus */
/*      */
/************************************************************************
 *      Parameter Value Definition
 ************************************************************************/
/*      */
#define GPS_PLOT_NORMAL         (0)     /* 通常印刷、  ファイル削除 */
#define GPS_PLOT_REPLOT         (1)     /* リプロット、ファイル保存、他のファイル作成でファイル削除 */
#define GPS_PLOT_PROOF          (2)     /* １部印刷、  ファイル保存、残部印刷後、ファイル削除 */
#define GPS_PLOT_SECURE         (3)     /* 印刷せず、  ファイル保存、　　印刷後、ファイル削除 */
#define GPS_PLOT_STORED         (4)     /* 印刷せず、  ファイル保存、　　印刷後もファイル保存 */
#define GPS_PLOT_PAUSE          (5)     /* 保留印刷蓄積 */
#define GPS_PLOT_KEEP           (6)     /* 保存印刷蓄積 */
#define GPS_PLOT_FORM           (7)     /* フォーム登録 */
/* OPTION指定 */
#define GPS_PLOT_OPT_MICR       (0x100) /* OPTION指定：MICR印刷 */
/*      */
#define GPS_REPLOT_BIT          (0x80)  /* リプロット指定ビット */
/*      */
#define GPS_PRINT_NORMAL        (0)
#define GPS_PRINT_FORCE         (1)
/*      */
#define GPS_COLOR_K             (0)
#define GPS_COLOR_C             (1)
#define GPS_COLOR_M             (2)
#define GPS_COLOR_Y             (3)
/*      */
#define GPS_PAGE_SUCCESS        (0)
#define GPS_PAGE_BUSY           (-1)
#define GPS_PAGE_FAILURE        (-2)
/*      */
#define GPS_BAND_SUCCESS        (1)
#define GPS_BAND_BUSY           (-1)
#define GPS_BAND_FAIL           (-2)
/*      */
#define GPS_BAND_NO_DRAW        (0)
#define GPS_BAND_DRAW           (1)
#define GPS_BAND_DRAW_CONTINUE  (3)
/*      */
#define GPS_TRAY_FOUND          (0)
#define GPS_TRAY_ERRSKIP        (1)
#define GPS_TRAY_CANCEL         (2)
#define GPS_TRAY_FORCE          (3)
#define GPS_TRAY_ANOTHER        (4)
/*      */
#define	GPS_PAGE_CHAP_OFF		(0)		/* なし */
#define	GPS_PAGE_CHAP_BLANK		(1)		/* 章区切り：印刷しない */
#define	GPS_PAGE_CHAP_COPY		(2)		/* 章区切り：印刷する */
#define	GPS_PAGE_CHAP_DIVIDE	(3)		/* 章分け */
#define	GPS_PAGE_CHAP_SPECIAL	(4)		/* 特定用紙 */

#define	GPS_PAGE_CHAP_SHEET1	(1)		/* 区切り用紙１ */
#define	GPS_PAGE_CHAP_SHEET2	(2)		/* 区切り用紙２ */
#define	GPS_PAGE_CHAP_SHEET3	(3)		/* 区切り用紙３ */
#define	GPS_PAGE_CHAP_SHEET4	(4)		/* 区切り用紙４ */
#define	GPS_PAGE_CHAP_SHEET5	(5)		/* 区切り用紙５ */
#define	GPS_PAGE_CHAP_SHEET6	(6)		/* 区切り用紙６ */
#define	GPS_PAGE_CHAP_SHEET7	(7)		/* 区切り用紙７ */
#define	GPS_PAGE_CHAP_SHEET8	(8)		/* 区切り用紙８ */
#define	GPS_PAGE_CHAP_SHEET9	(9)		/* 区切り用紙９ */
/*      */
/************************************************************************
 *      Structure Type Definition
 ************************************************************************/
/*      */
typedef struct gps_pageparam
{
    unsigned long       flag;           /* 設定するパラメータ */
/*#define GPS_PARAM_GET           (1 <<  0)*/
#define GPS_PARAM_QTY           (1 <<  1)
#define GPS_PARAM_LIMITLESS_EXIT (1 << 2)
#define GPS_PARAM_OUTPUT_TRAY   (1 <<  3)
#define GPS_PARAM_OUTMODE       (1 <<  4)
#define GPS_PARAM_BINDING       (1 <<  5)
#define GPS_PARAM_MARGIN1V      (1 <<  6)
#define GPS_PARAM_MARGIN1H      (1 <<  7)
#define GPS_PARAM_MARGIN2V      (1 <<  8)
#define GPS_PARAM_MARGIN2H      (1 <<  9)
#define GPS_PARAM_COVER         (1 << 10)
#define GPS_PARAM_COVERPRINT    (1 << 11)
#define GPS_PARAM_SLIP          (1 << 12)
#define GPS_PARAM_SHIFTOFF      (1 << 13)
#define GPS_PARAM_FINISH        (1 << 14)
#define GPS_PARAM_STAPLE        (1 << 15)
#define GPS_PARAM_PUNCH         (1 << 16)
#define GPS_PARAM_COVERTRAY     (1 << 17)
#define GPS_PARAM_SLIPTRAY      (1 << 18)
#define GPS_PARAM_MULTI_SIZE    (1 << 19)
#define GPS_PARAM_MULTI_WIDTH   (1 << 20)
#define GPS_PARAM_MULTI_LENGTH  (1 << 21)
#define GPS_PARAM_MULTI_TYPE    (1 << 22)
#define GPS_PARAM_TONERSAVE     (1 << 23)
#define GPS_PARAM_PRIORITY_TRAY (1 << 24)
#define GPS_PARAM_UPSIDEDOWN    (1 << 25)
#define GPS_PARAM_COLORCOUNT    (1 << 26)
#define GPS_PARAM_DOCBODYTRAY   (1 << 27)
#define GPS_PARAM_MIXEDDIRROT   (1 << 28)
#define GPS_PARAM_1STPAGEORDER  (1 << 29)
#define GPS_PARAM_JAMRECOVERY   (1 << 30)
#define GPS_PARAM_ACS           (1 << 31)
    unsigned short      qty;            /* 印刷部数 */
    unsigned char       limitless_exit; /* リミットレス排紙指定 */
#define GPS_LIMITLESS_OFF       (0x00)          /* リミットレスしない */
#define GPS_LIMITLESS_EXIT      (0x10)          /* リミットレス排紙する */
/* 廃止予定ここから */
    unsigned char       input_tray;     /* 給紙トレイ */
    unsigned char       paper_code;     /* 用紙サイズ・コード (paper.h 参照) */
    unsigned short      xw;             /* 用紙幅(0.1mm) (paper.h 参照) */
    unsigned short      yw;             /* 用紙長(0.1mm) (paper.h 参照) */
    unsigned char       paper_type;     /* 紙種 */
/* 廃止予定ここまで */
    unsigned short      output_tray;    /* 排紙トレイ */
#define GPS_BIN_MAIN            (0x0000)        /* 本体排紙(両面/マルチビン) */
#define GPS_BIN_FINISHER        (0x0100)        /* フィニッシャ */
#define GPS_BIN_MAILBOX         (0x0200)        /* メールボックス */
#define GPS_BIN_MULTI           (0x0300)        /* マルチビン(CFトレイ) */
#define GPS_BIN_SUB_FINISHER    (0x0400)        /* サブフィニッシャ */
#define GPS_BIN_MAIN_STD        (0x0000)        /* FD/標準排紙 */
#define GPS_BIN_MAIN_BIN1       (0x0001)        /* 1ビン排紙 */
#define GPS_BIN_MAIN_EXTED      (0x0002)        /* 拡張(ストレート)排紙 */
#define GPS_BIN_FINI_PROOF      (0x0100)        /* プルーフトレイ */
#define GPS_BIN_FINI_SHIFT      (0x0101)        /* シフトトレイ */
#define GPS_BIN_FINI_BOOKLET    (0x0105)        /* ブックレット 0x102から0x105へ変更 2001.12.10 */
#define GPS_BIN_FOLD_STRAIGHT   (0x0106)        /* 折り機:ストレート排紙トレイ */
#define GPS_BIN_FOLD_BELLOWS    (0x0107)        /* 折り機:ジャバラ折り排出トレイ */
#define GPS_BIN_FOLD_BIN        (0x0108)        /* 折り機:１ｂｉｎトレイ */
#define GPS_BIN_MAILBOX1        (0x0201)        /* メールボックス１ */
#define GPS_BIN_MULTI_1         (0x0300)        /* マルチビン１ */
#define GPS_BIN_MULTI_2         (0x0301)        /* マルチビン２ */
#define GPS_BIN_SUBFINI_RING    (0x040C)        /* リングバインダ排紙トレイ */
#define GPS_BIN_SUBFINI_PERF    (0x040F)        /* くるみ製本機排紙トレイ */
/* 廃止予定ここから */
#define GPS_BIN_MAIN_DPX        (0x0080)        /* 両面トレイ */
#define GPS_BIN_FINI_SHIFT2     (0x0102)        /* シフトトレイ２ */
#define GPS_BIN_FINI_STAPLE     (0x0103)        /* ステープルトレイ */
#define GPS_BIN_FINI_STA_SAD    (0x0104)        /* ステープルトレイ (サドル) */
#define GPS_BIN_FINI_SADDLE     (0x0105)        /* サドルトレイ */
/* 廃止予定ここまで */
    unsigned char       outmode;        /* 印刷モード */
#define GPS_OUT_IMGINFO         (0)             /* 画像属性情報の指定に従う */
#define GPS_OUT_SINGLE          (1)             /* 片面印刷 */
#define GPS_OUT_DUPLEX          (2)             /* 両面印刷 */
    unsigned char       binding;        /* 縦とじ方向 */
#define GPS_BIND_LEFT           (0)             /* 左綴じ */
#define GPS_BIND_TOP            (1)             /* 上綴じ */
#define GPS_BIND_RIGHT          (2)             /* 右綴じ */
#define GPS_BIND_BOTTOM         (3)             /* 下綴じ(未使用) */
#define GPS_BIND_LEFTRIGHT      (4)             /* 左右綴じ(RTIFF) */
#define GPS_BIND_TOPBOTTOM      (5)             /* 上下綴じ(RTIFF) */
#define GPS_BIND_OFF            (0xF)           /* 指定なし （gpsPlotChkDirection() の引数で使用） */
/* 互換性の為に残す */
#define GPS_BIND_LR             (0)             /* 左右綴じ(実際は左) */
#define GPS_BIND_TB             (1)             /* 上下綴じ(実際は上) */
    signed short        margin1v;       /* 縦とじ代(両面時、第1面 0.1mm) */
    signed short        margin1h;       /* 横とじ代(　　    〃 　 　   ) */
    signed short        margin2v;       /* 縦とじ代(両面第2面 0.1mm) */
    signed short        margin2h;       /* 横とじ代(　　  〃 　    ) */
    unsigned char       cover;          /* 表紙モード */
#define GPS_COVER_OFF           (0x00)          /* 表紙設定しない */
#define GPS_COVER_FRONT         (0x01)          /* 表紙 */
/*#define GPS_COVER_BACK          (0x02)    */      /* 裏表紙 */
/*#define GPS_COVER_BOTH          (0x03)   */       /* 表裏表紙 */
    unsigned char       coverprint;     /* 表紙画像印刷面 */
#define GPS_COVER_FRONT_D       (0x11)          /* 表紙 */
/*#define GPS_COVER_BACK_R        (0x22) */          /* 裏表紙 */
    unsigned char       cover_tray;     /* 表紙トレイ */
    unsigned char       slip;           /* 合紙モード */
#define GPS_SLIP_OFF            (0x00)          /* OHP合紙しない */
#define GPS_SLIP_ON             (0x01)          /* OHP合紙する */
#define GPS_SLIP_PRINT          (0x11)          /* OHP合紙に印刷する */
    unsigned char       slip_tray;      /* 合紙トレイ */
    unsigned char       shiftoff;       /* フィニッシャーシフトオフ */
#define GPS_SHIFT_ON            (0)             /* シフトオン */
#define GPS_SHIFT_OFF           (1)             /* シフトオフ */
    unsigned char       finish;         /* 仕分け指定 */
#define GPS_FINISH_OFF          (0)             /* 仕分けしない */
#define GPS_SORT                (1)             /* ソート */
#define GPS_STACK               (2)             /* スタック */
#define GPS_ROT_SORT            (3)             /* 回転ソート */
#define GPS_ROT_STACK           (4)             /* 回転スタック */
    unsigned char       staple;         /* ステープル */
#define GPS_STAPLE_OFF              (0)
/*#define GPS_STAPLE_LEFT_TOP       (0) */         /* 左上 */
#define GPS_STAPLE_LEFT_TOP_HORIZ   (1)         /* 左上水平 */
#define GPS_STAPLE_LEFT_TOP_VERT    (2)         /* 左上垂直 */
#define GPS_STAPLE_LEFT_TOP_SLANT   (3)         /* 左上斜め */
/*#define GPS_STAPLE_RIGHT_TOP      (4)   */      /* 右上 */
#define GPS_STAPLE_RIGHT_TOP_HORIZ  (5)         /* 右上水平 */
#define GPS_STAPLE_RIGHT_TOP_VERT   (6)         /* 右上垂直 */
#define GPS_STAPLE_RIGHT_TOP_SLANT  (7)         /* 右上斜め */
/*#define GPS_STAPLE_DOUBLE         (8)   */        /* 右上 */
#define GPS_STAPLE_DOUBLE_LEFT      (9)         /* 左側２個所 */
#define GPS_STAPLE_DOUBLE_TOP       (10)        /* 上側２個所 */
#define GPS_STAPLE_DOUBLE_RIGHT     (11)        /* 右側２個所 */
#define GPS_STAPLE_BOOKLET          (12)        /* 真中２個所 */
#define GPS_STAPLE_NONE             (15)        /* 空打ち */
#define GPS_STAPLE_LEFT_TOP         (16)        /* 左上 */
#define GPS_STAPLE_RIGHT_TOP        (17)        /* 右上 */
#define GPS_STAPLE_CLEAR_BIT        (32)        /* ステープル解除(GPS内部使用) */
/* 廃止予定ここから */
#define GPS_STAPLE_TOP          (1)             /* 奥　　　　(上) */
#define GPS_STAPLE_TOP_SL       (2)             /* 奥斜め　　(上) */
#define GPS_STAPLE_BOTTOM       (3)             /* 手前　　　(下) */
#define GPS_STAPLE_BOTTOM_SL    (4)             /* 手前斜め　(下) */
#define GPS_STAPLE_BOTH         (5)             /* 2個所　　(中央) */
#define GPS_STAPLE_SADDLE       (6)             /* サドル */
/* 廃止予定ここまで */
    unsigned char       punch;          /* パンチ */
#define GPS_PUNCH_OFF           (0)
#define GPS_PUNCH_LEFT          (1)             /* 左辺 */
#define GPS_PUNCH_TOP           (2)             /* 上辺 */
#define GPS_PUNCH_RIGHT         (3)             /* 右辺 */
#define GPS_PUNCH_LEFT_TOP      (4)             /* 左上（１穴パンチ用） */
#define GPS_PUNCH_POS_BIT_MASK  (0x07)          /* パンチ位置指定ビット */
#define GPS_PUNCH_CLEAR_BIT     (0x08)          /* パンチ解除(GPS内部使用) */
#define GPS_PUNCH_TYPE_BIT_MASK (0xF0)          /* パンチ種別指定ビット */
#define GPS_PUNCH_JP2           (0x00)
#define GPS_PUNCH_US2           (0x10)
#define GPS_PUNCH_US3           (0x20)
#define GPS_PUNCH_EU4           (0x30)
#define GPS_PUNCH_NEU4          (0x40)
#define GPS_PUNCH_JP1           (0x50)
#define GPS_PUNCH_MULTI         (0x60)
/* 廃止予定ここから */
#define GPS_PUNCH_ON            (1)
/* 廃止予定ここまで */
/* 廃止予定ここから */
    unsigned char       multi_size;     /* マルチトレイの用紙サイズ・コード (paper.h 参照) */
    unsigned short      multi_width;    /* マルチトレイのフリーサイズ時の用紙幅   (0.1mm単位) */
    unsigned short      multi_length;   /* マルチトレイのフリーサイズ時の用紙高さ (0.1mm単位) */
    unsigned char       multi_type;     /* マルチトレイの紙種 */
/* 廃止予定ここまで */
    unsigned char       tonersave;      /* トナーセーブ */
#define GPS_TONERSAVE_OFF       (0)             /* トナーセーブOFF */
#define GPS_TONERSAVE_MODE1     (1)             /* トナーセーブ・モード1 */
#define GPS_TONERSAVE_MODE2     (2)             /* トナーセーブ・モード2 */
#define GPS_TONERSAVE_SOFT      (3)             /* ソフトトナーセーブを実施した */
    unsigned char       priority_tray;  /* 優先給紙トレイ */
    unsigned char       upsidedown;     /* 180度回転 */
#define GPS_UPSIDE_UP           (0)             /* 回転しない */
#define GPS_UPSIDE_DOWN         (1)             /* 回転する */
    unsigned char       color_count;    /* 色数 */
#define GPS_COLOR_1             (1)             /* 1原色 */
#define GPS_COLOR_RK            (2)             /* 赤黒 */
#define GPS_COLOR_CMYK          (4)             /* 4原色 (CMYK) */
#define GPS_COLOR_XRGB          (5)             /* RGB[COSMOS] */
#define GPS_COLOR_2C            (6)             /* 2原色 */
    unsigned char       docbody_tray;   /* 表合紙時の本文トレイ */
    unsigned char       mixeddirrot;    /* 用紙方向混在時の回転方向 */
#define GPS_MIXED_OFF           (0)
#define GPS_MIXED_LEFT          (1)
#define GPS_MIXED_RIGHT         (2)
    unsigned char       firstpageorder; /* 先頭ページ揃え */
#define GPS_1STPAGEORDER_OFF    (0)
#define GPS_1STPAGEORDER_ON     (1)
    unsigned char       jamrecovery;    /* ジャム・リカバー */
#define GPS_JAMRECOVERY_OFF     (0)
#define GPS_JAMRECOVERY_ON      (1)
    unsigned char       acs;            /* ACS */
#define GPS_ACS_OFF             (0)
#define GPS_ACS_ON              (1)

} gps_pageparam_t, *gps_pageparam_p;
/*      */
typedef struct gps_pagemode
{
    unsigned short      frame_width;    /* フレームの幅   (ドット単位) */
    unsigned short      frame_length;   /* フレームの高さ (ドット単位) */
    unsigned short      band_length;    /* バンドの高さ   (ドット単位) */
    unsigned char       color_count;    /* 色数 */
/*#define GPS_COLOR_1             (1) */            /* 1原色 */
/*#define GPS_COLOR_RK            (2)   */          /* 赤黒 */
/*#define GPS_COLOR_CMYK          (4)     */        /* 4原色 (CMYK) */
    unsigned char       depth;          /* 量子化数 (階調) */
#define GPS_DEPTH_NONE          (0)             /* 画像以外 */
#define GPS_DEPTH_2             (1)             /* ２値 */
#define GPS_DEPTH_4             (2)             /* ４値 */
#define GPS_DEPTH_MC            (3)             /* 多値 (１次圧縮符号) */
#define GPS_DEPTH_M             (4)             /* 多値 (圧縮なし) */
#define GPS_DEPTH_16            (5)             /* １６値 */
#define GPS_DEPTH_256           (6)             /* ２５６値 */
    unsigned char       skip_level;     /* 間引きレベル */
#define GPS_SKIP_NONE           (0x00)          /* 間引きしない */
#define GPS_SKIP_X              (0x01)          /* 副走査を間引く */
#define GPS_SKIP_Y              (0x02)          /* 主走査を間引く */
#define GPS_SKIP_XY             (0x03)          /* 主副走査を間引く */
    unsigned char       rotate;         /* 回転 */
#define GPS_ROT_0               (0)
#define GPS_ROT_90              (1)
#define GPS_ROT_180             (2)
#define GPS_ROT_270             (3)
    unsigned char       face;           /* 印刷面 */
#define GPS_FACE_SINGLE         (0)             /* 片面 */
#define GPS_FACE_DPX1ST         (1)             /* 両面第１面 */
#define GPS_FACE_DPX2ND         (2)             /* 両面第２面 */
/* 廃止予定ここから */
    unsigned char       upsidedown;     /* 180度回転 */
/*#define GPS_UPSIDE_UP           (0)      */       /* 回転しない */
/*#define GPS_UPSIDE_DOWN         (1)        */     /* 回転する */
/* 廃止予定ここまで */

                                        /* リアレンジマトリクスパターンID */
                                        /* ID = 0 リアレンジOFF */
    unsigned short      ra_id_k;                /* K plane */
    unsigned short      ra_id_c;                /* C plane */
    unsigned short      ra_id_m;                /* M plane */
    unsigned short      ra_id_y;                /* Y plane */
                                        /* フレームとリアレンジマトリクスのオフセット */
    unsigned char       ra_offx_k;              /* 主走査方向 K plane */
    unsigned char       ra_offy_k;              /* 副走査方向 K plane */
    unsigned char       ra_offx_c;              /* 主走査方向 C plane */
    unsigned char       ra_offy_c;              /* 副走査方向 C plane */
    unsigned char       ra_offx_m;              /* 主走査方向 M plane */
    unsigned char       ra_offy_m;              /* 副走査方向 M plane */
    unsigned char       ra_offx_y;              /* 主走査方向 Y plane */
    unsigned char       ra_offy_y;              /* 副走査方向 Y plane */

} gps_pagemode_t, *gps_pagemode_p;
/*      */
typedef struct gps_pageinfo
{
    unsigned char       paper_code;     /* 用紙サイズ・コード (paper.h 参照) */
    unsigned short      paper_width;    /* フリーサイズ時の用紙幅   (0.1mm単位) */
    unsigned short      paper_length;   /* フリーサイズ時の用紙高さ (0.1mm単位) */
    unsigned short      frame_width;    /* フレームの幅   (ドット単位) */
    unsigned short      frame_length;   /* フレームの高さ (ドット単位) */
    unsigned short      band_length;    /* バンドの高さ   (ドット単位) */
    unsigned long       line_size;      /* 物理フレーム幅 (バイト数) */
    unsigned long       xoffset;        /* 水平方向オフセット (ドット単位) */
    unsigned long       yoffset;        /* 垂直方向オフセット (ドット単位) */
    unsigned short      resolution_x;   /* X方向解像度 (25.4mmあたりのドット数) */
    unsigned short      resolution_y;   /* Y方向解像度 (25.4mmあたりのドット数) */
    unsigned char       compress;       /* 圧縮 */
#define GPS_COMP_NONE           (0)             /* 圧縮なし */
#define GPS_COMP_K4             (4)
    unsigned char       color;          /* 使用カラー（プレーン） */
#define GPS_CB_K                (0x01)
#define GPS_CB_C                (0x02)
#define GPS_CB_M                (0x04)
#define GPS_CB_Y                (0x08)
    unsigned char       fci;            /* FCI */
#define GPS_FCI_OFF             (0)
#define GPS_FCI_ON              (1)
    unsigned char       input_tray;     /* 給紙トレイ */
#define GPS_TRAY_MAN            (0)             /* 手差し給紙トレイ */
#define GPS_TRAY_1              (1)             /* 本体第１給紙トレイ */
#define GPS_TRAY_2              (2)             /* 本体第２給紙トレイ */
#define GPS_TRAY_3              (3)             /* 本体第３給紙トレイ */
#define GPS_TRAY_4              (4)             /* 本体第４給紙トレイ */
#define GPS_TRAY_5              (5)             /* 本体第５給紙トレイ */
#define GPS_TRAY_6              (6)             /* 本体第６給紙トレイ */
#define GPS_TRAY_7              (7)             /* 本体第７給紙トレイ */
#define GPS_TRAY_LCT            (0x0A)          /* 大量給紙トレイ */
#define GPS_TRAY_AUTO           (0x0F)          /* 自動用紙選択 */
#define GPS_TRAY_INSERTER       (0x10)          /* 合紙挿入ユニット */
#define GPS_TRAY_INSERTER2      (0x11)          /* 合紙挿入ユニット（２段）*/
#define GPS_TRAY_PERF_INSERTER  (0x12)          /* くるみインサータ上段 */
#define GPS_TRAY_PERF_INSERTER2 (0x13)          /* くるみインサータ下段 */
    unsigned char       paper_type;     /* 紙種 */
#define GPS_PAPER_AUTO					(0x00)	/* 普通紙／再生紙 */
#define GPS_PAPER_NORMAL				(0x01)	/* 普通紙 */
#define GPS_PAPER_RECYCLE				(0x02)	/* 再生紙 */
#define GPS_PAPER_SPECIAL				(0x03)	/* 特殊紙 */
#define GPS_PAPER_TRACING				(0x04)	/* トレーシング紙 */
#define GPS_PAPER_OHP					(0x05)	/* OHP */
#define GPS_PAPER_LABEL					(0x06)	/* ラベル紙 */
#define GPS_PAPER_BOND					(0x07)	/* ボンド紙 */
#define GPS_PAPER_CARDSTOCK				(0x08)	/* カードストック */
#define GPS_PAPER_CARDBOARD 			(0x09)	/* 厚紙 */
#define GPS_PAPER_PREPRINT				(0x0A)	/* 印刷済み紙 */
#define GPS_PAPER_LETTER_HEAD			(0x0B)	/* レターヘッド紙 */
#define GPS_PAPER_LTHEAD				(0x0B)	/* 廃止予定 */
#define GPS_PAPER_PUNCH					(0x0C)	/* パンチ済み紙 */
#define GPS_PAPER_PREPUNCH				(0x0C)	/* 廃止予定 */
#define GPS_PAPER_TAB					(0x0D)	/* タブ紙 */
#define GPS_PAPER_COLOR					(0x0E)	/* 色紙 */
#define GPS_PAPER_NORMAL2ND				(0x0F)	/* 普通紙(裏面) */
#define GPS_PAPER_CARDBOARD2ND			(0x10)	/* 厚紙(裏面) */
#define GPS_PAPER_THIN 					(0x11)	/* 薄紙 */
#define GPS_PAPER_GLOSSY 				(0x12)	/* 光沢紙 */
#define GPS_PAPER_USED					(0x13)	/* 裏紙（使用済み） */
#define GPS_PAPER_POSTCARD				(0x14)	/* ハガキ */
#define GPS_PAPER_POSTCARD2ND			(0x15)	/* ハガキ(裏面) */
#define GPS_PAPER_CARDBOARD2			(0x16)	/* 厚紙２ */
#define GPS_PAPER_FILM					(0x17)	/* フィルム紙（図面コピー用） */
#define GPS_PAPER_INKPOST				(0x18)	/* インクジェット用はがき */
#define GPS_PAPER_HG_NORMAL				(0x19)	/* HG普通紙 */
#define GPS_PAPER_ENVELOPE				(0x1A)	/* 封筒 */
#define GPS_PAPER_CARDBOARD3			(0x1B)	/* 厚紙３ */
#define GPS_PAPER_SPECIAL2				(0x1C)	/* 特殊紙２ */
#define GPS_PAPER_SPECIAL3				(0x1D)	/* 特殊紙３ */
#define GPS_PAPER_MIDDLETHICK			(0x1E)	/* 中厚口 */
#define GPS_PAPER_COATED				(0x1F)	/* コート紙 */
#define GPS_PAPER_CARDBOARD2REV			(0x20)	/* 厚紙２(裏面) */
#define GPS_PAPER_CARDBOARD3REV			(0x21)	/* 厚紙３(裏面) */
#define GPS_PAPER_NORMAL2				(0x22)	/* 普通紙２ */
#define GPS_PAPER_THICKGLOSSY			(0x23)	/* 厚手光沢紙 */
#define GPS_PAPER_SPECIAL4				(0x24)	/* 特殊紙４ */
#define GPS_PAPER_SPECIAL5				(0x25)	/* 特殊紙５ */
#define GPS_PAPER_SPECIAL6				(0x26)	/* 特殊紙６ */

#define GPS_PAPER_USER_DEF1				(0x30)	/* ユーザ指定１ */
#define GPS_PAPER_USER_DEF2				(0x31)	/* ユーザ指定２ */
#define GPS_PAPER_USER_DEF3				(0x32)	/* ユーザ指定３ */
#define GPS_PAPER_USER_DEF4				(0x33)	/* ユーザ指定４ */
#define GPS_PAPER_USER_DEF5				(0x34)	/* ユーザ指定５ */
#define GPS_PAPER_USER_DEF6				(0x35)	/* ユーザ指定６ */
#define GPS_PAPER_USER_DEF7				(0x36)	/* ユーザ指定７ */
#define GPS_PAPER_USER_DEF8				(0x37)	/* ユーザ指定８ */
#define GPS_PAPER_USER_DEF0				(0x38)	/* ユーザ指定０(未登録カスタム紙種) */

#define GPS_PAPER_COLOR1				(0x40)	/* 色紙１	*/
#define GPS_PAPER_COLOR2				(0x41)	/* 色紙２	*/

#define GPS_PAPER_COLOR_WHITE			(0x50)	/* 使用不可(標準) */
#define GPS_PAPER_COLOR_YELLOW			(0x51)	/* 黄 */
#define GPS_PAPER_COLOR_GREEN			(0x52)	/* 緑 */
#define GPS_PAPER_COLOR_BLUE			(0x53)	/* 青 */
#define GPS_PAPER_COLOR_PURPLE			(0x54)	/* 紫 */
#define GPS_PAPER_COLOR_IVORY			(0x55)	/* アイボリー */
#define GPS_PAPER_COLOR_ORANGE			(0x56)	/* 橙 */
#define GPS_PAPER_COLOR_PINK			(0x57)	/* 桃 */
#define GPS_PAPER_COLOR_RED				(0x58)	/* 赤 */
#define GPS_PAPER_COLOR_GRAY			(0x59) 	/* 灰 */

#define GPS_PAPER_GLOSSY_COATED			(0x60)	/* コート紙(グロス) */
#define GPS_PAPER_THICK_GLOSSY_COATED	(0x61)	/* コート紙(グロス厚紙) */
#define GPS_PAPER_MAT_COATED			(0x62)	/* コート紙(マット) */
#define GPS_PAPER_THICK_MAT_COATED		(0x63)	/* コート紙(マット厚紙) */
#define GPS_PAPER_WATER_PROOF			(0x64)	/* 耐水紙 */
#define GPS_PAPER_CARDBOARD4			(0x65)	/* 厚紙4  */
#define GPS_PAPER_CARDBOARD4REV			(0x66)	/* 厚紙4裏面 */
#define GPS_PAPER_COATED_HIGH_GLOSSY	(0x67)	/* コート紙(高グロス) */

#define GPS_PAPER_SEMIGLOSSY			(0x68)	/* フォト光沢紙・半光沢紙 */
#define GPS_PAPER_INKJETPLAIN			(0x69)	/* インクジェット普通紙 */
#define GPS_PAPER_MONO_TRACING			(0x6A)	/* トレペ(モノクロ) */
#define GPS_PAPER_COLOR_TRACING			(0x6B)	/* トレペ(カラー) */
#define GPS_PAPER_MATFILM				(0x6C)	/* マットフィルム */
#define GPS_PAPER_CADCOATED				(0x6D)	/* コート紙(CAD) */

#define GPS_PAPER_NONE					(0x80)	/* トレイに設定されている紙種(特定PDLかつトレイ指定時のみ使用可) */

#define	GPS_PAPER_USER_DEF9				(0x81)	/* ユーザ指定９(IMSS) */
#define	GPS_PAPER_USER_DEF10			(0x82)	/* ユーザ指定１０(IMSS) */
#define	GPS_PAPER_USER_DEF11			(0x83)	/* ユーザ指定１１(IMSS) */
#define	GPS_PAPER_USER_DEF12			(0x84)	/* ユーザ指定１２(IMSS) */
#define	GPS_PAPER_USER_DEF13			(0x85)	/* ユーザ指定１３(IMSS) */
#define	GPS_PAPER_USER_DEF14			(0x86)	/* ユーザ指定１４(IMSS) */
#define	GPS_PAPER_USER_DEF15			(0x87)	/* ユーザ指定１５(IMSS) */
#define	GPS_PAPER_USER_DEF16			(0x88)	/* ユーザ指定１６(IMSS) */
#define	GPS_PAPER_USER_DEF17			(0x89)	/* ユーザ指定１７(IMSS) */
#define	GPS_PAPER_USER_DEF18			(0x8A)	/* ユーザ指定１８(IMSS) */
#define	GPS_PAPER_USER_DEF19			(0x8B)	/* ユーザ指定１９(IMSS) */
#define	GPS_PAPER_USER_DEF20			(0x8C)	/* ユーザ指定２０(IMSS) */
#define	GPS_PAPER_USER_DEF21			(0x8D)	/* ユーザ指定２１(IMSS) */
#define	GPS_PAPER_USER_DEF22			(0x8E)	/* ユーザ指定２２(IMSS) */
#define	GPS_PAPER_USER_DEF23			(0x8F)	/* ユーザ指定２３(IMSS) */
#define	GPS_PAPER_USER_DEF24			(0x90)	/* ユーザ指定２４(IMSS) */
#define	GPS_PAPER_USER_DEF25			(0x91)	/* ユーザ指定２５(IMSS) */
#define	GPS_PAPER_USER_DEF26			(0x92)	/* ユーザ指定２６(IMSS) */
#define	GPS_PAPER_USER_DEF27			(0x93)	/* ユーザ指定２７(IMSS) */
#define	GPS_PAPER_USER_DEF28			(0x94)	/* ユーザ指定２８(IMSS) */
#define	GPS_PAPER_USER_DEF29			(0x95)	/* ユーザ指定２９(IMSS) */
#define	GPS_PAPER_USER_DEF30			(0x96)	/* ユーザ指定３０(IMSS) */
#define	GPS_PAPER_USER_DEF31			(0x97)	/* ユーザ指定３１(IMSS) */
#define	GPS_PAPER_USER_DEF32			(0x98)	/* ユーザ指定３２(IMSS) */
#define	GPS_PAPER_USER_DEF33			(0x99)	/* ユーザ指定３３(IMSS) */
#define	GPS_PAPER_USER_DEF34			(0x9A)	/* ユーザ指定３４(IMSS) */
#define	GPS_PAPER_USER_DEF35			(0x9B)	/* ユーザ指定３５(IMSS) */
#define	GPS_PAPER_USER_DEF36			(0x9C)	/* ユーザ指定３６(IMSS) */
#define	GPS_PAPER_USER_DEF37			(0x9D)	/* ユーザ指定３７(IMSS) */
#define	GPS_PAPER_USER_DEF38			(0x9E)	/* ユーザ指定３８(IMSS) */
#define	GPS_PAPER_USER_DEF39			(0x9F)	/* ユーザ指定３９(IMSS) */
#define	GPS_PAPER_USER_DEF40			(0xA0)	/* ユーザ指定４０(IMSS) */
#define	GPS_PAPER_USER_DEF41			(0xA1)	/* ユーザ指定４１(IMSS) */
#define	GPS_PAPER_USER_DEF42			(0xA2)	/* ユーザ指定４２(IMSS) */
#define	GPS_PAPER_USER_DEF43			(0xA3)	/* ユーザ指定４３(IMSS) */
#define	GPS_PAPER_USER_DEF44			(0xA4)	/* ユーザ指定４４(IMSS) */
#define	GPS_PAPER_USER_DEF45			(0xA5)	/* ユーザ指定４５(IMSS) */
#define	GPS_PAPER_USER_DEF46			(0xA6)	/* ユーザ指定４６(IMSS) */
#define	GPS_PAPER_USER_DEF47			(0xA7)	/* ユーザ指定４７(IMSS) */
#define	GPS_PAPER_USER_DEF48			(0xA8)	/* ユーザ指定４８(IMSS) */
#define	GPS_PAPER_USER_DEF49			(0xA9)	/* ユーザ指定４９(IMSS) */
#define	GPS_PAPER_USER_DEF50			(0xAA)	/* ユーザ指定５０(IMSS) */
#define	GPS_PAPER_USER_DEF51			(0xAB)	/* ユーザ指定５１(IMSS) */
#define	GPS_PAPER_USER_DEF52			(0xAC)	/* ユーザ指定５２(IMSS) */
#define	GPS_PAPER_USER_DEF53			(0xAD)	/* ユーザ指定５３(IMSS) */
#define	GPS_PAPER_USER_DEF54			(0xAE)	/* ユーザ指定５４(IMSS) */
#define	GPS_PAPER_USER_DEF55			(0xAF)	/* ユーザ指定５５(IMSS) */
#define	GPS_PAPER_USER_DEF56			(0xB0)	/* ユーザ指定５６(IMSS) */
#define	GPS_PAPER_USER_DEF57			(0xB1)	/* ユーザ指定５７(IMSS) */
#define	GPS_PAPER_USER_DEF58			(0xB2)	/* ユーザ指定５８(IMSS) */
#define	GPS_PAPER_USER_DEF59			(0xB3)	/* ユーザ指定５９(IMSS) */
#define	GPS_PAPER_USER_DEF60			(0xB4)	/* ユーザ指定６０(IMSS) */
#define	GPS_PAPER_USER_DEF61			(0xB5)	/* ユーザ指定６１(IMSS) */
#define	GPS_PAPER_USER_DEF62			(0xB6)	/* ユーザ指定６２(IMSS) */
#define	GPS_PAPER_USER_DEF63			(0xB7)	/* ユーザ指定６３(IMSS) */
#define	GPS_PAPER_USER_DEF64			(0xB8)	/* ユーザ指定６４(IMSS) */
#define	GPS_PAPER_USER_DEF65			(0xB9)	/* ユーザ指定６５(IMSS) */
#define	GPS_PAPER_USER_DEF66			(0xBA)	/* ユーザ指定６６(IMSS) */
#define	GPS_PAPER_USER_DEF67			(0xBB)	/* ユーザ指定６７(IMSS) */
#define	GPS_PAPER_USER_DEF68			(0xBC)	/* ユーザ指定６８(IMSS) */
#define	GPS_PAPER_USER_DEF69			(0xBD)	/* ユーザ指定６９(IMSS) */
#define	GPS_PAPER_USER_DEF70			(0xBE)	/* ユーザ指定７０(IMSS) */
#define	GPS_PAPER_USER_DEF71			(0xBF)	/* ユーザ指定７１(IMSS) */
#define	GPS_PAPER_USER_DEF72			(0xC0)	/* ユーザ指定７２(IMSS) */
#define	GPS_PAPER_USER_DEF73			(0xC1)	/* ユーザ指定７３(IMSS) */
#define	GPS_PAPER_USER_DEF74			(0xC2)	/* ユーザ指定７４(IMSS) */
#define	GPS_PAPER_USER_DEF75			(0xC3)	/* ユーザ指定７５(IMSS) */
#define	GPS_PAPER_USER_DEF76			(0xC4)	/* ユーザ指定７６(IMSS) */
#define	GPS_PAPER_USER_DEF77			(0xC5)	/* ユーザ指定７７(IMSS) */
#define	GPS_PAPER_USER_DEF78			(0xC6)	/* ユーザ指定７８(IMSS) */
#define	GPS_PAPER_USER_DEF79			(0xC7)	/* ユーザ指定７９(IMSS) */
#define	GPS_PAPER_USER_DEF80			(0xC8)	/* ユーザ指定８０(IMSS) */
#define	GPS_PAPER_USER_DEF81			(0xC9)	/* ユーザ指定８１(IMSS) */
#define	GPS_PAPER_USER_DEF82			(0xCA)	/* ユーザ指定８２(IMSS) */
#define	GPS_PAPER_USER_DEF83			(0xCB)	/* ユーザ指定８３(IMSS) */
#define	GPS_PAPER_USER_DEF84			(0xCC)	/* ユーザ指定８４(IMSS) */
#define	GPS_PAPER_USER_DEF85			(0xCD)	/* ユーザ指定８５(IMSS) */
#define	GPS_PAPER_USER_DEF86			(0xCE)	/* ユーザ指定８６(IMSS) */
#define	GPS_PAPER_USER_DEF87			(0xCF)	/* ユーザ指定８７(IMSS) */
#define	GPS_PAPER_USER_DEF88			(0xD0)	/* ユーザ指定８８(IMSS) */
#define	GPS_PAPER_USER_DEF89			(0xD1)	/* ユーザ指定８９(IMSS) */
#define	GPS_PAPER_USER_DEF90			(0xD2)	/* ユーザ指定９０(IMSS) */
#define	GPS_PAPER_USER_DEF91			(0xD3)	/* ユーザ指定９１(IMSS) */
#define	GPS_PAPER_USER_DEF92			(0xD4)	/* ユーザ指定９２(IMSS) */
#define	GPS_PAPER_USER_DEF93			(0xD5)	/* ユーザ指定９３(IMSS) */
#define	GPS_PAPER_USER_DEF94			(0xD6)	/* ユーザ指定９４(IMSS) */
#define	GPS_PAPER_USER_DEF95			(0xD7)	/* ユーザ指定９５(IMSS) */
#define	GPS_PAPER_USER_DEF96			(0xD8)	/* ユーザ指定９６(IMSS) */
#define	GPS_PAPER_USER_DEF97			(0xD9)	/* ユーザ指定９７(IMSS) */
#define	GPS_PAPER_USER_DEF98			(0xDA)	/* ユーザ指定９８(IMSS) */
#define	GPS_PAPER_USER_DEF99			(0xDB)	/* ユーザ指定９９(IMSS) */
#define	GPS_PAPER_USER_DEF100			(0xDC)	/* ユーザ指定１００(IMSS) */

/*#define GPS_PAPER_DEPEND      (0xFF)*/          /* 設定されている紙種 */
    unsigned char       limitless_feed; /* リミットレス給紙 */
#define GPS_LIMITLESS_OFF       (0x00)          /* リミットレスしない */
#define GPS_LIMITLESS_FEED      (0x01)          /* リミットレス給紙する */
    unsigned short      paper_count;    /* 出力枚数 */
    unsigned char       count_off;      /* ページカウント */
#define GPS_COUNT_ON            (0)             /* カウントする */
#define GPS_COUNT_OFF           (1)             /* カウントしない */

} gps_pageinfo_t, *gps_pageinfo_p;
/*      */
/*
 * 引数の定義
 */
/* direction */
#define GPS_ROT_ERROR	(0)						/* エラー */
#define GPS_ROT_0B		(1<<GPS_ROT_0)			/* ０度 */
#define GPS_ROT_90B		(1<<GPS_ROT_90)			/* ９０度 */
#define GPS_ROT_180B	(1<<GPS_ROT_180)		/* １８０度 */
#define GPS_ROT_270B	(1<<GPS_ROT_270)		/* ２７０度 */
#define GPS_ROT_ALL		(GPS_ROT_0B|GPS_ROT_90B|GPS_ROT_180B|GPS_ROT_270B)	/* 回転処理不必要 */
#define GPS_ROT_NG		(0x80)					/* 回転処理不可 */


typedef struct gps_chkdirprm_tag
{
	unsigned long	flag;					/* 設定するパラメータ */
#define GPS_CHKDIR_STAPLE		(1<<0)
#define GPS_CHKDIR_PUNCH		(1<<1)
#define GPS_CHKDIR_BINDING		(1<<2)
#define GPS_CHKDIR_RESOLUTION	(1<<3)
#define GPS_CHKDIR_TRAY			(1<<4)
#define GPS_CHKDIR_DEPTH		(1<<5)
#define GPS_CHKDIR_DMY			(1<<31)

	int				psize;					/* 用紙サイズ(必須) */
	unsigned short	pwidth;					/* フリー用紙幅(0.1mm単位) */
	unsigned short	plength;				/* フリー用紙長(0.1mm単位) */

	unsigned char	orientation;			/* オリエンテーション(必須) */
#define GPS_ORIENTATION_PORTRAIT	(1<<0)
#define GPS_ORIENTATION_LANDSCAPE	(1<<1)

	unsigned char	staple;					/* ステープル(flagにて設定) */
#ifdef notuse   /* See pageprint.h */
#define GPS_STAPLE_OFF				(0)		/* なし */
#define GPS_STAPLE_LEFT_TOP_HORIZ	(1)		/* 使用は推奨しない */
#define GPS_STAPLE_LEFT_TOP_VERT	(2)		/* 使用は推奨しない */
#define GPS_STAPLE_LEFT_TOP_SLANT	(3)		/* 左上斜め */
#define GPS_STAPLE_RIGHT_TOP_HORIZ	(5)		/* 使用は推奨しない */
#define GPS_STAPLE_RIGHT_TOP_VERT	(6)		/* 使用は推奨しない */
#define GPS_STAPLE_RIGHT_TOP_SLANT	(7)		/* 右上斜め */
#define GPS_STAPLE_DOUBLE_LEFT		(9)		/* 左側２個所 */
#define GPS_STAPLE_DOUBLE_TOP		(10)	/* 上側２個所 */
#define GPS_STAPLE_DOUBLE_RIGHT		(11)	/* 右側２個所 */
#define GPS_STAPLE_BOOKLET			(12)	/* 真中２個所 */
#define GPS_STAPLE_LEFT_TOP			(16)	/* 左上 */
#define GPS_STAPLE_RIGHT_TOP		(17)	/* 右上 */
#endif

	unsigned char	punch;					/* パンチ(flagにて設定) */
#ifdef notuse   /* See pageprint.h */
#define GPS_PUNCH_OFF		(0)				/* なし */
#define GPS_PUNCH_LEFT		(1)				/* 左辺 */
#define GPS_PUNCH_TOP		(2)				/* 上辺 */
#define GPS_PUNCH_RIGHT		(3)				/* 右辺 */
#define GPS_PUNCH_LEFT_TOP	(4)                             /* 左上（１穴パンチ用） */
#define GPS_PUNCH_JP2		(0x00)			/* 上位のパンチ種類の指定はあってもなくても良い */
#define GPS_PUNCH_US2		(0x10)
#define GPS_PUNCH_US3		(0x20)
#define GPS_PUNCH_EU4		(0x30)
#define GPS_PUNCH_NEU4		(0x40)
#define GPS_PUNCH_JP1		(0x50)
#endif

	unsigned char	binding;				/* とじ方向(flagにて設定) */
	/* 片面の場合には flag を立てないか「指定なし」を指定すること */
#ifdef notuse   /* See pageprint.h */
#define GPS_BIND_LEFT			(0)			/* 左綴じ */
#define GPS_BIND_TOP			(1)			/* 上綴じ */
#define GPS_BIND_RIGHT			(2)			/* 右綴じ */
#define GPS_BIND_BOTTOM			(3)			/* 下綴じ(未使用) */
#define GPS_BIND_LEFTRIGHT		(4)			/* 左右綴じ(RTIFF) */
#define GPS_BIND_TOPBOTTOM		(5)			/* 上下綴じ(RTIFF) */
#define GPS_BIND_OFF			(0xF)		/* 指定なし(gpsPlotChkDirection()用) */
#endif

	unsigned char	dmy;					/* リサーブ */
	unsigned short	resX;					/* X 方向の解像度(flagにて設定, resYも設定する事) */
	unsigned short	resY;					/* Y 方向の解像度(1200dpiの時は1200) */

	unsigned char	tray;					/* === 相談なく使用する事を禁ずる === 給紙トレイ(flagにて設定, GPS_TRAY_MAN, GPS_TRAY_1 ... GPS_TRAY_AUTO) */

	unsigned char	depth;					/* 階調(flagにて設定) */
#ifdef notuse	/* See pageprint.h */
#define GPS_DEPTH_2				(1)			/* ２値(1bit) */
#define GPS_DEPTH_4				(2)			/* ４値(2bit) */
#define GPS_DEPTH_16				(5)			/* １６値(4bit) */
#define GPS_DEPTH_256				(6)			/* ２５６値(8bit) */
#endif

	unsigned char	rsv[6];					/* リザーブ */
} gps_chkdirprm_t, *gps_chkdirprm_p;

/*--------------------------------------------------------------------------------*/

/* --綴じ代-- */
typedef struct tgGpsMargin
{
	signed short		margin1v;		/* 縦とじ代(両面時、第1面 0.1mm単位) */
	signed short		margin1h;		/* 横とじ代(　　    〃 　 　   ) */
	signed short		margin2v;		/* 縦とじ代(両面第2面 0.1mm単位) */
	signed short		margin2h;		/* 横とじ代(　　  〃 　    ) */
} gpsMargin;

/* --表紙-- */
typedef struct tgGpsCover
{
	unsigned char		mode;			/* モード */
/*#define	GPS_COVER_OFF					(0x00)	*/	/* 表紙ＯＦＦ */
#define	GPS_FCOVER_ON					(0x01)		/* おもて表紙ＯＮ */
#define	GPS_BCOVER_ON					(0x02)		/* うら表紙ＯＮ */

	unsigned char		front;			/* おもて表紙モード */
#define	GPS_COVER_BLANK					(0x00)		/* 表紙に印刷しない */
/*#define	GPS_COVER_FRONT					(0x01)*/		/* 表紙に片面印刷する */
/*#define	GPS_COVER_FRONT_D				(0x11)	*/	/* 表紙に両面印刷する */

	unsigned char		back;			/* うら表紙モード */
/*#define	GPS_COVER_BLANK					(0x00)	*/	/* 裏表紙に印刷しない */
/*#define	GPS_COVER_BACK					(0x02)	*/	/* 裏表紙に印刷する */
/*#define	GPS_COVER_BACK_R				(0x22)	*/	/* 裏表紙反転排紙 */
													/* (画像が片面の場合のみ) */

	unsigned char		fcover_tray;	/* 表紙トレイ */

	unsigned char		bcover_tray;	/* 裏表紙トレイ */
} gpsCover;

/* --合紙-- */
typedef struct tgGpsSlip
{
	unsigned char		mode;			/* モード */
	unsigned char		slip_tray;		/* 合紙トレイ */
} gpsSlip;

/* --仕切り紙-- */
typedef struct tgGpsPartition
{
	unsigned char		mode;			/* モード */
/*#define	GPS_PARTITION_OFF				(0)		*/	/* 仕切紙なし */
/*#define	GPS_PARTITION_SORT				(1)		*/	/* 部単位 */
/*#define	GPS_PARTITION_JOB				(2)		*/	/* ジョブ単位 */

	unsigned short		cycle;			/* 部数指定（部単位の場合のみ有効） */
} gpsPartition;

/* --パンチ-- */
typedef struct tgGpsPunch
{
	unsigned char		pos;			/* 位置 */
/*#define	GPS_PUNCH_OFF					(0)	*/	/* なし */
/*#define	GPS_PUNCH_LEFT					(1)	*/	/* 左 */
/*#define	GPS_PUNCH_TOP					(2)	*/	/* 上 */
/*#define	GPS_PUNCH_RIGHT					(3)	*/	/* 右 */
/*#define	GPS_PUNCH_LEFT_TOP				(4)	*/	/* 左上 */

	unsigned char		unit;			/* 種別 */
#define	GPS_PHOLE_JP2					(0)		/* 日本２穴 */
#define	GPS_PHOLE_US2					(1)		/* 北米２穴 */
#define	GPS_PHOLE_US3					(2)		/* 北米３穴 */
#define	GPS_PHOLE_EU4					(3)		/* 欧州４穴 */
#define	GPS_PHOLE_NEU4					(4)		/* 北欧４穴 */
#define	GPS_PHOLE_JP1					(5)		/* 日本１穴 */
#define	GPS_PHOLE_MULTI					(6)		/* GBCパンチ */
} gpsPunch;

/* --広幅折り-- */
typedef struct tgGpsW_Fold
{
	unsigned char		w_fold;			/* 折り種類 */
/*#define	GPS_W_FOLD_OFF				(0)	*/	/* 折りなし */
/*#define	GPS_W_FOLD_ZIGZAG				(1)*/		/* ジャバラ折り */
/*#define	GPS_W_FOLD_ZIGZAGFILE			(2)	*/	/* ジャバラファイル折り */
/*#define	GPS_W_FOLD_BASIC				(3)	*/	/* 基本折り */
/*#define	GPS_W_FOLD_BAG					(4)	*/	/* 袋折り */
/*#define	GPS_W_FOLD_FILE					(5)	*/	/* ファイル折り */
/*#define	GPS_W_FOLD_CUSTOM1				(6)	*/	/* 特殊折り１ */
/*#define	GPS_W_FOLD_CUSTOM2				(7)	*/	/* 特殊折り２ */
/*#define	GPS_W_FOLD_PROGRAM1				(8)	*/	/* プログラム折り１ */
/*#define	GPS_W_FOLD_PROGRAM2				(9)	*/	/* プログラム折り２ */
/*#define	GPS_W_FOLD_PROGRAM3				(10)*/	/* プログラム折り３ */
/*#define	GPS_W_FOLD_PROGRAM4				(11)*/	/* プログラム折り４ */

	unsigned long		zigzag_width;	/* ジャバラ折りの折り幅(0.1mm単位) */

	unsigned char		w_punch;		/* 折り機パンチ */
/*#define	GPS_W_PUNCH_OFF					(0)	*/	/* 折り機パンチなし */
/*#define	GPS_W_PUNCH_ON					(1)	*/	/* 折り機パンチあり */

	unsigned char		w_edgefold;		/* 耳折り */
/*#define	GPS_W_EDGEFOLD_OFF				(0)	*/	/* 耳折りなし */
/*#define	GPS_W_EDGEFOLD_ON				(1)	*/	/* 耳折りあり */

	unsigned char		w_machinestamp;	/* メカスタンプ */
/*#define	GPS_W_MACHINE_STAMP_OFF	(0)	*/	/* 使用しない */
/*#define	GPS_W_MACHINE_STAMP_ON	(1)	*/	/* 使用する */

	unsigned char		reserve[64];	/* 機能追加用 */
} gpsW_Fold;

/* --リング製本-- */
typedef struct tgGpsRingBind
{
	unsigned char		ring_bind;		/* リング製本設定 */
/*#define	GPS_RING_BIND_OFF				(0)	*/	/* リング製本しない */
#define	GPS_RING_BIND_ON				(1)		/* リング製本する */

	unsigned char		bind_pos;		/* リング製本綴じ位置 */
/*#define	GPS_RING_BIND_LEFT				(1)	*/	/* 左綴じ */
/*#define	GPS_RING_BIND_TOP				(2)	*/	/* 上綴じ */
/*#define	GPS_RING_BIND_RIGHT				(3)	*/	/* 右綴じ */

	unsigned char		bind_mode;		/* リング製本モード設定 */
#define	GPS_RING_BIND_MODE_PUNCH		(1)		/* パンチのみモード */
#define	GPS_RING_BIND_MODE_RING			(2)		/* リング製本モード */

	unsigned char		reserve[5];		/* 機能追加用 */
} gpsRingBind;

/* --くるみ製本-- */
typedef struct tgGpsPerfectBind
{
	unsigned char		perf_bind;				/* くるみ製本設定 */
/*#define	GPS_PERF_BIND_OFF				(0)	*/		/* くるみ製本しない */
#define	GPS_PERF_BIND_ON				(1)			/* くるみ製本する */

	unsigned char		bind_pos;				/* くるみ製本綴じ位置 */
/*#define	GPS_PERF_BIND_LEFT				(1)	*/		/* 左綴じ */
/*#define	GPS_PERF_BIND_TOP				(2)	*/		/* 上綴じ */
/*#define	GPS_PERF_BIND_RIGHT				(3)	*/		/* 右綴じ */

	unsigned char		perf_trim;				/* くるみ製本裁断設定 */
/*#define	GPS_PERF_TRIM_NONE				(0)	*/		/* 裁断なし */
/*#define	GPS_PERF_TRIM_SINGLE			(1)	*/		/* 小口カット */
/*#define	GPS_PERF_TRIM_TRIPLE			(2)	*/		/* 三辺カット */

	unsigned char		trim_mode;				/* くるみ製本裁断モード設定 */
#define	GPS_PERF_TRIM_MODE_FINALSIZE	(1)			/* 仕上がりサイズ指定 */
#define	GPS_PERF_TRIM_MODE_CUTSIZE		(2)			/* カット範囲指定 */

	unsigned char		perf_paper_code;		/* くるみ製本 中紙サイズコード(paper.h 参照) */

	unsigned long		perf_paper_width;		/* くるみ製本 フリーサイズ時の中紙幅(主走査方向)　 (0.1mm単位) */

	unsigned long		perf_paper_length;		/* くるみ製本 フリーサイズ時の中紙高さ(副走査方向) (0.1mm単位) */

	unsigned char		perf_input_tray;		/* くるみ製本 中紙給紙トレイ */

	unsigned char		perf_cover_tray;		/* くるみ製本 表紙トレイ */

	unsigned char		perf_cover_mode;		/* くるみ製本 表紙モード */
#define	GPS_PERF_COVER_BLANK			(0)	/* くるみ表紙に印刷しない */
#define	GPS_PERF_COVER_PRINT_INSIDE		(1)	/* くるみ表紙に片面内側印刷する */
#define	GPS_PERF_COVER_PRINT_OUTSIDE	(2)	/* くるみ表紙に片面外側印刷する */
#define	GPS_PERF_COVER_PRINT_DUPLEX		(3)	/* くるみ表紙に両面印刷する */

	long				perf_cover_vert;		/* くるみ製本 表紙作像天地(主走査)位置調整 (0.1mm単位) */

	long				perf_cover_hori;		/* くるみ製本 表紙作像小口(副走査)位置調整 (0.1mm単位) */

	long				perf_image_vert;		/* くるみ製本 作像天地位置調整 (0.1mm単位) */

	long				perf_image_hori;		/* くるみ製本 作像小口位置調整 (0.1mm単位) */

	unsigned char		perf_final_paper_code;	/* 仕上がりサイズ指定時 製本サイズコード(paper.h 参照) */

	unsigned long		perf_final_paper_width; 	/* 仕上がりサイズ指定時 フリーサイズ時の製本幅(主走査方向)　 (0.1mm単位) */

	unsigned long		perf_final_paper_length;	/* 仕上がりサイズ指定時 フリーサイズ時の製本高さ(副走査方向) (0.1mm単位) */

	long				perf_final_paper_vert;	/* 仕上がりサイズ指定時 仕上がりサイズ位置調整 (0.1mm単位) */

	unsigned long		perf_cut_paper_top;	 	/* カット範囲指定時 天方向　 (0.1mm単位) */

	unsigned long		perf_cut_paper_bottom;	/* カット範囲指定時 地方向　 (0.1mm単位) */

	unsigned long		perf_cut_paper_side;	/* カット範囲指定時 小口方向 (0.1mm単位) */

	unsigned char		reserve[32];			/* 機能追加用 */
} gpsPerfectBind;

/* --マーキング[COSMOS]-- */
typedef struct tgGpsMarking
{
	unsigned char		markingtype;				/* 埋め込み種類 */
#define	GPS_MARKING_OFF							(0)		/* 埋め込みしない */
#define	GPS_MARKING_COPYGUARD					(1)		/* 不正コピーガード */
#define	GPS_MARKING_SECURITY					(2)		/* セキュリティートレース */
#define	GPS_MARKING_FALSIFICATION				(3)		/* 改ざん検知 */

	/* 不正コピーガードＥＸ埋め込み */
	unsigned long		pattern_type;				/* 地紋種類 */
#define	GPS_UCP_PATTERN_ON						(1<<0)		/* 抑止文字 */
#define	GPS_COPYGUARD_ON						(1<<1)		/* 不正コピーガード */
#define	GPS_COPYGUARD_EX_ON						(1<<2)		/* 不正コピーガードＥＸ */
#define	GPS_SECURUTY_TRACE_ON					(1<<3)		/* セキュリティトレース */
#define	GPS_PATTERN_AREA_FULL					(1<<4)		/* 地紋領域（ON:全面 OFF:枠のみ） */

	unsigned char		ucp_pattern_color;			/* 抑止文字の色 */
/*#define	GPS_COLOR_K								(0)	*/	/* ブラック */
/*#define	GPS_COLOR_C								(1)	*/	/* シアン */
/*#define	GPS_COLOR_M								(2)	*/	/* マゼンダ */

	unsigned char		ucp_pattern_density;			/* 抑止文字の濃度 */

	unsigned char		ucp_fg_effect;			/* 抑止文字の効果・文字色 */
#define	GPS_UCP_FG_EFFECT_WHITE					(0)		/* 始めから消えている */
#define	GPS_UCP_FG_EFFECT_VANISH				(1)		/* 消える */
#define	GPS_UCP_FG_EFFECT_REMAIN				(2)		/* 消えない */

	unsigned char		ucp_bg_effect;			/* 抑止文字の効果・背景色 */
#define	GPS_UCP_BG_EFFECT_WHITE					(0)		/* 始めから消えている */
#define	GPS_UCP_BG_EFFECT_VANISH				(1)		/* 消える */
#define	GPS_UCP_BG_EFFECT_REMAIN				(2)		/* 消えない */

	unsigned char		ucp_mask_type;			/* 抑止文字の模様 */
#define	GPS_MASK_TYPE_NONE						(0)		/* 模様なし */
#define	GPS_MASK_TYPE_SEIGAIHA					(1)		/* 青海波 */
#define	GPS_MASK_TYPE_AMIME						(2)		/* 網目 */
#define	GPS_MASK_TYPE_KOUSHI1					(3)		/* 格子１ */
#define	GPS_MASK_TYPE_KOUSHI2					(4)		/* 格子２ */
#define	GPS_MASK_TYPE_SHIPPOU					(5)		/* 七宝 */
#define	GPS_MASK_TYPE_SYOKKOU					(6)		/* 蜀江 */
#define	GPS_MASK_TYPE_MATSUKAWABISHI			(7)		/* 松皮菱 */
#define	GPS_MASK_TYPE_UROKO						(8)		/* 鱗 */
#define	GPS_MASK_TYPE_HIGAKI					(9)		/* 檜垣 */
#define	GPS_MASK_TYPE_KIKKOU					(10)	/* 亀甲 */

	unsigned short	device_ctl_type;			/* 不正コピーガードＥＸの機器制御コード */

	unsigned char		trace_info;				/* セキュリティートレース情報形式 */
#define	GPS_CG_FORMAT_USERID					(0)		/* ユーザーＩＤ */
#define	GPS_CG_FORMAT_PAPERID					(1)		/* 紙ＩＤ */

	/* セキュリティートレース埋め込み */
	unsigned char		embed_mode;				/* 埋め込みモード */
#define	GPS_SE_MODE_IMAGEQUALITY				(0)		/* 画質優先 */
#define	GPS_SE_MODE_NORMAL						(1)		/* 普通 */
#define	GPS_SE_MODE_TOLERANCE					(2)		/* 耐性優先 */

	/* 改ざん検知埋め込み */
	unsigned char		pattern_density;			/* 地紋濃度 */
#define	GPS_FA_DENSITY_LIGHT					(0)		/* 薄い */
#define	GPS_FA_DENSITY_MIDDLE					(1)		/* 中間 */
#define	GPS_FA_DENSITY_DARK						(2)		/* 濃い */

	/* 地紋付加状態 */
	unsigned char		pattern_status;				/* 地紋付加状態 */
#define	GPS_FA_STATUS_NONE						(0)		/* 地紋なし */
#define	GPS_FA_STATUS_ADDED						(1)		/* 地紋あり */

	unsigned short	errorcorrection_level;		/* 誤り訂正レベル */

	/* リフレッシュコピー */
	unsigned char		refreshcopy;				/* 埋め込み */
#define	GPS_RF_MODE_OFF							(0)		/* OFF */
#define	GPS_RF_MODE_ON							(1)		/* ON */

	unsigned char		embedding_position;			/* 埋め込み位置 */
#define	GPS_RF_POS_RIGHTTOP						(0)		/* 右上 */
#define	GPS_RF_POS_LEFTTOP						(1)		/* 左上 */
#define	GPS_RF_POS_RIGHTBOTTOM					(2)		/* 右下 */
#define	GPS_RF_POS_LEFTBOTTOM					(3)		/* 左下 */

	unsigned long		embedding_pos_adj_vert;		/* 埋め込み位置調整（縦方向）(0.1mm単位) */

	unsigned long		embedding_pos_adj_horiz;	/* 埋め込み位置調整（横方向）(0.1mm単位) */

	unsigned char		barcode_format;			/* バーコード形式 */
#define	GPS_RF_FORMAT_QR						(0)		/* QR */
#define	GPS_RF_FORMAT_PDF417					(1)		/* PDF417 */
#define	GPS_RF_FORMAT_DATAMATRIX				(2)		/* DataMatrix */

	unsigned char		reserve[64];			/* 機能追加用 */
} gpsMarking;

/* --多機能折り-- */
typedef struct tgGpsMultifold
{
	unsigned char		multifold_kind;				/* 多機能折り種類 */
#define	GPS_MULTIFOLD_KIND_OFF					(0)		/* 多機能折りなし */
#define	GPS_MULTIFOLD_KIND_HALF					(1)		/* ２つ折り（中折り） */
#define	GPS_MULTIFOLD_KIND_THIRDS_INSIDE		(2)		/* 内３つ折り */
#define	GPS_MULTIFOLD_KIND_THIRDS_OUTSIDE		(3)		/* 外３つ折り */
#define	GPS_MULTIFOLD_KIND_QUART				(4)		/* 単純４つ折り */
#define	GPS_MULTIFOLD_KIND_GATE					(5)		/* 観音折り */

	unsigned char		multifold_printposition;	/* 印字面 */
#define	GPS_MULTIFOLD_PRINTPOSITION_INSIDE		(0)		/* 内側印字 */
#define	GPS_MULTIFOLD_PRINTPOSITION_OUTSIDE		(1)		/* 外側印字 */

	unsigned char		multifold_direction;		/* 開き（折り）方向 */
#define	GPS_MULTIFOLD_DIRECTION_LEFT			(0)		/* 左開き */
#define	GPS_MULTIFOLD_DIRECTION_BOTTOM			(1)		/* 下開き */
#define	GPS_MULTIFOLD_DIRECTION_RIGHT			(2)		/* 右開き */
#define	GPS_MULTIFOLD_DIRECTION_TOP				(3)		/* 上開き */

	unsigned char		multifold_sheets;			/* 重ね折り */
#define	GPS_MULTIFOLD_SHEETS_OFF				(0)		/* 重ね折りしない */
#define	GPS_MULTIFOLD_SHEETS_ON					(1)		/* 重ね折りする */

	unsigned char		reserve[16];				/* 機能追加用 */
} gpsMultifold;

/* --トリム指定-- */
typedef struct tgGpsTrim
{
	unsigned char		trim_mode;		/* トリマーの裁断動作設定 */
#define	GPS_TRIM_OFF				(0)		/* カットなし */
#define	GPS_TRIM_SINGLECUT			(1)		/* 小口カット */

	unsigned long		side_edge_cut;	/* トリマーのカット量　小口方向設定(0.1mm単位) */

	unsigned char		reserve[16];	/* 機能追加用 */
} gpsTrim;

#define	GPS_MAX_PAGEPARAM_SHM	8

typedef struct gps_pageparam_shm
{
	unsigned long		support_flag[GPS_MAX_PAGEPARAM_SHM];	/* サポートするパラメータ */

	unsigned long		flag[GPS_MAX_PAGEPARAM_SHM];			/* 設定するパラメータ */
/* byte:1 */
#define	GPS_PARAM_SHM_QTY 				(1 <<  0)
#define	GPS_PARAM_SHM_LIMITLESS_EXIT	(1 <<  1)
#define	GPS_PARAM_SHM_OUTPUT_TRAY		(1 <<  2)
#define	GPS_PARAM_SHM_OUTMODE			(1 <<  3)
#define	GPS_PARAM_SHM_BINDING			(1 <<  4)
#define	GPS_PARAM_SHM_MARGIN			(1 <<  5)
#define	GPS_PARAM_SHM_COVER				(1 <<  6)
#define	GPS_PARAM_SHM_SLIP				(1 <<  7)
#define	GPS_PARAM_SHM_PARTITION			(1 <<  8)
#define	GPS_PARAM_SHM_SHIFTOFF			(1 <<  9)
#define	GPS_PARAM_SHM_FINISH			(1 << 10)
#define	GPS_PARAM_SHM_STAPLE			(1 << 11)
#define	GPS_PARAM_SHM_PUNCH				(1 << 12)
#define	GPS_PARAM_SHM_Z_FOLD			(1 << 13)
#define	GPS_PARAM_SHM_W_FOLD			(1 << 14)
#define	GPS_PARAM_SHM_TONERSAVE			(1 << 15)
#define	GPS_PARAM_SHM_PRIORITY_TRAY		(1 << 16)
#define	GPS_PARAM_SHM_UPSIDEDOWN		(1 << 17)
#define	GPS_PARAM_SHM_COLOR				(1 << 18)
#define	GPS_PARAM_SHM_MIXEDDIRROT		(1 << 19)
#define	GPS_PARAM_SHM_JAMRECOVERY		(1 << 20)
#define	GPS_PARAM_SHM_ACS				(1 << 21)
#define	GPS_PARAM_SHM_STAMP				(1 << 22)
#define	GPS_PARAM_SHM_DUPLEXMODE		(1 << 23)
#define	GPS_PARAM_SHM_WHITESUPPRESS		(1 << 24)
#define	GPS_PARAM_SHM_COLORSEPARATE		(1 << 25)
#define	GPS_PARAM_SHM_RING				(1 << 26)
#define	GPS_PARAM_SHM_PERFECT			(1 << 27)
#define	GPS_PARAM_SHM_MARKING			(1 << 28)
#define	GPS_PARAM_SHM_MULTIFOLD			(1 << 29)
#define	GPS_PARAM_SHM_TRIM				(1 << 30)
#define	GPS_PARAM_SHM_FACEUP			(1 << 31)
/* byte:2 */
#define	GPS_PARAM_SHM_MAGAZINE			(1 <<  0)
#define	GPS_PARAM_SHM_PRTHEAD_DIRECTION	(1 <<  1)
#define	GPS_PARAM_SHM_SADDLE_FOLD		(1 <<  2)
/* byte:3 */
/* byte:4 */
/* byte:5 */
/* byte:6 */
/* byte:7 */
/* byte:8 */

	/* ----- パラメータ１ ----- */
	unsigned short		qty;				/* 印刷部数 */

	unsigned char		limitless_exit;		/* シーケンシャルスタック */
/*#define	GPS_LIMITLESS_OFF				(0x00)	*/	/* ＯＦＦ */
/*#define	GPS_LIMITLESS_EXIT				(0x10)	*/	/* ＯＮ */

	unsigned short		output_tray;		/* 排紙トレイ */
/*#define	GPS_BIN_MAIN					(0x0000) */	/* 本体排紙(両面/マルチビン) */
/*#define	GPS_BIN_FINISHER				(0x0100) */	/* フィニッシャ */
/*#define	GPS_BIN_MAILBOX					(0x0200)*/	/* メールボックス */
/*#define	GPS_BIN_MAIN_STD				(0x0000)*/	/* FD/標準排紙 */
/*#define	GPS_BIN_MAIN_BIN1				(0x0001)*/	/* 1ビン排紙 */
/*#define	GPS_BIN_MAIN_EXTED				(0x0002)*/	/* 拡張(ストレート)排紙 */
/*#define	GPS_BIN_FINI_PROOF				(0x0100)*/	/* プルーフトレイ */
/*#define	GPS_BIN_FINI_SHIFT				(0x0101)*/	/* シフトトレイ */
/*#define	GPS_BIN_FINI_BOOKLET			(0x0105)*/	/* ブックレット */
/*#define	GPS_BIN_MAILBOX1				(0x0201)*/	/* メールボックス１ */
/*#define	GPS_BIN_MULTI_1					(0x0300)*/	/* マルチビン１ */
/*#define	GPS_BIN_MULTI_2					(0x0301)*/	/* マルチビン２ */
/*#define	GPS_BIN_SUBFINI_RING			(0x040C)*/	/* リングバインダ排紙トレイ */
/*#define	GPS_BIN_SUBFINI_PERF			(0x040F)*/	/* くるみ製本機排紙トレイ */

#define	GPS_BIN_STACKER_PROOF	(0x0400)				/* スタッカープルーフ */
#define	GPS_BIN_STACKER			(0x0401)				/* スタッカーシフト１ */
#define	GPS_BIN_STACKER2		(0x0402)				/* スタッカーシフト２ */
#define	GPS_BIN_RING_STACKER	GPS_BIN_SUBFINI_RING	/* リングバインダ排紙トレイ(08Aではなるべくこちらを使用してください) */
#define	GPS_BIN_LOADINGTRAY		GPS_BIN_SUBFINI_PERF	/* くるみ製本機排紙トレイ　(08Aではなるべくこちらを使用してください) */
#define	GPS_BIN_FOLD_PROOF		(0x0411)				/* 多機能折りプルーフトレイ */

	unsigned char		outmode;			/* 印刷モード */
/*#define	GPS_OUT_IMGINFO					(0)	*/	/* 画像属性情報の指定に従う*/
/*#define	GPS_OUT_SINGLE					(1)	*/	/* 片面印刷 */
/*#define	GPS_OUT_DUPLEX					(2)	*/	/* 両面印刷 */

	unsigned char		binding;			/* 両面とじ方向 */
/*#define	GPS_BIND_LEFT					(0)	*/	/* 左綴じ */
/*#define	GPS_BIND_TOP					(1)	*/	/* 上綴じ */
/*#define	GPS_BIND_RIGHT					(2)	*/	/* 右綴じ */
/*#define	GPS_BIND_LEFTRIGHT				(4)	*/	/* 左右綴じ (RTIFF, PCL) */
/*#define	GPS_BIND_TOPBOTTOM				(5)*/		/* 上下綴じ(RTIFF, PCL) */

	gpsMargin			Margin;				/* 綴じ代 */

	gpsCover			Cover;				/* 表紙 */

	gpsSlip				Slip;				/* 合紙 */

	gpsPartition		Partition;			/* 仕切り紙 */

	unsigned char		shiftoff;			/* ジョブ単位のシフト */
/*#define	GPS_SHIFT_ON					(0)	*/	/* ジョブ単位にシフトする */
/*#define	GPS_SHIFT_OFF					(1)	*/	/* シフトしない */

	unsigned char		finish;				/* 仕分け指定 */
/*#define	GPS_FINISH_OFF					(0) */		/* 仕分けしない */
/*#define	GPS_SORT						(1)	*/	/* ソート */
/*#define	GPS_STACK						(2)	*/	/* スタック */
/*#define	GPS_ROT_SORT					(3)	*/	/* 回転ソート */
#define	GPS_SHIFT_SORT					(4)		/* シフトソート */

	unsigned char		staple;		/* ステープル */
/*#define	GPS_STAPLE_OFF					(0)	*/	/* なし */
/*#define	GPS_STAPLE_LEFT_TOP_HORIZ		(1)	*/	/* 左上水平 */
/*#define	GPS_STAPLE_LEFT_TOP_VERT		(2)	*/	/* 左上垂直 */
/*#define	GPS_STAPLE_LEFT_TOP_SLANT		(3)	*/	/* 左上斜め */
/*#define	GPS_STAPLE_RIGHT_TOP_HORIZ		(5)	*/	/* 右上水平 */
/*#define	GPS_STAPLE_RIGHT_TOP_VERT		(6)	*/	/* 右上垂直 */
/*#define	GPS_STAPLE_RIGHT_TOP_SLANT		(7)	*/	/* 右上斜め */
/*#define	GPS_STAPLE_DOUBLE_LEFT			(9)	*/	/* 左側２個所 */
/*#define	GPS_STAPLE_DOUBLE_TOP			(10)*/	/* 上側２個所 */
/*#define	GPS_STAPLE_DOUBLE_RIGHT			(11)*/	/* 右側２個所 */
/*#define	GPS_STAPLE_BOOKLET				(12)*/	/* 真中２個所 */
/*#define	GPS_STAPLE_LEFT_TOP				(16)*/	/* 左上 */
/*#define	GPS_STAPLE_RIGHT_TOP			(17)*/	/* 右上 */

	gpsPunch			Punch;		/* パンチ */

	/* --Ｚ折り-- */
	unsigned char		z_fold;		/* Ｚ折り */
/*#define	GPS_Z_FOLD_OFF					(0)	*/	/* Ｚ折りなし */
/*#define	GPS_Z_FOLD_RIGHT				(1)	*/	/* 右折り */
/*#define	GPS_Z_FOLD_BOTTOM				(2)	*/	/* 下折り */
/*#define	GPS_Z_FOLD_LEFT					(3)	*/	/* 左折り */

	gpsW_Fold			w_fold;		/* 広幅折り */

	unsigned char		tonersave;		/* トナーセーブ */
/*#define	GPS_TONERSAVE_OFF				(0)	*/	/* トナーセーブOFF */
/*#define	GPS_TONERSAVE_MODE1				(1)	*/	/* トナーセーブ・モード1 */
/*#define	GPS_TONERSAVE_MODE2				(2)	*/	/* トナーセーブ・モード2 */
/*#define	GPS_TONERSAVE_SOFT				(3)	*/	/* ソフトトナーセーブ */

	unsigned char		priority_tray;	/* 優先給紙トレイ */

	unsigned char		upsidedown;		/* 180度回転 */
/*#define	GPS_UPSIDE_UP					(0) */		/* 回転しない */
/*#define	GPS_UPSIDE_DOWN					(1)	*/	/* 回転する */

	unsigned char		color_count;		/* 色数 */
#define	GPS_COLOR_1C				GPS_COLOR_1		/* 1原色 */
/*#define	GPS_COLOR_RK					(2)	*/	/* 赤黒 */
/*#define	GPS_COLOR_CMYK					(4)	*/	/* 4原色 */
/*#define	GPS_COLOR_XRGB					(5)	*/	/* RGB[COSMOS] */
/*#define	GPS_COLOR_2C					(6)	*/	/* 2原色 */

	unsigned char		mixeddirrot;		/* 用紙方向混在時の回転方向 */
/*#define	GPS_MIXED_OFF					(0)	*/	/* GPS仕様に従う */
/*#define	GPS_MIXED_LEFT					(1)	*/	/* 左 */
/*#define	GPS_MIXED_RIGHT					(2)*/		/* 右 */

	unsigned char		jamrecovery;		/* ジャム・リカバリー */
/*#define	GPS_JAMRECOVERY_OFF				(0)	*/	/* リカバリーしない */
/*#define	GPS_JAMRECOVERY_ON				(1)	*/	/* リカバリーする */

	unsigned char		acs;			/* ACS */
/*#define	GPS_ACS_OFF						(0)	*/	/* ACSしない */
/*#define	GPS_ACS_ON						(1)	*/	/* ACSする */

	unsigned char		stamp;			/* 本体スタンプを使用する */
/*#define	GPS_STAMP_OFF					(0)	*/	/* 使用しない */
/*#define	GPS_STAMP_ON					(1)*/		/* 使用する */

	unsigned char		duplexmode;		/* ドライバーから両面指定 */
/*#define	GPS_DUPLEXMODE_OFF				(0)  */   	/* 両面指定なし */
/*#define	GPS_DUPLEXMODE_ON				(1)    */ 	/* 両面指定あり */

	unsigned char		white_suppress;	/* 白紙抑制[COSMOS] */
#define	GPS_WHITE_SUPPRESS_OFF			(0)		/* OFF */
#define	GPS_WHITE_SUPPRESS_ON			(1)		/* ON */
#define	GPS_WHITE_SUPPRESS_SPACE		(2)		/* スペース印刷 */

	unsigned char		color_separate;	/* 色分版[COSMOS] */
#define	GPS_COLOR_SEPARATE_K			(1<<0)		/* ブラック */
#define	GPS_COLOR_SEPARATE_C			(1<<1)		/* シアン */
#define	GPS_COLOR_SEPARATE_M			(1<<2)		/* マゼンダ */
#define	GPS_COLOR_SEPARATE_Y			(1<<3)		/* イエロー */

	gpsRingBind			Ringbind;		/* リング製本 */

	gpsPerfectBind		Perfectbind;	/* くるみ製本 */

	gpsMarking			Marking;		/* マーキング[COSMOS] */

	gpsMultifold		Multifold;		/* 多機能折り */

	gpsTrim				Trim;			/* トリミング指定 */

	unsigned char		face_up;		/* フェースアップ排紙（フェースアップ機のみ有効） */
#define	GPS_FACEUP_OFF					(0)		/* フェースダウン排紙 */
#define	GPS_FACEUP_ON					(1)		/* フェースアップ排紙 */

/* ----- パラメータ２ ----- */
	unsigned char		magazine;		/* 週刊誌綴じ(PS専用) */
#define	GPS_MAGAZINE_OFF				(0)		/* 週刊誌綴じなし */
#define	GPS_MAGAZINE_RIGHT				(1)		/* 右綴じ */
#define	GPS_MAGAZINE_LEFT				(2)		/* 左綴じ */
#define	GPS_MAGAZINE_UP					(3)		/* 上綴じ */
#define	GPS_MAGAZINE_DOWN				(4)		/* 下綴じ */

	unsigned char		prthead_direction;	/* 片方向/双方向印刷 */
#define	GPS_PRTHEAD_AUTO				(0)		/* 自動 */
#define	GPS_PRTHEAD_UNIDIRECTIONAL		(1)		/* 片方向 */

	unsigned char		saddle_fold;		/* 中折り(中綴じトレイ) */
#define	GPS_SADDLE_FOLD_OFF				(0)		/* 中折りしない */
#define	GPS_SADDLE_FOLD_INSIDE			(1)		/* 内折り */
#define	GPS_SADDLE_FOLD_OUTSIDE			(2)		/* 外折り */
#define	GPS_SADDLE_FOLD_SHEETS			(3)		/* 重ね折り */

} gps_pageparam_shm_t, *gps_pageparam_shm_p;

/*      */

#ifdef  __cplusplus
}
#endif  /* !__cplusplus */
#endif  /* !_PAGEPRINT_H */
/* EOF  */
