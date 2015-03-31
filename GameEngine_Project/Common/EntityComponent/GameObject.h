#ifndef GAME_ENGINE_GAME_OBJECT_H
#define GAME_ENGINE_GAME_OBJECT_H

#include "../BasicTypes.h"
#include "../Utilities/Utilities.h"
#include "../Math/Math.h"
#include "Component.h"

namespace Engine
{
	class OpenGLWindow;



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

		void OnWindowFocus(OpenGLWindow * aWindow);
		void OnWindowUnfocus(OpenGLWindow * aWindow);
		void OnWindowClose(OpenGLWindow * aWindow);
		void OnWindowChangeSize(OpenGLWindow * aWindow, int aWidth, int aHeight);

		void SetActive(bool aFlag);
		bool IsActive();

		std::string GetName();
		void SetName(std::string aName);

		std::string GetTag();
		void SetTag(std::string aTag);

		int GetRenderMask();
		void SetRenderMask(int aMask);

		int GetPhysicsMask();
		void SetPhysicsMask(int aMask);

		GameObject * GetParent();
		void SetParent(GameObject * aParent);

		Vector3 GetPosition();
		void SetPosition(Vector3 aPosition);

		Vector3 GetRotation();
		void SetRotation(Vector3 aRotation);

		Vector3 GetScale();
		void SetScale(Vector3 aScale);

		Vector3 GetLocalPosition();
		void SetLocalPosition(Vector3 aLocalPosition);

		Vector3 GetLocalRotation();
		void SetLocalRotation(Vector3 aLocalRotation);

		Matrix4x4 GetLocalToWorldMatrix();

		void LookAt(Vector3 aPosition);
		
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

		//Transform Components
		Vector3 m_Position;
		Vector3 m_Rotation;
		Vector3 m_Scale;
		Vector3 m_LocalPosition;
		Vector3 m_LocalRotation;

	};

	TYPE_DEFINE(GameObject)
}

#endif
