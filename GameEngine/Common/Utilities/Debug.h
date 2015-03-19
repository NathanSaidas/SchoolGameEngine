#ifndef GAME_ENGINE_DEBUG_H
#define GAME_ENGINE_DEBUG_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

namespace Engine
{
    namespace Utilities
    {
#define DEBUG_LOG( FORMAT, ...)  printf(FORMAT,__VA_ARGS__); printf("\n")

        //class Debug
        //{
        //public:
        //    static void Log(const char * aMessage)
        //    {
        //        printf(aMessage);
        //    }
        //    
        //    static void LogFormat(const char * aFormat, ...)
        //    {
        //        va_list ap;
        //        va_start(ap, count);
        //        va_arg(ap,)
        //
        //        printf(aFormat, aArgs);
        //    }
        //};
    }
    
}


#endif