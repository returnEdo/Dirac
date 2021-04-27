#pragma once

#include <array>
#include <memory>

#include "ECSConstants.h"
#include "Entity.h"
#include "System.h"


/*
INFO

Manages System entity set on component masks
updates


*/

namespace Dirac
{


class SystemManager
{
	private:

	// the manager owns the systems
	std::array<std::shared_ptr<ISystem>, ECSConstants::MAX_SYSTEMS> mSystems;

	unsigned int mSystemsCount { 0 };

	public:

	template <typename SystemType>
	unsigned int getSystemID(void)
	{
		// managing the unique systems id

		static unsigned int sSystemID = mSystemsCount;
		static unsigned int sThisSystemCount = 0;
		
		if (not sThisSystemCount)
		{
			mSystems[sSystemID] = std::make_shared<ISystem>();
			mSystemsCount ++;
		}

		sThisSystemCount ++;

		return sSystemID;
	}


	template <typename SystemType>
	void setSignature(const Signature& tSignature)
	{
		mSystems[getSystemID<SystemType>()] -> mSignature = tSignature;
	}


	template <typename SystemType>
	Signature& getSignature(void)
	{
		// TODO: throw exception

		return mSystems[getSystemID<SystemType>()] -> mSignature;
	}


	template <typename SystemType>
	std::shared_ptr<SystemType> getSystem(void)
	{
		return (std::static_pointer_cast<SystemType>(mSystems[getSystemID<SystemType>()]));
	}


	void onComponentMaskUpdate(EntityID tID, ComponentMask tComponentMask)
	{
		// Entity list update

		for (auto lSystem: mSystems)
		{
			if (lSystem != nullptr)
			{

				if (((lSystem -> mSignature) & tComponentMask) == (lSystem -> mSignature))
				{
					(lSystem -> mEntities).insert(tID);
				}
				else
				{
					// returns 0 if no element is erased
					(lSystem -> mEntities).erase(tID);
				}
			}
		}
	}


	void entityRemoved(EntityID tID)
	{
		for (auto lSystem: mSystems)
		{
			if (lSystem != nullptr)
			{
				(lSystem -> mEntities).erase(tID);
			}
		}
	}
};

};


