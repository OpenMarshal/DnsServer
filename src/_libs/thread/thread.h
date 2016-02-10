#ifndef _LIBS_THREAD_H
#define	_LIBS_THREAD_H

#include "General.h"
#include "_libs/exception/all/IllegalOperationException.h"

#if OS == WIN
	#include <windows.h>
#elif OS == LINUX
	#include <pthread.h>
#endif

#ifndef _LIBS_THREAD_MAX_THS
	#define _LIBS_THREAD_MAX_THS 50
#endif

typedef void (*thread_method)(void* data);

class Thread
{
public:
	Thread(thread_method fun_ptr, bool useAutoDestroy = false, void* data = 0);
	
	~Thread() throw(IllegalOperationException)
	{
		if(useAutoDestroy)
			throw new IllegalOperationException("You can't delete ");
	}
	
	int start(void* data);
	int start();
	
	void* join();
	
private:
	bool useAutoDestroy;
	thread_method fun_ptr;
	void* data;
	
	#if OS == WIN
		DWORD thId;
		HANDLE thHandle;
	#elif OS == LINUX
		pthread_t thHandle;
	#endif
};



#endif	/* _LIBS_THREAD_H */

