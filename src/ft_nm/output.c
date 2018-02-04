/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:19:24 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 18:58:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	clean_output(t_vector *out)
{
	size_t	i;

	i = out->n;
	while (--i != (size_t)-1)
		free(*(char**)ft_vector_get(out, i));
	ft_vector_resize(out, 0);
}

void	print_output(t_vector *out)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < out->n)
		ft_putendl(*(char**)ft_vector_get(out, i));
}

void	add_to_output(t_vector *out, char *s)
{
	ft_vector_add(out, &s);
}
