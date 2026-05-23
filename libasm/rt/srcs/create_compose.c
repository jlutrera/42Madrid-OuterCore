/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_compose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:17:00 by jutrera           #+#    #+#             */
/*   Updated: 2025/09/28 12:54:06 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void add_new_composite(t_lst_obj *node, t_composite *p)
{
    if (!p->objects)
        p->objects = node;
    else
    {
        t_lst_obj *last = p->objects;
        while (last->next)
            last = last->next;
        last->next = node;
    }
}

void add_composite_solids(cJSON *obj_array, t_composite *newcomp)
{
    t_lst_obj *element = newcomp->objects;
    
    while (element)
    {
        cJSON *obj = cJSON_CreateObject();
        switch (element->type)
        {
            case SPHERE:
                cJSON_AddStringToObject(obj, "type", "sphere");
                add_sphereToJSON(obj, element->object);
                break;
            case PLANE:
                cJSON_AddStringToObject(obj, "type", "plane");
                add_planeToJSON(obj, element->object);
                break;
            case CONE:
                cJSON_AddStringToObject(obj, "type", "cone");
                add_coneToJSON(obj, element->object);
                break;
            case CYLINDER:
                cJSON_AddStringToObject(obj, "type", "cylinder");
                add_cylinderToJSON(obj, element->object);
                break;
            default:
                break;
        }
        cJSON_AddItemToArray(obj_array, obj);
        element = element->next;
    }
}

int save_planeCompose(GtkWidget *child, t_composite *p)
{
    t_plane_widgets *w = g_object_get_data(G_OBJECT(child), "plane_widgets");
    t_plane *pl = malloc(sizeof(t_plane));
    if (!pl) return MEMORY_E;
    
    pl->coordinate = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    pl->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(pl->direction))
        return free(pl), POINT_E;

    if (bad_norm(pl->direction))
        return free(pl), NORM_E;
        
    pl->direction = vec_unit(pl->direction);

    // Creamos el nodo de la lista de objetos
    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
        return free(pl), MEMORY_E;

    node->type = PLANE;
    node->object = pl;
    node->slices = NULL;
    node->texture = NULL;
    node->next = NULL;
    add_new_composite(node, p);
    return SUCCESS;
}

int save_coneCompose(GtkWidget *child, t_composite *p)
{
    t_cone_widgets *w = g_object_get_data(G_OBJECT(child), "cone_widgets");

    t_cylinder *co = malloc(sizeof(t_cone));
    if (!co) return MEMORY_E;

    co->coordinate = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    co->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(co->direction))
        return free(co), POINT_E;

    if (bad_norm(co->direction))
        return free(co), NORM_E;

    co->direction = vec_unit(co->direction);
    co->radius = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_radius)));
    co->height = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_height)));
	if (co->radius <= 0 || co->height <= 0)
		return free(co), NEGATIVE_E;

    // Creamos el nodo de la lista de objetos
    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
        return free(co), MEMORY_E;

    node->type = CONE;
    node->object = co;
    node->next = NULL;
    node->slices = NULL;
    node->texture = NULL;
    add_new_composite(node, p);
    return SUCCESS;
}

int save_cylinderCompose(GtkWidget *child, t_composite *p)
{
    t_cylinder_widgets *w = g_object_get_data(G_OBJECT(child), "cylinder_widgets");

    t_cylinder *cy = malloc(sizeof(t_cylinder));
    if (!cy) return MEMORY_E;
    
    cy->coordinate = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                             atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    cy->direction = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dx))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dy))),
                            atof(gtk_entry_get_text(GTK_ENTRY(w->entry_dz))));
    if (bad_direction(cy->direction))
        return free(cy), POINT_E;
    
    if (bad_norm(cy->direction))
        return free(cy), NORM_E;

    cy->direction = vec_unit(cy->direction);

    cy->radius = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_radius)));
    cy->height = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_height)));
	if (cy->radius <= 0 || cy->height <= 0)
		return free(cy), NEGATIVE_E;

    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
        return free(cy), MEMORY_E;

    node->type = CYLINDER;
    node->object = cy;
    node->next = NULL;
    node->slices = NULL;
    node->texture = NULL;
    add_new_composite(node, p);
    return SUCCESS;
}

int save_sphereCompose(GtkWidget *child, t_composite *p)
{
    t_sphere_widgets *w = g_object_get_data(G_OBJECT(child), "sphere_widgets");

    t_sphere *sp = malloc(sizeof(t_sphere));
    if (!sp) return MEMORY_E;
    
    sp->center = point3( atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cx))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cy))),
                         atof(gtk_entry_get_text(GTK_ENTRY(w->entry_cz))));
    sp->radius = atof(gtk_entry_get_text(GTK_ENTRY(w->entry_radius)));
    if (sp->radius <= 0)
        return free(sp), NEGATIVE_E;

    // Creamos el nodo de la lista de objetos
    t_lst_obj *node = malloc(sizeof(t_lst_obj));
    if (!node)
        return free(sp), MEMORY_E;

    node->type = SPHERE;
    node->object = sp;
    node->next = NULL;
    node->slices = NULL;
    node->texture = NULL;
    add_new_composite(node, p);
    return SUCCESS;
}
