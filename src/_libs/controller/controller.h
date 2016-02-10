#ifndef _LIBS_CONTROLLER_H
#define	_LIBS_CONTROLLER_H

#include "General.h"
#include "_libs/argument/argumentmanager.h"
#include "_libs/thread/runnable.h"
#include "_libs/socket/tcp.h"

class Controller;

class _Controller_Client : public Runnable
{
public:
	_Controller_Client(Socket* client, Controller* controller)
		: Runnable(),
		controller(controller),
		client(client)
	{ }
	
	std::string compute(std::string cmd, std::list<std::string>::iterator itParams, std::list<std::string>::iterator itEnd)
	{/*
		for(; it != itEnd; ++it)
		{
			
		}*/
	}
	
	void run()
	{
		int data_size = 256;
		char data[data_size + 1];

		try
		{
			do
			{
				int nb = client->receive(data, data_size);
				std::list<std::string> arguments = ::extractArguments(data, nb);
				
				std::string cmd = arguments.front();
				std::list<std::string>::iterator itParams = ++arguments.begin();
				std::list<std::string>::iterator itEnd = arguments.end();
				
				
			} while(!isStopped());
		}
		catch(...)
		{ }
		
		try
		{
			client->close();
		}
		catch(...)
		{ }
	}
	
private:
	Socket* client;
	Controller* controller;
};

class Controller : public Runnable
{
public:
	Controller(int port)
		: Runnable(),
		port(port)
	{ }

	~Controller()
	{ }

	void run() throw(SocketCreationException)
	{
		INetAddress addr(port);
		ServerSocket server(addr);
		
		server.listen();
		
		do
		{
			try
			{
				Socket* client = server.accept();
				_Controller_Client* cl = new _Controller_Client(client, this);
				cl->start();
			}
			catch(...)
			{ }
		} while(!isStopped());
		
		server.close();
	}
	
private:
	int port;
};



#endif	/* _LIBS_CONTROLLER_H */

