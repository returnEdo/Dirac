#include "QuadTree.hpp"

#include "MathUtils.hpp"
#include "Manager.hpp"
#include "RenderingComponents.hpp"
#include "PhysicsComponents.hpp"

#include <cmath>


extern Dirac::Manager gManager;


namespace Dirac
{

namespace Physics
{

constexpr unsigned int MAX_QUAD_TREE_DEPTH 	= 3;
constexpr unsigned int MAX_ENTITIES_PER_QUAD	= 4;



void QuadTree::init(const Math::vec2 tQuadPosition, const Math::vec2& tQuadDimensions)
{

	unsigned int lQuadNumber = 0;
	for (int i = 1; i <= MAX_QUAD_TREE_DEPTH; i++)
	{
		lQuadNumber += pow(4, i);
	}
	
	mMemoryPool.allocate(lQuadNumber);

	mRoot = mMemoryPool -> getMemory(nullptr, tQuadPosition, tQuadDimensions, 1);

	mRoot -> mPosition 	= tQuadPosition;
	mRoot -> mDimensions 	= tQuadDimensions;

}


bool QuadTree::insert(EntityID tID, const Math::vec2& tBoxPosition, const Math::vec2& tBoxDimensions, QuadNode* tCurrentNode)
{
	bool lIntersect = Math::areRectanglesIntersecting(tCurrentNode -> mPosition, tCurrentNode -> mDimensions,
							  tBoxPosition, tBoxDimensions);
	
	if (not lIntersect)
	{
		return false;
	}
	
	PRINT_AUTO((tCurrentNode -> mEntities).size());
	if (((tCurrentNode -> mEntities).size() < MAX_ENTITIES_PER_QUAD and not (tCurrentNode -> mPartitioned)) or
	     (tCurrentNode -> mDepth) == MAX_QUAD_TREE_DEPTH)
	{
		(tCurrentNode -> mEntities).push_back(tID);
		return true;
	}
	
	if (not (tCurrentNode -> mPartitioned))
	{
		Math::vec2 lPosition 		= tCurrentNode -> mPosition;
		Math::vec2 lDimension		= (tCurrentNode -> mDimensions) / 4.0f;
		Math::vec2 lNewDimensions	= tBoxDimensions / 2.0f;

		tCurrentNode -> mPartitioned = true;
		tCurrentNode -> mQuadrantI 	= mMemoryPool -> getMemory(tCurrentNode, 
									   Math::vec2(lPosition.x + lDimension.x, lPosition.y + lDimension.y),
									   lNewDimensions,
									   (tCurrentNode -> mDepth) + 1);
		tCurrentNode -> mQuadrantII 	= mMemoryPool -> getMemory(tCurrentNode, 
									   Math::vec2(lPosition.x - lDimension.x, lPosition.y + lDimension.y),
									   lNewDimensions,
									   (tCurrentNode -> mDepth) + 1);
		tCurrentNode -> mQuadrantIII 	= mMemoryPool -> getMemory(tCurrentNode, 
									   Math::vec2(lPosition.x - lDimension.x, lPosition.y - lDimension.y),
									   lNewDimensions,
									   (tCurrentNode -> mDepth) + 1);
		tCurrentNode -> mQuadrantIV 	= mMemoryPool -> getMemory(tCurrentNode, 
									   Math::vec2(lPosition.x + lDimension.x, lPosition.y - lDimension.y),
									   lNewDimensions,
									   (tCurrentNode -> mDepth) + 1);
		for (EntityID entity: tCurrentNode -> mEntities)
		{
			Transform lTransform 	= gManager.getComponent<Transform>(entity);
			Physics::AABB lBox	= gManager.getComponent<Physics::AABB>(entity);

			lPosition.x = lTransform.mPosition.x;
			lPosition.y = lTransform.mPosition.y;

			insert(entity, lPosition, lBox.mDimensions, tCurrentNode -> mQuadrantI);
			insert(entity, lPosition, lBox.mDimensions, tCurrentNode -> mQuadrantII);
			insert(entity, lPosition, lBox.mDimensions, tCurrentNode -> mQuadrantIII);
			insert(entity, lPosition, lBox.mDimensions, tCurrentNode -> mQuadrantIV);
		}
		(tCurrentNode -> mEntities).clear();

	}

	insert(tID, tBoxPosition, tBoxDimensions, tCurrentNode -> mQuadrantI);
	insert(tID, tBoxPosition, tBoxDimensions, tCurrentNode -> mQuadrantII);
	insert(tID, tBoxPosition, tBoxDimensions, tCurrentNode -> mQuadrantIII);
	insert(tID, tBoxPosition, tBoxDimensions, tCurrentNode -> mQuadrantIV);

	return true;
}


void QuadTree::clear(QuadNode* tCurrentNode)
{
	if (tCurrentNode -> mPartitioned)
	{
		clear(tCurrentNode -> mQuadrantI);
		clear(tCurrentNode -> mQuadrantII);
		clear(tCurrentNode -> mQuadrantIII);
		clear(tCurrentNode -> mQuadrantIV);
	}

	mMemoryPool -> freeMemory(tCurrentNode);
}

void QuadTree::clearRoot(void)
{
	mRoot  -> mQuadrantI 	= nullptr;
	mRoot  -> mQuadrantII 	= nullptr;
	mRoot  -> mQuadrantIII 	= nullptr;
	mRoot  -> mQuadrantIV 	= nullptr;
	
	(mRoot -> mEntities).clear();

	mRoot -> mPartitioned 	= false;
}


void QuadTree::update(void)
{
	if (mRoot -> mPartitioned)
	{
		clear(mRoot -> mQuadrantI);
		clear(mRoot -> mQuadrantII);
		clear(mRoot -> mQuadrantIII);
		clear(mRoot -> mQuadrantIV);
	}
	clearRoot();

	for (EntityID entity: mEntities)
	{
		Transform lTransform 	= gManager.getComponent<Transform>(entity);
		Physics::AABB lBox 	= gManager.getComponent<Physics::AABB>(entity);
		
		Math::vec2 lPosition { lTransform.mPosition.x, lTransform.mPosition.y };

		insert(entity, lPosition, lBox.mDimensions, mRoot);
	}

}


};

};
