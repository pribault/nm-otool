/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:30:21 by pribault          #+#    #+#             */
/*   Updated: 2018/02/24 11:16:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	sort_symtab_32(t_nm *nm)
{
	t_bool			boolean;
	struct nlist	*a;
	struct nlist	*b;
	size_t			i;

	boolean = FT_FALSE;
	while (!boolean)
	{
		boolean = FT_TRUE;
		i = nm->syms_32->n - 1;
		while (--i != (size_t)-1)
		{
			a = ft_vector_get(nm->syms_32, i);
			b = ft_vector_get(nm->syms_32, i + 1);
			if (ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
				nm->ptr + nm->stroff + b->n_un.n_strx) > 0)
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

	i = nm->syms_32->n;
	while (--i != (size_t)-1)
	{
		nlist = ft_vector_get(nm->syms_32, i);
		ft_printf("\t%s\n", nm->ptr + nm->stroff + nlist->n_un.n_strx);
	}
}

void	sort_symtab_64(t_nm *nm)
{
	t_bool			boolean;
	struct nlist	*a;
	struct nlist	*b;
	size_t			i;

	boolean = FT_FALSE;
	while (!boolean)
	{
		boolean = FT_TRUE;
		i = nm->syms_64->n - 1;
		while (--i != (size_t)-1)
		{
			a = ft_vector_get(nm->syms_64, i);
			b = ft_vector_get(nm->syms_64, i + 1);
			if (ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
				nm->ptr + nm->stroff + b->n_un.n_strx) < 0)
			{
				boolean = FT_FALSE;
				ft_swap(a, b, sizeof(struct nlist));
			}
		}
	}
}

void	print_symtab_64(t_nm *nm)
{
	struct section_64	*section;
	struct nlist		*nlist;
	size_t				i;

	i = nm->syms_64->n;
	while (--i != (size_t)-1 && (nlist = ft_vector_get(nm->syms_64, i)))
	{
		if ((nlist->n_type & N_TYPE) == N_UNDF)
			ft_printf("                 U %s\n",
			nm->ptr + nm->stroff + nlist->n_un.n_strx);
		else if ((section = ft_vector_get(nm->sect_64, nlist->n_sect)) &&
			!ft_strcmp(&section->segname, SEG_TEXT))
			ft_printf("%.16lx T %s\n", nlist->n_value + 0x100000000,
		nm->ptr + nm->stroff + nlist->n_un.n_strx);
	}
}
