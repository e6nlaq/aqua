
/*******************************************************

			  lib/ojf.h

	Created at: Mar 1, 2023, 13:17 PM GMT+9
	Copyright (C) 2023 e6nlaq
	This file is part of aqua.
	Licensed under the MIT License.

*******************************************************/

#pragma once

template <typename T1, typename T2>
inline bool chmax(T1 &a, T2 b)
{
	if (b > a)
	{
		a = b;
		return true;
	}
	else
		return false;
}

template <typename T1, typename T2>
inline bool chmin(T1 &a, T2 b)
{
	if (b < a)
	{
		a = b;
		return true;
	}
	else
		return false;
}
