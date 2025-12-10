/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:30:33 by jutrera-          #+#    #+#             */
/*   Updated: 2024/07/30 14:30:33 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static double ft_power(double base, int exponent)
{
	double result;
	
	result = 1.0;
	for (int i = 0; i < exponent; i++)
		result *= base;

	return result;
}

static unsigned long long	ft_factorial(int n)
{
	unsigned long long result;

	result = 1;
	for (int i = 2; i <= n; i++)
		result *= i;

	return result;
}

double	ft_root(double a, int n)
{
	double	x;
	double	diference;
	double	xBefore;
	double	xPower;

	if (a == 0 || a== 1)
		return a;

	x = a;
	do
	{
		xBefore = x;
		xPower = ft_power(x, n - 1);
		x = (1.0 / n) * ((n - 1) * x + a / xPower);
		diference = x > xBefore ? x - xBefore : xBefore - x;
	}
	while (diference > PRECISION);

	return x;
}

double	ft_cos(double x)
{
	double	term;
	double	sum;

	sum = 0;
	for (int n = 0; n < TAYLOR_TERMS; n++)
	{
		term = ft_power(-1, n) * ft_power(x, 2*n) / ft_factorial(2*n);
		sum += term;
	}

	return sum;
}

double ft_arccos(double x)
{
	double term;
	double sum;

	if (x == 1)
		return 0;
	if (x == -1)
		return PI;

	sum = 0;
	for (int n = 0; n < TAYLOR_TERMS; n++)
	{
		term = (ft_factorial(2 * n) / (ft_power(4, n) * ft_power(ft_factorial(n), 2) * (2 * n + 1))) * ft_power(x, 2 * n + 1);
		sum += term;
	}

	return PI / 2 - sum;
}
