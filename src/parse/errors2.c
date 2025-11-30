/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:40:31 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/30 01:02:47 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	perror_missingelements(uint8_t seen)
{
	write(2, "Error\nMissing mandatory elements in .cub file:", 46);
	if ((seen & E_NO) == 0)
		write(2, " NO", 3);
	if ((seen & E_SO) == 0)
		write(2, " SO", 3);
	if ((seen & E_WE) == 0)
		write(2, " WE", 3);
	if ((seen & E_EA) == 0)
		write(2, " EA", 3);
	if ((seen & E_F) == 0)
		write(2, " F", 2);
	if ((seen & E_C) == 0)
		write(2, " C", 2);
	if ((seen & E_MAP) == 0)
		write(2, " MAP", 4);
	write(2, "\n", 1);
	return (1);
}

int	perror_emptylineinmap(void)
{
	write(2, "Error\nEmpty line found in map definition\n", 41);
	return (1);
}

int	perror_emptyarg(t_elemfile elem)
{
	write(2, "Error\nEmpty argument for element in .cub file: ", 47);
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
	else if (elem == E_DO)
		write(2, "DO\n", 3);
	return (1);
}

int	perror_noplayerstart(void)
{
	write(2, "Error\nNo player start position in map\n", 38);
	return (1);
}

int	perror_multipleplayerstart(void)
{
	write(2, "Error\nMultiple player start positions in map\n", 45);
	return (1);
}
