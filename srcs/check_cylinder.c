/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:12:43 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:15:02 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	fill_cylinder_data(t_object *cylinder, char **elements)
{
	if (!update_tuple(&cylinder->position, elements[1], 1))
		return (0);
	if (!update_tuple(&cylinder->orientation, elements[2], 0))
		return (0);
	if (!is_valid_orientation_range(cylinder->orientation))
		return (error("Cylinder orientation isn't in a valid range."), 0);
	cylinder->orientation = normalize(cylinder->orientation);
	if (!is_valid_double(elements[3]) || !is_valid_double(elements[4]))
		return (error("Cy height/radius isn't a number."), 0);
	cylinder->radius = ft_atof(elements[3]) / 2;
	if (cylinder->radius < INT_MIN || cylinder->radius > INT_MAX)
		return (error("Radius overflow."), 0);
	cylinder->height = ft_atof(elements[4]);
	if (cylinder->height < INT_MIN || cylinder->height > INT_MAX)
		return (error("Height overflow."), 0);
	if (!update_color(&cylinder->color, elements[5]))
		return (0);
	return (1);
}

int	check_cylinder(char *line, t_object *cylinder, int *object_index)
{
	char	**elements;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (error("Split cylinder failed."), 0);
	if (ft_strcmp(elements[0], "cy") != 0)
		return (free_split(elements),
			error("Invalid cylinder identifier."), 0);
	if (count_line_tab(elements) != 6)
		return (free_split(elements),
			error("Nb of elements of cylinder isn't valid."), 0);
	if (!fill_cylinder_data(cylinder, elements))
		return (free_split(elements), 0);
	free_split(elements);
	cylinder->type = CYLINDER;
	*object_index += 1;
	return (1);
}
