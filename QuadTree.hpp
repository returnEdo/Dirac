#pragma once

#include <vector>

#include "vec2.hpp"
#include "Entity.hpp"
#include "Memory/Unique.hpp"
#include "Memory/MemoryPool.hpp"

namespace Dirac
{


namespace Physics
{


struct QuadNode
{
	QuadNode* 		mParent		{ nullptr };
	QuadNode* 		mQuadrantI	{ nullptr };
	QuadNode* 		mQuadrantII	{ nullptr };
	QuadNode* 		mQuadrantIII	{ nullptr };
	QuadNode* 		mQuadrantVI	{ nullptr };

	Math::vec2 		mPosition;
	Math::vec2 		mDimensions;

	std::vector<EntityID>	mEntities;

	unsigned int 		mDepth		{ 0 };
	bool 			mPartitioned	{ false };
};


using QuadPool = Memory::Unique<Memory::MemoryPool<QuadNode>>;


class QuadTree
{
	private:

	QuadNode*	mRoot	{ nullptr };
	QuadPool	mMemoryPool;
	
	public:

	QuadTree(const Math::vec2 tQuadPosition, const Math::vec2& tQuadDimensions);
	
	bool insert(EntityID tID, const Math::vec2& tBoxPosition, const Math::vec2& tBoxDimensions, QuadNode* tCurrentNode);
//	void insert(EntityID tID, const AABB& tBox);
//	void clear(void);
};



};


};
