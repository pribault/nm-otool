/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:19:40 by pribault          #+#    #+#             */
/*   Updated: 2017/01/13 18:00:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_long_base(long long nbr, int *len, char *base, int b)
{
	if (nbr < 0)
		print_nbr_base(-nbr, len, base, b);
	else
	{
		if (nbr >= b)
		{
			print_nbr_base(nbr / b, len, base, b);
			print_nbr_base(nbr % b, len, base, b);
		}
		else
			(*len) += print_wchar(base[nbr]);
	}
}

void	ifl2(long long nbr, t_param p, int *len, char *base)
{
	int				l;

	l = number_len(nbr, ft_strlen(base));
	l += (!ft_strcmp("01234567", base) && p.hash && nbr != 0) ? 1 : 0;
	if (p.hash && nbr != 0)
		l += (!ft_strcmp("01234567", base)) ? 1 : 0;
	*len += print_params(&p, l, ' ', 2);
	if (!ft_strcmp("01234567", base) && p.hash && nbr != 0)
		print_str("0", len, 1);
	if (!p.plus && p.space && nbr >= 0)
		*len += print_char(' ');
	*len += print_params(&p, l, '0', 2);
	if (nbr < 0 && p.prec > l && p.c == ' ' && ft_strcmp(base, "01234567"))
		*len += print_char('-');
	*len += print_params(&p, l, '0', 1);
	if (nbr < 0 && p.c == ' ' && p.save <= l && ft_strcmp(base, "01234567"))
		*len += print_char('-');
	print_long_base(nbr, len, base, ft_strlen(base));
	*len += print_params(&p, l, '0', -1);
}

void	ifl3(t_param p, int *len)
{
	long int	l;

	l = 0;
	p.field = (p.less) ? -p.field : p.field;
	*len += print_params(&p, l, '0', 1);
	*len += print_params(&p, l, ' ', 2);
	*len += print_params(&p, l, '0', 2);
	*len += print_params(&p, l, '0', -1);
}

void	if_forest_long(va_list va, t_param p, int *len, char *base)
{
	long long	nbr;

	nbr = (long int)va_arg(va, long int);
	if (p.bool == 1 && p.prec == 0 && (!p.hash || ft_strcmp(base, "01234567")))
		ifl3(p, len);
	else
		ifl2(nbr, p, len, base);
}
