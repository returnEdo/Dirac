#include "IObserver.h"

namespace Dirac
{

template <typename Enum>
IObserver<Enum>::~IObserver(void)
{
	if (mISubject != nullptr)
	{
		mISubject -> unsubscribe(*this);
	}
};


};
