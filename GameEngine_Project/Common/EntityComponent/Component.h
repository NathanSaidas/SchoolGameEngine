#ifndef GAME_ENGINE_COMPONENT_H
#define GAME_ENGINE_COMPONENT_H

#include "../BasicTypes.h"

namespace Engine
{
	class GameObject;

	class Component : public object
	{
		CLASS_HEADER(Component)
	public:
		Component();
		~Component();


	

		GameObject * GetGameObject();

		std::string GetName();
		void SetName(const std::string & aName);

		std::string GetTag();
		void SetTag(const std::string & aName);

		int GetRenderMask();
		void SetRenderMask(int aMask);

		int GetPhysicsMask();
		void SetPhysicsMask(int aMask);


		Component * GetComponent(const std::string & aTypename);
		Component * GetComponent(const Type & aType);
		template<typename COMPONENT>
		COMPONENT * GetComponent()
		{
			return (COMPONENT*)GetComponent(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		Component * GetComponentInChildren(const std::string & aTypename);
		Component * GetComponentInChildren(const Type & aType);
		template<typename COMPONENT>
		COMPONENT * GetComponentInChildren()
		{
			return (COMPONENT*)GetComponentInChildren(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		Component * GetComponentInParent(const std::string & aTypename);
		Component * GetComponentInParent(const Type & aType);
		template<typename COMPONENT>
		COMPONENT * GetComponentInParent()
		{
			return (COMPONENT*)GetComponentInParent(Reflection::Runtime::TypeOf<COMPONENT>());
		}

		std::vector<Component*> GetComponents(const std::string & aTypename);
		std::vector<Component*> GetComponents(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponents()
		{
			return (COMPONENT*)GetComponents(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		std::vector<Component*> GetComponentsInChildren(const std::string & aTypename);
		std::vector<Component*> GetComponentsInChildren(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponentsInChildren()
		{
			return (COMPONENT*)GetComponentsInChildren(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		std::vector<Component*> GetComponentsInParent(const std::string & aTypename);
		std::vector<Component*> GetComponentsInParent(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponentsInParent()
		{
			return (COMPONENT*)GetComponentsInParent(Reflection::Runtime::TypeOf<COMPONENT>());
		}


	protected:
		///Gets called immediately when the component is added.
		virtual void OnRegister();
		///Gets called first when initialized during the update loop. Gets called once.
		virtual void OnInitialize();
		///Gets called after Initialize on all gameobjects/components during the update loop.
		virtual void OnLateInitialize();

		virtual void OnDestroy();
		virtual void OnLateDestroy();

		///Gets called during the update loop.
		virtual void Update();
		///Gets called after the Update call in the update loop.
		virtual void LateUpdate();
		virtual void FixedUpdate();

		///Gets called to gather geometry for the scene when prepping for rendering.
		virtual void OnPreRender();
		///Gets called after the scene has been renderered.
		virtual void OnRender();
		///Gets calld after extra scene rendering.
		virtual void OnPostRender();
		//TODO: Implement when Serialization has been designed / implemented.
		//void OnSerializeEditor(Stream aStream);
		//void OnDeserializeEditor(Stream aStream);
	private:
		GameObject * m_GameObject;
		friend GameObject;
	};

	TYPE_DEFINE(Component)
}

#endif