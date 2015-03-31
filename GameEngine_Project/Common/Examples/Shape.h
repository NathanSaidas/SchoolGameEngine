#ifndef SHAPE_H
#define SHAPE_H

#include "../Engine.h"



namespace Engine
{
	class Shape
	{
		ABSTRACT_CLASS_HEADER(Shape)
	public:
		//static const System::Reflection::MetaObject<Shape> ATTRIBUTE_ABSTRACT_CLASS;
		

		Shape();
		virtual ~Shape();
		virtual void Update() = 0;
		virtual int GetVertexCount() = 0;


	};

	TYPE_DEFINE(Shape)
}

#endif