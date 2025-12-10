/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:35:53 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/28 12:50:24 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int camera_count = 0;
int spot_count = 0;
bool directional_created = false;
int plane_count = 0;
int sphere_count = 0;
int cylinder_count = 0;
int cone_count = 0;
int paraboloid_count = 0;
int toroid_count = 0;
int moebius_count = 0;
int instances_count = 0;

static void free_slice_widget(gpointer data)
{
    t_slice_widgets *slice = (t_slice_widgets *)data;
    if (slice)
        g_free(slice);
}

static void free_gui_data(GtkBuilder *builder)
{
    GtkNotebook *notebook = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook_scene_elements"));
    int page_count = gtk_notebook_get_n_pages(notebook);

    for (int i = 0; i < page_count; i++)
    {
        GtkWidget *child = gtk_notebook_get_nth_page(notebook, i);
        GtkWidget *tab_label = gtk_notebook_get_tab_label(notebook, child);
        const gchar *tab_title = gtk_label_get_text(GTK_LABEL(tab_label));

        if (g_str_has_prefix(tab_title, "Cylinder"))
        {
            t_cylinder_widgets *w = g_object_get_data(G_OBJECT(child), "cylinder_widgets");
            if (w)
            {
                t_common_widgets *w_common = g_object_get_data(G_OBJECT(w->grid_common), "common_widgets");
                if (w_common  && w_common->list_slices)
                    g_list_free_full(w_common->list_slices, (GDestroyNotify)free_slice_widget);
            }
        }
        else if (g_str_has_prefix(tab_title, "Cone"))
        {
            t_cone_widgets *w = g_object_get_data(G_OBJECT(child), "cone_widgets");
            if (w)
            {
                t_common_widgets *w_common = g_object_get_data(G_OBJECT(w->grid_common), "common_widgets");
                if (w_common  && w_common->list_slices)
                    g_list_free_full(w_common->list_slices, (GDestroyNotify)free_slice_widget);
            }
        }
        else if (g_str_has_prefix(tab_title, "Sphere"))
        {
            t_sphere_widgets *w = g_object_get_data(G_OBJECT(child), "sphere_widgets");
            if (w)
            {
                t_common_widgets *w_common = g_object_get_data(G_OBJECT(w->grid_common), "common_widgets");
                if (w_common  && w_common->list_slices)
                    g_list_free_full(w_common->list_slices, (GDestroyNotify)free_slice_widget);
            }
        }
        else if (g_str_has_prefix(tab_title, "Plane"))
        {
            t_plane_widgets *w = g_object_get_data(G_OBJECT(child), "plane_widgets");
            if (w)
            {
                t_common_widgets *w_common = g_object_get_data(G_OBJECT(w->grid_common), "common_widgets");
                if (w_common  && w_common->list_slices)
                    g_list_free_full(w_common->list_slices, (GDestroyNotify)free_slice_widget);
            }
        }
        else if (g_str_has_prefix(tab_title, "Paraboloid"))
        {
            t_paraboloid_widgets *w = g_object_get_data(G_OBJECT(child), "paraboloid_widgets");
            if (w)
            {
                t_common_widgets *w_common = g_object_get_data(G_OBJECT(w->grid_common), "common_widgets");
                if (w_common  && w_common->list_slices)
                    g_list_free_full(w_common->list_slices, (GDestroyNotify)free_slice_widget);
            }
        }
        else if (g_str_has_prefix(tab_title, "Torus"))
        {
            t_torus_widgets *w = g_object_get_data(G_OBJECT(child), "torus_widgets");
            if (w)
            {
                t_common_widgets *w_common = g_object_get_data(G_OBJECT(w->grid_common), "common_widgets");
                if (w_common  && w_common->list_slices)
                    g_list_free_full(w_common->list_slices, (GDestroyNotify)free_slice_widget);
            }
        }
        else if (g_str_has_prefix(tab_title, "Moebius"))
        {
            t_moebius_widgets *w = g_object_get_data(G_OBJECT(child), "moebius_widgets");
            if (w)
            {
                t_common_widgets *w_common = g_object_get_data(G_OBJECT(w->grid_common), "common_widgets");
                if (w_common  && w_common->list_slices)
                    g_list_free_full(w_common->list_slices, (GDestroyNotify)free_slice_widget);
            }
        }
    }
}

static void add_object_page(GtkBuilder *builder, const char *object_name, int *counter, GtkWidget *grid)
{
    GtkNotebook *notebook = GTK_NOTEBOOK(gtk_builder_get_object(builder, "notebook_scene_elements"));
    GtkWidget *label;
    if (strcmp(object_name, "Directional") != 0 && strcmp(object_name, "Ambient") != 0)
    {
        char label_text[64];
        sprintf(label_text, "%s %d", object_name, ++(*counter));
        label = gtk_label_new(label_text);
    }
    else
        label = gtk_label_new(object_name);
    
    int page_num = gtk_notebook_append_page(notebook, grid, label);
    gtk_widget_show_all(grid);
    gtk_notebook_set_current_page(notebook, page_num);
}

static gchar *ask_filename_dialog(GtkWindow *parent)
{
    GtkWidget *dialog;
    gchar *filename = NULL;

    dialog = gtk_file_chooser_dialog_new("Save scene",
                                         parent,
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Save", GTK_RESPONSE_ACCEPT,
                                         NULL);

    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "scene.rt");

    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Files (*.rt)");
    gtk_file_filter_add_pattern(filter, "*.rt");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

    gtk_widget_destroy(dialog);
    return filename;
}

static gboolean confirm_quit(GtkWidget *parent)
{
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(parent)),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Do you really want to quit?");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (response == GTK_RESPONSE_YES)
    {
        camera_count = 0;
        spot_count = 0;
        directional_created = false;
        plane_count = 0;
        sphere_count = 0;
        cylinder_count = 0;
        cone_count = 0;
        paraboloid_count = 0;
        toroid_count = 0;
        moebius_count = 0;
        instances_count = 0;
        return TRUE;
    }
    
    return FALSE;
}

void fix_tab_titles(GtkNotebook *notebook, const gchar *title)
{
    int counter = 1;
    int page_count = gtk_notebook_get_n_pages(notebook);

    for (int i = 0; i < page_count; i++)
    {
        GtkWidget *child = gtk_notebook_get_nth_page(notebook, i);
        GtkWidget *tab_label = gtk_notebook_get_tab_label(notebook, child);
        const gchar *tab_title = gtk_label_get_text(GTK_LABEL(tab_label));
    
        if (g_str_has_prefix(tab_title, title))
        {
            char new_title[64];
            sprintf(new_title, "%s %d", title, counter++);
            gtk_label_set_text(GTK_LABEL(tab_label), new_title);
        }
    }
}

void on_btn_quit_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    if (confirm_quit(GTK_WIDGET(button)))
    {
        free_gui_data(ctx->creator_builder);
        gtk_widget_destroy(GTK_WIDGET(ctx->creator_window));
        g_object_unref(ctx->creator_builder);
        ctx->creator_builder = NULL;
    }
}

gboolean on_close_secondwindow(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    t_context *ctx = user_data;
    if (confirm_quit(widget))
    {
        free_gui_data(ctx->creator_builder);
        g_object_unref(ctx->creator_builder);
        ctx->creator_builder = NULL;
    
        return FALSE;
    }
    return TRUE; 
}

void on_btn_add_co_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
   
    GtkWidget *grid = create_co_properties();
    add_object_page(ctx->creator_builder, "Cone", &cone_count, grid);
}

void on_btn_add_cy_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    GtkWidget *grid = create_cy_properties();
    add_object_page(ctx->creator_builder, "Cylinder", &cylinder_count, grid);
}

void on_btn_add_pl_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;

    GtkWidget *grid = create_pl_properties();
    add_object_page(ctx->creator_builder, "Plane", &plane_count, grid);
}

void on_btn_add_sp_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;

    GtkWidget *grid = create_sp_properties();
    add_object_page(ctx->creator_builder, "Sphere", &sphere_count, grid);
}

void on_btn_add_pa_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;

    GtkWidget *grid = create_pa_properties();
    add_object_page(ctx->creator_builder, "Paraboloid", &paraboloid_count, grid);
}

void on_btn_add_to_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    GtkWidget *grid = create_to_properties();
    add_object_page(ctx->creator_builder, "Torus", &toroid_count, grid);
}

void on_btn_add_mo_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    GtkWidget *grid = create_mo_properties();
    add_object_page(ctx->creator_builder, "Moebius", &moebius_count, grid);
}

void on_btn_add_spot_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    GtkWidget *grid = create_spot_properties();
    add_object_page(ctx->creator_builder, "Spot", &spot_count, grid);
}

void on_btn_add_camera_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    GtkWidget *grid = create_camera_properties();
    add_object_page(ctx->creator_builder, "Camera", &camera_count, grid);
}

void on_btn_add_directional_clicked(GtkButton *button, gpointer user_data)
{
    if (directional_created)
        return;

    t_context *ctx = user_data;
    
    GtkWidget *grid = create_directional_properties();
    add_object_page(ctx->creator_builder, "Directional", NULL, grid);
    directional_created = true;
}

void on_btn_add_library_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    GtkWidget *page = create_composite_properties();
    add_object_page(ctx->creator_builder, "Instance", &instances_count, page);
}

void on_btn_delete_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    
    GtkNotebook *notebook = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(ctx->creator_builder), "notebook_scene_elements"));
   
    gint current_page = gtk_notebook_get_current_page(notebook);
    if (current_page == -1)
        return;

    GtkWidget *child = gtk_notebook_get_nth_page(notebook, current_page);
    GtkWidget *tab_label = gtk_notebook_get_tab_label(notebook, child);
    const gchar *tab_title = gtk_label_get_text(GTK_LABEL(tab_label));
  
    // Camera 1 and Ambient tabs cannot be deleted
    if (g_strcmp0(tab_title, "Camera 1") == 0 || g_strcmp0(tab_title, "Ambient") == 0)
    {
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "The tab \"%s\" cannot be deleted.", tab_title);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Confirm deletion
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Do you want to delete the tab \"%s\"?", tab_title);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (response == GTK_RESPONSE_YES)
    {
        char *space_pos = strchr(tab_title, ' ');
        if (space_pos)
            *space_pos = '\0';
        
        gchar *tab_name = g_strdup(tab_title);
        gtk_notebook_remove_page(notebook, current_page);

        if (g_strcmp0(tab_name, "Camera") == 0)
            camera_count--;

        else if (g_strcmp0(tab_name, "Spot") == 0)
            spot_count--;

        else if (g_strcmp0(tab_name, "Directional") == 0)
            directional_created = false;

        else if (g_strcmp0(tab_name, "Sphere") == 0)
            sphere_count--;

        else if (g_strcmp0(tab_name, "Cylinder") == 0)
            cylinder_count--;

        else if (g_strcmp0(tab_name, "Cone") == 0)
            cone_count--;

        else if (g_strcmp0(tab_name, "Plane") == 0)
            plane_count--;

        else if (g_strcmp0(tab_name, "Moebius") == 0)
            moebius_count--;

        else if (g_strcmp0(tab_name, "Torus") == 0)
            toroid_count--;

        else if (g_strcmp0(tab_name, "Paraboloid") == 0)
            paraboloid_count--;
            
        else if (g_strcmp0(tab_name, "Instance") == 0)
            instances_count--;
            
        fix_tab_titles(notebook, tab_name);
        g_free(tab_name);
    }
}

void on_btn_save_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    t_scene	*aux = init_scene();

    if (!aux)
        set_status_label(ctx->status_label, err_msg(MEMORY_E));
    else
    {
        int err = create_scene(ctx, aux);
        if (err)
            set_status_label(ctx->status_label, err_msg(err));
        else
        {
            gchar *filepath = ask_filename_dialog(GTK_WINDOW(ctx->creator_window));
            if (filepath)
            {
                if (create_file(ctx->scene, filepath) == 1)
                    set_status_label(ctx->status_label, "Error: Failed to save the image to file.");
                else
                    set_status_label(ctx->status_label, "Image saved successfully.");
                    
                g_free(filepath);
            }
        }
        free_scene(aux);
    }
}

void on_btn_render_clicked(GtkButton *button, gpointer user_data)
{
    t_context *ctx = user_data;
    t_scene	*aux = init_scene();
    
    if (!aux)
        set_status_label(ctx->status_label, err_msg(MEMORY_E));
    else
    {
       int err = create_scene(ctx, aux);
        if (err)
        {
            free_scene(aux);
            set_status_label(ctx->status_label, err_msg(err));
        }
        else
        {
            free_scene(ctx->scene);
            ctx->scene = aux;
            t_camera *cam = ctx->scene->camera;
	        while (cam)
	        {
		        cam->prec_rays = precalculated_rays(cam, ctx->scene ->height, ctx->scene ->width);
		        if (cam->prec_rays == NULL)
		        {
			        free_scene(aux);
                    set_status_label(ctx->status_label, err_msg(MEMORY_E));
		        }
		        cam = cam->next;
	        }
 
            set_status_label(ctx->status_label, "Data processed successfully");  
            render_scene(ctx);
            update_menu_camera(ctx);
        }
    }
}

void add_minimum_elements(GtkBuilder *builder)
{
    GtkWidget *grid;
    
     // Añadir página Ambient
    grid = create_ambient_properties();
    add_object_page(builder, "Ambient", NULL, grid);
    
    // Añadir página Camera 1
    grid = create_camera_properties();
    add_object_page(builder, "Camera", &camera_count, grid);
}
