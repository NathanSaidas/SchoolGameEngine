#ifndef GAME_ENGINE_STRING_EXTENSIONS_H
#define GAME_ENGINE_STRING_EXTENSIONS_H

#include "../BasicTypes.h"
#include <string>

namespace Engine
{
	namespace Utilities
	{
		void GetWords(std::string aString, std::vector<std::string> & aWords);
		std::string F2S(Float32 aValue);
		std::string I2S(SInt32 aValue);
		Float32 S2F(const std::string & aString);
		SInt32 S2I(const std::string & aString);
	}
}


#endif
