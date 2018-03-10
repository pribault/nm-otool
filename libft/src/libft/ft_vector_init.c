/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 11:31:27 by pribault          #+#    #+#             */
/*   Updated: 2018/03/03 11:33:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_init(t_vector *vector, size_t type)
{
	vector->ptr = NULL;
	vector->type = type;
	vector->n = 0;
	vector->size = 0;
}
