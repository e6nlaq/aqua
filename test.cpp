#include <iostream>
#include <locale>

using namespace std;

string getOSLanguage()
{
	locale loc("ja_JP.UTF-8");
	auto a = &loc;
	string language = a->name();
	return language;
}

int main()
{
	string language = getOSLanguage();
	cout << "OSの言語は" << language << "です。" << endl;
	return 0;
}
