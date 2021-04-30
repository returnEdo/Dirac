#pragma once

namespace Dirac
{

namespace Memory
{


template <typename T>
class Unique
{
	private:

	T* mPointer	{ nullptr };

	public:

	Unique(void):		mPointer(nullptr)	{}
	Unique(T* tPointer):	mPointer(tPointer)	{}
	Unique(Unique<T>& tUnique)
	{
		tUnique.moveTo(*this);
	}
	
	~Unique(void)
	{
		if (mPointer != nullptr)
		{
			destroy();
		}
	}

	void allocate(T* tPointer)
	{
		mPointer = tPointer;
	}

	void destroy()
	{
		delete mPointer;
	}

	void moveTo(Unique<T>& tUnique)
	{
		if (mPointer != nullptr)
		{		
			tUnique.mPointer 	= mPointer;
			mPointer		= nullptr;
		}
	}

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
