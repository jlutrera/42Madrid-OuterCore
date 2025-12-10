/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:30:20 by jutrera-          #+#    #+#             */
/*   Updated: 2024/07/30 14:30:20 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "computor.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("%sError%s: Invalid number of arguments.", RED, RESET);
		printf("Please, type %s./computor \"[equation]\"%s\n", YELLOW, RESET);
		return 1;
	}

	if (bad_digits(argv[1]) || bad_letters(argv[1]) || syntax_error_equation(argv[1]))
		return 1;
	
	solve(argv[1]);

	return 0;
}
