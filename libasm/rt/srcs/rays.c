/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:33:31 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/06 17:35:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_point3	compute_pixel(t_vec n, t_scene scene, t_vec p, double shine, t_color color)
{
	t_point3	light;
	t_point3	shadow;
	t_point3	intensity;

	light = compute_lights(scene, p, n, shine);
	shadow = compute_shadows(scene, p, n, shine);
	intensity = point3((light.x - shadow.x) * color.r,
					   (light.y - shadow.y) * color.g,
					   (light.z - shadow.z) * color.b);
	return (intensity);
}

static t_point3 adjust_color(t_point3 color)
{
	color.x = fmax(0, fmin(255, color.x));
	color.y = fmax(0, fmin(255, color.y));
	color.z = fmax(0, fmin(255, color.z));
	
	return (color);
}

t_lst_obj	*get_closest(t_ray ray, t_lst_obj *obj, double *t_closest)
{
	t_point2	t;
	t_lst_obj *closest_obj = NULL;

	while (obj)
	{
		if (obj->object != ray.last_hit_object) // Ignorar el último objeto impactado
        {
			switch (obj->type)
			{
				case SPHERE		: intersect_sp(ray, obj, &t);
								  break;
				case PLANE		: intersect_pl(ray, obj, &t);
								  break;
				case CYLINDER	: intersect_cy(ray, obj, &t);
								  break;
				case CONE		: intersect_co(ray, obj, &t);
								  break;
				case PARABOLOID	: intersect_pa(ray, (t_paraboloid *)obj->object, &t);
								  break;
				case TORUS		: intersect_to(ray, (t_torus *)obj->object, &t);
								  break;
				case MOEBIUS	: intersect_moebius(ray, (t_moebius *)obj->object, &t);
								  break;
				default			:
								  break;
			}

			if ((t.x > EPSILON && t.x < *t_closest) || (t.y > EPSILON && t.y < *t_closest))
			{
				closest_obj = obj;
				*t_closest = fmin(*t_closest, fmin(t.x, t.y));
			}
		}
		obj = obj->next;
	}
	return closest_obj;
}

t_ray	construct_ray(t_point3 origin, t_vec dir)
{
	t_ray	ray;

	ray.origin = point3(origin.x, origin.y, origin.z);
	ray.dir = vec_unit(vec(dir.x, dir.y, dir.z));
	ray.last_hit_object = NULL;
	return (ray);
}

t_ray **precalculated_rays(t_camera *cam, int height, int width)
{
	// Configurar view port
	cam->viewp.z = 1;
	cam->viewp.x = 2 * cam->viewp.z * tan(cam->fov * M_PI / 360);
	cam->viewp.y = cam->viewp.x * height / width;

	// Configurar sistema de referencia desde la cámara
	cam->localbase.w = cam->direction;

	if (fabs(cam->localbase.w.y) + EPSILON < 1)
		cam->localbase.u = vec_unit(vec_cross(cam->localbase.w,  vec(0, 1, 0)));
	else
		cam->localbase.u = vec_unit(vec_cross(cam->localbase.w,  vec(1, 0, 0)));
	
	cam->localbase.v = vec_cross(cam->localbase.w, cam->localbase.u);

	// Precalcular los rayos para todos los píxeles de la imagen
	t_ray **rays = (t_ray **)malloc(sizeof(t_ray *) * height);
	if (!rays)
		return NULL;

	for (int i = 0; i < height; i++)
	{
        rays[i] = (t_ray *)malloc(sizeof(t_ray) * width);
		if (!rays[i])
		{
			for (int j = 0; j < i; j++)
				free(rays[j]);
			free(rays);
			return NULL;
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double u = (j - width / 2) * cam->viewp.x / width;
			double v = (i - height / 2) * cam->viewp.y / height;
			// Dirección del rayo en el espacio local
			t_vec dir = vec_add(cam->localbase.w,
							vec_add(vec_mul(cam->localbase.u, u),
									vec_mul(cam->localbase.v, v)));

			dir = vec_unit(dir);

			// Construir el rayo desde la posición de la cámara
			rays[i][j] = construct_ray(cam->position, dir);
		}
	}
	return rays; 
}

t_ray construct_secondary_ray(t_point3 origin, t_vec direction, void *last_hit)
{
    t_ray new_ray;
    new_ray.origin = origin;
    new_ray.dir = direction;
    new_ray.last_hit_object = last_hit;
    return new_ray;
}

t_vec	ray_at(t_ray ray, double t)
{
	return vec_add(ray.origin, vec_mul(ray.dir, t));
}

t_point3	trace_ray(t_ray ray, t_scene *scene, double n1, int depth_r, int depth_t)
{
	t_lst_obj	*closest_obj;
	double		t_closest = INFINITY;
	t_vec		p, n;
	t_point3	local_color;
	t_color 	obj_color;

	closest_obj = get_closest(ray, scene->obj, &t_closest);
	if (!closest_obj)
		return (point3(0,0,0));
	
	obj_color = closest_obj->color;
	p = ray_at(ray, t_closest);

	switch (closest_obj->type)
	{
		case SPHERE	   : n = get_sphere_normal(closest_obj, p);
						 if (closest_obj->texture)
							 obj_color = apply_texture_to_sphere(closest_obj, p);
						 break;
		case CYLINDER  : n = get_cylinder_normal(closest_obj, p);
						 if (closest_obj->texture)
							 obj_color = apply_texture_to_cylinder(closest_obj, p);
						 break;
		case CONE	   : n = get_cone_normal(closest_obj, p);
						 if (closest_obj->texture)
							 obj_color = apply_texture_to_cone(closest_obj, p);
						 break;
		case PLANE	   : n = get_plane_normal((t_plane *)closest_obj->object);
						 if (closest_obj->texture)
							 obj_color = apply_texture_to_plane(closest_obj, p);
						 break;
		case PARABOLOID: n = get_paraboloid_normal((t_paraboloid *)closest_obj->object, p);
						 break;
		case TORUS	   : n = get_torus_normal((t_torus *)closest_obj->object, ray, t_closest);
						 break;
		case MOEBIUS   : n = get_moebius_normal((t_moebius *)closest_obj->object, ray, t_closest);
						 break;
						 
		default		   : return adjust_color(local_color);
	}	

	// ---- Color local en la superficie
	local_color = compute_pixel(n, *scene, p, closest_obj->shine, obj_color);

	// Refracción
	if (closest_obj->transparency > 0.0 && depth_t < MAX_REFR_DEPTH)
	{
		t_point3 refracted = compute_refraction_color(ray.dir, n, p, scene,
			n1, depth_r, depth_t, closest_obj);
		local_color.x += local_color.x * (1 - closest_obj->transparency) +  refracted.x;
		local_color.y += local_color.y * (1 - closest_obj->transparency) +  refracted.y;
		local_color.z += local_color.z * (1 - closest_obj->transparency) +  refracted.z;
	}
	// Reflexión
	if (closest_obj->reflect > 0.0 && depth_r < MAX_REFL_DEPTH)
	{
		t_point3 reflected = compute_reflection_color(ray.dir, n, p, scene,
			n1, depth_r, depth_t, closest_obj->reflect);
		local_color.x += local_color.x * (1.0 - closest_obj->reflect) + reflected.x;
		local_color.y += local_color.y * (1.0 - closest_obj->reflect) + reflected.y;
		local_color.z += local_color.z * (1.0 - closest_obj->reflect) + reflected.z;
	}

	return adjust_color(local_color);
}
