/*
 * Wipro Technologies, Bangalore
 * Logic to read the the data from gps_host input buffer instead of reading from * file or from socket
 */

/*! \file
 *  \ingroup PMS
 *  \brief Input Buffer.
 *
 */

#ifdef WIN32
#include <windows.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#elif defined(UNIX) || defined(MACOSX)
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define MAX_PATH PATH_MAX
#elif defined(THREADX)
#include <rtipapi.h>
#else /* vxworks */
#include <vxWorks.h>
#include <sockLib.h>
#include <inetLib.h>
#include <taskLib.h>
#include <stdioLib.h>
#include <strLib.h>
#include <ioLib.h>
#include <fioLib.h>
#include <hostLib.h>
#endif
#include <stdio.h>

#ifdef PMS_SUPPORT_BUFFER
#include <pms_input_buffer.h>
#endif

#include "pms.h"
#include "pms_malloc.h"
#include "pms_platform.h"
#include "oil_entry.h"
#include "pms_input_manager.h"
#include "pms_thread.h"
#include "gps/host.h"

#ifdef PMS_SUPPORT_BUFFER
#include <pms_input_buffer.h>
char *dataInBuffer;
#endif

extern int job_hostid_in;
extern int job_hostid_out;
/* static gps_hostbuf_t	gps_hostbuffer;		host buffer.	*/		
gps_hostbuf_p host_inBuff, host_outBuff;

extern gwmsg_client_t *gps_client;
extern int g_jobAvailable;

extern gps_hostbuf_p GPS_SinOpen(gwmsg_client_t *, int);
extern gps_hostbuf_p GPS_SoutOpen(gwmsg_client_t *, int);

/* Just initialize the module */
int Input_Buffer_Initialize() {
  return TRUE;
}

/* Just finialize the module */
int Input_Buffer_Finalize() {
  return TRUE;
}

/**
 * \brief Wrapper for init input buffer
 *
 */
int Input_Buffer_InitDataStream(void)
{
  return TRUE;
}

/**
 * \brief Wrapper for open input buffer
 *
 */
int Input_Buffer_OpenDataStream(void)
{
  
    dataInBuffer = NULL;
     /*************Call to gpsSinOpen*************************************************/
    if (host_inBuff == NULL)
      host_inBuff = GPS_SinOpen(gps_client,job_hostid_in);
	if(host_inBuff)
	{
		printf("GPS_SinOpen : Successful\n");
	}
	else
	{
		printf("GPS_SinOpen : Failed\n");
	}
    PMS_Delay(200);	
	if(host_inBuff)
	{
		printf("GPS_SinOpen : host_inBuff Successful\n");
        if(host_inBuff->_HostBuf)
        dataInBuffer = host_inBuff->_HostBuf->buf;
	}

  /*************Call to gpsSoutOpen*************************************************/
    if (host_outBuff == NULL)
      host_outBuff = GPS_SoutOpen(gps_client,job_hostid_out);
    if(host_outBuff)
	{
		printf("GPS_SoutOpen : Successful\n");
	}
	else
	{
		printf("GPS_SoutOpen : Failed\n");
	}
	
    if(host_inBuff)
    {
      return TRUE;
    }
  return FALSE;
}
 
/**
 * \brief Wrapper for closing input buffer
 *
 */
int Input_Buffer_CloseDataStream(void)
{
  g_jobAvailable = 0;
  return TRUE;
}

/**
 * \brief Wrapper for peek input buffer
 *
 */
int Input_Buffer_PeekDataStream(unsigned char * buffer, int nBytesToRead)
{


	return (gpsSinPeek(host_inBuff, buffer, nBytesToRead, 0));
}

/**
 * \brief Wrapper for consume input socket function
 *
 */
int Input_Buffer_ConsumeDataStream(int nBytesToConsume)
{
  if(gpsSinSeek(host_inBuff, nBytesToConsume) != 0)
  {
	printf("gpsSinSeek() Failed..\n");
	return 0;
  }


  return (nBytesToConsume);
}

