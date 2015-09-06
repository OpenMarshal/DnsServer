/* 
 * File:   DNSCache.h
 * Author: Adrien Castex
 *
 * Created on 6 septembre 2015, 13:08
 */
 
#ifndef DNSCACHE_H
#define	DNSCACHE_H

#include "GlobalHeader.h"

class DNSCacheEntry
{
public:
	DNSCacheEntry(char* domain, char* data, uint len);
	
	char* get();
	uint getLength();
	
	bool matches(char* domain);
	DNSCacheEntry* getNext();
	void setNext(DNSCacheEntry* next);
	
private:
	DNSCacheEntry* next;
	char* domain;
	char* data;
	uint len;
};

class DNSCache
{
public:
	DNSCache();
	
	DNSCacheEntry* get(char* domain);
	void set(char* domain, char* data, uint len);
	
private:
	DNSCacheEntry* head;
	DNSCacheEntry* tail;
};

#endif /* DNSCACHE_H */