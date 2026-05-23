/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:07 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/06 13:24:11 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void connect_btn_editor_signals(t_context *ctx)
{
    GtkBuilder *builder = ctx->creator_builder;

    GtkWidget *btn_camera      = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_camera"));
    GtkWidget *btn_spot        = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_spot"));
    GtkWidget *btn_directional = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_directional"));
    GtkWidget *btn_pl          = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_pl"));
    GtkWidget *btn_sp          = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_sp"));
    GtkWidget *btn_cy          = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_cy"));
    GtkWidget *btn_co          = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_co"));
    GtkWidget *btn_pa          = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_pa"));
    GtkWidget *btn_to          = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_to"));
    GtkWidget *btn_mo          = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_mo"));
    GtkWidget *btn_library     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_library"));
    GtkWidget *btn_delete      = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
    GtkWidget *btn_save        = GTK_WIDGET(gtk_builder_get_object(builder, "btn_save"));
    GtkWidget *btn_render      = GTK_WIDGET(gtk_builder_get_object(builder, "btn_render"));
    GtkWidget *btn_quit        = GTK_WIDGET(gtk_builder_get_object(builder, "btn_quit"));

    g_signal_connect(ctx->creator_window, "delete-event", G_CALLBACK(on_close_secondwindow), ctx);
    g_signal_connect(btn_camera,      "clicked", G_CALLBACK(on_btn_add_camera_clicked), ctx);
    g_signal_connect(btn_spot,        "clicked", G_CALLBACK(on_btn_add_spot_clicked), ctx);
    g_signal_connect(btn_directional, "clicked", G_CALLBACK(on_btn_add_directional_clicked), ctx);
    g_signal_connect(btn_pl,          "clicked", G_CALLBACK(on_btn_add_pl_clicked), ctx);
    g_signal_connect(btn_sp,          "clicked", G_CALLBACK(on_btn_add_sp_clicked), ctx);
    g_signal_connect(btn_cy,          "clicked", G_CALLBACK(on_btn_add_cy_clicked), ctx);
    g_signal_connect(btn_co,          "clicked", G_CALLBACK(on_btn_add_co_clicked), ctx);
    g_signal_connect(btn_pa,          "clicked", G_CALLBACK(on_btn_add_pa_clicked), ctx);
    g_signal_connect(btn_to,          "clicked", G_CALLBACK(on_btn_add_to_clicked), ctx);
    g_signal_connect(btn_mo,          "clicked", G_CALLBACK(on_btn_add_mo_clicked), ctx);
    g_signal_connect(btn_library  ,   "clicked", G_CALLBACK(on_btn_add_library_clicked), ctx);
    g_signal_connect(btn_delete,      "clicked", G_CALLBACK(on_btn_delete_clicked), ctx);
    g_signal_connect(btn_save,        "clicked", G_CALLBACK(on_btn_save_clicked), ctx);
    g_signal_connect(btn_render,      "clicked", G_CALLBACK(on_btn_render_clicked), ctx);
    g_signal_connect(btn_quit,        "clicked", G_CALLBACK(on_btn_quit_clicked), ctx);
}

static void connect_btn_compose_signals(t_composite_widgets *ui)
{
    GtkBuilder *builder = gtk_builder_new_from_file("gui/gtk_compose.ui");
    
    GtkWidget *btn_add_pl = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_pl"));
    GtkWidget *btn_add_sp = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_sp"));
    GtkWidget *btn_add_cy = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_cy"));
    GtkWidget *btn_add_co = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_co"));
    GtkWidget *btn_save   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_save"));
    GtkWidget *btn_delete = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
    GtkWidget *btn_quit   = GTK_WIDGET(gtk_builder_get_object(builder, "btn_quit"));
    ui->window            = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    ui->notebook          = GTK_WIDGET(gtk_builder_get_object(builder, "notebook_compose"));
    ui->entry_name        = GTK_WIDGET(gtk_builder_get_object(builder, "composeNameEntry"));

    g_signal_connect(ui->window, "delete-event", G_CALLBACK(on_close_composeWindow), ui->window);
    g_signal_connect(btn_add_pl, "clicked", G_CALLBACK(on_addCompose_plane), ui);
    g_signal_connect(btn_add_sp, "clicked", G_CALLBACK(on_addCompose_sphere), ui);
    g_signal_connect(btn_add_cy, "clicked", G_CALLBACK(on_addCompose_cylinder), ui);
    g_signal_connect(btn_add_co, "clicked", G_CALLBACK(on_addCompose_cone), ui);
    g_signal_connect(btn_delete, "clicked", G_CALLBACK(on_deleteCompose), ui);
    g_signal_connect(btn_save,   "clicked", G_CALLBACK(on_saveCompose), ui);
    g_signal_connect(btn_quit,   "clicked", G_CALLBACK(on_quitCompose), ui);
   
    g_object_unref(builder);
}

static gboolean confirm_exit(GtkWidget *parent)
{
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(parent)),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Do you really want to exit?");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return (response == GTK_RESPONSE_YES);
}

void on_btn_exit_clicked(GtkButton *button, gpointer user_data)
{   
    t_context *ctx = user_data;
    if (!ctx->render_finished)
        return;
    
    if (confirm_exit(GTK_WIDGET(button)))
        gtk_main_quit();
}

int get_camera_index(t_camera *camera)
{
    int index = 1;
    t_camera *cam = camera;
    while (cam)
    {
        if (cam->active)
            return index;
        cam = cam->next;
        index++;
    }
    return 1;
}

void on_toggle_gizmo(GtkToggleButton *toggle_button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    gboolean active = gtk_toggle_button_get_active(toggle_button);

    if (active && ctx->scene->camera)
    {
        if (ctx->gizmo_window != NULL)
        {
            gtk_window_present(GTK_WINDOW(ctx->gizmo_window));
            return;
        }

        ctx->gizmo_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_widget_set_size_request(ctx->gizmo_window, 220, 220);
        
        // Muestra la cánara activa
        int cam_index = get_camera_index(ctx->scene->camera);
        char label[32];
        snprintf(label, sizeof(label), "Cam %d", cam_index);
        gtk_window_set_title(GTK_WINDOW(ctx->gizmo_window), label);
        
        g_signal_connect(ctx->gizmo_window, "destroy", G_CALLBACK(on_gizmo_window_destroy), ctx);

        ctx->gizmo_area = gtk_drawing_area_new();
        gtk_widget_set_hexpand(ctx->gizmo_area, TRUE);
        gtk_widget_set_vexpand(ctx->gizmo_area, TRUE);
        gtk_container_add(GTK_CONTAINER(ctx->gizmo_window), ctx->gizmo_area);

        g_signal_connect(G_OBJECT(ctx->gizmo_area), "draw", G_CALLBACK(on_gizmo_draw), ctx);

        gtk_widget_show_all(ctx->gizmo_window);
    }
    else if (ctx->gizmo_window != NULL)
        gtk_widget_destroy(ctx->gizmo_window);
}

gboolean on_close_mainwindow(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    t_context *ctx = user_data;
    if (!ctx->render_finished)
        return TRUE; // Prevent closing
    
    if (confirm_exit(widget))
    {
        gtk_main_quit();
        return FALSE;
    }
    return TRUE; 
}

void on_btn_create_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    if (!ctx->render_finished)
        return;

    if (ctx->creator_window && gtk_widget_get_visible(ctx->creator_window))
    {
        gtk_window_present(GTK_WINDOW(ctx->creator_window));
        return;
    }

    ctx->creator_builder = gtk_builder_new_from_file("gui/gtk_creator.ui");

    if (!ctx->creator_builder)
    {
        set_status_label(ctx->status_label, "Error loading the interface from file\n");
        return ;
    }

    ctx->creator_window = GTK_WIDGET(gtk_builder_get_object(ctx->creator_builder, "main_window"));
    gtk_window_set_title(GTK_WINDOW(ctx->creator_window), "Scene Creator");
    connect_btn_editor_signals(ctx);

    // La ventana secundaria aparece siempre por encima de la principal
    gtk_window_set_transient_for(GTK_WINDOW(ctx->creator_window), GTK_WINDOW(ctx->main_window));

    // Añadir Camera 1 y Ambient SIEMPRE
    add_minimum_elements(ctx->creator_builder);  

    gtk_widget_show_all(ctx->creator_window);
}

void on_filter_selected(GtkWidget *menu_item, gpointer user_data)
{
    t_context *ctx = user_data;

    const gchar *filter = gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item));
        
    if (g_strcmp0(filter, "None") == 0)
    {
        ctx->scene->filter_type = ORIGINAL;
        set_status_label(ctx->status_label, "");
     
    }
    else if (g_strcmp0(filter, "Grayscale") == 0)
    {
        ctx->scene->filter_type = GRAYSCALE;
        set_status_label(ctx->status_label, "Filter selected: Grayscale");
    }
    else if (g_strcmp0(filter, "Sepia") == 0)
    {
        ctx->scene->filter_type = SEPIA;
        set_status_label(ctx->status_label, "Filter selected: Sepia");
    }
    else if (g_strcmp0(filter, "Invert") == 0)
    {
        ctx->scene->filter_type = INVERT;
        set_status_label(ctx->status_label, "Filter selected: Invert");
    }
    else if (g_strcmp0(filter, "Posterize") == 0)
    {
        ctx->scene->filter_type = POSTERIZE;
        set_status_label(ctx->status_label, "Filter selected: Posterize");
    }

    if (ctx->scene->rgb_buffer && ctx->scene->camera)
        draw_rgb_buffer(ctx);
}

void on_camera_selected(GtkWidget *menu_item, gpointer user_data)
{
    t_context *ctx = user_data;
    
    if (!ctx->render_finished)
        return;

    t_camera *cam = ctx->scene->camera;
    if (!cam)
        return;

    // // Si el item NO está activo, ignoramos el evento
    if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menu_item)))
        return;

    const gchar *cam_selected = gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item));
    int index = cam_selected[0] - '0';
    int n = 1;
    while (cam)
    {
        cam->active = (n == index);
        cam = cam->next;
        n++;
    }
    
   render_scene(ctx);
}

void on_btn_load_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog;
    t_context *ctx = user_data;

    if (!ctx->render_finished)
        return;

    GtkWindow *window = GTK_WINDOW(ctx->main_window);
 
    dialog = gtk_file_chooser_dialog_new("Open .rt File",
                                         window,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Open", GTK_RESPONSE_ACCEPT,
                                         NULL);
    GtkFileChooser *chooser= GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_current_folder(chooser, "./scenes");

    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "RT files");
    gtk_file_filter_add_pattern(filter, "*.rt");
    gtk_file_chooser_add_filter(chooser, filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {        
        gchar *filename = gtk_file_chooser_get_filename(chooser);
        gchar *basename = g_path_get_basename(filename);
        set_status_label(ctx->status_label, "File %s loaded successfully", basename);

        int err = process_load(filename, ctx);
        if (err > 0)
            set_status_label(ctx->status_label, err_msg(err));
        else
            update_menu_camera(ctx);
        g_free(basename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void on_btn_capture_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog;
    t_context *ctx = user_data;
    
    if (!ctx->render_finished)
        return;
    
    if (!ctx->scene->camera)
    {
        set_status_label(ctx->status_label, "No scene to capture");
        return;
    }
    
 	dialog = gtk_file_chooser_dialog_new("Save image",
 		                                 NULL,
 		                                 GTK_FILE_CHOOSER_ACTION_SAVE,
 		                                 "_Cancel", GTK_RESPONSE_CANCEL,
 		                                 "_Save", GTK_RESPONSE_ACCEPT,
 		                                 NULL);

 	GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_current_folder(chooser, "./images");

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
    gtk_file_chooser_set_current_name(chooser, "scene.png");

 	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
 	{
 		gchar *filename = gtk_file_chooser_get_filename(chooser);
        gchar *basename = g_path_get_basename(filename);
        set_status_label(ctx->status_label, "Image saved as: %s", basename);
        int err = process_save(filename, ctx);
        if (err)
            set_status_label(ctx->status_label, err_msg(err));
        g_free(filename);
        g_free(basename);
 	}
 	gtk_widget_destroy(dialog);
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    t_context *ctx = user_data;

    if (ctx->render_finished && event->keyval == GDK_KEY_Escape)
        confirm_exit(ctx->main_window) ? gtk_main_quit() : TRUE;
    
    else if (event->keyval == GDK_KEY_L || event->keyval == GDK_KEY_l)
        on_btn_load_clicked(NULL, ctx);

    else if (event->keyval == GDK_KEY_C || event->keyval == GDK_KEY_c)
        on_btn_capture_clicked(NULL, ctx);

    else if (event->keyval == GDK_KEY_S || event->keyval == GDK_KEY_s)
        on_btn_create_clicked(NULL, ctx);

    else if (event->keyval == GDK_KEY_M || event->keyval == GDK_KEY_m)
        on_btn_create_clicked(NULL, ctx);
        
    else if (ctx->render_finished && ctx->scene->camera &&
            (event->keyval == GDK_KEY_Left    || 
             event->keyval == GDK_KEY_Right   ||
             event->keyval == GDK_KEY_Up      ||
             event->keyval == GDK_KEY_Down    ||
             event->keyval == GDK_KEY_Page_Up ||
             event->keyval == GDK_KEY_Page_Down ))
        move_camera(ctx, event->keyval);

    else if (event->keyval == GDK_KEY_N || event->keyval == GDK_KEY_n ||
             event->keyval == GDK_KEY_G || event->keyval == GDK_KEY_g ||
             event->keyval == GDK_KEY_E || event->keyval == GDK_KEY_e ||
             event->keyval == GDK_KEY_I || event->keyval == GDK_KEY_i ||
             event->keyval == GDK_KEY_P || event->keyval == GDK_KEY_p)
        select_filter(ctx, event->keyval);

    else if (ctx->render_finished && event->keyval >= '1' && event->keyval <= '9')
    {
        int index = event->keyval - '0';
        if (index <= ctx->camera_count)
            gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ctx->camera_menu_items[index-1]), TRUE);
    }   
    
    return TRUE;
}

gboolean on_drawing_area_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    t_context *ctx = user_data;
    if (!ctx->render_finished)
    {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_paint(cr);
        return TRUE;
    }

    int width = ctx->scene->width;
	int height = ctx->scene->height;
	int **rgb_to_draw;
	if (ctx->scene->filter_type == ORIGINAL)
    	rgb_to_draw = (int **)ctx->scene->rgb_buffer;
	else
		rgb_to_draw = (int **)ctx->scene->rgb_buffer_filtered;


    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    unsigned char *data = cairo_image_surface_get_data(surface);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int rgb = rgb_to_draw[y][x];
            int offset = (y * width + x) * 4;
            data[offset + 3] = 0xFF;               // Alpha channel (not used)
            data[offset + 2] = (rgb >> 16) & 0xFF; // R
            data[offset + 1] = (rgb >> 8) & 0xFF;  // G
            data[offset + 0] = rgb & 0xFF;         // B
        }

    cairo_surface_mark_dirty(surface);
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_surface_destroy(surface);
    cairo_paint(cr);
    
    return TRUE;
}

void on_btn_composite_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;

    if (!ctx->render_finished)
        return;
    
    t_composite_widgets *ui = g_malloc0(sizeof(t_composite_widgets));
    
    connect_btn_compose_signals(ui);
    gtk_window_set_title(GTK_WINDOW(ui->window), "Composite Designer");
    gtk_widget_show_all(ui->window);

    // La ventana secundaria aparece siempre por encima de la principal
    gtk_window_set_transient_for(GTK_WINDOW(ui->window), GTK_WINDOW(ctx->main_window));
}
