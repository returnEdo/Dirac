#pragma once

#include <memory>
#include <array>

#include "ComponentPool.h"
#include "ECSConstants.h"


namespace Dirac
{


class ComponentManager
{

	private:
	
	// ptr to leverage polymorphism
	std::array<std::shared_ptr<IComponentPool>, ECSConstants::MAX_COMPONENTS>	mComponentPools;

	unsigned int mComponentCounter { 0 };

	template <typename ComponentType>
	std::shared_ptr<ComponentPool<ComponentType>> getComponentPool(void);

	public:

	template <typename ComponentType>
	unsigned int getComponentID(void);

	template <typename ComponentType>
	void addComponent(EntityID tID, ComponentType tComponent);

	template <typename ComponentType>
	void removeComponent(EntityID tID);

	template <typename ComponentType>
	ComponentType& getComponent(EntityID tID);

	template <typename ComponentType>
	void setComponent(EntityID tID, ComponentType& tComponent);

	void entityRemoved(EntityID id);

};

template <typename ComponentType>
std::shared_ptr<ComponentPool<ComponentType>> ComponentManager::getComponentPool(void)
{
	// given the ComponentType returns the associated pool

	return (std::static_pointer_cast<ComponentPool<ComponentType>>(mComponentPools[getComponentID<ComponentType>()]));
}



template <typename ComponentType>
unsigned int ComponentManager::getComponentID(void)
{	
	// the id is used as index in mComponentPools
	// assign an ID to the component if necessary
	
	static unsigned int sComponentID 	= mComponentCounter;
	static unsigned int sThisComponentCounter 	= 0;		// keep track of current type
	
	if (not sThisComponentCounter)
	{
		mComponentPools[sComponentID] = std::make_shared<ComponentPool<ComponentType>>();
		mComponentCounter ++;
	}

	sThisComponentCounter ++;

	return sComponentID;
}


template <typename ComponentType>
void ComponentManager::addComponent(EntityID tID, ComponentType tComponent)
{
	getComponentPool<ComponentType>() -> addComponent(tID, tComponent);
}


template <typename ComponentType>
void ComponentManager::removeComponent(EntityID tID)
{
	getComponentPool<ComponentType>() -> removeComponent(tID);
}


template <typename ComponentType>
ComponentType& ComponentManager::getComponent(EntityID tID)
{
	return getComponentPool<ComponentType>() -> getComponent(tID);
}


template <typename ComponentType>
void ComponentManager::setComponent(EntityID tID, ComponentType& tComponent)
{
	getComponentPool<ComponentType>() -> setComponent(tID, tComponent);
}




void ComponentManager::entityRemoved(EntityID tID)
{
	for (std::shared_ptr<IComponentPool> pComponentPool: mComponentPools)
	{
		if (pComponentPool != nullptr)
		{
			// check if Component is attached

			pComponentPool -> removeComponent(tID);
		}
	}

}


};
