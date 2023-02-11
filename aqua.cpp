
/**********************************************

			  aqua.cpp

	Created at: Jan 7, 2023, 7:41 AM GMT+9
	Copyright (C) 2023 e6nlaq

**********************************************/

// Include
#include "./lib/all.h"
using namespace std;

// Using Type
using ll = long long;
using ld = long double;

// Macro
#define co(x) cout << (x) << "\n"
#define cou(x) cout << (x)
#define err(x) errorlog(line, linenum, (x));
#define all(x) x.begin(), x.end()
#define rep(i, n) for (ll i = 0; i < (n); i++)

// Variant (Option)
bool op_funcskip = false;
bool op_stylereset = true;
bool op_end_anykey = false;

// Variant ()
map<string, int> var_int;
map<string, string> var_string;
map<string, bool> var_bool;
map<string, double> var_double;
vector<string> lines;
int linenume;
bool runcode = true;
int inc_now = 0;
int inc_code = 0;

ll debug_test = 0;

// Advance Declaration
inline void errorlog(vector<string> line, int linenum, int errorcode);
inline string nx();

inline bool dup_varname(string name)
{
	if (var_int.count(name) || var_string.count(name) || var_bool.count(name) || var_double.count(name))
	{
		return false;
	}

	return true;
}

inline int var_search(string name)
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

inline bool m_numt(string name)
{
	return (var_search(name) == 1 || var_search(name) == 4);
}

inline string var_value(string name)
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

inline void errorlog(vector<string> line, int linenum, int errorcode)
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

	case 11:
		co("Division by zero is not allowed");
		break;

	case 12:
		co("There is no square root of a negative number");
		break;

	case 13:
		co("Invalid Variable");
		break;

	case 14:
		co("Missing argument");
		break;

	case 15:
		co("You can't use : here.");
		break;

	case 16:
		co("You can't break here.");
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
	exit(-1);

#pragma endregion
}

inline string aqua(string script, vector<string> line, int linenum)
{
	vector<string> code = scriptcut(script);
	string func = code[0];

	for (int i = 0; i < 10; i++)
	{
		code.push_back("");
	}

	if (inc_code == inc_now)
	{

		if (func == "out")
		{
			if (code[1][0] == '\"')
				out(cutstr(code[1]));
			else if (code[1] == ":")
				out(nx());
			else
			{
				out(var_value(code[1]));
			}
		}
		else if (func == "option")
		{

			// True or False?
			if (code[2] == "true" || code[2] == "false")
			{

				if (code[1] == "function_skip")
				{
					op_funcskip = stob(code[2]);
				}
				else if (code[1] == "reset_style")
				{
					op_stylereset = stob(code[2]);
				}
				else if (code[1] == "end_anykey")
				{
					op_end_anykey = stob(code[2]);
				}
				else if (code[1] == "set_few")
				{
					cout << fixed << setprecision(stoi(code[2]));
				}
				else
				{
					errorlog(line, linenum, 3);
				}
			}
			else
			{
				err(2);
			}
		}
		else if (func == "outf")
		{
			if (isstring(code[1]))
				outf(cutstr(code[1]));
			else if (code[1] == ":")
			{
				outf(nx());
			}
			else if (isvarok(code[1]))
			{
				outf(var_value(code[1]));
			}
			else
				err(2);
		}
		else if (func == "#" || func == "comment")
		{
			// Nothing. :)
		}
		else if (func == "exit")
		{
			if (code[1] == "")
			{
				exit(0);
			}
			else
			{
				exit(stoi(code[1]));
			}
		}
		else if (func == "throw")
		{
			if (code[1] == "")
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
			if (code[1] == "")
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
				break;

			case 3:
				cin >> var_bool[code[1]];
				break;

			case 4:
				cin >> var_double[code[1]];
				break;

			default:
				err(10);
				break;
			}
		}
		else if (func == "set")
		{
			// co(to_string(isvarok(":")));
			switch (var_search(code[1]))
			{
			case 1:
				if (isvarok(code[2]))
					var_int[code[1]] = stoi(var_value(code[2]));
				else if (code[2] == ":")
					var_int[code[1]] = stoi(nx());
				else
					var_int[code[1]] = stoi(code[2]);
				break;

			case 2:
				if (code[2][0] == '\"')
					var_string[code[1]] = cutstr(code[2]);
				else if (code[2] == ":")
					var_string[code[1]] = nx();
				else
					var_string[code[1]] = var_value(code[2]);
				break;

			case 3:
				if (isvarok(code[2]))
					var_bool[code[1]] = stob(var_value(code[2]));
				else if (code[2] == ":")
					var_bool[code[1]] = stob(nx());
				else
					var_bool[code[1]] = stob(var_value(code[2]));

			case 4:
				if (isvarok(code[2]))
					var_double[code[1]] = stoi(var_value(code[2]));
				else if (code[2] == ":")
					var_double[code[1]] = stod(nx());
				else
					var_double[code[1]] = stoi(code[2]);
				break;

			default:
				err(10);
				break;
			}
		}
		else if (func == "flush")
		{
			cout << flush;
		}
		else if (func == "+")
		{
			ld a, b;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			if (isvarok(code[2]))
				b = stold(var_value(code[2]));
			else
				b = stold(code[2]);

			return to_string(a + b);
		}
		else if (func == "-")
		{
			ld a, b;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			if (isvarok(code[2]))
				b = stold(var_value(code[2]));
			else
				b = stold(code[2]);

			return to_string(a - b);
		}
		else if (func == "*")
		{
			ld a, b;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			if (isvarok(code[2]))
				b = stold(var_value(code[2]));
			else
				b = stold(code[2]);

			return to_string(a * b);
		}
		else if (func == "/")
		{
			ld a, b;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			if (isvarok(code[2]))
				b = stold(var_value(code[2]));
			else
				b = stold(code[2]);

			if (b == 0)
				err(11);

			return to_string(a / b);
		}
		else if (func == "%")
		{
			ll a, b;
			if (isvarok(code[1]))
				a = stoll(var_value(code[1]));
			else
				a = stoll(code[1]);

			if (isvarok(code[2]))
				b = stoll(var_value(code[2]));
			else
				b = stoll(code[2]);

			if (b == 0)
				err(11);

			return to_string(a % b);
		}
		else if (func == "abs")
		{
			ld a;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			return to_string(abs(a));
		}
		else if (func == "sqrt")
		{
			ld a;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			if (a < 0)
				err(12);

			return to_string(sqrt(a));
		}
		else if (func == "sin")
		{
			ld a;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			return to_string(sin(a));
		}
		else if (func == "cos")
		{
			ld a;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			return to_string(cos(a));
		}
		else if (func == "tan")
		{
			ld a;
			if (isvarok(code[1]))
				a = stold(var_value(code[1]));
			else
				a = stold(code[1]);

			return to_string(tan(a));
		}
		else if (func == "++")
		{
			if (m_numt(code[1]))
			{
				if (var_search(code[1]) == 1)
				{
					var_int[code[1]]++;
				}
				else
				{
					var_int[code[1]]++;
				}
			}
			else
				err(13);
		}
		else if (func == "--")
		{
			if (m_numt(code[1]))
			{
				if (var_search(code[1]) == 1)
				{
					var_int[code[1]]--;
				}
				else
				{
					var_int[code[1]]--;
				}
			}
			else
				err(13);
		}
		else if (func == "if")
		{
			// co("ififif");
			if (isvarok(code[1]))
			{
				runcode = stob(var_value(code[1]));
			}
			else if (code[1] == ":")
				runcode = stob(nx());
			else
			{
				runcode = stob(code[1]);
			}

			if (runcode)
			{
				inc_now++;
				inc_code++;
			}
			else
				inc_now++;
		}
		else if (func == "end")
		{
			// For if condition is true
			// Nothing (LOL)
		}
		else if (func == "else")
		{
			if (runcode)
			{
				inc_now--;
				inc_code--;
			}
			else
			{
				inc_now--;
			}

			runcode = !runcode;

			if (runcode)
			{
				inc_now++;
				inc_code++;
			}
			else
				inc_now++;
		}
		else if (func == "and")
		{
			bool a, b;
			if (isvarok(code[1]))
			{
				a = stob(var_value(code[1]));
			}
			else if (code[1] == ":")
			{
				a = stob(nx());
			}
			else
				a = stob(code[1]);

			if (isvarok(code[2]))
			{
				b = stob(var_value(code[2]));
			}
			else if (code[2] == ":")
			{
				b = stob(nx());
			}
			else
				b = stob(code[2]);

			return to_string(a && b);
		}
		else if (func == "or")
		{
			bool a, b;
			if (isvarok(code[1]))
			{
				a = stob(var_value(code[1]));
			}
			else if (code[1] == ":")
			{
				a = stob(nx());
			}
			else
				a = stob(code[1]);

			if (isvarok(code[2]))
			{
				b = stob(var_value(code[2]));
			}
			else if (code[2] == ":")
			{
				b = stob(nx());
			}
			else
				b = stob(code[2]);

			return to_string(a || b);
		}
		else if (func == "xor")
		{
			bool a, b;
			if (isvarok(code[1]))
			{
				a = stob(var_value(code[1]));
			}
			else if (code[1] == ":")
			{
				a = stob(nx());
			}
			else
				a = stob(code[1]);

			if (isvarok(code[2]))
			{
				b = stob(var_value(code[2]));
			}
			else if (code[2] == ":")
			{
				b = stob(nx());
			}
			else
				b = stob(code[2]);

			return to_string(a ^ b);
		}
		else if (func == "not" || func == "!")
		{
			bool a;
			if (isvarok(code[1]))
			{
				a = stob(var_value(code[1]));
			}
			else if (code[1] == ":")
			{
				a = stob(nx());
			}
			else
				a = stob(code[1]);

			return to_string(!a);
		}
		else if (func == "is")
		{
			string a, b;

			if (isvarok(code[1]))
			{
				a = var_value(code[1]);
			}
			else if (code[1] == ":")
				a = nx();
			else
			{
				if (code[1][0] == '\"')
				{
					a = cutstr(code[1]);
				}
				else
					a = code[1];
			}

			if (isvarok(code[2]))
			{
				b = var_value(code[2]);
			}
			else if (code[2] == ":")
				b = nx();
			else
			{
				if (code[1][0] == '\"')
				{
					b = cutstr(code[1]);
				}
				else
					b = code[1];
			}

			return to_string(a == b);
		}
		else if (func == "clear")
		{
			system("clear");
		}
		else if (func == "&")
		{
			string ans = "";

			if (code.size() < 3)
				err(14);

			rep(i, code.size())
			{
				if (i == 0)
					continue;

				string arg = code[i];
				if (arg == "")
					continue;

				if (isstring(arg))
				{
					ans += cutstr(arg);
				}
				else if (isvarok(arg))
				{
					ans += var_value(arg);
				}
				else if (arg == ":")
				{
					err(15);
				}
				else
				{
					err(2);
				}
			}

			return ans;
		}
		else if (func == "break")
		{
			if (inc_code == 0 && inc_now == 0)
				err(16);

			if (inc_code == inc_now)
			{
				inc_now++;
				runcode = false;
			}
		}
		else
		{
			if (!op_funcskip && func != "" && func[0] >= '0')
			{
				if (inc_now == inc_code)
					errorlog(line, linenum, 1);
			}
		}
	}
	else
	{
		if (func == "end")
		{
			if (code[1] == "if")
			{
				if (runcode)
				{
					inc_now--;
					inc_code--;
				}
				else
				{
					inc_now--;
				}
			}
		}
		else if (func == "else")
		{
			if (runcode)
			{
				inc_now--;
				inc_code--;
			}
			else
			{
				inc_now--;
			}

			runcode = !runcode;

			if (runcode)
			{
				inc_now++;
				inc_code++;
			}
			else
				inc_now++;
		}
		else if (func == "if")
		{
			if (isvarok(code[1]))
			{
				runcode = stob(var_value(code[1]));
			}
			else if (code[1] == ":")
				runcode = stob(nx());
			else
			{
				runcode = stob(code[1]);
			}

			if (runcode)
			{
				inc_now++;
				inc_code++;
			}
			else
				inc_now++;
		}
	}

	return "";
}

inline string nx()
{
	return aqua(lines[linenume + 1], lines, linenume + 1);
}

int main(int argc, char const *argv[])
{

#pragma region Aqua System Variables

	var_bool["true"] = true;
	var_bool["false"] = false;
	var_int["null"] = (int)NULL;
	var_double["pi"] = acos(-1);
	var_int["api_version"] = 20230204;
	var_bool["api_systrue"] = true;
	var_bool["api_sysfalse"] = false;

#pragma endregion

	if (argc == 1 || argc > 2 || argv[1] == "--help")
	{
		co("----------------------------------------------------------------------");
		cou("Welcome to Aqua For ");

		// OS

		bool os_win64 = false;

#ifdef _WIN64
		cou("Windows 64bit");
		var_string["api_os"] = "win64";
		os_win64 = true;
#endif

#ifdef _WIN32
		if (!os_win64)
		{
			cou("Windows 32bit");
			var_string["api_os"] = "win32";
		}
#endif

#if defined(__unix) || defined(__unix__)
		cou("UNIX");
		var_string["api_os"] = "unix";
#endif

		co("!");
		co("\nAqua helps to solve a very small problem");
		co("Let's specify the Aqua script as the first argument!");
		co("----------------------------------------------------------------------");
		co("\nTo exit, press Enter key.");
		int i = getchar();

		return 0;
	}

	ifstream file;
	file.open(argv[1]);

	string read_file;

	while (getline(file, read_file))
	{
		lines.push_back(read_file);
	}

	lines = incident(lines);

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
		int aqua_get;
		aqua_get = getchar();
	}

	// Program End

	return 0;
}
