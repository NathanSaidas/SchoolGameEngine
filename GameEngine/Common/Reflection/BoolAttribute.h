#ifndef GAME_ENGINE_BOOL_ATTRIBUTE_H
#define GAME_ENGINE_BOOL_ATTRIBUTE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added BoolAttribute class/file
#pragma endregion

#include "Attribute.h"

namespace Engine
{
    namespace Reflection
    {
        ///BoolAttribute describes a boolean value for a class type
        class BoolAttribute : public Attribute
        {
        public:
            BoolAttribute(const char * aClassName, const char * aAttributeName, bool aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }
            inline bool GetValue()
            {
                return m_Value;
            }
        private:
            bool m_Value;
        };


    }
    
}

#endif