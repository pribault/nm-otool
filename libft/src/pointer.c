/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:59:12 by pribault          #+#    #+#             */
/*   Updated: 2017/01/13 17:21:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	if_forest_pointer(va_list va, t_param p, int *len)
{
	void	*nbr;
	int		l;
	int		t;

	nbr = va_arg(va, void*);
	l = unsigned_len((unsigned long long)nbr, 16);
	p.field = (ft_abs(p.field) < p.prec) ? l : p.field;
	l = (p.bool && p.prec == 0) ? 0 : l;
	t = (l > p.prec) ? l : p.prec;
	*len += print_params(&p, t + 2, ' ', 2);
	print_str("0x", len, 2);
	*len += print_params(&p, t + 2, '0', 2);
	*len += print_params(&p, l, '0', 1);
	if (!p.bool || p.prec != 0)
		print_nbr_base((long long)nbr, len, "0123456789abcdef", 16);
	*len += print_params(&p, l + 2, '0', -1);
}
