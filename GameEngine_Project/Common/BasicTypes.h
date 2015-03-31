#ifndef GAME_ENGINE_BASIC_TYPES_H
#define GAME_ENGINE_BASIC_TYPES_H

#include <limits>
#include <string>
#include "Reflection\Reflection.h"

namespace Engine
{    

    //See minimum size of the data types defined by the standard at
    //http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf 
    //Sec 5.2.4.2.1 Sizes of Integer Types page 21-22

    typedef unsigned char       UInt8;
    typedef unsigned short      UInt16;
    typedef unsigned long       UInt32;
    typedef unsigned long long  UInt64;
    typedef signed char         SInt8;
    typedef signed short        SInt16;
    typedef signed long         SInt32;
    typedef signed long long    SInt64;
    typedef float               Float32;
    typedef double              Float64;

    typedef uintptr_t           IntPtr;

	typedef std::string string;

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