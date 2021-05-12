#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "DiracMacros.hpp"

namespace Dirac
{

namespace Math
{

namespace Sparse
{

constexpr float MIN_TOLL = .000001;


template <typename T>
bool near(T tValueA, T tValueB)
{
	float lDiff = static_cast<float>(tValueA - tValueB);

	return ((lDiff > 0.0f? lDiff: -lDiff) < MIN_TOLL);
}


template <typename T>
struct VectorEntry
{
	unsigned int 	mIndex;
	T		mValue;
};


template <typename T>
struct Entry
{
	unsigned int 	mRow;
	unsigned int 	mColumn;
	T 		mValue;
};


template <typename T>
bool lessThanVector(VectorEntry<T> tEntryA, VectorEntry<T> tEntryB)
{
	return (tEntryA.mIndex < tEntryB.mIndex);
}


template <typename T>
bool lessThanRows(Entry<T> tEntryA, Entry<T> tEntryB)
{
	return ((tEntryA.mRow < tEntryB.mRow) or
		(tEntryA.mRow == tEntryB.mRow and tEntryA.mColumn < tEntryB.mColumn));
}


template <typename T>
bool lessThanColumns(Entry<T> tEntryA, Entry<T> tEntryB)
{
	return ((tEntryA.mColumn < tEntryB.mColumn) or
		(tEntryA.mColumn == tEntryB.mColumn and tEntryA.mRow < tEntryB.mRow));
}


template <typename T>
struct CRS
{
	std::vector<T>			mValues;
	std::vector<unsigned int>	mColumnIndex;
	std::vector<unsigned int>	mFirstIndex;
};


template <typename T>
struct CCS
{
	std::vector<T>			mValues;
	std::vector<unsigned int>	mRowIndex;
	std::vector<unsigned int>	mFirstIndex;
};


template <typename T>
class SparseMatrix;


template <typename T>
class SparseVector
{
	private:

	std::vector<T>			mValues;
	std::vector<unsigned int>	mIndexes;
	std::vector<VectorEntry<T>>	mEntries;

	unsigned int			mLen;

	public:

	SparseVector(const std::vector<VectorEntry<T>>& tEntries, unsigned int tLen, bool tParse = false):
			mEntries(tEntries), mLen(tLen)
	{
		if (tParse)
		{
			for (int i = 0; i < mEntries.size(); i++)
			{	
				if (near<T>(mEntries[i].mValue, T(0)))
				{	
					mEntries.erase(mEntries.begin() + i);
				}
			}
			std::sort(mEntries.begin(), mEntries.end(), lessThanVector<T>);
			
		}
	}

	
	inline bool 			isEmpty(void) const 	{ return mEntries.empty(); }
	inline unsigned int 		getLength(void) const	{ return mLen; }
	inline std::vector<VectorEntry<T>> getEntries(void) const	{ return mEntries; }


	friend std::ostream& operator <<(std::ostream& os, SparseVector& tVec)
	{
		os << "\n\tLenght: " << tVec.mLen;
		os << "\n\t{Position, Value}";

		for (int i = 0; i < tVec.mEntries.size(); i++)
		{
			os << "\n\t" << "{" << tVec.mEntries[i].mIndex <<
			   	", " << tVec.mEntries[i].mValue << "}";
		}
		return os;
	}

};


template <typename T>
T dot(const SparseVector<T>& tVecA, const SparseVector<T>& tVecB)
{
	DIRAC_ASSERT(tVecA.getLength() == tVecB.getLength(), "Vector dimensions do not agree!!");

	if (tVecA.isEmpty() or tVecB.isEmpty())	{ return T(0); }

	T lResult = T(0);

	std::vector<VectorEntry<T>>	lEntriesA = tVecA.getEntries();
	std::vector<VectorEntry<T>>	lEntriesB = tVecB.getEntries();

	unsigned int iA = 0;
	unsigned int iB = 0;

	while (iA < lEntriesA.size() and iB <= lEntriesB.size())
	{
		if (lEntriesA[iA].mIndex > lEntriesB[iB].mIndex)		{ iB++; }
		else if (lEntriesA[iA].mIndex < lEntriesB[iB].mIndex)		{ iA++; }
		else if (lEntriesA[iA].mIndex == lEntriesB[iB].mIndex)
		{
			lResult += (lEntriesA[iA].mValue * (lEntriesB[iB].mValue));
			iA++;
			iB++;
		}
	}
	return lResult;
}


template <typename T>
SparseVector<T> multScalar(const SparseVector<T>& tVec, T tScalar)
{
	std::vector<VectorEntry<T>>	lEntries;

	for (auto lEntry: tVec.getEntries())
	{
		T lResult = lEntry.mValue * tScalar;

		if (not near<T>(lResult, T(0)))
		{
			lEntries.push_back({lEntry.mIndex, lResult});
		}

	}

	return {lEntries, tVec.getLength()};
}



template <typename T>
SparseVector<T> sum(const SparseVector<T>& tVecA, const SparseVector<T>& tVecB)
{
	DIRAC_ASSERT((tVecA.getLength() == tVecB.getLength()), "The two vector must have the same lenght!!");

	std::vector<VectorEntry<T>>	lEntriesA = tVecA.getEntries();
	std::vector<VectorEntry<T>>	lEntriesB = tVecB.getEntries();

	std::vector<VectorEntry<T>>	lEntries;

	unsigned int iA = 0;
	unsigned int iB = 0;
	while (iA < lEntriesA.size() and iB < lEntriesB.size())
	{
		if (lEntriesA[iA].mIndex < lEntriesB[iB].mIndex)
		{
			lEntries.push_back(lEntriesA[iA]);
			iA++;
		}
		else if (lEntriesA[iA].mIndex > lEntriesB[iB].mIndex)
		{
			lEntries.push_back(lEntriesB[iA]);
			iB++;
		}
		else
		{
			T lSum = lEntriesA[iA].mValue + lEntriesB[iB].mValue;

			if (not near<T>(lSum, T(0)))
			{
				lEntries.push_back({lEntriesA[iA].mIndex, lSum});
			}
			iA++;
			iB++;
		}

	}
	while (iA < lEntriesA.size())	{ lEntries.push_back(lEntriesA[iA++]); }
	while (iB < lEntriesB.size())	{ lEntries.push_back(lEntriesB[iB++]); }

	return {lEntries, tVecA.getLength()};
}




template <typename T>
class SparseMatrix
{
	private:

	CRS<T>	mCrs;
	CCS<T>	mCcs;
	
	unsigned int mRowsCount;
	unsigned int mColumnsCount;

	public:

	SparseMatrix(const CRS<T>& tCrs, const CCS<T>& tCcs,
		     unsigned int tRowsCount, unsigned int tColumnsCount):
		     	mCrs(tCrs), mCcs(tCcs),
			mRowsCount(tRowsCount),
			mColumnsCount(tColumnsCount)	{}

	
	SparseMatrix(const std::vector<Entry<T>>& tEntries,
		     unsigned int tRowsCount,
		     unsigned int tColumnsCount):
		     	mRowsCount(tRowsCount),
			mColumnsCount(tColumnsCount)
	{
		std::vector<Entry<T>> lRowOrder		= tEntries;
		std::vector<Entry<T>> lColumnOrder	= tEntries;

		std::sort(lRowOrder.begin(), lRowOrder.end(), lessThanRows<T>);
		std::sort(lColumnOrder.begin(), lColumnOrder.end(), lessThanColumns<T>);

		mCrs.mFirstIndex.push_back(0);
		for (int i = 0; i < lRowOrder.size(); i++)
		{
			mCrs.mValues.push_back(lRowOrder[i].mValue);
			mCrs.mColumnIndex.push_back(lRowOrder[i].mColumn);
			
			if (i != 0)
			{
				unsigned int lDiff = lRowOrder[i].mRow - lRowOrder[i - 1].mRow;
				for (int j = 0; j < lDiff; j++)
				{
					mCrs.mFirstIndex.push_back(mCrs.mValues.size() - 1);
				}
			}
		}
		mCrs.mFirstIndex.push_back(mCrs.mValues.size());



		mCcs.mFirstIndex.push_back(0);
		for (int i = 0; i < lRowOrder.size(); i++)
		{
			mCcs.mValues.push_back(lColumnOrder[i].mValue);
			mCcs.mRowIndex.push_back(lColumnOrder[i].mRow);
			
			if (i != 0)
			{
				unsigned int lDiff = lColumnOrder[i].mColumn - lColumnOrder[i-1].mColumn;
				for (int j = 0; j < lDiff; j++)
				{
					mCcs.mFirstIndex.push_back(mCcs.mValues.size() - 1);
				}
			}
		}
		mCcs.mFirstIndex.push_back(mCcs.mValues.size());

	}

	inline unsigned int getRowsCount(void) const { return mRowsCount; }
	inline unsigned int getColumnsCount(void) const { return mColumnsCount; }

	SparseMatrix<T> getTranspose(void)
	{

		CRS<T> newCrs {mCcs.mValues, mCcs.mRowIndex, mCcs.mFirstIndex};
		CCS<T> newCcs {mCrs.mValues, mCrs.mColumnIndex, mCrs.mFirstIndex};


		return SparseMatrix<T>(newCrs, newCcs, mColumnsCount, mRowsCount);
	}

	SparseVector<T> getRow(unsigned int tRow) const
	{
		DIRAC_ASSERT((tRow >= 0 and tRow < mRowsCount), "Row requested exceeds the matrix dimensions!!");

		unsigned int lStart 	= mCrs.mFirstIndex[tRow];
		unsigned int lSpan	= mCrs.mFirstIndex[tRow + 1] - lStart;

		std::vector<VectorEntry<T>>	lEntries;

		for (int i = 0; i < lSpan; i++)
		{
			lEntries.push_back({mCrs.mColumnIndex[lStart + i], mCrs.mValues[lStart + i]});
		}

		return SparseVector<T>(lEntries, mColumnsCount);
	}


	SparseVector<T> getColumn(unsigned int tColumn) const
	{
		DIRAC_ASSERT((tColumn >= 0 and tColumn < mColumnsCount), "Column requested exceeds the matrix dimensions!!");

		unsigned int lStart 	= mCcs.mFirstIndex[tColumn];
		unsigned int lSpan	= mCcs.mFirstIndex[tColumn + 1] - lStart;

		std::vector<VectorEntry<T>>			lEntries;

		for (int i = 0; i < lSpan; i++)
		{
			lEntries.push_back({mCcs.mRowIndex[lStart + i], mCcs.mValues[lStart + i]});
		}

		return SparseVector<T>(lEntries, mColumnsCount);
	}

	friend std::ostream& operator <<(std::ostream& os, SparseMatrix<T>& tMat)
	{
		os << "\n\tDimension: " << tMat.mRowsCount << " x " << tMat.mColumnsCount;
		os << "\n\t{Position, Value}";

		for (int i = 0; i < tMat.mCcs.mValues.size(); i++)
		{
			os << "\n\t" << "{(" << tMat.mCcs.mRowIndex[i] <<
				", " << tMat.mCrs.mColumnIndex[i] <<
			   	"), " << tMat.mCcs.mValues[i] << "}";
		}
		return os;
	}


};


template <typename T>
SparseVector<T> mult(const SparseMatrix<T>& tMat, const SparseVector<T>& tVec)
{
	DIRAC_ASSERT((tMat.getColumnsCount() == tVec.getLength()), "Matrix and vector dimensions do not agree!!");
		
	std::vector<VectorEntry<T>> lEntries;

	for (unsigned int i = 0; i < tMat.getRowsCount(); i++)
	{
		SparseVector<T> lVec = tMat.getRow(i);
		
		if (not lVec.isEmpty())
		{
			T lResult = dot(lVec, tVec);
			if (not near<T>(lResult, T(0)))
			{
				lEntries.push_back({i, lResult});
			}
		}

	}
	return {lEntries, tMat.getRowsCount()};

}


template <typename T>
SparseMatrix<T> mult(const SparseMatrix<T>& tMatA, const SparseMatrix<T>& tMatB)
{
	DIRAC_ASSERT((tMatA.getColumnsCount() == tMatB.getRowsCount()), "Matrix dimensions do not agree!!");
	
	std::vector<Entry<T>>	lEntries;
	
	for (unsigned int i = 0; i < tMatA.getRowsCount(); i++)
	{
		SparseVector<T> lLeft = tMatA.getRow(i);

		for (unsigned int j = 0; j < tMatB.getColumnsCount(); j++)
		{
			SparseVector<T> lRight = tMatB.getColumn(j);

			T lResult = dot(lLeft, lRight);

			if (not near<T>(lResult, T(0)))
			{	
				lEntries.push_back({i, j, lResult});
			}
		}
	}

	return SparseMatrix<T>(lEntries, tMatA.getRowsCount(), tMatB.getColumnsCount());

}


};


};


};
