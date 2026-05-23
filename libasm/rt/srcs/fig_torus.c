/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_torus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:52:26 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/21 10:52:26 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// ******************* RESOLVER ECUACIÓN CUÁRTICA *********
// ********************* método Durand-Kerner *************
static int solve_quartic(double b, double c, double d, double e, double roots[4])
{
	const int MAX_ITERS = 20;
    double complex zs[4] = {
        1.0 + 0.0 * I,
        0.0 + 1.0 * I,
       -1.0 + 0.0 * I,
        0.0 - 1.0 * I
    };

    for (int iter = 0; iter < MAX_ITERS; ++iter)
    {
        int converged = 1;
        for (int i = 0; i < 4; ++i)
        {
            double complex zi = zs[i];
            double complex f = cpow(zi, 4) + b * cpow(zi, 3) + c * cpow(zi, 2) + d * zi + e;

            double complex denom = 1.0;
            for (int j = 0; j < 4; ++j)
                if (j != i)
                    denom *= (zi - zs[j]);

            double complex delta = f / denom;
            zs[i] -= delta;

            if (cabs(delta) > EPSILON)
                converged = 0;
        }
        if (converged)
            break;
    }

    int n_roots = 0;
    for (int i = 0; i < 4; ++i)
    {
        double re = creal(zs[i]);
        double im = cimag(zs[i]);
        if (fabs(im) < EPSILON && re > EPSILON)
        {
            roots[n_roots++] = re;
        }
    }
    return n_roots;
}

// Función para obtener coeficientes cuárticos (torus centrado en (0,0,0), eje Z):
static void compute_torus_coeffs(t_ray ray, double R, double r, double *coeffs)
{
	t_vec o = ray.origin;
	t_vec d = ray.dir;

	double H = 2 * vec_dot(o, d);
	double M = vec_dot(o, o) + R * R - r * r;

	double J = o.x * o.x + o.y * o.y;
	double K = d.x * d.x + d.y * d.y;
	double L = o.x * d.x + o.y * d.y;

	coeffs[0] = 2 * H;
	coeffs[1] = 2 * M + H * H - 4 * R * R * K;
	coeffs[2] = 2 * H * M - 8 * R * R * L;
	coeffs[3] = M * M - 4 * R * R * J;
}

// Función para seleccionar la raíz positiva más pequeña
static t_point2 select_t_hit(int n_cuartic, double *roots)
{
	double t_min = INFINITY;
	for (int i = 0; i < n_cuartic; ++i)
	{
		if (roots[i] < t_min)
			t_min = roots[i];
	}
	return point2(t_min, t_min);
}

static t_vec torus_gradient(t_vec p, double R, double r)
{
	double factor = 4 * (p.x * p.x + p.y * p.y + p.z * p.z + R * R - r * r);

	double dx = p.x * factor - 8 * R * R * p.x;
	double dy = p.y * factor - 8 * R * R * p.y;
	double dz = p.z * factor;

	return (vec(dx, dy, dz));
}

void intersect_to(t_ray ray, t_torus *to, t_point2 *t_out)
{
	// Paso 1: transformar el rayo a coordenadas locales del toroide
	// (de esta forma el toroide estará centrado en el origen y alineado con el eje Z)
	t_ray local_ray;
	local_ray.origin = point_to_local(ray.origin, to->center, to->basis);
	local_ray.dir = dir_to_local(ray.dir, to->basis);

	// Paso 2: calcular coeficientes de la ecuación cuártica
	double coeffs[4];
	compute_torus_coeffs(local_ray, to->r_max, to->r_min, coeffs);

	// Paso 3: resolver cuártica usando el método Durand-Kerner
	double roots[4];
	int n_cuartic = solve_quartic(coeffs[0], coeffs[1], coeffs[2], coeffs[3], roots);

	// Paso 4: Devolver el menor valor positivo
	*t_out = select_t_hit(n_cuartic, roots);
}

t_vec get_torus_normal(t_torus *to, t_ray ray, double t_hit)
{
	t_ray local_ray;
	local_ray.origin = point_to_local(ray.origin, to->center, to->basis);
	local_ray.dir = dir_to_local(ray.dir, to->basis);
	
	t_vec p_local = ray_at(local_ray, t_hit);
	t_vec n_local = torus_gradient(p_local, to->r_max, to->r_min);
	
	t_vec n_global = dir_to_global(n_local, to->basis);
	
	return n_global;
}

