/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:33:35 by jutrera-          #+#    #+#             */
/*   Updated: 2025/03/09 20:33:35 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"rt.h"

int process_load(gchar *filename, t_context *ctx)
{
	int		error;
	t_scene	*aux = init_scene();

	if (!aux)
		return MEMORY_E;
	
	error = parse_file(filename, aux, ctx);
	if (error != SUCCESS)
	{
		free_scene(aux);
		return error;
	}
	
	aux->filter_type = ctx->scene->filter_type;
	free_scene(ctx->scene);
	ctx->scene = aux;
	t_camera *cam = aux->camera;
	while (cam)
	{
		cam->prec_rays = precalculated_rays(cam, aux->height, aux->width);
		if (cam->prec_rays == NULL)
		{
			free_scene(aux);
			return MEMORY_E;
		}
		cam = cam->next;
	}
	set_status_label(ctx->status_label, "Rendering image ...");
    
	render_scene(ctx);

	return SUCCESS;
}
