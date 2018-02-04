/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:04:36 by pribault          #+#    #+#             */
/*   Updated: 2017/10/12 12:04:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "structs.h"
#include "prototypes.h"

size_t	show_allocs(t_alloc *alloc)
{
	size_t	size;

	size = 0;
	while (alloc)
	{
		ft_printf(
		"  %p \033[38;5;88m-\033[0m %p \033[38;5;88m:\033[0m %u octets\n",
		alloc->ptr, alloc->ptr + alloc->size - 1, alloc->size);
		size += alloc->size;
		alloc = alloc->next;
	}
	return (size);
}

size_t	show_zone(t_zone *zone)
{
	size_t	size;

	size = 0;
	while (zone)
	{
		size += show_allocs(zone->allocs);
		zone = zone->next;
	}
	return (size);
}

size_t	show_allocs_ex(t_alloc *alloc)
{
	size_t	size;
	size_t	i;

	size = 0;
	while (alloc)
	{
		ft_printf(
		"  %p \033[38;5;88m-\033[0m %p \033[38;5;88m:\033[0m %u octets\n",
		alloc->ptr, alloc->ptr + alloc->size - 1, alloc->size);
		i = 0;
		while (i < alloc->size)
		{
			if (!(i % LINE_FEED))
				ft_putstr("   ");
			ft_putstr((!((char*)alloc->ptr)[i]) ? "\033[38;5;240m" :
			"\033[38;5;87m");
			ft_printf(" %.2hhx\033[0m", ((char*)alloc->ptr)[i++]);
			if (!(i % LINE_FEED))
				ft_putchar('\n');
		}
		ft_putstr("\n\n");
		size += alloc->size;
		alloc = alloc->next;
	}
	return (size);
}

size_t	show_zone_ex(t_zone *zone)
{
	size_t	size;

	size = 0;
	while (zone)
	{
		size += show_allocs_ex(zone->allocs);
		zone = zone->next;
	}
	return (size);
}

void	show_alloc_mem_ex(void)
{
	t_zone	*zone;
	size_t	size;

	size = 0;
	sort_zones(&g_env.tiny);
	sort_zones(&g_env.small);
	sort_allocs(&g_env.large);
	ft_printf("\033[38;5;214mTINY\033[0m : %p\n", g_env.tiny);
	zone = g_env.tiny;
	while (zone)
	{
		size += show_zone_ex(zone);
		zone = zone->next;
	}
	ft_printf("\033[38;5;214mSMALL\033[0m : %p\n", g_env.small);
	zone = g_env.small;
	while (zone)
	{
		size += show_zone_ex(zone);
		zone = zone->next;
	}
	ft_printf("\033[38;5;214mLARGE\033[0m : %p\n", g_env.large);
	size += show_allocs_ex(g_env.large);
	ft_printf("\033[38;5;166mTotal\033[0m : %u octects\n", size);
}
