/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_library.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:21:56 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/10 09:21:56 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	add_composite(t_scene *scene, t_composite *new_composite)
{
	if (!scene->composites)
		scene->composites = new_composite;
	else
	{
		t_composite *tmp = scene->composites;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_composite;
	}
}

int parse_elements_library(t_scene *scene, cJSON *def)
{
	if (!cJSON_IsObject(def))
		return JSON_E;
		
	cJSON *entry = def->child;

	if (!entry || !cJSON_IsArray(entry))
		return JSON_E;

	if (!entry->string)
		return JSON_E;
	
	t_composite *composite = calloc(1, sizeof(t_composite));
	if (!composite)
		return MEMORY_E;

	t_lst_obj *head = NULL;
    t_lst_obj *tail = NULL;

	cJSON *elem;
	cJSON_ArrayForEach(elem, entry)
	{
		int err = JSON_E;
		cJSON *type_json = cJSON_GetObjectItem(elem, "type");
		if (!type_json || !cJSON_IsString(type_json))
		{
			free_composites(composite);
			return JSON_E;
		}

		t_lst_obj *new_obj = calloc(1, sizeof(t_lst_obj));
		if (!new_obj)
		{
			free_composites(composite);
			return MEMORY_E;
		}

		const char *type = type_json->valuestring;

		if (strcmp(type, "cylinder") == 0)
			err = parse_cylinder(elem, new_obj);
		else if (strcmp(type, "sphere") == 0)
			err = parse_sphere(elem, new_obj);
		else if (strcmp(type, "plane") == 0)
			err = parse_plane(elem, new_obj);
		else if (strcmp(type, "cone") == 0)
			err = parse_cone(elem, new_obj);
		else if (strcmp(type, "paraboloid") == 0)
			err = parse_paraboloid(elem, new_obj);
		else if (strcmp(type, "torus") == 0)
			err = parse_torus(elem, new_obj);
		else if (strcmp(type, "moebius") == 0)
			err = parse_moebius(elem, new_obj);
		else
			err = FIELD_E;

		if (err != SUCCESS)
		{
			free(new_obj);
			free_composites(composite);
			return err;
		}
		if (!head)
        {
            head = new_obj;
            tail = new_obj;
        }
        else
        {
            tail->next = new_obj;
            tail = new_obj;
        }
	}
	composite->name = strdup(entry->string);
	composite->next = NULL;
	composite->objects = head;
	add_composite(scene, composite);

	return SUCCESS;
}

int parse_library(t_scene *scene, cJSON *json)
{
	cJSON *defs = cJSON_GetObjectItem(json, "library");
	if (!defs)
		return SUCCESS;

	if (!cJSON_IsArray(defs))
		return JSON_E;

	cJSON *def;
	cJSON_ArrayForEach(def, defs)
	{	
		int err =  parse_elements_library(scene, def);
		if (err != SUCCESS)
		{
			return err;
		}
	}
	
	return SUCCESS;
}
