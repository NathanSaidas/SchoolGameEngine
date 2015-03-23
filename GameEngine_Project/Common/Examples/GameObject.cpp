#include "GameObject.h"

using namespace Engine::Reflection;

namespace Engine
{
    //CLASS_CPP(GameObject, Object)
	//
    //GameObject::GameObject()
    //{
	//
    //}
    //GameObject::~GameObject()
    //{
    //    for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
    //    {
    //        if ((*it) != nullptr)
    //        {
    //            delete (*it);
    //        }
    //    }
    //    m_Components.clear();
    //}
	//
    //void GameObject::SendMessage(const char * aMessage)
    //{
    //    SendMessage(std::string(aMessage));
    //}
	//
    //void GameObject::SendMessage(const char * aMessage, void * aData)
    //{
    //    SendMessage(std::string(aMessage), aData);
    //}
	//
	//
    //void GameObject::SendMessage(std::string & aMessage)
    //{
    //    for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
    //    {
    //        Component * component = (*it);
    //        component->SendMessage(aMessage);
    //    }
    //}
    //void GameObject::SendMessage(std::string & aMessage, void * aData)
    //{
    //    for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
    //    {
    //        Component * component = (*it);
    //        component->SendMessage(aMessage, aData);
    //    }
    //}
	//
    //void GameObject::AddComponent(Component * aComponent)
    //{
    //    if (aComponent != nullptr)
    //    {
    //        m_Components.push_back(aComponent);
    //    }
    //}
    //void GameObject::RemoveComponent(Component * aComponent)
    //{
    //    for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
    //    {
    //        if ((*it) == aComponent)
    //        {
    //            delete (*it);
    //            break;
    //        }
    //    }
    //}
}