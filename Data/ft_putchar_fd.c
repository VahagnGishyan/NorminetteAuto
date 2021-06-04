/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:41:19 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:41:25 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

const int g_utf8_cp1 = 0x80;
const int g_utf8_bx = 0x80;
const int g_utf8_b2 = 0xC0;

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	chr;

	if ((unsigned char)c >= g_utf8_cp1)
	{
		chr = (unsigned char)c / 0x40 + g_utf8_b2;
		write(fd, &chr, 1);
		chr = (unsigned char)c % 0x40 + g_utf8_bx;
		write(fd, &chr, 1);
	}
	else
	{
		write(fd, &c, 1);
	}
}
