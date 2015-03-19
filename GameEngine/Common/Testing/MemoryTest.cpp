#include "MemoryTest.h"

#include <random>
#include <functional>
#include <chrono>

#include <Windows.h>
#include "../Engine.h"


using namespace Engine;
using namespace Engine::Memory;


namespace Engine
{
	std::chrono::system_clock::time_point g_Start;
	std::chrono::system_clock::time_point g_End;
	Float64 g_DeltaTime = 0.0;


	void LogAddress(const char * aContent, void * aAddress)
	{
		IntPtr address = reinterpret_cast<IntPtr>(aAddress);
		printf("Address %s %u\n", aContent, address);
	}

	void LogAllocFail(UInt32 aSize)
	{
		printf("Failed to allocate memory of size %u", aSize);
	}
	void CheckAlloc(void * aAddress, UInt32 aSize)
	{
		if (aAddress == nullptr)
		{
			LogAllocFail(aSize);
		}
	}

	void LogDeltaTime(const char * aOperation)
	{
		printf("Operation (%s) took %.15f time to execute\n", aOperation, g_DeltaTime);
	}
	

	void StartTime()
	{
		g_Start = std::chrono::high_resolution_clock::now();
	}
	void StopTime()
	{
		g_End = std::chrono::high_resolution_clock::now();
		g_DeltaTime = ((std::chrono::duration<Float64>)(g_End - g_Start)).count();
	}

	void ExecuteStabilityTest()
	{
		//Test Pool Allocator Functions
		{
			printf("---- Testing Pool Allocator functionality ----\n\n");
			//Allocate sizes of 72. This should only be able to allocate 3 objects. The fourth will fail because it will be out of memory.
			PoolAllocator * poolAllocator = new PoolAllocator(256, 0, sizeof(Data72), __alignof(Data72));

			//Allocate first to last 
			void * poolA = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72));
			void * poolB = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72));
			void * poolC = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72));
			//void * poolD = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72)); // This would fail. Uncomment to see.
			//However this can also be proven by checking with the allocator in a safer manner.
			if (poolAllocator->CanAlloc(sizeof(Data72), __alignof(Data72)))
			{
				printf("Can allocate another object of size %u and alignment of %u\n", sizeof(Data72), __alignof(Data72));
			}
			else
			{
				printf("Cannot allocate another object of size %u and alignment of %u\n", sizeof(Data72), __alignof(Data72));
			}

			MemoryInfo info = poolAllocator->GetInfo();
			printf("Currently using %u/%u memory\n", info.memoryUsed, info.totalMemory);
			
			//Deallocate first to last.
			poolA = poolAllocator->Deallocate(poolA);
			poolB = poolAllocator->Deallocate(poolB);
			poolC = poolAllocator->Deallocate(poolC);
			//poolD = poolAllocator->Deallocate(poolD);

			

			//Allocate first to last
			poolA = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72));
			poolB = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72));
			poolC = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72));

			LogAddress("PoolA", poolA);
			LogAddress("PoolB", poolB);
			LogAddress("PoolC", poolC);

			printf("----Deallocate / Reallocate----\n");
			//Deallocate unordered
			poolB = poolAllocator->Deallocate(poolB);
			poolA = poolAllocator->Deallocate(poolA);


			//Reallocate
			poolB = poolAllocator->Allocate(sizeof(Data72), __alignof(Data72)); //This should have the same address poolA originally had.

			LogAddress("PoolA", poolA);
			LogAddress("PoolB", poolB);
			LogAddress("PoolC", poolC);

			//Finish Deallocating
			poolC = poolAllocator->Deallocate(poolC);
			poolB = poolAllocator->Deallocate(poolB);

			delete poolAllocator;

			printf("\n---- End Pool Allocator Test ----\n\n");
		}

		//Test Stack Allocator Functions
		{
			printf("---- Testing Stack Allocator functionality ----\n\n");
			StackAllocator * stackAllocator = new StackAllocator(256, 0);

			void * stackA = stackAllocator->Allocate(sizeof(Data72), __alignof(Data72));
			void * stackB = stackAllocator->Allocate(sizeof(Data32), __alignof(Data32));
			void * stackC = stackAllocator->Allocate(sizeof(Data32), __alignof(Data32));
			void * stackD = stackAllocator->Allocate(sizeof(Data72), __alignof(Data72));

			if (stackAllocator->CanAlloc(sizeof(Data72), __alignof(Data72)))
			{
				printf("Can allocate another object of size %u and alignment of %u\n", sizeof(Data72), __alignof(Data72));
			}
			else
			{
				printf("Cannot allocate another object of size %u and alignment of %u\n", sizeof(Data72), __alignof(Data72));
			}

			MemoryInfo info = stackAllocator->GetInfo();
			printf("Currently using %u/%u memory\n", info.memoryUsed, info.totalMemory);

			//Rollback and deallocate stackC
			stackC = stackAllocator->Rollback(stackC);
			//Deallocate B then A
			stackAllocator->FastDeallocate(stackB);
			stackAllocator->FastDeallocate(stackA);

			delete stackAllocator;
			printf("\n---- End Stack Allocator Test ----\n\n");
		}

		//Test Frame Allocator Functions
		{
			printf("---- Testing Frame Allocator functionality ----\n\n");

			FrameAllocator * frameAllocator = new FrameAllocator(256, 0);

			void * frameA = frameAllocator->Allocate(sizeof(Data72), __alignof(Data72));
			void * frameB = frameAllocator->Allocate(sizeof(Data32), __alignof(Data32));
			void * frameC = frameAllocator->Allocate(sizeof(Data32), __alignof(Data32));
			void * frameD = frameAllocator->Allocate(sizeof(Data72), __alignof(Data72));

			if (frameAllocator->CanAlloc(sizeof(Data72), __alignof(Data72)))
			{
				printf("Can allocate another object of size %u and alignment of %u\n", sizeof(Data72), __alignof(Data72));
			}
			else
			{
				printf("Cannot allocate another object of size %u and alignment of %u\n", sizeof(Data72), __alignof(Data72));
			}

			MemoryInfo info = frameAllocator->GetInfo();
			printf("Currently using %u/%u memory\n", info.memoryUsed, info.totalMemory);

			printf("Clear Memory\n");
			frameAllocator->Reset();

			info = frameAllocator->GetInfo();
			printf("Currently using %u/%u memory\n", info.memoryUsed, info.totalMemory);

			delete frameAllocator;

			printf("\n---- End Frame Allocator Test ----\n\n");
		}

		//Test Memory Manager Functions
		MemoryManager::Initialize();

		//Pool
		{
			printf("---- Testing Memory Manager Pool Allocator functionality ----\n\n");
			void * poolAllocs[10];
			poolAllocs[0] = MEM_POOL_ALLOC(sizeof(Data72), __alignof(Data72));
			poolAllocs[1] = MEM_POOL_ALLOC(sizeof(Data16), __alignof(Data16));
			poolAllocs[2] = MEM_POOL_ALLOC(sizeof(Data512), __alignof(Data512));
			poolAllocs[3] = MEM_POOL_ALLOC(sizeof(Data256), __alignof(Data256));
			poolAllocs[4] = MEM_POOL_ALLOC(sizeof(Data384), __alignof(Data384));
			poolAllocs[5] = MEM_POOL_ALLOC(sizeof(Data96), __alignof(Data96));
			poolAllocs[6] = MEM_POOL_ALLOC(sizeof(Data72), __alignof(Data72));
			poolAllocs[7] = MEM_POOL_ALLOC(sizeof(Data1544), __alignof(Data1544));
			poolAllocs[8] = MEM_POOL_ALLOC(sizeof(Data10), __alignof(Data10));
			poolAllocs[9] = MEM_POOL_ALLOC(sizeof(Data4), __alignof(Data4));


			CheckAlloc(poolAllocs[0], sizeof(Data72));
			CheckAlloc(poolAllocs[1], sizeof(Data16));
			CheckAlloc(poolAllocs[2], sizeof(Data512));
			CheckAlloc(poolAllocs[3], sizeof(Data256));
			CheckAlloc(poolAllocs[4], sizeof(Data384));
			CheckAlloc(poolAllocs[5], sizeof(Data96));
			CheckAlloc(poolAllocs[6], sizeof(Data72));
			CheckAlloc(poolAllocs[7], sizeof(Data1544));
			CheckAlloc(poolAllocs[8], sizeof(Data10));
			CheckAlloc(poolAllocs[9], sizeof(Data4));


			poolAllocs[0] = MEM_POOL_DEALLOC(poolAllocs[0], sizeof(Data72));
			poolAllocs[1] = MEM_POOL_DEALLOC(poolAllocs[1], sizeof(Data16));
			poolAllocs[2] = MEM_POOL_DEALLOC(poolAllocs[2], sizeof(Data512));
			poolAllocs[3] = MEM_POOL_DEALLOC(poolAllocs[3], sizeof(Data256));
			poolAllocs[4] = MEM_POOL_DEALLOC(poolAllocs[4], sizeof(Data384));
			poolAllocs[5] = MEM_POOL_DEALLOC(poolAllocs[5], sizeof(Data96));
			poolAllocs[6] = MEM_POOL_DEALLOC(poolAllocs[6], sizeof(Data72));
			poolAllocs[7] = MEM_POOL_DEALLOC(poolAllocs[7], sizeof(Data1544));
			poolAllocs[8] = MEM_POOL_DEALLOC(poolAllocs[8], sizeof(Data10));
			poolAllocs[9] = MEM_POOL_DEALLOC(poolAllocs[9], sizeof(Data4));

			printf("\n---- End Memory Manager Pool Allocator Test ----\n\n");
		}
		//Stack
		{
			printf("---- Testing Memory Manager Stack Allocator functionality ----\n\n");

			void * stackAllocs[5];
			stackAllocs[0] = MEM_STACK_ALLOC(sizeof(Data72), __alignof(Data72));
			stackAllocs[1] = MEM_STACK_ALLOC(sizeof(Data16), __alignof(Data16));
			stackAllocs[2] = MEM_STACK_ALLOC(sizeof(Data512), __alignof(Data512));
			stackAllocs[3] = MEM_STACK_ALLOC(sizeof(Data256), __alignof(Data256));
			stackAllocs[4] = MEM_STACK_ALLOC(sizeof(Data384), __alignof(Data384));

			CheckAlloc(stackAllocs[0], sizeof(Data72));
			CheckAlloc(stackAllocs[1], sizeof(Data16));
			CheckAlloc(stackAllocs[2], sizeof(Data512));
			CheckAlloc(stackAllocs[3], sizeof(Data256));
			CheckAlloc(stackAllocs[4], sizeof(Data384));

			stackAllocs[4] = MEM_STACK_DEALLOC(stackAllocs[4]);
			stackAllocs[3] = MEM_STACK_DEALLOC(stackAllocs[3]);
			stackAllocs[2] = MEM_STACK_DEALLOC(stackAllocs[2]);
			stackAllocs[1] = MEM_STACK_DEALLOC(stackAllocs[1]);
			stackAllocs[0] = MEM_STACK_DEALLOC(stackAllocs[0]);

			stackAllocs[0] = MEM_STACK_ALLOC(sizeof(Data72), __alignof(Data72));
			stackAllocs[1] = MEM_STACK_ALLOC(sizeof(Data16), __alignof(Data16));
			stackAllocs[2] = MEM_STACK_ALLOC(sizeof(Data512), __alignof(Data512));
			stackAllocs[3] = MEM_STACK_ALLOC(sizeof(Data256), __alignof(Data256));
			stackAllocs[4] = MEM_STACK_ALLOC(sizeof(Data384), __alignof(Data384));

			MemoryManager::GetInstance()->RollbackStack(stackAllocs[1]);
			stackAllocs[0] = MEM_STACK_DEALLOC(stackAllocs[0]);

			for (int i = 1; i < 5; i++)
			{
				stackAllocs[i] = nullptr;
			}

			printf("\n---- End Memory Manager Stack Allocator Test ----\n\n");
		}
		//Frame
		{
			printf("---- Testing Memory Manager Frame Allocator functionality ----\n\n");

			void * frameAllocs[5];

			frameAllocs[0] = MEM_FRAME_ALLOC(sizeof(Data72), __alignof(Data72));
			frameAllocs[1] = MEM_FRAME_ALLOC(sizeof(Data16), __alignof(Data16));
			frameAllocs[2] = MEM_FRAME_ALLOC(sizeof(Data512), __alignof(Data512));
			frameAllocs[3] = MEM_FRAME_ALLOC(sizeof(Data256), __alignof(Data256));
			frameAllocs[4] = MEM_FRAME_ALLOC(sizeof(Data384), __alignof(Data384));

			CheckAlloc(frameAllocs[0], sizeof(Data72));
			CheckAlloc(frameAllocs[1], sizeof(Data16));
			CheckAlloc(frameAllocs[2], sizeof(Data512));
			CheckAlloc(frameAllocs[3], sizeof(Data256));
			CheckAlloc(frameAllocs[4], sizeof(Data384));

			MemoryManager::GetInstance()->ResetFrame();

			printf("\n---- End Memory Manager Frame Allocator Test ----\n\n");
		}

		//Test Memory Leak Detection

		//Test Invalid Operations

		MemoryManager::Terminate();
		system("pause");
	}

	void ExecuteMemoryLeakTest()
	{
		printf("----Memory Leak Test----\n\n");
		MemoryManager::Initialize();

		MEM_POOL_ALLOC(sizeof(Data72), __alignof(Data72));
		MEM_STACK_ALLOC(sizeof(Data512), __alignof(Data256));
		MEM_POOL_ALLOC(sizeof(Data10), __alignof(Data10));

		MemoryManager::Terminate();
		printf("----Memory Leak Test End----\n\n");
	}

	void ExecuteInvalidOperationTest()
	{
		MemoryManager::Initialize();

		//Invalid Deallocation. Using an address from one allocator in another. This is not allowed but is difficult to detect.
		//Methods for detecting this kind of operation would involve storing a pointer to the allocator responsible for the allocation
		//in the memory header. However memory with no header or memory with a bad offset could possibly still make it by.
		//Another method for detecting this error is to store all allocated pointers and do a check to see if the memory being deallocated was infact allocated by the allocator.
		//This can have a huge negative impact on performance because of search time but would be great for catching memory corruption.
		//-------------------------------------------------------------------------------------------------------------------------------
		//If using the memory manager there is checks put in place to check ID information within the header, as well as flags and object sizes. (Object sizes must be of size 65535 or lower)
		//But even thats not 100% accurate.
		{
			PoolAllocator * poolAllocator72 = new PoolAllocator(256, 0, sizeof(Data72), __alignof(Data72));
			PoolAllocator * poolAllocator10 = new PoolAllocator(256, 0, sizeof(Data10), __alignof(Data10));

			void * poolA = poolAllocator72->Allocate(sizeof(Data72), __alignof(Data72));
			void * poolB = poolAllocator10->Allocate(sizeof(Data10), __alignof(Data10));

			poolAllocator72->Deallocate(poolB);
			poolAllocator72->Deallocate(poolA);
			poolAllocator72->Deallocate(poolA);

			delete poolAllocator72;
			delete poolAllocator10;
		}


		//Invalid Stack Deallocation Order. The stack must be deallocated in reverse order it was allocated in.
		//This is an example of how such error would occur.
		{
			void * stackA = MEM_STACK_ALLOC(sizeof(Data72), __alignof(Data72));
			void * stackB = MEM_STACK_ALLOC(sizeof(Data16), __alignof(Data72));

			MEM_STACK_DEALLOC(stackA);
		}

		//Invalid Frame Deallocation. Memory allocated using the frame allocator is not allowed to be deallocated.
		//Use the Reset or ResetFrame method from the allocator/memory manager to reset all of the memory.
		{
			void * frameA = MEM_FRAME_ALLOC(sizeof(Data72), __alignof(Data72));

			MEM_FRAME_DEALLOC(frameA);
		}

		//Invalid Allocation Size. Cannot allocate memory that has a size of 0 bytes.
		{
			void * zeroMemoryAlloc = MEM_POOL_ALLOC(0, 4);
			zeroMemoryAlloc = MEM_STACK_ALLOC(0, 4);
			zeroMemoryAlloc = MEM_FRAME_ALLOC(0, 4);
		}

		//Invalid Pool Allocation Size. Cannot allocate memory that is larger than 2048 bytes for a pool allocator from the Memory Manager.
		//Note: Its possible to create an instance of a PoolAllocator that allocates in sizes of 5000.
		//The sizes supported by the Memory Manager is listed in the MemoryConfig.h file.
		{
			void * largePoolAlloc = MEM_POOL_ALLOC(5000, 4);
		}

		//Invalid Stack / Pool Deallocation. Cannot deallocate a nullptr.
		{
			MEM_POOL_DEALLOC(nullptr, 16);
			MEM_STACK_DEALLOC(nullptr);
		}

		MemoryManager::Terminate();
	}

	//The main goal of the performance test is to show how efficient the custom allocators are compared to new and delete
	void TestStack();
	void TestFrame();
	void TestPool();

	void TestMemoryManagerStack();
	void TestMemoryManagerFrame();

	void ExecutePerformanceTest()
	{
		printf("Performance Test Started");
		printf("=== Testing Raw Allocators ===\n");
		TestStack();
		TestFrame();
		TestPool();

		printf("=== Testing Memory Manager ===\n");

		MemoryManager::Initialize();
		TestMemoryManagerStack();
		TestMemoryManagerFrame();
		MemoryManager::Terminate();

		printf("Performance Test Complete");
	}

	void TestStack()
	{
		UInt32 maxAllocs = 262144;
		UInt32 minAllocSize = 4;
		UInt32 maxAllocSize = 2048;

		//Generate Random Numbers
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		auto generator = std::bind(std::uniform_int_distribution<UInt32>(minAllocSize, maxAllocSize), std::mt19937(seed));
		UInt32 * randomNumbers = new UInt32[maxAllocs];
		UInt32 memorySum = 0;
		printf("Generating Random Numbers...\n");
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			randomNumbers[i] = generator();
			memorySum += randomNumbers[i];
		}
		printf("Generated Random Numbers.\nAllocating memory: %u\n", memorySum);

		void ** addresses = new void*[maxAllocs];

		StackAllocator * stackAllocator = new StackAllocator(Config::MEGA_BYTE * 512, 0);
		
		printf("==Stack Allocate/Deallocate Begin==\n");

		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = stackAllocator->Allocate(randomNumbers[i], 4);
		}
		StopTime();
		LogDeltaTime("Stack Allocation");

		StartTime();
		for (SInt32 i = maxAllocs - 1; i >= 0; i--)
		{
			addresses[i] = stackAllocator->Deallocate(addresses[i]);
		}
		StopTime();
		LogDeltaTime("Stack Deallocation");

		printf("==Stack Allocate/Deallocate Finish==\n");

		delete stackAllocator;

		printf("==Malloc/Free Allocate/Deallocate Begin==\n");
		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = malloc(randomNumbers[i]);
		}
		StopTime();
		LogDeltaTime("Malloc");


		StartTime();
		for (SInt32 i = maxAllocs - 1; i >= 0; i--)
		{
			free(addresses[i]);
			addresses[i] = nullptr;
		}
		StopTime();
		LogDeltaTime("Free");

		printf("==Malloc/Free Allocate/Deallocate Finish==\n");

		delete[] addresses;
		delete[] randomNumbers;

		system("pause");
	}
	
	void TestFrame()
	{
		UInt32 maxAllocs = 262144;
		UInt32 minAllocSize = 4;
		UInt32 maxAllocSize = 2048;

		//Generate Random Numbers
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		auto generator = std::bind(std::uniform_int_distribution<UInt32>(minAllocSize, maxAllocSize), std::mt19937(seed));
		UInt32 * randomNumbers = new UInt32[maxAllocs];
		UInt32 memorySum = 0;
		printf("Generating Random Numbers...\n");
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			randomNumbers[i] = generator();
			memorySum += randomNumbers[i];
		}
		printf("Generated Random Numbers.\nAllocating memory: %u\n", memorySum);

		void ** addresses = new void*[maxAllocs];

		FrameAllocator * frameAllocator = new FrameAllocator(Config::MEGA_BYTE * 512, 0);

		printf("==Frame Allocate/Deallocate Begin==\n");

		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = frameAllocator->Allocate(randomNumbers[i], 4);
		}
		StopTime();
		LogDeltaTime("Frame Allocation");

		StartTime();
		frameAllocator->Reset();
		StopTime();
		LogDeltaTime("Frame Deallocation");

		printf("==Frame Allocate/Deallocate Finish==\n");

		delete frameAllocator;

		printf("==Malloc/Free Allocate/Deallocate Begin==\n");
		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = malloc(randomNumbers[i]);
		}
		StopTime();
		LogDeltaTime("Malloc");


		StartTime();
		for (SInt32 i = maxAllocs - 1; i >= 0; i--)
		{
			free(addresses[i]);
			addresses[i] = nullptr;
		}
		StopTime();
		LogDeltaTime("Free");

		printf("==Malloc/Free Allocate/Deallocate Finish==\n");

		delete[] addresses;
		delete[] randomNumbers;
		

		system("pause");
	}

	void TestPool()
	{
		UInt32 maxAllocs = 262144;
		UInt32 allocSize = 16;
		void ** addresses = new void*[maxAllocs];

		PoolAllocator * poolAllocator = new PoolAllocator(maxAllocs * (allocSize + sizeof(MemoryHeader)), 0, allocSize, 4);
		printf("==Pool Allocate/Deallocate Begin==\n");
		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = poolAllocator->Allocate(allocSize, 4);
		}
		StopTime();
		LogDeltaTime("Pool Allocate");


		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = poolAllocator->Deallocate(addresses[i]);
		}
		StopTime();
		LogDeltaTime("Pool Deallocate");
		printf("==Pool Allocate/Deallocate Finish==\n");

		delete poolAllocator;

		printf("==Malloc/Free Allocate/Deallocate Begin==\n");
		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = malloc(allocSize);
		}
		StopTime();
		LogDeltaTime("Malloc");

		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			free(addresses[i]);
			addresses[i] = nullptr;
		}
		StopTime();
		LogDeltaTime("Free");
		printf("==Malloc/Free Allocate/Deallocate Finish==\n");

		delete addresses;

		system("pause");
	}

	void TestMemoryManagerStack()
	{
		UInt32 maxAllocs = 262144;
		UInt32 minAllocSize = 4;
		UInt32 maxAllocSize = 2048;

		//Generate Random Numbers
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		auto generator = std::bind(std::uniform_int_distribution<UInt32>(minAllocSize, maxAllocSize), std::mt19937(seed));
		UInt32 * randomNumbers = new UInt32[maxAllocs];
		UInt32 memorySum = 0;
		printf("Generating Random Numbers...\n");
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			randomNumbers[i] = generator();
			memorySum += randomNumbers[i];
		}
		printf("Generated Random Numbers.\nAllocating memory: %u\n", memorySum);

		void ** addresses = new void*[maxAllocs];



		printf("==Stack Allocate/Deallocate Begin==\n");

		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = MEM_STACK_ALLOC(randomNumbers[i], 4);
		}
		StopTime();
		LogDeltaTime("Stack Allocation");

		StartTime();
		for (SInt32 i = maxAllocs - 1; i >= 0; i--)
		{
			addresses[i] = MEM_STACK_DEALLOC(addresses[i]);
		}
		StopTime();
		LogDeltaTime("Stack Deallocation");

		printf("==Stack Allocate/Deallocate Finish==\n");

		printf("==Malloc/Free Allocate/Deallocate Begin==\n");
		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = malloc(randomNumbers[i]);
		}
		StopTime();
		LogDeltaTime("Malloc");


		StartTime();
		for (SInt32 i = maxAllocs - 1; i >= 0; i--)
		{
			free(addresses[i]);
			addresses[i] = nullptr;
		}
		StopTime();
		LogDeltaTime("Free");

		printf("==Malloc/Free Allocate/Deallocate Finish==\n");

		delete[] addresses;
		delete[] randomNumbers;

		system("pause");
	}

	void TestMemoryManagerFrame()
	{
		UInt32 maxAllocs = 262144;
		UInt32 minAllocSize = 4;
		UInt32 maxAllocSize = 2048;

		//Generate Random Numbers
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		auto generator = std::bind(std::uniform_int_distribution<UInt32>(minAllocSize, maxAllocSize), std::mt19937(seed));
		UInt32 * randomNumbers = new UInt32[maxAllocs];
		UInt32 memorySum = 0;
		printf("Generating Random Numbers...\n");
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			randomNumbers[i] = generator();
			memorySum += randomNumbers[i];
		}
		printf("Generated Random Numbers.\nAllocating memory: %u\n", memorySum);

		void ** addresses = new void*[maxAllocs];

		printf("==Frame Allocate/Deallocate Begin==\n");

		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = MEM_FRAME_ALLOC(randomNumbers[i], 4);
		}
		StopTime();
		LogDeltaTime("Frame Allocation");

		StartTime();
		MemoryManager::GetInstance()->ResetFrame();
		StopTime();
		LogDeltaTime("Frame Deallocation");

		printf("==Frame Allocate/Deallocate Finish==\n");


		printf("==Malloc/Free Allocate/Deallocate Begin==\n");
		StartTime();
		for (UInt32 i = 0; i < maxAllocs; i++)
		{
			addresses[i] = malloc(randomNumbers[i]);
		}
		StopTime();
		LogDeltaTime("Malloc");


		StartTime();
		for (SInt32 i = maxAllocs - 1; i >= 0; i--)
		{
			free(addresses[i]);
			addresses[i] = nullptr;
		}
		StopTime();
		LogDeltaTime("Free");

		printf("==Malloc/Free Allocate/Deallocate Finish==\n");

		delete[] addresses;
		delete[] randomNumbers;


		system("pause");
	}
}



