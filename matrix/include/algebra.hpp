/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:51:09 by jutrera-          #+#    #+#             */
/*   Updated: 2026/01/31 21:05:39 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <cmath>
#include <complex>
#include <stdexcept>
#include <algorithm>

#include "vector.hpp"
#include "matrix.hpp"

// Fused multiply-add
template<typename K>
K fused_mul_add(K a, K b, K c);

// Absolute value
template<typename K>
double abs_value(const K& x);

// Dot product
template<typename K>
K dot(const Vector<K>& u, const Vector<K>& v);

// Linear combination
template<typename K>
Vector<K> linear_combination(K a, const Vector<K>& u,
                             K b, const Vector<K>& v);

// Linear interpolation
template<typename K>
Vector<K> lerp(const Vector<K>& u, const Vector<K>& v, double t);
template<typename K>
Matrix<K> lerp(const Matrix<K>& A, const Matrix<K>& B, double t);

// L2 Norm
template<typename K>
double norm(const Vector<K>& u);

// Norm 1
template<typename K>
double norm_1(const Vector<K>& u);

// Infinity Norm
template<typename K>
double norm_inf(const Vector<K>& u);

// Cosine of angle
template<typename K>
double angle_cos(const Vector<K>& u, const Vector<K>& v);

// Cross product
template<typename K>
Vector<K> cross_product(const Vector<K>& u, const Vector<K>& v);

#include "../tpp/algebra.tpp"
