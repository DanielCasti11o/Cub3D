/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:15:31 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/06 20:41:38 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	perror_filename(void)
{
	write(2, "Error\nInvalid file name\n", 24);
	return (1);
}

int	perror_args(void)
{
	write(2, "Error\nInvalid number of arguments\n", 34);
	return (1);
}

int	perror_unexpectedchar(char unexpected)
{
	write(2, "Error\nUnexpected character in .cub file: ", 41);
	write(2, &unexpected, 1);
	write(2, "\n", 1);
	return (1);
}

int	perror_alreadydefined(t_elemfile elem)
{
	write(2, "Error\nElement redefinition in .cub file: ", 41);
	if (elem == E_NO)
		write(2, "NO\n", 3);
	else if (elem == E_SO)
		write(2, "SO\n", 3);
	else if (elem == E_WE)
		write(2, "WE\n", 3);
	else if (elem == E_EA)
		write(2, "EA\n", 3);
	else if (elem == E_F)
		write(2, "F\n", 2);
	else if (elem == E_C)
		write(2, "C\n", 2);
	else if (elem == E_MAP)
		write(2, "MAP\n", 4);
	return (1);
}

int	perror_overflow(void)
{
	write(2, "Error\nColor value must be between 0 and 255\n", 44);
	return (1);
}
