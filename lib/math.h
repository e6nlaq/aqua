
/*******************************************************

			  lib/math.h

	Created at: Feb 25, 2023, 11:24 AM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#pragma once

#include "./type.h"

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