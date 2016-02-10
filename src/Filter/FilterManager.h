#ifndef _FILTER_FILTER_MANAGER_H
#define	_FILTER_FILTER_MANAGER_H

#include "_libs/string/WildString.h"

#include <list>

class FilterManager
{
public:
    FilterManager()
	{ }
	
	~FilterManager()
	{
		clear();
	}
	
	bool loadFromFile(const char* filePath);
	
	void clear();
	
	bool matches(char* str);
	bool matches(char* str, int len);
    
private:
    std::list<WildString*> entries;
};


#endif	/* _FILTER_FILTER_MANAGER_H */

