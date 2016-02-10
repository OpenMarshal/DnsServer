#ifndef _CONFIGURATION_H
#define	_CONFIGURATION_H

#include <fstream>

#include "_libs/argument/argumentmanager.h"

class Configuration : public ArgumentManager
{
public:
	Configuration(const char* defaultRemoteDnsServerIp);
	
	virtual void beforeHelp();
	virtual void afterHelp();
	
    int port;
    const char* remoteDnsServerIp;
    int remoteDnsServerPort;
    bool hide;
    const char* filtersFile;
	bool dnsCache;
	
private:
	bool setPort(char** data)
	{
		this->port = atoi(data[0]);
		return true;
	}
	
	bool setRemotePort(char** data)
	{
		this->remoteDnsServerPort = atoi(data[0]);
		return true;
	}
	
	bool setOutputFile(char** data)
	{
		std::ofstream* os = new std::ofstream();
		os->open(data[0], std::ofstream::out | std::ofstream::app);
		::setOutput(os);
		return true;
	}
	
	bool setDNS(char** data)
	{
		this->filtersFile = data[0];
		return true;
	}
	
	bool setRemoteIP(char** data)
	{
		this->remoteDnsServerIp = data[0];
		return true;
	}
};

#endif	/* _CONFIGURATION_H */

