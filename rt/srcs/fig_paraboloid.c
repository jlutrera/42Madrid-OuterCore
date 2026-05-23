/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_paraboloid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:18:01 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/15 22:18:01 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double intersect_paraboloid_cap(t_ray ray, t_paraboloid *pa)
{
	t_vec cap_center = vec_add(pa->center, vec_mul(pa->direction, pa->height));
	double denom = vec_dot(ray.dir, pa->direction);

	if (fabs(denom) < EPSILON)
		return INFINITY;

	double t = vec_dot(vec_sub(cap_center, ray.origin), pa->direction) / denom;
	if (t < EPSILON)
		return INFINITY;

	t_vec hit =  ray_at(ray, t);
	t_vec v = vec_sub(hit, cap_center);
	double dist2 = vec_dot(v, v);

	// El radio en la tapa (distancia máxima desde centro)
	double max_radius = sqrt(4 * pa->k * pa->height);

	if (dist2 <= max_radius * max_radius)
		return t;
	return INFINITY;
}

static void intersect_paraboloid(t_ray ray, t_paraboloid *pa, t_point2 *t_out)
{
	t_vec	oc = vec_sub(ray.origin, pa->center);
	double	d_dot_d = vec_dot(ray.dir, ray.dir);
	double	d_dot_v = vec_dot(ray.dir, pa->direction);
	double	oc_dot_d = vec_dot(oc, ray.dir);
	double	oc_dot_v = vec_dot(oc, pa->direction);
	double	oc_dot_oc = vec_dot(oc, oc);
	double	k = pa->k;

	double	a = d_dot_d - d_dot_v * d_dot_v;
	double	b = 2 * (oc_dot_d - d_dot_v * (oc_dot_v + 2 * k));
	double	c = oc_dot_oc - oc_dot_v * (oc_dot_v + 4 * k);

	double	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
	{
		*t_out = point2(INFINITY, INFINITY);
		return;
	}

	double sqrt_d = sqrt(discriminant);
	double t0 = (-b - sqrt_d) / (2 * a);
	double t1 = (-b + sqrt_d) / (2 * a);

	// Ordenar t0 y t1
	if (t0 > t1)
	{
		double tmp = t0;
		t0 = t1;
		t1 = tmp;
	}

	// Comprobar si están dentro de la altura del paraboloide
	t_vec hit0 = ray_at(ray, t0);
	t_vec hit1 = ray_at(ray, t1);

	double h0 = vec_dot(vec_sub(hit0, pa->center), pa->direction);
	double h1 = vec_dot(vec_sub(hit1, pa->center), pa->direction);

	bool valid0 = (h0 >= 0 && h0 <= pa->height);
	bool valid1 = (h1 >= 0 && h1 <= pa->height);

	if (valid0 && valid1)
		*t_out = point2(t0, t1);
	else if (valid0)
		*t_out = point2(t0, INFINITY);
	else if (valid1)
		*t_out = point2(t1, INFINITY);
	else
		*t_out = point2(INFINITY, INFINITY);
}

static t_vec	get_paraboloid_lateral_normal(t_paraboloid *pa, t_vec p)
{
	t_vec oc = vec_sub(p, pa->center);
	double h = vec_dot(oc, pa->direction);
	t_vec ortho = vec_sub(oc, vec_mul(pa->direction, h));
	t_vec grad = vec_sub(vec_mul(ortho, 2), vec_mul(pa->direction, 4 * pa->k));
	return vec_unit(grad);
}

static t_vec	get_paraboloid_cap_normal(t_paraboloid *pa)
{
	return pa->direction;
}

void intersect_pa(t_ray ray, t_paraboloid *pa, t_point2 *t_out)
{
	t_point2 paraboloid_t;
	intersect_paraboloid(ray, pa, &paraboloid_t);

	double cap_t = intersect_paraboloid_cap(ray, pa);

	double t0 = paraboloid_t.x;
	double t1 = paraboloid_t.y;

	// Elige el más cercano entre t0, t1, y cap_t
	double min_t = INFINITY;
	if (t0 > EPSILON && t0 < min_t) min_t = t0;
	if (t1 > EPSILON && t1 < min_t) min_t = t1;
	if (cap_t > EPSILON && cap_t < min_t) min_t = cap_t;

	if (min_t == INFINITY)
		*t_out = point2(INFINITY, INFINITY);
	else
		*t_out = point2(min_t, INFINITY);
}

t_vec	get_paraboloid_normal(t_paraboloid *pa, t_vec p)
{
	t_vec v = pa->direction;
	double height = vec_dot(vec_sub(p, pa->center), v);

	if (fabs(height - pa->height) < EPSILON)
		return get_paraboloid_cap_normal(pa);
	else
		return  get_paraboloid_lateral_normal(pa, p);
}
