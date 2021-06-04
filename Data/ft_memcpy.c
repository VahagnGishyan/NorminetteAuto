/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:38:45 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:38:47 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

void*		ft_memcpy(void* destination, const void* source, size_t size) 
{
	unsigned short	index;
	char* dest_ptr;
	const char* srce_ptr;

	dest_ptr = (char*)destination;
	srce_ptr = (const char*)source;
	if (dest_ptr == NULL || srce_ptr == NULL)
		return NULL;
	index = 0;
	while (srce_ptr[index] != '\0' && index != size)
		dest_ptr[index] = srce_ptr[++index];
	if (srce_ptr[index] == '\0')
		dest_ptr[index] = srce_ptr[index];
	return (dest_ptr);
}
