/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 09:58:00 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 11:51:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <inttypes.h>

void		*malloc(size_t size);
void		*calloc(size_t nmemb, size_t size);
void		*realloc(void *ptr, size_t size);
void		*reallocf(void *ptr, size_t size);
void		free(void *ptr);

void		show_alloc_mem(void);
void		show_alloc_mem_ex(void);

void		malloc_print_logs(void);

void		malloc_set_env(char **env);

#endif
