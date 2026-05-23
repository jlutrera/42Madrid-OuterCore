/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:36:23 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/28 12:57:01 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void on_select_library_file_clicked(GtkButton *button, gpointer user_data)
{
    t_instance_widgets *widgets = user_data;
    
    GtkWidget *dialog;
    GtkFileFilter *filter;

    dialog = gtk_file_chooser_dialog_new("Select library file",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Select", GTK_RESPONSE_ACCEPT,
                                         NULL);

    filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter, "*.lib");
    gtk_file_filter_set_name(filter, "RT Libraries");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "./libraries");

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_name), filename);

        // try to load file content
        gchar *contents = NULL;
        gsize length;
        GError *error = NULL;

        if (g_file_get_contents(filename, &contents, &length, &error))
        {
            gtk_text_buffer_set_text(widgets->preview_buffer, contents, length);
            g_free(contents);
        }
        else
        {
            // if error reading, clear buffer and show error
            gtk_text_buffer_set_text(widgets->preview_buffer,
                                     error->message, -1);
            g_error_free(error);
        }
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

GtkWidget *create_common_properties_grid(int selectprop)
{
    // selectprop = 0 => se aplican todas las propiedaes: co, cy, sp, pl
    // selectprop = 1 => se aplican slices pero NO texturas: mo, to, pa
    // selectprop = 2 => NO se aplican ni texturas ni slices: composites
    
    t_common_widgets *widgets = malloc(sizeof(t_common_widgets));
    if (!widgets) return NULL;

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

    widgets->row = 0;
    create_transformations(grid, widgets);
    create_color(grid, widgets);
    create_reflect_refract(grid, widgets);
    
    if (selectprop == 0)
        create_texture(grid, widgets);
    else
        widgets->combo_texture = NULL;
        
    if (selectprop == 0 || selectprop == 1)
        create_slice(grid, widgets);
    
    widgets->list_slices = NULL;
    widgets->file_texture = NULL;
    g_object_set_data_full(G_OBJECT(grid), "common_widgets", widgets, g_free);
      
    return grid;
}

GtkWidget *create_spot_properties(void)
{
    t_spot_widgets *widgets = malloc(sizeof(t_spot_widgets));
    if (!widgets) return NULL;

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);
    gtk_widget_set_margin_top(grid, 12);
    gtk_widget_set_margin_bottom(grid, 12);
    gtk_widget_set_margin_start(grid, 12);
    gtk_widget_set_margin_end(grid, 12);

    // --- POSITION ---
    GtkWidget *lbl_pos = gtk_label_new("Position:");
    widgets->entry_cx = gtk_entry_new();
    widgets->entry_cy = gtk_entry_new();
    widgets->entry_cz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cz), "z value");
    gtk_grid_attach(GTK_GRID(grid), lbl_pos, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cx, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cy, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cz, 3, 0, 1, 1);

    // --- BRIGHT ---
    GtkWidget *lbl_intensity = gtk_label_new("Bright:");
    GtkAdjustment *adj = gtk_adjustment_new(0.5, 0.0, 1.0, 0.01, 0.1, 0.0);
    widgets->spin_bright = gtk_spin_button_new(adj, 0.01, 2);
    gtk_grid_attach(GTK_GRID(grid), lbl_intensity, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->spin_bright, 1, 1, 1, 1);

    // --- COLOR ---
    GtkWidget *lbl_color = gtk_label_new("Color:");
    widgets->btn_color = gtk_color_button_new();
    GdkRGBA white = {1.0, 1.0, 1.0, 1.0};
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widgets->btn_color), &white);
    gtk_grid_attach(GTK_GRID(grid), lbl_color, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->btn_color, 1, 2, 1, 1);

    g_object_set_data_full(G_OBJECT(grid), "spot_widgets", widgets, g_free);
     
    return grid;
}

GtkWidget *create_directional_properties(void)
{
    t_directional_widgets *widgets = malloc(sizeof(t_directional_widgets));
    if (!widgets) return NULL;

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);
    gtk_widget_set_margin_top(grid, 12);
    gtk_widget_set_margin_bottom(grid, 12);
    gtk_widget_set_margin_start(grid, 12);
    gtk_widget_set_margin_end(grid, 12);

    // --- DIRECTION ---
    GtkWidget *lbl_dir = gtk_label_new("Direction:");
    widgets->entry_dx = gtk_entry_new();
    widgets->entry_dy = gtk_entry_new();
    widgets->entry_dz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dz), "z value");
    gtk_grid_attach(GTK_GRID(grid), lbl_dir, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dx, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dy, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dz, 3, 0, 1, 1);
    
    // --- BRIGHT ---
    GtkWidget *lbl_intensity = gtk_label_new("Bright:");
    GtkAdjustment *adj = gtk_adjustment_new(0.5, 0.0, 1.0, 0.01, 0.1, 0.0);
    widgets->spin_bright = gtk_spin_button_new(adj, 0.01, 2);
    gtk_grid_attach(GTK_GRID(grid), lbl_intensity, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->spin_bright, 1, 1, 1, 1);

    // --- COLOR ---
    GtkWidget *lbl_color = gtk_label_new("Color:");
    widgets->btn_color = gtk_color_button_new();
    GdkRGBA white = {1.0, 1.0, 1.0, 1.0};
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widgets->btn_color), &white);
    gtk_grid_attach(GTK_GRID(grid), lbl_color, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->btn_color, 1, 2, 1, 1);

    g_object_set_data_full(G_OBJECT(grid), "directional_widgets", widgets, g_free);
    
    return grid;
}

GtkWidget *create_ambient_properties(void)
{
    t_ambient_widgets *widgets = malloc(sizeof(t_ambient_widgets));
    if (!widgets) return NULL;

    // Grid para organizar los campos
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);
    gtk_widget_set_margin_top(grid, 12);
    gtk_widget_set_margin_bottom(grid, 12);
    gtk_widget_set_margin_start(grid, 12);
    gtk_widget_set_margin_end(grid, 12);

    // --- BRIGHT ---
    GtkWidget *lbl_intensity = gtk_label_new("Bright:");
    GtkAdjustment *adj = gtk_adjustment_new(0.25, 0.25, 1.0, 0.01, 0.1, 0.0);
    widgets->spin_bright = gtk_spin_button_new(adj, 0.01, 2);
    gtk_grid_attach(GTK_GRID(grid), lbl_intensity, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->spin_bright, 1, 0, 1, 1);

    // --- COLOR ---
    GtkWidget *lbl_color = gtk_label_new("Color:");
    widgets->btn_color = gtk_color_button_new();
    GdkRGBA white = {1.0, 1.0, 1.0, 1.0};
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widgets->btn_color), &white);
    gtk_grid_attach(GTK_GRID(grid), lbl_color, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->btn_color, 1, 1, 1, 1);

    // Guardar el puntero a los widgets en el contenedor principal (page)
    g_object_set_data_full(G_OBJECT(grid), "ambient_widgets", widgets, g_free);
    
    return grid;
}

GtkWidget *create_camera_properties(void)
{
    t_camera_widgets *widgets = malloc(sizeof(t_camera_widgets));
    if (!widgets) return NULL;
    
    // Grid para organizar los campos
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    // --- POSITION ---
    GtkWidget *lbl_pos = gtk_label_new("Position:");
    widgets->entry_cx = gtk_entry_new();
    widgets->entry_cy = gtk_entry_new();
    widgets->entry_cz = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_cz), "z value");
    gtk_grid_attach(GTK_GRID(grid), lbl_pos, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cx, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cy, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_cz, 3, 0, 1, 1);

    // --- DIRECTION ---
    GtkWidget *lbl_dir = gtk_label_new("Direction:");
    widgets->entry_dx =  gtk_entry_new();
    widgets->entry_dy = gtk_entry_new();
    widgets->entry_dz = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dy), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_dz), "z value");
    gtk_grid_attach(GTK_GRID(grid), lbl_dir, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dx, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dy, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_dz, 3, 1, 1, 1);

    // --- FOV ---
    GtkWidget *lbl_fov = gtk_label_new("FOV:");
    widgets->entry_fov = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_fov), "80");
    gtk_grid_attach(GTK_GRID(grid), lbl_fov, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_fov, 1, 2, 1, 1);

    // Guardar el puntero a los widgets en el contenedor principal (page)
    g_object_set_data_full(G_OBJECT(grid), "camera_widgets", widgets, g_free);
   
    return grid;
}

GtkWidget *create_composite_properties(void) 
{
    t_instance_widgets *widgets = malloc(sizeof(t_instance_widgets));
    if (!widgets) return NULL;

    // --- LEFT PANEL: properties ---
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Label: Instance properties
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Instance properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    // Grid: specific properties
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    GtkWidget *label_use = gtk_label_new("Use:");
    gtk_widget_set_halign(label_use, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_use, 0, 0, 1, 1);

    widgets->entry_name = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_name, 1, 0, 1, 1);
    gtk_widget_set_sensitive(widgets->entry_name, FALSE);

    GtkWidget *btn_library_choose = gtk_button_new_with_label("Browse...");
    gtk_grid_attach(GTK_GRID(grid), btn_library_choose, 2, 0, 1, 1);
    g_signal_connect(btn_library_choose, "clicked", G_CALLBACK(on_select_library_file_clicked), widgets);

    GtkWidget *label_scale = gtk_label_new("Scale:");
    gtk_widget_set_halign(label_scale, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_scale, 0, 1, 1, 1);
    widgets->entry_scale = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_scale), "scale value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_scale, 1, 1, 3, 1);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Common properties
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 10);

    widgets->grid_common = create_common_properties_grid(2);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // --- RIGHT PANEL: preview ---
    widgets->preview_buffer = gtk_text_buffer_new(NULL);
    widgets->preview_view = gtk_text_view_new_with_buffer(widgets->preview_buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets->preview_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(widgets->preview_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(widgets->preview_view), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_justification(GTK_TEXT_VIEW(widgets->preview_view), GTK_JUSTIFY_LEFT);
    gtk_widget_set_halign(widgets->preview_view, GTK_ALIGN_FILL);
    gtk_widget_set_valign(widgets->preview_view, GTK_ALIGN_FILL);
    
    widgets->preview_scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(widgets->preview_scrolled), widgets->preview_view);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widgets->preview_scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(widgets->preview_scrolled, 300, -1);
    gtk_widget_set_hexpand(widgets->preview_scrolled, TRUE);
    gtk_widget_set_vexpand(widgets->preview_scrolled, TRUE);
    gtk_widget_set_halign(widgets->preview_scrolled, GTK_ALIGN_FILL);
    gtk_widget_set_valign(widgets->preview_scrolled, GTK_ALIGN_FILL);
    
    // Optional: put inside a frame with border
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame), widgets->preview_scrolled);
    gtk_container_set_border_width(GTK_CONTAINER(frame), 12); // padding inside

    // --- PANED ---
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_paned_add1(GTK_PANED(paned), vbox);       // left panel
    gtk_paned_add2(GTK_PANED(paned), frame);      // right panel

    // Save widgets structure
    g_object_set_data_full(G_OBJECT(paned), "instance_widgets", widgets, g_free);

    return paned;
}
