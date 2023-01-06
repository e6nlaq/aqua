
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	ifstream file;
	file.open(argv[1]);

	string read_file;

	while (getline(file, read_file))
	{
		cout << read_file << endl;
	}

	return 0;
}
