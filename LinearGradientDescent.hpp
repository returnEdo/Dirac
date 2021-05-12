#pragma once

#include "SparseMatrix.hpp"


namespace Dirac
{

namespace Math
{


constexpr unsigned int LGD_MAX_ITER 	= 100;
constexpr float	LGD_TOLL		= 0.00001;


void linearGradientDescent(const Sparse::SparseMatrix<float>& tA,
			   const Sparse::SparseVector<float>& tB,
			   Sparse::SparseVector<float>& tX,
			   float* tRes2);

void solve(const Sparse::SparseMatrix<float>& tA,
	   const Sparse::SparseVector<float>& tB,
	   Sparse::SparseVector<float>& tX,
	   unsigned int tMaxIter = LGD_MAX_ITER,
	   float tToll = LGD_TOLL);
};

};
