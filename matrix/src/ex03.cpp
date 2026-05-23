/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex03.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:55:54 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/22 12:28:14 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex03()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 03] DOT PRODUCT\n" COLOR_RESET;

    Vector<K> u({1, 2});
    Vector<K> v({-5, 6});

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    u.print("  u");
    v.print("  v");

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    try
    {
        std::cout << "  u * v = " COLOR_NUM << dot(u, v) << COLOR_RESET "\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
}
