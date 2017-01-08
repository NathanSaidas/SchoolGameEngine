#ifndef GAME_ENGINE_WINDOW_H
#define GAME_ENGINE_WINDOW_H

#include "../BasicTypes.h"
#include "OpenGLProfile.h"

namespace Engine
{
	class OpenGLWindow : public Object
	{
		RDECLARE_CLASS(OpenGLWindow)
	public:
		OpenGLWindow();
		~OpenGLWindow();

		void SetDefault();

		void SetFullscreen(bool aIsFullscreen);
		void SetResizeable(bool aIsResizeable);
		void SetVisible(bool aIsVisible);
		void SetEmbeddedSystem(bool aIsEmbeddedSystem);
		void SetWidth(UInt32 aWidth);
		void SetHeight(UInt32 aHeight);
		void SetColorBits(SInt32 aRed, SInt32 aGreen, SInt32 aBlue, SInt32 aAlpha);
		void SetDepthBits(SInt32 aDepth);
		void SetStencilBits(SInt32 aStencil);
		void SetRefreshRate(SInt32 aRefreshRate);

		void SetProfile(OpenGLProfile aProfile);
		void SetVersion(UInt8 aMajor, UInt8 aMinor);		

		bool IsFullscreen();
		bool IsResizeable();
		bool IsVisible();
		bool IsEmbeddedSystem();
		UInt32 GetWidth();
		UInt32 GetHeight();

		SInt32 GetRedBits();
		SInt32 GetGreenBits();
		SInt32 GetBlueBits();
		SInt32 GetAlphaBits();
		SInt32 GetDepthBits();
		SInt32 GetStencilBits();
		SInt32 GetRefreshRate();

		OpenGLProfile GetProfile();
		UInt8 GetMajorVersion();
		UInt8 GetMinorVersion();

		bool Create();
		void DestroyWindow();

		bool IsCreated();
		bool ShouldClose();
		
		void SwapBuffers();
		void MakeCurrentContext();
		
		void * GetHandle();
		
	private:

		bool m_IsFullscreen;
		bool m_IsResizeable;
		bool m_IsVisible;
		bool m_IsEmbeddedSystem;
		UInt32 m_Width;
		UInt32 m_Height;

		SInt32 m_RedBits;
		SInt32 m_GreenBits;
		SInt32 m_BlueBits;
		SInt32 m_AlphaBits;
		SInt32 m_DepthBits;
		SInt32 m_StencilBits;

		SInt32 m_RefreshRate;

		void * m_WindowHandle;

		OpenGLProfile m_Profile;
		UInt8 m_MajorVersion;
		UInt8 m_MinorVersion;

		
		void OnChangeSize(int aWidth, int aHeight);
		
		friend class Application;
		
	};

	TYPE_DEFINE(OpenGLWindow)
}

#endif