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
		Color();
		Color(Float32 r, Float32 g, Float32 b, Float32 a);
		~Color();
		
        Float32 r;
        Float32 g;
        Float32 b;
        Float32 a;

		inline static const Color White() 
		{
			return Color(1.0f, 1.0f, 1.0f, 1.0f);
		}
		inline static const Color Black() 		
		{
			return Color(0.0f, 0.0f, 0.0f, 1.0f);
		}

		inline static const Color Crimson()
		{
			return ByteToFloat(220.0f, 20.0f, 60.0f);
		}
		inline static const Color Indigo()
		{
			return ByteToFloat(75.0f, 0.0f, 130.0f);
		}
		inline static const Color CornflowerBlue()
		{
			return ByteToFloat(100.f, 149.0f, 237.0f);
		}
		inline static const Color MidnightBlue()
		{
			return ByteToFloat(25.0f, 25.0f, 112.0f);
		}
		inline static const Color Turquoise()
		{
			return ByteToFloat(64.0f, 224.0f, 208.0f);
		}

		inline static const Color ByteToFloat(Float32 r, Float32 g, Float32 b, Float32 aAlpha = 1.0f)
		{
			return Color(r / 255.0f, g / 255.0f, b / 250.0f, aAlpha);
		}
    };

    TYPE_DEFINE(Color)
}

#endif