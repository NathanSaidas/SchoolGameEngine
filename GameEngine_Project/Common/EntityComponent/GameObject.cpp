#include "GameObject.h"
#include "Scene.h"
#include "../Windows/Application.h"
#include "../Memory/Memory.h"

namespace Engine
{
	CLASS_CPP(GameObject,object)


	GameObject::GameObject()
	{
		m_Name = "";
		m_Tag = "";
		m_RenderMask = 0;
		m_PhysicsMask = 0;
		m_IsActive = true;
		m_Parent = nullptr;

		Scene * scene = Application::GetCurrentScene();
		if (scene != nullptr)
		{
			scene->Register(this);
		}

	}
	GameObject::GameObject(const std::string & aName)
	{
		m_Name = aName;
		m_Tag = "";
		m_RenderMask = 0;
		m_PhysicsMask = 0;
		m_IsActive = true;
		m_Parent = nullptr;
		Scene * scene = Application::GetCurrentScene();
		if (scene != nullptr)
		{
			scene->Register(this);
		}
	}
	GameObject::~GameObject()
	{
		for (int i = m_Components.size() - 1; i >= 0; i--)
		{
			Component * component = m_Components[i];
			Type type = component->GetType();
			type.GetDestructor().Invoke(component);
			MEM_POOL_DEALLOC(component, type.GetSize());
		}
		
		m_Components.clear();
	}
	
	void Destroy(GameObject * aGameObject)
	{
		if (aGameObject != nullptr)
		{
			Scene * scene = Application::GetCurrentScene();
			if (scene != nullptr)
			{
				scene->Register(aGameObject);
			}
		}
	}

	void GameObject::OnRegistered()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnRegister();
		}
	}
	void GameObject::OnInitialize()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnInitialize();
		}
	}
	void GameObject::OnLateInitialize()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnLateInitialize();
		}
	}
	void GameObject::OnEnable()
	{

	}
	void GameObject::OnDisable()
	{

	}
	void GameObject::OnDestroy()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnDestroy();
		}
	}
	void GameObject::OnLateDestroy()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnLateDestroy();
		}
	}
	void GameObject::Update()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->LateUpdate();
		}
	}
	void GameObject::FixedUpdate()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->FixedUpdate();
		}
	}
	void GameObject::OnPreRender()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnPreRender();
		}
	}
	void GameObject::OnRender()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnRender();
		}
	}
	void GameObject::OnPostRender()
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->OnPostRender();
		}
	}

	void GameObject::SetActive(bool aFlag)
	{
		if (!m_IsActive && aFlag)
		{
			OnEnable();
		}
		else if (m_IsActive && !aFlag)
		{
			OnDisable();
		}
		m_IsActive = aFlag;
	}
	bool GameObject::IsActive()
	{
		return m_IsActive;
	}

	std::string GameObject::GetName()
	{
		return m_Name;
	}
	void GameObject::SetName(const std::string & aName)
	{
		m_Name = aName;
	}

	std::string GameObject::GetTag()
	{
		return m_Tag;
	}
	void GameObject::SetTag(const std::string & aTag)
	{
		m_Tag = aTag;
	}

	int GameObject::GetRenderMask()
	{
		return m_RenderMask;
	}
	void GameObject::SetRenderMask(int aMask)
	{
		m_RenderMask = aMask;
	}

	int GameObject::GetPhysicsMask()
	{
		return m_PhysicsMask;
	}
	void GameObject::SetPhysicsMask(int aMask)
	{
		m_PhysicsMask = aMask;
	}

	GameObject * GameObject::GetParent()
	{
		return m_Parent;
	}
	void GameObject::SetParent(GameObject * aParent)
	{
		m_Parent = aParent;
	}
	
	void GameObject::AddChild(GameObject * aChild)
	{
		if (!Utilities::Exists<GameObject*>(m_Children, aChild))
		{
			m_Children.push_back(aChild);
		}
	}
	void GameObject::AddChildren(const std::vector<GameObject*> & aChildren)
	{
		for (std::vector<GameObject*>::const_iterator it = aChildren.begin(); it != aChildren.end(); it++)
		{
			AddChild(*it);
		}
	}
	void GameObject::AddChildren(const Array<GameObject*> & aChildren)
	{
		for (unsigned int i = 0; i < aChildren.GetCount(); i++)
		{
			AddChild(aChildren[i]);
		}
	}
	
	void GameObject::RemoveChild(std::string aName)
	{
		for (std::vector<GameObject*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
		{
			if ((*it)->GetName() == aName)
			{
				m_Children.erase(it);
				break;
			}
		}
	}
	void GameObject::RemoveChild(GameObject * aChild)
	{
		Utilities::Remove<GameObject*>(m_Children, aChild);
	}
	void GameObject::RemoveChildren(const std::vector<GameObject*> & aChildren)
	{
		for (std::vector<GameObject*>::const_iterator it = aChildren.begin(); it != aChildren.end(); it++)
		{
			RemoveChild(*it);
		}
	}
	void GameObject::RemoveChildren(const Array<GameObject*> & aChildren)
	{
		for (unsigned int i = 0; i < aChildren.GetCount(); i++)
		{
			RemoveChild(aChildren[i]);
		}
	}
	//
	Component * GameObject::GetComponent(const std::string & aTypename)
	{
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			if ((*it)->GetType().GetName() == aTypename)
			{
				return *it;
			}
		}
		return nullptr;
	}
	Component * GameObject::GetComponent(const Type & aType)
	{
		return GetComponent(aType.GetName());
	}
	Component * GameObject::GetComponentInChildren(const std::string & aTypename)
	{
		for (std::vector<GameObject*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
		{
			Component * component = (*it)->GetComponent(aTypename);
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}
	Component * GameObject::GetComponentInChildren(const Type & aType)
	{
		for (std::vector<GameObject*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
		{
			Component * component = (*it)->GetComponent(aType);
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}
	Component * GameObject::GetComponentInParent(const std::string & aTypename)
	{
		if (m_Parent != nullptr)
		{
			return m_Parent->GetComponent(aTypename);
		}
		return nullptr;
	}
	Component * GameObject::GetComponentInParent(const Type & aType)
	{
		if (m_Parent != nullptr)
		{
			return m_Parent->GetComponent(aType);
		}
		return nullptr;
	}
	std::vector<Component *> GameObject::GetComponents(const std::string & aTypename)
	{
		std::vector<Component*> components;
		for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			if ((*it)->GetType().GetName() == aTypename)
			{
				components.push_back(*it);
			}
		}
		return components;
	}
	std::vector<Component *> GameObject::GetComponents(const Type & aType)
	{
		return GetComponents(aType.GetName());
	}
	std::vector<Component *> GameObject::GetComponentsInChildren(const std::string & aTypename)
	{
		std::vector<Component*> components;
	
		for (std::vector<GameObject*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
		{
			std::vector<Component *> childComponents = (*it)->GetComponents(aTypename);
			for (std::vector<Component*>::iterator childIT = childComponents.begin(); childIT != childComponents.end(); childIT++)
			{
				components.push_back(*childIT);
			}
		}
		return components;
	}
	std::vector<Component *> GameObject::GetComponentsInChildren(const Type & aType)
	{
		return GetComponentsInChildren(aType.GetName());
	}
	std::vector<Component *> GameObject::GetComponentsInParent(const std::string & aTypename)
	{
		if (m_Parent != nullptr)
		{
			return m_Parent->GetComponents(aTypename);
		}
		return std::vector<Component*>();
	}
	std::vector<Component *> GameObject::GetComponentsInParent(const Type & aType)
	{
		return GetComponentsInParent(aType.GetName());
	}
	Component * GameObject::AddComponent(const std::string & aTypename)
	{
		return AddComponent(Reflection::Runtime::TypeOf(aTypename));
	}
	Component * GameObject::AddComponent(const Type & aType)
	{
		if (Reflection::Runtime::IsBadType(aType))
		{
			DEBUG_LOG("Failed to add a component. The type is invalid.");
			return nullptr;
		}
		Property prop = aType.GetProperty("DisallowMultipleComponent");
	
		if (!prop.IsValid() && GetComponent(aType.GetName()) != nullptr)
		{
			DEBUG_LOG("Failed to add a component. %s contains the %s property and a component of the type already exists on the gameobject.", aType.GetName().c_str(), "DisallowMultipleComponent");
			return nullptr;
		}
		//Initialize the component with the memory manager and invoke the constructor through reflection.
		Component * component = (Component*)MEM_POOL_ALLOC(aType.GetSize(), aType.GetAlignment());
		if (component != nullptr)
		{
			component->m_GameObject = this;
			component = (Component*)aType.GetConstructor().Invoke(component);
			m_Components.push_back(component);
			component->OnRegister();
		}
		else
		{
			DEBUG_LOG("Failed to allocate a component. Possibly out of memory.");
		}
		return component;
	}
	void GameObject::RemoveComponent(Component * aComponent)
	{
		Utilities::Remove<Component*>(m_Components, aComponent);
	}
}
	