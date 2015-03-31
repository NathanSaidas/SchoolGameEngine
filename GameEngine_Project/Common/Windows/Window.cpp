#include "Window.h"
#include "Application.h"
#include "../Math/Math.h"
#include "../Utilities/Utilities.h"


namespace Engine
{
	CLASS_CPP(OpenGLWindow,Object)

	OpenGLWindow::OpenGLWindow()
	{
		m_WindowHandle = nullptr;
		SetDefault();
	}
	OpenGLWindow::~OpenGLWindow()
	{
		if (m_WindowHandle != nullptr)
		{
			DestroyWindow();
		}
	}
	void OpenGLWindow::SetDefault()
	{
		m_IsFullscreen = false;
		m_IsResizeable = true;
		m_IsVisible = true;
		m_IsEmbeddedSystem = false;

		m_RedBits = 8;
		m_GreenBits = 8;
		m_BlueBits = 8;
		m_AlphaBits = 8;
		m_DepthBits = 24;
		m_StencilBits = 8;
		
		m_RefreshRate = GLFW_DONT_CARE;
		
		
		SetVersion(1, 0);
		SetProfile(OpenGLProfile::Any);
	}

	void OpenGLWindow::SetFullscreen(bool aIsFullscreen)
	{
		m_IsFullscreen = aIsFullscreen;
	}
	void OpenGLWindow::SetResizeable(bool aIsResizeable)
	{
		m_IsResizeable = aIsResizeable;
	}
	void OpenGLWindow::SetVisible(bool aIsVisible)
	{
		m_IsVisible = aIsVisible;
	}
	void OpenGLWindow::SetEmbeddedSystem(bool aIsEmbeddedSystem)
	{
		m_IsEmbeddedSystem = aIsEmbeddedSystem;
	}
	void OpenGLWindow::SetWidth(UInt32 aWidth)
	{
		m_Width = aWidth;
	}
	void OpenGLWindow::SetHeight(UInt32 aHeight)
	{
		m_Height = aHeight;
	}

	void OpenGLWindow::SetColorBits(SInt32 aRed, SInt32 aGreen, SInt32 aBlue, SInt32 aAlpha)
	{
		m_RedBits = aRed;
		m_GreenBits = aGreen;
		m_BlueBits = aBlue;
		m_AlphaBits = aAlpha;
	}
	void OpenGLWindow::SetDepthBits(SInt32 aDepth)
	{
		m_DepthBits = aDepth;
	}
	void OpenGLWindow::SetStencilBits(SInt32 aDepth)
	{
		m_StencilBits = aDepth;
	}
		
	
	void OpenGLWindow::SetRefreshRate(SInt32 aRefreshRate)
	{
		m_RefreshRate = aRefreshRate;
	}

	void OpenGLWindow::SetProfile(OpenGLProfile aProfile)
	{
		m_Profile = aProfile;
	}
	void OpenGLWindow::SetVersion(UInt8 aMajor, UInt8 aMinor)
	{
		m_MajorVersion = Math::Clamp(aMajor, 1, 4);
		switch (m_MajorVersion)
		{
		case 1:
			m_MinorVersion = 0;
			break;
		case 2:
			m_MinorVersion = Math::Clamp(aMinor, 0, 1);
			break;
		case 3:
			m_MinorVersion = Math::Clamp(aMinor, 0, 3);
			break;
		case 4:
			m_MinorVersion = Math::Clamp(aMinor, 0, 4);
			break;
		}
		if (aMajor != m_MajorVersion)
		{
			DEBUG_LOG("Invalid Major Version");
		}
		if (aMinor != m_MinorVersion)
		{
			DEBUG_LOG("Invalid minor version");
		}
	}

	bool OpenGLWindow::IsFullscreen()
	{
		return m_IsFullscreen;
	}
	bool OpenGLWindow::IsResizeable()
	{
		return m_IsResizeable;
	}
	bool OpenGLWindow::IsVisible()
	{
		return m_IsVisible;
	}
	bool OpenGLWindow::IsEmbeddedSystem()
	{
		return m_IsEmbeddedSystem;
	}
	UInt32 OpenGLWindow::GetWidth()
	{
		return m_Width;
	}
	UInt32 OpenGLWindow::GetHeight()
	{
		return m_Height;
	}

	SInt32 OpenGLWindow::GetRedBits()
	{
		return m_RedBits;
	}
	SInt32 OpenGLWindow::GetGreenBits()
	{
		return m_GreenBits;
	}
	SInt32 OpenGLWindow::GetBlueBits()
	{
		return m_BlueBits;
	}
	SInt32 OpenGLWindow::GetAlphaBits()
	{
		return m_AlphaBits;
	}
	SInt32 OpenGLWindow::GetDepthBits()
	{
		return m_DepthBits;
	}
	SInt32 OpenGLWindow::GetStencilBits()
	{
		return m_StencilBits;
	}
	SInt32 OpenGLWindow::GetRefreshRate()
	{
		return m_RefreshRate;
	}

	OpenGLProfile OpenGLWindow::GetProfile()
	{
		return m_Profile;
	}
	UInt8 OpenGLWindow::GetMajorVersion()
	{
		return m_MajorVersion;
	}
	UInt8 OpenGLWindow::GetMinorVersion()
	{
		return m_MinorVersion;
	}
		

	/// <summary>
	/// Creates the window.
	/// </summary>
	/// <returns></returns>
	bool OpenGLWindow::Create()
	{
		//Reset to defaults;
		glfwDefaultWindowHints();
		//
		////Set window Hints;
		glfwWindowHint(GLFW_RED_BITS, m_RedBits);
		glfwWindowHint(GLFW_GREEN_BITS, m_GreenBits);
		glfwWindowHint(GLFW_BLUE_BITS, m_BlueBits);
		glfwWindowHint(GLFW_DEPTH_BITS, m_DepthBits);
		glfwWindowHint(GLFW_STENCIL_BITS, m_StencilBits);
		glfwWindowHint(GLFW_REFRESH_RATE, m_RefreshRate);
		glfwWindowHint(GLFW_RESIZABLE, m_IsResizeable);
		glfwWindowHint(GLFW_VISIBLE, m_IsVisible);
		
		////Specify a context version of 1.0 will default to the highest available context
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_MajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_MinorVersion);

		///Specify the API
		if (IsEmbeddedSystem())
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
		}
		else
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		}


		///If major / minor version is greater than 3.2 check the forward compatibility for OpenGL profiles
		//Any version 3.2 and previous versions need to use the default GLFW_OPENGL_ANY profile
		if ((m_MajorVersion == 3 && m_MinorVersion > 2) || m_MajorVersion == 4)
		{
			if (m_Profile == OpenGLProfile::ForwardCompatibility || m_Profile == OpenGLProfile::ForwardCore)
			{
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			}

			//Set the profile
			if (m_Profile == OpenGLProfile::ForwardCompatibility || m_Profile == OpenGLProfile::Compatibility)
			{
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
			}
			else if (m_Profile == OpenGLProfile::ForwardCore || m_Profile == OpenGLProfile::Core)
			{
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			}
		}
		else
		{
			if (m_Profile != OpenGLProfile::Any)
			{
				DEBUG_LOG("Invalid profile value %u. Profile should be set to Any for context versions 3.2 and previous", (UInt32)m_Profile);
			}
			
			m_Profile = OpenGLProfile::Any;
		}
	
		


		GLFWwindow * window = glfwCreateWindow(m_Width, m_Height, GetName().c_str(), NULL, NULL);
		m_WindowHandle = window;

		Application * app = Application::GetInstance();
		if (app != nullptr)
		{
			app->RegisterWindow(this);
		}
		

		return m_WindowHandle != nullptr;
	}
	void OpenGLWindow::DestroyWindow()
	{
		Application * app = Application::GetInstance();
		if (app != nullptr)
		{
			app->UnregisterWindow(this);
		}

		GLFWwindow * window = (GLFWwindow*)m_WindowHandle;
		if (window != nullptr)
		{
			glfwDestroyWindow(window);
		}
		m_WindowHandle = nullptr;
	}

	bool OpenGLWindow::IsCreated()
	{
		return m_WindowHandle != nullptr;
	}

	bool OpenGLWindow::ShouldClose()
	{
		return glfwWindowShouldClose((GLFWwindow*)m_WindowHandle) == GL_TRUE;
	}

	void OpenGLWindow::SwapBuffers()
	{
		if (m_WindowHandle != nullptr)
		{
			glfwSwapBuffers((GLFWwindow*)m_WindowHandle);
		}
	}
	void OpenGLWindow::MakeCurrentContext()
	{
		Application * app = Application::GetInstance();
		if (app != nullptr)
		{
			app->MakeCurrentContext(this);
		}
	}

	void * OpenGLWindow::GetHandle()
	{
		return m_WindowHandle;
	}

	void OpenGLWindow::OnChangeSize(int aWidth, int aHeight)
	{
		m_Width = aWidth;
		m_Height = aHeight;
	}


}