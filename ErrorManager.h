/* 
 * File:   ErrorManager.h
 * Author: pandora
 *
 * Created on September 3, 2015, 6:28 PM
 */

#ifndef ERRORMANAGER_H
#define	ERRORMANAGER_H

#include "GlobalHeader.h"

#if OS == WIN
    #include <winsock2.h>
#endif
#if OS == LINUX
    #include <errno.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

sint getErrorNo()
{
    #if OS == WIN
        return WSAGetLastError();
    #endif
    #if OS == LINUX
        return errno;
    #endif
}


#ifdef	__cplusplus
}
#endif

#endif	/* ERRORMANAGER_H */

