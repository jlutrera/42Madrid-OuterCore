/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  transformations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:17:39 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/05 17:17:39 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_point3 do_translation(t_point3 p, t_vec v)
{
	p.x += v.x;
	p.y += v.y;
	p.z += v.z;
	return (p);
}

static t_vec do_rotation_vector(t_vec p, t_vec rad)
{
	double		temp1;
	double		temp2;
	
	if (rad.x != 0)
	{
		temp1 = p.y;
		temp2 = p.z;
		p.y = temp1 * cos(rad.x) - temp2 * sin(rad.x);
		p.z = temp1 * sin(rad.x) + temp2 * cos(rad.x);
	}
	if (rad.y != 0)
	{
		temp1 = p.x;
		temp2 = p.z;
		p.x = temp1 * cos(rad.y) + temp2 * sin(rad.y);
		p.z = -temp1 * sin(rad.y) + temp2 * cos(rad.y);
	}
	if (rad.z != 0)
	{
		temp1 = p.x;
		temp2 = p.y;
		p.x = temp1 * cos(rad.z) - temp2 * sin(rad.z);
		p.y = temp1 * sin(rad.z) + temp2 * cos(rad.z);
	}
	return (p);
}

static t_vec do_rotation_point(t_vec p, t_vec center, t_vec rad, double scale)
{
	if (rad.x == 0 && rad.y == 0 && rad.z == 0)
        return p;
    // 1. Traslada al origen local
    p = vec_sub(p, center);

	p = vec_mul(p, scale);
    // 2. Rota en el origen
    p = do_rotation_vector(p, rad);

    // 3. Devuelve al sitio original
    p = vec_add(p, center);

    return p;
}

static void do_scale(t_lst_obj *obj, double scale)
{
	switch (obj->type)
	{
		case PLANE: break;
		case CYLINDER:
		{
			t_cylinder *cy = (t_cylinder *)obj->object;
    		cy->radius *= scale;
        	cy->height *= scale;
			break;
		}
		case CONE:
		{
			t_cone *co = (t_cone *)obj->object;
			co->radius *= scale;
			co->height *= scale;
			break;
		}
		case SPHERE:
		{
			t_sphere *sp = (t_sphere *)obj->object;
        	sp->radius *= scale;
			break;
		}
		case PARABOLOID:
		{
			t_paraboloid *pa = (t_paraboloid *)obj->object;
			pa->height *= scale;
			pa->k *= scale;
			break;
		}
		case TORUS:
		{
			t_torus *to = (t_torus *)obj->object;
			to->r_max *= scale;
			to->r_min *= scale;
			break;
		}
		case MOEBIUS:
		{
			t_moebius *mo = (t_moebius *)obj->object;
			mo->width *= scale;
			break;
		}
	}
}

t_vec get_object_center(t_lst_obj *obj)
{
    switch (obj->type)
    {
        case SPHERE:
            return ((t_sphere *)obj->object)->center;
        case CYLINDER:
            return ((t_cylinder *)obj->object)->coordinate;
        case CONE:
            return ((t_cone *)obj->object)->coordinate;
        case PLANE:
            return ((t_plane *)obj->object)->coordinate;
        case PARABOLOID:
            return ((t_paraboloid *)obj->object)->center;
        case TORUS:
            return ((t_torus *)obj->object)->center;
        case MOEBIUS:
            return ((t_moebius *)obj->object)->center;
        default:
            return vec(0, 0, 0);
    }
}

void apply_transformations(t_lst_obj *obj, double scale, t_point3 center)
{
	if (scale != 0)
		do_scale(obj, scale);

	t_vec trans = obj->translation;
	t_vec rota = obj->rotation;
	switch (obj->type)
	{
		case SPHERE:
		{
			t_sphere *sp = (t_sphere *)obj->object;
			sp->center = do_translation(sp->center, trans);
			//La esfera no rota
			break;
		}
		case CYLINDER:
		{
			t_cylinder *cy = (t_cylinder *)obj->object;
			cy->coordinate = do_rotation_point(cy->coordinate, center, rota, scale);
			cy->coordinate = do_translation(cy->coordinate, trans);
			cy->direction = do_rotation_vector(cy->direction, rota);
			break;
		}
		case CONE:
		{
			t_cone *co = (t_cone *)obj->object;
			co->coordinate = do_rotation_point(co->coordinate, center, rota, scale);
			co->coordinate = do_translation(co->coordinate, trans);
			co->direction = do_rotation_vector(co->direction, rota);
			break;
		}
		case PLANE:
		{
			t_plane *pl = (t_plane *)obj->object;
			pl->coordinate = do_rotation_point(pl->coordinate, center, rota, scale);
			pl->coordinate = do_translation(pl->coordinate, trans);
			pl->direction = do_rotation_vector(pl->direction, rota);
			break;
		}
		case PARABOLOID:
		{
			t_paraboloid *pa = (t_paraboloid *)obj->object;
			pa->center = do_rotation_point(pa->center, center, rota, scale);
			pa->center = do_translation(pa->center, trans);
			pa->direction = do_rotation_vector(pa->direction, rota);
			break;
		}
		case TORUS:
		{
			t_torus *to = (t_torus *)obj->object;
			to->center = do_rotation_point(to->center, center, rota, scale);
			to->center = do_translation(to->center, trans);
			to->direction = do_rotation_vector(to->direction, rota);
			break;
		}
		case MOEBIUS:
		{
			t_moebius *mo = (t_moebius *)obj->object;
			mo->center = do_rotation_point(mo->center, center, rota, scale);
			mo->center = do_translation(mo->center, trans);
			mo->direction = do_rotation_vector(mo->direction, rota);
			break;
		}
		default:  break;
	}
	if (obj->slices)
	{
		t_slices *slice = obj->slices;
		while (slice)
		{
			slice->slice.coordinate = do_rotation_point(slice->slice.coordinate, center, rota, scale);
			slice->slice.coordinate = do_translation(slice->slice.coordinate, trans);
			slice->slice.direction = do_rotation_vector(slice->slice.direction, rota);
			slice = slice->next;
		}
	}
}
