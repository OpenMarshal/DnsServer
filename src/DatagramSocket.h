/* 
 * File:   DatagramSocket.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 12:39
 */

#ifndef DATAGRAMSOCKET_H
#define	DATAGRAMSOCKET_H

#include "INetAddress.h"
#include "Datagram.h"

class DatagramSocket
{
public:
	DatagramSocket(INetAddress addr, int timeout);
    DatagramSocket(INetAddress addr);
	DatagramSocket(int timeout);
    DatagramSocket();
    
    void receive(Datagram* dtg) const;
    Datagram* receive(uint dataLen) const;
    
    uint send(Datagram* dtg) const;
    uint send(const Datagram* dtg, INetAddress dest) const;
    uint send(char* data, uint len, struct sockaddr* addr, uint addrLen) const;
    uint send(char* data, uint len, INetAddress dest) const;
    
    bool isErroneous()
    {
        return error != 0;
    }
    bool isErrorOnBinding()
    {
        return errorLocation == 1;
    }
    bool isErrorOnSocketCreation()
    {
        return errorLocation == 0;
    }
    sint getError()
    {
        return error;
    }
    
    INetAddress getAddress()
    {
        return addr;
    }
    
private:
    sint error = 0;
    uint errorLocation;
    
    INetAddress addr;
    
    sint sock;
};


#endif	/* DATAGRAMSOCKET_H */

