#pragma once

#include <set>

#include "ECSConstants.h"
#include "Entity.h"


namespace Dirac
{


using Signature = std::bitset<ECSConstants::MAX_COMPONENTS>;


class SystemManager;


class ISystem
{
	protected:

	std::set<EntityID> mEntities;

	Signature mSignature;
	
	friend class SystemManager;
};


};
