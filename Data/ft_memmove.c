/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:40:09 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:40:11 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

void*		ft_memmove(void* destination, const void* source, size_t size)
{
	unsigned short	index;
	char* srce_char_ptr;
	char* dest_char_ptr;
	char			arr[128];

	srce_char_ptr = (char*)source;
	dest_char_ptr = (char*)destination;
	index = 0;
	while (index < size)
	{
		arr[index] = srce_char_ptr[index];
		++index;
	}
	index = 0;
	while (index < size)
	{
		dest_char_ptr[index] = arr[index];
		++index;
	}
	return (dest_char_ptr);
}
