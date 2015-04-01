#ifndef GAME_ENGINE_REFLECTION_H
#define GAME_ENGINE_REFLECTION_H

#pragma region CHANGE LOG
/// -- January, 29, 2015 - Nathan Hanlan - Added file Reflection. Added TYPE_DEFINE, TYPE_DEFINE_PTR, TYPE_NAME macros
/// -- January, 30, 2015 - Nathan Hanlan - Added MetaObject / Runtime includes as well as macros for defining Types.
/// -- March,   15, 2015 - Nathan Hanlan - Added type traits for std::string
/// -- 
#pragma endregion

#include "Attribute.h"
#include "BoolAttribute.h"
#include "FloatAttribute.h"
#include "IntAttribute.h"
#include "StringAttribute.h"
#include "FunctionAttribute.h"
#include "TypeTrait.h"
#include "MetaObject.h"
#include "MetaObjectLinker.h"
#include "Runtime.h"
#include "AttributeBinder.h"
#include "ClassMember.h"
#include "MethodInfo.h"
#include "../Type.h"

//////////////////////
///AVAILABLE MACROS///
//////////////////////

//Note: No macros require any type to have their data held within parentheses. Any string conversion is handled automatically.

// -- OUT SIDE OF CLASS MACROS - These macros should be used outside of the class. (Note: This applies to headers)

//TYPEDEFINE (TYPE) - Defines a TypeTrait for the given TYPE
//TYPEDEFINE_PTR(TYPE,NAME) - Defines a TypeTrait for a givens TYPE's pointer version. The NAME is used to give a different name for pointer types.

// -- INSIDE CLASS MACROS - These macros are intended to be used within the class definition. (Note: This applies to headers.)

//CLASS_ (HEADER/CPP) - Defines a non abstract class for the reflection system.
//ABSTRACT_CLASS_ (HEADER/CPP) - Defines a abstract class for the reflection system.

//METHOD_INFO_HEADER(TYPE,METHOD_NAME) - Defines the method info inside the class file.
//METHOD_INFO_CPP(TYPE,METHOD_NAME, METHOD_INFO) - METHOD_INFO is any class that inherits from ClassMember. Usually a MethodInfo template class.

//CLASS_ATTRIBUTE_INTERFACE_ (HEADER/CPP) - Defines a interface that a class inherits from.

namespace Engine
{
    namespace Reflection
    {





#define TYPE_NAME(TYPE) Engine::Reflection::TypeTrait<TYPE>::Name()

#define CLASS_HEADER(TYPE)                                                          \
    static const Engine::Reflection::MetaObject<TYPE> ATTRIBUTE_CLASS;              \
    public:                                                                         \
    virtual Engine::Type GetType();                                                 \
    private:                                                                        \

#define CLASS_CPP(TYPE,BASECLASS)                                                                                                                               \
    const Engine::Reflection::MetaObject<TYPE> TYPE::ATTRIBUTE_CLASS = Engine::Reflection::MetaObject<TYPE>::DefineClass(#TYPE, #BASECLASS);    \
    Engine::Type TYPE::GetType() { static Engine::Type type = Engine::Reflection::Runtime::TypeOf(#TYPE); return type; }                \

#define ABSTRACT_CLASS_HEADER(TYPE) static const Engine::Reflection::MetaObject<TYPE> ATTRIBUTE_ABSTRACT_CLASS;
#define ABSTRACT_CLASS_CPP(TYPE,BASECLASS) const Engine::Reflection::MetaObject<TYPE> TYPE::ATTRIBUTE_ABSTRACT_CLASS = Engine::Reflection::MetaObject<TYPE>::DefineAbstractClass(#TYPE, #BASECLASS);

#define INTERFACE_HEADER(TYPE) static const Engine::Reflection::MetaObject<TYPE> ATTRIBUTE_INTERFACE; 
#define INTERFACE_CPP(TYPE) const Engine::Reflection::MetaObject<TYPE> TYPE::ATTRIBUTE_INTERFACE = Engine::Reflection::MetaObject<TYPE>::DefineInterface(#TYPE);

#define METHOD_INFO_HEADER(TYPE, METHOD_NAME) static const Engine::Reflection::MetaObject<TYPE> MEMBER_ ## TYPE ## _ ## METHOD_NAME;
#define METHOD_INFO_CPP(TYPE,METHOD_NAME,METHOD_INFO) const Engine::Reflection::MetaObject<TYPE> TYPE:: ## MEMBER_ ## TYPE ## _ ## METHOD_NAME = Engine::Reflection::MetaObject<TYPE>::DefineMember(#TYPE, METHOD_INFO);          


#define CLASS_ATTRIBUTE_INTERFACE_HEADER(TYPE,INTERFACE) static const Engine::Reflection::MetaObject<TYPE> ATTRIBUTE_ ## TYPE ## _ ## INTERFACE;
#define CLASS_ATTRIBUTE_INTERFACE_CPP(TYPE,INTERFACE) const Engine::Reflection::MetaObject<TYPE> TYPE:: ## ATTRIBUTE_ ## TYPE ## _ ## INTERFACE = Engine::Reflection::MetaObject<TYPE>::DefineClassInterface(#TYPE,#INTERFACE);

#define CLASS_PROPERTY_HEADER(TYPE,PROP_NAME) static const Engine::Reflection::MetaObject<TYPE> ATTRIBUTE_ ## TYPE ## _ ## PROP_NAME;
#define CLASS_PROPERTY_CPP(TYPE,PROP_NAME,PROP_VALUE) const Engine::Reflection::MetaObject<TYPE> TYPE:: ## ATTRIBUTE_ ## TYPE ## _ ## PROP_NAME = Engine::Reflection::MetaObject<TYPE>::DefineProperty(#TYPE, #PROP_NAME, #PROP_VALUE);

        ///Define Primitive Types to allow for limited reflection info.

		TYPE_DEFINE(char)
		TYPE_DEFINE(bool)
		TYPE_DEFINE(short)
		TYPE_DEFINE(int)
		TYPE_DEFINE(float)
		TYPE_DEFINE(double)
		TYPE_DEFINE(void)
		TYPE_DEFINE(long)
		TYPE_DEFINE(unsigned char)
		TYPE_DEFINE(unsigned short)
		TYPE_DEFINE(unsigned int)
		TYPE_DEFINE(unsigned long)
		TYPE_DEFINE(std::string)
		


		template<typename A,typename B>
		class TypeEqual
		{
		public:
			static bool IsEqual()
			{
				const char * a = TypeTrait<A>::Name();
				const char * b = TypeTrait<B>::Name();
				return strcmp(a, b) == 0;
			}
			
		};

		
    }

}

#endif