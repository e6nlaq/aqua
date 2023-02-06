
#pragma once

#include <string>
using namespace std;

inline string cutstr(string cut)
{

	string ret = "";

	ret = cut.substr(1, cut.size() - 2);

	return ret;
}

inline bool stob(string s)
{
	if (s == "true" || s == "1")
		return true;
	return false;
}