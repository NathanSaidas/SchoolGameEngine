#ifndef GAME_ENGINE_TYPE_H
#define GAME_ENGINE_TYPE_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added class/file Type.
#pragma endregion

#include <string>
#include <vector>
#include "Func.h"
#include "../Examples/Property.h"


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

        inline std::string GetName() const
        {
            return m_Name;
        }
        inline std::string GetBaseClass() const
        {
            return m_BaseClass;
        }
        inline int GetSize() const
        {
            return m_Size;
        }
        inline int GetAlignment() const
        {
            return m_Alignment;
        }
        inline int GetTypeID() const
        {
            return m_TypeID;
        }
        inline bool IsClass() const
        {
            return m_IsClass;
        }
        inline bool IsInterface() const
        {
            return m_IsInterface;
        }
        inline bool IsAbstract() const
        {
            return m_IsAbstract;
        }
        std::vector<std::string> GetInterfaces() const
        {
            return m_Interfaces;
        }
        std::vector<Reflection::ClassMember*> GetMembers() const
        {
            return m_Members;
        }
        Func<void*, void*> GetConstructor() const
        {
            return m_Constructor;
        }
        Func<void*, void*> GetDestructor() const
        {
            return m_Destructor;
        }

        bool operator== (Type & aType) const
        {
            return m_TypeID == aType.m_TypeID;
        }
        
        Property GetProperty(const std::string & aPropertyName) const
        {
            for (std::vector<Property>::const_iterator it = m_Properties.begin(); it != m_Properties.end(); it++)
            {
                if ((*it).GetName() == aPropertyName)
                {
                    return *it;
                }
            }
            return Property("", "");
        }

        std::vector<Property> GetProperties() const
        {
            return m_Properties;
        }

        void InsertProperty(Property aProperty)
        {
            if (s_IsCompiling)
            {
                m_Properties.push_back(aProperty);
            }
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
        std::vector<Property> m_Properties;
        Func<void*, void*> m_Constructor;
        Func<void*, void*> m_Destructor;

        static bool s_IsCompiling;

        friend Engine::Reflection::Runtime;
        //friend class PropertyBinder;
    };

    
}

#endif