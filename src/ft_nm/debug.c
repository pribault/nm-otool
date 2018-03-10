/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 11:53:05 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 18:55:37 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	debug_sections_32(t_nm *nm)
{
	struct section	*section_32;
	size_t			i;

	ft_printf("\n");
	if (nm->sect_32.n)
	{
		i = (size_t)-1;
		ft_printf("___ sections x32 ___\n");
		while (++i < nm->sect_32.n &&
			(section_32 = ft_vector_get(&nm->sect_32, i)))
			ft_printf(" [ %s ] : [ %s ]\n  addr=%u size=%u\n",
				&section_32->sectname, &section_32->segname,
				section_32->addr, section_32->size);
	}
}

void	debug_sections_64(t_nm *nm)
{
	struct section_64	*section_64;
	size_t				i;

	ft_printf("\n");
	if (nm->sect_64.n)
	{
		i = (size_t)-1;
		ft_printf("___ sections x64 ___\n");
		while (++i < nm->sect_64.n &&
			(section_64 = ft_vector_get(&nm->sect_64, i)))
			ft_printf(" [ %s ] : [ %s ]\n  addr=%u size=%u\n",
				&section_64->sectname, &section_64->segname,
				section_64->addr, section_64->size);
	}
}

void	debug_symbols_32(t_nm *nm)
{
	struct nlist	*sym_32;
	size_t			i;

	ft_printf("\n");
	if (nm->syms_32.n)
	{
		i = nm->syms_32.n;
		ft_printf("___ symbols x32 ___\n");
		while (--i != (size_t)-1 &&
			(sym_32 = ft_vector_get(&nm->syms_32, i)))
		{
			ft_printf(" %s:\n\t%s\n\ttype=%hhx\n\tsection=%hhx\n\tvalue=%lx\n",
				nm->ptr + nm->stroff + sym_32->n_un.n_strx,
				(sym_32->n_type & N_EXT) ? "external" : "local",
				sym_32->n_type, sym_32->n_sect, sym_32->n_value);
			ft_printf("\tstrx=%x\n\tdesc=%hx\n", sym_32->n_un.n_strx,
				sym_32->n_desc);
		}
	}
}

void	debug_symbols_64(t_nm *nm)
{
	struct nlist_64	*sym_64;
	size_t			i;

	ft_printf("\n");
	if (nm->syms_64.n)
	{
		i = nm->syms_64.n;
		ft_printf("___ symbols x64 ___\n");
		while (--i != (size_t)-1 &&
			(sym_64 = ft_vector_get(&nm->syms_64, i)))
		{
			ft_printf(" %s:\n\t%s\n\ttype=%hhx\n\tsection=%hhx\n\tvalue=%lx\n",
				nm->ptr + nm->stroff + sym_64->n_un.n_strx,
				(sym_64->n_type & N_EXT) ? "external" : "local",
				sym_64->n_type, sym_64->n_sect, sym_64->n_value);
			ft_printf("\tstrx=%x\n\tdesc=%hx\n", sym_64->n_un.n_strx,
				sym_64->n_desc);
			ft_memdump(sym_64, sizeof(struct nlist_64));
		}
	}
}

void	debug_full(t_nm *nm)
{
	if (!(nm->opt & DEBUG))
		return ;
	debug_sections_32(nm);
	debug_sections_64(nm);
	debug_symbols_32(nm);
	debug_symbols_64(nm);
	ft_printf("\n");
}
