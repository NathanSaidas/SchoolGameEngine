#include "Component.h"

using namespace Engine::Reflection;

namespace Engine
{

    CLASS_CPP(Component, Object)
    METHOD_INFO_CPP(Component, Awake, new MethodActionInfo<Component>("Component","Awake", (&Component::Awake)))
    METHOD_INFO_CPP(Component, Start, new MethodActionInfo<Component>("Component", "Start", (&Component::Start)))
    METHOD_INFO_CPP(Component, OnDestroy, new MethodActionInfo<Component>("Component", "OnDestroy", (&Component::OnDestroy)))
    METHOD_INFO_CPP(Component, Update, new MethodActionInfo<Component>("Component", "Update", (&Component::Update)))
    METHOD_INFO_CPP(Component, Render, new MethodActionInfo<Component>("Component", "Awake", (&Component::Render)))
    METHOD_INFO_CPP(Component, NetworkCallback, (new MethodActionInfo<Component,void*>("Component", "NetworkCallback", (&Component::NetworkCallback))))

    void Component::Awake()
    {
        printf("Component Awake\n");
    }
    void Component::Start()
    {
        printf("Component Start\n");
    }
    void Component::OnDestroy()
    {
        printf("Component OnDestroy\n");
    }
    void Component::Update()
    {
        printf("Component Update\n");
    }
    void Component::Render()
    {
        printf("Component Render\n");
    }
    void Component::NetworkCallback(void * aData)
    {
        printf("Component NetworkCallback\n");
    }
    void Component::SendMessage(const char * aMessage)
    {
        SendMessage(std::string(aMessage));
    }

    void Component::SendMessage(const char * aMessage, void * aData)
    {
        SendMessage(std::string(aMessage), aData);
    }

    void Component::SendMessage(std::string & aMessage)
    {
        Type type = GetType();

        std::vector<ClassMember*> members = type.GetMembers();
        for (std::vector<ClassMember*>::iterator memberIt = members.begin(); memberIt != members.end(); ++memberIt)
        {
            if ((*memberIt)->GetMemberName() == aMessage)
            {
                
                try
                {
                    MethodActionInfo<Component> * member = (MethodActionInfo<Component>*)(*memberIt);
                    member->GetMethod()(this);
                }
                catch (std::exception aException)
                {
                    printf("Send Message Thrown an Exception %s", aException.what());
                }
                
                break;
            }
        }
    }
    void Component::SendMessage(std::string & aMessage, void * aData)
    {
        Type type = GetType();

        std::vector<ClassMember*> members = type.GetMembers();
        for (std::vector<ClassMember*>::iterator memberIt = members.begin(); memberIt != members.end(); ++memberIt)
        {
            if ((*memberIt)->GetMemberName() == aMessage)
            {
                
                try
                {
                    MethodActionInfo<Component, void*> * member = (MethodActionInfo<Component, void*>*)(*memberIt);
                    member->GetMethod()(this, aData);
                }
                catch (std::exception aException)
                {
                    printf("Send Message Thrown an Exception %s", aException.what());
                }
                
                break;
            }
        }
    }
}