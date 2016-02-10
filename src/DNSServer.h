#ifndef _DNSSERVER_H
#define	_DNSSERVER_H

#include "General.h"
#include "_libs/thread/runnable.h"

#include "Filter/FilterManager.h"
#include "Configuration/Configuration.h"
#include "DNSCache/DNSCache.h"
#include "_libs/string/ExString.h"
#include "_libs/socket/udp.h"

class DNSServer : public Runnable
{
public:
	DNSServer(Configuration* config)
		: config(config),
		in_ds(0),
		out_ds(0)
	{
		filterManager = new FilterManager();
		filterManager->loadFromFile(config->filtersFile);
	}
	
	void run() throw(int, SocketCreationException);
	
protected:
	virtual bool createSockets() throw(SocketCreationException);
	
	virtual void formatReceivedInput(char* data, bool isBlocked);
	virtual void receivedBlocked(char* data);
	virtual void receivedAuthorized(char* data);
	virtual void received(char* data, bool isBlocked);
	
private:
	Configuration* config;
	FilterManager* filterManager;
	
	DatagramSocket* in_ds;
	DatagramSocket* out_ds;
	
	DNSCache dnsCache;
};


#endif /* _DNSSERVER_H */