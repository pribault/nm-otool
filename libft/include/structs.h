/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 13:04:57 by pribault          #+#    #+#             */
/*   Updated: 2017/10/18 20:35:04 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

# define TINY		128
# define SMALL		1024
# define ALLOCS		256

# define LINE_FEED	16

typedef struct		s_alloc
{
	void			*ptr;
	size_t			size;
	struct s_alloc	*next;
}					t_alloc;

typedef struct		s_zone
{
	void			*ptr;
	size_t			size;
	t_alloc			*allocs;
	struct s_zone	*next;
}					t_zone;

/*
**	mutex[0]: malloc
**	mutex[1]: free
**	mutex[2]: calloc
**	mutex[3]: realloc
*/

typedef struct		s_env
{
	t_zone			*tiny;
	t_zone			*small;
	t_alloc			*large;
	pthread_mutex_t	mutex[4];
}					t_env;

extern t_env		g_env;

#endif
