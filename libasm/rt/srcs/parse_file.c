/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:21:04 by jutrera-          #+#    #+#             */
/*   Updated: 2025/04/12 18:21:04 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_file_extension(const char *filename)
{
	const char	*dot;

	dot = strrchr(filename, '.');
	if (dot && !strcmp(dot, ".rt"))
		return (SUCCESS);
	return EXTENSION_E;
}

static char *read_file_content(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
		return NULL;

	fseek(file, 0, SEEK_END);
	long len = ftell(file);
	rewind(file);

	char *data = malloc(len + 1);
	if (!data)
	{
		fclose(file);
		return NULL;
	}
	fread(data, 1, len, file);
	data[len] = '\0';
	fclose(file);
	return data;
}

static char *remove_comments(const char *input) 
{
    size_t len = strlen(input);
    char *output = malloc(len + 1);
    if (!output) return NULL;

    const char *src = input;
    char *dst = output;
    int in_string = 0;

    while (*src) {
        if (*src == '"' && (src == input || src[-1] != '\\')) {
            in_string = !in_string; // toggle inside string
            *dst++ = *src++;
        }
        else if (!in_string && *src == '#') {
            while (*src && *src != '\n')
                src++;
            if (*src == '\n') // preserve line break
                *dst++ = *src++;
        }
        else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    return output;
}


static bool brackets_are_balanced(const char *json)
{
    int curly = 0, square = 0;
    bool in_string = false;

    for (const char *p = json; *p; p++)
	{
        // Detectar comillas (evitar escapar comillas con \")
        if (*p == '"' && (p == json || *(p - 1) != '\\'))
            in_string = !in_string;

        if (in_string) continue;

        // Contar llaves y corchetes
        if (*p == '{') 
			curly++;
        else if (*p == '}')
			curly--;
        else if (*p == '[')
			square++;
        else if (*p == ']')
			square--;

        // Error: cierre sin apertura
        if (curly < 0 || square < 0)
            return false;
    }

    // Comprobación final
    return curly == 0 && square == 0;
}

static int get_error_line_number(const char *clean_data, const char *error_ptr)
{
	// Retroceder si el error apunta a un salto de línea o espacio
	const char *adjusted_ptr = error_ptr;

	// Retroceder hasta el último carácter no vacío antes del error
	const char *whitespace = " \t\r\n";
	while (adjusted_ptr > clean_data &&
			(strchr(whitespace, *adjusted_ptr) || strchr(whitespace, *(adjusted_ptr - 1))))
		adjusted_ptr--;
	
    // Contar líneas hasta el puntero ajustado
    int line_num = 1;
    for (const char *p = clean_data; p < adjusted_ptr; p++)
	{
        if (*p == '\n')
            line_num++;
    }

    return (line_num);
}

int parse_file(char *filename, t_scene *scene, t_context *ctx)
{
	if (check_file_extension(filename) == EXTENSION_E)
		return EXTENSION_E;

	char *raw_data = read_file_content(filename);
	if (!raw_data)
		return FILE_E;

	char *clean_data = remove_comments(raw_data);
	free(raw_data);
	if (!clean_data)
		return MEMORY_E;

	if (!brackets_are_balanced(clean_data))
	{
		free(clean_data);
		return BRACKETS_E;
    }

	const char *error_ptr = NULL;
	cJSON *json = cJSON_ParseWithOpts(clean_data, &error_ptr, 0);
	if (!json)
	{
		int line_error = get_error_line_number(clean_data, error_ptr);
		set_status_label(ctx->status_label, "Syntax error near line %d", line_error);
		free(clean_data);
        return UNKNOWN;
	}

	free(clean_data);
	int error = parse_cameras(scene, json);

	if (error == SUCCESS)
		error = parse_lights(scene, json);

	if (error == SUCCESS)
		error = parse_objects(scene, json);

	if(error == SUCCESS)
		error = parse_library(scene, json);

	if (error == SUCCESS)
		error = parse_instances(scene, json);

	
	cJSON_Delete(json);
	return (error);
}

