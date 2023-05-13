
/*******************************************************

			  lib/math.h

	Created at: Feb 25, 2023, 11:24 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#pragma once

#include "./type.h"
#include <math.h>

inline ll a_gcd(const ll a, const ll b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return a_gcd(b, a % b);
	}
}

inline ll a_lcm(const ll a, const ll b)
{
	return a * b / a_gcd(a, b);
}

inline bool is_prime(const ll num)
{
	if (num < 2)
		return false;
	else if (num == 2)
		return true;
	else if (num % 2 == 0)
		return false; // 偶数はあらかじめ除く

	long double sqrtNum = sqrt(num);
	for (int i = 3; i <= sqrtNum; i += 2)
	{
		if (num % i == 0)
		{
			// 素数ではない
			return false;
		}
	}

	// 素数である
	return true;
}

inline ll fact(ll x)
{
	ll ret = 1;
	for (ll i = 1; i <= x; i++)
	{
		ret *= i;
	}
	return ret;
}

inline ld log_a(ld x, ld b)
{
	return log10l(x) / log10l(b);
}
