/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 23:31:02 by pribault          #+#    #+#             */
/*   Updated: 2017/10/01 15:06:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "structs.h"
#include "prototypes.h"

void	swap_zones(t_zone *a, t_zone *b)
{
	void	*tmp_ptr;
	t_alloc	*tmp_allocs;

	tmp_ptr = a->ptr;
	a->ptr = b->ptr;
	b->ptr = tmp_ptr;
	tmp_allocs = a->allocs;
	a->allocs = b->allocs;
	b->allocs = tmp_allocs;
}

void	swap_allocs(t_alloc *a, t_alloc *b)
{
	void	*tmp_ptr;
	size_t	tmp_size;

	tmp_ptr = a->ptr;
	a->ptr = b->ptr;
	b->ptr = tmp_ptr;
	tmp_size = a->size;
	a->size = b->size;
	b->size = tmp_size;
}

void	sort_zones(t_zone **head)
{
	t_zone	*zone;
	char	stop;

	stop = 0;
	while (!stop && *head)
	{
		stop = 1;
		zone = *head;
		while (zone->next)
		{
			if (zone->ptr > zone->next->ptr)
			{
				swap_zones(zone, zone->next);
				stop = 0;
			}
			zone = zone->next;
		}
	}
}

void	sort_allocs(t_alloc **head)
{
	t_alloc	*alloc;
	char	stop;

	stop = 0;
	while (!stop && *head)
	{
		stop = 1;
		alloc = *head;
		while (alloc->next)
		{
			if (alloc->ptr > alloc->next->ptr)
			{
				swap_allocs(alloc, alloc->next);
				stop = 0;
			}
			alloc = alloc->next;
		}
	}
}
