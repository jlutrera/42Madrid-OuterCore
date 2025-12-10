/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:30:51 by jutrera-          #+#    #+#             */
/*   Updated: 2024/07/30 14:30:51 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

double	*reduce_equation(char *str, int degree)
{
	double	*tmp;
	double 	coefficient;
	double	n;
	int		i;
	int		sign;
	int 	deg;
	int 	minus;
	int 	decimal;

	tmp = (double *)calloc(degree + 1, sizeof(double));
	if (!tmp)
		exit(EXIT_FAILURE);

	i = 0;
	sign = 1;
	coefficient = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			sign = -1;
			i++;
		}
		else if (isalpha(str[i]))
		{
			if ( i > 0 && str[i-1] == '-')
				coefficient = -1;
			if (str[i+1] == '^')
			{
				i += 2;
				deg = 0;
				while (isdigit(str[i]) && str[i] != '\0')
				{
					deg = 10 * deg + str[i] - '0';
					i++;
				}
			}
			else
			{
				deg = 1;
				i++;
			}
			tmp[deg] += coefficient * sign;
			coefficient = 1;
		}
		else if (isdigit(str[i]))
		{
			if (i > 0 && str[i-1] == '-')
				minus = -1;
			else
				minus = 1;
			coefficient = 0;
			while (isdigit(str[i]) && str[i] != '\0')
			{
				coefficient *= 10;
				coefficient += str[i] - '0';
				i++;
			}
			if (str[i] == '.')
			{
				i++;
				decimal = 10.0;
				
				while (isdigit(str[i]) && str[i] != '\0')
				{
					n = str[i] - '0';
					coefficient += n / decimal;
					decimal *= 10;
					i++;
				}
				if (str[i] == '.')
				{
					printf("%sError%s: Bad format in decimal number.\n", RED, RESET);
					free(tmp);
					return NULL;
				}
			}
			coefficient *= minus;
			if (str[i] == '*')
				i++;	
			if (!isalpha(str[i]))
			{
				tmp[0] += coefficient * sign;
				coefficient = 1;
			}
		}
		else
			i++;
	}
	return tmp;
}

void	printf_reduced(double *reduced, int degree, char letter)
{
	int 	i;
	bool	allIsZero;

	printf("   Reduced form: %s", YELLOW);
	i = degree;
	allIsZero = 0;
	while (i >= 0)
	{
		if (reduced[i] != 0)
		{
			allIsZero = 1;
			if (reduced[i] > 0 && i != degree)
				printf("+");
			if (i == 0)
			{
				printf_number(reduced[i]);
				printf(" ");
			}
			else if (i == 1)
			{
				if (reduced[i] != 1 && reduced[i] != -1)
					printf_number(reduced[i]);
				if (reduced[i] == -1)
					printf("-");
				printf("%c ", letter);
			}
			else
			{
				if (reduced[i] != 1 && reduced[i] != -1)
					printf_number(reduced[i]);
				if (reduced[i] == -1)
					printf("-");
				printf("%c^%d ", letter, i);
			}
		 }
		i--;
	}

	if (allIsZero == 0)
		printf("0 ");
	printf("= 0%s\n", RESET);
}
