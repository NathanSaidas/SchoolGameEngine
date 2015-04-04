#ifndef GAME_ENGINE_RESOURCE_H
#define GAME_ENGINE_RESOURCE_H

//Using for basic types. Object
#include "../BasicTypes.h"

namespace Engine
{

	/**
	* Resource represents the base class for all future resources.
	* Texture/Mesh/Shader
	*/
	class Resource : public Object
	{
		RDECLARE_CLASS(Resource)
	public:

	private:

	};

	TYPE_DEFINE(Resource)
}

#endif