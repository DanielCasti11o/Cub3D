/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:03:51 by dacastil          #+#    #+#             */
/*   Updated: 2025/10/30 20:06:18 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **node, void (*del)(void *))
{
	if (node != NULL && *node != NULL)
	{
		if (del != NULL)
			del((*node)->content);
		free(*node);
		*node = NULL;
	}
}
