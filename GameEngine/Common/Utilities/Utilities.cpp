#include "Utilities.h"
#include "../BasicTypes.h"

namespace Engine
{
    void GetWords(std::string aString, std::vector<std::string> & aWords)
    {
        UInt32 end = 0;

        while (aString.size() > 0)
        {
            for (int i = 0; i < aString.size(); i++)
            {
                if (aString[i] == ' ')
                {
                    end = i;
                    string word = aString.substr(0, end);
                    aString.erase(aString.begin(), aString.begin() + end + 1);
                    aWords.push_back(word);
                    break;
                }
                else if (i == aString.size() - 1)
                {
                    end = i;
                    string word = aString.substr(0, end + 1);
                    aString.clear();
                    aWords.push_back(word);
                    break;
                }
            }
            
        }
    }
}