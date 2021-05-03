#include "QuadTree.hpp"

#include "MathUtils.hpp"

#include <cmath>


namespace Dirac
{

namespace Physics
{

constexpr unsigned int MAX_QUAD_TREE_DEPTH 	= 4;
constexpr unsigned int MAX_ENTITIES_PER_QUAD	= 4;

QuadTree::QuadTree(const Math::vec2 tQuadPosition, const Math::vec2& tQuadDimensions)
{

	mRoot -> mPosition 	= tQuadPosition;
	mRoot -> mDimensions 	= tQuadDimensions;

	unsigned int lQuadNumber = 0;
	for (int i = 1; i <= MAX_QUAD_TREE_DEPTH; i++)
	{
		lQuadNumber += pow(4, i);
	}
	
	mMemoryPool.allocate(new Memory::MemoryPool<QuadNode>(lQuadNumber));
}


bool QuadTree::insert(EntityID tID, const Math::vec2& tBoxPosition, const Math::vec2& tBoxDimensions, QuadNode* tCurrentNode)
{
	bool lIntersect = Math::areRectanglesIntersecting(tCurrentNode -> mPosition, tCurrentNode -> mDimensions,
							  tBoxPosition, tBoxDimensions);
	
	if (not lIntersect)
	{
		return false;
	}
	
	if ((tCurrentNode -> mEntities).size() < MAX_ENTITIES_PER_QUAD)
	{
		(tCurrentNode -> mEntities).push_back(tID);
		return true;
	}
	
	if (not (tCurrentNode -> mPartitioned))
	{
		tCurrentNode -> mPartitioned = true;
		tCurrentNode -> mQuadrantI 	= mMemoryPool.getMemory();
		tCurrentNode -> mQuadrantII 	= mMemoryPool.getMemory();
		tCurrentNode -> mQuadrantIII 	= mMemoryPool.getMemory();
		tCurrentNode -> mQuadrantVI 	= mMemoryPool.getMemory();
		//TODO: variadic arguments here
	}

	return true;
}


};

};
