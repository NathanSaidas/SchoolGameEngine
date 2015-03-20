#ifndef GAME_ENGINE_PROPERTY_H
#define GAME_ENGINE_PROPERTY_H

#include <string>

namespace Engine
{

    class Property
    {
    public:
        Property(const std::string & aName,const  std::string & aValue)
        {
            m_Name = aName;
            m_Value = aValue;
        }
        inline std::string GetName()
        {
            return m_Name;
        }
        inline std::string GetValue()
        {
            return m_Value;
        }

    private:

        std::string m_Name;
        std::string m_Value;
    };

}

#endif