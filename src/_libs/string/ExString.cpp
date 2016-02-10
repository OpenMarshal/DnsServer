#include "ExString.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <iostream>

std::string ltrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

std::string rtrim(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string trim(std::string s)
{
    return ltrim(rtrim(s));
}

std::string toLowerCase(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

std::string replace(std::string s, const char* from, const char* to)
{
	int fromSize = strlen(from);
	size_t index;
	while((index = s.find(from)) != std::string::npos)
		s.replace(index, fromSize, to);
	
	return s;
}

