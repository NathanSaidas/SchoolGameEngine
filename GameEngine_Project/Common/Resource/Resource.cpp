#include "Resource.h"
#include "ResourceDatabase.h"

namespace Engine
{
	RDEFINE_CLASS(Resource, Object)

	/**
	*
	*/
	Resource::Resource()
	{
		GenerateID();
	}
	/**
	*
	*/
	Resource::~Resource()
	{

	}
	/**
	* Saves the changes made to a resource
	* @param The path to the directory of the resource. Save uses ../Directory/GetName for the full path.
	*/
	void Resource::Save(const std::string & aDirectory)
	{
		string filename = aDirectory;
		filename.append(GetName());
		IniFileStream file;
		file.SetPath(filename);
		file.AddSection("Resource");
		file.BindSection("Resource");
		file.AddString(ResourceDatabase::META_ID_TOKEN, m_UniqueID.ToString());
		file.Save();
	}
	/**
	* Loads changes made from a resource
	@param The path to the directory of the resource. Load uses ../Directory/GetName for the full path.
	*/
	void Resource::Load(const std::string & aDirectory)
	{
		string filename = aDirectory;
		filename.append(GetName());
		IniFileStream file;
		file.SetPath(filename);
		file.Read();
		if (!file.BindSection("Resource"))
		{
			DEBUG_LOG("Invalid resource file %s", filename.c_str());
		}
		else
		{
			IniString metaID = file.GetString(ResourceDatabase::META_ID_TOKEN);
			if (IniString::IsBadValue(metaID))
			{
				DEBUG_LOG("Missing meta-id-token variable {%s}", ResourceDatabase::META_ID_TOKEN.c_str());
			}
			else
			{
				m_UniqueID = Guid(metaID.GetValue());
			}
		}
	}
	/**
	* Generates the Unique ID
	*/
	void Resource::GenerateID()
	{
		m_UniqueID = Guid::NewGuid();
	}
	/**
	* Gets the unique ID
	* @return Returns the unique ID
	*/
	Guid Resource::GetID()
	{
		return m_UniqueID;
	}
}