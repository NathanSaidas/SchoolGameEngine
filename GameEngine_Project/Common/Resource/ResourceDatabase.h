#ifndef GAME_ENGINE_RESOURCE_DATABASE_H
#define GAME_ENGINE_RESOURCE_DATABASE_H


//Using for basic types. object
#include "../BasicTypes.h"


namespace Engine
{
	
	/*
	* The resource database will manage all resources.
	* 
	*/
	class ResourceDatabase : public object
	{
		RDECLARE_CLASS(ResourceDatabase)
	public:
		static const std::string META_ID_TOKEN;

		
	};

	TYPE_DEFINE(ResourceDatabase)
}


#endif