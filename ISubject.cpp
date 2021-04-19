#include "ISubject.h"

namespace Dirac
{

template <typename Enum>
ISubject<Enum>::~ISubject(void)
{
	for (IObserver<Enum>* observer: mIObservers)
	{	
		observer -> set_mISubject( nullptr );
	}
};


template <typename Enum>
void ISubject<Enum>::subscribe(IObserver<Enum>& tIObserver)
{	
	mIObservers.insert(&tIObserver);

	tIObserver -> set_mISubject(this);
}


template <typename Enum>
void ISubject<Enum>::unsubscribe(IObserver<Enum>& tIObserver)
{
	auto tPosition = mIObservers.find(&tIObserver);

	DIRAC_ASSERT(tPosition == mIObservers.end(),
		     "Cannot usubscribe an observer not subscribed!");	

	mIObservers.erase(tPosition);

}


template <typename Enum>
void ISubject<Enum>::notify(Enum tEnum, const std::string& tMessage)
{
	for (IObserver<Enum>* observer: mIObservers)
	{
		observer -> update(tEnum, tMessage);
	}
}


};
