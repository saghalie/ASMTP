/*
**   Filename: ASMTPClass.h
**
**   Author: Troy E Bouchard (Wawa Kopa Saghalie - Talks to the Sky)
**   WKS Software.
**
**   DESC: H Module for Amiga SMTP C++ Class
**
**   Requires the Miami SDK netincludes
**
**		File create 2005 - can't remember the exact date.
**
**   C++ Class SMTP Send Mail Utility.
**
**       YOU CAN DO ANYTHING WITH THIS CODE THAT YOU WANT TO DO.  JUST REMEMBER,
**       TROY E BOUCHARD WILL BEAR ABSOLUTELY NO RESPONSIBILITY FOR THE USE, 
**       MISUSE, INABILITY TO USE OR INABLITY TO UNDERSTAND ANY OR ALL PARTS OF 
**       THIS CODE.  ENJOY IT IN GOOD HEALTH.                                   
*/

extern "C" {
/* System */
#include <exec/types.h> 	  // For GLOBAL, USHORT, UBYTE etc...
#include <clib/exec_protos.h>	  // Protos for OpenLibrary() etc...
#include <exec/memory.h>	  // For MEMF_PUBLIC etc...
#include <clib/alib_protos.h>	  // Protos for DoMethod().

#include <dos/dos.h>		  // For SYStem output.
#include <graphics/gfxmacros.h>   // For Graphics.
#include <workbench/workbench.h>  // For Workbench related.
#include <libraries/gadtools.h>   // For struct NewMenu and sundry.

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/intuition.h>

/* Prototypes */
#include <clib/dos_protos.h>
#include <clib/icon_protos.h>
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>
#include <clib/gadtools_protos.h>
#include <clib/utility_protos.h>
#include <clib/asl_protos.h>

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <time.h>
#include <sys/dir.h>
#include <dos/stdio.h>
#include <dos/dosextens.h>
}

#ifndef SMTP_RC_CODES
#define SMTP_RC_CODES

#define SMTP_NO_SOCKET	      -1
#define SMTP_STATUS_REPLY     211
#define SMTP_HELP_MESSAGE     214
#define SMTP_SERVICE_READY    220
#define SMTP_SERVICE_CLOSE    221
#define SMTP_OK 	      250
#define SMTP_OK_FORWARD       251
#define SMTP_SEND_MAIL	      354
#define SMTP_CRASH_CLOSE      421
#define SMTP_MBOX_BUSY	      450
#define SMTP_ABORT_FAILURE    451
#define SMTP_STORAGE_FULL     452
#define SMTP_BAD_CMD_SYNTAX   500
#define SMTP_BAD_PARM_SYNTAX  501
#define SMTP_UNKNOWN_CMD      502
#define SMTP_BAD_CMD_SEQ      503
#define SMTP_UNKNOWN_PARM     504
#define SMTP_UNKNOWN_MBOX     550
#define SMTP_FORWARD_TO       551
#define SMTP_STORAGE_IS_FULL  552
#define SMTP_BAD_MBOX_SYNTAX  553
#define SMTP_TX_FAILURE       554

#endif // SMTP_RC_CODES

#define USERID_LEN    16
#define USERNAME_LEN  64
#define HOSTNAME_LEN 256
#define CMDBUF_SIZE  512
#define DATBUF_SIZE 1024

struct hostent * HostAddr;

class ASMTPSocket
{
   public:
      ASMTPSocket();
      ~ASMTPSocket();

      BOOL CreateS();
      BOOL ConnectS(UBYTE HostAddr, int Port);
      void CloseS();

   protected:
      BOOL ConnectS( (struct sockaddr*) aSockAddr, int SockAddrLen);
      struct sockaddr_in INetSocketAddr;
      long hSocket;

//   private:
};
