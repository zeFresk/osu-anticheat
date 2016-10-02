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
	OsrFile make_osr(std::ifstream& stream);



}