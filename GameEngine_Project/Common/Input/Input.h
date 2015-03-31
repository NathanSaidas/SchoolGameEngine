#ifndef GAME_ENGINE_INPUT_H
#define GAME_ENGINE_INPUT_H
#include <vector>
#include <string>
#include "../BasicTypes.h"
#include "../Math/Math.h"
#include "KeyDef.h"
#include "Key.h"

namespace Engine
{
    class InputAxis;
    class Input : public Object
    {
		CLASS_HEADER(Input)
    public:
		static void Initialize();
        static Input * Instance();
        static void Terminate();

        //int GetKeyState(KeyCode aKeyCode);

        //returns true if key is down (press)
        inline
        bool GetKeyDown(KeyCode aKeyCode)
        {
            if(m_Keys[(int)aKeyCode] != nullptr)
            {
                return m_Keys[(int)aKeyCode]->CurrentState() == ButtonState::PRESS;
            }
            return false;
        }
        //returns true if the key is up (released)
        
        inline bool GetKeyUp(KeyCode aKeyCode)
        {
            if(m_Keys[(int)aKeyCode] != nullptr)
            {
                return m_Keys[(int)aKeyCode]->CurrentState() == ButtonState::RELEASE;
            }
            return false;
        }

        //returns true if the key is down or pressed
        //returns false if the key is up or released
        
        inline bool GetKey(KeyCode aKeyCode)
        {
            if(m_Keys[(int)aKeyCode] != nullptr)
            {
                return m_Keys[(int)aKeyCode]->IsDown() == true;
            }
            return false;
        }
        inline bool GetMouseButtonDown(MouseButton aButton)
        {
            if(m_MouseButtons[(int)aButton] != nullptr)
            {
                return m_MouseButtons[(int)aButton]->CurrentState() == ButtonState::PRESS;
            }
            return false;
        }
        inline bool GetMouseButtonUp(MouseButton aButton)
        {
            if(m_MouseButtons[(int)aButton] != nullptr)
            {
                return m_MouseButtons[(int)aButton]->CurrentState() == ButtonState::RELEASE;
            }
            return false;
        }
        inline bool GetMouseButton(MouseButton aButton)
        {
            if(m_MouseButtons[(int)aButton] != nullptr)
            {
                return m_MouseButtons[(int)aButton]->IsDown() == true;
            }
            return false;
        }
        inline Vector2 ScrollDirection()
        {
            return m_MouseScrollWheel;
        }
        inline Vector2 MousePosition()
        {
            return m_MousePosition;
        }
        inline Vector2 LastMousePosition()
        {
            return m_LastMousePosition;
        }
        inline Vector2 DeltaMousePosition()
        {
            return Math::Abs(m_MousePosition - m_LastMousePosition);
        }

        ///Input Axis Functions
        void DestroyAxis(string aName);
        void CreateAxis(string aName);
        void CreateAxis(string aName, AxisCode aPositiveKey, AxisCode aNegativeKey);
        void SetAxisPositiveKey(string aName, AxisCode aKeyCode, int aKey);
        void SetAxisNegativeKey(string aName, AxisCode aKeyCode, int aKey);
        void SetAxisReSetOnRelease(string, bool aReSetflag);

        float GetAxis(string aName);
        AxisCode GetAxisPositiveKey(string aName , int aKey);
        AxisCode GetAxisNegativeKey(string aName , int aKey);
        bool GetAxisResetOnRelease(string aName );

        Input();
        ~Input();
    private:
        //Key * m_Keys[(int)KeyCode::COUNT];
        //Button * m_MouseButtons[(int)MouseButton::COUNT];
        std::vector<Key*> m_Keys;
        std::vector<Button*> m_MouseButtons;

        Vector2 m_MouseScrollWheel;

        Vector2 m_MousePosition;
        Vector2 m_LastMousePosition;
        int m_CurrentWindowID;


        std::vector<InputAxis*> m_Axis;

        static Input * s_Instance;
        


        void Update();

        void ProcessKeyEvent(int aKey, int aAction, int aMods);
        void ProcessMouseEvent(int aButton, int aAction, int aMods);
        void ProcessMouseMove(float aX, float aY);
        void ProcessMouseScroll(float aX, float aY);

        friend class Application;
    };
	TYPE_DEFINE(Input)
}

#endif