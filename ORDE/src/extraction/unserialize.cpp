#include <sstream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include <iterator>

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include "../../../LZMA/include/decompress.hpp"

#include "conversion/osustring.hpp"
#include "conversion/uleb128.hpp"

#include "extraction/unserialize.hpp"
#include "extraction/osrfile.hpp"


namespace orde {

	template <>
	void unserialize<std::string>(std::istream& stream, std::string& str)
	{
		uint8_t present = 0x00;
		unserialize(stream, present);
		assert((present == 0x00 || present == 0x0b) && "invalid osu string");

		if (present == 0x0b)
		{
			auto size = uleb128_from_istream(stream); //'\0'

			str.reserve(static_cast<std::size_t>(size));
			std::copy_n(std::istreambuf_iterator<char>(stream), size, std::back_inserter(str));
			stream.ignore(1); //???
		}
		else
		{
			str = "";
		}
	}


	void unserialize(std::istream& stream, Actions& actions, Integer size)
	{
		assert(size != 0 && "actions are empty");

		std::vector<char> inBuf(size);
		stream.read(inBuf.data(), size);

		std::vector<char> outBuf;
		lzma_decompress(outBuf, inBuf);

		std::string uncompressed_string(outBuf.begin(), outBuf.end()); //Peppy why u do dis ? Why a string ???
		uncompressed_string.resize(uncompressed_string.size() - 1); //"the last one is a ','

		std::vector<std::string> results;
		boost::split(results, uncompressed_string, [](char car) {return car == ','; });
		actions.reserve(results.size());

		for (auto& a : results)
		{
			std::vector<std::string> wxyz;
			boost::split(wxyz, a, [](char car) {return car == '|'; });
			actions.push_back({ boost::lexical_cast<Action::w_t>(std::move(wxyz[0])), boost::lexical_cast<Action::x_t>(std::move(wxyz[1])), boost::lexical_cast<Action::y_t>(std::move(wxyz[2])), boost::lexical_cast<Action::z_t>(std::move(wxyz[3])) });
		}
	}

	template <>
	void unserialize<Graph>(std::istream& stream, Graph& graph)
	{
		assert(graph.empty() && "graph must be empty");

		std::string graph_str;
		unserialize(stream, graph_str);
		graph_str.resize(graph_str.size() - 1); //we need to remove the last ","

		std::vector<std::string> results;
		boost::split(results, graph_str, [](char car) {return car == ','; });
		graph.reserve(results.size());

		for (auto& a : results)
		{
			std::vector<std::string> uv;
			boost::split(uv, a, [](char car) {return car == '|'; });
			graph.push_back(std::make_pair(boost::lexical_cast<Graph::value_type::first_type>(uv[0]), boost::lexical_cast<Graph::value_type::second_type>(uv[1])));
		}
	}

}