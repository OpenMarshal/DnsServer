/* 
 * File:   GlobalHeader.h
 * Author: Adrien Castex
 *
 * Created on 2 septembre 2015, 23:17
 */

#ifndef GLOBALHEADER_H
#define	GLOBALHEADER_H

#include "Defines.h"

#if DEBUG
#define debug(format, args...) printf(format, ##args); _flushall();
#else
#define debug(format, args...) ;
#endif

#include "Types.h"
#include <stdio.h>


#endif	/* GLOBALHEADER_H */

