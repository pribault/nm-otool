/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:03:35 by pribault          #+#    #+#             */
/*   Updated: 2017/01/13 16:14:01 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_params2(t_param *p, int l, char c, int state)
{
	int		len;

	len = 0;
	if (state == 1)
		while (p->prec > l)
		{
			len += print_wchar(c);
			p->prec--;
		}
	else
		while (p->field < -l && p->field < -ft_abs(p->save))
		{
			len += print_wchar(' ');
			p->field++;
		}
	return (len);
}

int		print_params(t_param *p, int l, char c, int state)
{
	int		len;

	len = 0;
	if (state == 2)
	{
		while (c == '0' && p->field > p->prec + p->plus / 43 && p->field > l)
		{
			len += print_wchar(p->c);
			p->field--;
		}
		while (p->c == ' ' && c == ' ' && p->field > p->prec)
		{
			if (p->field > l)
				len += print_wchar(p->c);
			p->field--;
		}
	}
	else
		len += print_params2(p, l, c, state);
	return (len);
}

t_param	if_forest_modif(t_param p, const char *format, int *i)
{
	if (format[*i] == 'h' && (p.modif == MODIF_H || !p.modif))
		p.modif = (p.modif == MODIF_H) ? MODIF_HH : MODIF_H;
	else if (format[*i] == 'l' && (p.modif == MODIF_L || !p.modif))
		p.modif = (p.modif == MODIF_L) ? MODIF_LL : MODIF_L;
	else if (format[*i] == 'j' && !p.modif)
		p.modif = MODIF_J;
	else if (format[*i] == 'z' && !p.modif)
		p.modif = MODIF_Z;
	else if (format[*i] == '#')
		p.hash = 1;
	else if (format[*i] == '0')
		p.c = '0';
	else if (format[*i] == '+')
		p.plus = format[*i];
	else if (format[*i] == '-')
		p.less = format[*i];
	else if (format[*i] == ' ')
		p.space = 1;
	(*i)++;
	return (p);
}

t_param	param_init(void)
{
	t_param	param;

	param.modif = 0;
	param.prec = 0;
	param.field = 0;
	param.bool = 0;
	param.hash = 0;
	param.plus = 0;
	param.less = 0;
	param.space = 0;
	param.c = ' ';
	return (param);
}

t_param	if_forest_param(const char *f, int *i)
{
	t_param	param;

	param = param_init();
	while (ft_check2(f[*i]))
	{
		if (is_number(f, i))
		{
			param.plus = (f[*i] == '+') ? '+' : param.plus;
			param.less = (f[*i] == '-') ? '-' : param.less;
			param.field = ft_atoi2(f, i);
			param.c = (param.field == 0 && f[*i] == '0') ? '0' : param.c;
		}
		else if (f[*i] == '.')
		{
			(*i)++;
			param.prec = ft_atoi2(f, i);
			(*i) += (param.prec == 0 && f[*i] == '0') ? 1 : 0;
			param.bool = 1;
		}
		else
			param = if_forest_modif(param, f, i);
	}
	param.field = (param.less) ? -ft_abs(param.field) : param.field;
	param.save = param.prec;
	return (param);
}
