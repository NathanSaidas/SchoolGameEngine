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
			return (TYPE*)GetComponent(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		Component * GetComponentInChildren(const std::string & aTypename);
		Component * GetComponentInChildren(const Type & aType);
		template<typename COMPONENT>
		COMPONENT * GetComponentInChildren()
		{
			return (TYPE*)GetComponentInChildren(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		Component * GetComponentInParent(const std::string & aTypename);
		Component * GetComponentInParent(const Type & aType);
		template<typename COMPONENT>
		COMPONENT * GetComponentInParent()
		{
			return (TYPE*)GetComponentInParent(Reflection::Runtime::TypeOf<COMPONENT>());
		}

		std::vector<Component*> GetComponents(const std::string & aTypename);
		std::vector<Component*> GetComponents(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponents()
		{
			return (TYPE*)GetComponents(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		std::vector<Component*> GetComponentsInChildren(const std::string & aTypename);
		std::vector<Component*> GetComponentsInChildren(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponentsInChildren()
		{
			return (TYPE*)GetComponentsInChildren(Reflection::Runtime::TypeOf<COMPONENT>());
		}
		std::vector<Component*> GetComponentsInParent(const std::string & aTypename);
		std::vector<Component*> GetComponentsInParent(const Type & aType);
		template<typename COMPONENT>
		std::vector<COMPONENT*> GetComponentsInParent()
		{
			return (TYPE*)GetComponentsInParent(Reflection::Runtime::TypeOf<COMPONENT>());
		}


	protected:
		virtual void OnRegister();
		virtual void OnInitialize();
		virtual void OnLateInitialize();

		virtual void OnDestroy();
		virtual void OnLateDestroy();

		virtual void Update();
		virtual void LateUpdate();
		virtual void FixedUpdate();

		virtual void OnPreRender();
		virtual void OnRender();
		virtual void OnPostRender();
		//TODO: Implement when Serialization has been designed / implemented.
		//void OnSerializeEditor(Stream aStream);
		//void OnDeserializeEditor(Stream aStream);
	private:
		GameObject * m_GameObject;
		friend GameObject;
	};

	TYPE_DEFINE(Component)
	TYPE_DEFINE_PTR(Component*, "Component Ptr")
}

#endif