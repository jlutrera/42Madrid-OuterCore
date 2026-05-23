/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex09.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:23:18 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/21 14:31:29 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex09()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 09] TRANSPOSE\n" COLOR_RESET;

    Matrix<K> A({{8, 9}, {10, 12}});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    A.print("  A");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    Matrix<K> A_T = A.transpose();
    A_T.print("  A^T");
}