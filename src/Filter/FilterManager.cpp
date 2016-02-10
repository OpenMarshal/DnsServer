#include "FilterManager.h"

#include "_libs/string/ExString.h"
#include "_libs/dataParse/dataLine.h"

#include <fstream>
#include <algorithm>


bool FilterManager::loadFromFile(const char* filePath)
{
	::DataLine dl;
	if(!dl.load(filePath))
		return false;
	
	for(const std::string& s : dl.getEntries())
	{
		this->entries.push_back(WildString::create()
			.setWildString(s)
			.setWildChar('*')
			.setIgnoreChar('.')
			.build());
	}
	
	return true;
}

bool FilterManager::matches(char* str)
{
	return std::none_of(
		this->entries.begin(),
		this->entries.end(),
		[&str](WildString* ef)
		{
			return ef->matches(str);
		});
	
}
bool FilterManager::matches(char* str, int len)
{
	return std::none_of(
		this->entries.begin(),
		this->entries.end(),
		[&str, len](WildString* ef)
		{
			return ef->matches(str, len);
		});
}

void FilterManager::clear()
{
	while(!this->entries.empty())
	{
		delete(this->entries.back());
		this->entries.pop_back();
	}
}