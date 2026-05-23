/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_reflection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:04:50 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/25 15:04:50 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_point3 compute_reflection_color(t_vec ray_dir, t_vec n, t_vec p, t_scene *scene,
	double n1, int depth_r, int depth_t, double reflectivity)
{
	t_vec reflected_dir = vec_unit(vec_sub(ray_dir, vec_mul(n, 2 * vec_dot(ray_dir, n))));
	t_vec offset_p = vec_add(p, vec_mul(reflected_dir, EPSILON));
	t_ray reflected_ray = construct_ray(offset_p, reflected_dir);
	t_point3 reflected = trace_ray(reflected_ray, scene, n1, depth_r + 1, depth_t);
	return point3(	reflected.x * reflectivity,
					reflected.y * reflectivity,
					reflected.z * reflectivity);
}

t_point3 compute_refraction_color(t_vec i, t_vec n, t_vec p, t_scene *scene,
	double n1, int depth_r, int depth_t, t_lst_obj	*closest_obj)
{
	double transparency = closest_obj->transparency;
	double n2 = closest_obj->ior;
	double eta = n1 / n2;
	t_vec normal;
	
	double cos_theta1 = vec_dot(i, n);
	if (cos_theta1 < 0) // Entrando en el objeto
	{
		n2 = closest_obj->ior;
		normal = vec_mul(n, -1);
		eta = n1 / n2;
		cos_theta1 = -cos_theta1;
	}
	else // Saliendo del objeto
    {
		n2 = 1.0;
		normal = n;
		eta = n2 / n1;
	}
	
	double k = 1.0 - eta * eta * (1.0 - cos_theta1 * cos_theta1);
	if (k < 0.0)
		return point3(0, 0, 0); // reflexión interna total

	t_vec dir1 = vec_mul(i, eta);
	t_vec dir2 = vec_mul(normal, eta * cos_theta1 - sqrt(k));
	t_vec refracted_dir = vec_add(dir1, dir2);
	t_vec p_offset = vec_add(p, vec_mul(refracted_dir, EPSILON));
	t_ray refracted_ray = construct_secondary_ray(p_offset, vec_unit(refracted_dir), closest_obj->object);
	t_point3 refracted_color = trace_ray(refracted_ray, scene, n2, depth_r, depth_t + 1);
	return point3(	refracted_color.x * transparency,
					refracted_color.y * transparency,
					refracted_color.z * transparency);
}