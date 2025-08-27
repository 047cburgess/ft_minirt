/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:11:27 by caburges          #+#    #+#             */
/*   Updated: 2025/05/16 12:11:29 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// adjusts camera settings based upon pixel location, aspect ratio and scale
t_tuple	get_cam_offset(t_cam *cam, t_local cam_basis, double row, double col)
{
	t_tuple	right;
	t_tuple	up;
	t_tuple	combined_offset;

	right = scale(cam_basis.right, col * cam->aspect_ratio * cam->fov_scale);
	up = scale(cam_basis.up, row * cam->fov_scale);
	combined_offset = add(right, up);
	return (combined_offset);
}

// Caculates the camera up, right, with forward as a base reference
void	setup_cam(t_cam *cam)
{
	cam->basis.forward = vector(0, 1, 0);
	if (fabs(cam->orientation.x) < EPSILON && fabs(cam->orientation.z) < EPSILON)
			cam->basis.forward = vector(0, 0, 1);
	cam->basis.right = normalize(cross(cam->orientation, cam->basis.forward));
	cam->basis.up = normalize(cross(cam->basis.right, cam->orientation));
}
