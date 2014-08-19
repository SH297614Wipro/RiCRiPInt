/* Copyright (C) 2005-2013 Global Graphics Software Ltd. All rights reserved.
 *
 * This example is provided on an "as is" basis and without
 * warranty of any kind. Global Graphics Software Ltd. does not
 * warrant or make any representations regarding the use or results
 * of use of this example.
 *
 * $HopeName: SWebd_OIL_example_gg!src:gwid_eventhandle.h(EBDSDK_P.1) $
 *
 */
/*! \file
 *  \ingroup OIL
 *  \brief Implementation of the event handling functions.
 *
 * This file contains the definitions of the functions which does event handling 
 * for registered events that occurs in GPS.
 *
 */

/**
 * \brief  this function is a common Event handler for all GPS events
 *
 * GPS events
 */
#ifndef _GWID_EVENTHANDLER_H_
#define _GWID_EVENTHANDLER_H_

#include "gw_gps.h"
#include "oil.h"
#include <stdio.h>
#include "gpssim.h"

#define	DI_ENV_VAR_ID_COPIES			1
#define	PENV_HANDLER	                5	

typedef int Bool;
/* extern variables */
extern OIL_TyJob *g_pstCurrentJob;
extern OIL_TySystem g_SystemState;

int GWID_Event_Handler(void *cl, gwmsg_t *m);
//int   Get_Data_From_GPS(int hostid_in,int hostid_out, int jobid );

void Get_Env_var_From_GPS(OIL_TyJob *pstJob);

int       gpsJobId, gpsPDLType;
static gwmsg_GpsEv_Req_Proc_Data_t *processJobData;
int  plotID, frameID;
//int job_pdlid;
int current_pdlid;
extern int PlotSet_plotid;
#endif /* _GWID_EVENTHANDLER_H_
*/
