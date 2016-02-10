#ifndef _LIBS_RUNNABLE_H
#define	_LIBS_RUNNABLE_H

#include "General.h"
#include "thread.h"

class Runnable
{
public:
	Runnable()
		: stopped(false),
		th(0),
		useCycle(false)
	{ }

	~Runnable()
	{
		if(th)
			delete(th);
	}

	virtual void run() = 0;
	
	void start();
	
	void stop()
	{
		stopped = true;
	}
	
	bool isStopped()
	{
		return stopped;
	}
	
	void useThreadCycle(bool value = true)
	{
		useCycle = value;
	}
	
private:
	::Thread* th;
	bool stopped;
	bool useCycle;
};



#endif	/* _LIBS_RUNNABLE_H */

