/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex07_mulmat.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:06:18 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/22 12:28:28 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "matrix.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex07_mulmat()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 07] MATRIX-MATRIX MULTIPLICATION\n" COLOR_RESET;
    
    Matrix<K> A({{1, 2, 3}, {4, 5, 6}});
    Matrix<K> B({{7, 8, 9}, {10, 11, 12}, {-2, 3, 0}});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    A.print("  A");
    B.print("  B");

    std::cout << COLOR_NAME "II. Results\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    try
    {
        Matrix<K> C = A.mul_mat(B);
        C.print("  A * B");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}
