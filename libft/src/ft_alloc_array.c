/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:24:32 by pribault          #+#    #+#             */
/*   Updated: 2016/11/23 11:47:03 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_alloc_array(size_t h, size_t w, size_t size)
{
	void	**array;
	size_t	i;

	if (!(array = malloc(sizeof(void*) * h)))
		return (NULL);
	i = 0;
	while (i < h)
	{
		if (!(array[i] = malloc(size * w)))
		{
			ft_free_array(array, i);
			return (NULL);
		}
		i++;
	}
	return (array);
}
