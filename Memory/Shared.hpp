#pragma once



namespace Dirac
{

namespace Memory
{

template <typename T>
class Shared
{
	private:

	inline static unsigned int mCounter = 0;
	
	T* mPointer	{ nullptr };

	public:

	Shared(void):			mPointer(nullptr)		{}
	Shared(T* tPointer):		mPointer(tPointer)		{ mCounter++; }
	Shared(Shared<T>& tShared):	mPointer(tShared.mPointer)	{ mCounter++; }
	
	~Shared(void)
	{
		if (mPointer != nullptr)
		{
			if (mCounter == 1)
			{
				delete mPointer;
			}
			mCounter --;
		}
	}

	void sharedFrom(Shared<T> tShared)
	{
		if (tShared.mPointer != nullptr and mPointer == nullptr)
		{
			mPointer = tShared.mPointer;
			mCounter ++;
		}
	}

	inline unsigned int getReferenceCount(void) const	{ return mCounter; }

	T& operator *(void)
	{
		return *mPointer;
	}

	T* operator ->(void)
	{
		return mPointer;
	}

	bool isEmpty(void)
	{
		return (mPointer == nullptr);
	}

};

};


};
