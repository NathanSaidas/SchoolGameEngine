#ifndef GAME_ENGINE_SCENE_H
#define GAME_ENGINE_SCENE_H

#include "../BasicTypes.h"
#include <vector>


namespace Engine
{
	class GameObject;
	class Application;
	class OpenGLWindow;
	class Graphics;

	class Scene : public Object
	{
		CLASS_HEADER(Scene)
	public:
		Scene();
		~Scene();


		

		void Register(GameObject * aGameObject);
		void Unregister(GameObject * aGameObject);


		



	private:
		std::vector<GameObject*> m_GameObjects;

		std::vector<GameObject*> m_InitializationQueue;
		std::vector<GameObject*> m_LateInitializationQueue;


		void Update();
		void FixedUpdate();
		void PreRender();
		void Render();
		void PostRender();

		void OnWindowFocus(OpenGLWindow * aWindow);
		void OnWindowUnfocus(OpenGLWindow * aWindow);
		void OnWindowClose(OpenGLWindow * aWindow);
		void OnWindowChangeSize(OpenGLWindow * aWindow, int aWidth, int aHeight);

		friend Application;
		friend GameObject;
		friend Graphics;

	};

	TYPE_DEFINE(Scene)
}

#endif