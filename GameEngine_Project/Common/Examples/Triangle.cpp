#include "Triangle.h"


using namespace Engine::Reflection;

namespace Engine
{
    CLASS_CPP(Triangle, Shape)
    METHOD_INFO_CPP(Triangle, GetVertexCount, (new MethodInfo<Triangle,int>("Triangle", "GetVertexCount", (&Triangle::GetVertexCount))))
    METHOD_INFO_CPP(Triangle, Update, (new MethodActionInfo<Triangle>("Triangle","Update",(&Triangle::Update))))

    CLASS_PROPERTY_CPP(Triangle, CustomPropRadProp, This is a RadProperty)
	Triangle::Triangle() : Shape()
	{
        
	}

	Triangle::~Triangle()
	{
        
	}

	void Triangle::Update()
	{

	}

	int Triangle::GetVertexCount()
	{
		return 3;
	}
}