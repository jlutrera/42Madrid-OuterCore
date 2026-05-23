/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_slice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:28:06 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/02 11:55:42 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// Function to remove a slice plane
static void on_remove_slice_clicked(GtkButton *button, gpointer user_data)
{ 
    t_slice_widgets *slice = g_object_get_data(G_OBJECT(button), "slice");
    t_common_widgets *widgets = g_object_get_data(G_OBJECT(button), "widgets");
    
    int *row = &widgets->row;
    (*row)--;
    
    // Lo quitamos de la lista
    widgets->list_slices = g_list_remove(widgets->list_slices, slice);

    // Destruimos el frame
    gtk_widget_destroy(slice->frame);

    // Liberamos memoria
    g_free(slice);
}

// Function to add a new slice plane
static void on_add_slice_plane_clicked(GtkButton *button, gpointer user_data)
{
    t_common_widgets *widgets = user_data;
    t_slice_widgets *slice = g_new0(t_slice_widgets, 1);
    int *row = &widgets->row;

    (*row)++;

    slice->frame = gtk_frame_new(NULL);
    gtk_widget_set_margin_top(slice->frame, 5);
    gtk_widget_set_margin_bottom(slice->frame, 5);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(slice->frame), hbox);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(hbox), grid, TRUE, TRUE, 0);

    // --- SLICE POSITION ---
    GtkWidget *label_position = gtk_label_new("Position:");
    gtk_widget_set_halign(label_position, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_position, 0, 0, 1, 1);
    slice->entry_px = gtk_entry_new();
    slice->entry_py = gtk_entry_new();
    slice->entry_pz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(slice->entry_px), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(slice->entry_py), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(slice->entry_pz), "z value");
    gtk_grid_attach(GTK_GRID(grid), slice->entry_px, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), slice->entry_py, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), slice->entry_pz, 3, 0, 1, 1);

    // --- SLICE NORMAL ---
    GtkWidget *label_normal = gtk_label_new("Normal:");
    gtk_widget_set_halign(label_normal, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_normal, 0, 1, 1, 1);
    slice->entry_nx = gtk_entry_new();
    slice->entry_ny = gtk_entry_new();
    slice->entry_nz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(slice->entry_nx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(slice->entry_ny), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(slice->entry_nz), "z value");
    gtk_grid_attach(GTK_GRID(grid), slice->entry_nx, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), slice->entry_ny, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), slice->entry_nz, 3, 1, 1, 1);
    
    // --- REMOVE BUTTON ---
    GtkWidget *btn_remove = gtk_button_new_with_label("Remove");
    gtk_box_pack_start(GTK_BOX(hbox), btn_remove, FALSE, FALSE, 5);
    g_object_set_data(G_OBJECT(btn_remove), "slice", slice);
    g_object_set_data(G_OBJECT(btn_remove), "widgets", widgets);
    g_signal_connect(btn_remove, "clicked", G_CALLBACK(on_remove_slice_clicked), NULL);

    gtk_box_pack_start(GTK_BOX(widgets->slice_container), slice->frame, FALSE, FALSE, 5);
    gtk_widget_show_all(widgets->slice_container);

     widgets->list_slices = g_list_append(widgets->list_slices, slice);
}

void create_slice(GtkWidget *grid, t_common_widgets *widgets)
{
    int *row = &widgets->row;
    
    GtkWidget *label_slices = gtk_label_new("Slice:");
    gtk_widget_set_halign(label_slices, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_slices, 0, *row, 1, 1);

    GtkWidget *btn_add_slice = gtk_button_new_with_label("Add slice plane");
    gtk_grid_attach(GTK_GRID(grid), btn_add_slice, 1, *row, 1, 1);
    (*row)++;
    
    widgets->slice_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_hexpand(widgets->slice_container, TRUE);
    gtk_widget_set_vexpand(widgets->slice_container, FALSE);
    gtk_grid_attach(GTK_GRID(grid), widgets->slice_container, 1, *row, 3, 1);
    g_signal_connect(btn_add_slice, "clicked", G_CALLBACK(on_add_slice_plane_clicked), widgets);
}
