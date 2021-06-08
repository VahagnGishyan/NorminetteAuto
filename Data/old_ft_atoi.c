/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:19:09 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:23:38 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		my_iswspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

int		ft_atoi(const char *str)
{
	unsigned short	index;
	unsigned short	negative;
	unsigned short	result;

	index = 0;
	negative = 1;
	result = 0;
	while (my_iswspace(str[index] ))
		++index;
	if (str[index] == '+' || str[index] == '-')
		if (str[index++] == '-')
		negative *= -1;
	while (ft_isdigit(str[index] ))
	{
		result *= 10;
		result += str[index] - '0';
		++index;
	}
	return (result *negative);
}
