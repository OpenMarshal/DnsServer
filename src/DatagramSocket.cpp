#include "DatagramSocket.h"
#include "ErrorManager.h"
#include "Sock.h"


DatagramSocket::DatagramSocket(INetAddress addr, int timeout)
{
    this->addr = addr;

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1)
    {
        error = getErrorNo();
        errorLocation = 0;
        return;
    }
    
	if(timeout > 0)
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    if(bind(sock, addr.toPtrSockAddr(), addr.getLength()) == -1)
    {
        error = getErrorNo();
        errorLocation = 1;
        return;
    }
}

DatagramSocket::DatagramSocket(INetAddress addr) : DatagramSocket(addr, 0)
{ }

DatagramSocket::DatagramSocket(int timeout) : DatagramSocket(INetAddress(), timeout)
{ }

DatagramSocket::DatagramSocket() : DatagramSocket(INetAddress())
{ }

void DatagramSocket::receive(Datagram* dtg) const
{
    INetAddress* addr = dtg->getPtrINetAddress();

#if OS == WIN
    dtg->len = recvfrom(sock, dtg->data, dtg->maxLen, 0, addr->toPtrSockAddr(), (int*)addr->getPtrLength());
#elif OS == LINUX
    dtg->len = recvfrom(sock, dtg->data, dtg->maxLen, 0, addr->toPtrSockAddr(), addr->getPtrLength());
#endif
    if(dtg->len < 0)
        dtg->error = getErrorNo();
}
Datagram* DatagramSocket::receive(uint dataLen) const
{
    Datagram* dtg = new Datagram();
    dtg->data = new char[dataLen];
    dtg->maxLen = dataLen;
    dtg->homemadeData = true;

    receive(dtg);

    return dtg;
}

uint DatagramSocket::send(Datagram* dtg) const
{
    return this->send(dtg, dtg->getINetAddress());
}
uint DatagramSocket::send(const Datagram* dtg, INetAddress dest) const
{
    return this->send(dtg->data, dtg->len, dest.toPtrSockAddr(), dest.getLength());
}
uint DatagramSocket::send(char* data, uint len, INetAddress dest) const
{
    return this->send(data, len, dest.toPtrSockAddr(), dest.getLength());
}
uint DatagramSocket::send(char* data, uint len, struct sockaddr* addr, uint addrLen) const
{
    if(sendto(sock, data, len, 0, addr, addrLen) < 0)
        return getErrorNo();
    else
        return 0;
}