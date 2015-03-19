#ifndef GAME_ENGINE_INI_FILE_STREAM_H
#define GAME_ENGINE_INI_FILE_STREAM_H

#include <vector>
#include "IniSection.h"
#include "IniVariables.h"
#include "../BasicTypes.h"

namespace Engine
{
	class IniFileStream : object
	{
	public:
		IniFileStream();
		~IniFileStream();

		//Clears all variables. Opens up the file, reads in all variables. Closes the file.
		void Read();
		//Opens up the file, saves all variables to the file. Closes the file.
		void Save();
        void LogConsole();
        void Clear();

		bool AddSection(const string & aSectionName);
		bool RemoveSection(const string & aSectionName);
		bool BindSection(const string & aSectionName);
		void GetSectionNames(std::vector<string> & aSectionNames);

		// -- Creates a new variable with the name and value. 
		void AddBool(const string & aVariableName, bool & aValue);
		void AddInt(const string & aVariableName, int & aValue);
		void AddFloat(const string & aVariableName, float & aValue);
		void AddString(const string & aVariableName, string & aValue);

		// -- Searches for a variable by name in the currently bound section
		IniBool GetBool(const string & aVariableName);
		IniInt GetInt(const string & aVariableName);
		IniFloat GetFloat(const string & aVariableName);
		IniString GetString(const string & aVariableName);



		// -- Removes a variable by name
		bool RemoveVariable(const string & aVariableName);
		bool VariableExists(const string & aVariableName);

		string GetPath();
		void SetPath(const string & aPath);
		void SetPath(const char * aPath);

		//TODO: Add in sections.
		//Eg. IniSection.. foreach(IniSection ->  IniSection->Write(stream &))
		// IniSection could have their own variable lists.

	private:
		string m_Path;
		IniSection * m_BoundSection;
		std::vector<IniSection*> m_Sections;
	};
}

#endif