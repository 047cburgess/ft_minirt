/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:31:14 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:20:27 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_tuple	calc_ray_dir(t_cam *cam, t_local basis, int col, int row);

// Sends a ray to each pixel of the screen to determine its colour
int	render_image(t_scene *scene)
{
	t_ray	ray;
	t_tuple	ray_direction;
	int		col;
	int		row;
	int		color;

	setup_cam(&scene->camera);
	row = 0;
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			ray_direction = calc_ray_dir(&scene->camera, scene->camera.basis,
					col, row);
			ray = new_ray(scene->camera.position, ray_direction);
			color = get_pixel_color(scene, ray, scene->objects);
			my_mlx_pixel_put(scene, col, row, color);
			col++;
		}
		row++;
	}
	return (0);
}

// Moves the ray direction to the correct pixel location
// Normalised pixel coordinates between -1 and 1
static	t_tuple	calc_ray_dir(t_cam *cam, t_local basis, int col, int row)
{
	double	normalised_col;
	double	normalised_row;
	t_tuple	offset;

	normalised_col = -((double)col / (double)W_WIDTH * 2 - 1);
	normalised_row = -((double)row / (double)W_HEIGHT * 2 - 1);
	offset = get_cam_offset(cam, basis, normalised_row, normalised_col);
	return (normalize(add(offset, cam->orientation)));
}

// Finds whats colour the pixel should be
// based on what the ray hits first
int	get_pixel_color(t_scene *scene, t_ray ray, t_object *objects)
{
	int		final_color;
	t_xs	closest_intersection;

	final_color = 0;
	closest_intersection = get_closest_intersection(scene, ray, objects);
	if (closest_intersection.hit_distance < 0)
		return (0);
	apply_lighting(scene, &closest_intersection, &final_color);
	return (final_color);
}

void	my_mlx_pixel_put(t_scene *map, int x, int y, int colour)
{
	char	*dst;

	if ((x >= 0 && x < W_WIDTH) && (y >= 0 && y < W_HEIGHT))
	{
		dst = map->addr + (y * map->l_l + x * (map->bpp / 8));
		*(unsigned int *)dst = colour;
	}
}
