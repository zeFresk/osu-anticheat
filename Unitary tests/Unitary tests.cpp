/*
	Unitary tests bound to ORDE.
	Made thanks to "Catch" : https://github.com/philsquared/Catch
*/

#include <fstream>
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
			auto first_c = ULEB128_to_integer(first);
			auto second_c = ULEB128_to_integer(second);
			auto third_c = ULEB128_to_integer(third);
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
	GIVEN("some osu String")
	{
		unsigned char str[] = { 0x0B,0x07,0x7A,0x65,0x46,0x72,0x65,0x73,0x6B };

		WHEN("converted to std::string")
		{
			std::string str_c = osustring_to_stdstring(str);
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
		OsrFile const file;

		WHEN("the file is loaded")
		{
			std::ifstream filestream("Tests files/Granat.hpp", std::ios::binary);
			file = make_osr(filestream);

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
				REQUIRE(file.katus == 39);
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
				REQUIRE(file.lifebar_graph == "449|1,2769|1,4937|1,7078|1,9399|1,11553|1,13878|1,15883|1,18010|1,20011|1,22136|0.97,24139|1,26478|0.99,28627|1,30952|1,33437|1,35440|1,37444|0.97,39577|0.62,41732|0.66,42099|0.69");
			}
			THEN("timestamp is correctly read")
			{
				REQUIRE(file.timestamp != 0); //TODO
			}
			THEN("compressed data length isn't null")
			{
				REQUIRE(file.length_compressed_data != 0);
			}
			THEN("data replay isn't empty")
			{
				REQUIRE(!file.data.empty());
			}
		}
	}
}

