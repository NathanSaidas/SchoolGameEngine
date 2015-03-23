#ifndef GAME_ENGINE_GEOMETRY_H
#define GAME_ENGINE_GEOMETRY_H

#include "../BasicTypes.h"
#include "../Memory/AllocatorType.h"

namespace Engine
{
	class Mesh;
	class Color;

	class Geometry : public object
	{
		CLASS_HEADER(Geometry)
	public:
		Geometry();
		~Geometry();


		static Mesh * CreatePlane(Float32 aWidth, Float32 aHeight,const Color & aColor, const Memory::AllocatorType & AllocType);
		static Mesh * CreateCube(Float32 aWidth, Float32 aHeight, Float32 aDepth, const Color & aColor, const Memory::AllocatorType & aAllocatorType);

	private:

	};

	TYPE_DEFINE(Geometry)
	TYPE_DEFINE_PTR(Geometry*, "Geometry Ptr")
}


#endif