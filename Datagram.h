/* 
 * File:   Datagram.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 13:28
 */

#ifndef DATAGRAM_H
#define	DATAGRAM_H

#include "GlobalHeader.h"
#include "DatagramSocket.h"
#include "INetAddress.h"

class DatagramSocket;

class Datagram
{
public:
    Datagram()
        : homemadeData(false),
        addr()
    { }
    Datagram(char* data, uint maxLen)
        : homemadeData(false),
        addr(),
        data(data),
        maxLen(maxLen),
        len(0),
        error(0)
    { }
    Datagram(char* data, sint len, uint maxLen, sint error)
        : homemadeData(false),
        addr(),
        data(data),
        len(len),
        error(error),
        maxLen(maxLen)
    { }

    char* getData()
    {
        return data;
    }
    sint getLength()
    {
        return len;
    }
    uint getMaxLength()
    {
        return maxLen;
    }
    
    INetAddress getINetAddress()
    {
        return addr;
    }
    INetAddress* getPtrINetAddress()
    {
        return &addr;
    }

    char* getStrAddress()
    {
        return inet_ntoa(addr.toPtrSockAddrIn()->sin_addr);
    }
    struct in_addr getAddress()
    {
        return addr.toPtrSockAddrIn()->sin_addr;
    }
    ushort getPort()
    {
        return addr.toPtrSockAddrIn()->sin_port;
    }

    bool isErroneous()
    {
        return len == -1;
    }
    sint getError()
    {
        return error;
    }

    void dispose()
    {
        if(homemadeData)
            delete(data);
        delete(this);
    }

private:
    char* data;
    uint maxLen;
    sint len;
    sint error;
    
    bool homemadeData;

    INetAddress addr;
    
    
    friend class DatagramSocket;
};

#endif	/* DATAGRAM_H */

