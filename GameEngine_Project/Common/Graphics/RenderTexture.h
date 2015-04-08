#ifndef GAME_ENGINE_RENDER_TEXTURE_H
#define GAME_ENGINE_RENDER_TEXTURE_H

#include "../BasicTypes.h"
#include "Texture.h"

namespace Engine
{
	class RenderTexture : public Texture
	{
		RDECLARE_CLASS(RenderTexture)
	public:
		RenderTexture();
		~RenderTexture();
		

		unsigned int GetFBOHandle();
		unsigned int GetDepthHandle();

		void Create(UInt32 aWidth, UInt32 aHeight);
		void ReleaseGPU();

	private:

		unsigned int m_FBOHandle;
		unsigned int m_DepthTextureHandle;
	};

	TYPE_DEFINE(RenderTexture)
}

#endif