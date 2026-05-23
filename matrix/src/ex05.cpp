#include "vector.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex05()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 05] COSINE\n" COLOR_RESET;

    Vector<K> u({1, 2});
    Vector<K> v({-5, 6});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    u.print("  u");
    v.print("  v");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    try
    {
        std::cout << "  cos(u,v) = " COLOR_NUM << angle_cos(u, v) << COLOR_RESET " rad\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }    
}
