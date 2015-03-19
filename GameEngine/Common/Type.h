#ifndef GAME_ENGINE_TYPE_H
#define GAME_ENGINE_TYPE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added class/file Type.
#pragma endregion

#include <string>
#include <vector>
#include "Func.h"


namespace Engine
{

    namespace Reflection
    {
        class Runtime;
        class ClassMember;
    }

    class Type
    {
    public:
        Type()
        {
            m_Name = "";
            m_BaseClass = "";
            m_Size = 0;
            m_Alignment = 0;
            m_TypeID = -1;
            m_IsClass = false;
            m_IsAbstract = false;
            m_IsInterface = false;
            m_Constructor = nullptr;
            m_Destructor = nullptr;
        }

        inline std::string GetName()
        {
            return m_Name;
        }
        inline std::string GetBaseClass()
        {
            return m_BaseClass;
        }
        inline int GetSize()
        {
            return m_Size;
        }
        inline int GetAlignment()
        {
            return m_Alignment;
        }
        inline int GetTypeID()
        {
            return m_TypeID;
        }
        inline bool IsClass()
        {
            return m_IsClass;
        }
        inline bool IsInterface()
        {
            return m_IsInterface;
        }
        inline bool IsAbstract()
        {
            return m_IsAbstract;
        }
        std::vector<std::string> GetInterfaces()
        {
            return m_Interfaces;
        }
        std::vector<Reflection::ClassMember*> GetMembers()
        {
            return m_Members;
        }
        Func<void*, void*> GetConstructor()
        {
            return m_Constructor;
        }
        Func<void*, void*> GetDestructor()
        {
            return m_Destructor;
        }

        bool operator== (Type & aType)
        {
            return m_TypeID == aType.m_TypeID;
        }



    private:
        std::string m_Name;
        std::string m_BaseClass;
        int m_Size;
        int m_Alignment;
        int m_TypeID;
        bool m_IsClass;
        bool m_IsInterface;
        bool m_IsAbstract;
        std::vector<std::string> m_Interfaces;
        std::vector<Reflection::ClassMember*> m_Members;
        Func<void*, void*> m_Constructor;
        Func<void*, void*> m_Destructor;


        friend Engine::Reflection::Runtime;
    };


}

#endif