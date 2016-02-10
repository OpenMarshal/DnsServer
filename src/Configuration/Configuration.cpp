#include "Configuration.h"
#include "General.h"

#include <string.h>
#include <stdlib.h>
#include <fstream>

Configuration::Configuration(const char* defaultRemoteDnsServerIp)
	: ArgumentManager(4),
	port(53),
	remoteDnsServerIp(defaultRemoteDnsServerIp),
	remoteDnsServerPort(53),
	hide(false),
	dnsCache(false),
	filtersFile("filters.txt")
{
	ArgumentManager::add("-p", 1, __ARG_IM__(setPort), "[PORT]\t\tDefine the port number.", 2);
	ArgumentManager::add("-remoteip", 1, __ARG_IM__(setRemoteIP), "[IP]\t\tDefine the IP of the \"remote\" DNS Server.", 1);
	ArgumentManager::add("-remoteport", 1, __ARG_IM__(setRemotePort), "[PORT]\t\tDefine the port of the \"remote\" DNS Server.", 1);
	ArgumentManager::add("-dns", 1, __ARG_IM__(setDNS), "[FILE_PATH]\tDefine the file containing the filters.", 2);
	ArgumentManager::add("-o", 1, __ARG_IM__(setOutputFile), "[FILE_PATH]\tDefine the output file.", 2);
	ArgumentManager::add("-cache", 0, __ARG_IA__(dnsCache), "Use a DNS Cache.", 3);
	#if OS == WIN
		ArgumentManager::add("-hide", 0, __ARG_IA__(hide), "Hide the window.", 3);
	#endif
}


void Configuration::beforeHelp()
{
	getOutput() << "****************************************" << std::endl
				<< "************** DNS Server **************" << std::endl
				<< "****************************************" << std::endl
				<< std::endl;
}
void Configuration::afterHelp()
{
	getOutput() << std::endl
				<< "****************************************" << std::endl;
}

