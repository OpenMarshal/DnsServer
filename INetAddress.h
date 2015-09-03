/* 
 * File:   INetAddress.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 13:48
 */

#ifndef INETADDRESS_H
#define	INETADDRESS_H

#include "ErrorManager.h"
#include "Sock.h"

class INetAddress
{
public:
    INetAddress(const char* ip, uint port)
        : size(sizeof(struct sockaddr_in)),
        port(port)
    {
        if(
        #if OS == WIN
            WSAStringToAddress(ip, AF_INET, NULL, (struct sockaddr*)&sock, &size)
        #endif
        #if OS == LINUX
            inet_pton(AF_INET, ip, &sock.sin_addr)
        #endif
                    != 0)
            error = getErrorNo();
        else
            error = 0;
        
        sock.sin_family = AF_INET;
        sock.sin_port = htons(port);
    }
    INetAddress(const char* ip) : INetAddress(ip, 0)
    { }
    
    INetAddress(uint port)
        : size(sizeof(struct sockaddr_in)),
        port(port)
    {
        sock.sin_family = AF_INET;
        sock.sin_addr.s_addr = INADDR_ANY;
        sock.sin_port = htons(port);
    }
    INetAddress() : INetAddress((uint)0)
    { }
    
    bool isErroneous()
    {
        return error != 0;
    }
    sint getError()
    {
        return error;
    }
    
    struct sockaddr_in toSockAddrIn()
    {
        return sock;
    }
    struct sockaddr_in* toPtrSockAddrIn()
    {
        return &sock;
    }
    struct sockaddr* toPtrSockAddr()
    {
        return (struct sockaddr*)&sock;
    }
    sint getLength()
    {
        return size;
    }
    uint* getPtrLength()
    {
        return (uint*)&size;
    }
    
    uint getPort()
    {
        return port;
    }
    
private:
    struct sockaddr_in sock;
    sint size;
    
    uint port;
    
    sint error;
};

#endif	/* INETADDRESS_H */

