#pragma once



namespace Dirac
{

namespace Math
{
	
float sign(float tValue);

template <typename T>
T sign(T tValue)
{
	return (T)((tValue > T(0)) - (tValue < T(0)));
}

};

};
