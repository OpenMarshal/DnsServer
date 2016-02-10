#ifndef _LIBS_HTTP_MESSAGE_BUILDER_H
#define	_LIBS_HTTP_MESSAGE_BUILDER_H

#include "_libs/exception/exception.h"
#include "_libs/string/ExString.h"

#include <istream>
#include <string>
#include <map>
#include <exception>


template<class T>
class HttpMessageBuilder
{
public:
	HttpMessageBuilder()
		: body(0),
		bodyStream(0),
		bodySize(0),
		version("HTTP/1.1")
	{ }

	T& addHeader(const char* name, int value);
	T& addHeader(std::string name, int value);
	T& addHeader(const char* name, const char* value);
	T& addHeader(std::string name, std::string value);

	T& setVersion(const char* version);
	T& setVersion(std::string version);
	
	T& setContent(std::istream* contentStream);
	T& setContent(const char* content);
	T& setContent(std::string content);
	T& setContent(const char* content, int start, int size);
	T& setContent(const char* content, int size);
	
protected:
	std::map<std::string, std::string> headers;
	
	std::string version;
	
	std::istream* bodyStream;
	char* body;
	int bodySize;
	
	void build(HttpMessage* result);
};


#define _HttpMessageBuilder(XX) \
template<class T> \
XX HttpMessageBuilder<T>


_HttpMessageBuilder(T&)::addHeader(const char* name, int value)
{
	char cvalue[10];
	sprintf(cvalue, "%i", value);
	
	return this->addHeader(name, cvalue);
}

_HttpMessageBuilder(T&)::addHeader(std::string name, int value)
{
	char cvalue[10];
	sprintf(cvalue, "%i", value);
	
	return this->addHeader(name, std::string(cvalue));
}

_HttpMessageBuilder(T&)::addHeader(const char* name, const char* value)
{
	return this->addHeader(std::string(name), std::string(value));
}

_HttpMessageBuilder(T&)::addHeader(std::string name, std::string value)
{
	name = ::toLowerCase(name);
	if(name.compare("content-length") == 0)
		bodySize = atoi(value.c_str());
		
	this->headers.emplace(name, ::trim(value));
	
	return *(T*)this;
}


_HttpMessageBuilder(T&)::setVersion(const char* version)
{
	return this->setVersion(std::string(version));
}

_HttpMessageBuilder(T&)::setVersion(std::string version)
{
	this->version = version;
	return *(T*)this;
}


_HttpMessageBuilder(T&)::setContent(std::istream* contentStream)
{
	this->bodyStream = contentStream;
}

_HttpMessageBuilder(T&)::setContent(const char* content, int start, int size)
{
	char* body = new char[size];
	memcpy(body, content + start, size);
	this->body = body;
	
	this->bodySize = size;
	return *(T*)this;
}

_HttpMessageBuilder(T&)::setContent(const char* content, int size)
{
	return this->setContent(content, 0, size);
}

_HttpMessageBuilder(T&)::setContent(const char* content)
{
	return this->setContent(content, 0, ::strlen(content));
}

_HttpMessageBuilder(T&)::setContent(std::string content)
{
	return this->setContent(content.c_str(), 0, content.size());
}


_HttpMessageBuilder(void)::build(HttpMessage* result)
{
	std::map<std::string, std::string>::iterator it = this->headers.find("content-length");
	
	if(bodyStream)
	{
		result->bodyStream = bodyStream;
	}
	else
	{
		if(it == this->headers.end())
			this->addHeader("content-length", bodySize);
		result->body = body;
	}
	
	result->headers = headers;
	result->bodySize = bodySize;
	result->version = version;
}

#endif	/* _LIBS_HTTP_MESSAGE_BUILDER_H */

