#pragma once

#include <queue>


namespace Dirac
{

namespace Memory
{

template <typename T>
class MemoryPool
{
	private:

	uint8_t* 			mPool	{ nullptr };
	unsigned int			mTypeSize;
	unsigned int			mCount;
	std::queue<unsigned int>	mIndexes;

	public:

	MemoryPool(unsigned int tCount):
		mCount(tCount),
		mTypeSize(sizeof(T))
	{
		mPool = new uint8_t[tCount * mTypeSize];

		for (unsigned int i = 0; i < tCount; i++)
		{
			mIndexes.push(i);
		}
	}

	~MemoryPool(void)
	{
		delete [] mPool;
	}

	T* getMemory(void)
	{
		if (mIndexes.empty())
		{
			return nullptr;
		}

		unsigned int lIndex = mIndexes.front();
		mIndexes.pop();
		
		return ((T*)(mPool) + lIndex);	
	}

	bool freeMemory(T* mData)
	{
		unsigned int lIndex = ((uint8_t*)mData - mPool) / mTypeSize;	
		
		if (lIndex >= 0 and lIndex < mCount)
		{
			mIndexes.push(lIndex);

			return true;
		}

		return false;
	}

	unsigned int sizeAvailable(void)
	{
		return (mIndexes.size() * mTypeSize);
	}

};


};

};
