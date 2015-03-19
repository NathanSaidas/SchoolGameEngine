#ifndef GAME_ENGINE_CLASS_MEMBER_INFO_H
#define GAME_ENGINE_CLASS_MEMBER_INFO_H

#pragma region CHANGE LOG
/// -- January, 30, 2015 - Nathan Hanlan - Added ClassMember class/file 
#pragma endregion

#include <string>

namespace Engine
{
    namespace Reflection
    {

        class ClassMember
        {
        public:
            ClassMember(std::string aClassName, std::string aMemberName)
            {
                m_ClassName = aClassName;
                m_MemberName = aMemberName;
            }

            inline std::string GetClassName()
            {
                return m_ClassName;
            }
            inline std::string GetMemberName()
            {
                return m_MemberName;
            }

        private:
            std::string m_ClassName;
            std::string m_MemberName;
        };
    }
    
}

#endif