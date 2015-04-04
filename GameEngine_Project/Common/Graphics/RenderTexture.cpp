#include "RenderTexture.h"
#include "Graphics.h"

namespace Engine
{
	RDEFINE_CLASS(RenderTexture, Object)

	RenderTexture::RenderTexture()
	{
		m_Width = 0;
		m_Height = 0;
		m_IsAllocated = false;
		m_FBOHandle = 0;
		m_TextureHandle = 0;
		m_DepthTextureHandle = 0;

	}

	RenderTexture::~RenderTexture()
	{
		Release();
	}

	void RenderTexture::Create(UInt32 aWidth, UInt32 aHeight)
	{
		Release();
		m_Width = aWidth;
		m_Height = aHeight;
		Graphics::CheckForGLErrors(__FILE__, __LINE__);
		//Create Framebuffer
        m_IsAllocated = true;
		glGenFramebuffers(1, &m_FBOHandle);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBOHandle);

		//Create Color Texture
		glGenTextures(1, &m_TextureHandle);
		glBindTexture(GL_TEXTURE_2D, m_TextureHandle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			GL_RGB, 
			m_Width, m_Height, 
			0,
			GL_RGB, 
			GL_UNSIGNED_BYTE, 
			0);
		glBindTexture(GL_TEXTURE_2D, 0);
		Graphics::CheckForGLErrors(__FILE__, __LINE__);
		//Create Depth Texture
        //glGenRenderbuffers(1, &m_DepthTextureHandle);
        //glBindRenderbuffer(GL_RENDERBUFFER, m_DepthTextureHandle);
        //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height);
        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthTextureHandle);
        
        glGenTextures(1, &m_DepthTextureHandle);
		glBindTexture(GL_TEXTURE_2D, m_DepthTextureHandle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			GL_DEPTH_COMPONENT24, 
			m_Width, m_Height,
			0,
			GL_DEPTH_COMPONENT, 
			GL_FLOAT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		Graphics::CheckForGLErrors(__FILE__, __LINE__);

        //glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT)

		//Attahc color / depth textures to the frame buffer.
		//glBindFramebuffer(GL_FRAMEBUFFER, m_FBOHandle);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureHandle, 0);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTextureHandle, 0);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_TextureHandle, 0);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_DepthTextureHandle, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			DEBUG_LOG("Failed to create Render Texture");
            Release();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		Graphics::CheckForGLErrors(__FILE__, __LINE__);
	}
	void RenderTexture::Release()
	{
		if (m_IsAllocated)
		{
			glDeleteTextures(1, &m_TextureHandle);
			glDeleteTextures(1, &m_DepthTextureHandle);

			glDeleteFramebuffers(1, &m_FBOHandle);
			m_Width = 0;
			m_Height = 0;
			m_IsAllocated = false;
			m_TextureHandle = 0;
			m_DepthTextureHandle = 0;
			m_FBOHandle = 0;
		}
	}

	bool RenderTexture::IsAllocated()
	{
		return m_IsAllocated;
	}
	UInt32 RenderTexture::GetWidth()
	{
		return m_Width;
	}
	UInt32 RenderTexture::GetHeight()
	{
		return m_Height;
	}
	GLuint RenderTexture::GetFBOHandle()
	{
		return m_FBOHandle;
	}
	GLuint RenderTexture::GetDepthHandle()
	{
		return m_DepthTextureHandle;
	}
	GLuint RenderTexture::GetTextureHandle()
	{
		return m_TextureHandle;
	}

}