/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:56:04 by jutrera-          #+#    #+#             */
/*   Updated: 2025/08/22 17:32:24 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// Error messages
# define    UNKNOWN		 -1
# define    SUCCESS 	 0
# define    AMBIENT_E    1
# define    AMBI_BR_E    25
# define    ANY_CAM_E    2
# define    ARGC_E       3
# define    BRACKETS_E   4
# define    BRIGHT_E     5
# define    COLOR_E      6
# define    DIR_E        7
# define    DIRECT_E     8
# define    EXTENSION_E  9
# define    FIELD_E      10
# define    FILE_E       11
# define    FOV_E        12
# define    IOR_E        13
# define    JSON_E       14
# define    MEMORY_E     15
# define    MLX_E        16
# define    NEGATIVE_E   17
# define    NORM_E       18
# define    NO_SCENE_E   19
# define    POINT_E      20
# define    SHINE_E      21
# define    TEXTURE_E    22
# define    TRANSP_E     23
# define    VALUE_E      24


// Main window, dimensions and aspect ratio
# define 	WIDTH 		800
# define 	ASPECTRATIO	(16.0 / 9.0)

// Accuracy and limits
# define 	EPSILON 	    1.0E-6
# define    MAX_THREADS 	20  // Maximum number of threads
# define    MAX_REFL_DEPTH  1   // Maximum depth of reflection
# define    MAX_REFR_DEPTH  5   // Maximum depth of refraction

#endif
