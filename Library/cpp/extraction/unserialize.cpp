#include <sstream>
#include <string>
#include <istream>
#include <cassert>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

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
			auto size = uleb128_from_istream(stream) + 1;

			str.resize(static_cast<std::size_t>(size));
			stream.get(const_cast<char*>(str.c_str()), size); //horrible
		}
		else
		{
			str = "";
		}
	}


	void unserialize(std::istream& stream, Actions& actions, Integer size)
	{
		assert(size != 0 && "actions are empty");

		actions.reserve(size);


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
		results.resize(results.size() - 1); //don't ask me why, the last one is empty
		graph.reserve(results.size());

		for (auto& a : results)
		{
			std::vector<std::string> uv;
			boost::split(uv, a, [](char car) {return car == '|'; });
			graph.push_back(std::make_pair(boost::lexical_cast<Graph::value_type::first_type>(uv[0]), boost::lexical_cast<Graph::value_type::second_type>(uv[1])));
		}
	}

}