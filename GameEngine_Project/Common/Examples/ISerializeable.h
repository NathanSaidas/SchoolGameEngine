#ifndef I_SERIALIZEABLE_H
#define I_SERIALIZEABLE_H

#include "../Engine.h"

namespace Engine
{
    class ISerializeable
    {
        INTERFACE_HEADER(ISerializeable)
    public:
        virtual void OnSerialize() = 0;
        virtual void OnDeserialize() = 0;
    };
}

#endif