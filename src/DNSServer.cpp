#include "DNSServer.h"



bool DNSServer::createSockets() throw(SocketCreationException)
{
	INetAddress inaddr(config->port);
	
	in_ds = new DatagramSocket(inaddr);
	out_ds = new DatagramSocket(1000);
}

void DNSServer::run() throw(int, SocketCreationException)
{
	INetAddress outaddr(config->remoteDnsServerIp, config->remoteDnsServerPort);
	
	createSockets();
	
	char data[500];
	Datagram* dtg_in = new Datagram(data, 500);
	Datagram* dtg_out = new Datagram(data, 500);
	
	for(;;)
	{
		try
		{
			in_ds->receive(dtg_in);
			
			char* str = dtg_in->getData() + 13;
			
			if(config->dnsCache)
			{
				DNSCacheEntry* entry = dnsCache.get(str);
				if(entry)
				{
					char* data = entry->getData();
					data[0] = dtg_in->getData()[0];
					data[1] = dtg_in->getData()[1];
					
					in_ds->send(data, entry->getDataLength(), dtg_in->getINetAddress());
					continue;
				}
			}
			
			if(filterManager->matches(str))
			{ // Not Blocked
				out_ds->send(dtg_in, outaddr);

				out_ds->receive(dtg_out);

				in_ds->send(dtg_out, dtg_in->getINetAddress());
				
				if(config->dnsCache)
					dnsCache.set(new DNSCacheEntry(str, dtg_out->getData(), dtg_out->getLength()));
				
				received(str, false);
			}
			else
			{ // Blocked
				char* data = dtg_in->getData();
				
				data[2] = 0;
				data[3] = 0;
				data[6] = 0;
				data[7] = 0;
				
				in_ds->send(dtg_in, dtg_in->getINetAddress());
				
				if(config->dnsCache)
					dnsCache.set(new DNSCacheEntry(str, dtg_in->getData(), dtg_in->getLength()));
				
				received(str, true);
			}
		}
		catch(int errNo)
		{
			if(errNo != 0 && errNo != 10054 && errNo != 10060)
				throw errNo;
		}
	}
	
	delete(dtg_in);
	delete(dtg_out);
}



void DNSServer::formatReceivedInput(char* data, bool isBlocked)
{
	for(char* c = data; c < data + strlen(data); c++)
		if(!('a' <= *c && *c <= 'z' ||
			'A' <= *c && *c <= 'z' ||
			'0' <= *c && *c <= '9' ||
			*c == '-' || *c == '_'))
			(*c) = '.';
}
void DNSServer::receivedBlocked(char* data)
{
	getOutput() << " >X> " << data << " [BLOCKED]" << std::endl;
}
void DNSServer::receivedAuthorized(char* data)
{
	getOutput() << " >>> " << data << std::endl;
}
void DNSServer::received(char* data, bool isBlocked)
{
	formatReceivedInput(data, isBlocked);
	
	if(isBlocked)
		receivedBlocked(data);
	else
		receivedAuthorized(data);
}
