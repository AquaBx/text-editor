//
// Created by tomch on 17/10/2024.
//
#pragma once

#include <stdexcept>
#include <string>
#include <iostream>

typedef void (* vFunctionCall)();

namespace Tools
{
    void assert_equals(auto expected, auto actual, std::string message )
    {
        if (expected != actual) {
            throw std::runtime_error(message);
        }
    }

    int test(const vFunctionCall function)
    {
        try
        {
            function();
            return 0;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
}


