/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stb_impl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:38:13 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/02 12:20:33 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define     STB_IMAGE_IMPLEMENTATION
#include	"stb_image.h"
#define    	STB_IMAGE_WRITE_IMPLEMENTATION
#include	"stb_image_write.h"

#include    "rt.h"

t_texture *load_texture(const gchar *filename)
{
	t_texture *tex = malloc(sizeof(t_texture));
	if (!tex)
		return NULL;
    
    if (strcmp(filename, "Checkerboard") == 0)
	{
		tex->name = strdup("Checkerboard");
		tex->data = NULL;
		tex->width = 0;
		tex->height = 0;
		tex->channels = 0;
		return tex;
	}

	tex->data = stbi_load(filename, &tex->width, &tex->height, &tex->channels, 3);
	if (!tex->data)
	{
		free(tex);
		return NULL;
	}
	tex->name = strdup(filename);
	tex->channels = 3;
	return tex;
}

int save_png(char *filename, t_scene *scene)
{
    int width = scene->width;
    int height = scene->height;

	int **rgb_buffer;
    if (scene->filter_type == ORIGINAL)
        rgb_buffer = scene->rgb_buffer;
    else
        rgb_buffer = scene->rgb_buffer_filtered;

    unsigned char *rgb = malloc(width * height * 3);
    if (!rgb)
        return MEMORY_E;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int color = rgb_buffer[y][x]; // Extraemos el pixel de la matriz

            // Extraemos componentes RGB suponiendo 0x00RRGGBB
            unsigned char r = (color >> 16) & 0xFF;
            unsigned char g = (color >> 8) & 0xFF;
            unsigned char b = color & 0xFF;

            int dst = (y * width + x) * 3;
            rgb[dst + 0] = r;
            rgb[dst + 1] = g;
            rgb[dst + 2] = b;
        }
    }

    int ok = stbi_write_png(filename, width, height, 3, rgb, width * 3);
    free(rgb);

    if (!ok)
        return FILE_E;

    return SUCCESS;
}

void free_texture(t_texture *tex)
{
    if (tex)
    {
        if (tex->data)
            stbi_image_free(tex->data);
        if (tex->name)
            free(tex->name);
        free(tex);
    }
}
