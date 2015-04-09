#ifndef GAME_ENGINE_RESOURCE_H
#define GAME_ENGINE_RESOURCE_H

//Using for basic types. Object
#include "../BasicTypes.h"
#include "../Utilities/Utilities.h"

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
		/**
		*
		*/
		Resource();
		/**
		*
		*/
		~Resource();

		
		/**
		* Generates the Unique ID
		*/
		void GenerateID();
		/**
		* Gets the unique ID
		* @return Returns the unique ID
		*/
		Guid GetID();

	protected:
		/**
		* Saves the changes made to a resource
		* @param The path to the directory of the resource. Save uses ../Directory/GetName for the full path.
		*/
		virtual void SaveMeta(IniFileStream & aDirectory);
		/**
		* Loads changes made from a resource
		@param The path to the directory of the resource. Load uses ../Directory/GetName for the full path.
		*/
		virtual void LoadMeta(IniFileStream & aDirectory);

	private:
		Guid m_UniqueID;
		friend class ResourceDatabase;
	};

	TYPE_DEFINE(Resource)
}

#endif