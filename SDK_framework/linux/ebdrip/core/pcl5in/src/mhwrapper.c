/**file
 * in group pcl5in
 * Contains wrapper implementations to update media attributes
 */

#include "mhwrapper.h"
#include "pcl5context.h"
PCL5Context *pcl5_ctxt;
Uint32 mediatype, pagesize, orientation, papersource, pagewidth, pagelength, custompagewidth, custompagelength;

static void CurrentContext()
{
    pcl5_ctxt = pcl5_current_context();
}

void SetMediaType(Uint32 media)
{
    mediatype = media;
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        page_ctrl_info->media_type = media;
    }
    
}
void SetPaperSource(int tray)
{
    papersource = tray;
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        page_ctrl_info->paper_source = tray;
    }
}
int GetMediaType()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        return page_ctrl_info->media_type;
    }
    else
    {
        return 0; /*media type plain*/
    }
}

OMenum GetPaperSource()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        papersource = page_ctrl_info->paper_source;
        return page_ctrl_info->paper_source;
    }
    else
    {
        return 7; /*tray auto*/
    }        
}

Uint32 GetPageSize()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        return page_ctrl_info->page_size;
    }
    else 
    {
        return (26); /*A4 papersize*/
    }
}

void SetPageSize(int size)
{
    pagesize = size;
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        page_ctrl_info->page_size = size;
    }
}

Uint32 GetCustomPageWidth()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        return page_ctrl_info->custom_page_width;
    }    
    else 
    {
        return DEFAULT_PAGE_WIDTH;
    }
}

Uint32 GetCustomPageHeight()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        return page_ctrl_info->custom_page_length;
    }
    else
    {
        return DEFAULT_PAGE_LENGTH;
    }
}

Uint32 GetPageWidth()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        return page_ctrl_info->page_width;
    }
    else
    {
        return DEFAULT_PAGE_WIDTH;
    }
}

Uint32 GetPageHeight()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        return  page_ctrl_info->page_length;
    }
    else
    {
        return DEFAULT_PAGE_LENGTH;
    }

}

Uint32 GetBinding()
{
    CurrentContext();
    JobCtrlInfo *job_ctrl_info = NULL;
    job_ctrl_info = get_job_ctrl_info(pcl5_ctxt);
    if(job_ctrl_info != NULL)
    {
	    return job_ctrl_info->binding;
    }
    else 
    {
         return 0; /* simplex*/
    }
}

Uint32 GetDuplex()
{
    CurrentContext();
    JobCtrlInfo *job_ctrl_info = NULL;
    job_ctrl_info = get_job_ctrl_info(pcl5_ctxt);
    if(job_ctrl_info != NULL)
    {
	    return job_ctrl_info->duplex;
    }
    else 
    {
        return 0; /*simplex binding*/
    }
}

int32 GetOrientation()
{
    CurrentContext();
    PageCtrlInfo *page_ctrl_info = NULL;
    page_ctrl_info = get_page_ctrl_info(pcl5_ctxt);
    if(page_ctrl_info != NULL)
    {
        return page_ctrl_info->orientation;
    }
    else
    {
        return 0; /*default portrait*/
    }
}

int32 GetQualityMode()
{
  return 0;
}

int getMhPageSize()
{
    return pagesize;

}
int getMhMediaType()
{
    return mediatype;

}
int getMhPaperSource()
{
    return papersource;
}
