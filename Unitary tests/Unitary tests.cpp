/*
	Unitary tests bound to ORDE.
	Made thanks to "Catch" : https://github.com/philsquared/Catch
*/

#include <fstream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "orde_headers.hpp"

SCENARIO("OSRE can read custom types used in replay files", "[types]")
{
	GIVEN("some ULEB128")
	{
		unsigned char first[] = { 0x07 };
		unsigned char second[] = { 0x20 };
		unsigned char third[] = { 0xB4, 0x01 };

		WHEN("converted to uint64_t")
		{
			auto first_c = uleb128_to_uint64_t(first);
			auto second_c = uleb128_to_uint64_t(second);
			auto third_c = uleb128_to_uint64_t(third);
			THEN("1 byte ULEB128 are successfully converted")
			{
				REQUIRE(first_c == 7);
				REQUIRE(second_c == 32);
			}
			THEN("2 bytes ULEB128 are successfully converted")
			{
				REQUIRE(third_c == 180);
			}
		}
	}
	GIVEN("some ULEB128 from istream")
	{
		std::vector<char> raw = { 0x07, 0x7A, 0x65, 0x46, 0x72, 0x65, 0x73, 0x6B };
		std::string str{ std::begin(raw), std::end(raw) };
		std::stringstream sstream{ str };
		raw.clear();
		REQUIRE(sstream.str() == "\azeFresk");
		THEN("ULEB128 is successfully read.")
		{
			REQUIRE(uleb128_from_istream(sstream) == 7);
		}
	}
	GIVEN("some osu String")
	{
		unsigned char str[] = { 0x0B,0x07,0x7A,0x65,0x46,0x72,0x65,0x73,0x6B };

		WHEN("converted to std::string")
		{
			std::string str_c = osustring_to_stdstring(str, str + 10);
			THEN("strings are successfully converted")
			{
				REQUIRE(str_c == "zeFresk");
			}
		}
	}
}
SCENARIO("OSRE read and extract data correctly from replay files", "[extraction]")
{
	GIVEN("a replay file")
	{
		orde::OsrFile file;

		WHEN("the file is loaded")
		{
			std::ifstream filestream("Tests files/Granat.osr", std::ios::binary);
			file = orde::make_osr(filestream);

			THEN("gamemode is correctly read")
			{
				REQUIRE(file.gamemode == orde::gamemode::standard);
			}
			THEN("osu version is correctly read")
			{
				REQUIRE(file.osu_version == 20160821);
			}
			THEN("beatmap hash is correctly read")
			{
				REQUIRE(file.beatmap_hash != ""); //TODO
			}
			THEN("player name is correctly read")
			{
				REQUIRE(file.player_name == "zeFresk");
			}
			THEN("replay hash is correctly read")
			{
				REQUIRE(file.replay_hash != ""); //TODO
			}
			THEN("number of 300s is correctly read")
			{
				REQUIRE(file.three_hundreds == 176);
			}
			THEN("number of 100s is correctly read")
			{
				REQUIRE(file.one_hundreds == 8);
			}
			THEN("number of 50s is correctly read")
			{
				REQUIRE(file.fiftys == 0);
			}
			THEN("number of gekis is correctly read")
			{
				REQUIRE(file.gekis == 39);
			}
			THEN("number of katus is correctly read")
			{
				REQUIRE(file.katus == 5);
			}
			THEN("number of misses is correctly read")
			{
				REQUIRE(file.misses == 2);
			}
			THEN("score is correctly read")
			{
				REQUIRE(file.score == 1134460);
			}
			THEN("greatest combo is correctly read")
			{
				REQUIRE(file.max_combo == 219);
			}
			THEN("full (or not) combo is correctly read")
			{
				REQUIRE(file.full_combo == false);
			}
			THEN("mods used is correctly read")
			{
				REQUIRE(file.mods == orde::mod::none);
			}
			THEN("lifebar graph is correctly read")
			{
				REQUIRE(file.lifebar_graph.size() == 21);
			}
			THEN("timestamp is correctly read")
			{
				REQUIRE(file.timestamp != 0); //TODO
			}
			THEN("compressed data length isn't null")
			{
				REQUIRE(file.compressed_data_length != 0);
			}
			THEN("data replay isn't empty")
			{
				REQUIRE(!file.data.empty());
			}
		}
	}
}

