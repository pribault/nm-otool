/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:51:11 by pribault          #+#    #+#             */
/*   Updated: 2018/02/24 11:49:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_enum_func	g_test_func[] =
{
	{PARAM_STR, NULL},
	{PARAM_INTEGER, (void*)&ft_isinteger},
	{PARAM_UNSIGNED, (void*)&ft_isunsigned},
	{PARAM_FLOAT, (void*)&ft_isfloat}
};

static int			g_error_codes[] =
{
	ERROR_STR,
	ERROR_INTEGER,
	ERROR_UNSIGNED,
	ERROR_FLOAT
};

static void	ft_get_short_flag(char c, t_short_flag *flags, void *data)
{
	uint64_t	x;
	size_t		i;

	i = -1;
	if (!flags)
		return ;
	while (flags[++i].function)
		if (flags[i].c == c)
			return ((flags[i].function) ? flags[i].function(data) : (void)0);
	ft_error(2, ERROR_UNKNOWN_SHORT_FLAG, (void*)(x = c));
}

static int	ft_test_long_flag(t_long_flag *flag, char **argv)
{
	t_bool		boolean;
	uint64_t	x;
	int			type;
	int			j;

	j = -1;
	boolean = FT_TRUE;
	while (++j < flag->n_params)
	{
		if ((type = flag->params_type[j]) >= PARAM_MAX)
		{
			ft_error(2, ERROR_UNKNOW_PARAMETER_TYPE, (void*)(x = type));
			boolean = FT_FALSE;
		}
		else if (g_test_func[type].function &&
			!g_test_func[type].function(argv[j]))
		{
			ft_error(2, g_error_codes[type], argv[j]);
			boolean = FT_FALSE;
		}
	}
	return (boolean);
}

static int	ft_get_long_flag(int argc, char **argv, t_long_flag *flags,
		void *data)
{
	size_t	i;

	i = -1;
	if (!flags)
		return (0);
	while (flags[++i].function)
		if (!ft_strcmp(&argv[0][2], flags[i].str))
		{
			if (flags[i].n_params >= argc)
			{
				ft_error(2, ERROR_NOT_ENOUGHT_PARAM, &argv[0][2]);
				return (0);
			}
			if (!ft_test_long_flag(&flags[i], &argv[1]))
				return (flags[i].n_params);
			flags[i].function(data, &argv[1], flags[i].n_params);
			return (flags[i].n_params);
		}
	ft_error(2, ERROR_UNKNOWN_LONG_FLAG, &argv[0][2]);
	return (0);
}

void		ft_get_flags(int argc, char **argv, t_flags *flags, void *data)
{
	size_t	len;
	size_t	j;
	int		i;

	i = 0;
	if (!flags || !argv)
		return ;
	while (++i < argc)
	{
		if (!ft_strncmp(argv[i], "--", 2))
			i += ft_get_long_flag(argc - i, &argv[i], flags->longs, data);
		else if (argv[i][0] == '-')
		{
			j = 0;
			len = ft_strlen(argv[i]);
			while (++j < len)
				ft_get_short_flag(argv[i][j], flags->shorts, data);
		}
		else if (flags->def)
			flags->def(argv[i], data);
		else
			ft_error(2, ERROR_UNKNOWN_PARAMETER, argv[i]);
	}
}
