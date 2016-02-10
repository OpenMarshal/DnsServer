#include "General.h"
#include "argumentmanager.h"


std::list<std::string> extractArguments(char* str, int len)
{
	std::list<std::string> data;
	
	int start = 0;
	bool par = false;
	for(int i = 0; i < len; i++)
	{
		if(start == i && str[i] == '"')
			par = true;
		else
		{
			if(!par && (str[i] == ' ' || str[i] == '\t') ||
				par && (str[i] == '"'))
			{
				if(i - start != 0)
				{
					int parInc = (par ? 1 : 0);
					data.push_back(std::string(str + start + parInc, i - start - parInc));
				}
				start = i + 1;
				par = false;
			}
		}
	}
	if(len - start != 0)
		data.push_back(std::string(str + start, len - start));
	
	return data;
}



ArgumentManager::ArgumentManager(int defaultDescTab)
	: defaultDescTab(defaultDescTab)
{
	add("-h", 0, __ARG_M__ { showHelp(); return false; }, "Display help.");
}

void ArgumentManager::add(const char* name, int nbParams, argument_method method, const char* desc, int nbDescTab)
{
	struct Argument* a = new struct Argument;
	a->name = name;
	a->nbParams = nbParams;
	a->method = method;
	a->desc = desc;
	a->nbDescTab = (nbDescTab == -1 ? defaultDescTab : nbDescTab);
	arguments.push_back(a);
}

bool ArgumentManager::compute(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++)
		for(struct Argument* a : arguments)
		{
			if(strcmp(a->name, argv[i]) == 0)
			{
				if(argc - i + 1 < a->nbParams)
					return false;
				
				if(!a->method(&argv[i + 1]))
					return false;
				
				i += a->nbParams;
			}
		}
	
	return true;
}

void ArgumentManager::error(struct Argument* a)
{
	getOutput() << "Argument error : \"" << a->name << "\" needs " << a->nbParams << " parameters.";
}

void ArgumentManager::showHelp()
{
	beforeHelp();
	
	for(struct Argument* a : arguments)
	{
		getOutput() << "   " << a->name;
		for(int t = 0; t < a->nbDescTab; t++)
			getOutput() << "\t";
		getOutput() << a->desc << std::endl;
	}
	
	afterHelp();
}
void ArgumentManager::drawArg(struct Argument* a)
{
	getOutput() << "\t" << a->name << "\t" << a->desc << std::endl;
}
