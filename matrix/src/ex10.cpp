/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex10.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:43:54 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/21 12:34:33 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "colors.hpp"
#include <iostream>

void ex10()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 10] ROW-ECHELON FORM\n" COLOR_RESET;

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
    Matrix<K> A_ref = A.row_echelon();
    A_ref.print("  REF(A)");
}
