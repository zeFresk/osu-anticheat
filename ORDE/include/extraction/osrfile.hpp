/*
	here is defined the structure of osrfile
*/

#pragma once

#include <vector>
#include <string>
#include <utility>

#include "enums.hpp"
#include "types.hpp"
#include "action.hpp"


namespace orde {

	using Actions = std::vector<Action>;
	using Graph_point = std::pair<uint32_t, float>;
	using Graph = std::vector<Graph_point>;

	struct OsrFile
	{
		gamemode gamemode;
		Integer osu_version;
		std::string beatmap_hash;
		std::string player_name;
		std::string replay_hash;
		Short three_hundreds;
		Short one_hundreds;
		Short fiftys;
		Short gekis;
		Short katus;
		Short misses;
		Integer score;
		Short max_combo;
		Byte full_combo;
		Integer mods;
		Graph lifebar_graph;
		Long timestamp;
		Integer compressed_data_length;
		Actions data;
	};

}