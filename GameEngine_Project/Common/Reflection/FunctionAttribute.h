#ifndef GAME_ENGINE_FUNCTION_ATTRIBUTE_H
#define GAME_ENGINE_FUNCTION_ATTRIBUTE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added FunctionAttribute class/file
#pragma endregion

#include "Attribute.h"
#include "../Func.h"

namespace Engine
{
    namespace Reflection
    {
        ///FunctionAttribute describes a function with a void * return and void * arg function.
        class FunctionAttribute : public Attribute
        {
        public:
            FunctionAttribute(const char * aClassName, const char * aAttributeName, Func<void*, void*> aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }
            inline Func<void*, void*> GetValue()
            {
                return m_Value;
            }
        private:
            Func<void*, void*> m_Value;
        };


    }
    
}

#endif