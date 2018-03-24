/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 19:09:52 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 19:13:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		sort_symbol_32_alpha(t_nm *nm, struct nlist *a, struct nlist *b)
{
	int		ret;

	if ((ret = ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
		nm->ptr + nm->stroff + b->n_un.n_strx)) < 0 ||
		(!ret && a->n_value < b->n_value))
		return (1);
	return (0);
}

int		sort_symbol_64_alpha(t_nm *nm, struct nlist_64 *a, struct nlist_64 *b)
{
	int		ret;

	if ((ret = ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
		nm->ptr + nm->stroff + b->n_un.n_strx)) < 0 ||
		(!ret && a->n_value < b->n_value))
		return (1);
	return (0);
}

int		sort_symbol_32_numeric(t_nm *nm, struct nlist *a, struct nlist *b)
{
	if (a->n_value < b->n_value || (a->n_value == b->n_value &&
		ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
		nm->ptr + nm->stroff + b->n_un.n_strx) < 0))
		return (1);
	return (0);
}

int		sort_symbol_64_numeric(t_nm *nm, struct nlist_64 *a, struct nlist_64 *b)
{
	if (a->n_value < b->n_value || (a->n_value == b->n_value &&
		ft_strcmp(nm->ptr + nm->stroff + a->n_un.n_strx,
		nm->ptr + nm->stroff + b->n_un.n_strx) < 0))
		return (1);
	return (0);
}
