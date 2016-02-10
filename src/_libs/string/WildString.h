#ifndef _LIBS_EXSTRING_H
#define	_LIBS_EXSTRING_H

#include <stdio.h>
#include <string.h>
#include <string>

class WildString_Builder;

class WildString
{
public:
	WildString(const char* wild, int length, char wildChar, char ignoreChar)
		: wildChar(wildChar),
		ignoreChar(ignoreChar),
		wildLen(length)
	{
		char* w = new char[length];
		memcpy(w, wild, length);
		this->wild = w;
	}
	
	bool matches(const char* s, int len)
	{
		return _matches(s, len);
	}
	bool matches(const char* s)
	{
		return _matches(s, strlen(s));
	}
	bool matches(std::string s)
	{
		return _matches(s.c_str(), s.size());
	}
	
	static WildString_Builder& create();
	
private:
	const char* wild;
	int wildLen;
	char wildChar;
	char ignoreChar;
	
	bool _matches(const char* s, int len, int thisStrIndex = 0, int paramStrIndex = 0);
};

class WildString_Builder
{
public:
	WildString_Builder& setWildString(std::string wildString)
	{
		return setWildString(wildString.c_str(), wildString.size());
	}
	WildString_Builder& setWildString(const char* wildString)
	{
		return setWildString(wildString, strlen(wildString));
	}
	WildString_Builder& setWildString(const char* wildString, int len)
	{
		this->wild = wildString;
		this->wildLen = len;
		return *this;
	}
	
	WildString_Builder& setWildStringLength(int len)
	{
		this->wildLen = len;
		return *this;
	}
	
	WildString_Builder& setWildChar(int wildChar)
	{
		this->wildChar = wildChar;
		return *this;
	}
	WildString_Builder& setIgnoreChar(int ignoreChar)
	{
		this->ignoreChar = ignoreChar;
		return *this;
	}
	
	WildString* build()
	{
		WildString* ws = new WildString(wild, wildLen, wildChar, ignoreChar);
		delete(this);
		return ws;
	}
	
private:
	WildString_Builder()
		: wildChar('*'),
		ignoreChar(0),
		wild(0),
		wildLen(0)
	{ }
	
	const char* wild;
	int wildLen;
	char wildChar;
	char ignoreChar;
	
	friend class WildString;
};


#endif	/* _LIBS_EXSTRING_H */

