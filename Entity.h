#pragma once

#include <bitset>

#include "ECSConstants.h"

/*

INFO: Entity

Entities are only ids.
For each Entity there is a component mask
indicating the components attached to it.

*/


namespace Dirac
{

// define two recurrent aliases
using EntityID 		= unsigned int;
using ComponentMask 	= std::bitset<ECSConstants::MAX_COMPONENTS>;

};
