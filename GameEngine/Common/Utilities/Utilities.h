#ifndef GAME_ENGINE_UTILITIES_H
#define GAME_ENGINE_UTILITIES_H

#include "Debug.h"
#include "IniFileStream.h"
#include "IniVariables.h"

namespace Engine
{
    void GetWords(std::string aString, std::vector<std::string> & aWords);
}

#endif