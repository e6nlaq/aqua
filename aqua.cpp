
/*******************************************************

			  aqua.cpp

	Created at: Jan 7, 2023, 7:41 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under GNU General Public License v3.0.

*******************************************************/

// Include
#include "./lib/all.h"
using namespace std;

// Using Type
using ll = long long;
using ld = long double;

// Macro
#define co(x) cout << (x) << "\n"
#define cou(x) cout << (x)
#define err(x) errorlog(lines, code_line, (x));
#define all(x) x.begin(), x.end()
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define sn(i) now(setting, (i));

// Variant (Option)
bool op_funcskip = false;
bool op_stylereset = true;
bool op_end_anykey = false;

// Variant
map<string, int> var_int;
map<string, string> var_string;
map<string, bool> var_bool;
map<string, double> var_double;
vector<string> lines;
vector<int> sett;
int linenume;
bool runcode = true;
int inc_now = 0;
int inc_code = 0;
bool iswin = true;
ll code_line = 0;
ll forever_line = -1;

// Advance Declaration
inline void errorlog(vector<string> line, int linenum, int errorcode);
inline string nx();
inline void aqua_setting();

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

// エラー
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

	case 17:
		co("goto must be greater than or equal to 1");
		break;

	case 18:
		co("This is only valid within the FOREVER");
		break;

	case 19:
		co("I can't find a sentence that fits the end");
		break;

	case 20:
		co("Strings are invalid for this function.");
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

	if (sett[0])
	{
		if (linenum > 1)
			co(to_string(linenum - 1) + "| " + line[linenum - 2]);
		if (linenum > 0)
			co(to_string(linenum) + "| " + line[linenum - 1]);

		co(to_string(linenum + 1) + "| \033[1m\033[31m\033[4m" + line[linenum] + "\033[m");
		if (linenum != line.size() - 1)
			co(to_string(linenum + 2) + "| " + line[linenum + 1]);

		if (linenum + 2 < line.size())
			co(to_string(linenum + 3) + "| " + line[linenum + 2]);
	}
	else
	{
		co(to_string(linenum + 1) + "| " + line[linenum]);
	}
	exit(-1);

#pragma endregion
}

inline string f_math(int id, string s, string t)
{

	ll a, b;

	if (isstring(s) || isstring(t))
		err(20);

	if (isvarok(s))
		a = stold(var_value(s));
	else if (s == ":")
		a = stold(nx());
	else
		a = stold(s);

	if (isvarok(t))
		b = stold(var_value(t));
	else if (t == ":")
		b = stold(nx());
	else
		b = stold(t);

	switch (id)
	{
	case 1:
		return to_string(a + b);
		break;

	case 2:
		return to_string(a - b);
		break;

	case 3:
		return to_string(a * b);
		break;

	case 4:
		if (b != 0)
			return to_string(a / b);
		else
			err(11);
		break;

	case 5:
		if (b != 0)
			return to_string(a % b);
		else
			err(11);
		break;

	case 6:
		return to_string(pow(a, b));
		break;
	}

	return "";
}

inline string f_trig(int id, string s)
{
	ld a;
	if (isvarok(s))
		a = stold(var_value(s));
	else if (s == ":")
		a = stold(nx());
	else
		a = stold(s);

	switch (id)
	{
	case 1:
		return to_string(abs(a));
		break;

	case 2:
		if (a < 0)
			err(12);
		return to_string(sqrtl(a));
		break;

	case 3:
		return to_string(sinl(a));
		break;

	case 4:
		return to_string(cosl(a));
		break;

	case 5:
		return to_string(tanl(a));
		break;
	}

	return "";
}

inline string aqua(string script, vector<string> line, int linenum)
{
	vector<string> code = scriptcut(script);
	string func = code[0];

	// 実行時エラー防止
	for (int i = 0; i < 10; i++)
	{
		code.push_back("");
	}

	// インシデントチェック
	if (inc_code == inc_now)
	{
		// 以下、関数記述
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
			if (sett[0])
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
			return f_math(1, code[1], code[2]);
		}
		else if (func == "-")
		{
			return f_math(2, code[1], code[2]);
		}
		else if (func == "*")
		{
			return f_math(3, code[1], code[2]);
		}
		else if (func == "/")
		{
			return f_math(4, code[1], code[2]);
		}
		else if (func == "%")
		{
			return f_math(5, code[1], code[2]);
		}
		else if (func == "abs")
		{
			return f_trig(1, code[1]);
		}
		else if (func == "sqrt")
		{
			return f_trig(2, code[1]);
		}
		else if (func == "sin")
		{
			return f_trig(3, code[1]);
		}
		else if (func == "cos")
		{
			return f_trig(4, code[1]);
		}
		else if (func == "tan")
		{
			return f_trig(5, code[1]);
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

			// インシデントチェック
			if (inc_now == 0 && inc_code == 0)
				err(19);

			if (code[1] == "forever")
			{
				if (forever_line != -1)
				{
					code_line = forever_line;
					// inc_now--;
					// inc_code--;
				}
				else
				{
					err(18);
				}
			}
			else if (code[1] == "if")
			{
				inc_now--;
				inc_code--;
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
		else if (func == "goto")
		{
			if (stoll(code[1]) < 1)
				err(17);

			if (isvarok(code[1]))
			{
				code_line = stoll(var_value(code[1]));
			}
			else if (code[1] == ":")
			{
				code_line = stoll(nx());
			}
			else
			{
				code_line = stoll(code[1]);
			}

			code_line -= 2;
		}
		else if (func == "^")
		{
			return f_math(6, code[1], code[2]);
		}
		else if (func == "sh")
		{
			if (isvarok(code[1]))
			{
				system(var_value(code[1]).c_str());
			}
			else if (isstring(code[1]))
			{
				system(cutstr(code[1]).c_str());
			}
			else if (code[1] == ":")
			{
				system(nx().c_str());
			}
			else
			{
				err(2);
			}
		}
		else if (func == "forever")
		{
			forever_line = code_line;
			inc_code++;
			inc_now++;
		}
		else if (func == "fibz")
		{
			ll a = 0;

			if (isstring(code[1]))
			{
				err(20);
			}
			else if (isvarok(code[1]))
			{
				a = stoll(var_value(code[1]));
			}
			else
			{
				a = stoll(code[1]);
			}

			if (a % 3 == 0 && a % 5 == 0)
				return "FizzBuzz";
			else if (a % 3 == 0)
				return "Fizz";
			else if (a % 5 == 0)
				return "Buzz";
			else
				return to_string(a);
		}
		else
		{
			if (!op_funcskip && func != "" && func[0] >= '0')
			{
				if (inc_now == inc_code)
				{
					co(func.size());
					errorlog(line, linenum, 1);
				}
			}
		}
	}
	else
	{
		if (func == "end")
		{

			if (code[1] == "if")
			{
				// インシデントチェック
				if (inc_now == 0 && inc_code == 0)
					err(19);

				inc_now--;
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
	string ans;
	code_line++;
	ans = aqua(lines[code_line], lines, code_line);
	code_line--;
	return ans;
}

inline void cscle()
{
	if (iswin)
		system("cls");
	else
		system("clear");
}

int main(int argc, char const *argv[])
{

	// Aqua基本処理系

#pragma region Aqua System Variables

	var_bool["true"] = true;
	var_bool["false"] = false;
	var_int["null"] = (int)NULL;
	var_double["pi"] = acos(-1);
	var_int["api_version"] = 20230204;
	var_bool["api_systrue"] = true;
	var_bool["api_sysfalse"] = false;

#pragma endregion

	// 何もオプションがない場合

	if (argc == 1 || argc > 2)
	{
		co("----------------------------------------------------------------------");
		cou("Welcome to Aqua For ");

		// OS

		bool os_win64 = false;

#ifdef _WIN64
		cou("Windows 64bit");
		var_string["api_os"] = "win64";
		os_win64 = true;
		iswin = true;
#endif

#ifdef _WIN32
		if (!os_win64)
		{
			cou("Windows 32bit");
			var_string["api_os"] = "win32";
		}
		iswin = true;
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

	// UNIXだったらfalse
#if defined(__unix) || defined(__unix__)
	iswin = false;
#endif

	string arg1 = argv[1];

	// 	if (arg1 == "--install")
	// 	{

	// 		if (iswin)
	// 		{
	// #include <direct.h>
	// 			_mkdir("C:\\Aqua\\");
	// 		}
	// 		else
	// 		{
	// #include <sys/stat.h>
	// 			mkdir("/usr/program/aqua");
	// 		}
	// 	}

	// 	if (arg1 == "--setting" || arg1 == "--s")
	// 	{
	// 		aqua_setting();
	// 	}

	// ifstream settingfile;
	// settingfile.open("./setting/setting.txt");
	// string reads;

	// while (getline(settingfile, reads))
	// {
	// 	sett.push_back(stoi(reads));
	// }

	// settingfile.close();

	// TODO: Aqua Setting無効化のため
	sett = {1};

	// ファイル読み込み
	ifstream file;
	file.open(arg1);

	string read_file;

	while (getline(file, read_file))
	{
		lines.push_back(read_file);
	}

	// インシデント対応
	lines = incident(lines);

	// Aqua実行
	for (code_line = 0; code_line < lines.size(); code_line++)
	{
		linenume = code_line;
		aqua(lines[code_line], lines, code_line);
	}

	if (op_stylereset && sett[0])
		cou("\033[m");

	if (op_end_anykey)
	{
		co("\nThe program was successfully completed.");
		co("To exit, press Enter key.");
		int aqua_get;
		aqua_get = getchar();
	}

	// if (op_stylereset && sett[0])
	// 	cou("\033[m");

	// Program End

	return 0;
}

int ans;

inline void inp()
{
	cou("\n> ");
	cin >> ans;
}

inline void aqua_setting()
{
	// Aqua Setting

	cou("Aqua Setting> File is open...    ");

	vector<string> settingf;
	vector<string> setting;
	ifstream settingfile;
	settingfile.open("./setting/setting.txt");
	string reads;

	while (getline(settingfile, reads))
	{
		settingf.push_back(reads);
	}

	setting = settingf;

	settingfile.close();

	co("OK");

	cscle();

	co("----------------------------------------------");
	co("Welcome to Aqua Setting");
	co("Please select your desired setting.");
	co("----------------------------------------------\n");

	while (true)
	{
		co("0: Exit");
		co("1: Environment settings");
		co("2: Reset");

		inp();
		cscle();

		switch (ans)
		{
		case 0:
			if (setting != settingf)
			{
				cscle();
				co("Settings are not saved.");
				co("Do you want to save it?");

				co("0: Don't Save Close");
				co("1: Save and Close");

				inp();

				if (ans)
				{
					ofstream w_setting;
					w_setting.open("./setting/setting.txt", ios::out);
					w_setting << vtos(setting);
					w_setting.close();
				}
			}

			cscle();
			exit(0);

			break;

		case 1:
			co("0: go back");
			co("1: Style");

			inp();
			cscle();

			switch (ans)
			{
			case 0:
				break;

			case 1:

				co("Style");
				co("Enable or select ASCII style in Aqua.");

				sn(0);

				co("0: Disable");
				co("1: Enable (Specified value)");

				inp();

				if (ans)
					setting[0] = "1";
				else
					setting[0] = "0";

				break;
			}

			break;

		case 2:
			co("0: go back");
			co("1: Setting");

			inp();
			cscle();

			switch (ans)
			{
			case 0:
				break;

			case 1:
				co("Restore settings to default values");
				co("Resets the setting to the specified value.");
				co("*All settings are discarded.");

				co("0: No");
				co("1: Yes");

				inp();

				if (ans)
				{
					setting = {"1"};
				}

				break;
			}
		}

		cscle();
	}
}
