#pragma once

#include <vector>

#include "vec2.hpp"
#include "Entity.hpp"
#include "System.hpp"
#include "Memory/Unique.hpp"
#include "Memory/MemoryPool.hpp"
#include "DiracConstants.hpp"

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
	QuadNode* 		mQuadrantIV	{ nullptr };

	Math::vec2 		mPosition;
	Math::vec2 		mDimensions;

	std::vector<EntityID>	mEntities;

	unsigned int 		mDepth		{ 1 };
	bool 			mPartitioned	{ false };

	QuadNode(QuadNode* tParent, Math::vec2 tPosition, Math::vec2 tDimension, unsigned int tDepth):
			mParent(tParent),
			mQuadrantI(nullptr),
			mQuadrantII(nullptr),
			mQuadrantIII(nullptr),
			mQuadrantIV(nullptr),
			mPosition(tPosition),
			mDimensions(tDimension),
			mDepth(tDepth),
			mPartitioned(false) 	{ if (not mEntities.empty()) { mEntities.clear(); } }
};


using QuadPool = Memory::Unique<Memory::MemoryPool<QuadNode>>;


/*
SIGNATURE:
- Transform
- Physics::AABB
*/


class QuadTree: public ISystem
{
	private:

	QuadNode*	mRoot	{ nullptr };
	QuadPool	mMemoryPool;

	void clear(QuadNode* tCurrentNode);
	void clearRoot(void);
	
	public:

	void init(const Math::vec2 tQuadPosition = Math::vec2(),
		  const Math::vec2& tQuadDimensions = Math::vec2(Constants::DELTAX, Constants::DELTAX / Constants::ASPECT_RATIO));
	void update(void);
	
	bool insert(EntityID tID, const Math::vec2& tBoxPosition, const Math::vec2& tBoxDimensions, QuadNode* tCurrentNode);
};



};


};
