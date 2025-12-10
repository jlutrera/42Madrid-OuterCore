/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:22:09 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/10 09:22:09 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	convert_to_radians(double a)
{
	while (a < 0)
		a += 360;
	while (a > 360)
		a = a - 360;
	return (a * M_PI / 180.0);
}

static int parse_slice(cJSON *elem, t_plane *pl)
{
	int err;

	cJSON *point = cJSON_GetObjectItem(elem, "position");
	cJSON *normal = cJSON_GetObjectItem(elem, "normal");

	if (!point || !normal)
		return FIELD_E;

	err = parse_point3(point, &pl->coordinate);
	if (err != SUCCESS)
		return err;

	err = parse_vec(normal, &pl->direction);
	if (err != SUCCESS)
		return err;

	pl->direction = vec_unit(pl->direction);

	return SUCCESS;
}

static t_slices *parse_slices(cJSON *slice)
{
	t_slices 	*slices = NULL;
	t_slices 	*last = NULL;
	cJSON 		*slice_elem;
	t_slices 	*new_slice;
	t_slices	*tmp;

	cJSON_ArrayForEach(slice_elem, slice)
	{
		new_slice = calloc(1, sizeof(t_slices));
		if (!new_slice)
		{	
			while (slices)
			{
				tmp = slices;
				slices = slices->next;
				free(tmp);
			}
			return NULL;
		}
		if (parse_slice(slice_elem, &new_slice->slice) != SUCCESS)
		{
			while (slices)
			{
				tmp = slices;
				slices = slices->next;
				free(tmp);
			}
			free(new_slice);
			return NULL;
		}
		if (!slices)
			slices = new_slice;
		else
			last->next = new_slice;
		last = new_slice;
	}

	return slices;
}

int parse_options(t_lst_obj *obj, cJSON *elem)
{
	int err;

	cJSON *color = cJSON_GetObjectItem(elem, "color");
	cJSON *shine = cJSON_GetObjectItem(elem, "shine");
	cJSON *reflect = cJSON_GetObjectItem(elem, "reflectivity");
	cJSON *transp = cJSON_GetObjectItem(elem, "transparency");
	cJSON *ior = cJSON_GetObjectItem(elem, "refraction");
	cJSON *translate = cJSON_GetObjectItem(elem, "translate");
	cJSON *rotate = cJSON_GetObjectItem(elem, "rotate");
	cJSON *slice = cJSON_GetObjectItem(elem, "slice");
	cJSON *texture = cJSON_GetObjectItem(elem, "texture");
	
	// 1. Transformaciones
	if (translate)
	{
		err = parse_point3(translate, &obj->translation);
		if (err != SUCCESS)
			return err;
	}
	else 
		obj->translation = vec(0,0,0);

	if (rotate)
	{
		err = parse_point3(rotate, &obj->rotation);
		obj->rotation.x = convert_to_radians(obj->rotation.x);
		obj->rotation.y = convert_to_radians(obj->rotation.y);
		obj->rotation.z = convert_to_radians(obj->rotation.z);
		if (err != SUCCESS)
			return err;		
	}
	else
		obj->rotation = vec(0,0,0);

	// 2. Reflexión y Transparencia
	if (!reflect)
		obj->reflect = 0; //por defecto no refleja
	else
	{
		if (!cJSON_IsNumber(reflect))
			return JSON_E;
		obj->reflect = reflect->valuedouble;
		if (bad_ratio(obj->reflect, 0, 1))
			return BRIGHT_E;
	}
	if (!transp)
		obj->transparency = 0; // por defecto no es transparente
	else
	{
		if (!cJSON_IsNumber(transp))
			return JSON_E;
		obj->transparency = transp->valuedouble;
		if (bad_ratio(obj->transparency, 0, 1))
			return TRANSP_E;
	}
	// Normalizar transparencia y reflexión
	double sum_rt = obj->transparency + obj->reflect;
	if (sum_rt > 1)
	{
		double scale = 1.0 / sum_rt;
		obj->reflect *= scale;
		obj->transparency *= scale;
	}

	// 3. Índice de refracción
	if (!ior)
		obj->ior = 1; // por defecto no hay refracción
	else
	{
		if (!cJSON_IsNumber(ior))
			return JSON_E;
		obj->ior = ior->valuedouble;
		if (bad_ratio(obj->ior, 1, 5))
			return IOR_E;
		
	}

	// 4. Color
	if (!color)
		obj->color = (t_color){255,255,255}; // blanco por defecto
	else
	{
		err = parse_color(color, &obj->color);
		if (err != SUCCESS)
			return err;
	}

	// 5. Brillo
	if (!shine)
		obj->shine = 10; //por defecto no hay brillo
	else
	{
		if (!cJSON_IsNumber(shine))
			return JSON_E;
		obj->shine = shine->valuedouble;
		if (bad_ratio(obj->shine, 10, 1000))
			return SHINE_E;
	}
	
	// 6. Slice	
	if (slice)
	{
		if (!cJSON_IsArray(slice))
			return JSON_E;
		obj->slices = parse_slices(slice);
		if (!obj->slices)
			return MEMORY_E;
		check_intersections_slices(obj);
	}
	else
		obj->slices = NULL; // por defecto no hay slice

	// 7. Texture
	if (!texture)
		obj->texture = NULL; // por defecto no hay textura
	else
	{
		if (!cJSON_IsString(texture))
			return JSON_E;
		obj->texture = load_texture(texture->valuestring);
		if (!obj->texture)
			return TEXTURE_E;
	}
	return SUCCESS;
}
