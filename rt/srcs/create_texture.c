/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:31:32 by jutrera           #+#    #+#             */
/*   Updated: 2025/08/30 11:23:48 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void on_texture_type_changed(GtkComboBox *combo, gpointer user_data)
{
    t_common_widgets *widgets = user_data;
    GtkWidget *entry_img = widgets->entry_texture_image;
    GtkWidget *btn_imgtexture = widgets->btn_texture_image;
    int active = gtk_combo_box_get_active(combo);
    if (active == 2) // "Image"
    {
        gtk_widget_set_sensitive(entry_img, TRUE);
        gtk_widget_set_sensitive(btn_imgtexture, TRUE);
    }
    else
    {
        gtk_widget_set_sensitive(entry_img, FALSE);
        gtk_widget_set_sensitive(btn_imgtexture, FALSE);
    }
}

static void on_select_texture_file_clicked(GtkButton *button, gpointer user_data)
{
    t_common_widgets *widgets = user_data;

    GtkWidget *dialog = gtk_file_chooser_dialog_new("Select Texture Image",
                                                    NULL,
                                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Cancel", GTK_RESPONSE_CANCEL,
                                                    "_Open", GTK_RESPONSE_ACCEPT,
                                                    NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_texture_image), filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void create_texture(GtkWidget *grid , t_common_widgets *widgets)
{
    int *row = &widgets->row;
    GtkWidget *label_texture_type = gtk_label_new("Texture:");
    gtk_widget_set_halign(label_texture_type, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_texture_type, 0, *row, 1, 1);

    widgets->combo_texture = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets->combo_texture), "None");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets->combo_texture), "Checkerboard");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(widgets->combo_texture), "Image");
    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets->combo_texture), 0);
    gtk_grid_attach(GTK_GRID(grid), widgets->combo_texture, 1, *row, 1, 1);

    GtkWidget *label_texture_image = gtk_label_new("Texture file:");
    gtk_widget_set_halign(label_texture_image, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), label_texture_image, 2, *row, 1, 1);

    widgets->entry_texture_image = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid),  widgets->entry_texture_image, 3, *row, 1, 1);
    gtk_widget_set_sensitive(widgets->entry_texture_image, FALSE);

    widgets->btn_texture_image = gtk_button_new_with_label("Browse...");
    gtk_grid_attach(GTK_GRID(grid), widgets->btn_texture_image, 4, *row, 1, 1);
    g_signal_connect(widgets->btn_texture_image, "clicked", G_CALLBACK(on_select_texture_file_clicked), widgets);

    (*row)++;
    
    g_signal_connect(widgets->combo_texture, "changed", G_CALLBACK(on_texture_type_changed), widgets);
    gtk_widget_set_sensitive(widgets->btn_texture_image, FALSE);
}
