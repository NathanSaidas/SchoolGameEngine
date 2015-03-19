#ifndef GAME_ENGINE_FRUSTUM_H
#define GAME_ENGINE_FRUSTUM_H

#include "../BasicTypes.h"

namespace Engine
{
    struct Frustum
    {
        Float32 top;
        Float32 bottom;
        Float32 left;
        Float32 right;
        Float32 near;
        Float32 far;
    };
}

#endif