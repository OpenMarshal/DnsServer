#ifndef _LIBS_ARGUMENT_MANAGER_H
#define	_LIBS_ARGUMENT_MANAGER_H

#define __ARG_M__ [&](char** data) -> bool
#define __ARG_IM__(m) [&](char** data) -> bool { return m(data); }
#define __ARG_IA__(f) [&](char** data) -> bool { f = true; return true; }

#include "General.h"

#include <functional>
#include <list>

typedef std::function<bool (char**)> argument_method;

std::list<std::string> extractArguments(char* str, int len);

struct Argument
{
	const char* name;
	int nbParams;
	argument_method method;
	const char* desc;
	int nbDescTab;
};

class ArgumentManager
{
public:
	ArgumentManager(int defaultDescTab = 1);

	void add(const char* name, int nbParams, argument_method func, const char* desc = 0, int nbDescTab = -1);
	
	bool compute(int argc, char* argv[]);
	
	void error(struct Argument* a);
	
	void showHelp();
	virtual void drawArg(struct Argument* a);
	
	virtual void beforeHelp()
	{ }
	virtual void afterHelp()
	{ }
	
private:
	std::list<struct Argument*> arguments;
	int defaultDescTab;
};



#endif	/* _LIBS_ARGUMENT_MANAGER_H */

