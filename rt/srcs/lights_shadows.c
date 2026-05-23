/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_shadows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:12:17 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/04 11:15:12 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_point3	calc_int(t_point3 p, double d, t_color color)
{
	return  point3(	p.x + d * color.r / 255,
					p.y + d * color.g / 255,
					p.z + d * color.b / 255);
}

static t_point3	compute_int(t_vec n, t_vec l, double bright, t_color color, t_camera *camera, double shine)
{
	t_point3 intensity = point3(0, 0, 0);
	t_vec r = vec_sub(vec_mul(n, 2 * vec_dot(n, l)), l);

	double dot_v = vec_dot(n, l) * bright;
	if (dot_v > EPSILON)
		intensity = calc_int(intensity, dot_v, color);
		
	dot_v = vec_dot(r, vec_mul(camera->direction, -1));
	if (dot_v >= EPSILON)
	{
		double coef = bright * pow(dot_v / (vec_length(r) * vec_length(camera->direction)), shine);
		intensity = calc_int(intensity, coef, color);
	}
	return (intensity);
}

t_point3	compute_shadows(t_scene scene, t_vec p, t_vec n, double shine)
{
	t_point3	tmp;
	t_ray		ray;
	t_vec 		l;
	t_point3 	intensity = point3(0, 0, 0);
	double		t_closest;
	t_lst_obj	*closest_obj;

	// Spotlights shadows
	t_spotlight	*spotlight = scene.spotlight;
	while (spotlight)
	{
		t_closest = vec_length(vec_sub(spotlight->position, p));
		l = vec_unit(vec_sub(spotlight->position, p));
		ray = construct_ray(p, l);
		closest_obj = get_closest(ray, scene.obj, &t_closest);
		if (closest_obj)
		{
			
			tmp = compute_int(n, l, spotlight->bright, spotlight->color, scene.camera, shine);
			intensity = point3(intensity.x + tmp.x, intensity.y + tmp.y, intensity.z + tmp.z);
			intensity.x *= (1 - closest_obj->transparency);
			intensity.y *= (1 - closest_obj->transparency);
			intensity.z *= (1 - closest_obj->transparency);
		}
		spotlight = spotlight->next;
	}

	// Parallel shadow
	t_directional directional = scene.directional;
	if (directional.declared)
	{
		t_closest = INFINITY;
		l = vec_mul(directional.direction, -1);
		ray = construct_ray(p, l);
		closest_obj = get_closest(ray, scene.obj, &t_closest);
		if (closest_obj)
		{
			tmp = compute_int(n, l, directional.bright, directional.color, scene.camera, shine);
			intensity = point3(intensity.x + tmp.x, intensity.y + tmp.y, intensity.z + tmp.z);
			intensity.x *= (1 - closest_obj->transparency);
			intensity.y *= (1 - closest_obj->transparency);
			intensity.z *= (1 - closest_obj->transparency);
		}
	}
	
	return (intensity);
}

t_point3	compute_lights(t_scene scene, t_vec p, t_vec n, double shine)
{
	t_vec		l;
	t_point3	tmp;
	t_point3	intensity = point3(0, 0, 0);

	t_camera	*camera = scene.camera;
	while (!camera->active)
		camera = camera->next;

	// Spotlights
	t_spotlight	*spotlight = scene.spotlight;
	while (spotlight)
	{
		l = vec_unit(vec_sub(spotlight->position, p));
		tmp = compute_int(n, l, spotlight->bright, spotlight->color, camera, shine);
		intensity = point3(intensity.x + tmp.x, intensity.y + tmp.y, intensity.z + tmp.z);
		spotlight = spotlight->next;
	}

	// Parallel light
	t_directional  directional = scene.directional;
	if (directional.declared)
	{
		l = directional.direction;
		l = vec_mul(l, -1);
		
		tmp = compute_int(n, l, directional.bright, directional.color, camera, shine);
		intensity = point3(intensity.x + tmp.x, intensity.y + tmp.y, intensity.z + tmp.z);
	}

	// Ambient light
	t_ambient	ambient = scene.ambient;
	intensity = calc_int(intensity, ambient.bright, ambient.color);
	return (intensity);
}
