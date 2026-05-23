/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex15.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:20:00 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/22 12:30:08 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "vector.hpp"
#include "algebra.hpp"
#include "colors.hpp"
#include <iostream>

void ex15()
{
    using R = float;
    using C = std::complex<R>;

    std::cout << COLOR_EX "[Exercise 15] COMPLEX VECTOR SPACES\n" COLOR_RESET;
    // ============================================================
    // DATA
    // ============================================================
    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    Vector<C> u({ C(1, 2), C(-3, 0) });
    Vector<C> v({ C(0, 1), C(2, -1) });
    Matrix<C> A({
        { C(1, 0),  C(0, 1)  },
        { C(2, -1), C(-1, 2) }
    });
    Matrix<C> B({
        { C(1, 1),  C(2, -1)},
        { C(0, -1), C(1, 0) }
    });

    u.print("  u");
    v.print("  v");
    A.print("  A");
    B.print("  B");

    // ============================================================
    // I. VECTOR ALGEBRA
    // ============================================================
    std::cout << COLOR_NAME "II. Vector Algebra\n" COLOR_RESET;
    std::cout << "---------------------------\n";

    // Add
    try
    {
        Vector<C> v_sum = u;
        v_sum.add(v);
        v_sum.print("  u + v");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    // Sub
    try
    {
        Vector<C> v_sub = u;
        v_sub.sub(v);
        v_sub.print("  u - v");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }

    // Scale
    Vector<C> v_scl = u;
    v_scl.scl(C(0, 1));
    v_scl.print("  i * u");

    // Linear combination
    try
    {
        Vector<C> v_lin = linear_combination(C(2, -1), u, C(-1, 0.5), v);
        v_lin.print("  (2 - i) * u  +  (-1 + 0.5i) * v");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }

    // Linear interpolation
    try
    {
        Vector<C> v_lerp = lerp(u, v, 0.3);
        v_lerp.print("  lerp(u, v, 0.3)");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }

    // Dot product (Hermitian)
    try
    {
        C dot12 = dot(u, v);
        std::cout << "  u * v = " COLOR_NUM << dot12 << COLOR_RESET "\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }

    // Norms
    std::cout << "  ||u||₁ = " COLOR_NUM << norm_1(u)   << COLOR_RESET "\n";
    std::cout << "  ||u||  = " COLOR_NUM << norm(u)     << COLOR_RESET "\n";
    std::cout << "  ||u||∞ = " COLOR_NUM << norm_inf(u) << COLOR_RESET "\n\n";

    // Cosine
    try
    {
        std::cout << "  cos(u, v) = " << COLOR_NUM << angle_cos(u, v) << COLOR_RESET "\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    // ============================================================
    // II. MATRIX ALGEBRA
    // ============================================================
    std::cout << COLOR_NAME "III. Matrix Algebra\n" COLOR_RESET;
    std::cout << "---------------------------\n";

    // Add
    try
    {
        Matrix<C> M_sum = A;
        M_sum.add(B);
        M_sum.print("  A + B");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    // Sub
    try
    {
        Matrix<C> M_sub = A;
        M_sub.sub(B);
        M_sub.print("  A - B");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    // Scale
    Matrix<C> M_scl = A;
    M_scl.scl(C(0, 1));
    M_scl.print("  i * A");

    // Linear interpolation
    try
    {
        Matrix<C> M_lerp = lerp(A, B, 0.3);
        M_lerp.print("  lerp(A, B, 0.3)");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    // Matrix-vector multiplication
    try
    {
        Vector<C> Av = A.mul_vec(v);
        Av.print("  A * v");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }

    // Matrix-matrix multiplication
    try
    {
        Matrix<C> AB = A.mul_mat(B);
        AB.print("  A * B");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }

    // Transpose
    Matrix<C> At = A.transpose();
    At.print("  A^T");

    // Trace
    try
    {
        std::cout << "  trace(A) = " COLOR_NUM << A.trace() << COLOR_RESET "\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }

    // ============================================================
    // III. SOLVING SYSTEMS OF LINEAR EQUATIONS
    // ============================================================
    std::cout << COLOR_NAME "IV. Linear equations\n" COLOR_RESET;
    std::cout << "---------------------------\n";

    // Determinant
    try
    {
        C detB = B.determinant();
        std::cout << "  det(B) = " COLOR_NUM << detB << COLOR_RESET "\n\n";
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    // Inverse
    try
    {
        Matrix<C> B_inv = B.inverse();
        B_inv.print("  B^(-1)");
    }
    catch(const std::exception& e)
    {
        std::cout << COLOR_ERR "  Error: " << e.what() << COLOR_RESET "\n";
    }
    
    // REF
    Matrix<C> B_ref = B.row_echelon();
    B_ref.print("  REF(B)");

    // Rank
    std::cout << "  rank(B) = " COLOR_NUM << B.rank() << COLOR_RESET "\n\n";
}
