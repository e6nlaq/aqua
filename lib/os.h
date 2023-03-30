
/*******************************************************

              lib/os.h

    Created at: Mar 23, 2023, 18:16 PM GMT+9
    Copyright (C) 2023 e6nlaq
    This file is part of aqua.
    Licensed under the MIT License.

*******************************************************/

#pragma once
#include <iostream>

inline void cscle()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}