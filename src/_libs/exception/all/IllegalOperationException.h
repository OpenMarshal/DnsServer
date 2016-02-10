#ifndef _LIBS_ILLEGALOPERATIONEXCEPTION_H
#define	_LIBS_ILLEGALOPERATIONEXCEPTION_H

#include "_libs/exception/exception.h"

class IllegalOperationException : public Exception
{
public:
	IllegalOperationException(const char* message = "Illegal operation.")
	{
		this->message = message;
	}
	
	const char* getMessage()
	{
		return message;
	}
	
private:
	const char* message;
};

#endif	/* _LIBS_ILLEGALOPERATIONEXCEPTION_H */

