
#include <bits/stdc++.h>
#include "./lib/all.h"
#include "./lib/string.h"
using namespace std;

#define co(x) cout << (x) << "\n"

void aqua(string script)
{
	co(cutstr("\"Hello,world!\""));
}

int main(int argc, char const *argv[])
{

	if (argc == 1 || argc > 2 || argv[1] == "--help")
	{
		co("Welcome to Aqua!");
		co("\nAqua helps to solve a very small problem");
		co("Let's specify the Aqua script as the first argument!");
		return 0;
	}

	ifstream file;
	file.open(argv[1]);

	string read_file;

	vector<string> lines;

	while (getline(file, read_file))
	{
		lines.push_back(read_file);
	}

	for (string line : lines)
	{
		aqua(line);
	}

	return 0;
}
