/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:35:20 by jutrera-          #+#    #+#             */
/*   Updated: 2025/12/20 11:35:20 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <limits>
#include "colors.hpp"

// Prototypes for exercise functions
void ex00_add();
void ex00_sub();
void ex00_scl();
void ex01();
void ex02();
void ex03();
void ex04();
void ex05();
void ex06();
void ex07_mulvec();
void ex07_mulmat();
void ex08();
void ex09();
void ex10();
void ex11();
void ex12();
void ex13();
void ex14();
void ex15();

static void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

static void wait_key()
{
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

static void print_menu()
{
    std::cout << "==================================\n";
    std::cout << "           MATRIX - TESTS         \n";
    std::cout << "==================================\n";
    std::cout << "Select an option:\n\n";

    std::cout << COLOR_BRACE "  I-  " COLOR_RESET "BASIC ALGEBRA\n";
    std::cout << "     ***************\n";
    std::cout << COLOR_EX "  0" COLOR_RESET " : Exercise 00: Addiction\n";
    std::cout << COLOR_EX "  1" COLOR_RESET " : Exercise 00: Subtraction\n";
    std::cout << COLOR_EX "  2" COLOR_RESET " : Exercise 00: Scaling\n";
    std::cout << COLOR_EX "  3" COLOR_RESET " : Exercise 01: Linear Combination\n";
    std::cout << COLOR_EX "  4" COLOR_RESET " : Exercise 02: Linear Interpolation\n\n";

    std::cout << COLOR_BRACE " II-  " COLOR_RESET "NORMS AND PRODUCTS\n";
    std::cout << "     ********************\n";
    std::cout << COLOR_EX "  5" COLOR_RESET " : Exercise 03: Dot Product\n";
    std::cout << COLOR_EX "  6" COLOR_RESET " : Exercise 04: Norm\n";
    std::cout << COLOR_EX "  7" COLOR_RESET " : Exercise 05: Cosine\n";
    std::cout << COLOR_EX "  8" COLOR_RESET " : Exercise 06: Cross Product\n\n";

    std::cout << COLOR_BRACE "III-  " COLOR_RESET "MATRIX ALGEBRA\n";
    std::cout << "     ****************\n";
    std::cout << COLOR_EX "  9" COLOR_RESET " : Exercise 07: Vector - Matrix Multiplication\n";
    std::cout << COLOR_EX " 10" COLOR_RESET " : Exercise 07: Matrix - Matrix Multiplication\n";
    std::cout << COLOR_EX " 11" COLOR_RESET " : Exercise 08: Trace\n";
    std::cout << COLOR_EX " 12" COLOR_RESET " : Exercise 09: Transpose\n\n";

    std::cout << COLOR_BRACE " IV-  " COLOR_RESET "SOLVING SYSTEMS OF LINEAR EQUATIONS\n";
    std::cout << "     *************************************\n";
    std::cout << COLOR_EX " 13" COLOR_RESET " : Exercise 10: Row-Echelon Form\n";
    std::cout << COLOR_EX " 14" COLOR_RESET " : Exercise 11: Determinant\n";
    std::cout << COLOR_EX " 15" COLOR_RESET " : Exercise 12: Inverse\n";
    std::cout << COLOR_EX " 16" COLOR_RESET " : Exercise 13: Rank\n\n";

    std::cout << COLOR_BRACE "  V-  " COLOR_RESET "BONUS\n";
    std::cout << "     *******\n";
    std::cout << COLOR_EX " 17" COLOR_RESET " : Exercise 14: Projection Matrix\n";
    std::cout << COLOR_EX " 18" COLOR_RESET " : Exercise 15: Complex vector spaces\n\n";

    std::cout << " 99 : Quit\n\n";
    std::cout << "Option: ";
}

static void run_test(int option)
{
    switch (option)
    {
        case 0:  ex00_add(); break;
        case 1:  ex00_sub(); break;
        case 2:  ex00_scl(); break;
        case 3:  ex01(); break;
        case 4:  ex02(); break;
        case 5:  ex03(); break;
        case 6:  ex04(); break;
        case 7:  ex05(); break;
        case 8:  ex06(); break;
        case 9:  ex07_mulvec(); break;
        case 10: ex07_mulmat(); break;
        case 11: ex08(); break;
        case 12: ex09(); break;
        case 13: ex10(); break;
        case 14: ex11(); break;
        case 15: ex12(); break;
        case 16: ex13(); break;
        case 17: ex14(); break;
        case 18: ex15(); break;

        default:
            std::cout << "Invalid option\n";
            break;
    }
}

int main()
{
    while (true)
    {
        clear_screen();
        print_menu();

        int option;
        std::cin >> option;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (option == 99)
        {
            clear_screen();
            std::cout << "Exiting...\n";
            break;
        }

        clear_screen();
        run_test(option);

        std::cout << "\n--- End of test ---\n";
        wait_key();
    }

    return 0;
}
