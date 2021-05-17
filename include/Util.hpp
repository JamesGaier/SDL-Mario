#pragma once
#include <iostream>

namespace smb
{

    void dynamic_assert(bool expr, const std::string& msg)
    {
        if(expr)
        {
            std::cout << msg << std::endl;
        }
        else
        {
            std::cerr << "Assertion Failed" << std::endl;
            std::abort();
        }
    }

}