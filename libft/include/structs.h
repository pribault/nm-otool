/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 13:04:57 by pribault          #+#    #+#             */
/*   Updated: 2018/04/01 19:58:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

# define TINY				64
# define SMALL				512
# define ALLOCS				128

# define LINE_FEED			16

# define TYPE_FREE			0
# define TYPE_ALLOC			1

# define COLORS				16

# define DEFAULT_PADDING	8

# define REALLOC_MULTIPLIER	2

# define MALLOC_LOG_SIZE	1024

typedef enum		e_log_type
{
	LOG_MALLOC_REQUEST,
	LOG_MALLOC_RETURN,
	LOG_REALLOC_REQUEST,
	LOG_REALLOC_RETURN,
	LOG_REALLOCF_REQUEST,
	LOG_REALLOCF_RETURN,
	LOG_CALLOC_REQUEST,
	LOG_CALLOC_RETURN,
	LOG_VALLOC_REQUEST,
	LOG_VALLOC_RETURN,
	LOG_FREE_REQUEST,
	LOG_MMAP,
	LOG_MUNMAP
}					t_log_type;

typedef struct		s_log
{
	t_log_type		type;
	uint64_t		ptr;
	uint64_t		size;
}					t_log;

typedef struct		s_alloc
{
	size_t			size;
	uint8_t			type;
}					t_alloc;

typedef struct		s_zone
{
	size_t			size;
	struct s_zone	*next;
	char			*name;
}					t_zone;

typedef struct		s_env
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*large;
	pthread_mutex_t	mutex;
	char			*colors[COLORS];
	t_circ_buffer	log;
	char			**env;
}					t_env;

extern t_env		g_env;

#endif
