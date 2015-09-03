/* 
 * File:   main.cpp
 * Author: Adrien Castex
 *
 * Created on 31 août 2015, 15:35
 */

#include "GlobalHeader.h"
#include "EntryFilter.h"
#include "DatagramSocket.h"
#include "INetAddress.h"
#include "ExString.h"

#include <fstream>






EntryFilter* loadEntryFilters();
void received(char* data, boolean blocked);

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if(error != 0)
    {
        debug("WSAStartup error : %i\r\n", error);
        return -1;
    }
    
    INetAddress outaddr(DNS_SERVER_IP, DNS_SERVER_PORT);
    INetAddress inaddr(53);
    
    DatagramSocket in_ds(inaddr);
    if(in_ds.isErroneous())
    {
        debug("in_ds error : %i %i %i\r\n", in_ds.isErroneous(), in_ds.getError(), in_ds.isErrorOnBinding(), in_ds.isErrorOnSocketCreation());
        return -1;
    }
    
    DatagramSocket out_ds;
    if(out_ds.isErroneous())
    {
        debug("out_ds error : %i %i %i\r\n", out_ds.getError(), out_ds.isErrorOnBinding(), out_ds.isErrorOnSocketCreation());
        return -1;
    }
    
    EntryFilter* filters = loadEntryFilters();
    
    char data[500];
    Datagram* dtg_in = new Datagram(data, 500);
    Datagram* dtg_out = new Datagram(data, 500);
    
    debug("Started\r\n");
    
    for(;;)
    {
        in_ds.receive(dtg_in);
        debug("in_ds.receive : %i %i\r\n", dtg_in->isErroneous(), dtg_in->getError());
        
        char* str = dtg_in->getData() + 13;
        
        if(filters == 0 || !filters->matches(str))
        { // Not Blocked
            error = out_ds.send(dtg_in, outaddr);
            debug("out_ds.send : %i\r\n", error);

            out_ds.receive(dtg_out);
            debug("out_ds.receive : %i %i\r\n", dtg_out->isErroneous(), dtg_out->getError());

            error = in_ds.send(dtg_out, dtg_in->getINetAddress());
            debug("in_ds.send : %i\r\n", error);
            
            received(str, false);
        }
        else
        { // Blocked
            char* data = dtg_in->getData();
            
            data[2] = 0;
            data[3] = 0;
            data[6] = 0;
            data[7] = 0;
            
            error = in_ds.send(dtg_in, dtg_in->getINetAddress());
            debug("in_ds.send : %i\r\n", error);
            
            received(str, true);
        }
    }
    
    dtg_in->dispose();
    dtg_out->dispose();
        
    return 0;
}


EntryFilter* loadEntryFilters()
{
    std::ifstream infile("filters.txt");
    
    if(!infile.good())
        return 0;
    
    EntryFilter* ef = 0;
    
    std::string line;
    while (std::getline(infile, line))
    {
        line = trim(line);
        if(line.length() == 0)
            continue;
        
        int comment = line.find('#');
        
        if(comment == 0)
            continue;
        
        line = line.substr(0, comment);
        line = trim(line);
        
        EntryFilter* wef = new EntryFilter(line.c_str(), 0, line.length());
        
        if(ef == 0)
            ef = wef;
        else
            ef = ef->setNextEntry(wef);
    }
    
    return ef;
}

void received(char* data, boolean blocked)
{
    if(blocked)
        printf(" >X> %s [BLOCKED]\r\n", data);
    else
        printf(" >>> %s\r\n", data);
    
    _flushall();
}
