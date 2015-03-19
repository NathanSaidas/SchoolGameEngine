#ifndef GAME_ENGINE_INI_SECTION_H
#define GAME_ENGINE_INI_SECTION_H


#include <vector>
#include "IniVariables.h"
#include "../BasicTypes.h"


namespace Engine
{
	class IniSection : public Object
	{
		CLASS_HEADER(IniSection);
	public:
		IniSection();
		~IniSection();


		void Write(std::ofstream & aFileStream);
		void Read(std::fstream & aFileStream);

        void LogConsole();

		// -- Creates a new variable with the name and value. 
		void AddBool(const string & aVariableName, bool & aValue);
		void AddInt(const string & aVariableName, int & aValue);
		void AddFloat(const string & aVariableName, float & aValue);
		void AddString(const string & aVariableName, string & aValue);

		// -- Searches for a variable by name
		IniBool GetBool(const string & aVariableName);
		IniInt GetInt(const string & aVariableName);
		IniFloat GetFloat(const string & aVariableName);
		IniString GetString(const string & aVariableName);

		// -- Removes a variable by name
		bool RemoveVariable(const string & aVariableName);

		bool VariableExists(const string & aVariableName);

	private:
		

		std::vector<Object*> m_Variables;
	};
}

#endif