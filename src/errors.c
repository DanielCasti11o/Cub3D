/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:38:26 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/21 18:06:29 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	perror_malloc(void)
{
	write(2, "Error\nMalloc error\n", 19);
	return (1);
}

int	perror_args(void)
{
	write(2, "Error\nInvalid number of arguments\n", 34);
	return (1);
}

int	perror_filename(void)
{
	write(2, "Error\nInvalid file name\n", 24);
	return (1);
}

int	perror_open(char *filename)
{
	write(2, "Error\nCould not open file: ", 27);
	perror(filename);
	return (1);
}
