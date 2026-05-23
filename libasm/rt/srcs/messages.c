/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera <jutrera@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:34:23 by jutrera-          #+#    #+#             */
/*   Updated: 2025/08/22 13:57:59 by jutrera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char *err_msg(int e)
{
	switch (e)
	{
		case AMBIENT_E	: return ("Error: Only one \"ambient\" light field allowed");
		case AMBI_BR_E	: return ("Error: Ambient brightness must be between 0.25 and 1");
		case ANY_CAM_E	: return ("Error: The \"cameras\" field is not declared");
		case BRACKETS_E : return ("Error: Missing brackets");
		case BRIGHT_E	: return ("Error: Brightness must be between 0 and 1");
		case COLOR_E	: return ("Error: Invalid color value");
		case DIR_E 		: return ("Error: Invalid direction vector");
		case DIRECT_E	: return ("Error: Only one \"directional\" light field allowed");
		case EXTENSION_E: return ("Error: The file must have a .rt file extension");
		case FIELD_E 	: return ("Error: Missing required fields");
		case FILE_E		: return ("Error: Cannot open file");
		case FOV_E 		: return ("Error: FOV must be between 0 and 180");
		case IOR_E		: return ("Error: Refraction index must be between 1 and 5");
		case JSON_E 	: return ("Error: Syntax error");
		case MEMORY_E 	: return ("Error: Memory error");
		case NEGATIVE_E : return ("Error: Invalid value. It must be greater than zero.");
		case NORM_E 	: return ("Error: Vectors must be normalized to [0,1]");
		case NO_SCENE_E : return ("Error: No scene found");
		case POINT_E	: return ("Error: Invalid coordinates");
		case SHINE_E	: return ("Error: Shininess must be between 10 and 1000");
		case TEXTURE_E	: return ("Error: Invalid texture file or not found");
		case TRANSP_E   : return ("Error: Transparency must be between 0 and 1");
		case VALUE_E	: return ("Error: Invalid number");

		default: return ("Unknown error");
	}
}

void set_status_label(GtkWidget *status_label, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // g_strdup_vprintf crea un string con el formato (similar a sprintf)
    char *msg = g_strdup_vprintf(format, args);

    va_end(args);

    gtk_label_set_text(GTK_LABEL(status_label), msg);

    g_free(msg);
}
