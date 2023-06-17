
#include <bits/stdc++.h>
#include "lib/strconv.h"
using namespace std;

int main()
{
	wstring_convert<codecvt_utf8<char32_t>, char32_t> utf32conv;

	cout << utf8_to_ansi(utf32conv.to_bytes(u32string{12354})) << endl;
}
