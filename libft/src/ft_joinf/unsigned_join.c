/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:30:53 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 14:59:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"

void	print_unsigned_base_join(va_list va, char *new, size_t *j, char *base)
{
	uint64_t		nbr;
	uint64_t		pow;
	uint32_t		b;
	char			c;

	nbr = va_arg(va, uint64_t);
	pow = 1;
	b = ft_strlen(base);
	while (pow * b <= nbr)
		pow *= b;
	while (pow > 0)
	{
		c = nbr / pow;
		new[(*j)++] = base[(int)c];
		nbr -= c * pow;
		pow /= b;
	}
}

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
