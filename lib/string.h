
/*******************************************************

			  lib/string.h

	Created at: Jan 7, 2023, 7:41 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#pragma once

#include <string>
using namespace std;

inline bool isint(string s)
{
	if (s == "")
		return false;

	for (char c : s)
	{
		if (!(c >= '0' && c <= '9'))
			return false;
	}

	return true;
}

inline string cutstr(string cut)
{

	string ret = "";

	ret = cut.substr(1, cut.size() - 2);

	return ret;
}

inline bool stob(string s)
{

	if (s == "true")
		return true;

	if (isint(s))
	{
		if (stoi(s) != 0)
			return true;
	}

	return false;
}

inline bool isstring(string str)
{
	return str[0] == '\"';
}