/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex14.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:30:00 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/26 13:56:32 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "colors.hpp"
#include <iostream>

void ex14()
{
    using K = float;

    std::cout << COLOR_EX "[Exercise 14] PROJECTION MATRIX\n" COLOR_RESET;

    std::cout << COLOR_NAME "I. Data\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    std::cout << "  fov = 90°\n  ratio = 16/9\n  near = 0.1\n  far = 100\n";

    std::cout << COLOR_NAME "II. Result\n" COLOR_RESET;
    std::cout << "---------------------------\n";
    K fov   = 90.0f * M_PI / 180.0f;   // convertir a radianes
    K ratio = 16.0f / 9.0f;
    K near  = 0.1f;
    K far   = 100.0f;
    try
    {
        Matrix<K> P = Matrix<K>::projectionOpenGL(fov, ratio, near, far);
        P.print("Projection Matrix (OpenGL version)");
        
        Matrix<K> P_dx = Matrix<K>::projectionDirectX(fov, ratio, near, far);
        P_dx.print("Projection Matrix (DirectX version)");
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
