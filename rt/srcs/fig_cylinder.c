/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:38:14 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/27 22:00:44 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color cylinder_disk_uv(t_lst_obj *obj, t_vec p)
{
	t_cylinder *cy = (t_cylinder *)obj->object;
	double radius = cy->radius;
	t_vec center = cy->coordinate; // Centro de la base
	t_vec normal = cy->direction; // Normal de la base

	t_vec pc = vec_sub(p, center); // Vector desde centro al punto

	// Construir base ortonormal del plano de la base
	t_vec up = (fabs(normal.y) < 0.99) ? (t_vec){0, 1, 0} : (t_vec){1, 0, 0};
	t_vec u_dir = vec_unit(vec_cross(up, normal));
	t_vec v_dir = vec_cross(normal, u_dir);

	// Proyectar el punto en el plano de la base
	double u_proj = vec_dot(pc, u_dir);
	double v_proj = vec_dot(pc, v_dir);

	// Normalizar a [0,1] (el disco va de -radius a +radius en ambas direcciones)
	double u = 0.5 + u_proj / (2.0 * radius);
	double v = 0.5 + v_proj / (2.0 * radius);

	double tiles = cy->radius * 4;
	return textures(u, v, obj->texture, tiles, tiles);
}

static t_color cylinder_lateral_uv(t_lst_obj *obj, t_vec p)
{
	t_cylinder *cy = (t_cylinder *)obj->object;
	
	t_vec	axis = cy->direction; // Debe ser unitario
	t_vec	pc = vec_sub(p, cy->coordinate); // Vector desde base al punto
	double	h = vec_dot(pc, axis);           // Proyección sobre el eje (altura local)

	// Construir sistema ortonormal perpendicular al eje
	t_vec	up = (fabs(axis.y) < 0.99) ? (t_vec){0, 1, 0} : (t_vec){1, 0, 0};
	t_vec	u_dir = vec_unit(vec_cross(up, axis));      // Primer eje perpendicular
	t_vec	v_dir = vec_cross(axis, u_dir);             // Segundo eje perpendicular

	// Proyectar pc sobre el plano perpendicular al eje
	t_vec	proj = vec_sub(pc, vec_mul(axis, h));

	// Coordenada u (ángulo alrededor del eje)
	double	theta = atan2(vec_dot(proj, v_dir), vec_dot(proj, u_dir));
	double u = 0.5 + theta / (2.0 * M_PI);
	// Coordenada v (posición relativa a lo largo del eje)
	double v = h / cy->height;
	// Clamp opcional para mantener [0,1]
	if (u < 0) u += 1.0;
	if (u > 1) u -= 1.0;

	double tiles_u = 2.0 * M_PI * cy->radius * 2; // número de cuadros en dirección angular
	double tiles_v = cy->height * 2;  

	return textures(u, v, obj->texture, tiles_u, tiles_v);
}

static double t_calc(t_ray ray, double t, t_vec point, double radius)
{
	if (t < EPSILON)
		return INFINITY;
	t_vec p = ray_at(ray, t);
	if (vec_length(vec_sub(p, point)) - radius > EPSILON)
		return INFINITY;
	else
		return t;
}

static t_point2 intersect_disk(t_ray ray, t_cylinder *cy)
{
	double denom, num, t1, t2;
	t_vec normal = cy->direction;
	denom = vec_dot(normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return point2(INFINITY, INFINITY); // Ray is parallel to the disk

	t_vec cy_bottom = cy->coordinate;
	num = vec_dot(normal, vec_sub(cy_bottom, ray.origin));
	t1 = t_calc(ray, num / denom, cy_bottom, cy->radius);

	t_vec cy_top = vec_add(cy->coordinate, vec_mul(normal, cy->height));
	num = vec_dot(normal, vec_sub(cy_top, ray.origin));
	t2 = t_calc(ray, num / denom, cy_top, cy->radius);
	
	return point2(t1, t2);
}

static t_point2	intersect_lateral(t_cylinder *cy, t_vec oc, t_vec od, t_ray ray)
{
	double	a, b, c, discriminant, t1, t2;
	t_point2 res = point2(INFINITY, INFINITY);

	a = vec_dot(od, od);
	b = 2 * vec_dot(oc, od);
	c = vec_dot(oc, oc) - cy->radius * cy->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		return res;
	
	double sqrt_disc = sqrt(discriminant);
	t1 = (-b + sqrt_disc) / (2 * a);
	t2 = (-b - sqrt_disc) / (2 * a);
	
	if (t1 > EPSILON)
	{
		t_vec p1 = ray_at(ray, t1);
		double h1 = vec_dot(vec_sub(p1, cy->coordinate), cy->direction);
		if (h1 > EPSILON && h1 < cy->height - EPSILON)
			res.x = t1;
	}
	if (t2 > EPSILON)
	{
		t_vec p2 = ray_at(ray, t2);
		double h2 = vec_dot(vec_sub(p2, cy->coordinate), cy->direction);
		if (h2 > EPSILON && h2 < cy->height - EPSILON)
			res.y = t2;
	}
	return res;
}

t_color apply_texture_to_cylinder(t_lst_obj *obj, t_vec p)
{
	t_cylinder *cy = (t_cylinder *)obj->object;
	
	t_vec	pc = vec_sub(p, cy->coordinate); // Vector desde base al punto
	double	h = vec_dot(pc, cy->direction);  // Proyección sobre el eje (altura local)

	if (fabs(h) < EPSILON || fabs(h - cy->height) < EPSILON)
		return cylinder_disk_uv(obj, p);
	
	return cylinder_lateral_uv(obj, p);
}

void	intersect_cy(t_ray ray, t_lst_obj *obj, t_point2 *t)
{
	t_cylinder	*cy = (t_cylinder *)obj->object;
	t_vec	cd = cy->direction;

	t_vec	od;
	od = vec_sub(ray.dir, vec_mul(cd, vec_dot(ray.dir, cd)));
	if (vec_length(od) < EPSILON)
		od = vec(ray.dir.y, -ray.dir.x, ray.dir.z);

	t_vec oc;
	oc = vec_sub(ray.origin, cy->coordinate);
	oc = vec_sub(oc, vec_mul(cd, vec_dot(oc, cd)));
	
	t_point2 t_lateral = intersect_lateral(cy, oc, od, ray);
	t_point2 t_base = intersect_disk(ray, cy);

	*t = point2(INFINITY, INFINITY);
	if (t_base.x    == INFINITY && t_base.y == INFINITY &&
		t_lateral.x == INFINITY && t_lateral.y == INFINITY)
		return;

	double t_vals[4] = {t_lateral.x, t_lateral.y, t_base.x, t_base.y};
	double t_in = INFINITY;
	double t_out = -INFINITY;
	for (int i = 0; i < 4; i++)
	{
		if (t_vals[i] == INFINITY)
			continue;
		if (t_vals[i] < t_in)
			t_in = t_vals[i];
		if (t_vals[i] > t_out)
			t_out = t_vals[i];
	}
	double t_cut = t_in_the_slices(obj->slices, ray, t_in, t_out);

	*t = point2(t_cut, t_cut);
}

t_vec	get_cylinder_normal(t_lst_obj *obj, t_vec p)
{
	t_cylinder *cy = (t_cylinder *)obj->object;
	t_slices	*s = obj->slices;

	t_vec	cp = vec_sub(p, cy->coordinate);
	double	h = vec_dot(cp, cy->direction);

	// Base inferior
	if (fabs(h) < EPSILON)
		return vec_mul(cy->direction, -1); // base inferior

	// Base superior
	if (fabs(h - cy->height) < EPSILON)
		return cy->direction; // base superior

	// Cara lateral
	t_vec	proj = vec_mul(cy->direction, h);
	t_vec	normal = vec_sub(cp, proj);
	double inside = cy->radius - vec_length(normal);

	while (s)
	{	
		if (inside > EPSILON && p_over_slice(s->slice, p) == 0)
			return s->slice.direction;
		s = s->next;
	}

	return vec_unit(normal);
}
