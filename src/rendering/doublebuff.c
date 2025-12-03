/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublebuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:52:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/12/02 19:36:51 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel(t_buf *img, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0x000000);
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	pixel_image(t_buf *img, int x, int y, uint32_t color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_buf *img)
{
	int	total_bytes;

	total_bytes = HEIGHT * img->size_line;
	ft_memset(img->addr, 0, total_bytes);
}

int	init_image_path(t_game *game, t_buf *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx,
			path,
			&img->width,
			&img->height);
	if (!img->ptr)
		return (perror_texture(path));
	img->addr = mlx_get_data_addr(img->ptr,
			&img->bpp,
			&img->size_line,
			&game->endian);
	return (0);
}
