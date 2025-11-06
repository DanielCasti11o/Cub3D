/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:43:58 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/06 20:44:05 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	perror_unclosedmap(void)
{
	write(2, "Error\nMap is not closed/surrounded by walls\n", 44);
	return (1);
}
