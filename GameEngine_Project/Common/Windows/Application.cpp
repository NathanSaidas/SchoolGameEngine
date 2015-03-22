#include "Application.h"
#include <new>
#include "../Memory/Memory.h"
#include "../Reflection/Reflection.h"

#include "Window.h"
#include "../Utilities/Utilities.h"

namespace Engine
{
	CLASS_CPP(Application, object)

	Application * Application::s_Instance = nullptr;
	Application * Application::GetInstance()
	{
		return s_Instance;
	}
	void Application::Terminate()
	{
		if (s_Instance != nullptr)
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}

	Application::Application()
	{
		m_DefaultWindow = nullptr;
		m_CurrentContext = nullptr;
		m_IsRunning = false;
	}
	Application::~Application()
	{
		m_DefaultWindow->DestroyWindow();
		delete m_DefaultWindow;
		m_DefaultWindow = nullptr;
		glfwTerminate();
	}
	void Application::InitializeAndExecute()
	{
		Memory::MemoryManager::Initialize();
		Reflection::Runtime::Compile(nullptr);

		//Setup Defaults
		ApplicationInfo info;
		info.applicationName = "Default-Application";
		info.width = 640;
		info.height = 480;
		info.fullscreen = false;
		info.majorVersion = 4;
		info.minorVersion = 4;
		info.profile = OpenGLProfile::ForwardCore;

		///Read from initialization file.
		IniFileStream * initializationFile = MEM_POOL_ALLOC_T(IniFileStream);
		if (initializationFile != nullptr)
		{
			initializationFile->SetPath("Settings.ini");
			initializationFile->Read();

			if (!initializationFile->BindSection("Application"))
			{
				DEBUG_LOG("Missing application section, generating defaults");
				initializationFile->AddSection("Application");
				initializationFile->BindSection("Application");
				int width = info.width;
				int height = info.height;
				int profile = (int)info.profile;
				int majorVersion = info.majorVersion;
				int minorVersion = info.minorVersion;

				initializationFile->AddString("applicationName", info.applicationName);
				initializationFile->AddInt("width", width);
				initializationFile->AddInt("height",height);
				initializationFile->AddBool("fullscreen", info.fullscreen);
				initializationFile->AddInt("profile", profile);
				initializationFile->AddInt("majorVersion", majorVersion);
				initializationFile->AddInt("minorVersion", minorVersion);
				initializationFile->Save();
			}
			
			info.applicationName = initializationFile->GetString("applicationName").GetValue();
			info.width = initializationFile->GetInt("width").GetValue();
			info.height = initializationFile->GetInt("height").GetValue();
			info.fullscreen = initializationFile->GetBool("fullscreen").GetValue();
			info.profile = (OpenGLProfile)initializationFile->GetInt("profile").GetValue();
			info.majorVersion = initializationFile->GetInt("majorVersion").GetValue();
			info.minorVersion = initializationFile->GetInt("minorVersion").GetValue();
			MEM_POOL_DEALLOC_T(initializationFile, IniFileStream);
		}

		//If failed to initialize open gl close the program
		if (!InitializeOpenGL(info))
		{
			DEBUG_LOG("Failed to initialize OpenGL");
			Terminate();
			Reflection::Runtime::Terminate();
			Memory::MemoryManager::Terminate();
			return;
		}

		Application * application = GetInstance();
		application->m_IsRunning = true;

		while (IsRunning())
		{
			application->Update();
		}

		Terminate();
		Reflection::Runtime::Terminate();
		Memory::MemoryManager::Terminate();
	}
	bool Application::InitializeOpenGL(const ApplicationInfo & aInfo)
	{
		

		if (!glewInit())
		{
			return false;
		}

		if (!glfwInit())
		{
			return false;
		}

		if (s_Instance == nullptr)
		{
			s_Instance = new Application();
		}

		glfwSetErrorCallback(OnGLFWError);

		OpenGLWindow * window = new OpenGLWindow();
		window->SetName(aInfo.applicationName);
		window->SetWidth(aInfo.width);
		window->SetHeight(aInfo.height);
		window->SetVersion(aInfo.majorVersion, aInfo.minorVersion);
		window->SetProfile(aInfo.profile);
		window->SetFullscreen(aInfo.fullscreen);
		if (!window->CreateWindow())
		{
			delete window;
			delete s_Instance;
			s_Instance = nullptr;
			return false;
		}
		window->MakeCurrentContext();

		const GLubyte * renderer = glGetString(GL_RENDERER);
		const GLubyte * version = glGetString(GL_VERSION);
		DEBUG_LOG("Renderer: %s\nVersion: %s", renderer, version);

		s_Instance->m_DefaultWindow = window;

		return true;
	}

	bool Application::IsRunning()
	{
		if (s_Instance != nullptr)
		{
			return s_Instance->m_IsRunning;
		}
		return false;
	}
	void Application::CancelQuit()
	{
		if (s_Instance != nullptr)
		{
			s_Instance->m_IsRunning = true;
			//TODO: Invoke OnCancelQuit
		}
	}
	void Application::Quit()
	{
		if(s_Instance != nullptr)
		{
			s_Instance->m_IsRunning = false;
			//TODO: Invoke OnQuit
		}
	}

	void Application::RegisterWindow(OpenGLWindow * aWindow)
	{
		if (aWindow != nullptr && !Utilities::Exists<OpenGLWindow*>(m_Windows,aWindow))
		{
			if (!aWindow->IsCreated())
			{
				DEBUG_LOG("Must call CreateWindow before registering.");
				return;
			}
			m_Windows.push_back(aWindow);
			//Set Callbacks
			GLFWwindow * windowHandle = (GLFWwindow*)aWindow->GetHandle();
			glfwSetMouseButtonCallback(windowHandle, OnMouseButtonEvent);
			glfwSetCursorPosCallback(windowHandle, OnMouseMoveEvent);
			glfwSetScrollCallback(windowHandle, OnScrollEvent);
			glfwSetKeyCallback(windowHandle, OnKeyEvent);
			glfwSetDropCallback(windowHandle, OnDropFileEvent);
			glfwSetWindowFocusCallback(windowHandle, OnWindowFocus);
			glfwSetWindowCloseCallback(windowHandle, OnWindowClose);
			glfwSetWindowSizeCallback(windowHandle, OnWindowChangeSize);
			
		}
		else
		{
			DEBUG_LOG("Window was null or has already been registered");
		}
	}
	void Application::UnregisterWindow(OpenGLWindow * aWindow)
	{
		if (aWindow != nullptr)
		{
			if (!Utilities::Remove<OpenGLWindow*>(m_Windows, aWindow))
			{
				DEBUG_LOG("Attempting to remove a window which was not added. (%s)", aWindow->GetName().c_str());
			}
		}
	}
	void Application::MakeCurrentContext(OpenGLWindow * aWindow)
	{
		if (aWindow != nullptr)
		{
			glfwMakeContextCurrent((GLFWwindow*)aWindow->GetHandle());
			m_CurrentContext = aWindow;
		}
	}

	OpenGLWindow * Application::GetWindow(const std::string & aName)
	{
		for (std::vector<OpenGLWindow*>::iterator it = m_Windows.begin(); it != m_Windows.end(); it++)
		{
			if ((*it)->GetName() == aName)
			{
				return *it;
			}
		}
		return nullptr;
	}

	OpenGLWindow * Application::GetWindow(void * aHandle)
	{
		for (std::vector<OpenGLWindow*>::iterator it = m_Windows.begin(); it != m_Windows.end(); it++)
		{
			if ((*it)->GetHandle() == aHandle)
			{
				return *it;
			}
		}
		return nullptr;
	}
	OpenGLWindow * Application::GetDefaultWindow()
	{
		return m_DefaultWindow;
	}
	OpenGLWindow * Application::GetCurrentWindow()
	{
		return m_CurrentContext;
	}


	void Application::OnGLFWError(int aCode, const char * aErrorString)
	{
		DEBUG_LOG("GLFW Error [%u]: %s", aCode, aErrorString);
	}
	void Application::OnMouseButtonEvent(GLFWwindow * aWindow, int aButton, int aAction, int aMods)
	{

	}
	void Application::OnMouseMoveEvent(GLFWwindow * aWindow, double aXPosition, double aYPosition)
	{

	}
	void Application::OnScrollEvent(GLFWwindow * aWindow, double aXOffset, double aYOffset)
	{

	}
	void Application::OnKeyEvent(GLFWwindow * aWindow, int aKey, int aScanCode, int aAction, int aMods)
	{

	}
	void Application::OnDropFileEvent(GLFWwindow * aWindow, int aCount, const char ** aFilePaths)
	{

	}
	void Application::OnWindowFocus(GLFWwindow * aWindow, int aFocus)
	{
		if (aFocus == GL_TRUE)
		{

		}
		else
		{
			
		}
	}
	void Application::OnWindowClose(GLFWwindow * aWindow)
	{
		if (s_Instance != nullptr)
		{
			OpenGLWindow * window = s_Instance->GetWindow(aWindow);
			if (window == s_Instance->m_DefaultWindow)
			{
				s_Instance->Quit();
			}
		}
	}
	void Application::OnWindowChangeSize(GLFWwindow * aWindow, int aWidth, int aHeight)
	{

	}

	void Application::Update()
	{
		if (m_CurrentContext == nullptr)
		{
			m_CurrentContext = m_DefaultWindow;
		}


		m_CurrentContext->SwapBuffers();
		glfwPollEvents();
	}

}