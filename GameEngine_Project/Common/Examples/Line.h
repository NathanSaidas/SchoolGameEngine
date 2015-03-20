#ifndef LINE_H
#define LINE_H

#include "Shape.h"

namespace Engine
{
	class Line : Shape
	{
        CLASS_HEADER(Line)
        METHOD_INFO_HEADER(Line, Update)
        METHOD_INFO_HEADER(Line, GetVertexCount)
	public:
		Line();
		~Line();
		void Update();
		int GetVertexCount();
	};

    TYPE_DEFINE(Line)
    TYPE_DEFINE_PTR(Line*, "Line Ptr")
}

#endif