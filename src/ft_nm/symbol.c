/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:03:13 by pribault          #+#    #+#             */
/*   Updated: 2018/02/24 20:22:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_symbol_value_32(t_nm *nm, struct nlist *nlist)
{
	struct section	*section;

	if (nlist->n_sect == NO_SECT && (nlist->n_type & N_TYPE) == N_UNDF)
		return ('U');
	else if (nlist->n_sect != NO_SECT &&
		(section = ft_vector_get(nm->sect_32, nlist->n_sect - 1)) &&
		!ft_strcmp((char*)&section->segname, SEG_TEXT))
		return ('T');
	return ('?');
}

char	get_symbol_value_64(t_nm *nm, struct nlist_64 *nlist)
{
	struct section_64	*section;

	if (nlist->n_sect == NO_SECT)
	{
		if ((nlist->n_type & N_TYPE) == N_UNDF)
			return ('U');
		else if ((nlist->n_type & N_TYPE) == N_ABS)
			return ((nlist->n_type & N_EXT) ? 'A' : 'a');
	}
	else if (nlist->n_sect != NO_SECT &&
		(section = ft_vector_get(nm->sect_64, nlist->n_sect - 1)))
	{
		if (!ft_strcmp((char*)&section->sectname, SECT_TEXT))
			return ((nlist->n_type & N_EXT) ? 'T' : 't');
		else if (!ft_strcmp((char*)&section->sectname, SECT_BSS))
			return ((nlist->n_type & N_EXT) ? 'B' : 'b');
		else if (!ft_strcmp((char*)&section->sectname, SECT_DATA))
			return ((nlist->n_type & N_EXT) ? 'D' : 'd');
		else
			return ((nlist->n_type & N_EXT) ? 'S' : 's');
	}
	return ('?');
}
