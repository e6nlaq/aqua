
/*******************************************************

              lib/ios.h

    Created at: Jan 7, 2023, 7:41 AM GMT+9
    Copyright (C) 2023 e6nlaq
    This file is part of aqua.
    Licensed under the MIT License.

*******************************************************/

#pragma once

#include <iostream>

template <typename T>
inline void out(T output)
{
    std::cout << output;
}

template <typename T>
inline void outf(T output)
{
    std::cout << output << "\n";
}

template <typename T>
inline void err_out(T output)
{
    std::cerr << output;
}

template <typename T>
inline void err_outf(T output)
{
    std::cerr << output << "\n";
}
