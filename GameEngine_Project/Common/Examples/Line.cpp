#include "Line.h"

using namespace Engine::Reflection;

namespace Engine
{
	CLASS_CPP(Line,Shape)
    METHOD_INFO_CPP(Line, Update, (new MethodActionInfo<Line>("Line","Update",(&Line::Update))))
    METHOD_INFO_CPP(Line, GetVertexCount, (new MethodInfo<Line,int>("Line","GetVertexCount",(&Line::GetVertexCount))))
	Line::Line() : Shape()
	{

	}

	Line::~Line()
	{

	}

	void Line::Update()
	{

	}

	int Line::GetVertexCount()
	{
		return 2;
	}
}