#ifndef GAME_ENGINE_SYSTEM_ASSERT_H
#define GAME_ENGINE_SYSTEM_ASSERT_H

#pragma region CHANGE LOG
/// January, 31, 2015 - Nathan Hanlan - Added file SystemAssert
/// February, 2, 2015 - Nathan Hanlan - Added macro for asserting with filename as well as overloaded method to assert with filename.
#pragma endregion


#include <iostream>
#include <assert.h>

namespace Engine
{

#define ASSERT_TRACE
#define ASSERT(EXPRESSION,MESSAGE) Assert(EXPRESSION,MESSAGE,__FILE__,__LINE__)



    inline void Assert(bool aExpression, const char * aMessage)
    {
        if (aExpression == false)
        {
            std::cerr << aMessage << std::endl;
            assert(aExpression);
        }
    }

    inline void Assert(bool aExpression, const char * aMessage, const char * aFile, unsigned int aLine)
    {
        if (aExpression == false)
        {
            std::cerr << aMessage << " " << aFile << "(" << aLine << ")\n";
            assert(aExpression);
        }
    }

}

#endif