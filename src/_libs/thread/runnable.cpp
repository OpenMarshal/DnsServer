#include "runnable.h"

static void runIt(Runnable* r)
{
	r->run();
}

void Runnable::start()
{
	if(th)
		delete(th);
	
	stopped = false;
	
	th = new ::Thread((thread_method)runIt, useCycle, this);
	th->start();
}
