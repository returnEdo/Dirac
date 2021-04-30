#pragma once

#include <memory>

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "Entity.hpp"
#include "System.hpp"



namespace Dirac
{



class Manager
{
	private:

	std::unique_ptr<EntityManager>		mEntityManager;
	std::unique_ptr<ComponentManager>	mComponentManager;
	std::unique_ptr<SystemManager>		mSystemManager;

	public:

	void init(void)
	{
		mEntityManager 		= std::make_unique<EntityManager>();
		mComponentManager 	= std::make_unique<ComponentManager>();
		mSystemManager 		= std::make_unique<SystemManager>();
	}


	EntityID createEntity(void)
	{
		return (mEntityManager -> createEntity());
	}


	void removeEntity(EntityID tID)
	{
		// tID is newly available
		mEntityManager -> removeEntity(tID);
		
		// tID is no longer in the componentPools
		mComponentManager -> entityRemoved(tID);
		
		// tID is removed from system entity lists
		mSystemManager -> entityRemoved(tID);
	}	


	template <typename ComponentType>
	void addComponent(EntityID tID, ComponentType tComponent)
	{
		// find component id
		unsigned int lComponentID = mComponentManager -> getComponentID<ComponentType>();	
		
		// update Entity component mask
		ComponentMask lComponentMask = mEntityManager -> getComponentMask(tID);

		lComponentMask.set(lComponentID, true);
		mEntityManager -> setComponentMask(tID, lComponentMask);

		// store new component
		mComponentManager -> addComponent<ComponentType>(tID, tComponent);

		// update system entity lists
		mSystemManager -> onComponentMaskUpdate(tID, lComponentMask);
	}


	template <typename ComponentType>
	void removeComponent(EntityID tID)
	{
		// find component id
		unsigned int lComponentID = mComponentManager -> getComponentID<ComponentType>();	
		
		// update Entity component mask
		ComponentMask lComponentMask = mEntityManager -> getComponentMask(tID);

		lComponentMask.set(lComponentID, false);

		mEntityManager -> setComponentMask(tID, lComponentMask);

		// store new component
		mComponentManager -> removeComponent<ComponentType>(tID);

		// update system entity lists
		mSystemManager -> onComponentMaskUpdate(tID, lComponentMask);
	}


	template <typename ComponentType>
	ComponentType& getComponent(EntityID tID)
	{
		return (mComponentManager -> getComponent<ComponentType>(tID));
	}


	template <typename ComponentType>
	unsigned int getComponentID(void)
	{

		return (mComponentManager -> getComponentID<ComponentType>());
	}


	template <typename ComponentType>
	void setComponent(EntityID tID, ComponentType& tComponent)
	{
		mComponentManager -> setComponent<ComponentType>(tID, tComponent);
	}


	template <typename SystemType>
	void setSignature(Signature& tSignature)
	{	
		mSystemManager -> setSignature<SystemType>(tSignature);
	}


	template <typename SystemType>
	std::shared_ptr<SystemType> getSystem(void)
	{
		return (mSystemManager -> getSystem<SystemType>());
	}
};
//	void Manager::init(void)
//	{
//		mEntityManager 		= std::make_unique<EntityManager>();
//		mComponentManager 	= std::make_unique<ComponentManager>();
//		mSystemManager 		= std::make_unique<SystemManager>();
//	}
//
//
//	EntityID Manager::createEntity(void)
//	{
//		return (mEntityManager -> createEntity());
//	}
//
//
//	void Manager::removeEntity(EntityID tID)
//	{
//		// tID is newly available
//		mEntityManager -> removeEntity(tID);
//		
//		// tID is no longer in the componentPools
//		mComponentManager -> entityRemoved(tID);
//		
//		// tID is removed from system entity lists
//		mSystemManager -> entityRemoved(tID);
//	}	
//
//
//	template <typename ComponentType>
//	void Manager::addComponent(EntityID tID, ComponentType tComponent)
//	{
//		// find component id
//		unsigned int lComponentID = mComponentManager -> getComponentID<ComponentType>();	
//		
//		// update Entity component mask
//		ComponentMask lComponentMask = mEntityManager -> getComponentMask(tID);
//
//		lComponentMask.set(lComponentID, true);
//		mEntityManager -> setComponentMask(tID, lComponentMask);
//
//		// store new component
//		mComponentManager -> addComponent<ComponentType>(tID, tComponent);
//
//		// update system entity lists
//		mSystemManager -> onComponentMaskUpdate(tID, lComponentMask);
//	}
//
//
//	template <typename ComponentType>
//	void Manager::removeComponent(EntityID tID)
//	{
//		// find component id
//		unsigned int lComponentID = mComponentManager -> getComponentID<ComponentType>();	
//		
//		// update Entity component mask
//		ComponentMask lComponentMask = mEntityManager -> getComponentMask(tID);
//
//		lComponentMask.set(lComponentID, false);
//
//		mEntityManager -> setComponentMask(tID, lComponentMask);
//
//		// store new component
//		mComponentManager -> removeComponent<ComponentType>(tID);
//
//		// update system entity lists
//		mSystemManager -> onComponentMaskUpdate(tID, lComponentMask);
//	}
//
//
//	template <typename ComponentType>
//	ComponentType& Manager::getComponent(EntityID tID)
//	{
//		return (mComponentManager -> getComponent<ComponentType>(tID));
//	}
//
//
//	template <typename ComponentType>
//	unsigned int Manager::getComponentID(void)
//	{
//
//		return (mComponentManager -> getComponentID<ComponentType>());
//	}
//
//
//	template <typename ComponentType>
//	void Manager::setComponent(EntityID tID, ComponentType& tComponent)
//	{
//		mComponentManager -> setComponent<ComponentType>(tID, tComponent);
//	}
//
//
//	template <typename SystemType>
//	void Manager::setSignature(Signature& tSignature)
//	{	
//		mSystemManager -> setSignature<SystemType>(tSignature);
//	}
//
//
//	template <typename SystemType>
//	std::shared_ptr<SystemType> Manager::getSystem(void)
//	{
//		return (mSystemManager -> getSystem<SystemType>());
//	}
//};
//


};


