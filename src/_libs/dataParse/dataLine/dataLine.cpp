#include "dataLine.h"
#include "_libs/string/ExString.h"

#include <fstream>

bool DataLine::load(const char* filePath)
{
	std::ifstream infile(filePath);

	if(!infile.good())
		return false;

	std::string line;
	while(std::getline(infile, line))
	{
		line = ::trim(line);
		if(line.length() == 0)
			continue;
		
		int comment = line.find('#');
		
		if(comment == 0)
			continue;
		
		line = line.substr(0, comment);
		line = ::trim(line);
		
		if(line.size() == 0)
			continue;
		
		this->entries.push_back(line);
	}
	
	return true;
}
