/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:38:30 by pribault          #+#    #+#             */
/*   Updated: 2017/07/19 13:42:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ft_joinf.h"
# include <stdarg.h>
# include <wchar.h>
# include <inttypes.h>

# define MODIF_HH	0x10
# define MODIF_H	0x1
# define MODIF_L	0x100
# define MODIF_LL	0x1000
# define MODIF_J	0x10000
# define MODIF_Z	0x100000

typedef struct	s_param
{
	int			modif;
	int			prec;
	int			field;
	int			bool;
	int			hash;
	int			plus;
	int			less;
	int			space;
	int			save;
	char		c;
}				t_param;

int				ft_printf(const char *format, ...);

int				if_forest_one(va_list va, const char *format, int *i);

t_param			if_forest_param(const char *format, int *i);

void			if_forest_number(va_list v, t_param p, int *l, char *bs);
void			if_forest_unsigned(va_list v, t_param p, int *l, char *bs);
void			if_forest_string(va_list v, t_param p, int *l, int t);
void			if_forest_char(va_list v, t_param p, int *l, int state);
void			if_forest_pointer(va_list va, t_param param, int *len);
void			if_forest_long(va_list va, t_param param, int *len, char *base);

int				print_params(t_param *p, int l, char c, int state);

void			print_nbr_base(long long int n, int *l, char *bs, int b);

size_t			number_len(long long int nbr, int base);
size_t			unsigned_len(unsigned long long int nbr, unsigned int base);

int				is_number(const char *f, int *i);

int				print_char(char c);
int				print_wchar(wchar_t c);

void			print_str(char *str, int *len, int n);

int				ft_check(char c);
int				ft_check2(char c);

int				ft_atoi2(const char *str, int *i);
int				ft_abs(int nbr);

#endif
