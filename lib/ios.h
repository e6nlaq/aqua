
/*******************************************************

              lib/ios.h

    Created at: Jan 7, 2023, 7:41 AM GMT+9
    Copyright (C) 2023 e6nlaq
    This file is part of aqua.
    Licensed under GNU General Public License v3.0.

*******************************************************/

#pragma once

#include <iostream>
using namespace std;

template <typename T>
inline void out(T output)
{
    cout << output;
}

template <typename T>
inline void outf(T output)
{
    cout << output << "\n";
}
