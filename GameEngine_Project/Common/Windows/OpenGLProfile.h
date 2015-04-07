#ifndef GAME_ENGINE_OPENGL_PROFILE_H
#define GAME_ENGINE_OPENGL_PROFILE_H

#include "../Enum.h"

//enum class OpenGLProfile
//{
//	Core,
//	Compatibility,
//	ForwardCore,
//	ForwardCompatibility,
//	Any
//};

namespace Engine
{
	class OpenGLProfile : public Enum
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
		RDECLARE_ENUM(OpenGLProfile)
		RENUM_H(OpenGLProfile, Values)
	private:
		static const std::string NAMES[Values::Any + 1];
	};
}

#endif