/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:40:37 by pribault          #+#    #+#             */
/*   Updated: 2017/07/10 11:18:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_nbr_base(long long int nbr, int *len, char *base, int b)
{
	if (nbr < 0)
	{
		if (nbr == -9223372036854775807 - 1)
		{
			print_nbr_base(-(nbr / b), len, base, b);
			print_nbr_base(-(nbr % b), len, base, b);
		}
		else
			print_nbr_base(-nbr, len, base, b);
	}
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

size_t	number_len(long long int nbr, int base)
{
	size_t			len;

	len = 1;
	if (nbr < 0)
	{
		nbr = (nbr != -9223372036854775807 - 1) ? -nbr : 1 - nbr;
	}
	while (nbr >= base)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

void	ifn2(long long int nbr, t_param p, int *len, char *base)
{
	int				l;
	int				sign;

	l = number_len(nbr, ft_strlen(base));
	p.plus = (nbr < 0) ? '+' : p.plus;
	sign = (p.plus) ? 1 : 0;
	p.field = (ft_abs(p.field) < p.prec) ? l + sign : p.field;
	p.field -= p.space;
	if (!p.plus && p.space && nbr >= 0)
		*len += print_char(' ');
	if (p.plus && nbr >= 0 && p.c == '0')
		*len += print_char('+');
	if (nbr < 0 && (p.c == '0' || p.prec > l + sign) && p.c == '0')
		*len += print_char('-');
	*len += print_params(&p, l + sign, '0', 2);
	if (p.plus && nbr >= 0 && p.c == ' ')
		*len += print_char('+');
	if (nbr < 0 && p.prec > l && p.c == ' ')
		*len += print_char('-');
	*len += print_params(&p, l, '0', 1);
	if (nbr < 0 && p.c == ' ' && p.save <= l)
		*len += print_char('-');
	print_nbr_base(nbr, len, base, ft_strlen(base));
	p.save += sign;
	*len += print_params(&p, l + sign, '0', -1);
}

void	ifn3(t_param p, int *len)
{
	int	l;

	l = 0;
	p.field = (p.less) ? -p.field : p.field;
	*len += print_params(&p, l, '0', 2);
	*len += print_params(&p, l, '0', 1);
	*len += print_params(&p, l, '0', -1);
}

void	if_forest_number(va_list va, t_param param, int *len, char *base)
{
	long long int	nbr;

	if (param.modif == MODIF_HH)
		nbr = (char)va_arg(va, int);
	else if (param.modif == MODIF_H)
		nbr = (short)va_arg(va, int);
	else if (param.modif == MODIF_LL)
		nbr = (long long int)va_arg(va, long long int);
	else if (param.modif == MODIF_L)
		nbr = (long int)va_arg(va, long int);
	else if (param.modif == MODIF_J)
		nbr = (intmax_t)va_arg(va, intmax_t);
	else if (param.modif == MODIF_Z)
		nbr = (ssize_t)va_arg(va, ssize_t);
	else
		nbr = (int)va_arg(va, int);
	if (param.bool)
		param.c = ' ';
	if (param.prec == 0 && param.bool == 1 && nbr == 0)
		ifn3(param, len);
	else
		ifn2(nbr, param, len, base);
}
