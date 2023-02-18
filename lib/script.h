
/*******************************************************

			  lib/script.h

	Created at: Jan 7, 2023, 8:00 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under GNU General Public License v3.0.

*******************************************************/

#pragma once

#include "./stdc++.h"
using namespace std;

inline vector<string> scriptcut(string line)
{

	vector<string> result(1, "");
	string copystr = "";
	bool isstr = false;

	int i = 0;
	for (char c : line)
	{
		if (c != ' ')
		{
			if (c != '\t' && (c == '\n' || c >= ' '))
				result[i] += c;
			if (c == '\"')
			{
				isstr = !isstr;
			}
		}
		else
		{
			if (!isstr)
			{
				result.push_back("");
				i++;
			}
			else
			{
				result[i] += c;
			}
		}
	}

	return result;
}

inline bool isvarok(string s)
{

	if (s == "")
		return false;

	if (s == ":")
		return false;

	if (s[0] == '\"')
		return false;

	for (char c : s)
	{
		if (!isdigit(c))
		{
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
			{
			}
			else
				return false;
		}
		else
			return false;
	}

	return true;
}

inline string bond(string a, string b)
{
	return a + b;
}

// string ret(string type, string value)
// {
// 	if (type == "int")
// 	{
// 		return bond("001", value);
// 	}
// 	else if (type == "string")
// 	{
// 		return bond("002", value);
// 	}
// 	else if (type == "bool")
// 	{
// 		return bond("003", value);
// 	}
// 	else if (type == "double")
// 	{
// 		return bond("004", value);
// 	}
// }

inline string boty(string s)
{
	return s.substr(3);
}

inline vector<string> incident(vector<string> s)
{
	// Return
	vector<string> ret;
	string a = "";
	bool in_char = false;

	// For each
	for (auto x : s)
	{
		a = "";
		in_char = false;
		for (auto c : x)
		{
			if (!in_char)
			{
				if (c != ' ' && c != '\t')
				{
					a.push_back(c);
					in_char = true;
				}
			}
			else
				a.push_back(c);
		}
		ret.push_back(a);
	}

	return ret;
}

inline string vtos(vector<string> s)
{
	string ans = "";

	for (auto x : s)
	{
		ans += x;
		ans += "\n";
	}

	return ans;
}

inline void now(vector<string> s, int a)
{
	cout << "\nCurrent Value: " << s[a] << "\n\n";
}