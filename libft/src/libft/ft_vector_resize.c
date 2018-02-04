/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:15:55 by pribault          #+#    #+#             */
/*   Updated: 2017/10/18 19:54:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_resize(t_vector *vector, size_t new_size)
{
	size_t	mem;

	if (!vector)
		return ;
	if (new_size * vector->type > vector->size)
	{
		mem = VECTOR_SIZE * ((new_size * vector->type - 1) /
		VECTOR_SIZE) + VECTOR_SIZE;
		if (!(vector->ptr = realloc(vector->ptr, mem)))
			return ;
		vector->size = mem;
	}
	vector->n = new_size;
}
