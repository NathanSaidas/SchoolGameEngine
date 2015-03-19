#ifndef GAME_ENGINE_STRING_ATTRIBUTE_H
#define GAME_ENGINE_STRING_ATTRIBUTE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added StringAttribute class/header
#pragma endregion

#include "Attribute.h"
#include <string>

namespace Engine
{
    namespace Reflection
    {
        ///StringAttribute describes a floating value for a class type
        class StringAttribute : public Attribute
        {
        public:
            StringAttribute(const char * aClassName, const char * aAttributeName, std::string aValue)
                : Attribute(aClassName, aAttributeName)
            {
                m_Value = aValue;
            }

            inline std::string GetValue()
            {
                return m_Value;
            }
        private:
            std::string m_Value;
        };


    }
    
}

#endif