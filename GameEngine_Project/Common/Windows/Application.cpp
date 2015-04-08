#include "Application.h"
#include <new>
#include "../Engine.h"

#include "../EntityComponent/TestComponent.h"

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
				int profile = Enum::GetValue(&info.profile); // (int)info.profile;
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
		Graphics::Initialize();
		Input::Initialize();

		Application * application = GetInstance();
		application->m_IsRunning = true;

		application->Start();

		while (IsRunning())
		{
			application->Update();
		}

		application->CleanUp();

		Input::Terminate();
		Graphics::Terminate();
		Terminate();
		Reflection::Runtime::Terminate();
		Memory::MemoryManager::Terminate();
		system("pause");
	}
	bool Application::InitializeOpenGL(const ApplicationInfo & aInfo)
	{
		
		

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
		if (!window->Create())
		{
			delete window;
			delete s_Instance;
			s_Instance = nullptr;
			return false;
		}
		window->MakeCurrentContext();

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			return false;
		}
		

		const GLubyte * renderer = glGetString(GL_RENDERER);
		const GLubyte * version = glGetString(GL_VERSION);
		DEBUG_LOG("Renderer: %s\nVersion: %s", renderer, version);

		s_Instance->m_DefaultWindow = window;

		Graphics::CheckForGLErrors(__FILE__, __LINE__);

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
	Scene * Application::GetCurrentScene()
	{
		if (s_Instance != nullptr)
		{
			return s_Instance->m_CurrentScene;
		}
		return nullptr;
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
		if (s_Instance != nullptr)
		{
			for (std::vector<OpenGLWindow*>::iterator it = s_Instance->m_Windows.begin(); it != s_Instance->m_Windows.end(); it++)
			{
				if ((*it)->GetName() == aName)
				{
					return *it;
				}
			}
		}

		
		return nullptr;
	}

	OpenGLWindow * Application::GetWindow(void * aHandle)
	{
		if (s_Instance != nullptr)
		{
			for (std::vector<OpenGLWindow*>::iterator it = s_Instance->m_Windows.begin(); it != s_Instance->m_Windows.end(); it++)
			{
				if ((*it)->GetHandle() == aHandle)
				{
					return *it;
				}
			}
		}
		
		return nullptr;
	}
	OpenGLWindow * Application::GetDefaultWindow()
	{
		return s_Instance != nullptr ? s_Instance->m_DefaultWindow : nullptr;
	}
	OpenGLWindow * Application::GetCurrentWindow()
	{
		return s_Instance != nullptr ? s_Instance->m_CurrentContext : nullptr;
	}


	void Application::OnGLFWError(int aCode, const char * aErrorString)
	{
		DEBUG_LOG("GLFW Error [%u]: %s", aCode, aErrorString);
	}
	void Application::OnMouseButtonEvent(GLFWwindow * aWindow, int aButton, int aAction, int aMods)
	{
		Input::Instance()->ProcessMouseEvent(aButton, aAction, aMods);
	}
	void Application::OnMouseMoveEvent(GLFWwindow * aWindow, double aXPosition, double aYPosition)
	{
		Input::Instance()->ProcessMouseMove((Float32)aXPosition, (Float32)aYPosition);
	}
	void Application::OnScrollEvent(GLFWwindow * aWindow, double aXOffset, double aYOffset)
	{
		Input::Instance()->ProcessMouseScroll((Float32)aXOffset, (Float32)aYOffset);
	}
	void Application::OnKeyEvent(GLFWwindow * aWindow, int aKey, int aScanCode, int aAction, int aMods)
	{
		Input::Instance()->ProcessKeyEvent(aKey, aAction, aMods);
	}
	void Application::OnDropFileEvent(GLFWwindow * aWindow, int aCount, const char ** aFilePaths)
	{

	}
	void Application::OnWindowFocus(GLFWwindow * aWindow, int aFocus)
	{
		if (s_Instance == nullptr && s_Instance->m_CurrentScene != nullptr)
		{
			return;
		}
		OpenGLWindow * window = s_Instance->GetWindow(aWindow);
		if (aFocus == GL_TRUE)
		{
			s_Instance->m_CurrentScene->OnWindowFocus(window);
		}
		else
		{
			s_Instance->m_CurrentScene->OnWindowUnfocus(window);
		}
	}
	void Application::OnWindowClose(GLFWwindow * aWindow)
	{
		if (s_Instance != nullptr)
		{
			//Get the window from the Application vector.
			OpenGLWindow * window = s_Instance->GetWindow(aWindow);
			//Notify the scene about the event.
			if (s_Instance->m_CurrentScene != nullptr)
			{
				s_Instance->m_CurrentScene->OnWindowClose(window);
			}

			bool defaultWindowClose = window == s_Instance->m_DefaultWindow;

			//If the default window is closing. Close the application.
			if (defaultWindowClose)
			{
				s_Instance->Quit();
			}
			else //If the window being destroyed is the current context, bind the default window to the current context.
			{
				//Windows being destroyed must have their resources released externally since they can be allocated externally.
				if (window == s_Instance->m_CurrentContext)
				{
					s_Instance->m_DefaultWindow->MakeCurrentContext();
				}
			}
		}
	}
	void Application::OnWindowChangeSize(GLFWwindow * aWindow, int aWidth, int aHeight)
	{
		if (s_Instance != nullptr && s_Instance->m_CurrentScene != nullptr)
		{
			OpenGLWindow * window = s_Instance->GetWindow(aWindow);
			s_Instance->m_CurrentScene->OnWindowChangeSize(window, aWidth, aHeight);
			if (window != nullptr)
			{
				window->OnChangeSize(aWidth, aHeight);
			}
		}
	}

	void Application::Start()
	{
		//TODO: Find methods with InitializeOnStart attribute and invoke them.

		//TODO: Write code to create gameobjects / scenes..
		m_CurrentScene = MEM_POOL_ALLOC_T(Scene);


		GameObject * testObject = NEW_POOL(GameObject)("Main Object");
		testObject->AddComponent<TestComponent>();

		GameObject * renderer = NEW_POOL(GameObject)("Renderer");
		renderer->AddComponent<Renderer>();

		GameObject * camera = NEW_POOL(GameObject)("Camera");
		camera->AddComponent<Camera>();

		renderer->SetParent(testObject);
		camera->SetParent(testObject);


	}

	void Application::Update()
	{
		Float32 lastTime = Time::s_Time;
		Float32 currentTime = glfwGetTime();

		Float32 deltaTime = currentTime - lastTime;
		Time::s_DeltaTime = deltaTime;
		Time::s_Time = currentTime;


		if (m_CurrentContext == nullptr)
		{
			m_DefaultWindow->MakeCurrentContext();
		}

		m_CurrentScene->Update();
		//m_CurrentScene->PreRender(); //Gather Geometry
		Graphics::Render(m_CurrentScene);
		//m_CurrentScene->Render(); //Render Shadow Map Pass, Render Scene  => Give Final FBO for post processing
		//m_CurrentScene->PostRender();


		m_CurrentContext->SwapBuffers();
		Input::Instance()->Update();



		Memory::MemoryManager::GetInstance()->ResetFrame();
	}

	void Application::CleanUp()
	{
		//TODO: Cleanup the scenes.
		MEM_POOL_DEALLOC_T(m_CurrentScene, Scene);
	}

}