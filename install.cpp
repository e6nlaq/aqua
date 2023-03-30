
/*******************************************************

			  install.cpp

	Created at: Mar 23, 2023, 18:14 PM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#include "./lib/all.h"
using namespace std;

#define co(x) cout << (x) << "\n"

vector<string> exename = {"node", "npm", "python3", "pip3"};
vector<string> npmi = {"npm init -y", "npm install git+https://github.com/e6nlaq/aqua-tools.git"};
vector<string> pipm = {"pyutogui", "requests", "playsound==1.2.2"};

inline void check()
{
	co("I'm checking to see if there is an app I need...");

	for (auto x : exename)
	{
		string tmp = x + " --version";
		if (system(tmp.c_str()))
		{
			co("Error: App \"" + x + "\" does not exist!");
			exit(1);
		}
	}
}

inline void npm()
{
	co("Download Aqua Tools...");

	for (auto x : npmi)
	{
		if (system(x.c_str()))
		{
			co("Error: An unexpected error has occurred.");
			exit(1);
		}
	}
}

inline void pip()
{
	co("Download Python Modules...");

	for (auto x : pipm)
	{
		string s = "pip3 install " + x;
		if (system(s.c_str()))
		{
			co("Error: An unexpected error has occurred.");
			exit(1);
		}
	}
}

int main(int argc, char const *argv[])
{

	cscle();

	vector<string> args(argv, argv + argc);

	co("-----------------------------------------------------------------------");
	co("Aqua Tools Install Manager");
	co("Copyright (C) 2023 e6nlaq");
	co("-----------------------------------------------------------------------");

	if (argc == 1)
	{
		co("Please specify options!");
		co("-----------------------------------------------------------------------");
		co("init: Install Aqua Tools!");
		co("pyinstall: Install the necessary modules for Aqua Tools for Python!");
		co("-----------------------------------------------------------------------");
		exit(1);
	}

	string arg = args[1];

	if (arg == "init")
	{
		check();
		npm();
		co("-----------------------------------------------------------------------");
		co("You have successfully downloaded Aqua Tools!");
		co("For proper operation, please also try \" ati pyinstall \"!");
		co("-----------------------------------------------------------------------");
	}
	else if (arg == "pyinstall")
	{
	}

	return 0;
}
