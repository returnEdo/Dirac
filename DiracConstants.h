#pragma once

#include "Vector.h"

namespace Constants{

	/* settings */
	const bool 		VERBOSE			= true;
	const int		WINDOW_WIDTH		= 1080;
	const int 		WINDOW_HEIGHT		= 720;
	const float		ASPECT_RATIO		= static_cast<float>(Constants::WINDOW_WIDTH) / static_cast<float>(Constants::WINDOW_HEIGHT);
	const Vector		BACKGROUND_COLOR(.3f);

	/* Object constants */

	const unsigned int 	VERTICES_COUNT		= 3;
	const unsigned int	COLOR_COUNT		= 3;


	/* Camera constants */

	const float 		DELTAX			= 10.0f;
	const float 		DELTAZ			= 100.0f;
	const float		NEAR_PLANE		= 0.5f;

	/* batch line */
	const unsigned int 	MAX_ISTANCES		= 100;
	constexpr unsigned int 	MAX_LINES 		= 200;
	constexpr unsigned int 	MAX_VERTICES_BATCH	= 1000; 
};
