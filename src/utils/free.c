/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:50:03 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/03 17:53:21 by dacastil         ###   ########.fr       */
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
	if (game->infile.door)
		ft_freestr(&game->infile.door);
}

void	ft_destroy_image(t_game *game, t_buf *image)
{
	if (game == NULL || image == NULL)
		return ;
	if (game->mlx && image->ptr)
		mlx_destroy_image(game->mlx, image->ptr);
	image->ptr = NULL;
	image->addr = NULL;
}

void	free_end(t_game *game)
{
	if (game == NULL)
		return ;
	free_infile(game);
	if (game->map.grid)
		ft_freestrarr(&game->map.grid);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	ft_destroy_image(game, &game->img);
	ft_destroy_image(game, &game->map.tex.no);
	ft_destroy_image(game, &game->map.tex.so);
	ft_destroy_image(game, &game->map.tex.we);
	ft_destroy_image(game, &game->map.tex.ea);
	ft_destroy_image(game, &game->map.tex.door);
	while (game->map.tex.vm.frame_count-- > 0)
		ft_destroy_image(game,
			&game->map.tex.vm.frames[game->map.tex.vm.frame_count]);
	if (game->map.tex.vm.frames)
		ft_free((void **)&game->map.tex.vm.frames);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		ft_free((void **)&game->mlx);
	}
}

void	free_parse(t_game *game, t_parse *parse)
{
	if (parse != NULL && parse->head_map)
	{
		ft_lstclear(&parse->head_map, free);
		parse->tail_map = NULL;
	}
	free_infile(game);
	if (game->map.grid)
		ft_freestrarr(&game->map.grid);
}
