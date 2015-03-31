#ifndef GAME_ENGINE_POINTER_H
#define GAME_ENGINE_POINTER_H

#pragma region CHANGE LOG
/// --	March	30	2015 - Nathan Hanlan - Added class/file Pointer.h.
#pragma endregion

#include "MemoryManager.h"
#include "../Utilities/Utilities.h"
#include "../SystemAssert.h"
#include "../SystemError.h"

namespace Engine
{

	//This class is designed to keep track of references to a pointer. 
	//
	template<typename TYPE>
	class Pointer
	{
	public:
		///Default Constructor will allocate a instance of the TYPE and set the reference count to 1.
		Pointer()
		{
			//Set Defaults
			m_Pointer = nullptr;
			m_Count = nullptr;

			//Allocate and set count to 1.
			m_Count = new int;
			*m_Count = 1;
			Alloc();
		}
		///Copy Constructor will take the pointer from the incoming pointer and increment the reference count.
		Pointer(const Pointer & aPointer)
		{
#ifdef CONFIG_MEMORY_DEBUG
			Assert(aPointer.m_Pointer != nullptr, Error::BAD_POINTER_COPY);
#endif
			//Take pointer / count and increment reference.
			m_Pointer = aPointer.m_Pointer;
			m_Count = aPointer.m_Count;
			AddReference();
		}
		
		///Destructor decrements a reference.
		~Pointer()
		{
			RemoveReference();
		}

		///Asignment operator removes previous reference and adds a reference to the incoming pointer.
		Pointer operator=(const Pointer & aPointer)
		{
			RemoveReference();
			m_Pointer = aPointer.m_Pointer;
			m_Count = aPointer.m_Count;
			AddReference();
			return *this;
		}

		///Access to the data.
		TYPE * operator->()
		{
			if (m_Count == nullptr || *m_Count == 0)
			{
				m_Pointer = nullptr;
			}
			return m_Pointer;
		}

		///Access to the data.
		TYPE * operator->() const
		{
			if (m_Count == nullptr || *m_Count == 0)
			{
				return nullptr;
			}
			return m_Pointer;
		}

		///Returns true if the 
		bool IsAlive()
		{
			if (m_Count == nullptr || *m_Count == 0)
			{
				m_Pointer = nullptr;
			}
			return m_Pointer != nullptr;
		}

		///Returns true if the 
		bool IsAlive() const
		{
			return m_Pointer != nullptr && m_Count != nullptr && *m_Count != 0;
		}

		///Returns the reference count
		int GetReferenceCount()
		{
			return *m_Count;
		}

		///Removes a reference from the pointer and sets the count / pointer to nullptr;
		void Release()
		{
			RemoveReference();
			m_Pointer = nullptr;
			m_Count = nullptr;
		}

		///Makes this pointer a unique instance and uses the assignment operator.
		void MakeUnique()
		{
			if (m_Count != nullptr && *m_Count > 1)
			{
				TYPE * prev = m_Pointer;
				Release();
				
				m_Count = new int;
				*m_Count = 1;
				Alloc();

				*m_Pointer = *prev;
			}
			//Else this is already unique.
			
		}

		///Makes this pointer unique using an already allocated pointer.
		void MakeUnique(TYPE * aPointer)
		{
			if (aPointer == nullptr)
			{
				return;
			}
			Memory::MemoryHeader * header = (Memory::MemoryHeader*)Memory::MemoryUtils::SubtractPtr(aPointer, 4);
			UInt8 flags;
			UInt8 id;
			UInt16 size;
			header->Read(flags, id, size);

			if (!((flags & Memory::MemoryFlags::POOL) == Memory::MemoryFlags::POOL))
			{
				DEBUG_LOG("Cannot make a pointer not allocated through a pool a managed pointer.");
				return;
			}

			RemoveReference();
			m_Pointer = aPointer;
			m_Count = new int;
			*m_Count = 1;
		}

	private:
		///Adds a reference to the pointer.
		void AddReference()
		{
			if (m_Count != nullptr)
			{
				(*m_Count)++;
			}
		}

		///Removes a refrence from the pointer. Handles deallocation upon meeting 0 references.
		void RemoveReference()
		{
			if (m_Count != nullptr)
			{
				(*m_Count)--;
				if ((*m_Count) == 0)
				{
					delete m_Count;
					m_Count = nullptr;
					Dealloc();
				}
			}
		}
		
		///Allocates a pointer. If the pointer has 
		void Alloc()
		{
			if (m_Pointer != nullptr)
			{
				DEBUG_LOG("Pointer has not been deallocated yet.");
				Dealloc();
			}
			m_Pointer = MEM_POOL_ALLOC_T(TYPE);
		}

		///Deallocates the memory associated with the pointer.
		void Dealloc()
		{
			MEM_POOL_DEALLOC_T(m_Pointer,TYPE);
		}

	
		TYPE * m_Pointer;
		int * m_Count;
	};

}

#endif