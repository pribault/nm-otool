/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:33:43 by pribault          #+#    #+#             */
/*   Updated: 2017/10/18 18:47:35 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "structs.h"
#include "prototypes.h"

#include <sys/time.h>
#include <sys/resource.h>

t_alloc	*create_allocation(void *ptr, size_t size)
{
	t_alloc	*new;

	if ((new = mmap(NULL, sizeof(t_alloc), PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (malloc_error(1, NULL));
	new->ptr = ptr;
	new->size = size;
	new->next = NULL;
	return (new);
}

void	add_allocation(t_alloc **head, t_alloc *new)
{
	t_alloc	*alloc;

	if (!new)
		return ;
	alloc = *head;
	while (alloc && alloc->ptr < new->ptr && alloc->next &&
	alloc->next->ptr < new->ptr)
		alloc = alloc->next;
	if (!alloc)
		*head = new;
	else if (alloc && alloc->ptr > new->ptr)
	{
		new->next = *head;
		*head = new;
	}
	else if (alloc->next && alloc->next->ptr > new->ptr)
	{
		new->next = alloc->next;
		alloc->next = new;
	}
	else if (!alloc->next)
		alloc->next = new;
}

void	*alloc_in_zone(t_zone *zone, size_t size)
{
	t_alloc	*alloc;
	void	*prev;

	prev = zone->ptr;
	alloc = zone->allocs;
	while (alloc)
	{
		if (size < (size_t)(alloc->ptr - prev))
		{
			add_allocation(&zone->allocs, create_allocation(prev, size));
			return (prev);
		}
		prev = alloc->ptr + alloc->size + 1;
		alloc = alloc->next;
	}
	if (size < (size_t)(prev - (zone->ptr + zone->size)))
	{
		add_allocation(&zone->allocs, create_allocation(prev, size));
		return (prev);
	}
	if (!(zone->next = alloc_zone(zone->size)))
		return (NULL);
	return (alloc_in_zone(zone->next, size));
}

void	*alloc_large(size_t size)
{
	t_alloc	*new;

	if ((new = mmap(NULL, sizeof(t_alloc), PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (malloc_error(1, NULL));
	if ((new->ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (malloc_error(1, NULL));
	new->size = size;
	new->next = NULL;
	add_allocation(&g_env.large, new);
	return (new->ptr);
}

t_zone	*alloc_zone(size_t size)
{
	t_zone	*new;

	if ((new = mmap(NULL, sizeof(t_zone), PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (malloc_error(1, NULL));
	if ((new->ptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (malloc_error(1, NULL));
	new->size = size;
	new->allocs = NULL;
	new->next = NULL;
	return (new);
}
