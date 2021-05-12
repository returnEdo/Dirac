#include "LinearGradientDescent.hpp"


namespace Dirac
{

namespace Math
{


void linearGradientDescent(const Sparse::SparseMatrix<float>& tA,
			   const Sparse::SparseVector<float>& tB,
			   Sparse::SparseVector<float>& tX,
			   float* tRes2)		// residual squared
{
	// A should be psd
	Sparse::SparseVector<float> lR = Sparse::sum(tB, Sparse::multScalar(Sparse::mult(tA, tX), -1.0f));
	
	*tRes2 = Sparse::dot(lR, lR);
	float lAlpha = *tRes2 / Sparse::dot(lR, Sparse::mult(tA, lR));
	
	tX = Sparse::sum(tX, Sparse::multScalar(lR, lAlpha));
}


void solve(const Sparse::SparseMatrix<float>& tA,
	   const Sparse::SparseVector<float>& tB,
	   Sparse::SparseVector<float>& tX,
	   unsigned int tMaxIter,
	   float tToll)
{
	float lToll2 		= tToll * tToll;
	float lRes2 		= 2.0f * lToll2;
	unsigned int lCounter 	= 0;

	while (lRes2 > lToll2 and lCounter < tMaxIter)
	{
		linearGradientDescent(tA, tB, tX, &lRes2);
		lCounter ++;
	}
	PRINT_AUTO(lCounter);
}

};

};
