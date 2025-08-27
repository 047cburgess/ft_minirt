/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:06:21 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:15:52 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Function for check if the extension is terminate by .rt
int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3 || file[len - 3] != '.'
		|| file[len - 2] != 'r' || file[len - 1] != 't')
	{
		error("File extension isn't valid.");
		return (0);
	}
	return (1);
}

int	check_overflow(t_tuple *tuple)
{
	if (tuple->x < INT_MIN || tuple->x > INT_MAX)
		return (0);
	if (tuple->y < INT_MIN || tuple->y > INT_MAX)
		return (0);
	if (tuple->z < INT_MIN || tuple->z > INT_MAX)
		return (0);
	return (1);
}

void	error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
}
