/*
	action struct
*/

#pragma once

#include "types.hpp"

namespace orde {

	struct Action {
		Long time_since_last_action;
		Float x_coord;
		Float y_coord;
		Integer pressed;
	};

}