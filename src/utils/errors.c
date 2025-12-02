/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:38:26 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/17 19:22:48 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>

int	perror_malloc(void)
{
	write(2, "Error\nMalloc error\n", 19);
	return (1);
}

int	perror_open(char *filename)
{
	write(2, "Error\nCould not open file: ", 27);
	perror(filename);
	return (1);
}

int	perror_gnl(char *filename)
{
	if (errno == 0)
		return (perror_malloc());
	write(2, "Error\nCould not read file: ", 27);
	perror(filename);
	return (1);
}

int	perror_texture(char *filename)
{
	if (errno == 0)
		return (perror_malloc());
	write(2, "Error\nCould not load texture: ", 30);
	perror(filename);
	return (1);
}
