/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:49:01 by jutrera-          #+#    #+#             */
/*   Updated: 2025/09/27 16:30:16 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color apply_texture_to_sphere(t_lst_obj *obj, t_vec p)
{
	t_sphere *sp = (t_sphere *)obj->object;
	
	t_vec local = vec_sub(p, sp->center);
	local = vec_unit(local); 

	double theta = acos(local.y);
	double phi = atan2(local.x, local.z);

	double u = (phi + M_PI) / (2.0 * M_PI);
	double v = 1-theta / M_PI;


	double tiles = 2 * M_PI * sp->radius;
	return textures(u, v, obj->texture, tiles, tiles);
}

void	intersect_sp(t_ray ray, t_lst_obj *obj, t_point2 *t)
{
	t_sphere *sp = (t_sphere *)obj->object;
	t_vec co = vec_sub(ray.origin, sp->center);
	double a = vec_dot(ray.dir, ray.dir);
	double b = 2 * vec_dot(co, ray.dir);
	double c = vec_dot(co, co) - sp->radius * sp->radius;
	double discriminant = b * b - 4 * a * c;

	*t = point2(INFINITY, INFINITY);
	if (discriminant < 0)
		return;

	double t1 = (-b - sqrt(discriminant)) / (2 * a);
	double t2 = (-b + sqrt(discriminant)) / (2 * a);

	if (t1 < EPSILON && t2 < EPSILON)
		return;

	double t_in  = fmin(t1, t2);
	double t_out = fmax(t1, t2);

    double t_cut = t_in_the_slices(obj->slices, ray, t_in, t_out);

    *t = point2(t_cut, t_cut);
}

t_vec	get_sphere_normal(t_lst_obj *obj, t_vec p)
{
	t_sphere *sp = (t_sphere *)obj->object;
	t_slices *s = obj->slices;
	t_vec cp = vec_sub(p, sp->center);
	double inside = sp->radius - vec_length(cp);
	if (inside > EPSILON)
		while (s)
		{
			if (p_over_slice(s->slice, p) == 0)
				return s->slice.direction;
			s = s->next;
		}
	return vec_unit(cp);
}
