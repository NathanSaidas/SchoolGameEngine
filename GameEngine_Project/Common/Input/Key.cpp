#include "Key.h"
#include "../Reflection/Reflection.h"
#include "../Windows/Application.h"

namespace Engine
{
    using namespace Reflection;

	RDEFINE_CLASS(Key, Object)
    Key::Key()
    {
        m_CurrentState = ButtonState::UP;
    }
    Key::~Key()
    {

    }

    void Key::Update()
    {
        if(m_CurrentState == ButtonState::PRESS)
        {
            m_CurrentState = ButtonState::DOWN;
        }
        else if(m_CurrentState == ButtonState::RELEASE)
        {
            m_CurrentState = ButtonState::UP;
        }
    }
    void Key::OnEvent(int aAction)
    {
        if(aAction == GLFW_PRESS)
        {
            m_CurrentState = ButtonState::PRESS;
        }
        else if(aAction == GLFW_RELEASE)
        {
            m_CurrentState = ButtonState::RELEASE;
        }
    }
    bool Key::IsDown()
    {
        if(m_CurrentState == ButtonState::DOWN || m_CurrentState == ButtonState::PRESS)
        {
            return true;
        }
        return false;
    }
    bool Key::IsUp()
    {
        if(m_CurrentState == ButtonState::UP || m_CurrentState == ButtonState::RELEASE)
        {
            return true;
        }
        return false;
    }
    ButtonState Key::CurrentState()
    {
        return m_CurrentState;
    }


}