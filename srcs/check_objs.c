/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:53:43 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:13:20 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	update_color(t_color *color, char *line)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (error("Split color failed."), 0);
	if (count_line_tab(rgb) != 3)
		return (free_split(rgb),
			error("Nb of color elements isn't valid."), 0);
	if (!is_valid_int(rgb[0]) || !is_valid_int(rgb[1]) || !is_valid_int(rgb[2]))
		return (free_split(rgb), error("Color isn't a valid number."), 0);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if ((color->r < 0 || color->r > 255) || (color->g < 0 || color->r > 255)
		|| (color->b < 0 || color->b > 255))
		return (free_split(rgb),
			error("Color isn't valid number."), 0);
	color->r /= (double)255.0;
	color->g /= (double)255.0;
	color->b /= (double)255.0;
	free_split(rgb);
	return (1);
}

// need to check for overflow
int	update_tuple(t_tuple *tuple, char *line, double w)
{
	char	**coords;

	coords = ft_split(line, ',');
	if (!coords)
		return (error("Split vector failed."), 0);
	if (count_line_tab(coords) != 3)
		return (free_split(coords),
			error("Invalid number of elements."), 0);
	if (!is_valid_double(coords[0]) || !is_valid_double(coords[1])
		|| !is_valid_double(coords[2]))
		return (free_split(coords),
			error("Isn't a valid number."), 0);
	tuple->x = ft_atof(coords[0]);
	tuple->y = ft_atof(coords[1]);
	tuple->z = ft_atof(coords[2]);
	tuple->w = w;
	if (!check_overflow(tuple))
	{
		error("Position overflow.");
		free_split(coords);
		return (0);
	}
	free_split(coords);
	return (1);
}

int	check_sphere(char *line, t_object *sphere, int *object_index)
{
	char	**elements;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (error("Split sphere failed."), 0);
	if (ft_strcmp(elements[0], "sp") != 0)
		return (free_split(elements), error("Invalid cam identifier."), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements),
			error("Invalid number of sphere elements."), 0);
	if (!update_tuple(&sphere->position, elements[1], 1))
		return (free_split(elements), 0);
	if (!is_valid_double(elements[2]))
		return (free_split(elements), error("Isn't a valid number."), 0);
	sphere->radius = ft_atof(elements[2]) / 2;
	if (sphere->radius < INT_MIN || sphere->radius > INT_MAX)
		return (free_split(elements), error("Radius overflow."), 0);
	if (!update_color(&sphere->color, elements[3]))
		return (free_split(elements), 0);
	free_split(elements);
	sphere->type = SPHERE;
	*object_index += 1;
	return (1);
}

int	check_plane(char *line, t_object *plane, int *object_index)
{
	char	**elements;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (error("Split plane failed."), 0);
	if (ft_strcmp(elements[0], "pl") != 0)
		return (free_split(elements), error("Invalid plane identifier."), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements),
			error("Nb of elements of plane isn't valid."), 0);
	if (!update_tuple(&plane->position, elements[1], 1))
		return (free_split(elements), 0);
	if (!update_tuple(&plane->normal, elements[2], 0))
		return (free_split(elements), 0);
	if (!is_valid_orientation_range(plane->normal))
		return (free_split(elements),
			error("Plane orientation isn't in a valid range."), 0);
	if (!update_color(&plane->color, elements[3]))
		return (free_split(elements), 0);
	free_split(elements);
	plane->type = PLANE;
	*object_index += 1;
	return (1);
}
