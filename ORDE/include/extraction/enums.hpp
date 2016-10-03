/*
	necessary enums
*/

#pragma once

#include <cstdint>

namespace orde {

	enum gamemode : char
	{
		standard = 0, taiko = 1, ctb = 2, mania = 3
	};

	enum buttons : char
	{
		M1 = 1, M2 = 2, K1 = 5, K2 = 10
	};

	enum mod : uint32_t
	{
		none = 0,
		no_fail = 1,
		easy = 2,
		no_video = 1 << 2,
		hidden = 1 << 3,
		hardrock = 1 << 4,
		sudden_death = 1 << 5,
		double_time = 1 << 6,
		relax = 1 << 7,
		half_time = 1 << 8,
		nightcore = 1 << 9,
		flashlight = 1 << 10,
		autoplay = 1 << 11,
		spun_out = 1 << 12,
		autopilot = 1 << 13,
		perfect = 1 << 14,
		key4 = 1 << 15,
		key5 = 1 << 16,
		key6 = 1 << 17,
		key7 = 1 << 18,
		key8 = 1 << 19,
		fade_in = 1 << 20,
		random = 1 << 21,
		cinema = 1 << 22,
		target_practice = 1 << 23,
		key9 = 1 << 24,
		coop = 1 << 25,
		key1 = 1 << 26,
		key3 = 1 << 27,
		key2 = 1 << 28
	};

}