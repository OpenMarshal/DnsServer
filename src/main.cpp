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
#include "Configuration.h"
#include "DNSCache.h"

#include <fstream>



EntryFilter* loadEntryFilters(const char* filepath);
void received(char* data, bool blocked);
void displayHelp();
int runtime(Configuration& config);


int main(int argc, char* argv[])
{
    Configuration config(argv, argc);
    
    if(config.isHelp)
    {
        displayHelp();
        return 0;
    }
    
    return runtime(config);
}


int runtime(Configuration& config)
{
    int error;
    
#if OS == WIN
    if(config.hide)
        FreeConsole();
    
    WSADATA wsaData;
    error = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if(error != 0)
    {
        debug("WSAStartup error : %i\r\n", error)
        return -1;
    }
#endif

	debug("Cache : %s\r\n", (config.dnsCache ? "ON" : "OFF"))
	
	DNSCache dnsCache;
    
    INetAddress outaddr(config.remoteDnsServerIp, config.remoteDnsServerPort);
    INetAddress inaddr(config.port);
    
    DatagramSocket in_ds(inaddr);
    if(in_ds.isErroneous())
    {
        if(in_ds.isErrorOnSocketCreation())
        {
            debug("in_ds error : Can't create socket [error no. %i]\r\n", in_ds.getError())
            getOutput() << "Can't create socket, error " << in_ds.getError() << "." << std::endl;
        }
        if(in_ds.isErrorOnBinding())
        {
            debug("in_ds error : Can't bind [error no. %i]\r\n", in_ds.getError())
            switch(in_ds.getError())
            {
                case 98:
                    getOutput() << "Can't bind, the port " << inaddr.getPort() << " is already in use." << std::endl;
                    break;
                    
                default:
                    getOutput() << "Can't bind, error " << in_ds.getError() << "." << std::endl;
                    break;
            }
        }
        return -1;
    }
    
    DatagramSocket out_ds(1000);
    if(out_ds.isErroneous())
    {
        if(in_ds.isErrorOnSocketCreation())
        {
            debug("out_ds error : Can't create socket [error no. %i]\r\n", out_ds.getError())
            getOutput() << "Can't create socket, error " << out_ds.getError() << "." << std::endl;
        }
        if(in_ds.isErrorOnBinding())
        {
            debug("out_ds error : Can't bind [error no. %i]\r\n", out_ds.getError())
            switch(out_ds.getError())
            {
                case 98:
                    getOutput() << "Can't bind, the port is already in use." << std::endl;
                    break;
                    
                default:
                    getOutput() << "Can't bind, error " << out_ds.getError() << "." << std::endl;
                    break;
            }
        }
        return -1;
    }
    
    EntryFilter* filters = loadEntryFilters(config.filtersFile);
    
    char data[500];
    Datagram* dtg_in = new Datagram(data, 500);
    Datagram* dtg_out = new Datagram(data, 500);
    
    debug("Started on the port : %i\r\n", in_ds.getAddress().getPort())
    
    for(;;)
    {
		debug("Start in_ds.receive\r\n")
        in_ds.receive(dtg_in);
        
        if(dtg_in->isErroneous())
        {
            debug("in_ds.receive error no. %i\r\n", dtg_in->getError())
            continue;
        }
        
        char* str = dtg_in->getData() + 13;
		
		
		if(config.dnsCache)
		{
			DNSCacheEntry* entry = dnsCache.get(str);
			if(entry)
			{
				char* data = entry->get();
				data[0] = dtg_in->getData()[0];
				data[1] = dtg_in->getData()[1];
				
				debug("[Cache] Start in_ds.send\r\n")
				in_ds.send(data, entry->getLength(), dtg_in->getINetAddress());
				continue;
			}
		}
		
		
        
		debug("Start filters->matches\r\n")
        if(filters == 0 || !filters->matches(str))
        { // Not Blocked
			debug("[NotBlocked] Start out_ds.send\r\n")
            error = out_ds.send(dtg_in, outaddr);
            if(error != 0)
            {
				debug("[NotBlocked] out_ds.send error : %i\r\n", error)
                continue;
            }

			debug("[NotBlocked] Start out_ds.receive\r\n")
            out_ds.receive(dtg_out);
            
            if(dtg_out->isErroneous())
            {
				if(dtg_out->getError() == 10060)
					debug("[NotBlocked] dtg_out.receive timeout : %i\r\n", dtg_out->getError())
				else
					debug("[NotBlocked] dtg_out.receive error no. %i\r\n", dtg_out->getError())
                continue;
            }

			debug("[NotBlocked] Start in_ds.send\r\n")
            error = in_ds.send(dtg_out, dtg_in->getINetAddress());
            if(error != 0)
            {
                debug("[NotBlocked] in_ds.send error : %i\r\n", error)
                continue;
            }
			
			if(config.dnsCache)
			{
				dnsCache.set(str, dtg_out->getData(), dtg_out->getLength());
			}
            
            received(str, false);
        }
        else
        { // Blocked
            char* data = dtg_in->getData();
            
            data[2] = 0;
            data[3] = 0;
            data[6] = 0;
            data[7] = 0;
            
			debug("[Blocked] Start in_ds.send\r\n")
            error = in_ds.send(dtg_in, dtg_in->getINetAddress());
            if(error != 0)
            {
                debug("[Blocked] in_ds.send error : %i\r\n", error)
                continue;
            }
            
            received(str, true);
        }
		debug("Done\r\n")
    }
    
    dtg_in->dispose();
    dtg_out->dispose();
        
    return 0;
}


EntryFilter* loadEntryFilters(const char* filepath)
{
    std::ifstream infile(filepath);
    
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

void received(char* data, bool blocked)
{
    if(blocked)
        getOutput() << " >X> " << data << " [BLOCKED]" << std::endl;
    else
        getOutput() << " >>> " << data << std::endl;
    
    fflush(stdout);
}

void displayHelp()
{
    printf("\r\n********************************\r\n");
    printf("******* Local DNS Server *******\r\n");
    printf("********************************\r\n");
    printf("\r\nList of parameters :\r\n");

    int i = 0;
    while(configuration_parameters[i][0] != '\0')
        printf("   %s\r\n", configuration_parameters[i++]);

    fflush(stdout);
}
