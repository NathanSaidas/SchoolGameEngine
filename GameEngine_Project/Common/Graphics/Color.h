#ifndef GAME_ENGINE_COLOR_H
#define GAME_ENGINE_COLOR_H


#include "../BasicTypes.h"

namespace Engine
{
    //TODO: Implement functions such as mixing / lerping and static constant color values
    class Color : public object
    {
        CLASS_HEADER(Color)
    public:
        Float32 r;
        Float32 g;
        Float32 b;
        Float32 a;
    };

    TYPE_DEFINE(Color)
    TYPE_DEFINE_PTR(Color*, "Color Ptr")
}

#endif