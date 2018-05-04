/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 10:10:58 by pribault          #+#    #+#             */
/*   Updated: 2018/04/11 23:03:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static void	*realloc_1(t_alloc *next, t_alloc *alloc, size_t size)
{
	t_alloc	*tmp;

	if (alloc->size - size >= sizeof(t_alloc))
	{
		tmp = (void*)&alloc[1] + size;
		tmp->type = TYPE_FREE;
		tmp->size = alloc->size - size - sizeof(t_alloc);
		if (next && next->type == TYPE_FREE)
			tmp->size += (sizeof(t_alloc) + next->size);
		alloc->size = size;
	}
	return (&alloc[1]);
}

static void	*realloc_2(t_alloc *prev, t_alloc *alloc, size_t size)
{
	uint64_t	mem;
	t_alloc		*tmp;

	mem = alloc->size;
	prev->type = TYPE_ALLOC;
	ft_memcpy(&prev[1], &alloc[1], alloc->size);
	if (prev->size + sizeof(t_alloc) + mem - size >=
		sizeof(t_alloc))
	{
		tmp = (void*)&prev[1] + size;
		tmp->type = TYPE_FREE;
		tmp->size = prev->size + mem - size;
		prev->size = size;
	}
	else
		prev->size += (sizeof(t_alloc) + mem);
	return (&prev[1]);
}

static void	*realloc_3(t_alloc *next, t_alloc *alloc, size_t size)
{
	t_alloc	*tmp;

	if (next->size + sizeof(t_alloc) + alloc->size - size >=
		sizeof(t_alloc))
	{
		tmp = (void*)&alloc[1] + size;
		tmp->type = TYPE_FREE;
		tmp->size = alloc->size + next->size - size;
		alloc->size = size;
	}
	else
		alloc->size += (sizeof(t_alloc) + next->size);
	return (&alloc[1]);
}

static void	*realloc_4(t_alloc *prev, t_alloc *next, t_alloc *alloc,
			size_t size)
{
	uint64_t	mem;
	t_alloc		*tmp;

	mem = alloc->size;
	prev->type = TYPE_ALLOC;
	ft_memcpy(&prev[1], &alloc[1], alloc->size);
	if (2 * sizeof(t_alloc) + prev->size + mem + next->size -
		size >= sizeof(t_alloc))
	{
		tmp = (void*)&prev[1] + size;
		tmp->type = TYPE_FREE;
		tmp->size = sizeof(t_alloc) + prev->size + mem +
		next->size - size;
		prev->size = size;
	}
	else
		prev->size += (2 * sizeof(t_alloc) + mem + next->size);
	return (&prev[1]);
}

void		*realloc_in_zone(t_zone *zone, t_alloc *prev, t_alloc *alloc,
			size_t size)
{
	void	*ptr;
	t_alloc	*next;

	next = get_in_zone(zone, (void*)&alloc[1] + alloc->size, sizeof(t_alloc));
	if (size <= alloc->size)
		return (realloc_1(next, alloc, size));
	if (prev && prev->type == TYPE_FREE &&
		size <= prev->size + sizeof(t_alloc) + alloc->size)
		return (realloc_2(prev, alloc, size));
	if (next && next->type == TYPE_FREE &&
		size <= alloc->size + sizeof(t_alloc) + next->size)
		return (realloc_3(next, alloc, size));
	if (prev && prev->type == TYPE_FREE && next && next->type == TYPE_FREE &&
		size <= 2 * sizeof(t_alloc) + prev->size + alloc->size + next->size)
		return (realloc_4(prev, next, alloc, size));
	pthread_mutex_unlock(&g_env.mutex);
	if (!(ptr = malloc(size)))
		return (lock_and_return(NULL));
	pthread_mutex_lock(&g_env.mutex);
	ft_memcpy(ptr, &alloc[1], (alloc->size < size) ? alloc->size : size);
	pthread_mutex_unlock(&g_env.mutex);
	free(&alloc[1]);
	pthread_mutex_lock(&g_env.mutex);
	return (ptr);
}
