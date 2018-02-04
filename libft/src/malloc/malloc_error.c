/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 10:46:23 by pribault          #+#    #+#             */
/*   Updated: 2017/10/01 16:07:21 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "structs.h"
#include "prototypes.h"

void	*malloc_error(int error, void *param)
{
	char	*env;

	env = getenv("MALLOC_DEBUG");
	if (!env)
		return (NULL);
	if (!ft_strcmp(env, "1") || !ft_strcmp(env, "3"))
	{
		ft_putstr("\033[38;5;124m");
		if (error == 1)
			ft_putendl("malloc error: cannot allocate memory");
		else if (error == 2)
			ft_printf("malloc error: invalid free: %p\n", param);
		else if (error == 3)
			ft_printf("malloc error: invalid pointer to realloc: %p", param);
		ft_putstr("\033[0m");
	}
	if (!ft_strcmp(env, "2") || !ft_strcmp(env, "3"))
		abort();
	return (NULL);
}
