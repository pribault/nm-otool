/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 00:57:28 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 17:32:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_del(t_vector *vector)
{
	if (vector->alloc == ALLOC_MALLOC)
	{
		if (vector->size)
			free(vector->ptr);
	}
	else if (vector->alloc == ALLOC_MMAP)
	{
		if (vector->size)
			munmap(vector->ptr, vector->size);
	}
	*vector = DEFAULT_VECTOR;
}
