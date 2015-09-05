/* 
 * File:   Sock.h
 * Author: pandora
 *
 * Created on September 3, 2015, 6:08 PM
 */

#ifndef SOCK_H
#define	SOCK_H

#include "GlobalHeader.h"

#ifdef	__cplusplus
extern "C" {
#endif

#if OS == WIN
    #include <winsock2.h>
    #include <io.h>
#endif
#if OS == LINUX
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* SOCK_H */

