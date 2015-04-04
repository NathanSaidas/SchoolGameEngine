#ifndef GAME_ENGINE_OPENGL_PROFILE_H
#define GAME_ENGINE_OPENGL_PROFILE_H

#include "../Enum.h"

enum class OpenGLProfile
{
	Core,
	Compatibility,
	ForwardCore,
	ForwardCompatibility,
	Any
};

namespace Engine
{
	class OpenProfile : public Enum
	{
	public:
		enum Values
		{
			Core,
			Compatibility,
			ForwardCore,
			ForwardCompatibility,
			Any
		};
		RDECLARE_ENUM_IMPLEMENTATION(OpenProfile,Values)
	private:
		static const std::string NAMES[Values::Any + 1];
	};
	//public:
	//	enum Values
	//	{
	//		Core,
	//		Compatibility,
	//		ForwardCore,
	//		ForwardCompatibility,
	//		Any
	//	};
	//private:
	//	RDECLARE_ENUM(OpenProfile)
	//protected:
	//	std::string GetName();
	//	Array<std::string> GetNames();
	//	SInt32 GetValue();
	//	Array<SInt32> GetValues();
	//public:
	//	OpenProfile();
	//	OpenProfile(const OpenProfile::Values & aValue);
	//	OpenProfile(SInt32 aValue);
	//	
	//	inline OpenProfile operator=(const OpenProfile::Values & aValue)
	//	{
	//		m_Value = aValue;
	//		return *this;
	//	}
	//	inline OpenProfile operator=(int aValue)
	//	{
	//		m_Value = (OpenProfile::Values)aValue;
	//		return *this;
	//	}
	//	inline bool operator==(const OpenProfile::Values & aValue)
	//	{
	//		return m_Value == aValue;
	//	}
	//	inline bool operator==(const OpenProfile & aEnum)
	//	{
	//		return m_Value == aEnum.m_Value;
	//	}
	//	inline bool operator!=(const OpenProfile::Values & aValue)
	//	{
	//		return m_Value != aValue;
	//	}
	//	inline bool operator!=(const OpenProfile & aEnum)
	//	{
	//		return m_Value != aEnum.m_Value;
	//	}
	//
	//private:
	//	Values m_Value;
	//	static const std::string NAMES[Values::Any + 1];
	//};
}

#endif