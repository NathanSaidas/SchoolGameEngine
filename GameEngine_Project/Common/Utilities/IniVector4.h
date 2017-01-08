#ifndef GAME_ENGINE_INI_VECTOR_4_H
#define GAME_ENGINE_INI_VECTOR_4_H

#include "IniVariables.h"
#include "StringExtensions.h"
#include "../Math/Vector4.h"

namespace Engine
{
	template<>
	class IniVariable<Vector4> : public Object
	{
	public:
		IniVariable() : Object()
		{
			m_VariableName = "";
			SetName(string("Ini").append(Reflection::TypeTrait<Vector4>::Name()));
		}
		IniVariable(const string & aVariableName) : Object()
		{
			m_VariableName = aVariableName;
			SetName(string("Ini").append(Reflection::TypeTrait<Vector4>::Name()));
		}
		IniVariable(const char * aVariableName) : Object()
		{
			m_VariableName = aVariableName;
			SetName(string("Ini").append(Reflection::TypeTrait<Vector4>::Name()));
		}
		~IniVariable()
		{
		}

		/// <summary>
		/// Gets the variable name.
		/// </summary>
		/// <returns> Returns the variable name </returns>
		string GetVariableName()
		{
			return m_VariableName;
		}
		/// <summary>
		/// Sets the variable name
		/// </summary>
		/// <param name="aVariableName">The name of the variable.</param>
		void SetVariableName(const string & aVariableName)
		{
			m_VariableName = aVariableName;
		}
		/// <summary>
		/// Sets the variable name
		/// </summary>
		/// <param name="aVariableName">The name of the variable.</param>
		void SetVariableName(const char * aVariableName)
		{
			m_VariableName = aVariableName;
		}

		/// <summary>
		/// Gets the variable value.
		/// </summary>
		/// <returns> Returns the variable value </returns>
		Vector4 GetValue()
		{
			return m_Value;
		}

		/// <summary>
		/// Sets the variable value
		/// </summary>
		/// <param name="aValue">The value of the variable.</param>
		void SetValue(const Vector4 & aValue)
		{
			m_Value = aValue;
		}

		/// <summary>
		/// Determines if a variable is a bad variable or not.
		/// </summary>
		/// <returns> Returns true if the variable is a bad variable. </returns>
		static bool IsBadValue(IniVariable<Vector4> & aType)
		{
			return aType.GetName() == INI_BAD_VARIABLE_NAME;
		}


		/// <summary>
		/// Override the object.ToString() method to a string representation of the type name variable name and value
		/// </summary>
		/// <returns> Returns the variable value </returns>
		string ToString()
		{
			//Format ex. type_name variable_name = value
			//Example: int points = 64

			const char * typeName = Reflection::TypeTrait<Vector4>::Name();
			string value = "";

			if (strcmp(typeName, Reflection::TypeTrait<Vector4>::Name()) == 0)
			{
				value = "x: ";
				std::string sValue = Utilities::F2S(m_Value.x);
				value.append(sValue).append(" y: ");
				sValue = Utilities::F2S(m_Value.y);
				value.append(sValue).append(" z: ");
				sValue = Utilities::F2S(m_Value.z);
				value.append(sValue).append(" w: ");
				sValue = Utilities::F2S(m_Value.w);
				value.append(sValue);
			}
			else
			{
				DEBUG_LOG("Invalid variable type. Cannot convert value.");
				return "";
			}
			//Return a copy of the string with the proper format.
			return string(typeName).append(" ").append(m_VariableName).append(" = ").append(value);
		}

	private:
		/// <summary>
		/// The name of the variable
		/// </summary>
		string m_VariableName;
		/// <summary>
		/// The value of the variable.
		/// </summary>
		Vector4 m_Value;

	};

	typedef IniVariable<Vector4> IniVector4;

	TYPE_DEFINE(IniVector4);
}

#endif