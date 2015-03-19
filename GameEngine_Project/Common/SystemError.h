#ifndef GAME_ENGINE_ERROR_CONSTANTS_H
#define GAME_ENGINE_ERROR_CONSTANTS_H

#pragma region CHANGE LOG
/// -- January, 31, 2015 - Nathan Hanlan - Added SystemError class/file
#pragma endregion

#include <string>

namespace Engine
{
    ///Error contains all the string constants for errors.
    class Error
    {
    public:
        /// Frame Allocator Errors
        static const char * BAD_FRAME_ALLOCATOR_INIT;
        static const char * BAD_FRAME_ALLOCATOR_ALLOCATION;
        static const char * BAD_FRAME_ALLOCATOR_DEALLOCATION;

        /// Stack Allocator Errors
        static const char * BAD_STACK_ALLOCATOR_INIT;
        static const char * BAD_STACK_ALLOCATOR_ALLOCATION;
        static const char * BAD_STACK_ALLOCATOR_DEALLOCATION;

        /// Pool Allocator Errors
        static const char * BAD_POOL_ALLOCATOR_INIT;
        static const char * BAD_POOL_ALLOCATOR_ALLOCATION;
        static const char * BAD_POOL_ALLOCATOR_DEALLOCATION;

        ///Memory Manager
        static const char * INVALID_ALLOCATOR_TYPE;
        static const char * INVALID_ALLOCATION_SIZE;
        static const char * INVALID_ALLOCATION_ALIGNMENT;
        static const char * INVALID_DEALLOCATION_ADDRESS;
        static const char * INVALID_DEALLOCATION_TYPE;
        static const char * INVALID_DEALLOCATION_GARBAGE_COLLECTION;
        static const char * INVALID_GARBAGE_COLLECTION;
        static const char * OUT_OF_FRAME_MEMORY;
        static const char * OUT_OF_STACK_MEMORY;
        static const char * OUT_OF_POOL_MEMORY;

    };

}

#endif