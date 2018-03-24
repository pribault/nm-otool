/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 18:45:36 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 18:50:35 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	reverse_symtab_32(t_nm *nm)
{
	size_t	i;
	size_t	j;

	i = (size_t)-1;
	j = (size_t)nm->syms_32.n;
	while (++i < --j)
		ft_swap(ft_vector_get(&nm->syms_32, i), ft_vector_get(&nm->syms_32, j),
		sizeof(struct nlist));
}

void	reverse_symtab_64(t_nm *nm)
{
	size_t	i;
	size_t	j;

	i = (size_t)-1;
	j = (size_t)nm->syms_64.n;
	while (++i < --j)
		ft_swap(ft_vector_get(&nm->syms_64, i), ft_vector_get(&nm->syms_64, j),
		sizeof(struct nlist_64));
}
