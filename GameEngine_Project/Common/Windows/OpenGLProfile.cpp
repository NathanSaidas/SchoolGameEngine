#include "OpenGLProfile.h"

namespace Engine
{
	const std::string OpenProfile::NAMES[Values::Any + 1] =
	{
		"Core",
		"Compatibility",
		"ForwardCore",
		"ForwardCompatibility",
		"Any"
	};

	RDEFINE_ENUM_IMPLEMENTATION(OpenProfile,Values,Values::Any + 1,NAMES)

	//OpenProfile::OpenProfile()
	//{
	//	Array<SInt32> values = GetValues();
	//	if (values.GetCount() > 0)
	//	{
	//		m_Value = (Values)values[0];
	//	}
	//	m_Value = (Values)0;
	//}
	//OpenProfile::OpenProfile(const OpenProfile::Values & aValue)
	//{
	//	m_Value = aValue;
	//}
	//OpenProfile::OpenProfile(SInt32 aValue)
	//{
	//	m_Value = (Values)aValue;
	//}
	//std::string OpenProfile::GetName()
	//{
	//	return NAMES[(SInt32)m_Value];
	//}
	//Array<std::string> OpenProfile::GetNames()
	//{
	//	Array<std::string> names(Values::Any + 1);
	//	for (int i = 0; i < Values::Any + 1; i++)
	//	{
	//		names[i] = NAMES[i];
	//	}
	//	return names;
	//}
	//SInt32 OpenProfile::GetValue()
	//{
	//	return (SInt32)m_Value;
	//}
	//Array<SInt32> OpenProfile::GetValues()
	//{
	//	Array<SInt32> values(Values::Any + 1);
	//	for (int i = 0; i < Values::Any + 1; i++)
	//	{
	//		values[i] = i;
	//	}
	//	return values;
	//}
}