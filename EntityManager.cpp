#include "EntityManager.h"

#include "DiracMacros.h"


namespace Dirac
{

EntityManager::EntityManager(void)
{
	// fills the queue
	for (EntityID i = 0; i < ECSConstants::MAX_ENTITIES; i++)
	{
		mPoolID.push(i);
	}

}


EntityID EntityManager::createEntity(void)
{

	DIRAC_ASSERT(mPoolID.size() != 0, "Maximum number of entites reached!!");

	// polls the front of the ID pool
	EntityID rID = mPoolID.front();

	mPoolID.pop();

	return rID;
}


void EntityManager::removeEntity(EntityID tID)
{
	DIRAC_ASSERT(mPoolID.size() != ECSConstants::MAX_ENTITIES, "Cannot remove an entity if it does not exist!!");
	
	// the ID is newly pollable
	mPoolID.push(tID);

	// the components are resetted
	mComponentMasks[tID].reset();
}


void EntityManager::setComponentMask(EntityID tID, const ComponentMask& tComponentMask)
{
	// no checks are made

	mComponentMasks[tID] = tComponentMask;

}


};
