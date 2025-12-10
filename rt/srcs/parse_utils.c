/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:51:14 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/21 10:51:14 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int parse_point3(cJSON *obj, t_point3 *p)
{
	const char *str = cJSON_GetStringValue(obj);
	if (!str)
		return JSON_E;

	char extra;
	if (sscanf(str, "%lf,%lf,%lf%c", &p->x, &p->y, &p->z, &extra) != 3)
		return POINT_E;
	return SUCCESS;
}

int parse_color(cJSON *obj,  t_color *color)
{
	const char *str = cJSON_GetStringValue(obj);
	if (!str)
		return JSON_E;

	
	char extra;
	if (sscanf(str, "%d,%d,%d%c", &color->r, &color->g, &color->b, &extra) != 3)
		return COLOR_E;

	if (bad_color(*color))
		return COLOR_E;

	return SUCCESS;
}

int parse_vec(cJSON *obj, t_vec *v)
{
	const char *str = cJSON_GetStringValue(obj);
	if (!str)
		return JSON_E;

	char extra;
	if (sscanf(str, "%lf,%lf,%lf%c", &v->x, &v->y, &v->z, &extra) != 3)
		return (DIR_E);
	
	if (bad_norm(*v))
		return NORM_E;

	if (bad_direction(*v))
		return DIR_E;

	return SUCCESS;
}

void	add_object(t_scene *scene, t_lst_obj *new_obj)
{
	if (!scene->obj)
		scene->obj = new_obj;
	else
	{
		t_lst_obj *last = scene->obj;
		while (last->next)
			last = last->next;
		last->next = new_obj;
	}
}

cJSON *point_to_json(double x, double y, double z)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%.3f,%.3f,%.3f", x, y, z);
    return cJSON_CreateString(buf);
}

cJSON *color_to_json(int x, int y, int z)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%d,%d,%d", x, y, z);
    return cJSON_CreateString(buf);
}