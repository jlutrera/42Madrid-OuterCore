/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:31:57 by jutrera-          #+#    #+#             */
/*   Updated: 2024/07/30 14:31:57 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static bool isinteger(double num)
{
	int part_int;

	part_int = (int)num;
	return (num - part_int) == 0.0;
}

static bool printf_error(char *msg, char *s, int i)
{
	int n;

	printf("%sError%s: ", RED, RESET);
	printf("%s => ", msg);
	n= 0;
	while (n < i && s[n] != '\0')
		printf("%c", s[n++]);
	if (s[n] != '\0')
	{
		printf("%s%c", RED, s[n++]);
		if (i == -1)
			printf("%s", RED);
		else
			printf("%s", RESET);
		while (s[n] != '\0')
			printf("%c", s[n++]);
	}
	printf("%s\n", RESET);
	return 1;
}

static void	remove_spaces(char* source)
{
	char	*i;  // Pointer which moves up the string and makes the result
	char	*j;  // Pointer which goes the original string

	i = source;
	j = source;
	while (*j != '\0')
	{
		if (*j != ' ')
		{
			*i = tolower((unsigned char)*j);
			i++;
		}
		j++;
	}
	*i = '\0';
}

bool	bad_letters(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (isalpha(s[i]))
		{
			while (s[i] && isalpha(s[i]))
				++i;
			while (s[i] && isblank(s[i]))
				++i;
			if (s[i] && isalpha(s[i]))
				return printf_error("Invalid variable format.", s, i);
		}
		else
			++i;
	}
	
	return 0;
}

bool	bad_digits(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (isdigit(s[i]) || s[i] == '.')
		{
			while (s[i] && (isdigit(s[i]) || s[i] == '.'))
				++i;
			while (s[i] && isblank(s[i]))
				++i;
			if (s[i] && (isdigit(s[i]) || s[i] == '.'))
				return printf_error("Invalid number format.", s, i);
		}
		else
			++i;
	}
	
	return 0;
}

bool	syntax_error_equation(char *str)
{
	int 	i;
	int 	equalSign;
	char 	letter;
	bool 	isPower;

	i = 0;
	equalSign = 0;
	letter = 0;
	isPower = 0;

	remove_spaces(str);

	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			equalSign++;
			if (equalSign > 1 || i == 0)
				return printf_error("There is an issue with equal symbol", str, i);
			if (str[i+1] == '\0')
				return printf_error("Unexpected equation ending", str, i);
			i++;
			isPower = 0;
		}
		else if (isalpha(str[i]))
		{
			if (!letter)
				letter = str[i];
			else if (letter != str[i])
				return printf_error("Only one variable name must be written", str, i);
			i++;
			if (str[i] != '^' && str[i] != '\0' && str[i] != '+' && str[i] != '-' && str[i] != '=')	
				return printf_error("Invalid symbol after variable", str, i);
			isPower = 0;
		}
		else if (str[i] == '^')
		{
			isPower = 1;
			if (str[i+1] == '\0')
				return printf_error("Invalid symbol found", str, i);
			i++;
			if (!isdigit(str[i]))
				return printf_error("Invalid symbol found", str, i);
		}
		else if (str[i] == '+' || str[i] == '-')
		{
			i++;
			if (str[i] == '\0')
				return printf_error("Unexpected equation ending", str, i-1);
			if (!isalpha(str[i]) && !isdigit(str[i]))
				return printf_error("Invalid symbol found", str, i);
			isPower = 0;
		}
		else if (str[i] == '*' && i != 0)
		{
			if (str[i+1] == '\0')
				return printf_error("Unexpected equation ending", str, i);
			i++;
			if (!isalpha(str[i]))
				return printf_error("It must be [number]*[variable]", str, i);
			isPower = 0;
		}
		else if (str[i] == '.')
		{
			if (i == 0 || !isdigit(str[i-1]))
				return printf_error("Invalid symbol found", str, i);
			if (isPower == 1)
				return printf_error("Degree has to be an integer", str, i);
			i++;
			if (!isdigit(str[i]))
				return printf_error("Invalid symbol found", str, i);
		}
		else if (isdigit(str[i]))
		{
			i++;	
		}
		else if (str[i] != '\0')
			return printf_error("Invalid symbol found", str, i);
	}

	if (equalSign == 0)
		return printf_error("Invalid syntax. No equal symbol found", str, -1);

	if (i < 2)
		return printf_error("Invalid syntax. No equation found", str, -1);

	return 0;
}

int calc_degree(char *str)
{
	int 	i;
	int 	degree;
	int		tmp; 

	i = 0;
	degree = 0;
	while (str[i] != '\0')
	{
		if (isalpha(str[i]) && degree == 0)
			degree = 1;
		else if (str[i] == '^')
		{
			i++;
			tmp = 0;
			while (isdigit(str[i]))
			{
				tmp *= 10;
				tmp += str[i] - '0';
				i++;
			}
			if (tmp > degree)
				degree = tmp;
		}
		if (str[i] != '\0')
			i++;
	}
	return degree;
}

int	adjust_degree(double *reduced, int degree)
{
	int	i;

	i = degree;
	while (i > 0 && reduced[i] == 0)
		i--;
	return i;
}

char get_letter(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (isalpha(str[i]))
			return str[i];
		i++;
	}
	return 0;
}

void	printf_number(double d)
{
	if (d < 0 + PRECISION && d > 0 - PRECISION)
		printf("0");
	else if (isinteger(d))
		printf("%0.0f", d);
	else
		printf("%0.2f", d);
}