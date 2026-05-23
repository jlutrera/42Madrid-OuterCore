/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:41 by jutrera           #+#    #+#             */
/*   Updated: 2025/08/19 19:21:13 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"rt.h"

static void free_objects(t_lst_obj	*object)
{
	t_lst_obj	*ob;

	while (object)
	{
		ob = object;
		object = object->next;

		while (ob->slices)
		{
			t_slices *tmp = ob->slices;
			ob->slices = ob->slices->next;
			free(tmp);
		}
		free(ob->slices);
		free(ob->object);
		if (ob->texture)
			free_texture(ob->texture);
		free(ob);
	}
}

static void free_spotlights(t_spotlight *spotlight)
{
	t_spotlight	*light;

	while (spotlight)
	{
		light = spotlight;
		spotlight = spotlight->next;
		free(light);
	}
	free(spotlight);

}

static void free_cameras(t_camera *camera, int height)
{
	t_camera	*cam;

	while (camera)
	{
		cam = camera;
		if (cam->prec_rays)
		{
			for (int i = 0; i < height; i++)
				free(cam->prec_rays[i]);
			free(cam->prec_rays);
		}
		camera = cam->next;
		free(cam);
	}
	free(camera);
}

void free_composites(t_composite *composites)
{
	t_composite *comp;

	while (composites)
	{			
		comp = composites;
		free_objects(comp->objects);
		free(comp->name);
		composites = composites->next;
		free(comp);
	}
}

void free_rgb_buffer(int **rgb_buffer, int height)
{
	if (rgb_buffer)
	{
		for (int i = 0; i < height; i++)
			free(rgb_buffer[i]);
		free(rgb_buffer);
	}
}

void	free_scene(t_scene *scene)
{
	t_lst_obj	*ob, *ob_comp;
	t_spotlight	*light;
	t_camera	*cam;
	t_composite *comp;

	if (!scene)
		return ;
	
	// Elimina todos los objetos
	free_objects(scene->obj);

	//Elimina todos los compuestos
	free_composites(scene->composites);

	// Elimina todos los puntos de luz
	free_spotlights(scene->spotlight);

	// Elimina las cámaras
	free_cameras(scene->camera, scene->height);

	//Elimina la imagen guardada con y sin filtros
	free_rgb_buffer(scene->rgb_buffer, scene->height);
	free_rgb_buffer(scene->rgb_buffer_filtered, scene->height);

	//Elimina la escena
	free(scene);
}
