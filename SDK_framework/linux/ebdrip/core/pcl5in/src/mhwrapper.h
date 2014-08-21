/**\file
 * \in group pcl5in
 * Contains wrapper declarations to update media attributes
 */

#include "core.h"
#include "pcl.h"
#include "mm.h"
#include "pcl5.h"
#include "pcl5context.h"
#include "pagecontrol.h"
#include "jobcontrol.h"
#include "mh.h"

void SetMediaType(Uint32 media);
int GetMediaType();
Uint32 GetPaperSource();
Uint32 GetPageSize();
void SetPageSize();
Uint32 GetCustomPageWidth();
Uint32 GetCustomPageHeight();
Uint32 GetPageWidth();
Uint32 GetPageHeight();
Uint32 GetOrientation();
int32 GetQualityMode();
int getMhPageSize();
int getMhMediaType();
void SetPaperSource(int tray);
int getMhPaperSource(); 
