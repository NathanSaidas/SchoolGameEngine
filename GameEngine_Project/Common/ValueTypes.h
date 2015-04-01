#ifndef GAME_ENGINE_VALUE_TYPES_H
#define GAME_ENGINE_VALUE_TYPES_H

// File just defines basic value types.

#include <limits>
#include <string>

namespace Engine
{
    //See minimum size of the data types defined by the standard at
    //http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf 
    //Sec 5.2.4.2.1 Sizes of Integer Types page 21-22

    typedef unsigned char       UInt8;
    typedef unsigned short      UInt16;
    typedef unsigned long       UInt32;
    typedef unsigned long long  UInt64;
    typedef signed char         SInt8;
    typedef signed short        SInt16;
    typedef signed long         SInt32;
    typedef signed long long    SInt64;
    typedef float               Float32;
    typedef double              Float64;

    typedef uintptr_t           IntPtr;

    typedef std::string string;
}

#endif