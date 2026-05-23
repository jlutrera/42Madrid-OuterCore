/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_solids.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:22:22 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/10 09:22:22 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_localbase get_local_basis(t_vec dir)
{
    t_localbase b;

    b.w = vec_unit(dir); // eje Z local (principal)

    // Vector auxiliar para construir la base (debe ser diferente de b.w)
    t_vec tmp = (fabs(b.w.y) < 0.99) ? (t_vec){0, 1, 0} : (t_vec){1, 0, 0};

    b.u = vec_unit(vec_cross(tmp, b.w)); // eje X local (perpendicular a Z)
    b.v = vec_unit(vec_cross(b.w, b.u)); // eje Y local (perpendicular a X y Z)

    return b;
}

int parse_moebius(cJSON *elem, t_lst_obj *obj)
{
	int err;

	cJSON *pos = cJSON_GetObjectItem(elem, "center");
	cJSON *width = cJSON_GetObjectItem(elem, "width");
	cJSON *dir = cJSON_GetObjectItem(elem, "direction");
	cJSON *rad = cJSON_GetObjectItem(elem, "radius");

	if (!rad || !pos || !width || !dir || !cJSON_IsNumber(width) || !cJSON_IsNumber(rad))
		return FIELD_E;

	t_moebius *moebius = calloc(1, sizeof(t_moebius));
	if (!moebius)
		return MEMORY_E;

	err = parse_point3(pos, &moebius->center);
	if (err != SUCCESS)
	{
		free(moebius);
		return err;
	}
	err = parse_vec(dir, &moebius->direction);
	if (err != SUCCESS)
	{
		free(moebius);
		return err;
	}
	moebius->direction = vec_unit(moebius->direction);
	moebius->radius = rad->valuedouble;
	if (moebius->radius <= 0)
	{
		free(moebius);
		return NEGATIVE_E;
	}
	moebius->width = width->valuedouble;
	if (bad_ratio(moebius->width, 0, 1))
	{
		free(moebius);
		return VALUE_E;
	}
	moebius->width = moebius->width / 100 + 0.005; // mínimo 0.005, máximo 0.015
	moebius->basis = get_local_basis(moebius->direction);
	obj->type = MOEBIUS;
	obj->object = moebius;

	return SUCCESS;
}

int parse_torus(cJSON *elem, t_lst_obj *obj)
{
	int err;

	cJSON *pos = cJSON_GetObjectItem(elem, "center");
	cJSON *dir = cJSON_GetObjectItem(elem, "direction");
	cJSON *r_min = cJSON_GetObjectItem(elem, "minor");
	cJSON *r_max = cJSON_GetObjectItem(elem, "major");

	if (!pos || !dir || !r_min || !r_max || !cJSON_IsNumber(r_min) || !cJSON_IsNumber(r_max))
		return FIELD_E;

	t_torus *torus = calloc(1, sizeof(t_torus));
	if (!torus)
		return MEMORY_E;

	err = parse_point3(pos, &torus->center);
	if (err != SUCCESS)
	{
		free(torus);
		return err;
	}
	err = parse_vec(dir, &torus->direction);
	if (err != SUCCESS)
	{
		free(torus);
		return err;
	}
	torus->direction = vec_unit(torus->direction);
	torus->r_min = r_min->valuedouble;
	torus->r_max = r_max->valuedouble;
	if (torus->r_min <= 0 || torus->r_max <= 0)
	{
		free(torus);
		return NEGATIVE_E;
	}
	if (torus->r_max < torus->r_min)
	{
		free(torus);
		return VALUE_E;
	}
	torus->basis = get_local_basis(torus->direction);
	obj->type = TORUS;
	obj->object = torus;

	return SUCCESS;
}

int parse_paraboloid(cJSON *elem, t_lst_obj *obj)
{
	int err;

	cJSON *pos = cJSON_GetObjectItem(elem, "center");
	cJSON *dir = cJSON_GetObjectItem(elem, "direction");
	cJSON *k = cJSON_GetObjectItem(elem, "k");
	cJSON *height = cJSON_GetObjectItem(elem, "height");

	if (!pos || !dir ||!height || !k || !cJSON_IsNumber(k) || !cJSON_IsNumber(height))
		return FIELD_E;

	t_paraboloid *paraboloid = calloc(1, sizeof(t_paraboloid));
	if (!paraboloid)
		return MEMORY_E;

	err = parse_point3(pos, &paraboloid->center);
	if (err != SUCCESS)
	{
		free(paraboloid);
		return err;
	}
	err = parse_vec(dir, &paraboloid->direction);
	if (err != SUCCESS)
	{
		free(paraboloid);
		return err;
	}
	paraboloid->direction = vec_unit(paraboloid->direction);
	paraboloid->k = k->valuedouble;
	paraboloid->height = height->valuedouble;
	if (paraboloid->k <= 0 || paraboloid->height <= 0)
	{
		free(paraboloid);
		return NEGATIVE_E;
	}

	obj->type = PARABOLOID;
	obj->object = paraboloid;

	return SUCCESS;
}

int parse_plane(cJSON *elem, t_lst_obj *obj)
{
	int err;

	cJSON *point = cJSON_GetObjectItem(elem, "position");
	cJSON *normal = cJSON_GetObjectItem(elem, "normal");

	if (!point || !normal)
		return FIELD_E;

	t_plane *pl = calloc(1, sizeof(t_plane));
	if (!pl)
		return MEMORY_E;

	err = parse_point3(point, &pl->coordinate);
	if (err != SUCCESS)
	{
		free(pl);
		return err;
	}
	err = parse_vec(normal, &pl->direction);
	if (err != SUCCESS)
	{
		free(pl);
		return err;
	}
	pl->direction = vec_unit(pl->direction);
	obj->type = PLANE;
	obj->object = pl;

	return SUCCESS;
}

int parse_cone(cJSON *elem, t_lst_obj *obj)
{
	int err;

	cJSON *pos = cJSON_GetObjectItem(elem, "position");
	cJSON *dir = cJSON_GetObjectItem(elem, "direction");
	cJSON *radius = cJSON_GetObjectItem(elem, "radius");
	cJSON *height = cJSON_GetObjectItem(elem, "height");

	if (!pos || !dir || !radius || !height || !cJSON_IsNumber(radius) || !cJSON_IsNumber(height))
		return FIELD_E;

	t_cone *cone = calloc(1, sizeof(t_cone));
	if (!cone)
		return MEMORY_E;

	err = parse_point3(pos, &cone->coordinate);
	if (err != SUCCESS)
	{
		free(cone);
		return err;
	}
	err = parse_vec(dir, &cone->direction);
	if (err != SUCCESS)
	{
		free(cone);
		return err;
	}
	cone->direction = vec_unit(cone->direction);
	cone->radius = radius->valuedouble;
	cone->height = height->valuedouble;
	if (cone->radius <= 0 || cone->height <= 0)
	{
		free(cone);
		return NEGATIVE_E;
	}
		
	obj->type = CONE;
	obj->object = cone;

	return SUCCESS;
}

int parse_cylinder(cJSON *elem, t_lst_obj *obj)
{
	int err;
	
	cJSON *pos = cJSON_GetObjectItem(elem, "position");
	cJSON *dir = cJSON_GetObjectItem(elem, "direction");
	cJSON *radius = cJSON_GetObjectItem(elem, "radius");
	cJSON *height = cJSON_GetObjectItem(elem, "height");
	if (!pos || !dir || !radius || !height || !cJSON_IsNumber(radius) || !cJSON_IsNumber(height))
		return FIELD_E;

	t_cylinder *cyl = calloc(1, sizeof(t_cylinder));
	if (!cyl)
		return MEMORY_E;
		
	err = parse_point3(pos, &cyl->coordinate);
	if (err != SUCCESS)
	{
		free(cyl);
		return err;
	}
	err = parse_vec(dir, &cyl->direction);
	if (err != SUCCESS)
	{
		free(cyl);
		return err;
	}
	cyl->direction = vec_unit(cyl->direction);
	cyl->radius = radius->valuedouble;
	cyl->height = height->valuedouble;
	if (cyl->radius <= 0 || cyl->height <= 0)
	{
		free(cyl);
		return NEGATIVE_E;
	}
	obj->type = CYLINDER;
	obj->object = cyl;
	
	return SUCCESS;
}

int parse_sphere(cJSON *elem, t_lst_obj *obj)
{
	int err;

	cJSON *pos = cJSON_GetObjectItem(elem, "center");
	cJSON *radius = cJSON_GetObjectItem(elem, "radius");
	if (!pos || !radius || !cJSON_IsNumber(radius))
		return FIELD_E;

	t_sphere *sph = calloc(1, sizeof(t_sphere));
	if (!sph)
		return MEMORY_E;

	err = parse_point3(pos, &sph->center);
	if (err != SUCCESS)
	{
		free(sph);
		return err;
	}
	sph->radius = radius->valuedouble;
	if (sph->radius <= 0)
	{
		free(sph);
		return NEGATIVE_E;
	}
	obj->type = SPHERE;
	obj->object = sph;
		
	return SUCCESS;
}
