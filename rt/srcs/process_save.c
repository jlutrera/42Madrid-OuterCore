/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:24:55 by jutrera-          #+#    #+#             */
/*   Updated: 2025/03/24 22:24:55 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"rt.h"

static char *append_png(const char *filename)
{
	if (!filename)
		return NULL;

	// Verificar si el nombre ya tiene la extensión .png
	if (strstr(filename, ".png") != NULL)
		return strdup(filename);

	// Crear nuevo nombre de archivo con la extensión .png
	size_t len = strlen(filename);
	char *new_filename = malloc(len + 5); // +5 para ".png" y '\0'
	if (!new_filename)
		return NULL;

	sprintf(new_filename, "%s.png", filename);
	return new_filename;
}

int process_save(gchar *filename, t_context *ctx)
{
	if (!ctx->scene->camera)
		return NO_SCENE_E;

	char *png_filename = append_png(filename);
	if (png_filename)
	{
	 	save_png(png_filename, ctx->scene);
 		free(png_filename);
	}
	return SUCCESS;
}
