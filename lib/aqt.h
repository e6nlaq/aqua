
/*******************************************************

			  lib/aqt.h

	Created at: Mar 28, 2023, 18:30 PM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <fstream>
#include "./filename.h"

#pragma once

// Aqua Toolsのファイル(return.txt)があるかどうかの判定
inline bool tool_ok()
{
	// まずはディレクトリを確認
	struct stat node_module;
	if (!stat("./node_modules/aqua-tools", &node_module) == 0)
		return false;

	// 一応try
	FILE *fp;
	try
	{
		fp = fopen("./node_modules/aqua-tools/return.txt", "r");
		if (fp == NULL)
		{
			fclose(fp);
			return false;
		}
	}
	catch (const std::exception &e)
	{
		return false;
	}

	fclose(fp);
	return true;
}

template <class... A>
inline void run(std::string filename, A... args)
{
	std::string cmd = "echo";
	if (is_jsfile(filename))
		cmd = "node";
	else
		cmd = "python3";

	cmd += " ./node_modules/aqua-tools/" + filename;

	for (auto x : std::initializer_list<std::string>{args...})
	{
		cmd += " \"" + x + "\"";
	}

	system(cmd.c_str());
}

inline std::string get_return()
{
	std::ifstream file;

	file.open("./node_modules/aqua-tools/return.txt", std::ios::in);
	std::string ans = "", tmp = "";

	while (std::getline(file, tmp))
	{
		ans += tmp + "\n";
	}

	ans = ans.substr(0, ans.size() - 1);

	return ans;
}
