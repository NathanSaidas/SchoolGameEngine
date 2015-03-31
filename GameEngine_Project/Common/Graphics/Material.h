#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "../BasicTypes.h"
#include "Shader.h"
#include "Texture.h"
#include "../Memory/Memory.h"

namespace Engine
{
	class Shader;
	class Texture;

	class Material : public Object
	{
		CLASS_HEADER(Material)
	public:
		Material();
		~Material();

		void SetShader(Pointer<Shader> aShader);
		Pointer<Shader> GetShader();

		void SetTexture(Pointer<Texture> aTexture);
		Pointer<Texture> GetTexture();
	private:
		Pointer<Shader> m_Shader;
		Pointer<Texture> m_Texture;
	};

	TYPE_DEFINE(Material)
}

#endif