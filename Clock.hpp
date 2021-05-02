#pragma once

#include <chrono>



namespace Dirac
{

namespace Physics
{

using SteadyClock 	= std::chrono::steady_clock;
using TimePoint 	= std::chrono::time_point<SteadyClock>;

class Clock
{
	private:

	TimePoint			mTime;
	TimePoint			mStartUpTime;
	std::chrono::duration<float>	mDuration;

	public:

	Clock(void);

	float refreshTimer(void);
	float timeSinceStartUp(void);
};


};

};
