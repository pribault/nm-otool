/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:30:21 by pribault          #+#    #+#             */
/*   Updated: 2018/02/25 13:54:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	sort_symtab_32(t_nm *nm)
{
	t_bool			boolean;
	struct nlist	*a;
	struct nlist	*b;
	size_t			i;
	int				ret;

	boolean = FT_FALSE;
	while (!boolean)
	{
		boolean = FT_TRUE;
		i = nm->syms_32->n - 1;
		while (--i != (size_t)-1)
		{
			a = ft_vector_get(nm->syms_32, i);
			b = ft_vector_get(nm->syms_32, i + 1);
			if ((ret = ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
				nm->ptr + nm->stroff + b->n_un.n_strx)) < 0 ||
				(!ret && a->n_value < b->n_value))
			{
				boolean = FT_FALSE;
				ft_swap(a, b, sizeof(struct nlist));
			}
		}
	}
}

void	print_symtab_32(t_nm *nm)
{
	struct nlist	*nlist;
	size_t			i;
	char			c;

	i = nm->syms_32->n;
	while (--i != (size_t)-1 && (nlist = ft_vector_get(nm->syms_32, i)))
	{
		if ((c = get_symbol_value_32(nm, nlist)) == 'U')
			ft_printf("         %c %s\n", c,
			nm->ptr + nm->stroff + nlist->n_un.n_strx);
		else
			ft_printf("%.8lx %c %s\n", nlist->n_value, c,
			nm->ptr + nm->stroff + nlist->n_un.n_strx);
	}
}

void	sort_symtab_64(t_nm *nm)
{
	t_bool			boolean;
	struct nlist_64	*a;
	struct nlist_64	*b;
	size_t			i;
	int				ret;

	boolean = FT_FALSE;
	while (!boolean)
	{
		boolean = FT_TRUE;
		i = nm->syms_64->n - 1;
		while (--i != (size_t)-1)
		{
			a = ft_vector_get(nm->syms_64, i);
			b = ft_vector_get(nm->syms_64, i + 1);
			if ((ret = ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
				nm->ptr + nm->stroff + b->n_un.n_strx)) < 0 ||
				(!ret && a->n_value < b->n_value))
			{
				boolean = FT_FALSE;
				ft_swap(a, b, sizeof(struct nlist_64));
			}
		}
	}
}

void	print_symtab_64(t_nm *nm)
{
	struct nlist_64		*nlist;
	size_t				i;
	char				c;

	i = nm->syms_64->n;
	while (--i != (size_t)-1 && (nlist = ft_vector_get(nm->syms_64, i)))
	{
		if ((c = get_symbol_value_64(nm, nlist)) == 'U')
			ft_printf("                 %c %s\n", c,
			nm->ptr + nm->stroff + nlist->n_un.n_strx);
		else
			ft_printf("%.16lx %c %s\n", nlist->n_value, c,
			nm->ptr + nm->stroff + nlist->n_un.n_strx);
	}
}
