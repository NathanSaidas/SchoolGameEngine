#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

namespace Engine
{
	class Triangle : Shape
	{
        CLASS_HEADER(Triangle)
        METHOD_INFO_HEADER(Triangle, GetVertexCount);
        METHOD_INFO_HEADER(Triangle, Update);

        CLASS_PROPERTY_HEADER(Triangle, CustomPropRadProp)
	public:
		Triangle();
		~Triangle();
		void Update();
		int GetVertexCount();
	};

	TYPE_DEFINE(Triangle)
    TYPE_DEFINE_PTR(Triangle*, "Triangle Ptr")
}

#endif