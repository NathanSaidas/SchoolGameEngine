#include "../Engine.h"
#include "../Examples/Examples.h"


using namespace Engine;



class PropertyBinder : public Reflection::AttributeBinder
{
public:
    void BindInteger(Reflection::IntAttribute & aAttribute, Type & aType);
    void BindFloat(Reflection::FloatAttribute & aAttribute, Type & aType);
    void BindBool(Reflection::BoolAttribute & aAttribute, Type & aType);
    void BindString(Reflection::StringAttribute & aAttribute, Type & aType);
    void BindFunction(Reflection::FunctionAttribute & aAttribute, Type & aType);
};

void PropertyBinder::BindInteger(Reflection::IntAttribute & aAttribute, Type & aType)
{

}
void PropertyBinder::BindFloat(Reflection::FloatAttribute & aAttribute, Type & aType)        
{

}
void PropertyBinder::BindBool(Reflection::BoolAttribute & aAttribute, Type & aType)          
{

}
void PropertyBinder::BindString(Reflection::StringAttribute & aAttribute, Type & aType)      
{
    std::string attribname = std::string(aAttribute.GetAttributeName());
    std::string substring = attribname.substr(0, 10);
    if (substring == "CustomProp")
    {
        std::string propName = attribname.substr(10, attribname.size() - 10);
        aType.InsertProperty(Property(propName, aAttribute.GetValue()));
    }
}
void PropertyBinder::BindFunction(Reflection::FunctionAttribute & aAttribute, Type & aType)  
{

}

int main()
{
    //Compile the Reflection Meta Data
    Reflection::Runtime::Compile(new PropertyBinder());


    Type type = Reflection::Runtime::TypeOf("Triangle");
    std::vector<Property> triangleProperties = type.GetProperties();


    
    system("pause");
    //Release resources allocated by the Reflection Runtime.
    Reflection::Runtime::Terminate();

	return 0;
}