/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gizmo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:17:10 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/28 13:02:47 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void draw_cube(cairo_t *cr, double cx, double cy, t_localbase base, double size)
{
    typedef struct { double x, y; } t_point;
    t_point verts[8];

    // Calcula los 8 vértices del cubo
    int i = 0;
    for (int dx = -1; dx <= 1; dx += 2)
    for (int dy = -1; dy <= 1; dy += 2)
    for (int dz = -1; dz <= 1; dz += 2)
    {
        double x = cx + size * (dx * base.u.x + dy * base.v.x + dz * base.w.x);
        double y = cy - size * (dx * base.u.y + dy * base.v.y + dz * base.w.y); // Y invertida
        verts[i++] = (t_point){x, y};
    }

    // Define las caras visibles (índices de vértices)
    int faces[3][4] = {
        {0, 1, 3, 2}, // Cara XY → Z
        {0, 1, 5, 4}, // Cara XZ → Y
        {0, 2, 6, 4}  // Cara YZ → X
    };

    // Colores por eje
    double colors[3][3] = {
        {0.0, 0.0, 1.0}, // Azul para Z
        {0.0, 1.0, 0.0}, // Verde para Y
        {1.0, 0.0, 0.0}  // Rojo para X
    };

    // Dibuja las caras coloreadas
    for (int f = 0; f < 3; f++) {
        cairo_set_source_rgb(cr, colors[f][0], colors[f][1], colors[f][2]);
        cairo_move_to(cr, verts[faces[f][0]].x, verts[faces[f][0]].y);
        for (int j = 1; j < 4; j++)
            cairo_line_to(cr, verts[faces[f][j]].x, verts[faces[f][j]].y);
        cairo_close_path(cr);
        cairo_fill(cr);
    }

    // Dibuja todas las aristas
    int edges[12][2] = {
        {0,1},{1,3},{3,2},{2,0}, // base
        {4,5},{5,7},{7,6},{6,4}, // top
        {0,4},{1,5},{2,6},{3,7}  // verticales
    };

    cairo_set_line_width(cr, 1.0);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // Blanco
    for (int e = 0; e < 12; e++) {
        cairo_move_to(cr, verts[edges[e][0]].x, verts[edges[e][0]].y);
        cairo_line_to(cr, verts[edges[e][1]].x, verts[edges[e][1]].y);
    }
    cairo_stroke(cr);

    // Dibuja las aristas frontales más gruesas
    int bold_edges[3][2] = {
        {0,1}, {0,2}, {0,4}
    };

    cairo_set_line_width(cr, 3.0);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // Blanco
    for (int b = 0; b < 3; b++) {
        cairo_move_to(cr, verts[bold_edges[b][0]].x, verts[bold_edges[b][0]].y);
        cairo_line_to(cr, verts[bold_edges[b][1]].x, verts[bold_edges[b][1]].y);
    }
    cairo_stroke(cr);
}

static void draw_axis(cairo_t *cr, double cx, double cy, t_vec axis, double axis_length,
               double r, double g, double b, const char *label)
{
    // Punto final del eje
    double ex = cx + axis.x * axis_length;
    double ey = cy - axis.y * axis_length; // Y invertida por Cairo

    // Dibuja línea del eje
    cairo_set_source_rgb(cr, r, g, b);
    cairo_move_to(cr, cx, cy);
    cairo_line_to(cr, ex, ey);
    cairo_set_line_width(cr, 2.0);
    cairo_stroke(cr);

    // Dibuja punta de flecha como triángulo orientado
    double arrow_size = 9.0;
    double angle = atan2(-axis.y, axis.x); // Y invertida

    double tip_x = ex;
    double tip_y = ey;

    double base_x = tip_x - arrow_size * cos(angle);
    double base_y = tip_y - arrow_size * sin(angle);

    double left_x = base_x + arrow_size * cos(angle + M_PI / 2);
    double left_y = base_y + arrow_size * sin(angle + M_PI / 2);

    double right_x = base_x + arrow_size * cos(angle - M_PI / 2);
    double right_y = base_y + arrow_size * sin(angle - M_PI / 2);

    cairo_move_to(cr, tip_x, tip_y);
    cairo_line_to(cr, left_x, left_y);
    cairo_line_to(cr, right_x, right_y);
    cairo_close_path(cr);
    cairo_fill(cr);

    // Dibuja etiqueta si existe
    if (label && label[0] != '\0') {
        double label_dist = axis_length + 12.0;
        double lx = cx + axis.x * label_dist;
        double ly = cy - axis.y * label_dist;

        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // Blanco
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12.0);
        cairo_move_to(cr, lx, ly);
        cairo_show_text(cr, label);
    }
}

static void draw_gizmo(cairo_t *cr, GtkWidget *widget, t_scene *scene)
{
    t_camera *cam = get_active_camera(scene);
    if (!cam) return;

    // Obtiene el tamaño del widget donde se dibuja
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    int width = allocation.width;
    int height = allocation.height;

    const int gizmo_size = MIN(width, height) - 20; // Ajuste dinámico
    const int margin = 10;
    const double axis_length = gizmo_size * 0.35;

    double cx = width / 2.0;
    double cy = height / 2.0;

    // Fondo gris
    cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    // Dibuja el cubo centrado en (cx, cy)
    draw_cube(cr, cx, cy, cam->localbase, gizmo_size * 0.06);

    // Dibuja los ejes con etiquetas
    draw_axis(cr, cx, cy, vec_unit(cam->localbase.u), axis_length, 1.0, 0.0, 0.0, "X");
    draw_axis(cr, cx, cy, vec_unit(cam->localbase.v), axis_length, 0.0, 1.0, 0.0, "Y");
    draw_axis(cr, cx, cy, vec_unit(cam->localbase.w), axis_length, 0.0, 0.0, 1.0, "Z");
}

gboolean on_gizmo_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    t_context *ctx = data;
    
    if (ctx->scene->camera)
        draw_gizmo(cr, widget, ctx->scene);
    return FALSE;
}

void on_gizmo_window_destroy(GtkWidget *widget, gpointer data)
{
    t_context *ctx = data;

    ctx->gizmo_window = NULL;
    ctx->gizmo_area = NULL;
    gtk_toggle_button_set_active(ctx->gizmo_btn, FALSE); // Desactiva el botón
}
