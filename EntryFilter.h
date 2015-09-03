/* 
 * File:   EntryFilter.h
 * Author: Adrien Castex
 *
 * Created on 3 septembre 2015, 10:26
 */

#ifndef ENTRYFILTER_H
#define	ENTRYFILTER_H

#include <String.h>

class EntryFilter
{
public:
    EntryFilter(const char* buffer) : EntryFilter(buffer, 0, strlen(buffer))
    { }
    EntryFilter(const char* buffer, int start, int len)
    {
        this->next = 0;
        
        this->str = new char[len];
        for(int i = 0; i < len; i++)
            this->str[i] = buffer[i + start];
        
        this->len = len;
    }
    
    EntryFilter* setNextEntry(EntryFilter* next)
    {
        next->next = this;
        
        return next;
    }
    
    bool matches(char* str)
    {
        return matches(str, strlen(str));
    }
    bool matches(char* str, int len)
    {
        EntryFilter* current = this;
        
        do
        {
            if(current->_matches(str, len))
                return true;
            
            current = current->next;
        } while(current != 0);
        
        return false;
    }
    
private:
    EntryFilter* next;
    char* str;
    int len;
    
    
    bool _matches(char* str, int len)
    {
        _matches(str, len, 0, 0);
    }
    bool _matches(char* str, int len, int thisStrIndex, int paramStrIndex)
    {
        while(paramStrIndex < len && thisStrIndex < this->len)
        {
            switch(this->str[thisStrIndex])
            {
                case '*':
                    thisStrIndex++;
                    if(thisStrIndex == this->len)
                        return true;
                    
                    do
                    {
                        if(_matches(str, len, thisStrIndex, paramStrIndex))
                            return true;
                        
                        paramStrIndex++;
                    } while(paramStrIndex < len && thisStrIndex < this->len);
                    
                    return false;
                    break;
                    
                case '.':
                    break;
                    
                default:
                    if(this->str[thisStrIndex] != str[paramStrIndex])
                        return false;
                    break;
            }
            thisStrIndex++;
            paramStrIndex++;
        }
        
        return paramStrIndex == len && thisStrIndex == this->len;
    }
};


#endif	/* ENTRYFILTER_H */

