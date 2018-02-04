/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:30:53 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 19:55:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

size_t	ft_unsigned_len_base(unsigned long nbr, int base)
{
	size_t	len;

	len = 1;
	while (nbr / base)
	{
		len++;
		nbr /= base;
	}
	return (len);
}

size_t	get_unsigned_len(va_list va, char *base)
{
	unsigned long	n;

	n = va_arg(va, unsigned long);
	return (ft_unsigned_len_base(n, ft_strlen(base)));
}
