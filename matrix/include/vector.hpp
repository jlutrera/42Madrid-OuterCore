/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:34:44 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/20 11:34:44 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <initializer_list>
#include <string> 
#include <cstddef>

template<typename K>
    class Matrix;

template<typename K>
class Vector
{
    public:
        // Constructors
        Vector() = default;
        Vector(std::initializer_list<K> init);

        // Size and Resize
        std::size_t size() const;
        void resize(std::size_t n, K value = K());

        //Print
        void print(const std::string& text) const;

        //add, sub, scale
        void add(const Vector<K>& v);
        void sub(const Vector<K>& v);  
        void scl(K a);

        //Reshape as a matrix        
        Matrix<K> reshape_to_matrix(std::size_t r, std::size_t c) const;

        //Indexing
        const K& operator[](std::size_t i) const;
        K& operator[](std::size_t i);

    private:
        std::vector<K> data;
        // Allow Matrix to access private members
        template<typename T>
        friend class Matrix;
};

#include "../tpp/vector.tpp"

