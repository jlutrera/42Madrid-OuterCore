/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:10:06 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/04 09:10:06 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void apply_filter(t_point3 *color, t_filter_type type)
{
	if (type == GRAYSCALE)
	{
		double gray = 0.3 * color->x + 0.59 * color->y + 0.11 * color->z;
		color->x = gray;
		color->y = gray;
		color->z = gray;
	}
	else if (type == SEPIA)
	{
		double r = color->x * 0.393 + color->y * 0.769 + color->z * 0.189;
		double g = color->x * 0.349 + color->y * 0.686 + color->z * 0.168;
		double b = color->x * 0.272 + color->y * 0.534 + color->z * 0.131;
		color->x = fmin(r, 255);
		color->y = fmin(g, 255);
		color->z = fmin(b, 255);
	}
	else if (type == INVERT)
	{
		color->x = 255 - color->x;
		color->y = 255 - color->y;
		color->z = 255 - color->z;
	}
	else if (type == POSTERIZE)
	{
    	int levels = 4;
    	color->x = floor(color->x / (256 / levels)) * (256 / levels);
    	color->y = floor(color->y / (256 / levels)) * (256 / levels);
    	color->z = floor(color->z / (256 / levels)) * (256 / levels);
	}
}

void select_filter(t_context *ctx, guint type)
{
	if (type == GDK_KEY_N || type == GDK_KEY_n)
        ctx->scene->filter_type = ORIGINAL; // item 0

    else if (type == GDK_KEY_G || type  == GDK_KEY_g)
        ctx->scene->filter_type = GRAYSCALE; // item 1

    else if (type == GDK_KEY_E || type  == GDK_KEY_e)
        ctx->scene->filter_type = SEPIA; // item 2

    else if (type == GDK_KEY_I || type  == GDK_KEY_i)
        ctx->scene->filter_type = INVERT; // item 3

    else //if (type == GDK_KEY_P || type  == GDK_KEY_p)
        ctx->scene->filter_type = POSTERIZE; // item 4

	gsize item = ctx->scene->filter_type;
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ctx->filter_menu_items[item]), TRUE);
}

void draw_rgb_buffer(t_context *ctx)
{
	int width = ctx->scene->width;
	int height =ctx->scene->height;
	t_filter_type type = ctx->scene->filter_type;
	int **original = ctx->scene->rgb_buffer;
	int **filtered = ctx->scene->rgb_buffer_filtered;

	if (type == ORIGINAL)
	{
		for (int y = 0; y < height; y++)
   			memcpy(filtered[y], original[y], width * sizeof(int));
	}
	else
	{
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				int color = original[y][x];
				t_point3 colorrgb = {(color >> 16) & 0xFF,
                   	         		 (color >> 8) & 0xFF,
                   	        		  color & 0xFF};
				apply_filter(&colorrgb, type);
				filtered[y][x] = (((int)colorrgb.x << 16) | 
            				 	  ((int)colorrgb.y << 8)  |
								  ((int)colorrgb.z) );
			}
	}
	gtk_widget_queue_draw(ctx->drawing_area);
}
