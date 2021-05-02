#include "Clock.hpp"


namespace Dirac
{

namespace Physics
{


Clock::Clock(void):
	mStartUpTime(SteadyClock::now()),
	mTime(mStartUpTime)			{}


float Clock::refreshTimer(void)
{
	TimePoint lNow 	= SteadyClock::now();

	mDuration 	= lNow - mTime;
	mTime		= lNow;

	return mDuration.count();
}

float Clock::timeSinceStartUp(void)
{
	mDuration = SteadyClock::now() - mStartUpTime;
	
	return mDuration.count();
}


};

};
