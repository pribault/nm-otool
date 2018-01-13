/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_del_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:33:15 by pribault          #+#    #+#             */
/*   Updated: 2017/10/11 22:45:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_del_one(t_vector *vector, size_t i)
{
	void	*new;
	size_t	new_size;
	size_t	n;

	if (!vector)
		return ;
	if (i + 1 == vector->n)
		ft_vector_resize(vector, i);
	else if (i < vector->n)
	{
		new_size = VECTOR_SIZE * (((vector->n - 1) * vector->type - 1) /
		VECTOR_SIZE) + VECTOR_SIZE;
		new = malloc(new_size);
		n = 0;
		while (n < vector->n)
		{
			ft_memcpy(new + vector->type * n, vector->ptr + vector->type *
			((n < i) ? n : n + 1), vector->type);
			n++;
		}
		free(vector->ptr);
		vector->ptr = new;
		vector->n--;
	}
}
