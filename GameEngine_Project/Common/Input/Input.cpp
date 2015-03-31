#include "Input.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../Reflection/Reflection.h"
#include "../Memory/Memory.h"
#include "../Windows/Application.h"
#include "InputAxis.h"
namespace Engine
{
    using namespace Reflection;

	CLASS_CPP(Input,Object)

    Input * Input::s_Instance = nullptr;
	void Input::Initialize()
	{
		Instance();
	}
    Input * Input::Instance()
    {
        if(s_Instance == nullptr)
        {
			s_Instance = new Input();
        }
        return s_Instance;
    }
    void Input::Terminate()
    {
        if(s_Instance != nullptr)
        {
			delete s_Instance;
			s_Instance = nullptr;
        }
    }

    Input::Input()
    {
        //For use when allocating memory dynamically.
        //However there is a weird memory glitch.
        //m_Keys = Memory::instantiate<Key*>();
        //m_MouseButtons = Memory::instantiate<Button*>();

        for(int i = 0; i < (int)KeyCode::KEY_COUNT; i++)
        {
            m_Keys.push_back(MEM_POOL_ALLOC_T(Key));
        }
        for(int i = 0; i < (int)MouseButton::COUNT; i++)
        {
            m_MouseButtons.push_back(MEM_POOL_ALLOC_T(Button));
        }
        m_CurrentWindowID = -1;
    }
    Input::~Input()
    {
        for(int i = 0; i < (int)KeyCode::KEY_COUNT; i++)
        {
			MEM_POOL_DEALLOC_T(m_Keys[i], Key);
        }
        for(int i = 0; i < (int)MouseButton::COUNT; i++)
        {
			MEM_POOL_DEALLOC_T(m_MouseButtons[i], Button);
        }

        m_Keys.clear();
        m_MouseButtons.clear();
        //For use when allocating memory dynamically.
        //However there is a weird memory glitch.
        //m_Keys = Memory::Destroy<Key*>(m_Keys,(int)KeyCode::COUNT);
        //m_MouseButtons = Memory::Destroy<Button*>(m_MouseButtons,(int)MouseButton::COUNT);

        for(int i = 0; i < m_Axis.size(); i++)
        {
            //m_Axis[i] = Memory::Destroy<InputAxis>(m_Axis[i]);
			MEM_POOL_DEALLOC_T(m_Axis[i], InputAxis);
        }
        m_Axis.clear();
    }

    //int Input::GetKeyState(KeyCode aKeyCode)
    //{
    //    GLFWwindow * currentWindow = WindowManager::Instance()->GetCurrentWindow();
    //    if(currentWindow == nullptr)
    //    {
    //        return -1;
    //    }
    //    return 0;
    //
    //}

    void Input::Update()
    {
        for(int i = 0; i < m_Axis.size(); i++)
        {
            if(m_Axis[i] != nullptr)
            {
                m_Axis[i]->Update();
            }
        }

        for(int i = 0; i < (int)KeyCode::KEY_COUNT; i++)
        {
            if(m_Keys[i] != nullptr)
            {
                m_Keys[i]->Update();
            }
        }
        for(int i = 0; i < (int)MouseButton::COUNT; i++)
        {
            if(m_MouseButtons[i] != nullptr)
            {
                m_MouseButtons[i]->Update();
            }
        }

        m_MouseScrollWheel.x = 0.0f;
        m_MouseScrollWheel.y = 0.0f;

        //int currentWindow = WindowManager::Instance()->GetFocusedWindow();
        //if(currentWindow != m_CurrentWindowID)
        //{
        //    //Window focus has changed
        //}
        //m_CurrentWindowID = currentWindow;
        glfwPollEvents();
    }

    void Input::ProcessKeyEvent(int aKey, int aAction, int aMods)
    {
        if(aKey < 0 || aKey >= (int)KeyCode::KEY_COUNT)
        {
            //ignore
            return;
        }
        m_Keys[aKey]->OnEvent(aAction);

    }
    void Input::ProcessMouseEvent(int aButton, int aAction, int aMods)
    {
        if(aButton < 0 || aButton >= (int)MouseButton::COUNT)
        {
            return;
        }
        m_MouseButtons[aButton]->OnEvent(aAction);
    }
    void Input::ProcessMouseMove(Float32 aX, Float32 aY)
    {
        m_LastMousePosition = m_MousePosition;

        m_MousePosition.x = aX;
        m_MousePosition.y = aY;
    }
    //x and y represent direction
	void Input::ProcessMouseScroll(Float32 aX, Float32 aY)
    {
        m_MouseScrollWheel.x = aX;
        m_MouseScrollWheel.y = aY;
    }

    void Input::DestroyAxis(string aName)
    {
        for(unsigned int i = 0; i < m_Axis.size(); i++)
        {
            if(m_Axis[i]->Name() == aName)
            {
                InputAxis * axis = m_Axis[i];
                m_Axis.erase(m_Axis.begin() + i);
                //axis = Memory::Destroy<InputAxis>(axis);
				MEM_POOL_DEALLOC_T(axis, InputAxis);
                return;
            }
        }
    }
    void Input::CreateAxis(string aName)
    {
        CreateAxis(aName,AxisCode::NONE,AxisCode::NONE);
    }
    void Input::CreateAxis(string aName, AxisCode aPositiveKey, AxisCode aNegativeKey)
    {
		InputAxis * inputAxis = MEM_POOL_ALLOC_T(InputAxis); 
        inputAxis->SetName(aName);
        inputAxis->SetPositiveKey(aPositiveKey,0);
        inputAxis->SetNegativeKey(aNegativeKey,0);
        m_Axis.push_back(inputAxis);
    }
    void Input::SetAxisPositiveKey(string aName, AxisCode aKeyCode, int aKey)
    {
		for (std::vector<InputAxis*>::iterator it = m_Axis.begin(); it != m_Axis.end(); it++)
		{
			InputAxis * axis = *it;
			if (axis->Name() == aName)
			{
				axis->SetPositiveKey(aKeyCode, aKey);
				return;
			}
		}
    }
    void Input::SetAxisNegativeKey(string aName, AxisCode aKeyCode, int aKey)
    {
		for (std::vector<InputAxis*>::iterator it = m_Axis.begin(); it != m_Axis.end(); it++)
		{
			InputAxis * axis = *it;
			if (axis->Name() == aName)
			{
				axis->SetNegativeKey(aKeyCode, aKey);
				return;
			}
		}
    }
    void Input::SetAxisReSetOnRelease(string aName, bool aResetflag)
    {
		for (std::vector<InputAxis*>::iterator it = m_Axis.begin(); it != m_Axis.end(); it++)
		{
			InputAxis * axis = *it;
			if (axis->Name() == aName)
			{
				axis->SetResetOnRelease(aResetflag);
				return;
			}
		}
    }

    float Input::GetAxis(string aName)
    {
		for (std::vector<InputAxis*>::iterator it = m_Axis.begin(); it != m_Axis.end(); it++)
		{
			InputAxis * axis = *it;
			if (axis->Name() == aName)
			{
				return axis->AxisValue();
			}
		}
		return 0.0f;
    }
    AxisCode Input::GetAxisPositiveKey(string aName, int aKey)
    {
        for(int i = 0; i < m_Axis.size(); i++)
        {
            if(m_Axis[i]->Name() == aName)
            {
                return m_Axis[i]->PositiveKey(aKey);
            }
        }
        return AxisCode::NONE;
    }
    AxisCode Input::GetAxisNegativeKey(string aName, int aKey)
    {
        for(int i = 0; i < m_Axis.size(); i++)
        {
            if(m_Axis[i]->Name() == aName)
            {
                return m_Axis[i]->NegativeKey(aKey);
            }
        }
        return AxisCode::NONE;
    }
    bool Input::GetAxisResetOnRelease(string aName)
    {
        for(int i = 0; i < m_Axis.size(); i++)
        {
            if(m_Axis[i]->Name() == aName)
            {
                return m_Axis[i]->ReSetOnRelease();
            }
        }
        return true;
    }

       

}