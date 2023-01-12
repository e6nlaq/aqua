
#include <bits/stdc++.h>
#include "./lib/all.h"
using namespace std;

#define co(x) cout << (x) << "\n"
#define err(x) errorlog(line, linenum, (x));

// Variant
bool op_funcskip = false;
map<string, int> var_int;

void errorlog(vector<string> line, int linenum, int errorcode)
{
	cout << "\n\nError: ";
	switch (errorcode)
	{

	case 0:
		co("Example Error");
		break;

	case 1:
		co("Invalid function passed.");
		break;
	case 2:
		co("Invalid argument.");
		break;

	case 3:
		co("Invalid option.");
		break;

	case 4:
		co("User-defined exception thrown");
		break;

	case 5:
		co("Invalid error code");
		break;

	case 6:
		co("invalid type");
		break;

	default:
		err(5);
		return;
		break;
	}

#pragma region Error Messages

	co("The program ended with code " + to_string(errorcode));
	co("Line " + to_string(linenum + 1));
	co("Error location\n");
	if (linenum > 1)
		co(to_string(linenum - 1) + "| " + line[linenum - 2]);
	if (linenum > 0)
		co(to_string(linenum) + "| " + line[linenum - 1]);
	co(to_string(linenum + 1) + "| \033[1m\033[31m\033[4m" + line[linenum] + "\033[m");
	if (linenum != line.size() - 1)
		co(to_string(linenum + 2) + "| " + line[linenum + 1]);

	if (linenum + 2 < line.size())
		co(to_string(linenum + 3) + "| " + line[linenum + 2]);
	exit(errorcode);

#pragma endregion
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
	else if (func == "option")
	{
		if (code[1] == "function_skip")
		{
			if (code[2] == "true")
				op_funcskip = true;
			else if (code[2] == "false")
				op_funcskip = false;
			else
			{
				errorlog(line, linenum, 2);
			}
		}
		else
		{
			errorlog(line, linenum, 3);
		}
	}
	else if (func == "outf")
	{
		if (code[1][0] == '\"')
			outf(cutstr(code[1]));
	}
	else if (func == "#" || func == "comment")
	{
	}
	else if (func == "exit")
	{
		if (code.size() == 1)
			exit(0);
		else
			exit(stoi(code[1]));
	}
	else if (func == "throw")
	{
		if (code.size() == 1)
		{
			err(4);
		}
		else
		{
			err(stoi(code[1]));
		}
	}
	else if (func == "var")
	{
		if (code[1] == "int")
		{
		}
		else
		{
			err(6);
		}
	}
	else if (func == "ln")
	{
		if (code.size() == 1)
		{
			cout << "\n";
		}
		else
		{
			for (int i = 0; i < stoi(code[1]); i++)
				cout << "\n";
		}
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
