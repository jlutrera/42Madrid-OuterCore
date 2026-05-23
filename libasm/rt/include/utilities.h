/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:41:25 by jutrera-          #+#    #+#             */
/*   Updated: 2025/08/31 21:33:03 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_UTILS_H
# define VEC_UTILS_H

# include "structs.h"

/*                            static inline functions 
¿Por qué inline?
  - Evitas el overhead de la llamada a función, que aunque es pequeño, se nota cuando 
	haces millones de llamadas por píxel.
  - Mejoras el rendimiento sin sacrificar la legibilidad modular del código.
  - Dejas que el compilador decida si en realidad conviene expandirla,
	así que es una "sugerencia" más que una obligación.
*/

static inline t_color color_rgb(double r, double g, double b)
{
	return (t_color){(int)(r  * 255.0 + 0.5),
		 			 (int)(g  * 255.0 + 0.5),
		 			 (int)(b  * 255.0 + 0.5)};
}

static inline t_vec	vec(double x, double y, double z)
{
	return (t_vec){x, y, z};
}

static inline t_point3	point3(double x, double y, double z)
{
	return (t_point3){x, y, z};
}

static inline t_point2	point2(double x, double y)
{
	return (t_point2){x, y};
}

static inline t_vec	vec_add(t_vec v1, t_vec v2)
{
	return (t_vec){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

static inline t_vec	vec_sub(t_vec v1, t_vec v2)
{
	return (t_vec){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

static inline t_vec	vec_mul(t_vec v, double t)
{
	return (t_vec){v.x * t, v.y * t, v.z * t};
}

static inline t_vec	vec_div(t_vec v, double t)
{
	return (t_vec){v.x / t, v.y / t, v.z / t};
}

static inline t_vec	vec_cross(t_vec v1, t_vec v2)
{
	return (t_vec){ v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x};
}

static inline double vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

static inline double vec_length(t_vec v)
{
	double	l;

	l = vec_dot(v, v);
	return (sqrt(l));
}

static inline t_vec	vec_unit(t_vec v)
{
	double	len;

	len = vec_length(v);
	if (len < EPSILON)
		return (v);

	return (t_vec){v.x / len, v.y / len, v.z /len};
}

static inline t_vec point_to_local(t_vec p, t_vec center, t_localbase base)
{
    t_vec p_local = vec_sub(p, center);

    return vec(vec_dot(p_local, base.u),
               vec_dot(p_local, base.v),
               vec_dot(p_local, base.w));
}

static inline t_vec dir_to_local(t_vec d, t_localbase base)
{
    t_vec v = vec(vec_dot(d, base.u),
                  vec_dot(d, base.v),
                  vec_dot(d, base.w));

    return vec_unit(v);
}

static inline t_vec dir_to_global(t_vec d, t_localbase base) 
{
    t_vec x = vec_mul(base.u, d.x);
    t_vec y = vec_mul(base.v, d.y);
    t_vec z = vec_mul(base.w, d.z);
    t_vec v = vec_add(vec_add(x,y), z);

    return vec_unit(v);
}

#endif