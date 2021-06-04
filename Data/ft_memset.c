/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgishyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 23:40:32 by vgishyan          #+#    #+#             */
/*   Updated: 2021/06/03 23:40:36 by vgishyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

void*		ft_memset(void* destination, int value, size_t size)
{
	unsigned short index;

	if (destination == NULL)
		return destination;
	index = 0;
	while (index < size)
	{
		((unsigned char*)destination)[index] = value;
		++index;
	}

	return (destination);
}
