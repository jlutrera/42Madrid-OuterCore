/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_moebius.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:41:49 by jutrera-          #+#    #+#             */
/*   Updated: 2025/05/02 19:41:49 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* https://www.shadertoy.com/view/4slSD8 */

#define STEPS      	    256 // más intentos para acotar raíz
#define FACTOR_WIDTH    10.0

static double sdf_moebius(t_vec p, t_moebius *mb) 
{
    double radius = mb->radius;
	double a = mb->width; //determina el ancho de la cinta.
    double b = a * FACTOR_WIDTH; //determina el grosor de la cinta.

    // Este valor lo dejo fijo para que salga siempre bien.
    // De otra manera, otros valores dan como resultado una cinta 
    // con solapamientos y deformaciones al intersectarse consigo misma.

    p = vec_div(p, radius);

	double x = p.x;
	double y = p.y;
	double z = p.z;
    double xx = x * x;
	double yy = y * y;
	double zz = z * z;
	double y3 = yy * y;
	double x3 = xx * x;
	double xy = xx + yy;
    double zxy = z * (3*xx*y - y3);
    double xyy = 3*x*yy - x3;

    double k1 = (2 * zxy + xyy * (xy - zz + 1)) * (b - a) - 2 * (b + a) * xy * xy;
    double k2 = 2 * b * a * xy + 2 * (b - a) * (zxy + xyy) - (b + a) * xy * (xy + zz + 1);

    double F = (k1*k1 - xy*k2*k2) * radius;

    return F;
}

static double compute_dt(double R, double width)
{
    const double eta = 0.2; // seguridad: 5 pasos por grosor
    double term1 = eta * width;
    double term2 = (M_PI * R) / WIDTH; // un pixel en la esfera circunscrita
    return fmax(term1, term2);
}

static double bisect_root(t_ray lr, t_moebius *mb, double t1, double t2)
{
    // Bisección del intervalo [t1, t2]
    double f1 = sdf_moebius(ray_at(lr, t1), mb);
    double f2 = sdf_moebius(ray_at(lr, t2), mb);
    double tm;

    for (int i = 0; i < 64; ++i) 
	{
        tm = 0.5 * (t1 + t2);
        double fm = sdf_moebius(ray_at(lr, tm), mb);

        // criterio de parada: intervalo pequeño o |F| pequeño
        if (fabs(t2 - t1) < 1e-12 || fabs(fm) < 1e-12) 
		{
			return tm;
		}

        // mantiene el cambio de signo en [t1,t2]
        if ((f1 < 0.0 && fm > 0.0) || (f1 > 0.0 && fm < 0.0))
		{
            t2 = tm;
            f2 = fm;
		}
		else
        {
			t1 = tm;
            f1 = fm;
		}
    }

    return tm;
}

static void narrow_interval(t_ray lr, t_moebius *mb, double *t1, double *t2)
{
    double width = mb->width * FACTOR_WIDTH;
    double dt = compute_dt(mb->radius, width);

    t_vec p1 = ray_at(lr, *t1);
    double f1 = sdf_moebius(p1, mb);
    int bracketed = 0;

    // Acotar t1 y t2 con cambio de signo
    for (int i = 0; i < STEPS; ++i)
	{
        if (f1 == 0.0) 
		{ 
			bracketed = 1; 
			*t2 = *t1; 
			break;
		}

        *t2 = *t1 + fmax(fabs(f1), dt);
        t_vec p2 = ray_at(lr, *t2);
        double f2 = sdf_moebius(p2, mb);
		if ((f1 < 0.0 && f2 > 0.0) || (f1 > 0.0 && f2 < 0.0)) 
		{ 
			bracketed = 1; 
			break;
		}

        *t1 = *t2;
        f1 = f2;
    }

    if (bracketed == 0)
        *t1 = *t2 = -1; // no se ha encontrado raíz
}

static t_vec mobius_gradient(t_vec p, t_moebius *mb) 
{
    double  width = mb->width * FACTOR_WIDTH;
    double scale = fmax(mb->width + width, 1.0);
	double h = fmax(EPSILON, 1e-4 * scale);

	t_vec ex = vec(h,0,0);
	t_vec ey = vec(0,h,0);
	t_vec ez = vec(0,0,h);

    double fx = sdf_moebius(vec_add(p, ex), mb) - sdf_moebius(vec_sub(p, ex), mb);
    double fy = sdf_moebius(vec_add(p, ey), mb) - sdf_moebius(vec_sub(p, ey), mb);
    double fz = sdf_moebius(vec_add(p, ez), mb) - sdf_moebius(vec_sub(p, ez), mb);

    return vec(fx/(2*h), fy/(2*h), fz/(2*h));
}

void intersect_moebius(t_ray ray, t_moebius *mb, t_point2 *t_out)
{
    t_ray lr;
    lr.origin = point_to_local(ray.origin, mb->center, mb->basis);
    lr.dir    = dir_to_local(ray.dir, mb->basis);
 
    double t1 = 0.0;
    double t2 = 0.0;
    narrow_interval(lr, mb, &t1, &t2);
    if (t1 < 0.0 || t2 < 0.0)
    {
        *t_out = point2(INFINITY, INFINITY);
        return;
    }

    double t_hit = bisect_root(lr, mb, t1, t2);

    if (t_hit <= 0.0)
	{ 
		*t_out = point2(INFINITY, INFINITY);
	}
    else
        *t_out = point2(t_hit, t_hit);
}

t_vec get_moebius_normal(t_moebius *mb, t_ray ray, double t_hit)
{
    t_ray lr;
    lr.origin = point_to_local(ray.origin, mb->center, mb->basis);
    lr.dir    = dir_to_local(ray.dir, mb->basis);

    t_vec p_local = ray_at(lr, t_hit);
    t_vec n_local = mobius_gradient(p_local, mb);

    // Lleva la normal a global (solo rotación) y oriéntala contra el rayo (faceforward)
    t_vec n_global = dir_to_global(n_local, mb->basis);
    
    if (vec_dot(n_global, ray.dir) > 0.0) 
		n_global = vec_mul(n_global, -1.0);

    return n_global;
}
