#include "thread.h"

#include "General.h"
#include "_libs/error/ErrorManager.h"


static void manageThreads(Thread* th)
{
	static Thread* threads[_LIBS_THREAD_MAX_THS];
	static int index = -1;
	static bool didReturn = false;
	
	index++;
	
	if(index == _LIBS_THREAD_MAX_THS)
		didReturn = true;
	
	if(didReturn)
	{ // delete the last thread
		delete(threads[index]);
	}
	
	threads[index] = th;
}


Thread::Thread(thread_method fun_ptr, bool useAutoDestroy, void* data)
	: fun_ptr(fun_ptr),
	data(data),
	useAutoDestroy(useAutoDestroy)
{
	if(useAutoDestroy)
		manageThreads(this);
}

int Thread::start(void* data)
{
	#if OS == WIN
		this->thHandle = ::CreateThread( 
            0,                   					// default security attributes
            0,                      				// use default stack size  
            (LPTHREAD_START_ROUTINE)this->fun_ptr,	// thread function name
            data,          							// argument to thread function 
            0,                      				// use default creation flags 
            &this->thId);  							// returns the thread identifier
	#elif OS == LINUX
		::pthread_create(
			&this->thHandle,
			0,
			this->fun_ptr,
			data);
	#endif
	return (int)this->thHandle;
}
int Thread::start()
{
	return this->start(this->data);
}

void* Thread::join()
{
	void* result;
	
	#if OS == WIN
		::WaitForSingleObject(this->thHandle, INFINITE);
		::GetExitCodeThread(this->thHandle, (PDWORD)&result);
	#elif OS == LINUX
		::pthread_join(this->thHandle, &result);
	#endif
	
	return result;
}

