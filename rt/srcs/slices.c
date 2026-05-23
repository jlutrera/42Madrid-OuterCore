/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slices.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:00:00 by jutrera-          #+#    #+#             */
/*   Updated: 2025/09/27 19:03:30 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void check_intersections_slices(t_lst_obj *obj)
{
    if (!obj->slices)
        return;

    t_slices *current = obj->slices;
    t_slices *prev = NULL;

    while (current)
    {
        int keep = 1; // por defecto mantenemos

        switch (obj->type)
        {
            case PLANE:
            {
                t_plane *pl = (t_plane *)obj->object;
                t_vec N_slice = current->slice.direction;
                double dot_normals = vec_dot(pl->direction, N_slice);

                if (fabs(dot_normals) > 1.0 - EPSILON)
                {
                    // Slice paralelo: calcular distancia perpendicular
                    t_vec w = vec_sub(current->slice.coordinate, pl->coordinate);
                    double dist = fabs(vec_dot(w, N_slice));
                    if (dist > EPSILON)
                        keep = 0; // Slice paralelo y fuera → eliminar
                }
                break;
            }

            case SPHERE:
            {
                t_sphere *sp = (t_sphere *)obj->object;
                t_vec cp = vec_sub(sp->center, current->slice.coordinate);
                double dist_center = fabs(vec_dot(cp, current->slice.direction));
                if (dist_center > sp->radius + EPSILON)
                    keep = 0;
                break;
            }

            case CYLINDER:
            {
                t_cylinder *cy = (t_cylinder *)obj->object;
                t_vec w = vec_sub(cy->coordinate, current->slice.coordinate);
                t_vec w_perp = vec_sub(w, vec_mul(cy->direction, vec_dot(w, cy->direction)));
                double dist_center = fabs(vec_dot(w_perp, current->slice.direction));
                if (dist_center > cy->radius + EPSILON)
                    keep = 0;
                break;
            }

            case CONE:
            {
                t_cone *co = (t_cone *)obj->object;
                t_vec w = vec_sub(current->slice.coordinate, co->coordinate);
                double dist_along_axis = vec_dot(w, co->direction);
                if (dist_along_axis < -EPSILON || dist_along_axis > co->height + EPSILON)
                    keep = 0;
                break;
            }

            default:
                break; // otros tipos no filtran slices
        }

        if (!keep)
        {
            // eliminar slice de la lista
            t_slices *to_free = current;
            if (prev)
                prev->next = current->next;
            else
                obj->slices = current->next;
            current = current->next;
            free(to_free);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

int p_over_slice(t_plane sl, t_vec p)
{
	t_vec cp = vec_sub(p, sl.coordinate);
	double d = vec_dot(cp, sl.direction);
	if (d > EPSILON)
		return 1; // Si está en zona no visible
	else if (d < -EPSILON) // Si está en zona visible
		return -1;
	return 0; // Si está en el plano
}

double t_in_the_slices(t_slices *slices, t_ray ray, double t_in, double t_out)
{
    t_point2    t_slice;
    double      t_cut = t_in;
    t_slices    *slice_node;

    slice_node = slices;
    while (slice_node)
    {
        t_lst_obj slice_obj = {.type = PLANE, .object = &slice_node->slice, .slices = NULL};
        intersect_pl(ray, &slice_obj, &t_slice);

        if (t_slice.x != INFINITY &&  t_slice.x > t_cut - EPSILON && t_slice.x < t_out + EPSILON)
            t_cut = t_slice.x;

        slice_node = slice_node->next;
    }
    
    t_point3 p = ray_at(ray, t_cut);
    slice_node = slices;
    while (slice_node)
    {
         if (p_over_slice(slice_node->slice, p) == 1)
             return INFINITY;
         slice_node = slice_node->next;    
    }
    return t_cut;
}
