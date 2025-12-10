/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:51 by jutrera           #+#    #+#             */
/*   Updated: 2025/08/26 22:51:15 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int main(int argc, char *argv[]) 
{
    t_context *ctx;

    (void)argv;

    if (argc != 1)
	{
		printf("Arguments are not allowed\n");
		return (ARGC_E);
	}

    gtk_init(&argc, &argv);

    ctx = init_gui();
    if (!ctx)
        return EXIT_FAILURE;

    gtk_main();
    
    free_scene(ctx->scene);
    free(ctx);

    return EXIT_SUCCESS;
}
