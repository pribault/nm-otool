/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 13:04:57 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 21:04:43 by pribault         ###   ########.fr       */
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
}					t_env;

extern t_env		g_env;

#endif
