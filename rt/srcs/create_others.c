/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:35:11 by jutrera           #+#    #+#             */
/*   Updated: 2025/08/30 11:19:05 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void create_transformations(GtkWidget *grid , t_common_widgets *widgets)
{
    int *row = &widgets->row;
    // --- TRANSLATE ---
    GtkWidget *label_translate = gtk_label_new("Translate:");
    gtk_widget_set_halign(label_translate, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_translate, 0, *row, 1, 1);
    widgets->entry_tx = gtk_entry_new();
    widgets->entry_ty = gtk_entry_new();
    widgets->entry_tz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_tx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_ty), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_tz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_tx, 1, *row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_ty, 2, *row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_tz, 3, *row, 1, 1);

    (*row)++;

    // --- ROTATE ---
    GtkWidget *label_rotate = gtk_label_new("Rotate (deg):");
    gtk_widget_set_halign(label_rotate, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_rotate, 0, *row, 1, 1);
    widgets->entry_rx = gtk_entry_new();
    widgets->entry_ry = gtk_entry_new();
    widgets->entry_rz = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_rx), "x value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_ry), "y value");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_rz), "z value");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_rx, 1, *row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_ry, 2, *row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_rz, 3, *row, 1, 1);

    (*row)++;
}

void create_color(GtkWidget *grid , t_common_widgets *widgets)
{
    int *row = &widgets->row;
    
    GtkWidget *label_color = gtk_label_new("Color:");
    gtk_widget_set_halign(label_color, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_color, 0, *row, 1, 1);
    widgets->btn_color = gtk_color_button_new();

    GdkRGBA white = {1.0, 1.0, 1.0, 1.0};
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(widgets->btn_color), &white);
    gtk_grid_attach(GTK_GRID(grid), widgets->btn_color, 1, *row, 1, 1);

    (*row)++;
}

void create_reflect_refract(GtkWidget *grid , t_common_widgets *widgets)
{
    int *row = &widgets->row;
    
    // --- REFLECTIVITY ---
    GtkWidget *label_reflect = gtk_label_new("Reflectivity:");
    gtk_widget_set_halign(label_reflect, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_reflect, 0, *row, 1, 1);
    widgets->spin_reflect = gtk_spin_button_new_with_range(0, 1, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widgets->spin_reflect), 0);
    gtk_grid_attach(GTK_GRID(grid), widgets->spin_reflect, 1, *row, 1, 1);

    // --- SHINE ---
    GtkWidget *label_shine = gtk_label_new("Shine:");
    gtk_widget_set_halign(label_shine, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_shine, 2, *row, 1, 1);
    
    widgets->spin_shine = gtk_spin_button_new_with_range(10, 1000, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widgets->spin_shine), 10);
    gtk_grid_attach(GTK_GRID(grid), widgets->spin_shine, 3, *row, 1, 1);
    
    (*row)++;

    // --- TRANSPARENCY ---
    GtkWidget *label_transparency = gtk_label_new("Transparency:");
    gtk_widget_set_halign(label_transparency, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_transparency, 0, *row, 1, 1);
    widgets->spin_transparency = gtk_spin_button_new_with_range(0, 1, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widgets->spin_transparency), 0);
    gtk_grid_attach(GTK_GRID(grid), widgets->spin_transparency, 1, *row, 1, 1);

    // --- REFRACTION ---
    GtkWidget *label_refraction = gtk_label_new("Refraction:");
    gtk_widget_set_halign(label_refraction, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_refraction, 2, *row, 1, 1);
    
    widgets->spin_ior = gtk_spin_button_new_with_range(1, 5, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widgets->spin_ior), 1);
    gtk_grid_attach(GTK_GRID(grid), widgets->spin_ior, 3, *row, 1, 1);

    (*row)++;
}
