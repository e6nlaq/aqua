
/*******************************************************

			  aqua.cpp

	Created at: Jan 7, 2023, 7:41 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

// All comments are written in Japanese.
// Please understand.

// インクルード
#include "./lib/all.h"
using namespace std;

// マクロ
#define co(x) cout << (x) << "\n"
#define cou(x) cout << (x)
#define err(x) errorlog(lines, code_line, (x));
#define all(x) x.begin(), x.end()
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define sn(i) now(setting, (i));
#define jnx() js_next(line, linenum)

// optionとかの変数
bool op_funcskip = false;
bool op_stylereset = true;
bool op_end_anykey = false;
bool op_over_var = false;
bool st_using_yes = false;
bool st_style = true;
bool us_shell = false;
bool us_net = false;
bool us_clip = false;
bool tooljs = false;
bool toolpy = false;

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
vector<ll> while_line;
vector<ll> until_line;
int linenume;
bool runcode = true;
int inc_now = 0;
int inc_code = 0;
bool iswin = true;
ll code_line = 0;
ll forever_line = -1;
const string version = "1.5.0";
ll if_count = 0;
ll while_count = 0;
ll until_count = 0;
int isnx = 0;
int isjnx = 0;

// 事前宣言
inline void errorlog(vector<string> line, int linenum, int errorcode);
inline string nx();
inline void aqua_setting();
inline string to_js(string script, vector<string> line, int linenum);

inline void warn(string s)
{
	if (st_style)
	{
		cout << "\033[33m\033[1mWarning\033[m: ";
	}
	else
	{
		cout << "Warning: ";
	}

	cout << s << "\n";
}

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

	case 27:
		co("Variables of invalid type");
		break;

	case 28:
		co("The length of the string must be 1.");
		break;

	case 29:
		co("Numerical values are invalid.");
		break;

	case 30:
		co("Out of Range");
		break;

	case 31:
		co("There is no if corresponding to this end if.");
		break;

	case 32:
		co("There is no corresponding while for this end while.");
		break;

	case 33:
		co("There is no if corresponding to this else.");
		break;

	case 34:
		co("There is no corresponding while for this end until.");
		break;

	case 35:
		co("Aqua Tools does not exist");
		break;

	case 36:
		co("Requires Aqua Tools to run.");
		break;

	case 37:
		co("In JavaScript, you can use `http://... ` is not supported.");
		break;

	case 38:
		co("Spaces are not allowed at the end of file or folder names.");
		break;

	case 39:
		co("Python is required for execution.");
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
	exit(1);

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

		case 2:
			co("Network");
			co("Connect to the Internet and retrieve information");
			break;

		case 3:
			co("Clipboard");
			co("Writing to and reading from the clipboard");
			break;
		}

		co("\nAre you sure you want to do this? (Y/n)");
		cou("> ");

		cin >> ans;
		transform(all(ans), ans.begin(), ::tolower); // StackOverflowから
	}

	if (st_using_yes || ans == "y" || ans == "yes")
	{
		switch (id)
		{
		case 1:
			us_shell = true;
			break;

		case 2:
			us_net = true;
			break;

		case 3:
			us_clip = true;
			break;
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
	case 1: // +
		return to_string(a + b);
		break;

	case 2: // -
		return to_string(a - b);
		break;

	case 3: // *
		return to_string(a * b);
		break;

	case 4: // /
		if (b != 0)
			return to_string(a / b);
		else
			err(11);
		break;

	case 5: // %
		if (b != 0)
			return to_string((ll)a % (ll)b);
		else
			err(11);
		break;

	case 6: // ^
		return to_string(pow(a, b));
		break;

	case 7: // >
		return to_string(a > b);
		break;

	case 8: // <
		return to_string(a < b);

		break;

	case 9: // <=
		return to_string(a <= b);
		break;

	case 10: // >=
		return to_string(a >= b);
		break;

	case 11: // gcd
		return to_string(a_gcd((ll)a, (ll)b));
		break;

	case 12: // lcm
		return to_string(a_lcm((ll)a, (ll)b));
		break;

	case 13: // and
		return to_string((ll)a & ll(b));
		break;

	case 14: // or
		return to_string((ll)a | ll(b));
		break;

	case 15: // xor
		return to_string((ll)a ^ ll(b));
		break;

	case 16: // rand
		if (a > b)
		{
			swap(a, b);
		}

		// rand_r使えって言われるけどVC++で使えないから却下
		return to_string(rand() % ((ll)b - (ll)a + 1LL) + (ll)a);
		break;

	case 17: // lsh
		return to_string((ll)a << (ll)b);
		break;

	case 18: // rsh
		return to_string((ll)a >> (ll)b);
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

	case 8:
		string k = {(char)a};
		return k;
		break;
	}

	return "";
}

inline bool to_bool(string s)
{
	bool ret;
	if (isvarok(s))
	{
		ret = stob(var_value(s));
	}
	else if (s == ":")
		ret = stob(nx());
	else
	{
		ret = stob(s);
	}

	return ret;
}

inline ld to_num(string s)
{
	ld ret;
	if (isvarok(s))
	{
		ret = stold(var_value(s));
	}
	else if (s == ":")
		ret = stold(nx());
	else
	{
		try
		{
			ret = stold(s);
		}
		catch (const std::exception &e)
		{
			err(20);
		}
	}

	return ret;
}

inline string get_str(string s)
{
	string ret;
	if (isvarok(s))
	{
		ret = var_value(s);
	}
	else if (s == ":")
		ret = nx();
	else if (isstring(s))
	{
		ret = cutstr(s);
	}
	else
	{
		ret = s;
	}

	return ret;
}

inline string aqua(string script, vector<string> line, int linenum)
{
	// スペースごとに変換
	vector<string> code = scriptcut(script);
	string func = code[0];

	// funcを含まない引数の数
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
			// 全ての始まり。改行なし出力

			if (code[1][0] == '\"')
				out(cutstr(code[1]));
			else if (code[1] == ":")
				out(nx());
			else if (isvarok(code[1]))
			{
				out(var_value(code[1]));
			}
			else
				err(2);
		}
		else if (func == "option")
		{
			// オプション。色々。

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
				err(3);
			}
		}
		else if (func == "outf")
		{
			// 改行付き出力。fついてるけどflushしない

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
			// 終了コード指定可exit

			exit((ll)to_num(code[1]));
		}
		else if (func == "throw")
		{
			// 例外を投げる

			if (code[1] == "")
			{
				err(4);
			}
			else
			{
				err((ll)to_num(code[1]));
			}
		}
		else if (func == "var")
		{
			// 変数宣言

			bool changed = false; // 初期値を自動的に変更したか否か

			if (code[3] == "")
			{
				changed = true;
				code[3] = "0";
			}

			if (isvarok(code[3]))
			{
				code[3] = var_value(code[3]);
			}

			if (isvarok(code[2]))
			{
				if (dup_varname(code[2]) || op_over_var)
				{
					if (code[1] == "int")
					{
						var_int[code[2]] = stoi(code[3]);
					}
					else if (code[1] == "string")
					{
						if (changed)
							var_string[code[2]] = "";
						else
							var_string[code[2]] = cutstr(code[3]);
					}
					else if (code[1] == "bool")
					{
						if (changed)
							var_bool[code[2]] = true;
						else
							var_bool[code[2]] = stob(code[3]);
					}
					else if (code[1] == "double")
					{
						var_double[code[2]] = stod(code[3]);
					}
					else if (code[1] == "int64_t")
					{
						var_int64[code[2]] = stoll(code[3]);
					}
					else if (code[1] == "longlong" || code[1] == "ll")
					{
						var_ll[code[2]] = stoll(code[3]);
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
				for (ll i = 0; i < (ll)to_num(code[1]); i++) // rep使えよ
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
			// 変数の空白区切り入力

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
			// 変数の中身を変更

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
			// 出力をフラッシュ

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

			if_count++;

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
				if_count--;

				if (if_count < 0)
				{
					err(19);
				}

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
			else if (code[1] == "while")
			{
				while_count--;

				if (while_count < 0)
				{
					err(32);
				}

				inc_code--;
				inc_now--;
				code_line = while_line.back() - 1;
				while_line.pop_back();
			}
			else if (code[1] == "until")
			{
				until_count--;

				if (until_count < 0)
				{
					err(32);
				}

				inc_code--;
				inc_now--;
				code_line = until_line.back() - 1;
				until_line.pop_back();
			}
		}
		else if (func == "else")
		{
			if_count++;

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
			// 出力全クリア
			// 動作は環境依存

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
				if (label_list.count(code[1]))
				{
					code_line = label_list[code[1]];
				}
				else
				{
					auto itr = find(all(lines), "label " + code[1]);

					if (itr != lines.end())
					{
						code_line = distance(lines.begin(), itr);
					}
					else
					{
						err(24);
					}
				}
			}
			else if (code[1] == ":")
			{
				code_line = stoll(nx());
				code_line -= 2;
			}
			else
			{
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
			// 高度なことをするのを宣言する
			// モジュールとはまた違う
			// 使用するたびに確認入る(aqua-toolsを除く)
			if (code[1] == "sh" || code[1] == "shell")
			{
				usinglog(1);
			}
			else if (code[1] == "tools")
			{
				if (tool_ok())
				{
					tooljs = true;
					toolpy = true;
				}
				else
				{
					err(35);
				}
			}
			else if (code[1] == "tools-js")
			{
				if (tool_ok())
				{
					tooljs = true;
				}
				else
				{
					err(35);
				}
			}
			else if (code[1] == "tools-py")
			{
				if (tool_ok())
				{
					toolpy = true;
				}
				else
				{
					err(35);
				}
			}
			else if (code[1] == "network" || code[1] == "net")
			{
				usinglog(2);
			}
			else if (code[1] == "clipboard" || code[1] == "clip")
			{
				usinglog(3);
			}
			else
			{
				err(2);
			}
		}
		else if (func == "label")
		{
			// ラベル
			// gotoと合わせて使用

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
			// 合計

			// 返り値
			ld ans = 0;

			// 全探索
			rep(i, argn)
			{

				// 仮
				string s = code[i + 1];

				if (isvarok(s)) // 変数の場合
				{
					try
					{
						ans += stold(var_value(s));
					}
					catch (const exception &e)
					{
						err(20); // stringとかの場合
					}
				}
				else if (isstring(s)) // あからさまにstring("")の場合
				{
					err(20);
				}
				else if (s == ":")
				{
					try
					{
						ans += stold(nx());
					}
					catch (const exception &e)
					{
						err(20); // 一応
					}
				}
				else
				{
					// 多分数値だけど一応try
					try
					{
						ans += stold(s);
					}
					catch (const exception &e)
					{
						err(20); // 察し((
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
			srand(time(NULL)); // 魔法の言葉
		}
		else if (func == "ord")
		{
			// Pythonのordと一緒

			string s = "";

			if (isstring(code[1]))
			{
				s = cutstr(code[1]);
			}
			else if (isvarok(code[1]))
			{
				switch (var_search(code[1]))
				{
				case 3:
					s = var_value(code[1]);
					break;

				case 0:
					err(10);
					break;

				default:
					err(27);
					break;
				}
			}
			else if (code[1] == ":")
			{
				s = nx();
			}
			else
			{
				err(2);
			}

			if (s.size() != 1)
			{
				err(28);
			}

			return to_string((int)s[0]);
		}
		else if (func == "chr")
		{
			return f_trig(8, code[1]);
		}
		else if (func == "at")
		{
			ll index = 0;
			if (isstring(code[2]))
			{
				err(20);
			}
			else if (isvarok(code[2]))
			{
				switch (var_search(code[2]))
				{
				case 2:
				case 3:
				case 4:
					err(27);
					break;

				case 0:
					err(10);
					break;

				default:
					index = stoll(var_value(code[2]));
					break;
				}
			}
			else if (isint(code[2]))
			{
				index = stoll(code[2]);
			}
			else if (code[2] == ":")
			{
				index = stoll(nx());
			}
			else
			{
				err(2);
			}

			string s = "";

			if (isstring(code[1]))
			{
				s = cutstr(code[1]);
			}
			else if (isint(code[1]))
			{
				err(29);
			}
			else if (isvarok(code[1]))
			{
				switch (var_search(code[1]))
				{
				case 2:
					s = var_value(code[1]);
					break;

				case 0:
					err(10);
					break;

				default:
					err(27);
					break;
				}
			}
			else if (code[1] == ":")
			{
				s = nx();
			}
			else
			{
				err(2);
			}

			if (index > -1 && index < s.size())
			{
				string tmp = {s.at(index)};
				return tmp;
			}
			else
			{
				err(30);
			}
		}
		else if (func == "len")
		{
			// やっぱりPython((

			string s = "";

			if (isstring(code[1]))
			{
				s = cutstr(code[1]);
			}
			else if (isint(code[1]))
			{
				err(29);
			}
			else if (isvarok(code[1]))
			{
				switch (var_search(code[1]))
				{
				case 2:
					s = var_value(code[1]);
					break;

				case 0:
					err(10);
					break;

				default:
					err(27);
					break;
				}
			}
			else if (code[1] == ":")
			{
				s = nx();
			}
			else
			{
				err(2);
			}

			return to_string(s.size());
		}
		else if (func == "?")
		{
		}
		else if (func == "while")
		{
			runcode = to_bool(code[1]);
			while_count++;

			if (runcode) // ifのやつを流用
			{
				inc_now++;
				inc_code++;
			}
			else
				inc_now++;

			while_line.push_back(code_line);
		}
		else if (func == "until")
		{
			runcode = !to_bool(code[1]);
			until_count++;

			if (runcode)
			{
				inc_now++;
				inc_code++;
			}
			else
				inc_now++;

			until_line.push_back(code_line);
		}
		else if (func == "getline")
		{
			// 入力を一行受け取ってそれを返す

			string s = "undefined";
			getline(cin, s);
			return s;
		}
		else if (func == "lsh")
		{
			return f_math(17, code[1], code[2]);
		}
		else if (func == "rsh")
		{
			return f_math(18, code[1], code[2]);
		}
		else if (func == "download")
		{
			if (us_net)
			{
				string url = get_str(code[1]), path = get_str(code[2]);

				if (path[path.length() - 1] == ' ')
				{
					err(38);
				}

				if (tooljs)
				{
					if (url.substr(0, 5) == "https")
					{
						run("download.js", code[1], code[2]);
					}
					else if (toolpy)
					{
						run("download.py", code[1], code[2]);
					}
					else
					{
						err(37);
					}
				}
				else if (toolpy)
				{
					run("download.py", code[1], code[2]);
				}
				else
				{
					err(36);
				}
			}
			else
			{
				err(21);
			}
		}
		else if (func == "get_clip")
		{
			if (us_clip)
			{
				if (toolpy)
				{
					run("get_clip.py");
				}
				else if (tooljs)
				{
					err(39);
				}
				else
				{
					err(36);
				}

				return get_return();
			}
			else
			{
				err(21);
			}
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
				if (if_count <= 0)
					err(31);

				if_count--;

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
			else if (code[1] == "while")
			{
				while_count--;

				if (while_count < 0)
				{
					err(32);
				}

				inc_now--;
				while_line.pop_back();
			}
			else if (code[1] == "until")
			{
				until_count--;

				if (until_count < 0)
				{
					err(34);
				}

				inc_now--;
				until_line.pop_back();
			}
		}
		else if (func == "else")
		{
			if_count++;

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

			if_count++;

			if (runcode)
			{
				inc_now++;
				inc_code++;
			}
			else
				inc_now++;
		}
		else if (func == "while")
		{
			while_count++;
			while_line.push_back(code_line);

			inc_now++;
		}
		else if (func == "until")
		{
			until_count++;
			until_line.push_back(code_line);

			inc_now++;
		}
	}

	// 未定義を返す
	return "undefined";
}

inline string js_next(vector<string> line, int linenum)
{
	isjnx++;
	return to_js(line[linenum + 1], line, linenum + 1);
}

// JavaScriptコンパイラ
inline string to_js(string script, vector<string> line, int linenum)
{
	// スペースごとに変換
	vector<string> code = scriptcut(script);
	string func = code[0];
	string ans = "";
	// bool sc = true;

	ll argn = code.size() - 1;

	rep(i, code.size())
	{
		if (code[i] == ":")
			code[i] = jnx();
	}

	// 実行時エラー(忌まわしきSEGMENTATION FAULT)防止
	for (int i = 0; i < 10; i++)
	{
		code.push_back("");
	}

	if (func == "outf")
	{
		ans += "console.log(" + code[1] + ")";
	}
	else if (func == "?" || func == "" || func == "﻿")
	{
		// sc = false;
	}
	else if (func == "out")
	{
		ans += "process.stdout.write(" + code[1] + ")";
	}
	else if (func == "var")
	{
		ans += "var " + code[2];
	}
	else if (func == "set")
	{
		ans += code[1] + " = " + code[2];
	}
	else if (func == "+")
	{
		ans += code[1] + " + " + code[2];
	}
	else if (func == "-")
	{
		ans += code[1] + " - " + code[2];
	}
	else if (func == "*")
	{
		ans += code[1] + " * " + code[2];
	}
	else if (func == "/")
	{
		ans += code[1] + " / " + code[2];
	}
	else if (func == "%")
	{
		ans += code[1] + " % " + code[2];
	}
	else if (func == "^")
	{
		ans += code[1] + " ** " + code[2];
	}
	else if (func == "if")
	{
		ans += "if(" + code[1] + "){";
	}
	else if (func == "else")
	{
		ans += "}else{";
	}
	else if (func == "end")
	{
		ans += "}";
	}
	else if (func == "#" || func == "comment")
	{
		ans += "// ";
		rep(i, argn)
		{
			ans += code[i + 1] + " ";
		}
	}
	else if (func == "!" || func == "not")
	{
		ans += "!" + code[1];
	}
	else if (func == "forever")
	{
		ans += "while(true){";
	}
	else if (func == "break")
	{
		ans += "break";
	}
	else if (func == "style")
	{
		string s = "";

		ans += "process.stdout.write(\"" + s + "\")";
	}
	else
	{
		ans += "// Unknown function " + func;
	}

	return ans;
}

inline string nx()
{
	string ans;
	code_line++;
	ans = aqua(lines[code_line], lines, code_line);
	code_line--;
	isnx++;
	return ans;
}

int main(int argc, char const *argv[])
{
	// Aqua基本処理系

#pragma region Aqua System Variables

	var_bool["true"] = true;
	var_bool["false"] = false;
	var_int["null"] = (int)NULL;
	var_int["nan"] = var_int["NaN"] = (int)NAN;
	var_ll["infinity"] = var_ll["Infinity"] = (ll)INFINITY;
	var_double["pi"] = acos(-1);
	var_int["api_version"] = 20230204;
	var_bool["api_systrue"] = true;
	var_bool["api_sysfalse"] = false;
	var_string["api_version"] = version;
	var_ll["api_randmax"] = RAND_MAX;

#pragma endregion

#if defined(__unix__) || defined(__unix__)
#define LINUX 1
	iswin = false;
#endif

	// 引数をvector<string>に変換
	vector<string> args(argv, argv + argc);

	// 最優先オプション
	if (count(all(args), "--win"))
	{
		if (!iswin)
		{
			iswin = true;
		}
		else
			warn("It is already Windows.");
	}

	if (count(all(args), "--unix"))
	{
		if (iswin)
		{
			iswin = false;
		}
		else
			warn("It is already UNIX.");
	}

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
#ifdef LINUX
	iswin = false;
#endif

	// コマンド引数適用
	if (count(all(args), "--no-style"))
	{
		sett = {0};
		st_style = false;
	}
	else
	{
		sett = {1};
		st_style = true;
	}
	if (count(all(args), "--yes"))
		st_using_yes = true;
	else
		st_using_yes = false;

	// ファイル存在チェック
	FILE *fp = fopen(args[1].c_str(), "r");
	if (fp == NULL)
	{
		if (st_style)
			co("\033[31m\033[1mFatal error\033[m: File does not exist or cannot be opened.");
		else
			co("Fatal error: File does not exist or cannot be opened.");
		exit(-1);
	}
	fclose(fp);

	// ファイル読み込み
	ifstream file;
	file.open(args[1]);

	string read_file;

	while (getline(file, read_file))
	{
#ifdef WINDOWS
		lines.push_back(utf8_to_ansi(read_file));
#else
		lines.push_back(read_file);
#endif
	}

	// インシデント対応
	lines = incident(lines);

	// コンパイラ
	if (count(all(args), "-c") || count(all(args), "--compile"))
	{
		co("----------------------------------------------------------------------");
		co("Aqua JavaScript Compiler v" + version);
		co("Copyright (C) 2023 e6nlaq");
		co("----------------------------------------------------------------------");

		co("Compiling... " + args[1]);

		string jsfile;

		if (argc == 3)
		{
			jsfile = get_filename(args[1]) + ".js";
		}
		else
		{
			jsfile = args[2];
		}

		ofstream js;
		js.open(jsfile, ios::out);

		js << "\n// Created with Aqua JavaScript compiler.\n"
		   << endl;

		for (code_line = 0; code_line < lines.size(); code_line++)
		{
			linenume = code_line;
#ifdef WINDOWS
			js << ansi_to_utf8(to_js(lines[code_line], lines, code_line)) << endl;
#else
			js << to_js(lines[code_line], lines, code_line) << endl;
#endif
			if (isjnx)
			{
				code_line += isjnx;
				isjnx = 0;
			}
		}

		exit(0);
	}

	// Aqua実行
	for (code_line = 0; code_line < lines.size(); code_line++)
	{
		// cout << inc_now << " " << inc_code << endl;
		linenume = code_line;
		aqua(lines[code_line], lines, code_line);

		if (isnx) // :使ったら繰り越し
		{
			code_line += isnx;
			isnx = 0;
		}
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

	// 終了

	return 0;
}

int ans;

inline void inp()
{
	cou("\n>>> ");
	cin >> ans;
}
