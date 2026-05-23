/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:09:48 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/06 10:17:43 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

/*****************************************************/
/*   Estructuras para guardar referencias con GTK    */
/*****************************************************/
typedef struct	s_slice_widgets
{
    GtkWidget   *entry_px;
    GtkWidget   *entry_py;
    GtkWidget   *entry_pz;
    GtkWidget   *entry_nx;
    GtkWidget   *entry_ny;
    GtkWidget   *entry_nz;
	GtkWidget   *frame;
} 				t_slice_widgets;

typedef struct	s_common_widgets
{
	GtkWidget 	*btn_color;
	GtkWidget	*spin_shine;
	GtkWidget	*entry_tx;
	GtkWidget	*entry_ty;
	GtkWidget	*entry_tz;
	GtkWidget	*entry_rx;
	GtkWidget	*entry_ry;
	GtkWidget	*entry_rz;
	GtkWidget	*spin_reflect;
	GtkWidget	*spin_transparency;
	GtkWidget	*spin_ior;
	GtkWidget	*combo_texture;
	GtkWidget	*entry_texture_image;
	GtkWidget	*btn_texture_image;
    gchar       *file_texture;
	GtkWidget   *entry_spx;
	GtkWidget   *entry_spy;
	GtkWidget   *entry_spz;
	GtkWidget   *entry_snx;
	GtkWidget   *entry_sny;
	GtkWidget   *entry_snz;
	GList       *list_slices;
	GtkWidget   *slice_container;
    int         row;
}				t_common_widgets;

typedef struct 	s_cylinder_widgets 
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
    GtkWidget 	*entry_radius;
    GtkWidget 	*entry_height;
    GtkWidget 	*grid_common;
} 				t_cylinder_widgets;

typedef struct 	s_cone_widgets 
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
    GtkWidget 	*entry_radius;
    GtkWidget 	*entry_height;
    GtkWidget 	*grid_common;
} 				t_cone_widgets;

typedef struct 	s_sphere_widgets 
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_radius;
    GtkWidget 	*grid_common;
} 				t_sphere_widgets;

typedef struct 	s_plane_widgets 
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
    GtkWidget 	*grid_common;
} 				t_plane_widgets;

typedef struct 	s_paraboloid_widgets 
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
    GtkWidget 	*entry_k;
    GtkWidget 	*entry_height;
    GtkWidget 	*grid_common;
} 				t_paraboloid_widgets;

typedef struct 	s_torus_widgets 
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
    GtkWidget 	*entry_r_min;
    GtkWidget 	*entry_r_max;
    GtkWidget 	*grid_common;
} 				t_torus_widgets;

typedef struct 	s_moebius_widgets 
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
    GtkWidget 	*entry_width;
    GtkWidget 	*entry_radius;
    GtkWidget 	*grid_common;
} 				t_moebius_widgets;

typedef struct 	s_camera_widgets
{
    GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
    GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
	GtkWidget 	*entry_fov;
}				t_camera_widgets;

typedef struct 	s_spot_widgets
{
	GtkWidget 	*entry_cx;
    GtkWidget 	*entry_cy;
    GtkWidget 	*entry_cz;
	GtkWidget 	*spin_bright;
	GtkWidget 	*btn_color;
}				t_spot_widgets;

typedef struct 	s_directional_widgets
{
	GtkWidget 	*entry_dx;
    GtkWidget 	*entry_dy;
    GtkWidget 	*entry_dz;
	GtkWidget 	*spin_bright;
	GtkWidget 	*btn_color;
}				t_directional_widgets;

typedef struct 	s_ambient_widgets
{
	GtkWidget 	*spin_bright;
	GtkWidget 	*btn_color;
}				t_ambient_widgets;

typedef struct 	s_composite_widgets
{
    GtkWidget	*window;
    GtkWidget 	*notebook;
    GtkWidget 	*entry_name;
}				t_composite_widgets;

typedef struct	s_instance_widgets
{
    GtkWidget	    *entry_name;
    GtkWidget 	    *entry_scale;
    GtkWidget 	    *grid_common;
    GtkWidget       *preview_scrolled;
    GtkWidget       *preview_view;
    GtkTextBuffer   *preview_buffer;
}   			t_instance_widgets;

typedef struct	s_context
{
    t_scene     	*scene;
    // Referencias a objetos GTK

	GtkBuilder		*creator_builder;
    GtkWidget   	*main_window;
	GtkWidget		*creator_window;
	GtkWidget		*btn_camera;
    GtkWidget   	*drawing_area;
    GtkWidget   	*status_label;
    GtkWidget 		*progress_bar;
	GtkWidget 		*filter_menu_items[5];
	GtkWidget 		*camera_menu;
	GtkWidget		*camera_menu_items[10];
    GtkToggleButton *gizmo_btn;
    GtkWidget       *gizmo_window;
    GtkWidget       *gizmo_area;
	int		    	camera_count;
    bool            render_finished;
} 				t_context;

#endif
