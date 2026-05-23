/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks_compose.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:23:26 by jutrera           #+#    #+#             */
/*   Updated: 2025/08/30 11:38:42 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int planecomposite_count = 0;
int spherecomposite_count = 0;
int cylindercomposite_count = 0;
int conecomposite_count = 0;
bool saved = false;

static void add_compositeOject_page(GtkNotebook *notebook, const char *object_name, int *counter, GtkWidget *grid)
{
    GtkWidget *label;

    char label_text[64];
    sprintf(label_text, "%s %d", object_name, ++(*counter));
    label = gtk_label_new(label_text);
    int page_num = gtk_notebook_append_page(notebook, grid, label);
    
    gtk_widget_show_all(grid);
    gtk_notebook_set_current_page(notebook, page_num);
    saved = false;
}

static gboolean confirm_quitCompose(GtkWidget *parent)
{
    if (!saved)
    {
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(parent)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Compose is not saved. Do you really want to exit?");
    
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        if (response == GTK_RESPONSE_YES)
        {
            planecomposite_count = 0;
            spherecomposite_count = 0;
            cylindercomposite_count = 0;
            conecomposite_count = 0;
            return TRUE;
        }
        return FALSE;        
    }
    saved = false;
    return TRUE;
}

static char *select_folder_dialog(GtkWindow *parent)
{
    GtkWidget *dialog;
    gchar *foldername;

    // Crear diálogo de selección de carpeta
    dialog = gtk_file_chooser_dialog_new(
        "Select folder",
        parent,
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Select", GTK_RESPONSE_ACCEPT,
        NULL
    );

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "./libraries");

    // Mostrar diálogo y esperar respuesta
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        foldername = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_widget_destroy(dialog);
        return foldername;
    }

    gtk_widget_destroy(dialog);
    return NULL;
}

gboolean on_close_composeWindow(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    if (confirm_quitCompose(widget))
        return FALSE;

    return TRUE; 
}

void on_quitCompose(GtkButton *button, gpointer user_data)
{
    t_composite_widgets *ui = user_data;
    if (confirm_quitCompose(GTK_WIDGET(button)))
    {
        gtk_widget_destroy(GTK_WIDGET(ui->window));
        g_free(ui);
    }
}

void on_deleteCompose(GtkButton *button, gpointer user_data)
{
    t_composite_widgets *ui = user_data;
    
    GtkNotebook *notebook = GTK_NOTEBOOK(ui->notebook);
   
    gint current_page = gtk_notebook_get_current_page(notebook);
    if (current_page == -1)
        return;

    GtkWidget *child = gtk_notebook_get_nth_page(notebook, current_page);
    GtkWidget *tab_label = gtk_notebook_get_tab_label(notebook, child);
    const gchar *tab_title = gtk_label_get_text(GTK_LABEL(tab_label));
  
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

        if (g_strcmp0(tab_name, "Sphere") == 0)
            spherecomposite_count--;

        else if (g_strcmp0(tab_name, "Cylinder") == 0)
            cylindercomposite_count--;

        else if (g_strcmp0(tab_name, "Cone") == 0)
            conecomposite_count--;

        else if (g_strcmp0(tab_name, "Plane") == 0)
            planecomposite_count--;

        fix_tab_titles(notebook, tab_name);
        g_free(tab_name);
        saved = false;
    }
}

void on_saveCompose(GtkButton *button, gpointer user_data)
{
    t_composite_widgets *ui = user_data;
    
    const gchar *entry_name = gtk_entry_get_text(GTK_ENTRY(ui->entry_name));
    if (!entry_name || strlen(entry_name) == 0)
        return;
        
    char *folder = select_folder_dialog(GTK_WINDOW(ui->window));
    if (!folder)
        return;
    
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s.lib", folder, entry_name);
    g_free(folder);
        
    FILE *f = fopen(filepath, "w");
    if (!f)
        return;
    
    t_composite *new_comp = malloc(sizeof(t_composite));
    if (!new_comp) 
        return;

    new_comp->name = strdup(entry_name);
    new_comp->objects = NULL;
    new_comp->next = NULL;
    
    gint n_pages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(ui->notebook));
    for (gint i = 0; i < n_pages; i++)
    {
        GtkWidget *child = gtk_notebook_get_nth_page(GTK_NOTEBOOK(ui->notebook), i);
        GtkWidget *tab_label = gtk_notebook_get_tab_label(GTK_NOTEBOOK(ui->notebook), child);
        const gchar *title = gtk_label_get_text(GTK_LABEL(tab_label));

        if (g_str_has_prefix(title, "Plane"))
            save_planeCompose(child, new_comp);
            
        else if (g_str_has_prefix(title, "Cylinder"))
            save_cylinderCompose(child, new_comp);
            
        else if (g_str_has_prefix(title, "Cone"))
            save_coneCompose(child, new_comp);
            
        else if (g_str_has_prefix(title, "Sphere"))
            save_sphereCompose(child, new_comp);
    }

    cJSON *root = cJSON_CreateObject();
    cJSON *obj_array = cJSON_CreateArray();
    cJSON_AddItemToObject(root, new_comp->name, obj_array);

    add_composite_solids(obj_array, new_comp);
 
    char *json_str = cJSON_Print(root);
    fputs(json_str, f);
    fclose(f);
    cJSON_free(json_str);
    cJSON_Delete(root);
    free_composites(new_comp);
    saved = false;
    gtk_widget_destroy(GTK_WIDGET(ui->window));
}

void on_addCompose_plane(GtkButton *button, gpointer user_data)
{
    t_composite_widgets *ui = user_data;
    t_plane_widgets *widgets = malloc(sizeof(t_plane_widgets));
    if (!widgets) return;

    // Crear contenedor general
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Label para propiedades específicas
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Plane properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    // Crear grid para propiedades específicas
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    // --- POSITION ---
    GtkWidget *label_position = gtk_label_new("Position:");
    gtk_widget_set_halign(label_position, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_position, 0, 0, 1, 1);
    widgets->entry_cx = gtk_entry_new();
    widgets->entry_cy = gtk_entry_new();
    widgets->entry_cz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cx, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cy, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cz, 3, 0, 1, 1);

    // --- NORMAL ---
    GtkWidget *label_normal = gtk_label_new("Normal:");
    gtk_widget_set_halign(label_normal, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_normal, 0, 1, 1, 1);
    widgets->entry_dx = gtk_entry_new();
    widgets->entry_dy = gtk_entry_new();
    widgets->entry_dz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dx, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dy, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dz, 3, 1, 1, 1);
    
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);
    g_object_set_data_full(G_OBJECT(vbox), "plane_widgets", widgets, free);
    add_compositeOject_page(GTK_NOTEBOOK(ui->notebook), "Plane", &planecomposite_count, vbox);
}

void on_addCompose_cone(GtkButton *button, gpointer user_data)
{
    t_composite_widgets *ui = user_data;
    // Creamos la estructura para guardar punteros
    t_cone_widgets *widgets = malloc(sizeof(t_cone_widgets));
    if (!widgets) return;
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Label propiedades específicas
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Cone properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    // --- POSITION ---
    GtkWidget *label_position = gtk_label_new("Position:");
    gtk_widget_set_halign(label_position, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_position, 0, 0, 1, 1);
    widgets->entry_cx = gtk_entry_new();
    widgets->entry_cy = gtk_entry_new();
    widgets->entry_cz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cx, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cy, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cz, 3, 0, 1, 1);

    // --- DIRECTION ---
    GtkWidget *label_direction = gtk_label_new("Direction:");
    gtk_widget_set_halign(label_direction, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_direction, 0, 1, 1, 1);
    widgets->entry_dx = gtk_entry_new();
    widgets->entry_dy = gtk_entry_new();
    widgets->entry_dz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dx, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dy, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dz, 3, 1, 1, 1);

    // --- RADIUS ---
    GtkWidget *label_radius = gtk_label_new("Radius:");
    gtk_widget_set_halign(label_radius, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_radius, 0, 2, 1, 1);
    widgets->entry_radius = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_radius), "radius value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_radius, 1, 2, 3, 1);

    // --- HEIGHT ---
    GtkWidget *label_height = gtk_label_new("Height:");
    gtk_widget_set_halign(label_height, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_height, 0, 3, 1, 1);
    widgets->entry_height = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_height), "height value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_height, 1, 3, 3, 1);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);
    g_object_set_data_full(G_OBJECT(vbox), "cone_widgets", widgets, free);
    add_compositeOject_page(GTK_NOTEBOOK(ui->notebook), "Cone", &conecomposite_count, vbox);
}

void on_addCompose_sphere(GtkButton *button, gpointer user_data)
{
    t_composite_widgets *ui = user_data;
    t_sphere_widgets *widgets = malloc(sizeof(t_sphere_widgets));
    if (!widgets) return;

    // Crear contenedor general
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Label para propiedades específicas
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Sphere properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    // Grid propiedades específicas
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    // --- CENTER-
    GtkWidget *label_center = gtk_label_new("Center:");
    gtk_widget_set_halign(label_center, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_center, 0, 0, 1, 1);
    widgets->entry_cx = gtk_entry_new();
    widgets->entry_cy = gtk_entry_new();
    widgets->entry_cz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cx, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cy, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cz, 3, 0, 1, 1);

    // --- RADIUS ---
    GtkWidget *label_radius = gtk_label_new("Radius:");
    gtk_widget_set_halign(label_radius, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_radius, 0, 1, 1, 1);
    widgets->entry_radius = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_radius), "radius value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_radius, 1, 1, 3, 1);

    // Añadir grid de propiedades específicas al vbox
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);
    g_object_set_data_full(G_OBJECT(vbox), "sphere_widgets", widgets, free);
    add_compositeOject_page(GTK_NOTEBOOK(ui->notebook), "Sphere", &spherecomposite_count, vbox);
}

void on_addCompose_cylinder(GtkButton *button, gpointer user_data)
{
    t_composite_widgets *ui = user_data;
    t_cylinder_widgets *widgets = malloc(sizeof(t_cylinder_widgets));
    if (!widgets) return;
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    
    // Label propiedades específicas
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Cylinder properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    // --- POSITION ---
    GtkWidget *label_position = gtk_label_new("Position:");
    gtk_widget_set_halign(label_position, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_position, 0, 0, 1, 1);
    widgets->entry_cx = gtk_entry_new();
    widgets->entry_cy = gtk_entry_new();
    widgets->entry_cz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cx, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cy, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cz, 3, 0, 1, 1);

    // --- DIRECTION ---
    GtkWidget *label_direction = gtk_label_new("Direction:");
    gtk_widget_set_halign(label_direction, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_direction, 0, 1, 1, 1);
    widgets->entry_dx = gtk_entry_new();
    widgets->entry_dy = gtk_entry_new();
    widgets->entry_dz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dx, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dy, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dz, 3, 1, 1, 1);

    // --- RADIUS ---
    GtkWidget *label_radius = gtk_label_new("Radius:");
    gtk_widget_set_halign(label_radius, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_radius, 0, 2, 1, 1);
    widgets->entry_radius = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_radius), "radius value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_radius, 1, 2, 3, 1);

    // --- HEIGHT ---
    GtkWidget *label_height = gtk_label_new("Height:");
    gtk_widget_set_halign(label_height, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_height, 0, 3, 1, 1);
    widgets->entry_height = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_height), "height value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_height, 1, 3, 3, 1);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);
    g_object_set_data_full(G_OBJECT(vbox), "cylinder_widgets", widgets, free);
    add_compositeOject_page(GTK_NOTEBOOK(ui->notebook), "Cylinder", &cylindercomposite_count, vbox);    
}
