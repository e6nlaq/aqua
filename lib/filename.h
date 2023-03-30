
/*******************************************************

			  lib/filename.h

	Created at: Mar 18, 2023, 13:31 PM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#include <string>
using namespace std;

#pragma once

inline string get_filename(string s)
{
	long long at = 9999999999999LL;
	for (long long i = s.size() - 1; 0 <= i; i--)
	{
		if (s[i] == '.')
		{
			at = i;
			break;
		}
	}

	return s.substr(0, at);
}

inline bool is_jsfile(string filename)
{
	if (filename.substr(filename.size() - 2) == "js")
	{
		return true;
	}
	else
		return false;
}
