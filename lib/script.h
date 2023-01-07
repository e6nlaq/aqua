
#pragma once

#include <bits/stdc++.h>
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