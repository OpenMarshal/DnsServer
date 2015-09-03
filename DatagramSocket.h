/* 
 * File:   DatagramSocket.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 12:39
 */

#ifndef DATAGRAMSOCKET_H
#define	DATAGRAMSOCKET_H

#include "GlobalHeader.h"

#if OS == WIN
    #include <winsock2.h>
    #include <io.h>
#endif

#include "INetAddress.h"
#include "Datagram.h"

class DatagramSocket
{
public:
    DatagramSocket(INetAddress addr)
    {
        this->addr = addr;
        
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(sock == -1)
        {
            error = WSAGetLastError();
            errorLocation = 0;
            return;
        }
        
        if(bind(sock, addr.toPtrSockAddr(), addr.getLength()) == -1)
        {
            error = WSAGetLastError();
            errorLocation = 1;
            return;
        }
    }
    DatagramSocket() : DatagramSocket(INetAddress())
    { }
    
    void receive(Datagram* dtg) const
    {
        INetAddress* addr = dtg->getPtrINetAddress();
        
        dtg->len = recvfrom(sock, dtg->data, dtg->maxLen, 0, addr->toPtrSockAddr(), addr->getPtrLength());
        if(dtg->len < 0)
            dtg->error = WSAGetLastError();
    }
    Datagram* receive(uint dataLen) const
    {
        Datagram* dtg = new Datagram();
        dtg->data = new char[dataLen];
        dtg->maxLen = dataLen;
        dtg->homemadeData = true;
        
        receive(dtg);
        
        return dtg;
    }
    
    uint send(const Datagram* dtg, INetAddress dest) const
    {
        return send(dtg->data, dtg->len, dest.toPtrSockAddr(), dest.getLength());
    }
    uint send(Datagram* dtg) const
    {
        return send(dtg, dtg->getINetAddress());
    }
    uint send(char* data, uint len, struct sockaddr* addr, uint addrLen) const
    {
        if(sendto(sock, data, len, 0, addr, addrLen) <= 0)
            return WSAGetLastError();
        else
            return 0;
    }
    
    boolean isErroneous()
    {
        return error != 0;
    }
    boolean isErrorOnBinding()
    {
        return errorLocation == 0;
    }
    boolean isErrorOnSocketCreation()
    {
        return errorLocation == 1;
    }
    sint getError()
    {
        return error;
    }
    
private:
    sint error = 0;
    uint errorLocation;
    
    INetAddress addr;
    
    sint sock;
};


#endif	/* DATAGRAMSOCKET_H */

