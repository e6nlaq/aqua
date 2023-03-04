
/*******************************************************

			  aqua.cpp

	Created at: Jan 7, 2023, 7:41 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

// やあ!このソースコードを見てるそこの君!
// この難解なコードを読み解けるかな((

// Include
#include "./lib/all.h"
using namespace std; // std?なにそれ

// Macro
#define co(x) cout << (x) << "\n"
#define cou(x) cout << (x)
#define err(x) errorlog(lines, code_line, (x));
#define all(x) x.begin(), x.end()
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define sn(i) now(setting, (i));

// optionの変数
bool op_funcskip = false;
bool op_stylereset = true;
bool op_end_anykey = false;
bool op_over_var = false;
bool st_using_yes = false;
bool us_shell = false;

// 変数
map<string, int> var_int;
map<string, string> var_string;
map<string, bool> var_bool;
map<string, double> var_double;
map<string, int64_t> var_int64;
map<string, ll> var_ll;
map<string, ll> label_list;
vector<string> lines;
vector<int> sett;
int linenume;
bool runcode = true;
int inc_now = 0;
int inc_code = 0;
bool iswin = true;
ll code_line = 0;
ll forever_line = -1;
const string version = "1.5.0 Preview";

// 事前宣言
inline void errorlog(vector<string> line, int linenum, int errorcode);
inline string nx();
inline void aqua_setting();
inline void cscle();

inline bool dup_varname(string name)
{
	if (var_int.count(name) || var_string.count(name) || var_bool.count(name) || var_double.count(name) || var_int64.count(name) || var_ll.count(name))
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
	else if (var_int64.count(name))
	{
		return 5;
	}
	else if (var_ll.count(name))
	{
		return 6;
	}
	else
	{
		return 0;
	}
}

inline bool m_numt(string name)
{
	const int tmp = var_search(name);
	return (tmp == 1 || tmp == 4 || tmp == 5 || tmp == 6);
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
		break;

	case 5:
		return to_string(var_int64[name]);
		break;

	case 6:
		return to_string(var_ll[name]);
		break;

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

	case 21:
		co("No access rights");
		break;

	case 22:
		co("Duplicate labels");
		break;

	case 23:
		co("Invalid label name");
		break;

	case 24:
		co("nonexistent label");
		break;

	case 25:
		co("Decimals not available");
		break;

	case 26:
		co("The value must be smaller on the left.");
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

	// エラーの周りの行を表示するやつ
	// なんて親切((
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

inline void usinglog(int id)
{
	// usingのやつ
	string ans = "";
	if (!st_using_yes)
	{
		cscle();

		co("-----------------------------------------------------------------------");
		co("A request was received from this Aqua script.");
		co("By accepting this request, the following will become available\n");

		switch (id)
		{
		case 1:
			co("Shell");
			co("All operations on this OS and PC");
			break;
		}

		co("\nAre you sure you want to do this? (Y/n)");
		cou("> ");

		cin >> ans;
		transform(all(ans), ans.begin(), ::tolower); // StackOverflow最強!
	}

	if (st_using_yes || ans == "y" || ans == "yes")
	{
		switch (id)
		{
		case 1:
			us_shell = true;
		}
	}

	if (!st_using_yes)
		cscle();
}

inline string f_math(int id, string s, string t)
{

	// いろんな関数が使ってるやつ

	ld a, b;

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
			return to_string((ll)a % (ll)b);
		else
			err(11);
		break;

	case 6:
		return to_string(pow(a, b));
		break;

	case 7:
		return to_string(a > b);
		break;

	case 8:
		return to_string(a < b);

		break;

	case 9:
		return to_string(a <= b);
		break;

	case 10:
		return to_string(a >= b);
		break;

	case 11:
		return to_string(a_gcd((ll)a, (ll)b));
		break;

	case 12:
		return to_string(a_lcm((ll)a, (ll)b));
		break;

	case 13:
		return to_string((ll)a & ll(b));
		break;

	case 14:
		return to_string((ll)a | ll(b));
		break;

	case 15:
		return to_string((ll)a ^ ll(b));
		break;

	case 16: // rand
		if (a > b)
		{
			swap(a, b);
		}

		return to_string(rand() % ((ll)b - (ll)a + 1LL) + (ll)a);
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

	case 6:
		return to_string(is_prime((ll)a));
		break;

	case 7:
		return to_string(!a);
		break;
	}

	return "";
}

inline string aqua(string script, vector<string> line, int linenum)
{
	// スペースごとに変換
	vector<string> code = scriptcut(script);
	string func = code[0];

	ll argn = code.size() - 1;

	// 実行時エラー(忌まわしきSEGMENTATION FAULT)防止
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

			// 大欠陥じゃねえかこれ
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
				else if (code[1] == "over_var")
				{
					op_over_var = stob(code[2]);
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
			// 何もない。何もしない。
		}
		else if (func == "exit")
		{

			// exit. そのまま。

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

			// 使う人おるの?

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

			// 新しい型追加するときめんどくさい(((

			if (isvarok(code[2]))
			{
				if (dup_varname(code[2]) || op_over_var)
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
					else if (code[1] == "int64_t")
					{
						var_int64[code[2]] = 0;
					}
					else if (code[1] == "longlong" || code[1] == "ll")
					{
						var_ll[code[2]] = 0ll;
					}
					else
					{
						err(6); // 存在しない型の時
					}
				}
				else
				{
					err(9); // 変数が重複しているとき。optionで制御可能
				}
			}
			else
			{
				err(8); // やべえ名前の時
			}
		}
		else if (func == "ln")
		{

			// 改行。エスケープシーケンス対応したから多分もう使わない。

			if (code[1] == "")
			{
				cout << "\n";
			}
			else
			{
				for (int i = 0; i < stoi(code[1]); i++) // rep使えよ
					cout << "\n";
			}
		}
		else if (func == "style")
		{

			// \033のやつ。意味わからん

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

			// 入力。型追加するときに忘れんな

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

			case 5:
				cin >> var_int64[code[1]];
				break;

			case 6:
				cin >> var_ll[code[1]];
				break;

			default:
				err(10);
				break;
			}
		}
		else if (func == "set")
		{

			// 変数の中身を変更。上と同様

			switch (var_search(code[1]))
			{
			case 1:
				if (isvarok(code[2]))
					var_int[code[1]] = stoi(var_value(code[2]));
				else if (code[2] == ":")
					var_int[code[1]] = stoi(nx());
				else if (isstring(code[2]))
				{
					err(20);
				}
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
				else if (isstring(code[2]))
				{
					err(20);
				}
				else
					var_bool[code[1]] = stob(var_value(code[2]));

			case 4:
				if (isvarok(code[2]))
					var_double[code[1]] = stod(var_value(code[2]));
				else if (code[2] == ":")
					var_double[code[1]] = stod(nx());
				else if (isstring(code[2]))
				{
					err(20);
				}
				else
					var_double[code[1]] = stod(code[2]);
				break;

			case 5:
				if (isvarok(code[2]))
					var_int64[code[1]] = stoll(var_value(code[2]));
				else if (code[2] == ":")
					var_int64[code[1]] = stoll(nx());
				else if (isstring(code[2]))
				{
					err(20);
				}
				else
					var_int64[code[1]] = stoll(code[2]);
				break;

			case 6:
				if (isvarok(code[2]))
					var_ll[code[1]] = stoll(var_value(code[2]));
				else if (code[2] == ":")
					var_ll[code[1]] = stoll(nx());
				else if (isstring(code[2]))
				{
					err(20);
				}
				else
					var_ll[code[1]] = stoll(code[2]);
				break;

			default:
				err(10);
				break;
			}
		}
		else if (func == "flush")
		{

			// いるか?

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
			return f_math(13, code[1], code[2]);
		}
		else if (func == "or")
		{
			return f_math(14, code[1], code[2]);
		}
		else if (func == "xor")
		{
			return f_math(15, code[1], code[2]);
		}
		else if (func == "not" || func == "!")
		{
			return f_trig(7, code[1]);
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
			cscle();
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

			if (!isint(code[1]))
			{
				// あ～ね。ラベル系ね。
				if (label_list.count(code[1]))
				{
					// あ～おｋ、そのラベルね
					code_line = label_list[code[1]];
				}
				else
				{
					// そんなラベルねえよ。先にあるんじゃないの?
					auto itr = find(all(lines), "label " + code[1]);

					if (itr != lines.end())
					{
						// な～んだ。あるじゃねえか。
						code_line = distance(lines.begin(), itr);
					}
					else
					{
						// マジでねえじゃねえか! おい! エラーぶん投げるぞ!
						err(24);
					}
				}
			}
			else if (code[1] == ":")
			{
				// え? next?
				code_line = stoll(nx());
				code_line -= 2;
			}
			else
			{
				// 数値直接指定????まじ????
				if (stoll(code[1]) < 1)
					err(17);
				code_line = stoll(code[1]);

				code_line -= 2;
			}
		}
		else if (func == "^")
		{
			return f_math(6, code[1], code[2]);
		}
		else if (func == "sh")
		{

			if (!us_shell)
				err(21);

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
		else if (func == ">")
		{
			return f_math(7, code[1], code[2]);
		}
		else if (func == "<")
		{
			return f_math(8, code[1], code[2]);
		}
		else if (func == "<=")
		{
			return f_math(9, code[1], code[2]);
		}
		else if (func == ">=")
		{
			return f_math(10, code[1], code[2]);
		}
		else if (func == "using")
		{
			if (code[1] == "sh" || code[1] == "shell")
			{
				usinglog(1);
			}
			else
			{
				err(2);
			}
		}
		else if (func == "label")
		{

			// 形式検査
			if (code[1] == "")
				err(2);
			if (code[1] == ":")
				err(15);
			if (!isvarok(code[1]))
				err(23);

			if (label_list.count(code[1]))
			{
				err(22);
			}
			else
			{
				label_list[code[1]] = code_line;
			}
		}
		else if (func == "sum")
		{
			// 合計求めるよ～

			// 出力だよ～ 小数とかも考えてlong doubleだよ～
			ld ans = 0;

			// 配列内全部チェックするよ～
			rep(i, argn)
			{

				// 仮置き場～
				string s = code[i + 1];

				if (isvarok(s)) // これは変数?
				{
					try
					{
						ans += stold(var_value(s));
					}
					catch (const exception &e)
					{
						err(20);
					}
				}
				else if (isstring(s)) // えっ、string!?
				{
					// stringはだめ!エラー投げる!
					err(20);
				}
				else if (s == ":") // nextかぁ...
				{
					try
					{
						ans += stold(nx());
					}
					catch (const exception &e)
					{
						// まじで!?
						err(20);
					}
				}
				else
				{ // どれも違う?

					// じゃあ数値でしょ!一応tryしとくけど...
					try
					{
						ans += stold(s);
					}
					catch (const exception &e)
					{
						// えぇ...
						err(20);
					}
				}
			}

			// 全部終わり! じゃあね!
			return to_string(ans);
		}
		else if (func == "gcd")
		{
			if (argn != 2)
				err(2);

			return f_math(11, code[1], code[2]);
		}
		else if (func == "lcm")
		{
			if (argn != 2)
				err(2);

			return f_math(12, code[1], code[2]);
		}
		else if (func == "is_prime")
		{
			return f_trig(6, code[1]);
		}
		else if (func == "rand")
		{
			// code[1]~code[2]までの乱数
			return f_math(16, code[1], code[2]);
		}
		else if (func == "set_rand")
		{
			srand(time(NULL));
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
	else // インシデントが違うとき
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

	// 未定義だよ～
	return "undefined";
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
	var_string["api_version"] = version;
	var_ll["api_randmax"] = RAND_MAX;

#pragma endregion

	// 引数をvector<string>に変換
	vector<string> args(argv, argv + argc);

	// 何もオプションがない場合

	if (argc == 1)
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

	// コマンド引数適用
	if (count(all(args), "--no-style"))
		sett = {0};
	else
		sett = {1};

	if (count(all(args), "--yes"))
		st_using_yes = true;
	else
		st_using_yes = false;

	// ファイル読み込み
	ifstream file;
	file.open(args[1]);

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

	// しゅ～りょ～

	return 0;
}

int ans;

inline void inp()
{
	cou("\n> ");
	cin >> ans;
}
