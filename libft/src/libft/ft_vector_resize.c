/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:15:55 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 17:31:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*vector_realloc(void *ptr, size_t size, size_t new_size)
{
	void	*new_ptr;

	if (!(new_ptr = mmap(NULL, new_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANON, -1, 0)))
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	munmap(ptr, size);
	return (new_ptr);
}

void		ft_vector_resize(t_vector *vector, size_t new_size)
{
	size_t	mem;

	if (new_size * vector->type > vector->size)
	{
		mem = VECTOR_SIZE * ((new_size * vector->type - 1) /
		VECTOR_SIZE) + VECTOR_SIZE;
		if (vector->alloc == ALLOC_MALLOC)
		{
			if (!(vector->ptr = realloc(vector->ptr, mem)))
				return ;
		}
		else if (vector->alloc == ALLOC_MMAP)
		{
			if (!(vector->ptr = vector_realloc(vector->ptr, vector->size, mem)))
				return ;
		}
		vector->size = mem;
	}
	vector->n = new_size;
}
