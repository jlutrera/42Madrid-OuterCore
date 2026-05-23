/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:05:54 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/25 16:05:54 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera *get_active_camera(t_scene *scene)
{
	t_camera *cam = scene->camera;
	while (cam)
	{
		if (cam->active)
			return cam;
		cam = cam->next;
	}
	return scene->camera;
}

void    update_menu_camera(t_context *ctx)
{
	if (ctx->camera_menu)
    {
        gtk_widget_destroy(ctx->camera_menu);
        ctx->camera_menu = NULL;
    }
    GtkWidget *menu = gtk_menu_new();
	ctx->camera_menu = menu;
    t_camera *cam = ctx->scene->camera;
    GSList *group = NULL;
    int num_cam = 0;

    while (cam && num_cam < 10)
    {
        char label[10];
        sprintf(label, "%d", num_cam + 1);

        GtkWidget *item;
        if (num_cam == 0)
            item = gtk_radio_menu_item_new_with_label(NULL, label);
        else
            item = gtk_radio_menu_item_new_with_label(group, label);

        group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(item));

        // Conectar señal (puedes pasar el índice si quieres)
        g_signal_connect(item, "toggled", G_CALLBACK(on_camera_selected), ctx);

        gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

        ctx->camera_menu_items[num_cam] = item;

        // Marcar si esta cámara está activa
        if (cam->active)
            gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);

        cam = cam->next;
        num_cam++;
    }

    ctx->camera_count = num_cam;

    gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(ctx->btn_camera), menu);
    gtk_widget_show_all(menu);
}

void	move_camera(t_context *ctx, guint dir)
{
	double move = 1.0;
	t_camera *cam = get_active_camera(ctx->scene);
	if (!cam)
		return ;

	// Muevo la cámara según su sistema de referencia, 
	// quiero crear un movimiento según la posición del usuario
	t_vec right   = cam->localbase.u;
	t_vec up      = cam->localbase.v;
	t_vec forward = cam->localbase.w;

	if (dir == GDK_KEY_Up)
		cam->position = vec_sub(cam->position, vec_mul(up, move));
		
	else if (dir == GDK_KEY_Down)
		cam->position = vec_add(cam->position, vec_mul(up, move));
		
	else if (dir == GDK_KEY_Left)
		cam->position = vec_sub(cam->position, vec_mul(right, move));

	else if (dir == GDK_KEY_Right)
		cam->position = vec_add(cam->position, vec_mul(right, move));

	else if (dir == GDK_KEY_Page_Up)
		cam->position = vec_sub(cam->position, vec_mul(forward, move));

	else //if (dir == GDK_KEY_Page_Down)
		cam->position = vec_add(cam->position, vec_mul(forward, move));

	// Borro los rayos precalculados y los recalculo

	if (cam->prec_rays)
	{
		for (int i = 0; i < ctx->scene->height; i++)
			free(cam->prec_rays[i]);
		free(cam->prec_rays);
	}
	cam->prec_rays = precalculated_rays(cam, ctx->scene->height, ctx->scene->width);

	render_scene(ctx);
}
