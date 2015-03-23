#ifndef GAME_ENGINE_GAME_OBJECT_H
#define GAME_ENGINE_GAME_OBJECT_H

#include "../BasicTypes.h"
#include "../Utilities/Utilities.h"
#include "Component.h"

namespace Engine
{


	class GameObject : public object
	{
		CLASS_HEADER(GameObject)
	public:
		GameObject();
		GameObject(const std::string & aName);
		~GameObject();

		static void Destroy(GameObject * aGameObject);

		void OnRegistered();
		void OnInitialize();
		void OnLateInitialize();

		void OnEnable();
		void OnDisable();

		void OnDestroy(); //New
		void OnLateDestroy();

		void Update();
		void LateUpdate();

		void FixedUpdate();

		void OnPreRender();
		void OnRender();
		void OnPostRender();

		void SetActive(bool aFlag);
		bool IsActive();

		std::string GetName();
		void SetName(const std::string & aName);

		std::string GetTag();
		void SetTag(const std::string & aTag);

		int GetRenderMask();
		void SetRenderMask(int aMask);

		int GetPhysicsMask();
		void SetPhysicsMask(int aMask);

		GameObject * GetParent();
		void SetParent(GameObject * aParent);
		
		void AddChild(GameObject * aChild);
		void AddChildren(const std::vector<GameObject*> & aChildren);
		void AddChildren(const Array<GameObject*> & aChildren);
		
		void RemoveChild(std::string aName);
		void RemoveChild(GameObject * aChild);
		void RemoveChildren(const std::vector<GameObject*> & aChildren);
		void RemoveChildren(const Array<GameObject*> & aChildren);
		//
		//
		////Component Getters
		Component * GetComponent(const std::string & aTypename);
		Component * GetComponent(const Type & aType);
		template<class COMPONENT>
		COMPONENT* GetComponent()
		{
			return (COMPONENT*)GetComponent(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		Component * GetComponentInChildren(const std::string & aTypename);
		Component * GetComponentInChildren(const Type & aType);
		template<typename COMPONENT>
		COMPONENT* GetComponentInChildren()
		{
			return (COMPONENT*)GetComponentInChildren(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		Component * GetComponentInParent(const std::string & aTypename);
		Component * GetComponentInParent(const Type & aType);
		template<typename COMPONENT>
		COMPONENT* GetComponentInParent()
		{
			return (COMPONENT*)GetComponentInParent(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		
		std::vector<Component *> GetComponents(const std::string & aTypename);
		std::vector<Component *> GetComponents(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponents()
		{
			return (COMPONENT*)GetComponents(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		std::vector<Component *> GetComponentsInChildren(const std::string & aTypename);
		std::vector<Component *> GetComponentsInChildren(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponentsInChildren()
		{
			return (COMPONENT*)GetComponentsInChildren(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		std::vector<Component *> GetComponentsInParent(const std::string & aTypename);
		std::vector<Component *> GetComponentsInParent(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponentsInParent()
		{
			return (COMPONENT*)GetComponentsInParent(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		
		//Add Components
		Component * AddComponent(const std::string & aTypename);
		Component * AddComponent(const Type & aType);
		template<typename COMPONENT>
		COMPONENT * AddComponent()
		{
			return (COMPONENT*)AddComponent(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		
		//Remove Components
		void RemoveComponent(Component * aComponent);


		//TODO: Implement when Serialization has been designed / implemented.
		//void OnSerializeEditor(Stream aStream);
		//void OnDeserializeEditor(Stream aStream);

	private:
		std::string m_Name;
		std::string m_Tag;
		UInt32 m_RenderMask;
		UInt32 m_PhysicsMask;
		bool m_IsActive;
		GameObject * m_Parent;
		std::vector<GameObject*> m_Children;
		std::vector<Component*> m_Components;
	};

	TYPE_DEFINE(GameObject)
	TYPE_DEFINE_PTR(GameObject*,"GameObject Ptr")

}

#endif
