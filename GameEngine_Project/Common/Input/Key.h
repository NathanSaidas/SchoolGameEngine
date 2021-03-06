#ifndef GAME_ENGINE_KEY_H
#define GAME_ENGINE_KEY_H

#include "../BasicTypes.h"
#include "KeyDef.h"

namespace Engine
{
    class Key : public Object
    {
		RDECLARE_CLASS(Key)
    public:
        Key();
        virtual ~Key();

        void Update();

        void OnEvent(int aAction);
        bool IsDown();
        bool IsUp();
        ButtonState CurrentState();
        
    protected:
        ButtonState m_CurrentState;
    };
    typedef Key Button;
	TYPE_DEFINE(Key);
}

#endif