
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
bool us_sound = false;
bool tooljs = false;
bool toolpy = false;

// 変数
unordered_map<string, int> var_int;
unordered_map<string, string> var_string;
unordered_map<string, bool> var_bool;
unordered_map<string, double> var_double;
unordered_map<string, int64_t> var_int64;
unordered_map<string, ll> var_ll;
unordered_map<string, unsigned int> var_uint;
unordered_map<string, ll> label_list;
unordered_set<ll> nx_line;
unordered_set<string> const_var = {"true", "false", "True", "False"};
vector<string> lines;
vector<int> sett;
vector<ll> while_line;
vector<ll> until_line;
bool runcode = true;
bool comment = false;
bool iswin = true;
bool clirun = false;
int linenume;
int inc_now = 0;
int inc_code = 0;
int isnx = 0;
int isjnx = 0;
ll code_line = 0;
ll forever_line = -1;
ll if_count = 0;
ll while_count = 0;
ll until_count = 0;
const string version = "1.7.0 Preview 1";
wstring_convert<codecvt_utf8<char32_t>, char32_t> utf32conv;

// 事前宣言
inline void errorlog(vector<string> line, int linenum, int errorcode);
inline string nx();
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
	else if (var_uint.count(name))
	{
		return 7;
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

	case 7:
		return to_string(var_uint[name]);
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
		co("Example Error"); // 未使用
		break;

	case 1:
		co("Invalid function passed."); // 存在しない関数
		break;
	case 2:
		co("Invalid argument."); // 無効な引数
		break;

	case 3:
		co("Invalid option."); // 存在しないoption
		break;

	case 4:
		co("User-defined exception thrown"); // throwエラー
		break;

	case 5:
		co("Invalid error code"); // 無効なエラーコード
		break;

	case 6:
		co("invalid type"); // 無効な型
		break;

	case 7:
		co("Invalid Style"); // 無効なスタイル
		break;

	case 8:
		co("Invalid name"); // 無効な変数名
		break;

	case 9:
		co("Overlapping variables"); // 重複している変数
		break;

	case 10:
		co("Non-existent variable"); // 存在しない変数
		break;

	case 11:
		co("Division by zero is not allowed"); // ゼロ除算
		break;

	case 12:
		co("There is no square root of a negative number"); // 負の数の平方根
		break;

	case 13:
		co("Invalid Variable"); // 無効な変数
		break;

	case 14:
		co("Missing argument"); // 引数が足りない
		break;

	case 15:
		co("You can't use : here."); // 無効な場所の:
		break;

	case 16:
		co("You can't break here."); // 無効な場所のbreak
		break;

	case 17:
		co("goto must be greater than or equal to 1"); // 0以下の行数
		break;

	case 18:
		co("This is only valid within the FOREVER"); // forever無いのにend forever
		break;

	case 19:
		co("I can't find a sentence that fits the end"); // 対応するendがない
		break;

	case 20:
		co("Strings are invalid for this function."); // 引数に文字列
		break;

	case 21:
		co("No access rights"); // アクセス拒否
		break;

	case 22:
		co("Duplicate labels"); // ラベルの重複
		break;

	case 23:
		co("Invalid label name"); // 無効なラベル名
		break;

	case 24:
		co("nonexistent label"); // 存在しないラベル
		break;

	case 25:
		co("Decimals not available"); // 利用できない小数
		break;

	case 26:
		co("The value must be smaller on the left."); // A>Bのとき
		break;

	case 27:
		co("Variables of invalid type"); // 無効な引数の変数の型
		break;

	case 28:
		co("The length of the string must be 1."); // 文字列の長さが1(char)ではないとき
		break;

	case 29:
		co("Numerical values are invalid."); // 数値が無効
		break;

	case 30:
		co("Out of Range"); // 範囲外
		break;

	case 31:
		co("There is no if corresponding to this end if."); // ifがないのにend if
		break;

	case 32:
		co("There is no corresponding while for this end while."); // whileがないのにend while
		break;

	case 33:
		co("There is no if corresponding to this else."); // ifがないのにelse
		break;

	case 34:
		co("There is no corresponding until for this end until."); // untilがないのにend until
		break;

	case 35:
		co("Aqua Tools does not exist"); // Aqua Toolsがない
		break;

	case 36:
		co("Requires Aqua Tools to run."); // Aqua Toolsが必要
		break;

	case 37:
		co("In JavaScript, you can use `http://... ` is not supported."); // Node.jsでhttpでの通信
		break;

	case 38:
		co("Spaces are not allowed at the end of file or folder names."); // ファイルまたはフォルダ名の末尾に空白
		break;

	case 39:
		co("Python is required for execution."); // Pythonが必要
		break;

	case 40:
		co("Node.js is required for execution."); // Node.jsが必要
		break;

	case 41:
		co("C++ runtime error"); // C++実行時エラー
		break;

	case 42:
		co("Negative numbers are not allowed."); // 負の数は使用できません
		break;

	case 43:
		co("Must be a string or array."); // 文字列又は配列である必要があります。
		break;

	case 44:
		co("Argument must be a variable"); // 引数は変数である必要があります
		break;

	case 45:
		co("Initial value of const not set"); // constの初期値未設定
		break;

	case 46:
		co("Change of const.");
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

	if (!clirun)
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

		case 4:
			co("Sound");
			co("Sound reproduction");
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

		case 4:
			us_sound = true;
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
			return to_string(fmodl(a, b));
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

	case 19: // log
		if (a < 0 || b < 0)
			err(12);

		return to_string(log_a(a, b));
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

	u32string k;

	switch (id)
	{
	case 1: // abs
		return to_string(abs(a));
		break;

	case 2: // sqrt
		if (a < 0)
			err(12);
		return to_string(sqrtl(a));
		break;

	case 3: // sin
		return to_string(sinl(a));
		break;

	case 4: // cos
		return to_string(cosl(a));
		break;

	case 5: // tan
		return to_string(tanl(a));
		break;

	case 6: // is_prime
		return to_string(is_prime((ll)a));
		break;

	case 7: // not
		return to_string(!a);
		break;

	case 8: // chr
		k = {(char32_t)a};

#ifdef WINDOWS
		return utf8_to_ansi(utf32conv.to_bytes(k));
#else
		return utf32conv.to_bytes(k);
#endif
		break;

	case 9: // fact
		if (a < 0)
			err(12);

		return to_string(fact((ll)a));
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
	if (code[code.size() - 1].back() == ';')
	{
		code[code.size() - 1] = code[code.size() - 1].substr(0, code[code.size() - 1].size() - 1);
	}
	string func = code[0];

	// funcを含まない引数の数
	ll argn = code.size() - 1;

	// 実行時エラー(忌まわしきSEGMENTATION FAULT)防止
	for (int i = 0; i < 10; i++)
	{
		code.push_back("");
	}

	// 謎のエラー防止
	try
	{
		// インシデントチェック
		if (inc_code == inc_now && !comment)
		{
			// 以下、関数記述
			if (func == "out")
			{
				// 全ての始まり。改行なし出力

				if (isstring(code[1]))
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

				if (code[1] == "")
					exit(0);
				else
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
				bool isconst = false; // 定数か否か

				if (code[3] == "")
				{
					changed = true;
					code[3] = "0";
				}

				if (isvarok(code[3]))
				{
					code[3] = var_value(code[3]);
				}

				if (code[2][0] == '$')
				{
					isconst = true;
					code[2] = code[2].substr(1);
					const_var.insert(code[2]);

					if (changed) // なんで動くのか不明
						err(45);
				}

				if (isvardecok(code[2]))
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
						else if (code[1] == "uint")
						{
							if (stoll(code[3]) < 0)
							{
								err(42);
							}
							else
							{
								var_uint[code[2]] = stoul(code[3]);
							}
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

				if (const_var.count(code[1]))
				{
					err(46);
				}

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

				if (const_var.count(code[1]))
				{
					err(46);
				}

				switch (var_search(code[1]))
				{
				case 1:
					var_int[code[1]] = to_num(code[2]);
					break;

				case 2:
					if (isstring(code[2]))
						var_string[code[1]] = cutstr(code[2]);
					else if (code[2] == ":")
						var_string[code[1]] = nx();
					else
						var_string[code[1]] = var_value(code[2]);
					break;

				case 3:
					var_bool[code[1]] = to_num(code[2]);
					break;

				case 4:
					var_double[code[1]] = to_num(code[2]);
					break;

				case 5:
					var_int64[code[1]] = to_num(code[2]);
					break;

				case 6:
					var_ll[code[1]] = to_num(code[2]);
					break;

				case 7:
					if (stoll(code[2]) < 0)
						err(42);

					var_uint[code[1]] = to_num(code[2]);
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

					if (inc_now == inc_code)
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
			else if (func == "is" || func == "==")
			{
				// 一緒かどうか調べる
				string a, b;

				a = get_str(code[1]);
				b = get_str(code[2]);

				return to_string(a == b);
			}
			else if (func == "nis" || func == "!=")
			{
				// 一緒かどうか調べる
				string a, b;

				a = get_str(code[1]);
				b = get_str(code[2]);

				return to_string(a != b);
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

				rep(i, argn)
				{
					string arg = code[i + 1];

					ans += get_str(arg);
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
				else if (code[1] == "sound")
				{
					usinglog(4);
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

#ifdef WINDOWS
				u32string x = utf32conv.from_bytes(ansi_to_utf8(s));
#else
				u32string x = utf32conv.from_bytes(s);
#endif

				if (x.size() != 1)
				{
					err(28);
				}

				return to_string((int)x[0]);
			}
			else if (func == "chr")
			{
				return f_trig(8, code[1]);
			}
			else if (func == "fact")
			{
				return f_trig(9, code[1]);
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

#ifdef WINDOWS
				u32string at = utf32conv.from_bytes(ansi_to_utf8(s));
#else
				u32string at = utf32conv.from_bytes(s);
#endif
				if (index > -1 && index < at.size())
				{
					// 日本語対応部分
					// WindowsはUTF-8に直してやる
					u32string a = u32string{at[index]};

#ifdef WINDOWS
					return utf8_to_ansi(utf32conv.to_bytes(a));
#else
					return utf32conv.to_bytes(a);
#endif
				}
				else
				{
					err(30);
				}
			}
			else if (func == "len")
			{
				// Pythonみたいに長さはかるやつ

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

#ifdef WINDOWS
				u32string len = utf32conv.from_bytes(ansi_to_utf8(s));
#else
				u32string len = utf32conv.from_bytes(s);
#endif

				return to_string(len.size());
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
			else if (func == "log")
			{
				return f_math(19, code[1], code[2]);
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
			else if (func == "copy_clip")
			{
				if (us_clip)
				{
					if (toolpy)
					{
						run("copy_clip.py", get_str(code[1]));
					}
					else if (tooljs)
					{
						err(39);
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
			else if (func == "play")
			{
				if (us_sound)
				{
					if (toolpy)
					{
						run("play.py", get_str(code[1]));
					}
					else if (tooljs)
					{
						err(39);
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
			else if (func == "cin")
			{
				string S;
				cin >> S;

				return S;
			}
			else if (func == "max")
			{
				ld ans = LDBL_MIN;
				for (ll i = 0; i < argn; i++)
				{
					chmax(ans, to_num(code[i + 1]));
				}

				return to_string(ans);
			}
			else if (func == "min")
			{
				ld ans = LDBL_MAX;
				for (ll i = 0; i < argn; i++)
				{
					chmin(ans, to_num(code[i + 1]));
				}

				return to_string(ans);
			}
			else if (func == "find")
			{
				int var_pos = var_search(code[1]);
				bool val_str = isstring(code[1]);
				code[1] = get_str(code[1]);
				code[2] = get_str(code[2]);

#ifdef WINDOWS
				u32string a = utf32conv.from_bytes(ansi_to_utf8(code[1]));
				u32string b = utf32conv.from_bytes(ansi_to_utf8(code[2]));
#else
				u32string a = utf32conv.from_bytes(code[1]);
				u32string b = utf32conv.from_bytes(code[2]);
#endif
				if (var_pos == 2 || val_str)
				{
					if (b.size() != 1)
					{
						err(28);
					}

					char32_t find_check = b[0];
					for (ll i = 0; i < a.size(); i++)
					{
						if (a[i] == find_check)
						{
							return to_string(i);
						}
					}

					return "-1";
				}
				else
				{
					err(43);
				}
			}
			else if (func == "rfind")
			{
				int var_pos = var_search(code[1]);
				bool val_str = isstring(code[1]);
				code[1] = get_str(code[1]);
				code[2] = get_str(code[2]);

#ifdef WINDOWS
				u32string a = utf32conv.from_bytes(ansi_to_utf8(code[1]));
				u32string b = utf32conv.from_bytes(ansi_to_utf8(code[2]));
#else
				u32string a = utf32conv.from_bytes(code[1]);
				u32string b = utf32conv.from_bytes(code[2]);
#endif
				if (var_pos == 2 || val_str)
				{
					if (b.size() != 1)
					{
						err(28);
					}

					char32_t find_check = b[0];
					for (ll i = a.size() - 1; i >= 0; i--)
					{
						if (a[i] == find_check)
						{
							return to_string(i);
						}
					}

					return "-1";
				}
				else
				{
					err(43);
				}
			}
			else if (func == "\"\"\"")
			{
				comment = true;
			}
			else
			{
				if (!op_funcskip && func != "" && func[0] >= '0')
				{
					if (inc_now == inc_code)
					{
						errorlog(line, linenum, 1);
					}
				}
			}
		}
		else if (comment)
		{
			if (func == "\"\"\"")
			{
				comment = false;
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

					if (inc_code == inc_now)
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
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
		err(41);
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
	if (!nx_line.count(code_line))
		isnx++;
	nx_line.insert(code_line);
	return ans;
}

int main(int argc, char const *argv[])
{
	// OS取得
	string os = "Unknown";
	bool os_win64 = false;

#ifdef _WIN64
	var_string["api_os"] = "win64";
	os_win64 = true;
	iswin = true;
	os = "Windows 64bit";
#endif

#ifdef _WIN32
	if (!os_win64)
	{
		var_string["api_os"] = "win32";
		os = "Windows 32bit";
	}
	iswin = true;
#endif

#if defined(__unix) || defined(__unix__)
	var_string["api_os"] = "unix";
	os = "Unix OS";
#endif

	// Aqua基本処理系

#pragma region Aqua System Variables

	var_bool["true"] = true;
	var_bool["True"] = true;
	var_bool["false"] = false;
	var_bool["False"] = false;
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

	// 引数
	if (count(all(args), "--version") || count(all(args), "-v"))
	{
		co("Aqua " + version);
		exit(0);
	}
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
	if (count(all(args), "--yes") || count(all(args), "-y"))
		st_using_yes = true;
	else
		st_using_yes = false;

	// 何もオプションがない場合
	// Pythonみたいな感じでCUIで実行できるようにする
	if (argc == 1 || (argc == 2 && !st_style))
	{
		clirun = true;
		co("--------------------------------------------------------------------------");
		co("Aqua " + version + " / " + os);
		co("Bugs and feedback can be sent to `https://github.com/e6nlaq/aqua/issues`");
		if (os == "Unix OS")
			warn("In the case of Unix, the arrow keys may not respond. Our apologies.");
		co("--------------------------------------------------------------------------\n");

		ll pyinc = 0;
		bool nxrun = false; // falseの時そのまま実行 trueの時もう一度入力
		const unordered_set<string> inc_plus_func = {"if", "while", "until", "forever"};

		while (true)
		{
			// cout << pyinc << " " << nxrun << endl;
			cou((pyinc > 0 || nxrun ? "... " : ">>> "));
			string inp;
			getline(cin, inp);
			nxrun = false;

			lines.push_back(inp);

			vector<string> code_tmp = scriptcut(incident(vector<string>{inp})[0]);
			string func = code_tmp[0];
			if (func == "end")
			{
				pyinc--;
			}
			else if (inc_plus_func.count(func))
				pyinc++;
			else if (count(all(code_tmp), ":"))
				nxrun = true;

			if (pyinc <= 0 && !nxrun)
			{
				for (code_line = 0; code_line < lines.size(); code_line++)
				{
					aqua(lines[code_line], lines, code_line);

					if (isnx) // :使ったら繰り越し
					{
						code_line += isnx;
						isnx = 0;
					}
				}
				lines.clear();
			}
		}

		return 0;
	}

	// UNIXだったらfalse
#ifdef LINUX
	iswin = false;
#endif

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
		co("Aqua JavaScript Compiler " + version);
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
		// cout << inc_code << " " << inc_now << endl;
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