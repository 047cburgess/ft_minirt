/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:37:58 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 14:35:06 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_ambient(char *line, t_scene *scene)
{
	char	**elements;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (error("Split ambient failed."), 0);
	if (ft_strcmp(elements[0], "A") != 0)
		return (free_split(elements),
			error("Invalid ambient identifier."), 0);
	if (count_line_tab(elements) != 3)
		return (free_split(elements),
			error("Invalid number of elements."), 0);
	if (!is_valid_double(elements[1]))
		return (free_split(elements),
			error("Isn't a number."), 0);
	scene->ambient.ratio = ft_atof(elements[1]);
	if (!update_color(&scene->ambient.color, elements[2]))
		return (free_split(elements), 0);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (free_split(elements),
			error("Ambient ratio isn't valid."), 0);
	free_split(elements);
	return (1);
}

static int	check_camera(char *line, t_scene *scene)
{
	char	**elements;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (error("Split camera failed."), 0);
	if (ft_strcmp(elements[0], "C") != 0)
		return (free_split(elements), error("Invalid cam identifier."), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements),
			error("Invalid number of cam elements."), 0);
	if (!update_tuple(&scene->camera.position, elements[1], 1))
		return (free_split(elements), 0);
	if (!update_tuple(&scene->camera.orientation, elements[2], 0))
		return (free_split(elements), 0);
	if (!is_valid_orientation_range(scene->camera.orientation))
		return (free_split(elements), error("Cam orientation isn't valid."), 0);
	if (!is_valid_int(elements[3]))
		return (free_split(elements), error("Cam fov isn't a number."), 0);
	scene->camera.fov = ft_atoi(elements[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (free_split(elements),
			error("Cam fov isn't in a valid range."), 0);
	free_split(elements);
	return (1);
}

static int	check_light(char *line, t_scene *scene)
{
	char	**elements;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (error("Split light failed."), 0);
	if (ft_strcmp(elements[0], "L") != 0)
		return (free_split(elements), error("Invalid light identifier"), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements),
			error("Invalid number of light elements."), 0);
	if (!update_tuple(&scene->light.position, elements[1], 1))
		return (free_split(elements), 0);
	if (!is_valid_double(elements[2]))
		return (free_split(elements),
			error("Light ratio isn't a number."), 0);
	scene->light.ratio = ft_atof(elements[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		return (free_split(elements),
			error("Light ratio isn't in a valid range."), 0);
	if (!update_color(&scene->light.color, elements[3]))
		return (free_split(elements), 0);
	free_split(elements);
	scene->light.coeff = 0.7;
	scene->light.shine = 100.0;
	return (1);
}

static int	parse_objs(char *line, t_scene *scene, int *obj_index)
{
	if (ft_strncmp(line, "sp", 2) == 0)
		return (check_sphere(line, &scene->objects[*obj_index], obj_index));
	else if (ft_strncmp(line, "pl", 2) == 0)
		return (check_plane(line, &scene->objects[*obj_index], obj_index));
	else if (ft_strncmp(line, "cy", 2) == 0)
		return (check_cylinder(line, &scene->objects[*obj_index], obj_index));
	return (0);
}

// //Function for parse elements of type line by line
int	parse_element_line(char *line, t_scene *scene, int *obj_index)
{
	if (ft_strncmp(line, "A", 1) == 0)
	{
		if (!check_ambient(line, scene))
			return (0);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (!check_camera(line, scene))
			return (0);
	}
	else if (ft_strncmp(line, "L", 1) == 0)
	{
		if (!check_light(line, scene))
			return (0);
	}
	else if (ft_strncmp(line, "sp", 2) == 0 || ft_strncmp(line, "pl", 2) == 0
		|| ft_strncmp(line, "cy", 2) == 0)
	{
		if (!parse_objs(line, scene, obj_index))
			return (0);
	}
	else
		return (0);
	return (1);
}
