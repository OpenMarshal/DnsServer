#ifndef _LIBS_REMOTE_CONTROLLER_H
#define	_LIBS_REMOTE_CONTROLLER_H

#include "General.h"
#include "_libs/thread/runnable.h"
#include "_libs/socket/tcp.h"

#include <iostream>
#include <istream>
#include <ostream>

class RemoteController : public Runnable
{
public:
	RemoteController()
		: RemoteController(&std::cin)
	{ }
	RemoteController(std::istream* in)
		: Runnable(),
		in(in),
		maxBufferInSize(256),
		maxBufferOutSize(256),
		addr(0),
		output(0)
	{ }

	~RemoteController()
	{ }
	
	void setMaxBufferInSize(int maxBufferSize)
	{
		this->maxBufferInSize = maxBufferSize;
	}
	void setMaxBufferOutSize(int maxBufferSize)
	{
		this->maxBufferOutSize = maxBufferSize;
	}
	
	void setRemote(const char* ip, uint port)
	{
		this->addr = new INetAddress(ip, port);
	}
	
	void setOutput(std::ostream* output)
	{
		this->output = output;
	}

	void run()
	{
		if(addr == 0)
			return;
		
		if(!output)
			output = &getOutput();
		
		char buff_out[maxBufferOutSize];
		char buff_in[maxBufferInSize];
		uint lineLen;
		
		bool exit = false;
		
		::Socket sock(*addr);
		
		do
		{
			in->getline(buff_out, maxBufferOutSize);
			lineLen = strlen(buff_out);
			
			if(strcmp("exit", buff_out))
			{
				exit = true;
				continue;
			}
			
			sock.send(buff_out, lineLen);
			uint rnb = sock.receive(buff_in, maxBufferInSize - 1);
			buff_in[rnb + 1] = '\0';
			(*output) << buff_in << std::endl;
			
		} while(!exit && !isStopped());
		
		sock.close();
	}
	
private:
	std::istream* in;
	std::ostream* output;
	
	int maxBufferOutSize;
	int maxBufferInSize;
	INetAddress* addr;
};



#endif	/* _LIBS_REMOTE_CONTROLLER_H */

