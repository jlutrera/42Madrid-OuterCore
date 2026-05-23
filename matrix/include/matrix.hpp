/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:34:29 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/20 11:34:29 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <initializer_list>
#include <string>
#include <cstddef>
#include <utility>
#include <stdexcept>

template<typename K>
    class Vector;
template<typename K>
class Matrix
{
    public:
        // Constructors
        Matrix() = default;
        Matrix(std::initializer_list<std::initializer_list<K>> init);
        Matrix(std::size_t r, std::size_t c, const std::vector<K>& values);

        // Getters
        std::size_t nrows() const;
        std::size_t ncols() const;
        std::pair<std::size_t, std::size_t> shape() const;
        
        // Check square
        bool is_square() const;

        // Add, Subtract, Scale
        void add(const Matrix<K>& m);
        void sub(const Matrix<K>& m);
        void scl(K a);

        // Indexing
        const K& operator()(std::size_t r, std::size_t c) const;
        K& operator()(std::size_t r, std::size_t c);

        // Reshape to vector
        Vector<K> reshape_to_vector() const;

        // Print
        void print(const std::string& text) const;

        // Multiplication : matrix * matrix and matrix * vector
        Matrix<K> mul_mat(const Matrix<K>& B);
        Vector<K> mul_vec(const Vector<K>& v);

        // Advanced operations
        K trace();
        Matrix<K> transpose();
        Matrix<K> row_echelon() const;
        K determinant();
        Matrix<K> inverse();
        std::size_t rank() const;

        // Projection matrices with different NDC conventions
        static Matrix<K> projectionOpenGL(K fov, K ratio, K near, K far);
        static Matrix<K> projectionDirectX(K fov, K ratio, K near, K far);

    private:
        std::size_t rows = 0;
        std::size_t cols = 0;
        std::vector<K> data;
};

#include "../tpp/matrix.tpp"

