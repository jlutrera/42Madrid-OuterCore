/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_solids.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:42:51 by jutrera           #+#    #+#             */
/*   Updated: 2025/08/31 19:40:29 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GtkWidget *create_mo_properties(void)
{
    t_moebius_widgets *widgets = malloc(sizeof(t_moebius_widgets));
    if (!widgets) return NULL;

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Label propiedades específicas
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Moebius strip properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

    // --- CENTER ---
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

    // --- WIDTH
    GtkWidget *label_width = gtk_label_new("Width:");
    gtk_widget_set_halign(label_width, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_width, 0, 2, 1, 1);
    widgets->entry_width = gtk_spin_button_new_with_range(0, 1, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widgets->entry_width), 0);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_width, 1, 2, 1, 1);

    // --- RADIUS
    GtkWidget *label_radius = gtk_label_new("Radius:");
    gtk_widget_set_halign(label_radius, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_radius, 0, 3, 1, 1);
    widgets->entry_radius = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_radius), "radius value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_radius, 1, 3, 1, 1);
    
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Label propiedades comunes
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 5);

    widgets->grid_common = create_common_properties_grid(1);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // Guardamos la estructura en los datos del vbox
    g_object_set_data_full(G_OBJECT(vbox), "moebius_widgets", widgets, g_free);
    
    return vbox;
}

GtkWidget *create_to_properties(void)
{
    t_torus_widgets *widgets = malloc(sizeof(t_torus_widgets));
    if (!widgets) return NULL;

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Label propiedades específicas
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Torus properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

    // --- CENTER ---
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

    // --- INNER RADIUS ---
    GtkWidget *label_rminor = gtk_label_new("Minor:");
    gtk_widget_set_halign(label_rminor, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_rminor, 0, 2, 1, 1);
    widgets->entry_r_min = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_r_min), "inner radius value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_r_min, 1, 2, 1, 1);

    // --- OUTER RADIUS ---
    GtkWidget *label_rmajor = gtk_label_new("Major:");
    gtk_widget_set_halign(label_rmajor, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_rmajor, 0, 3, 1, 1);
    widgets->entry_r_max = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_r_max), "outer radius value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_r_max, 1, 3, 1, 1);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Label propiedades comunes
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 5);

    widgets->grid_common = create_common_properties_grid(1);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // Guardamos la estructura en los datos del vbox
    g_object_set_data_full(G_OBJECT(vbox), "torus_widgets", widgets, g_free);
    
    return vbox;
}

GtkWidget *create_pa_properties(void)
{
    t_paraboloid_widgets *widgets = malloc(sizeof(t_paraboloid_widgets));
    if (!widgets) return NULL;
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Label propiedades específicas
    GtkWidget *label_specific = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_specific), "<b>Paraboloid properties</b>");
    gtk_widget_set_halign(label_specific, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_specific, FALSE, FALSE, 5);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

    // --- CENTER ---
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

    // --- FACTOR K ---
    GtkWidget *label_k = gtk_label_new("k:");
    gtk_widget_set_halign(label_k, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_k, 0, 2, 1, 1);
    widgets->entry_k = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_k), "factor k value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_k, 1, 2, 1, 1);

    // --- HEIGHT ---
    GtkWidget *label_height = gtk_label_new("Height:");
    gtk_widget_set_halign(label_height, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_height, 0, 3, 1, 1);
    widgets->entry_height = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_height), "height value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_height, 1, 3, 1, 1);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Label propiedades comunes
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 5);

    widgets->grid_common = create_common_properties_grid(1);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // Guardamos la estructura en los datos del vbox
    g_object_set_data_full(G_OBJECT(vbox), "paraboloid_widgets", widgets, g_free);
    
    return vbox;
}

GtkWidget *create_cy_properties(void)
{
    // Creamos la estructura para guardar punteros
    t_cylinder_widgets *widgets = malloc(sizeof(t_cylinder_widgets));
    if (!widgets) return NULL;
    
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
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

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
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_radius, 1, 2, 1, 1);

    // --- HEIGHT ---
    GtkWidget *label_height = gtk_label_new("Height:");
    gtk_widget_set_halign(label_height, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_height, 0, 3, 1, 1);
    widgets->entry_height = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_height), "height value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_height, 1, 3, 1, 1);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Label propiedades comunes
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 5);

    widgets->grid_common = create_common_properties_grid(0);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // Guardamos la estructura en los datos del vbox
    g_object_set_data_full(G_OBJECT(vbox), "cylinder_widgets", widgets, g_free);
    
    return vbox;
}

GtkWidget *create_co_properties(void)
{
    // Creamos la estructura para guardar punteros
    t_cone_widgets *widgets = malloc(sizeof(t_cone_widgets));
    if (!widgets) return NULL;
    
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
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

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
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_radius, 1, 2, 1, 1);

    // --- HEIGHT ---
    GtkWidget *label_height = gtk_label_new("Height:");
    gtk_widget_set_halign(label_height, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_height, 0, 3, 1, 1);
    widgets->entry_height = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_height), "height value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_height, 1, 3, 1, 1);

    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Label propiedades comunes
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 5);

    widgets->grid_common = create_common_properties_grid(0);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // Guardamos la estructura en los datos del vbox
    g_object_set_data_full(G_OBJECT(vbox), "cone_widgets", widgets, g_free);
    
    return vbox;
}

GtkWidget *create_sp_properties(void)
{
    // Creamos la estructura para guardar punteros
    t_sphere_widgets *widgets = malloc(sizeof(t_sphere_widgets));
    if (!widgets) return NULL;

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
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

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
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_radius, 1, 1, 1, 1);

    // Añadir grid de propiedades específicas al vbox
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Label para propiedades comunes
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 5);

    // Grid propiedades comunes
    widgets->grid_common = create_common_properties_grid(0);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // Guardamos la estructura en los datos del vbox
    g_object_set_data_full(G_OBJECT(vbox), "sphere_widgets", widgets, g_free);
    
    return vbox;
}

GtkWidget *create_pl_properties(void)
{
    t_plane_widgets *widgets = malloc(sizeof(t_plane_widgets));
    if (!widgets) return NULL;

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
    gtk_widget_set_halign(grid, GTK_ALIGN_START);

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

    // Añadir grid de propiedades específicas al vbox
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 0);

    // Label para propiedades comunes
    GtkWidget *label_common = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_common), "<b>Common / Optional properties</b>");
    gtk_widget_set_halign(label_common, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label_common, FALSE, FALSE, 5);

    // Grid propiedades comunes
    widgets->grid_common = create_common_properties_grid(0);
    gtk_box_pack_start(GTK_BOX(vbox), widgets->grid_common, FALSE, FALSE, 0);

    // Guardamos la estructura en los datos del vbox
    g_object_set_data_full(G_OBJECT(vbox), "plane_widgets", widgets, g_free);
    
    return vbox;
}
