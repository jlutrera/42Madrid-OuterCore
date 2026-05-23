/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex12.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:43:47 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/22 12:28:58 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "colors.hpp"
#include <iostream>

void ex12()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 12] INVERSE\n" COLOR_RESET;

    Matrix<K> A({{1, 2}, {5, 6}});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    A.print("  A");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    try
    {
        Matrix<K> A_inv = A.inverse();
        A_inv.print("  A^(-1)");
    }
    catch (const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}
