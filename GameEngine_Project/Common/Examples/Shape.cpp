#include "Shape.h"


using namespace Engine::Reflection;

namespace Engine
{

	//const MetaObject<Shape> Shape::ATTRIBUTE_ABSTRACT_CLASS = MetaObject<Shape>::DefineAbstractClass("Shape", "");
	ABSTRACT_CLASS_CPP(Shape, "")

	Shape::Shape()
	{

	}
	Shape::~Shape()
	{

	}
}