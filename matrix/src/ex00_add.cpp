/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex00_add.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:41:07 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/21 10:41:07 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "matrix.hpp"
#include "colors.hpp"
#include <iostream>

void ex00_add()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 00] ADDICTION\n" COLOR_RESET;

    Vector<K> u({1, 12, 3});
    Vector<K> v({4, 5, -6});
    Matrix<K> A({{1, -2}, {3, 4}});
    Matrix<K> B({{5, 6}, {17, 8}});
    Vector<K> temp;
    Matrix<K> tempM;

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    u.print("  u");
    v.print("  v");
    A.print("  A");
    B.print("  B");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";

    try
    {
        temp = u;
        temp.add(v);
        temp.print("  u + v");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    try
    {
        tempM = A;
        tempM.add(B);
        tempM.print("  A + B");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    
}
