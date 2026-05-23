/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:33:31 by jutrera-          #+#    #+#             */
/*   Updated: 2025/08/29 13:14:07 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*            Article : https://iquilezles.org/articles/filteringrm/          */
/*                                                                            */
/**************************************************************************** */
#include    "rt.h"

static t_color get_pixel(t_texture *tex, int x, int y)
{
    x = fmax(0, fmin(x, tex->width - 1));
    y = fmax(0, fmin(y, tex->height - 1));

    int index = (y * tex->width + x) * tex->channels;
    unsigned char r = tex->data[index];
    unsigned char g = tex->data[index + 1];
    unsigned char b = tex->data[index + 2];

    return (t_color){ r, g, b };
}

static t_color lerp_color(t_color a, t_color b, double t)
{
    // Clamp without branching
    t = (t < 0.0) ? 0.0 : (t > 1.0) ? 1.0 : t;
    
    return (t_color){
        .r = (int)(a.r + (b.r - a.r) * t + 0.5),
        .g = (int)(a.g + (b.g - a.g) * t + 0.5),
        .b = (int)(a.b + (b.b - a.b) * t + 0.5)
    };
}

static t_color checkers(double u, double v, double tiles_u, double tiles_v)
{
    t_color white = {255, 238, 201};  // Light color
    t_color black = {46, 25, 10};     // Dark color

    u = u * tiles_u;
    v = v * tiles_v;

    // Integer pattern with proper flooring
    int ui = (int)(u >= 0 ? u : u - 1);
    int vi = (int)(v >= 0 ? v : v - 1);
    
    // Perfect checker pattern
    return ((ui + vi) % 2 == 0) ? white : black;
}

t_color textures(double u, double v, t_texture *tex, double tiles_u, double tiles_v)
{
	if (strcmp(tex->name, "Checkerboard") == 0)
		return checkers(u, v,tiles_u, tiles_v);

// --- Para texturas de imagen, normalizar u y v a [0, 1) ---
    // fmod(x, 1.0) asegura que el valor esté entre 0 y 1 (o -1 y 0 si x es negativo)
    // Para manejar negativos y que siempre esté en [0, 1):
    u = fmod(u, 1.0);
    if (u < 0.0) u += 1.0;

    v = fmod(v, 1.0);
    if (v < 0.0) v += 1.0;
    // --------------------------------------------------------

    int x = (int)(u * (tex->width - 1));
    // (1 - v) es para invertir el eje Y al tener la imagen (0,0) en la parte superior izquierda
    int y = (int)((1 - v) * (tex->height - 1)); 

    double tx = (u * (tex->width - 1)) - x;
    double ty = ((1 - v) * (tex->height - 1)) - y;

    t_color c00 = get_pixel(tex, x, y);
    t_color c10 = get_pixel(tex, x + 1, y);
    t_color c01 = get_pixel(tex, x, y + 1);
    t_color c11 = get_pixel(tex, x + 1, y + 1);

    t_color cx0 = lerp_color(c00, c10, tx);
    t_color cx1 = lerp_color(c01, c11, tx);
    
    return lerp_color(cx0, cx1, ty);
}
