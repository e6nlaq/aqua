
#pragma once

#include <bits/stdc++.h>
using namespace std;

string cutstr(string cut)
{
	string ret = "";

	for (char c : cut)
	{
		if (c != '\"')
			ret += c;
	}

	return ret;
}