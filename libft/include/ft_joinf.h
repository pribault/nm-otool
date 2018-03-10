/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 11:39:59 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 14:59:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JOINF_H
# define FT_JOINF_H

/*
**	includes
*/

# include "libft.h"
# include <stdarg.h>

# define WIDTH		BYTE(0)
# define PRECISION	BYTE(1)

/*
**	prototypes
*/

char	*ft_joinf(const char *format, ...);
int		ft_printj(const char *format, ...);

size_t	get_next_arg(va_list va, const char *format, size_t *i);
void	print_next_arg(va_list va, char *new, size_t *j, char c);
void	fill_string(va_list va, const char *format, char *new);

void	print_number(va_list va, char *new, size_t *j, char *base);
size_t	get_number_len(va_list va, char *base);

void	print_unsigned_base_join(va_list va, char *new, size_t *j, char *base);
size_t	get_unsigned_len(va_list va, char *base);

void	print_string(va_list va, char *new, size_t *j);
void	print_char_join(va_list va, char *new, size_t *j);
size_t	get_string_len(va_list va);

void	print_pointer(va_list va, char *new, size_t *j);
size_t	get_pointer_len(va_list va, char *base);

#endif
