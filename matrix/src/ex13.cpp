/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex13.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:43:41 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/21 12:36:45 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "colors.hpp"
#include <iostream>

void ex13()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 13] RANK\n" COLOR_RESET;

    Matrix<K> A({
        {1, 2, 1, -1},
        {2, 4, -1, 3},
        {3, 6, 2, 1}
    });

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    A.print("  A");
   
    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    std::cout << "  rank(A) = " COLOR_NUM << A.rank() << COLOR_RESET "\n\n";
}
