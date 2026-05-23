/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:55:43 by jutrera-          #+#    #+#             */
/*   Updated: 2025/09/06 13:11:13 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "macros.h"

/********************************************************* */
/*                   Estructuras básicas                   */
/********************************************************* */
typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef t_vec t_point3; // puntos y vectores son equivalentes

typedef struct	s_point2
{
	double	x;
	double	y;
}				t_point2;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray
{
	t_point3	origin;
	t_vec		dir;
	void      	*last_hit_object; // Puntero al último objeto intersectado
}				t_ray;

typedef struct s_thread_manager
{
	pthread_t	threads[MAX_THREADS];
	int 		count;
}				t_thread_manager;

typedef struct	s_localbase
{
	t_vec	u;
	t_vec	v;
	t_vec	w;
}				t_localbase;

typedef struct	s_texture 
{
	char 			*name;
	unsigned char 	*data;
	int 			width;
	int				height;
	int				channels;
} 				t_texture;

/********************************************************* */
/*                  Objetos de la escena                   */
/********************************************************* */
typedef enum	s_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	PARABOLOID,
	TORUS,
	MOEBIUS
}				t_obj_type;

typedef struct	s_sphere
{
	t_point3	center;
	double		radius;
}				t_sphere;

typedef struct	s_plane
{
	t_point3	coordinate;
	t_vec		direction;
}				t_plane;

typedef struct	s_cylinder
{
	t_point3	coordinate;
	t_vec		direction;
	double		radius;
	double		height;
}				t_cylinder;

typedef struct	s_cone
{
	t_point3	coordinate;
	t_vec		direction;
	double		radius;
	double		height;
}				t_cone;

typedef struct	s_paraboloid
{
	t_point3	center;
	t_vec		direction;
	double		k;  //factor de apertura
	double		height;
}				t_paraboloid;

typedef struct	s_torus
{
	t_point3	center;
	double		r_min; //radio del círculo que lo genera
	double		r_max; //radio interior
	t_vec		direction;
	t_localbase	basis; // base local para renderizado, con Z como normal
}				t_torus;

typedef struct	s_moebius
{
	t_point3	center;
	double		width;
	double		radius;
	t_vec		direction;
	t_localbase	basis; // base local para renderizado, con Z como normal
}				t_moebius;

/********************************************************* */
/*               Elementos para la escena                  */
/********************************************************* */
typedef struct	s_ambient
{
	bool		declared;
	double		bright;
	t_color		color;
}				t_ambient;

typedef struct	s_spotlight
{
	t_point3			position;
	double				bright;
	t_color				color;
	struct s_spotlight	*next;	
}				t_spotlight;

typedef	struct	s_directional
{
	bool	declared;
	t_vec	direction;
	double	bright;
	t_color	color;
}				t_directional;

typedef enum	s_filter_type
{
	ORIGINAL,
	GRAYSCALE,
	SEPIA,
	INVERT,
	POSTERIZE
}				t_filter_type;

typedef struct	s_camera
{
	bool			active;
	t_point3		position;
	t_vec			direction;
	int				fov;
	t_point3		viewp;
	t_localbase		localbase;
	t_ray 			**prec_rays;
	struct s_camera	*next;
}				t_camera;

typedef struct	s_slices
{
	t_plane 		slice;
	struct s_slices *next;
}				t_slices;

typedef struct	s_lst_obj
{
	void				*object;
	t_obj_type			type;
	t_color				color;
	double				shine;
	t_vec				translation;
	t_vec				rotation;
	double				reflect;
	double				transparency;
	double				ior;
	t_slices			*slices;
	t_texture			*texture;
	struct s_lst_obj	*next;
}				t_lst_obj;

typedef struct	s_composite
{
	char				*name;
	double				scale;
	t_lst_obj			*objects;
	struct s_composite	*next;
}				t_composite;

/********************************************************* */
/*                         La escena                       */
/********************************************************* */

typedef struct	s_scene
{
	t_camera		*camera;
	t_ambient		ambient;
	t_spotlight		*spotlight;
	t_directional	directional;
	t_filter_type	filter_type;
	t_lst_obj		*obj;
	t_composite		*composites;
	int				**rgb_buffer;
	int				**rgb_buffer_filtered;
	int				width;
	int				height;
}				t_scene;

#endif
