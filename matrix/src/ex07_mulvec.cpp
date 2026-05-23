/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex07_mulvec.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:06:18 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/22 12:28:35 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "matrix.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex07_mulvec()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 07] VECTOR-MATRIX MULTIPLICATION\n" COLOR_RESET;
    
    Vector<K> u({1, 2, 5});
    Matrix<K> A({{1, 2, 3}, {4, 5, 6}});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    u.print("  u");
    A.print("  A");
   
    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    
    try
    {
        Vector<K> mapped = A.mul_vec(u);
        mapped.print("  A * u");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}
