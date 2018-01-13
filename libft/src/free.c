/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:20:52 by pribault          #+#    #+#             */
/*   Updated: 2017/10/18 19:59:04 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "structs.h"
#include "prototypes.h"

char	is_in_alloc(t_alloc *alloc, void *ptr)
{
	if (ptr >= alloc->ptr && (ptr < alloc->ptr + alloc->size || !alloc->size))
		return (1);
	return (0);
}

char	search_and_free(t_alloc **head, void *ptr, char state)
{
	t_alloc	*alloc;
	t_alloc	*del;

	alloc = *head;
	if (!alloc)
		return (0);
	while (!is_in_alloc(alloc, ptr) && alloc->next &&
	!is_in_alloc(alloc->next, ptr))
		alloc = alloc->next;
	if (is_in_alloc(alloc, ptr))
	{
		*head = alloc->next;
		del = alloc;
	}
	else if (alloc->next && is_in_alloc(alloc->next, ptr))
	{
		del = alloc->next;
		alloc->next = del->next;
	}
	else
		return (0);
	if (state)
		munmap(del->ptr, del->size);
	munmap(del, sizeof(t_alloc));
	return (1);
}

void	free(void *ptr)
{
	t_zone	*zone;

	pthread_mutex_lock(&g_env.mutex[1]);
	if (!ptr || search_and_free(&g_env.large, ptr, 1))
		return ((void)pthread_mutex_unlock(&g_env.mutex[1]));
	zone = g_env.tiny;
	while (zone)
	{
		if (search_and_free(&zone->allocs, ptr, 0))
			return ((void)pthread_mutex_unlock(&g_env.mutex[1]));
		zone = zone->next;
	}
	zone = g_env.small;
	while (zone)
	{
		if (search_and_free(&zone->allocs, ptr, 0))
			return ((void)pthread_mutex_unlock(&g_env.mutex[1]));
		zone = zone->next;
	}
	pthread_mutex_unlock(&g_env.mutex[1]);
	malloc_error(2, ptr);
}
