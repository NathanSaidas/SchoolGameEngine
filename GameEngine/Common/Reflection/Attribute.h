#ifndef GAME_ENGINE_ATTRIBUTE_H
#define GAME_ENGINE_ATTRIBUTE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added Attribute class/file
#pragma endregion

#include <cstring>

namespace Engine
{
    namespace Reflection
    {
        ///This class define the base of all attributes to come.
        ///It holds information related to its attribute name and the class type
        ///it belongs to.
        class Attribute
        {
        public:
            Attribute(const char * aClassName, const char * aAttributeName)
            {
                m_ClassName = const_cast<char*>(aClassName);
                m_AttributeName = const_cast<char*>(aAttributeName);
            }

            inline char * GetClassName()
            {
                return m_ClassName;
            }
            inline char * GetAttributeName()
            {
                return m_AttributeName;
            }
            inline bool Is(const char * aName)
            {
                return strcmp(m_AttributeName, aName) == 0;
            }
        private:
            char * m_ClassName;
            char * m_AttributeName;
        };


    }
    
}

#endif