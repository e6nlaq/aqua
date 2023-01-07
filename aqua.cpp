
#include <bits/stdc++.h>
#include "./lib/all.h"
using namespace std;

#define co(x) cout << (x) << "\n"

bool op_funcskip = false;

void errorlog(vector<string> line, int linenum, int errorcode)
{
	switch (errorcode)
	{
	case 1:
		co("\n\nError: Invalid function passed.");
		break;
	}

	co("The program ended with code " + to_string(errorcode));
	co("Line " + to_string(linenum + 1));
	co("Error location\n");
	if (linenum > 0)
		co(to_string(linenum) + "| " + line[linenum - 1]);
	co(to_string(linenum + 1) + "| \033[1m\033[31m\033[4m" + line[linenum] + "\033[m");
	if (linenum != line.size() - 1)
		co(to_string(linenum + 2) + "| " + line[linenum + 1]);
	exit(errorcode);
}

void aqua(string script, vector<string> line, int linenum)
{
	vector<string> code = scriptcut(script);
	string func = code[0];
	if (func == "out")
	{
		if (code[1][0] == '\"')
			out(cutstr(code[1]));
	}
	else
	{
		if (!op_funcskip && func != "" && func[0] >= '0')
		{
			errorlog(line, linenum, 1);
		}
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

	for (int i = 0; i < lines.size(); i++)
	{
		aqua(lines[i], lines, i);
	}

	return 0;
}
