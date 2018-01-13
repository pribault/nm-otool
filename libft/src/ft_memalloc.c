/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 10:57:39 by pribault          #+#    #+#             */
/*   Updated: 2016/11/09 16:03:35 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*r;

	if (size == 0)
		return (NULL);
	r = malloc(size);
	if (r == NULL)
		return (NULL);
	ft_bzero(r, size);
	return (r);
}
