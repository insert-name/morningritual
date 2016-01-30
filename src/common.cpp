#include "common.h"

namespace MorningRitual
{
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss(s);
		std::string item;
		
		while (std::getline(ss, item, delim))
		{
		    elems.push_back(item);
		}
		
		return elems;
	}
	
	std::vector<std::string> split(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
	
	float sign(float x)
	{
		if (x > 0.0f)
			return 1.0f;
		else if (x < 0.0f)
			return -1.0f;
		else
			return 0.0f;
	}
}
