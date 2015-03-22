#ifndef GAME_ENGINE_UTILITIES_H
#define GAME_ENGINE_UTILITIES_H

#include <vector>
#include "Debug.h"
#include "Array.h"
#include "IniFileStream.h"
#include "IniVariables.h"


namespace Engine
{
    void GetWords(std::string aString, std::vector<std::string> & aWords);

	namespace Utilities
	{
		template<typename T>
		bool Exists(std::vector<T> & aVector, T aElement)
		{
			for (std::vector<T>::iterator it = aVector.begin(); it != aVector.end(); it++)
			{
				if ((*it) == aElement)
				{
					return true;
				}
			}
			return false;
		}

		template<typename T>
		bool Remove(std::vector<T> & aVector, T aElement)
		{
			for (std::vector<T>::iterator it = aVector.begin(); it != aVector.end(); it++)
			{
				if ((*it) == aElement)
				{
					aVector.erase(it);
					return true;
				}
			}
			return false;
		}
	}
}

#endif