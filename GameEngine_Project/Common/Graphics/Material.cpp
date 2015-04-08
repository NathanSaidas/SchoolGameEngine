#include "Material.h"

namespace Engine
{
	RDEFINE_CLASS(Material, Resource)
	Material::Material() : Resource()
	{

	}
	Material::~Material()
	{

	}

	void Material::SetShader(Pointer<Shader> & aShader)
	{
		m_Shader = aShader;
	}
	Pointer<Shader> Material::GetShader()
	{
		return m_Shader;
	}

	void Material::SetTexture(Pointer<Texture> & aTexture)
	{
		m_Texture = aTexture;
	}
	Pointer<Texture> Material::GetTexture()
	{
		return m_Texture;
	}

}