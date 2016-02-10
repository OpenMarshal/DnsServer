#ifndef _LIBS_EXSTRING_H
#define	_LIBS_EXSTRING_H

#include <stdio.h>
#include <string.h>
#include <string>

std::string ltrim(std::string s);
std::string rtrim(std::string s);
std::string trim(std::string s);

std::string toLowerCase(std::string s);
std::string replace(std::string s, const char* from, const char* to);


#endif	/* _LIBS_EXSTRING_H */

