#pragma once

#include <string>


namespace Dirac
{

template <typename E>
class ISubject;


template <typename E>
class IObserver
{
	private:

	IObserver<E>* mPrevious	{ nullptr };
	IObserver<E>* mNext	{ nullptr };

	ISubject<E>* mISubject	{ nullptr };

	void set_mSubject(ISubject<E>* tISubject)	{ mISubject = tISubject; }

	friend class ISubject<E>;

	public:

	virtual ~IObserver(void)
	{
		// removes this observer from subscriber list

		if (mISubject != nullptr)
		{
			mISubject -> unsubscribe(this);
		}

		mISubject = nullptr;
	}



	virtual void update(E tEnum, const std::string& tMessage) = 0;



};


};
