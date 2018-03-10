/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 08:46:45 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 14:59:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

void			print_pointer(va_list va, char *new, size_t *j)
{
	new[(*j)++] = '0';
	new[(*j)++] = 'x';
	print_unsigned_base_join(va, new, j, "0123456789abcdef");
}

size_t			get_pointer_len(va_list va, char *base)
{
	int		nbr;

	nbr = va_arg(va, int);
	return (ft_nbrlen_base(nbr, ft_strlen(base)) + 2);
}
