#ifndef GAME_ENGINE_INT_ATTRIBUTE_H
#define GAME_ENGINE_INT_ATTRIBUTE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added IntAttribute class/file
#pragma endregion

#include "Attribute.h"

namespace Engine
{
    namespace Reflection
    {
        ///IntAttribute describes a int value for a class type
        class IntAttribute : public Attribute
        {
        public:
            IntAttribute(const char * aClassName, const char * aAttributeName, int aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }

            inline int GetValue()
            {
                return m_Value;
            }
        private:
            int m_Value;
        };


    }
    
}

#endif