/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_del_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:33:15 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 12:47:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_del_one(t_vector *vector, size_t i)
{
	size_t	new_size;

	if (!vector)
		return ;
	if (i + 1 == vector->n)
		ft_vector_resize(vector, i);
	else if (i < vector->n)
	{
		new_size = VECTOR_SIZE * (((vector->n - 1) * vector->type - 1) /
		VECTOR_SIZE) + VECTOR_SIZE;
		ft_memcpy(vector->ptr + vector->type * i,
		vector->ptr + vector->type * (i + 1),
		vector->type * (vector->n - i - 1));
		vector->size = new_size;
		vector->n--;
	}
}
