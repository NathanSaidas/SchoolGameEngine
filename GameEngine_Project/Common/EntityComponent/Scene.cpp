#include "Scene.h"

#include "GameObject.h"
#include "../Memory/Memory.h"


namespace Engine
{
	CLASS_CPP(Scene, Object)

		Scene::Scene()
		{

		}
		Scene::~Scene()
		{
			for (int i = m_GameObjects.size() - 1; i >= 0; i--)
			{
				GameObject * gameObject = m_GameObjects[i];
				Memory::AllocatorType allocType = Memory::MemoryUtils::GetAllocatorType(gameObject);
				switch (allocType)
				{
					case Memory::AllocatorType::Pool:
						MEM_POOL_DEALLOC_T(gameObject, GameObject);
						break;
					case Memory::AllocatorType::Stack:
						MEM_STACK_DEALLOC_T(gameObject, GameObject);
						break;
					default:
						DEBUG_LOG("Invalid GameObject allocation made");
						break;
				}
			}
			
			m_GameObjects.clear();
			m_InitializationQueue.clear();
			m_LateInitializationQueue.clear();
		}


		void Scene::Update()
		{
			for (std::vector<GameObject*>::iterator it = m_InitializationQueue.begin();m_InitializationQueue.size() > 0 && it != m_InitializationQueue.end();)
			{
				if ((*it)->IsActive())
				{
					(*it)->OnInitialize();
					m_LateInitializationQueue.push_back(*it);
					std::vector<GameObject*>::iterator prev = it;
					it++;
					m_InitializationQueue.erase(prev);
				}
				else
				{
					it++;
				}
			}

			for (std::vector<GameObject*>::iterator it = m_LateInitializationQueue.begin();m_LateInitializationQueue.size() > 0 && it != m_LateInitializationQueue.end();)
			{
				if ((*it)->IsActive())
				{
					(*it)->OnLateInitialize();
					std::vector<GameObject*>::iterator prev = it;
					it++;
					m_LateInitializationQueue.erase(prev);
				}
				else
				{
					it++;
				}
			}


			for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				if ((*it)->IsActive())
				{
					(*it)->Update();
				}
			}
			for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				if ((*it)->IsActive())
				{
					(*it)->LateUpdate();
				}
				
			}
		}
		void Scene::FixedUpdate()
		{
			for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				if ((*it)->IsActive())
				{
					(*it)->FixedUpdate();
				}
				
			}
		}
		void Scene::PreRender()
		{
			for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				if ((*it)->IsActive())
				{
					(*it)->OnPreRender();
				}
				
			}
		}
		void Scene::Render()
		{
			for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				if ((*it)->IsActive())
				{
					(*it)->OnRender();
				}
				
			}
		}
		void Scene::PostRender()
		{
			for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
			{
				if ((*it)->IsActive())
				{
					(*it)->OnPostRender();
				}
				
			}
		}

		void Scene::Register(GameObject * aGameObject)
		{
			if (!Utilities::Exists<GameObject*>(m_GameObjects,aGameObject))
			{
				aGameObject->OnRegistered();
				m_GameObjects.push_back(aGameObject);
				m_InitializationQueue.push_back(aGameObject);
			}
		}
		void Scene::Unregister(GameObject * aGameObject)
		{
			Utilities::Remove<GameObject*>(m_GameObjects, aGameObject);
		}

	
}