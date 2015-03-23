#include "Material.h"

namespace Engine
{
	CLASS_CPP(Material,Object)
	Material::Material() : Object()
	{
		m_Shader = nullptr;
		m_Texture = nullptr;
	}
	Material::~Material()
	{

	}

	void Material::SetShader(Shader * aShader)
	{
		m_Shader = aShader;
	}
	Shader * Material::GetShader()
	{
		return m_Shader;
	}

	void Material::SetTexture(Texture * aTexture)
	{
		m_Texture = aTexture;
	}
	Texture * Material::GetTexture()
	{
		return m_Texture;
	}

}