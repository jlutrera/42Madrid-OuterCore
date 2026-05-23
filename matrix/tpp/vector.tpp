/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:50:23 by jutrera-          #+#    #+#             */
/*   Updated: 2026/01/30 11:02:10 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>        // std::cout
#include <stdexcept>       // std::invalid_argument
#include "colors.hpp"      // COLOR_*
#include "matrix.hpp"      // Matrix<K> (declaración suficiente)

// CONSTRUCTOR WITH INITIALIZER LIST
template<typename K>
Vector<K>::Vector(std::initializer_list<K> init) : data(init) {}

// SIZE
template<typename K>
std::size_t Vector<K>::size() const
{
    return data.size();
}

// RESIZE
template<typename K>
void Vector<K>::resize(std::size_t n, K value)
{
    data.resize(n, value);
}

// ADD
template<typename K>
void Vector<K>::add(const Vector<K>& u)
{
    if (data.size() != u.data.size())
        throw std::invalid_argument("Vectors must have the same size");

    for (std::size_t i = 0; i < data.size(); ++i)
        data[i] += u.data[i];
}

// SUBTRACT
template<typename K>
void Vector<K>::sub(const Vector<K>& u)
{
    if (data.size() != u.data.size())
        throw std::invalid_argument("Vectors must have the same size");

    for (std::size_t i = 0; i < data.size(); ++i)
        data[i] -= u.data[i];
}

// SCALE
template<typename K>
void Vector<K>::scl(K a)
{
    for (auto& x : data)
        x *= a;
}

// INDEXING
template<typename K>
const K& Vector<K>::operator[](std::size_t i) const
{
    return data[i];
}

template<typename K>
K& Vector<K>::operator[](std::size_t i)
{
    return data[i];
}

// PRINT 
template<typename K>
void Vector<K>::print(const std::string& text) const
{
    std::cout << text << " = ";
    std::cout << COLOR_BRACE "[ " COLOR_RESET;
    for (std::size_t i = 0; i < data.size(); ++i)
    {
        std::cout << COLOR_NUM << data[i] << COLOR_RESET;
        if (i < data.size() - 1)
            std::cout << ", ";
    }
    std::cout << COLOR_BRACE " ]\n\n" COLOR_RESET;
}

// RESHAPE TO MATRIX
template<typename K>
Matrix<K> Vector<K>::reshape_to_matrix(std::size_t r, std::size_t c) const
{
    if (data.size() != r * c)
        throw std::invalid_argument("Vector size does not match matrix shape");

    return Matrix<K>(r, c, data);
}
