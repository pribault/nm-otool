/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:06:03 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 14:55:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"
#include <stdio.h>

void			print_number(va_list va, char *new, size_t *j, char *base)
{
	int				nbr;
	int				pow;
	int				b;
	char			c;

	ft_printf("va_arg?\n");
	nbr = va_arg(va, int);
	ft_printf("???\n");
	pow = 1;
	b = ft_strlen(base);
	ft_printf("b=%d\n", b);
	if (nbr < 0)
	{
		new[(*j)++] = '-';
		nbr = -nbr;
	}
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

size_t			get_number_len(va_list va, char *base)
{
	int		nbr;

	nbr = va_arg(va, int);
	return (ft_nbrlen_base(nbr, ft_strlen(base)));
}
