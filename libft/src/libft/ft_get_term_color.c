/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_term_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:04:16 by pribault          #+#    #+#             */
/*   Updated: 2018/04/29 12:19:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_overwrite(char *s, uint8_t n)
{
	s[0] = '0' + ((n / 100) % 10);
	s[1] = '0' + ((n / 10) % 10);
	s[2] = '0' + (n % 10);
}

char		*ft_get_term_color(t_color front, t_color back,
			t_color_effect effect)
{
	static char	s1[] = "\e[38;5;000m";
	static char	s2[] = "\e[000m\e[38;5;000m\e[48;5;000m";

	front.r = (front.r * 6) / 256;
	front.g = (front.g * 6) / 256;
	front.b = (front.b * 6) / 256;
	back.r = (back.r * 6) / 256;
	back.g = (back.g * 6) / 256;
	back.b = (back.b * 6) / 256;
	if (effect == EFFECT_NOBACK)
	{
		ft_overwrite(&s1[7], 16 + front.r * 36 + front.g * 6 + front.b);
		return ((char*)&s1);
	}
	ft_overwrite(&s2[2], effect);
	ft_overwrite(&s2[13], 16 + front.r * 36 + front.g * 6 + front.b);
	ft_overwrite(&s2[24], 16 + back.r * 36 + back.g * 6 + back.b);
	return ((char*)&s2);
}
