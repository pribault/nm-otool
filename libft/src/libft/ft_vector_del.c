/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 00:57:28 by pribault          #+#    #+#             */
/*   Updated: 2018/03/03 12:00:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_del(t_vector *vector)
{
	if (vector->size)
		munmap(vector->ptr, vector->size);
	*vector = DEFAULT_VECTOR;
}
