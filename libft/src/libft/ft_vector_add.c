/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:30:45 by pribault          #+#    #+#             */
/*   Updated: 2017/09/01 03:04:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_add(t_vector *vector, void *ptr)
{
	ft_vector_resize(vector, vector->n + 1);
	ft_memcpy(vector->ptr + (vector->n - 1) * vector->type, ptr, vector->type);
}
