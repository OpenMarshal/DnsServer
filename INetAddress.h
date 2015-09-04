/* 
 * File:   INetAddress.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 13:48
 */

#ifndef INETADDRESS_H
#define	INETADDRESS_H

#include "Sock.h"

class INetAddress
{
public:
    INetAddress(char* ip, uint port);
    INetAddress(char* ip);
    
    INetAddress(uint port);
    INetAddress();
    
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

