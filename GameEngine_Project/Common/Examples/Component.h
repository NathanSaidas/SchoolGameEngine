#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Engine.h"

namespace Engine
{
    //class Component : public Object
    //{
    //    CLASS_HEADER(Component)
    //    METHOD_INFO_HEADER(Component,Awake)
    //    METHOD_INFO_HEADER(Component, Start)
    //    METHOD_INFO_HEADER(Component, OnDestroy)
    //    METHOD_INFO_HEADER(Component, Update)
    //    METHOD_INFO_HEADER(Component, Render)
    //    METHOD_INFO_HEADER(Component, NetworkCallback)
	//
    //protected:
    //    virtual void Awake();
    //    virtual void Start();
    //    virtual void OnDestroy();
    //    virtual void Update();
    //    virtual void Render();
    //    virtual void NetworkCallback(void * aData);
	//
    //public:
    //    //Send Message implementation on the Components just simply searches for functions defined in the component using reflection
    //    //Then invokes the invoke call.
	//
    //    void SendMessage(const char * aMessage);
    //    void SendMessage(const char * aMessage, void * aArgs);
    //    void SendMessage(std::string & aMessage);
    //    void SendMessage(std::string & aMessage, void * aData);
	//
    //};
	//
    //TYPE_DEFINE(Component)
    //TYPE_DEFINE_PTR(Component*, "Component Ptr");
}

#endif