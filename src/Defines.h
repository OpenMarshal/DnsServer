/* 
 * File:   Defines.h
 * Author: Adrien Castex
 *
 * Created on 2 septembre 2015, 23:12
 */

#ifndef DEFINES_H
#define	DEFINES_H


/*****************************
 * Constants
 * /!\ DO NOT TOUCH
 *****************************/
#define WIN 1
#define LINUX 2



/*****************************
 * Select the OS :
 *    WIN
 *    LINUX
 *****************************/

// Windows
#if defined(__WIN32__)
    #define OS WIN
#elif defined(_WIN32)
    #define OS WIN
#elif defined(__CYGWIN__)
    #define OS WIN
#elif defined(__CYGWIN32__)
    #define OS WIN
#elif defined(__BORLANDC__)
    #define OS WIN
#elif defined(__MINGW32__)
    #define OS WIN
#elif defined(WIN32)
    #define OS WIN
#elif defined(windows)
    #define OS WIN
#endif

// Linux
#if defined(linux)
    #define OS LINUX
#elif defined(__linux__)
    #define OS LINUX
#endif

// Other
#ifndef OS
    #error OS or compiler not supported.
#endif


/*****************************
 * Debugger
 *****************************/
#define DEBUG 0


/*****************************
 * Default DNS Server
 *****************************/
#define DNS_SERVER_IP "212.27.40.241"
#define DNS_SERVER_PORT 53


#endif	/* DEFINES_H */

