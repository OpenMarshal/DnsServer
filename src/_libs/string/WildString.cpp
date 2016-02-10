#include "WildString.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <iostream>

WildString_Builder& WildString::create()
{
	return *new WildString_Builder();
}


bool WildString::_matches(const char* s, int len, int thisStrIndex, int paramStrIndex)
{
    while(paramStrIndex < len && thisStrIndex < wildLen)
    {
        if(wildChar != 0 && wild[thisStrIndex] == wildChar)
        {
			thisStrIndex++;
			if(thisStrIndex == wildLen)
				return true;

			do
			{
				if(_matches(s, len, thisStrIndex, paramStrIndex))
					return true;

				paramStrIndex++;
			} while(paramStrIndex < len && thisStrIndex < wildLen);

			return false;
		}
		else if(ignoreChar != 0 && wild[thisStrIndex] == ignoreChar)
		{ }
		else
		{
			if(wild[thisStrIndex] != s[paramStrIndex])
				return false;
		}
		
        thisStrIndex++;
        paramStrIndex++;
    }

    return paramStrIndex == len && thisStrIndex == wildLen;
}
