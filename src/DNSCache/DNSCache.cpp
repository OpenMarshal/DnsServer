#include "DNSCache.h"

#include <string.h>

DNSCacheEntry::DNSCacheEntry(char* domain, char* data, uint dataLength)
	: dataLength(dataLength)
{
	this->data = new char[dataLength];
	memcpy(this->data, data, dataLength);
	
	uint domainLen = strlen(domain);
	this->domain = new char[domainLen + 1];
	memcpy(this->domain, domain, domainLen);
	this->domain[domainLen] = '\0';
}

inline bool DNSCacheEntry::matches(char* domain)
{
	return strcmp(this->domain, domain) == 0;
}



DNSCacheEntry* DNSCache::get(char* domain)
{
	for(DNSCacheEntry* e : entries)
		if(e->matches(domain))
			return e;
	
	return 0;
}

void DNSCache::set(DNSCacheEntry* entry)
{
	entries.push_back(entry);
}

void DNSCache::clear()
{
	while(!entries.empty())
	{
		delete(entries.back());
		entries.pop_back();
	}
}
void DNSCache::remove(char* domain)
{
	bool exit;
	
	do
	{
		exit = true;
		for(std::list<DNSCacheEntry*>::iterator it = entries.begin(); it != entries.end(); ++it)
		{
			if((*it)->matches(domain))
			{
				entries.erase(it);
				exit = false;
				break;
			}
		}
	} while(!exit);
}
