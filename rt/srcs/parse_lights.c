/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:36:03 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/12 19:36:03 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	create_spot(cJSON *spot_json, t_spotlight *spot)
{
	int err;

	cJSON *pos = cJSON_GetObjectItem(spot_json, "position");
	cJSON *bright = cJSON_GetObjectItem(spot_json, "bright");
	cJSON *color = cJSON_GetObjectItem(spot_json, "color");

	if (!pos || !bright || !color)
		return (FIELD_E);
	err = parse_point3(pos, &spot->position);
	if (err != SUCCESS)
		return err;
	spot->bright = bright->valuedouble;
	if (bad_ratio(spot->bright, 0, 1))
		return BRIGHT_E;
	err = parse_color(color, &spot->color);
	if (err != SUCCESS)
		return err;
	spot->next = NULL;

	return SUCCESS;
}

static int	parse_spotlights(t_scene *scene, cJSON *json)
{
	cJSON *spots = cJSON_GetObjectItem(json, "spots");
	if (!spots || !cJSON_IsArray(spots))
		return (SUCCESS);
	t_spotlight *first = NULL;
	t_spotlight *last = NULL;

	cJSON *spot_json;
	cJSON_ArrayForEach(spot_json, spots)
	{
		t_spotlight *new_spot = calloc(sizeof(t_spotlight), 1);
		if (!new_spot)
			return MEMORY_E;

		int err = create_spot(spot_json, new_spot);
		if (err != SUCCESS)
		{
			free(new_spot);
			while (first)
			{
				t_spotlight *aux;
				aux = first;
				first = first->next;
				free(aux);
			}
			return (err);
		}
		if (!first)
			first = new_spot;
		else
			last->next = new_spot;
		last = new_spot;
	}

	scene->spotlight = first;
	return (SUCCESS);
}

static int	parse_directional(t_scene *scene, cJSON *json)
{
	int err;

	cJSON *directional = cJSON_GetObjectItem(json, "directional");
	if (!directional || !cJSON_IsObject(directional))
		return (SUCCESS);
	if (scene->directional.declared)
		return (DIRECT_E);

	cJSON *bright = cJSON_GetObjectItem(directional, "bright");
	cJSON *color = cJSON_GetObjectItem(directional, "color");
	cJSON *direction = cJSON_GetObjectItem(directional, "direction");
	if (!bright || !color || !direction)
		return (FIELD_E);

	scene->directional.bright = bright->valuedouble;
	if (bad_ratio(scene->directional.bright, 0, 1))
		return (BRIGHT_E);

	err = parse_color(color, &scene->directional.color);
	if (err != SUCCESS)
		return (err);

	err = parse_vec(direction, &scene->directional.direction);
	if (err != SUCCESS)
		return (err);
	scene->directional.direction = vec_unit(scene->directional.direction);
	scene->directional.declared = true;
	return (SUCCESS);
}

static int	parse_ambient(t_scene *scene, cJSON *json)
{
	int err;

	cJSON *ambient = cJSON_GetObjectItem(json, "ambient");
	if (!ambient || !cJSON_IsObject(ambient))
	{
		scene->ambient.color = (t_color){255,255, 255};
		scene->ambient.bright = 0.25;
		scene->ambient.declared = true;
		return (SUCCESS);
	}
	if (scene->ambient.declared)
		return (AMBIENT_E);

	cJSON *bright = cJSON_GetObjectItem(ambient, "bright");
	cJSON *color = cJSON_GetObjectItem(ambient, "color");
	if (!bright || !color)
		return (FIELD_E);

	scene->ambient.bright = bright->valuedouble;
	if (bad_ratio(scene->ambient.bright, 0.25, 1))
		return (AMBI_BR_E);

	err = parse_color(color, &scene->ambient.color);
	if (err != SUCCESS)
		return (err);

	scene->ambient.declared = true;
	return (SUCCESS);
}

int parse_lights(t_scene *scene, cJSON *json)
{
	int err;

	if ((err = parse_ambient(scene, json)) != SUCCESS)
		return (err);
	if ((err = parse_directional(scene, json)) != SUCCESS)
		return (err);	
	if ((err = parse_spotlights(scene, json)) != SUCCESS)
		return (err);

	return (err);
}
