#pragma once

#include <string>

#include "DiracMacros.h"
#include "IObserver.h"


namespace Dirac
{

template <typename E>
class ISubject
{
	private:

	IObserver<E>* mHead { nullptr };
	
	unsigned int mSubscribers	{ 0 };

	public:

	virtual ~ISubject(void)
	{
		mHead = nullptr;
	}

	void subscribe(IObserver<E>* tObserver)
	{
		// tObserver is the new head
	
		DIRAC_ASSERT(tObserver != nullptr, "Cannot subscribe nullptr!!");

		if (not mSubscribers)
		{
			mHead = tObserver;
		}
		else
		{
			tObserver -> mNext = mHead;
			mHead -> mPrevious = tObserver;

			mHead = tObserver;
		}
		tObserver -> set_mSubject(this);

		mSubscribers ++;
	}

	void unsubscribe(IObserver<E>* tObserver)
	{
		// doubly linked list removal
		
		DIRAC_ASSERT(tObserver != nullptr, "Cannot unsubscribe nullptr!!");
		DIRAC_ASSERT(mSubscribers != 0, "The subsciber list is already empty!!");

		if (mSubscribers == 1) { mHead = nullptr; }
		else
		{
			
			if (tObserver -> mNext != nullptr)
			{
				IObserver<E>* lNext = tObserver -> mNext;
				
				tObserver -> mNext = nullptr;
				lNext -> mPrevious = tObserver -> mPrevious;
			}

			if (tObserver -> mPrevious != nullptr)
			{
				IObserver<E>* lPrevious = tObserver -> mPrevious;

				tObserver -> mPrevious = nullptr;
				lPrevious -> mNext = tObserver -> mNext;
			}

		}
		mSubscribers --;
	}

	void notify(E tEnum, const std::string& tMessage)
	{
		// calls update on each IObserver

		IObserver<E>* lCurrent = mHead;

		while (lCurrent != nullptr)
		{
			
			lCurrent -> update(tEnum, tMessage);
			lCurrent = lCurrent -> mNext;
		}

	}

	GETTER(unsigned int, Subscribers);
};


};
