/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex06.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:04:28 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/21 14:31:17 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex06()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 06] CROSS PRODUCT\n" COLOR_RESET;

    Vector<K> u({1, 2, 3});
    Vector<K> v({4, -5, 6});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    u.print("  u");
    v.print("  v");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    try
    {
        Vector<K> cross = cross_product(u, v);
        cross.print("  u x v");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}