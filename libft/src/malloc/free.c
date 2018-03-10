/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:30:57 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 15:18:29 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_bool	free_in_zone(t_zone *zone, void *ptr)
{
	t_alloc	*alloc;
	t_alloc	*prev;
	t_alloc	*next;

	prev = NULL;
	alloc = get_in_zone(zone, &zone[1], sizeof(t_zone));
	while (alloc)
	{
		if (ptr >= (void*)&alloc[1] && ptr < (void*)&alloc[1] + alloc->size)
		{
			if (alloc->type != TYPE_ALLOC)
				return (FT_FALSE);
			if ((next = get_in_zone(zone, (void*)&alloc[1] + alloc->size,
				sizeof(t_alloc))) && next->type == TYPE_FREE)
				alloc->size += (next->size + sizeof(t_alloc));
			if (prev && prev->type == TYPE_FREE)
				prev->size += (alloc->size + sizeof(t_alloc));
			alloc->type = TYPE_FREE;
			return (FT_TRUE);
		}
		prev = alloc;
		alloc = get_in_zone(zone, (void*)&alloc[1] + alloc->size,
		sizeof(t_alloc));
	}
	return (FT_FALSE);
}

t_bool	free_in_zones(t_zone *zone, void *ptr)
{
	while (zone)
	{
		if (ptr >= (void*)&zone[1] && ptr < (void*)&zone[1] + zone->size)
			return (free_in_zone(zone, ptr));
		zone = zone->next;
	}
	return (FT_FALSE);
}
