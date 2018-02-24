/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:52:30 by pribault          #+#    #+#             */
/*   Updated: 2018/02/10 20:58:31 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_execute(char *file, char **arg, char **env)
{
	int		fd[2];
	char	*s;
	pid_t	pid;
	int		ret;

	s = NULL;
	if (!arg || !env || !file || pipe(fd) < 0 || (pid = fork()) < 0)
		return (NULL);
	if (!pid)
	{
		dup2(fd[1], 1);
		if (execve(file, arg, env) < 0)
			exit(1);
	}
	else
		wait4(pid, &ret, 0, NULL);
	close(fd[1]);
	ft_get_all_lines(fd[0], &s);
	close(fd[0]);
	return (s);
}
