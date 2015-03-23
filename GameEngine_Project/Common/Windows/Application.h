#ifndef GAME_ENGINE_APPLICATION_H
#define GAME_ENGINE_APPLICATION_H

#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "../BasicTypes.h"
#include "OpenGLProfile.h"
#include "Window.h"
#include "Time.h"





namespace Engine
{
	class OpenGLWindow;
	class Scene;

	struct ApplicationInfo
	{
		std::string applicationName;
		UInt32 width;
		UInt32 height;
		bool fullscreen;
		OpenGLProfile profile;
		UInt8 majorVersion;
		UInt8 minorVersion;
	};

	class Application : public object
	{
		CLASS_HEADER(Application)
	public:
		static Application * GetInstance();
		static void Terminate();

		static void InitializeAndExecute();
		static bool IsRunning();
		static void CancelQuit();
		static void Quit();

		static Scene * GetCurrentScene();

		void RegisterWindow(OpenGLWindow * aWindow);
		void UnregisterWindow(OpenGLWindow * aWindow);
		void MakeCurrentContext(OpenGLWindow * aWindow);


		OpenGLWindow * GetWindow(const std::string & aName);
		OpenGLWindow * GetWindow(void * aHandle);
		OpenGLWindow * GetDefaultWindow();
		OpenGLWindow * GetCurrentWindow();

		

	private:
		static Application * s_Instance;
		static bool InitializeOpenGL(const ApplicationInfo & aInfo);
		Application();
		~Application();
		friend class Reflection::MetaObject<Application>;

		//-- Window
		OpenGLWindow * m_DefaultWindow;
		OpenGLWindow * m_CurrentContext;
		std::vector<OpenGLWindow*> m_Windows;

		static void OnGLFWError(int aCode, const char * aErrorString);
		static void OnMouseButtonEvent(GLFWwindow * aWindow, int aButton, int aAction, int aMods);
		static void OnMouseMoveEvent(GLFWwindow * aWindow, double aXPosition, double aYPosition);
		static void OnScrollEvent(GLFWwindow * aWindow, double aXOffset, double aYOffset);
		static void OnKeyEvent(GLFWwindow * aWindow, int aKey, int aScanCode, int aAction, int aMods);
		static void OnDropFileEvent(GLFWwindow * aWindow, int aCount, const char ** aFilePaths);
		static void OnWindowFocus(GLFWwindow * aWindow, int aFocus);
		static void OnWindowClose(GLFWwindow * aWindow);
		static void OnWindowChangeSize(GLFWwindow * aWindow, int aWidth, int aHeight);
		

		//-- General
		bool m_IsRunning;
		Scene * m_CurrentScene;

		//--Internal Functions
		void Start();
		void Update();
		void CleanUp();
		

	};

	TYPE_DEFINE(Application)
	TYPE_DEFINE_PTR(Application*, "Applcation Ptr")
}

#endif