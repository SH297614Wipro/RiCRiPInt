/*
 *	Copyright(c) 1997,2002 by RICOH Co.,LTD.
 *
 *	$Author: shihab $
 *	$Date: 2009/03/16 06:03:43 $
 *	$Revision: 1.38 $
 */

#ifndef __PAGER_H__
#define __PAGER_H__


/*
 *	Return Value
 *		いずれは OK = 1(TRUE), ERROR = 0(FALSE) に変更予定。
 */

#define	PR_OK			 0
#define	PR_ERROR		 1
#define	PR_OK_BLANKPAGE		-1	/* pr_pagestart() 専用 */

/*
 * support function
 */
#define PR_FUNC_DEFAULT_SETTING		0x00000000  /* すべてdefaultが指定される */

//Permanent Font
#define PR_FUNC_PERMANENTFONT_OFF	0x00000000 /* 外字機能OFF */
#define PR_FUNC_PERMANENTFONT_ON	0x00000001 /* 外字機能ON */
#define PR_FUNC_PERMANENTFONT_MASK	0x00000001 /* 外字機能 マスク */

/* Alignment Size */
#define PR_FUNC_8BYTE_ALIGN			0x00000002 /* 8byte alignment size */
#define PR_FUNC_4BYTE_ALIGN			0x00000000 /* 4byte alignment size (default)*/
#define PR_FUNC_ALIGNSIZE_MASK		0x00000002 /* alignment size mask */

//Source trans

#define PR_FUNC_SOURCETRANS_OFF  0x00000000 
#define PR_FUNC_SOURCETRANS_ON	0x00000010
#define PR_FUNC_SOURCETRANS_MASK	0x00000010

/*
 *	印刷モード
 */
#define	PR_PENV_VAL_INT_QUALITYMODE_STANDARD	(0)
#define	PR_PENV_VAL_INT_QUALITYMODE_FAST	(1)
#define	PR_PENV_VAL_INT_QUALITYMODE_FINE	(2)
#define	PR_PENV_VAL_INT_QUALITYMODE_SUPERFINE	(3)

#define	PR_PRINT_MODE_HIGH			(0x01)
#define	PR_PRINT_MODE_NORMAL			(0x02)
#define	PR_PRINT_MODE_QUALITY			(0x03)
#define	PR_PRINT_MODE_HIGHQUALITY		(0x04)
#define	PR_PRINT_MODE_MASK			(0x0F)
#define	PR_PRINT_DENSITY_STANDARD		(0x40)
#define	PR_PRINT_DENSITY_LIGHT			(0x30)
#define	PR_PRINT_DENSITY_DARK			(0x50)
#define	PR_PRINT_DENSITY_MASK			(0xF0)

/*
 *	color mode
 */

#define	PR_COLOR_GRAY		0	/* モノクロ */
#define	PR_COLOR_RGB		1	/* RGB カラー */
#define	PR_COLOR_CMYK		2	/* CMYK カラー */
#define	PR_COLOR_NOUSE		3	/* 未使用 カラーモード */
#define	PR_COLOR_MASK		3	/* カラーモードマスク */
#define	PR_COLOR_BGMODE		8

/*
 *	PR2用 pr_setcolor追加マクロ
 */
#define PR_COLOR_FILL		0	/* FILLパターン 通常の塗りつぶし */
#define PR_COLOR_GRADATION	0x10	/* FILLパターン グラデーション */

/*
 *	bit depth
 */
#define	PR_DEPTH_1BIT		0x00	/* 1bit			*/
#define	PR_DEPTH_2BIT		0x10	/* 2bit			*/
#define	PR_DEPTH_4BIT		0x20	/* 4bit			*/
#define	PR_DEPTH_8BIT		0x30	/* 8bit			*/
#define	PR_DEPTH_MASK		0x30	/* ビット深さマスク	*/

/*
 *	device color
 */
#define	PR_DEVICE_MONO		0x00	/* 白黒			*/
#define	PR_DEVICE_RGB		0x01	/* RGB			*/
#define	PR_DEVICE_CMY		0x02	/* CMY			*/
#define	PR_DEVICE_CMYK		0x03	/* CMYK			*/
#define	PR_DEVICE_RK		0x04	/* 赤黒二色		*/
#define	PR_DEVICE_RK2		0x05	/* 全オブジェクト赤黒二色	*/
#define	PR_DEVICE_MASK		0x0F	/* Device Colorマスク	*/

/*
 *	rotation direction
 */
#define	PR_ROTATE_R0		0x00	/* 回転なし		*/
#define	PR_ROTATE_R90		0x40	/* 右90度回転		*/
#define	PR_ROTATE_R180		0x80	/* 180度回転		*/
#define	PR_ROTATE_R270		0xC0	/* 右270度回転		*/
#define	PR_ROTATE_DIRECTION	0xC0	/* 回転指定マスク	*/

/*
 *	rotation direction
 */
#define	PR_ROT_R0		0x00	/* 回転なし		*/
#define	PR_ROT_R90		0x01	/* 右90度回転		*/
#define	PR_ROT_R180		0x02	/* 180度回転		*/
#define	PR_ROT_R270		0x03	/* 右270度回転		*/
#define	PR_ROT_DIRECTION	0x03	/* 回転指定マスク	*/

/*
 *	rendering color
 */
#define PR_RENDERING_NONE	0x0000	/* Use device color	*/
#define PR_RENDERING_MONO	0x0100	/* Monochrome		*/
#define PR_RENDERING_RGB	0x0200	/* RGB			*/
#define PR_RENDERING_CMY	0x0300	/* CMY			*/
#define PR_RENDERING_CMYK	0x0400	/* CMYK			*/
#define PR_RENDERING_RK		0x0500	/* RK			*/
#define PR_RENDERING_MASK	0x0F00	/* Rendering color mask	*/

/*
 *	重なり判定を抑制(pr_pagestart)
 */
#define	PR_CUTOUT_AVAIL		0x00010000

/*
 *	gray mode
 */

#define	PR_GRAY_G2K		0	/* グレイのみ黒変換orBG/UCR	*/
#define	PR_GRAY_CMYK		1	/* 常にBG/UCR			*/
#define	PR_GRAY_K2K		2	/* 黒のみ黒変換orBG/UCR		*/
#define	PR_GRAY_CMY		3	/* BG/UCRしない(RGB->CMYのみ)	*/
#define	PR_GRAY_PIXELK		4	/* カラーイメージでもグレイのみ
					   黒変換orBG/UCR（本当のG2K）  */
#define	PR_GRAY_MAYBEK		5	/* 画素履歴を見てGRAY->K変換を行なう */
#define	PR_GRAY_ABOUTK		6	/* R≒G≒BでGRAY->K変換を行なう */
#define	PR_GRAY_IMAGEK		7	/* イメージでもK2K変換を行なう	*/
#define	PR_GRAY_COMPBK		8	/* Composite black */
#define	PR_GRAY_HGRG2K		10	/* グレイのみ黒変換orBG/UCR(高墨)	*/
#define	PR_GRAY_HGRCMYK		11	/* 常にBG/UCR(高墨)			*/
#define	PR_GRAY_MAX		11	/* グレイ指定最大値 */

#define	PR_GRAY_MASK		3	/* グレイ指定マスク */

#define PR_JUDGE_GRAY_AFTER_CMM_ON	0	/* CMM後のグレイ判定処理を行なう（デフォルト） */
#define PR_JUDGE_GRAY_AFTER_CMM_OFF	1	/* CMM後のグレイ判定処理を行なわない */
#define PR_JUDGE_GRAY_MAX 1				/* CMM後のグレイ判定処理指定最大値 */


/*
 *	output mode
 */
#define	PR_PAPERFEED_NORMAL			0	/* 通常排紙   */
#define	PR_PAPERFEED_NOTPRINT		1	/* 排紙しない */
#define	PR_PAPERFEED_OVERLAY		2	/* 合成印刷   */
#define	PR_PAPERFEED_NOWHITE		3	/* 白紙抑制   */
#define	PR_PAPERFEED_FORCE			4	/* 強制印刷   */
#define PR_PAPERFEED_FORCE_NOWHITE	5	/* 強制印刷かつ白紙抑制 */
#define PR_PAPERFEED_NOTDRAW_NOTPRINT	6	/* Only GJ support it */

/*
 *	dither type
 */

#define	PR_DIT_PHOT		0	/* 写真ディザ */
#define	PR_DIT_TEXT		1	/* 文字ディザ */
#define	PR_DIT_GRAP		2	/* グラフィックスディザ */
#define	PR_DIT_CAD		3	/* CADディザ */
#define	PR_DIT_MASK		3	/* ディザ指定マスク */

/*
 * 誤差拡散モード
 */
#define	PR_IMAGE_ED		0x01	/* イメージ誤差拡散(現状未使用) */
#define	PR_FRAME_ED		0x02	/* 全面誤差拡散 */
#define	PR_ED_MASK		0x03

/*
 * 紙種 ID (iRPJL, PR 共に同じ ID を使用する)
 */
#define	PR_MEDIA_PLAIN		1	/* 普通紙 */
#define	PR_MEDIA_THICK		3	/* 厚紙 */
#define	PR_MEDIA_TRANSPARENCY	17	/* OHP */
#define	PR_MEDIA_GLOSSY		19	/* 光沢紙 */
#define	PR_MEDIA_JPOST		24	/* 官製はがき */
#define	PR_MEDIA_COATED		38	/* 専用コート紙 */
#define	PR_MEDIA_INKJETJPOST	39	/* インクジェット官製はがき */
#define	PR_MEDIA_ENVELOPE	40	/* 封筒 */
#define	PR_MEDIA_MASK		0x7f

/*
 *	brush types.
 */

#define	PR_BRUSH_MONO		0	/* mono brush.			*/
#define	PR_BRUSH_RGB		1	/* RGB brush.			*/
#define	PR_BRUSH_CMYK		2	/* CMYK brush.			*/
#define	PR_BRUSH_MASK		3	/* ブラシ用マスク		*/

#define PR_BRUSH_TRANS		8	/* 透過パターン指定あり		*/

/*
 *	BackGround Mode
 */

#define	PR_TRANS		1	/* 透過 */
#define	PR_OPAQUE		2	/* 不透過 */
#define	PR_BGMODE_MASK		3	/* バックグラウンド用マスク */

#define PR_SOURCE_TRANS		0x04	/* ソース透過モード */
#define PR_SOURCE_OPAQUE	0x00	/* ソース非透過モード */
#define PR_SOURCE_MASK		0x04	/* ソース透過モード用マスク */

#define PR_PATTERN_TRANS	0x08	/* ブラシ透過モード */
#define PR_PATTERN_OPAQUE	0x00	/* ブラシ非透過モード */
#define PR_PATTERN_MASK		0x08	/* ブラシ透過モード用マスク */

#define PR_TRANS_EXCEPTION_ON	0x10	/* 透過モード例外処理有効 */
#define PR_TRANS_EXCEPTION_OFF	0x00	/* 透過モード例外処理無効 */
#define PR_TRANS_EXCEPTION_MASK	0x10	/* 透過モード例外処理用マスク */

#define PR_SOLID_BRUSH_EXCEPTION_ON	0x20	/* SOLID BRUSH例外処理有効 */
#define PR_SOLID_BRUSH_EXCEPTION_OFF	0x00	/* SOLID BRUSH例外処理無効 */
#define PR_SOLID_BRUSH_EXCEPTION_MASK	0x20	/* SOLID BRUSH例外処理用マスク */

/*
 *	line cap types.
 */

#define	PR_CAP_ROUND		0	/* windows default line cap.	*/
#define	PR_CAP_BUTT		1	/* butt cap.			*/
#define	PR_CAP_SQUARE		2	/* square cap.			*/
#define	PR_CAP_TRIANGLE		3	/* triangle cap.		*/
#define	PR_CAP_MASK		3	/* CAP 指定マスク		*/

/*
 *	joint types.
 */

#define	PR_JOINT_ROUND		0	/* round type.         */
#define	PR_JOINT_BEVEL		1	/* bevel connecttion.  */
#define	PR_JOINT_MITER		2	/* miter connection    */
#define	PR_JOINT_MASK		3	/* JOINT 指定マスク    */

/*
 *	object type
 */
#define	PR_OBJ_IMAG		0
#define	PR_OBJ_GRAP		1
#define	PR_OBJ_TEXT		2
#define	PR_OBJ_LINE		3
#define	PR_OBJ_MASK		3


/*
 * オブジェクト種類毎のグレイ印刷種類モード
 * 	各描画オブジェクト (イメージ、文字、グラフィック(線、塗り)) に、
 * 	それぞれどのグレイ印刷方式 (G2K,CMYK,K2K) のどれを使うかを示すモード
 * 	gmod は pagestart の 'g' オプションで指定される vec_gray を使う。
 *
 * gmod: IIGGTTLL
 *	II:	イメージオブジェクト用グレイ印刷方式
 *	GG:	グラフィック(塗り)オブジェクト用グレイ印刷方式
 *	TT:	文字オブジェクト用グレイ印刷方式
 *	LL:	線画オブジェクト用グレイ印刷方式
 */
#define	GRAY_IMAG_MODE(gmod)	((gmod >> 24) & GRAY_MASK)
#define	GRAY_GRAP_MODE(gmod)	((gmod >> 16) & GRAY_MASK)
#define	GRAY_TEXT_MODE(gmod)	((gmod >> 8)  & GRAY_MASK)
#define	GRAY_LINE_MODE(gmod)	((gmod >> 0)  & GRAY_MASK)

/*
 *	graphic object flag
 */

#define	PR_DRAW			0x00	/* Draw */
#define	PR_ALTFILL		0x01	/* Alt Fill */
#define	PR_WINDFILL		0x02	/* Wind Fill */
#define	PR_DRAWALTFILL		0x03	/* Draw and Alt Fill */
#define	PR_DRAWWINDFILL		0x04	/* Draw and Wind Fill */
#define	PR_ALTCLIP		0x05	/* Alt Clip */
#define	PR_WINDCLIP		0x06	/* Wind Clip */
#define	PR_DRAW_NOUSE		0x07	/* Reserve */
#define	PR_DRAW_MASK		0x07	/* Draw Mask */
#define	PR_PATHCLOSE		0x08	/* path Open/Close mode */
#define	PR_SHORT_COORD		0x20	/* Spool 2BYTE COORD */
#define	PR_FLOAT_COORD		0x40	/* Spool FLOAT COORD */
#define	PR_COORD_MASK		0x60	/* Spool COORD Mask */
#define	PR_SCRECT_DRAW		0x40	/* SC Rectangle Draw */
#define PR_ARC_DRAW		0x00	/* Arc Draw */
#define PR_ARC_FILL		0x01	/* Arc Fill */
#define PR_ARC_DRAWFILL		0x03	/* Arc Draw and Fill */
#define PR_ARC_CLIP		0x05	/* Arc Clip */

#define	PR_CLIP_STACK		0x00010000	/* Clip STACK */

/* for scanline */

#define PR_SC_FILL		0x00	/* Fill */
#define PR_SC_CLIP		0x01	/* Clip */
#define PR_SC_NOCOMP		0x00	/* not compress */
#define PR_SC_DLDE		0x04	/* DLDE */
#define PR_SC_COMPMASK		0x06	/* compress flag mask */

#define	PR_ATTR_DRAW_DEFAULT		0x00000000
#define	PR_ATTR_DRAW_IMAGE_COLOR	0x08000000
#define	PR_ATTR_DRAW_IMAGE_MONO		0x10000000
#define	PR_ATTR_DRAW_GRAPH		0x18000000
#define	PR_ATTR_DRAW_TEXT		0x20000000
#define	PR_ATTR_DRAW_LINE		0x28000000
#define	PR_ATTR_DRAW_MASK		0x38000000

#define	PR_ATTR_FILL_DEFAULT		0x00000000
#define	PR_ATTR_FILL_IMAGE_COLOR	0x01000000
#define	PR_ATTR_FILL_IMAGE_MONO		0x02000000
#define	PR_ATTR_FILL_GRAPH		0x03000000
#define	PR_ATTR_FILL_TEXT		0x04000000
#define	PR_ATTR_FILL_LINE		0x05000000
#define	PR_ATTR_FILL_MASK		0x07000000

#define	PR_ATTR_DEFAULT		0x00000000
#define	PR_ATTR_IMAGE_COLOR	0x01000000
#define	PR_ATTR_IMAGE_MONO	0x02000000
#define	PR_ATTR_GRAPH		0x03000000
#define	PR_ATTR_TEXT		0x04000000
#define	PR_ATTR_LINE		0x05000000
#define	PR_ATTR_MASK		0x07000000

#define PR_BOP_IMAG		0x40
#define PR_BOP_GRAP		0x10
#define PR_BOP_TEXT		0x04
#define PR_BOP_LINE		0x01

#define PR_SUPPRESS_NORMAL	0x00000000
#define PR_SUPPRESS_SPACE	0x00000001
#define	PR_SUPPRESS_MASK	(PR_SUPPRESS_NORMAL | PR_SUPPRESS_SPACE)

#define	PR_RULE_WIN		0x00	/* scanline rule (Windows)	*/
#define	PR_RULE_PS		0x80	/* scanline rule (PS)		*/

/*
 *	ROP modes.
 */
#define PR_ROP_COLOR_SRC	0x00
#define PR_ROP_COLOR_BRUSH	0x01
#define PR_ROP_COLOR_MASK	0x01
#define PR_ROP_CC_BRUSH		0x00
#define PR_ROP_CC_SRC		0x02
#define PR_ROP_CC_MASK		0x02

/*
 *	print mode (pr_setratio_rgb, pr_setratio_tonerlimit)
 */
#define PR_PRINT_NORMAL		0x00	/* Normal Print */
#define PR_PRINT_COMPBK		0x01	/* CompositeBlack Print */

/*******************************************************************
 **	cached object data tags.				  **
 *******************************************************************/

#define	PR_SINGLE_SFONT		0x00	/* single char with soft font.	*/
#define	PR_SINGLE_SFONT_CTL	0x02	/* regist single char with soft font.(comp) */
#define	PR_SINGLE_SFONT_CTLn	0x03	/* regist single char with soft font.(nocomp(run)) */
#define	PR_POLYLINE		0x11	/* polyline.			*/
#define	PR_POLYLINE_PATH	0x12	/* polyline.(path many)		*/
#define	PR_POLYBEZIER		0x13	/* polybezier.			*/
#define	PR_POLYBEZIER_PATH	0x14	/* polybezier.(path many)	*/
#define	PR_SCANLINE		0x15	/* scanline.			*/
#define	PR_BITBLT		0x20	/* bitblt.			*/
#define	PR_STRETCHBLT		0x21	/* stretchblt.			*/
#define	PR_BRUSH		0x30	/* brush.			*/

/*
 *	inforamtion of errors.
 *		各関数のエラー判定は基本として、
 *			PR_ERR_FATAL
 *			PR_ERR_SYNTAX
 *			PR_ERR_STATUS
 *			PR_ERR_INVALID
 *			その他。。。
 *			の順で行なう。
 */
#define	PR_ERR_FATAL		0x01	/* NULL pointer.		*/
#define	PR_ERR_DRAW		0x02	/* draw error.	        	*/
#define	PR_ERR_MEMORY		0x03	/* memory allocation error.	*/
#define	PR_ERR_STATUS		0x04	/* status error.		*/
#define	PR_ERR_INIT		0x05	/* init error.     		*/
#define	PR_ERR_FUNC		0x06	/* function error.     		*/
#define PR_ERR_DOWNLOAD		0x07	/* download error.		*/
#define	PR_ERR_INVALID		0x08	/* invalid value error.		*/
#define	PR_ERR_SYNTAX		0x09	/* invalid parameter error.	*/
#define	PR_ERR_SUPPORT		0x0a	/* support error */

/*
 *	memory type
 */

#define	PR_MEMORY_USED		0x80000000
				/* 0: 呼び出し側領域, 1: pr 領域	*/
/*
 *	for pr_definefont_device
 */
#define	PR_FNT_R0	0x00	/* 反時計周りに  0度回転 */
#define	PR_FNT_R90	0x04	/* 反時計周りに 90度回転 */
#define	PR_FNT_R180	0x08	/* 反時計周りに180度回転 */
#define	PR_FNT_R270	0x0c	/* 反時計周りに270度回転 */

#define PR_FNT_NOSTY		0x00	/* スタイルなし */
#define PR_FNT_STY_BLD		0x10	/* Bold */
#define PR_FNT_STY_ITL		0x20	/* Italic */
#define PR_FNT_STY_BLDITL	0x30	/* BoldItalic */

#define	PR_F_PMINCHO		0x0000	/* MS-P mincho font.		*/
#define	PR_F_PGOTHIC		0x0004	/* MS-P gothic font.		*/
#define	PR_F_MINCHO		0x0008	/* MS mincho font.		*/
#define	PR_F_GOTHIC		0x000c	/* MS gothic font.		*/
#define	PR_F_TIMES_ROME		0x0010	/* times new roman.		*/
#define	PR_F_TIMES_ROMEB	0x0011	/* times new roman(bold).	*/
#define	PR_F_TIMES_ROMEI	0x0012	/* times new roman(italic).	*/
#define	PR_F_TIMES_ROMEBI	0x0013	/* times new roman(italic/bold).*/
#define	PR_F_ARIAL		0x0014	/* arial.			*/
#define	PR_F_ARIALB		0x0015	/* arial(bold).			*/
#define	PR_F_ARIALI		0x0016	/* arial(italic).		*/
#define	PR_F_ARIALBI		0x0017	/* arial(italic/bold).		*/
#define	PR_F_COURIER		0x0018	/* Courier.			*/
#define	PR_F_COURIERB		0x0019	/* Courier(bold).		*/
#define	PR_F_COURIERI		0x001a	/* Courier(Italic).		*/
#define	PR_F_COURIERBI		0x001b	/* Courier(Italic/Bold).	*/
#define	PR_F_WINGDINGS		0x0020	/* wingdings.			*/
#define	PR_F_SYMBOL		0x0024	/* Symbol.			*/
#define	PR_F_CENTURY		0x0028	/* Century.			*/
#define PR_F_OCRB		0x002c	/* OCR B('P'&'I')		*/
#define PR_F_OCRB2		0x0030	/* OCR B2('P'&'I')		*/
#define PR_F_PROLQ10		0x0034	/* PRO_LQ 10 ('P'&'U')		*/
#define PR_F_PROLQ12		0x0038	/* PRO_LQ 12 ('P'&'U')		*/
#define PR_F_PROLQ15		0x003c	/* PRO_LQ 15 ('P'&'U')		*/
#define	PR_F_HGPAGOTHIC_EUSTD	0x0040  /* HGP-AGothic ('P'&'S')	*/
#define	PR_F_HGPAGOTHIC_CE	0x0044  /* HGP-AGothic ('P'&'Q')	*/
#define	PR_F_HGPAGOTHIC_CYR	0x0048  /* HGP-AGothic ('P'&'R')	*/
#define	PR_F_HGPAGOTHIC_GREEK	0x004c  /* HGP-AGothic ('P'&'D')	*/
#define	PR_F_ATPMINCHO		0x8000	/* MS-P mincho '@' font.	*/
#define	PR_F_ATPGOTHIC		0x8004	/* MS-P gothic '@' font.	*/
#define	PR_F_ATMINCHO		0x8008	/* MS mincho '@' font.		*/
#define	PR_F_ATGOTHIC		0x800c	/* MS gothic '@' font.		*/
/*
 *	for pr_putchar_download
 */
#define	PR_FNT_JAGGY		0x00000100	/* ジャギー補正 0:OFF, 1:ON */
#define	PR_FNT_CTYPE		0x00000003	/* CompressDataTypeMask */
#define	PR_FNT_CTYPE_BMP		0	/* BMP */
#define	PR_FNT_CTYPE_RUN		1	/* RUN */
#define	PR_FNT_CTYPE_MMR		2	/* MMR */

#define	PR_FNT_CACHETYPE	0x30		/* CachingDataTypeMask */

/*
 *	for permanent font
 */
#define	FNT_CTLDEVICE_SAVE		0x00
#define	FNT_CTLDEVICE_LOAD		0x01
#define	FNT_CTLDEVICE_DELETE_FILE	0x02
#define	FNT_CTLDEVICE_DELETE_DIR	0x03

#define	EXTERNALFONT_FILENAMESZ		229

#define	FNT_CTLDEVDEL_FILE		0x00
#define	FNT_CTLDEVDEL_DIRECTORY		0x01

#define	PERMFONTIDSTART		0xf000
#define	PERMFONTIDEND		0xfffe
#define	EXTERNALFONTIDSTART	0xf000
#define	EXTERNALFONTIDEND	0xf100

/*
 *	for BitBlt
 */
#define	PR_BITBLT_BPP_MASK	0x00000003
#define	PR_BITBLT_1BPP		0x00000000
#define	PR_BITBLT_2BPP		0x00000001
#define	PR_BITBLT_4BPP		0x00000002
#define	PR_BITBLT_8BPP		0x00000003
#define	PR_BITBLT_COLORMODE	0x00000004	/* 0: Mono, 1: Color */

/* スプール領域の先頭アドレスをイメージ格納領域先頭から求める */
#define PR_BITBLT_GETSPOOLADR(adr)	(adr - sizeof(int) * 5)
/* イメージ格納領域の先頭アドレスをスプール先頭から求める */
#define PR_BITBLT_GETIMAGEADR(adr)	(adr + sizeof(int) * 5)

/*
 *	for StretchBlt
 */
#define	PR_STRBLT_BPP_MASK	0x00000007 /* BPP 種別マスク */
#define	PR_STRBLT_1BPP		0x00000000 /* 1BPP */
#define	PR_STRBLT_4BPP		0x00000001 /* 4BPP */
#define	PR_STRBLT_8BPP		0x00000002 /* 8BPP */
#define	PR_STRBLT_24BPP		0x00000003 /* 24BPP */
#define	PR_STRBLT_32BPP		0x00000004 /* 32BPP */
#define	PR_STRBLT_COLOR_MASK	0x00000038 /* データ種別マスク */
#define	PR_STRBLT_MONO		0x00000000 /* 白黒データ */
#define	PR_STRBLT_RGB		0x00000008 /* RGB データ */
#define	PR_STRBLT_KCMY		0x00000010 /* KCMY データ */
#define	PR_STRBLT_INDEX_MASK	0x000000c0 /* Index Table 種別マスク */
#define	PR_STRBLT_INDEX_OFF	0x00000000 /* Index Table 無し */
#define	PR_STRBLT_INDEX_ON	0x00000040 /* Index Table 有り */
#define	PR_STRBLT_INDEX_EXIST	0x00000080 /* 機能未実装 */
#define	PR_STRBLT_INDEX_REGIST	0x000000c0 /* 機能未実装 */
#define	PR_STRBLT_INDEX_CMD2PR	6 /* コマンド仕様からPR仕様への shift */
#define	PR_STRBLT_REPEAT	0x00000200 /* 繰り返し描画 */
#define	PR_STRBLT_SEQUENTIAL	0x00000400 /* 面順次 */
#define	PR_STRBLT_REVERSE	0x00000800 /* 面順次 */
#define	PR_STRBLT_CMOSTMASK	0x00003000 /* CMOST モードマスク */
#define	PR_STRBLT_ZOOMCMOST	0x00001000 /* CMOST ON */
#define	PR_STRBLT_EDMASK	0x0000c000 /* ED モードマスク */
#define	PR_STRBLT_ED		0x00004000 /* ED ON */
#define	PR_STRBLT_DATAALIGN	0x00030000 /* Data Align 種別マスク */
#define	PR_STRBLT_NO_ALIGN	0x00000000 /* Align 無し */
#define	PR_STRBLT_ALIGN_1BYTE	0x00010000 /* 1Byte Align */
#define	PR_STRBLT_ALIGN_4BYTE	0x00020000 /* 4Byte Align */
#define	PR_STRBLT_THROUGH	0x00040000 /* Through gamma and toner limit */
#define	PR_STRBLT_RGB_ORDER	0x00000200 /* on:R,G,B  off:B,G,R */
#define	PR_STRBLT_EX_DATA	0x00000100 /* on:拡張データ off:通常データ */
#define	PR_IMAGE_ROTATE_MASK	0x30000000 /* コマンド毎の回転フラグ用マスク */
#define	PR_IMAGE_ROTATE_0	0x00000000 /* イメージデータをそのまま回転せずに描画する */
#define	PR_IMAGE_ROTATE_90	0x10000000 /* イメージデータを右９０度回転し描画する */
#define	PR_IMAGE_ROTATE_180	0x20000000 /* イメージデータを１８０度回転し描画する */
#define	PR_IMAGE_ROTATE_270	0x30000000 /* イメージデータを右２７０度回転し描画する */

/* pr_bitmap_clip用 */
#define	PR_BITCLIP_DATAALIGN	0x00000003 /* Data Align 種別マスク(ビットマップクリップ) */
#define	PR_BITCLIP_ALIGN_1BYTE	0x00000001 /* 1Byte Align(ビットマップクリップ) */
#define	PR_BITCLIP_ALIGN_4BYTE	0x00000002 /* 4Byte Align(ビットマップクリップ) */

/* スプール領域の先頭アドレスをイメージ格納領域先頭から求める */
#define	PR_STRBLT_GETSPOOLADR(adr)	(adr - sizeof(int) * 11)
/* イメージ格納領域の先頭アドレスをスプール先頭から求める */
#define	PR_STRBLT_GETIMAGEADR(adr)	(adr + sizeof(int) * 11)

/* 通知情報 */
#define PR_VALUE_PROTID		0x00000001 /* プロッタID */
#define PR_VALUE_PAGECOUNT	0x00000002 /* フレーム作成を要求したページ数（ジョブ毎） */
#define PR_VALUE_PRINTCOUNT	0x00000003 /* 実際にフレーム印刷を要求したページ数（ジョブ毎） */
#define PR_VALUE_USEDCOLOR	0x00000004

/* CMM デジカメ補正テーブルサイズ */
#define PR_ACCENTPHOTOTABLESIZE 256

/* メモリ削減モード */
#define	PR_REDUCEMEMORY_MASK	0x00000001U
#define	PR_REDUCEMEMORY_OFF	0x00000000U
#define	PR_REDUCEMEMORY_MODE1	0x00000001U

/*
 *	for URF
 */
#define	PR_URF_MONO			0
#define	PR_URF_RGB			1
#define	PR_URF_ROTATE_0		0
#define	PR_URF_ROTATE_90	1
#define	PR_URF_ROTATE_180	2
#define	PR_URF_ROTATE_270	3

/*
 *	for Barcode
 */

/* Declaration for command param */

#define	PR_BC_CODE128		0x01
#define	PR_BC_JAN		0x02
#define	PR_BC_JANS		0x03
#define	PR_BC_UPCA		0x04
#define	PR_BC_UPCE		0x05
#define	PR_BC_NW7		0x06
#define	PR_BC_CODE39		0x07
#define	PR_BC_25ID		0x08
#define	PR_BC_25M		0x09
#define	PR_BC_25IL		0x0a
#define	PR_BC_CUSTOM		0x0b
#define	PR_BC_QR		0x0c
#define	PR_BC_EAN128		0x0d

/* Declaration for buffer data */

#define	PR_BC_MAX_PARAM		256
#define	PR_BC_MAX_DATA		259
#define	PR_BC_MAX_CHAR		(PR_BC_MAX_DATA * 2)

/* Declaration for CODE128 */

#define	PR_BC_CODE128_UNIT	11

#define	PR_BC_CODE128_START_A	103
#define	PR_BC_CODE128_START_B	104
#define	PR_BC_CODE128_START_C	105
#define	PR_BC_EAN128_AI1	106
#define	PR_BC_EAN128_AI2	107
#define	PR_BC_EAN128_AI3	108
#define	PR_BC_CODE128_STOP	109

#define PR_BC_CODE_SET_A	1
#define PR_BC_CODE_SET_B	2
#define PR_BC_CODE_SET_C	3

typedef struct pr_bc_code128
{
	unsigned short h;
	unsigned short uw;
	unsigned short fid;
	unsigned short dfid;
	unsigned short cw;
	unsigned short ch;
	unsigned char cg;
	unsigned short sum;
	char start;
} pr_bc_code128_t;

/* Declaration for JAN */

#define	PR_BC_JAN_UNIT	7

typedef struct pr_bc_jan
{
	unsigned short h;
	unsigned short uw;
	unsigned short fid;
	unsigned short dfid;
	unsigned short cw;
	unsigned short ch;
	unsigned char cg;
	unsigned short sum;
	char ns;
} pr_bc_jan_t;

/* Declaration for NW7 */

typedef struct pr_bc_nw7
{
	unsigned short h;
	unsigned short nbw;
	unsigned short nsw;
	unsigned short wbw;
	unsigned short wsw;
	unsigned char g;
	unsigned short fid;
	unsigned short dfid;
	unsigned short cw;
	unsigned short ch;
	unsigned char cg;
	unsigned short sum;
	char start;
	char stop;
} pr_bc_nw7_t;

/* Declaration for CUSTOM */

#define	PR_BC_CUSTOM_START	19
#define	PR_BC_CUSTOM_STOP	20

typedef struct pr_bc_custom
{
	unsigned char p;
} pr_bc_custom_t;

/* Declaration for QR */

#define	PR_BC_QR_DIR_V		0
#define	PR_BC_QR_DIR_H		1

typedef struct pr_bc_qr
{
	char m;
	unsigned short cell;
	char quality;
	char imode;
	unsigned char div;
	char dir;
} pr_bc_qr_t;

typedef struct pr_qrhead
{
	unsigned char div_mark;
	unsigned char div_numerator0;
	unsigned char div_numerator1;
	unsigned char div_denominator0;
	unsigned char div_denominator1;
	unsigned char parity_h;
	unsigned char parity_l;
	unsigned char separater1;
	unsigned char quality_level;
	unsigned char input_mode;
	unsigned char separater2;
} pr_bc_qrhead_t;

/* Declaration for EAN128 */
typedef struct pr_bc_ean128
{
	unsigned short h;
	unsigned short uw;
	unsigned short fid;
	unsigned short dfid;
	unsigned short cw;
	unsigned short ch;
	unsigned char cg;
	unsigned short sum;
	char start;
	char ai1;
	char ai2;
} pr_bc_ean128_t;

typedef union pr_barcode
{
	pr_bc_code128_t code128;
	pr_bc_jan_t jan;
	pr_bc_nw7_t nw7;
	pr_bc_custom_t custom;
	pr_bc_qr_t qr;
	pr_bc_ean128_t ean128;
} pr_barcode_t;

/*
 *	PR用 TRUE / FALSE
 */
#define	PR_TRUE  		 1
#define	PR_FALSE		 0

/* Graphics */
/* pr_scanlinepath用ポインタテーブル構造体 */
typedef struct pr_spl_scanlinepath_data
{
	unsigned long size;		/* パスのサイズ */
	unsigned char *data;		/* パスのデータへのポインタ */
} pr_scpath_data;

/* ディザ情報構造体 */
typedef struct pr_dit_info
{
	unsigned char *dit_ptr;		/* ディザの先頭アドレス */
	unsigned char x_size;			/* 幅 */
	unsigned char y_size;			/* 高さ */
	unsigned char dit_order;		/* DIT_ORDER(痾値) */
	unsigned short rearrange;		/* rearrange ID */
	unsigned char	e_flag_max;		/* engine flag for color level: 255 */
	unsigned char	e_flag_mid;		/* engine flag for color level: 1 to 254 */
} pr_dit_info_t;

/* 解像度構造体 */
typedef struct pr_reso_info
{
	unsigned int x;	/* 主走査方向解像度 */
	unsigned int y;	/* 副走査方向解像度 */
} pr_reso_info_t;

/* 解像度構造体(ビットとの組合せ) */
typedef struct pr_resolution_info
{
	unsigned int x;		/* 主走査方向解像度 */
	unsigned int y;		/* 副走査方向解像度 */
	unsigned char bit;	/* ビット数 */

	unsigned char pkgroup;      /* 紙種グループ */
	unsigned char dit_mode;     /* ディザモード */
	unsigned char prtmode;       /* 印刷モード(高速/標準/高精細) */

} pr_resolution_info_t;

/* 総量規制値情報構造体 */
typedef struct pr_tlimit_info
{
	pr_resolution_info_t reso;	/* 解像度&深さ */
	int text;	/* 文字オブジェクト */
	int line;	/* 線画オブジェクト */
	int phot;	/* 写真オブジェクト */
	int fill;	/* 塗りつぶしオブジェクト */
} pr_tlimit_info_t;


/* imaqual.dat用情報構造体 */
typedef struct pr_bgucrinfo
{
	unsigned char *bg;  /* BGテーブル */
	unsigned char *ucr;/* UCRテーブル */
	unsigned char *bg_hgr;  /* BGテーブル(高墨) */
	unsigned char *ucr_hgr;/* UCRテーブル(高墨) */
	unsigned char *bg_compbk; /* for composite black */
	unsigned char *ucr_compbk;
} pr_bgucrinfo_t;

typedef struct pr_gcrinfo
{
	unsigned long flag;
	short *CB_bg;
	short *CB_ucr;
	short *CG_bg;
	short *CG_ucr;
	short *YG_bg;
	short *YG_ucr;
	short *MB_bg;
	short *MB_ucr;
	short *MR_bg;
	short *MR_ucr;
	short *YR_bg;
	short *YR_ucr;
} pr_gcrinfo_t;

typedef struct pr_dropinfo
{
	unsigned char *lit;/* 滴量データ */
	unsigned char *inv;/* 逆変換テーブル */
} pr_dropinfo_t;

typedef struct pr_dupgaminfo
{
	unsigned char *gam_front; /* 表面割合  */
	unsigned char *gam_back; /* 裏面割合 */
} pr_dupgaminfo_t;


typedef struct ExternalFontImage
{
	unsigned short regimgw;
	unsigned short regimgh;
	unsigned short offsetx;
	unsigned short offsety;
	unsigned char direct;
	unsigned char reserved[3];
	void *data;
} pr_external_fontimg_t;

/* IJデバイス情報構造体 */
typedef struct pr_ij_info
{
	unsigned long headnum;		/* ヘッド数 */
	unsigned long nozzlenum;	/* ノズル数 */
	unsigned long nozzlepitch;	/* ノズルピッチ数 */
	unsigned long overlapnum;	/* オーバーラップ数 */
	unsigned long multipath;	/* マルチパス数 */
	unsigned long direction;	/* スキャン方向:片方向・双方向 */
	unsigned long compmode;		/* 圧縮パラメータ */
	unsigned long bound;		/* 実バンドイメージのboundary数:byte */
	unsigned long planemode;	/* 順次指定:線順次・面順次・点順次 */
	unsigned long machineID;	/* 機種 ID */
	/* Alsace-P1	: 0x01010001	*/
	/* Alsace-P1W	: 0x01010011	*/
	/* Provence-P1	: 0x01020001	*/
	unsigned long supplement;	/* 捕捉機能 */
	/* 単色双方向処理  : 0x00000001	*/
	/* 先端線速遅延    : 0x00000002	*/
	/* 後端線速遅延    : 0x00000004	*/
	/* overlap無効化   : 0x00000008	*/
	/* 組み付け誤差調整: 0x00000010	*/
	char dllname[260];		/* IJ Renderer の DLL 名	*/
	unsigned char headid[4];	/* ヘッドばらつき ID 番号	*/
	unsigned long ffeedline;	/* 先端遅延基準ライン		*/
	unsigned long reserve[9];	/* 予約領域			*/
} pr_ij_info_t;

/* 機種情報構造体 */
typedef struct pr_dev_info
{
	/*
	 * ディザ情報
	 * 実際の数は
	 *  解像度&ビット数 x ディザ種類数 x プレーン数
	 * 配置順は
	 *  for 解像度&ビット組み合わせ数(順番はreso_setで指定)
	 *      for ディザ種類数(photo -> text -> cad -> graphics)
	 *        for プレーン数(C -> M -> Y -> K)
	 *          dither_info
	 * となる
	 */
	pr_dit_info_t *dither_info;

	/*
	 * ガンマ情報
	 * 数,配置順は dither_info と同様
	 */
	unsigned char **gamma_info;

	unsigned char *font_address;	/* デバイスフォントの先頭アドレス */
	/* NULLの場合は使用しない */
	unsigned long font_size;		/* デバイスフォントサイズ */

	long dither_cache;	/* ディザキャッシュサイズ(byte 単位) */
	/*
	 * ４色同時描画する場合の痾値
	 * １バンド描画に必要なバイト数 <= band_4C_thresh
	 * なら４色同時描画する(PRがサポートしている場合のみ有効)
	 */
	int band_4C_thresh;
	/*
	 * PR側でバンディングする時に必要なパラメータ
	 * バンド高さは
	 * (bandsize * 100 * 1024) / (４バイトアライン修正された)ページ幅
	 */
	int bandsize;
	int minbandheight;
	int maxbandheight;

	unsigned int resonum;	/* サポート解像度&ビット組み合わせ種類数  */
	pr_resolution_info_t *reso_set;	/* 解像度&ビット組合せ */
	/* reso分ある(=reso_set[resonum]) */
	int ndit;			/* dither種類数 */
	int nplane;			/* プレーン数[1:mono, 4:color] */
	float bg_startp;		/* BG が始まる開始レベル */
	float bg_slant;		/* BG 直線勾配 */
	float ucr_startp;		/* UCR が始まる開始レベル */
	float ucr_slant;		/* UCR 直線勾配 */
	int soft_tsave;		/* ソフトトナーセーブのサポート[1:あり, 0:なし] */
	float tsave_ratio;	/* ソフトトナーセーブ割合(0.0 - 1.0) */

	int extend_soft_tsave;	/* 拡張ソフトトナーセーブの対応[1:あり, 0:なし] */

	int toner_limit;	/* 総量規制のサポート[1:あり, 0:なし] */
	unsigned int tlimit_num;	/* 機種がサポートしている総量規制値の種類数 */
	/*
	 * 総量規制値のバリエーション
	 * tlimit_num 分ある(=tlimit_val[tlimit_num])
	 * 一番最初がデフォルト値(解像度,深さは0にセット),
	 * それ以外は特殊モード
	 */
	pr_tlimit_info_t *tlimit_val;

	/* システムハンドル。現状GPSのみ有効 */
	long sys_handle;
	/*
	 * ジョブリセットの通知受信変数
	 * 外部で変更される
	 * 通知しない場合はNULL
	 */
	int *notified_job_resetted;
	int *notified_forced_job_reset;

	/* CMMで使用するプロファイル情報 */
	void *profaddress;
	long profnumber;


	unsigned long flag;                     /* フラグ */
	unsigned int mode_num;                 /* 描画モードの総数 */
	pr_bgucrinfo_t **bgucr_info;  /* BG/UCR情報 */
	pr_gcrinfo_t *gcr_info;     /* WiShGCR */
	pr_gcrinfo_t *gcrhgr_info;     /* WiShGCR(高墨) */
	pr_dropinfo_t **drop_info;   /* 滴量補正情報 */
	pr_dupgaminfo_t **dupgam_info; /* 両面γ割合情報 */

	int pqtc;        /* 適量補正のON/OFF(OFF:FALSE,ON:TRUE) */
} pr_dev_info_t;

typedef struct pr_preceding_info
{
	int job_id;			/* ジョブID */
	unsigned short resox;			/* X方向解像度 (25.4mmあたりのドット数) */
	unsigned short resoy;			/* Y方向解像度 (25.4mmあたりのドット数) */
	unsigned char depth;			/* 量子化数(階調) */
	unsigned char paper_type;		/* 紙種 */
	unsigned char color_count;	/* 色数 */
} pr_preceding_info_t;

typedef struct pr_job_info
{
	/* 各種フラグ */
	int flag;
#define PR_JOBINFO_IS_DUPLEX			0x00000001
#define PR_JOBINFO_IS_IMAGE_SKIP		0x00000002
#define PR_JOBINFO_IS_PANELOUT_ROTATED	0x00000004
#define PR_JOBINFO_FULL_SLANT_ITALIC		0x00000008
#define PR_JOBINFO_XRGB_ACCUMULATION		0x00000010

	/* job_id */
	int job_id;

	/* gps_pageparam_t の情報 */
	unsigned long para;		/* 設定するパラメータ(オリジナルではflag) */
	unsigned short qty;		/* 印刷部数 */
	unsigned char outmode;	/* 印刷モード */
	unsigned char binding;	/* 縦とじ方向*/
	short margin1v;	/* 縦とじ代(両面第１面) */
	short margin1h;	/* 横とじ代(両面第１面) */
	short margin2v;	/* 縦とじ代(両面第２面) */
	short margin2h;	/* 横とじ代(両面第２面) */
	unsigned char finish;		/* 仕分け指定 */
	unsigned char upsidedown;	/* 180度回転 */
	unsigned char color_count;	/* 色数 */
	unsigned char paper_code;
	unsigned char paper_type;
	unsigned char slip;		/* 合紙モード */
	unsigned char slip_tray;		/* 合紙トレイ */
} pr_job_info_t;


typedef struct pr_page_info
{
	/* 各種フラグ */
	int flag;
#define PR_PAGEINFO_IS_LANDSCAPE		0x00000001
#define PR_PAGEINFO_IS_SEF				0x00000002
#define PR_PAGEINFO_IS_CUSTOM			0x00000004
#define PR_PAGEINFO_IS_REVERSE			0x00000008
#define PR_PAGEINFO_LOAD_ENV			0x00000010

#define PR_PAGEINFO_HARDTONERSAVE_OFF	0x00000020

#define PR_PAGEINFO_IS_DUPLEX			0x00000040
#define PR_PAGEINFO_IGNORE_2NDFACE_DIR	0x00000080

	/* gps_pageinfo_t の情報 */
	unsigned char paper_code;			/* 用紙サイズ・コード */
	unsigned short paper_width;		/* フリーサイズ時の用紙幅 */
	unsigned short paper_length;		/* フリーサイズ時の用紙幅 */
	unsigned long xoffset;			/* 水平方向オフセット */
	unsigned long yoffset;			/* 垂直方向オフセット */
	unsigned char fci;				/* fci */
	unsigned char input_tray;			/* 給紙トレイ */
	unsigned char paper_type;			/* 紙種 */
	unsigned char limitless_feed;		/* リミットレス給紙*/
	unsigned short paper_count;		/* 出力枚数 */
	unsigned char count_off;			/* ページカウントしない */
	unsigned long para;
#define PR_COUNT_ON			(0)	/* カウントする  */
#define PR_COUNT_OFF			(1)	/* カウントしない */
	unsigned char outmode;	/* 印刷モード*/
	unsigned char binding;	/* 縦とじ方向 */
	short margin1v;	/* 縦とじ代(両面第１面) */
	short margin1h;	/* 横とじ代(両面第１面) */
	short margin2v;	/* 縦とじ代(両面第２面) */
	short margin2h;	/* 横とじ代(両面第２面) */

	/* gps_pagemode_t の情報 */
	int memory_rotate;		/* メモリ上の画像向き */

	unsigned long paper_width2;            /* フリーサイズ時の用紙幅(ulong) */
	unsigned long paper_length2;          /* フリーサイズ時の用紙長さ(ulong) */


	unsigned char pkgroup;    /* 紙種グループ */
	unsigned char prtmode;    /* 印刷モード */


	unsigned char page_shift;	/* ページシフト */
	unsigned char eco_color;	/* エコノミーカラーモード */

} pr_page_info_t;

typedef struct pr_page_info_s
{
	unsigned long flag;			/* 設定するパラメータ */
	unsigned short output_tray;	/* 排紙トレイ */
	unsigned char limitless_exit;	/* シーケンシャルスタック */
	unsigned char staple;			/* ステープル */
	unsigned char punch;				/* パンチ */
	unsigned char z_fold;			/* Z折り */
	unsigned char tonersave;		/* トナーセーブ */
	unsigned char jamrecovery;	/* ジャムリカバリー */
	unsigned char face;			/* 印刷面の指定 */
#define PR_FACE_SINGLE	(0)		/* 片面 */
#define PR_FACE_DPX1ST	(1)		/* 両面第１面 */
#define PR_FACE_DPX2ND	(2)		/* 両面第２面 */
	unsigned char shift;			/* 部間でシフトをする／しない */
	unsigned short paper_count;	/* 出力枚数 */
	unsigned char count_off;	/* ページカウントの指定 */
	unsigned char slip;		/* 合紙モードの指定 */
	unsigned char slip_tray;	/* 合紙モードのトレイ番号指定 */
	unsigned char cover;		/* 表紙モード */
	unsigned char coverprint;	/* 表紙画像印刷面 */
	unsigned char cover_tray;	/* 表紙トレイ */
	unsigned char backcover;	/* 裏表紙モード */
	unsigned char backcoverprint;	/* 裏表紙画像印刷面 */
	unsigned char backcovertray;	/* 裏表紙トレイ */
} pr_page_info_s_t;

/* define the members of pr_page_info_shm_t */
typedef struct prMargin {
	signed short		margin1v;		/* 縦とじ代(両面時、第1面 0.1mm単位) */
	signed short		margin1h;		/* 横とじ代(　　    〃 　 　   ) */
	signed short		margin2v;		/* 縦とじ代(両面第2面 0.1mm単位) */
	signed short		margin2h;		/* 横とじ代(　　  〃 　    ) */
} prMargin_t;

/* --表紙-- */
typedef struct prCover {
	unsigned char		mode;			/* モード */
#define	PR_SHM_COVER_OFF		PR_COVER_OFF		/* 表紙ＯＦＦ */
#define	PR_SHM_COVER_FRONT		PR_COVER_FRONT		/* おもて表紙ＯＮ */
#define	PR_SHM_COVER_BACK		PR_COVER_BACK		/* うら表紙ＯＮ */

	unsigned char		front;			/* おもて表紙モード */
#define	PR_SHM_COVER_OFF		PR_COVER_OFF		/* 表紙に印刷しない */
#define	PR_SHM_COVER_FRONT		PR_COVER_FRONT		/* 表紙に片面印刷する */
#define	PR_SHM_COVER_FRONT_D	PR_COVER_FRONT_D	/* 表紙に両面印刷する */

	unsigned char		back;			/* うら表紙モード */
#define	PR_SHM_COVER_OFF		PR_COVER_OFF		/* 裏表紙に印刷しない */
#define	PR_SHM_COVER_BACK		PR_COVER_BACK		/* 裏表紙に印刷する */
#define	PR_SHM_COVER_BACK_R		PR_COVER_BACK_R		/* 裏表紙反転排紙 */
													/* (画像が片面の場合のみ) */

	unsigned char		fcover_tray;	/* 表紙トレイ */
	unsigned char		bcover_tray;	/* 裏表紙トレイ */
} prCover_t;

typedef struct prSlip {
	unsigned char	mode;
#define	PR_SHM_SLIP_OFF			PR_SLIP_OFF
#define	PR_SHM_SLIP_ON			PR_SLIP_ON
#define	PR_SHM_SLIP_PRINT		PR_SLIP_PRINT

	unsigned char	slip_tray;
} prSlip_t;

typedef struct prPartition {
	unsigned char	mode;
#define	PR_SHM_PARTITION_OFF		(0)
#define	PR_SHM_PARTITION_SORT		(1)
#define	PR_SHM_PARTITION_JOB		(2)

	unsigned short	cycle;
} prPartition_t;

typedef struct prPunch {
	unsigned char	pos;
#define	PR_SHM_PUNCH_OFF			(0)
#define	PR_SHM_PUNCH_LEFT			(1)
#define	PR_SHM_PUNCH_TOP			(2)
#define	PR_SHM_PUNCH_RIGHT			(3)
#define	PR_SHM_PUNCH_LEFT_TOP		(4)

	unsigned char	unit;
#define	PR_SHM_PUNCH_JP2			(0)
#define	PR_SHM_PUNCH_US2			(1)
#define	PR_SHM_PUNCH_US3			(2)
#define	PR_SHM_PUNCH_EU4			(3)
#define	PR_SHM_PUNCH_NEU4			(4)
#define	PR_SHM_PUNCH_JP1			(5)
#define	PR_SHM_PUNCH_MULTI			(6)
} prPunch_t;

typedef struct prW_Fold {
	unsigned char	w_fold;
#define	PR_SHM_W_FOLD_OFF			(0)		/* 折りなし */
#define	PR_SHM_W_FOLD_ZIGZAG		(1)		/* ジャバラ折り */
#define	PR_SHM_W_FOLD_ZIGZAGFILE	(2)		/* ジャバラファイル折り */
#define	PR_SHM_W_FOLD_BASIC			(3)		/* 基本折り */
#define	PR_SHM_W_FOLD_BAG			(4)		/* 袋折り */
#define	PR_SHM_W_FOLD_FILE			(5)		/* ファイル折り */
#define	PR_SHM_W_FOLD_CUSTOM1		(6)		/* 特殊折り１ */
#define	PR_SHM_W_FOLD_CUSTOM2		(7)		/* 特殊折り２ */
#define	PR_SHM_W_FOLD_PROGRAM1		(8)		/* プログラム折り１ */
#define	PR_SHM_W_FOLD_PROGRAM2		(9)		/* プログラム折り２ */
#define	PR_SHM_W_FOLD_PROGRAM3		(10)	/* プログラム折り３ */
#define	PR_SHM_W_FOLD_PROGRAM4		(11)	/* プログラム折り４ */
#define	PR_SHM_W_FOLD_ZIGZAGCUSTOM1	(12)	/* Special Fan Fold 1 */
#define	PR_SHM_W_FOLD_ZIGZAGCUSTOM2	(13)	/* Special Fan Fold 2 */
	
	unsigned long	zigzag_width;	/* ジャバラ折りの折り幅(0.1mm単位) */
	unsigned char	w_punch;		/* 折り機パンチ */
#define	PR_SHM_W_PUNCH_OFF			(0)		/* 折り機パンチなし */
#define	PR_SHM_W_PUNCH_ON			(1)		/* 折り機パンチあり */

	unsigned char	w_edgefold;		/* 耳折り */
#define	PR_SHM_W_EDGEFOLD_OFF		(0)		/* 耳折りなし */
#define	PR_SHM_W_EDGEFOLD_ON		(1)		/* 耳折りあり */
	
	unsigned char	w_machinestamp;
#define	PR_SHM_W_MACHINE_STAMP_OFF	(0)
#define	PR_SHM_W_MACHINE_STAMP_ON	(1)

	unsigned char	reserve[64];
} prW_Fold_t;

/* --リング製本-- */
typedef struct prRingBind {
	unsigned char		ring_bind;	/* リング製本設定 */
#define	PR_SHM_RING_BIND_OFF		(0)		/* リング製本しない */
#define	PR_SHM_RING_BIND_ON			(1)		/* リング製本する */

	unsigned char		bind_pos;	/* リング製本綴じ位置 */
#define	PR_SHM_RING_BIND_LEFT		(1)		/* 左綴じ */
#define	PR_SHM_RING_BIND_TOP		(2)		/* 上綴じ */
#define	PR_SHM_RING_BIND_RIGHT		(3)		/* 右綴じ */

	unsigned char		bind_mode;	/* リング製本モード設定 */
#define	PR_SHM_RING_BIND_MODE_PUNCH	(1)		/* パンチのみモード */
#define	PR_SHM_RING_BIND_MODE_RING	(2)		/* リング製本モード */

	unsigned char		reserve[5];
} prRingBind_t;

typedef struct prPerfectBind {
	unsigned char		perf_bind;	/* くるみ製本設定 */
#define	PR_SHM_PERF_BIND_OFF		(0)		/* くるみ製本しない */
#define	PR_SHM_PERF_BIND_ON			(1)		/* くるみ製本する */

	unsigned char		bind_pos;	/* くるみ製本綴じ位置 */
#define	PR_SHM_PERF_BIND_LEFT		(1)		/* 左綴じ */
#define	PR_SHM_PERF_BIND_TOP		(2)		/* 上綴じ */
#define	PR_SHM_PERF_BIND_RIGHT		(3)		/* 右綴じ */

	unsigned char		perf_trim;	/* くるみ製本裁断設定 */
#define	PR_SHM_PERF_TRIM_NONE		(0)		/* 裁断なし */
#define	PR_SHM_PERF_TRIM_SINGLE		(1)		/* 小口カット */
#define	PR_SHM_PERF_TRIM_TRIPLE		(2)		/* 三辺カット */

	unsigned char		trim_mode;	/* くるみ製本裁断モード設定 */
#define	PR_SHM_PERF_TRIM_MODE_FINALSIZE	(1)		/* 仕上がりサイズ指定 */
#define	PR_SHM_PERF_TRIM_MODE_CUTSIZE	(2)		/* カット範囲指定 */

	unsigned char		perf_paper_code;	/* くるみ製本 中紙サイズコード */
	unsigned long		perf_paper_width;	/* くるみ製本 フリーサイズ時の中紙幅(副操作方向)　 (0.1mm単位) */
	unsigned long		perf_paper_length;	/* くるみ製本 フリーサイズ時の中紙高さ(主操作方向) (0.1mm単位) */
	unsigned char		perf_input_tray;	/* くるみ製本 中紙給紙トレイ */
	unsigned char		perf_cover_tray;	/* くるみ製本 表紙トレイ */
#define	PR_TRAY_1			(1)		/* 本体第１給紙トレイ */
#define	PR_TRAY_2			(2)		/* 本体第２給紙トレイ */
#define	PR_TRAY_3			(3)		/* 本体第３給紙トレイ */
#define	PR_TRAY_4			(4)		/* 本体第４給紙トレイ */
#define	PR_TRAY_5			(5)		/* 本体第５給紙トレイ */
#define	PR_TRAY_6			(6)		/* 本体第６給紙トレイ */
#define	PR_TRAY_7			(7)		/* 本体第７給紙トレイ */
#define	PR_TRAY_LCT			(0x0A)		/* 大量給紙トレイ */
#define	PR_TRAY_PERF_INSERTER		(0x12)		/* くるみインサータ上段 */
#define	PR_TRAY_PERF_INSERTER2		(0x13)		/* くるみインサータ下段 */

	unsigned char		perf_cover_mode;	/* くるみ製本 表紙モード */
#define	PR_SHM_PERF_COVER_BLANK		(0)	/* くるみ表紙に印刷しない */
#define	PR_SHM_PERF_COVER_PRINT_INSIDE	(1)	/* くるみ表紙に片面内側印刷する */
#define	PR_SHM_PERF_COVER_PRINT_OUTSIDE	(2)	/* くるみ表紙に片面外側印刷する */
#define	PR_SHM_PERF_COVER_PRINT_DUPLEX	(3)	/* くるみ表紙に両面印刷する */

	long			perf_cover_vert;		/* くるみ製本 表紙作像天地(主走査)位置調整 (0.1mm単位) */
	long			perf_cover_hori;		/* くるみ製本 表紙作像小口(副走査)位置調整 (0.1mm単位) */
	long			perf_image_vert;		/* くるみ製本 作像天地(主走査)位置調整 (0.1mm単位) */
	long			perf_image_hori;		/* くるみ製本 作像小口(副走査)位置調整 (0.1mm単位) */
	unsigned char	perf_final_paper_code;	/* 仕上がりサイズ指定時 製本サイズコード(paper.h 参照) */
	unsigned long	perf_final_paper_width;	/* 仕上がりサイズ指定時 フリーサイズ時の製本幅(副操作方向)　 (0.1mm単位) */
	unsigned long	perf_final_paper_length;/* 仕上がりサイズ指定時 フリーサイズ時の製本高さ(主操作方向) (0.1mm単位) */
	long			perf_final_paper_vert;	/* 仕上がりサイズ指定時 仕上がりサイズ位置調整 (0.1mm単位) */
	unsigned long	perf_cut_paper_top;	 	/* カット範囲指定時 天方向　 (0.1mm単位) */
	unsigned long	perf_cut_paper_bottom;	/* カット範囲指定時 地方向　 (0.1mm単位) */
	unsigned long	perf_cut_paper_side;	/* カット範囲指定時 小口方向 (0.1mm単位) */
	unsigned char	reserve[32];			/* 機能追加用 */
} prPerfectBind_t;

/* --マーキング[COSMOS]-- */
typedef struct prMarking {
	unsigned char	markingtype;	/* 埋め込み種類 */
#define	PR_SHM_MARKING_OFF				(0)		/* 埋め込みしない */
#define	PR_SHM_MARKING_COPYGUARD		(1)		/* 不正コピーガード */
#define	PR_SHM_MARKING_SECURITY			(2)		/* セキュリティートレース */
#define	PR_SHM_MARKING_FALSIFICATION	(3)		/* 改ざん検知 */
	
	/* 不正コピーガードＥＸ埋め込み */
	unsigned long	pattern_type;		/* 地紋種類 */
#define	PR_SHM_UCP_PATTERN_ON			(1<<0)	/* 抑止文字 */
#define	PR_SHM_COPYGUARD_ON				(1<<1)	/* 不正コピーガード */
#define	PR_SHM_COPYGUARD_EX_ON			(1<<2)	/* 不正コピーガードＥＸ */
#define	PR_SHM_SECURUTY_TRACE_ON		(1<<3)	/* セキュリティトレース */
#define	PR_SHM_PATTERN_AREA_FULL		(1<<4)	/* 地紋領域（ON:全面 OFF:枠のみ） */

	unsigned char	ucp_pattern_color;	/* 抑止文字の色 */
#define	PR_SHM_COLOR_K					(0)		/* ブラック */
#define	PR_SHM_COLOR_C					(1)		/* シアン */
#define	PR_SHM_COLOR_M					(2)		/* マゼンダ */	

	unsigned char	ucp_pattern_density;/* 抑止文字の濃度 */
	unsigned char	ucp_fg_effect;		/* 抑止文字の効果・文字色 */
#define	PR_SHM_UCP_FG_EFFECT_WHITE		(0)		/* 始めから消えている */
#define	PR_SHM_UCP_FG_EFFECT_VANISH		(1)		/* 消える */
#define	PR_SHM_UCP_FG_EFFECT_REMAIN		(2)		/* 消えない */

	unsigned char	ucp_bg_effect;		/* 抑止文字の効果・背景色 */
#define	PR_SHM_UCP_BG_EFFECT_WHITE		(0)		/* 始めから消えている */
#define	PR_SHM_UCP_BG_EFFECT_VANISH		(1)		/* 消える */
#define	PR_SHM_UCP_BG_EFFECT_REMAIN		(2)		/* 消えない */

	unsigned char	ucp_mask_type;		/* 抑止文字の模様 */
#define	PR_SHM_MASK_TYPE_NONE			(0)		/* 模様なし */
#define	PR_SHM_MASK_TYPE_SEIGAIHA		(1)		/* 青海波 */
#define	PR_SHM_MASK_TYPE_AMIME			(2)		/* 網目 */
#define	PR_SHM_MASK_TYPE_KOUSHI1		(3)		/* 格子１ */
#define	PR_SHM_MASK_TYPE_KOUSHI2		(4)		/* 格子２ */
#define	PR_SHM_MASK_TYPE_SHIPPOU		(5)		/* 七宝 */
#define	PR_SHM_MASK_TYPE_SYOKKOU		(6)		/* 蜀江 */
#define	PR_SHM_MASK_TYPE_MATSUKAWABISHI	(7)		/* 松皮菱 */
#define	PR_SHM_MASK_TYPE_UROKO			(8)		/* 鱗 */
#define	PR_SHM_MASK_TYPE_HIGAKI			(9)		/* 檜垣 */
#define	PR_SHm_MASK_TYPE_KIKKOU			(10)	/* 亀甲 */

	unsigned short	device_ctl_type;	/* 不正コピーガードＥＸの機器制御コード */
	unsigned char	trace_info;			/* セキュリティートレース情報形式 */
#define	PR_SHM_CG_FORMAT_USERID			(0)		/* ユーザーＩＤ */
#define	PR_SHM_CG_FORMAT_PAPERID		(1)		/* 紙ＩＤ */

	/* セキュリティートレース埋め込み */
	unsigned char	embed_mode;			/* 埋め込みモード */
#define	PR_SHM_SE_MODE_IMAGEQUALITY		(0)		/* 画質優先 */
#define	PR_SHM_SE_MODE_NORMAL			(1)		/* 普通 */
#define	PR_SHM_SE_MODE_TOLERANCE		(2)		/* 耐性優先 */

	/* 改ざん検知埋め込み */
	unsigned char	pattern_density;	/* 地紋濃度 */
#define	PR_SHM_FA_DENSITY_LIGHT			(0)		/* 薄い */
#define	PR_SHM_FA_DENSITY_MIDDLE		(1)		/* 中間 */
#define	PR_SHM_FA_DENSITY_DARK			(2)		/* 濃い */

	unsigned char	pattern_status;		/* pattern status*/
#define	PR_SHM_FA_STATUS_NONE			(0)		/* no pattern */
#define	PR_SHM_FA_STATUS_ADDED			(1)		/* use pattern */
	
	unsigned short	errorcorrection_level;		/* 誤り訂正レベル */

	/* リフレッシュコピー */
	unsigned char	refreshcopy;		/* 埋め込み */
#define	PR_SHM_RF_MODE_OFF				(0)		/* OFF */
#define	PR_SHM_RF_MODE_ON				(1)		/* ON */

	unsigned char	embedding_position;	/* 埋め込み位置 */
#define	PR_SHM_RF_POS_RIGHTTOP			(0)		/* 右上 */
#define	PR_SHM_RF_POS_LEFTTOP			(1)		/* 左上 */
#define	PR_SHM_RF_POS_RIGHTBOTTOM		(2)		/* 右下 */
#define	PR_SHM_RF_POS_LEFTBOTTOM		(3)		/* 左下 */

	unsigned long	embedding_pos_adj_vert;	/* 埋め込み位置調整（縦方向）(0.1mm単位) */
	unsigned long	embedding_pos_adj_horiz;/* 埋め込み位置調整（横方向）(0.1mm単位) */
	unsigned char	barcode_format;		/* バーコード形式 */
#define	PR_SHM_RF_FORMAT_QR				(0)		/* QR */
#define	PR_SHM_RF_FORMAT_PDF417			(1)		/* PDF417 */
#define	PR_SHM_RF_FORMAT_DATAMATRIX		(2)		/* DataMatrix */

	unsigned char	reserve[64];		/* 機能追加用 */
} prMarking_t;

/* --多機能折り-- */
typedef struct prMultifold {
	unsigned char	multifold_kind;		/* 多機能折り種類 */
#define	PR_SHM_MULTIFOLD_KIND_OFF				(0)	/* 多機能折りなし */
#define	PR_SHM_MULTIFOLD_KIND_HALF				(1)	/* ２つ折り（中折り） */
#define	PR_SHM_MULTIFOLD_KIND_THIRDS_INSIDE		(2)	/* 内３つ折り */
#define	PR_SHM_MULTIFOLD_KIND_THIRDS_OUTSIDE	(3)	/* 外３つ折り */
#define	PR_SHM_MULTIFOLD_KIND_QUART				(4)	/* 単純４つ折り */
#define	PR_SHM_MULTIFOLD_KIND_GATE				(5)	/* 観音折り */

	unsigned char	multifold_printposition;/* 印字面 */
#define	PR_SHM_MULTIFOLD_PRINTPOSITION_INSIDE	(0)	/* 内側印字 */
#define	PR_SHM_MULTIFOLD_PRINTPOSITION_OUTSIDE	(1)	/* 外側印字 */

	unsigned char	multifold_direction;	/* 開き（折り）方向 */
#define	PR_SHM_MULTIFOLD_DIRECTION_LEFT			(0)	/* 左開き */
#define	PR_SHM_MULTIFOLD_DIRECTION_BOTTOM		(1)	/* 下開き */
#define	PR_SHM_MULTIFOLD_DIRECTION_RIGHT		(2)	/* 右開き */
#define	PR_SHM_MULTIFOLD_DIRECTION_TOP			(3)	/* 上開き */

	unsigned char	multifold_sheets;		/* 重ね折り */
#define	PR_SHM_MULTIFOLD_SHEETS_OFF				(0)	/* 重ね折りしない */
#define	PR_SHM_MULTIFOLD_SHEETS_ON				(1)	/* 重ね折りする */

	unsigned char	reserve[16];			/* 機能追加用 */
} prMultifold_t;

/* --トリム指定-- */
typedef struct prTrim {
	unsigned char	trim_mode;		/* トリマーの裁断動作設定 */
#define	PR_SHM_TRIM_OFF					(0)		/* カットなし */
#define	PR_SHM_TRIM_SINGLECUT			(1)		/* 小口カット */

	unsigned long	side_edge_cut;	/* トリマーのカット量　小口方向設定(0.1mm単位) */
	unsigned char	reserve[16];	/* 機能追加用 */
} prTrim_t; 

typedef struct pr_page_info_shm {
#define	PR_MAX_PAGEPARAM_SHM			8
	unsigned long flag[PR_MAX_PAGEPARAM_SHM];
	
	/* declaration for flag[0] */
#define	PR_SHM_QTY							(1 <<  0)
#define	PR_SHM_LIMITLESS_EXIT				(1 <<  1)
#define	PR_SHM_OUTPUT_TRAY					(1 <<  2)
#define	PR_SHM_OUTMODE						(1 <<  3)
#define	PR_SHM_BINDING						(1 <<  4)
#define	PR_SHM_MARGIN						(1 <<  5)
#define	PR_SHM_COVER						(1 <<  6)
#define	PR_SHM_SLIP							(1 <<  7)
#define	PR_SHM_PARTITION					(1 <<  8)
#define	PR_SHM_SHIFTOFF						(1 <<  9)
#define	PR_SHM_FINISH						(1 << 10)
#define	PR_SHM_STAPLE						(1 << 11)
#define	PR_SHM_PUNCH						(1 << 12)
#define	PR_SHM_Z_FOLD						(1 << 13)
#define	PR_SHM_W_FOLD						(1 << 14)
#define	PR_SHM_TONERSAVE					(1 << 15)
#define	PR_SHM_PRIORITY_TRAY				(1 << 16)
#define	PR_SHM_UPSIDEDOWN					(1 << 17)
#define	PR_SHM_COLOR						(1 << 18)
#define	PR_SHM_MIXEDDIRROT					(1 << 19)
#define	PR_SHM_JAMRECOVERY					(1 << 20)
#define	PR_SHM_ACS							(1 << 21)
#define	PR_SHM_STAMP						(1 << 22)
#define	PR_SHM_DUPLEXMODE					(1 << 23)
#define	PR_SHM_WHITESUPPRESS				(1 << 24)
#define	PR_SHM_COLORSEPARATE				(1 << 25)
#define	PR_SHM_RING							(1 << 26)
#define	PR_SHM_PERFECT						(1 << 27)
#define	PR_SHM_MARKING						(1 << 28)
#define	PR_SHM_MULTIFOLD					(1 << 29)
#define	PR_SHM_TRIM							(1 << 30)
#define	PR_SHM_FACEUP						(1 << 31)
	
	unsigned short	qty;
	unsigned char	limitless_exit;
#define	PR_SHM_LIMITLESS_OFF				PR_LIMITLESS_OFF
#define	PR_SHM_LIMITLESS_ON					PR_LIMITLESS_ON

	unsigned short	output_tray;
	unsigned char	outmode;
#define	PR_SHM_OUT_IMGINFO					PR_OUT_IMGINFO
#define	PR_SHM_OUT_SINGLE					PR_OUT_SINGLE
#define	PR_SHM_OUT_DUPLEX					PR_OUT_DUPLEX

	unsigned char	binding;
#define	PR_SHM_BIND_LEFT					PR_BIND_LEFT
#define	PR_SHM_BIND_TOP						PR_BIND_TOP
#define	PR_SHM_BIND_RIGHT					PR_BIND_RIGHT
#define	PR_SHM_BIND_LEFTRIGHT				PR_BIND_LEFTRIGHT
#define	PR_SHM_BIND_TOPBOTTOM				PR_BIND_TOPBOTTOM

	prMargin_t		Margin;
	prCover_t		Cover;
	prSlip_t		Slip;
	prPartition_t	Partition;
	unsigned char	shiftoff;
#define	PR_SHM_SHIFT_ON						PR_SHIFT_ON
#define	PR_SHM_SHIFT_OFF					PR_SHIFT_OFF
	
	unsigned char	finish;
#define	PR_SHM_SORT							PR_SORT
#define	PR_SHM_STACK						PR_STACK
#define	PR_SHM_ROT_SORT						PR_ROT_SORT
#define	PR_SHM_SHIFT_SORT					PR_SHIFT_SORT
	
	unsigned char	staple;
#define	PR_SHM_STAPLE_OFF					PR_STAPLE_OFF
#define	PR_SHM_STAPLE_LEFT_TOP_HORIZ		PR_STAPLE_LEFT_TOP_HORIZ
#define	PR_SHM_STAPLE_LEFT_TOP_VERT			PR_STAPLE_LEFT_TOP_VERT
#define	PR_SHM_STAPLE_LEFT_TOP_SLANT		PR_STAPLE_LEFT_TOP_SLANT
#define	PR_SHM_STAPLE_RIGHT_TOP_HORIZ		PR_STAPLE_RIGHT_TOP_HORIZ
#define	PR_SHM_STAPLE_RIGHT_TOP_VERT		PR_STAPLE_RIGHT_TOP_VERT
#define	PR_SHM_STAPLE_RIGHT_TOP_SLANT		PR_STAPLE_RIGHT_TOP_SLANT
#define	PR_SHM_STAPLE_DOUBLE_LEFT			PR_STAPLE_DOUBLE_LEFT
#define	PR_SHM_STAPLE_DOUBLE_TOP			PR_STAPLE_DOUBLE_TOP
#define	PR_SHM_STAPLE_DOUBLE_RIGHT			PR_STAPLE_DOUBLE_RIGHT
#define	PR_SHM_STAPLE_BOOKLET				PR_STAPLE_BOOKLET
#define	PR_SHM_STAPLE_LEFT_TOP				PR_STAPLE_LEFT_TOP
#define	PR_SHM_STAPLE_RIGHT_TOP				PR_STAPLE_RIGHT_TOP

	prPunch_t		Punch;
	unsigned char	z_fold;
#define	PR_SHM_Z_FOLD_OFF					PR_Z_FOLD_OFF
#define	PR_SHM_Z_FOLD_RIGHT					PR_Z_FOLD_RIGHT
#define	PR_SHM_Z_FOLD_BOTTOM				PR_Z_FOLD_BOTTOM
#define	PR_SHM_Z_FOLD_LEFT					PR_Z_FOLD_LEFT

	prW_Fold_t		w_fold;
	unsigned char	tonersave;
#define	PR_SHM_TONERSAVE_OFF				PR_TONERSAVE_OFF
#define	PR_SHM_TONERSAVE_MODE1				PR_TONERSAVE_MODE1
#define	PR_SHM_TONERSAVE_MODE2				PR_TONERSAVE_MODE2
#define	PR_SHM_TONERSAVE_SOFT				(3)	/* soft tonersave */

	unsigned char	priority_tray;
	unsigned char	upsidedown;
#define	PR_SHM_UPSIDE_UP					(0)
#define	PR_SHM_UPSIDE_DOWN					(1)

	unsigned char	color_count;
#define	PR_SHM_COLORCOUNT_MONO				PR_COLORCOUNT_MONO
#define	PR_SHM_COLORCOUNT_RK				PR_COLORCOUNT_RK
#define	PR_SHM_COLORCOUNT_CMYK				PR_COLORCOUNT_CMYK
#define	PR_SHM_COLORCOUNT_XRGB				(5)
#define	PR_SHM_COLORCOUNT_2C				(6)

	unsigned char	mixeddirrot;		/* for RPCS only*/
#define	PR_SHM_MIXED_OFF					(0)
#define	PR_SHM_MIXED_LEFT					(1)
#define	PR_SHM_MIXED_RIGHT					(2)

	unsigned char	jamrecovery;
#define	PR_SHM_JAMRECOVERY_OFF				PR_JAMRECOVERY_OFF
#define	PR_SHM_JAMRECOVERY_ON				PR_JAMRECOVERY_ON

	unsigned char	acs;
#define	PR_SHM_ACS_OFF						(0)	/* no ACS */
#define	PR_SHM_ACS_ON						(1)	/* do ACS*/

	unsigned char	stamp;
#define	PR_SHM_STAMP_OFF					(0)
#define	PR_SHM_STAMP_ON						(1)

	unsigned char	duplexmode;
#define	PR_SHM_DUPLEXMODE_OFF				(0)
#define	PR_SHM_DUPLEXMODE_ON				(1)

	unsigned char	white_suppress;
	unsigned char	color_separate;
	prRingBind_t	Ringbind;
	prPerfectBind_t	Perfectbind;
	prMarking_t		Marking;
	prMultifold_t	Multifold;
	prTrim_t		Trim;
	unsigned char	face_up;
#define	PR_SHM_FACEUP_OFF					(0)
#define	PR_SHM_FACEUP_ON					(1)

	/* declaration for flag[1] */
#define PR_SHM_SADDLE_FOLD	(1 << 2)

	unsigned char	saddle_fold;
#define PR_SHM_SADDLE_FOLD_OFF			(0)
#define PR_SHM_SADDLE_FOLD_INSIDE		(1)
#define PR_SHM_SADDLE_FOLD_OUTSIDE		(2)
#define PR_SHM_SADDLE_FOLD_SHEETS		(3)

} pr_page_info_shm_t;

typedef struct pr_gradation
{
	long x;		/* 原点のX座標 */
	long y;		/* 原点のY座標 */
	long xgradient;	/* X軸変化量の基準点 */
	long ygradient;	/* Y軸変化量の基準点 */
	float *color;	/* 色情報の先頭アドレス */
} pr_gradation_t;

/* ジョブ分割 */
#define	PR_DIVIDE_SUCCESS	(0)
#define	PR_JOBCLOSE_ERROR	(1)
#define	PR_UJOBSTART_ERROR	(2)
#define	PR_SETPARAM_ERROR	(3)
#define	PR_JOBSTART_ERROR	(4)
#define	PR_CANCEL		(-1)

typedef struct pr_ujob_info
{

	unsigned long flag;
	/* flag */
#define	PR_UPARAM_DATE			(1 << 0)
#define	PR_UPARAM_TIME			(1 << 1)
#define	PR_UPARAM_TRACKID			(1 << 2)
#define	PR_UPARAM_USERCODE			(1 << 3)
#define	PR_UPARAM_USERID			(1 << 4)
#define	PR_UPARAM_JOBID			(1 << 5)
#define	PR_UPARAM_JOBPASSWORD		(1 << 6)
#define	PR_UPARAM_DISPCHARSET		(1 << 7)
#define	PR_UPARAM_HOSTCHARSET		(1 << 8)
#define	PR_UPARAM_HOSTLOGINNAME		(1 << 9)
#define	PR_UPARAM_HOSTNAME			(1 << 10)
#define	PR_UPARAM_HOSTPORTNAME		(1 << 11)
#define	PR_UPARAM_HOSTPRINTERNAME		(1 << 12)
#define	PR_UPARAM_PROOFJOB			(1 << 13)
#define	PR_UPARAM_SECUREJOB			(1 << 14)
#define	PR_UPARAM_JOBNAME			(1 << 15)
#define	PR_UPARAM_OWNERID			(1 << 16)
#define	PR_UPARAM_PRINTINFO			(1 << 17)
#define	PR_UPARAM_AUTHUSERNAME		(1 << 18)
#define	PR_UPARAM_AUTHPASSWORD		(1 << 19)
#define	PR_UPARAM_AUTHENCRYPTMETHOD		(1 << 20)
#define	PR_UPARAM_AUTHENCRYPTSETTING	(1 << 21)
#define	PR_UPARAM_JOBPASSWORD_EXT		(1 << 22)
#define	PR_UPARAM_PAUSEDJOB			(1 << 23)
#define	PR_UPARAM_FORMJOB			(1 << 24)
#define	PR_UPARAM_AUTHUSERNAMECHARSET	(1 << 25)
#define	PR_UPARAM_AUTHPASSWORDCHARSET	(1 << 26)
#define	PR_UPARAM_NDISPCHARSET		(1 << 27)
#define	PR_UPARAM_NHOSTCHARSET		(1 << 28)
#define	PR_UPARAM_BILLINGCODE		(1 << 29)
#define	PR_UPARAM_REUSABLESTOREDJOB		(1 << 30)
#define	PR_UPARAM_PRINTAPPOINTEDTIME	(1 << 30)
#define	PR_UPARAM_EXT2				(1 << 31)

	unsigned long flag2;
	/* flag2 */
#define	PR_UPARAM_DRIVERKINDINFO	(1 << 0)
#define	PR_UPARAM_FOLDERNUMBER		(1 << 1)
#define	PR_UPARAM_FOLDERPASSWORD	(1 << 2)
#define	PR_UPARAM_EXT3				(1 << 31)

	struct
	{
		/* max length */
#define	PR_MAX_UPARAM_DATE_LEN			(10+1)
#define	PR_MAX_UPARAM_TIME_LEN			(8+1)
#define	PR_MAX_UPARAM_TRACKID_LEN			(20+1)
#define	PR_MAX_UPARAM_USERCODE_LEN		(8+1)
#define	PR_MAX_UPARAM_USERID_LEN			(8+1)
#define	PR_MAX_UPARAM_JOBID_LEN			(20+1)
#define	PR_MAX_UPARAM_JOBPASSWORD_LEN		(4+1)
#define	PR_MAX_UPARAM_DISPCHARSET_LEN		(63+1)
#define	PR_MAX_UPARAM_HOSTCHARSET_LEN		(63+1)
#define	PR_MAX_UPARAM_HOSTLOGINNAME_LEN		(20+1)
#define	PR_MAX_UPARAM_HOSTNAME_LEN		(63+1)
#define	PR_MAX_UPARAM_HOSTPORTNAME_LEN		(64+1)
#define	PR_MAX_UPARAM_HOSTPRINTERNAME_LEN	(64+1)
#define	PR_MAX_UPARAM_JOBNAME_LEN			(232+1)
#define	PR_MAX_UPARAM_OWNERID_LEN			(20+1)
#define	PR_MAX_UPARAM_PRINTINFO_LEN		(230+1)
#define	PR_MAX_UPARAM_AUTHUSERNAME_LEN		(217+1)
#define	PR_MAX_UPARAM_AUTHPASSWORD_LEN		(217+1)
#define	PR_MAX_UPARAM_JOBPASSWORD_EXT_LEN	(8+1)
#define	PR_MAX_UPARAM_BILLINGCODE_LEN		(32+2)
#define	PR_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN	(5+1)
#define	PR_MAX_UPARAM_FOLDERPASSWORD_LEN	(8+1)

		unsigned char date[PR_MAX_UPARAM_DATE_LEN];
		unsigned char time[PR_MAX_UPARAM_TIME_LEN];
		unsigned char trackid[PR_MAX_UPARAM_TRACKID_LEN];
		unsigned char usercode[PR_MAX_UPARAM_USERCODE_LEN];
		unsigned char billingcode[PR_MAX_UPARAM_BILLINGCODE_LEN];
		unsigned char userid[PR_MAX_UPARAM_USERID_LEN];
		unsigned char jobid[PR_MAX_UPARAM_JOBID_LEN];
		unsigned char jobpassword[PR_MAX_UPARAM_JOBPASSWORD_LEN];
		unsigned char dispcharset[PR_MAX_UPARAM_DISPCHARSET_LEN];
		unsigned char hostcharset[PR_MAX_UPARAM_HOSTCHARSET_LEN];
		unsigned char hostloginname[PR_MAX_UPARAM_HOSTLOGINNAME_LEN];
		unsigned char hostname[PR_MAX_UPARAM_HOSTNAME_LEN];
		unsigned char hostportname[PR_MAX_UPARAM_HOSTPORTNAME_LEN];
		unsigned char hostprintername[PR_MAX_UPARAM_HOSTPRINTERNAME_LEN];
		unsigned char jobname[PR_MAX_UPARAM_JOBNAME_LEN];
		unsigned char ownerid[PR_MAX_UPARAM_OWNERID_LEN];
		unsigned char printinfo[PR_MAX_UPARAM_PRINTINFO_LEN];
		unsigned char authusername[PR_MAX_UPARAM_AUTHUSERNAME_LEN];
		unsigned char authpassword[PR_MAX_UPARAM_AUTHPASSWORD_LEN];
		int authencryptmethod;
		int authencryptsetting;
		unsigned char jobpassword_ext[PR_MAX_UPARAM_JOBPASSWORD_EXT_LEN];
		short authusernamecharset;
		short authpasswordcharset;
		short ndispcharset;
		short nhostcharset;
		unsigned char printappointedtime[PR_MAX_UPARAM_PRINTAPPOINTEDTIME_LEN];
		int driverkindinfo;
		/* driver kind info */
#define	PR_UPARAM_DRIVERKINDINFO_INBOX			(1)
#define	PR_UPARAM_DRIVERKINDINFO_PCL6			(2)
#define	PR_UPARAM_DRIVERKINDINFO_PCL6UD			(3)
#define	PR_UPARAM_DRIVERKINDINFO_PCL6UDGENERIC	(4)
#define	PR_UPARAM_DRIVERKINDINFO_PS				(5)
#define	PR_UPARAM_DRIVERKINDINFO_PSUD			(6)
#define	PR_UPARAM_DRIVERKINDINFO_PSUDGENERIC	(7)
#define	PR_UPARAM_DRIVERKINDINFO_RPCSBASIC		(8)
#define	PR_UPARAM_DRIVERKINDINFO_RPCSXPS		(9)
#define	PR_UPARAM_DRIVERKINDINFO_RPCS			(10)

		unsigned short foldernumber;
		unsigned char folderpassword[PR_MAX_UPARAM_FOLDERPASSWORD_LEN];
	} up;
} pr_ujob_info_t;

#define	PR_UJOB_UNDEF	(0)	/* コマンドで明示的に定義されていない場合 */
#define	PR_UJOB_PJL	(1)	/* PJLのJOBコマンドで定義されたジョブの場合 */
#define	PR_UJOB_RPDL	(2)	/* RPDLのジョブコマンドにて定義されたジョブの場合 */
#define	PR_UJOB_HEXDUMP	(11)	/* HEXDUMP */

#define	PR_MAX_UJOB_ATTR_NAME_LEN	80

typedef struct pr_ujob_attr
{
	unsigned long flag;
#define	PR_UJOB_ATTR_NAME	(1 << 0)

	char name[PR_MAX_UJOB_ATTR_NAME_LEN + 1];	/* PJLのJOB/EOJコマンドで通知されるNAME */

} pr_ujob_attr_t;

typedef struct pr_dividejob_info
{
	int njobid;	/* ネットジョブID。参照。 */
	pr_ujob_info_t *ujob_info;	/* ユーザージョブパラメータ構造体 */
	int kind;		/* ジョブの種類 */
	pr_ujob_attr_t *ujob_attr;	/* ユーザージョブアトリビュート構造体 */
} pr_dividejob_info_t;

/*
 *	pr_setmargin()用
 *	余白シフト方法
 */
#define	PR_MARGIN_MASK		0x03
#define	PR_MARGIN_MASK_TB	0x01	/* 上下(抜き) */
#define	PR_MARGIN_MASK_LR	0x02	/* 左右(抜き) */

/* 出力先 */
#define	PR_OUT_FRAME	0	/* フレームメモリ(デフォルト) */
#define	PR_OUT_SPOOLER	1	/* スプーラ */
#define	PR_OUT_FILE	2	/* ファイル */
#define	PR_OUT_MEMORY	3	/* メモリ */
#define	PR_OUT_RASTER	4	/* ファイル(Raster形式) */

/* エラー情報 */
#define	PR_ERRINFO_RENDERINIT    	0x1001	  /* render_init() error */
#define	PR_ERRINFO_RENDERINITPAGE	0x1002	  /* render_init_page() error */
#define	PR_ERRINFO_GEINIT		0x1003	  /* ge_initialize() error */
#define	PR_ERRINFO_INITGRAPHICS 	0x1004	  /* init_graphics() error */
#define	PR_ERRINFO_POSITION     	0x2001	  /* illegal command position */
#define	PR_ERRINFO_BANDLINES    	0x3005	  /* livalid band lines */
#define	PR_ERRINFO_GMALLOC		0x4011	  /* gmAlloc() error */
#define	PR_ERRINFO_FMALLOC		0x4021	  /* fmAlloc() error */
#define	PR_ERRINFO_OMALLOC		0x4031	  /* omAlloc() error */
#define	PR_ERRINFO_BRUSHSIZE    	0x4041	  /* Brush area not allocated */
#define	PR_ERRINFO_SPOOLSIZE    	0x4042	  /* Spool area not allocated */
#define	PR_ERRINFO_OBJECTSIZE   	0x4043	  /* Object area not allocated */
#define	PR_ERRINFO_GRAPHICSIZE  	0x4044	  /* Graphic area too small */
#define	PR_ERRINFO_FONTSIZE     	0x4045	  /* Font area not allocated */
#define	PR_ERRINFO_FRAMECREATE  	0x7001	  /* FrameCreate */
#define	PR_ERRINFO_FRAMEPRINT   	0x7002	  /* FramePrint */
#define	PR_ERRINFO_FRAMECLOSE   	0x7003	  /* FrameClose */
#define	PR_ERRINFO_GETBAND		0x7004	  /* GetBand */
#define	PR_ERRINFO_FLUSHBAND    	0x7005	  /* FlushBand */

/*
 * pr_job_info_tのメンバ情報
 */
/* 設定するパラメータ */
#define	PR_PARAM_QTY 			(1 <<  1)	/* 印刷部数 */
#define	PR_PARAM_LIMITLESS_EXIT		(1 <<  2)	/* リミットレス排紙 */
#define	PR_PARAM_OUTPUT_TRAY		(1 <<  3)	/* 排紙トレイ */
#define	PR_PARAM_OUTMODE		(1 <<  4)	/* 印刷モード */
#define	PR_PARAM_BINDING		(1 <<  5)	/* 縦とじ方向 */
#define	PR_PARAM_MARGIN1V		(1 <<  6)	/* 縦とじ代(両面第１面) */
#define	PR_PARAM_MARGIN1H		(1 <<  7)	/* 横とじ代(両面第１面) */
#define	PR_PARAM_MARGIN2V		(1 <<  8)	/* 縦とじ代(両面第２面) */
#define	PR_PARAM_MARGIN2H		(1 <<  9)	/* 横とじ代(両面第２面) */
#define	PR_PARAM_COVER			(1 << 10)	/* 表紙モード */
#define	PR_PARAM_COVERPRINT		(1 << 11)	/* 表紙画像印刷面 */
#define	PR_PARAM_SLIP			(1 << 12)	/* 合紙モード */
#define	PR_PARAM_SHIFTOFF		(1 << 13)	/* ジョブ単位のシフト */
#define	PR_PARAM_FINISH			(1 << 14)	/* 仕分け指定 */
#define	PR_PARAM_STAPLE			(1 << 15)	/* ステープル */
#define	PR_PARAM_PUNCH			(1 << 16)	/* パンチ */
#define	PR_PARAM_COVERTRAY		(1 << 17)	/* 表紙トレイ */
#define	PR_PARAM_SLIPTRAY		(1 << 18)	/* 合紙トレイ */
#define	PR_PARAM_TONERSAVE		(1 << 23)	/* トナーセーブ */
#define	PR_PARAM_PRIORITY_TRAY		(1 << 24)	/* 優先給紙トレイ */
#define	PR_PARAM_UPSIDEDOWN		(1 << 25)	/* 180度回転 */
#define	PR_PARAM_COLORCOUNT		(1 << 26)	/* 色数 */
#define	PR_PARAM_DOCBODYTRAY		(1 << 27)	/* 未使用 */
#define	PR_PARAM_MIXEDDIRROT		(1 << 28)	/* 用紙方向混在時の回転方向 */
#define	PR_PARAM_1STPAGEORDER		(1 << 29)	/* 未使用 */
#define	PR_PARAM_JAMRECOVERY		(1 << 30)	/* ジャム・リカバリー */
#define	PR_PARAM_ACS			(1 << 31)	/* ACS */

#define	PR_PARAM_PAGE_SHIFT		(1 << 20)	/* ページシフト(PR独自定義) */
#define PR_PARAM_ECO_COLOR		(1 << 21)	/* エコノミーカラー(PR独自定義) */

/* 印刷モード */
#define	PR_OUT_IMGINFO	(0)		/* 画像属性情報の指定に従う*/
#define	PR_OUT_SINGLE	(1)		/* 片面印刷 */
#define	PR_OUT_DUPLEX	(2)		/* 両面印刷 */
/* 綴じ方向 */
#define	PR_BIND_LEFT		(0)		/* 左綴じ */
#define	PR_BIND_TOP		(1)		/* 上綴じ */
#define	PR_BIND_RIGHT		(2)		/* 右綴じ */
#define	PR_BIND_BOTTOM		(3)		/* 下綴じ */
#define	PR_BIND_LEFTRIGHT	(4)		/* 左右綴じ */
#define	PR_BIND_TOPBOTTOM	(5)		/* 上下綴じ */

#define PR_BIND_SUCCESS		(0)		/* 成功 */
#define PR_BIND_BUSY		(-1)		/* ビジー */
#define PR_BIND_FAILURE		(-2)		/* 失敗 */
/* 仕分け指定 */
#define	PR_SORT			(1)		/* ソート */
#define	PR_STACK		(2)		/* スタック */
#define	PR_ROT_SORT		(3)		/* 回転ソート */
#define	PR_SHIFT_SORT		(4)		/* シフトソート */
/* 色数 */
#define PR_COLORCOUNT_MONO	(1)	/* １色(単色プレーン) */
#define PR_COLORCOUNT_RK	(2)	/* 赤黒 */
#define PR_COLORCOUNT_CMYK	(4)	/* ４色(ＣＭＹＫ) */
#define PR_COLORCOUNT_RGB_PIXEL_ORDER	(8)	/* ＸＲＧＢ点順次 */
#define PR_SLIP_OFF		(0x00)	/* 合紙しない */
#define PR_SLIP_ON		(0x01)	/* 合紙する */
#define PR_SLIP_PRINT		(0x11)	/* 合紙しない */

/*
 * pr_page_info_tのメンバ情報
 */
/* 給紙トレイ */
#define		PR_TRAY_MAN		(0)		/* 手差し給紙トレイ */
#define		PR_TRAY_1		(1)		/* 第１給紙トレイ */
#define		PR_TRAY_2		(2)		/* 第２給紙トレイ */
#define		PR_TRAY_3		(3)		/* 第３給紙トレイ */
#define		PR_TRAY_4		(4)		/* 第４給紙トレイ */
#define		PR_TRAY_5		(5)		/* 第５給紙トレイ */
#define		PR_TRAY_6		(6)		/* 第６給紙トレイ */
#define		PR_TRAY_7		(7)		/* 第７給紙トレイ */
#define		PR_TRAY_LCT		(0x0A)		/* 大量給紙トレイ */
#define		PR_TRAY_AUTO		(0x0F)		/* 自動用紙選択 */
#define		PR_TRAY_INSERTER	(0x10)		/* 合紙挿入ユニット */
#define		PR_TRAY_INSERTER2	(0x11)		/* 合紙挿入ユニット（２段） */
/* 紙種 */
#define		PR_PAPER_AUTO		(0x00)          /* 紙種指定なし */
#define		PR_PAPER_NORMAL		(0x01)          /* 普通紙 */
#define		PR_PAPER_RECYCLE	(0x02)          /* 再生紙 */
#define		PR_PAPER_SPECIAL	(0x03)          /* 特殊紙 */
#define		PR_PAPER_TRACING	(0x04)          /* トレーシング紙 */
#define		PR_PAPER_OHP		(0x05)          /* OHP */
#define		PR_PAPER_LABEL		(0x06)          /* ラベル紙 */
#define		PR_PAPER_BOND		(0x07)          /* ボンド紙 */
#define		PR_PAPER_CARDSTOCK	(0x08)          /* カードストック */
#define		PR_PAPER_CARDBOARD	(0x09)          /* 厚紙 */
#define		PR_PAPER_PREPRINT	(0x0A)          /* 印刷済み紙 */
#define		PR_PAPER_LETTER_HEAD	(0x0B)          /* レターヘッド紙 */
#define		PR_PAPER_LETTER_PUNCH	(0x0C)
#define		PR_PAPER_TAB		(0x0D)          /* タブ紙 */
#define		PR_PAPER_COLOR		(0x0E)          /* 色紙 */
#define		PR_PAPER_NORMAL2ND	(0x0F)          /* 普通紙(裏面) */
#define		PR_PAPER_CARDBOARD2ND	(0x10)          /* 厚紙(裏面) */
#define		PR_PAPER_THIN		(0x11)          /* 薄紙 */
#define		PR_PAPER_GLOSSY        	(0x12)          /* 光沢紙 */
#define		PR_PAPER_USED          	(0x13)          /* 裏紙（使用済み） */
#define		PR_PAPER_POSTCARD      	(0x14)          /* ハガキ */
#define		PR_PAPER_POSTCARD2ND   	(0x15)          /* ハガキ(裏面) */
#define		PR_PAPER_CARDBOARD2		(0x16)
#define		PR_PAPER_FILM		(0x17)
#define		PR_PAPER_INKPOST		(0x18)
#define		PR_PAPER_HG_NORMAL		(0x19)
#define		PR_PAPER_ENVELOPE		(0x1A)
#define		PR_PAPER_CARDBOARD3		(0x1B)
#define		PR_PAPER_SPECIAL2		(0x1C)
#define		PR_PAPER_SPECIAL3		(0x1D)
#define		PR_PAPER_MIDDLETHICK	(0x1E)
#define		PR_PAPER_COATED		(0x1F)
#define		PR_PAPER_CARDBOARD2REV	(0x20)
#define		PR_PAPER_CARDBOARD3REV	(0x21)
#define		PR_PAPER_NORMAL2		(0x22)
#define		PR_PAPER_THICKGLOSSY	(0x23)
#define		PR_PAPER_SPECIAL4		(0x24)
#define		PR_PAPER_SPECIAL5		(0x25)
#define		PR_PAPER_SPECIAL6		(0x26)
#define		PR_PAPER_USER_DEF1		(0x30)
#define		PR_PAPER_USER_DEF2		(0x31)
#define		PR_PAPER_USER_DEF3		(0x32)
#define		PR_PAPER_USER_DEF4		(0x33)
#define		PR_PAPER_USER_DEF5		(0x34)
#define		PR_PAPER_USER_DEF6		(0x35)
#define		PR_PAPER_USER_DEF7		(0x36)
#define		PR_PAPER_USER_DEF8		(0x37)
#define		PR_PAPER_USER_DEF0		(0x38)
#define		PR_PAPER_COLOR1        	(0x40)          /* 色紙１ */
#define		PR_PAPER_COLOR2        	(0x41)          /* 色紙２ */
#define		PR_PAPER_COLOR_YELLOW	(0x51)          /* 黄 */
#define		PR_PAPER_COLOR_GREEN	(0x52)          /* 緑 */
#define		PR_PAPER_COLOR_BLUE	(0x53)          /* 青 */
#define		PR_PAPER_COLOR_PURPLE	(0x54)          /* 紫 */
#define		PR_PAPER_COLOR_IVORY	(0x55)          /* アイボリー */
#define		PR_PAPER_COLOR_ORANGE	(0x56)          /* 橙 */
#define		PR_PAPER_COLOR_PINK	(0x57)          /* 桃 */
#define		PR_PAPER_COLOR_RED	(0x58)          /* 赤 */
#define		PR_PAPER_COLOR_GRAY	(0x59)          /* 灰 */
#define		PR_PAPER_GLOSSY_COATED		(0x60)	/* glossy coated */
#define		PR_PAPER_THICK_GLOSSY_COATED	(0x61)	/* thick glossy coated */
#define		PR_PAPER_MAT_COATED		(0x62)	/* matt coated */
#define		PR_PAPER_THICK_MAT_COATED	(0x63)	/* thick matt coated */
#define		PR_PAPER_WATER_PROOF		(0x64)	/* waterproof */
#define		PR_PAPER_CARDBOARD4		(0x65)	/* cardboard 4 */
#define		PR_PAPER_CARDBOARD4REV		(0x66)	/* cardboard 4 (reverse) */
#define		PR_PAPER_COATED_HIGH_GLOSSY	(0x67)	/* high glossy coated */
#define		PR_PAPER_SEMIGLOSSY		(0x68)
#define		PR_PAPER_INKJETPLAIN	(0x69)
#define		PR_PAPER_MATFILM		(0x6C)
#define		PR_PAPER_CADCOATED		(0x6D)
#define		PR_PAPER_NONE			(0x80)
#define		PR_PAPER_USER_DEF9			(0x81)	/* ユーザ指定９(IMSS) */
#define		PR_PAPER_USER_DEF10			(0x82)	/* ユーザ指定１０(IMSS) */
#define		PR_PAPER_USER_DEF11			(0x83)	/* ユーザ指定１１(IMSS) */
#define		PR_PAPER_USER_DEF12			(0x84)	/* ユーザ指定１２(IMSS) */
#define		PR_PAPER_USER_DEF13			(0x85)	/* ユーザ指定１３(IMSS) */
#define		PR_PAPER_USER_DEF14			(0x86)	/* ユーザ指定１４(IMSS) */
#define		PR_PAPER_USER_DEF15			(0x87)	/* ユーザ指定１５(IMSS) */
#define		PR_PAPER_USER_DEF16			(0x88)	/* ユーザ指定１６(IMSS) */
#define		PR_PAPER_USER_DEF17			(0x89)	/* ユーザ指定１７(IMSS) */
#define		PR_PAPER_USER_DEF18			(0x8A)	/* ユーザ指定１８(IMSS) */
#define		PR_PAPER_USER_DEF19			(0x8B)	/* ユーザ指定１９(IMSS) */
#define		PR_PAPER_USER_DEF20			(0x8C)	/* ユーザ指定２０(IMSS) */
#define		PR_PAPER_USER_DEF21			(0x8D)	/* ユーザ指定２１(IMSS) */
#define		PR_PAPER_USER_DEF22			(0x8E)	/* ユーザ指定２２(IMSS) */
#define		PR_PAPER_USER_DEF23			(0x8F)	/* ユーザ指定２３(IMSS) */
#define		PR_PAPER_USER_DEF24			(0x90)	/* ユーザ指定２４(IMSS) */
#define		PR_PAPER_USER_DEF25			(0x91)	/* ユーザ指定２５(IMSS) */
#define		PR_PAPER_USER_DEF26			(0x92)	/* ユーザ指定２６(IMSS) */
#define		PR_PAPER_USER_DEF27			(0x93)	/* ユーザ指定２７(IMSS) */
#define		PR_PAPER_USER_DEF28			(0x94)	/* ユーザ指定２８(IMSS) */
#define		PR_PAPER_USER_DEF29			(0x95)	/* ユーザ指定２９(IMSS) */
#define		PR_PAPER_USER_DEF30			(0x96)	/* ユーザ指定３０(IMSS) */
#define		PR_PAPER_USER_DEF31			(0x97)	/* ユーザ指定３１(IMSS) */
#define		PR_PAPER_USER_DEF32			(0x98)	/* ユーザ指定３２(IMSS) */
#define		PR_PAPER_USER_DEF33			(0x99)	/* ユーザ指定３３(IMSS) */
#define		PR_PAPER_USER_DEF34			(0x9A)	/* ユーザ指定３４(IMSS) */
#define		PR_PAPER_USER_DEF35			(0x9B)	/* ユーザ指定３５(IMSS) */
#define		PR_PAPER_USER_DEF36			(0x9C)	/* ユーザ指定３６(IMSS) */
#define		PR_PAPER_USER_DEF37			(0x9D)	/* ユーザ指定３７(IMSS) */
#define		PR_PAPER_USER_DEF38			(0x9E)	/* ユーザ指定３８(IMSS) */
#define		PR_PAPER_USER_DEF39			(0x9F)	/* ユーザ指定３９(IMSS) */
#define		PR_PAPER_USER_DEF40			(0xA0)	/* ユーザ指定４０(IMSS) */
#define		PR_PAPER_USER_DEF41			(0xA1)	/* ユーザ指定４１(IMSS) */
#define		PR_PAPER_USER_DEF42			(0xA2)	/* ユーザ指定４２(IMSS) */
#define		PR_PAPER_USER_DEF43			(0xA3)	/* ユーザ指定４３(IMSS) */
#define		PR_PAPER_USER_DEF44			(0xA4)	/* ユーザ指定４４(IMSS) */
#define		PR_PAPER_USER_DEF45			(0xA5)	/* ユーザ指定４５(IMSS) */
#define		PR_PAPER_USER_DEF46			(0xA6)	/* ユーザ指定４６(IMSS) */
#define		PR_PAPER_USER_DEF47			(0xA7)	/* ユーザ指定４７(IMSS) */
#define		PR_PAPER_USER_DEF48			(0xA8)	/* ユーザ指定４８(IMSS) */
#define		PR_PAPER_USER_DEF49			(0xA9)	/* ユーザ指定４９(IMSS) */
#define		PR_PAPER_USER_DEF50			(0xAA)	/* ユーザ指定５０(IMSS) */
#define		PR_PAPER_USER_DEF51			(0xAB)	/* ユーザ指定５１(IMSS) */
#define		PR_PAPER_USER_DEF52			(0xAC)	/* ユーザ指定５２(IMSS) */
#define		PR_PAPER_USER_DEF53			(0xAD)	/* ユーザ指定５３(IMSS) */
#define		PR_PAPER_USER_DEF54			(0xAE)	/* ユーザ指定５４(IMSS) */
#define		PR_PAPER_USER_DEF55			(0xAF)	/* ユーザ指定５５(IMSS) */
#define		PR_PAPER_USER_DEF56			(0xB0)	/* ユーザ指定５６(IMSS) */
#define		PR_PAPER_USER_DEF57			(0xB1)	/* ユーザ指定５７(IMSS) */
#define		PR_PAPER_USER_DEF58			(0xB2)	/* ユーザ指定５８(IMSS) */
#define		PR_PAPER_USER_DEF59			(0xB3)	/* ユーザ指定５９(IMSS) */
#define		PR_PAPER_USER_DEF60			(0xB4)	/* ユーザ指定６０(IMSS) */
#define		PR_PAPER_USER_DEF61			(0xB5)	/* ユーザ指定６１(IMSS) */
#define		PR_PAPER_USER_DEF62			(0xB6)	/* ユーザ指定６２(IMSS) */
#define		PR_PAPER_USER_DEF63			(0xB7)	/* ユーザ指定６３(IMSS) */
#define		PR_PAPER_USER_DEF64			(0xB8)	/* ユーザ指定６４(IMSS) */
#define		PR_PAPER_USER_DEF65			(0xB9)	/* ユーザ指定６５(IMSS) */
#define		PR_PAPER_USER_DEF66			(0xBA)	/* ユーザ指定６６(IMSS) */
#define		PR_PAPER_USER_DEF67			(0xBB)	/* ユーザ指定６７(IMSS) */
#define		PR_PAPER_USER_DEF68			(0xBC)	/* ユーザ指定６８(IMSS) */
#define		PR_PAPER_USER_DEF69			(0xBD)	/* ユーザ指定６９(IMSS) */
#define		PR_PAPER_USER_DEF70			(0xBE)	/* ユーザ指定７０(IMSS) */
#define		PR_PAPER_USER_DEF71			(0xBF)	/* ユーザ指定７１(IMSS) */
#define		PR_PAPER_USER_DEF72			(0xC0)	/* ユーザ指定７２(IMSS) */
#define		PR_PAPER_USER_DEF73			(0xC1)	/* ユーザ指定７３(IMSS) */
#define		PR_PAPER_USER_DEF74			(0xC2)	/* ユーザ指定７４(IMSS) */
#define		PR_PAPER_USER_DEF75			(0xC3)	/* ユーザ指定７５(IMSS) */
#define		PR_PAPER_USER_DEF76			(0xC4)	/* ユーザ指定７６(IMSS) */
#define		PR_PAPER_USER_DEF77			(0xC5)	/* ユーザ指定７７(IMSS) */
#define		PR_PAPER_USER_DEF78			(0xC6)	/* ユーザ指定７８(IMSS) */
#define		PR_PAPER_USER_DEF79			(0xC7)	/* ユーザ指定７９(IMSS) */
#define		PR_PAPER_USER_DEF80			(0xC8)	/* ユーザ指定８０(IMSS) */
#define		PR_PAPER_USER_DEF81			(0xC9)	/* ユーザ指定８１(IMSS) */
#define		PR_PAPER_USER_DEF82			(0xCA)	/* ユーザ指定８２(IMSS) */
#define		PR_PAPER_USER_DEF83			(0xCB)	/* ユーザ指定８３(IMSS) */
#define		PR_PAPER_USER_DEF84			(0xCC)	/* ユーザ指定８４(IMSS) */
#define		PR_PAPER_USER_DEF85			(0xCD)	/* ユーザ指定８５(IMSS) */
#define		PR_PAPER_USER_DEF86			(0xCE)	/* ユーザ指定８６(IMSS) */
#define		PR_PAPER_USER_DEF87			(0xCF)	/* ユーザ指定８７(IMSS) */
#define		PR_PAPER_USER_DEF88			(0xD0)	/* ユーザ指定８８(IMSS) */
#define		PR_PAPER_USER_DEF89			(0xD1)	/* ユーザ指定８９(IMSS) */
#define		PR_PAPER_USER_DEF90			(0xD2)	/* ユーザ指定９０(IMSS) */
#define		PR_PAPER_USER_DEF91			(0xD3)	/* ユーザ指定９１(IMSS) */
#define		PR_PAPER_USER_DEF92			(0xD4)	/* ユーザ指定９２(IMSS) */
#define		PR_PAPER_USER_DEF93			(0xD5)	/* ユーザ指定９３(IMSS) */
#define		PR_PAPER_USER_DEF94			(0xD6)	/* ユーザ指定９４(IMSS) */
#define		PR_PAPER_USER_DEF95			(0xD7)	/* ユーザ指定９５(IMSS) */
#define		PR_PAPER_USER_DEF96			(0xD8)	/* ユーザ指定９６(IMSS) */
#define		PR_PAPER_USER_DEF97			(0xD9)	/* ユーザ指定９７(IMSS) */
#define		PR_PAPER_USER_DEF98			(0xDA)	/* ユーザ指定９８(IMSS) */
#define		PR_PAPER_USER_DEF99			(0xDB)	/* ユーザ指定９９(IMSS) */
#define		PR_PAPER_USER_DEF100		(0xDC)	/* ユーザ指定１００(IMSS) */


/*
 * 印刷モード
 */
#define PR_PLOT_NORMAL   (0)     /* 通常印刷 */
#define PR_PLOT_PROOF    (2)     /* 試し印刷 */
#define PR_PLOT_SECURE   (3)     /* 機密印刷 */
#define PR_PLOT_STORED   (4)     /* 保存文書 ドキュメントボックス */
#define PR_PLOT_PAUSE    (5)     /* 保留印刷 */
#define PR_PLOT_KEEP     (6)     /* 保存文書印刷 */

#define PR_ECO_COLOR_NONE		(0)		/* エコノミーカラーモード指定なし */
#define PR_ECO_COLOR_PRT		(1)		/* エコノミーカラーモード指定あり */

/*
 * pr_page_info_s_tのメンバ情報
 */
/* 設定するパラメータ指定(bit) */
#define PR_OUTPUT_TRAY		(1 << 0)	/* output_tray が有効 */
#define PR_LIMITLESS_EXIT	(1 << 1)	/* limitless_exit が有効 */
#define PR_STAPLE		(1 << 2)	/* staple が有効 */
#define PR_PUNCH		(1 << 3)	/* punch が有効 */
#define PR_Z_FOLD		(1 << 4)	/* z_fold が有効 */
#define PR_TONERSAVE		(1 << 5)	/* tonersave が有効 */
#define PR_JAMRECOVERY		(1 << 6)	/* jamrecovery が有効 */
#define PR_FACE			(1 << 7)	/* face が有効 */
#define PR_PAPER_COUNT		(1 << 8)	/* paper_count が有効 */
#define PR_SHIFT		(1 << 9)	/* shift が有効 */
#define PR_COUNTOFF		(1 << 10)	/* パラメータ count_off が有効 */
#define PR_SLIP			(1 << 11)		/* パラメータ slip,slip_tray が有効 */
#define PR_COVER		(1 << 12)	/* パラメータ cover,coverprint,cover_tray が有効 */
#define PR_BACKCOVER		(1 << 13)	/* パラメータ backcover,backcoverprint,backcovertray が有効 */
/* シーケンシャルスタック */
#define PR_LIMITLESS_OFF	(0x0000)
#define PR_LIMITLESS_ON		(0x0010)
/* 排紙トレイ */
#define PR_BIN_MAIN             (0x0000)        /* 本体排紙(両面/マルチビン) */
#define PR_BIN_FINISHER         (0x0100)        /* フィニッシャ */
#define PR_BIN_MAILBOX          (0x0200)        /* メールボックス */
#define PR_BIN_MULTI            (0x0300)        /* マルチビン(CFトレイ) */
#define PR_BIN_MAIN_STD         (0x0000)        /* FD/標準排紙 */
#define PR_BIN_MAIN_BIN1        (0x0001)        /* 1ビン排紙 */
#define PR_BIN_MAIN_EXTED       (0x0002)        /* 拡張(ストレート)排紙 */
#define PR_BIN_FINI_PROOF       (0x0100)        /* プルーフトレイ */
#define PR_BIN_FINI_SHIFT       (0x0101)        /* シフトトレイ */
#define PR_BIN_FINI_BOOKLET     (0x0105)        /* ブックレット */
#define PR_BIN_MAILBOX1         (0x0201)        /* メールボックス１ */
#define PR_BIN_MULTI_1          (0x0300)        /* マルチビン１ */
#define PR_BIN_MULTI_2          (0x0301)        /* マルチビン２ */
/* ステープル */
#define PR_STAPLE_OFF              (0)
#define PR_STAPLE_LEFT_TOP_HORIZ   (1)         /* 左上水平 */
#define PR_STAPLE_LEFT_TOP_VERT    (2)         /* 左上垂直 */
#define PR_STAPLE_LEFT_TOP_SLANT   (3)         /* 左上斜め */
#define PR_STAPLE_RIGHT_TOP_HORIZ  (5)         /* 右上水平 */
#define PR_STAPLE_RIGHT_TOP_VERT   (6)         /* 右上垂直 */
#define PR_STAPLE_RIGHT_TOP_SLANT  (7)         /* 右上斜め */
#define PR_STAPLE_DOUBLE_LEFT      (9)         /* 左側２個所 */
#define PR_STAPLE_DOUBLE_TOP       (10)        /* 上側２個所 */
#define PR_STAPLE_DOUBLE_RIGHT     (11)        /* 右側２個所 */
#define PR_STAPLE_BOOKLET          (12)        /* 真中２個所 */
#define PR_STAPLE_NONE             (15)        /* 空打ち(GPS未対応のため使用禁止) */
#define PR_STAPLE_LEFT_TOP         (16)        /* 左上 */
#define PR_STAPLE_RIGHT_TOP        (17)        /* 右上 */
/* パンチ位置 */
#define PR_PUNCH_POS_BIT_MASK  (0x07)          /* パンチ位置指定ビット */
#define PR_PUNCH_OFF           (0)			   /* なし */
#define PR_PUNCH_LEFT          (1)             /* 左辺 */
#define PR_PUNCH_TOP           (2)             /* 上辺 */
#define PR_PUNCH_RIGHT         (3)             /* 右辺 */
#define PR_PUNCH_LEFT_TOP      (4)			   /* 左上 */
/* パンチ種別 */
#define PR_PUNCH_TYPE_BIT_MASK (0xF0)          /* パンチ種別指定ビット */
#define PR_PUNCH_JP2           (0x00)          /* 日本2穴 */
#define PR_PUNCH_US2           (0x10)          /* 北米2穴*/
#define PR_PUNCH_US3           (0x20)          /* 北米3穴*/
#define PR_PUNCH_EU4           (0x30)          /* 欧州4穴*/
#define PR_PUNCH_NEU4          (0x40)          /* 北欧4穴*/
#define PR_PUNCH_JP1           (0x50)          /* 日本1穴 */
#define PR_PUNCH_MULTI         (0x60)          /* GBCパンチ */
/* Z折り */
#define	PR_Z_FOLD_OFF		(0)		/* Ｚ折りなし */
#define	PR_Z_FOLD_RIGHT		(1)		/* 右折り */
#define	PR_Z_FOLD_BOTTOM	(2)		/* 下折り */
#define	PR_Z_FOLD_LEFT		(3)		/* 左折り */
/* トナーセーブ */
#define PR_TONERSAVE_OFF       (0)             /* トナーセーブOFF */
#define PR_TONERSAVE_MODE1     (1)             /* トナーセーブ・モード1 */
#define PR_TONERSAVE_MODE2     (2)             /* トナーセーブ・モード2 */
/* ジャムリカバリー */
#define PR_JAMRECOVERY_OFF     (0)
#define PR_JAMRECOVERY_ON      (1)
/* 部間でシフトをする／しない */
#define PR_SHIFT_ON		(0)		/* シフトする */
#define PR_SHIFT_OFF		(1)		/* シフトしない */

#define	PR_PAGE_CHAP_OFF		0		/* なし */
#define	PR_PAGE_CHAP_BLANK		1		/* 章区切り：印刷しない */
#define	PR_PAGE_CHAP_COPY		2		/* 章区切り：印刷する */
#define	PR_PAGE_CHAP_DIVIDE		3		/* 章分け */

#define	PR_PAGE_CHAP_SHEET1		1		/* 区切り用紙１ */
#define	PR_PAGE_CHAP_SHEET2		2		/* 区切り用紙２ */
#define	PR_PAGE_CHAP_SHEET3		3		/* 区切り用紙３ */
#define	PR_PAGE_CHAP_SHEET4		4		/* 区切り用紙４ */
#define	PR_PAGE_CHAP_SHEET5		5		/* 区切り用紙５ */
#define	PR_PAGE_CHAP_SHEET6		6		/* 区切り用紙６ */
#define	PR_PAGE_CHAP_SHEET7		7		/* 区切り用紙７ */

/* 表紙モード */
#define	PR_COVER_OFF		(0x00)		/* 表紙ＯＦＦ */
#define	PR_COVER_FRONT		(0x01)		/* 表紙ＯＮ */

/* 表紙画像印刷面 */
#define	PR_COVER_OFF		(0x00)		/* 表紙に印刷しない */
#define	PR_COVER_FRONT		(0x01)		/* 表紙に片面印刷する */
#define	PR_COVER_FRONT_D	(0x11)		/* 表紙に両面印刷する */

/* 裏表紙モード */
#define	PR_COVER_BACK		(0x02)		/* 裏表紙あり */

/* 裏表紙画像印刷面 */
#define	PR_COVER_BACK		(0x02)		/* 裏表紙印刷あり */
#define	PR_COVER_BACK_R		(0x22)		/* 裏表紙反転排紙(画像が片面の場合のみ) */

#define PR_UCP_BITMASK	0x00000003
#define PR_UCP_1BPP		0x00000000
#define PR_UCP_2BPP		0x00000001
#define PR_UCP_4BPP		0x00000002
#define PR_UCP_ENABLEBP		0x00004000
#define PR_UCP_ENABLEBMP	0x00008000

typedef struct pr_backpattern {
	unsigned long flag;
	unsigned long bpw;
	unsigned long bph;
	unsigned long bpsize;
	unsigned char *bpimg;
	unsigned long bpmw;
	unsigned long bpmh;
	unsigned long bpmsize;
	unsigned char *bpmimg;
} pr_backpattern_t;

typedef struct pr_forepattern {
	unsigned long flag;
	unsigned long fpw;
	unsigned long fph;
	unsigned long fosize;
	unsigned char *fppimg;
} pr_forepattern_t;

#define PR_UCP_TEXT_MASK		0x00000007
#define PR_UCP_TEXT_CENTER		0x00000000
#define PR_UCP_TEXT_TOPLEFT		0x00000001
#define PR_UCP_TEXT_TOPMID		0x00000002
#define PR_UCP_TEXT_TOPRIGHT	0x00000003
#define PR_UCP_TEXT_BOTLEFT		0x00000004
#define PR_UCP_TEXT_BOTMID		0x00000005
#define PR_UCP_TEXT_BOTRIGHT	0x00000006
#define PR_UCP_TEXT_REPEAT		0x00000007

#define PR_UCP_TEXT_REVERSE		0x00000008

#define PR_UCP_PRINT_MASK		0x00000060	
#define PR_UCP_PRINT_FG			0x00000020
#define PR_UCP_PRINT_BG			0x00000040
#define PR_UCP_PRINT_ALL		0x00000000
#define PR_UCP_PRINT_REVERSE	0x00000060	

#define PR_UCP_ROTATE_MASK		0x30000000
#define PR_UCP_ROTATE_0			0x00000000
#define PR_UCP_ROTATE_90		0x10000000
#define PR_UCP_ROTATE_180		0x20000000
#define PR_UCP_ROTATE_270		0x30000000

#define PR_UCP_CLR_MASK			0x0000000F
#define PR_UCP_CLR_BGP			0x00000001
#define PR_UCP_CLR_BGMP			0x00000002
#define PR_UCP_CLR_FGP			0x00000004
#define PR_UCP_CLR_TEXT			0x00000008

/*
 *	GIPA 
 */
#define PR_ACCELERATION_OFF		0x00000000
#define PR_ACCELERATION_ON		0x00000001

/* GIPA用メモリの最小値[KB] */
#define PR_GIPA_MIN_MEMSIZE		(1024*15)

/*
 *	PageRenderer commands.
 */


#ifndef EXPORT
#ifndef PACKDLL
#define EXPORT
#else
#define EXPORT	__declspec(dllexport)
#endif
#endif

/* Common functions */
#ifdef __cplusplus

/* Common functions */

extern "C" EXPORT int pr_resetusergamma(long lprh);
extern "C" EXPORT int pr_setusergamma(long lprh, unsigned long flag,
	unsigned char *gamma);
extern "C" EXPORT int pr_setscanlinerule(long, unsigned char);
extern "C" EXPORT int pr_bitmap_clip(long, unsigned long, unsigned
	long, unsigned long, long, long, unsigned long, unsigned long,
	unsigned long, unsigned char *);
extern "C" EXPORT int pr_barcode(long, unsigned char, unsigned long,
	long, long, pr_barcode_t*, long, unsigned char *, long, unsigned
	char *);
extern "C" EXPORT long pr_init(unsigned char *, unsigned long);
extern "C" EXPORT long pr_init_ext(unsigned char *, unsigned long,
	unsigned long);
extern "C" EXPORT int pr_end(long);
extern "C" EXPORT unsigned char * pr_getalloc(long, int, unsigned long);
extern "C" EXPORT unsigned char * pr_realloc(long, unsigned char *,
	int, unsigned long);
extern "C" EXPORT long pr_availalloc(long, int);
extern "C" EXPORT unsigned char * pr_memory_alloc(long, unsigned long);
extern "C" EXPORT unsigned char * pr_memory_realloc(long, unsigned
	char *, unsigned long);
extern "C" EXPORT int pr_memory_free(long, unsigned char *);
extern "C" EXPORT unsigned char * pr_memory_shrink(long, unsigned char
	*, unsigned long);
extern "C" EXPORT int pr_memory_avail(long);
extern "C" EXPORT int pr_memory_avail_free (long lprh);
extern "C" EXPORT int pr_getworkinuse (long lprh);
extern "C" EXPORT int pr_getworksize (long lprh);
extern "C" EXPORT int pr_limit_memory(long lprh, unsigned long size);
extern "C" EXPORT int pr_setworksize(long lprh, unsigned long worksize);
extern "C" EXPORT int pr_setdevice(long, pr_dev_info_t *);
extern "C" EXPORT int pr_setprecedinginfo(long, pr_preceding_info_t *);
extern "C" EXPORT int pr_setjobinfo(long, pr_job_info_t *);
extern "C" EXPORT int pr_setpageinfo(long, pr_page_info_t *);
extern "C" EXPORT int pr_getvalue(long, int, int *);
extern "C" EXPORT int pr_setprintmode(long, int);
extern "C" EXPORT int pr_setpageinfo_specified(long, pr_page_info_s_t *);
extern "C" EXPORT int pr_setpageinfo_extend(long, pr_page_info_shm_t *);
extern "C" EXPORT int pr_changebinding(long, unsigned char, long *);
extern "C" EXPORT int pr_setchaptermode(long, long, long);
extern "C" EXPORT int pr_reducememory_mode(long, unsigned long);
extern "C" EXPORT int pr_popclip(long);
extern "C" EXPORT int pr_saveclip(long);
extern "C" EXPORT int pr_restoreclip(long);
extern "C" EXPORT int pr_settransmode(long, unsigned long, unsigned
	char *);
extern "C" EXPORT int pr_setrop3mode(long, unsigned long);
extern "C" EXPORT int pr_scanline_slope(long, unsigned long, long,
	long, long, unsigned long, long, long, char *, char *);
extern "C" EXPORT int pr_selectdevicedither(long, pr_resolution_info_t
	*, pr_resolution_info_t *);
extern "C" EXPORT int pr_getallocmemsize(long, unsigned char *);
extern "C" EXPORT int pr_getmemsize(long,unsigned char *);
extern "C" EXPORT int pr_getabsmemsize(long,unsigned char *);

/* Job Control Category functions */
extern "C" EXPORT int pr_jobstart(long);
extern "C" EXPORT int pr_jobend(long);
extern "C" EXPORT int pr_delayed_jobend(long);
extern "C" EXPORT int pr_pagestart(long, unsigned long, unsigned long,
	unsigned long, unsigned long, unsigned long, unsigned long,
	unsigned long, unsigned long, unsigned long, unsigned long);
extern "C" EXPORT int pr_pageend(long, long);
extern "C" EXPORT int pr_bandstart(long, unsigned long);
extern "C" EXPORT int pr_bandend(long);
extern "C" EXPORT int pr_bandcancel(long);
extern "C" EXPORT int pr_abort(long);
extern "C" EXPORT int pr_dividejob (long, pr_dividejob_info_t *, int *);

/* Page Control Category function */
extern "C" EXPORT int pr_setgraymode(long, unsigned char, unsigned
	char, unsigned char, unsigned char);
extern "C" EXPORT int pr_setgrayjudgemode(long, unsigned char, unsigned
	char, unsigned char, unsigned char);
extern "C" EXPORT int pr_setusedplane(long, unsigned char, unsigned
	char, unsigned char, unsigned char);
extern "C" EXPORT int pr_settonersave(long, char);
extern "C" EXPORT int pr_settonerlimit(long, int);
extern "C" EXPORT int pr_setdeftonerlimit_ratio(long, int, int, int,
	int, int);
extern "C" EXPORT int pr_setusedframe(long, unsigned char);
extern "C" EXPORT int pr_settonerlimit_ratio(long, int, int, int, int,
	int *, int *, int *, int *);
extern "C" EXPORT int pr_settonersave_ratio(long, char, char, char,
	char);
extern "C" EXPORT int pr_setgammathrough(long, char);
extern "C" EXPORT int pr_clipinit(long, long, long, unsigned long,
	unsigned long);
extern "C" EXPORT int pr_densityadjust(long, unsigned char, unsigned
	char, unsigned char, unsigned char);
extern "C" EXPORT int pr_setmediatype(long, unsigned char);
extern "C" EXPORT int pr_setratio_rgb(long, unsigned char,
				unsigned char, unsigned char,
				unsigned char, unsigned char);
extern "C" EXPORT int pr_setratio_tonerlimit(long, unsigned char,
				unsigned char, unsigned char,
				unsigned char, unsigned char);


/* Graphics Category functions */
extern "C" EXPORT int pr_rectangle(long, unsigned long, long, long,
	long, long);
extern "C" EXPORT int pr_polyline(long, unsigned long, unsigned long,
	void *);
extern "C" EXPORT int pr_polylinepath(long, unsigned long, unsigned
	long, void *);
extern "C" EXPORT int pr_polybezier(long, unsigned long, unsigned long,
	void *);
extern "C" EXPORT int pr_polybezierpath(long, unsigned long, unsigned
	long, void *);
extern "C" EXPORT int pr_scanline(long, unsigned long, unsigned long,
	void *);
extern "C" EXPORT int pr_scanlinepath(long, unsigned long, void *);

/* Font Category functions */
extern "C" EXPORT int pr_init_devfont(long, unsigned char *, unsigned
	long);
extern "C" EXPORT int pr_font_savetodevice(long lprh, unsigned char
	deviceobject, char *filename);
extern "C" EXPORT int pr_font_loadfromdevice(long lprh, unsigned char
	deviceobject, char *filename);
extern "C" EXPORT int pr_font_deleteofdevice(long lprh, unsigned char
	deviceobject, unsigned char deleteobject, char *filename);
extern "C" EXPORT int pr_definefont_device(long, unsigned short,
	unsigned char, unsigned short, unsigned short, unsigned short);
extern "C" EXPORT int pr_definefont_download(long, unsigned short);
extern "C" EXPORT int pr_selectfont(long, unsigned short);
extern "C" EXPORT int pr_deletefont(long, unsigned short);
extern "C" EXPORT int pr_deleteallfont(long);
extern "C" EXPORT int pr_registchar(long, unsigned long, unsigned
	short, unsigned char, unsigned long, unsigned short, unsigned
	short, void *);
extern "C" EXPORT int pr_deletechar(long, unsigned short, unsigned
	short *);
extern "C" EXPORT int pr_deleteallchar(long);
extern "C" EXPORT int pr_putchar_device(long, long, long, unsigned
	short);
extern "C" EXPORT int pr_putchar_download(long, unsigned long, long,
	long, unsigned long, unsigned short, unsigned short, void *);
extern "C" EXPORT int pr_putchar_cached(long, long, long, unsigned
	short);
extern "C" EXPORT int pr_putstring_device(long, unsigned short, long,
	long, unsigned short *);
extern "C" EXPORT int pr_getcharbox(long, unsigned char, unsigned
	short, unsigned short, unsigned short, unsigned short, short *,
	short *, unsigned short *, unsigned short *);
extern "C" EXPORT int pr_getbaseline(long, unsigned short, float *);

/* Image Category functions */
extern "C" EXPORT int pr_bitblt(long, unsigned long, unsigned short,
	long, long, unsigned long, unsigned long, unsigned long, unsigned
	char *);
extern "C" EXPORT int pr_stretchblt(long, unsigned long, unsigned long,
	unsigned long, long, long, unsigned long, unsigned long, unsigned
	char *, unsigned long);
extern "C" EXPORT int pr_stretchblt_index(long, unsigned long,
	unsigned long, unsigned long, long, long, unsigned long, unsigned
	long, unsigned char *, unsigned char *, unsigned long);
extern "C" EXPORT int pr_stretchblt_repeat(long, unsigned long,
	unsigned long, unsigned long, long, long, unsigned long, unsigned
	long, unsigned long, unsigned long, unsigned char *, unsigned long);
extern "C" EXPORT int pr_stretchblt_index_repeat(long, unsigned long,
	unsigned long, unsigned long, long, long, unsigned long, unsigned
	long, unsigned long, unsigned long, unsigned char *, unsigned char
	*, unsigned long);
extern "C" EXPORT int pr_drawurf(long, unsigned short, unsigned short,
	unsigned long, unsigned long, long, long, unsigned long, unsigned long,
	unsigned char *);
#ifdef  PR_XPS_SUPPORT 
extern "C" EXPORT int pr_enableblending(long prh, int bBlending);
extern "C" EXPORT int pr_setalpha(long prh, unsigned int uiFlag,
	unsigned int uiAlpha);
extern "C" EXPORT int pr_setblendcolorspace(long prh, unsigned int
	uiBlendColorSpace);
extern "C" EXPORT int pr_setblendmode(long prh, int Blendmode);
#endif
/* Graphics Setting Category functions */
extern "C" EXPORT int pr_setrop3(long, unsigned char);
extern "C" EXPORT int pr_setlinewidth(long, unsigned long);
extern "C" EXPORT int pr_setlinedash(long, unsigned long, unsigned
	short);
#ifndef NOT_SUPPORT_IPS
extern "C" EXPORT int pr_setlinedash_ex(long, unsigned char *,
	unsigned long, unsigned long);
extern "C" EXPORT int pr_setlineshift(long, unsigned long);
#else /* NOT_SUPPORT_IPS */
extern "C" EXPORT int pr_setlineshift(long, unsigned char);
#endif /* NOT_SUPPORT_IPS */
extern "C" EXPORT int pr_setbrushorg(long, long, long);
extern "C" EXPORT int pr_resetclip(long);
extern "C" EXPORT int pr_setbkmode(long, unsigned char);
extern "C" EXPORT int pr_setcolor(long, unsigned char, unsigned char *);
extern "C" EXPORT int pr_setcolordrawfill(long, unsigned char,
	unsigned char *);
extern "C" EXPORT int pr_setlinecap(long, unsigned char);
extern "C" EXPORT int pr_setlinejoin(long, unsigned char);
extern "C" EXPORT int pr_setmiterlimit(long, float);
extern "C" EXPORT int pr_setflatness(long, float);
extern "C" EXPORT int pr_setdithermode(long, unsigned char, unsigned
	char, unsigned char, unsigned char);
extern "C" EXPORT int pr_setwidthadjust(long, unsigned char);
extern "C" EXPORT int pr_setbop(long, unsigned char);
extern "C" EXPORT int pr_setcutoutmode(long, char);
extern "C" EXPORT int pr_setpapersuppress(long, unsigned int);

extern "C" EXPORT int pr_setaccelerationmode(long, unsigned long, unsigned long);

/* Object Category functions */
extern "C" EXPORT int pr_defobject(long, unsigned short);
extern "C" EXPORT int pr_allclearobject(long);
extern "C" EXPORT int pr_paintobject(long, unsigned short);

/* Rendering Category functions */
extern "C" EXPORT int pr_defbrush(long, unsigned long, unsigned char,
	unsigned char, unsigned char, unsigned short, unsigned char *);
extern "C" EXPORT int pr_selectbrush(long, unsigned long);
extern "C" EXPORT int pr_allclearbrush(long);
extern "C" EXPORT int pr_defbrush_anysize(long, unsigned long,
	unsigned long, unsigned long, unsigned long, unsigned long,
	unsigned long, unsigned char *, unsigned char *);

/* Error Code Control function */
extern "C" EXPORT int pr_get_errorcode(long);
extern "C" EXPORT void pr_clear_errorcode(long);

/* CMM functions */
extern "C" EXPORT long pr_setprofileid(long, unsigned long, unsigned
	long, unsigned long, unsigned long);
extern "C" EXPORT long pr_defineprofile(long, unsigned long, unsigned
	long, unsigned char *);
extern "C" EXPORT long pr_setaccentphototable(long, unsigned char *);
extern "C" EXPORT int pr_applyprofilergb(long, unsigned char, unsigned
	char *, unsigned char *, unsigned char *, unsigned char *,
	unsigned char *, unsigned char *, unsigned long);
extern "C" EXPORT long pr_setprofileid_ext(long, unsigned char,
	unsigned long, unsigned long, unsigned long, unsigned long);

/* IJ Renderer Category */
extern "C" EXPORT int pr_setmargin(long, unsigned char, long, long);
extern "C" EXPORT int pr_setinfo_ij(long, pr_ij_info_t *);
extern "C" EXPORT int pr_setoutput(long, long, unsigned long, unsigned
	long);

/* Other Category */
extern "C" EXPORT int pr_rgb2cmyk(long, unsigned char, unsigned char,
	unsigned char, unsigned char, unsigned char *, unsigned char *,
	unsigned char *, unsigned char *);
extern "C" EXPORT int pr_rgb2cmyk_pixels(long, unsigned char,
	unsigned char *, unsigned char *, unsigned long);
extern "C" EXPORT int pr_rgb2k(long, unsigned char, unsigned char,
	unsigned char, unsigned char, unsigned char *);
extern "C" EXPORT int pr_rgb2k_pixels(long, unsigned char,
	unsigned char *, unsigned char *, unsigned long);
extern "C" EXPORT int pr_notify_noerror_display(long, long *);
extern "C" EXPORT int pr_set_pageerror_continue(long, int);
extern "C" EXPORT int pr_notify_errorinformation(long, long *);

/* Unauthorized Copy Prevention */
extern "C" EXPORT int pr_ucp_start(long, int);
extern "C" EXPORT int pr_set_ucp_backpattern(long, pr_backpattern_t *);
extern "C" EXPORT int pr_set_ucp_forepattern(long, pr_forepattern_t *);
extern "C" EXPORT int pr_set_ucp_text(long, unsigned long, long, long,
	unsigned long,  unsigned long, unsigned long, void *);
extern "C" EXPORT int pr_set_ucp_text_device(long, unsigned short,
	unsigned short,  unsigned short, unsigned short, unsigned short,
	unsigned short *);
extern "C" EXPORT int pr_ucp_end(long);
extern "C" EXPORT int pr_ucp_paint(long, unsigned long, unsigned short,
	unsigned long);
extern "C" EXPORT int pr_ucp_clear(long, unsigned long);
#else /* __cplusplus */
// If CPLUSPLUS is not defined , c compiler

extern EXPORT long pr_init(unsigned char *, unsigned long);
extern EXPORT long pr_init_ext(unsigned char *, unsigned long,
	unsigned long);
extern EXPORT int pr_end(long);
extern EXPORT unsigned char * pr_getalloc(long, int, unsigned long);
extern EXPORT unsigned char * pr_realloc(long, unsigned char *, int,
	unsigned long);
extern EXPORT long pr_availalloc(long, int);
extern EXPORT unsigned char * pr_memory_alloc(long, unsigned long);
extern EXPORT unsigned char *pr_memory_realloc(long, unsigned char *,
	unsigned long);
extern EXPORT int pr_memory_free(long, unsigned char *);
extern EXPORT unsigned char * pr_memory_shrink(long, unsigned char *,
	unsigned long);
extern EXPORT int pr_memory_avail(long);
extern EXPORT int pr_setdevice(long, pr_dev_info_t *);
extern EXPORT int pr_setprecedinginfo(long, pr_preceding_info_t *);
extern EXPORT int pr_setjobinfo(long, pr_job_info_t *);
extern EXPORT int pr_setpageinfo(long, pr_page_info_t *);
extern EXPORT int pr_getvalue(long, int, int *);
extern EXPORT int pr_setprintmode(long, int);
extern EXPORT int pr_setpageinfo_specified(long, pr_page_info_s_t *);
extern EXPORT int pr_setpageinfo_extend(long, pr_page_info_shm_t *);
extern EXPORT int pr_changebinding(long, unsigned char, long *);
extern EXPORT int pr_setchaptermode(long, long, long);
extern EXPORT int pr_reducememory_mode(long, unsigned long);
extern EXPORT int pr_popclip(long);
extern EXPORT int pr_saveclip(long);
extern EXPORT int pr_restoreclip(long);
extern EXPORT int pr_settransmode(long, unsigned long, unsigned char *);
extern EXPORT int pr_setrop3mode(long, unsigned long);
extern EXPORT int pr_scanline_slope(long, unsigned long, long, long,
	long, unsigned long, long, long, char *, char *);
extern EXPORT int pr_selectdevicedither(long, pr_resolution_info_t *,
	pr_resolution_info_t *);
extern EXPORT int pr_limit_memory(long, unsigned long);
extern EXPORT int pr_setworksize(long, unsigned long);
extern EXPORT int pr_memory_avail_free(long);
extern EXPORT int pr_getworksize(long);
extern EXPORT int pr_getworkinuse(long);
extern EXPORT int pr_getallocmemsize(long, unsigned char *);
extern EXPORT int pr_getmemsize(long,unsigned char *);
extern EXPORT int pr_getabsmemsize(long,unsigned char *);

/* Job Control Category functions */
extern EXPORT int pr_jobstart(long);
extern EXPORT int pr_jobend(long);
extern EXPORT int pr_delayed_jobend(long);
extern EXPORT int pr_pagestart(long, unsigned long, unsigned long,
	unsigned long, unsigned long, unsigned long, unsigned long,
	unsigned long, unsigned long, unsigned long, unsigned long);
extern EXPORT int pr_pageend(long, long);
extern EXPORT int pr_bandstart(long, unsigned long);
extern EXPORT int pr_bandend(long);
extern EXPORT int pr_bandcancel(long);
extern EXPORT int pr_abort(long);
extern EXPORT int pr_dividejob(long, pr_dividejob_info_t *, int *);

/* Page Control Category function */
extern EXPORT int pr_setgraymode(long, unsigned char, unsigned char,
	unsigned char, unsigned char);
extern EXPORT int pr_setgrayjudgemode(long, unsigned char, unsigned char,
	unsigned char, unsigned char);
extern EXPORT int pr_setusedplane(long, unsigned char, unsigned char,
	unsigned char, unsigned char);
extern EXPORT int pr_settonersave(long, char);
extern EXPORT int pr_settonerlimit(long, int);
extern EXPORT int pr_setusedframe(long, unsigned char);
extern EXPORT int pr_settonerlimit_ratio(long, int, int, int, int, int
	*, int *, int *, int *);
extern EXPORT int pr_settonerlimit_ratio(long, int, int, int, int, int
	*, int *, int *, int *);
extern EXPORT int pr_settonersave_ratio(long, char, char, char, char);
extern EXPORT int pr_setgammathrough(long, char);
extern EXPORT int pr_clipinit(long, long, long, unsigned long,
	unsigned long);
extern EXPORT int pr_densityadjust(long, unsigned char, unsigned char,
	unsigned char, unsigned char);
extern EXPORT int pr_setmediatype(long, unsigned char);
extern EXPORT int pr_setratio_rgb(long, unsigned char,
				unsigned char, unsigned char,
				unsigned char, unsigned char);
extern EXPORT int pr_setratio_tonerlimit(long, unsigned char,
				unsigned char, unsigned char,
				unsigned char, unsigned char);


/* Graphics Category functions */
extern EXPORT int pr_rectangle(long, unsigned long, long, long, long,
	long);
extern EXPORT int pr_polyline(long, unsigned long, unsigned long, void
	*);
extern EXPORT int pr_polylinepath(long, unsigned long, unsigned long,
	void *);
extern EXPORT int pr_polybezier(long, unsigned long, unsigned long,
	void *);
extern EXPORT int pr_polybezierpath(long, unsigned long, unsigned long,
	void *);
extern EXPORT int pr_scanline(long, unsigned long, unsigned long, void
	*);
extern EXPORT int pr_scanlinepath(long, unsigned long, void *);
extern EXPORT int pr_arc(long, unsigned long, long, long, unsigned
	long, unsigned long, unsigned long);
extern EXPORT int pr_barcode(long, unsigned char, unsigned long, long,
	long, pr_barcode_t *, long, unsigned char *, long, unsigned char *);


/* Font Category functions */
extern EXPORT int pr_init_devfont(long, unsigned char *, unsigned long);
extern EXPORT int pr_font_savetodevice(long lprh, unsigned char
	deviceobject, char *filename);
extern EXPORT int pr_font_loadfromdevice(long lprh, unsigned char
	deviceobject, char *filename);
extern EXPORT int pr_font_deleteofdevice(long lprh, unsigned char
	deviceobject, unsigned char deleteobject, char *filename);
extern EXPORT int pr_definefont_device(long, unsigned short, unsigned
	char, unsigned short, unsigned short, unsigned short);
extern EXPORT int pr_definefont_download(long, unsigned short);
extern EXPORT int pr_selectfont(long, unsigned short);
extern EXPORT int pr_deletefont(long, unsigned short);
extern EXPORT int pr_deleteallfont(long);
extern EXPORT int pr_registchar(long, unsigned long, unsigned short,
	unsigned char, unsigned long, unsigned short, unsigned short, void *);
extern EXPORT int pr_deletechar(long, unsigned short, unsigned short *);
extern EXPORT int pr_deleteallchar(long);
extern EXPORT int pr_putchar_device(long, long, long, unsigned short);
extern EXPORT int pr_putchar_download(long, unsigned long, long, long,
	unsigned long, unsigned short, unsigned short, void *);
extern EXPORT int pr_putchar_cached(long, long, long, unsigned short);
extern EXPORT int pr_putstring_device(long, unsigned short, long, long,
	unsigned short *);
extern EXPORT int pr_getcharbox(long, unsigned char, unsigned short,
	unsigned short, unsigned short, unsigned short, short *, short *,
	unsigned short *, unsigned short *);
extern EXPORT int pr_getbaseline(long, unsigned short, float *);

/* Image Category functions */
extern EXPORT int pr_bitblt(long, unsigned long, unsigned short, long,
	long, unsigned long, unsigned long, unsigned long, unsigned char *);
extern EXPORT int pr_stretchblt(long, unsigned long, unsigned long,
	unsigned long, long, long, unsigned long, unsigned long, unsigned
	char *, unsigned long);
extern EXPORT int pr_stretchblt_index(long, unsigned long, unsigned
	long, unsigned long, long, long, unsigned long, unsigned long,
	unsigned char *, unsigned char *, unsigned long);
extern EXPORT int pr_stretchblt_repeat(long, unsigned long, unsigned
	long, unsigned long, long, long, unsigned long, unsigned long,
	unsigned long, unsigned long, unsigned char *, unsigned long);
extern EXPORT int pr_stretchblt_index_repeat(long, unsigned long,
	unsigned long, unsigned long, long, long, unsigned long, unsigned
	long, unsigned long, unsigned long, unsigned char *, unsigned char
	*, unsigned long);
extern EXPORT int pr_drawurf(long, unsigned short, unsigned short,
	unsigned long, unsigned long, long, long, unsigned long, unsigned long,
	unsigned char *);
extern EXPORT int pr_bitmap_clip(long, unsigned long, unsigned long,
	unsigned long, long, long, unsigned long, unsigned long, unsigned
	long, unsigned char *);

/* Graphics Setting Category functions */
extern EXPORT int pr_setrop3(long, unsigned char);
extern EXPORT int pr_setlinewidth(long, unsigned long);
extern EXPORT int pr_setlinedash(long, unsigned long, unsigned short);
#ifndef NOT_SUPPORT_IPS
extern EXPORT int pr_setlinedash_ex(long, unsigned char *, unsigned
	long, unsigned long);
extern EXPORT int pr_setlineshift(long, unsigned long);
#else /* NOT_SUPPORT_IPS */
extern EXPORT int pr_setlineshift(long, unsigned char);
#endif /* NOT_SUPPORT_IPS */
extern EXPORT int pr_setbrushorg(long, long, long);
extern EXPORT int pr_resetclip(long);
extern EXPORT int pr_setbkmode(long, unsigned char);
extern EXPORT int pr_setcolor(long, unsigned char, unsigned char *);
extern EXPORT int pr_setcolordrawfill(long, unsigned char, unsigned
	char *);
extern EXPORT int pr_setlinecap(long, unsigned char);
extern EXPORT int pr_setlinejoin(long, unsigned char);
extern EXPORT int pr_setmiterlimit(long, float);
extern EXPORT int pr_setflatness(long, float);
extern EXPORT int pr_setdithermode(long, unsigned char, unsigned char,
	unsigned char, unsigned char);
extern EXPORT int pr_setwidthadjust(long, unsigned char);
extern EXPORT int pr_setbop(long, unsigned char);
extern EXPORT int pr_setcutoutmode(long, char);
extern EXPORT int pr_setpapersuppress(long, unsigned int);
extern EXPORT int pr_setscanlinerule(long, unsigned char);

extern EXPORT int pr_setaccelerationmode(long, unsigned long, unsigned long);

/* Object Category functions */
extern EXPORT int pr_defobject(long, unsigned short);
extern EXPORT int pr_allclearobject(long);
extern EXPORT int pr_paintobject(long, unsigned short);

/* Rendering Category functions */
extern EXPORT int pr_defbrush(long, unsigned long, unsigned char,
	unsigned char, unsigned char, unsigned short, unsigned char *);
extern EXPORT int pr_selectbrush(long, unsigned long);
extern EXPORT int pr_allclearbrush(long);
extern EXPORT int pr_defbrush_anysize(long, unsigned long, unsigned
	long, unsigned long, unsigned long, unsigned long, unsigned long,
	unsigned char *, unsigned char *);

/* Error Code Control function */
extern EXPORT int pr_get_errorcode(long);
extern EXPORT void pr_clear_errorcode(long);

/* CMM functions */
extern EXPORT long pr_setprofileid(long, unsigned long, unsigned long,
	unsigned long, unsigned long);
extern EXPORT long pr_defineprofile(long, unsigned long, unsigned long,
	unsigned char *);
extern EXPORT long pr_setaccentphototable(long, unsigned char *);
extern EXPORT int pr_applyprofilergb(long, unsigned char, unsigned
	char *, unsigned char *, unsigned char *, unsigned char *,
	unsigned char *, unsigned char *, unsigned long);
extern EXPORT long pr_setprofileid_ext(long, unsigned char,
	unsigned long, unsigned long, unsigned long, unsigned long);

/* IJ Renderer Category */
extern EXPORT int pr_setmargin(long, unsigned char, long, long);
extern EXPORT int pr_setinfo_ij(long, pr_ij_info_t *);
extern EXPORT int pr_setoutput(long, long, unsigned long, unsigned
	long);

/* Dither, Gamma Category */
extern EXPORT int pr_setusergamma(long, unsigned long, unsigned char *);
extern EXPORT int pr_resetusergamma(long);

/* Other Category */
extern EXPORT int pr_rgb2cmyk(long, unsigned char, unsigned char,
	unsigned char, unsigned char, unsigned char *, unsigned char *,
	unsigned char *, unsigned char *);
extern EXPORT int pr_rgb2cmyk2(long, unsigned char, unsigned char,
	unsigned char, unsigned char, unsigned char *, unsigned char *,
	unsigned char *, unsigned char *);
extern EXPORT int pr_rgb2cmyk_pixels(long, unsigned char,
	unsigned char *, unsigned char *, unsigned long);
extern EXPORT int pr_rgb2k(long, unsigned char, unsigned char,
	unsigned char, unsigned char, unsigned char *);
extern EXPORT int pr_rgb2k_pixels(long, unsigned char,
	unsigned char *, unsigned char *, unsigned long);
extern EXPORT int pr_notify_noerror_display(long, long *);
extern EXPORT int pr_set_pageerror_continue(long, int);
extern EXPORT int pr_notify_errorinformation(long, long *);

/* Unauthorized Copy Prevention */
extern EXPORT int pr_ucp_start(long, int);
extern EXPORT int pr_set_ucp_backpattern(long, pr_backpattern_t *);
extern EXPORT int pr_set_ucp_forepattern(long, pr_forepattern_t *);
extern EXPORT int pr_set_ucp_text(long, unsigned long, long, long,
	unsigned long,  unsigned long, unsigned long, void *);
extern EXPORT int pr_set_ucp_text_device(long, unsigned short, unsigned short,
	unsigned short,  unsigned short, unsigned short, unsigned short *);
extern EXPORT int pr_ucp_end(long);
extern EXPORT int pr_ucp_paint(long, unsigned long, unsigned short,
	unsigned long);
extern EXPORT int pr_ucp_clear(long, unsigned long);
#endif /* __cplusplus */

#endif  /*  __PAGER_H__  */

