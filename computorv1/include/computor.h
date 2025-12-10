/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:30:36 by jutrera-          #+#    #+#             */
/*   Updated: 2024/07/30 14:30:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_H
# define COMPUTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <ctype.h>

# define PI				3.141592653589793
# define PRECISION		1e-15
# define TAYLOR_TERMS	10

# define RED 	"\033[1;31m"
# define GREEN 	"\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET 	"\033[0m"

// maths.c
double	ft_root(double a, int n);
double	ft_cos(double x);
double	ft_arccos(double x);
// reduce.c
double	*reduce_equation(char *str, int degree);
void	printf_reduced(double *reduced, int degree, char letter);
// solve.c
void	solve(char *str);
// utils_eq.c
bool	syntax_error_equation(char *str);
int 	calc_degree(char *str);
int		adjust_degree(double *reduced, int degree);
char 	get_letter(char *str);
void	printf_number(double d);
bool	bad_digits(char *s);
bool	bad_letters(char *s);

#endif
