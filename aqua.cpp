
// #include <bits/stdc++.h>
#include "./lib/all.h"
using namespace std;

// Macro
#define co(x) cout << (x) << "\n"
#define cou(x) cout << (x)
#define err(x) errorlog(line, linenum, (x));
#define all(x) x.begin(), x.end()

// Variant
bool op_funcskip = false, op_stylereset = true, op_end_anykey = false;
map<string, int> var_int;
map<string, string> var_string;
map<string, bool> var_bool;
map<string, double> var_double;
vector<string> lines;
int linenume;

void errorlog(vector<string> line, int linenum, int errorcode);

bool dup_varname(string name)
{
	if (var_int.count(name) || var_string.count(name))
	{
		return false;
	}

	return true;
}

int var_search(string name)
{
	if (var_int.count(name))
	{
		return 1;
	}
	else if (var_string.count(name))
	{
		return 2;
	}
	else if (var_bool.count(name))
	{
		return 3;
	}
	else if (var_double.count(name))
	{
		return 4;
	}
	else
	{
		return 0;
	}
}

string var_value(string name)
{
	switch (var_search(name))
	{
	case 1:
		return to_string(var_int[name]);
		break;

	case 2:
		return var_string[name];
		break;

	case 3:
		return to_string(var_bool[name]);
		break;

	case 4:
		return to_string(var_double[name]);

	default:
		errorlog(lines, linenume, 10);
		break;
	}

	return "";
}

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

	case 7:
		co("Invalid Style");
		break;

	case 8:
		co("Invalid name");
		break;

	case 9:
		co("Overlapping variables");
		break;

	case 10:
		co("Non-existent variable");
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

string aqua(string script, vector<string> line, int linenum)
{
	vector<string> code = scriptcut(script);
	string func = code[0];

	for (int i = 0; i < 10; i++)
	{
		code.push_back("");
	}

	if (func == "out")
	{
		if (code[1][0] == '\"')
			out(cutstr(code[1]));
		else
		{
			out(var_value(code[1]));
		}
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
		else if (code[1] == "reset_style")
		{
			if (code[2] == "true")
				op_stylereset = true;
			else if (code[2] == "false")
				op_stylereset = false;
			else
			{
				err(2)
			}
		}
		else if (code[1] == "end_anykey")
		{
			if (code[2] == "true")
				op_end_anykey = true;
			else if (code[2] == "false")
				op_end_anykey = false;
			else
			{
				err(2)
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
		else
		{
			outf(var_value(code[1]));
		}
	}
	else if (func == "#" || func == "comment")
	{
		// Nothing. :)
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
		if (isvarok(code[2]))
		{
			if (dup_varname(code[2]))
			{
				if (code[1] == "int")
				{
					var_int[code[2]] = 0;
				}
				else if (code[1] == "string")
				{
					var_string[code[2]] = "";
				}
				else if (code[1] == "bool")
				{
					var_bool[code[2]] = true;
				}
				else if (code[1] == "double")
				{
					var_double[code[2]] = 0.0;
				}
				else
				{
					err(6);
				}
			}
			else
			{
				err(9);
			}
		}
		else
		{
			err(8);
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
	else if (func == "style")
	{
		if (code[1] == "text")
		{
			if (code[2] == "black")
			{
				cou("\033[30m");
			}
			else if (code[2] == "red")
			{
				cou("\033[31m");
			}
			else if (code[2] == "green")
			{
				cou("\033[32m");
			}
			else if (code[2] == "yellow")
			{
				cou("\033[33m");
			}
			else if (code[2] == "blue")
			{
				cou("\033[34m");
			}
			else if (code[2] == "magenta")
			{
				cou("\033[35m");
			}
			else if (code[2] == "cyan")
			{
				cou("\033[36m");
			}
			else if (code[2] == "white")
			{
				cou("\033[37m");
			}
			else if (code[2] == "bold")
			{
				cou("\033[1m");
			}
			else if (code[2] == "thinly")
			{
				cou("\033[2m");
			}
			else if (code[2] == "italic")
			{
				cou("\033[3m");
			}
			else if (code[2] == "underline")
			{
				cou("\033[4m");
			}
			else if (code[2] == "blink")
			{
				cou("\033[5m");
			}
			else if (code[2] == "fastblink")
			{
				cou("\033[6m");
			}
			else
			{
				err(7);
			}
		}
		else if (code[1] == "reset")
		{
			cou("\033[m");
		}
		else if (code[1] == "background")
		{
			if (code[2] == "black")
			{
				cou("\033[40m");
			}
			else if (code[2] == "red")
			{
				cou("\033[41m");
			}
			else if (code[2] == "green")
			{
				cou("\033[42m");
			}
			else if (code[2] == "yellow")
			{
				cou("\033[43m");
			}
			else if (code[2] == "blue")
			{
				cou("\033[44m");
			}
			else if (code[2] == "magenta")
			{
				cou("\033[45m");
			}
			else if (code[2] == "cyan")
			{
				cou("\033[46m");
			}
			else if (code[2] == "white")
			{
				cou("\033[47m");
			}
		}
		else
		{
			err(2);
		}
	}
	else if (func == "in")
	{
		switch (var_search(code[1]))
		{
		case 1:
			cin >> var_int[code[1]];
			break;

		case 2:
			cin >> var_string[code[1]];

		case 3:
			cin >> var_bool[code[1]];

		case 4:
			cin >> var_double[code[1]];

		default:
			err(10);
			break;
		}
	}
	else if (func == "set")
	{
		switch (var_search(code[1]))
		{
		case 1:
			if (isvarok(code[2]))
				var_int[code[1]] = stoi(var_value(code[2]));
			else
				var_int[code[1]] = stoi(code[2]);
			break;

		case 2:
			if (code[2][0] == '\"')
				var_string[code[1]] = cutstr(code[2]);
			else
				var_string[code[1]] = var_value(code[2]);
			break;

		case 3:
			var_bool[code[1]] = stob(var_value(code[2]));

		case 4:
			if (isvarok(code[2]))
				var_double[code[1]] = stoi(var_value(code[2]));
			else
				var_double[code[1]] = stoi(code[2]);
			break;

		default:
			err(10);
			break;
		}
	}
	else
	{
		if (!op_funcskip && func != "" && func[0] >= '0')
		{
			errorlog(line, linenum, 1);
		}
	}

	return "";
}

int main(int argc, char const *argv[])
{

#pragma region Aqua System Variables

	var_bool["true"] = true;
	var_bool["false"] = false;
	var_int["null"] = NULL;

#pragma endregion

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

	while (getline(file, read_file))
	{
		lines.push_back(read_file);
	}

	for (int i = 0; i < lines.size(); i++)
	{
		linenume = i;
		aqua(lines[i], lines, i);
	}

	if (op_stylereset)
		cou("\033[m");

	if (op_end_anykey)
	{
		co("\nThe program was successfully completed.");
		co("To exit, press Enter key.");
		int get;
		get = getchar();
	}

	return 0;
}
