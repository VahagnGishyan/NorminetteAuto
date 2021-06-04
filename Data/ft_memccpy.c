/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:37:32 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:37:35 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

void*		ft_memccpy(void* destination, const void* source, int value, size_t size)
{
	unsigned short	index;
	unsigned char	symbol;
	char* dest_ptr;
	const char* srce_ptr;

	index = 0;
	symbol = (char)value;
	dest_ptr = (char*)destination;
	srce_ptr = (const char*)source;
	while (index < size)
	{
		dest_ptr[index] = srce_ptr[index];
		if (dest_ptr[index] == symbol)
			return (dest_ptr + index + 1);
		++index;
	}
	return (NULL);
}
