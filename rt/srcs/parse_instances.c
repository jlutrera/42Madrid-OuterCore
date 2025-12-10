/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instances.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:21:47 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/10 09:21:47 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_composite *load_library_file(t_scene *scene, const char *filename)
{
	
    FILE *fp = fopen(filename, "r");
    if (!fp)
	{
        return NULL;
	}

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char *buffer = malloc(fsize + 1);
    if (!buffer)
    {
        fclose(fp);
        return NULL;
    }
    fread(buffer, 1, fsize, fp);
    buffer[fsize] = '\0';
    fclose(fp);

    cJSON *json = cJSON_Parse(buffer);
    free(buffer);
    if (!json)
        return NULL;

	t_composite *result = NULL;
    if (parse_elements_library(scene, json) == SUCCESS)
    {
        t_composite *comp = scene->composites;
        while (comp->next)
            comp = comp->next;
        result = comp;
    }
	cJSON_Delete(json);
	return result;
}

static t_composite *find_instance(t_scene *scene, const char *name)
{
	t_composite *comp = scene->composites;
	while (comp)
	{
		if (strcmp(comp->name, name) == 0)
			return comp;
		comp = comp->next;
	}
	// Si no lo encuentra, se puede tratar de una librería externa.
	// *name es el nombre de un archivo con el objeto compuesto
	return load_library_file(scene, name);
}

t_lst_obj *clone_object(t_lst_obj *src)
{
    t_lst_obj *clone = calloc(1, sizeof(t_lst_obj));
    if (!clone)
		return NULL;

    clone->type = src->type;
	switch (src->type)
	{
    	case CYLINDER:
    	{
        	t_cylinder *orig = (t_cylinder *)src->object;
        	t_cylinder *cpy = malloc(sizeof(t_cylinder));
        	if (!cpy) { free(clone); return NULL; }
        	*cpy = *orig;
        	clone->object = cpy;
			break;
    	}
    	case SPHERE:
		{
        	t_sphere *orig = (t_sphere *)src->object;
        	t_sphere *cpy = malloc(sizeof(t_sphere));
        	if (!cpy) { free(clone); return NULL; }
        	*cpy = *orig;
        	clone->object = cpy;
			break;
    	}
    	case CONE:
		{
    	    t_cone *orig = (t_cone *)src->object;
    	    t_cone *cpy = malloc(sizeof(t_cone));
    	    if (!cpy) { free(clone); return NULL; }
    	    *cpy = *orig;
    	    clone->object = cpy;
			break;
		}
		case PLANE:
		{
			t_plane *orig = (t_plane *)src->object;
			t_plane *cpy = malloc(sizeof(t_plane));
			if (!cpy) { free(clone); return NULL; }
    	    *cpy = *orig;
    	    clone->object = cpy;
			break;
		}
		case PARABOLOID:
		{
			t_paraboloid *orig = (t_paraboloid *)src->object;
			t_paraboloid *cpy = malloc(sizeof(t_paraboloid));
    	    if (!cpy) { free(clone); return NULL; }
    	    *cpy = *orig;
    	    clone->object = cpy;
			break;
		}
		case TORUS:
		{
			t_torus *orig = (t_torus *)src->object;
			t_torus *cpy = malloc(sizeof(t_torus));
        	if (!cpy) { free(clone); return NULL; }
        	*cpy = *orig;
        	clone->object = cpy;
			break;
		}
		default: //case  MOEBIUS:
		{
			t_moebius *orig = (t_moebius *)src->object;
			t_moebius *cpy = malloc(sizeof(t_moebius));
        	if (!cpy) { free(clone); return NULL; }
        	*cpy = *orig;
        	clone->object = cpy;
		}
	}
    return clone;
}

int parse_instances(t_scene *scene, cJSON *json)
{
	int err;
    t_vec center_of_rotation;
    bool first_object = true;

	cJSON *instances = cJSON_GetObjectItem(json, "instances");
	if (!instances)
		return SUCCESS;
	if (!cJSON_IsArray(instances))
		return JSON_E;
	
	cJSON *inst;
	cJSON_ArrayForEach(inst, instances)
	{
		cJSON *juse = cJSON_GetObjectItem(inst, "use");
		if (!juse || !cJSON_IsString(juse))
			return FIELD_E;
		
		t_composite *ref = find_instance(scene, juse->valuestring);
		if (!ref)
			return JSON_E;

		cJSON *jscale = cJSON_GetObjectItem(inst, "scale");
		if (!jscale)
			ref->scale = 1;
		else if (!cJSON_IsNumber(jscale))
			return FIELD_E;
		else
			ref->scale = jscale->valuedouble;
		
		t_lst_obj *obj = ref->objects;
		while (obj)
		{
			t_lst_obj *clone = clone_object(obj);
			if (!clone)
				return MEMORY_E;

			err = parse_options(clone, inst);
			if (err != SUCCESS)
				return err;

 			if (first_object)
            {
                center_of_rotation = get_object_center(clone);
                first_object = false;
            }
			apply_transformations(clone, ref->scale, center_of_rotation);
			add_object(scene, clone);
			obj = obj->next;
		}
		first_object = true;
	}

	return SUCCESS;
}
