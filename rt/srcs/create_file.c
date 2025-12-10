/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:15:24 by jutrera           #+#    #+#             */
/*   Updated: 2025/10/23 23:29:31 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void add_ambient(cJSON *root, t_ambient element)
{
    cJSON *ambient = cJSON_CreateObject();
    cJSON_AddItemToObject(ambient, "color", color_to_json(element.color.r,
                                                          element.color.g,
                                                          element.color.b));
    cJSON_AddNumberToObject(ambient, "bright", element.bright);
    cJSON_AddItemToObject(root, "ambient", ambient);
}

static void add_directional(cJSON *root, t_directional element)
{
    cJSON *dir = cJSON_CreateObject();
    cJSON_AddItemToObject(dir, "direction", point_to_json(element.direction.x,
                                                           element.direction.y,
                                                           element.direction.z));
    cJSON_AddNumberToObject(dir, "bright", element.bright);
    cJSON_AddItemToObject(dir, "color", color_to_json(element.color.r,
                                                      element.color.g,
                                                      element.color.b));
    cJSON_AddItemToObject(root, "directional", dir);
}

static void add_spotlights(cJSON *root, t_spotlight *element)
{
    cJSON *spotlights = cJSON_CreateArray();
    while (element)
    {
        cJSON *spot = cJSON_CreateObject();
        cJSON_AddItemToObject(spot, "position", point_to_json(element->position.x,
                                                               element->position.y,
                                                               element->position.z));
        cJSON_AddNumberToObject(spot, "bright", element->bright);
        cJSON_AddItemToObject(spot, "color", color_to_json(element->color.r, 
                                                           element->color.g, 
                                                           element->color.b));
        cJSON_AddItemToArray(spotlights, spot);
        element = element->next;
    }
    cJSON_AddItemToObject(root, "spots", spotlights);
}

static void add_cameras(cJSON *root, t_camera *element)
{
    cJSON *cams = cJSON_CreateArray();
    while (element)
    {
        cJSON *cam = cJSON_CreateObject();
        cJSON_AddItemToObject(cam, "position", point_to_json(element->position.x,
                                                              element->position.y,
                                                              element->position.z));
        cJSON_AddItemToObject(cam, "direction", point_to_json(element->direction.x,
                                                               element->direction.y,
                                                               element->direction.z));
        cJSON_AddNumberToObject(cam, "fov", element->fov);
        cJSON_AddItemToArray(cams, cam);
        element  = element->next;
    }
    cJSON_AddItemToObject(root, "cameras", cams);
}

static void add_paraboloidToJSON(cJSON *paraboloid, t_paraboloid *pa)
{
    cJSON_AddItemToObject(paraboloid, "center", point_to_json(pa->center.x,
                                                              pa->center.y,
                                                              pa->center.z));
    cJSON_AddItemToObject(paraboloid, "direction", point_to_json(pa->direction.x,
                                                               pa->direction.y,
                                                               pa->direction.z));
    cJSON_AddNumberToObject(paraboloid, "k", pa->k);
    cJSON_AddNumberToObject(paraboloid, "height", pa->height);
}

static void add_torusToJSON(cJSON *torus, t_torus *to)
{
    cJSON_AddItemToObject(torus, "center", point_to_json(to->center.x,
                                                         to->center.y,
                                                         to->center.z));
    cJSON_AddItemToObject(torus, "direction", point_to_json(to->direction.x,
                                                            to->direction.y,
                                                            to->direction.z));
    cJSON_AddNumberToObject(torus, "minor", to->r_min);
    cJSON_AddNumberToObject(torus, "major", to->r_max);
}

static void add_moebiusToJSON(cJSON *moebius, t_moebius *mo)
{
    cJSON_AddItemToObject(moebius, "center", point_to_json(mo->center.x,
                                                           mo->center.y,
                                                           mo->center.z));
    cJSON_AddItemToObject(moebius, "direction", point_to_json(mo->direction.x,
                                                              mo->direction.y,
                                                              mo->direction.z));
    cJSON_AddNumberToObject(moebius, "width", mo->width);
    cJSON_AddNumberToObject(moebius, "radius", mo->radius);
}

static void add_commonProperties(cJSON *object, t_lst_obj *element)
{
    // Las transformaciones: traslacione y rotaciones ya se han aplicado
    // Por eso no se guardan en el archivo .rt
    
    if (element->color.r != 255 ||
        element->color.g != 255 ||
        element->color.b != 255 )
        cJSON_AddItemToObject(object, "color", color_to_json(element->color.r, 
                                                             element->color.g, 
                                                             element->color.b)); 
                                                             
    if (element->shine != 10)
        cJSON_AddNumberToObject(object, "shine", element->shine);
    
    if (element->reflect != 0)
        cJSON_AddNumberToObject(object, "reflectivity", element->reflect);
        
    if (element->transparency != 0)
        cJSON_AddNumberToObject(object, "transparency", element->transparency);

    if (element->ior != 1)
        cJSON_AddNumberToObject(object, "refraction", element->ior);

    if (element->texture)
        cJSON_AddStringToObject(object, "texture", element->texture->name);

    if (element->slices)
    {
        cJSON *slices = cJSON_CreateArray();
        t_slices *elem = element->slices;
        while (elem)
        {
            cJSON *sl = cJSON_CreateObject();
            add_planeToJSON(sl, &elem->slice);
            cJSON_AddItemToArray(slices, sl);
            elem = elem->next;
        }
        cJSON_AddItemToObject(object, "slice", slices);
    }
}

void add_planeToJSON(cJSON *plane, t_plane *pl)
{
    cJSON_AddItemToObject(plane, "position", point_to_json(pl->coordinate.x,
                                                           pl->coordinate.y,
                                                           pl->coordinate.z));
    cJSON_AddItemToObject(plane, "normal", point_to_json(pl->direction.x,
                                                         pl->direction.y,
                                                         pl->direction.z));
}

void add_sphereToJSON(cJSON *sphere, t_sphere *sp)
{
    cJSON_AddItemToObject(sphere, "center", point_to_json(sp->center.x,
                                                          sp->center.y,
                                                          sp->center.z));
    cJSON_AddNumberToObject(sphere, "radius", sp->radius);
}

void add_coneToJSON(cJSON *cone, t_cone *co)
{
    cJSON_AddItemToObject(cone, "position", point_to_json(co->coordinate.x,
                                                          co->coordinate.y,
                                                          co->coordinate.z));
    cJSON_AddItemToObject(cone, "direction", point_to_json(co->direction.x,
                                                            co->direction.y,
                                                            co->direction.z));
    cJSON_AddNumberToObject(cone, "radius", co->radius);
    cJSON_AddNumberToObject(cone, "height", co->height);
}

void add_cylinderToJSON(cJSON *cylinder, t_cone *cy)
{
    cJSON_AddItemToObject(cylinder, "position", point_to_json(cy->coordinate.x,
                                                          cy->coordinate.y,
                                                          cy->coordinate.z));
    cJSON_AddItemToObject(cylinder, "direction", point_to_json(cy->direction.x,
                                                            cy->direction.y,
                                                            cy->direction.z));
    cJSON_AddNumberToObject(cylinder, "radius", cy->radius);
    cJSON_AddNumberToObject(cylinder, "height", cy->height);
}

void manageArray(cJSON *root, cJSON *array, char *item)
{
    if (cJSON_GetArraySize(array) == 0)
    {
        cJSON_Delete(array);
        array = NULL;
    }
    else
        cJSON_AddItemToObject(root, item, array);
}

void add_solids(cJSON *root, t_lst_obj *element)
{
    cJSON *spheres = cJSON_CreateArray();
    cJSON *planes = cJSON_CreateArray();
    cJSON *cones = cJSON_CreateArray();
    cJSON *cylinders = cJSON_CreateArray();
    cJSON *paraboloids = cJSON_CreateArray();
    cJSON *tori = cJSON_CreateArray();
    cJSON *moebiuses = cJSON_CreateArray();
    
    while (element)
    {
        switch (element->type)
        {
            case SPHERE:
            {
				cJSON *sphere = cJSON_CreateObject();
                add_sphereToJSON(sphere, element->object);
                add_commonProperties(sphere, element);
                cJSON_AddItemToArray(spheres, sphere);
                break;
			}
            case PLANE:
            {
                cJSON *plane = cJSON_CreateObject();
                add_planeToJSON(plane, element->object);
                add_commonProperties(plane, element);
                cJSON_AddItemToArray(planes, plane);
                break;
			}
            case CONE:
            {
                cJSON *cone = cJSON_CreateObject();
                add_coneToJSON(cone, element->object);
                add_commonProperties(cone, element);
                cJSON_AddItemToArray(cones, cone);
                break;
			}
            case CYLINDER:
            {
                cJSON *cylinder = cJSON_CreateObject();
                add_cylinderToJSON(cylinder, element->object);
                add_commonProperties(cylinder, element);
                cJSON_AddItemToArray(cylinders, cylinder);
                break;
			}
            case PARABOLOID:
            {
                cJSON *paraboloid = cJSON_CreateObject();
                add_paraboloidToJSON(paraboloid, element->object);
                add_commonProperties(paraboloid, element);
                cJSON_AddItemToArray(paraboloid, paraboloid);
                break;
			}
            case TORUS:
            {
                cJSON *torus = cJSON_CreateObject();
                add_torusToJSON(torus, element->object);
                add_commonProperties(torus, element);
                cJSON_AddItemToArray(torus, tori);
                break;
			}
            case MOEBIUS:
            {
                cJSON *moebius = cJSON_CreateObject();
                add_moebiusToJSON(moebius, element->object);
                add_commonProperties(moebius, element);
                cJSON_AddItemToArray(moebius, moebiuses);
                break;
			}
            default:
                break;
        }
        element = element->next;
    }
   manageArray(root, spheres, "spheres");
   manageArray(root, planes, "planes");
   manageArray(root, cylinders, "cylinders");
   manageArray(root, cones, "cones");
   manageArray(root, paraboloids, "paraboloids");
   manageArray(root, tori, "tori");
   manageArray(root, moebiuses, "moebius");
}

int   create_file(t_scene *scene, gchar *filename)
{
    cJSON *root = cJSON_CreateObject();

    add_cameras(root, scene->camera);
    
    if (scene->ambient.bright != 0.25 || scene->ambient.color.r != 255 ||
        scene->ambient.color.g != 255 || scene->ambient.color.b != 255)
        add_ambient(root, scene->ambient);
    
    if (scene->directional.declared)
        add_directional(root, scene->directional);
    if (scene->spotlight)
    
        add_spotlights(root, scene->spotlight);

    if (scene->obj)
        add_solids(root, scene->obj);    
    
    char *json_str = cJSON_Print(root);
    if (!json_str)
    {
        cJSON_Delete(root);
        return 1;
    }

    FILE *f = fopen(filename, "w");
    if (!f)
    {
        cJSON_free(json_str);
        cJSON_Delete(root);
        return 1;
    }
    fputs(json_str, f);
    fclose(f);

    cJSON_free(json_str);
    cJSON_Delete(root);
    return 0;
}
