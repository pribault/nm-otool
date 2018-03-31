/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 23:54:51 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 17:00:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static void		log_trashed(void *data, t_log *trashed)
{
	(void)data;
	(void)trashed;
}

static t_bool	malloc_log_enabled(void)
{
	static t_bool	enabled = FT_FALSE;
	static char		*env = NULL;

	if (!env)
	{
		if (!(env = ft_getenv(g_env.env, "MALLOC_LOG")))
			enabled = FT_TRUE;
		else
			enabled = (ft_atou(env)) ? FT_TRUE : FT_FALSE;
	}
	return (enabled);
}

void			malloc_log(t_log_type type, uint64_t ptr, uint64_t size)
{
	static t_bool	init = FT_FALSE;
	t_log			log;
	char			*env;

	if (malloc_log_enabled() == FT_FALSE)
		return ;
	if (init == FT_FALSE)
	{
		if ((env = ft_getenv(g_env.env, "MALLOC_LOG_SIZE")))
			ft_circ_buffer_init(&g_env.log, ALLOC_MMAP, sizeof(t_log),
			ft_atou(env));
		else
			ft_circ_buffer_init(&g_env.log, ALLOC_MMAP, sizeof(t_log),
			MALLOC_LOG_SIZE);
		ft_circ_buffer_set_trash_callback(&g_env.log, (void*)&log_trashed,
		NULL);
		init = FT_TRUE;
	}
	if (init == FT_TRUE)
	{
		log.type = type;
		log.ptr = ptr;
		log.size = size;
		ft_circ_buffer_enqueue(&g_env.log, &log);
	}
}

static void		malloc_print_log_2(t_log *log)
{
	if (log->type == LOG_CALLOC_REQUEST)
		ft_printf("calloc request for %lu bytes\n", log->size);
	else if (log->type == LOG_CALLOC_RETURN)
		ft_printf("calloc returned %p\n", log->ptr);
	else
		ft_printf("unknown log\n");
}

void			malloc_print_logs(void)
{
	t_log	*log;

	while ((log = ft_circ_buffer_dequeue(&g_env.log)))
		if (log->type == LOG_MMAP)
			ft_printf("page maped for %lu bytes\n", log->size);
		else if (log->type == LOG_MUNMAP)
			ft_printf("page unmaped at %p\n", log->ptr);
		else if (log->type == LOG_MALLOC_REQUEST)
			ft_printf("malloc request for %lu bytes\n", log->size);
		else if (log->type == LOG_MALLOC_RETURN)
			ft_printf("malloc returned %p\n", log->ptr);
		else if (log->type == LOG_FREE_REQUEST)
			ft_printf("free request for %p\n", log->ptr);
		else if (log->type == LOG_REALLOC_REQUEST)
			ft_printf("realloc request at %p for %lu bytes\n", log->ptr,
			log->size);
		else if (log->type == LOG_REALLOC_RETURN)
			ft_printf("realloc returned %p\n", log->ptr);
		else if (log->type == LOG_VALLOC_REQUEST)
			ft_printf("valloc request for %lu bytes\n", log->size);
		else if (log->type == LOG_VALLOC_RETURN)
			ft_printf("valloc returned %p\n", log->ptr);
		else
			malloc_print_log_2(log);
}
