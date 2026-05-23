/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:43:22 by jutrera           #+#    #+#             */
/*   Updated: 2025/08/13 20:43:28 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int bad_direction(t_vec d)
{
    return (d.x == 0 && d.y == 0 && d.z == 0);
}

int bad_norm(t_vec d)
{
    return (d.x < -1 || d.x > 1 ||
            d.y < -1 || d.y > 1 ||
            d.z < -1 || d.z > 1 );   
}

int bad_ratio(double r, double min, double max)
{
    return (r > max || r < min);
}

int bad_color(t_color c)
{
    return (c.r < 0 || c.r > 255 ||
            c.g < 0 || c.g > 255 ||
            c.b < 0 || c.b > 255);
}
