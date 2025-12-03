/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:33:59 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/02 21:16:12 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_vm_path(int frame_index)
{
	char	*num;
	char	*xpm;
	char	*path;

	num = ft_itoa(frame_index);
	if (num == NULL)
		return (NULL);
	xpm = ft_strjoin(num, ".xpm");
	free(num);
	if (xpm == NULL)
		return (NULL);
	path = ft_strjoin(VM_FILEBASE, xpm);
	free(xpm);
	if (path == NULL)
		return (NULL);
	return (path);
}

int	init_vm_frames(t_game *game)
{
	char	*path;

	game->map.tex.vm.frame_count = 0;
	if (VM_COUNT == 0)
		return (0);
	game->map.tex.vm.frames = malloc(sizeof(t_buf) * VM_COUNT);
	if (game->map.tex.vm.frames == NULL)
		return (perror_malloc());
	while (game->map.tex.vm.frame_count < VM_COUNT)
	{
		path = get_vm_path(game->map.tex.vm.frame_count + 1);
		if (path == NULL)
			return (perror_malloc());
		if (init_image_path(game,
				&game->map.tex.vm.frames[game->map.tex.vm.frame_count],
				path) == 1)
			return (free(path), 1);
		free(path);
		game->map.tex.vm.frame_count++;
	}
	game->map.tex.vm.current_frame = 0;
	game->map.tex.vm.frame_delay = VM_DELAY;
	game->map.tex.vm.delay_counter = 0;
	return (0);
}

static void	update_animation(t_game *game)
{
	game->map.tex.vm.delay_counter++;
	game->map.tex.vm.delay_counter %= game->map.tex.vm.frame_delay;
	if (game->map.tex.vm.delay_counter == 0)
	{
		game->map.tex.vm.current_frame++;
		game->map.tex.vm.current_frame %= game->map.tex.vm.frame_count;
	}
}

static void	draw_pixel(t_game *game, t_vec2i count, uint32_t packed)
{
	t_vec2i		base;
	t_vec2i		offset;

	base.x = (WIDTH / 2) + VM_X_OFFSET
		- (game->map.tex.vm.frames[game->map.tex.vm.current_frame].width
			* VM_FACTOR) / 2 + (count.x * VM_FACTOR);
	base.y = HEIGHT - VM_Y_OFFSET
		- (game->map.tex.vm.frames[game->map.tex.vm.current_frame].height
			* VM_FACTOR) + (count.y * VM_FACTOR);
	offset.x = 0;
	while (offset.x < (int)VM_FACTOR)
	{
		offset.y = 0;
		while (offset.y < (int)VM_FACTOR)
		{
			pixel_image(&game->img, base.x + offset.x, base.y + offset.y,
				packed);
			offset.y++;
		}
		offset.x++;
	}
}

void	animated_vm(t_game *game)
{
	t_vec2i	count;
	t_color	color;

	if (game->map.tex.vm.frame_count == 0)
		return ;
	update_animation(game);
	count.y = 0;
	while (count.y < game->map.tex.vm.frames[0].height)
	{
		count.x = 0;
		while (count.x < game->map.tex.vm.frames[0].width)
		{
			color = unpack_color(game->endian, get_pixel(
						game->map.tex.vm.frames
						+ game->map.tex.vm.current_frame,
						count.x, count.y));
			if (color.a == 0x00) // TODO: for some reason is inverted
				draw_pixel(game, count, pack_color(game->endian, color));
			count.x++;
		}
		count.y++;
	}
}
