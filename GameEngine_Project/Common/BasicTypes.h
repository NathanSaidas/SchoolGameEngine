#ifndef GAME_ENGINE_BASIC_TYPES_H
#define GAME_ENGINE_BASIC_TYPES_H

#include "ValueTypes.h"
#include "Reflection\Reflection.h"

namespace Engine
{    

    

	/// <summary>
	/// This is the base class of all objects within the engine.
	/// </summary>
	class object
	{
		CLASS_HEADER(object);
	public:
		object();
		~object();


		virtual string ToString();
	};

	/// <summary>
	/// An extended version of the object class to include naming of objects.
	/// </summary>
	class Object : public object
	{ 
		CLASS_HEADER(Object)
	public:
		Object();
		~Object();
		string GetName();
		void SetName(const string & aName);
		void SetName(const char * aName);

		string ToString();
	private:
		string m_Name;

	};

	
	TYPE_DEFINE(object)
	TYPE_DEFINE(Object)




}

#endif