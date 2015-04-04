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
		RDECLARE_CLASS(IniFileStream)
	public:
		IniFileStream();
		~IniFileStream();

		//Clears all variables. Opens up the file, reads in all variables. Closes the file.
		void Read();
		//Opens up the file, saves all variables to the file. Closes the file.
		void Save();
        void LogConsole();
        void Clear();

		bool AddSection(const std::string & aSectionName);
		bool RemoveSection(const std::string & aSectionName);
		bool BindSection(const std::string & aSectionName);
		void GetSectionNames(std::vector<std::string> & aSectionNames);

		// -- Creates a new variable with the name and value. 
		void AddBool(const std::string & aVariableName, bool aValue);
		void AddInt(const std::string & aVariableName, int aValue);
		void AddFloat(const std::string & aVariableName, float aValue);
		void AddString(const std::string & aVariableName, std::string aValue);
		void AddVector3(const std::string & aVariableName, Vector3 aValue);
		void AddVector4(const std::string & aVariableName, Vector4 aValue);

		// -- Searches for a variable by name in the currently bound section
		IniBool GetBool(const std::string & aVariableName);
		IniInt GetInt(const std::string & aVariableName);
		IniFloat GetFloat(const std::string & aVariableName);
		IniString GetString(const std::string & aVariableName);
		IniVector3 GetVector3(const std::string & aVariableName);
		IniVector4 GetVector4(const std::string & aVariableName);


		// -- Removes a variable by name
		bool RemoveVariable(const std::string & aVariableName);
		bool VariableExists(const std::string & aVariableName);

		std::string GetPath();
		void SetPath(const std::string & aPath);
		void SetPath(const char * aPath);

		//TODO: Add in sections.
		//Eg. IniSection.. foreach(IniSection ->  IniSection->Write(stream &))
		// IniSection could have their own variable lists.

	private:
		std::string m_Path;
		IniSection * m_BoundSection;
		std::vector<IniSection*> m_Sections;
	};
}

#endif