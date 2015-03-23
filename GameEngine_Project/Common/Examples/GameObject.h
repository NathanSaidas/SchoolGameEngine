#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../Engine.h"
#include "Component.h"
#include <vector>
#include <string>


namespace Engine
{

    //class GameObject : public Object
    //{
    //    CLASS_HEADER(GameObject)
    //    
    //public:
    //    GameObject();
    //    ~GameObject();
	//
	//
    //    ///Send Message Broadcasts a function call message to all components to invoke.
    //    ///Send Message with no arguments besides message is intended for the use of void function calls with no arguments
    //    ///Send Message with void * arg is intended for the use of void function calls with a single void * argument.
    //    ///void * may be used as any data type pretty much in c++ so it could be considered user data type.
    //    ///void * could easily be replaced with an 'object' base class and that way type information could be retrieved at runtime.
	//
    //    void SendMessage(const char * aMessage);
    //    void SendMessage(const char * aMessage, void * aArgs);
    //    void SendMessage(std::string & aMessage);
    //    void SendMessage(std::string & aMessage, void * aArgs);
	//
    //    void AddComponent(Component * aComponent);
    //    void RemoveComponent(Component * aComponent);
	//
    //private:
    //    std::vector<Component*> m_Components;
    //};
	//
    //TYPE_DEFINE(GameObject)
    //TYPE_DEFINE_PTR(GameObject*, "GameObject Ptr")
}

#endif