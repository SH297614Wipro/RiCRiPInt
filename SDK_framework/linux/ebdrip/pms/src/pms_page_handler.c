/* Copyright (C) 2007-2012 Global Graphics Software Ltd. All rights reserved.
 *
 * This example is provided on an "as is" basis and without
 * warranty of any kind. Global Graphics Software Ltd. does not
 * warrant or make any representations regarding the use or results
 * of use of this example.
 *
 * $HopeName: GGEpms_gg_example!src:pms_page_handler.c(EBDSDK_P.1) $
 *
 */

/*! \file
 *  \ingroup PMS
 *  \brief Page Handler.
 *
 */

#include "pms.h"
#include "pms_page_handler.h"
#include "oil_entry.h"
#include "pms_platform.h"
#include "pms_malloc.h"
#ifdef PMS_SUPPORT_TIFF_OUT
#include "pms_tiff_out.h"
#endif
#ifdef PMS_SUPPORT_PDF_OUT
#include "pms_pdf_out.h"
#endif
#include "pms_thread.h"
#ifndef VXWORKS
#ifndef THREADX
#include <memory.h> /* for memset */
#endif
#endif
#ifdef PMS_OIL_MERGE_DISABLE
PMS_TyPage *g_pstCurrentPMSPage;
#else
OIL_TyPage *g_pstCurrentPMSPage;
#endif

/**
 * \brief Append the checked-in Page to PMS's page queue.
 *
 * Append the checked-in Page into PMS's page queue (g_pstPageList).\n
 */
#ifdef PMS_OIL_MERGE_DISABLE
void AppendToPageQueue(PMS_TyPage *ptPMSPage)
#else
void AppendToPageQueue(OIL_TyPage *ptPMSPage)
#endif
{
  PMS_TyPageList **pstLastNode, *pstNewNode;

  ptPMSPage->eState = PMS_CHECKEDIN;

  pstNewNode = (PMS_TyPageList*)OSMalloc(sizeof(PMS_TyPageList),PMS_MemoryPoolPMS);
  while(!pstNewNode)
  {
    if(g_nPageCount == 0)
    {
      PMS_SHOW_ERROR("**LACK OF MEMORY ERROR, no page can be checked in!\n");
      /* need some error handling */
      break;
    }
    else
    {
      PMS_SHOW_ERROR("Page Buffer Full, wait until a page is printed out!\n");
      PMS_WaitOnSemaphore_Forever(g_semCheckin);
    }
    pstNewNode = (PMS_TyPageList*)OSMalloc(sizeof(PMS_TyPageList),PMS_MemoryPoolPMS);
  }

  if(g_tSystemInfo.uUseEngineSimulator)
  {
    if(g_nPageCount > MAX_PAGE_IN_PAGEBUFFER)
      PMS_WaitOnSemaphore_Forever(g_semCheckin);
  }

  if(pstNewNode != NULL)
  {
    pstNewNode->pPage = ptPMSPage;
    pstNewNode->pNext = NULL;

    /*CRITICAL SECTION - START*/
    PMS_EnterCriticalSection(g_csPageList);

    pstLastNode = &g_pstPageList;
    while(*pstLastNode != NULL)
      pstLastNode = &(*pstLastNode)->pNext;

    *pstLastNode = pstNewNode;
    g_nPageCount++;

    PMS_LeaveCriticalSection(g_csPageList);
    /*CRITICAL SECTION - END*/
    PMS_IncrementSemaphore(g_semPageQueue);
  }
  else
  {
    PMS_SHOW_ERROR(" ***ASSERT*** AppendToPageQueue: Failed to allocate %lu bytes \n", (unsigned long) sizeof(PMS_TyPageList));
  }
}

/**
 * \brief Shuffle the pages in PMS's page queue.
 *
 * Shuffle the pages in PMS's page queue(g_pstPageList).\n
 */
void ShufflePageList()
{
  PMS_TyPageList *pstOddPageHolder, *pstEvenPageHolder;
#ifdef PMS_OIL_MERGE_DISABLE
  PMS_TyPage *pstTemp;
#else
  OIL_TyPage *pstTemp;
#endif
  int nPagesToSwap, i;

  nPagesToSwap = g_nPageCount - (g_nPageCount%2);

  pstOddPageHolder = g_pstPageList;
  for (i=0; i < nPagesToSwap; i=i+2)
  {
    pstTemp = pstOddPageHolder->pPage;
    pstEvenPageHolder = pstOddPageHolder->pNext;
    pstOddPageHolder->pPage = pstEvenPageHolder ->pPage;
    pstEvenPageHolder ->pPage = pstTemp;
    pstOddPageHolder = pstEvenPageHolder->pNext;
  }
}

/**
 * \brief Print all the pages form PMS's page queue.
 *
 * Print all the pages form PMS's page queue(g_pstPageList).\n
 */
void PrintPageList()
{
/*  while(g_pstPageList != NULL)
  {
    PrintPage(g_pstPageList->pPage);
    OIL_PageDone(g_pstPageList->pPage);
      pstPageNode = pstPageNode->pNext;
    RemovePage(g_pstPageList->pPage);
  }
  */
}

/**
 * \brief Create a PMS style plane of empty data .
 *
 * The specified colorant has a plane of blank data created and inserted into the supplied
 * PMSPage.  The last parameter is a sample PMS plane structure that has a template for the
 * plane and band data - all planes must contain the same number of bands with the same band sizes)
 *
 */
#ifdef PMS_OIL_MERGE_DISABLE
void CreatePMSBlankPlane(PMS_TyPage *ptPMSPage, PMS_eColourant eColorant, PMS_TyPlane *ptPMSSamplePlane)
{
    unsigned int  size, i;
	unsigned char *ptBuffer;
	int plane;
	
	/* determine which plane we want to create */
	switch(eColorant)
	{
	case PMS_RED:
	case PMS_CYAN:
	  plane = 0;
	  break;
	case PMS_GREEN:
	case PMS_MAGENTA:
	  plane = 1;
	  break;
	case PMS_BLUE:
	case PMS_YELLOW:
	  plane = 2;
	  break;
	case PMS_BLACK:
	  plane = 3;
	  break;
	default:
	  PMS_SHOW_ERROR("CreatePMSBlankPage: Invalid colorant input parameter");
	  return;
	  break;
	}
#else
void CreatePMSBlankPlane(OIL_TyPage *ptPMSPage, OIL_eColorant eColorant, OIL_TyPlane *ptPMSSamplePlane)
{
  unsigned int  size, i;
  unsigned char *ptBuffer;
  int plane;

  /* determine which plane we want to create */
  switch(eColorant)
  {
  case OIL_Red:
  case OIL_Cyan:
    plane = 0;
    break;
  case OIL_Green:
  case OIL_Magenta:
    plane = 1;
    break;
  case OIL_Blue:
  case OIL_Yellow:
    plane = 2;
    break;
  case OIL_Black:
    plane = 3;
    break;
  default:
    PMS_SHOW_ERROR("CreatePMSBlankPage: Invalid colorant input parameter");
    return;
    break;
  }
#endif

  for (i=0; i<ptPMSSamplePlane->uBandTotal; i++)
  {
    /* create the band buffer data */
    size = ptPMSSamplePlane->atBand[i].cbBandSize;
#ifdef PMS_OIL_MERGE_DISABLE_MEM
    ptBuffer = OSMalloc(size, PMS_MemoryPoolPMS);
#else
    ptBuffer = malloc(size);
#endif
    PMS_ASSERT(ptBuffer!=NULL, ("CreatePMSBlankPlane: Failed to allocate %d bytes \n", size));
    if(ptPMSPage->eColorantFamily == PMS_ColorantFamily_RGB)
    {
      /* For white RGB must be all 1s */
      memset(ptBuffer, 0xFF, size);
    }
    else
    {
      /* For white CMYK must be all 0s */
      memset(ptBuffer, 0x00, size);
    }

    /* fill out the band data */
    ptPMSPage->atPlane[plane].atBand[i].pBandRaster = ptBuffer;
    ptPMSPage->atPlane[plane].atBand[i].uBandHeight = ptPMSSamplePlane->atBand[i].uBandHeight;
    ptPMSPage->atPlane[plane].atBand[i].uBandNumber = ptPMSSamplePlane->atBand[i].uBandNumber;
    ptPMSPage->atPlane[plane].atBand[i].cbBandSize = ptPMSSamplePlane->atBand[i].cbBandSize;
  }

  /* fill out the plane data */
  ptPMSPage->atPlane[plane].ePlaneColorant = eColorant;
  ptPMSPage->atPlane[plane].uBandTotal = ptPMSSamplePlane->uBandTotal;
  ptPMSPage->atPlane[plane].bBlankPlane = TRUE;

  /* uTotalPlanes contains the number of valid planes.
     If we are creating planes outside the RIP we need to increment the count
     so that PMS has the correct number of planes */
#ifdef PMS_OIL_MERGE_DISABLE
  ptPMSPage->uTotalPlanes++;
#else
  ptPMSPage->nColorants++;
#endif
}

#ifdef PMS_OIL_MERGE_DISABLE
void Detect_and_Fill_Blank_Planes(PMS_TyPage * pstPageToPrint)
{
  int i, SamplePlaneCreated=FALSE;
  PMS_TyPlane *ptPMSSamplePlane = NULL;

  /* non-blank page with at least 1 valid plane */
  /* if RIP has not rendered all channels then we need to create empty planes */
  if (pstPageToPrint->uTotalPlanes != (unsigned int)PMS_MAX_VALID_PLANES_COUNT(pstPageToPrint->eColorantFamily))
#else
void Detect_and_Fill_Blank_Planes(OIL_TyPage * pstPageToPrint)
{
  int i, SamplePlaneCreated=FALSE;
  OIL_TyPlane *ptPMSSamplePlane = NULL;

  /* non-blank page with at least 1 valid plane */
  /* if RIP has not rendered all channels then we need to create empty planes */
  if (pstPageToPrint->nColorants != (unsigned int)PMS_MAX_VALID_PLANES_COUNT(pstPageToPrint->eColorantFamily))
#endif
  {
    /* find a valid plane data that can be used as a sample for the blank planes */
    for(i=0; i< PMS_MAX_VALID_PLANES_COUNT(pstPageToPrint->eColorantFamily); i++)
    {
      if (pstPageToPrint->atPlane[i].uBandTotal > 0)
      {
        ptPMSSamplePlane = &(pstPageToPrint->atPlane[i]);
        break;
      }
    }
   if(!ptPMSSamplePlane)
    {
      int samplebandsize = 81;  /* pick a typical band size */

      /* no valid plane found. Must be a completely blank page. lets create our own bands */
      /* BandWidth is width in bits, regardless of output mode. */
#ifdef PMS_OIL_MERGE_DISABLE
#ifdef PMS_OIL_MERGE_DISABLE_MEM
      ptPMSSamplePlane = (PMS_TyPlane*)OSMalloc(sizeof(PMS_TyPlane), PMS_MemoryPoolPMS);
#else
      ptPMSSamplePlane = (PMS_TyPlane*)malloc(sizeof(PMS_TyPlane));
#endif
#else
#ifdef PMS_OIL_MERGE_DISABLE_MEM
	  ptPMSSamplePlane = (OIL_TyPlane*)OSMalloc(sizeof(OIL_TyPlane), PMS_MemoryPoolPMS);
#else
      ptPMSSamplePlane = (OIL_TyPlane*)malloc(sizeof(OIL_TyPlane));
#endif
#endif

      if(!ptPMSSamplePlane)
      {
        PMS_SHOW_ERROR("\n**** PMS Page Handler: Failed to create sample plane for blank page **** \n\n");
        return;
      }

      /* create the sample blank page of bands */
      ptPMSSamplePlane->uBandTotal = (pstPageToPrint->nPageHeightPixels/samplebandsize) ;
      for (i=0; i<(int)ptPMSSamplePlane->uBandTotal; i++)
      {
          ptPMSSamplePlane->atBand[i].uBandHeight = samplebandsize;
          ptPMSSamplePlane->atBand[i].uBandNumber = i;
#ifdef PMS_OIL_MERGE_DISABLE
          ptPMSSamplePlane->atBand[i].cbBandSize = (pstPageToPrint->nRasterWidthBits >> 3) * ptPMSSamplePlane->atBand[i].uBandHeight;
#else
          ptPMSSamplePlane->atBand[i].cbBandSize = (pstPageToPrint->nRasterWidthData >> 3) * ptPMSSamplePlane->atBand[i].uBandHeight;
#endif
      }
      ptPMSSamplePlane->uBandTotal = i;

      /* reminder band if required */
      if (pstPageToPrint->nPageHeightPixels%samplebandsize != 0)
      {
        ptPMSSamplePlane->atBand[i].uBandHeight = pstPageToPrint->nPageHeightPixels%samplebandsize ;
        ptPMSSamplePlane->atBand[i].uBandNumber = i ;
#ifdef PMS_OIL_MERGE_DISABLE
        ptPMSSamplePlane->atBand[i].cbBandSize = (pstPageToPrint->nRasterWidthBits >> 3) * ptPMSSamplePlane->atBand[i].uBandHeight;
#else
        ptPMSSamplePlane->atBand[i].cbBandSize = (pstPageToPrint->nRasterWidthData >> 3) * ptPMSSamplePlane->atBand[i].uBandHeight;
#endif
        ptPMSSamplePlane->uBandTotal++ ;
      }
      SamplePlaneCreated = TRUE;
    }

    if (pstPageToPrint->eColorantFamily == PMS_ColorantFamily_RGB)
    {
      if (pstPageToPrint->atPlane[0].uBandTotal == 0)
      {
      #ifdef PMS_OIL_MERGE_DISABLE
        CreatePMSBlankPlane(pstPageToPrint, PMS_RED, ptPMSSamplePlane);
	  #else
	    CreatePMSBlankPlane(pstPageToPrint, OIL_Red, ptPMSSamplePlane);
	  #endif
      }
      if (pstPageToPrint->atPlane[1].uBandTotal == 0)
      {
      #ifdef PMS_OIL_MERGE_DISABLE
        CreatePMSBlankPlane(pstPageToPrint, PMS_GREEN, ptPMSSamplePlane);
	  #else
	    CreatePMSBlankPlane(pstPageToPrint, OIL_Green, ptPMSSamplePlane);
	  #endif
      }
      if (pstPageToPrint->atPlane[2].uBandTotal == 0)
      {
      #ifdef PMS_OIL_MERGE_DISABLE
        CreatePMSBlankPlane(pstPageToPrint, PMS_BLUE, ptPMSSamplePlane);
	  #else
	    CreatePMSBlankPlane(pstPageToPrint, OIL_Blue, ptPMSSamplePlane);
	  #endif
      }
    }
    else if(pstPageToPrint->eColorantFamily == PMS_ColorantFamily_CMYK)/* CMYK page */
    {
      unsigned char bForceMono = FALSE;
      unsigned int bCyanOmitted, bMagentaOmitted, bYellowOmitted, bBlackOmitted;

      bCyanOmitted = ( pstPageToPrint->atPlane[0].uBandTotal == 0 );
      bMagentaOmitted = ( pstPageToPrint->atPlane[1].uBandTotal == 0 );
      bYellowOmitted = ( pstPageToPrint->atPlane[2].uBandTotal == 0 );
      bBlackOmitted = ( pstPageToPrint->atPlane[3].uBandTotal == 0 );

      /* if flag is set to do not output CMY if they are blank then skip creating blank color planes */
#ifdef PMS_OIL_MERGE_DISABLE
      if (pstPageToPrint->bForceMonoIfCMYblank)
      {
        if (bCyanOmitted && bMagentaOmitted && bYellowOmitted)
        {
          bForceMono = TRUE;
        }
      }

      if (!bForceMono)
      {
        if (bCyanOmitted)
        {
          CreatePMSBlankPlane(pstPageToPrint, PMS_CYAN, ptPMSSamplePlane);
        }
        if (bMagentaOmitted)
        {
          CreatePMSBlankPlane(pstPageToPrint, PMS_MAGENTA, ptPMSSamplePlane);
        }
        if (bYellowOmitted)
        {
          CreatePMSBlankPlane(pstPageToPrint, PMS_YELLOW, ptPMSSamplePlane);
        }
      }

      if (bBlackOmitted)
      {
        CreatePMSBlankPlane(pstPageToPrint, PMS_BLACK, ptPMSSamplePlane);
      }
    }
    else /* Gray page */
    {
      if (pstPageToPrint->atPlane[3].uBandTotal == 0)
      {
        CreatePMSBlankPlane(pstPageToPrint, PMS_BLACK, ptPMSSamplePlane);
      }
    }
#else
      if (pstPageToPrint->pstJob->bForceMonoIfCMYblank)
      {
        if (bCyanOmitted && bMagentaOmitted && bYellowOmitted)
        {
          bForceMono = TRUE;
        }
      }

      if (!bForceMono)
      {
        if (bCyanOmitted)
        {
          CreatePMSBlankPlane(pstPageToPrint, OIL_Cyan, ptPMSSamplePlane);
        }
        if (bMagentaOmitted)
        {
          CreatePMSBlankPlane(pstPageToPrint, OIL_Magenta, ptPMSSamplePlane);
        }
        if (bYellowOmitted)
        {
          CreatePMSBlankPlane(pstPageToPrint, OIL_Yellow, ptPMSSamplePlane);
        }
      }

      if (bBlackOmitted)
      {
        CreatePMSBlankPlane(pstPageToPrint, OIL_Black, ptPMSSamplePlane);
      }
    }
    else /* Gray page */
    {
      if (pstPageToPrint->atPlane[3].uBandTotal == 0)
      {
        CreatePMSBlankPlane(pstPageToPrint, OIL_Black, ptPMSSamplePlane);
      }
    }
#endif

    if(SamplePlaneCreated == TRUE && ptPMSSamplePlane != NULL)
    {
#ifdef PMS_OIL_MERGE_DISABLE_MEM
      OSFree(ptPMSSamplePlane, PMS_MemoryPoolPMS);
#else
      free(ptPMSSamplePlane);
#endif
    }
  }
}

/**
 * \brief Print the Page.
 *
 * Print the page pointed to by the Page structure (pstPageToPrint) which is passed as parameter.\n
 */
#ifdef PMS_OIL_MERGE_DISABLE
void PrintPage(PMS_TyPage * pstPageToPrint)
#else
void PrintPage(OIL_TyPage * pstPageToPrint)
#endif
{
  /* A zero pstPageToPrint indicates end of job */
  if(pstPageToPrint != NULL)
  {
#ifdef PMS_OIL_MERGE_DISABLE
    int nColorant, nBandNo, nSuccessFlag;
    /* example code for pulling bands from OIL */
    if(g_tSystemInfo.eBandDeliveryType == PMS_PULL_BAND)
    {
      for(nColorant=PMS_CYAN; nColorant < PMS_MAX_PLANES_COUNT; nColorant++)
      {
        /* Bands can be fetched from oil in any random order. This example fetches them in reverse order */
        for(nBandNo=pstPageToPrint->atPlane[nColorant].uBandTotal-1; nBandNo >= 0; nBandNo--)
        {
          PMS_TyBand tBand;
          /* Get band data from oil into tBand structure */
          nSuccessFlag = OIL_GetBandData(pstPageToPrint->JobId, pstPageToPrint->PageId, nColorant, nBandNo, &tBand);
          if(nSuccessFlag != TRUE)
          {
            PMS_SHOW_ERROR("\n**** Page Handler: Failed to get band data from OIL **** \n\n");
            return;
          }
          else
          {
            /* In this example we will fill the PMS_TyPage structure with the band data we got*/
            pstPageToPrint->atPlane[nColorant].atBand[nBandNo].uBandHeight = tBand.uBandHeight;
            pstPageToPrint->atPlane[nColorant].atBand[nBandNo].uBandNumber = tBand.uBandNumber;
            pstPageToPrint->atPlane[nColorant].atBand[nBandNo].pBandRaster = tBand.pBandRaster;
            pstPageToPrint->atPlane[nColorant].atBand[nBandNo].cbBandSize  = tBand.cbBandSize;
          }
        }
      }
    }
    else if((g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND || g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_SINGLE || g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_FRAME) && (g_tSystemInfo.uUseRIPAhead))
#else
    if((g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND || g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_SINGLE || g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_FRAME) && (g_tSystemInfo.uUseRIPAhead))
#endif
    {
      /* wait if this is running in PMS context */
      PMS_WaitOnSemaphore_Forever(g_semPageComplete);
    }

    if(g_tSystemInfo.eOutputType != PMS_NONE)
    {
#ifdef PMS_OIL_MERGE_DISABLE
      if (pstPageToPrint->eColorMode != PMS_RGB_PixelInterleaved) {
#else
      if (pstPageToPrint->pstJob->eColorMode != OIL_RGB_PixelInterleaved) {
#endif
        /* detect if any blank planes are present and fill them */
        Detect_and_Fill_Blank_Planes(pstPageToPrint);
      }
    }

    if(g_tSystemInfo.eOutputType == PMS_NONE)
    {
#ifdef PMS_OIL_MERGE_DISABLE
      PMS_SHOW("Output suppressed (Page %d): %s\n", pstPageToPrint->PageId, pstPageToPrint->szJobName);
#else
      PMS_SHOW("Output suppressed (Page %d): %s\n", pstPageToPrint->uPageNo, pstPageToPrint->pstJob->szJobName);
#endif
    }
  #ifdef PMS_SUPPORT_TIFF_OUT
    else if((g_tSystemInfo.eOutputType == PMS_TIFF) || (g_tSystemInfo.eOutputType == PMS_TIFF_SEP)
                                                      || (g_tSystemInfo.eOutputType == PMS_TIFF_VIEW))
    {
      TIFF_PageHandler(pstPageToPrint);
    }
  #endif
#ifdef PMS_OIL_MERGE_DISABLE
  #ifdef PMS_SUPPORT_PDF_OUT
    else if((g_tSystemInfo.eOutputType == PMS_PDF)|| (g_tSystemInfo.eOutputType == PMS_PDF_VIEW))
    {
      PDF_PageHandler(pstPageToPrint);
    }
  #endif
#endif
    else
    {
      PMS_SHOW_ERROR("\n**** Page Handler: OutputType %d is not supported. **** \n\n", g_tSystemInfo.eOutputType);
    }

    /* free the PMS memory allocated for the rasters in PMS page
       In non-direct band delivery model, all the memory allocated for band rasters belong to PMS*/
    if((g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND) ||
       (g_tSystemInfo.eBandDeliveryType == PMS_PUSH_BAND_DIRECT_SINGLE) ||
       g_tSystemInfo.bScanlineInterleave)
    {
      int i;
      unsigned int j;
      for(i=0; i < PMS_MAX_PLANES_COUNT; i++)
      {
        for(j=0; j < pstPageToPrint->atPlane[i].uBandTotal; j++)
        {
          if ( pstPageToPrint->atPlane[i].atBand[j].pBandRaster)
          {
            /* free the PMS memory allocated for each band of each plane */
#ifdef PMS_OIL_MERGE_DISABLE_MEM
            OSFree(pstPageToPrint->atPlane[i].atBand[j].pBandRaster, PMS_MemoryPoolPMS);
#else
            free(pstPageToPrint->atPlane[i].atBand[j].pBandRaster);
#endif
#ifndef PMS_OIL_MERGE_DISABLE
            pstPageToPrint->atPlane[i].atBand[j].pBandRaster = NULL;
#endif
          }
        }
      }
    }
    else
    {
      /* In page and band direct delivery model, only the band memory allocated in blank planes belong to PMS. We need to free them here*/
      int i;
      unsigned int j;
      for(i=0; i < PMS_MAX_PLANES_COUNT; i++)
      {
        if (pstPageToPrint->atPlane[i].bBlankPlane == TRUE) /* free only if its a blank plane */
        {
          for(j=0; j < pstPageToPrint->atPlane[i].uBandTotal; j++)
          {
            if (pstPageToPrint->atPlane[i].atBand[j].pBandRaster)
            {
              /* free the PMS memory allocated for each band of each blank plane */
              OSFree(pstPageToPrint->atPlane[i].atBand[j].pBandRaster, PMS_MemoryPoolPMS);
#ifndef PMS_OIL_MERGE_DISABLE
              pstPageToPrint->atPlane[i].atBand[j].pBandRaster = NULL;
#endif
            }
          }
        }
      }
    }
  } else { /* otherwise end of job */

    switch(g_tSystemInfo.eOutputType) 
    {
    default:
    case PMS_NONE:
      break;
#ifdef PMS_SUPPORT_TIFF_OUT
    case PMS_TIFF:
    case PMS_TIFF_SEP:
     /* \todo Implement multipage TIFFs
      TIFF_PageHandler(NULL);
      */
      break;
#endif
#ifdef PMS_SUPPORT_PDF_OUT
    case PMS_PDF:
     /* \todo Implement multipage PDFs
      \todo PDF_PageHandler(NULL);
      */
      break;
#endif
#ifdef PMS_SUPPORT_APEC_OUT
    case PMS_APEC:
      APEC_PageHandler(NULL);
      break;
#endif
    }
  }
}

/**
 * \brief Remove the Page from PMS's page queue.
 *
 * Remove the Page from PMS's page queue(g_pstPageList).\n
 */
#ifdef PMS_OIL_MERGE_DISABLE
void RemovePage(PMS_TyPage *pstPageToDelete)
#else
void RemovePage(OIL_TyPage *pstPageToDelete)
#endif
{
  PMS_TyPageList **ppstHead, *pstNodeToDelete;
  ppstHead = &g_pstPageList;

  while(*ppstHead)
  {
    pstNodeToDelete = *ppstHead;
    if(pstNodeToDelete->pPage == pstPageToDelete)
    {
      /*CRITICAL SECTION - START*/
      PMS_EnterCriticalSection(g_csPageList);

      *ppstHead = (*ppstHead)->pNext;
      PMS_IncrementSemaphore(g_semCheckin);

      g_nPageCount--;

      PMS_LeaveCriticalSection(g_csPageList);
      /*CRITICAL SECTION - END*/

      OSFree(pstNodeToDelete,PMS_MemoryPoolPMS);
      return;
    }
    *ppstHead = (*ppstHead)->pNext;
  }
}

/**
 * \brief Check if PMS's page queue contains any page which is in Printing state.
 *
 * Returns TRUE if any page in the PMS's page queue is in Printing state, else returns FALSE.\n
 */
int IsEngineIdle()
{
  PMS_TyPageList *pstPageNode;

  pstPageNode = g_pstPageList;
  while(pstPageNode != NULL)
  {
    if (pstPageNode->pPage->eState == PMS_PRINTING)
    {
      return FALSE;
    }
    pstPageNode = pstPageNode->pNext;
  }
  return TRUE;
}

