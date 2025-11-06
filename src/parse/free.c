/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:50:03 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/06 21:00:57 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_infile(t_game *game)
{
	if (game == NULL)
		return ;
	if (game->infile.no)
		ft_freestr(&game->infile.no);
	if (game->infile.so)
		ft_freestr(&game->infile.so);
	if (game->infile.we)
		ft_freestr(&game->infile.we);
	if (game->infile.ea)
		ft_freestr(&game->infile.ea);
}

void	free_parse(t_game *game, t_parse *parse)
{
	if (parse != NULL && parse->head_map)
	{
		ft_lstclear(&parse->head_map, free);
		parse->tail_map = NULL;
	}
	free_infile(game);
	if (game->pos.map.grid)
		ft_freestrarr(&game->pos.map.grid);
}
