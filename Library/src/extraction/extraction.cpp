#include <cassert>
#include <fstream>

#include "extraction/extraction.hpp"
#include "extraction/unserialize.hpp"

namespace orde {

	OsrFile make_osr(std::ifstream & stream)
	{
		assert(stream.is_open() && "couldn't open replay file");
		
		OsrFile ret;
		unserialize(stream, *reinterpret_cast<uint8_t*>(&ret.gamemode));
		unserialize(stream, ret.osu_version);
		unserialize(stream, ret.beatmap_hash);
		unserialize(stream, ret.player_name);
		ret.player_name.resize(ret.player_name.size() - 1); // ?????
		unserialize(stream, ret.replay_hash);
		unserialize(stream, ret.three_hundreds);
		unserialize(stream, ret.one_hundreds);
		unserialize(stream, ret.fiftys);
		unserialize(stream, ret.gekis);
		unserialize(stream, ret.katus);
		unserialize(stream, ret.misses);
		unserialize(stream, ret.score);
		unserialize(stream, ret.max_combo);
		unserialize(stream, ret.full_combo);
		unserialize(stream, ret.mods);
		unserialize(stream, ret.lifebar_graph);
		unserialize(stream, ret.timestamp);
		unserialize(stream, ret.compressed_data_length);
		unserialize(stream, ret.data, ret.compressed_data_length);

		return ret;
	}

}