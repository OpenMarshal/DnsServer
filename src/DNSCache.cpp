#include "DNSCache.h"

#include <string.h>

DNSCacheEntry::DNSCacheEntry(char* domain, char* data, uint len)
	: next(0),
	len(len)
{
	this->data = new char[len];
	for(int i = 0; i < len; i++)
		this->data[i] = data[i];
	
	uint domainLen = strlen(domain);
	this->domain = new char[domainLen + 1];
	for(int i = 0; i < domainLen; i++)
		this->domain[i] = domain[i];
	this->domain[domainLen] = '\0';
}

char* DNSCacheEntry::get()
{
	return data;
}

uint DNSCacheEntry::getLength()
{
	return len;
}

inline bool DNSCacheEntry::matches(char* domain)
{
	return strcmp(this->domain, domain) == 0;
}

inline DNSCacheEntry* DNSCacheEntry::getNext()
{
	return next;
}

inline void DNSCacheEntry::setNext(DNSCacheEntry* next)
{
	this->next = next;
}


DNSCache::DNSCache()
	: head(0),
	tail(0)
{ }

DNSCacheEntry* DNSCache::get(char* domain)
{
	DNSCacheEntry* entry = head;
	
	while(entry != 0)
	{
		if(entry->matches(domain))
			return entry;
		entry = entry->getNext();
	}
	
	return 0;
}

void DNSCache::set(char* domain, char* data, uint len)
{
	DNSCacheEntry* entry = new DNSCacheEntry(domain, data, len);
	
	if(tail == 0)
		head = entry;
	else
		tail->setNext(entry);
	
	tail = entry;
}
