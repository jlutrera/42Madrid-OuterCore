/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:31:46 by jutrera-          #+#    #+#             */
/*   Updated: 2024/07/30 14:31:46 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	solve_equality(double *reduced, char letter)
{
	printf("\n%sSolving an equality:%s\n", GREEN, RESET);

	if (reduced[0] == 0)
	{
		printf("   ");
		if (letter)
			printf("%s%c \u2208 \u211D %s ", YELLOW, letter, RESET);
		printf("(Every real number satisfies the equation).");
	}
	else
	{
		if (!letter)
			printf("   %s\u2204 solution%s", YELLOW, RESET);
		else
			printf("   %s\u2204 %c%s", YELLOW, letter, RESET);
	}
}

static void	solve_linear(double *reduced, char letter)
{
	double	solution;

	printf("\n%sSolving linear equation:%s\n", GREEN, RESET);

	solution = -reduced[0] / reduced[1];
	
	printf("   %c = %s", letter, YELLOW);
	printf_number(solution);
	printf("%s", RESET);
}

static void	solve_quadratic(double *reduced, char letter)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	part1;
	double	part2;


	a = reduced[2];
	b = reduced[1];
	c = reduced[0];
	part1 = -b / (2 * a);
	discriminant = b * b - 4 * a * c;
	//Studing the three cases
	if (discriminant == 0)
	{
		printf("   \u0394 %s= 0%s (one real solution).\n", YELLOW, RESET);
		printf("\n%sSolving quadratic equation:%s\n", GREEN, RESET);
		printf("   %c = %s", letter, YELLOW);
		printf_number(part1);
		printf("%s (double)", RESET);
	}
	else if (discriminant > 0)
	{
		printf("   \u0394 %s> 0%s (two real solutions).\n", YELLOW, RESET);
		printf("\n%sSolving quadratic equation:%s\n", GREEN, RESET);
		part2 = ft_root(discriminant, 2) / (2 * a);
		if (part1 != 0)
		{
			printf("   %c1 = %s", letter, YELLOW);
			printf_number(part1 - part2);
			printf("%s\n", RESET);
			printf("   %c2 = %s", letter, YELLOW);
			printf_number(part1 + part2);
			printf("%s", RESET);
		}
		else
		{
			printf("   %c = %s\u00B1 ", letter, YELLOW);
			printf_number(part2);
			printf("%s", RESET);
		}
	}
	else //discriminant < 0
	{
		printf("   \u0394 %s< 0%s (two complex solutions).\n", YELLOW, RESET);
		printf("\n%sSolving quadratic equation:%s\n", GREEN, RESET);
		part2 = ft_root(-discriminant, 2) / (2 * a);
		if (part1 != 0)
		{
			printf("   %c = %s", letter, YELLOW);
			printf_number(part1);
			printf(" \u00B1 ");
			printf_number(part2);
			printf("i%s", RESET);
		}
		else
		{
			printf("   %c = %s\u00B1 ", letter, YELLOW);
			printf_number(part2);
			printf("i%s", RESET);
		}
	}
}

static void	solve_cubic(double *reduced, char letter)
{
	double	a;
	double	b;
	double	c;
	double	p;
	double	q;
	double 	discriminant;
	double	u;
	double	v;
	double	sol1;
	double	sol2;
	double	sol3;
	double 	realPart;
	double 	imaginaryPart;
	double	angle;

	a = reduced[2] / reduced[3];
	b = reduced[1] / reduced[3];
	c = reduced[0] / reduced[3];
	p = b - a * a / 3;
	q = 2 * a * a * a / 27 - a * b / 3 + c;
	discriminant = q * q / 4 + p * p * p / 27;

	if (discriminant > 0)
	{
		printf("   \u0394 %s> 0%s (one real solution and two complex).\n", YELLOW, RESET);
		printf("\n%sSolving cubic equation:%s\n", GREEN, RESET);
		
		u = ft_root(-q / 2 + ft_root(discriminant, 2), 3);
		v = ft_root(-q / 2 - ft_root(discriminant, 2), 3);
		sol1 = u + v - a / 3;
	
		printf("   %c1 = %s", letter, YELLOW);
		printf_number(sol1);
		printf("%s\n", RESET);
	
		realPart = -0.5 * (u + v) - a / 3;
		imaginaryPart = 0.5 * ft_root(3, 2) * (u - v);
		
		if (realPart == 0)
		{
			printf("   %c2 = \u00B1 %s", letter, YELLOW);
			printf_number(imaginaryPart);
			printf("i%s", RESET);
		}
		else
		{
			printf("   %c2 = %s", letter, YELLOW);
			printf_number(realPart);
			printf(" \u00B1 ");
			printf_number(imaginaryPart);
			printf("i%s", RESET);
		}
	}
	else if (discriminant == 0)
	{
		printf("   \u0394 %s= 0%s (two real solutions (one of them is double) or one triple solution).\n", YELLOW, RESET);
		printf("\n%sSolving cubic equation:%s\n", GREEN, RESET);
		
		sol1 = 2 * ft_root(-q / 2, 3) - a / 3;
		sol2 = -ft_root(-q / 2, 3) - a / 3; //This root is double
		
		if (sol1 == sol2)
		{
			printf("   %c = %s", letter, YELLOW);
			printf_number(sol1);
			printf("%s (triple)", RESET);
		}
		else
		{
			printf("   %c1 = %s", letter, YELLOW);
			printf_number(sol1);
			printf("%s\n", RESET);
			printf("   %c2 = %s", letter, YELLOW);
			printf_number(sol2);
			printf("%s (double)", RESET);
		}
	}
	else //discriminant < 0
	{
		printf("   \u0394 %s< 0%s (three real solutions).\n", YELLOW, RESET);
		printf("\n%sSolving cubic equation:%s\n", GREEN, RESET);
		
		angle = ft_arccos(1.5 * q / p * ft_root(-3 / p, 2)) / 3;
		sol1 = 2 * ft_root(-p / 3, 2) * ft_cos(angle) - a / 3;
		sol2 = 2 * ft_root(-p / 3, 2) * ft_cos(angle + 2 * PI / 3) - a / 3;
		sol3 = 2 * ft_root(-p / 3, 2) * ft_cos(angle + 4 * PI / 3) - a / 3;
		
		printf("   %c1 = %s", letter, YELLOW);
		printf_number(sol1);
		printf("%s\n", RESET);
		printf("   %c2 = %s", letter, YELLOW);
		printf_number(sol2);
		printf("%s\n", RESET);
		printf("   %c3 = %s", letter, YELLOW);
		printf_number(sol3);
		printf("%s\n", RESET);
	}
}

void	solve(char *str)
{
	int		degree;
	double	*reduced;
	char	letter;

	degree = calc_degree(str);
	reduced = reduce_equation(str, degree);
	if (!reduced)
		return ;
	degree = adjust_degree(reduced, degree);
	letter = get_letter(str);

	printf("\n%sEquation data:%s\n", GREEN, RESET);
	printf_reduced(reduced, degree, letter);
	printf("   Polynomial degree: %s%d%s\n", YELLOW, degree, RESET);
	
	switch (degree)
	{
		case 0:
			solve_equality(reduced, letter);
			break;
		case 1:
			solve_linear(reduced, letter);
			break;
		case 2:
			solve_quadratic(reduced, letter);
			break;
		case 3:
			solve_cubic(reduced, letter);
			break;
		default:
			printf("\n%sSolving equation:%s\n", GREEN, RESET);
			printf("   %sI can't solve equations with a degree greater than 3.%s", RED, RESET);
			break;
	}

	printf("\n\n");
	free(reduced);
}