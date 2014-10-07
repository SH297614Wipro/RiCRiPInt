/**file
 * in group pcl5in
 * Contains wrapper implementations to update media attributes
 */
#include "mhwrapper.h"
#include "pcl5context.h"

#define GPS_PRINT_MODE_NONE			(0)

PCL5Context *pcl5_ctxt;
int mediatype;
int pagesize;
int orientation;
int papersource;
int pagewidth;
int pagelength;
int custompagewidth;
int custompagelength;
int binding;
int duplex;

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
        return PMS_TYPE_PLAIN;
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
        return PMS_PCL5TRAY_AUTO;
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
        return PMS_PCL5_A4;
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
         return SHORT_EDGE;
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
}

int32 GetQualityMode()
{
    return GPS_PRINT_MODE_NONE;
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
