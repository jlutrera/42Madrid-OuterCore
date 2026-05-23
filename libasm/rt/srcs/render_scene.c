/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:08:05 by jutrera-          #+#    #+#             */
/*   Updated: 2025/09/28 10:24:32 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int percent;

// Hilo principal
static gboolean update_progress_bar(gpointer user_data)
{
    t_context *ctx = user_data;

    int p = atomic_load(&percent);
    int total = ctx->scene->width * ctx->scene->height;
    double fraction = (double)p / (double)total;
    if (fraction > 1.0) fraction = 1.0;

    // ancho total de la barra en caracteres a ojo
    int width = 65;
    // BARRA DE RELLENO
    int filled = (int)(fraction * width);
    if (filled > width) filled = width;
    GString *bar = g_string_new("");
    for (int i = 0; i < filled; i++)
        g_string_append(bar, "█");

    // TEXTO LOAD %
    char percent_text[16];
    snprintf(percent_text, sizeof(percent_text), " %.1f%%", fraction * 100.0);
    g_string_append(bar, percent_text);

    // BARRA DE LO QUE FALTA
    int used = filled + (int)strlen(percent_text);
    for (int i = used; i < width; i++)
        g_string_append(bar, "░");

    
    gtk_label_set_text(GTK_LABEL(ctx->status_label), bar->str);
    g_string_free(bar, TRUE);
    if (p >= total)
    {
        ctx->render_finished = true;
        draw_rgb_buffer(ctx);
        set_status_label(ctx->status_label, "Image rendered");
        if (ctx->gizmo_window)
        {
            int cam_index = get_camera_index(ctx->scene->camera);
            char label[32];
            snprintf(label, sizeof(label), "Cam %d", cam_index);
            gtk_window_set_title(GTK_WINDOW(ctx->gizmo_window), label);
            gtk_widget_queue_draw(ctx->gizmo_area); 
        }
        return FALSE;
    }
    return TRUE;
}

// Función para generar un rayo para una coordenada de subpíxel
static t_ray camera_generate_subpixel_ray(t_camera *cam, int px, int py, 
				double sub_x_offset, double sub_y_offset, int width, int height)
{
    double pixel_x_coord_float = (double)px + sub_x_offset;
    double pixel_y_coord_float = (double)py + sub_y_offset;

    double u_coord = (pixel_x_coord_float - (double)width / 2.0) * cam->viewp.x / (double)width;
    double v_coord = (pixel_y_coord_float - (double)height / 2.0) * cam->viewp.y / (double)height;
    
    t_vec dir = vec_add(cam->localbase.w,
                    vec_add(vec_mul(cam->localbase.u, u_coord),
                            vec_mul(cam->localbase.v, v_coord)));

    dir = vec_unit(dir);

    return construct_ray(cam->position, dir);
}

// Esta función renderiza los píxeles de la escena utilizando SUPERSAMPLING
static void ft_render(t_context *ctx)
{
    t_camera *cam = ctx->scene->camera;
    while (cam && !cam->active)
        cam = cam->next;

    int **rgb_buffer = ctx->scene->rgb_buffer;

    // Define la cantidad de muestras por dimensión (2x2 = 2 muestras en X, 2 en Y)
    const int SAMPLES_PER_DIMENSION = 2;
    const int TOTAL_SAMPLES = SAMPLES_PER_DIMENSION * SAMPLES_PER_DIMENSION;

	int width = ctx->scene->width;
	int height = ctx->scene->height;
    int total = width * height;
            
    g_timeout_add(50, update_progress_bar, ctx);

    #pragma omp parallel for collapse(2) shared(percent)
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            t_point3 accumulated_color = {0, 0, 0};

            for (int sy = 0; sy < SAMPLES_PER_DIMENSION; sy++)
            {
                for (int sx = 0; sx < SAMPLES_PER_DIMENSION; sx++)
                {
                    // Calcular el offset para la submuestra.
                    // Para 2x2, los offsets pueden ser:(0.25, 0.25), (0.75, 0.25), (0.25, 0.75), (0.75, 0.75)
                    double sub_x_offset = (double)sx / SAMPLES_PER_DIMENSION + (0.5 / SAMPLES_PER_DIMENSION);
                    double sub_y_offset = (double)sy / SAMPLES_PER_DIMENSION + (0.5 / SAMPLES_PER_DIMENSION);

                    t_ray ray = camera_generate_subpixel_ray(cam, x, y, sub_x_offset, sub_y_offset, width, height);
                    ray.last_hit_object = NULL;
                    t_point3 sub_color = trace_ray(ray, ctx->scene, 1.0, 0, 0);
					accumulated_color = vec_add(accumulated_color, sub_color);
                }
            }

            // Promediar los colores acumulados
            t_point3 final_color = vec_div(accumulated_color, (double)TOTAL_SAMPLES);
            rgb_buffer[y][x] = ( ((int)final_color.x << 16) | 
                   				 ((int)final_color.y << 8)  |
								 ((int)final_color.z) );

            #pragma omp atomic 
            percent++;
        }
    }
}

void render_scene(t_context *ctx)
{
    //create_progress_window(ctx);
    gtk_widget_set_visible(ctx->progress_bar, TRUE);
    ctx->render_finished = false;
    percent = 0;
    g_thread_new("render-thread", (GThreadFunc)ft_render, ctx);
}