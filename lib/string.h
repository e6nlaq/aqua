
/*******************************************************

			  lib/string.h

	Created at: Jan 7, 2023, 7:41 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#pragma once

#include <string>
#include "./type.h"
#include <cassert>
#include <iostream>
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
	string ret = "", ans = "";

	ret = cut.substr(1, cut.size() - 2);

	// エスケープシーケンス対応
	for (ull i = 0; i < ret.size(); i++)
	{
		if (ret[i] == '\\')
		{
			// assert(ret[i + 1] == 'n');
			if (i != ret.size() - 1)
			{
				// 次の文字によって変える
				switch (ret[i + 1])
				{
				case 'a':
					ans.push_back('\a');
					break;

				case 'b':
					ans.push_back('\b');
					break;

				case 'f':
					ans.push_back('\f');
					break;

				case 'n':
					ans.push_back('\n');
					break;

				case 'r':
					ans.push_back('\r');
					break;

				case 't':
					ans.push_back('\t');
					break;

				case 'v':
					ans.push_back('\v');
					break;

				case '\\':
					ans.push_back('\\');
					break;

				case '?':
					ans.push_back('\?');
					break;

				case '\'':
					ans.push_back('\'');
					break;

				case '\"':
					ans.push_back('\"');
					break;

				case '0':
					ans.push_back('\0');
					break;

				default:
					// 不正な場合は、C++と同様に
					ans.push_back(ret[i + 1]);
					break;
				}
				i++;
			}
			else
			{
				ans.push_back('\\');
			}
		}
		else
		{
			ans.push_back(ret[i]);
		}
	}

	return ans;
}

inline bool isstring(string str)
{
	return str[0] == '\"' && str[str.size() - 1] == '\"';
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
	if (isstring(s))
	{
		return true;
	}

	return false;
}
