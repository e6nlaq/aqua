
#pragma once

#include <string>
using namespace std;

inline string cutstr(string cut)
{
	string ret = "";

	for (char c : cut)
	{
		if (c != '\"')
			ret += c;
	}

	return ret;
}

inline bool stob(string s)
{
	if (s == "true" || s == "1")
		return true;
	return false;
}