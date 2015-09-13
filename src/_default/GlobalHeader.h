/* 
 * File:   GlobalHeader.h
 * Author: Adrien Castex
 *
 * Created on 2 septembre 2015, 23:17
 */

#ifndef GLOBALHEADER_H
#define	GLOBALHEADER_H

#include "_default/src/Defines.h"

#if DEBUG
    #define debug(format, args...) { printf(format, ##args); fflush(stdout); }
#else
    #define debug(format, args...) ;
#endif

#include "_default/src/Types.h"
#include <stdio.h>

#include "_default/src/Printer.h"


#endif	/* GLOBALHEADER_H */

