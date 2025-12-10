/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 09:43:27 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/04 09:43:27 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int create_camera(cJSON *cam_json, t_camera *new_cam)
{
	int err;

	cJSON *pos = cJSON_GetObjectItem(cam_json, "position");
	cJSON *dir = cJSON_GetObjectItem(cam_json, "direction");
	cJSON *fov = cJSON_GetObjectItem(cam_json, "fov");

	if (!pos || !dir || !fov)
		return FIELD_E;

	err = parse_point3(pos, &new_cam->position);
	if (err != SUCCESS)
		return err;
	err = parse_vec(dir, &new_cam->direction);
	if (err != SUCCESS)
		return err;
	new_cam->direction = vec_unit(new_cam->direction);
	new_cam->fov = fov->valueint;
	if (bad_ratio(new_cam->fov, 10, 180))
		return FOV_E;
	new_cam->next = NULL;
	new_cam->active = false;
	
	return SUCCESS;
}

int	parse_cameras(t_scene *scene, cJSON *json)
{
	cJSON *cameras = cJSON_GetObjectItem(json, "cameras");
	if (!cameras || !cJSON_IsArray(cameras) || cJSON_GetArraySize(cameras) == 0)
		return (ANY_CAM_E);

	t_camera *first = NULL;
	t_camera *last = NULL;
	cJSON *cam_json;

	cJSON_ArrayForEach(cam_json, cameras)
	{
		t_camera *new_cam  = calloc(1, sizeof(t_camera));
		if (!new_cam)
			return MEMORY_E;		

		int err = create_camera(cam_json, new_cam);
		if (err != SUCCESS)
		{
			free(new_cam);
			while (first)
			{
				t_camera *aux = first;
				first = first->next;
				free(aux);
			}
			return (err);
		}
		if (!first)
			first = new_cam;
		else
			last->next = new_cam;
		last = new_cam;
	}
	scene->camera = first;
	scene->camera->active = true;

	return (SUCCESS);
}
