/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:38:21 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/27 21:59:52 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color cone_disk_uv(t_lst_obj *obj, t_vec p)
{
	t_cone *co = (t_cone *)obj->object;
	double radius = co->radius;
	t_vec center = co->coordinate; // Centro de la base
	t_vec normal = co->direction; // Normal de la base

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

	double tiles = co->radius * 4.0;
	return textures(u, v, obj->texture, tiles, tiles);
}

static t_color cone_lateral_uv(t_lst_obj *obj, t_vec p)
{
	t_cone *co = (t_cone *)obj->object;
	// Base y eje
	t_vec axis = co->direction; // Unitario
	t_vec base = co->coordinate;
	t_vec apex = vec_add(base, vec_mul(axis, co->height));

	// Vector del vértice al punto de intersección
	t_vec ap = vec_sub(p, apex);
	double h = vec_dot(ap, axis); // Proyección sobre el eje → altura relativa desde vértice

	// Coordenada v: altura relativa desde la base
	double v = 1.0 - (h / co->height);

	// Base ortonormal en el plano perpendicular al eje
	t_vec up = (fabs(axis.y) < 0.99) ? (t_vec){0, 1, 0} : (t_vec){1, 0, 0};
	t_vec u_dir = vec_unit(vec_cross(up, axis));
	t_vec v_dir = vec_cross(axis, u_dir);

	// Proyección sobre plano perpendicular para calcular ángulo
	t_vec proj = vec_sub(ap, vec_mul(axis, h));
	double theta = atan2(vec_dot(proj, v_dir), vec_dot(proj, u_dir));

	double u = 0.5 + theta / (2.0 * M_PI);
	if (u < 0) u += 1.0;
	if (u > 1) u -= 1.0;

	double generatriz = sqrt(co->radius * co->radius + co->height * co->height);
	double tiles_u = 2.0 * M_PI * co->radius * 2.0;
	double tiles_v = generatriz * 2.0;
	return textures(u, v, obj->texture, tiles_u, tiles_v);
}

static double	intersect_disk(t_ray ray, t_cone *cone)
{
	double	denom, num, t;
	t_vec	p;

	denom = vec_dot(cone->direction, ray.dir);
	if (fabs(denom) < EPSILON)
		return (INFINITY);

	num = vec_dot(cone->direction, vec_sub(cone->coordinate, ray.origin));
	t = num / denom;
	if (t < EPSILON)
		return (INFINITY);

	p = ray_at(ray, t);
	if (vec_length(vec_sub(p, cone->coordinate)) - cone->radius > EPSILON)
		return (INFINITY);

	return (t);
}

static t_point2	intersect_lateral(t_cone *co, t_vec d, t_vec v, t_ray ray)
{
	double	a, b, c, x;
	t_point2 res = point2(INFINITY, INFINITY);
	t_vec	oc;

	oc = vec_add(co->coordinate, vec_mul(co->direction, co->height));
	oc = vec_sub(ray.origin, oc);
	x = 1 + pow(co->radius / co->height, 2);
	a = vec_dot(d, d) - x * pow(vec_dot(d, v), 2);
	b = 2 * (vec_dot(d, oc) - x * vec_dot(d, v) * vec_dot(oc, v));
	c = vec_dot(oc, oc) - x * pow(vec_dot(oc, v), 2);
	
	double discriminant  = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		return res;

	double sqrt_disc = sqrt(discriminant);
	double t1 = (-b + sqrt_disc) / (2 * a);
	double t2 = (-b - sqrt_disc) / (2 * a);

    if (t1 > EPSILON)
	{
		t_vec p1 = ray_at(ray, t1);
		double h1 = vec_dot(vec_sub(p1, co->coordinate), co->direction);
		if (h1 > EPSILON && h1 < co->height - EPSILON)
			res.x = t1;
	}
	if (t2 > EPSILON)
	{
		t_vec p2 = ray_at(ray, t2);
		double h2 = vec_dot(vec_sub(p2, co->coordinate), co->direction);
		if (h2 > EPSILON && h2 < co->height - EPSILON)
			res.y = t2;
	}
	return res;
}

t_color apply_texture_to_cone(t_lst_obj *obj, t_vec p)
{
	t_cone *co = (t_cone *)obj->object;

	t_vec	pc = vec_sub(p, co->coordinate); // Vector desde base al punto
	double	h = vec_dot(pc, co->direction); // Proyección sobre el eje (altura
	if (fabs(h) < EPSILON)
		return cone_disk_uv(obj, p);
	
	return cone_lateral_uv(obj, p);
}

void	intersect_co(t_ray ray, t_lst_obj *obj, t_point2 *t)
{
	t_cone	*cone = (t_cone *)obj->object;

	t_vec v = vec_mul(cone->direction, -1);
	t_point2 t_lateral = intersect_lateral(cone, ray.dir, v, ray);
	double t_base = intersect_disk(ray, cone);
	
	*t = point2(INFINITY, INFINITY);
	if (t_base == INFINITY && t_lateral.x == INFINITY && t_lateral.y == INFINITY)
		return;
	
	double t_vals[3] = {t_lateral.x, t_lateral.y, t_base};
	double t_in = INFINITY;
	double t_out = -INFINITY;
	for (int i = 0; i < 3; i++)
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

t_vec	get_cone_normal(t_lst_obj *obj, t_vec p)
{
	t_cone	*cone = (t_cone *)obj->object;
	t_slices	*s = obj->slices;

	t_vec	cp = vec_sub(p, cone->coordinate);
	double	h = vec_dot(cp, cone->direction);

	// Base
	if (fabs(h) < EPSILON)
		return vec_mul(cone->direction, -1); // base

	// Cara lateral
	t_vec	a = cone->direction;
	double	k = cone->radius / cone->height;
	t_vec	proj = vec_mul(a, h);
	t_vec	normal = vec_sub(cp, proj);
	normal = vec_unit(normal);
	normal = vec_sub(normal, vec_mul(a, k)); // ajustar con pendiente

	double inside = cone->radius - vec_length(normal);

	while (s)
	{
		if (inside > EPSILON && p_over_slice(s->slice, p) == 0)
			return s->slice.direction;
		s = s->next;
	}
	return vec_unit(normal);
}
