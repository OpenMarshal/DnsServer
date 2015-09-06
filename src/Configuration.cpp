#include "Configuration.h"
#include "GlobalHeader.h"

#include <string.h>
#include <stdlib.h>
#include <fstream>


std::ostream* output;

char* configuration_parameters[]
{
    "-p, -port         [PORT]       : define the port",
    "-rip, -remoteip   [IP]         : define the IP of the \"remote\" DNS Server",
    "-rp, -remoteport  [PORT]       : define the port of the \"remote\" DNS Server",
    "-dns              [FILE_PATH]  : define the file containing the filters",
    "-o, -output       [FILE_PATH]  : define the output file",
    "-c, -cache                     : use a DNS Cache",
#if OS == WIN
    "-hide                          : hide the window",
#endif
    "\0"
};


enum ConfigurationType
{
    CT_NONE,
    CT_FILTERS,
    CT_PORT,
    CT_REMOTE_PORT,
    CT_REMOTE_IP,
    CT_OUTPUT
};


Configuration::Configuration(char* params[], int nb)
    : port(53),
    remoteDnsServerIp(DNS_SERVER_IP),
    remoteDnsServerPort(DNS_SERVER_PORT),
    isHelp(false),
    hide(false),
	dnsCache(false),
    filtersFile("filters.txt")
{
    output = &std::cout;
    
    load(params, nb);
}

void Configuration::load(char* params[], int nb)
{
    enum ConfigurationType current = CT_NONE;

    #define __IS(val) (strcmp(str, val) == 0)
    #define IS(val) if(__IS(val))

    for(int i = 0; i < nb; i++)
    {
        char* str = params[i];

        if(str[0] == '-')
        { // Option
            if(__IS("-p") || __IS("-port"))
                current = CT_PORT;
            else if(__IS("-rip") || __IS("-remoteip"))
                current = CT_REMOTE_PORT;
            else if(__IS("-rp") || __IS("-remoteport"))
                current = CT_REMOTE_IP;
            else if(__IS("-h") || __IS("-help") || __IS("--help"))
                isHelp = true;
            else IS("-dns")
                current = CT_FILTERS;
            else if(__IS("-o") || __IS("-output"))
                current = CT_OUTPUT;
            else if(__IS("-c") || __IS("-cache"))
				dnsCache = true;
            #if OS == WIN
            else IS("-hide")
                hide = true;
            #endif
        }
        else
        { // Value
            switch(current)
            {
                case CT_PORT:
                    this->port = atoi(str);
                    break;

                case CT_REMOTE_IP:
                    this->remoteDnsServerIp = str;
                    break;

                case CT_REMOTE_PORT:
                    this->remoteDnsServerPort = atoi(str);
                    break;

                case CT_FILTERS:
                    this->filtersFile = str;
                    break;
                    
                case CT_OUTPUT:
                {
                    std::ofstream* os = new std::ofstream();
                    os->open(str, std::ofstream::out | std::ofstream::app);
                    output = os;
                    break;
                }
            }
        }
    }
}
