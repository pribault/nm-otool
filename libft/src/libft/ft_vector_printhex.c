/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_printhex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:49:11 by pribault          #+#    #+#             */
/*   Updated: 2017/09/01 01:53:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vector_printhex(t_vector *vector)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!vector)
		return ;
	while (i < vector->n)
	{
		j = 0;
		while (j < vector->type)
			ft_printf("%.2x ", ((char*)ft_vector_get(vector, i))[j++]);
		ft_putchar('\n');
		i++;
	}
}
