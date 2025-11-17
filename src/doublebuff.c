/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublebuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:52:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/17 21:20:39 by migugar2         ###   ########.fr       */
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

// Print pixels in the image to print this image in the window

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
	memset(img->addr, 0, total_bytes);
}

// TODO: move to a utils or math file
// The best way of representation: degrees

double	degrees(double grad)
{
	double	rad;

	rad = grad * (PI / 180);
	return (rad);
}
