#ifndef GAME_ENGINE_ALLOCATION_INFO_H
#define GAME_ENGINE_ALLOCATION_INFO_H

#pragma region CHANGE LOG
/// -- January, 31, 2015 - Nathan Hanlan - Added AllocationInfo class/file
#pragma endregion

#include <string>
#include "../ValueTypes.h"
#include "AllocatorType.h"


namespace Engine
{
    namespace Memory
    {		
		/// <summary>
		///	The class used to represent allocation info. The filename the line and information regarding the allocator responsible for the allocation.
		/// </summary>
        class AllocationInfo
        {
        public:
			AllocationInfo()
			{
				m_Filename = "";
				m_Line = 0;
				m_AllocatorID = 0;
				m_AllocationType = AllocatorType::Pool;
				m_Address = 0;
				m_Count = 0;
				m_AllocatorMisMatch = false;
			}

            AllocationInfo(const char * aFilename, 
                UInt32 aLine, 
                UInt8 aAllocatorID,
                AllocatorType aAllocationType, 
                IntPtr aAddress)
            {
                m_Filename = aFilename;
                m_Line = aLine;
                m_AllocatorID = aAllocatorID;
                m_AllocationType = aAllocationType;
                m_Address = aAddress;
                m_Count = 1;
                m_AllocatorMisMatch = false;
            }
            ~AllocationInfo()
            {

            }
			
			/// <summary>
			/// Gets the filename.
			/// </summary>
			/// <returns>Returns the filename</returns>
			inline const char * GetFilename()
            {
                return m_Filename;
            }		

			/// <summary>
			/// Gets the line.
			/// </summary>
			/// <returns>Returns the line</returns>
			inline UInt32 GetLine()
            {
                return m_Line;
            }
						
			/// <summary>
			/// Gets the amount of times this address has been allocated
			/// </summary>
			/// <returns>Returns the count.</returns>
			inline unsigned GetCount()
            {
                return m_Count;
            }

			
			/// <summary>
			/// Increments the count by one.
			/// </summary>
			inline void AddCount()
            {
                m_Count++;
            }
			
			/// <summary>
			/// Decrements the count by one
			/// </summary>
			inline void SubtractCount()
            {
                m_Count--;
            }
			
			/// <summary>
			/// Gets the id of the allocator responsible of the allocation made.
			/// </summary>
			/// <returns>Returns the allocator ID</returns>
			inline UInt8 GetAllocatorID()
            {
                return m_AllocatorID;
            }
			
			/// <summary>
			/// Sets the id of the allocator made. If the ID does not match the previous FlagAllocatorMisMatch should be invoked.
			/// </summary>
			/// <param name="aAllocatorID">The ID of the allocator</param>
			inline void SetAllocatorID(UInt8 aAllocatorID)
            {
                m_AllocatorID = aAllocatorID;
            }
			
			/// <summary>
			/// Flags the allocator for giving a warning about a mismatch in allocations made. (Address used two times or more without being deallocated)
			/// </summary>
			inline void FlagAllocatorMismatch()
            {
                m_AllocatorMisMatch = true;
            }
			
			/// <summary>
			/// Gets the type of allocator that made the allocation
			/// </summary>
			/// <returns>Returns the allocator type</returns>
			inline AllocatorType GetAllocatorType()
            {
                return m_AllocationType;
            }
			
			/// <summary>
			/// Returns the address of the allocation.
			/// </summary>
			/// <returns>Returns the address of the allocation made.</returns>
			inline IntPtr GetAddress()
            {
                return m_Address;
            }
            

        private:
            const char * m_Filename;
            UInt32 m_Line;
            UInt32 m_Count;
            UInt8 m_AllocatorID;
            AllocatorType m_AllocationType;
            bool m_AllocatorMisMatch;
            IntPtr m_Address;
            
        };
    }
}

#endif