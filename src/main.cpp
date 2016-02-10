#include "Filter/FilterManager.h"
#include "Configuration/Configuration.h"
#include "DNSCache/DNSCache.h"
#include "General.h"
#include "_libs/string/ExString.h"
#include "_libs/socket/udp.h"
#include "DNSServer.h"
#include "_libs/controller/controller.h"
#include "_libs/controller/remoteController.h"

#include "_libs/argument/argumentmanager.h"

#include <fstream>


int main(int argc, char* argv[])
{
	Configuration config(DNS_SERVER_IP);
	if(!config.compute(argc, argv))
		return 0;
	
	#if OS == WIN
		if(config.hide)
			FreeConsole();
	#endif
	
	initSockets();
	
	try
	{
		DNSServer dnsServer(&config);
		dnsServer.run();
	}
	catch(SocketCreationException ex)
	{
		getOutput() << "Fatal error : [FuncName: " << ex.getFunctionName() << "; ErrNo: " << ex.getErrorNo() << "]";
		return 0;
	}
	catch(int ex)
	{
		getOutput() << "An error occured : " << ex << std::endl;
		return 0;
	}
	
	stopSockets();
    
    return 0;
}


