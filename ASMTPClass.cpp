/*
**   Filename: ASMTPClass.c
**
**   Author: Troy E Bouchard (Wawa Kopa Saghalie - Talks to the Sky)
**   WKS Software.
**
**   DESC: C Module for Amiga SMTP C++ Class
**
**   C++ Class SMTP Send Mail Utility.
**
**   Requires the Miami SDK netincludes
**
**		File created 2005 - can't remember the exact date.
**
**       YOU CAN DO ANYTHING WITH THIS CODE THAT YOU WANT TO DO.  JUST REMEMBER,
**       TROY E BOUCHARD WILL BEAR ABSOLUTELY NO RESPONSIBILITY FOR THE USE, 
**       MISUSE, INABILITY TO USE OR INABLITY TO UNDERSTAND ANY OR ALL PARTS OF 
**       THIS CODE.  ENJOY IT IN GOOD HEALTH.                                   
*/

#include "ASMTPClass.h"

extern "C" {
#include <clib/socket_protos.h>
#include <proto/socket.h>
#include <proto/usergroup.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
}

/* I'm not sure what this is for.  I might have been doing some testing
** but I really don't remember
*/
extern int h_errno;

/* the extra letters added to the library commands
** are because I didn't want to get compile
** errors for duplicate commands from the 
** miami net.lib
*/
ASMTPSocket::ASMTPSocket()
{
   hSocket = SMTP_NO_SOCKET;
}

ASMTPSocket::~ASMTPSocket()
{
   CloseS();
}

BOOL ASMTPSocket::CreateS()
{
   hSocket = socket(AF_INET, SOCK_STREAM, 0);
   return (hSocket != SMTP_NO_SOCKET);
}

void ASMTPSocket::CloseS()
{
   if( hSocket != SMTP_NO_SOCKET )
   {
      shutdown(hSocket, 2);
      hSocket = SMTP_NO_SOCKET;
   }
}

BOOL ASMTPSocket::ConnectS(UBYTE SMTPHost, int Port)
{
   if(!(HostAddr = gethostbyname(SMTPHost)))
   {
      if(h_errno == TRY_AGAIN)
      {
	 printf("Unable to locate the SMTP Host!\n");
	 return 20;
      }
      else
      {
	 printf("The SMTP Host is invalid\n");
	 return 20;
      }
   }

   INetSocketAddr.sin_len    = sizeof(INetSocketAddr);
   INetSocketAddr.sin_family = AF_INET;
   INetSocketAddr.sin_port   = Port;
   INetSocketAddr.sin_addr.s_addr = 0;

   memcpy(&INetSocketAddr.sin_addr, HostAddr->h_addr, HostAddr->h_length);

   hSocket = socket(HostAddr->h_addrtype, SOCK_STREAM,0);
   if( hSocket == SMTP_NO_SOCKET )
   {
      printf("Socket allocation failed.\n");
      return 20;
   }

   if(connect(hSocket, (struct sockaddr *) &INetSocketAddr, sizeof(INetSocketAddr)) == SMTP_NO_SOCKET)
   {
      printf("Connect Failed!\n");
      return 20;
   }

   printf("Connected to %s\n'", SMTPHost);

   return ConnectS( (struct sockaddr *)&INetSocketAddr, sizeof(INetSocketAddr));
}

BOOL ASMTPSocket::ConnectS( (struct sockaddr *) aSockAddr, int SockAddrLen)
{
   return (connect(hSocket, aSockAddr, SockAddrLen) != SMTP_NO_SOCKET);
}
