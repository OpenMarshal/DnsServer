/* 
 * File:   Configuration.h
 * Author: Adrien Castex
 *
 * Created on 4 septembre 2015, 15:19
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

extern char* configuration_parameters[];

class Configuration
{
public:
    Configuration(char* params[], int nb);
    
    int port;
    char* remoteDnsServerIp;
    int remoteDnsServerPort;
    bool isHelp;
    bool hide;
    char* filtersFile;
    
private:
    void load(char* params[], int nb);
};

#endif	/* CONFIGURATION_H */

