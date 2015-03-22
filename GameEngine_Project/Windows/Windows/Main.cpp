#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "../Engine.h"
#include "../Examples/Examples.h"

#include "../Windows/Application.h"
#include "../Windows/Window.h"


using namespace Engine;

void Test();

int main()
{
	Test();
	system("pause");
	return 0;
}

void Test()
{
	Application::InitializeAndExecute();
	

	//if (!glewInit())
	//{
	//	DEBUG_LOG("Failed to initialize glew");
	//	return;
	//}
	//
	//if (!glfwInit())
	//{
	//	DEBUG_LOG("Failed to initialize glfw");
	//	return;
	//}
	//
	//OpenGLWindow * window = new OpenGLWindow();
	//window->SetWidth(640);
	//window->SetHeight(480);
	//window->SetName("Chelseas Bitch Maker");
	//window->SetFullscreen(false);
	//window->SetProfile(OpenGLProfile::ForwardCompatibility);
	//window->SetVersion(7, 2);
	//
	//
	//if (!window->CreateWindow())
	//{
	//	glfwTerminate();
	//	delete window;
	//	DEBUG_LOG("Failed to create window");
	//	return;
	//}
	//
	//window->MakeCurrentContext();
	//
	//
	//
	//while (!window->ShouldClose())
	//{
	//	///Update
	//	window->SwapBuffers();
	//	glfwPollEvents();
	//}
	//
	//
	//window->DestroyWindow();
	//delete window;
	//
	//glfwTerminate();
}