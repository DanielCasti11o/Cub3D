/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by dacastil          #+#    #+#             */
/*   Updated: 2025/12/03 18:17:45 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (parse_game(&game, argc, argv) == 1)
		return (1);
	if (init_game(&game) == 1)
		return (free_end(&game), 1);
	free_end(&game);
	return (0);
}
