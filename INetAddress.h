/* 
 * File:   INetAddress.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 13:48
 */

#ifndef INETADDRESS_H
#define	INETADDRESS_H

#if OS == WIN
    #include <winsock2.h>
    #include <io.h>
#endif

class INetAddress
{
public:
    INetAddress(LPWSTR ip, uint port)
        : size(sizeof(struct sockaddr_in)),
        port(port)
    {
        if(WSAStringToAddressW(ip, AF_INET, NULL, (LPSOCKADDR)&sock, &size) != 0)
            error = WSAGetLastError();
        else
            error = 0;
        
        sock.sin_port = htons(port);
    }
    INetAddress(LPWSTR ip) : INetAddress(ip, 0)
    { }
    
    INetAddress(uint port)
        : size(sizeof(struct sockaddr_in)),
        port(port)
    {
        sock.sin_family = AF_INET;
        sock.sin_addr.s_addr = htonl(INADDR_ANY);
        sock.sin_port = htons(port);
    }
    INetAddress() : INetAddress((uint)0)
    { }
    
    boolean isErroneous()
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
    int* getPtrLength()
    {
        return (int*)&size;
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

