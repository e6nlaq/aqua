
#include <bits/stdc++.h>
using namespace std;

int main()
{
	double N;
	cin >> N;
	double ret = 1;

	if (fmod(N, 1) != 0)
	{
		ret += fmod(N, 1);
	}

	for (int i = 1; i <= N; i++)
	{
		ret *= i;
	}

	cout << ret << endl;
}
