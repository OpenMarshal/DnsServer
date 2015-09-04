/* 
 * File:   EntryFilter.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 10:26
 */

#ifndef ENTRYFILTER_H
#define	ENTRYFILTER_H

class EntryFilter
{
public:
    EntryFilter(const char* buffer);
    EntryFilter(const char* buffer, int start, int len);
    
    EntryFilter* setNextEntry(EntryFilter* next);
    
    bool matches(char* str);
    bool matches(char* str, int len);
    
private:
    EntryFilter* next;
    char* str;
    int len;
    
    bool _matches(char* str, int len);
    bool _matches(char* str, int len, int thisStrIndex, int paramStrIndex);
};


#endif	/* ENTRYFILTER_H */

