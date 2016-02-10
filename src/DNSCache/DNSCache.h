#ifndef _DNSCACHE_H
#define	_DNSCACHE_H

#include "General.h"
#include <list>

class DNSCacheEntry
{
public:
	DNSCacheEntry(char* domain, char* data, uint dataLength);
	
	char* getData()
	{
		return data;
	}
	uint getDataLength()
	{
		return dataLength;
	}
	
	bool matches(char* domain);
	
private:
	char* domain;
	char* data;
	uint dataLength;
};

class DNSCache
{
public:
	DNSCacheEntry* get(char* domain);
	void set(DNSCacheEntry* entry);
	
	void clear();
	void remove(char* domain);
	
private:
	std::list<DNSCacheEntry*> entries;
};

#endif /* _DNSCACHE_H */