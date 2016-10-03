/*
	extraction section main header
*/

#pragma once

#include <iosfwd>

#include "osrfile.hpp"

namespace orde {

	/*
		Return a OsrFile from an input stream
	*/
	OsrFile make_osr(std::istream& stream);

	inline std::istream& operator >> (std::istream& stream, OsrFile& osr)
	{
		osr = make_osr(stream);
		return stream;
	}

	//OsrFile make_osr_no_graph(std::istream& stream);

}