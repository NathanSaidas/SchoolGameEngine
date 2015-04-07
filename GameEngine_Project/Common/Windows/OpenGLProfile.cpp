#include "OpenGLProfile.h"

namespace Engine
{
	const std::string OpenGLProfile::NAMES[Values::Any + 1] =
	{
		"Core",
		"Compatibility",
		"ForwardCore",
		"ForwardCompatibility",
		"Any"
	};

	RDEFINE_ENUM(OpenGLProfile)
	RENUM_CPP(OpenGLProfile, Values, Values::Any + 1, NAMES)
}