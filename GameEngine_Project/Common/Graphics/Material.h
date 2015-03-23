#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "../BasicTypes.h"

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

		void SetShader(Shader * aShader);
		Shader * GetShader();

		void SetTexture(Texture * aTexture);
		Texture * GetTexture();
	private:
		Shader * m_Shader;
		Texture * m_Texture;
	};

	TYPE_DEFINE(Material)
	TYPE_DEFINE_PTR(Material*, "Material Ptr")
}

#endif