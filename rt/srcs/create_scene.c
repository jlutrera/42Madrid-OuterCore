/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:45:08 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/02 12:21:34 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_slices *convert_slices_list(t_common_widgets *w)
{
    t_slices *head = NULL;
    t_slices *tail = NULL;

    for (GList *l = w->list_slices; l != NULL; l = l->next)
    {
        t_slice_widgets *sw = (t_slice_widgets *)l->data;
        t_slices *node = g_new0(t_slices, 1);

        node->slice.coordinate = point3( atof(gtk_entry_get_text(GTK_ENTRY(sw->entry_px))),
                                         atof(gtk_entry_get_text(GTK_ENTRY(sw->entry_py))),
                                         atof(gtk_entry_get_text(GTK_ENTRY(sw->entry_pz))));

        node->slice.direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(sw->entry_nx))),
                                        atof(gtk_entry_get_text(GTK_ENTRY(sw->entry_ny))),
                                        atof(gtk_entry_get_text(GTK_ENTRY(sw->entry_nz))));
        if (!head)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

static void save_common_properties(GtkWidget *grid_common, t_lst_obj *obj)
{
    t_common_widgets *w = g_object_get_data(G_OBJECT(grid_common), "common_widgets");

    GdkRGBA color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(w->btn_color), &color);
    obj->color = color_rgb(color.red, color.green, color.blue);
    if (bad_color(obj->color))
        obj->color = (t_color){255,255,255};

    obj->shine = gtk_spin_button_get_value(GTK_SPIN_BUTTON(w->spin_shine));
    if (bad_ratio(obj->shine, 10, 1000))
        obj->shine = 10;

    obj->ior = gtk_spin_button_get_value(GTK_SPIN_BUTTON(w->spin_ior));
    if (bad_ratio(obj->ior, 1, 5))
        obj->ior = 1;

    obj->reflect = gtk_spin_button_get_value(GTK_SPIN_BUTTON(w->spin_reflect));
    if (bad_ratio(obj->reflect, 0, 1))
        obj->reflect = 0;

    obj->transparency = gtk_spin_button_get_value(GTK_SPIN_BUTTON(w->spin_transparency));
    if (bad_ratio(obj->transparency, 0, 1))
        obj->transparency = 0;

    // Normalizar transparencia y reflexión
	double sum_rt = obj->transparency + obj->reflect;
	if (sum_rt > 1)
	{
		double scale = 1.0 / sum_rt;
		obj->reflect *= scale;
		obj->transparency *= scale;
	}

    obj->translation = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_tx))),
                               atof(gtk_entry_get_text(GTK_ENTRY(w->entry_ty))), 
                               atof(gtk_entry_get_text(GTK_ENTRY(w->entry_tz))));

    obj->rotation = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_rx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_ry))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_rz))));

    if (w->combo_texture)
    {
        gchar *name = (gchar *)gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(w->combo_texture));
        if (g_strcmp0(name, "Checkerboard") == 0)
            obj->texture = load_texture(name);
        else if (g_strcmp0(name, "None") == 0)
            obj->texture = NULL;
        else //name = "Image"              
        {
            const gchar *filepath = gtk_entry_get_text(GTK_ENTRY(w->entry_texture_image));
            obj->texture = load_texture(filepath);
        }
        g_free(name);
    }
    else
        obj->texture = NULL;

    if (w->list_slices)
        obj->slices = convert_slices_list(w);
    else
        obj->slices = NULL;
}

static int save_camera(GtkWidget *child, t_scene *scene)
{
    t_camera_widgets *w = g_object_get_data(G_OBJECT(child), "camera_widgets");

    t_camera *cam = malloc(sizeof(t_camera));
    if (!cam)
        return MEMORY_E;

    cam->fov = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_fov)));
    if (bad_ratio(cam->fov, 10, 120))
    {
        free(cam);
        return FOV_E;
    }

    cam->position = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    cam->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));

    if (bad_direction(cam->direction))
    {
        free(cam);
        return POINT_E;
    }

    if (bad_norm(cam->direction))
    {
        free(cam);
        return(NORM_E);
    }
    cam->direction = vec_unit(cam->direction);
    cam->prec_rays = NULL;
    cam->next = NULL;

    if (!scene->camera)
    {
        scene->camera = cam;
        cam->active = true;
    }
    else
    {
        t_camera *p = scene->camera;
        while (p->next)
            p = p->next;
        p->next = cam;
        cam->active = false;
    }

    return SUCCESS;
}

static int save_ambient(GtkWidget *child, t_scene *scene)
{
    t_ambient_widgets *w = g_object_get_data(G_OBJECT(child), "ambient_widgets");

    scene->ambient.bright= gtk_spin_button_get_value(GTK_SPIN_BUTTON(w->spin_bright));
    if (bad_ratio(scene->ambient.bright, 0.25, 1))
        return AMBI_BR_E;
    scene->ambient.declared = true;

    GdkRGBA color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(w->btn_color), &color);
    scene->ambient.color = color_rgb(color.red, color.green, color.blue);
    if (bad_color(scene->ambient.color))
        return COLOR_E;

    return SUCCESS;
}

static int save_directional(GtkWidget *child, t_scene *scene)
{
    t_directional_widgets *w = g_object_get_data(G_OBJECT(child), "directional_widgets");

    
    scene->directional.direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                                                atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                                                atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    
    if (bad_direction(scene->directional.direction))
        return DIRECT_E;
    scene->directional.direction = vec_unit(scene->directional.direction);

    scene->directional.bright = gtk_spin_button_get_value(GTK_SPIN_BUTTON(w->spin_bright));
    if (bad_ratio(scene->directional.bright, 0, 1))
        return BRIGHT_E;

    GdkRGBA color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(w->btn_color), &color);
    scene->directional.color = color_rgb(color.red, color.green, color.blue);
    if (bad_color(scene->directional.color))
        return COLOR_E;

    scene->directional.declared = true;

    return SUCCESS;
}

static int save_spot(GtkWidget *child, t_scene *scene)
{
    t_spot_widgets *w = g_object_get_data(G_OBJECT(child), "spot_widgets");

    t_spotlight *spot = malloc(sizeof(t_spotlight));
    if (!spot)
        return MEMORY_E;

    spot->position = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    spot->bright = gtk_spin_button_get_value(GTK_SPIN_BUTTON(w->spin_bright));
    if (bad_ratio(spot->bright, 0, 1))
    {
        free(spot);
        return BRIGHT_E;
    }

    GdkRGBA color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(w->btn_color), &color);
    spot->color = color_rgb(color.red, color.green, color.blue);
    if (bad_color(spot->color))
    {
        free(spot);
        return COLOR_E;
    }

    spot->next = NULL;
    if (!scene->spotlight)
    {
        scene->spotlight = spot;
    }
    else
    {
        t_spotlight *p = scene->spotlight;
        while (p->next)
            p = p->next;
        p->next = spot;
    }

    return SUCCESS;
}

static int save_cylinder(GtkWidget *child, t_scene *scene)
{
    t_cylinder_widgets *w = g_object_get_data(G_OBJECT(child), "cylinder_widgets");

    t_cylinder *cy = malloc(sizeof(t_cylinder));
    if (!cy)
        return MEMORY_E;
    cy->coordinate = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    cy->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(cy->direction))
    {
        free(cy);
        return POINT_E;
    }
    if (bad_norm(cy->direction))
    {
        free(cy);
        return NORM_E;
    }
    cy->direction = vec_unit(cy->direction);

    cy->radius = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_radius)));
    cy->height = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_height)));
	if (cy->radius <= 0 || cy->height <= 0)
	{
		free(cy);
		return NEGATIVE_E;
	}

    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
    {
        free(cy);
        return MEMORY_E;
    }
    node->type = CYLINDER;
    node->object = cy;
    node->next = NULL;

    save_common_properties(w->grid_common, node);

    t_vec center = get_object_center(node);
    apply_transformations(node, 0, center);
    add_object(scene, node);

    return SUCCESS;
}

static int save_cone(GtkWidget *child, t_scene *scene)
{
    t_cone_widgets *w = g_object_get_data(G_OBJECT(child), "cone_widgets");

    t_cylinder *co = malloc(sizeof(t_cone));
    if (!co)
        return MEMORY_E;

    co->coordinate = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    co->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(co->direction))
    {
        free(co);
        return POINT_E;
    }
    if (bad_norm(co->direction))
    {
        free(co);
        return NORM_E;
    }
    co->direction = vec_unit(co->direction);
    co->radius = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_radius)));
    co->height = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_height)));
	if (co->radius <= 0 || co->height <= 0)
	{
		free(co);
		return NEGATIVE_E;
	}
   
    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
    {
        free(co);
        return MEMORY_E;
    }
    node->type = CONE;
    node->object = co;
    node->next = NULL;

    save_common_properties(w->grid_common, node);

    t_vec center = get_object_center(node);
    apply_transformations(node, 0, center);
    add_object(scene, node);

    return SUCCESS;
}

static int save_sphere(GtkWidget *child, t_scene *scene)
{
    t_sphere_widgets *w = g_object_get_data(G_OBJECT(child), "sphere_widgets");

    t_sphere *sp = malloc(sizeof(t_sphere));
    if (!sp)
        return MEMORY_E;
    sp->center = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    sp->radius = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_radius)));
    if (sp->radius <= 0)
    {
        free(sp);
        return NEGATIVE_E;
    }
   
    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
    {
        free(sp);
        return MEMORY_E;
    }
    node->type = SPHERE;
    node->object = sp;
    node->next = NULL;

    save_common_properties(w->grid_common, node);

    t_vec center = get_object_center(node);
    apply_transformations(node, 0, center);
    add_object(scene, node);

    return SUCCESS;
}

static int save_plane(GtkWidget *child, t_scene *scene)
{
    t_plane_widgets *w = g_object_get_data(G_OBJECT(child), "plane_widgets");

    t_plane *pl = malloc(sizeof(t_plane));
    if (!pl)
        return MEMORY_E;
    pl->coordinate = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    pl->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(pl->direction))
    {
        free(pl);
        return POINT_E;
    }
    if (bad_norm(pl->direction))
    {
        free(pl);
        return NORM_E;
    }
    pl->direction = vec_unit(pl->direction);

    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
    {
        free(pl);
        return MEMORY_E;
    }
    node->type = PLANE;
    node->object = pl;
    node->next = NULL;

    save_common_properties(w->grid_common, node);
    
    t_vec center = get_object_center(node);
    apply_transformations(node, 0, center);
    add_object(scene, node);

    return SUCCESS;
}

static int save_paraboloid(GtkWidget *child, t_scene *scene)
{
    t_paraboloid_widgets *w = g_object_get_data(G_OBJECT(child), "paraboloid_widgets");

    t_paraboloid *pa = malloc(sizeof(t_paraboloid));
    if (!pa)
        return MEMORY_E;
    pa->center = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    pa->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(pa->direction))
    {
        free(pa);
        return POINT_E;
    }
    if (bad_norm(pa->direction))
    {
        free(pa);
        return NORM_E;
    }
    pa->direction = vec_unit(pa->direction);

    pa->k = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_k)));
    pa->height = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_height)));
    if (pa->k <= 0 || pa->height <= 0)
    {
        free(pa);
        return VALUE_E;
    }

    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
    {
        free(pa);
        return MEMORY_E;
    }
    node->type = PARABOLOID;
    node->object = pa;
    node->next = NULL;

    save_common_properties(w->grid_common, node);
    
    t_vec center = get_object_center(node);
    apply_transformations(node, 0, center);
    add_object(scene, node);

    return SUCCESS;
}

static int save_torus(GtkWidget *child, t_scene *scene)
{
    t_torus_widgets *w = g_object_get_data(G_OBJECT(child), "torus_widgets");

    t_torus *to = malloc(sizeof(t_torus));
    if (!to)
        return MEMORY_E;
    to->center = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    to->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(to->direction))
    {
        free(to);
        return POINT_E;
    }
    if (bad_norm(to->direction))
    {
        free(to);
        return NORM_E;
    }
    to->direction = vec_unit(to->direction);

    to->r_min = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_r_min)));
    to->r_max = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_r_max)));

 	if (to->r_min <= 0 || to->r_max <= 0)
	{
		free(to);
		return NEGATIVE_E;
	}
	if (to->r_max < to->r_min)
	{
		free(to);
		return VALUE_E;
	}
	to->basis = get_local_basis(to->direction);

    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
    {
        free(to);
        return MEMORY_E;
    }
    node->type = TORUS;
    node->object = to;
    node->next = NULL;

    save_common_properties(w->grid_common, node);
    
    t_vec center = get_object_center(node);
    apply_transformations(node, 0, center);
    add_object(scene, node);

    return SUCCESS;
}

static int save_moebius(GtkWidget *child, t_scene *scene)
{
    t_moebius_widgets *w = g_object_get_data(G_OBJECT(child), "moebius_widgets");

    t_moebius *mo = malloc(sizeof(t_moebius));
    if (!mo)
        return MEMORY_E;
    mo->center = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    mo->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(mo->direction))
    {
        free(mo);
        return POINT_E;
    }
    if (bad_norm(mo->direction))
    {
        free(mo);
        return NORM_E;
    }
    mo->direction = vec_unit(mo->direction);

    mo->width = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_width)));
    if (bad_ratio(mo->width, 0, 1))
    {
        free(mo);
        return VALUE_E;
    }
    mo->width = mo->width / 100 + 0.005; // ancho entre 0.005 y 0.015
    
    mo->basis = get_local_basis(mo->direction);

    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
    {
        free(mo);
        return MEMORY_E;
    }
    node->type = MOEBIUS;
    node->object = mo;
    node->next = NULL;
    
    save_common_properties(w->grid_common, node);
    
    t_vec center = get_object_center(node);
    apply_transformations(node, 0, center);
    add_object(scene, node);

    return SUCCESS;
}

static int save_instance(GtkWidget *child, t_scene *scene)
{
    t_instance_widgets *w = g_object_get_data(G_OBJECT(child), "instance_widgets");

    const gchar *instance_name = gtk_entry_get_text(GTK_ENTRY(w->entry_name));
    t_composite *node = load_library_file(scene, instance_name);    
    if (!node)
        return JSON_E;

    node->scale = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_scale)));
    
    t_lst_obj *obj = node->objects;
    bool first_object = true;
    t_vec center;
    while (obj)
    {
        t_lst_obj *clone = clone_object(obj);
		if (!clone)
			return MEMORY_E;
            
		save_common_properties(w->grid_common, clone);
        
        if (first_object)
		{
            center = get_object_center(clone);
            first_object = false;
        }
        
		apply_transformations(clone, node->scale, center);
		add_object(scene, clone);
        
		obj = obj->next;
    }
    return SUCCESS;
}

int create_scene(t_context *ctx, t_scene *aux)
{
    GtkNotebook *notebook = GTK_NOTEBOOK(gtk_builder_get_object(GTK_BUILDER(ctx->creator_builder), "notebook_scene_elements"));
    
    int page_count = gtk_notebook_get_n_pages(notebook);
    int i = 0;
    int error = 0;
    while (i < page_count && error == 0)
    {
        GtkWidget *child = gtk_notebook_get_nth_page(notebook, i);
        GtkWidget *tab_label = gtk_notebook_get_tab_label(notebook, child);
        const gchar *tab_title = gtk_label_get_text(GTK_LABEL(tab_label));
        
        if (g_str_has_prefix(tab_title, "Camera"))
            error = save_camera(child, aux);

        else if (g_str_has_prefix(tab_title, "Ambient"))
            error = save_ambient(child, aux);
    
        else if (g_str_has_prefix(tab_title, "Spot"))
            error = save_spot(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Directional"))
            error = save_directional(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Cylinder"))
            error = save_cylinder(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Cone"))
            error = save_cone(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Sphere"))
            error = save_sphere(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Plane"))
            error = save_plane(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Paraboloid"))
            error = save_paraboloid(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Torus"))
            error = save_torus(child, aux);
    
        else if (g_str_has_prefix(tab_title, "Moebius"))
            error = save_moebius(child, aux);
        
        else if (g_str_has_prefix(tab_title, "Instance"))
            error = save_instance(child, aux);
        
        i++;
    }
    aux->filter_type = ctx->scene->filter_type;
    
    if (error) 
        return error;
    return SUCCESS;
}
