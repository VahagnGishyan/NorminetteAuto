/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:42:54 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:42:56 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char* s, int fd)
{
	unsigned char* str;

	if (!(s))
	    return;
	str = (unsigned char*)s;
	while (*str)
		ft_putchar_fd(*str++, fd);
}
