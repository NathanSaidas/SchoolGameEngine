#ifndef GAME_ENGINE_SCENE_H
#define GAME_ENGINE_SCENE_H

#include "../BasicTypes.h"
#include <vector>


namespace Engine
{
	class GameObject;

	class Scene : public Object
	{
		CLASS_HEADER(Scene)
	public:
		Scene();
		~Scene();


		void Update();
		void FixedUpdate();
		void PreRender();
		void Render();
		void PostRender();

		void Register(GameObject * aGameObject);
		void Unregister(GameObject * aGameObject);


	private:
		std::vector<GameObject*> m_GameObjects;

		std::vector<GameObject*> m_InitializationQueue;
		std::vector<GameObject*> m_LateInitializationQueue;
	};

	TYPE_DEFINE(Scene)
	TYPE_DEFINE_PTR(Scene*, "Scene Ptr")
}

#endif