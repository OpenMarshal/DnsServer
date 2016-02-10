#ifndef _LIBS_DATAPARSE_DATALINE_H
#define	_LIBS_DATAPARSE_DATALINE_H

#include <string>
#include <list>

class DataLine
{
public:
	bool load(const char* pathFile);
	
	const std::list<std::string>& getEntries()
	{
		return entries;
	}
	
private:
	std::list<std::string> entries;
};



#endif	/* _LIBS_DATAPARSE_DATALINE_H */

