#include "INetAddress.h"
#include "ErrorManager.h"


INetAddress::INetAddress(char* ip, uint port)
    : size(sizeof(struct sockaddr_in)),
    port(port)
{
    if(
    #if OS == WIN
        WSAStringToAddress(ip, AF_INET, NULL, (struct sockaddr*)&sock, &size)
    #elif OS == LINUX
        inet_pton(AF_INET, ip, &sock.sin_addr)
    #endif
                != 0)
        error = getErrorNo();
    else
        error = 0;

    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
}

INetAddress::INetAddress(char* ip) : INetAddress(ip, 0)
{ }

INetAddress::INetAddress(uint port)
    : size(sizeof(struct sockaddr_in)),
    port(port)
{
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = INADDR_ANY;
    sock.sin_port = htons(port);
}

INetAddress::INetAddress() : INetAddress((uint)0)
{ }