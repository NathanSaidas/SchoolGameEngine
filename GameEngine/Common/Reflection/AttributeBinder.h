#ifndef GAME_ENGINE_ATTRIBUTE_BINDER_H
#define GAME_ENGINE_ATTRIBUTE_BINDER_H

#pragma region CHANGE LOG
/// -- January, 30, 2015 - Nathan Hanlan - Added AttributeBinder class/file 
#pragma endregion

#include "IntAttribute.h"
#include "FloatAttribute.h"
#include "BoolAttribute.h"
#include "StringAttribute.h"
#include "FunctionAttribute.h"
#include "../Type.h"


namespace Engine
{
    namespace Reflection
    {
        class AttributeBinder
        {
        public:
            virtual void BindInteger(IntAttribute & aAttribute, Type & aType) = 0;
            virtual void BindFloat(FloatAttribute & aAttribute, Type & aType) = 0;
            virtual void BindBool(BoolAttribute & aAttribute, Type & aType) = 0;
            virtual void BindString(StringAttribute & aAttribute, Type & aType) = 0;
            virtual void BindFunction(FunctionAttribute & aAttribute, Type & aType) = 0;
        };
    }
	
}

#endif