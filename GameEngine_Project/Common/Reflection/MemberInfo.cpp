#include "MemberInfo.h"
#include "../Memory/Memory.h"

namespace Engine
{
    namespace Reflection
    {
        MemberInfo::MemberInfo(char * aClassTypeName, char * aMemberName, char * aMemberTypename, size_t aOffset, bool aIsPublic)
        {
            m_ClassTypeName = aClassTypeName;
            m_MemberName = aMemberName;
            m_MemberTypename = aMemberTypename;
            m_Offset = aOffset;
            m_IsPublic = aIsPublic;
        }
        MemberInfo::MemberInfo()
        {
            m_ClassTypeName = "";
            m_MemberName = "";
            m_MemberTypename = "";
            m_Offset = 0;
            m_IsPublic = true;
        }

        MemberInfo::~MemberInfo()
        {

        }
        char * MemberInfo::GetClassTypeName()
        {
            return m_ClassTypeName;
        }
        char * MemberInfo::GetMemberName()
        {
            return m_MemberName;
        }
        char * MemberInfo::GetMemberTypename()
        {
            return m_MemberTypename;
        }
        size_t MemberInfo::GetOffset()
        {
            return m_Offset;
        }

        bool MemberInfo::IsPublic()
        {
            return m_IsPublic;
        }

        object * MemberInfo::GetOffsetPointer(object * aObject)
        {
            return (object*)Memory::MemoryUtils::AddPtr(aObject, m_Offset);
        }
    }
    
}