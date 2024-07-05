
/*******************************************************

			  lib/script.h

	Created at: Jan 7, 2023, 8:00 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#pragma once

#include "./stdc++.h"

inline std::vector<std::string> scriptcut(std::string line)
{
	std::vector<std::string> result(1, "");
	std::string copystr = "";
	bool isstr = false;

	int i = 0;

	for (long long j = 0; j < line.size(); j++)
	{
		char c = line[j];

		if (c != ' ')
		{
			if (c != '\t' && (c == '\n' || c >= ' ' || c < 0))
				result[i] += c;
			if (c == '\"')
			{
				if (line[j - 1] != '\\')
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

	// for (char c : line)
	// {
	// 	}

	return result;
}

inline bool isvarok(std::string s)
{
	if (s == "")
		return false;

	if (s == ":")
		return false;

	if (s[0] == '\"')
		return false;

	if (isdigit(s[0]))
		return false;

	for (char c : s)
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || c == ':' || (c >= '0' && c <= '9'))
		{
			// 何もしない
		}
		else
			return false;
	}

	return true;
}

inline bool isvardecok(std::string s)
{
	if (s == "")
		return false;

	if (s == ":")
		return false;

	if (s[0] == '\"')
		return false;

	if (isdigit(s[0]))
		return false;

	for (ll i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if (c == '$')
			continue;

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9'))
		{
			// 何もしない
		}
		else
			return false;
	}

	return true;
}

inline std::string bond(std::string a, std::string b)
{
	return a + b;
}

inline std::string boty(std::string s)
{
	return s.substr(3);
}

inline std::vector<std::string> incident(std::vector<std::string> s)
{
	// Return
	std::vector<std::string> ret;
	std::string a = "";
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
			{
				if ((int)c > 31 || (int)c < 0)
					a.push_back(c);
			}
		}
		ret.push_back(a);
	}

	return ret;
}

inline std::string vtos(std::vector<std::string> s)
{
	std::string ans = "";

	for (auto x : s)
	{
		ans += x;
		ans += "\n";
	}

	return ans;
}

inline void now(std::vector<std::string> s, int a)
{
	std::cout << "\nCurrent Value: " << s[a] << "\n\n";
}
