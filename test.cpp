
#include <bits/stdc++.h>
#include "./lib/math.h"
using namespace std;
using ll = long long;

#define co(x) cout << (x) << "\n"
#define rep(i, n) for (ll i = 0; i < (n); i++)

int main(int argc, char const *argv[])
{

	rep(i, 10000)
	{
		if (is_prime(i + 1))
			co(i + 1);
	}

	return 0;
}
