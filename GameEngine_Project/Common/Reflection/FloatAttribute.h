#ifndef GAME_ENGINE_FLOAT_ATTRIBUTE_H
#define GAME_ENGINE_FLOAT_ATTRIBUTE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added FloatAttribute class/file
#pragma endregion

#include "Attribute.h"

namespace Engine
{
    namespace Reflection
    {
        ///FloatAttribute describes a floating value for a class type
        class FloatAttribute : public Attribute
        {
        public:
            FloatAttribute(const char * aClassName, const char * aAttributeName, float aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }
            inline float GetValue()
            {
                return m_Value;
            }
        private:
            float m_Value;
        };


    }
    
}

#endif