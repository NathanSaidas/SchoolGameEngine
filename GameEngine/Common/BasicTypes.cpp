#include "BasicTypes.h"

namespace Engine
{
	CLASS_CPP(object, "");
	CLASS_CPP(Object, object);

	object::object()
	{

	}
	object::~object()
	{

	}
	string object::ToString()
	{
		return "object";
	}

	Object::Object() : object()
	{

	}
	Object::~Object()
	{

	}

	string Object::ToString()
	{
		return string("Object: ").append(m_Name);
	}

	string Object::GetName()
	{
		return m_Name;
	}
	void Object::SetName(const string & aName)
	{
		m_Name = aName;
	}

	void Object::SetName(const char * aName)
	{
		m_Name = aName;
	}


}