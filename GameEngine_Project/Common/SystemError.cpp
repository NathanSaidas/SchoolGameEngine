#include "SystemError.h"

namespace Engine
{
    const char * Error::BAD_FRAME_ALLOCATOR_INIT = "Cannot initialize Frame Allocator with 0 memory.";
    const char * Error::BAD_FRAME_ALLOCATOR_ALLOCATION = "Cannot allocate 0 bytes from Frame Allocator";
    const char * Error::BAD_FRAME_ALLOCATOR_DEALLOCATION = "Cannot deallocate memory using Frame Allocator, use Reset instead.";

    const char * Error::BAD_STACK_ALLOCATOR_INIT = "Cannot initialize Stack Allocator with 0 memory";
    const char * Error::BAD_STACK_ALLOCATOR_ALLOCATION = "Cannot allocate 0 bytes for Stack Allocator";
    const char * Error::BAD_STACK_ALLOCATOR_DEALLOCATION = "Cannot deallocate invalid memory using Stack Allocator";

    const char * Error::BAD_POOL_ALLOCATOR_INIT = "Cannot initialize a Pool Allocator with 0 memory.";
    const char * Error::BAD_POOL_ALLOCATOR_ALLOCATION = "Cannot allocate object into PoolAllocator. Size or alignment specified does not match the allocator's settings.";
    const char * Error::BAD_POOL_ALLOCATOR_DEALLOCATION = "Cannot deallocate object from PoolAllocator. Invalid memory.";

    const char * Error::INVALID_ALLOCATOR_TYPE = "Invalid allocator type given.";
    const char * Error::INVALID_ALLOCATION_SIZE = "Invalid allocation size.";
    const char * Error::INVALID_ALLOCATION_ALIGNMENT = "Invalid allocation alignment.";
    const char * Error::INVALID_DEALLOCATION_ADDRESS = "Invalid deallocation address. Cannot deallocate nullptr";
    const char * Error::INVALID_DEALLOCATION_TYPE = "Invalid deallocation type. Cannot deallocate Frame memory";
    const char * Error::INVALID_DEALLOCATION_GARBAGE_COLLECTION = "Invalid Deallocation Garbage Collection. Cannot deallocate memory marked for garbage collection.";
    const char * Error::INVALID_GARBAGE_COLLECTION = "Invalid Garbage Collection. Cannot collect a nullptr";
    const char * Error::OUT_OF_FRAME_MEMORY = "Out of Frame Memory";
    const char * Error::OUT_OF_STACK_MEMORY = "Out of Stack Memory";
    const char * Error::OUT_OF_POOL_MEMORY = "Out of Pool Memory";

	const char * Error::BAD_POINTER_COPY = "Bad pointer copy.";
}