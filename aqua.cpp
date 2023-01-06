
#include <bits/stdc++.h>
#include "./lib/all.h"
using namespace std;

#define co(x) cout << (x) << "\n"

void aqua(string script, vector<string> line)
{
	vector<string> code = scriptcut(script);
	string func = code[0];
	if (func == "out")
	{
		if (code[1][0] == '\"')
			out(cutstr(code[1]));
	}
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
		aqua(line, lines);
	}

	return 0;
}
