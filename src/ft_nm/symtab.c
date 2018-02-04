/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:30:21 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 17:27:13 by pribault         ###   ########.fr       */
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
	char			*tmp;
	struct nlist	*nlist;
	size_t			i;

	i = nm->syms_32->n;
	while (--i != (size_t)-1)
	{
		nlist = ft_vector_get(nm->syms_32, i);
		if (!(tmp = ft_joinf("\t%s",
		nm->ptr + nm->stroff + nlist->n_un.n_strx)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_vector_add(nm->out, &tmp);
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
	char			*tmp;
	struct nlist	*nlist;
	size_t			i;

	i = nm->syms_64->n;
	while (--i != (size_t)-1)
	{
		nlist = ft_vector_get(nm->syms_64, i);
		if (!(tmp = ft_joinf("\t%s",
		nm->ptr + nm->stroff + nlist->n_un.n_strx)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_vector_add(nm->out, &tmp);
	}
}
