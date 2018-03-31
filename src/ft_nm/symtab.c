/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:30:21 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 20:27:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	sort_symtab_32(t_nm *nm)
{
	if (nm->opt & NO_SORT)
		reverse_symtab_32(nm);
	else if (nm->opt & NUMERIC_SORT)
	{
		sort_symtab_32_function(nm, &sort_symbol_32_numeric);
		if (nm->opt & REVERSE)
			reverse_symtab_32(nm);
	}
	else
	{
		sort_symtab_32_function(nm, &sort_symbol_32_alpha);
		if (nm->opt & REVERSE)
			reverse_symtab_32(nm);
	}
}

void	print_symtab_32(t_nm *nm)
{
	struct nlist	*nlist;
	size_t			i;
	char			c;

	i = nm->syms_32.n;
	while (--i != (size_t)-1 && (nlist = ft_vector_get(&nm->syms_32, i)))
	{
		c = get_symbol_value_32(nm, nlist);
		if (c == 'U')
		{
			if (nm->opt & ONLY_UNDEFINED)
				ft_printf("%s\n", nm->ptr + nm->stroff + nlist->n_un.n_strx);
			else if (!(nm->opt & NO_UNDEFINED))
				ft_printf("         %c %s\n", c,
				nm->ptr + nm->stroff + nlist->n_un.n_strx);
		}
		else if (c != '?' && !(nm->opt & ONLY_UNDEFINED))
			ft_printf("%.8lx %c %s\n", nlist->n_value, c,
			nm->ptr + nm->stroff + nlist->n_un.n_strx);
	}
}

void	sort_symtab_64(t_nm *nm)
{
	if (nm->opt & NO_SORT)
		reverse_symtab_64(nm);
	else if (nm->opt & NUMERIC_SORT)
	{
		sort_symtab_64_function(nm, &sort_symbol_64_numeric);
		if (nm->opt & REVERSE)
			reverse_symtab_64(nm);
	}
	else
	{
		sort_symtab_64_function(nm, &sort_symbol_64_alpha);
		if (nm->opt & REVERSE)
			reverse_symtab_64(nm);
	}
}

void	print_symtab_64(t_nm *nm)
{
	struct nlist_64		*nlist;
	size_t				i;
	char				c;

	i = nm->syms_64.n;
	while (--i != (size_t)-1 && (nlist = ft_vector_get(&nm->syms_64, i)))
	{
		c = get_symbol_value_64(nm, nlist);
		if (c == 'U')
		{
			if (nm->opt & ONLY_UNDEFINED)
				ft_printf("%s\n", nm->ptr + nm->stroff + nlist->n_un.n_strx);
			else if (!(nm->opt & NO_UNDEFINED) &&
				(!(nm->opt & ONLY_GLOBAL) || (nlist->n_type & N_EXT)))
				ft_printf("                 %c %s\n", c,
				nm->ptr + nm->stroff + nlist->n_un.n_strx);
		}
		else if (c != '?' && !(nm->opt & ONLY_UNDEFINED) &&
			(!(nm->opt & ONLY_GLOBAL) || (nlist->n_type & N_EXT)))
			ft_printf("%.16lx %c %s\n", nlist->n_value, c,
			nm->ptr + nm->stroff + nlist->n_un.n_strx);
	}
}
