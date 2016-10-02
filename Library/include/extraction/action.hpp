/*
	action struct
*/

#pragma once

#include "types.hpp"

namespace orde {

	struct Action {
		using w_t = Long;
		using x_t = Float;
		using y_t = Float;
		using z_t = Integer;

		Long time_since_last_action;
		Float x_coord;
		Float y_coord;
		Integer pressed;
	};

}