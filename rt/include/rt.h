/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:06:47 by jutrera-          #+#    #+#             */
/*   Updated: 2025/11/01 13:59:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include	"cJSON.h"
# include 	<string.h>
# include 	<stdlib.h>
# include 	<unistd.h>
# include 	<stdio.h>
# include	<ctype.h>
# include	<pthread.h>
# include	<complex.h>
# include	<omp.h>
# include 	<wait.h>
# include   <math.h>
# include 	<stdatomic.h>
# include   <stdbool.h>
# include	<gtk/gtk.h>
# include 	<stdarg.h>

// Project headers
# include 	"utilities.h"
# include	"gui.h"

// callbacks_compose.c
void 		on_quitCompose(GtkButton *button, gpointer user_data);
void 		on_deleteCompose(GtkButton *button, gpointer user_data);
void 		on_saveCompose(GtkButton *button, gpointer user_data);
void 		on_addCompose_plane(GtkButton *button, gpointer user_data);
void 		on_addCompose_cone(GtkButton *button, gpointer user_data);
void 		on_addCompose_cylinder(GtkButton *button, gpointer user_data);
void 		on_addCompose_sphere(GtkButton *button, gpointer user_data);
gboolean 	on_close_composeWindow(GtkWidget *widget, GdkEvent *event, gpointer user_data);

// callbacks_create.c
void        on_btn_add_pl_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_sp_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_co_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_cy_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_pa_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_to_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_mo_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_spot_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_camera_clicked(GtkButton *button, gpointer user_data);
void        on_btn_add_directional_clicked(GtkButton *button, gpointer user_data);
void        on_btn_delete_clicked(GtkButton *button, gpointer user_data);
void        on_btn_save_clicked(GtkButton *button, gpointer user_data);
void        on_btn_render_clicked(GtkButton *button, gpointer user_data);
void        on_btn_quit_clicked(GtkButton *button, gpointer user_data);
gboolean    on_close_secondwindow(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void 		add_minimum_elements(GtkBuilder *builder);
void 		on_btn_add_library_clicked(GtkButton *button, gpointer user_data);
void 		fix_tab_titles(GtkNotebook *notebook, const gchar *title);

// callbacks_menu.c
void        on_btn_create_clicked(GtkButton *button, gpointer user_data);
void        on_btn_load_clicked(GtkButton *button, gpointer user_data);
void        on_btn_capture_clicked(GtkButton *button, gpointer user_data);
void        on_btn_exit_clicked(GtkButton *button, gpointer user_data);
void 		on_camera_selected(GtkWidget *menu_item, gpointer user_data);
void        on_filter_selected(GtkWidget *menu_item, gpointer user_data);
void 		on_btn_composite_clicked(GtkButton *button, gpointer user_data);
void 		on_toggle_gizmo(GtkToggleButton *toggle_button, gpointer user_data);
gboolean 	on_drawing_area_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean    on_close_mainwindow(GtkWidget *widget, GdkEvent *event, gpointer user_data);
gboolean    on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
int 		get_camera_index(t_camera *camera);

// cameras.c
void    	update_menu_camera(t_context *ctx);
void		move_camera(t_context *ctx, guint dir);
t_camera 	*get_active_camera(t_scene *scene);

// check_entries.c
int 		bad_direction(t_vec d);
int 		bad_ratio(double r, double min, double max);
int 		bad_color(t_color c);
int 		bad_norm(t_vec d);

// create_compose.c
int 		save_planeCompose(GtkWidget *child, t_composite *p);
int 		save_coneCompose(GtkWidget *child, t_composite *p);
int 		save_cylinderCompose(GtkWidget *child, t_composite *p);
int 		save_sphereCompose(GtkWidget *child, t_composite *p);
void 		add_composite_solids(cJSON *root, t_composite *newcomp);

// create_file.c
int		   	create_file(t_scene *scene, gchar *filename);
void 		add_solids(cJSON *root, t_lst_obj *element);
void 		add_planeToJSON(cJSON *plane, t_plane *pl);
void 		add_sphereToJSON(cJSON *sphere, t_sphere *sp);
void 		add_coneToJSON(cJSON *cone, t_cone *co);
void 		add_cylinderToJSON(cJSON *cylinder, t_cone *cy);
void 		manageArray(cJSON *root, cJSON *array, char *item);

// create_others.c
void 		create_transformations(GtkWidget *grid , t_common_widgets *widgets);
void 		create_color(GtkWidget *grid , t_common_widgets *widgets);
void 		create_reflect_refract(GtkWidget *grid , t_common_widgets *widgets);

// create_scene.c
int			create_scene(t_context *ctx, t_scene *aux);

// create_slice.c
void 		create_slice(GtkWidget *grid, t_common_widgets *widgets);

// create_solids.c
GtkWidget   *create_sp_properties(void);
GtkWidget   *create_pl_properties(void);
GtkWidget   *create_co_properties(void);
GtkWidget   *create_cy_properties(void);
GtkWidget   *create_pa_properties(void);
GtkWidget   *create_to_properties(void);
GtkWidget   *create_mo_properties(void);

// create_texture.c
void 		create_texture(GtkWidget *grid, t_common_widgets *widgets);

// create_window.c
GtkWidget   *create_common_properties_grid(int selectprop);
GtkWidget   *create_spot_properties(void);
GtkWidget   *create_camera_properties(void);
GtkWidget   *create_directional_properties(void);
GtkWidget   *create_ambient_properties(void);
GtkWidget 	*create_composite_properties(void);

// fig_cone.c
void		intersect_co(t_ray ray, t_lst_obj *obj, t_point2 *t);
t_vec		get_cone_normal(t_lst_obj *obj, t_vec p);
t_color		apply_texture_to_cone(t_lst_obj *obj, t_vec p);

// fig_cylinder.c
void		intersect_cy(t_ray ray, t_lst_obj *obj, t_point2 *t);
t_vec		get_cylinder_normal(t_lst_obj *obj, t_vec p);
t_color 	apply_texture_to_cylinder(t_lst_obj *obj, t_vec p);

// fig_moebius.c
void 		intersect_moebius(t_ray ray, t_moebius *mb, t_point2 *t_out);
t_vec 		get_moebius_normal(t_moebius *mb, t_ray ray, double t_hit);

// fig_paraboloid.c
void		intersect_pa(t_ray ray, t_paraboloid *pa, t_point2 *t);
t_vec		get_paraboloid_normal(t_paraboloid *pa, t_vec p);

// fig_plane.c
void		intersect_pl(t_ray ray, t_lst_obj *obj, t_point2 *t);
t_vec		get_plane_normal(t_plane *plane);
t_color		apply_texture_to_plane(t_lst_obj *obj, t_vec p);

// fig_sphere.c
void		intersect_sp(t_ray ray, t_lst_obj *obj, t_point2 *t);
t_vec		get_sphere_normal(t_lst_obj *obj, t_vec p);
t_color		apply_texture_to_sphere(t_lst_obj *obj, t_vec p);

// fig_torus.c
t_vec 		get_torus_normal(t_torus *to, t_ray ray, double t_hit);
void		intersect_to(t_ray ray, t_torus *to, t_point2 *t);

// filters.c
void 		select_filter(t_context *ctx, guint type);
void        draw_rgb_buffer(t_context *ctx);

// free_memory.c
void		free_scene(t_scene *scene);
void 		free_rgb_buffer(int **rgb_buffer, int height);
void 		free_composites(t_composite *composites);

// gizmo.c
void 		on_gizmo_window_destroy(GtkWidget *widget, gpointer data);
gboolean 	on_gizmo_draw(GtkWidget *widget, cairo_t *cr, gpointer data);

// initialize.c
t_scene	    *init_scene(void);
t_context 	*init_gui(void);

// lights_shadows.c
t_point3	compute_shadows(t_scene scene, t_vec p, t_vec n, double shine);
t_point3	compute_lights(t_scene scene, t_vec p, t_vec n, double shine);

// messages.c
char		*err_msg(int e);
void 		set_status_label(GtkWidget *status_label, const char *format, ...);

// parse_cameras.c
int			parse_cameras(t_scene *scene, cJSON *json);

// parse_file.c
int         parse_file(char *filename, t_scene *scene, t_context *ctx);

// parse_instances.c
int			parse_instances(t_scene *scene, cJSON *json);
t_composite *load_library_file(t_scene *scene, const char *filename);
t_lst_obj 	*clone_object(t_lst_obj *src);

// parse_library.c
int 		parse_library(t_scene *scene, cJSON *json);
int 		parse_elements_library(t_scene *scene, cJSON *defs);

// parse_lights.c
int			parse_lights(t_scene *scene, cJSON *json);

// parse_objects.c
int			parse_objects(t_scene *scene, cJSON *json);

// parse_options.c
int 		parse_options(t_lst_obj *obj, cJSON *elem);

// parse_solids.c
int			parse_sphere(cJSON *elem, t_lst_obj *obj);
int			parse_plane(cJSON *elem, t_lst_obj *obj);
int			parse_cylinder(cJSON *elem, t_lst_obj *obj);
int			parse_cone(cJSON *elem, t_lst_obj *obj);
int			parse_paraboloid(cJSON *elem, t_lst_obj *obj);
int			parse_torus(cJSON *elem, t_lst_obj *obj);
int			parse_moebius(cJSON *elem, t_lst_obj *obj);
t_localbase get_local_basis(t_vec dir);

// parse_utils.c
int 		parse_point3(cJSON *obj, t_point3 *p);
int 		parse_color(cJSON *obj,  t_color *color);
int 		parse_vec(cJSON *obj, t_vec *v);
void		add_object(t_scene *scene, t_lst_obj *new_obj);
cJSON 		*point_to_json(double x, double y, double z);
cJSON 		*color_to_json(int x, int y, int z);

// process_load.c
int         process_load(gchar *filename, t_context *ctx);

// process_save.c
int         process_save(gchar *filename, t_context *ctx);

// rays.c
t_vec		ray_at(t_ray ray, double t);
t_ray		construct_ray(t_point3 origin, t_vec dir);
t_ray 		construct_secondary_ray(t_point3 origin, t_vec direction, void *last_hit);
t_point3	trace_ray(t_ray ray, t_scene *scene, double n1, int depth_r, int depth_t);
t_lst_obj	*get_closest(t_ray ray, t_lst_obj *obj, double *t_closest);
t_ray 		**precalculated_rays(t_camera *cam, int height, int width);

// ref_ref.c
t_point3 	compute_reflection_color(t_vec ray_dir, t_vec n, t_vec p, t_scene *scene,
	double n1, int depth_r, int depth_t, double reflectivity);
t_point3 	compute_refraction_color(t_vec i, t_vec n, t_vec p, t_scene *scene,
	double n1, int depth_r, int depth_t, t_lst_obj	*closest_obj);
	
// render_scene.c
void 	    render_scene(t_context *ctx);

// slices.c
double 		t_in_the_slices(t_slices *slices, t_ray ray, double t_in, double t_out);
int			p_over_slice(t_plane pl, t_vec p);
void 		check_intersections_slices(t_lst_obj *obj);

// stb_impl.c
t_texture 	*load_texture(const char *filename);
int 		save_png(char *filename, t_scene *scene);
void 		free_texture(t_texture *tex);

// textures.c
t_color 	textures(double u, double v, t_texture *tex, double tiles_u, double tiles_v);


// transformations.c
void 		apply_transformations(t_lst_obj *obj, double scale, t_point3 center);
t_vec 		get_object_center(t_lst_obj *obj);

#endif
