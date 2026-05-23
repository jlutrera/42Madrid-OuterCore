/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex01.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:50:22 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/20 22:50:22 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex01()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 01] LINEAR COMBINATION\n" COLOR_RESET;

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
        Vector<K> lc = linear_combination(2.0f, u, -1.0f, v);
        lc.print("  2 * u - v");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    
    }
}