/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:51:06 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/21 10:51:06 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int parse_object(t_scene *scene, cJSON *json, char *type)
{
	int err;

	cJSON *array = cJSON_GetObjectItem(json, type);
	if (!array || !cJSON_IsArray(array))
		return SUCCESS;

	cJSON *elem;
	cJSON_ArrayForEach(elem, array)
	{
		t_lst_obj *obj = calloc(1, sizeof(t_lst_obj));
		if (!obj)
			return MEMORY_E;

		if (strcmp(type, "spheres") == 0)
			err = parse_sphere(elem, obj);
		else if (strcmp(type, "cylinders") == 0)
			err = parse_cylinder(elem, obj);
		else if (strcmp(type, "cones") == 0)
			err = parse_cone(elem, obj);
		else if (strcmp(type, "planes") == 0)
			err = parse_plane(elem, obj);
		else if (strcmp(type, "paraboloids") == 0)
			err = parse_paraboloid(elem, obj);
		else if (strcmp(type, "tori") == 0)
			err = parse_torus(elem, obj);
		else if (strcmp(type, "moebius") == 0)
			err = parse_moebius(elem, obj);
		else
			return FIELD_E; // Tipo de objeto no reconocido

		if (err != SUCCESS)
		{
			free(obj);
			return err;
		}
		err = parse_options(obj, elem);
		
		if (err != SUCCESS)
		{
			free(obj->object);
			free(obj);
			return err;
		}
		t_vec center = get_object_center(obj);
		apply_transformations(obj, 0, center);		
		add_object(scene, obj);
	}
	return SUCCESS;
}

int parse_objects(t_scene *scene, cJSON *json)
{
	int err;

	if ((err = parse_object(scene, json, "spheres")) != SUCCESS)
		return err;
	if ((err = parse_object(scene, json, "cylinders")) != SUCCESS)
		return err;
	if ((err = parse_object(scene, json, "cones")) != SUCCESS)
		return err;
	if ((err = parse_object(scene, json, "planes")) != SUCCESS)
		return err;
	if ((err = parse_object(scene, json, "paraboloids")) != SUCCESS)
		return err;
	if ((err = parse_object(scene, json, "tori")) != SUCCESS)
		return err;
	if ((err = parse_object(scene, json, "moebius")) != SUCCESS)
		return err;

	return SUCCESS;
}
