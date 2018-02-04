/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 23:37:46 by pribault          #+#    #+#             */
/*   Updated: 2017/10/18 18:47:51 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	*ft_vector_new(size_t type, size_t n)
{
	t_vector	*new;

	if (!(new = (t_vector*)malloc(sizeof(t_vector))))
		return (NULL);
	new->n = n;
	new->type = type;
	new->size = VECTOR_SIZE * ((type * n - 1) / VECTOR_SIZE) +
	VECTOR_SIZE;
	if (!(new->ptr = malloc(new->size)))
	{
		free(new);
		return (NULL);
	}
	ft_bzero(new->ptr, new->size);
	return (new);
}
