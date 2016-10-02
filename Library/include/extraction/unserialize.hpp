#pragma once

#include <istream>
#include <type_traits>

#include <boost/endian/conversion.hpp>

#include "types.hpp"
#include "osrfile.hpp"

namespace orde {

	template <typename Type>
	inline void unserialize(std::istream& stream, Type& data)
	{
		static_assert(std::is_arithmetic<Type>::value, "data must be an arithmetical type");
		stream.read(reinterpret_cast<char*>(&data), sizeof(data));
		data = boost::endian::little_to_native(data);
	}

	template <>
	void unserialize<std::string>(std::istream& stream, std::string& str);

	void unserialize(std::istream& stream, Actions& actions, Integer size);

	template <>
	void unserialize<Action>(std::istream& stream, Action& act);

	template <>
	void unserialize<Graph>(std::istream& stream, Graph& graph);

}