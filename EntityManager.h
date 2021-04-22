#pragma once

#include <queue>
#include <array>


#include "ECSConstants.h"
#include "Entity.h"

/*

INFO: EntityManager


*/
namespace Dirac
{

class EntityManager
{

	private:

	std::queue<EntityID>					mPoolID;
	std::array<ComponentMask, ECSConstants::MAX_ENTITIES>	mComponentMasks;
	
	public:

	EntityManager(void);

	// entity life management
	EntityID createEntity(void);
	void removeEntity(EntityID tID);

	// getters
	inline unsigned int getEntitiesCount(void) const		{ return (ECSConstants::MAX_ENTITIES - mPoolID.size()); }
	inline ComponentMask getComponentMask(EntityID tID) const	{ return mComponentMasks[tID]; }

	// setters
	void setComponentMask(EntityID tID, const ComponentMask& tComponentMask);
};

};
