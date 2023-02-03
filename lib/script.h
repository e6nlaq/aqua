
#pragma once

#include "./stdc++.h"
using namespace std;

vector<string> scriptcut(string line)
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

bool isvarok(string s)
{
	for (char c : s)
	{
		if (!(!isdigit(c) || c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
			return false;
	}

	return true;
}

string bond(string a, string b)
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

string boty(string s)
{
	return s.substr(3);
}