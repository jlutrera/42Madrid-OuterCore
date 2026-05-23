/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex02.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:53:01 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/21 14:30:48 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "matrix.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex02()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 02] LINEAR INTERPOLATION\n" COLOR_RESET;

    Vector<K> u({1, 2});
    Vector<K> v({-5, 6});
    Matrix<K> A({{1, 2}, {5, 6}});
    Matrix<K> B({{7, 8}, {11, 12}});

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
        Vector<K> lerp_vec = lerp(u, v, 0.25);
        lerp_vec.print("  lerp(u, v, 0.25)");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    try
    {
        Matrix<K> lerp_mat = lerp(A, B, 0.5);
        lerp_mat.print("  lerp(A, B, 0.5)");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}