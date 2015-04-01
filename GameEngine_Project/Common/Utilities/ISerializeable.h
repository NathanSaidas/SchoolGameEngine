#ifndef GAME_ENGINE_I_SERIALIZEABLE_H
#define GAME_ENGINE_I_SERIALIZEABLE_H

#include "../BasicTypes.h"
#include "Stream.h"
#include "IFormatter.h"

namespace Engine
{
    class ISerializeable
    {
        INTERFACE_HEADER(ISerializeable)
    public:
        virtual void OnSerialize(IFormatter * aFormatter, Stream & aStream) = 0;
        virtual void OnDeserialize(IFormatter * aFormatter, Stream & aStream) = 0;
    };

    TYPE_DEFINE(ISerializeable)
}

#endif