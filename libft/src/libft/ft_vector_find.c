/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:07:37 by pribault          #+#    #+#             */
/*   Updated: 2018/04/10 12:36:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_vector_find(t_vector *vector, void *ptr)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < vector->n)
		if (!ft_memcmp(ft_vector_get(vector, i), ptr, vector->type))
			return (i);
	return ((size_t)-1);
}
