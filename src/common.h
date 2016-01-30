#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <sstream>
#include <vector>
#include "deque"

namespace MorningRitual
{
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
	
	std::vector<std::string> split(const std::string &s, char delim);
	
	float sign(float x);
	
	template<class C>
	bool vectorContains(std::vector<C> v, C i)
	{
		for (C t : v)
		{
			if (t == i)
				return true;
		}
		return false;
	}
	
	template<class C>
	bool dequeContains(std::deque<C> v, C i)
	{
		for (C t : v)
		{
			if (t == i)
				return true;
		}
		return false;
	}
	
	template<class C>
	int dequeAt(std::deque<C> v, C i)
	{
		for (int a = 0; a < v.size(); a ++)
		{
			if (v[a] == i)
				return a;
		}
		return -1;
	}
}

#endif
