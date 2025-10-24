/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublebuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:52:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/23 20:31:54 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_image(t_img *img, int x, int y, double color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img)
{
	int	total_bytes;

	total_bytes = HEIGHT * img->line_length;
	memset(img->addr, 0, total_bytes);
}
