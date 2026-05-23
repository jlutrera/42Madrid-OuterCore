/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex11.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:43:51 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/21 12:35:22 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "colors.hpp"
#include <iostream>

void ex11()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 11] DETERMINANT\n" COLOR_RESET;

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    Matrix<K> A({
        {4, 3},
        {6, 3}
    });
    A.print("  A");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    try
    {
        std::cout << "  det(A) = " COLOR_NUM << A.determinant() << COLOR_RESET "\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}
