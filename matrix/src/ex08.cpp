/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex08.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:18:58 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/26 11:45:56 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex08()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 08] TRACE\n" COLOR_RESET;

    Matrix<K> A({{1, 2}, {-5, 6}});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    A.print("  A");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    try
    {
        std::cout << "  trace(A) = " COLOR_NUM << A.trace() << COLOR_RESET "\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}