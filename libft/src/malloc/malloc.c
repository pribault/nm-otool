/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 09:58:06 by pribault          #+#    #+#             */
/*   Updated: 2018/03/15 22:32:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"
#include <stdio.h>

t_env	g_env = {NULL, NULL, NULL, PTHREAD_MUTEX_INITIALIZER,
	{
		"\e[38;5;88m\e[1m",
		"\e[38;5;208m\e[1m",
		"\e[38;5;32m\e[1m",
		"\e[0m",
		"\e[38;5;250m",
		"\e[38;5;14m",
		"\e[38;5;240m"}
};

void	*unlock_and_return(void *ptr)
{
	pthread_mutex_unlock(&g_env.mutex);
	return (ptr);
}

void	*malloc(size_t size)
{
	if (!size)
		return (NULL);
	pthread_mutex_lock(&g_env.mutex);
	if (size <= TINY)
	{
		if (!g_env.tiny)
			g_env.tiny = create_zone(TINY * ALLOCS, "TINY");
		return (unlock_and_return(allocate_in_zone(g_env.tiny, size)));
	}
	else if (size <= SMALL)
	{
		if (!g_env.small)
			g_env.small = create_zone(SMALL * ALLOCS, "SMALL");
		return (unlock_and_return(allocate_in_zone(g_env.small, size)));
	}
	else
	{
		if (!g_env.large)
			return (unlock_and_return(get_allocation(g_env.large =
			create_zone(size, "LARGE"), size)));
			return (unlock_and_return(allocate_large(g_env.large, size)));
	}
	return (unlock_and_return(NULL));
}

void	*realloc(void *ptr, size_t size)
{
	void	*result;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_env.mutex);
	if (!(result = realloc_in_zones(g_env.tiny, ptr, size)) &&
		!(result = realloc_in_zones(g_env.small, ptr, size)) &&
		!(result = realloc_in_zones(g_env.large, ptr, size)))
	{
		malloc_error(ERROR_INVALID_POINTER, ptr);
		return (unlock_and_return(NULL));
	}
	return (unlock_and_return(result));
}

void	free(void *ptr)
{
	if (!ptr)
		return ;
	pthread_mutex_lock(&g_env.mutex);
	if (free_in_zones(g_env.tiny, ptr) != FT_TRUE &&
		free_in_zones(g_env.small, ptr) != FT_TRUE &&
		free_in_zones(g_env.large, ptr) != FT_TRUE)
		malloc_error(ERROR_INVALID_FREE, ptr);
	pthread_mutex_unlock(&g_env.mutex);
}

void	*calloc(size_t nmemb, size_t size)
{
	size_t	real_size;
	void	*ptr;

	if (!size)
		return (NULL);
	real_size = nmemb * size;
	if (!(ptr = malloc(real_size)))
		return (NULL);
	ft_bzero(ptr, real_size);
	return (ptr);
}
