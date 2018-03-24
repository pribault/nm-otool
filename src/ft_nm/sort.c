/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 18:26:31 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 19:10:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	sort_symtab_32_function(t_nm *nm,
		int (*function)(t_nm *, struct nlist *, struct nlist *))
{
	t_bool			boolean;
	struct nlist	*a;
	struct nlist	*b;
	size_t			i;

	boolean = FT_FALSE;
	while (!boolean)
	{
		boolean = FT_TRUE;
		i = nm->syms_32.n - 1;
		while (--i != (size_t)-1)
		{
			a = ft_vector_get(&nm->syms_32, i);
			b = ft_vector_get(&nm->syms_32, i + 1);
			if (function(nm, a, b) > 0)
			{
				boolean = FT_FALSE;
				ft_swap(a, b, sizeof(struct nlist));
			}
		}
	}
}

void	sort_symtab_64_function(t_nm *nm,
		int (*function)(t_nm *, struct nlist_64 *, struct nlist_64 *))
{
	t_bool			boolean;
	struct nlist_64	*a;
	struct nlist_64	*b;
	size_t			i;

	boolean = FT_FALSE;
	while (!boolean)
	{
		boolean = FT_TRUE;
		i = nm->syms_64.n - 1;
		while (--i != (size_t)-1)
		{
			a = ft_vector_get(&nm->syms_64, i);
			b = ft_vector_get(&nm->syms_64, i + 1);
			if (function(nm, a, b) > 0)
			{
				boolean = FT_FALSE;
				ft_swap(a, b, sizeof(struct nlist_64));
			}
		}
	}
}
