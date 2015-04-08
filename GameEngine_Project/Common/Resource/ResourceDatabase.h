#ifndef GAME_ENGINE_RESOURCE_DATABASE_H
#define GAME_ENGINE_RESOURCE_DATABASE_H

#include <map>
//Using for basic types. object
#include "../BasicTypes.h"
#include "../Graphics/ImageTexture.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Material.h"
#include "../Memory/Memory.h"



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

		/**
		* Initializes the database.
		*/
		//static void Initialize();
		/**
		* Unloads all loaded resources.
		*/
		//static void Terminate();
		/**
		*
		*/
		//static Pointer<ImageTexture> LoadTexture(const std::string & aName);
		//static Pointer<ImageTexture> GetTexture(const std::string & aName);
		//static Pointer<Mesh> LoadMesh(const std::string & aName);
		//static Pointer<Mesh> GetMesh(const std::string & aName);
		//static Pointer<Shader> LoadShader(const std::string & aName);
		//static Pointer<Shader> GetShader(const std::string & aName);
		//
		//static void UnloadResource(const std::string & aName);

		

	private:
		//static ResourceDatabase * s_Instance;
		//ResourceDatabase();
		//~ResourceDatabase();
		//
		//std::map<std::string, Pointer<Resource>> m_ResourceCache;
		
	};

	TYPE_DEFINE(ResourceDatabase)
}


#endif