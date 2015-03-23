#ifndef GAME_ENGINE_RENDER_TEXTURE_H
#define GAME_ENGINE_RENDER_TEXTURE_H

#include <GL\glew.h>
#include "../BasicTypes.h"

namespace Engine
{
	class RenderTexture : public Object
	{
		CLASS_HEADER(RenderTexture)
	public:
		RenderTexture();
		~RenderTexture();
		void Create(UInt32 aWidth, UInt32 aHeight);
		void Release();

		bool IsAllocated();
		UInt32 GetWidth();
		UInt32 GetHeight();
		GLuint GetFBOHandle();
		GLuint GetDepthHandle();
		GLuint GetTextureHandle();

	private:
		bool m_IsAllocated;
		UInt32 m_Width;
		UInt32 m_Height;

		GLuint m_FBOHandle;
		GLuint m_DepthTextureHandle;
		GLuint m_TextureHandle;
	};

	TYPE_DEFINE(RenderTexture)
	TYPE_DEFINE_PTR(RenderTexture*, "RenderTexture Ptr")
}

#endif