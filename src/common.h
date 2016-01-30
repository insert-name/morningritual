#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <sstream>
#include <vector>

namespace MorningRitual
{
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
	
	std::vector<std::string> split(const std::string &s, char delim);
	
	float sign(float x);
}

#endif
