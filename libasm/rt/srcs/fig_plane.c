/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:55:04 by jutrera-          #+#    #+#             */
/*   Updated: 2025/09/27 16:29:14 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color apply_texture_to_plane(t_lst_obj *obj, t_vec p)
{
	t_plane *pl = (t_plane *)obj->object;

	t_vec normal = vec_unit(pl->direction);
    // Choose the most orthogonal basis vector
    const t_vec bases[] = {{1,0,0}, {0,1,0}, {0,0,1}};
    t_vec best_basis = bases[0];
    double min_dot = 1.0;
    
    // Find which basis is most perpendicular to normal
    for (int i = 0; i < 3; i++)
	{
        double dot = fabs(vec_dot(normal, bases[i]));
        if (dot < min_dot)
		{
            min_dot = dot;
            best_basis = bases[i];
        }
    }
    
    // Calculate and normalize U axis
    t_vec u_axis = vec_cross(best_basis, normal);
    double length = vec_length(u_axis);
    if (length < EPSILON)
		u_axis = vec_cross((t_vec){0,1,0}, normal);

	u_axis = vec_unit(u_axis);
	t_vec v_axis = vec_unit(vec_cross(normal, u_axis));

	// Coordenadas locales del punto
	t_vec local = vec_sub(p, pl->coordinate);
	double u = vec_dot(local, u_axis);
	double v = vec_dot(local, v_axis);

	return textures(u, v, obj->texture, 2, 2);
}

void	intersect_pl(t_ray ray, t_lst_obj *obj, t_point2 *t)
{
	t_plane	*plane = (t_plane *)obj->object;
	t_vec	op;
	double	denom;
	double	num;
	double 	t1;
	
	denom = vec_dot(plane->direction, ray.dir);
	op = vec_sub(plane->coordinate, ray.origin);
	num = vec_dot(plane->direction, op);
	*t = point2(INFINITY, INFINITY);
	if (fabs(denom) < EPSILON)
		return;

	t1 = num / denom;
	t_vec p1 = ray_at(ray, t1);
	
	t_slices *s = obj->slices;
	while (s)
	{
		if (p_over_slice(s->slice, p1) == 1)
			return;
		s = s->next;
	}		
	*t = point2(t1, t1);
}

t_vec	get_plane_normal(t_plane *plane)
{
	return (plane->direction);
}
