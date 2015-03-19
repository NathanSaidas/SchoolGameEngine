#ifndef MEMORY_TEST_H
#define MEMORY_TEST_H

namespace Engine
{
	class DataSample
	{

	};

#define DATA_CLASS(SIZE)                        \
    class Data ## SIZE ## : public DataSample   \
    {                                           \
        int data[SIZE/4];                       \
    public:                                     \
    }                                           \


    DATA_CLASS(4);
    DATA_CLASS(10);
    DATA_CLASS(16);
    DATA_CLASS(24);
    DATA_CLASS(32);
    DATA_CLASS(72);
    DATA_CLASS(96);
    DATA_CLASS(128);
    DATA_CLASS(192);
    DATA_CLASS(256);
    DATA_CLASS(384);
    DATA_CLASS(512);
    DATA_CLASS(1544);

	

	///Tests the allocate and deallocate operations of the MemoryManager and individual allocators (Pool/Frame/Stack)
	void ExecuteStabilityTest();

	///Tests memory leak detection. Purposly leaks memory to test.
	void ExecuteMemoryLeakTest();

	///Tests cases of invalid operations. 
	void ExecuteInvalidOperationTest();

	///Tests the performance of the memory manager vs the new and delete operators.
	void ExecutePerformanceTest();




}

#endif