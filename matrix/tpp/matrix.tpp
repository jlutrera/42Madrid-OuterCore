/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:50:15 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/20 14:43:51 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <algorithm>
#include <stdexcept>

#include "vector.hpp"
#include "algebra.hpp"
#include "colors.hpp"


// CONSTRUCTORS
template<typename K>
Matrix<K>::Matrix(std::initializer_list<std::initializer_list<K>> init)
{
    rows = init.size();
    cols = init.begin()->size();
    data.reserve(rows * cols);

    for (const auto& row : init)
        for (const auto& val : row)
            data.push_back(val);  //El almacenamiento es row-major
}

template<typename K>
Matrix<K>::Matrix(std::size_t r, std::size_t c, const std::vector<K>& values) 
    : rows(r), cols(c), data(values)
{
    if (values.size() != r * c)
        throw std::invalid_argument("Value count does not match matrix shape");
}

// GETTERS
template<typename K>
std::size_t Matrix<K>::nrows() const { return rows; }

template<typename K>
std::size_t Matrix<K>::ncols() const { return cols; }

template<typename K>
std::pair<std::size_t, std::size_t> Matrix<K>::shape() const { return {rows, cols}; }

// IS SQUARE?
template<typename K>
bool Matrix<K>::is_square() const { return rows == cols; }

// ADD
template<typename K>
void Matrix<K>::add(const Matrix<K>& m)
{
    if (rows != m.rows || cols != m.cols)
        throw std::invalid_argument("Matrix sizes must match");

    for (std::size_t i = 0; i < data.size(); ++i)
        data[i] += m.data[i];
}

// SUBTRACT
template<typename K>
void Matrix<K>::sub(const Matrix<K>& m)
{
    if (rows != m.rows || cols != m.cols)
        throw std::invalid_argument("Matrix sizes must match");

    for (std::size_t i = 0; i < data.size(); ++i)
        data[i] -= m.data[i];
}

// SCALE
template<typename K>
void Matrix<K>::scl(K a)
{
    for (auto& x : data)
        x *= a;
}

// INDEXING
template<typename K>
K& Matrix<K>::operator()(std::size_t r, std::size_t c)
{
    return data[r * cols + c];
}

template<typename K>
const K& Matrix<K>::operator()(std::size_t r, std::size_t c) const
{
    return data[r * cols + c];
}

// RESHAPE TO VECTOR
template<typename K>
Vector<K> Matrix<K>::reshape_to_vector() const
{
    Vector<K> v;
    v.data = data;
    return v;
}

// PRINT
template<typename K>
void Matrix<K>::print(const std::string& text) const
{
    std::cout << text << " = ";

    auto dims = shape();
    auto rows = dims.first;
    auto cols = dims.second;

    std::vector<size_t> colWidths(cols, 0);

    // ---- COMPUTE COLUMNS WIDTHS ----
    for (size_t c = 0; c < cols; ++c)
    {
        for (size_t r = 0; r < rows; ++r)
        {
            std::ostringstream ss;
            ss << (*this)(r, c);
            colWidths[c] = std::max(colWidths[c], ss.str().length());
        }
    }

    // ---------- TOP BORDER ----------
    std::cout << COLOR_BRACE "\u250C " COLOR_RESET;

    for (size_t c = 0; c < cols; ++c)
    {
        std::cout << std::string(colWidths[c], ' ');
        if (c < cols - 1)
            std::cout << " ";
    }
    std::cout << COLOR_BRACE " \u2510\n" COLOR_RESET;

    // ---------- MATRIX CONTENT ----------
    for (size_t r = 0; r < rows; ++r)
    {
        std::cout << std::string(text.size() + 3, ' ')
            << COLOR_BRACE "\u2502 " COLOR_RESET;

        for (size_t c = 0; c < cols; ++c)
        {
            std::cout << COLOR_NUM << std::setw(colWidths[c])
                << (*this)(r, c) << COLOR_RESET;

            if (c < cols - 1)
                std::cout << " ";
        }

        std::cout << COLOR_BRACE " \u2502\n" COLOR_RESET;
    }

    // ---------- BOTTOM BORDER ----------
    std::cout << std::string(text.size() + 3, ' ')
         << COLOR_BRACE "\u2514 " COLOR_RESET;
    for (size_t c = 0; c < cols; ++c)
    {
        std::cout << std::string(colWidths[c], ' ');
        if (c < cols - 1)
            std::cout << " ";
    }
    std::cout << COLOR_BRACE " \u2518\n" COLOR_RESET;
}

// MATRIX * MATRIX
template<typename K>
Matrix<K> Matrix<K>::mul_mat(const Matrix<K>& B)
{
    if (this->ncols() != B.nrows())
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    std::size_t m = this->nrows();
    std::size_t n = this->ncols();
    std::size_t p = B.ncols();

    Matrix<K> C(m, p, std::vector<K>(m * p, 0));

    for (std::size_t i = 0; i < m; ++i)
    {
        for (std::size_t j = 0; j < p; ++j)
        {
            K sum = K(0);

            for (std::size_t k = 0; k < n; ++k)
                sum = fused_mul_add((*this)(i, k), B(k, j), sum);

            C(i, j) = sum;
        }
    }

    return C;
}

// MATRIX * VECTOR
template<typename K>
Vector<K> Matrix<K>::mul_vec(const Vector<K>& v)
{
    if (this->ncols() != v.size())
        throw std::invalid_argument("Matrix and vector dimensions do not match");

    std::size_t m = this->nrows();
    std::size_t n = this->ncols();

    Vector<K> result;
    result.resize(m, K());  // redimensionar el std::vector interno

    for (std::size_t i = 0; i < m; ++i)
    {
        K sum = K(0);

        for (std::size_t j = 0; j < n; ++j)
            sum = fused_mul_add((*this)(i, j), v[j], sum);

        result[i] = sum;
    }

    return result;
}

// TRACE
template<typename K>
K Matrix<K>::trace()
{
    if (!this->is_square())
        throw std::invalid_argument("Trace is defined only for square matrices");

    K sum = K(0);

    for (std::size_t i = 0; i < rows; ++i)
        sum += (*this)(i, i);

    return sum;
}

// TRANSPOSE
template<typename K>
Matrix<K> Matrix<K>::transpose()
{
    Matrix<K> T(cols, rows, std::vector<K>(rows * cols, 0));

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            T(j, i) = (*this)(i, j);

    return T;
}

// ROW ECHELON FORM
template<typename K>
Matrix<K> Matrix<K>::row_echelon() const
{
    Matrix<K> M = *this;
    std::size_t m = rows;
    std::size_t n = cols;

    std::size_t lead = 0;

    for (std::size_t r = 0; r < m; ++r)
    {
        if (lead >= n)
            break;

        std::size_t i = r;

        // Buscar fila con pivote no cero
        while (i < m && M(i, lead) == K(0))
            ++i;

        // Si no hay pivote en esta columna, pasar a la siguiente
        if (i == m)
        {
            ++lead;
            --r; // repetir esta fila con la siguiente columna
            continue;
        }

        // Intercambiar filas si es necesario
        if (i != r)
        {
            for (std::size_t c = 0; c < n; ++c)
                std::swap(M(r, c), M(i, c));
        }

        // Normalizar fila pivote
        K pivot = M(r, lead);
        if (abs_value(pivot) != 0.0)
        {
            for (std::size_t c = 0; c < n; ++c)
                M(r, c) /= pivot;
        }

        // Eliminar filas por debajo
        for (std::size_t rr = r + 1; rr < m; ++rr)
        {
            K factor = M(rr, lead);

            if (abs_value(factor) != 0.0)
            {
                for (std::size_t c = 0; c < n; ++c)
                    M(rr, c) = fused_mul_add(-factor, M(r, c), M(rr, c));
            }
        }

        ++lead;
    }

    return M;
}

// DETERMINANT
template<typename K>
K Matrix<K>::determinant()
{
    if (!this->is_square())
        throw std::invalid_argument("Determinant is defined only for square matrices");

    std::size_t n = rows;
    Matrix<K> M = *this;
    K det = K(1);

    for (std::size_t i = 0; i < n; ++i)
    {
        // Pivot must be non-zero
        if (abs_value(M(i, i)) == 0.0)
        {
            bool swapped = false;
            for (std::size_t r = i + 1; r < n; ++r)
            {
                if (abs_value(M(r, i)) != 0.0)
                {
                    for (std::size_t c = 0; c < n; ++c)
                        std::swap(M(i, c), M(r, c));

                    det = -det; // row swap flips sign
                    swapped = true;
                    break;
                }
            }
            if (!swapped)
                return 0; // determinant is zero
        }

        K pivot = M(i, i);
        det *= pivot;

        // Eliminate below pivot
        for (std::size_t r = i + 1; r < n; ++r)
        {
            K factor = M(r, i) / pivot;

            for (std::size_t c = i; c < n; ++c)
                M(r, c) = fused_mul_add(-factor, M(i, c), M(r, c));
        }
    }

    return det;
}

// INVERSE
template<typename K>
Matrix<K> Matrix<K>::inverse()
{
    if (!this->is_square())
        throw std::invalid_argument("Inverse is defined only for square matrices");

    std::size_t n = rows;

    Matrix<K> M = *this;
    Matrix<K> I(n, n, std::vector<K>(n * n, K(0)));

    // Initialize identity
    for (std::size_t i = 0; i < n; ++i)
        I(i, i) = K(1);

    for (std::size_t i = 0; i < n; ++i)
    {
        // Pivot must be non-zero
        if (abs_value(M(i, i)) == 0.0)
        {
            bool swapped = false;
            for (std::size_t r = i + 1; r < n; ++r)
            {
                if (abs_value(M(r, i)) != 0.0)
                {
                    for (std::size_t c = 0; c < n; ++c)
                    {
                        std::swap(M(i, c), M(r, c));
                        std::swap(I(i, c), I(r, c));
                    }
                    swapped = true;
                    break;
                }
            }
            if (!swapped)
                throw std::invalid_argument("Matrix is singular and cannot be inverted");
        }

        K pivot = M(i, i);

        // Normalize pivot row
        for (std::size_t c = 0; c < n; ++c)
        {
            M(i, c) /= pivot;
            I(i, c) /= pivot;
        }

        // Eliminate other rows
        for (std::size_t r = 0; r < n; ++r)
        {
            if (r == i) continue;

            K factor = M(r, i);

            for (std::size_t c = 0; c < n; ++c)
            {
                M(r, c) = fused_mul_add(-factor, M(i, c), M(r, c));
                I(r, c) = fused_mul_add(-factor, I(i, c), I(r, c));
            }
        }
    }

    return I;
}

// RANK
template<typename K>
std::size_t Matrix<K>::rank() const
{
    Matrix<K> M = *this;
    std::size_t m = rows;
    std::size_t n = cols;

    std::size_t rank = 0;
    std::size_t lead = 0;

    for (std::size_t r = 0; r < m && lead < n; ++r)
    {
        // Buscar pivote no nulo en la columna lead
        std::size_t i = r;
        while (i < m && M(i, lead) == K(0))
            ++i;

        if (i == m)
        {
            ++lead;
            --r;        // reintentar misma fila con siguiente columna
            continue;
        }

        // Intercambiar filas si es necesario
        if (i != r)
        {
            for (std::size_t c = lead; c < n; ++c)
                std::swap(M(r, c), M(i, c));
        }

        // Pivote encontrado → incrementa rango
        ++rank;

        K pivot = M(r, lead);

        // Eliminación por debajo
        for (std::size_t rr = r + 1; rr < m; ++rr)
        {
            if (M(rr, lead) != K(0))
            {
                K factor = M(rr, lead) / pivot;
            
                for (std::size_t c = lead; c < n; ++c)
                    M(rr, c) -= factor * M(r, c);
            }
        }

        ++lead;
    }

    return rank;
}

// PROJECTION MATRIX FOR OPENGL CONVENTIONS
//   - clip space z ∈ [-1,1]
//   - right-handed system
//   - camera looks towards -Z
//   - X to the right
//   - Y upwards
//   - near and far are positive distances
//   - ratio = width / height
//   - FOV vertical in radians

// Para obtener la proyección en perspectiva, se multiplica el vector por P y luego se divide por W.
template<typename K>
Matrix<K> Matrix<K>::projectionOpenGL(K fov, K ratio, K near, K far)
{
    // VALIDATIONS
    // FOV must be in (0, pi) radians
    if (fov <= K(0) || fov >= K(M_PI))
        throw std::invalid_argument("FOV must be in (0, pi) radians");
    // Aspect ratio must be positive
    if (ratio <= K(0))
        throw std::invalid_argument("Aspect ratio must be positive");
    // Near and far must be positive
    if (near <= K(0) || far <= K(0))
        throw std::invalid_argument("Near and far must be positive");
    // Near must be less than far
    if (near >= far)
        throw std::invalid_argument("Near plane must be less than far plane");

    //  COMPUTE PROJECTION MATRIX
    K t = std::tan(fov / (K)2);

    // Matriz de proyección 4x4 inicializada a cero
    Matrix<K> P(4, 4, std::vector<K>(16, K(0)));

    // Escalado en X y Y
    P(0, 0) = K(1) / (ratio * t);                   // Escala X según FOV y aspect ratio
    P(1, 1) = K(1) / t;                             // Escala Y según FOV

    // Transformación de profundidad (Z)
    P(2, 2) = -(far  + near) / (far - near);        // Mapea Z a clip space [-1,1]
    P(2, 3) = -(K(2) * far * near) / (far - near);  // Ajuste de profundidad

    // Componente homogénea
    P(3, 2) = -K(1);                                // Homogeneización W = -Z
 
    return P;
}

// PROJECTION MATRIX FOR DIRECTX CONVENTIONS
//   - clip space z ∈ [0,1]
//   - right-handed system
//   - camera looks towards +Z
//   - X to the right
//   - Y upwards
//   - near and far are positive distances
//   - ratio = width / height
//   - FOV vertical in radians
template<typename K>
Matrix<K> Matrix<K>::projectionDirectX(K fov, K ratio, K near, K far)
{
    // VALIDATIONS
    // FOV must be in (0, pi) radians
    if (fov <= K(0) || fov >= K(M_PI))
        throw std::invalid_argument("FOV must be in (0, pi) radians");
    // Aspect ratio must be positive
    if (ratio <= K(0))
        throw std::invalid_argument("Aspect ratio must be positive");
    // Near and far must be positive
    if (near <= K(0) || far <= K(0))
        throw std::invalid_argument("Near and far must be positive");
    // Near must be less than far
    if (near >= far)
        throw std::invalid_argument("Near plane must be less than far plane");

    //  COMPUTE PROJECTION MATRIX
    K t = std::tan(fov / (K)2);

    // Matriz de proyección 4x4 inicializada a cero
    Matrix<K> P(4, 4, std::vector<K>(16, K(0)));

    // Escalado en X y Y
    P(0, 0) = K(1) / (ratio * t);               // Escala X según FOV y aspect ratio
    P(1, 1) = K(1) / t;                         // Escala Y según FOV

    // Transformación de profundidad (Z)
    P(2, 2) = far / (near - far);               // Mapea Z a clip space [0,1]
    P(2, 3) = (far * near) / (near - far);     // Ajuste de profundidad
 
    // Componente homogénea
    P(3, 2) = K(-1);                             // Homogeneización W = -Z

    return P;
}