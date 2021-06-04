/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:37:47 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:37:49 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

void*		ft_memchr(const void* string, int value, size_t size)
{
	unsigned const char*	new_string;
	char			symbol;

	symbol = (char)value;
	new_string = (unsigned const char*)string;
	while (size--)
	{
		if (*new_string == symbol)
			return ((void*)new_string);
		++new_string;
	}
	return (NULL);
}
