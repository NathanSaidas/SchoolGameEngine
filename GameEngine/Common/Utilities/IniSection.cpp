#include "IniSection.h"

namespace Engine
{
	CLASS_CPP(IniSection, Object);
	

	IniSection::IniSection() : Object()
	{
		SetName("");
	}

	IniSection::~IniSection()
	{
		for (int i = m_Variables.size() - 1; i >= 0; i--)
		{
			delete m_Variables[i];
			m_Variables[i] = nullptr;
		}
		m_Variables.clear();
	}

	void IniSection::Write(std::ofstream & aFileStream)
	{
		aFileStream << "[" << GetName() << "]\n";

		for (std::vector<Object*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
		{
			aFileStream << (*it)->ToString() << "\n";
		}
	}
	void IniSection::Read(std::fstream & aFileStream)
	{

	}

    void IniSection::LogConsole()
    {
        DEBUG_LOG("[ %s ]", GetName().c_str());
        for (std::vector<Object*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
        {
            DEBUG_LOG((*it)->ToString().c_str(),"");
        }
    }

	// -- Creates a new variable with the name and value. 
	void IniSection::AddBool(const string & aVariableName, bool & aValue)
	{
		if (!VariableExists(aVariableName))
		{
			IniBool * variable = new IniBool();
			variable->SetVariableName(aVariableName);
			variable->SetValue(aValue);
			m_Variables.push_back(variable);
		}
	}
	void IniSection::AddInt(const string & aVariableName, int & aValue)
	{
		if (!VariableExists(aVariableName))
		{
			IniInt * variable = new IniInt();
			variable->SetVariableName(aVariableName);
			variable->SetValue(aValue);
			m_Variables.push_back(variable);
		}
	}
	void IniSection::AddFloat(const string & aVariableName, float & aValue)
	{
		if (!VariableExists(aVariableName))
		{
			IniFloat * variable = new IniFloat();
			variable->SetVariableName(aVariableName);
			variable->SetValue(aValue);
			m_Variables.push_back(variable);
		}
	}
	void IniSection::AddString(const string & aVariableName, string & aValue)
	{
		if (!VariableExists(aVariableName))
		{
			IniString * variable = new IniString();
			variable->SetVariableName(aVariableName);
			variable->SetValue(aValue);
			m_Variables.push_back(variable);
		}
	}

	// -- Searches for a variable by name
	IniBool IniSection::GetBool(const string & aVariableName)
	{
		for (std::vector<Object*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
		{
			if ((*it)->GetName() == INI_BOOL)
			{
				IniBool * boolVar = dynamic_cast<IniBool*>(*it);
				if (boolVar != nullptr && boolVar->GetVariableName() == aVariableName)
				{
					//IniBool variable;
					//variable.SetName(boolVar->GetName());
					//variable.SetVariableName(boolVar->GetVariableName());
					//variable.SetValue(boolVar->GetValue());
					//return variable;
                    return *boolVar;
				}
			}
		}
		return IniBool(INI_BAD_VARIABLE_NAME);
	}
	IniInt IniSection::GetInt(const string & aVariableName)
	{
		for (std::vector<Object*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
		{
			if ((*it)->GetName() == INI_INT)
			{
				IniInt * intVar = dynamic_cast<IniInt*>(*it);
				if (intVar != nullptr && intVar->GetVariableName() == aVariableName)
				{
					IniInt variable;
					variable.SetName(intVar->GetName());
					variable.SetVariableName(intVar->GetVariableName());
					variable.SetValue(intVar->GetValue());
					return variable;
                    //return *intVar;
				}
			}
		}
		return IniInt(INI_BAD_VARIABLE_NAME);
	}
	IniFloat IniSection::GetFloat(const string & aVariableName)
	{
		for (std::vector<Object*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
		{
			if ((*it)->GetName() == INI_FLOAT)
			{
				IniFloat * floatVar = dynamic_cast<IniFloat*>(*it);
				if (floatVar != nullptr && floatVar->GetVariableName() == aVariableName)
				{
					//IniFloat variable;
					//variable.SetName(floatVar->GetName());
					//variable.SetVariableName(floatVar->GetVariableName());
					//variable.SetValue(floatVar->GetValue());
					//return variable;
                    return *floatVar;
				}
			}
		}
		return IniFloat(INI_BAD_VARIABLE_NAME);
	}
	IniString IniSection::GetString(const string & aVariableName)
	{
		for (std::vector<Object*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
		{
			if ((*it)->GetName() == INI_STRING)
			{
				IniString * stringVar = dynamic_cast<IniString*>(*it);
				if (stringVar != nullptr && stringVar->GetVariableName() == aVariableName)
				{
					//IniString variable;
					//variable.SetName(stringVar->GetName());
					//variable.SetVariableName(stringVar->GetVariableName());
					//variable.SetValue(stringVar->GetValue());
					//return variable;
                    return *stringVar;
				}
			}
		}
		return IniString(INI_BAD_VARIABLE_NAME);
	}

	// -- Removes a variable by name
	bool IniSection::RemoveVariable(const string & aVariableName)
	{
		for (std::vector<Object*>::iterator it = m_Variables.begin(); it != m_Variables.end(); it++)
		{
			string typeName = (*it)->GetName();

			if (typeName == INI_BOOL)
			{
				IniBool * boolVar = dynamic_cast<IniBool*>(*it);
				if (boolVar != nullptr && boolVar->GetVariableName() == aVariableName)
				{
					m_Variables.erase(it);
					return true;
				}
			}
			else if (typeName == INI_INT)
			{
				IniInt * intVar = dynamic_cast<IniInt*>(*it);
				if (intVar != nullptr && intVar->GetVariableName() == aVariableName)
				{
					m_Variables.erase(it);
					return true;
				}
			}
			else if (typeName == INI_FLOAT)
			{
				IniFloat * floatVar = dynamic_cast<IniFloat*>(*it);
				if (floatVar != nullptr && floatVar->GetVariableName() == aVariableName)
				{
					m_Variables.erase(it);
					return true;
				}
			}
			else if (typeName == INI_STRING)
			{
				IniString * stringVar = dynamic_cast<IniString*>(*it);
				if (stringVar != nullptr && stringVar->GetVariableName() == aVariableName)
				{
					m_Variables.erase(it);
					return true;
				}
			}

		}
		return false;
	}

	bool IniSection::VariableExists(const string & aVariableName)
	{
		if (GetBool(aVariableName).GetVariableName() != INI_BAD_VARIABLE_NAME)
		{
			return true;
		}
		else if (GetInt(aVariableName).GetVariableName() != INI_BAD_VARIABLE_NAME)
		{
			return true;
		}
		else if (GetFloat(aVariableName).GetVariableName() != INI_BAD_VARIABLE_NAME)
		{
			return true;
		}
		else if (GetString(aVariableName).GetVariableName() != INI_BAD_VARIABLE_NAME)
		{
			return true;
		}
		return false;
	}
}