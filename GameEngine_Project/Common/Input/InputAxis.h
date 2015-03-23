#ifndef GAME_ENGINE_INPUT_AXIS_H
#define GAME_ENGINE_INPUT_AXIS_H

#include "../BasicTypes.h"
#include "Key.h"

namespace Engine
{


    class InputAxis : public Object
    {
		CLASS_HEADER(InputAxis)
    public:
        InputAxis();
        ~InputAxis();

        void Update();

        void SetName(string aName);
        void SetResetOnRelease(bool aReSetFlag);
        void SetPositiveKey(AxisCode aCode, int aKey);
        void SetNegativeKey(AxisCode aCode, int aKey);

        string Name();
        bool ReSetOnRelease();
        AxisCode PositiveKey(int aKey);
        AxisCode NegativeKey(int aKey);
        float AxisValue();

    private:
        static const int MAX_AXIS_KEYS = 2;
        static const float AXIS_INCREMENT_SPEED;
        
        string m_Name;
        bool m_ReSetOnRelease;
        float m_CurrentValue;
        
        
        AxisCode m_PositiveKeys[MAX_AXIS_KEYS];
        AxisCode m_NegativeKeys[MAX_AXIS_KEYS];
        

    };

	TYPE_DEFINE(InputAxis)
	TYPE_DEFINE_PTR(InputAxis*, "InputAxis Ptr")
}

#endif