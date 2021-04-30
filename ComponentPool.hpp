#pragma once

#include <array>
#include <unordered_map>

#include "ECSConstants.hpp"
#include "Entity.hpp"
#include "DiracMacros.hpp"

/*
INFO:

The pool manages a compact array of type T

*/

namespace Dirac
{



// this interface is only needed to write an array of ComponentPool<Type>
class IComponentPool
{
	public:

	virtual ~IComponentPool(void) {}
	virtual void removeComponent(EntityID) = 0;
};




template <typename Type>
class ComponentPool: public IComponentPool
{

	private:

	std::array<Type, ECSConstants::MAX_ENTITIES>	mComponents;

	// maps ID <-> index inside mComponents
	std::unordered_map<EntityID, unsigned int>	mIDtoIndex;
	std::unordered_map<unsigned int, EntityID>	mIndexToID;

	// last position available in mComponents
	unsigned int mLastPosition { 0 };

	public:

	void addComponent(EntityID tID, Type tComponent)
	{

		if (mIDtoIndex.find(tID) == mIDtoIndex.end())
		{
			DIRAC_ASSERT(mLastPosition < ECSConstants::MAX_ENTITIES - 1,
				     "Cannot add component!!\n\tMax number of entities reached.");
		}
		
		mIDtoIndex[tID]	= mLastPosition;
		mIndexToID[mLastPosition] = tID;
		
		mComponents[mLastPosition] = tComponent;

		mLastPosition ++;
	}


	void removeComponent(EntityID tID)
	{
		// NOTE: component is not deleted from mComponents

		// trying to remove a component from an entity
		// which does not have that component does not
		// have any effect
		if (mIDtoIndex.find(tID) == mIDtoIndex.end() or mLastPosition == 0)
		{
			return;
		}

		unsigned int lRemovedPosition 	= mIDtoIndex[tID];
		unsigned int lLastPosition	= mLastPosition - 1;

		EntityID lLastID = mIndexToID[lLastPosition];

		// update array to keep it compact
		mComponents[lRemovedPosition] 	= mComponents[lLastPosition];

		// update new data in dictionaries
		mIDtoIndex[lLastID]		= lRemovedPosition;
		mIndexToID[lRemovedPosition]	= lLastID;

		// clean old data in dictionaries
		mIDtoIndex.erase(tID);
		mIndexToID.erase(lLastPosition);
		
		mLastPosition --;
	}


	Type& getComponent(EntityID tID)
	{
		// TODO: throw error instead

		DIRAC_ASSERT(mIDtoIndex.find(tID) != mIDtoIndex.end(),
			     "The Entity does not have the required component!!");

		return mComponents[mIDtoIndex[tID]];
	}	

	void setComponent(EntityID tID, Type& tComponent)
	{
		DIRAC_ASSERT(mIDtoIndex.find(tID) != mIDtoIndex.end(),
			     "Couldn't set component. Component is not attached to entity!!");
		
		mComponents[mIDtoIndex[tID]] = tComponent;

	}


	virtual void entityRemoved(EntityID tID)
	{
		// NOTE: called by the Manager when an Entity is removed 

		auto lIterator = mIDtoIndex.find(tID);

		if (lIterator == mIDtoIndex.end())
		{
			return;
		}
		
		removeComponent(mIDtoIndex[tID]);
	}

};



};

