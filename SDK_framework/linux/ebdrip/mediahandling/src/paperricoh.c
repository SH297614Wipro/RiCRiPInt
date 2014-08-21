
#include "omstub.h"

#define NULL 0

static const PAPERINFO * curPaper;
static const PAPERINFO * endPaper;
extern Sint8 ChoosePaperDirectionDone;

void PRpaperPair (PAPERCODE OMsize, int xres, int yres, OMenum *LongEdge, OMenum *ShortEdge )
{
    int nPapers;
    const PAPERINFO *paperInfo, *paperInfo2;
	PAPERINFO  * papers;

    paperInfo = PRpaperinfoOriginal (OMsize, xres, yres);
    /*ASSERT(paperInfo);*/
    nPapers = PRpapertable(&papers, xres, yres);
	/*ASSERT(LongEdge && ShortEdge);*/
    *LongEdge = *ShortEdge = 0;

    if( paperInfo != (papers+nPapers) ) {    /* 'paperInfo' is not last table */
        paperInfo2 = paperInfo + 1; /* check next PAPERINFO */
        if ( paperInfo->PCLpaperID == paperInfo2->PCLpaperID ) {
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo->OMcode) )
#endif
            *ShortEdge = paperInfo->OMcode;
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo2->OMcode) )
#endif
            *LongEdge = paperInfo2->OMcode;
			return;
        }
    }

    if( paperInfo != papers ) {  /* 'paperInfo' is not first table*/
        paperInfo2 = paperInfo - 1; /* check previous PAPERINFO */
            if ( paperInfo->PCLpaperID == paperInfo2->PCLpaperID ) {
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo2->OMcode) )
#endif
            *ShortEdge = paperInfo2->OMcode;
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo->OMcode) )
#endif
            *LongEdge = paperInfo->OMcode;
            return;
        }
    }

    *ShortEdge = paperInfo->OMcode; /*Not found pair code*/
}

void PRcustompaperinfo(int pwidth, int plength, int xres, int yres)
{ 
#if 0 /*Disabling custom paper for now */
    int i;
    Sint32 n;
    PAPERINFO * np = (PAPERINFO *) paper_table_variable_resolution;
    CONST PAPERINFO * op = (CONST PAPERINFO *) system_paper_table;
    Boolean convert8 = ( xres % 300 );
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    Boolean   = OMGetCurrentBool(OMEDGETOEDGE,OMSYSTEM);
#ifdef PCL_CUSTOM_EDGE2EDGE
    Boolean enter_lang;
	if(customEdge2Edge){
		int njobid, ujobid;
    	enter_lang = OMGetCurrentEnum(OMREQPROCREASON, OMSYSTEM) ==
						REQPROCREASON_ENTERLANGUAGE;
		PrintSysGetjobid( &njobid, &ujobid);
		if(njobid == pre_njobid && ujobid == pre_ujobid)
			enter_lang = pre_enter_lang_custom;
		else {
			pre_njobid = njobid;
			pre_ujobid = ujobid;
		}
	}
#endif /* PCL_CUSTOM_EDGE2EDGE */
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */

#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    if (cvtx == xres && cvty == yres && cvtw == pwidth && cvtl == plength && set_edge2edge_custom == edge2edge
#ifdef PCL_CUSTOM_EDGE2EDGE
					 && (!customEdge2Edge || enter_lang == pre_enter_lang_custom) 
#endif
       )
        return;
#else
    if (cvtx == xres && cvty == yres && cvtw == pwidth && cvtl == plength)
        return;
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */

	for (i = dimof(system_paper_table); i > 0; i--, np++, op++) {
        if (op->OMcode == PAPERSIZE_CUSTOM)
            break;
    }

    if (i == 0)
        return;

#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    if ( edge2edge ) {
#ifdef PCL_CUSTOM_EDGE2EDGE
		if (customEdge2Edge && !enter_lang) {
			np->size.x = np->printable.x = np->rotnomsize.x = pwidth;
			np->nominal.x = pwidth - CONVERT_XONE(nomoffset);
			np->size.y = np->printable.y = np->nominal.y = plength;
			np->rotnomsize.y = plength - CONVERT_YONE(rotnomoffset);
			np->offset.x = np->offset.y = 0;
			CONVERT(nomoffset);
			if (pwidth >= plength) {
				CONVERT(rotnomoffset);
			} else {
				np->rotnomoffset.x = np->rotnomoffset.y = 0;
			}
	
			/*	The next 2 entries are NOT scaled. They get scaled when they used.
			 */
			np->HPnomoffset.x = np->nomoffset.x;
			np->HPnomoffset.y = np->HProtnomoffset.x = 0;
			np->HProtnomoffset.y = np->rotnomoffset.y;
		} else {
#endif /*PCL_CUSTOM_EDGE2EDGE*/   

#ifdef RP_CUSTOMPAPERSIZE
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if ((TRUE == PrintSysIsPS()) || (TRUE == PrintSysIsPDF())){
#endif
    if(pwidth > plength){
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = plength;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = pwidth;
    } else {
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = pwidth;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = plength;
	}   
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
    } else {		
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = pwidth;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = plength;
	}   
#endif
#else    /* RP_CUSTOMPAPERSIZE */ 
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = pwidth;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = plength;
#endif  /* RP_CUSTOMPAPERSIZE */ 
        np->offset.x = np->nomoffset.x = np->rotnomoffset.x = 0;
        np->offset.y = np->nomoffset.y = np->rotnomoffset.y = 0;

		/*  The next 2 entries are NOT scaled. They get scaled when they used.
         */
        np->HPnomoffset.x = np->HProtnomoffset.x = 0;
        np->HPnomoffset.y = np->HProtnomoffset.y = 0;
#ifdef PCL_CUSTOM_EDGE2EDGE
		}
#endif

    } else {
#endif

#ifdef RP_CUSTOMPAPERSIZE
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if ((TRUE == PrintSysIsPS()) || (TRUE == PrintSysIsPDF())){
#endif
    np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);
    if(pwidth > plength){
    np->size.x = plength;
    np->size.y = pwidth;
    np->nominal.x = plength - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = pwidth - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = plength - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = pwidth - 2 * CONVERT_YONE(rotnomoffset);
    } else {
    np->size.x = pwidth;
    np->size.y = plength;
    np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);
    np->nominal.x = pwidth - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = plength - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = pwidth - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = plength - 2 * CONVERT_YONE(rotnomoffset);
    }
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
    } else{
    np->size.x = pwidth;
    np->size.y = plength;
    np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);
    np->nominal.x = pwidth - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = plength - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = pwidth - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = plength - 2 * CONVERT_YONE(rotnomoffset);
	}
#endif
#else   /* RP_CUSTOMPAPERSIZE */ 
	
    np->size.x = pwidth;
    np->size.y = plength;
    np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);
    np->nominal.x = pwidth - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = plength - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = pwidth - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = plength - 2 * CONVERT_YONE(rotnomoffset);
#endif /* RP_CUSTOMPAPERSIZE */ 
    
    CONVERT(offset);
    CONVERT(nomoffset);
    CONVERT(rotnomoffset);
    
    /*  The next 2 entries are NOT scaled. They get scaled when they used.
     */
    FIELDCOPY(HPnomoffset);
    FIELDCOPY(HProtnomoffset);

#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    }
#endif

#ifdef PCL5_CUSTOMSIZE_COMMAND
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if( (TRUE == PrintSysIsPCL()) || (TRUE == PrintSysIsPCLXL())){
#endif
    if (np->printable.x <= 0)
        np->printable.x = NBITS;
    if (np->nominal.x <= 0)
        np->nominal.x = NBITS;
    if (np->rotnomsize.x <= 0)
        np->rotnomsize.x = NBITS;
    if (np->printable.y <= 0)
        np->printable.y = 1;
    if (np->nominal.y <= 0)
        np->nominal.y = 1;
    if (np->rotnomsize.y <= 0)
        np->rotnomsize.y = 1;
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	}
#endif
#endif /* PCL5_CUSTOMSIZE_COMMAND */

    np->OMcode = op->OMcode;
    np->PCLpaperID = op->PCLpaperID;
    np->XLpaperID = op->XLpaperID;
    np->envelope = op->envelope;
    np->noduplex = op->noduplex;

#ifdef EMPOSTSCRIPT /* RP_CUSTOMPAPERSIZE */
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if ((TRUE == PrintSysIsPS()) || (TRUE == PrintSysIsPDF())){
#endif
#ifdef RP_CUSTOMPAPERSIZE
      if(pwidth > plength){
	np->PS_PageSize.x = (int)(((float)plength/xres)*72);  /* dot -> pt */
	np->PS_PageSize.y = (int)(((float)pwidth/yres)*72); /* dot -> pt */
      	}else{
	np->PS_PageSize.x = (int)(((float)pwidth/xres)*72);  /* dot -> pt */
	np->PS_PageSize.y = (int)(((float)plength/yres)*72); /* dot -> pt */
	  	}
#endif /* RP_CUSTOMPAPERSIZE */ 
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    if ( edge2edge ) {
		np->PS_printable.x = pwidth;
		np->PS_printable.y = plength;
		np->PS_margins.x = 0;
		np->PS_margins.y = 0;
    } else {
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */
		np->PS_printable.x = pwidth - 2 * CONVERT_XONE(PS_margins);
		np->PS_printable.y = plength - 2 * CONVERT_YONE(PS_margins);
		CONVERT(PS_margins);
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    }
#endif
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	}
#endif
#endif /* EMPOSTSCRIPT (RP_CUSTOMPAPERSIZE) */

    np->resolution.x = xres;
    np->resolution.y = yres;

#ifdef GPS_REJECTION
	np->Direction = op->Direction;
	np->Duplex = op->Duplex;
	np->Staple = op->Staple;
	np->RotateCollate = op->RotateCollate;
	np->StandardTray = op->StandardTray;
	np->ShiftBin = op->ShiftBin;
	np->MailBoxBin = op->MailBoxBin;
#endif /* GPS_REJECTION */

    cvtx = xres;
    cvty = yres;
    cvtw = pwidth;
    cvtl = plength;
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    set_edge2edge_custom = edge2edge;
#ifdef PCL_CUSTOM_EDGE2EDGE
	if(customEdge2Edge){
		pre_enter_lang_custom = enter_lang;
	}
#endif
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */
#endif /*Cutompaper disabled for now */
}

const PAPERINFO * PRpaperfirst(Sint32 code, int xres, int yres, int (*comp)())
{
    int nPapers;
    PAPERINFO * papers;

    nPapers = PRpapertable(&papers, xres, yres);
    curPaper = papers;
    endPaper = papers+nPapers;
    /*ASSERT(comp && curPaper);*/

    while (curPaper != endPaper) {
        if ((*comp)(code, curPaper) == TRUE)
            if (PrintSysGetPaperInfo(curPaper->OMcode))
            return curPaper ++;
        curPaper ++;
    }
    return (PAPERINFO *)NULL;       /* not found */
}

PAPERINFO * PRpaperinfoOriginal (PAPERCODE size, int xres, int yres)
{
	int i;
	PAPERINFO  *p,  *papers;

	i = PRpapertable(&papers, xres, yres);
#if 0 /*to be implemented for all paper sizes*/
	for (p = papers; i > 0; i--, p++) {
		/*ASSERT(p);*/
		if (p->OMcode == size) {
#ifdef LONG_EDGE_FEED
		/*	For these four sizes, we have matched pairs of entries in the table,
		 *	with the short-edge version preceeding the long-edge version, such that
		 *	when we have the first one in 'p', the second is implicitly at 'p+1'.
		 *	The option that we are interrogating is normally implemented, for Core
		 *	testing, by the "-L" command-line switch; for porting/customer purposes,
		 *	this may have to be modified.  (A long-edge version of A3, for example,
		 *	is quite unlikely in a typical printer.)
		 *
		 *	Because this OM call will lock a semaphore, it is inadvisable to call
		 *	PRpaperinfo() before the Options Manager has been initialized.
		 *	If this proves to be a problem, Core can replace the option with
		 *	a simple global flag; customers might need something more elaborate.
		 */
			  if (p->OMcode == PAPERSIZE_A4 && OMGetCurrentBool(LONGEDGEFEED, OMPRINTER))
			    return (p + 1);
			   else if (p->OMcode == PAPERSIZE_LETTER && OMGetCurrentBool(LONGEDGEFEED, OMPRINTER))
			    return (p + 1);
#endif
			return p;
		}
	}
	return NULL;
#else
if ((size == PAPERSIZE_A4) && OMGetCurrentBool(LONGEDGEFEED, OMPRINTER))
			    return (&papers);
			   else if ((size == PAPERSIZE_LETTER) && OMGetCurrentBool(LONGEDGEFEED, OMPRINTER))
			    return (&papers);
#endif 

               return (&papers);
}
