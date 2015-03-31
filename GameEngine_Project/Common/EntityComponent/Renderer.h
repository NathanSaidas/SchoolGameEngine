#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H

#include "Component.h"
#include "../Graphics/Graphics.h"

namespace Engine
{
	class Renderer : public Component
	{
		CLASS_HEADER(Renderer)
	public:
		Renderer();
		~Renderer();

		void SetMesh(Pointer<Mesh> aMesh);
		Pointer<Mesh> GetMesh();

		void SetMaterial(Pointer<Material> aMaterial);
		Pointer<Material> GetMaterial();

	protected:

		virtual void OnPreRender();
		virtual void OnRender();
		virtual void OnPostRender();

	private:
		Pointer<Mesh> m_Mesh;
		Pointer<Material> m_Material;
	};

	TYPE_DEFINE(Renderer)
}

#endif