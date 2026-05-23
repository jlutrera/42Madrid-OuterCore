/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:06:32 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/25 16:06:32 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 	"rt.h"

static int **allocate_rgb_buffer(int width, int height)
{
	int **rgb_buffer = calloc(sizeof(int *), height);
	if (!rgb_buffer)
		return NULL;

	for (int i = 0; i < height; i++)
	{
		rgb_buffer[i] = calloc((size_t)width, sizeof *rgb_buffer[i]);
		if (!rgb_buffer[i])
		{
			for (int j = 0; j < i; j++)
				free(rgb_buffer[j]);
			free(rgb_buffer);
			return NULL;
		}
	}
	
	return rgb_buffer;
}

static t_context *init_ctx(GtkBuilder *builder, t_scene *scene)
{
	t_context *ctx = malloc(sizeof(t_context));
	if (!ctx)
    	return NULL;
	memset(ctx, 0, sizeof(t_context));

	GtkWidget *btn_load      = GTK_WIDGET(gtk_builder_get_object(builder, "btn_load"));
	GtkWidget *btn_capture   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_capture"));
	GtkWidget *btn_create    = GTK_WIDGET(gtk_builder_get_object(builder, "btn_create"));
	GtkWidget *btn_composite = GTK_WIDGET(gtk_builder_get_object(builder, "btn_composite"));
	GtkWidget *btn_exit      = GTK_WIDGET(gtk_builder_get_object(builder, "btn_exit"));
	GtkWidget *btn_filter	 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_filter"));
	ctx->btn_camera		     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_camera"));
	ctx->main_window   		 = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	ctx->drawing_area  		 = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
	ctx->status_label  		 = GTK_WIDGET(gtk_builder_get_object(builder, "status_label"));
	ctx->progress_bar		 = GTK_WIDGET(gtk_builder_get_object(builder, "progress_bar"));
	ctx->gizmo_btn		     = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "btn_gizmo"));
	ctx->gizmo_window        = NULL;
	ctx->gizmo_area			 = NULL;
	ctx->scene         		 = scene;
	ctx->camera_menu   		 = NULL;
	ctx->render_finished	 = TRUE;
	gtk_widget_set_visible(ctx->progress_bar, FALSE); 
	gtk_window_set_title(GTK_WINDOW(ctx->main_window), "Ray Tracing by jutrera-");
	gtk_widget_set_size_request(ctx->drawing_area, scene->width, scene->height);

	// Callbacks
	g_signal_connect(btn_load,      "clicked", G_CALLBACK(on_btn_load_clicked), ctx);
	g_signal_connect(btn_capture,   "clicked", G_CALLBACK(on_btn_capture_clicked), ctx);
	g_signal_connect(btn_create,    "clicked", G_CALLBACK(on_btn_create_clicked), ctx);
	g_signal_connect(btn_composite, "clicked", G_CALLBACK(on_btn_composite_clicked), ctx);
	g_signal_connect(btn_exit,      "clicked", G_CALLBACK(on_btn_exit_clicked), ctx);
	g_signal_connect(ctx->drawing_area,"draw", G_CALLBACK(on_drawing_area_draw), ctx);
	g_signal_connect(ctx->main_window, "delete-event", G_CALLBACK(on_close_mainwindow), ctx);
	g_signal_connect(ctx->main_window, "key-press-event", G_CALLBACK(on_key_press), ctx);
	g_signal_connect(ctx->gizmo_btn,   "toggled", G_CALLBACK(on_toggle_gizmo), ctx);

	// Añadir menú de filtros
	GtkWidget *menu = gtk_menu_new();
	GSList *group = NULL;

	const char *filters[] = {"None", "Grayscale", "Sepia", "Invert", "Posterize"};

	for (int i = 0; i < 5; ++i)
	{
		GtkWidget *item;
		if (i == 0)
			item = gtk_radio_menu_item_new_with_label(NULL, filters[i]);
		else
			item = gtk_radio_menu_item_new_with_label(group, filters[i]);

		group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(item));
		ctx->filter_menu_items[i] = item;
		g_signal_connect(item, "toggled", G_CALLBACK(on_filter_selected), ctx);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	}

	gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(btn_filter), menu);
	gtk_widget_show_all(menu);

	set_status_label(ctx->status_label, "Ready — awaiting your first render");

	return ctx;
}

t_context *init_gui(void)
{
    GtkBuilder *builder = gtk_builder_new_from_file("gui/gtk_menu.ui");

    if (!builder)
    {
        printf("Error loading the interface from file\n");
        return NULL;
    }

	t_scene *scene = init_scene();
	if (!scene)
	{
        printf("Error: Could not init scene structure\n");
		g_object_unref(builder);
        return NULL;	
	}

	t_context *ctx = init_ctx(builder, scene);
	if (!ctx)
	{
		printf("Error: Could not init context structure\n");
		g_object_unref(builder);
		free_scene(scene);
		return NULL;
	}
	
	g_object_unref(builder);
	gtk_widget_set_can_focus(ctx->main_window, TRUE);
    gtk_widget_grab_focus(ctx->main_window);
	gtk_widget_show_all(ctx->main_window);

	return ctx;
}

t_scene	*init_scene(void)
{
	t_scene *scene = (t_scene *) malloc (sizeof(t_scene));
	if (!scene)
		return NULL;

	scene->ambient.declared = false;
	scene->directional.declared = false;
	scene->filter_type = ORIGINAL;
	scene->spotlight = NULL;
	scene->obj = NULL;
	scene->camera = NULL;
	scene->composites = NULL;
	
	scene->width = WIDTH;
	if (WIDTH > 2500 || WIDTH < 800)
		scene->width = 2500;
	scene->height = (int)(scene->width / ASPECTRATIO);
	if (scene->height < 600)
    {
        scene->width = 800;
		scene->height = 600;
    }
	
	scene->rgb_buffer = allocate_rgb_buffer(scene->width, scene->height);
	if (!scene->rgb_buffer)
		return NULL;
	
	scene->rgb_buffer_filtered = allocate_rgb_buffer(scene->width, scene->height);
	if (!scene->rgb_buffer_filtered)
	{
		free_rgb_buffer(scene->rgb_buffer, scene->height);
		return NULL;
	}
	return scene;
}
